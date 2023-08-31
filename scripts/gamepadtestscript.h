#pragma once
#include "../Core/Common/resources/ntshengn_resources_scripting.h"
#include "../Core/Common/module_interfaces/ntshengn_graphics_module_interface.h"
#include "../Core/Common/module_interfaces/ntshengn_window_module_interface.h"

using namespace NtshEngn;
struct GamepadTestScript : public Script {
	NTSHENGN_SCRIPT(GamepadTestScript);

	void init() {
		if (windowModule && windowModule->isWindowOpen(windowModule->getMainWindowID())) {
			windowModule->setWindowResizable(windowModule->getMainWindowID(), false);
		}

		if (graphicsModule) {
			m_font = graphicsModule->load(*assetManager->loadFont("assets/fonts/JetBrainsMono-Regular.ttf", 32.0f));

			m_controllerImage = graphicsModule->load(*assetManager->loadImage("assets/images/controller.png"));

			m_buttonImage = graphicsModule->load(*assetManager->loadImage("assets/images/button.png"));

			m_startSelectImage = graphicsModule->load(*assetManager->loadImage("assets/images/start_select.png"));

			m_bumperImage = graphicsModule->load(*assetManager->loadImage("assets/images/bumper.png"));

			m_triggerImage = graphicsModule->load(*assetManager->loadImage("assets/images/trigger.png"));

			m_dPadImage = graphicsModule->load(*assetManager->loadImage("assets/images/dpad.png"));

			m_stickImage = graphicsModule->load(*assetManager->loadImage("assets/images/stick.png"));
		}
	}

	void update(double dt) {
		NTSHENGN_UNUSED(dt);

		if (windowModule && graphicsModule) {
			const Math::vec2 windowSize = Math::vec2(static_cast<float>(windowModule->getWindowWidth(windowModule->getMainWindowID())), static_cast<float>(windowModule->getWindowHeight(windowModule->getMainWindowID())));

			graphicsModule->drawUIImage(m_controllerImage, ImageSamplerFilter::Nearest, windowSize / 2.0f, 0.0f, Math::vec2(2.0f), Math::vec4(1.0f));

			std::vector<GamepadID> gamepads = windowModule->getConnectedGamepads();
			graphicsModule->drawUIText(m_font, gamepads.empty() ? "No gamepad is detected." : windowModule->getGamepadName(gamepads[0]), Math::vec2(30.0f, 30.0f), Math::vec4(1.0f));

			if (!gamepads.empty()) {
				// Face buttons
				graphicsModule->drawUIImage(m_buttonImage, ImageSamplerFilter::Nearest, Math::vec2(791.0f, 343.0f), 0.0f, Math::vec2(2.0f), getColorByState(windowModule->getGamepadButtonState(gamepads[0], InputGamepadButton::Face1)));
				graphicsModule->drawUIImage(m_buttonImage, ImageSamplerFilter::Nearest, Math::vec2(829.0f, 305.0f), 0.0f, Math::vec2(2.0f), getColorByState(windowModule->getGamepadButtonState(gamepads[0], InputGamepadButton::Face2)));
				graphicsModule->drawUIImage(m_buttonImage, ImageSamplerFilter::Nearest, Math::vec2(753.0f, 305.0f), 0.0f, Math::vec2(2.0f), getColorByState(windowModule->getGamepadButtonState(gamepads[0], InputGamepadButton::Face3)));
				graphicsModule->drawUIImage(m_buttonImage, ImageSamplerFilter::Nearest, Math::vec2(791.0f, 265.0f), 0.0f, Math::vec2(2.0f), getColorByState(windowModule->getGamepadButtonState(gamepads[0], InputGamepadButton::Face4)));

				// Start and select buttons
				graphicsModule->drawUIImage(m_startSelectImage, ImageSamplerFilter::Nearest, Math::vec2(684.0f, 304.0f), 0.0f, Math::vec2(2.0f), getColorByState(windowModule->getGamepadButtonState(gamepads[0], InputGamepadButton::Start)));
				graphicsModule->drawUIImage(m_startSelectImage, ImageSamplerFilter::Nearest, Math::vec2(602.0f, 304.0f), 0.0f, Math::vec2(2.0f), getColorByState(windowModule->getGamepadButtonState(gamepads[0], InputGamepadButton::Select)));

				// Bumpers
				graphicsModule->drawUIImage(m_bumperImage, ImageSamplerFilter::Nearest, Math::vec2(498.0f, 212.0f), 0.0f, Math::vec2(2.0f), getColorByState(windowModule->getGamepadButtonState(gamepads[0], InputGamepadButton::LeftBumper)));
				graphicsModule->drawUIImage(m_bumperImage, ImageSamplerFilter::Nearest, Math::vec2(782.0f, 212.0f), 0.0f, Math::vec2(-2.0f, 2.0f), getColorByState(windowModule->getGamepadButtonState(gamepads[0], InputGamepadButton::RightBumper)));

				// Triggers
				graphicsModule->drawUIImage(m_triggerImage, ImageSamplerFilter::Nearest, Math::vec2(499.0f, 162.0f), 0.0f, Math::vec2(2.0f), Math::vec4(1.0f, 0.0f, 0.0f, windowModule->getGamepadLeftTrigger(gamepads[0])));
				graphicsModule->drawUIImage(m_triggerImage, ImageSamplerFilter::Nearest, Math::vec2(781.0f, 162.0f), 0.0f, Math::vec2(-2.0f, 2.0f), Math::vec4(1.0f, 0.0f, 0.0f, windowModule->getGamepadRightTrigger(gamepads[0])));

				// D-Pad
				graphicsModule->drawUIImage(m_dPadImage, ImageSamplerFilter::Nearest, Math::vec2(561.0f, 375.0f), 0.0f, Math::vec2(2.0f), getColorByState(windowModule->getGamepadButtonState(gamepads[0], InputGamepadButton::DPadUp)));
				graphicsModule->drawUIImage(m_dPadImage, ImageSamplerFilter::Nearest, Math::vec2(583.0f, 397.0f), Math::toRad(90.0f), Math::vec2(2.0f), getColorByState(windowModule->getGamepadButtonState(gamepads[0], InputGamepadButton::DPadRight)));
				graphicsModule->drawUIImage(m_dPadImage, ImageSamplerFilter::Nearest, Math::vec2(561.0f, 419.0f), Math::toRad(180.0f), Math::vec2(2.0f), getColorByState(windowModule->getGamepadButtonState(gamepads[0], InputGamepadButton::DPadDown)));
				graphicsModule->drawUIImage(m_dPadImage, ImageSamplerFilter::Nearest, Math::vec2(539.0f, 397.0f), Math::toRad(270.0f), Math::vec2(2.0f), getColorByState(windowModule->getGamepadButtonState(gamepads[0], InputGamepadButton::DPadLeft)));

				// Sticks
				graphicsModule->drawUIImage(m_stickImage, ImageSamplerFilter::Nearest, Math::vec2(487.0f + (20.0f * windowModule->getGamepadStickAxisX(gamepads[0], InputGamepadStick::Left)), 305.0f + (20.0f * windowModule->getGamepadStickAxisY(gamepads[0], InputGamepadStick::Left))), 0.0f, Math::vec2(2.0f), getColorByStateStick(windowModule->getGamepadButtonState(gamepads[0], InputGamepadButton::LeftStick)));
				graphicsModule->drawUIImage(m_stickImage, ImageSamplerFilter::Nearest, Math::vec2(717.0f + (20.0f * windowModule->getGamepadStickAxisX(gamepads[0], InputGamepadStick::Right)), 391.0f + (20.0f * windowModule->getGamepadStickAxisY(gamepads[0], InputGamepadStick::Right))), 0.0f, Math::vec2(2.0f), getColorByStateStick(windowModule->getGamepadButtonState(gamepads[0], InputGamepadButton::RightStick)));
			}
		}
	}

	void destroy() {
	}

private:
	Math::vec4 getColorByState(InputState state) {
		if (state == InputState::Pressed) {
			return Math::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		}
		else if (state == InputState::Held) {
			return Math::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		}
		else if (state == InputState::Released) {
			return Math::vec4(1.0f, 1.0f, 0.0f, 1.0f);
		}

		return Math::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	Math::vec4 getColorByStateStick(InputState state) {
		if (state == InputState::Pressed) {
			return Math::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		}
		else if (state == InputState::Held) {
			return Math::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		}
		else if (state == InputState::Released) {
			return Math::vec4(1.0f, 1.0f, 0.0f, 1.0f);
		}

		return Math::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

private:
	FontID m_font;

	ImageID m_controllerImage;

	ImageID m_buttonImage;

	ImageID m_startSelectImage;

	ImageID m_bumperImage;

	ImageID m_triggerImage;

	ImageID m_dPadImage;

	ImageID m_stickImage;
};
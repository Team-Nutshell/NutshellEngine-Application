#pragma once
#include "../Core/scripting/ntshengn_scripting_api.h"

using namespace NtshEngn;
struct GamepadTestScript : public ScriptingAPI {
	NTSHENGN_SCRIPT(GamepadTestScript);

	void init() {
		setWindowResizable(false);

		m_font = getFontID(*loadFont("assets/fonts/JetBrainsMono-Regular.ttf", 32.0f));

		m_controllerImage = getImageID(*loadImage("assets/images/controller.png"));

		m_buttonImage = getImageID(*loadImage("assets/images/button.png"));

		m_startSelectImage = getImageID(*loadImage("assets/images/start_select.png"));

		m_bumperImage = getImageID(*loadImage("assets/images/bumper.png"));

		m_triggerImage = getImageID(*loadImage("assets/images/trigger.png"));

		m_dPadImage = getImageID(*loadImage("assets/images/dpad.png"));

		m_stickImage = getImageID(*loadImage("assets/images/stick.png"));
	}

	void update(double dt) {
		NTSHENGN_UNUSED(dt);

		const Math::vec2 windowSize = Math::vec2(static_cast<float>(getWindowWidth()), static_cast<float>(getWindowHeight()));

		drawUIImage(m_controllerImage, ImageSamplerFilter::Nearest, windowSize / 2.0f, 0.0f, Math::vec2(2.0f), Math::vec4(1.0f));

		std::vector<GamepadID> gamepads = getConnectedGamepads();
		drawUIText(m_font, gamepads.empty() ? "No gamepad is detected." : getGamepadName(gamepads[0]), Math::vec2(30.0f, 30.0f), Math::vec4(1.0f));

		if (!gamepads.empty()) {
			// Face buttons
			drawUIImage(m_buttonImage, ImageSamplerFilter::Nearest, Math::vec2(791.0f, 343.0f), 0.0f, Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[0], InputGamepadButton::Face1)));
			drawUIImage(m_buttonImage, ImageSamplerFilter::Nearest, Math::vec2(829.0f, 305.0f), 0.0f, Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[0], InputGamepadButton::Face2)));
			drawUIImage(m_buttonImage, ImageSamplerFilter::Nearest, Math::vec2(753.0f, 305.0f), 0.0f, Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[0], InputGamepadButton::Face3)));
			drawUIImage(m_buttonImage, ImageSamplerFilter::Nearest, Math::vec2(791.0f, 265.0f), 0.0f, Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[0], InputGamepadButton::Face4)));

			// Guide button
			drawUIImage(m_buttonImage, ImageSamplerFilter::Nearest, Math::vec2(643.0f, 241.0f), 0.0f, Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[0], InputGamepadButton::Guide)));

			// Start and select buttons
			drawUIImage(m_startSelectImage, ImageSamplerFilter::Nearest, Math::vec2(684.0f, 304.0f), 0.0f, Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[0], InputGamepadButton::Start)));
			drawUIImage(m_startSelectImage, ImageSamplerFilter::Nearest, Math::vec2(602.0f, 304.0f), 0.0f, Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[0], InputGamepadButton::Select)));

			// Bumpers
			drawUIImage(m_bumperImage, ImageSamplerFilter::Nearest, Math::vec2(498.0f, 212.0f), 0.0f, Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[0], InputGamepadButton::LeftBumper)));
			drawUIImage(m_bumperImage, ImageSamplerFilter::Nearest, Math::vec2(782.0f, 212.0f), 0.0f, Math::vec2(-2.0f, 2.0f), getColorByState(getGamepadButtonState(gamepads[0], InputGamepadButton::RightBumper)));

			// Triggers
			drawUIImage(m_triggerImage, ImageSamplerFilter::Nearest, Math::vec2(499.0f, 162.0f), 0.0f, Math::vec2(2.0f), Math::vec4(1.0f, 0.0f, 0.0f, getGamepadLeftTrigger(gamepads[0])));
			drawUIImage(m_triggerImage, ImageSamplerFilter::Nearest, Math::vec2(781.0f, 162.0f), 0.0f, Math::vec2(-2.0f, 2.0f), Math::vec4(1.0f, 0.0f, 0.0f, getGamepadRightTrigger(gamepads[0])));

			// D-Pad
			drawUIImage(m_dPadImage, ImageSamplerFilter::Nearest, Math::vec2(561.0f, 375.0f), 0.0f, Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[0], InputGamepadButton::DPadUp)));
			drawUIImage(m_dPadImage, ImageSamplerFilter::Nearest, Math::vec2(583.0f, 397.0f), Math::toRad(90.0f), Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[0], InputGamepadButton::DPadRight)));
			drawUIImage(m_dPadImage, ImageSamplerFilter::Nearest, Math::vec2(561.0f, 419.0f), Math::toRad(180.0f), Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[0], InputGamepadButton::DPadDown)));
			drawUIImage(m_dPadImage, ImageSamplerFilter::Nearest, Math::vec2(539.0f, 397.0f), Math::toRad(270.0f), Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[0], InputGamepadButton::DPadLeft)));

			// Sticks
			drawUIImage(m_stickImage, ImageSamplerFilter::Nearest, Math::vec2(487.0f + (20.0f * getGamepadStickAxisX(gamepads[0], InputGamepadStick::Left)), 305.0f + (20.0f * getGamepadStickAxisY(gamepads[0], InputGamepadStick::Left))), 0.0f, Math::vec2(2.0f), getColorByStateStick(getGamepadButtonState(gamepads[0], InputGamepadButton::LeftStick)));
			drawUIImage(m_stickImage, ImageSamplerFilter::Nearest, Math::vec2(717.0f + (20.0f * getGamepadStickAxisX(gamepads[0], InputGamepadStick::Right)), 391.0f + (20.0f * getGamepadStickAxisY(gamepads[0], InputGamepadStick::Right))), 0.0f, Math::vec2(2.0f), getColorByStateStick(getGamepadButtonState(gamepads[0], InputGamepadButton::RightStick)));
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
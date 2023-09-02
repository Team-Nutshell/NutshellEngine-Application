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

		for (uint8_t i = 0; i < 4; i++) {
			if (drawUIButton(Math::vec2(20.0f + (75.0f * static_cast<float>(i)), 650.0f), Math::vec2(50.0f, 50.0f), Math::vec4(0.1f, 0.1f, 0.1f, 1.0f), InputMouseButton::One)) {
				m_activeGamepad = static_cast<size_t>(i);
			}
			drawUIText(m_font, std::to_string(i), Math::vec2(37.0f + (75.0f * static_cast<float>(i)), 685.0f), Math::vec4((gamepads.size() > static_cast<size_t>(i)) ? Math::vec2(0.0f, 1.0f) : Math::vec2(1.0, 0.0f), 0.0f, 1.0f));
		}

		drawUIText(m_font, "[" + std::to_string(m_activeGamepad) + "] " + ((gamepads.size() <= m_activeGamepad) ? "No gamepad is detected." : getGamepadName(gamepads[m_activeGamepad])), Math::vec2(5.0f, 30.0f), Math::vec4(1.0f));
		if (gamepads.size() > m_activeGamepad) {
			// Face buttons
			drawUIImage(m_buttonImage, ImageSamplerFilter::Nearest, Math::vec2(791.0f, 343.0f), 0.0f, Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[m_activeGamepad], InputGamepadButton::Face1)));
			drawUIImage(m_buttonImage, ImageSamplerFilter::Nearest, Math::vec2(829.0f, 305.0f), 0.0f, Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[m_activeGamepad], InputGamepadButton::Face2)));
			drawUIImage(m_buttonImage, ImageSamplerFilter::Nearest, Math::vec2(753.0f, 305.0f), 0.0f, Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[m_activeGamepad], InputGamepadButton::Face3)));
			drawUIImage(m_buttonImage, ImageSamplerFilter::Nearest, Math::vec2(791.0f, 265.0f), 0.0f, Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[m_activeGamepad], InputGamepadButton::Face4)));

			// Guide button
			drawUIImage(m_buttonImage, ImageSamplerFilter::Nearest, Math::vec2(643.0f, 241.0f), 0.0f, Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[m_activeGamepad], InputGamepadButton::Guide)));

			// Start and select buttons
			drawUIImage(m_startSelectImage, ImageSamplerFilter::Nearest, Math::vec2(684.0f, 304.0f), 0.0f, Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[m_activeGamepad], InputGamepadButton::Start)));
			drawUIImage(m_startSelectImage, ImageSamplerFilter::Nearest, Math::vec2(602.0f, 304.0f), 0.0f, Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[m_activeGamepad], InputGamepadButton::Select)));

			// Bumpers
			drawUIImage(m_bumperImage, ImageSamplerFilter::Nearest, Math::vec2(498.0f, 212.0f), 0.0f, Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[m_activeGamepad], InputGamepadButton::LeftBumper)));
			drawUIImage(m_bumperImage, ImageSamplerFilter::Nearest, Math::vec2(782.0f, 212.0f), 0.0f, Math::vec2(-2.0f, 2.0f), getColorByState(getGamepadButtonState(gamepads[m_activeGamepad], InputGamepadButton::RightBumper)));

			// Triggers
			drawUIImage(m_triggerImage, ImageSamplerFilter::Nearest, Math::vec2(499.0f, 162.0f), 0.0f, Math::vec2(2.0f), Math::vec4(1.0f, 0.0f, 0.0f, getGamepadLeftTrigger(gamepads[m_activeGamepad])));
			drawUIImage(m_triggerImage, ImageSamplerFilter::Nearest, Math::vec2(781.0f, 162.0f), 0.0f, Math::vec2(-2.0f, 2.0f), Math::vec4(1.0f, 0.0f, 0.0f, getGamepadRightTrigger(gamepads[m_activeGamepad])));

			// D-Pad
			drawUIImage(m_dPadImage, ImageSamplerFilter::Nearest, Math::vec2(561.0f, 375.0f), 0.0f, Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[m_activeGamepad], InputGamepadButton::DPadUp)));
			drawUIImage(m_dPadImage, ImageSamplerFilter::Nearest, Math::vec2(583.0f, 397.0f), Math::toRad(90.0f), Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[m_activeGamepad], InputGamepadButton::DPadRight)));
			drawUIImage(m_dPadImage, ImageSamplerFilter::Nearest, Math::vec2(561.0f, 419.0f), Math::toRad(180.0f), Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[m_activeGamepad], InputGamepadButton::DPadDown)));
			drawUIImage(m_dPadImage, ImageSamplerFilter::Nearest, Math::vec2(539.0f, 397.0f), Math::toRad(270.0f), Math::vec2(2.0f), getColorByState(getGamepadButtonState(gamepads[m_activeGamepad], InputGamepadButton::DPadLeft)));

			// Sticks
			drawUIImage(m_stickImage, ImageSamplerFilter::Nearest, Math::vec2(487.0f + (20.0f * getGamepadStickAxisX(gamepads[m_activeGamepad], InputGamepadStick::Left)), 305.0f + (20.0f * getGamepadStickAxisY(gamepads[m_activeGamepad], InputGamepadStick::Left))), 0.0f, Math::vec2(2.0f), getColorByStateStick(getGamepadButtonState(gamepads[m_activeGamepad], InputGamepadButton::LeftStick)));
			drawUIImage(m_stickImage, ImageSamplerFilter::Nearest, Math::vec2(717.0f + (20.0f * getGamepadStickAxisX(gamepads[m_activeGamepad], InputGamepadStick::Right)), 391.0f + (20.0f * getGamepadStickAxisY(gamepads[m_activeGamepad], InputGamepadStick::Right))), 0.0f, Math::vec2(2.0f), getColorByStateStick(getGamepadButtonState(gamepads[m_activeGamepad], InputGamepadButton::RightStick)));

			// Values
			drawUIText(m_font, "Left Stick: [" + std::to_string(getGamepadStickAxisX(gamepads[m_activeGamepad], InputGamepadStick::Left)) + "; " + std::to_string(getGamepadStickAxisY(gamepads[m_activeGamepad], InputGamepadStick::Left)) + "]", Math::vec2(5.0, 80.0f), Math::vec4(1.0f));
			drawUIText(m_font, "Right Stick: [" + std::to_string(getGamepadStickAxisX(gamepads[m_activeGamepad], InputGamepadStick::Right)) + "; " + std::to_string(getGamepadStickAxisY(gamepads[m_activeGamepad], InputGamepadStick::Right)) + "]", Math::vec2(5.0, 110.0f), Math::vec4(1.0f));
			drawUIText(m_font, "Left Trigger: " + std::to_string(getGamepadLeftTrigger(gamepads[m_activeGamepad])), Math::vec2(5.0, 140.0f), Math::vec4(1.0f));
			drawUIText(m_font, "Right Trigger: " + std::to_string(getGamepadRightTrigger(gamepads[m_activeGamepad])), Math::vec2(5.0, 170.0f), Math::vec4(1.0f));
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
	size_t m_activeGamepad = 0;

	FontID m_font;

	ImageID m_controllerImage;

	ImageID m_buttonImage;

	ImageID m_startSelectImage;

	ImageID m_bumperImage;

	ImageID m_triggerImage;

	ImageID m_dPadImage;

	ImageID m_stickImage;
};
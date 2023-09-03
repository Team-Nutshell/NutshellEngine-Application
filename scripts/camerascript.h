#pragma once
#include "../Core/scripting/ntshengn_script.h"

using namespace NtshEngn;
struct CameraScript : public Script {
	NTSHENGN_SCRIPT(CameraScript);

	void init() {
		setCursorVisibility(!m_mouseMiddleMode);

		m_prevMouseX = getWindowWidth() / 2;
		m_prevMouseY = getWindowHeight() / 2;
		setCursorPosition(m_prevMouseX, m_prevMouseY);
	}

	void update(double dt) {
		NTSHENGN_UNUSED(dt);

		if (getKeyState(InputKeyboardKey::R) == InputState::Pressed) {
			m_mouseMiddleMode = !m_mouseMiddleMode;
			setCursorVisibility(!m_mouseMiddleMode);
			if (m_mouseMiddleMode) {
				m_prevMouseX = getWindowWidth() / 2;
				m_prevMouseY = getWindowHeight() / 2;
				setCursorPosition(m_prevMouseX, m_prevMouseY);
			}
		}

		Transform& transform = getEntityComponent<Transform>(entityID);

		const Transform& otherTransform = getEntityComponent<Transform>(m_other);

		if (m_mouseMiddleMode) {
			const int mouseX = getCursorPositionX();
			const int mouseY = getCursorPositionY();

			m_prevMouseX = getWindowWidth() / 2;
			m_prevMouseY = getWindowHeight() / 2;
			setCursorPosition(m_prevMouseX, m_prevMouseY);

			const float xOffset = (mouseX - m_prevMouseX) * m_mouseSensitivity;
			const float yOffset = (mouseY - m_prevMouseY) * m_mouseSensitivity;

			m_prevMouseX = mouseX;
			m_prevMouseY = mouseY;

			m_yaw = std::fmod(m_yaw + xOffset, 360.0f);
			m_pitch = std::max(-89.0f, std::min(89.0f, m_pitch - yOffset));
		}

		m_distance = std::max(0.0f, std::min(m_distance - getMouseScrollOffsetY(), 100.0f));

		float yawRad = Math::toRad(m_yaw);
		float pitchRad = Math::toRad(m_pitch);

		transform.position.x = std::cos(pitchRad) * std::cos(yawRad);
		transform.position.y = -std::sin(pitchRad);
		transform.position.z = std::cos(pitchRad) * std::sin(yawRad);
		transform.position *= m_distance;
		transform.position += otherTransform.position;
		transform.rotation = normalize(otherTransform.position - transform.position);
	}

	void destroy() {
	}

private:

	bool m_mouseMiddleMode = false;

	const float m_cameraSpeed = 0.0015f;
	const float m_mouseSensitivity = 0.12f;

	int m_prevMouseX = 0;
	int m_prevMouseY = 0;

	float m_yaw = 0.0f;
	float m_pitch = 0.0f;

	float m_distance = 4.0f;

	Entity m_other = 1;
};
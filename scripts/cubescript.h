#pragma once
#include "../Common/script/ntshengn_script.h"

using namespace NtshEngn;
struct CubeScript : public Script {
	NTSHENGN_SCRIPT(CubeScript);

	void init() {
	}

	void update(double dt) {
		Transform& transform = getEntityComponent<Transform>(entityID);
		Camera& camera = getEntityComponent<Camera>(m_camera);
		const float cubeSpeed = m_cubeSpeed * static_cast<float>(dt);

		if (getKeyState(InputKeyboardKey::W) == InputState::Held) {
			transform.position.x += (camera.forward.x * cubeSpeed);
			transform.position.z += (camera.forward.z * cubeSpeed);
		}
		if (getKeyState(InputKeyboardKey::S) == InputState::Held) {
			transform.position.x -= (camera.forward.x * cubeSpeed);
			transform.position.z -= (camera.forward.z * cubeSpeed);
		}
		if (getKeyState(InputKeyboardKey::A) == InputState::Held) {
			Math::vec3 t = Math::normalize(Math::vec3(-camera.forward.z, 0.0, camera.forward.x));
			transform.position.x -= (t.x * cubeSpeed);
			transform.position.z -= (t.z * cubeSpeed);
		}
		if (getKeyState(InputKeyboardKey::D) == InputState::Held) {
			Math::vec3 t = Math::normalize(Math::vec3(-camera.forward.z, 0.0, camera.forward.x));
			transform.position.x += (t.x * cubeSpeed);
			transform.position.z += (t.z * cubeSpeed);
		}
	}

	void destroy() {
	}

private:
	const float m_cubeSpeed = 0.015f;

	Entity m_camera = 0;
};
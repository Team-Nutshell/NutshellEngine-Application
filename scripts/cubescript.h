#pragma once
#include "../Core/scripting/ntshengn_scripting_api.h"

using namespace NtshEngn;
struct CubeScript : public ScriptingAPI {
	NTSHENGN_SCRIPT(CubeScript);

	void init() {
	}

	void update(double dt) {
		Transform& transform = getEntityComponent<Transform>(entityID);
		Transform& cameraTransform = getEntityComponent<Transform>(m_camera);
		const float cubeSpeed = m_cubeSpeed * static_cast<float>(dt);

		if (getKeyState(InputKeyboardKey::W) == InputState::Held) {
			transform.position.x += (cameraTransform.rotation.x * cubeSpeed);
			transform.position.z += (cameraTransform.rotation.z * cubeSpeed);
		}
		if (getKeyState(InputKeyboardKey::S) == InputState::Held) {
			transform.position.x -= (cameraTransform.rotation.x * cubeSpeed);
			transform.position.z -= (cameraTransform.rotation.z * cubeSpeed);
		}
		if (getKeyState(InputKeyboardKey::A) == InputState::Held) {
			Math::vec3 t = Math::normalize(Math::vec3(-cameraTransform.rotation.z, 0.0, cameraTransform.rotation.x));
			transform.position.x -= (t.x * cubeSpeed);
			transform.position.z -= (t.z * cubeSpeed);
		}
		if (getKeyState(InputKeyboardKey::D) == InputState::Held) {
			Math::vec3 t = Math::normalize(Math::vec3(-cameraTransform.rotation.z, 0.0, cameraTransform.rotation.x));
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
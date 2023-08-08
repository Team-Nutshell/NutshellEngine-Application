#pragma once
#include "../Core/Common/resources/ntshengn_resources_scripting.h"
#include "../Core/Common/module_interfaces/ntshengn_window_module_interface.h"
#include "../Core/Common/utils/ntshengn_utils_math.h"
#include <cmath>

struct CubeScript : public NtshEngn::Script {
	NTSHENGN_SCRIPT(CubeScript);

	void init() {
	}

	void update(double dt) {
		if (windowModule && windowModule->isOpen(windowModule->getMainWindowID())) {
			NtshEngn::Transform& transform = ecs->getComponent<NtshEngn::Transform>(entityID);
			NtshEngn::Transform& cameraTransform = ecs->getComponent<NtshEngn::Transform>(m_camera);
			const float cubeSpeed = m_cubeSpeed * static_cast<float>(dt);

			if (windowModule->getKeyState(windowModule->getMainWindowID(), NtshEngn::InputKeyboardKey::W) == NtshEngn::InputState::Held) {
				transform.position.x += (cameraTransform.rotation.x * cubeSpeed);
				transform.position.z += (cameraTransform.rotation.z * cubeSpeed);
			}
			if (windowModule->getKeyState(windowModule->getMainWindowID(), NtshEngn::InputKeyboardKey::S) == NtshEngn::InputState::Held) {
				transform.position.x -= (cameraTransform.rotation.x * cubeSpeed);
				transform.position.z -= (cameraTransform.rotation.z * cubeSpeed);
			}
			if (windowModule->getKeyState(windowModule->getMainWindowID(), NtshEngn::InputKeyboardKey::A) == NtshEngn::InputState::Held) {
				NtshEngn::Math::vec3 t = NtshEngn::Math::normalize(NtshEngn::Math::vec3(-cameraTransform.rotation.z, 0.0, cameraTransform.rotation.x));
				transform.position.x -= (t.x * cubeSpeed);
				transform.position.z -= (t.z * cubeSpeed);
			}
			if (windowModule->getKeyState(windowModule->getMainWindowID(), NtshEngn::InputKeyboardKey::D) == NtshEngn::InputState::Held) {
				NtshEngn::Math::vec3 t = NtshEngn::Math::normalize(NtshEngn::Math::vec3(-cameraTransform.rotation.z, 0.0, cameraTransform.rotation.x));
				transform.position.x += (t.x * cubeSpeed);
				transform.position.z += (t.z * cubeSpeed);
			}
		}
	}

	void destroy() {
	}

private:
	const float m_cubeSpeed = 0.015f;

	NtshEngn::Entity m_camera = 0;
};
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

			NtshEngn::Math::vec3 position = NtshEngn::Math::vec3(transform.position.data());
			NtshEngn::Math::vec3 cameraRotation = NtshEngn::Math::vec3(cameraTransform.rotation.data());
			if (windowModule->getKeyState(windowModule->getMainWindowID(), NtshEngn::InputKeyboardKey::W) == NtshEngn::InputState::Held) {
				position.x += (cameraRotation.x * cubeSpeed);
				position.z += (cameraRotation.z * cubeSpeed);
			}
			if (windowModule->getKeyState(windowModule->getMainWindowID(), NtshEngn::InputKeyboardKey::S) == NtshEngn::InputState::Held) {
				position.x -= (cameraRotation.x * cubeSpeed);
				position.z -= (cameraRotation.z * cubeSpeed);
			}
			if (windowModule->getKeyState(windowModule->getMainWindowID(), NtshEngn::InputKeyboardKey::A) == NtshEngn::InputState::Held) {
				NtshEngn::Math::vec3 t = NtshEngn::Math::normalize(NtshEngn::Math::vec3(-cameraRotation.z, 0.0, cameraRotation.x));
				position.x -= (t.x * cubeSpeed);
				position.z -= (t.z * cubeSpeed);
			}
			if (windowModule->getKeyState(windowModule->getMainWindowID(), NtshEngn::InputKeyboardKey::D) == NtshEngn::InputState::Held) {
				NtshEngn::Math::vec3 t = NtshEngn::Math::normalize(NtshEngn::Math::vec3(-cameraRotation.z, 0.0, cameraRotation.x));
				position.x += (t.x * cubeSpeed);
				position.z += (t.z * cubeSpeed);
			}

			transform.position = { position.x, position.y, position.z };
		}
	}

	void destroy() {
	}

private:
	const float m_cubeSpeed = 0.015f;

	NtshEngn::Entity m_camera = 0;
};
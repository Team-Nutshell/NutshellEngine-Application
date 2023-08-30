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
			m_controllerImage = graphicsModule->load(*assetManager->loadImage("assets/images/controller.png"));
		}
	}

	void update(double dt) {
		NTSHENGN_UNUSED(dt);

		if (windowModule && graphicsModule) {
			const Math::vec2 windowSize = Math::vec2(windowModule->getWindowWidth(windowModule->getMainWindowID()), windowModule->getWindowHeight(windowModule->getMainWindowID()));

			graphicsModule->drawUIImage(m_controllerImage, ImageSamplerFilter::Nearest, windowSize / 2.0f, 0.0f, Math::vec2(1.0f), Math::vec4(1.0f));

			std::vector<GamepadID> gamepads = windowModule->getConnectedGamepads();
			if (!gamepads.empty()) {

			}
		}
	}

	void destroy() {
	}

private:
	ImageID m_controllerImage;
};
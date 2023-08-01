#include "Core/src/ntshengn_core.h"

int main() {
	NtshEngn::Core core;

	// Initialize
	core.init();

	// Scene
	core.getSceneManager()->goToScene("assets/scenes/scene.ntsn");

	// Loop
	core.update();

	// Destroy
	core.destroy();

	return 0;
}
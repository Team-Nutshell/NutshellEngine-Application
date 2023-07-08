#include "Core/src/ntshengn_core.h"

int main() {
	NtshEngn::Core core;

	// Initialize
	core.init();

	// Loop
	core.update();

	// Destroy
	core.destroy();

	return 0;
}
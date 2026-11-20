#include "tentrillion_error_reporter.hpp"
#include <cstddef>

constexpr const char *tentrillion_error_reporter_title =
	"TenTrillion Game Engine Error Reporter";

bool check_if_launched_by_parent_tentrillion() { // TODO
	return false;
}

void show_error_box(const char *description) {
	// TODO, SCHEDULED FOR LINUX AND WINDOWS
}

#ifdef WIN32
#include <windows.h>

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
					_In_ PWSTR pCmdLine, _In_ int nCmdShow) {
	// TODO
}
#else

int main() {
	if (!check_if_launched_by_parent_tentrillion())
		show_error_box(not_launched_from_parent_default);
}

#endif
#include "XelaNetworkInit.h"

static bool xelaNetworkingInitialized = false;

#if defined(_WIN32)
static bool xelaNetInitWindows() {
	WSAData wsaData;
	int res;
	//Init WinSock
	res = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (res != 0) {
		#if XELANETWORK_DEBUG_INIT
		std::cout << "[XelaNetworkInit] Error initializing WinSock" << std::endl;
		#endif
		return false;
	}

	return true;
}
#endif

bool xelaNetworkingInit() {
	if (!xelaNetworkingInitialized) {
		xelaNetworkingInitialized = true;

		#if XELANETWORK_DEBUG_INIT
		std::cout << "[XelaNetworkInit] Initializing Xela Networking" << std::endl;
		#endif

		#if defined(_WIN32)
		if (!xelaNetInitWindows()) {
			xelaNetworkingInitialized = false;
			return false;
		}
		#else
		return true;
		#endif

		#if XELANETWORK_DEBUG_INIT
		std::cout << "[XelaNetworkInit] Initialization success" << std::endl;
		#endif
	}

	return true;
}
#ifndef _XELA_NETWORK_INIT_H
#define _XELA_NETWORK_INIT_H

#include "XelaNetworking.h"

#if XELANETWORK_DEBUG_INIT
	#include <iostream>
#endif

extern "C" {
	XELANETWORK_API bool xelaNetworkingInit();
}

#endif
/**
 * @file src/r2plugin/registration.cpp
 * @brief Module that implements registration logic to r2 console.
 * @copyright (c) 2020 Avast Software, licensed under the MIT license.
 */

#include <mutex>

#include <retdec/utils/io/log.h>
#include <rz_core.h>

#include "r2plugin/r2data.h"
#include "r2plugin/console/decompiler.h"

using namespace retdec::r2plugin;
using namespace retdec::utils::io;

/**
 * R2 console registration method. This method is called
 * after each command typed into r2. If the function wants
 * to respond on provided command, provides response and returns true.
 * Activation method for this function is matching prefix of the input.
 *  -> prefix(input) == CMD_PREFIX
 *
 * Otherwise the function must return false which will indicate that
 * other command should be executed.
 */
static int r2retdec_cmd(void *user, const char* input)
{
	static std::mutex mutex;
	RzCore& core = *(RzCore*)user;
	R2Database binInfo(core);

	try {
		std::lock_guard<std::mutex> lock (mutex);
		return DecompilerConsole::handleCommand(std::string(input), binInfo);
	}
	catch (const std::exception& e) {
		Log::error() << Log::Error << e.what() << std::endl;
		return true;
	}
}

// Structure containing plugin info.
RzCorePlugin rz_core_plugin_retdec = {
	/* .name = */ "r2retdec",
	/* .desc = */ "RetDec integration",
	/* .license = */ "MIT",
	/* .author = */ "Avast",
	/* .version = */ "0.2",
// TODO	/* .call = */ r2retdec_cmd,
	/* .init = */ nullptr,
	/* .fini = */ nullptr
};

#ifndef CORELIB
#ifdef __cplusplus
extern "C"
#endif

// This will register the r2plugin in r2 console.
RZ_API RzLibStruct rizin_plugin = {
	/* .type = */ RZ_LIB_TYPE_CORE,
	/* .data = */ &rz_core_plugin_retdec,
	/* .version = */ RZ_VERSION,
	/* .free = */ nullptr,
	/* .pkgname */ "retdec-r2plugin"
};

#endif

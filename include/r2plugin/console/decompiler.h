/**
 * @file include/r2plugin/console/decompiler.h
 * @brief implementation of decompiler console (pdz_).
 * @copyright (c) 2020 avast software, licensed under the mit license.
 */

#pragma once

#include "r2plugin/console/console.h"
#include "r2plugin/r2retdec.h"

namespace retdec {
namespace r2plugin {

/**
 * Decompiler class. Provides and implements interface for decompiler
 * console that user sees after typing pdz_ command.
 */
class DecompilerConsole: public Console {
protected:
	DecompilerConsole();

public:
	/// Calls handle method of the DecompilerConsole singleton.
	static bool handleCommand(const std::string& commad, const R2Database& info);

public:
	/// Representation of pdz command.
	static const Console::Command DecompileCurrent;

	/// Representation of pdzo command.
	static const Console::Command DecompileWithOffsetsCurrent;

	/// Representation of pdzj command.
	static const Console::Command DecompileJsonCurrent;

	/// Representation of pdz* command.
	static const Console::Command DecompileCommentCurrent;
	
	/// Representation of pdza command.
	static const Console::Command DecompilerDataAnalysis;

	/// Representation of pdze command.
	static const Console::Command ShowUsedEnvironment;

private:
	/// Implementation of pdz command.
	static bool decompileCurrent(const std::string&, const R2Database& info);

	/// Implementation of pdzj command.
	static bool decompileJsonCurrent(const std::string&, const R2Database& info);

	/// Implementation of pdzo command.
	static bool decompileWithOffsetsCurrent(const std::string&, const R2Database& info);

	/// Implementation of pdz* command.
	static bool decompileCommentCurrent(const std::string&, const R2Database& info);

	/// Implementation of pdze command.
	static bool showEnvironment(const std::string&, const R2Database&);

	static config::Config createConsoleConfig(const R2Database& binInfo);

private:
	/// Singleton.
	static DecompilerConsole console;
};

};
};

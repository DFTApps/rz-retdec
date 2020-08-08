#pragma once

#include <map>
#include <tuple>

#include "r2plugin/r2info.h"

namespace retdec {
namespace r2plugin {

/**
 * @brief Provides console user interface.
 *
 * Provides interface (and implementation) for
 * handling console arguments. This class does
 * not implement logic only interface for
 * registering handler methods on required actions.
 */
class Console {
public:
	/// Callback funuction that can be registered to handle command.
	typedef bool (*Callback)(const std::string&, const R2InfoProvider&);

	/// Command is represented as suffix and callback for that suffix.
	struct Command {
		std::string help = "";
		Callback execute = nullptr;
		bool extra = false;
		std::string parameters = "";
	};

	using NamedCommand = std::pair<const std::string, const Command&>;

protected:
	Console(const std::string& base, const std::string& about, const std::vector<NamedCommand>&);

public:
	bool handle(const std::string& commad, const R2InfoProvider& info);
	bool printHelp(const RCore& core) const;

private:
	const std::string _base;
	const std::string _about;
	std::map<const std::string, const Command&> _callbacks;
};

}
}

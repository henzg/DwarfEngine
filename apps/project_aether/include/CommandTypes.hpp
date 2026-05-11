#pragma once
#include <string>
#include <vector>
#include <functional>
namespace Aether {
    using STR = std::string;

    struct ParseCommand {
        std::string name;
        std::vector<std::string> args;
    };

    struct CommandResult {
        std::string output;
        bool success;
    };

    struct Command {
        using CommandHandler = std::function<CommandResult(const ParseCommand&)>;
        STR name;
        STR usage;
        STR desc;
        CommandHandler callback;
    };

} // namespace Aether

#pragma once

#include "Xavier/Config.h"

namespace Xavier
{
    class CommandArguments
    {
    public:
        CommandArguments(int argc, char** argv);
        virtual ~CommandArguments();

        const std::string& GetCommandPath() const;
        bool IsOption(const std::string& name) const;
        const std::string& GetOptionValue(const std::string& name) const;
        const std::vector<std::string>& GetOptionValues(const std::string& name) const;
        const std::vector<std::string>& GetValues() const;

    private:
        std::string mCommandPath;
        std::unordered_map<std::string, std::vector<std::string>> mArguments;
        std::vector<std::string> mValues;
    };
}
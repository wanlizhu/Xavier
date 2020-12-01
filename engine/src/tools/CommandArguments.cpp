#include "CommandArguments.h"

namespace Xavier
{
    CommandArguments::CommandArguments(int argc, char** argv)
        : mCommandPath(argv[0])
    {
        for (int i = 1; i < argc; i++)
        {
            if (argv[i][0] == '-')
            {
                mArguments[argv[i]].clear();
            }
            else if (argv[i - 1][0] == '-')
            {
                mArguments[argv[i - 1]].push_back(argv[i]);
            }
            else
            {
                mValues.push_back(argv[i]);
            }
        }
    }

    CommandArguments::~CommandArguments()
    {}

    const std::string& CommandArguments::GetCommandPath() const
    {
        return mCommandPath;
    }

    bool CommandArguments::IsOption(const std::string& name) const
    {
        auto iter = mArguments.find(name);
        return iter != mArguments.end();
    }

    const std::string& CommandArguments::GetOptionValue(const std::string& name) const
    {
        auto iter = mArguments.find(name);
        assert(iter != mArguments.end());

        return iter->second[0];
    }

    const std::vector<std::string>& CommandArguments::GetOptionValues(const std::string& name) const
    {
        auto iter = mArguments.find(name);
        assert(iter != mArguments.end());

        return iter->second;
    }

    const std::vector<std::string>& CommandArguments::GetValues() const
    {
        return mValues;
    }
}
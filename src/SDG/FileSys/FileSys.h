//
// FileSys.h
// SDG_Engine
//
#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace SDG
{
    class FileSys
    {
    public:
        /**
         * Gets the path to the program's root directory, including the final slash.
         * e.g. "path/to/root/".
         * On Mac, this points to the app's Resource folder.
         */
        [[nodiscard]] std::string BasePath();

        /// Gets the path to this app title's writable file location.
        [[nodiscard]] std::string PrefPath();

        /// Sets the data for the app in order to retrieve its Pref path.
        void Initialize(const std::string &pAppName, const std::string &pOrgName);

    private:
        std::string appName;
        std::string orgName;
        std::string basePath;
        std::string prefPath;
    };
}

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
    /// Accesses application directories.
    /// Typically owned by an App to set up and retrieve these paths.
    class FileSys
    {
    public:
        FileSys();
        FileSys(const std::string &pAppName, const std::string &pOrgName);
        /// Gets the path to the program's base directory, including the final slash.
        /// e.g. "path/to/root/".
        /// On Mac, this points to the app's Resource folder.
        [[nodiscard]]
        std::string BasePath() const;

        /// Gets the path to this app title's writable file location.
        [[nodiscard]]
        std::string PrefPath() const;

        [[nodiscard]]
        std::string AppName() const { return appName; }

        [[nodiscard]]
        std::string OrgName() const { return orgName; }

        /// Sets the data for the app in order to retrieve its Pref path.
        void Initialize(const std::string &pAppName, const std::string &pOrgName);

    private:
        std::string appName;
        std::string orgName;
        // cached for quick access
        mutable std::string basePath;
        mutable std::string prefPath;
    };
}

//
// FileSys.h
// SDG_Engine
//
#pragma once
#include <SDG/Lib/String.h>

namespace SDG
{
    /// Accesses application directories.
    /// Typically owned by an App to set up and retrieve these paths.
    class FileSys
    {
    public:
        FileSys();
        FileSys(const String &pAppName, const String &pOrgName);
        /// Gets the path to the program's base directory, including the final slash.
        /// e.g. "path/to/root/".
        /// On Mac, this points to the app's Resource folder.
        [[nodiscard]]
        String BasePath() const;

        /// Gets the path to this app title's writable file location.
        [[nodiscard]]
        String PrefPath() const;

        [[nodiscard]]
        String AppName() const { return appName; }

        [[nodiscard]]
        String OrgName() const { return orgName; }

        /// Sets the data for the app in order to retrieve its Pref path.
        void Initialize(const String &pAppName, const String &pOrgName);

    private:
        String appName;
        String orgName;
        // cached for quick access
        mutable String basePath;
        mutable String prefPath;
    };
}

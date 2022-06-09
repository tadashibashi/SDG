#include "SDG_Tests.h"
#include <Engine/Filesys.h>
#include <Engine/Platform.h>

#include <SDL.h>

TEST_CASE("Path", "[path]")
{
// Set the root path for testing depending on platform
#if (SDG_TARGET_WINDOWS)
    String root = "C:\\";
#else // unix-based systems. What about WEBGL? Nintendo Switch?
    String root = "/";
#endif
    Filesys fileSys("SDG Tests", "SDG");
    SECTION("Setup")
    {
        // Set up file system
        Path::PushFileSys(fileSys);        // gives Path class access to these paths.
                                                // Changable if you want to use a different
                                                // set of folders.
    }



    SECTION("Path Constructor Tests")
    {
        SECTION("Default Path constructor creates empty path")
        {
            Path path;
            REQUIRE(path.Str().Empty());
            REQUIRE(path.Base() == Path::BaseDir::None);
            REQUIRE(path.Subpath().Empty());
        }

        SECTION("Path constructor omits preceding white space")
        {
            Path path("       test.txt", Path::BaseDir::Root);
            REQUIRE(path.Subpath() == "test.txt");
            REQUIRE(path.Str() == root + "test.txt");
        }

        SECTION("Path constructor omits preceding '/'")
        {
            Path path("////////////////////test.txt", Path::BaseDir::Root);
            REQUIRE(path.Subpath() == "test.txt");
            REQUIRE(path.Str() == root + "test.txt");
        }

            // Doesn't support folders or files with white-space in the beginning of subpath
            // e.g. "  path/to/folder" is trimmed to -> "path/to/folder"
        SECTION("Path constructor omits combo of preceding whitespace and '/'")
        {
            Path path("///  /// ////   /// // /// //test.txt", Path::BaseDir::Root);
            REQUIRE(path.Subpath() == "test.txt");
            REQUIRE(path.Str() == root + "test.txt");
        }

        SECTION("Path constructor omits a trailing whitespace")
        {
            Path path("test.txt ", Path::BaseDir::Root);
            REQUIRE(path.Subpath() == "test.txt");
            REQUIRE(path.Str() == root + "test.txt");
        }

        SECTION("Path constructor omits trailing whitespace")
        {
            Path path("test.txt                ", Path::BaseDir::Root);
            REQUIRE(path.Subpath() == "test.txt");
            REQUIRE(path.Str() == root + "test.txt");
        }

        SECTION("Path constructor omits a trailing slash")
        {
            Path path("test.txt/", Path::BaseDir::Root);
            REQUIRE(path.Subpath() == "test.txt");
            REQUIRE(path.Str() == root + "test.txt");
        }

        SECTION("Path constructor omits trailing slashes")
        {
            Path path("test.txt////////////////////", Path::BaseDir::Root);
            REQUIRE(path.Subpath() == "test.txt");
            REQUIRE(path.Str() == root + "test.txt");
        }


        SECTION("Path constructor omits trailing slashes and whitespaces")
        {
            Path path1("test.txt//   ///////   // /// ////// ", Path::BaseDir::Root);
            REQUIRE(path1.Subpath() == "test.txt");
            REQUIRE(path1.Str() == root + "test.txt");

            Path path2("test.txt/ ", Path::BaseDir::Root);
            REQUIRE(path2.Subpath() == "test.txt");
            REQUIRE(path2.Str() == root + "test.txt");

            Path path3("test.txt /", Path::BaseDir::Root);
            REQUIRE(path3.Subpath() == "test.txt");
            REQUIRE(path3.Str() == root + "test.txt");
        }

        SECTION("Path constructor omits trailing and preceding slashes and whitespaces")
        {
            Path path1(" //////////// // // //  /// / //test.txt//   ///////   // /// ////// ", Path::BaseDir::Root);
            REQUIRE(path1.Subpath() == "test.txt");
            REQUIRE(path1.Str() == root + "test.txt");

            Path path2(" /test.txt/ ", Path::BaseDir::Root);
            REQUIRE(path2.Subpath() == "test.txt");
            REQUIRE(path2.Str() == root + "test.txt");

            Path path3("/ test.txt /", Path::BaseDir::Root);
            REQUIRE(path3.Subpath() == "test.txt");
            REQUIRE(path3.Str() == root + "test.txt");
        }

        SECTION("Path constructor omits one-space path")
        {
            Path path(" ", Path::BaseDir::Root);
            REQUIRE(path.Subpath().Empty());
            REQUIRE(path.Str() == root);
        }

        SECTION("Path constructor omits one-slash path")
        {
            Path path("/", Path::BaseDir::Root);
            REQUIRE(path.Subpath().Empty());
            REQUIRE(path.Str() == root);
        }

        SECTION("Path constructor omits all white spaced path")
        {
            Path path("                     ", Path::BaseDir::Root);
            REQUIRE(path.Subpath().Empty());
            REQUIRE(path.Str() == root);
        }

        SECTION("Path constructor omits all-slash path")
        {
            Path path("/////////////////////////", Path::BaseDir::Root);
            REQUIRE(path.Subpath().Empty());
            REQUIRE(path.Str() == root);
        }

        SECTION("Path base is set correctly in constructor")
        {
            Path pathNoBase("myfile.exe", Path::BaseDir::None);
            Path pathRootBase("myfile.exe", Path::BaseDir::Root);
            Path pathBaseBase("myfile.exe", Path::BaseDir::Base);
            Path pathTitleBase("myfile.exe", Path::BaseDir::Pref);
            REQUIRE(pathNoBase.Base() == Path::BaseDir::None);
            REQUIRE(pathRootBase.Base() == Path::BaseDir::Root);
            REQUIRE(pathBaseBase.Base() == Path::BaseDir::Base);
            REQUIRE(pathTitleBase.Base() == Path::BaseDir::Pref);
        }

        SECTION("Path full string is same across paths bases. Fullpath should be equal or larger than subpath")
        {
            Path pathNoBase("myfile.txt", Path::BaseDir::Root);
            Path pathRootBase("myfile.txt", Path::BaseDir::Base);
            Path pathTitleBase("myfile.txt", Path::BaseDir::Pref);
            REQUIRE(pathNoBase.Subpath() == pathRootBase.Subpath());
            REQUIRE(pathTitleBase.Subpath() == pathRootBase.Subpath());
            REQUIRE(pathNoBase.Str().Length() >= pathNoBase.Subpath().Length());
            REQUIRE(pathTitleBase.Str().Length() >= pathTitleBase.Subpath().Length());
            REQUIRE(pathRootBase.Str().Length() >= pathRootBase.Subpath().Length());
        }
    } /* end Constructor Tests */

    SECTION("Path::Empty")
    {
        SECTION("Default path is empty")
        {
            Path path;
            REQUIRE(path.Empty());
        }

        SECTION("No basedir, with subpath is not empty")
        {
            Path path("path");
            REQUIRE(!path.Empty());
        }

        SECTION("No subpath, with basedir is not empty")
        {
            Path path("", Path::BaseDir::Base);
            REQUIRE(!path.Empty());
        }
    }


    SECTION("Filename() Tests")
    {
        SECTION("Filename when Path::Base::Root")
        {
            Path path("assets/myfile.txt", Path::BaseDir::Root);
            REQUIRE(path.Filename() == "myfile.txt");
        }

        SECTION("Filename when Path::Base::Pref")
        {
            Path path("assets/myfile.txt", Path::BaseDir::Pref);
            REQUIRE(path.Filename() == "myfile.txt");
        }

        SECTION("Filename when Path::Base::Base")
        {
            Path path("assets/myfile.txt", Path::BaseDir::Base);
            REQUIRE(path.Filename() == "myfile.txt");
        }

        SECTION("Filename begins with '.'")
        {
            Path path("assets/.myfile.txt", Path::BaseDir::Base);
            REQUIRE(path.Filename() == ".myfile.txt");
        }

        SECTION("Filename contains one '.'")
        {
            Path path("assets/.", Path::BaseDir::Base);
            REQUIRE(path.Filename() == "assets");
        }

        SECTION("Filename contains all '.'")
        {
            Path path("assets/....", Path::BaseDir::Base);
            REQUIRE(path.Filename() == "assets");
        }

        SECTION("Filename received correctly: filename contains all '/'")
        {
            Path path("folder///", Path::BaseDir::Base);
            REQUIRE(path.Filename() == "folder");
        }
    } /* End Filename() Tests */

    SECTION("Extension() Tests")
    {
        SECTION("Extension is correct on an extension regardless of base")
        {
            Path pathNoBase("myfile.txt", Path::BaseDir::Root);
            Path pathRootBase("myfile.txt", Path::BaseDir::Base);
            Path pathTitleBase("myfile.txt", Path::BaseDir::Pref);
            REQUIRE(pathNoBase.Extension() == "txt");
            REQUIRE(pathRootBase.Extension() == "txt");
            REQUIRE(pathTitleBase.Extension() == "txt");
        }

        SECTION("Extension is correctly empty regardless of base")
        {
            Path pathNoBase("myfolder", Path::BaseDir::Root);
            Path pathRootBase("myfolder", Path::BaseDir::Base);
            Path pathTitleBase("myfolder", Path::BaseDir::Pref);
            REQUIRE(pathNoBase.Extension().Empty());
            REQUIRE(pathRootBase.Extension().Empty());
            REQUIRE(pathTitleBase.Extension().Empty());
            REQUIRE(!pathNoBase.HasExtension());
            REQUIRE(!pathRootBase.HasExtension());
            REQUIRE(!pathTitleBase.HasExtension());
        }

        SECTION("Extension is correct when first char is '.' regardless of base")
        {
            Path pathNoBase(".config.txt", Path::BaseDir::Root);
            Path pathRootBase(".config.txt", Path::BaseDir::Base);
            Path pathTitleBase(".config.txt", Path::BaseDir::Pref);
            REQUIRE(pathNoBase.Extension() == "txt");
            REQUIRE(pathRootBase.Extension() == "txt");
            REQUIRE(pathTitleBase.Extension() == "txt");
            REQUIRE(pathNoBase.HasExtension());
            REQUIRE(pathRootBase.HasExtension());
            REQUIRE(pathTitleBase.HasExtension());
        }

        SECTION("Extension is correctly empty when first char is '.' regardless of base")
        {
            Path pathNoBase(".config", Path::BaseDir::Root);
            Path pathRootBase(".config", Path::BaseDir::Base);
            Path pathTitleBase(".config", Path::BaseDir::Pref);
            REQUIRE(pathNoBase.Extension().Empty());
            REQUIRE(pathRootBase.Extension().Empty());
            REQUIRE(pathTitleBase.Extension().Empty());
            REQUIRE(!pathNoBase.HasExtension());
            REQUIRE(!pathRootBase.HasExtension());
            REQUIRE(!pathTitleBase.HasExtension());
        }
    } /* end Extension() Tests */

    SECTION("Path addition operators")
    {
        SECTION("Path + string")
        {
            Path path("path/to/folder", Path::BaseDir::Root);
            String str("deeper/nesting/file.txt");
            Path combined = path + str;

            REQUIRE(combined.Str().Length() > path.Str().Length());
            REQUIRE(combined.Subpath() == "path/to/folder/deeper/nesting/file.txt");
            REQUIRE(combined.Extension() == "txt");
        }

        SECTION("Path += string")
        {
            Path path("path/to/folder", Path::BaseDir::Root);
            String str("deeper/nesting/file.txt");

            size_t subpathLength = path.Subpath().Length();
            path += str;

            REQUIRE(path.Subpath().Length() == str.Length() + subpathLength + 1); // +1 includes the auto-appended '/'
            REQUIRE(path.Str() == root + "path/to/folder/deeper/nesting/file.txt");
            REQUIRE(path.Extension() == "txt");
        }

    } /* End Path addition operators */


    SECTION("Path <-> Path comparison")
    {
        SECTION("Path is comparable to a path, base paths equal")
        {
            Path path1("path/to/folder/program.exe", Path::BaseDir::Base);
            Path path2("path/to/folder/program.exe", Path::BaseDir::Base);

            REQUIRE(path1 == path2);
        }

        SECTION("Path is comparable to a path, base path differ but strings are same")
        {
            Path path1("path/to/folder/program.exe", Path::BaseDir::Pref);
            Path path2(PrefPath().Str() + "path/to/folder/program.exe", Path::BaseDir::Root);
            REQUIRE(path1.Str() == path2.Str());
            REQUIRE(path1 == path2);
        }

        SECTION("Paths are unequal: same base, different subpath")
        {
            Path path1("path/to/folder/program.exe", Path::BaseDir::Pref);
            Path path2("some/other/path/program.exe", Path::BaseDir::Pref);

            REQUIRE(path1 != path2);
        }

        SECTION("Paths are unequal: different base, same subpath")
        {
            Path path1("path/to/folder/program.exe", Path::BaseDir::Pref);
            Path path2("path/to/folder/program.exe", Path::BaseDir::Root);

            REQUIRE(path1 != path2);
        }

        SECTION("Paths are not unequal when the same")
        {
            Path path1("path/to/folder/program.exe", Path::BaseDir::Root);
            Path path2("path/to/folder/program.exe", Path::BaseDir::Root);

            REQUIRE(!(path1 != path2));
        }

        SECTION("Paths are not unequal: differing base path, same full string")
        {
            Path path1("path/to/folder/program.exe", Path::BaseDir::Base);
            Path path2(BasePath().Str() + "path/to/folder/program.exe", Path::BaseDir::Root);

            REQUIRE(!(path1 != path2));
        }

    } /* End Path <-> Path comparison */

    SECTION("Path <-> string comparison")
    {
        SECTION("Path == string")
        {
            Path path("path/to/folder/program.exe", Path::BaseDir::Root);
            String str(root + "path/to/folder/program.exe");

            REQUIRE(path == str);
        }

        SECTION("Path != string")
        {
            Path path("path/to/folder/program.exe", Path::BaseDir::Root);
            String str(root + "path/to/another/place/program.exe");

            REQUIRE(path != str);
        }

        SECTION("string == Path")
        {
            Path path("path/to/folder/program.exe", Path::BaseDir::Root);
            String str(root + "path/to/folder/program.exe");
            REQUIRE(str == path);
        }

        SECTION("string != Path")
        {
            Path path("path/to/folder/program.exe", Path::BaseDir::Root);
            String str(root + "path/to/another/place/program.exe");

            REQUIRE(str != path);
        }

    } /* End Path <-> string comparison */

#if SDG_TARGET_DESKTOP // Executable is not at the base path on other platforms
    SECTION("Path FileExists tests")
    {
#if SDG_TARGET_WINDOWS
        String suffix = ".exe";
#else
        String suffix = "";
#endif

        SECTION("Executable file exists at path")
        {
            String subpath = "SDG_Tests" + suffix;
            Path path(subpath, Path::BaseDir::Base);

            REQUIRE(path.FileExists());
        }

        SECTION("Executable file does not exist at path")
        {
            String subpath = "SDG_Tests" + suffix;
            Path path(subpath, Path::BaseDir::Pref);

            REQUIRE(!path.FileExists());
        }
    }
#endif

    SECTION("BasePath creates a Path with BaseDir::Root")
    {
        REQUIRE(RootPath().Base() == Path::BaseDir::Root);
    }

    SECTION("BasePath default creates the OS root path")
    {
        REQUIRE(RootPath().Str() == root);
    }

    SECTION("PrefPath creates a Path with BaseDir::Pref")
    {
        REQUIRE(PrefPath().Base() == Path::BaseDir::Pref);
    }

    SECTION("BasePath creates a Path with BaseDir::Base")
    {
        REQUIRE(BasePath().Base() == Path::BaseDir::Base);
    }

    SECTION("Path default creates a Path with BaseDir::None")
    {
        REQUIRE(Path().Base() == Path::BaseDir::None);
    }

    SECTION("PopFileSys removes latest FileSys")
    {
        String prefPath1 = PrefPath().Str();

        Filesys sys2("SDG Different FileSys Test", "SDG");
        Path::PushFileSys(Ref(sys2));
        String prefPath2 = PrefPath().Str();
        Path::PopFileSys();
        String prefPath3 = PrefPath().Str();

        REQUIRE(prefPath2 != prefPath1);
        REQUIRE(prefPath1 == prefPath3);
    }

    SECTION("Cleanup")
    {
        Path::PopFileSys();
    }

} /* End TEST_CASE for class Path */

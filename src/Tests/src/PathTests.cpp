#include <catch2/catch_test_macros.hpp>
#include <SDG/FileSys/Path.h>
#include <SDG/Platform.h>

using namespace SDG;

TEST_CASE("Path", "[path]")
{
    // Set the root path for testing depending on platform
#if SDG_TARGET_WINDOWS
    std::string root = "C:\\";
#else // unix-based systems. What about WEBGL? Nintendo Switch?
    std::string root = "/";
#endif


    SECTION("Path Constructor Tests")
    {
        SECTION("Default Path constructor creates empty path")
        {
            Path path;
            REQUIRE(path.String().empty());
            REQUIRE(path.Base() == Path::BaseDir::None);
            REQUIRE(path.Subpath().empty());
        }

        SECTION("Path constructor omits preceding white space")
        {
            Path path("       test.txt");
            REQUIRE(path.Subpath() == "test.txt");
            REQUIRE(path.String() == root + "test.txt");
        }

        SECTION("Path constructor omits preceding '/'")
        {
            Path path("////////////////////test.txt");
            REQUIRE(path.Subpath() == "test.txt");
            REQUIRE(path.String() == root + "test.txt");
        }

            // Doesn't support folders or files with white-space in the beginning of subpath
            // e.g. "  path/to/folder" is trimmed to -> "path/to/folder"
        SECTION("Path constructor omits combo of preceding whitespace and '/'")
        {
            Path path("///  /// ////   /// // /// //test.txt");
            REQUIRE(path.Subpath() == "test.txt");
            REQUIRE(path.String() == root + "test.txt");
        }

        SECTION("Path constructor omits a trailing whitespace")
        {
            Path path("test.txt ");
            REQUIRE(path.Subpath() == "test.txt");
            REQUIRE(path.String() == root + "test.txt");
        }

        SECTION("Path constructor omits trailing whitespace")
        {
            Path path("test.txt                ");
            REQUIRE(path.Subpath() == "test.txt");
            REQUIRE(path.String() == root + "test.txt");
        }

        SECTION("Path constructor omits a trailing slash")
        {
            Path path("test.txt/");
            REQUIRE(path.Subpath() == "test.txt");
            REQUIRE(path.String() == root + "test.txt");
        }

        SECTION("Path constructor omits trailing slashes")
        {
            Path path("test.txt////////////////////");
            REQUIRE(path.Subpath() == "test.txt");
            REQUIRE(path.String() == root + "test.txt");
        }


        SECTION("Path constructor omits trailing slashes and whitespaces")
        {
            Path path1("test.txt//   ///////   // /// ////// ");
            REQUIRE(path1.Subpath() == "test.txt");
            REQUIRE(path1.String() == root + "test.txt");

            Path path2("test.txt/ ");
            REQUIRE(path2.Subpath() == "test.txt");
            REQUIRE(path2.String() == root + "test.txt");

            Path path3("test.txt /");
            REQUIRE(path3.Subpath() == "test.txt");
            REQUIRE(path3.String() == root + "test.txt");
        }

        SECTION("Path constructor omits trailing and preceding slashes and whitespaces")
        {
            Path path1(" //////////// // // //  /// / //test.txt//   ///////   // /// ////// ");
            REQUIRE(path1.Subpath() == "test.txt");
            REQUIRE(path1.String() == root + "test.txt");

            Path path2(" /test.txt/ ");
            REQUIRE(path2.Subpath() == "test.txt");
            REQUIRE(path2.String() == root + "test.txt");

            Path path3("/ test.txt /");
            REQUIRE(path3.Subpath() == "test.txt");
            REQUIRE(path3.String() == root + "test.txt");
        }

        SECTION("Path constructor omits one-space path")
        {
            Path path(" ");
            REQUIRE(path.Subpath().empty());
            REQUIRE(path.String() == root);
        }

        SECTION("Path constructor omits one-slash path")
        {
            Path path("/");
            REQUIRE(path.Subpath().empty());
            REQUIRE(path.String() == root);
        }

        SECTION("Path constructor omits all white spaced path")
        {
            Path path("                     ");
            REQUIRE(path.Subpath().empty());
            REQUIRE(path.String() == root);
        }

        SECTION("Path constructor omits all-slash path")
        {
            Path path("/////////////////////////");
            REQUIRE(path.Subpath().empty());
            REQUIRE(path.String() == root);
        }

        SECTION("Path base is set correctly in constructor")
        {
            Path pathNoBase("myfile.exe", Path::BaseDir::Root);
            Path pathRootBase("myfile.exe", Path::BaseDir::Base);
            Path pathTitleBase("myfile.exe", Path::BaseDir::Pref);
            REQUIRE(pathNoBase.Base() == Path::BaseDir::Root);
            REQUIRE(pathRootBase.Base() == Path::BaseDir::Base);
            REQUIRE(pathTitleBase.Base() == Path::BaseDir::Pref);
        }

        SECTION("Path bases result in the same subpath but different strings")
        {
            Path pathNoBase("myfile.txt", Path::BaseDir::Root);
            Path pathRootBase("myfile.txt", Path::BaseDir::Base);
            Path pathTitleBase("myfile.txt", Path::BaseDir::Pref);
            REQUIRE(pathNoBase.Subpath() == pathRootBase.Subpath());
            REQUIRE(pathTitleBase.Subpath() == pathRootBase.Subpath());
            REQUIRE(pathNoBase.String() != pathRootBase.String());
            REQUIRE(pathTitleBase.String() != pathRootBase.String());
        }
    } /* end Constructor Tests */


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
            REQUIRE(pathNoBase.Extension().empty());
            REQUIRE(pathRootBase.Extension().empty());
            REQUIRE(pathTitleBase.Extension().empty());
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
            REQUIRE(pathNoBase.Extension().empty());
            REQUIRE(pathRootBase.Extension().empty());
            REQUIRE(pathTitleBase.Extension().empty());
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
            std::string str("deeper/nesting/file.txt");
            Path combined = path + str;

            REQUIRE(combined.String().length() > path.String().length());
            REQUIRE(combined.Subpath() == "path/to/folder/deeper/nesting/file.txt");
            REQUIRE(combined.Extension() == "txt");
        }

        SECTION("Path += string")
        {
            Path path("path/to/folder", Path::BaseDir::Root);
            std::string str("deeper/nesting/file.txt");

            size_t subpathLength = path.Subpath().length();
            path += str;

            REQUIRE(path.Subpath().length() == str.length() + subpathLength + 1); // +1 includes the auto-appended '/'
            REQUIRE(path.String() == root + "path/to/folder/deeper/nesting/file.txt");
            REQUIRE(path.Extension() == "txt");
        }

    } /* End Path addition operators */


    SECTION("Path <-> Path comparison")
    {
        SECTION("Path is comparable to a path, base paths equal")
        {
            Path path1("path/to/folder/program.exe", Path::BaseDir::Base);
            Path path2("path/to/folder/program.exe", Path::BaseDir::Base);

            REQUIRE((path1 == path2));
        }

        SECTION("Path is comparable to a path, base path differ but strings are same")
        {
            Path path1("path/to/folder/program.exe", Path::BaseDir::Pref);
            Path path2(PrefPath().String() + "path/to/folder/program.exe");
            REQUIRE(path1.String() == path2.String());
            REQUIRE((path1 == path2));
        }

        SECTION("Paths are unequal: same base, different subpath")
        {
            Path path1("path/to/folder/program.exe", Path::BaseDir::Pref);
            Path path2("some/other/path/program.exe", Path::BaseDir::Pref);

            REQUIRE((path1 != path2));
        }

        SECTION("Paths are unequal: different base, same subpath")
        {
            Path path1("path/to/folder/program.exe", Path::BaseDir::Pref);
            Path path2("path/to/folder/program.exe", Path::BaseDir::Root);

            REQUIRE((path1 != path2));
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
            Path path2(BasePath().String() + "path/to/folder/program.exe");

            REQUIRE(!(path1 != path2));
        }

    } /* End Path <-> Path comparison */

    SECTION("Path <-> string comparison")
    {
        SECTION("Path == string")
        {
            Path path("path/to/folder/program.exe", Path::BaseDir::Root);
            std::string str(root + "path/to/folder/program.exe");

            REQUIRE((path == str));
        }

        SECTION("Path != string")
        {
            Path path("path/to/folder/program.exe", Path::BaseDir::Root);
            std::string str(root + "path/to/another/place/program.exe");

            REQUIRE((path != str));
        }

        SECTION("string == Path")
        {
            Path path("path/to/folder/program.exe", Path::BaseDir::Root);
            std::string str(root + "path/to/folder/program.exe");
            REQUIRE((str == path));
        }

        SECTION("string != Path")
        {
            Path path("path/to/folder/program.exe", Path::BaseDir::Root);
            std::string str(root + "path/to/another/place/program.exe");

            REQUIRE((str != path));
        }

    } /* End Path <-> string comparison */

    SECTION("Path FileExists tests")
    {
#if SDG_TARGET_WINDOWS
        std::string suffix = ".exe";
#else
        std::string suffix = "";
#endif

        SECTION("Executable file exists at path")
        {
            std::string subpath = "SDG_Tests" + suffix;
            Path path(subpath, Path::BaseDir::Base);

            REQUIRE(path.FileExists());
        }

        SECTION("Executable file does not exist at path")
        {
            std::string subpath = "SDG_Tests" + suffix;
            Path path(subpath, Path::BaseDir::Pref);

            REQUIRE(!path.FileExists());
        }
    }

    SECTION("RootPath creates a Path with BaseDir::Root")
    {
        REQUIRE(RootPath().Base() == Path::BaseDir::Root);
    }

    SECTION("RootPath default creates the OS root path")
    {
        REQUIRE(RootPath().String() == root);
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

} /* End TEST_CASE for class Path */

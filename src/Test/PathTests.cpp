#include <catch2/catch_test_macros.hpp>
#include <SDG/FileSys/Path.h>

using namespace SDG;

TEST_CASE("Path", "[path]")
{
    SECTION("Path Constructor Tests")
    {
        SECTION("Default Path constructor creates system root path")
        {
            Path path;
            REQUIRE(path.String() == "/");
            REQUIRE(path.BaseID() == Path::Base::None);
            REQUIRE(path.SubPath() == std::string());
        }

        SECTION("Path constructor omits preceding white space")
        {
            Path path("       test.txt");
            REQUIRE(path.SubPath() == "test.txt");
            REQUIRE(path.String() == "/test.txt");
        }

        SECTION("Path constructor omits preceding '/'")
        {
            Path path("////////////////////test.txt");
            REQUIRE(path.SubPath() == "test.txt");
            REQUIRE(path.String() == "/test.txt");
        }

            // Doesn't support folders or files with white-space in the beginning of subpath
            // e.g. "  path/to/folder" is trimmed to -> "path/to/folder"
        SECTION("Path constructor omits combo of preceding whitespace and '/'")
        {
            Path path("///  /// ////   /// // /// //test.txt");
            REQUIRE(path.SubPath() == "test.txt");
            REQUIRE(path.String() == "/test.txt");
        }

        SECTION("Path constructor omits a trailing whitespace")
        {
            Path path("test.txt ");
            REQUIRE(path.SubPath() == "test.txt");
            REQUIRE(path.String() == "/test.txt");
        }

        SECTION("Path constructor omits trailing whitespace")
        {
            Path path("test.txt                ");
            REQUIRE(path.SubPath() == "test.txt");
            REQUIRE(path.String() == "/test.txt");
        }

        SECTION("Path constructor omits a trailing slash")
        {
            Path path("test.txt/");
            REQUIRE(path.SubPath() == "test.txt");
            REQUIRE(path.String() == "/test.txt");
        }

        SECTION("Path constructor omits trailing slashes")
        {
            Path path("test.txt////////////////////");
            REQUIRE(path.SubPath() == "test.txt");
            REQUIRE(path.String() == "/test.txt");
        }


        SECTION("Path constructor omits trailing slashes and whitespaces")
        {
            Path path1("test.txt//   ///////   // /// ////// ");
            REQUIRE(path1.SubPath() == "test.txt");
            REQUIRE(path1.String() == "/test.txt");

            Path path2("test.txt/ ");
            REQUIRE(path2.SubPath() == "test.txt");
            REQUIRE(path2.String() == "/test.txt");

            Path path3("test.txt /");
            REQUIRE(path3.SubPath() == "test.txt");
            REQUIRE(path3.String() == "/test.txt");
        }

        SECTION("Path constructor omits trailing and preceding slashes and whitespaces")
        {
            Path path1(" //////////// // // //  /// / //test.txt//   ///////   // /// ////// ");
            REQUIRE(path1.SubPath() == "test.txt");
            REQUIRE(path1.String() == "/test.txt");

            Path path2(" /test.txt/ ");
            REQUIRE(path2.SubPath() == "test.txt");
            REQUIRE(path2.String() == "/test.txt");

            Path path3("/ test.txt /");
            REQUIRE(path3.SubPath() == "test.txt");
            REQUIRE(path3.String() == "/test.txt");
        }

        SECTION("Path constructor omits one-space path")
        {
            Path path(" ");
            REQUIRE(path.SubPath() == "");
            REQUIRE(path.String() == "/");
        }

        SECTION("Path constructor omits one-slash path")
        {
            Path path("/");
            REQUIRE(path.SubPath() == "");
            REQUIRE(path.String() == "/");
        }

        SECTION("Path constructor omits all white spaced path")
        {
            Path path("                     ");
            REQUIRE(path.SubPath() == "");
            REQUIRE(path.String() == "/");
        }

        SECTION("Path constructor omits all-slash path")
        {
            Path path("/////////////////////////");
            REQUIRE(path.SubPath() == "");
            REQUIRE(path.String() == "/");
        }

        SECTION("Path base is set correctly in constructor")
        {
            Path pathNoBase("myfile.exe", Path::Base::None);
            Path pathRootBase("myfile.exe", Path::Base::Root);
            Path pathTitleBase("myfile.exe", Path::Base::Title);
            REQUIRE(pathNoBase.BaseID() == Path::Base::None);
            REQUIRE(pathRootBase.BaseID() == Path::Base::Root);
            REQUIRE(pathTitleBase.BaseID() == Path::Base::Title);
        }

        SECTION("Path bases result in the same subpath but different strings")
        {
            Path pathNoBase("myfile.txt", Path::Base::None);
            Path pathRootBase("myfile.txt", Path::Base::Root);
            Path pathTitleBase("myfile.txt", Path::Base::Title);
            REQUIRE(pathNoBase.SubPath() == pathRootBase.SubPath());
            REQUIRE(pathTitleBase.SubPath() == pathRootBase.SubPath());
            REQUIRE(pathNoBase.String() != pathRootBase.String());
            REQUIRE(pathTitleBase.String() != pathRootBase.String());
        }
    }


    SECTION("Filename")
    {
        SECTION("Filename when Path::Base::None")
        {
            Path path("assets/myfile.txt", Path::Base::None);
            REQUIRE(path.Filename() == "myfile.txt");
        }

        SECTION("Filename when Path::Base::Title")
        {
            Path path("assets/myfile.txt", Path::Base::Title);
            REQUIRE(path.Filename() == "myfile.txt");
        }

        SECTION("Filename when Path::Base::Root")
        {
            Path path("assets/myfile.txt", Path::Base::Root);
            REQUIRE(path.Filename() == "myfile.txt");
        }

        SECTION("Filename begins with '.'")
        {
            Path path("assets/.myfile.txt", Path::Base::Root);
            REQUIRE(path.Filename() == ".myfile.txt");
        }

        SECTION("Filename contains one '.'")
        {
            Path path("assets/.", Path::Base::Root);
            REQUIRE(path.Filename() == "assets");
        }

        SECTION("Filename contains all '.'")
        {
            Path path("assets/....", Path::Base::Root);
            REQUIRE(path.Filename() == "assets");
        }

        SECTION("Filename received correctly: filename contains all '/'")
        {
            Path path("folder///", Path::Base::Root);
            REQUIRE(path.Filename() == "folder");
        }
    }

    SECTION("Path::Extension() Tests")
    {
        SECTION("Extension is correct on an extension regardless of base")
        {
            Path pathNoBase("myfile.txt", Path::Base::None);
            Path pathRootBase("myfile.txt", Path::Base::Root);
            Path pathTitleBase("myfile.txt", Path::Base::Title);
            REQUIRE(pathNoBase.Extension() == "txt");
            REQUIRE(pathRootBase.Extension() == "txt");
            REQUIRE(pathTitleBase.Extension() == "txt");
        }

        SECTION("Extension is correctly empty regardless of base")
        {
            Path pathNoBase("myfolder", Path::Base::None);
            Path pathRootBase("myfolder", Path::Base::Root);
            Path pathTitleBase("myfolder", Path::Base::Title);
            REQUIRE(pathNoBase.Extension() == "");
            REQUIRE(pathRootBase.Extension() == "");
            REQUIRE(pathTitleBase.Extension() == "");
            REQUIRE(!pathNoBase.HasExtension());
            REQUIRE(!pathRootBase.HasExtension());
            REQUIRE(!pathTitleBase.HasExtension());
        }

        SECTION("Extension is correct when first char is '.' regardless of base")
        {
            Path pathNoBase(".config.txt", Path::Base::None);
            Path pathRootBase(".config.txt", Path::Base::Root);
            Path pathTitleBase(".config.txt", Path::Base::Title);
            REQUIRE(pathNoBase.Extension() == "txt");
            REQUIRE(pathRootBase.Extension() == "txt");
            REQUIRE(pathTitleBase.Extension() == "txt");
            REQUIRE(pathNoBase.HasExtension());
            REQUIRE(pathRootBase.HasExtension());
            REQUIRE(pathTitleBase.HasExtension());
        }

        SECTION("Extension is correctly empty when first char is '.' regardless of base")
        {
            Path pathNoBase(".config", Path::Base::None);
            Path pathRootBase(".config", Path::Base::Root);
            Path pathTitleBase(".config", Path::Base::Title);
            REQUIRE(pathNoBase.Extension() == "");
            REQUIRE(pathRootBase.Extension() == "");
            REQUIRE(pathTitleBase.Extension() == "");
            REQUIRE(!pathNoBase.HasExtension());
            REQUIRE(!pathRootBase.HasExtension());
            REQUIRE(!pathTitleBase.HasExtension());
        }

        SECTION("Extension() return value is the same as value retrieved from HasExtension")
        {
            Path path("path/to/folder/program.exe");
            std::string outExt;
            REQUIRE(path.HasExtension(&outExt));
            REQUIRE(path.Extension() == outExt);
            REQUIRE(outExt == "exe");
        }
    }

    SECTION("Path addition")
    {
        SECTION("Path + string")
        {
            Path path("path/to/folder");
            std::string str("deeper/nesting/file.txt");
            Path combined = path + str;

            REQUIRE(combined.String().length() > path.String().length());
            REQUIRE(combined.String() == "/path/to/folder/deeper/nesting/file.txt");
            REQUIRE(combined.Extension() == "txt");
        }

        SECTION("Path += string")
        {
            Path path("path/to/folder");
            std::string str("deeper/nesting/file.txt");

            size_t subpathLength = path.SubPath().length();
            path += str;

            REQUIRE(path.SubPath().length() == str.length() + subpathLength + 1); // +1 includes the auto-appended '/'
            REQUIRE(path.String() == "/path/to/folder/deeper/nesting/file.txt");
            REQUIRE(path.Extension() == "txt");
        }

    }


    SECTION("Path <-> Path comparison")
    {
        SECTION("Path is comparable to a path, base paths equal")
        {
            Path path1("path/to/folder/program.exe", Path::Base::Root);
            Path path2("path/to/folder/program.exe", Path::Base::Root);

            REQUIRE((path1 == path2));
        }

        SECTION("Path is comparable to a path, base path differ but strings are same")
        {
            Path path1("path/to/folder/program.exe", Path::Base::Title);
            Path path2(TitlePath().String() + "path/to/folder/program.exe");

            REQUIRE((path1 == path2));
        }

        SECTION("Paths are unequal: same base, different subpath")
        {
            Path path1("path/to/folder/program.exe", Path::Base::Title);
            Path path2("some/other/path/program.exe", Path::Base::Title);

            REQUIRE((path1 != path2));
        }

        SECTION("Paths are unequal: different base, same subpath")
        {
            Path path1("path/to/folder/program.exe", Path::Base::Title);
            Path path2("path/to/folder/program.exe", Path::Base::None);

            REQUIRE((path1 != path2));
        }

        SECTION("Paths are not unequal when the same")
        {
            Path path1("path/to/folder/program.exe", Path::Base::None);
            Path path2("path/to/folder/program.exe", Path::Base::None);

            REQUIRE(!(path1 != path2));
        }

        SECTION("Paths are not unequal: differing base path, same full string")
        {
            Path path1("path/to/folder/program.exe", Path::Base::Root);
            Path path2(RootPath().String() + "path/to/folder/program.exe");

            REQUIRE(!(path1 != path2));
        }

    }

    SECTION("Path <-> string comparison")
    {
        SECTION("Path == string")
        {
            Path path("path/to/folder/program.exe");
            std::string str("/path/to/folder/program.exe");

            REQUIRE((path == str));
        }

        SECTION("Path != string")
        {
            Path path("path/to/folder/program.exe");
            std::string str("/path/to/another/place/program.exe");

            REQUIRE((path != str));
        }

        SECTION("string == Path")
        {
            Path path("path/to/folder/program.exe");
            std::string str("/path/to/folder/program.exe");
            REQUIRE((str == path));
        }

        SECTION("string != Path")
        {
            Path path("path/to/folder/program.exe");
            std::string str("/path/to/another/place/program.exe");

            REQUIRE((str != path));
        }
    }
}

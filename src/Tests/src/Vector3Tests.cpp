/* =============================================================================
 * Vector3Tests
 *
 *
 * ===========================================================================*/
#include "SDG_Tests.h"
#include <Engine/Math/Vector3.h>
#include <sstream>

static Vector3 ParseString(const std::string &str)
{
    size_t commaPos = str.find_first_of(',');
    size_t commaPos2 = str.find_first_of(',', commaPos + 1);
    size_t braceOpen = str.find_first_of('{');
    size_t braceClose = str.find_first_of('}');

    if (commaPos != str.npos && braceOpen != str.npos && braceClose != str.npos
    && commaPos2 != str.npos)
    {
        return {std::stof(str.substr(1, commaPos-1-commaPos2)),
                std::stof(str.substr(commaPos+1, commaPos2-1-commaPos)),
                std::stof(str.substr(commaPos2+1, braceClose-1-commaPos2))};
    }
    else
    {
        // failed to parse string, it was invalid!
        throw std::invalid_argument(str.c_str());
    }
}


TEST_CASE("Vector3 tests", "[Vector3]")
{
    SECTION("Constructors")
    {
        SECTION("Default")
        {
            Vector3 vec;
            REQUIRE(vec.X() == 0);
            REQUIRE(vec.Y() == 0);
            REQUIRE(vec.Z() == 0);

            // Test indexer
            REQUIRE(vec[0] == 0);
            REQUIRE(vec[1] == 0);
            REQUIRE(vec[2] == 0);
        }

        SECTION("Params")
        {
            Vector3 vec(-1, 25, 4);
            REQUIRE(vec.X() == -1);
            REQUIRE(vec.Y() == 25);
            REQUIRE(vec.Z() == 4);

            // Test indexer
            REQUIRE(vec[0] == -1);
            REQUIRE(vec[1] == 25);
            REQUIRE(vec[2] == 4);
        }

        SECTION("Static factory funcs")
        {
            Vector3 one = Vector3::One();
            REQUIRE(one.X() == 1);
            REQUIRE(one.Y() == 1);
            REQUIRE(one.Z() == 1);

            Vector3 zero = Vector3::Zero();
            REQUIRE(zero.X() == 0);
            REQUIRE(zero.Y() == 0);
            REQUIRE(zero.Z() == 0);
        }
    }

    SECTION("Setters and Getters")
    {
        SECTION("X and Y")
        {
            Vector3 v;
            v.X(10).Y(10).Z(10);
            REQUIRE(v.X() == 10);
            REQUIRE(v.Y() == 10);
            REQUIRE(v.Z() == 10);
        }
        SECTION("Set")
        {
            Vector3 v;
            v.Set(10, 10, 10);
            REQUIRE(v.X() == 10);
            REQUIRE(v.Y() == 10);
            REQUIRE(v.Z() == 10);
        }
    }

    SECTION("Distance")
    {
        SECTION("From {0,0} -> {1,1}")
        {
            Vector3 base = Vector3::Zero();
            Vector3 extension = Vector3::One();

            float result = Vector3::Distance(base, extension);
            REQUIRE(RoundF(result) == RoundF(std::sqrt(3.f)));
            REQUIRE(RoundF(extension.Length()) == RoundF(result));
        }

        SECTION("From negative number")
        {
            Vector3 base = {-2.5f, -4.4f, -6.4f};
            Vector3 extension = {4.2f, 5.9f, 42.f};

            float a = extension.X() - base.X();
            float b = extension.Y() - base.Y();
            float c = extension.Z() - base.Z();
            float expected = std::sqrt(a * a + b * b + c * c);

            float result = Vector3::Distance(base, extension);
            REQUIRE(result == expected);
        }

        SECTION("From mixed negative positive")
        {
            Vector3 base = {2.5412f, -4.4, 214123.4f};
            Vector3 extension = {4.22f, -5.99f, 4142142.57f};

            float a = extension.X() - base.X();
            float b = extension.Y() - base.Y();
            float c = extension.Z() - base.Z();
            float expected = std::sqrt(a * a + b * b + c * c);

            float result = Vector3::Distance(base, extension);
            REQUIRE(result == expected);
        }
    }

    // not implemented yet
//    SECTION("Rotate")
//    {
//        Vector3 vec(1, 0);
//        REQUIRE(vec.X() == 1.f);
//        REQUIRE(vec.Y() == 0.f);
//        vec = Vector3::Rotate(vec, 45);
//        REQUIRE(RoundF(vec.X()) == RoundF(std::sqrt(.5f)));
//        REQUIRE(RoundF(vec.Y()) == RoundF(std::sqrt(.5f)));
//        vec = Vector3::Rotate(vec, 45);
//        REQUIRE(vec.X() == 0.f);
//        REQUIRE(RoundF(vec.Y()) == RoundF(1.f));
//        vec = Vector3::Rotate(vec, 180);
//        REQUIRE(RoundF(vec.X()) == 0.f);
//        REQUIRE(RoundF(vec.Y()) == -1.f);
//        vec = Vector3::Rotate(vec, 45);
//        REQUIRE(RoundF(vec.X()) == RoundF(std::sqrt(.5f)));
//        REQUIRE(RoundF(vec.Y()) == RoundF(-std::sqrt(.5f)));
//        vec = Vector3::Rotate(vec, 45);
//        REQUIRE(RoundF(vec.X()) == 1.f);
//        REQUIRE(RoundF(vec.Y()) == 0.f);
//    }

    SECTION("Length")
    {
        REQUIRE(RoundF(Vector3().Length()) == 0);
        REQUIRE(RoundF(Vector3(1, 1, 1).Length()) == RoundF(std::sqrt(3.f)));
        REQUIRE(RoundF(Vector3(-1, 1, 1).Length()) == RoundF(std::sqrt(3.f)));
        REQUIRE(RoundF(Vector3(1, -1, 1).Length()) == RoundF(std::sqrt(3.f)));
        REQUIRE(RoundF(Vector3(-1, -1, 1).Length()) == RoundF(std::sqrt(3.f)));
    }

    SECTION("Normalize")
    {
        SECTION("Zero Length, no change")
        {
            REQUIRE(Vector3().Normalize() == Vector3::Zero());
        }

        SECTION("Various non-zero lengths")
        {
            REQUIRE(RoundF(Vector3(1, 1, 1).Normalize().Length()) == 1.f);
            REQUIRE(RoundF(Vector3(100, -1241, 123124).Normalize().Length()) == 1.f);
            REQUIRE(RoundF(Vector3(114, 21, 124).Normalize().Length()) == 1.f);
            REQUIRE(RoundF(Vector3(-1, 4121, 423.213f).Normalize().Length()) == 1.f);
            REQUIRE(RoundF(Vector3(-91, -704141.471f, 2143.f).Normalize().Length()) == 1.f);
        }
    }

    SECTION("String")
    {
        REQUIRE(Vector3::Zero() == ParseString(Vector3::Zero().Str()));
        REQUIRE(Vector3::One() == ParseString(Vector3::One().Str()));
        REQUIRE(Vector3(142.124f, -48.5f, 123.f) == ParseString(Vector3(142.124f, -48.5f, 123.f).Str()));
        REQUIRE(Vector3(42.f, 24.f, 876.4f) == ParseString(Vector3(42.f, 24.f, 876.4f).Str()));
        REQUIRE(Vector3(-247.f, -7.f, 876.4f) == ParseString(Vector3(-247.f, -7.f, 876.4f).Str()));
        REQUIRE(Vector3(-44.f, 0, 876.4f) == ParseString(Vector3(-44.f, 0, 876.4f).Str()));
        REQUIRE(Vector3(0, 124, 876.4f) == ParseString(Vector3(0, 124, 876.4f).Str()));
    }

    SECTION("operator << (ostream &)")
    {
        std::stringstream ss;
        ss << Vector3(2235.4124f, -421478.47821f, 2134.f);

        REQUIRE(Vector3(2235.4124f, -421478.47821f, 2134.f) == ParseString(ss.str()));
        ss.str(std::string()); // reset the stream

        ss << Vector3::Zero();

        REQUIRE(Vector3::Zero() == ParseString(ss.str()));
        ss.str(std::string());

        ss << Vector3::One();

        REQUIRE(Vector3::One() == ParseString(ss.str()));
    }

    SECTION("operator == (const Vector3 &)")
    {
        REQUIRE(Vector3::One() == Vector3(1.f, 1.f, 1.f));
        REQUIRE(Vector3::Zero() == Vector3(0, 0, 0));
        REQUIRE(Vector3(245.f, -123.f, -123412.412f) == Vector3(245.f, -123.f, -123412.412f));
        REQUIRE(!(Vector3(-456.f, 51.f, -123412.412f) == Vector3(14.f, -1247890.f, -123412.412f)));
        REQUIRE(Vector3(-245.123f, -123.321f, -123412.412f) == Vector3(-245.123f, -123.321f, -123412.412f));
        REQUIRE(Vector3(123.123f, 123.123f, -123412.412f) == Vector3(123.123f, 123.123f, -123412.412f));
    }

    SECTION("operator != (const Vector3 &)")
    {
        REQUIRE(Vector3::One() != Vector3(10.f, 10.f, 10.f));
        REQUIRE(Vector3(245.f, 123.f, 1.f) != Vector3(245.f, -123.f, -1.f));
        REQUIRE(!(Vector3(-456.f, 51.f, 4.f) != Vector3(-456.f, 51.f, 4.f)));
        REQUIRE(Vector3(245.123f, 123.321f, 41.f) != Vector3(-245.123f, -123.321f, 41.f));
        REQUIRE(Vector3(123.123f, 123.123f, 152.f) != Vector3(123.123f, 123.1233123f, 53.124f));
    }

    SECTION("operator + (const Vector3 &)")
    {
        REQUIRE(Vector3::One() + Vector3::One() == Vector3(2.f, 2.f, 2.f));
        REQUIRE(Vector3::One() + Vector3(-1.f, -1.f, -1.f) == Vector3::Zero());
        REQUIRE(Vector3(123.f, -555.f, 123.f) + Vector3(-10.f, -10.f, 123.f) == Vector3(113.f, -565.f, 246.f));
        REQUIRE(Vector3(44.f, 44.f, 44.f) + Vector3(22.f, -22.f, -44.f) == Vector3(66.f, 22.f, 0));
    }

    SECTION("operator += (const Vector3 &)")
    {
        REQUIRE((Vector3::One() += Vector3::One()) == Vector3(2.f, 2.f, 2.f));
        REQUIRE((Vector3::One() += Vector3(-1.f, -1.f, -1.f)) == Vector3::Zero());
        REQUIRE((Vector3(123.f, -555.f, 123.f) += Vector3(-10.f, -10.f, 123.f)) == Vector3(113.f, -565.f, 246.f));
        REQUIRE((Vector3(44.f, 44.f, 44.f) += Vector3(22.f, -22.f, -44.f)) == Vector3(66.f, 22.f, 0));
    }

    SECTION("operator - (const Vector3 &)")
    {
        REQUIRE(Vector3::One() - Vector3::One() == Vector3::Zero());
        REQUIRE(Vector3(10, 10, 10) - Vector3(9, 9, 9) == Vector3::One());
        REQUIRE(Vector3(-10, -10, -10) - Vector3(-10, -10, -10) == Vector3::Zero());
        REQUIRE(Vector3(44.f, 44.f, 44.f) - Vector3(-22.f, 22.f, 44.f) == Vector3(66.f, 22.f, 0));
    }

    SECTION("operator -= (const Vector3 &)")
    {
        REQUIRE((Vector3::One() -= Vector3::One()) == Vector3::Zero());
        REQUIRE((Vector3(10, 10, 10) -= Vector3(9, 9, 9)) == Vector3::One());
        REQUIRE((Vector3(-10, -10, -10) -= Vector3(-10, -10, -10)) == Vector3::Zero());
        REQUIRE((Vector3(44.f, 44.f, 44.f) -= Vector3(-22.f, 22.f, 44.f)) == Vector3(66.f, 22.f, 0));
    }

    SECTION("operator * (float)")
    {
        REQUIRE(Vector3(123.f, 123.f, 123.f) * 0 == Vector3::Zero());
        REQUIRE(Vector3(14.f, 14.5f, 14.5f) * 1 == Vector3(14.f, 14.5f, 14.5f));
        REQUIRE(Vector3(2.f, 2.f, 2.f) * 1.5f == Vector3(3.f, 3.f, 3.f));
        REQUIRE(Vector3(4.f, 4.f, 4.f) * -10.f == Vector3(-40.f, -40.f, -40.f));
    }

    SECTION("operator *= (float)")
    {
        REQUIRE((Vector3(123.f, 123.f, 123.f) *= 0) == Vector3::Zero());
        REQUIRE((Vector3(14.f, 14.5f, 14.f) *= 1) == Vector3(14.f, 14.5f, 14.f));
        REQUIRE((Vector3(2.f, 2.f, 2.f) *= 1.5f) == Vector3(3.f, 3.f, 3.f));
        REQUIRE((Vector3(4.f, 4.f, 4.f) *= -10.f) == Vector3(-40.f, -40.f, -40.f));
    }

    SECTION("operator / (float)")
    {
        SECTION("Divide by zero throws an error")
        {
            bool didThrow;
            try {
                Vector3 result = Vector3(123.f, 123.f, 123.f) / 0;
                didThrow = false;
            }
            catch(const DivisionByZeroException &e)
            {
                didThrow = true;
            }
            REQUIRE(didThrow);
        }

        SECTION("Typical division")
        {
            REQUIRE(Vector3(14.f, 14.5f, 14.f) / 1 == Vector3(14.f, 14.5f, 14.f));
            REQUIRE(Vector3(2.f, 2.f, 2.f) / 2.f == Vector3::One());
            REQUIRE(Vector3(4.f, 4.f, 5.f) / -10.f == Vector3(-.4f, -.4f, -.5f));
        }
    }

    SECTION("operator /= (float)")
    {
        SECTION("Divide by zero throws an error")
        {
            bool didThrow;
            try {
                Vector3 result = Vector3(123.f, 123.f, 123.f) /= Vector3::Zero();
                didThrow = false;
            }
            catch(const DivisionByZeroException &e)
            {
                didThrow = true;
            }
            REQUIRE(didThrow);
        }

        SECTION("Typical division")
        {
            REQUIRE((Vector3(14.f, 14.5f, 15.6f) /= 1) == Vector3(14.f, 14.5f, 15.6f));
            REQUIRE((Vector3(2.f, 2.f, 2.f) /= 2.f) == Vector3::One());
            REQUIRE((Vector3(4.f, 4.f, 4.f) /= -10.f) == Vector3(-.4f, -.4f, -.4f));
        }
    }

    SECTION("operator * (const Vector3 &)")
    {
        REQUIRE(Vector3(123.f, 123.f, 123.f) * Vector3::Zero() == Vector3::Zero());
        REQUIRE(Vector3(14.f, 14.5f, 16.f) * Vector3::One() == Vector3(14.f, 14.5f, 16.f));
        REQUIRE(Vector3(2.f, 2.f, 2.f) * Vector3(1.5f, 1.5f, 1.5f) == Vector3(3.f, 3.f, 3.f));
        REQUIRE(Vector3(4.f, 4.f, 4.f) * Vector3(-10.f, -10.f, -10.f) == Vector3(-40.f, -40.f, -40.f));
    }

    SECTION("operator *= (const Vector3 &)")
    {
        REQUIRE((Vector3(123.f, 123.f, 121252334.123f) *= Vector3::Zero()) == Vector3::Zero());
        REQUIRE((Vector3(14.f, 14.5f, 421.45f) *= Vector3::One()) == Vector3(14.f, 14.5f, 421.45f));
        REQUIRE((Vector3(2.f, 2.f, 2.f) *= Vector3(1.5f, 1.5f, 1.5f)) == Vector3(3.f, 3.f, 3.f));
        REQUIRE((Vector3(4.f, 4.f, 4.f) *= Vector3(-10.f, -10.f, -10.f)) == Vector3(-40.f, -40.f, -40.f));
    }

    SECTION("operator / (const Vector3 &)")
    {
        SECTION("Division by zero throws an error")
        {
            bool didThrow;
            try {
                Vector3 result = Vector3() /= Vector3::Zero();
                didThrow = false;
            }
            catch(const DivisionByZeroException &e)
            {
                didThrow = true;
            }
            REQUIRE(didThrow);
        }

        SECTION("Typical division")
        {
            REQUIRE(Vector3(14.f, 14.5f, 124.4f) / Vector3::One() == Vector3(14.f, 14.5f, 124.4f));
            REQUIRE(Vector3(2.f, 2.f, 2.f) / (Vector3::One() * 2.f) == Vector3::One());
            REQUIRE(Vector3(4.f, 3.f, 2.f) / Vector3(-10.f, -10.f, -10.f) == Vector3(-.4f, -.3f, -.2f));
        }
    }

    SECTION("operator /= (const Vector3 &)")
    {
        SECTION("Division by zero throws an error")
        {
            bool didThrow;
            try {
                Vector3 result = Vector3() /= 0;
                didThrow = false;
            }
            catch(const DivisionByZeroException &e)
            {
                didThrow = true;
            }
            REQUIRE(didThrow);
        }

        SECTION("Typical division")
        {
            REQUIRE((Vector3(14.5f, 14.54f, 16.1f) /= Vector3::One()) == Vector3(14.5f, 14.54f, 16.1f));
            REQUIRE((Vector3(2.f, 2.f, 2.f) /= (Vector3::One() * 2.f)) == Vector3::One());
            REQUIRE((Vector3(4.f, 4.f, 4.f) /= Vector3(-10.f, -10.f, -100.f)) == Vector3(-.4f, -.4f, -.04f));
        }
    }

    SECTION("- operator")
    {
        Vector3 v;
        REQUIRE(-v == v); // negative zero is zero
        v.Set(10, 10, 10);
        REQUIRE(-v == Vector3(-10, -10, -10));
        REQUIRE(-(-v) == Vector3(10, 10, 10));
        v.Set(14, -28, 42);
        REQUIRE(-v == Vector3(-14, 28, -42));
        REQUIRE(v == -Vector3(-14, 28, -42));
    }
}
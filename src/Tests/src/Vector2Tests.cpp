/* =============================================================================
 * Vector2Tests
 * 
 * 
 * ===========================================================================*/
#include "SDG_Tests.h"
#include <SDG/Math/Vector2.h>
#include <sstream>

static Vector2 ParseString(const String &str)
{
    size_t commaPos = str.FindFirstOf(',');
    size_t braceOpen = str.FindFirstOf('{');
    size_t braceClose = str.FindFirstOf('}');

    if (commaPos != str.NullPos && braceOpen != str.NullPos && braceClose != str.NullPos)
    {
        return {std::stof(str.Substr(1, commaPos-1-braceOpen).Str()),
                std::stof(str.Substr(commaPos+1, braceClose-1-commaPos).Str())};
    }
    else
    {
        // failed to parse string, it was invalid!
        throw std::invalid_argument(str.Cstr());
    }
}


TEST_CASE("Vector2 tests", "[Vector2]")
{
    SECTION("Constructors")
    {
        SECTION("Default")
        {
            Vector2 vec;
            REQUIRE(vec.X() == 0);
            REQUIRE(vec.Y() == 0);

            REQUIRE(vec.W() == 0);
            REQUIRE(vec.H() == 0);

            // Test indexer
            REQUIRE(vec[0] == 0);
            REQUIRE(vec[1] == 0);
        }

        SECTION("Params")
        {
            Vector2 vec(-1, 25);
            REQUIRE(vec.X() == -1);
            REQUIRE(vec.Y() == 25);

            REQUIRE(vec.W() == -1);
            REQUIRE(vec.H() == 25);

            // Test indexer
            REQUIRE(vec[0] == -1);
            REQUIRE(vec[1] == 25);
        }

        SECTION("Static factory funcs")
        {
            Vector2 one = Vector2::One();
            REQUIRE(one.X() == 1);
            REQUIRE(one.Y() == 1);

            Vector2 zero = Vector2::Zero();
            REQUIRE(zero.X() == 0);
            REQUIRE(zero.Y() == 0);
        }
    }

    SECTION("Setters and Getters")
    {
        SECTION("X and Y")
        {
            Vector2 v;
            v.X(10).Y(10);
            REQUIRE(v.X() == 10);
            REQUIRE(v.Y() == 10);
        }
        SECTION("W and H") // {x, y} unioned with {w, h}
        {
            Vector2 v;
            v.W(10).H(10);
            REQUIRE(v.X() == 10);
            REQUIRE(v.Y() == 10);
            REQUIRE(v.W() == 10); // union produces same result
            REQUIRE(v.H() == 10);
        }
        SECTION("Set")
        {
            Vector2 v;
            v.Set(10, 10);
            REQUIRE(v.X() == 10);
            REQUIRE(v.Y() == 10);
        }
    }

    SECTION("Rotate")
    {
        Vector2 vec(1, 0);
        REQUIRE(vec.X() == 1.f);
        REQUIRE(vec.Y() == 0.f);
        vec = Vector2::Rotate(vec, 45);
        REQUIRE(RoundF(vec.X()) == RoundF(std::sqrt(.5f)));
        REQUIRE(RoundF(vec.Y()) == RoundF(std::sqrt(.5f)));
        vec = Vector2::Rotate(vec, 45);
        REQUIRE(vec.X() == 0.f);
        REQUIRE(RoundF(vec.Y()) == RoundF(1.f));
        vec = Vector2::Rotate(vec, 180);
        REQUIRE(RoundF(vec.X()) == 0.f);
        REQUIRE(RoundF(vec.Y()) == -1.f);
        vec = Vector2::Rotate(vec, 45);
        REQUIRE(RoundF(vec.X()) == RoundF(std::sqrt(.5f)));
        REQUIRE(RoundF(vec.Y()) == RoundF(-std::sqrt(.5f)));
        vec = Vector2::Rotate(vec, 45);
        REQUIRE(RoundF(vec.X()) == 1.f);
        REQUIRE(RoundF(vec.Y()) == 0.f);
    }

    SECTION("Length")
    {
        REQUIRE(RoundF(Vector2().Length()) == 0);
        REQUIRE(RoundF(Vector2(1, 1).Length()) == RoundF(std::sqrt(2.f)));
        REQUIRE(RoundF(Vector2(-1, 1).Length()) == RoundF(std::sqrt(2.f)));
        REQUIRE(RoundF(Vector2(1, -1).Length()) == RoundF(std::sqrt(2.f)));
        REQUIRE(RoundF(Vector2(-1, -1).Length()) == RoundF(std::sqrt(2.f)));
    }

    SECTION("Normalize")
    {
        SECTION("Zero Length, no change")
        {
            REQUIRE(Vector2().Normalize() == Vector2::Zero());
        }

        SECTION("Various non-zero lengths")
        {
            REQUIRE(RoundF(Vector2(1, 1).Normalize().Length()) == 1.f);
            REQUIRE(RoundF(Vector2(100, -1241).Normalize().Length()) == 1.f);
            REQUIRE(RoundF(Vector2(114, 21).Normalize().Length()) == 1.f);
            REQUIRE(RoundF(Vector2(-1, 4121).Normalize().Length()) == 1.f);
            REQUIRE(RoundF(Vector2(-91, -704141).Normalize().Length()) == 1.f);
        }
    }

    SECTION("String")
    {
        REQUIRE(Vector2::Zero() == ParseString(Vector2::Zero().Str()));
        REQUIRE(Vector2::One() == ParseString(Vector2::One().Str()));
        REQUIRE(Vector2(142.124f, -48.5f) == ParseString(Vector2(142.124f, -48.5f).Str()));
        REQUIRE(Vector2(42.f, 24.f) == ParseString(Vector2(42.f, 24.f).Str()));
        REQUIRE(Vector2(-247.f, -7.f) == ParseString(Vector2(-247.f, -7.f).Str()));
        REQUIRE(Vector2(-44.f, 0) == ParseString(Vector2(-44.f, 0).Str()));
        REQUIRE(Vector2(0, 124) == ParseString(Vector2(0, 124).Str()));
    }

    SECTION("operator << (ostream &)")
    {
        std::stringstream ss;
        ss << Vector2(2235.4124f, -421478.47821f);

        REQUIRE(Vector2(2235.4124f, -421478.47821f) == ParseString(ss.str()));
        ss.str(std::string()); // reset the stream

        ss << Vector2::Zero();

        REQUIRE(Vector2::Zero() == ParseString(ss.str()));
        ss.str(std::string());

        ss << Vector2::One();

        REQUIRE(Vector2::One() == ParseString(ss.str()));
    }

    SECTION("operator == (const Vector2 &)")
    {
        REQUIRE(Vector2::One() == Vector2(1.f, 1.f));
        REQUIRE(Vector2(245.f, -123.f) == Vector2(245.f, -123.f));
        REQUIRE(!(Vector2(-456.f, 51.f) == Vector2(14.f, -1247890.f)));
        REQUIRE(Vector2(-245.123f, -123.321f) == Vector2(-245.123f, -123.321f));
        REQUIRE(Vector2(123.123f, 123.123f) == Vector2(123.123f, 123.123f));
    }

    SECTION("operator != (const Vector2 &)")
    {
        REQUIRE(Vector2::One() != Vector2(10.f, 10.f));
        REQUIRE(Vector2(245.f, 123.f) != Vector2(245.f, -123.f));
        REQUIRE(!(Vector2(-456.f, 51.f) != Vector2(-456.f, 51.f)));
        REQUIRE(Vector2(245.123f, 123.321f) != Vector2(-245.123f, -123.321f));
        REQUIRE(Vector2(123.123f, 123.123f) != Vector2(123.123f, 123.1233123f));
    }

    SECTION("operator + (const Vector2 &)")
    {
        REQUIRE(Vector2::One() + Vector2::One() == Vector2(2.f, 2.f));
        REQUIRE(Vector2::One() + Vector2(-1.f, -1.f) == Vector2::Zero());
        REQUIRE(Vector2(123.f, -555.f) + Vector2(-10.f, -10.f) == Vector2(113.f, -565.f));
        REQUIRE(Vector2(44.f, 44.f) + Vector2(22.f, -22.f) == Vector2(66.f, 22.f));
    }

    SECTION("operator += (const Vector2 &)")
    {
        REQUIRE((Vector2::One() += Vector2::One()) == Vector2(2.f, 2.f));
        REQUIRE((Vector2::One() += Vector2(-1.f, -1.f)) == Vector2::Zero());
        REQUIRE((Vector2(123.f, -555.f) += Vector2(-10.f, -10.f)) == Vector2(113.f, -565.f));
        REQUIRE((Vector2(44.f, 44.f) += Vector2(22.f, -22.f)) == Vector2(66.f, 22.f));
    }

    SECTION("operator - (const Vector2 &)")
    {
        REQUIRE(Vector2::One() - Vector2::One() == Vector2::Zero());
        REQUIRE(Vector2(10, 10) - Vector2(9, 9) == Vector2::One());
        REQUIRE(Vector2(-10, -10) - Vector2(-10, -10) == Vector2::Zero());
        REQUIRE(Vector2(44.f, 44.f) - Vector2(-22.f, 22.f) == Vector2(66.f, 22.f));
    }

    SECTION("operator -= (const Vector2 &)")
    {
        REQUIRE((Vector2::One() -= Vector2::One()) == Vector2::Zero());
        REQUIRE((Vector2(10, 10) -= Vector2(9, 9)) == Vector2::One());
        REQUIRE((Vector2(-10, -10) -= Vector2(-10, -10)) == Vector2::Zero());
        REQUIRE((Vector2(44.f, 44.f) -= Vector2(-22.f, 22.f)) == Vector2(66.f, 22.f));
    }

    SECTION("operator * (float)")
    {
        REQUIRE(Vector2(123.f, 123.f) * 0 == Vector2::Zero());
        REQUIRE(Vector2(14.f, 14.5f) * 1 == Vector2(14.f, 14.5f));
        REQUIRE(Vector2(2.f, 2.f) * 1.5f == Vector2(3.f, 3.f));
        REQUIRE(Vector2(4.f, 4.f) * -10.f == Vector2(-40.f, -40.f));
    }

    SECTION("operator *= (float)")
    {
        REQUIRE((Vector2(123.f, 123.f) *= 0) == Vector2::Zero());
        REQUIRE((Vector2(14.f, 14.5f) *= 1) == Vector2(14.f, 14.5f));
        REQUIRE((Vector2(2.f, 2.f) *= 1.5f) == Vector2(3.f, 3.f));
        REQUIRE((Vector2(4.f, 4.f) *= -10.f) == Vector2(-40.f, -40.f));
    }

    SECTION("operator / (float)")
    {
        SECTION("Divide by zero throws an error")
        {
            bool didThrow;
            try {
                Vector2 result = Vector2(123.f, 123.f) / 0;
                didThrow = false;
            }
            catch(const InvalidArgumentException &e)
            {
                didThrow = true;
            }
            REQUIRE(didThrow);
        }

        SECTION("Typical division")
        {
            REQUIRE(Vector2(14.f, 14.5f) / 1 == Vector2(14.f, 14.5f));
            REQUIRE(Vector2(2.f, 2.f) / 2.f == Vector2::One());
            REQUIRE(Vector2(4.f, 4.f) / -10.f == Vector2(-.4f, -.4f));
        }
    }

    SECTION("operator /= (float)")
    {
        SECTION("Divide by zero throws an error")
        {
            bool didThrow;
            try {
                Vector2 result = Vector2(123.f, 123.f) /= Vector2::Zero();
                didThrow = false;
            }
            catch(const InvalidArgumentException &e)
            {
                didThrow = true;
            }
            REQUIRE(didThrow);
        }

        SECTION("Typical division")
        {
            REQUIRE((Vector2(14.f, 14.5f) /= 1) == Vector2(14.f, 14.5f));
            REQUIRE((Vector2(2.f, 2.f) /= 2.f) == Vector2::One());
            REQUIRE((Vector2(4.f, 4.f) /= -10.f) == Vector2(-.4f, -.4f));
        }
    }

    SECTION("operator * (const Vector2 &)")
    {
        REQUIRE(Vector2(123.f, 123.f) * Vector2::Zero() == Vector2::Zero());
        REQUIRE(Vector2(14.f, 14.5f) * Vector2::One() == Vector2(14.f, 14.5f));
        REQUIRE(Vector2(2.f, 2.f) * Vector2(1.5f, 1.5f) == Vector2(3.f, 3.f));
        REQUIRE(Vector2(4.f, 4.f) * Vector2(-10.f, -10.f) == Vector2(-40.f, -40.f));
    }

    SECTION("operator *= (const Vector2 &)")
    {
        REQUIRE((Vector2(123.f, 123.f) *= Vector2::Zero()) == Vector2::Zero());
        REQUIRE((Vector2(14.f, 14.5f) *= Vector2::One()) == Vector2(14.f, 14.5f));
        REQUIRE((Vector2(2.f, 2.f) *= Vector2(1.5f, 1.5f)) == Vector2(3.f, 3.f));
        REQUIRE((Vector2(4.f, 4.f) *= Vector2(-10.f, -10.f)) == Vector2(-40.f, -40.f));
    }

    SECTION("operator / (const Vector2 &)")
    {
        SECTION("Division by zero throws an error")
        {
            bool didThrow;
            try {
                Vector2 result = Vector2(123.f, 123.f) /= Vector2::Zero();
                didThrow = false;
            }
            catch(const InvalidArgumentException &e)
            {
                didThrow = true;
            }
            REQUIRE(didThrow);
        }

        SECTION("Typical division")
        {
            REQUIRE(Vector2(14.f, 14.5f) / Vector2::One() == Vector2(14.f, 14.5f));
            REQUIRE(Vector2(2.f, 2.f) / (Vector2::One() * 2.f) == Vector2::One());
            REQUIRE(Vector2(4.f, 4.f) / Vector2(-10.f, -10.f) == Vector2(-.4f, -.4f));
        }
    }

    SECTION("operator /= (const Vector2 &)")
    {
        SECTION("Division by zero throws an error")
        {
            bool didThrow;
            try {
                Vector2 result = Vector2(123.f, 123.f) /= 0;
                didThrow = false;
            }
            catch(const InvalidArgumentException &e)
            {
                didThrow = true;
            }
            REQUIRE(didThrow);
        }

        SECTION("Typical division")
        {
            REQUIRE((Vector2(14.f, 14.5f) /= Vector2::One()) == Vector2(14.f, 14.5f));
            REQUIRE((Vector2(2.f, 2.f) /= (Vector2::One() * 2.f)) == Vector2::One());
            REQUIRE((Vector2(4.f, 4.f) /= Vector2(-10.f, -10.f)) == Vector2(-.4f, -.4f));
        }
    }
}
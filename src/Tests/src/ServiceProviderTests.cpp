#include "SDG_Tests.h"
#include <SDG/Game/ServiceProvider.h>

using namespace SDG;

TEST_CASE("ServiceProvider Tests", "[ServiceProvider]")
{
    ServiceProvider services;

    SECTION("Constructor creates empty ServiceProvider")
    {
        REQUIRE(services.Empty());
        REQUIRE(services.Size() == 0);
    }

    SECTION("Emplace increases ServiceProvider size")
    {
        int i = 20;
        services.Emplace(Ref(i));
        REQUIRE(!services.Empty());
        REQUIRE(services.Size() == 1);
    }

    SECTION("Get tests")
    {
        SECTION("Non-existing type results in null reference")
        {
            auto ref = services.Get<int>();
            REQUIRE(!ref);
        }

        SECTION("Get an existing reference")
        {
            int item = 100;
            services.Emplace(Ref(item));
            auto ref = services.Get<int>();

            REQUIRE(ref);

            int num = 0;
            try {
                num = *ref;
            }
            catch (const NullReferenceException &e)
            {
                // failed test, since dereferencing a nullptr will throw exception
            }

            REQUIRE(num == item); // check that correct number was retrieved
            REQUIRE(ref.Get() == &item);
        }

        SECTION("Get the last stored object of a certain type")
        {
            int a = 10, b = 20;
            services.Emplace(Ref(a));
            REQUIRE(services.Size() == 1);
            services.Emplace(Ref(b));
            REQUIRE(services.Size() == 1);

            auto n = services.Get<int>();
            REQUIRE((n && *n == 20));
            REQUIRE(n.Get() == &b);
        }

        SECTION("Get when there are multiple items stored in container")
        {
            bool b = true;
            int i = 10;
            double d = 20.5;
            float f = 104.1f;

            services
                .Emplace(Ref(b))
                .Emplace(Ref(i))
                .Emplace(Ref(d))
                .Emplace(Ref(f));
            REQUIRE(services.Size() == 4);

            auto iRef = services.Get<int>();
            auto bRef = services.Get<bool>();
            auto fRef = services.Get<float>();
            auto dRef = services.Get<double>();

            REQUIRE((bRef && *bRef == true));
            REQUIRE(bRef.Get() == &b);
            REQUIRE((iRef && *iRef == 10));
            REQUIRE(iRef.Get() == &i);
            REQUIRE((dRef && *dRef == 20.5));
            REQUIRE(dRef.Get() == &d);
            REQUIRE((fRef && *fRef == 104.1f));
            REQUIRE(fRef.Get() == &f);
        }
    }

    SECTION("TryGet tests")
    {
        SECTION("TryGet failed receipt")
        {
            Ref<int> i;
            bool didGet = services.TryGet(i);

            REQUIRE(!didGet);
            REQUIRE(!i);
        }

        SECTION("TryGet successful receipt")
        {
            int num = 10;
            services.Emplace(Ref(num));

            Ref<int> i;
            bool didGet = services.TryGet(i);

            REQUIRE(didGet);
            REQUIRE((i && (*i == num)));
        }

        SECTION("TryGet the last stored object of a certain type")
        {
            int a = 10, b = 20;
            services.Emplace(Ref(a));
            REQUIRE(services.Size() == 1);
            services.Emplace(Ref(b));
            REQUIRE(services.Size() == 1);

            Ref<int> ref;
            services.TryGet<int>(ref);
            REQUIRE((ref && *ref == 20));
            REQUIRE(ref.Get() == &b);
        }

        SECTION("Get when there are multiple items stored in container")
        {
            bool b = true;
            int i = 10;
            double d = 20.5;
            float f = 104.1f;

            Ref<bool> bRef;
            Ref<int> iRef;
            Ref<double> dRef;
            Ref<float> fRef;

            bool didGet;

            services
                    .Emplace(Ref(b))
                    .Emplace(Ref(i))
                    .Emplace(Ref(d))
                    .Emplace(Ref(f));
            REQUIRE(services.Size() == 4);

            didGet = services.TryGet<int>(iRef);
            REQUIRE(didGet);

            didGet = services.TryGet<bool>(bRef);
            REQUIRE(didGet);

            didGet = services.TryGet<float>(fRef);
            REQUIRE(didGet);

            didGet = services.TryGet<double>(dRef);
            REQUIRE(didGet);

            REQUIRE((bRef && *bRef == true));
            REQUIRE(bRef.Get() == &b);
            REQUIRE((iRef && *iRef == 10));
            REQUIRE(iRef.Get() == &i);
            REQUIRE((dRef && *dRef == 20.5));
            REQUIRE(dRef.Get() == &d);
            REQUIRE((fRef && *fRef == 104.1f));
            REQUIRE(fRef.Get() == &f);
        }
    }

    SECTION("Remove Tests")
    {
        SECTION("Remove one item")
        {
            int i = 10;
            Ref<int> iRef;

            services.Emplace(Ref(i));

            REQUIRE(!services.Empty());
            REQUIRE(services.Size() == 1);

            iRef = services.Get<int>();
            REQUIRE((iRef && *iRef == 10));
            REQUIRE(iRef.Get() == &i);

            services.Remove<int>();
            REQUIRE(services.Empty());
            REQUIRE(services.Size() == 0);

            iRef = services.Get<int>();
            REQUIRE(!iRef);
            REQUIRE(iRef.Get() == nullptr);
        }

        SECTION("Remove one item when there are multiple stored; others are unchanged")
        {
            int i = 10;
            float f = .5f;
            double d = 22.12;
            Ref<int> iRef;

            services.Emplace(Ref(i))
                    .Emplace(Ref(d))
                    .Emplace(Ref(f));

            REQUIRE(services.Size() == 3);

            iRef = services.Get<int>();
            REQUIRE((iRef && *iRef == 10));
            REQUIRE(iRef.Get() == &i);

            services.Remove<int>();
            REQUIRE(services.Size() == 2);

            iRef = services.Get<int>();
            REQUIRE(!iRef);
            REQUIRE(iRef.Get() == nullptr);

            auto dRef = services.Get<double>();
            REQUIRE((dRef && *dRef == 22.12));
            REQUIRE(dRef.Get() == &d);

            auto fRef = services.Get<float>();
            REQUIRE((fRef && *fRef == .5f));
            REQUIRE(fRef.Get() == &f);
        }

        SECTION("Remove via chaining")
        {
            int i;
            float f;
            double d;
            char c;

            REQUIRE(services.Empty());
            services
                .Emplace(Ref(i))
                .Emplace(Ref(f))
                .Emplace(Ref(d))
                .Emplace(Ref(c));
            REQUIRE(services.Size() == 4);
            services
                .Remove<int>()
                .Remove<float>()
                .Remove<double>()
                .Remove<char>();
            REQUIRE(services.Empty());
        }

        SECTION("RemoveAll")
        {
            int i;
            float f;
            double d;
            char c;

            REQUIRE(services.Empty());
            services
                    .Emplace(Ref(i))
                    .Emplace(Ref(f))
                    .Emplace(Ref(d))
                    .Emplace(Ref(c));
            REQUIRE(services.Size() == 4);
            services.RemoveAll();
            REQUIRE(services.Empty());
        }
    }
}

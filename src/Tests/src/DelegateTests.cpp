#include <SDG/Lib/Delegate.h>
#include "SDG_Tests.h"

static Delegate<int> delegate;
static int delegateTestCounter = 0;

class TestDelegateObj {
public:
    TestDelegateObj() : val(0) {}

    int val;

    void Doit(int i)
    {
        val = i;
    }

    void RemoveDelegate(int i)
    {
        delegate.RemoveListener(this, &TestDelegateObj::RemoveDelegate);
        val = delegate.Size();
    }
};

void TestDelegateFunc(int i)
{
    ::delegateTestCounter = i;
}
int delegateTestCounter2 = 0;
void TestDelegateFunc2(int i)
{
    ::delegateTestCounter2 = i;
}

TEST_CASE( "Delegate can add, remove, and invoke global, local function objs, and member functions", "[delegate]" ) {
    // Reset variables
    ::delegateTestCounter = 0;
    ::delegateTestCounter2 = 0;
    ::delegate.Clear();
    REQUIRE(delegate.Size() == 0);

    int localFuncVal = 0;
    std::function<void(int)> localFunc = [&localFuncVal] (int i) {
        localFuncVal = i;
    };

    SECTION("Global functions can be added and removed") {
        delegate.AddListener(::TestDelegateFunc);
        REQUIRE(delegate.Size() == 1);

        delegate.RemoveListener(::TestDelegateFunc);
        REQUIRE(delegate.Size() == 0);
    }
    SECTION("Member functions can be added and removed") {
        TestDelegateObj obj;

        delegate.AddListener(&obj, &TestDelegateObj::Doit);
        REQUIRE(delegate.Size() == 1);

        delegate.RemoveListener(&obj, &TestDelegateObj::Doit);
        REQUIRE(delegate.Size() == 0);
    }
    SECTION("Local function objects can be added and removed") {
        delegate.AddListener(&localFunc);
        REQUIRE(delegate.Size() == 1);

        delegate.RemoveListener(&localFunc);
        REQUIRE(delegate.Size() == 0);
    }
    SECTION("Throw InvalidArgumentException when attempting to remove non-existent global func") {
        bool didThrow = false;
        try {
            delegate.RemoveListener(::TestDelegateFunc);
        } catch (const InvalidArgumentException &e) {
            didThrow = true;
        }
        REQUIRE(didThrow);
    }
    SECTION("Throw InvalidArgumentException when attempting to remove non-existent member func") {
        TestDelegateObj obj;

        bool didThrow = false;
        try {
            delegate.RemoveListener(&obj, &TestDelegateObj::Doit);
        } catch (const InvalidArgumentException &e) {
            didThrow = true;
        }
        REQUIRE(didThrow);
    }
    SECTION("Throw InvalidArgumentException when attempting to remove non-existent local func object") {
        bool didThrow = false;
        try {
            delegate.RemoveListener(&localFunc);
        } catch (const InvalidArgumentException &e) {
            didThrow = true;
        }
        REQUIRE(didThrow);
    }
    SECTION("Invoke global function") {
        delegate.AddListener(::TestDelegateFunc);
        REQUIRE(delegate.Size() == 1);
        delegate.Invoke(20);
        REQUIRE(::delegateTestCounter == 20);
    }
    SECTION("Invoke member function") {
        TestDelegateObj obj;
        REQUIRE(obj.val == 0);
        delegate.AddListener(&obj, &TestDelegateObj::Doit);
        REQUIRE(delegate.Size() == 1);
        delegate.Invoke(100);
        REQUIRE(obj.val == 100);
    }
    SECTION("Invoke local function object") {
        delegate.AddListener(&localFunc);
        REQUIRE(delegate.Size() == 1);
        delegate.Invoke(20);
        REQUIRE(localFuncVal == 20);
    }
    SECTION("Global function does not invoke after removal") {
        delegate.AddListener(::TestDelegateFunc);
        REQUIRE(delegateTestCounter == 0);
        delegate.RemoveListener(::TestDelegateFunc);
        delegate.Invoke(2000);
        REQUIRE(delegateTestCounter == 0);
    }
    SECTION("Member function does not invoke after removal") {
        TestDelegateObj obj;
        delegate.AddListener(&obj, &TestDelegateObj::Doit);
        REQUIRE(delegate.Size() == 1);
        REQUIRE(obj.val == 0);
        delegate.RemoveListener(&obj, &TestDelegateObj::Doit);
        delegate.Invoke(4123);
        REQUIRE(obj.val == 0);
    }
    SECTION("Local function object does not invoke after removal") {
        delegate.AddListener(&localFunc);
        REQUIRE(localFuncVal == 0);
        delegate.RemoveListener(&localFunc);
        delegate.Invoke(2000);
        REQUIRE(localFuncVal == 0);
    }
    SECTION("Multiple global functions invoke the same value") {
        delegate.AddListener(::TestDelegateFunc);
        REQUIRE(delegate.Size() == 1);
        delegate.AddListener(::TestDelegateFunc2);
        REQUIRE(delegate.Size() == 2);
        delegate.Invoke(2345);
        REQUIRE(delegateTestCounter == 2345);
        REQUIRE(delegateTestCounter2 == 2345);
    }
    SECTION("Multiple member functions invoke the same value") {
        TestDelegateObj a, b;

        delegate.AddListener(&a, &TestDelegateObj::Doit);
        REQUIRE(delegate.Size() == 1);
        delegate.AddListener(&b, &TestDelegateObj::Doit);
        REQUIRE(delegate.Size() == 2);
        delegate.Invoke(2345);
        REQUIRE(a.val == 2345);
        REQUIRE(b.val == 2345);
    }
    SECTION("Multiple local function objects invoke the same value") {
        int localFuncVal2 = 0;
        std::function<void(int)> localFunc2 = [&localFuncVal2](int i) {
            localFuncVal2 = i;
        };

        delegate.AddListener(&localFunc);
        REQUIRE(delegate.Size() == 1);
        delegate.AddListener(&localFunc2);
        REQUIRE(delegate.Size() == 2);
        delegate.Invoke(2345);
        REQUIRE(localFuncVal== 2345);
        REQUIRE(localFuncVal2 == 2345);
    }
    SECTION("Global function and member functions invocable at the same time") {
        TestDelegateObj obj;
        delegate.AddListener(&obj, &TestDelegateObj::Doit);
        REQUIRE(delegate.Size() == 1);
        delegate.AddListener(::TestDelegateFunc);
        REQUIRE(delegate.Size() == 2);
        delegate.Invoke(145);
        REQUIRE(obj.val == 145);
        REQUIRE(delegateTestCounter == 145);
    }
    SECTION("Removals happen after every invocation is finished") {
        TestDelegateObj obj;
        delegate.AddListener(&obj, &TestDelegateObj::RemoveDelegate);
        REQUIRE(delegate.Size() == 1);
        delegate.Invoke(204); // arbitrary val

        // In TestDelegateObj::RemoveDelegate removes itself from the delegate, and
        // subsequently sets its val member to the delegate size.
        // If it's 1, and we later check delegate.Size() to be 0,
        // it demonstrates that it's handle was not removed until after each callback finished.
        REQUIRE(obj.val == 1);
        REQUIRE(delegate.Size() == 0);
    }

}

//
// Created by aishi on 4/22/2022.
//
#pragma once
#include <SDG/Events.h>
#include <SDG/Logging.h>

using namespace SDG;

int delegateTestCounter = 0;
Delegate<int> delegate;

void TestDelegateFunc(int i)
{
    delegateTestCounter = i;
}

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

void TestDelegate()
{
    delegate.AddListener(TestDelegateFunc);
    SDG_Assert(delegate.Size() == 1);
    delegate.Invoke(10);
    SDG_Assert(delegateTestCounter == 10);

    TestDelegateObj obj;
    SDG_Assert(obj.val == 0);
    delegate.AddListener(&obj, &TestDelegateObj::Doit);
    SDG_Assert(delegate.Size() == 2);
    delegate.Invoke(20);
    SDG_Assert(obj.val == 20);
    SDG_Assert(delegateTestCounter == 20);

    // Instant Removals
    delegate.RemoveListener(TestDelegateFunc);
    SDG_Assert(delegate.Size() == 1);
    delegate.Invoke(100);
    SDG_Assert(delegateTestCounter == 20);
    SDG_Assert(obj.val == 100);

    delegate.RemoveListener(&obj, &TestDelegateObj::Doit);
    SDG_Assert(delegate.Size() == 0);
    delegate.Invoke(200);
    SDG_Assert(delegateTestCounter == 20);
    SDG_Assert(obj.val == 100);

    // Removals after call
    delegate.AddListener(&obj, &TestDelegateObj::RemoveDelegate);
    SDG_Assert(delegate.Size() == 1);
    delegate.Invoke(2);

    // obj.val is set to the size of the delegate during the callback.
    // Checking it maintains size==1 demonstrates that its handle was not removed until after the call is finished.
    SDG_Assert(obj.val == 1);
    SDG_Assert(delegate.Size() == 0);
}
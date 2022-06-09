#include "DynamicState.h"

#include <utility>

namespace SDG
{
    DynamicState &DynamicState::OnStart(std::function<void(float)> callback)
    {
        start = std::move(callback);
        return *this;
    }

    DynamicState &DynamicState::OnUpdate(std::function<void(float)> callback)
    {
        update = std::move(callback);
        return *this;
    }

    DynamicState &DynamicState::OnEnd(std::function<void(float)> callback)
    {
        end = std::move(callback);
        return *this;
    }

    DynamicState &DynamicState::OnPause(std::function<void(float)> callback)
    {
        pause = std::move(callback);
        return *this;
    }

    DynamicState &DynamicState::OnResume(std::function<void(float)> callback)
    {
        resume = std::move(callback);
        return *this;
    }
}

#pragma once
#include <SDG/Lib/ClassMacros.h>

#include <functional>

namespace SDG
{
    /// State that can change its state function as callbacks on the fly.
    /// Intended for use in scripting-like scenarios such as player behavior.
    class DynamicState
    {
        SDG_NOCOPY(DynamicState);
    private:
        friend class DynamicStateMachine;
    public:
        DynamicState() = default;
        ~DynamicState() = default;

        /// Sets the start callback
        /// @param callback - called when state starts just before the first
        /// update. Callback receives total seconds taken in the last state
        DynamicState &OnStart(std::function<void(float)> callback);
        bool HasStart() const { return static_cast<bool>(start);  }

        /// Sets the update callback
        /// @param callback - called when state updates
        /// Callback receives total seconds taken in this state so far
        DynamicState &OnUpdate(std::function<void(float)> callback);
        bool HasUpdate() const { return static_cast<bool>(update); }

        /// Sets the end callback
        /// @param callback - called when state ends
        /// Callback receives total seconds taken in this state
        DynamicState &OnEnd(std::function<void(float)> callback);
        bool HasEnd() const { return static_cast<bool>(end); }

        /// Sets the pause callback
        /// @param callback - called when state pauses
        /// Callback receives total seconds taken in this state so far
        DynamicState &OnPause(std::function<void(float)> callback);
        bool HasPause() const { return static_cast<bool>(pause); }

        /// Sets the resume callback
        /// @param callback - called when state resumes
        /// Callback receives total seconds of the last state before resuming.
        /// State time is reset.
        DynamicState &OnResume(std::function<void(float)> callback);
        bool HasResume() const { return static_cast<bool>(resume); }
        
        /// Checks if empty, which means no callbacks have been set yet
        bool Empty() const { return (!start && !update && !end && !pause && !resume); }
    private:
        /// Called when state starts just before the first update. 
        /// Callback function receives total seconds taken in the last state
        std::function<void(float)> start;

        /// Called during every update iteration.
        /// Callback function receives total seconds taken in this state
        std::function<void(float)> update;

        /// Called when state ends. Receives the total seconds taken in
        /// this state
        std::function<void(float)> end;

        /// Called when the state pauses. Receives total seconds
        /// taken in this state
        std::function<void(float)> pause;

        /// Called when the state unpauses. Receives total seconds
        /// taken in this state
        std::function<void(float)> resume;
    };
}
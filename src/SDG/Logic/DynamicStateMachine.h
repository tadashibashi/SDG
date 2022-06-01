/*!
 * @file DynamicStateMachine.h
 * @namespace SDG
 * @class DynamicStateMachine
 * Stores and drives DynamicState objects. It is called "dynamic" because
 * you can reset callbacks anytime on-the-fly. This state machine is intended
 * for use in scripting-like scenarios, such as creating game object behavior.
 */
#pragma once
#include "DynamicState.h"

#include <SDG/Lib/Ref.h>

#include <map>
#include <stack>

namespace SDG
{
    /// Stores and drives states that can change its state function as
    /// callbacks on the fly. Intended for use in scripting-like scenarios
    /// such as player behavior.
    class DynamicStateMachine
    {
    public:
        DynamicStateMachine() : stateTime(0), nextState(), states(), stack(),
            isRemoving(), isReplacing() { }

        // ========== Usage =================

        /// Starts a state
        /// @param key - key of the state to start
        /// @param replaceCurrent - true: ends the current state;
        ///                         false: pauses the current state
        template <typename KeyType>
        void Start(KeyType key, bool replaceCurrent = true)
        {
            nextState = states[(size_t)key];
            isReplacing = replaceCurrent;
        }

        /// Ends the current state, unpausing the last state if one was paused
        void EndCurrent()
        {
            isRemoving = true;
        }


        // ========== State driver ==========

        /// Drives the state machine
        void Update(float deltaSeconds);


        // ========== State access ==========

        /// non-const indexer
        template <typename KeyType>
        DynamicState &operator[] (KeyType key)  { return states[(int)key]; }

        /// const indexer
        template <typename KeyType>
        [[nodiscard]] const DynamicState &operator[] (KeyType key) const { return states[(int)key]; }
    private:
        // storage-related members
        std::map<size_t, DynamicState> states;

        // driver-related members
        std::stack<Ref<DynamicState>> stack;
        Ref<DynamicState> nextState;
        bool isRemoving, isReplacing;
        float stateTime;

        void ProcessChanges();

    };
}
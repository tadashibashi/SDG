#include "DynamicStateMachine.h"

void SDG::DynamicStateMachine::ProcessChanges()
{
    if (isRemoving) // end current state
    {
        if (!stack.empty())
        {
            if (stack.top()->end)
                stack.top()->end(stateTime);
            stack.pop();

            // If no next state to start, resume the last one, if any
            if (!nextState)
            {
                if (!stack.empty() && stack.top()->resume)
                    stack.top()->resume(stateTime);

                // resets time only if no nextState, since we'll need
                // stateTime if there is one
                stateTime = 0;
            }
        }

        isRemoving = false;
    }

    if (nextState) // start next state
    {
        if (isReplacing) // remove and end last state
        {
            if (!stack.empty())
            {
                if (stack.top()->end)
                    stack.top()->end(stateTime);
                stack.pop();
            }

            isReplacing = false;
        }
        else             // pause last state
        {
            if (!stack.empty() && stack.top()->pause)
                stack.top()->pause(stateTime);
        }

        nextState->start(stateTime);
        stack.push(nextState);
        nextState = nullptr;
        stateTime = 0;
    }
}

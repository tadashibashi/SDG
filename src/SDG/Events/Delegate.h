/* =============================================================================
 * Delegate
 * An event observer that can make callbacks to subscribed listeners when an event has occured.
 * Listeners are created and stored within the Delegate, so no subclassing of a Listener class
 * is necessary as seen in the common Observer pattern.
 * Both member and global function callback Listeners are supported. To add one, you only need to pass
 * a function pointer to AddListener (and a corresponding object for member functions).
 * Listeners may be removed by a call to RemoveListener and passing the same pointer that was
 * previously added.
 *
 * ===========================================================================*/
#pragma once
#include <any>
#include <functional>
#include <typeinfo>
#include <vector>

using std::any_cast;

namespace SDG {

    /**
     * @tparam Args Argument types that the Delegate requires for each of its callback listeners.
     */
    template <typename... Args>
    class Delegate {
    private:
        // Indicates whether a FunctionWrapper contains a Member of Global function
        enum class FunctionType { Member, Global };

        // Class wrapping a Delegate's callback functions
        class FunctionWrapper {
        public:
            FunctionWrapper() = delete;

            // Used to wrap member function pointer
            template <typename T>
            FunctionWrapper(T *object, void (T::*func)(Args...)) :
                    object(object), functionPtr(func),
                    function([func, object](Args... args)->void
                        {
                            (object->*func)(args...);
                        })
            {
            }

            // Used to wrap member function pointer
            explicit FunctionWrapper(void (*func)(Args...)) :
                    object(nullptr), functionPtr(func), function(func)
            {
            }

            void operator()(Args ...args)
            {
                if (function)
                    function(args...);
            }

            // ========== Signature Checks ==========

            // Returns whether this is a Global or Member function. Intended for debug use.
            FunctionType GetType() const
            {
                return (object == nullptr) ? FunctionType::Global : FunctionType::Member;
            }

            // Checks signature against an object ptr + member function
            template <typename T>
            bool SignatureMatches(T *pObject, void (T::*pFunctionPtr)(Args...)) const
            {
                return ((void *)pObject == object &&
                        typeid(pFunctionPtr) == functionPtr.type() &&
                        pFunctionPtr == any_cast<void(T::*)(Args...)>(functionPtr));
            }

            // Checks equality for a specific global function
            bool SignatureMatches(void(*pFunctionPtr)(Args...)) const
            {
                return (object == nullptr &&
                        //functionPtr.type() == typeid(pFunctionPtr) &&
                        any_cast<void(*)(Args...)>(functionPtr) == pFunctionPtr);
            }

            // Whether or not this FunctionWrapper is to be removed or not.
            bool toRemove{false};
        private:
            void *object; // the object to call the function on, if a member func is stored
            std::any functionPtr; // any enables wrapper to store and compare different types of func ptrs for id
            std::function<void(Args...)> function; // the function to call
        };
    public:
        // Gets the number of listeners currently attached to this Delegate.
        int Size()
        {
            return (int)functions.size();
        }

        // Removes all previously added listeners.
        // Faster than individually removing each listener.
        void Clear()
        {
            if (isCalling)
            {
                for (auto &f : functions)
                    f.toRemove = true;

                removeThisFrame = true;
            }
            else
            {
                functions.clear();
            }
        }

        // Fires the callback to each subscribed listener
        void Invoke(Args... args)
        {
            if (functions.empty()) return;

            isCalling = true;
            for (FunctionWrapper &func : functions)
            {
                func(args...);
            }
            isCalling = false;

            ProcessRemovals();
        }

        // Fires the callback to each subscribed listener
        void operator()(Args... args)
        {
            Invoke(std::forward<Args>(args)...);
        }

        // Adds a member function listener for a particular object
        template <typename T>
        void AddListener(T *object, void (T::*func)(Args...))
        {
            functions.emplace_back(std::move(FunctionWrapper(object, func)));
        }

        // Adds a global function listener
        void AddListener(void (*func)(Args...))
        {
            functions.emplace_back(std::move(FunctionWrapper(func)));
        }

        // Removes an object + member function listener.
        template <typename T>
        void RemoveListener(T *object, void (T::*func)(Args...))
        {
            // Find the listener
            auto it = std::find_if(functions.begin(), functions.end(),
                                   [object, func](auto &f)
                                   {
                                       return f.SignatureMatches(object, func);
                                   });

            // If it exists, remove it
            if (it != functions.end())
            {
                if (isCalling) // Delegate busy calling, flag for later removal
                {
                    it->toRemove = true;
                    removeThisFrame = true;
                }
                else           // Delegate is free, remove now
                {
                    functions.erase(it);
                }
            }
        }

        // Removes a global function listener.
        void RemoveListener(void (*func)(Args...))
        {
            auto it = std::find_if(functions.begin(), functions.end(),
                                   [func](auto &f)
                                   {
                                       return f.SignatureMatches(func);
                                   });

            if (it != functions.end())
            {
                if (isCalling)
                {
                    it->toRemove = true;
                    removeThisFrame = true;
                }
                else
                {
                    functions.erase(it);
                }
            }
        }

    private:
        // Processes removals after delegate has been fired.
        void ProcessRemovals()
        {
            // Only perform removals if flag was set
            if (removeThisFrame)
            {
                // Erase all function wrappers with "toRemove" flag set
                functions.erase(
                        std::remove_if(functions.begin(), functions.end(),
                                       [](const FunctionWrapper &f) {
                                           return f.toRemove;
                                       }),
                        functions.end());

                // Unset flag
                removeThisFrame = false;
            }
        }

        // List of listeners
        std::vector<FunctionWrapper> functions{};

        // Flag indicating if this delegate is currently firing callbacks or not.
        bool isCalling{false};

        // Flag indicated whether or not removals need to be processed.
        bool removeThisFrame{false};
    };


}

/* =============================================================================
 * Delegate
 *
 * ===========================================================================*/
#pragma once
#include <any>
#include <functional>
#include <typeinfo>
#include <vector>
#include <SDG/Exceptions/InvalidArgumentException.h>

using std::any_cast;

namespace SDG {

    /**
     * @abstract
     * A Delegate is an event observer that can invoke callbacks of subscribed listeners when an event has occured.
     * "Listeners" are actually function pointers the user passes into the Delegate, which gets wraps and stored inside.
     * No subclassing of a Listener class is necessary, as seen in the typical Observer pattern.
     * Both member and global function callbacks are supported.
     *
     * @details
     * In practice, to add a callback, you will pass a global function pointer to AddListener, or another overload
     * where you can pass an object with a corresponding member function pointer.
     * Function signature must match that of the Delegate.
     * Listeners may be removed by a call to RemoveListener and passing the same global function pointer or object +
     * member function combination.
     *
     * When invoking a Delegate, simply call Invoke, or the operator() and pass the arguments.
     * These arguments are copied for each callback, so it is wise to use small objects like pointers/refs,
     * primitives or small structs.
     *
     * @tparam Args Argument types that the Delegate requires for each of its callback listeners.
     *
     */
    template <typename... Args>
    class Delegate {
    private:
        /// Indicates whether a FunctionWrapper contains a Member of Global function
        enum class FunctionType { Member, Global };

        /// Helper class that wraps a Delegate's subscribed listener callbacks.
        /// Enables identification of the wrapped callback via both global function pointer
        /// or object pointer + its member function pointer.
        class FunctionWrapper {
        public:
            FunctionWrapper() = delete;

            /// Used to wrap member function pointer
            template <typename T>
            FunctionWrapper(T *object, void (T::*func)(Args...)) :
                    object(object), functionPtr(func),
                    function([func, object](Args... args)->void
                        {
                            (object->*func)(args...);
                        })
            {
            }

            /// Used to wrap member function pointer
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

            /// Returns whether this is a Global or Member function. Intended for debug use.
            FunctionType CallbackType() const
            {
                return (object == nullptr) ? FunctionType::Global : FunctionType::Member;
            }

            /// Checks signature against an object ptr + member function
            template <typename T>
            bool SignatureMatches(T *pObject, void (T::*pFunctionPtr)(Args...)) const
            {
                return ((void *)pObject == object &&
                        typeid(pFunctionPtr) == functionPtr.type() &&
                        pFunctionPtr == any_cast<void(T::*)(Args...)>(functionPtr));
            }

            /// Checks equality for a specific global function
            bool SignatureMatches(void(*pFunctionPtr)(Args...)) const
            {
                return (object == nullptr &&
                        //functionPtr.type() == typeid(pFunctionPtr) &&
                        any_cast<void(*)(Args...)>(functionPtr) == pFunctionPtr);
            }

            /// represents if this FunctionWrapper is flagged to be removed or not.
            bool toRemove{false};
        private:
            void *object; // the object to call the function on, if a member func is stored
            std::any functionPtr; // any enables wrapper to store and compare different types of func ptrs for id
            std::function<void(Args...)> function; // the function to call
        };
    public:
        Delegate() = default;
        // Prevent copying and assignment
        Delegate(const Delegate &) = delete;
        Delegate &operator=(const Delegate &) = delete;

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
            else
            {
                throw InvalidArgumentException(__FUNCTION__, "object or func",
                                               "There was no matching callback in the Delegate.");
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
            else
            {
                throw InvalidArgumentException(__FUNCTION__, "func",
                                               "There was no matching callback in the Delegate.");
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

        // Flag indicated whether removals need to be processed.
        bool removeThisFrame{false};
    };

}

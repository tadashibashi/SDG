/*!
 * @file Delegate.h
 * @class Delegate
 * An event observer class that is similar in use to javascript's event handling, except with type safety.
 *
 */
#pragma once
#include <SDG/Lib/ClassMacros.h>

#include <any>
#include <cstddef>
#include <functional>
#include <vector>

namespace SDG {

    /**
     * @class
     * A Delegate is an event observer that can invoke callbacks of subscribed listeners when an event has occured.
     * "Listeners" are actually function pointers the user passes into the Delegate, which gets wrapped and stored inside.
     * No subclassing of a Listener class is necessary, which is the main difference from the Observer pattern.
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
    class Delegate
    {
        SDG_NOCOPY(Delegate);
    private:

        /// Helper class that wraps a Delegate's subscribed listener callbacks.
        /// Enables identification of the wrapped callback via both global function pointer
        /// or object pointer + its member function pointer.
        struct FunctionWrapper {
            friend class Delegate;
            FunctionWrapper() = delete;

            /// Used to wrap member function pointer
            template <typename T>
            FunctionWrapper(T *object, void (T:: *func)(Args...));

            /// Used to wrap member function pointer
            explicit FunctionWrapper(void (*func)(Args...));

            explicit FunctionWrapper(std::function<void(Args...)> *func);

            void operator()(Args ...args);

            // ========== Signature Checks ==========
            /// Checks signature against an object ptr + member function
            template <typename T>
            bool SignatureMatches(T *pObject, void (T:: *pFunctionPtr)(Args...)) const;

            /// Checks equality for a specific global function
            bool SignatureMatches(void(*pFunctionPtr)(Args...)) const;

            bool SignatureMatches(std::function<void(Args...)> *func) const;

        private:
            void *object; // the object to call the function on, if a member func is stored
            std::any functionPtr; // any enables wrapper to store and compare different types of func ptrs for id
            std::function<void(Args...)> function; // the function to call

            /// represents if this FunctionWrapper is flagged to be removed or not.
            bool toRemove{ false };
        };
    public:
        Delegate() : functions(), isCalling(), removeThisFrame() { }

        // Gets the number of listeners currently attached to this Delegate.
        size_t Size() { return functions.size(); }

        // Removes all previously added listeners.
        // Faster than individually removing each listener.
        void Clear();

        // Fires the callback to each subscribed listener
        void Invoke(Args... args);

        // Fires the callback to each subscribed listener
        void operator()(Args... args);

        // Adds a member function listener for a particular object
        template <typename T>
        void AddListener(T *object, void (T:: *func)(Args...));

        // Adds a global function listener
        void AddListener(void (*func)(Args...));

        // Adds a pointer to an std::function object
        void AddListener(std::function<void(Args...)> *func);

        // Removes an object + member function listener.
        template <typename T>
        void RemoveListener(T *object, void (T:: *func)(Args...));

        // Removes a global function listener.
        void RemoveListener(void (*func)(Args...));

        // Removes an std::function listener.
        void RemoveListener(std::function<void(Args...)> *func);

    private:
        // Processes removals after delegate has been fired.
        void ProcessRemovals();

        // List of listeners
        std::vector<FunctionWrapper> functions;

        // Flag indicating if this delegate is currently firing callbacks or not.
        bool isCalling;

        // Flag indicated whether removals need to be processed.
        bool removeThisFrame;
    };

}

#include "Delegate.inl"

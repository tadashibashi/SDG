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
     * Inspired by JavaScript listeners and C# delegates, "Listeners" are actually function pointers the user passes 
     * into the Delegate, which gets wrapped and stored inside.
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
     * @tparam Args - argument types that the Delegate requires for each of its callback listeners.
     *
     */
    template <typename Ret, typename... Args>
    class Delegate
    {
        SDG_NOCOPY(Delegate);
    private:

        /// Helper class that wraps a Delegate's subscribed listener callbacks.
        /// Enables identification of the wrapped callback via both global function pointer
        /// or object pointer + its member function pointer.
        class FunctionWrapper {
            friend class Delegate;
        public:
            template <typename T>
            FunctionWrapper(T *object, Ret (T:: *func)(Args...));
            explicit FunctionWrapper(Ret (*func)(Args...));
            explicit FunctionWrapper(std::function<Ret(Args...)> *func);
            FunctionWrapper() = delete;

            template <typename T>
            bool SignatureMatches(T *pObject, Ret (T:: *pFunctionPtr)(Args...)) const;
            bool SignatureMatches(Ret(*pFunctionPtr)(Args...)) const;
            bool SignatureMatches(std::function<Ret(Args...)> *func) const;

            Ret operator()(Args ...args) const;
        private:
            void *object;         // object to call the function on, if a member func is stored; null when none.
            std::any functionPtr; // stores the fn pointer id; we need std::any since member fn ptrs have no portable type.
            std::function<Ret(Args...)> function; // the callable function
            bool toRemove;        // flag the marks if this wrapper should be removed from Delegate
        };
    public:
        Delegate() : functions(), removeThisFrame() { }
        Delegate(Delegate &&moved);
        Delegate &operator = (Delegate &&moved);

    public:
        // Adds a member function listener for a particular object
        template<typename T>
        void AddListener(T *object, Ret (T:: *func)(Args...));

        // Adds a global function listener
        void AddListener(Ret (*func)(Args...));

        // Adds a pointer to an std::function object
        void AddListener(std::function<Ret(Args...)> *func);

        // Removes an object + member function listener.
        template<typename T>
        void RemoveListener(T *object, Ret (T:: *func)(Args...));

        /// Removes a global function listener.
        void RemoveListener(void (*func)(Args...));

        /// Removes an std::function pointer listener.
        void RemoveListener(std::function<Ret(Args...)> *func);

        /// Removes all previously added listeners.
        /// Faster than individually removing each listener.
        void Clear();

        // ===== Calling the delegate =================================================================================
        /// Attempts to fire the callback, ignoring the return value.
        /// Instead of the return value, a bool will be returned: 
        /// true: if any callback was called; false: if no callbacks were called, due to being empty.
        bool TryInvoke(Args... args);

        /// Fires the callback to each subscribed listener; returns the result of the last one.
        /// If there are no listeners, a RuntimeException will be thrown.
        /// Please check if (!Empty()), or if (Delegate &) before calling.
        Ret Invoke(Args... args);

        /// Fires the callback to each subscribed listener; returns the result of the last one
        /// If there are no listeners, a RuntimeException will be thrown.
        /// Please check if (!Empty()), or if (Delegate &) before calling.
        Ret operator()(Args... args);


        /// Gets the number of listeners currently attached to this Delegate.
        size_t Size() const { return functions.size(); }

        /// Checks if no listeners are attached to this Delegate.
        bool Empty() const { return functions.empty(); }

        /// checks if any listeners are attached to this Delegate.
        explicit operator bool() { return !functions.empty(); }        
        
        /// Processes removals from RemoveListener functions. Automatically called at the beginning
        /// of Invoke and TryInvoke.
        void ProcessRemovals();
    private:


        // List of listeners
        std::vector<FunctionWrapper> functions;

        // Flag indicated whether removals need to be processed.
        bool removeThisFrame;
    };

    template <typename Ret, typename...Args>
    class Delegate<Ret(Args...)> : public Delegate<Ret, Args...> { };

}

#include "Delegate.inl"

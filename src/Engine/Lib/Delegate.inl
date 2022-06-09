#include "Delegate.h"

#include <Engine/Exceptions/Fwd.h>

#include <algorithm>
#include <typeinfo>
#include <utility>

namespace SDG
{
    // ===== Delegate Implementation ==================================================================================
    template<typename Ret, typename... Args>
    Delegate<Ret, Args...>::Delegate(Delegate &&moved) :
        functions(std::move(moved.functions)), removeThisFrame(moved.removeThisFrame)
    {
        
    }

    template<typename Ret, typename...Args>
    Delegate<Ret, Args...> &Delegate<Ret, Args...>::operator = (Delegate &&moved)
    {
        functions = std::move(moved.functions);
        removeThisFrame = moved.removeThisFrame;

        return *this;
    }
    
    template<typename Ret, typename... Args>
    void Delegate<Ret, Args...>::Clear()
    {
        for (auto &f : functions)
            f.toRemove = true;

        removeThisFrame = true;
    }

    template<typename Ret, typename... Args>
    Ret Delegate<Ret, Args...>::Invoke(Args... args)
    {
        if (functions.empty())
            throw RuntimeException("Called Invoke on an empty Delegate: Delegate must contain at least one callback.");
        
        ProcessRemovals();
        for (auto it = functions.begin(), end = functions.end() - 1; it != end; ++it)
            (*it)(args...);

        return (*(functions.end() - 1))(args...);
    }

    template<typename Ret, typename... Args>
    bool Delegate<Ret, Args...>::TryInvoke(Args... args)
    {
        ProcessRemovals();
        for (auto &func : functions)
            func(args...);
        return !functions.empty();
    }

    template<typename Ret, typename... Args>
    Ret Delegate<Ret, Args...>::operator()(Args... args)
    {
        return Invoke(args...);
    }

    template<typename Ret, typename... Args>
    template<typename T>
    void Delegate<Ret, Args...>::RemoveListener(T *object, Ret (T:: *func)(Args...))
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
            it->toRemove = true;
            removeThisFrame = true;
        }
        else
        {
            ThrowInvalidArgumentException(__FUNCTION__, "object or func",
                "There was no matching callback in the Delegate.");
        }
    }

    template<typename Ret, typename... Args>
    void Delegate<Ret, Args...>::RemoveListener(void (*func)(Args...))
    {
        auto it = std::find_if(functions.begin(), functions.end(),
            [func](const auto &f)
            {
                return f.SignatureMatches(func);
            });

        if (it != functions.end())
        {
            it->toRemove = true;
            removeThisFrame = true;
        }
        else
        {
            ThrowInvalidArgumentException(__FUNCTION__, "func",
                "There was no matching callback in the Delegate.");
        }
    }

    template<typename Ret, typename... Args>
    void Delegate<Ret, Args...>::RemoveListener(std::function<Ret(Args...)> *func)
    {
        auto it = std::find_if(functions.begin(), functions.end(),
            [func](const auto &f)
            {
                return f.SignatureMatches(func);
            });

        if (it != functions.end())
        {
            it->toRemove = true;
            removeThisFrame = true;
        }
        else
        {
            ThrowInvalidArgumentException(__func__, "func",
                "There was no matching callback in the Delegate.");
        }
    }

    template<typename Ret, typename... Args>
    template<typename T>
    void Delegate<Ret, Args...>::AddListener(T *object, Ret (T:: *func)(Args...))
    {
        if (!object)
            ThrowInvalidArgumentException(__func__, "object", "object was null");
        if (!func)
            ThrowInvalidArgumentException(__func__, "func", "callback function ptr was null");

        functions.emplace_back(std::move(FunctionWrapper(object, func)));
    }

    template<typename Ret, typename... Args>
    void Delegate<Ret, Args...>::AddListener(Ret (*func)(Args...))
    {
        if (!func)
            ThrowInvalidArgumentException(__func__, "func", "callback function ptr was null");

        functions.emplace_back(std::move(FunctionWrapper(func)));
    }

    template<typename Ret, typename... Args>
    void Delegate<Ret, Args...>::AddListener(std::function<Ret(Args...)> *func)
    {
        if (!func)
            ThrowInvalidArgumentException(__func__, "func", "callback function ptr was null");
        if (!(*func))
            ThrowInvalidArgumentException(__func__, "func", "callback function does not have a target");

        functions.emplace_back(std::move(FunctionWrapper(func)));
    }

    template<typename Ret, typename... Args>
    void Delegate<Ret, Args...>::ProcessRemovals()
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


    // ===== Delegate<Ret, Args...>::FunctionWrapper Implementation ========================================================

    template<typename Ret, typename... Args>
    template<typename T>
    Delegate<Ret, Args...>::FunctionWrapper::FunctionWrapper(T *object, Ret(T:: *func)(Args...)) :
        object(object), functionPtr(func),
        function([func, object](Args... args)->Ret
            {
                (object->*func)(args...);
            }), toRemove()
    { }

    template<typename Ret, typename... Args>
    Delegate<Ret, Args...>::FunctionWrapper::FunctionWrapper(Ret (*func)(Args...)) :
        object(nullptr), functionPtr(func), function(func), toRemove()
    { }

    template<typename Ret, typename... Args>
    Delegate<Ret, Args...>::FunctionWrapper::FunctionWrapper(std::function<Ret(Args...)> *func) :
        object(nullptr), functionPtr(func), function(*func), toRemove()
    {}

    template<typename Ret, typename... Args>
    Ret Delegate<Ret, Args...>::FunctionWrapper::operator()(Args ...args) const
    {
        if (!function)
            ThrowRuntimeException(__func__ + std::string(": missing functor target. Functions stored in Delegate must have a target"));
            function(args...);
    }

    template<typename Ret, typename... Args>
    template <typename T>
    bool Delegate<Ret, Args...>::FunctionWrapper::SignatureMatches(T *pObject, Ret (T:: *pFunctionPtr)(Args...)) const
    {
        return ((void *)pObject == object &&
            typeid(pFunctionPtr) == functionPtr.type() &&
            pFunctionPtr == std::any_cast<Ret(T:: *)(Args...)>(functionPtr));
    }

    template<typename Ret, typename... Args>
    bool Delegate<Ret, Args...>::FunctionWrapper::SignatureMatches(Ret(*pFunctionPtr)(Args...)) const
    {
        return (object == nullptr &&
            std::any_cast<Ret(*)(Args...)>(functionPtr) == pFunctionPtr);
    }

    template<typename Ret, typename... Args>
    bool Delegate<Ret, Args...>::FunctionWrapper::SignatureMatches(std::function<Ret(Args...)> *func) const
    {
        return object == nullptr &&
            std::any_cast<std::function<Ret(Args...)> *>(functionPtr) == func;
    }
}
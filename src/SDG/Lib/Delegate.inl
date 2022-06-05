#include "Delegate.h"

#include <SDG/Exceptions/InvalidArgumentException.h>

#include <algorithm>
#include <typeinfo>
#include <utility>

namespace SDG
{
    // ===== Delegate Implementation ==================================================================================
    template<typename... Args>
    void Delegate<Args...>::Clear()
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

    template<typename... Args>
    void Delegate<Args...>::Invoke(Args... args)
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

    template<typename... Args>
    void Delegate<Args...>::operator()(Args... args)
    {
        Invoke(std::forward<Args>(args)...);
    }

    template<typename... Args>
    template<typename T>
    void Delegate<Args...>::RemoveListener(T *object, void (T:: *func)(Args...))
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

    template<typename... Args>
    void Delegate<Args...>::RemoveListener(void (*func)(Args...))
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

    template<typename... Args>
    void Delegate<Args...>::RemoveListener(std::function<void(Args...)> *func)
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

    template<typename... Args>
    template<typename T>
    void Delegate<Args...>::AddListener(T *object, void (T:: *func)(Args...))
    {
        functions.emplace_back(std::move(FunctionWrapper(object, func)));
    }

    template<typename... Args>
    void Delegate<Args...>::AddListener(void (*func)(Args...))
    {
        functions.emplace_back(std::move(FunctionWrapper(func)));
    }

    template<typename... Args>
    void Delegate<Args...>::AddListener(std::function<void(Args...)> *func)
    {
        functions.emplace_back(std::move(FunctionWrapper(func)));
    }

    template<typename... Args>
    void Delegate<Args...>::ProcessRemovals()
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


    // ===== Delegate<Args...>::FunctionWrapper Implementation ========================================================

    template<typename... Args>
    template<typename T>
    Delegate<Args...>::FunctionWrapper::FunctionWrapper(T *object, void(T:: *func)(Args...)) :
        object(object), functionPtr(func),
        function([func, object](Args... args)->void
            {
                (object->*func)(args...);
            })
    { }

    template<typename... Args>
    Delegate<Args...>::FunctionWrapper::FunctionWrapper(void (*func)(Args...)) :
        object(nullptr), functionPtr(func), function(func)
    { }

    template<typename... Args>
    Delegate<Args...>::FunctionWrapper::FunctionWrapper(std::function<void(Args...)> *func) :
        object(nullptr), functionPtr(func), function(*func)
    {}

    template<typename... Args>
    void Delegate<Args...>::FunctionWrapper::operator()(Args ...args)
    {
        if (function)
            function(args...);
    }

    template<typename... Args>
    template <typename T>
    bool Delegate<Args...>::FunctionWrapper::SignatureMatches(T *pObject, void (T:: *pFunctionPtr)(Args...)) const
    {
        return ((void *)pObject == object &&
            typeid(pFunctionPtr) == functionPtr.type() &&
            pFunctionPtr == std::any_cast<void(T:: *)(Args...)>(functionPtr));
    }

    template<typename... Args>
    bool Delegate<Args...>::FunctionWrapper::SignatureMatches(void(*pFunctionPtr)(Args...)) const
    {
        return (object == nullptr &&
            std::any_cast<void(*)(Args...)>(functionPtr) == pFunctionPtr);
    }

    template<typename... Args>
    bool Delegate<Args...>::FunctionWrapper::SignatureMatches(std::function<void(Args...)> *func) const
    {
        return object == nullptr &&
            std::any_cast<std::function<void(Args...)> *>(functionPtr) == func;
    }
}
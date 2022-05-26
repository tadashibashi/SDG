//
// Created by aishi on 4/21/2022.
//
#pragma once

union SDL_Event;

namespace SDG
{
    /**
     * Abstract base class for Input devices
     */
    class InputComponent 
    {
    public:
        InputComponent() : wasInit(false) { }
        virtual ~InputComponent() {}

        bool Initialize();
        void ProcessInput(const SDL_Event &ev);
        void UpdateLastStates();
        void Close();

        bool WasInit() const;
    private:
        /// Initialization logic, should return true on successful
        /// initialization.
        virtual bool InitializeImpl() = 0;

        /// All events are guaranteed to only be related to
        /// the InputComponent
        virtual void ProcessInputImpl(const SDL_Event &ev) = 0;
        virtual void UpdateLastStatesImpl() = 0;
        virtual void CloseImpl() = 0;

        bool wasInit;
    };

    // ====== Inline Implementation ======

    inline bool
    InputComponent::Initialize()
    {
        return wasInit = InitializeImpl();
    }

    inline void
    InputComponent::ProcessInput(const SDL_Event &ev)
    {
        ProcessInputImpl(ev);
    }

    inline void
    InputComponent::UpdateLastStates()
    {
        UpdateLastStatesImpl();
    }

    inline void
    InputComponent::Close()
    {
        CloseImpl();
    }

    inline bool
    InputComponent::WasInit() const
    {
        return wasInit;
    }
}

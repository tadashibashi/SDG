/// @file InputComponent.h
/// @namespace SDG
/// @class InputComponent
/// Abstract base class for Input devices
///
#pragma once

union SDL_Event; // forward declaration

namespace SDG
{
    /// Abstract base class for Input devices
    class InputComponent 
    {
    public: // Constructor / Destructor =======================================

        InputComponent() : wasInit(false) { }
        virtual ~InputComponent() { }

    public: // Driver functions ===============================================

        /// Drive's this component's initialization
        bool Initialize();

        /// Drives component's input handling
        void ProcessInput(const SDL_Event &ev);
        
        /// Drives updates of state change variables
        void UpdateLastStates();

        /// Drives this component's clean up
        void Close();

        /// Checks if the InputComponent was initialized
        bool WasInit() const;

    private: // Virtual functions to implement ================================

        /// Initialization logic, should return true on successful
        /// initialization.
        virtual bool InitializeImpl() = 0;

        /// All events are guaranteed to only be related to
        /// the InputComponent
        virtual void ProcessInputImpl(const SDL_Event &ev) = 0;

        /// Use this function to set any "last" states to track state changes
        virtual void UpdateLastStatesImpl() = 0;

        /// Clean up any allocated memory here
        virtual void CloseImpl() = 0;

    private: // Private members ===============================================

        bool wasInit;
    };




    // ====== Inline Implementation ======

    inline bool
    InputComponent::Initialize()
    {
        return (wasInit = InitializeImpl());
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

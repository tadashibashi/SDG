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
    class InputComponent {
    public:
        InputComponent() : mWasInit(false) { }
        virtual ~InputComponent() {}

        bool Initialize();
        void ProcessInput(const SDL_Event &ev);
        void Update();
        void Close();

        bool WasInit() const;
    private:
        virtual bool InitializeImpl() = 0;
        virtual void ProcessInputImpl(const SDL_Event &ev) = 0;
        virtual void UpdateImpl() = 0;
        virtual void CloseImpl() = 0;

        bool mWasInit;
    };

    // ====== Inline Implementation ======

    inline bool
    InputComponent::Initialize()
    {
        return mWasInit = InitializeImpl();
    }

    inline void
    InputComponent::ProcessInput(const SDL_Event &ev)
    {
        ProcessInputImpl(ev);
    }

    inline void
    InputComponent::Update()
    {
        UpdateImpl();
    }

    inline void
    InputComponent::Close()
    {
        CloseImpl();
    }

    inline bool
    InputComponent::WasInit() const
    {
        return mWasInit;
    }
}

#pragma once
#include <Engine/Filesys/Path.h>
#include "AudioChannel.h"

#include <fmod_studio.hpp>
#include <initializer_list>

namespace SDG
{
    enum class Loop
    {
        Off,
        Normal,
        Bidirectional
    };

    class AudioEngine
    {
        struct Impl;
    public:
        AudioEngine();
        ~AudioEngine();

        auto Initialize() -> bool;
        auto Update() -> void;
        auto UnloadAllSounds() -> void;
        auto PreloadFiles(const std::initializer_list<Path> &paths) -> void;

        /// Plays a compressed stream
        auto PlayStream(const Path &filepath, Loop loop = Loop::Normal, bool spatial = false) -> AudioChannel;
        /// Plays an uncompressed sound
        auto PlaySound(const Path &filepath, Loop loop = Loop::Off, bool spatial = false) -> AudioChannel;

        auto UnloadSound(const Path &filepath) -> void;

        // ===== Getters =====
        
        [[nodiscard]] auto SampleRate() const -> int;
        [[nodiscard]] auto StudioSystem()->FMOD::Studio::System *;
        [[nodiscard]] auto CoreSystem()->FMOD::System *;
    private:
        Impl *impl;
    };
}

#pragma once
#include <fmod_studio.hpp>
#include <Engine/Math/Vector3.h>

namespace SDG
{
    class AudioChannel
    {
        struct Impl;
    public:
        AudioChannel();
        explicit AudioChannel(FMOD::Channel *fmodChannel);
        AudioChannel(const AudioChannel &other);
        AudioChannel &operator=(const AudioChannel &other);
        ~AudioChannel();

        auto IsPlaying() const -> bool;
        auto IsFading() const -> bool;
        
        auto FadeTo(float value, float seconds);

        auto Stop(float fadeTime = 0) -> AudioChannel &;
        auto Paused(bool paused, float fadeTime = 0) -> AudioChannel &;
        auto Paused() const -> bool;

        auto Volume() const -> float;
        auto Volume(float volume)->AudioChannel &;
        auto VolumeRamping() const -> bool;
        auto VolumeRamping(bool ramping)->AudioChannel &;

        auto Set3DAttributes(const Vector3 &position, const Vector3 &velocity) -> AudioChannel &;
        auto Get3DAttributes(Vector3 *position, Vector3 *velocity) -> void;

        auto Reverb(int instance) const -> float;
        auto Reverb(int instance, float level) -> AudioChannel &;

        /// Convenience function to get 3D position directly
        auto Position() const -> Vector3;
        auto Position(const Vector3 &position) -> AudioChannel &;

        /// Convenience function to get 3D velocity directly
        auto Velocity() const -> Vector3;
        auto Velocity(const Vector3 &velocity) -> AudioChannel &;

        /// Gets the underlying FMOD::Channel
        auto GetChannel() const->FMOD::Channel *;
    private:
        Impl *impl;
    };
}

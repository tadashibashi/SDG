#include "AudioChannel.h"
#include "Private/FMOD.h"

struct SDG::AudioChannel::Impl
{
    Impl() : channel{}, stopping{}, paused{} { }
    FMOD::Channel *channel;
    bool stopping, paused;

    FMOD::System *CoreSystem() const
    {
        FMOD::System *core;
        Check(channel->getSystemObject(&core));
        return core;
    }

    int SampleRate() const
    {
        int samplerate;
        Check(CoreSystem()->getDriverInfo(0, nullptr, 0, nullptr, &samplerate, nullptr, nullptr));
        return samplerate;
    }
};

SDG::AudioChannel::AudioChannel() : impl(new Impl)
{
    
}

SDG::AudioChannel::AudioChannel(FMOD::Channel *fmodChannel) : impl(new Impl)
{
    impl->channel = fmodChannel;
}

SDG::AudioChannel::AudioChannel(const AudioChannel &other) : impl(new Impl)
{
    impl->channel = other.impl->channel;
    impl->stopping = other.impl->stopping;
    impl->paused = other.impl->paused;
}
auto SDG::AudioChannel::operator=(const AudioChannel &other) -> SDG::AudioChannel &
{
    impl->channel = other.impl->channel;
    impl->stopping = other.impl->stopping;
    impl->paused = other.impl->paused;
    return *this;
}

SDG::AudioChannel::~AudioChannel()
{
    delete impl;
}

auto SDG::AudioChannel::IsPlaying() const -> bool
{
    bool isPlaying;
    auto result = impl->channel->isPlaying(&isPlaying);
    return result == FMOD_OK ? isPlaying : false;
}

auto SDG::AudioChannel::IsFading() const -> bool
{
    unsigned numPoints;
    unsigned long long *pointClock;
    float *values;
    Check(impl->channel->getFadePoints(&numPoints, nullptr, nullptr));
    pointClock = new unsigned long long[numPoints];
    values = new float[numPoints];
    Check(impl->channel->getFadePoints(&numPoints, pointClock, values));

    unsigned long long now;
    Check(impl->channel->getDSPClock(nullptr, &now));

    bool isFading = false;
    for (int i = 0, end = (int)numPoints - 1; i < end; ++i)
    {
        if (now >= pointClock[i] && now < pointClock[i + 1])
        {
            if (values[i] != values[i + 1])
            {
                isFading = true;
                break;
            }
        }
    }

    delete[] values;
    delete[] pointClock;

    return isFading;
}

auto SDG::AudioChannel::FadeTo(float volume, float seconds)
{
    unsigned long long now;
    Check(impl->channel->getDSPClock(nullptr, &now));
    Check(impl->channel->addFadePoint(now + 
        static_cast<unsigned long long>(impl->SampleRate() * (double)seconds), volume));
    return *this;
}

auto SDG::AudioChannel::Stop(float fadeTime) -> AudioChannel &
{
    if (impl->stopping)
        return *this;

    if (fadeTime > 0 && !impl->paused) // stop after fading out
    {
        unsigned long long now;
        Check(impl->channel->getDSPClock(nullptr, &now));

        unsigned long long end = now + impl->SampleRate() * (double)fadeTime;

        Check(impl->channel->setDelay(now, end, true));
        Check(impl->channel->addFadePoint(now, 1.f));
        Check(impl->channel->addFadePoint(end, 0));
    }
    else // stop immediately
    {
        Check(impl->channel->stop());
    }
    
    impl->stopping = true;
    return *this;
}

auto SDG::AudioChannel::Paused(bool paused, float fadeTime) -> AudioChannel &
{
    bool isPaused;
    Check(impl->channel->getPaused(&isPaused));
    if (paused && !impl->paused)      // pause
    {
        if (fadeTime > 0)  // fade-out pause
        {
            unsigned long long now;
            Check(impl->channel->getDSPClock(nullptr, &now));
            unsigned long long end = now + impl->SampleRate() * (double)fadeTime;
            Check(impl->channel->setDelay(now, end, false));
            Check(impl->channel->addFadePoint(now, 1.f));
            Check(impl->channel->addFadePoint(end, 0.f));
            SDG_Core_Log("Pausing fade-out");
        }
        else               // immediately pause
        {
            Check(impl->channel->setPaused(true));
        }
        impl->paused = true;
    }
    else if (!paused && impl->paused) // unpause
    {
        Check(impl->channel->setPaused(false));
        if (fadeTime > 0)  // fade-in from unpause
        {
            unsigned long long now;
            Check(impl->channel->getDSPClock(nullptr, &now));
            unsigned long long end = now + impl->SampleRate() * (double)fadeTime;
            Check(impl->channel->setDelay(now, 0, false));
            Check(impl->channel->addFadePoint(now, 0));
            Check(impl->channel->addFadePoint(end, 1.f));
            SDG_Core_Log("Unpausing fade-in");
        }
        impl->paused = false;
    }
    
    return *this;
}

auto SDG::AudioChannel::Paused() const -> bool
{
    return impl->paused;
}

auto SDG::AudioChannel::GetChannel() const -> FMOD::Channel *
{
    return impl->channel;
}

auto SDG::AudioChannel::Volume() const -> float
{
    float volume;
    Check(impl->channel->getVolume(&volume));
    return volume;
}

auto SDG::AudioChannel::Volume(float volume) -> AudioChannel &
{
    Check(impl->channel->setVolume(volume));
    return *this;
}

auto SDG::AudioChannel::VolumeRamping() const -> bool
{
    bool ramping;
    Check(impl->channel->getVolumeRamp(&ramping));
    return ramping;
}

auto SDG::AudioChannel::VolumeRamping(bool ramping) -> AudioChannel &
{
    Check(impl->channel->setVolumeRamp(ramping));
    return *this;
}

auto 
SDG::AudioChannel::Set3DAttributes(const Vector3 &position, const Vector3 &velocity)->AudioChannel &
{
    FMOD_VECTOR fPosition{ position.X(), position.Y(), position.Z() };
    FMOD_VECTOR fVelocity{ velocity.X(), velocity.Y(), velocity.Z() };
    Check(impl->channel->set3DAttributes(&fPosition, &fVelocity));

    return *this;
}

auto SDG::AudioChannel::Get3DAttributes(Vector3 *position, Vector3 *velocity) -> void
{
    FMOD_VECTOR p, v;
    Check(impl->channel->get3DAttributes(&p, &v));
    if (position)
        *position = { p.x, p.y, p.z };
    if (velocity)
        *velocity = { v.x, v.y, v.z };
}

auto SDG::AudioChannel::Reverb(int instance) const -> float
{
    float reverb;
    Check(impl->channel->getReverbProperties(instance, &reverb));
    return reverb;
}

auto SDG::AudioChannel::Reverb(int instance, float level) -> AudioChannel &
{
    Check(impl->channel->setReverbProperties(instance, level));
    return *this;
}

auto 
SDG::AudioChannel::Position() const -> Vector3
{
    FMOD_VECTOR position;
    Check(impl->channel->get3DAttributes(&position, nullptr));
    return { position.x, position.y, position.z };
}

auto 
SDG::AudioChannel::Position(const Vector3 &position) -> AudioChannel &
{
    FMOD_VECTOR p {position.X(), position.Y(), position.Z() };
    Check(impl->channel->set3DAttributes(&p, nullptr));
    return *this;
}

auto 
SDG::AudioChannel::Velocity() const -> Vector3
{
    FMOD_VECTOR velocity;
    Check(impl->channel->get3DAttributes(nullptr, &velocity));
    return { velocity.x, velocity.y, velocity.z };
}

auto
SDG::AudioChannel::Velocity(const Vector3 &velocity) -> AudioChannel &
{
    FMOD_VECTOR v{ velocity.X(), velocity.Y(), velocity.Z() };
    Check(impl->channel->set3DAttributes(nullptr, &v));
    return *this;
}

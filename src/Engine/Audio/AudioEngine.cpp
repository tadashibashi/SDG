#include "AudioEngine.h"
#include "Private/FMOD.h"
#include <Engine/Debug/Log.h>
#include <Engine/Filesys/File.h>
#include <map>
#include <Engine/Debug/Assert.h>
#include <Engine/Exceptions/InvalidArgumentException.h>
#include <Engine/Platform.h>

struct SDG::AudioEngine::Impl
{
    Impl() : system(), core() { }
    ~Impl()
    {
        if (system->isValid())
        {
            system->release();
        }
    }

    FMOD::Sound *LoadSound(const Path &filepath, FMOD_MODE mode);
    FMOD::Studio::System *system;
    FMOD::System *core;
    std::map<String, std::pair<File, FMOD::Sound *>> files;
};


SDG::AudioEngine::AudioEngine() : impl{ new Impl }
{
    FMOD::Studio::System *system;
    FMOD::System *core;

    Check(FMOD::Studio::System::create(&system), "creating FMOD Studio System");
    Check(system->getCoreSystem(&core), "getting core system");

    impl->system = system;
    impl->core = core;
}

SDG::AudioEngine::~AudioEngine()
{
    UnloadAllSounds();
    delete impl;
}

auto 
SDG::AudioEngine::Initialize() -> bool
{
    int systemRate;
    Check(impl->core->getDriverInfo(0, nullptr, 0, nullptr, &systemRate, nullptr, nullptr));
    Check(impl->core->setSoftwareFormat(systemRate, FMOD_SPEAKERMODE_DEFAULT, 0));
    
#if (SDG_TARGET_WEBGL) || (SDG_TARGET_MOBILE)
    Check(impl->core->setDSPBufferSize(2048, 2));
#endif
    Check(impl->system->initialize(512, 
        FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr),
        "initializing FMOD Studio System");
   
    return impl->system->isValid();
}

auto SDG::AudioEngine::Update() -> void
{
    SDG_Assert(impl->system->isValid());
    impl->system->update();
}

auto SDG::AudioEngine::UnloadSound(const Path &filepath) -> void
{
    auto it = impl->files.find(filepath.Str());
    if (it != impl->files.end())
    {
        it->second.second->release();
        impl->files.erase(it);
    }
}

auto SDG::AudioEngine::UnloadAllSounds() -> void
{
    for (auto &[path, pair] : impl->files)
        pair.second->release();
    impl->files.clear();
}

auto SDG::AudioEngine::PreloadFiles(const std::initializer_list<Path> &paths) -> void
{
    for (const auto &path : paths)
    {
        auto &file = impl->files[path.Str()].first;
        if (!file.IsOpen())
            if(!file.Open(path))
                SDG_Core_Err("Failed to load file: \"{}\"", path);
    }
}

auto SDG::AudioEngine::Impl::LoadSound(const Path &filepath, FMOD_MODE mode) -> FMOD::Sound *
{
    auto &pair = files[filepath.Str()];
    File &file = pair.first;
    if (file.IsOpen())
        return pair.second;
    else
        file.Open(filepath);

    if (!file.IsOpen())
    {
        SDG_Core_Err("Failed to open file at {}", filepath);
        return nullptr;
    }

    FMOD::Sound *sound;
    mode |= FMOD_OPENMEMORY_POINT;
    auto info = FMOD_CREATESOUNDEXINFO{};
    info.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    info.length = file.Size();

    Check(core->createSound((const char *)file.Data(), mode, &info, &sound),
        "creating streamable sound");

    pair.second = sound;
    return sound;
}

static uint32_t LoopToMode(SDG::Loop loop)
{
    switch (loop)
    {
    case SDG::Loop::Off: return FMOD_LOOP_OFF;
    case SDG::Loop::Normal: return FMOD_LOOP_NORMAL;
    case SDG::Loop::Bidirectional: return FMOD_LOOP_BIDI;
    default:
        throw SDG::InvalidArgumentException(__func__, 
            SDG::String::Format("Loop value {} was invalid.", (uint32_t)loop));
    }
}

auto SDG::AudioEngine::PlaySound(const Path &filepath, Loop loop, bool spatial) -> AudioChannel
{
    FMOD_MODE mode = LoopToMode(loop);
    if (spatial)
        mode |= FMOD_3D;

    FMOD::Sound *sound = impl->LoadSound(filepath, mode);
    if (!sound)
    {
        SDG_Core_Err("Failed to load sound ({})", filepath);
        return AudioChannel { nullptr };
    }

    FMOD::Channel *channel;
    Check(impl->core->playSound(sound, nullptr, false, &channel));
    
    return AudioChannel{ channel };
}

auto SDG::AudioEngine::PlayStream(const Path &filepath, Loop loop, bool spatial) -> AudioChannel
{
    FMOD_MODE mode = LoopToMode(loop) | FMOD_CREATECOMPRESSEDSAMPLE;
    if (spatial)
        mode |= FMOD_3D;

    FMOD::Sound *sound = impl->LoadSound(filepath, mode);
    if (!sound)
    {
        SDG_Core_Err("Failed to load audio stream ({})", filepath);
        return AudioChannel{ nullptr };
    }
    
    FMOD::Channel *channel;
    Check(impl->core->playSound(sound, nullptr, false, &channel));

    return AudioChannel{ channel };
}

auto SDG::AudioEngine::SampleRate() const -> int
{
    int samplerate;
    Check(impl->core->getSoftwareFormat(&samplerate, nullptr, nullptr), 
        "getting core software format");
    return samplerate;
}

auto SDG::AudioEngine::StudioSystem() -> FMOD::Studio::System *
{
    return impl->system;
}

auto SDG::AudioEngine::CoreSystem() -> FMOD::System *
{
    return impl->core;
}

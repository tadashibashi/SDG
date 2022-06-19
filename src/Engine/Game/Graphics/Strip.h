#pragma once
#include <Engine/Lib/String.h>
#include <Engine/Filesys/Path.h>
#include <Engine/Game/Graphics/Frame.h>
#include <vector>

namespace SDG
{
    class Strip
    {
    public:
        Strip();
        Strip(Ref<class Texture> texture, size_t frameCount, Vector2 anchor = { 0.5f, 0.5f });
        auto Init(Ref<class Texture> texture, size_t frameCount, Vector2 anchor = { 0.5f, 0.5f }) -> bool;

        [[nodiscard]] auto operator[] (size_t index) const -> const Frame & { return frames[index]; }
        [[nodiscard]] auto Texture() const -> Ref<class Texture> { return texture; }
    private:
        std::vector<Frame> frames;
        Ref<class Texture> texture;
    };
}

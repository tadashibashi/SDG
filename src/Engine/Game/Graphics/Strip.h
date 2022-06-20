#pragma once
#include <Engine/Lib/String.h>
#include <Engine/Game/Graphics/Frame.h>
#include <vector>
//
//namespace SDG
//{
//    class Strip
//    {
//    public:
//        Strip();
//        Strip(Ref<Frame> source, size_t frameCount, Vector2 anchor = { 0.5f, 0.5f });
//        auto Init(Ref<Frame> source, size_t frameCount, Vector2 anchor = { 0.5f, 0.5f }) -> bool;
//
//        [[nodiscard]] auto operator[] (size_t index) const -> Rectangle { return frames[index]; }
//
//        [[nodiscard]] auto SourceFrame() const { return source; }
//
//        [[nodiscard]] auto FrameWidth() const { return source->ImageRect().Width() / frameCount; }
//        [[nodiscard]] auto FrameHeight() const -> int { source->ImageRect().Height(); }
//    private:
//        int frameCount;
//        Ref<Frame> source;
//    };
//}

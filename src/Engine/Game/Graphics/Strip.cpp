#include "Strip.h"

//SDG::Strip::Strip() : frames(), source() { }
//
//SDG::Strip::Strip(Ref<Frame> source, size_t frameCount, Vector2 anchor)
//{
//    Init(source, frameCount, anchor);
//}
//
//auto SDG::Strip::Init(Ref<Frame> source, size_t frameCount, Vector2 anchor) -> bool
//{
//    if (frameCount == 0 || source.Get() == nullptr) return false;
//
//    Point size = source->ImageRect().Size() / Vector2{(float)frameCount, 1};
//    std::vector<Frame> frames;
//    for (size_t i = 0; i < frameCount; ++i)
//    {
//        Rectangle frame{ (int)i * size.X(), 0, size.X(), size.Y() };
//        frames.emplace_back(frame, frame, false, (Point)(size * anchor), source.Get());
//    }
//    
//    this->frames.swap(frames);
//    this->source = source;
//
//    return true;
//}

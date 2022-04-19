//
// Created by Aaron Ishibashi on 4/15/22.
//

#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

namespace SDG
{
    class Scene {
    public:
        void Initialize();
        void Update();
        void Render();
        void Close();

        void OnPause();
        void OnResume();
    };
}


#endif //ENGINE_SCENE_H

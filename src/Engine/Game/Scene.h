#pragma once

namespace SDG
{
    class Scene 
    {
    public:
        void Initialize();
        void Update();
        void Render();
        void Close();

        void OnPause();
        void OnResume();
    };
}


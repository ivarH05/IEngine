#pragma once
#include <memory>

namespace IEngine
{
    namespace Core
    {
        class Scene;

        class Object
        {
        private:
            bool _isDestroyed = false;

            /// <summary>
            /// Destroy the object, block other objects from referencing it
            /// </summary>
            virtual void Destroy();

            /// <summary>
            /// The root scene of the object
            /// </summary>
            std::shared_ptr<Scene> scene = nullptr;

        public:
            Object* operator->();

            /// <summary>
            /// Destroy after the frame. 
            /// </summary>
            /// <param name="other"></param>
            void Destroy(std::shared_ptr<Object>);

            // Friend the Scene class to allow it to call Destroy()
            friend class Scene;
        };
    }
}


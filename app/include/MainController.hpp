#ifndef MYCONTROLLER_HPP
#define MYCONTROLLER_HPP

#include <engine/core/Controller.hpp>
#include <engine/resources/Shader.hpp>

namespace app {
    class MainController : public engine::core::Controller{

        private:
            bool spotLightEnabled = true;
            bool lastLKeyState = false;

        void initialize() override;
        bool loop() override;
        void begin_draw() override;
        void lighting(engine::resources::Shader *shader);
        void draw_wheel();
        void draw_carousel();
        void draw_ground();
        void draw_skybox();
        void draw() override;
        void end_draw() override;
    };
}

#endif
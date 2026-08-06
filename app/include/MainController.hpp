#ifndef MYCONTROLLER_HPP
#define MYCONTROLLER_HPP

#include <engine/core/Controller.hpp>

namespace app {
    class MainController : public engine::core::Controller{
        void initialize() override;
        bool loop() override;
        void begin_draw() override;
        void draw_wheel();
        void draw_skybox();
        void draw() override;
        void end_draw() override;
    };
}

#endif
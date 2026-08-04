#ifndef MYCONTROLLER_HPP
#define MYCONTROLLER_HPP

#include <engine/core/Controller.hpp>

namespace app {
    class MainController : public engine::core::Controller{
        void initialize() override;
        bool loop() override;
        void draw() override;
    };
}

#endif
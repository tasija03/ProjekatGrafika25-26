#include <MainController.hpp>
#include <engine/core/Controller.hpp>
#include <engine/platform/PlatformController.hpp>
#include <engine/resources/ResourcesController.hpp>
#include <engine/graphics/OpenGL.hpp>

namespace app {
    void MainController::initialize() {
        // Initialize your controller here
    }

    bool MainController::loop() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        if(platform->key(engine::platform::KeyId::KEY_ESCAPE).is_down()){
            return false;
        }

        return true;
    }

    void MainController::draw_wheel(){
        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        engine::resources::Model *model = resources->model("wheel");
        engine::resources::Shader *shader = resources->shader("shader");

        model->draw(shader);
    }

    void MainController::begin_draw() {
        engine::graphics::OpenGL::clear_buffers();
    }

    void MainController::end_draw() {
    }

    void MainController::draw() {
        draw_wheel();
    }
}
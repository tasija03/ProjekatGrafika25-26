#include "engine/graphics/GraphicsController.hpp"


#include <engine/core/Engine.hpp>
#include <spdlog/spdlog.h>

class WheelController : public engine::core::Controller {
private:
    engine::resources::Model* m_wheel = nullptr;
    engine::resources::Shader* m_shader = nullptr;

protected:
    void initialize() override {
        engine::graphics::OpenGL::enable_depth_testing();

        auto res = engine::core::Controller::get<engine::resources::ResourcesController>();

        m_wheel = res->model("wheel");
        m_shader = res->shader("shader");

    }

    void draw() override {
        if (!m_wheel|| !m_shader) {
            spdlog::error("NULL dragon or shader!");
            return;
        }

        auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>();
        camera->camera()->Position = glm::vec3(0.0f, 0.0f, 3.0f);

        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();

        m_shader->use();
        

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
        model = glm::scale(model, glm::vec3(0.01f));

        m_shader->set_mat4("model", model);
        m_shader->set_mat4("view", graphics->camera()->view_matrix());
        m_shader->set_mat4("projection", graphics->projection_matrix());

        m_wheel->draw(m_shader);

    }

};

class MyApp : public engine::core::App {
protected:
    void app_setup() override {
        auto wheel_controller = register_controller<WheelController>();
        wheel_controller->after(engine::core::Controller::get<engine::core::EngineControllersEnd>());
    }
};

int main(int argc, char **argv) {
    MyApp app;
    return app.run(argc, argv);
}
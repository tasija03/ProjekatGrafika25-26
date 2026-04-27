#include <engine/core/Engine.hpp>
#include <spdlog/spdlog.h>

class DragonController : public engine::core::Controller {
private:
    engine::resources::Model* my_dragon = nullptr;
    engine::resources::Shader* m_shader = nullptr;

protected:
    void initialize() override {
        auto res = engine::core::Controller::get<engine::resources::ResourcesController>();

        my_dragon = res->model("dragon");
        m_shader = res->shader("shader");
    }

    void draw() override {
        if (!my_dragon || !m_shader) {
            spdlog::error("NULL dragon or shader!");
            return;
        }

        my_dragon->draw(m_shader);
    }
};

class MyApp : public engine::core::App {
protected:
    void app_setup() override {
        register_controller<DragonController>();
    }
};

int main(int argc, char **argv) {
    MyApp app;
    return app.run(argc, argv);
}
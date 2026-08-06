#include <MainController.hpp>
#include <engine/core/Controller.hpp>
#include <engine/platform/PlatformController.hpp>
#include <engine/resources/ResourcesController.hpp>
#include <engine/graphics/OpenGL.hpp>
#include <engine/graphics/GraphicsController.hpp>


namespace app {
    void MainController::initialize() {
        engine::graphics::OpenGL::enable_depth_testing();
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
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        engine::resources::Model *wheel = resources->model("wheel");
        engine::resources::Model *stalak = resources->model("stalak");
        engine::resources::Model *carousel = resources->model("carousel");
        engine::resources::Shader *shader = resources->shader("shader");

        shader->use();

        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());
       
        /*stalak od pan. tocka*/
        glm::mat4 stalak_model = glm::mat4(1.0f);

        stalak_model = glm::translate(stalak_model, glm::vec3(-0.6f, -0.8f, -3.0f));
        stalak_model = glm::scale(stalak_model, glm::vec3(0.00005f));
        shader->set_mat4("model", stalak_model);
        stalak->draw(shader);

        /*tocak*/
        glm::mat4 model = glm::mat4(1.0f);

        auto curr_time = platform->frame_time().current;
        auto speed = 1.0f;

        model = glm::translate(model, glm::vec3(-0.6f, -0.8f, -3.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.62f, 0.0f));
        model = glm::rotate(model, speed*curr_time, glm::normalize(glm::vec3(1.0f, 0.0f, 1.0f)));
        model = glm::translate(model, glm::vec3(0.0f, -0.62f, 0.0f));
        model = glm::scale(model, glm::vec3(0.00005f));

        shader->set_mat4("model", model);

        wheel->draw(shader);

        /*karusel*/
        glm::mat4 carousel_model = glm::mat4(1.0f);
        carousel_model = glm::translate(carousel_model, glm::vec3(0.6f, -0.8f, -3.0f));
        carousel_model = glm::rotate(carousel_model, curr_time*speed, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
        carousel_model = glm::scale(carousel_model, glm::vec3(0.018f));
        shader->set_mat4("model", carousel_model);
        carousel->draw(shader);
    }

    void MainController::draw_skybox(){

        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        engine::resources::Skybox *skybox = resources->skybox("lunapark");
        engine::resources::Shader *shader = resources->shader("skybox_shader");
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        graphics->draw_skybox(shader, skybox);

    }

    void MainController::begin_draw() {
        engine::graphics::OpenGL::clear_buffers();

    }

    void MainController::draw() {
        draw_wheel();
        draw_skybox();
    }


    void MainController::end_draw() {
        auto pltform = engine::core::Controller::get<engine::platform::PlatformController>();
        pltform->swap_buffers();
    }
}
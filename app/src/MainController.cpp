#include <MainController.hpp>
#include <engine/core/Controller.hpp>
#include <engine/platform/PlatformController.hpp>
#include <engine/resources/ResourcesController.hpp>
#include <engine/graphics/OpenGL.hpp>
#include <engine/graphics/GraphicsController.hpp>
#include <engine/resources/Mesh.hpp>
#include <engine/resources/Texture.hpp>


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

    void MainController::poll_events(){

        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        
        auto isLKeyPressed = platform->key(engine::platform::KeyId::KEY_L).state();
        if (isLKeyPressed == engine::platform::Key::State::JustPressed) {
            spotLightEnabled = !spotLightEnabled;
        }
    }

    void MainController::lighting(engine::resources::Shader *shader){

        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();

        shader->set_vec3("viewPos", graphics->camera()->Position);

        
        shader->set_float("material.shininess", 128.0f);
        shader->set_vec3("material.specular", glm::vec3(1.5f));

        shader->set_vec3("dirLight.direction", glm::vec3(1.0f, -1.0f, 1.0f));
        shader->set_vec3("dirLight.ambient", glm::vec3(0.4f));
        shader->set_vec3("dirLight.diffuse", glm::vec3(0.9f));
        shader->set_vec3("dirLight.specular", glm::vec3(1.5f)); 

        shader->set_vec3("spotLight.position", glm::vec3(0.0f, 8.0f, -10.0f));
        shader->set_vec3("spotLight.direction", glm::vec3(0.0f, -1.0f, 0.0f));
        shader->set_float("spotLight.cutOff", glm::cos(glm::radians(12.0f)));
        shader->set_float("spotLight.outerCutOff", glm::cos(glm::radians(22.0f)));
        shader->set_float("spotLight.constant", 1.0f);
        shader->set_float("spotLight.linear", 0.045f);
        shader->set_float("spotLight.quadratic", 0.0075f);

        if (spotLightEnabled) {
            shader->set_vec3("spotLight.ambient", glm::vec3(0.0f));
            shader->set_vec3("spotLight.diffuse", glm::vec3(1.0f));
            shader->set_vec3("spotLight.specular", glm::vec3(1.0f));
        } else {
            shader->set_vec3("spotLight.ambient", glm::vec3(0.0f));
            shader->set_vec3("spotLight.diffuse", glm::vec3(0.0f));  
            shader->set_vec3("spotLight.specular", glm::vec3(0.0f)); 
        }
    }

    void MainController::draw_ground(){
        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();

        engine::resources::Model *stage = resources->model("stage");
        engine::resources::Shader *shader = resources->shader("shader_ground");

        shader->use();
        lighting(shader);
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());
        glm::mat4 stage_model = glm::mat4(1.0f);
        stage_model = glm::translate(stage_model, glm::vec3(0.0f, 2.0f, -10.0f));
        stage_model = glm::rotate(stage_model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        stage_model = glm::scale(stage_model, glm::vec3(1.0f));
        shader->set_mat4("model", stage_model);
        stage->draw(shader);


    }

    void MainController::draw_wheel(){


        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        engine::resources::Model *wheel = resources->model("wheel");
        engine::resources::Model *stalak = resources->model("stalak");
        engine::resources::Shader *shader = resources->shader("shader");

        shader->use();
        
        lighting(shader);

        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());

        /*stalak od pan. tocka*/
        glm::mat4 stalak_model = glm::mat4(1.0f);

        stalak_model = glm::translate(stalak_model, glm::vec3(-0.6f, -0.8f, -4.0f));
        stalak_model = glm::scale(stalak_model, glm::vec3(0.00005f));
        shader->set_mat4("model", stalak_model);
        stalak->draw(shader);

        /*tocak*/
        glm::mat4 model = glm::mat4(1.0f);

        auto curr_time = platform->frame_time().current;
        auto speed = 1.0f;

        model = glm::translate(model, glm::vec3(-0.6f, -0.8f, -4.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.62f, 0.0f));
        model = glm::rotate(model, speed*curr_time, glm::normalize(glm::vec3(1.0f, 0.0f, 1.0f)));
        model = glm::translate(model, glm::vec3(0.0f, -0.62f, 0.0f));
        model = glm::scale(model, glm::vec3(0.00005f));

        shader->set_mat4("model", model);

        wheel->draw(shader);

    }

    void MainController::draw_carousel(){
        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();


        engine::resources::Model *carousel = resources->model("carousel");
        engine::resources::Shader *shader = resources->shader("shader");

        auto curr_time = platform->frame_time().current;
        auto speed = 1.0f;

        shader->use();
        lighting(shader);
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());

        glm::mat4 carousel_model = glm::mat4(1.0f);
        carousel_model = glm::translate(carousel_model, glm::vec3(0.6f, -0.8f, -4.0f));
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
        draw_carousel();
        draw_ground();
        draw_skybox();
    }


    void MainController::end_draw() {
        auto pltform = engine::core::Controller::get<engine::platform::PlatformController>();
        pltform->swap_buffers();
    }
}
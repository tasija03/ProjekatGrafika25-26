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
        m_curr_time = platform->frame_time().current;
        
        if(platform->key(engine::platform::KeyId::KEY_ESCAPE).is_down()){
            return false;
        }

        return true;
    }

    void MainController::poll_events(){

        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        
        auto is_L_pressed = platform->key(engine::platform::KeyId::KEY_L).state();
        if (is_L_pressed == engine::platform::Key::State::JustPressed) {
            spot_light_enabled = !spot_light_enabled;
        }

        auto is_Space_pressed = platform->key(engine::platform::KeyId::KEY_SPACE).state();
        if (is_Space_pressed == engine::platform::Key::State::JustPressed){
            m_event_active = !m_event_active;
            if (m_event_active == true) {
                m_event_timer = 0.0f;
            }
        }
    }

    void MainController::update(){

        float dt = engine::core::Controller::get<engine::platform::PlatformController>()->dt();

        update_camera(dt);

        if(m_event_active){
            m_event_timer += dt;
            if(m_event_timer >= 3.0f){
                m_angle = glm::vec3(-1.0f, 0.0f, -1.0f);
            }
        }
        else{
            m_angle = glm::vec3(1.0f, 0.0f, 1.0f);
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

        if (spot_light_enabled) {
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

        model = glm::translate(model, glm::vec3(-0.6f, -0.8f, -4.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.62f, 0.0f));
        model = glm::rotate(model, m_curr_time * m_speed, glm::normalize(m_angle));
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


        shader->use();
        lighting(shader);
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());

        glm::mat4 carousel_model = glm::mat4(1.0f);
        carousel_model = glm::translate(carousel_model, glm::vec3(0.6f, -0.8f, -4.0f));
        carousel_model = glm::rotate(carousel_model, m_curr_time*m_speed, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
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

    void MainController::update_camera(float dt){

        auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();

        if(m_event_active){
            dt = m_event_timer/3.0f;
            if(dt > 1.0f){
                dt = 1.0f;
            }
            camera->Position = glm::mix(position, glm::vec3(0.4f, -0.8f, -4.0f), dt);
            camera->Front = glm::mix(front, glm::vec3(-1.0f, 0.5f, 0.0f), dt);
        }
        else{
            camera->Position = position;
            camera->Front = front;
        }
    }
}
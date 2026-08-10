#ifndef MYCONTROLLER_HPP
#define MYCONTROLLER_HPP

#include <engine/core/Controller.hpp>
#include <engine/resources/Shader.hpp>
#include <engine/graphics/GraphicsController.hpp>

namespace app {
    class MainController : public engine::core::Controller{

        private:
            bool spot_light_enabled = true;
            bool m_event_active = false;
            float m_event_timer = 0.0f;
            float m_curr_time = 0.0f;
            float m_speed = 1.0f;
            glm::vec3 m_angle = glm::vec3(1.0f, 0.0f, 1.0f);
            glm::vec3 position = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera()->Position;
            glm::vec3 front = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera()->Front;
            
        void initialize() override;
        bool loop() override;
        void poll_events() override;
        void update() override;
        void begin_draw() override;
        void lighting(engine::resources::Shader *shader);
        void draw_wheel();
        void draw_carousel();
        void draw_ground();
        void draw_skybox();
        void draw() override;
        void end_draw() override;
        void update_camera(float dt);
    };
}

#endif
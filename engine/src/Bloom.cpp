#include <glad/glad.h>

#include <engine/graphics/Bloom.hpp>
#include <engine/graphics/OpenGL.hpp>
#include <engine/resources/Shader.hpp>

namespace engine::graphics {

void Bloom::initialize(int width, int height) {
    m_width = width;
    m_height = height;

    init_hdr_fbo();
    init_pingpong_fbo();
    init_screen_quad();

    m_initialized = true;
}


}
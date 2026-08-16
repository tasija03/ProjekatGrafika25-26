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

void Bloom::init_hdr_fbo() {
    CHECKED_GL_CALL(glGenFramebuffers, 1, &m_hdr_fbo);
    CHECKED_GL_CALL(glBindFramebuffer, GL_FRAMEBUFFER, m_hdr_fbo);

    CHECKED_GL_CALL(glGenTextures, 2, m_color_buffers);
    for (unsigned int i = 0; i < 2; i++) {
        CHECKED_GL_CALL(glBindTexture, GL_TEXTURE_2D, m_color_buffers[i]);
        CHECKED_GL_CALL(glTexImage2D, GL_TEXTURE_2D, 0, GL_RGBA16F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, nullptr);
        CHECKED_GL_CALL(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        CHECKED_GL_CALL(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        CHECKED_GL_CALL(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        CHECKED_GL_CALL(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        CHECKED_GL_CALL(glFramebufferTexture2D, GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_color_buffers[i], 0);
    }

    CHECKED_GL_CALL(glGenRenderbuffers, 1, &m_depth_rbo);
    CHECKED_GL_CALL(glBindRenderbuffer, GL_RENDERBUFFER, m_depth_rbo);
    CHECKED_GL_CALL(glRenderbufferStorage, GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_width, m_height);
    CHECKED_GL_CALL(glFramebufferRenderbuffer, GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_rbo);

    unsigned int attachments[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    CHECKED_GL_CALL(glDrawBuffers, 2, attachments);

    CHECKED_GL_CALL(glBindFramebuffer, GL_FRAMEBUFFER, 0);
}


}
#include <glad/glad.h>

#include <engine/graphics/Bloom.hpp>
#include <engine/graphics/OpenGL.hpp>

namespace engine::graphics {

void Bloom::initialize(int width, int height) {
    m_width = width;
    m_height = height;
}

void Bloom::resize(int width, int height) {
    m_width = width;
    m_height = height;
}

void Bloom::begin() {
}

void Bloom::end() {
}

}
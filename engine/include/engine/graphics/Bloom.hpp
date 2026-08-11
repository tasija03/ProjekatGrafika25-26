#ifndef BLOOM_HPP
#define BLOOM_HPP

#include <cstdint>

namespace engine::graphics {

class Bloom {
public:
    void initialize(int width, int height);
    void resize(int width, int height);

    void begin();
    void end();

private:
    uint32_t m_hdr_fbo = 0;
    uint32_t m_color_buffers[2] = {0, 0};
    uint32_t m_depth_rbo = 0;

    uint32_t m_pingpong_fbo[2] = {0, 0};
    uint32_t m_pingpong_colorbuffers[2] = {0, 0};

    int m_width = 0;
    int m_height = 0;
};

}

#endif
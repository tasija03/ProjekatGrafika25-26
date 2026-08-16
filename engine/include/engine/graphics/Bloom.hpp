#ifndef BLOOM_HPP
#define BLOOM_HPP

#include <cstdint>

namespace engine::resources {
class Shader;
}

namespace engine::graphics {

class Bloom {
public:
    void initialize(int width, int height);
    void resize(int width, int height);

    void begin();
    void end();


    void destroy();

private:
    void init_hdr_fbo();
    void init_pingpong_fbo();
    void init_screen_quad();

    int m_width = 0;
    int m_height = 0;
    bool m_initialized = false;
};

}

#endif
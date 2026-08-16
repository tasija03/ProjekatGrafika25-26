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

};

}

#endif
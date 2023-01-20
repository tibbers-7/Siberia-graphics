#include "holebuffer.hpp"

std::vector<float> HoleBuffer::mVertices = {
    //      POS        |     COLOURS   
        // X    Y      Z       R    G     B
        -0.5f, -0.5f, -0.5f, 0.1f, 0.5f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.1f, 0.5f, 1.0f,
        0.5f, 0.5f, -0.5f,   0.1f, 0.5f, 1.0f,
        0.5f, 0.5f, -0.5f,   0.1f, 0.5f, 1.0f,
        -0.5f, 0.5f, -0.5f,  0.1f, 0.5f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.1f, 0.5f, 1.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,

        0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f,0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f,0.0f, 0.0f, 1.0f
};

HoleBuffer::HoleBuffer() {}

float*
HoleBuffer::GetVertices() {
    return mVertices.data();
}

unsigned
HoleBuffer::GetVertexCount() {
    return mVertices.size();
}

unsigned
HoleBuffer::GetVertexElementCount() {
    return 6;
}
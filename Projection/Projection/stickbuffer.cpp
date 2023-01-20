#include "stickbuffer.hpp"

std::vector<float> StickBuffer::mVertices = {
    //      POS        |     COLOURS   
        // X    Y      Z       R    G     B
        -0.5f, -0.5f, -0.5f, 0.7f, 0.45f, 0.05f,
        0.5f, -0.5f, -0.5f,  0.7f, 0.45f, 0.05f,
        0.5f, 0.5f, -0.5f,   0.7f, 0.435f, 0.05f,
        0.5f, 0.5f, -0.5f,   0.7f, 0.45f, 0.05f,
        -0.5f, 0.5f, -0.5f,  0.7f, 0.45f, 0.05f,
        -0.5f, -0.5f, -0.5f, 0.7f, 0.45f, 0.05f,

        -0.5f, -0.5f, 0.5f, 0.7f, 0.45f, 0.05f,
        0.5f, -0.5f, 0.5f,  0.7f, 0.45f, 0.05f,
        0.5f, 0.5f, 0.5f,   0.7f, 0.45f, 0.05f,
        0.5f, 0.5f, 0.5f,   0.7f, 0.45f, 0.05f,
        -0.5f, 0.5f, 0.5f,  0.7f, 0.45f, 0.05f,
        -0.5f, -0.5f, 0.5f, 0.7f, 0.45f, 0.05f,

        -0.5f, 0.5f, 0.5f,  0.7f, 0.45f, 0.05f,
        -0.5f, 0.5f, -0.5f, 0.7f, 0.45f, 0.05f,
        -0.5f, -0.5f, -0.5f,0.7f, 0.45f, 0.05f,
        -0.5f, -0.5f, -0.5f,0.7f, 0.45f, 0.05f,
        -0.5f, -0.5f, 0.5f, 0.7f, 0.45f, 0.05f,
        -0.5f, 0.5f, 0.5f,  0.7f, 0.45f, 0.05f,

        0.5f, 0.5f, 0.5f,  0.7f, 0.45f, 0.05f,
        0.5f, 0.5f, -0.5f, 0.7f, 0.45f, 0.05f,
        0.5f, -0.5f, -0.5f,0.7f, 0.45f, 0.05f,
        0.5f, -0.5f, -0.5f,0.7f, 0.45f, 0.05f,
        0.5f, -0.5f, 0.5f, 0.7f, 0.45f, 0.05f,
        0.5f, 0.5f, 0.5f,  0.7f, 0.45f, 0.05f,

        -0.5f, -0.5f, -0.5f,0.7f, 0.45f, 0.05f,
        0.5f, -0.5f, -0.5f, 0.7f, 0.45f, 0.05f,
        0.5f, -0.5f, 0.5f,  0.7f, 0.45f, 0.05f,
        0.5f, -0.5f, 0.5f,  0.7f, 0.45f, 0.05f,
        -0.5f, -0.5f, 0.5f, 0.7f, 0.45f, 0.05f,
        -0.5f, -0.5f, -0.5f,0.7f, 0.45f, 0.05f,

        -0.5f, 0.5f, -0.5f,0.7f, 0.45f, 0.05f,
        0.5f, 0.5f, -0.5f, 0.7f, 0.45f, 0.05f,
        0.5f, 0.5f, 0.5f,  0.7f, 0.45f, 0.05f,
        0.5f, 0.5f, 0.5f,  0.7f, 0.45f, 0.05f,
        -0.5f, 0.5f, 0.5f, 0.7f, 0.45f, 0.05f,
        -0.5f, 0.5f, -0.5f,0.7f, 0.45f, 0.05f
};

StickBuffer::StickBuffer() {}

float*
StickBuffer::GetVertices() {
    return mVertices.data();
}

unsigned
StickBuffer::GetVertexCount() {
    return mVertices.size();
}

unsigned
StickBuffer::GetVertexElementCount() {
    return 6;
}
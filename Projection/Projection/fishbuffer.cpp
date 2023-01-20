#include "fishbuffer.hpp"

std::vector<float> FishBuffer::mVertices = {
    //      POS        |     COLOURS   
        // X    Y      Z       R    G     B
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

        0.5f, 0.5f, 0.5f,  1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,  1.0f, 1.0f, 0.0f,

        -0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f,0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f,0.0f, 1.0f, 1.0f

        -0.5f, -0.5f, -0.5f,1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,1.0f, 0.0f, 1.0f,

        
};

FishBuffer::FishBuffer() {}

float*
FishBuffer::GetVertices() {
    return mVertices.data();
}

unsigned
FishBuffer::GetVertexCount() {
    return mVertices.size();
}

unsigned
FishBuffer::GetVertexElementCount() {
    return 6;
}
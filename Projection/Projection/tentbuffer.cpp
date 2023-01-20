#include "tentbuffer.hpp"

std::vector<float> TentBuffer::mVertices = {
    //      POS        |     COLOURS   
        // X    Y      Z       R    G     B
        -0.5f, -0.5, 0.0f,     0.0f, 0.40f, 0.325f,
        0.5f, -0.5f, 0.0f,      0.0f, 0.40f, 0.325f,
        0.0f, 0.0f, 0.0f,       0.0f, 0.40f, 0.325f,

        0.5f, -0.5f, 0.0f,      0.0f, 0.4f, 0.325f,
        0.0f, 0.0f, -2.0f,      0.0f, 0.4f, 0.325f,
        0.0f, 0.0f, 0.0f,       0.0f, 0.4f, 0.325f,

        0.5f, -0.5f, 0.0f,      0.0f, 0.40f, 0.325f,
        0.5f, -0.5f, -2.0f,     0.0f,0.40f, 0.325f,
        0.0f, 0.0f, -2.0f,      0.0f, 0.40f, 0.325f,
        
        0.0f, 0.0f, 0.0f,       0.0f, 0.40f, 0.325f,
        0.0f, 0.0f, -2.0f,      0.0f, 0.40f, 0.325f,
        -0.5f, -0.5f, 0.0f,      0.0f, 0.40f, 0.325f,

        0.0f, 0.0f, -2.0f,      0.0f, 0.40f, 0.325f,
        -0.5f, -0.5f, -2.0f,    0.0f, 0.40f, 0.325f,
        -0.5f, -0.5f, 0.0,      0.0f, 0.40f, 0.325f,

};

TentBuffer::TentBuffer() {}

float*
TentBuffer::GetVertices() {
    return mVertices.data();
}

unsigned
TentBuffer::GetVertexCount() {
    return mVertices.size();
}

unsigned
TentBuffer::GetVertexElementCount() {
    return 6;
}
#pragma once
#include <vector>
#include "ibufferable.hpp"

class HoleBuffer : public IBufferable {
public:
    HoleBuffer();
private:
    static std::vector<float> mVertices;

    virtual float* GetVertices();
    virtual unsigned GetVertexCount();
    virtual unsigned GetVertexElementCount();
};
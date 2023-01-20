#pragma once
#include <vector>
#include "ibufferable.hpp"

class StickBuffer : public IBufferable {
public:
    StickBuffer();
private:
    static std::vector<float> mVertices;

    virtual float* GetVertices();
    virtual unsigned GetVertexCount();
    virtual unsigned GetVertexElementCount();
};
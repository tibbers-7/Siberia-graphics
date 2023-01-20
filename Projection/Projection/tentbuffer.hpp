#pragma once
#include <vector>
#include "ibufferable.hpp"

class TentBuffer : public IBufferable {
public:
    TentBuffer();
private:
    static std::vector<float> mVertices;

    virtual float* GetVertices();
    virtual unsigned GetVertexCount();
    virtual unsigned GetVertexElementCount();
};

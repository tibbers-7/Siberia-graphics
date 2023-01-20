#pragma once
#include <vector>
#include "ibufferable.hpp"

class FishBuffer : public IBufferable {
public:
    FishBuffer();
private:
    static std::vector<float> mVertices;

    virtual float* GetVertices();
    virtual unsigned GetVertexCount();
    virtual unsigned GetVertexElementCount();
};
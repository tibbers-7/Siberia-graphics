#pragma once
#include <vector>

#include "irenderable.hpp"
#include "holebuffer.hpp"
#include "buffer.hpp"

class Hole : public IRenderable {
public:
    Hole();
    void Render();
private:
    Buffer* mBuffer;
};
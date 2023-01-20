#pragma once
#include <vector>

#include "irenderable.hpp"
#include "fishbuffer.hpp"
#include "buffer.hpp"

class Fish : public IRenderable {
public:
    Fish();
    void Render();
private:
    Buffer* mBuffer;
};
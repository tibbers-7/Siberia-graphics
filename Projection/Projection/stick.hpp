#pragma once
#include <vector>

#include "irenderable.hpp"
#include "stickbuffer.hpp"
#include "buffer.hpp"

class Stick : public IRenderable {
public:
    Stick();
    void Render();
private:
    Buffer* mBuffer;
};
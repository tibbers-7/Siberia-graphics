#pragma once
#include <vector>

#include "irenderable.hpp"
#include "cubebuffer.hpp"
#include "buffer.hpp"

class Tent : public IRenderable {
public:
    Tent();
    void Render();
private:
    Buffer* mBuffer;
};
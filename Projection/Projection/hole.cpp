#include "hole.hpp"
#include "holebuffer.hpp"

Hole::Hole() {
    HoleBuffer HoleBuffer;
    mBuffer = new Buffer(HoleBuffer);
}

void
Hole::Render() {
    mBuffer->Render();
}
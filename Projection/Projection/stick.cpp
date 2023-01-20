#include "stick.hpp"
#include "stickbuffer.hpp"

Stick::Stick() {
    StickBuffer StickBuffer;
    mBuffer = new Buffer(StickBuffer);
}

void
Stick::Render() {
    mBuffer->Render();
}
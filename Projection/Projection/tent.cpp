#include "tent.hpp"
#include "tentbuffer.hpp"

Tent::Tent() {
    TentBuffer TentBuffer;
    mBuffer = new Buffer(TentBuffer);
}

void
Tent::Render() {
    mBuffer->Render();
}
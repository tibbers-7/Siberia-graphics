#include "fish.hpp"
#include "fishbuffer.hpp"

Fish::Fish() {
    FishBuffer FishBuffer;
    mBuffer = new Buffer(FishBuffer);
}

void
Fish::Render() {
    mBuffer->Render();
}
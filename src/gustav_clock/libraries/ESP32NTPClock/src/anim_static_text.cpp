#include "anim_static_text.h"

StaticTextAnimation::StaticTextAnimation(std::string text) : _text(text) {}

void StaticTextAnimation::setup(IDisplayDriver* display) {
    IAnimation::setup(display);
    // Print the static text to the buffer ONCE.
    _display->print(_text.c_str());
    _startTime = millis();
}

void StaticTextAnimation::update() {
    // Do absolutely nothing. The buffer is already set.
}

bool StaticTextAnimation::isDone() {
     return (millis() - _startTime >= 2000);
}
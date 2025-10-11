#ifndef ANIM_STATIC_TEXT_H
#define ANIM_STATIC_TEXT_H

#include "i_animation.h"
#include <string>

class StaticTextAnimation : public IAnimation {
public:
    StaticTextAnimation(std::string text);
    void setup(IDisplayDriver* display) override;
    void update() override;
    bool isDone() override;

private:
    std::string _text;
    unsigned long _startTime;
};

#endif // ANIM_STATIC_TEXT_H
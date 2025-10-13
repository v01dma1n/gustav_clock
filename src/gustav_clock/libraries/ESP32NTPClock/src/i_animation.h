#ifndef I_ANIM_H
#define I_ANIM_H

#include "i_display_driver.h"
#include "anim_utils.h"
#include <string>
#include <vector>

class IAnimation {
public:
    virtual ~IAnimation() {}

    virtual void setup(IDisplayDriver* display) {
        _display = display;
        // Allocate the private buffer to match the display size
        _buffer.assign(_display->getDisplaySize(), 0); 
    }

    virtual void update() = 0;
    virtual bool isDone() = 0;

    // New function to get the completed frame from the animation
    const std::vector<unsigned long>& getFrame() const {
        return _buffer;
    }

protected:
    IDisplayDriver* _display;
    std::vector<unsigned long> _buffer; // The animation's private buffer

    // This now writes to the animation's private buffer, not the display driver
    void setChar(int position, char character, bool dot = false) {
        if (position < 0 || position >= _buffer.size()) return;
        _buffer[position] = _display->mapAsciiToSegment(character, dot);
    }
};

#endif // I_ANIM_H

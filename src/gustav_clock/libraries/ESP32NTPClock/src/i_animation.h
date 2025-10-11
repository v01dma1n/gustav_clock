#ifndef I_ANIM_H
#define I_ANIM_H

#include "i_display_driver.h"
#include <string>
#include <vector>

class IAnimation {
public:
    virtual ~IAnimation() {}

    // Setup is called once when the animation starts
    virtual void setup(IDisplayDriver* display) {
        _display = display;
    }

    // Update is called on every loop iteration to draw the next frame
    virtual void update() = 0;

    // Returns true if the animation has finished
    virtual bool isDone() = 0;

protected:
    IDisplayDriver* _display;

    void parseTextAndDots(const std::string& inputText, bool dotsWithPrevious,
                          std::string& outParsedText, std::vector<bool>& outDotStates) {
        outParsedText.clear();
        outDotStates.clear();
        int displaySize = _display->getDisplaySize();

        for (char c : inputText) {
            if (c == '.' && dotsWithPrevious) {
                if (!outDotStates.empty()) {
                    outDotStates.back() = true; // Apply dot to the previous char
                }
            } else {
                outParsedText += c;
                outDotStates.push_back(false);
            }
        }
        // Ensure the parsed text and dot states are padded to the display size
        while (outParsedText.length() < displaySize) {
            outParsedText += ' ';
        }
        while (outDotStates.size() < displaySize) {
            outDotStates.push_back(false);
        }
    }
};

#endif // I_ANIM_H
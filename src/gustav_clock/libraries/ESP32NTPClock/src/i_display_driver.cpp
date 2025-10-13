#include "i_display_driver.h"
#include "anim_utils.h" // Use the shared parser

// This provides the concrete implementation for the print() method.
void IDisplayDriver::print(const char* text, bool dotsWithPreviousChar) {
    std::string parsedText;
    std::vector<uint8_t> dotStates;
    
    // Use the shared parser to handle dots correctly
    parseTextAndDots(std::string(text), dotsWithPreviousChar, parsedText, dotStates);

    clear();
    int len = std::min((int)parsedText.length(), getDisplaySize());
    for (int i = 0; i < len; ++i) {
        setChar(i, parsedText[i], dotStates[i]);
    }
}
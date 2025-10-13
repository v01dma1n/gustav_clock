#ifndef ANIM_UTILS_H
#define ANIM_UTILS_H

#include <string>
#include <vector>
#include <cstdint>

// This is a shared utility function to parse text and handle dot placement.
inline void parseTextAndDots(const std::string& inputText, bool dotsWithPrevious,
                             std::string& outParsedText, std::vector<uint8_t>& outDotStates) {
    outParsedText.clear();
    outDotStates.clear();

    for (char c : inputText) {
        if (c == '.' && dotsWithPrevious) {
            // If a dot is found and we have text to attach it to,
            // set the dot flag for the *previous* character.
            if (!outDotStates.empty()) {
                outDotStates.back() = 1; // 1 means true
            }
        } else {
            // This is a regular character, add it to the text
            // and add a corresponding 'false' dot state.
            outParsedText += c;
            outDotStates.push_back(0); // 0 means false
        }
    }
}

#endif // ANIM_UTILS_H
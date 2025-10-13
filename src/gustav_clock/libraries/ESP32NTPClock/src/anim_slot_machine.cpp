#include "anim_slot_machine.h"
#include <Arduino.h>
#include <algorithm> // Required for std::find

SlotMachineAnimation::SlotMachineAnimation(std::string targetText,
                                           unsigned long lockDelay,
                                           unsigned long holdTime,
                                           unsigned long spinDelay,
                                           bool dotsWithPreviousChar)
    : _targetText(targetText),
      _lockDelay(lockDelay),
      _holdTime(holdTime),
      _spinDelay(spinDelay),
      _dotsWithPreviousChar(dotsWithPreviousChar),
      _lastLockTime(0),
      _lastSpinTime(0),
      _lockingCompleteTime(0),
      _finalFrameDrawn(false),
      _rng(millis())
{}

SlotMachineAnimation::~SlotMachineAnimation() {}

void SlotMachineAnimation::setup(IDisplayDriver* display) {
    IAnimation::setup(display);
    
    _parsedText = _targetText;
    _dotStates.assign(_targetText.length(), 0); 
    
    // Clear the list of locked indices.
    _lockedIndices.clear();
    
    _lastLockTime = millis();
    _lastSpinTime = millis();
    _lockingCompleteTime = 0;
    _finalFrameDrawn = false;
    
    int displaySize = _display->getDisplaySize();
    for (int i = 0; i < displaySize; ++i) {
        _display->setChar(i, _rng.nextRange(0, 9) + '0', false);    
    }
}

bool SlotMachineAnimation::isDone() {
    int displaySize = _display->getDisplaySize();
    bool lockingComplete = _lockedIndices.size() >= displaySize;
    if (!lockingComplete) {
        return false;
    }
    return (millis() - _lockingCompleteTime >= _holdTime);
}

void SlotMachineAnimation::update() {
    if (isDone()) {
        if (!_finalFrameDrawn) {
            int displaySize = _display->getDisplaySize();
            for (int i = 0; i < displaySize; ++i) {
                if (i < _parsedText.length()) {
                    _display->setChar(i, _parsedText[i], _dotStates[i]);
                } else {
                    _display->setChar(i, ' ', false);
                }
            }
            _finalFrameDrawn = true;
        }
        return;
    }

    unsigned long currentTime = millis();
    if (currentTime - _lastSpinTime < _spinDelay) {
        return;
    }
    _lastSpinTime = currentTime;

    // --- State Update Logic: Randomly lock one new digit ---
    int displaySize = _display->getDisplaySize();
    bool isLockingPhase = _lockedIndices.size() < displaySize;
    if (isLockingPhase && (currentTime - _lastLockTime >= _lockDelay)) {
        _lastLockTime = currentTime;
        
        // Find a digit that is not yet locked
        while (_lockedIndices.size() < displaySize) {
            int potentialIndex = _rng.nextRange(0, displaySize - 1);
            // Check if the index is already in our list
            bool alreadyLocked = (std::find(_lockedIndices.begin(), _lockedIndices.end(), potentialIndex) != _lockedIndices.end());
            if (!alreadyLocked) {
                _lockedIndices.push_back(potentialIndex); // Lock it
                break; // Exit the while loop
            }
        }

        if (_lockedIndices.size() == displaySize) {
            _lockingCompleteTime = millis();
        }
    }

    // --- Drawing Logic: Check if index is in the list ---
    for (int i = 0; i < displaySize; ++i) {
        bool isLocked = (std::find(_lockedIndices.begin(), _lockedIndices.end(), i) != _lockedIndices.end());
        
        if (isLocked) {
            if (i < _parsedText.length()) {
                _display->setChar(i, _parsedText[i], _dotStates[i]);
            } else {
                _display->setChar(i, ' ', false);
            }
        } else {
            _display->setChar(i, _rng.nextRange(0, 9) + '0', false);    
        }
    }
}
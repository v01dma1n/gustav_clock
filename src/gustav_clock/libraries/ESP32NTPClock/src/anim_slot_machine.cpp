#include "anim_slot_machine.h"

#include <Arduino.h>


SlotMachineAnimation::SlotMachineAnimation(std::string targetText, 
                                           unsigned long lockDelay, 
                                           unsigned long holdTime, 
                                           unsigned long spinDelay, 
                                           bool dotsWithPreviousChar)
    : _targetText(targetText),
      _lockDelay(lockDelay),
      _holdTime(holdTime),
      _spinDelay(spinDelay), // Initialize spinDelay
      _dotsWithPreviousChar(dotsWithPreviousChar),
      _lastLockTime(0),
      _lastSpinTime(0),      // Initialize spin timer
      _lockedCount(0),
      _lockingCompleteTime(0) {
    _isLocked = nullptr;
}

SlotMachineAnimation::~SlotMachineAnimation() {
    delete[] _isLocked;
}

void SlotMachineAnimation::setup(IDisplayDriver* display) {
    IAnimation::setup(display);
    int size = _display->getDisplaySize();

    // Use the new, reliable parser from the base class
    parseTextAndDots(_targetText, _dotsWithPreviousChar, _parsedText, _dotStates);

    _currentText.resize(size, ' ');

    delete[] _isLocked;
    _isLocked = new bool[size];
    for (int i = 0; i < size; ++i) {
        _isLocked[i] = false;
    }
    _lastLockTime = millis();
    randomSeed(analogRead(0));
}

bool SlotMachineAnimation::isDone() {
    bool lockingComplete = _lockedCount >= _display->getDisplaySize();
    if (!lockingComplete) {
        return false;
    }
    return (millis() - _lockingCompleteTime >= _holdTime);
}

void SlotMachineAnimation::update() {
    unsigned long currentTime = millis();
    if (currentTime - _lastSpinTime < _spinDelay) {
        return;
    }
    _lastSpinTime = currentTime;

    if (isDone()) {
        return;
    }

    int displaySize = _display->getDisplaySize();

    // --- Locking Logic ---
    bool lockingPhaseActive = _lockedCount < displaySize;
    if (lockingPhaseActive && (currentTime - _lastLockTime >= _lockDelay)) {
        _lastLockTime = currentTime;
        if (_lockedCount < displaySize) {
            _isLocked[_lockedCount] = true;
            _lockedCount++;
            if (_lockedCount == displaySize) {
                _lockingCompleteTime = millis();
            }
        }
    }

    // --- Drawing Logic ---
    for (int i = 0; i < displaySize; ++i) {
        char charToWrite = _isLocked[i] ? _parsedText[i] : (random(0, 10) + '0');
        bool hasDot = _dotStates[i];
        _display->setChar(i, charToWrite, hasDot);
    }
}


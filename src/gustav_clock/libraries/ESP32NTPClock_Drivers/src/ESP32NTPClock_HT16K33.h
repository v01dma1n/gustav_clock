#ifndef DISP_DRIVER_HT16K33_H
#define DISP_DRIVER_HT16K33_H

#include "i_display_driver.h"

#define HT16K33_I2C_DEF_ADR 0x70
#define HT16K33_DEF_DISP_SIZE 8
#define HT16K33_MAX_DISP_SIZE 16

#define HT16K33_MAX_BRIGHTNESS 15
#define HT16K33_DEF_BRIGHTNESS  7

class DispDriverHT16K33 : public IDisplayDriver {
public:
    DispDriverHT16K33(uint8_t i2c_addr = HT16K33_I2C_DEF_ADR, int displaySize = HT16K33_DEF_DISP_SIZE);
    virtual ~DispDriverHT16K33() {}

    void begin() override;
    int getDisplaySize() override;
    void setBrightness(uint8_t level) override;

    void clear() override;
    void setChar(int position, char character, bool dot = false) override;
    void setSegments(int position, uint16_t mask) override;

    void writeDisplay() override;

private:
    uint16_t _displayBuffer[HT16K33_MAX_DISP_SIZE]; 
    int _displaySize;
    uint8_t _i2c_addr;

    // Font table for character-to-segment mapping
    static const uint8_t PROGMEM sevensegfonttable[]; 
};

#endif // DISP_DRIVER_HT16K33_H

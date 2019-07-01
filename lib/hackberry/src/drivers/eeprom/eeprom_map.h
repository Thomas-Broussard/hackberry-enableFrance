/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  Mapping of the EEPROM memory for Hackberry hand
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

// in case of evolution, please modify the MAGIC_WORD value
#define MAGIC_WORD 0xABCD // this word is present at the beginning of the memory

/**
 * Structure representing the EEPROM memory of the Hackberry board. 
 * The order of the variables is important here: it determines their place in the EEPROM memory. 
 * 
 * Example: magicWord is located first in the structure, so it will be set to the very first address of the EEPROM (0x0000)
 */
typedef struct {
    unsigned long magicWord;

    char        selectedHand;  // Selected hand (RIGHT or LEFT)
    
    unsigned char majorVersion;
    unsigned char minorVersion;
    unsigned char patchVersion;

    unsigned char servoSpeed;    // Speed of servomotor (between 0 and 255)

    unsigned char thumbMin;      // between 0 and 180°
    unsigned char thumbMax;      // between 0 and 180°

    unsigned char indexMin;      // between 0 and 180°
    unsigned char indexMax;      // between 0 and 180°

    unsigned char fingersMin;    // between 0 and 180°
    unsigned char fingersMax;    // between 0 and 180°

    unsigned char sensorType;    
    int         sensorMin;     // between MIN_ADC and MAX_ADC
    int         sensorMax;     // between MIN_ADC and MAX_ADC
} Mapping_Struct;

// Macro to get position of member in the Mapping_Struct structure
#define ADDR(m) ((size_t) ( (char *)&((Mapping_Struct *)(0))->m - (char *)0 ))

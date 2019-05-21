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

typedef struct {
    unsigned long magicWord;

    char        selectedHand;  // Selected hand (RIGHT or LEFT)
    char        servoSpeed;    // Speed of servomotor (between 0 and 255)

    char        thumbMin;      // between 0 and 180°
    char        thumbMax;      // between 0 and 180°

    char        indexMin;      // between 0 and 180°
    char        indexMax;      // between 0 and 180°

    char        fingersMin;    // between 0 and 180°
    char        fingersMax;    // between 0 and 180°

    char        sensorType;    
    float       sensorGain;
    int         sensorOffset;
} Mapping_Struct;

// Macro to get position of member in the Mapping_Struct structure
#define ADDR(m) ((size_t) ( (char *)&((Mapping_Struct *)(0))->m - (char *)0 ))

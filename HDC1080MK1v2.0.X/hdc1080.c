// Gyroscope

#include <xc.h>
#include <assert.h>
#include <stdbool.h>
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c_master_example.h"
#include "hdc1080.h"

#define HDC1080_ADDR    0x40

#define TEMP_OUT        0x00
#define HUMY_OUT        0x01
#define CONFIG          0x02

uint8_t  writeBuffer[3] = {0x00, 0x00, 0x00};                           // definiert "writeBuffer"
uint8_t  readBuffer[10] = {0x00, 0x00};                                 // definiert "readBuffer" 

void HDC1080_Init(void){                                                // "HDC1080_Init"
    I2C_Write1ByteRegister(HDC1080_ADDR, CONFIG, 0x10);                 // schreibt "0x10" in "CONFIG"     
    __delay_ms(100);                                                    // warte 100ms
}                                                                       // 

void HDC1080_Read(void){                                                // "HDC1080_Read"
    uint8_t regist = 0x00;                                              // definiert "regist"

    I2C_WriteNBytes(HDC1080_ADDR, &regist, 1);                          // schreibt "regist" an den Sensor
    __delay_ms(15000);                                                  // warte 15s
    I2C_ReadNBytes(HDC1080_ADDR, &readBuffer, 6);                       // liest 6 Byte vom Sensor
}                                                                       // 

float HDC1080_temp_GetValue(void){                                      // "HDC1080_temp_GetValue"  
    float    tempDataAnz;                                               // definiert "tempDataAnz"
  
    HDC1080_Read();                                                     // ruft "HDC1080_Read" auf 
    tempDataAnz = (readBuffer[0] << 8) + readBuffer[1];                 //       
    tempDataAnz = tempDataAnz * 165 / 65536 - 40;                       //
    
    return tempDataAnz;                                                 // gibt "tempDataAnz" zur?ck     
}                                                                       // 

float HDC1080_humy_GetValue(void){                                      // "HDC1080_humy_GetValue" 
    float    humyDataAnz;                                               // definiert "humyDataAnz"
  
    HDC1080_Read();                                                     // ruft "HDC1080_Read" auf 
    humyDataAnz = (readBuffer[2] << 8) + readBuffer[3];                 //    
    humyDataAnz = humyDataAnz * 100 / 65536;                            //
    
    return humyDataAnz;                                                 // gibt "humyDataAnz" zur?ck     
}                                                                       // 


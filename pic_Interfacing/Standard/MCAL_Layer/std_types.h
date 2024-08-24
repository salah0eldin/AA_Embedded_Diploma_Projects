/* 
 * File:   mcal_std_types.h
 * Author: Salah-Eldin
 * 
 * Created on August 10, 2024
 */

//=========================================================================
//                             Includes
//=========================================================================
#ifndef MCAL_STD_TYPES_H
#define MCAL_STD_TYPES_H

#include "compiler.h"
#include "std_libraries.h"

//=========================================================================
//                        Macro Declarations
//=========================================================================
#define STD_HIGH        0x01
#define STD_LOW         0x00

#define STD_ON          0x01
#define STD_OFF         0x00

#define STD_ACTIVE      0x01
#define STD_IDLE        0x00

#define CONFIG_ENABLE   0x01
#define CONFIG_DISABLE  0x00

#define E_OK            0x01
#define E_NOT_OK        0x00

#define ZERO_INIT       0

//=========================================================================
//                   Macro Functions Declarations
//=========================================================================

//=========================================================================
//                        Data Types Declarations
//=========================================================================
typedef unsigned char boolean;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;
typedef float float32;

typedef uint8 Std_ReturnType;

typedef enum {
    INDEX0 = 0,
    INDEX1,
    INDEX2,
    INDEX3,
    INDEX4,
    INDEX5,
    INDEX6,
    INDEX7
} array_indexs;

//=========================================================================
//                    Functions Declarations
//=========================================================================


#endif /* MCAL_STD_TYPES_H */

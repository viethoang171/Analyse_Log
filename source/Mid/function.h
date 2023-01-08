/*******************************************************************************
 *				 _ _                                             _ _
                |   |                                           (_ _)
                |   |        _ _     _ _   _ _ _ _ _ _ _ _ _ _   _ _
                |   |       |   |   |   | |    _ _     _ _    | |   |
                |   |       |   |   |   | |   |   |   |   |   | |   |
                |   |       |   |   |   | |   |   |   |   |   | |   |
                |   |_ _ _  |   |_ _|   | |   |   |   |   |   | |   |
                |_ _ _ _ _| |_ _ _ _ _ _| |_ _|   |_ _|   |_ _| |_ _|
                                (C)2021 Lumi
 * Copyright (c) 2021
 * Lumi, JSC.
 * All Rights Reserved
 *
 * File name: Example.h
 *
 * Description:
 *
 * Author: PhuongNP
 *
 * Last Changed By:  $Author: phuongnp $
 * Revision:         $Revision: $
 * Last Changed:     $Date: $Jun 9, 2021
 *
 * Code sample:
 ******************************************************************************/
// Enclosing macro to prevent multiple inclusion
#ifndef FUNCTION_H_
#define FUNCTION_H_
/******************************************************************************/
/*                              INCLUDE FILES                                 */
#include <stdio.h>
#include "typedefs.h"
/******************************************************************************/

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
#define MAX_LENGTH_FILE 5000
#define FILENAME "log.txt"
/******************************************************************************/

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
i32_t fileToStr(u8_p pibStr);
i32_t count(u8_p pibFileLog);
u32_t pow10(u32_t dwDegree);
u32_t stringToNum(u8_t byStr[MAX_LENGTH_FILE]);
void_t task1();
void_t task2();
void_t task3();
void_t task4();
void_t task5();
void_t task6();
/******************************************************************************/

/******************************************************************************/
#endif // FUNCTION_H_

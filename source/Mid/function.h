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
 * File name: function.h
 *
 * Description:
 *
 * Author: HoangNV
 *
 * Last Changed By:  $Author: HoangNV $
 * Revision:         $Revision: $
 * Last Changed:     $Date: $Jan 09, 2023
 *
 * Code sample:
 ******************************************************************************/
// Enclosing macro to prevent multiple inclusion
#ifndef FUNCTION_H_
#define FUNCTION_H_
/******************************************************************************/
/*                              INCLUDE FILES                                 */
#include <stdio.h>
#include "../utils/typedefs.h"
/******************************************************************************/

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
#define MAX_LENGTH_FILE 5000
#define MAX_LENGTH_STRING_NUM 20
#define MAX_LENGTH_MINUTE 20
#define MAX_LENGTH_SECOND 20
#define MAX_LENGTH_REQID 20
#define MAX_LENGTH_DIRECT_NEWS 10
#define MAX_LENGTH_NWK 20
#define MAX_LENGTH_NETWORK 10
#define MAX_LENGTH_ENDPOINT 10
#define TINH_MAX_DELAY_TIME 5
#define TINH_TRUNG_BINH_DELAY_TIME 6
#define CONVERT_MINUTE_TO_SECOND 60
#define CONVERT_SECOND_TO_MILLISECOND 1000
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
void_t getCountSentNews();
void_t getCountSentNewsWithInputCode();
void_t getCountSwitch();
void_t getCountErrorNews();
void_t getMaxDelayTime();
void_t getAverageTimeDelay();
/******************************************************************************/

/******************************************************************************/
#endif // FUNCTION_H_

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
 * File name: main.c
 *
 * Description: This code is used to execute assignment 2 on Funix, process data on log.txt
 *
 * Author: HoangNV
 *
 * Last Changed By:  $Author: hoangNV $
 * Revision:         $Revision: $
 * Last Changed:     $Date: $Jan 09, 2023
 *
 * Code sample:
 ******************************************************************************/
/******************************************************************************/
/*                              INCLUDE FILES                                 */
#include <stdio.h>
#include <string.h>
#include "../mid/function.h"
#include "main.h"
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
u8_t g_fileStr[MAX_LENGTH_FILE];
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */

i32_t main()
{
    fileToStr(g_fileStr);
    getCountSentNews();
    getCountSentNewsWithInputCode();
    getCountSwitch();
    getCountErrorNews();
    getMaxDelayTime();
    getAverageTimeDelay();
    return 0;
}

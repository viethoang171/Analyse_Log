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
 * File name: Example.c
 *
 * Description: This code is used for tranning Lumi IOT member. It is the code form statandard.
 *
 * Author: PhuongNP
 *
 * Last Changed By:  $Author: phuongnp $
 * Revision:         $Revision: $
 * Last Changed:     $Date: $Jun 9, 2021
 *
 * Code sample:
 ******************************************************************************/
/******************************************************************************/
/*                              INCLUDE FILES                                 */
#include <stdio.h>
#include <stdlib.h>
#include "source/utils/typedefs.h"
#include <string.h>
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
i32_t fileToStr(u8_p pibStr);

i32_t count(u8_p pibFileLog);

void_t task1();

void_t task2();

void_t task3();

void_t task4();

void_t task5();

u32_t pow10(u32_t i);

u32_t stringToNum(u8_t byStr[MAX_LENGTH_FILE]);
void_t task6();

i32_t main()
{
    fileToStr(g_fileStr);
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    return 0;
}

i32_t fileToStr(u8_p pibStr)
{
    i32_t dwStatus;
    FILE *fp = NULL;
    fp = fopen(FILENAME, "r");
    if (fp == NULL)
    {
        printf("File does not exist\n");
        return -1;
    }
    dwStatus = fread(pibStr, MAX_LENGTH_FILE, 1, fp);
    fclose(fp);
    fp = NULL;
    return dwStatus;
}

i32_t count(u8_p pibFileLog)
{
    i32_t dwCount = 0;
    u8_t byDirect[] = "\"cmd\":\"set\"";
    u8_p pbyCheckEnd = NULL;
    do
    {
        if (pbyCheckEnd == NULL)
            pbyCheckEnd = strstr(pibFileLog, byDirect);
        else
            pbyCheckEnd = strstr(pbyCheckEnd + 1, byDirect);
        if (pbyCheckEnd != NULL)
            dwCount++;
    } while (pbyCheckEnd != NULL);
    return dwCount;
}

u32_t pow10(u32_t i)
{
    if (i == 0)
        return 1;
    u32_t dwResult = 1;
    for (u32_t k = 1; k <= i; k++)
        dwResult *= 10;
    return dwResult;
}
u32_t stringToNum(u8_t byStr[MAX_LENGTH_FILE])
{
    u32_t dwResult = 0;
    u32_t dwLengthStr = strlen(byStr);
    for (u32_t i = 0; i < dwLengthStr; i++)
    {
        u32_t dwChuSo = byStr[dwLengthStr - i - 1] - 48;
        dwResult += dwChuSo * pow10(i);
    }
    return dwResult;
}
void_t task5()
{
    u32_t dwMaxDelay = 0;
    u8_t byEnd[MAX_LENGTH_FILE] = "";
    byEnd[0] = 10;
    u8_p pbyCheckEnd = g_fileStr;

    u8_t byMinuteSet[MAX_LENGTH_FILE] = "";
    u8_t byMinuteStatus[MAX_LENGTH_FILE] = "";
    u8_t bySecondSet[MAX_LENGTH_FILE] = "";
    u8_t bySecondStatus[MAX_LENGTH_FILE] = "";

    u8_t byReqidSet[MAX_LENGTH_FILE] = "";
    u8_t byReqidStatus[MAX_LENGTH_FILE] = "";
    while (pbyCheckEnd != NULL)
    {
        u8_p pbyFindMinute = strstr(pbyCheckEnd, ":");

        // xu ly Time
        u8_p pbyFindSecond = strstr(pbyFindMinute + 1, ":");
        u8_p pbyFindEndTime = strstr(pbyFindSecond + 1, "]");
        u8_t byDelayMinute[MAX_LENGTH_FILE] = "";
        u8_t byDelaySecond[MAX_LENGTH_FILE] = "";
        u32_t dwLengthMinute = pbyFindSecond - pbyFindMinute - 1;
        for (u32_t i = 0; i < dwLengthMinute; i++)
            byDelayMinute[i] = *(pbyFindMinute + i + 1);
        u32_t dwLengthSecond = pbyFindEndTime - pbyFindSecond - 1;
        for (u32_t i = 0; i < dwLengthSecond; i++)
            byDelaySecond[i] = *(pbyFindSecond + i + 1);

        // FindDirect
        u8_p pbyFindDirect = strstr(pbyCheckEnd, "\"cmd\":");
        u32_t dwLengthDirect = strlen("\"cmd\":");
        u8_p pbyEndDirect = strstr(pbyCheckEnd, ",");
        u8_t byDirect[MAX_LENGTH_FILE] = "";
        for (u32_t i = 0; i < pbyEndDirect - pbyFindDirect - dwLengthDirect; i++)
            byDirect[i] = *(pbyFindDirect + i + dwLengthDirect);

        // FindCorrectNews
        u8_p pbyFindReqid = strstr(pbyCheckEnd, "\"reqid\": \"");
        u32_t dwLengthReqid = strlen("\"reqid\": \"");
        u8_p pbyFindReqidEnd = strstr(pbyFindReqid + dwLengthReqid, "\"");
        u32_t dwLengthReqidCode = pbyFindReqidEnd - pbyFindReqid - dwLengthReqid;
        if (strcmp(byDirect, "\"set\"") == 0)
        {
            byReqidSet[MAX_LENGTH_FILE] = "";
            for (u32_t i = 0; i < dwLengthReqidCode; i++)
                byReqidSet[i] = *(pbyFindReqid + i + dwLengthReqid);
        }
        else
        {
            byReqidStatus[MAX_LENGTH_FILE] = "";
            for (u32_t i = 0; i < dwLengthReqidCode; i++)
                byReqidStatus[i] = *(pbyFindReqid + i + dwLengthReqid);
            if (strcmp(byReqidSet, byReqidStatus) != 0)
            {
                pbyCheckEnd = strstr(pbyCheckEnd + 1, byEnd);
                continue;
            }
        }

        // Xu ly Direct
        if (strcmp(byDirect, "\"set\"") == 0)
        {
            byMinuteSet[MAX_LENGTH_FILE] = "";
            bySecondSet[MAX_LENGTH_FILE] = "";
            for (u32_t k = 0; k < dwLengthMinute; k++)
                byMinuteSet[k] = *(byDelayMinute + k);
            u32_t dwLengthSecondSet = 0;
            for (u32_t k = 0; k < dwLengthSecond; k++)
                if (*(byDelaySecond + k) != '.')
                    bySecondSet[dwLengthSecondSet++] = *(byDelaySecond + k);
        }
        else
        {
            byMinuteStatus[MAX_LENGTH_FILE] = "";
            bySecondStatus[MAX_LENGTH_FILE] = "";
            for (u32_t k = 0; k < dwLengthMinute; k++)
                byMinuteStatus[k] = *(byDelayMinute + k);
            u32_t dwLengthSecondStatus = 0;
            for (u32_t k = 0; k < dwLengthSecond; k++)
                if (*(byDelaySecond + k) != '.')
                    bySecondStatus[dwLengthSecondStatus++] = *(byDelaySecond + k);
            u32_t dwTimeDelay = (stringToNum(byMinuteStatus) - stringToNum(byMinuteSet)) * 60 * 1000 + (stringToNum(bySecondStatus) - stringToNum(bySecondSet));
            if (dwTimeDelay > dwMaxDelay)
                dwMaxDelay = dwTimeDelay;
        }

        pbyCheckEnd = strstr(pbyCheckEnd + 1, byEnd);
    }
    printf("Do tre lon nhat la: %d Millisecond\n", dwMaxDelay);
}

void_t task1()
{
    u32_t dwCount = count(g_fileStr);
    printf("\nSo luong ban tin la: %d", dwCount);
}

void_t task2()
{
    u8_t byAddressNWK[MAX_LENGTH_FILE] = "";
    printf("\nNhap dia chi nwk cua thiet bi: %");
    scanf("%s", byAddressNWK);
    printf("\n");
    u8_p pbyCheckEnd = g_fileStr;
    u8_t byEnd[MAX_LENGTH_FILE] = "";
    byEnd[0] = 10;
    u8_p pbyStart = NULL;
    u8_p pbyEnd = NULL;
    u32_t dwCountNews = 0;
    while (pbyCheckEnd != NULL)
    {
        u8_t byNews[MAX_LENGTH_FILE] = "";
        u32_t dwNewsIndex = 0;
        pbyStart = strstr(pbyCheckEnd, "[INFO]");
        pbyEnd = strstr(pbyCheckEnd + 1, byEnd);
        u8_p pibIndexNews = NULL;
        if (pbyStart - pbyEnd < 0)
            for (pibIndexNews = pbyStart; pibIndexNews != pbyEnd + 1; pibIndexNews++)
            {
                byNews[dwNewsIndex++] = *pibIndexNews;
            }

        u8_p pbyFindSet = strstr(byNews, "\"set\"");
        if (pbyFindSet == NULL)
        {
            pbyCheckEnd = strstr(pbyCheckEnd + 1, byEnd);
            continue;
        }
        u8_p pbyFindNwk = strstr(byNews, byAddressNWK);
        if (pbyFindNwk != NULL)
            dwCountNews++;
        pbyCheckEnd = strstr(pbyCheckEnd + 1, byEnd);
    }
    printf("\nSo ban tin gui di la: %d\n", dwCountNews);
}

void_t task3()
{
    u8_t pbyBufferString[20][MAX_LENGTH_FILE];
    u8_t pbyBufferEndPoint[20][MAX_LENGTH_FILE];
    u32_t dwNumberBufferString = 0;
    u8_t byEnd[MAX_LENGTH_FILE] = "";
    byEnd[0] = 10;
    u8_p pbyCheckEnd = g_fileStr;
    u8_p pbyStart = NULL;
    u8_p pbyEnd = NULL;
    while (pbyCheckEnd != NULL)
    {
        u8_t byNews[MAX_LENGTH_FILE] = "";
        u32_t dwNewsIndex = 0;
        pbyStart = strstr(pbyCheckEnd, "[INFO]");
        pbyEnd = strstr(pbyCheckEnd + 1, byEnd);
        u8_p pibNewsIndex = NULL;
        if (pbyStart - pbyEnd < 0)
            for (pibNewsIndex = pbyStart; pibNewsIndex != pbyEnd + 1; pibNewsIndex++)
            {
                byNews[dwNewsIndex++] = *pibNewsIndex;
            }

        u8_p pbyFindSet = strstr(byNews, "\"set\"");
        if (pbyFindSet == NULL)
        {
            pbyCheckEnd = strstr(pbyCheckEnd + 1, byEnd);
            continue;
        }
        u8_p pbyNewsCode = NULL;
        pbyNewsCode = strstr(pbyCheckEnd, "\"zwave");

        u8_p pbyNetWork = NULL;
        pbyNetWork = strstr(pbyNewsCode, "-");
        u32_t dwLengthNetWork = 0;
        u8_t byResultNetWork[MAX_LENGTH_FILE] = "";
        while (*(pbyNetWork + dwLengthNetWork) != ':')
        {
            byResultNetWork[dwLengthNetWork++] = *(pbyNetWork + dwLengthNetWork);
        }
        u8_p pbyEndPoint = NULL;
        pbyEndPoint = strstr(pbyNetWork + dwLengthNetWork, "-");
        u32_t dwLengthEndPoint = 0;
        u8_t byResultEndPoint[MAX_LENGTH_FILE] = "";
        while (*(pbyEndPoint + dwLengthEndPoint) != '"')
            byResultEndPoint[dwLengthEndPoint++] = *(pbyEndPoint + dwLengthEndPoint);
        u32_t dwCheckString = 0;
        for (u32_t i = 1; i <= dwNumberBufferString; i++)
            if (strcmp(byResultNetWork, pbyBufferString[i]) == 0)
            {
                dwCheckString = 1;
                break;
            }
        if (dwCheckString == 0)
        {
            ++dwNumberBufferString;
            for (u32_t j = 0; j < strlen(byResultEndPoint); j++)
                pbyBufferEndPoint[dwNumberBufferString][j] = byResultEndPoint[j];
            for (u32_t j = 0; j < strlen(byResultNetWork); j++)
                pbyBufferString[dwNumberBufferString][j] = byResultNetWork[j];
        }
        pbyCheckEnd = strstr(pbyCheckEnd + 1, byEnd);
    }
    for (u32_t i = 1; i <= dwNumberBufferString; i++)
        printf("thiet bi %d co dia chi la : NWK %s, ENDPOINT %s\n", i, pbyBufferString[i], pbyBufferEndPoint[i]);
}

void_t task4()
{
    u32_t dwCountErrorNews = 0;
    u8_p pbyCheckEnd = g_fileStr;
    u8_t byEnd[MAX_LENGTH_FILE] = "";
    byEnd[0] = 10;
    u8_t byReqidSet[MAX_LENGTH_FILE] = "";
    u8_t byReqidStatus[MAX_LENGTH_FILE] = "";

    while (pbyCheckEnd != NULL)
    {
        u8_p pbyEndNews = strstr(pbyCheckEnd + 1, byEnd);
        u8_p pbyFindDirect = strstr(pbyCheckEnd, "\"cmd\":");
        u32_t dwLengthDirect = strlen("\"cmd\":");
        u8_p pbyEndDirect = strstr(pbyCheckEnd, ",");
        u8_t byDirect[MAX_LENGTH_FILE] = "";
        for (u32_t i = 0; i < pbyEndDirect - pbyFindDirect - dwLengthDirect; i++)
            byDirect[i] = *(pbyFindDirect + i + dwLengthDirect);

        u8_p pbyFindReqid = strstr(pbyCheckEnd, "\"reqid\": \"");
        u32_t dwLengthReqid = strlen("\"reqid\": \"");
        u8_p pbyFindReqidEnd = strstr(pbyFindReqid + dwLengthReqid, "\"");
        u32_t dwLengthReqidCode = pbyFindReqidEnd - pbyFindReqid - dwLengthReqid;
        if (strcmp(byDirect, "\"set\"") == 0)
        {
            byReqidSet[MAX_LENGTH_FILE] = "";
            for (u32_t i = 0; i < dwLengthReqidCode; i++)
                byReqidSet[i] = *(pbyFindReqid + i + dwLengthReqid);
        }
        else
        {
            byReqidStatus[MAX_LENGTH_FILE] = "";
            for (u32_t i = 0; i < dwLengthReqidCode; i++)
                byReqidStatus[i] = *(pbyFindReqid + i + dwLengthReqid);
            if (strcmp(byReqidSet, byReqidStatus) != 0)
                dwCountErrorNews++;
        }

        pbyCheckEnd = strstr(pbyCheckEnd + 1, byEnd);
    }
    printf("\nSo ban tin loi: %d\n", dwCountErrorNews);
}

void_t task6()
{
    u32_t dwSumTimeDelay = 0;
    u32_t dwCountCorrectNews = 0;
    u8_t byEnd[MAX_LENGTH_FILE] = "";
    byEnd[0] = 10;
    u8_p pbyCheckEnd = g_fileStr;

    u8_t byMinuteSet[MAX_LENGTH_FILE] = "";
    u8_t byMinuteStatus[MAX_LENGTH_FILE] = "";
    u8_t bySecondSet[MAX_LENGTH_FILE] = "";
    u8_t bySecondStatus[MAX_LENGTH_FILE] = "";

    u8_t byReqidSet[MAX_LENGTH_FILE] = "";
    u8_t byReqidStatus[MAX_LENGTH_FILE] = "";
    while (pbyCheckEnd != NULL)
    {
        u8_p pbyFindMinute = strstr(pbyCheckEnd, ":");

        // xu ly Time
        u8_p pbyFindSecond = strstr(pbyFindMinute + 1, ":");
        u8_p pbyFindEndTime = strstr(pbyFindSecond + 1, "]");
        u8_t byDelayMinute[MAX_LENGTH_FILE] = "";
        u8_t byDelaySecond[MAX_LENGTH_FILE] = "";
        u32_t dwLengthMinute = pbyFindSecond - pbyFindMinute - 1;
        for (u32_t i = 0; i < dwLengthMinute; i++)
            byDelayMinute[i] = *(pbyFindMinute + i + 1);
        u32_t dwLengthSecond = pbyFindEndTime - pbyFindSecond - 1;
        for (u32_t i = 0; i < dwLengthSecond; i++)
            byDelaySecond[i] = *(pbyFindSecond + i + 1);

        // FindDirect
        u8_p pbyFindDirect = strstr(pbyCheckEnd, "\"cmd\":");
        u32_t dwLengthDirect = strlen("\"cmd\":");
        u8_p pbyEndDirect = strstr(pbyCheckEnd, ",");
        u8_t byDirect[MAX_LENGTH_FILE] = "";
        for (u32_t i = 0; i < pbyEndDirect - pbyFindDirect - dwLengthDirect; i++)
            byDirect[i] = *(pbyFindDirect + i + dwLengthDirect);

        // FindCorrectNews
        u8_p pbyFindReqid = strstr(pbyCheckEnd, "\"reqid\": \"");
        u32_t dwLengthReqid = strlen("\"reqid\": \"");
        u8_p pbyFindReqidEnd = strstr(pbyFindReqid + dwLengthReqid, "\"");
        u32_t dwLengthReqidCode = pbyFindReqidEnd - pbyFindReqid - dwLengthReqid;
        if (strcmp(byDirect, "\"set\"") == 0)
        {
            byReqidSet[MAX_LENGTH_FILE] = "";
            for (u32_t i = 0; i < dwLengthReqidCode; i++)
                byReqidSet[i] = *(pbyFindReqid + i + dwLengthReqid);
        }
        else
        {
            byReqidStatus[MAX_LENGTH_FILE] = "";
            for (u32_t i = 0; i < dwLengthReqidCode; i++)
                byReqidStatus[i] = *(pbyFindReqid + i + dwLengthReqid);
            if (strcmp(byReqidSet, byReqidStatus) != 0)
            {
                pbyCheckEnd = strstr(pbyCheckEnd + 1, byEnd);
                continue;
            }
            else
                dwCountCorrectNews++;
        }

        // Xu ly Direct
        if (strcmp(byDirect, "\"set\"") == 0)
        {
            byMinuteSet[MAX_LENGTH_FILE] = "";
            bySecondSet[MAX_LENGTH_FILE] = "";
            for (u32_t k = 0; k < dwLengthMinute; k++)
                byMinuteSet[k] = *(byDelayMinute + k);
            u32_t dwLengthSecondSet = 0;
            for (u32_t k = 0; k < dwLengthSecond; k++)
                if (*(byDelaySecond + k) != '.')
                    bySecondSet[dwLengthSecondSet++] = *(byDelaySecond + k);
            // printf("Set: %s, %s\n",byMinuteSet,bySecondSet);
        }
        else
        {
            byMinuteStatus[MAX_LENGTH_FILE] = "";
            bySecondStatus[MAX_LENGTH_FILE] = "";
            for (u32_t k = 0; k < dwLengthMinute; k++)
                byMinuteStatus[k] = *(byDelayMinute + k);
            u32_t dwLengthSecondStatus = 0;
            for (u32_t k = 0; k < dwLengthSecond; k++)
                if (*(byDelaySecond + k) != '.')
                    bySecondStatus[dwLengthSecondStatus++] = *(byDelaySecond + k);
            u32_t dwTimeDelay = (stringToNum(byMinuteStatus) - stringToNum(byMinuteSet)) * 60 * 1000 + (stringToNum(bySecondStatus) - stringToNum(bySecondSet));
            dwSumTimeDelay += dwTimeDelay;
        }

        pbyCheckEnd = strstr(pbyCheckEnd + 1, byEnd);
    }
    u32_t dwAveTimeDelay = dwSumTimeDelay / dwCountCorrectNews;
    printf("Do tre trung binh la: %d Millisecond\n", dwAveTimeDelay);
}
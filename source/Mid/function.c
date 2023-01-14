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
 * File name: function.c
 *
 * Description: This code is used to perform functions for task process file log.txt
 *
 * Author: HoangNV
 *
 * Last Changed By:  $Author: HoangNV $
 * Revision:         $Revision: $
 * Last Changed:     $Date: $Jan 9, 2023
 *
 * Code sample:
 ******************************************************************************/
/******************************************************************************/
/*                              INCLUDE FILES                                 */
#include <stdio.h>
#include "../utils/typedefs.h"
#include <string.h>
#include "function.h"
/******************************************************************************/

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

/******************************************************************************/
/*                              EXPORTED DATA                                 */
extern u8_t g_fileStr[MAX_LENGTH_FILE];
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/**
 * @func count
 * @brief Dem so ban tin trong file
 * @param [pibFileLog] : con tro doc du lieu file
 * @retval i32_t
 */
static i32_t count(u8_p pibFileLog)
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

/**
 * @func pow10
 * @brief Tinh luy thua bac i cua 10
 * @param [dwDegree] : bac luy thua
 * @retval u32_t
 */
static u32_t pow10(u32_t dwDegree)
{
    if (dwDegree == 0)
        return 1;
    u32_t dwResult = 1;
    for (u32_t k = 1; k <= dwDegree; k++)
        dwResult *= 10;
    return dwResult;
}
/**
 * @func stringToNum
 * @brief Chuyen do chuoi sang so
 * @param [byStr[MAX_LENGTH_STRING_NUM]] : chuoi dung de chuyen sang so
 * @retval u32_t
 */
static u32_t stringToNum(u8_t byStr[MAX_LENGTH_STRING_NUM])
{
    u32_t dwResult = 0;
    u32_t dwLengthStr = strlen(byStr);
    u32_t dwChuSo;
    for (u32_t i = 0; i < dwLengthStr; i++)
    {
        dwChuSo = byStr[dwLengthStr - i - 1] - 48;
        dwResult += dwChuSo * pow10(i);
    }
    return dwResult;
}

/**
 * @func findDirect
 * @brief tinh thoi gian delay trong lich su file log dua theo yeu cau
 * @param [pbyCheckEnd] : con tro kiem tra ket thuc file
 * @param [byDirect[MAX_LENGTH_DIRECT_NEWS]]: luu chuoi Direct
 * @retval void_t
 */
static void_t findDirect(u8_p pbyCheckEnd, u8_t byDirect[MAX_LENGTH_DIRECT_NEWS])
{
    u8_p pbyFindDirect = strstr(pbyCheckEnd, "\"cmd\":");
    u32_t dwLengthDirect = strlen("\"cmd\":");
    u8_p pbyEndDirect = strstr(pbyCheckEnd, ",");
    for (u32_t i = 0; i < pbyEndDirect - pbyFindDirect - dwLengthDirect; i++)
        byDirect[i] = *(pbyFindDirect + i + dwLengthDirect);
}

/**
 * @func checkErrorNews
 * @brief lay reqid cua set va status luu vao chuoi de kiem tra ban tin co loi hay khong
 * @param [pbyCheckEnd] : con tro kiem tra ket thuc file
 * @param [byDirect[MAX_LENGTH_DIRECT_NEWS]]: luu chuoi Direct
 * @param [byReqidSet[MAX_LENGTH_REQID]]: luu chuoi Reqid cua ban tin "set"
 * @param [byReqidStatus[MAX_LENGTH_REQID]]: luu chuoi Reqid cua ban tin "status"
 * @param [pdwCountErrorNews]: con tro dem so ban tin loi
 * @param [pdwCountCorrectNews]: con tro dem so ban tin dung
 * @retval u8_t
 */
static u8_t checkErrorNews(u8_p pbyCheckEnd, u8_t byDirect[MAX_LENGTH_DIRECT_NEWS], u8_t byReqidSet[MAX_LENGTH_REQID], u8_t byReqidStatus[MAX_LENGTH_REQID], u32_p pdwCountErrorNews, u32_p pdwCountCorrectNews)
{
    u8_p pbyFindReqid = strstr(pbyCheckEnd, "\"reqid\": \"");
    u32_t dwLengthReqid = strlen("\"reqid\": \"");
    u8_p pbyFindReqidEnd = strstr(pbyFindReqid + dwLengthReqid, "\"");
    u32_t dwLengthReqidCode = pbyFindReqidEnd - pbyFindReqid - dwLengthReqid;
    if (strcmp(byDirect, "\"set\"") == 0)
    {
        byReqidSet[MAX_LENGTH_REQID] = "";
        for (u32_t i = 0; i < dwLengthReqidCode; i++)
            byReqidSet[i] = *(pbyFindReqid + i + dwLengthReqid);
    }
    else
    {
        byReqidStatus[MAX_LENGTH_REQID] = "";
        for (u32_t i = 0; i < dwLengthReqidCode; i++)
            byReqidStatus[i] = *(pbyFindReqid + i + dwLengthReqid);
        if (strcmp(byReqidSet, byReqidStatus) != 0)
        {
            *pdwCountErrorNews = *pdwCountErrorNews + 1;
            return 0;
        }
        else
        {
            *pdwCountCorrectNews = *pdwCountCorrectNews + 1;
            return 1;
        }
    }
    return 2;
}
/**
 * @func processTimeDelay
 * @brief tinh thoi gian delay trong lich su file log dua theo yeu cau
 * @param [dwNameTask] : xu ly theo ten yeu cau task
 * @retval void_t
 */
static void_t processTimeDelay(u32_t dwNameTask, u32_p pdwResult)
{
    u32_t dwCountCorrectNews = 0;
    u32_t dwCountErrorNews = 0;
    u8_t byEnd[2] = "";
    byEnd[0] = 10; // dau enter
    u8_p pbyCheckEnd = g_fileStr;

    u8_t byMinuteSet[MAX_LENGTH_MINUTE] = "";
    u8_t byMinuteStatus[MAX_LENGTH_MINUTE] = "";
    u8_t bySecondSet[MAX_LENGTH_SECOND] = "";
    u8_t bySecondStatus[MAX_LENGTH_SECOND] = "";

    u8_t byReqidSet[MAX_LENGTH_REQID] = "";
    u8_t byReqidStatus[MAX_LENGTH_REQID] = "";
    while (pbyCheckEnd != NULL)
    {
        // xu ly time
        u8_p pbyFindMinute = strstr(pbyCheckEnd, ":");
        u8_p pbyFindSecond = strstr(pbyFindMinute + 1, ":");
        u8_p pbyFindEndTime = strstr(pbyFindSecond + 1, "]");
        u8_t byDelayMinute[MAX_LENGTH_MINUTE] = "";
        u8_t byDelaySecond[MAX_LENGTH_SECOND] = "";

        u32_t dwLengthMinute = pbyFindSecond - pbyFindMinute - 1;
        for (u32_t i = 0; i < dwLengthMinute; i++)
            byDelayMinute[i] = *(pbyFindMinute + i + 1);
        u32_t dwLengthSecond = pbyFindEndTime - pbyFindSecond - 1;
        for (u32_t i = 0; i < dwLengthSecond; i++)
            byDelaySecond[i] = *(pbyFindSecond + i + 1);

        u8_t byDirect[MAX_LENGTH_DIRECT_NEWS] = "";
        findDirect(pbyCheckEnd, byDirect);
        u8_t byCheck = checkErrorNews(pbyCheckEnd, byDirect, byReqidSet, byReqidStatus, &dwCountErrorNews, &dwCountCorrectNews);
        if (byCheck == 0) // neu ban tin loi thi khong tinh vao delaytime
        {
            pbyCheckEnd = strstr(pbyCheckEnd + 1, byEnd);
            continue;
        }
        // Xu ly Direct
        if (strcmp(byDirect, "\"set\"") == 0)
        {
            byMinuteSet[MAX_LENGTH_MINUTE] = "";
            bySecondSet[MAX_LENGTH_SECOND] = "";
            for (u32_t k = 0; k < dwLengthMinute; k++)
                byMinuteSet[k] = *(byDelayMinute + k);
            u32_t dwLengthSecondSet = 0;
            for (u32_t k = 0; k < dwLengthSecond; k++)
                if (*(byDelaySecond + k) != '.')
                    bySecondSet[dwLengthSecondSet++] = *(byDelaySecond + k);
        }
        else
        {
            byMinuteStatus[MAX_LENGTH_MINUTE] = "";
            bySecondStatus[MAX_LENGTH_SECOND] = "";
            for (u32_t k = 0; k < dwLengthMinute; k++)
                byMinuteStatus[k] = *(byDelayMinute + k);
            u32_t dwLengthSecondStatus = 0;
            for (u32_t k = 0; k < dwLengthSecond; k++)
                if (*(byDelaySecond + k) != '.')
                    bySecondStatus[dwLengthSecondStatus++] = *(byDelaySecond + k);
            u32_t dwTimeDelay = (stringToNum(byMinuteStatus) - stringToNum(byMinuteSet)) * CONVERT_MINUTE_TO_SECOND * CONVERT_SECOND_TO_MILLISECOND + (stringToNum(bySecondStatus) - stringToNum(bySecondSet));
            if (dwNameTask == TINH_MAX_DELAY_TIME)
            {
                if (dwTimeDelay > *pdwResult)
                    *pdwResult = dwTimeDelay;
            }
            else if (dwNameTask == TINH_TRUNG_BINH_DELAY_TIME)
            {
                *pdwResult += dwTimeDelay;
            }
        }
        pbyCheckEnd = strstr(pbyCheckEnd + 1, byEnd);
    }
    if (dwNameTask == TINH_TRUNG_BINH_DELAY_TIME)
    {
        *pdwResult = *pdwResult / dwCountCorrectNews;
    }
}

/**
 * @func getNews
 * @brief Duyet den 1 ban tin va lay ban tin ra 1 chuoi
 * @param [pbyCheckEnd] : con tro kiem tra ket thuc ban tin
 * @param [byNews[MAX_LENGTH_FILE]] :chuoi luu ban tin
 * @retval void_t
 */
static void_t getNews(u8_p pbyCheckEnd, u8_t byNews[MAX_LENGTH_FILE])
{
    u32_t dwNewsIndex = 0;
    u8_p pbyStart = NULL;
    u8_p pbyEnd = NULL;
    u8_t byEnd[2] = "";
    byEnd[0] = 10;
    pbyStart = strstr(pbyCheckEnd, "[INFO]");
    pbyEnd = strstr(pbyCheckEnd + 1, byEnd);
    u8_p pibIndexNews = NULL;
    if (pbyStart - pbyEnd < 0)
        for (pibIndexNews = pbyStart; pibIndexNews != pbyEnd + 1; pibIndexNews++)
        {
            byNews[dwNewsIndex++] = *pibIndexNews;
        }
}
/******************************************************************************/

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/**
 * @func fileToStr
 * @brief Doc du lieu file ben ngoai vao chuoi thong qua con tro
 *
 * @param [pibStr] : con tro doc du lieu file
 * @retval i32_t
 */
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

/**
 * @func getCountSentNews
 * @brief thuc hien yeu cau 1: dem so ban tin gui di
 * @param [] :
 * @retval void_t
 */
void_t getCountSentNews()
{
    u32_t dwCount = count(g_fileStr);
    printf("\nSo luong ban tin la: %d", dwCount);
}

/**
 * @func getCountSentNewsWithInputCode
 * @brief thuc hien yeu cau 2: dem so ban tin voi ma nhap tu user
 * @param [] :
 * @retval void_t
 */
void_t getCountSentNewsWithInputCode()
{
    u8_t byAddressNWK[MAX_LENGTH_NWK] = "";
    printf("\nNhap dia chi nwk cua thiet bi: %");
    scanf("%s", byAddressNWK);
    printf("\n");
    u8_p pbyCheckEnd = g_fileStr;
    u8_t byEnd[2] = "";
    byEnd[0] = 10; // dau enter
    u32_t dwCountNews = 0;
    while (pbyCheckEnd != NULL)
    {
        u8_t byNews[MAX_LENGTH_FILE] = "";
        getNews(pbyCheckEnd, byNews);
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
/**
 * @func getCountSwitch
 * @brief thuc hien yeu cau 3: dem so cong tac tren lich su file log
 * @param [] :
 * @retval void_t
 */
void_t getCountSwitch()
{
    u8_t pbyBufferNetWork[20][MAX_LENGTH_NETWORK];
    u8_t pbyBufferEndPoint[20][MAX_LENGTH_ENDPOINT];
    u32_t dwNumberBufferNetWork = 0;
    u8_p pbyCheckEnd = g_fileStr;
    while (pbyCheckEnd != NULL)
    {
        u8_t byNews[MAX_LENGTH_FILE] = "";
        u8_t byEnd[2] = "";
        byEnd[0] = 10;
        getNews(pbyCheckEnd, byNews);

        // luu 2 chuoi NetWork va EndPoint
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
        u8_t byResultNetWork[MAX_LENGTH_NETWORK] = "";
        while (*(pbyNetWork + dwLengthNetWork) != ':')
        {
            byResultNetWork[dwLengthNetWork++] = *(pbyNetWork + dwLengthNetWork);
        }
        u8_p pbyEndPoint = NULL;
        pbyEndPoint = strstr(pbyNetWork + dwLengthNetWork, "-");
        u32_t dwLengthEndPoint = 0;
        u8_t byResultEndPoint[MAX_LENGTH_ENDPOINT] = "";
        while (*(pbyEndPoint + dwLengthEndPoint) != '"')
            byResultEndPoint[dwLengthEndPoint++] = *(pbyEndPoint + dwLengthEndPoint);

        // kiem tra da ton tai chuoi NetWork dang duyet den chua
        u32_t dwCheckString = 0;
        for (u32_t i = 1; i <= dwNumberBufferNetWork; i++)
            if (strcmp(byResultNetWork, pbyBufferNetWork[i]) == 0)
            {
                dwCheckString = 1;
                break;
            }

        // them chuoi dang duyet vao mang chua chuoi
        if (dwCheckString == 0)
        {
            ++dwNumberBufferNetWork;
            for (u32_t j = 0; j < strlen(byResultEndPoint); j++)
                pbyBufferEndPoint[dwNumberBufferNetWork][j] = byResultEndPoint[j];
            for (u32_t j = 0; j < strlen(byResultNetWork); j++)
                pbyBufferNetWork[dwNumberBufferNetWork][j] = byResultNetWork[j];
        }
        pbyCheckEnd = strstr(pbyCheckEnd + 1, byEnd);
    }
    for (u32_t i = 1; i <= dwNumberBufferNetWork; i++)
        printf("thiet bi %d co dia chi la : NWK %s, ENDPOINT %s\n", i, pbyBufferNetWork[i], pbyBufferEndPoint[i]);
}

/**
 * @func getCountErrorNews
 * @brief thuc hien yeu cau 4: dem so ban tin loi tren lich su file log
 * @param [] :
 * @retval void_t
 */
void_t getCountErrorNews()
{
    u32_t dwCountErrorNews = 0;
    u32_t dwCountCorrectNews = 0;
    u8_p pbyCheckEnd = g_fileStr;
    u8_t byEnd[2] = "";
    byEnd[0] = 10; // dau enter
    u8_t byReqidSet[MAX_LENGTH_REQID] = "";
    u8_t byReqidStatus[MAX_LENGTH_REQID] = "";

    while (pbyCheckEnd != NULL)
    {
        u8_t byDirect[MAX_LENGTH_DIRECT_NEWS] = "";
        findDirect(pbyCheckEnd, byDirect);
        checkErrorNews(pbyCheckEnd, byDirect, byReqidSet, byReqidStatus, &dwCountErrorNews, &dwCountCorrectNews);
        pbyCheckEnd = strstr(pbyCheckEnd + 1, byEnd);
    }
    printf("\nSo ban tin loi: %d\n", dwCountErrorNews);
}

/**
 * @func getAverageTimeDelay
 * @brief thuc hien yeu cau 6: tinh thoi gian delay trung binh trong lich su file log
 * @param [] :
 * @retval void_t
 */
void_t getAverageTimeDelay()
{
    u32_t dwAveTimeDelay = 0;
    processTimeDelay(TINH_TRUNG_BINH_DELAY_TIME, &dwAveTimeDelay);
    printf("Do tre trung binh la: %d Millisecond\n", dwAveTimeDelay);
}

/**
 * @func getMaxDelayTime
 * @brief thuc hien yeu cau 5: tinh thoi gian delay lon nhat tren lich su file log
 * @param [] :
 * @retval void_t
 */
void_t getMaxDelayTime()
{
    u32_t dwMaxDelay;
    processTimeDelay(TINH_MAX_DELAY_TIME, &dwMaxDelay);
    printf("\nDo tre lon nhat la: %d Millisecond\n", dwMaxDelay);
}
/******************************************************************************/

/******************************************************************************/
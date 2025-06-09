/*
 *  conversions.c
 */

#include "libdlt860_platform_includes.h"
#include "conversions.h"

#include <time.h>

#if defined TARGET
#if (TARGET == UCLINUX-WAGO)
time_t timegm (struct tm *tm)
{
    time_t ret;
    char *tz;

    tz = getenv ("TZ");
    setenv ("TZ", "", 1);
    tzset ();
    ret = mktime (tm);
    if (tz)
        setenv ("TZ", tz, 1);
    else
        unsetenv ("TZ");
    tzset ();
    return ret;
}

#endif
#endif

#ifdef _WIN32

#ifndef _MSC_VER
/* Algorithm: http://howardhinnant.github.io/date_algorithms.html */
static int 
days_from_civil(int y, int m, int d)
{
	y -= m <= 2;
	int era = y / 400;
	int yoe = y - era * 400;                                   /* [0, 399] */
	int doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;  /* [0, 365] */
	int doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;           /* [0, 146096] */
	return era * 146097 + doe - 719468;
}

/* from https://stackoverflow.com/questions/16647819/timegm-cross-platform */
time_t 
timegm(struct tm const* t) /* does not modify broken-down time */
{
	int year = t->tm_year + 1900;
	int month = t->tm_mon;          /* 0-11 */
	if (month > 11)
	{
		year += month / 12;
		month %= 12;
	}
	else if (month < 0)
	{
		int years_diff = (11 - month) / 12;
		year -= years_diff;
		month += 12 * years_diff;
	}
	int days_since_1970 = days_from_civil(year, month + 1, t->tm_mday);

	return 60 * (60 * (24L * days_since_1970 + t->tm_hour) + t->tm_min) + t->tm_sec;
}
#else
#define timegm _mkgmtime
#endif

#if defined(__MINGW32__)

static inline /* assuming gmtime is thread safe in windows! */
struct tm* gmtime_r(const time_t* timep, struct tm* result)
{
   struct tm* t;

   t = gmtime(timep);

   if (t != NULL)
       memcpy(result, t, sizeof (struct tm));

   return result;
}

#else

#if defined(_MSC_VER)

static inline
struct tm* gmtime_r(const time_t* timep, struct tm* result)
{
    gmtime_s(result, timep);

    return result;
}

#else
#error "No gmtime_r available for platform!"
#endif
#endif
#endif

void Conversions_intToStringBuffer(int intValue, int numberOfDigits, uint8_t* buffer)
{
    int digitBase = 1;

    int i = 1;

    while (i < numberOfDigits) {
        digitBase = digitBase * 10;
        i++;
    }

    int remainder = intValue;

    for (i = 0; i < numberOfDigits; i++) {
        int digit = remainder / digitBase;

        buffer[i] = (uint8_t) (digit + 48);

        remainder = remainder % digitBase;

        digitBase = digitBase / 10;
    }

    buffer[i] = 0;
}

void Conversions_msTimeToGeneralizedTime(uint64_t msTime, uint8_t* buffer)
{
    int msPart = (msTime % 1000);

    time_t unixTime = (msTime / 1000);

    struct tm tmTime;

    gmtime_r(&unixTime, &tmTime);

    Conversions_intToStringBuffer(tmTime.tm_year + 1900, 4, buffer);

    Conversions_intToStringBuffer(tmTime.tm_mon + 1, 2, buffer + 4);
    Conversions_intToStringBuffer(tmTime.tm_mday, 2, buffer + 6);
    Conversions_intToStringBuffer(tmTime.tm_hour, 2, buffer + 8);
    Conversions_intToStringBuffer(tmTime.tm_min, 2, buffer + 10);
    Conversions_intToStringBuffer(tmTime.tm_sec, 2, buffer + 12);

    buffer[14] = '.';

    Conversions_intToStringBuffer(msPart, 3, buffer + 15);

    buffer[18] = 'Z';

    buffer[19] = 0;
}

static int getSecondsOffset(const char* offsetString)
{
    int hourOffset = GSP::StringUtils_digitsToInt(offsetString, 2);

    if (hourOffset < 0)
        return -1;

    int minOffset = GSP::StringUtils_digitsToInt(offsetString + 2, 2);

    if (minOffset < 0)
        return -1;

    int secondsOffset = (hourOffset * (60 * 60)) + (minOffset * 60);

    return secondsOffset;
}

uint64_t Conversions_generalizedTimeToMsTime(const char* gtString)
{
    int gtStringLen = (int) strlen(gtString);

    if (gtStringLen < 14) return -1;

    int year = GSP::StringUtils_digitsToInt(gtString, 4);

    if (year < 0) return -1;

    int month = GSP::StringUtils_digitsToInt(gtString + 4, 2);

    if (month < 0) return -1;

    int day = GSP::StringUtils_digitsToInt(gtString + 6, 2);

    if (day < 0) return -1;

    int hour = GSP::StringUtils_digitsToInt(gtString + 8, 2);

    if (hour < 0) return -1;

    int min = GSP::StringUtils_digitsToInt(gtString + 10, 2);

    if (min < 0) return -1;

    int seconds = GSP::StringUtils_digitsToInt(gtString + 12, 2);
    if (seconds < 0) return -1;

    struct tm tmTime;
    tmTime.tm_year = year - 1900;
    tmTime.tm_mon = month - 1;
    tmTime.tm_mday = day;
    tmTime.tm_hour = hour;
    tmTime.tm_min = min;
    tmTime.tm_sec = seconds;

    int msOffset = 0;

    const char* parsePos = gtString + 14;

    /* parse optional fraction of second field */
    if (*(parsePos) == '.') {
        parsePos++;
        const char* fractionOfSecondStart = parsePos;

        int fractionOfSecondLen = 0;

        int secondValue = 1;

        while (GSP::StringUtils_isDigit(fractionOfSecondStart[fractionOfSecondLen])) {
            fractionOfSecondLen++;

            secondValue = secondValue * 10;
        }

        if (fractionOfSecondLen > 0) {
            int fractionOfSecond = GSP::StringUtils_digitsToInt(fractionOfSecondStart, fractionOfSecondLen);
            msOffset = (fractionOfSecond * 1000) / secondValue;
        }

        parsePos += fractionOfSecondLen;
    }


    time_t t = 0;

    switch (*parsePos) {
    case 0: /* treat time as localtime */
        t = mktime(&tmTime);
        break;
    case 'Z': /* treat time as GMT(UTC) time */
        t = timegm(&tmTime);
        break;
    case '+': /* subtract offset */
        {
            t = timegm(&tmTime);
            int secondsOffset = getSecondsOffset(parsePos + 1);
            t = t - secondsOffset;
        }
        break;
    case '-': /* add offset */
        {
            t = timegm(&tmTime);
            int secondsOffset = getSecondsOffset(parsePos + 1);
            t = t + secondsOffset;
        }
        break;
    default:
        return -1;
    }

    uint64_t msTime = (uint64_t) t * 1000LL;

    msTime += msOffset;

    return msTime;
}

void memcpyReverseByteOrder(uint8_t* dst, const uint8_t* src, int size)
{
    int i = 0;
    for (i = 0; i < size; i++) {
        dst[i] = src[size - i - 1];
    }
}

uint64_t convertUtcTimeToMs(UtcTime_t &utcTime)
{
    uint32_t timeval32;
    const uint8_t* valueArray = utcTime.buf;

#if (ORDER_LITTLE_ENDIAN == 1)
    memcpyReverseByteOrder((uint8_t*) &timeval32, valueArray, 4);
#else
    memcpy((uint8_t*) &timeval32, valueArray, 4);
#endif

    uint32_t fractionOfSecond = 0;

    fractionOfSecond = (valueArray[4] << 16);
    fractionOfSecond += (valueArray[5] << 8);
    fractionOfSecond += (valueArray[6]);

    uint32_t remainder = fractionOfSecond / 16777;
    uint64_t msVal = (timeval32 * 1000LL) + remainder;

    return msVal;
}

char* Reference_GetReportNumber(const char* brcbReference){
    // 异常判断
    if(brcbReference == nullptr){
        return nullptr;
    }

    int refsSize = strlen(brcbReference);
    if(refsSize < 2){
        return nullptr;
    }

    // 获取最后两位的实例号码
    char* reportNumber = (char*)GspMemory_calloc(2, sizeof(char));
    memcpy(reportNumber, brcbReference+refsSize-2, 2);
    return reportNumber;
}

URCB_t* URCB_Clone(URCB_t* paramOther){
    URCB_t* urcbPtrBlk = (URCB_t*)GspMemory_calloc(1, sizeof(URCB_t));
    // rptid
    OCTET_STRING_fromBuf(&urcbPtrBlk->rptID, (const char *)paramOther->rptID.buf, paramOther->rptID.size);
    // rptEna
    urcbPtrBlk->rptEna = paramOther->rptEna;
    // datSet
    OCTET_STRING_fromBuf(&urcbPtrBlk->datSet, (const char *)paramOther->datSet.buf, paramOther->datSet.size);
    // confRev
    urcbPtrBlk->confRev = paramOther->confRev;
    // optFlds
    BitString_Update(urcbPtrBlk->optFlds, &paramOther->optFlds);
    // bufTm
    urcbPtrBlk->bufTm = paramOther->bufTm;
    // sqNum
    urcbPtrBlk->sqNum = paramOther->sqNum;
    // trgOps
    BitString_Update(urcbPtrBlk->trgOps, &paramOther->trgOps);
    // intgPd
    urcbPtrBlk->intgPd = paramOther->intgPd;
    // gi
    urcbPtrBlk->gi = paramOther->gi;
    // resv
    urcbPtrBlk->resv = paramOther->resv;
    return urcbPtrBlk;
}

BRCB_t* BRCB_Clone(BRCB_t* paramOther){
    BRCB_t* brcbPtrBlk = (BRCB_t*)GspMemory_calloc(1, sizeof(BRCB_t));
    // rptid 
    OCTET_STRING_fromBuf(&brcbPtrBlk->rptID, (const char *)paramOther->rptID.buf, paramOther->rptID.size);
    // rptEna
    brcbPtrBlk->rptEna = paramOther->rptEna;
    // datSet
    OCTET_STRING_fromBuf(&brcbPtrBlk->datSet, (const char *)paramOther->datSet.buf, paramOther->datSet.size);
    // confRev
    brcbPtrBlk->confRev = paramOther->confRev;
    // optFlds
    BitString_Update(brcbPtrBlk->optFlds, &paramOther->optFlds);
    // bufTm
    brcbPtrBlk->bufTm = paramOther->bufTm;
    // sqNum
    brcbPtrBlk->sqNum = paramOther->sqNum;
    // trgOps
    BitString_Update(brcbPtrBlk->trgOps, &paramOther->trgOps);
    // intgPd
    brcbPtrBlk->intgPd = paramOther->intgPd;
    // gi
    brcbPtrBlk->gi = paramOther->gi;
    // purgeBuf 
    brcbPtrBlk->purgeBuf = paramOther->purgeBuf;
    // EntryID_t
    OCTET_STRING_fromBuf(&brcbPtrBlk->entryID, (const char *)paramOther->entryID.buf, paramOther->entryID.size);
    // timeOfEntry
    OCTET_STRING_fromBuf(&brcbPtrBlk->timeOfEntry, (const char *)paramOther->timeOfEntry.buf, paramOther->timeOfEntry.size);
    // resvTms（暂不处理）
    // owner（暂不处理）
    return brcbPtrBlk;
}

BIT_STRING_s* BitString_Clone(BIT_STRING_t* paramOther){
    BIT_STRING_t* retObj = (BIT_STRING_t*)GspMemory_calloc(1, sizeof(BIT_STRING_t));
    retObj->size = paramOther->size;
    retObj->bits_unused = paramOther->bits_unused;
    retObj->buf = (uint8_t*)GspMemory_calloc(paramOther->size, sizeof(uint8_t));
    memcpy(retObj->buf, paramOther->buf, retObj->size);
    return retObj;
}

bool BitString_Update(BIT_STRING_t*& paramTarget, BIT_STRING_t* paramOther){
    if(paramTarget == nullptr){
        paramTarget = (BIT_STRING_t*)GspMemory_calloc(1, sizeof(BIT_STRING_t));
    }
    (paramTarget)->size = paramOther->size;
    (paramTarget)->bits_unused = paramOther->bits_unused;
    if((paramTarget)->buf == nullptr){
        (paramTarget)->buf = (uint8_t*)GspMemory_calloc((paramTarget)->size, sizeof(uint8_t));
    }
    memcpy((paramTarget)->buf, paramOther->buf, paramOther->size);
    return true;
}

bool BitString_Update(BIT_STRING_t &paramTarget, BIT_STRING_t* paramOther){
    paramTarget.size = paramOther->size;
    paramTarget.bits_unused = paramOther->bits_unused;
    if(paramTarget.buf == nullptr){
        paramTarget.buf = (uint8_t*)GspMemory_calloc((paramTarget).size, sizeof(uint8_t));
    }
    memcpy(paramTarget.buf, paramOther->buf, paramOther->size);
    return true;
}

void BitString_Printf(BIT_STRING_t* paramOther){
    int vaildSize = BitString_getBitSize(paramOther);
    printf("BitString 打印测试:");
    for(int i=0; i<vaildSize; ++i){
        bool value = BitString_getBitValue(paramOther, i);
        printf("%d", value);
    }
    printf("\n");
}

int BitString_getBitSize(BIT_STRING_t* paramOther){
    return paramOther->size * 8 - paramOther->bits_unused;
}

bool BitString_getBitValue(BIT_STRING_t* paramOther, int bitPos){
    int bitSize = BitString_getBitSize(paramOther);

    if (bitPos < bitSize) {
        int bytePos = bitPos / 8;
        int bitPosInByte = 7 - (bitPos % 8);
        int bitMask = (1 << bitPosInByte);

        if ((paramOther->buf[bytePos] & bitMask) > 0){
            return true;
        } else {
            return false;
        }

    } else {
        return false;
    }
}

bool BitString_setBitValue(BIT_STRING_t* paramOther, int bitPos, bool bitValue)
{
    int bitSize = BitString_getBitSize(paramOther);
    if (bitPos < bitSize) {
        int bytePos = bitPos / 8;
        int bitPosInByte = 7 - (bitPos % 8);
        int bitMask = (1 << bitPosInByte);

        if (bitValue){
            paramOther->buf[bytePos] |= bitMask;
        } else {
            paramOther->buf[bytePos] &= (~bitMask);
        }
    }
    return true;
}

GSPRCB BRCB_convert(BRCB_t *paramOther)
{
    GSPRCB brcbPtrBlk = (GSPRCB)GspMemory_calloc(1, sizeof(sGSPRCB));
    // rptid 1
    brcbPtrBlk->rptID = OCTET_STRING_new_fromBuf(&asn_DEF_VisibleString129, (const char*)paramOther->rptID.buf, paramOther->rptID.size);

    // rptEna
    brcbPtrBlk->rptEna = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
    *brcbPtrBlk->rptEna = paramOther->rptEna;

    // datSet 1
    brcbPtrBlk->datSet = OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, (const char*)paramOther->datSet.buf, paramOther->datSet.size);

    // optFlds 1
    BitString_Update(brcbPtrBlk->optFlds, &paramOther->optFlds);

    // bufTm
    brcbPtrBlk->bufTm = (INT32U_t*)GspMemory_calloc(1, sizeof(INT32U_t));
    *brcbPtrBlk->bufTm = paramOther->bufTm;

    // trgOps 1
    BitString_Update(brcbPtrBlk->trgOps, &paramOther->trgOps);

    // intgPd
    brcbPtrBlk->intgPd = (INT32U_t*)GspMemory_calloc(1, sizeof(INT32U_t));
    *brcbPtrBlk->intgPd = paramOther->intgPd;

    // gi
    brcbPtrBlk->gi = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
    *brcbPtrBlk->gi = paramOther->gi;

    // purgeBuf
    brcbPtrBlk->purgeBuf = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
    *brcbPtrBlk->purgeBuf = paramOther->purgeBuf;

    // EntryID_t 1
    brcbPtrBlk->entryID = OCTET_STRING_new_fromBuf(&asn_DEF_EntryID, (const char*)paramOther->rptID.buf, paramOther->rptID.size);

    // timeOfEntry(暂不处理)
    // sqNum(暂不处理)
    // confRev(暂不处理)
    // resvTms（暂不处理）
    // owner（暂不处理）
    return brcbPtrBlk;
}

void GRCB_Clean(GSPRCB paramother)
{
    if(!paramother){
        return;
    }
    if(paramother->gi){
        GspMemory_free(paramother->gi);
        paramother->gi = nullptr;
    }
    if(paramother->resv){
        GspMemory_free(paramother->resv);
        paramother->resv = nullptr;
    }
    if(paramother->bufTm){
        GspMemory_free(paramother->bufTm);
        paramother->bufTm = nullptr;
    }
    if(paramother->rptID){
        ASN_STRUCT_FREE(asn_DEF_VisibleString129, paramother->rptID);
        paramother->rptID = nullptr;
    }
    if(paramother->datSet){
        ASN_STRUCT_FREE(asn_DEF_ObjectReference, paramother->datSet);
        paramother->datSet = nullptr;
    }
    if(paramother->intgPd){
        GspMemory_free(paramother->intgPd);
        paramother->intgPd = nullptr;
    }
    if(paramother->rptEna){
        GspMemory_free(paramother->rptEna);
        paramother->rptEna = nullptr;
    }
    if(paramother->trgOps){
        ASN_STRUCT_FREE(asn_DEF_BIT_STRING, paramother->trgOps);
        paramother->trgOps = nullptr;
    }
    if(paramother->entryID){
        ASN_STRUCT_FREE(asn_DEF_EntryID, paramother->entryID);
        paramother->entryID = nullptr;
    }
    if(paramother->optFlds){
        ASN_STRUCT_FREE(asn_DEF_BIT_STRING, paramother->optFlds);
        paramother->optFlds = nullptr;
    }
    if(paramother->resvTms){
        GspMemory_free(paramother->resvTms);
        paramother->resvTms = nullptr;
    }
    if(paramother->purgeBuf){
        GspMemory_free(paramother->purgeBuf);
        paramother->purgeBuf = nullptr;
    }
    ASN_STRUCT_FREE(asn_DEF_ObjectReference, &paramother->reference);
}

void GRCB_Clean_Without_Reference(GSPRCB paramother)
{
    if(!paramother){
        return;
    }
    if(paramother->gi){
        GspMemory_free(paramother->gi);
        paramother->gi = nullptr;
    }
    if(paramother->resv){
        GspMemory_free(paramother->resv);
        paramother->resv = nullptr;
    }
    if(paramother->bufTm){
        GspMemory_free(paramother->bufTm);
        paramother->bufTm = nullptr;
    }
    if(paramother->rptID){
        ASN_STRUCT_FREE(asn_DEF_VisibleString129, paramother->rptID);
        paramother->rptID = nullptr;
    }
    if(paramother->datSet){
        ASN_STRUCT_FREE(asn_DEF_ObjectReference, paramother->datSet);
        paramother->datSet = nullptr;
    }
    if(paramother->intgPd){
        GspMemory_free(paramother->intgPd);
        paramother->intgPd = nullptr;
    }
    if(paramother->rptEna){
        GspMemory_free(paramother->rptEna);
        paramother->rptEna = nullptr;
    }
    if(paramother->trgOps){
        ASN_STRUCT_FREE(asn_DEF_BIT_STRING, paramother->trgOps);
        paramother->trgOps = nullptr;
    }
    if(paramother->entryID){
        ASN_STRUCT_FREE(asn_DEF_EntryID, paramother->entryID);
        paramother->entryID = nullptr;
    }
    if(paramother->optFlds){
        ASN_STRUCT_FREE(asn_DEF_BIT_STRING, paramother->optFlds);
        paramother->optFlds = nullptr;
    }
    if(paramother->resvTms){
        GspMemory_free(paramother->resvTms);
        paramother->resvTms = nullptr;
    }
    if(paramother->purgeBuf){
        GspMemory_free(paramother->purgeBuf);
        paramother->purgeBuf = nullptr;
    }
}

void GRCB_Clean_Without_SetReport(GSPRCB paramother){
    if(!paramother){
        return;
    }
    if(paramother->gi){
        GspMemory_free(paramother->gi);
        paramother->gi = nullptr;
    }
    if(paramother->resv){
        GspMemory_free(paramother->resv);
        paramother->resv = nullptr;
    }
    if(paramother->datSet){
        ASN_STRUCT_FREE(asn_DEF_ObjectReference, paramother->datSet);
        paramother->datSet = nullptr;
    }
    if(paramother->rptEna){
        GspMemory_free(paramother->rptEna);
        paramother->rptEna = nullptr;
    }
    if(paramother->entryID){
        ASN_STRUCT_FREE(asn_DEF_EntryID, paramother->entryID);
        paramother->entryID = nullptr;
    }
    if(paramother->intgPd){
        GspMemory_free(paramother->intgPd);
        paramother->intgPd = nullptr;
    }
    if(paramother->resvTms){
        GspMemory_free(paramother->resvTms);
        paramother->resvTms = nullptr;
    }
    if(paramother->purgeBuf){
        GspMemory_free(paramother->purgeBuf);
        paramother->purgeBuf = nullptr;
    }
}

GSPRCB URCB_convert(URCB_t *paramOther)
{
    GSPRCB brcbPtrBlk = (GSPRCB)GspMemory_calloc(1, sizeof(sGSPRCB));
    // rptid
    brcbPtrBlk->rptID = OCTET_STRING_new_fromBuf(&asn_DEF_VisibleString129, (const char*)paramOther->rptID.buf, paramOther->rptID.size);

    // rptEna
    brcbPtrBlk->rptEna = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
    *brcbPtrBlk->rptEna = paramOther->rptEna;

    // datSet
    brcbPtrBlk->datSet = OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, (const char*)paramOther->datSet.buf, paramOther->datSet.size);

    // optFlds
    BitString_Update(brcbPtrBlk->optFlds, &paramOther->optFlds);

    // bufTm
    brcbPtrBlk->bufTm = (INT32U_t*)GspMemory_calloc(1, sizeof(INT32U_t));
    *brcbPtrBlk->bufTm = paramOther->bufTm;

    // trgOps
    BitString_Update(brcbPtrBlk->trgOps, &paramOther->trgOps);

    // intgPd
    brcbPtrBlk->intgPd = (INT32U_t*)GspMemory_calloc(1, sizeof(INT32U_t));
    *brcbPtrBlk->intgPd = paramOther->intgPd;

    // gi
    brcbPtrBlk->gi = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
    *brcbPtrBlk->gi = paramOther->gi;

    // timeOfEntry(暂不处理)
    // sqNum(暂不处理)
    // confRev(暂不处理)
    // resvTms（暂不处理）
    // owner（暂不处理）
    return brcbPtrBlk;
}

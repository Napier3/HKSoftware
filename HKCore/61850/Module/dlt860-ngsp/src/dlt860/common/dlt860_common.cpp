/*
 * DLT860_common.c
 */

#include "dlt860_common.h"
#include "libdlt860_platform_includes.h"
#include "libdlt860_common_api.h"
#include "conversions.h"
#include "gsp_lib_memory.h"

using namespace GSP;

GspValidity GspQuality_getValidity(GspQuality* self)
{
    return (*self & 0x3);
}

void GspQuality_setValidity(GspQuality* self, GspValidity validity)
{
    *self = *self & (0xfffc);
    *self = *self | validity;
}

bool GspQuality_isFlagSet(GspQuality* self, int flag)
{
    if ((*self & flag) > 0)
        return true;
    else
        return false;
}

void GspQuality_setFlag(GspQuality* self, int flag)
{
    *self = *self | flag;
}

void GspQuality_unsetFlag(GspQuality* self, int flag)
{
    *self = *self & (~flag);
}

GspQuality GspQuality_fromMmsValue(const GspMmsValue* mmsValue)
{
    return (GspQuality) GspMmsValue_getBitStringAsInteger(mmsValue);
}

GspDbpos GspDbpos_fromMmsValue(const GspMmsValue* mmsValue)
{
    return (GspDbpos) GspMmsValue_getBitStringAsIntegerBigEndian(mmsValue);
}

GspMmsValue* GspDbpos_toMmsValue(GspMmsValue* mmsValue, GspDbpos dbpos)
{
    if (mmsValue == nullptr) {
        mmsValue = GspMmsValue_newBitString(2);
    }
    else {
        if (GspMmsValue_getType(mmsValue) != Data_PR_bit_string)
            return nullptr;

        if (GspMmsValue_getBitStringSize(mmsValue) != 2)
            return nullptr;
    }

    assert((int) dbpos >= 0);
    assert((int) dbpos < 4);

    GspMmsValue_setBitStringFromIntegerBigEndian(mmsValue, dbpos);

    return mmsValue;
}

char* GspFunctionalConstraint_toString(GspFunctionalConstraint fc) {
    char *fcDesc = new char[3];
    memset(fcDesc, 0, 3);
    switch (fc) {
    case DLT860_FC_ST:
        memcpy(fcDesc, "ST", 2);
        break;
    case DLT860_FC_MX:
        memcpy(fcDesc, "MX", 2);
        break;
    case DLT860_FC_SP:
        memcpy(fcDesc, "SP", 2);
        break;
    case DLT860_FC_SV:
        memcpy(fcDesc, "SV", 2);
        break;
    case DLT860_FC_CF:
        memcpy(fcDesc, "CF", 2);
        break;
    case DLT860_FC_DC:
        memcpy(fcDesc, "DC", 2);
        break;
    case DLT860_FC_SG:
        memcpy(fcDesc, "SG", 2);
        break;
    case DLT860_FC_SE:
        memcpy(fcDesc, "SE", 2);
        break;
    case DLT860_FC_SR:
        memcpy(fcDesc, "SR", 2);
        break;
    case DLT860_FC_OR:
        memcpy(fcDesc, "OR", 2);
        break;
    case DLT860_FC_BL:
        memcpy(fcDesc, "BL", 2);
        break;
    case DLT860_FC_EX:
        memcpy(fcDesc, "EX", 2);
        break;
    case DLT860_FC_CO:
        memcpy(fcDesc, "CO", 2);
        break;
    case DLT860_FC_US:
        memcpy(fcDesc, "US", 2);
        break;
    case DLT860_FC_MS:
        memcpy(fcDesc, "MS", 2);
        break;
    case DLT860_FC_RP:
        memcpy(fcDesc, "RP", 2);
        break;
    case DLT860_FC_BR:
        memcpy(fcDesc, "BR", 2);
        break;
    case DLT860_FC_LG:
        memcpy(fcDesc, "LG", 2);
        break;
    case DLT860_FC_GO:
        memcpy(fcDesc, "GO", 2);
        break;
    case DLT860_FC_ALL:
        memcpy(fcDesc, "XX", 2);
        break;
    default:
        delete [] fcDesc;
        return nullptr;
    }

    return fcDesc;
}

GspFunctionalConstraint GspFunctionalConstraint_fromString(const char* fcString)
{
    if (fcString[0] == 'S') {
        if (fcString[1] == 'T')
            return DLT860_FC_ST;
        if (fcString[1] == 'P')
            return DLT860_FC_SP;
        if (fcString[1] == 'V')
            return DLT860_FC_SV;
        if (fcString[1] == 'G')
            return DLT860_FC_SG;
        if (fcString[1] == 'E')
            return DLT860_FC_SE;
        if (fcString[1] == 'R')
            return DLT860_FC_SR;

        return DLT860_FC_NONE;
    }

    if (fcString[0] == 'M') {
        if (fcString[1] == 'X')
            return DLT860_FC_MX;
        if (fcString[1] == 'S')
            return DLT860_FC_MS;
        return DLT860_FC_NONE;
    }

    if (fcString[0] == 'C') {
        if (fcString[1] == 'F')
            return DLT860_FC_CF;
        if (fcString[1] == 'O')
            return DLT860_FC_CO;
        return DLT860_FC_NONE;
    }

    if (fcString[0] == 'D') {
        if (fcString[1] == 'C')
            return DLT860_FC_DC;
        return DLT860_FC_NONE;
    }

    if (fcString[0] == 'O') {
        if (fcString[1] == 'R')
            return DLT860_FC_OR;
        return DLT860_FC_NONE;
    }

    if (fcString[0] == 'B') {
        if (fcString[1] == 'L')
            return DLT860_FC_BL;
        if (fcString[1] == 'R')
            return DLT860_FC_BR;
        return DLT860_FC_NONE;
    }

    if (fcString[0] == 'E') {
        if (fcString[1] == 'X')
            return DLT860_FC_EX;
        return DLT860_FC_NONE;
    }

    if (fcString[0] == 'U') {
        if (fcString[1] == 'S')
            return DLT860_FC_US;
        return DLT860_FC_NONE;
    }

    if (fcString[0] == 'R') {
        if (fcString[1] == 'P')
            return DLT860_FC_RP;
        return DLT860_FC_NONE;
    }

    if (fcString[0] == 'L') {
        if (fcString[1] == 'G')
            return DLT860_FC_LG;
        return DLT860_FC_NONE;
    }

    if (fcString[0] == 'G') {
        if (fcString[1] == 'O')
            return DLT860_FC_GO;
        return DLT860_FC_NONE;
    }

    if(fcString[0] == 'X'){
        if (fcString[1] == 'X')
            return DLT860_FC_ALL;
        return DLT860_FC_NONE;
    }

    return DLT860_FC_NONE;
}

GspTimestamp* GspTimestamp_create()
{
    GspTimestamp* self = (GspTimestamp*) GLOBAL_CALLOC(1, sizeof(GspTimestamp));

    return self;
}

GspTimestamp* GspTimestamp_createFromByteArray(uint8_t* byteArray)
{
    GspTimestamp* self = GspTimestamp_create();

    if (self) {
        int i;

        for (i = 0; i < 8; i++)
            self->val[i] = byteArray[i];
    }

    return self;
}

void GspTimestamp_destroy(GspTimestamp* self)
{
    if (self != nullptr)
        GLOBAL_FREEMEM(self);
}

void GspTimestamp_clearFlags(GspTimestamp* self)
{
    self->val[7] = 0;
}

bool GspTimestamp_isLeapSecondKnown(GspTimestamp* self)
{
    if (self->val[7] & 0x80)
        return true;
    else
        return false;
}

void GspTimestamp_setLeapSecondKnown(GspTimestamp* self, bool value)
{
    if (value)
        self->val[7] |= 0x80;
    else
        self->val[7] &= 0x7f;
}

bool GspTimestamp_hasClockFailure(GspTimestamp* self)
{
    if (self->val[7] & 0x40)
        return true;
    else
        return false;
}

void GspTimestamp_setClockFailure(GspTimestamp* self, bool value)
{
    if (value)
        self->val[7] |= 0x40;
    else
        self->val[7] &= 0xbf;
}

bool GspTimestamp_isClockNotSynchronized(GspTimestamp* self)
{
    if (self->val[7] & 0x20)
        return true;
    else
        return false;
}

void GspTimestamp_setClockNotSynchronized(GspTimestamp* self, bool value)
{
    if (value)
        self->val[7] |= 0x20;
    else
        self->val[7] &= 0xdf;
}

int GspTimestamp_getSubsecondPrecision(GspTimestamp* self)
{
    return (int) (self->val[7] & 0x1f);
}

void GspTimestamp_setSubsecondPrecision(GspTimestamp* self, int subsecondPrecision)
{
    uint8_t ssp = subsecondPrecision & 0x1f;

    self->val[7] &= 0xe0;
    self->val[7] += ssp;
}

void GspTimestamp_setTimeInSeconds(GspTimestamp* self, uint32_t secondsSinceEpoch)
{
    uint8_t* timeArray = (uint8_t*) &secondsSinceEpoch;
    uint8_t* valueArray =  self->val;

#if (ORDER_LITTLE_ENDIAN == 1)
    memcpyReverseByteOrder(valueArray, timeArray, 4);
#else
    memcpy(valueArray, timeArray, 4);
#endif

    self->val[4] = 0;
    self->val[5] = 0;
    self->val[6] = 0;

    /* don't touch time quality */
}

void GspTimestamp_setTimeInMilliseconds(GspTimestamp* self, uint64_t millisSinceEpoch)
{
    uint32_t timeval32 = (uint32_t) (millisSinceEpoch / 1000LL);

    uint8_t* timeArray = (uint8_t*) &timeval32;
    uint8_t* valueArray = self->val;

#if (ORDER_LITTLE_ENDIAN == 1)
    memcpyReverseByteOrder(valueArray, timeArray, 4);
#else
    memcpy(valueArray, timeArray, 4);
#endif

    uint32_t remainder = (millisSinceEpoch % 1000LL);
    uint32_t fractionOfSecond = (remainder) * 16777 + ((remainder * 216) / 1000);

    /* encode fraction of second */
    valueArray[4] = ((fractionOfSecond >> 16) & 0xff);
    valueArray[5] = ((fractionOfSecond >> 8) & 0xff);
    valueArray[6] = (fractionOfSecond & 0xff);

    /* don't touch time quality */
}

uint32_t GspTimestamp_getTimeInSeconds(GspTimestamp* self)
{
    uint32_t timeval32;
    uint8_t* valueArray = self->val;

#if (ORDER_LITTLE_ENDIAN == 1)
    memcpyReverseByteOrder((uint8_t*) &timeval32, valueArray, 4);
#else
    memcpy((uint8_t*) &timeval32, valueArray, 4);
#endif

    return timeval32;
}

uint64_t GspTimestamp_getTimeInMs(GspTimestamp* self)
{
    uint32_t timeval32;
    uint8_t* valueArray = self->val;

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

    return (uint64_t) msVal;
}

char* GspMmsMapping_getMmsDomainFromObjectReference(const char* objectReference, char* buffer)
{
    int objRefLength = strlen(objectReference);
    char* domainName = nullptr;

    /* check for object reference size limit VISIBLESTRING129 */
    if (objRefLength > 129)
        goto exit_function;

    /* check if LD name is present */
    int i;
    for (i = 0; i < objRefLength; i++) {
        if (objectReference[i] == '/') {
            break;
        }
    }

    /* check for LD name limit (=64 characters) */
    if (i > 64)
        goto exit_function;

    if (i == objRefLength)
        goto exit_function;

    if (buffer == nullptr)
        domainName = (char*) GLOBAL_MALLOC(i + 1);
    else
        domainName = buffer;

    int j;
    for (j = 0; j < i; j++) {
        domainName[j] = objectReference[j];
    }

    domainName[j] = 0;

exit_function:
    return domainName;
}

char* GspMmsMapping_createMmsVariableNameFromObjectReference(const char* objectReference,
                                                             GspFunctionalConstraint fc, char* buffer)
{
    int objRefLength = strlen(objectReference);

    /* check for object reference size limit VISIBLESTRING129 */
    if (objRefLength > 129)
        return nullptr;

    /* check if LD name is present */
    int i;
    for (i = 0; i < objRefLength; i++) {
        if (objectReference[i] == '/') {
            break;
        }
    }

    /* check for LD name limit (= 64 characters) */
    if (i > 64)
        return nullptr;

    if (i == objRefLength) {
        i = 0; /* for the case when no LD name is present */
    } else {
        i++;
    }


    if (fc == DLT860_FC_NONE) {

        int len = objRefLength - i;

        char* mmsVariableName;

        if (buffer == nullptr) {
            mmsVariableName = (char*) GLOBAL_MALLOC(len);
        } else {
            mmsVariableName = buffer;
        }

        strcpy(mmsVariableName, objectReference + i);

        return mmsVariableName;
    }

    char* fcString = GspFunctionalConstraint_toString(fc);

    if (fcString == nullptr){
        return nullptr;
    }

    int namePartLength = objRefLength - i - 1;

    /* ensure that limit due to MMS name part length = 64 is not exceeded */
    if (namePartLength > 61){
        delete [] fcString;
        return nullptr;
    }

    char* mmsVariableName;

    if (buffer == nullptr) {
        mmsVariableName = (char*) GLOBAL_MALLOC(namePartLength + 5);
    } else {
        mmsVariableName = buffer;
    }

    int sourceIndex = i;
    int destIndex = 0;

    bool fcAdded = false;

    while (sourceIndex < objRefLength) {

        if (objectReference[sourceIndex] != '.') {
            mmsVariableName[destIndex++] = objectReference[sourceIndex++];
        } else {

            if (!fcAdded) {
                mmsVariableName[destIndex++] = '$';
                mmsVariableName[destIndex++] = fcString[0];
                mmsVariableName[destIndex++] = fcString[1];
                mmsVariableName[destIndex++] = '$';

                fcAdded = true;
            } else {
                mmsVariableName[destIndex++] = '$';
            }
            sourceIndex++;
        }
    }

    if (!fcAdded) {
        mmsVariableName[destIndex++] = '$';
        mmsVariableName[destIndex++] = fcString[0];
        mmsVariableName[destIndex++] = fcString[1];
    }

    mmsVariableName[destIndex] = 0;

    delete [] fcString;
    return mmsVariableName;
}

GspMmsVariableAccessSpecification* GspMmsMapping_ObjectReferenceToVariableAccessSpec(char* objectReference)
{
    char* domainIdEnd = strchr(objectReference, '/');

    if (domainIdEnd == nullptr) /* no logical device name present */
        return nullptr;

    int domainIdLen = domainIdEnd - objectReference;

    if (domainIdLen > 64)
        return nullptr;

    char* fcStart = strchr(objectReference, '[');

    if (fcStart == nullptr) /* no FC present */
        return nullptr;

    char* fcEnd = strchr(fcStart, ']');

    if (fcEnd == nullptr) /* syntax error in FC */
        return nullptr;

    if ((fcEnd - fcStart) != 3) /* syntax error in FC */
        return nullptr;

    GspFunctionalConstraint fc = GspFunctionalConstraint_fromString(fcStart + 1);

    GspMmsVariableAccessSpecification* accessSpec =
            (GspMmsVariableAccessSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableAccessSpecification));

    accessSpec->domainId = StringUtils_createStringFromBuffer((uint8_t*) objectReference, domainIdLen);

    char* indexBrace = strchr(domainIdEnd, '(');

    char* itemIdEnd = indexBrace;

    if (itemIdEnd == nullptr)
        itemIdEnd = strchr(domainIdEnd, '[');

    int objRefLen = strlen(objectReference);

    accessSpec->arrayIndex = -1; /* -1 --> not present */

    if (itemIdEnd != nullptr) {
        int itemIdLen = itemIdEnd - domainIdEnd - 1;

        char itemIdStr[129];

        memcpy(itemIdStr, (domainIdEnd + 1), itemIdLen);
        itemIdStr[itemIdLen] = 0;

        accessSpec->itemId = GspMmsMapping_createMmsVariableNameFromObjectReference(itemIdStr, fc, nullptr);

        if (indexBrace != nullptr) {

            char* indexStart = itemIdEnd + 1;

            char* indexEnd = strchr(indexStart, ')');

            int indexLen = indexEnd - indexStart;

            int index = StringUtils_digitsToInt(indexStart, indexLen);

            accessSpec->arrayIndex = (int32_t) index;

            int componentNameLen = objRefLen - ((indexEnd + 2) - objectReference) - 4;

            if (componentNameLen > 0) {
                accessSpec->componentName = StringUtils_createStringFromBuffer((uint8_t*) (indexEnd + 2), componentNameLen);
                StringUtils_replace(accessSpec->componentName, '.', '$');
            }
        }
    }

    return accessSpec;
}


static int getNumberOfDigits(int value)
{
    int numberOfDigits = 1;

    while (value > 9) {
        numberOfDigits++;
        value /= 10;
    }

    return numberOfDigits;
}

char* GspMmsMapping_varAccessSpecToObjectReference(GspMmsVariableAccessSpecification* varAccessSpec)
{
    char* domainId = varAccessSpec->domainId;

    int domainIdLen = strlen(domainId);

    char* itemId = varAccessSpec->itemId;

    char* separator = strchr(itemId, '$');

    int itemIdLen = strlen(itemId);

    int arrayIndexLen = 0;

    int componentPartLen = 0;

    if (varAccessSpec->componentName != nullptr)
        componentPartLen = strlen(varAccessSpec->componentName);

    if (varAccessSpec->arrayIndex > -1)
        arrayIndexLen = 2 + getNumberOfDigits(varAccessSpec->arrayIndex);

    int newStringLen = (domainIdLen + 1) + (itemIdLen - 2) + arrayIndexLen + 4 /* for FC */+ componentPartLen + 1;

    char* newString = (char*) GLOBAL_MALLOC(newStringLen);

    char* targetPos = newString;

    /* Copy domain id part */
    char* currentPos = domainId;

    while (currentPos < (domainId + domainIdLen)) {
        *targetPos = *currentPos;
        targetPos++;
        currentPos++;
    }

    *targetPos = '/';
    targetPos++;

    /* Copy item id parts */
    currentPos = itemId;

    while (currentPos < separator) {
        *targetPos = *currentPos;
        targetPos++;
        currentPos++;
    }

    *targetPos = '.';
    targetPos++;

    currentPos = separator + 4;

    while (currentPos < (itemId + itemIdLen)) {
        if (*currentPos == '$')
            *targetPos = '.';
        else
            *targetPos = *currentPos;

        targetPos++;
        currentPos++;
    }

    /* Add array index part */
    if (varAccessSpec->arrayIndex > -1) {
        sprintf(targetPos, "(%i)", varAccessSpec->arrayIndex);
        targetPos += arrayIndexLen;
    }

    /* Add component part */
    if (varAccessSpec->componentName != nullptr) {
        *targetPos = '.';
        targetPos++;

        int i;
        for (i = 0; i < componentPartLen; i++) {
            if (varAccessSpec->componentName[i] == '$')
                *targetPos = '.';
            else
                *targetPos = varAccessSpec->componentName[i];

            targetPos++;
        }
    }

    /* add FC part */
    *targetPos = '[';
    targetPos++;
    *targetPos = *(separator + 1);
    targetPos++;
    *targetPos = *(separator + 2);
    targetPos++;
    *targetPos = ']';
    targetPos++;

    *targetPos = 0; /* add terminator */

    return newString;
}

char* LibDLT860_getVersionString()
{
    return LIBDLT860_VERSION;
}

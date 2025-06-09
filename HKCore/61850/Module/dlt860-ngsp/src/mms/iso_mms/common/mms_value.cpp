/*
 *  mms_value.c
 */

#include "libdlt860_platform_includes.h"
#include "gsp_mms_common.h"
#include "gsp_mms_value.h"
#include "gsp_mms_type_spec.h"
#include "mms_common_internal.h"
#include "conversions.h"
#include "simple_allocator.h"

#ifdef USE_LOGGING_H
#include "nlogging.h"
#include <bitset>
#include <chrono>
#include <fmt/chrono.h>
#else
void Global_LogPrint(char *pzfString1,char *pzfString2)
{
}

void Global_LogPrint(char *pzfString)
{
}

#define ERROR_JUST_LOG 1
#define NLOG_ERROR Global_LogPrint
#define NLOG_WARN Global_LogPrint
#endif

#include <time.h>
#include "Data.h"
#include <vector>
#include "stack_config.h"


using namespace std;

static void setVisibleStringValue(GspMmsValue *self, const char *string)
{
    if (!self)
    {
        Global_LogString("mms_value setVisibleStringValue 操作时,参数异常\n");
        assert(ERROR_JUST_LOG);
        return;
    }

    OCTET_STRING_fromString(&self->choice.visible_string, string);
}

void createBitString(GspMmsValue *self, const char *buf, int bitSize)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "createBitString");
        return;
    }

    int byteSize = bitSize / 8 + 1;
    self->choice.bit_string.buf = (uint8_t *)calloc(byteSize, sizeof(uint8_t));
    self->choice.bit_string.size = byteSize;
    self->choice.bit_string.bits_unused = byteSize * 8 - bitSize;
    if (buf)
    {
        memcpy(self->choice.bit_string.buf, buf, byteSize);
    }
}

int getBitSizeOfBitString(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "getBitSizeOfBitString");
        return 0;
    }

    return self->choice.bit_string.size * 8 - self->choice.bit_string.bits_unused;
}

static int bitStringByteSize(const GspMmsValue *value)
{
    if (!value)
    {
        Global_LogString("mms_value bitStringByteSize 操作时,参数异常\n");
        assert(ERROR_JUST_LOG);
        return 0;
    }

    int bitSize = value->choice.bit_string.size;
    return (bitSize / 8) + ((bitSize % 8) > 0);
}

int GspMmsValue_getBitStringByteSize(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_getBitStringByteSize");
        return 0;
    }

    return bitStringByteSize(self);
}

static bool updateStructuredComponent(GspMmsValue *self, const GspMmsValue *update)
{
    if (!self || !update)
    {
        Global_LogString("mms_value updateStructuredComponent 操作时,参数异常\n");
        assert(ERROR_JUST_LOG);
        return false;
    }

    GspMmsValue **selfValues;
    GspMmsValue **updateValues;

    if (self->choice.structure.list.count == 0)
    {
        for (int i = 0; i < update->choice.structure.list.count; ++i)
        {
            asn_sequence_add(&self->choice.structure, GspMmsValue_clone(update->choice.structure.list.array[i]));
        }
    }
    else
    {
        if (self->choice.structure.list.count != update->choice.structure.list.count)
        {
#ifdef USE_LOGGING_H
            NLOG_WARN("gsp mms value update, 源结构体项数[{}]与目标结构体项数[{}]不一致", self->choice.structure.list.count, update->choice.structure.list.count)
#endif
            return false;
        }

        selfValues = self->choice.structure.list.array;
        updateValues = update->choice.structure.list.array;

        int i;
        for (i = 0; i < self->choice.structure.list.count; i++)
        {
            if (GspMmsValue_update(selfValues[i], updateValues[i]) == false)
                return false;
        }
    }
    return true;
}

bool GspMmsValue_equals(const GspMmsValue *self, const GspMmsValue *otherValue)
{
    // 容错处理
    if (!self || !otherValue)
    {
#ifdef USE_LOGGING_H
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_equals");
#endif
        return false;
    }

    if (self->present == otherValue->present)
    {
        switch (self->present)
        {
        case Data_PR_array:
        case Data_PR_structure:
        {
            if (self->choice.structure.list.count == otherValue->choice.structure.list.count)
            {
                int componentCount = self->choice.structure.list.count;
                int i;
                for (i = 0; i < componentCount; i++)
                {
                    if (!GspMmsValue_equals(self->choice.structure.list.array[i], otherValue->choice.structure.list.array[i]))
                        return false;
                }
                return true;
            }
        }
        break;

        case Data_PR_boolean:
        {
            if (self->choice.boolean == otherValue->choice.boolean)
                return true;
        }
        break;

        case Data_PR_float64:
        {
            if (memcmp(self->choice.float64.buf, otherValue->choice.float64.buf, 8) == 0)
            {
                return true;
            }
        }
        break;

        case Data_PR_float32:
        {
            if (memcmp(self->choice.float32.buf, otherValue->choice.float32.buf, 4) == 0)
            {
                return true;
            }
        }
        break;

        case Data_PR_utc_time:
        {
            if (memcmp(self->choice.utc_time.buf, otherValue->choice.utc_time.buf, 8) == 0)
                return true;
        }
        break;

        case Data_PR_check:
        case Data_PR_bit_string:
        case Data_PR_quality:
        case Data_PR_tcmd:
        case Data_PR_dbpos:
        {
            if (self->choice.bit_string.size == otherValue->choice.bit_string.size)
            {
                if (memcmp(self->choice.bit_string.buf, otherValue->choice.bit_string.buf, bitStringByteSize(self)) == 0)
                    return true;
            }
        }
        break;

        case Data_PR_binary_time:
        {
            if (self->choice.binary_time.size == otherValue->choice.binary_time.size)
            {
                if (memcmp(self->choice.binary_time.buf, otherValue->choice.binary_time.buf, self->choice.binary_time.size) == 0)
                    return true;
            }
        }
        break;

        case Data_PR_octet_string:
        {
            if (self->choice.octet_string.size == otherValue->choice.octet_string.size)
            {
                if (memcmp(self->choice.octet_string.buf, otherValue->choice.octet_string.buf, self->choice.octet_string.size) == 0)
                    return true;
            }
        }
        break;

        case Data_PR_unicode_string:
        case Data_PR_visible_string:
        {
            if (self->choice.visible_string.buf != nullptr)
            {
                if (otherValue->choice.visible_string.buf != nullptr)
                {
                    if (strcmp((const char *)self->choice.visible_string.buf, (const char *)otherValue->choice.visible_string.buf) == 0)
                        return true;
                }
            }
            else
            {
                if (otherValue->choice.visible_string.buf == nullptr)
                    return true;
            }
        }
        break;

        case Data_PR_error:
        {
            if (self->choice.error == otherValue->choice.error)
                return true;
        }
        break;

        case Data_PR_int8:
            return (self->choice.int8 == otherValue->choice.int8);

        case Data_PR_int16:
            return (self->choice.int16 == otherValue->choice.int16);

        case Data_PR_int32:
            return (self->choice.int32 == otherValue->choice.int32);

        case Data_PR_int64:
            return (self->choice.int64 == otherValue->choice.int64);

        case Data_PR_int8u:
            return (self->choice.int8u == otherValue->choice.int8u);

        case Data_PR_int16u:
            return (self->choice.int16u == otherValue->choice.int16u);

        case Data_PR_int32u:
            return (self->choice.int32u == otherValue->choice.int32u);

        case Data_PR_int64u:
            return (self->choice.int64u == otherValue->choice.int64u);

        default:
            break;
        }
        return false;
    }
    else
    {
        return false;
    }
}

bool GspMmsValue_equalTypes(const GspMmsValue *self, const GspMmsValue *otherValue)
{
    if (!self || !otherValue)
    {
#ifdef USE_LOGGING_H
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_equalTypes");
#endif
        return false;
    }

    if (self->present == otherValue->present)
    {
        switch (self->present)
        {
        case Data_PR_array:
        case Data_PR_structure:
            if (self->choice.structure.list.count == otherValue->choice.structure.list.count)
            {
                int componentCount = self->choice.structure.list.count;

                int i;
                for (i = 0; i < componentCount; i++)
                {
                    if (!GspMmsValue_equalTypes(self->choice.structure.list.array[i], otherValue->choice.structure.list.array[i]))
                        return false;
                }
                return true;
            }
            else
            {
                return false;
            }
        default:
            return true;
        }
    }
    else
    {
        return false;
    }
}

bool GspMmsValue_update(GspMmsValue *self, const GspMmsValue *update)
{
    if (!self || !update)
    {
#ifdef USE_LOGGING_H
        NLOG_WARN("gsp mms value update, 更新[{}]到[{}]失败", fmt::ptr(update), fmt::ptr(self));
#endif
        return false;
    }
    if (self->present == Data_PR_NOTHING)
    {
        self->present = update->present;
    }
    if (self->present == update->present)
    {
        switch (self->present)
        {
        case Data_PR_structure:
        case Data_PR_array:
        {
            if (!updateStructuredComponent(self, update))
            {
                return false;
            }
        }
        break;

        case Data_PR_boolean:
        {
            self->choice.boolean = update->choice.boolean;
        }
        break;

        case Data_PR_float64:
        {
            if (!self->choice.float64.buf)
            {
                OCTET_STRING_fromBuf(&self->choice.float64, "", 8);
            }
            memcpy(self->choice.float64.buf, update->choice.float64.buf, 8);
        }
        break;

        case Data_PR_float32:
        {
            if (!self->choice.float32.buf)
            {
                OCTET_STRING_fromBuf(&self->choice.float32, "", 4);
            }
            memcpy(self->choice.float32.buf, update->choice.float32.buf, 4);
        }
        break;

        case Data_PR_utc_time:
        {
            if (!self->choice.utc_time.buf)
            {
                OCTET_STRING_fromBuf(&self->choice.utc_time, "", 8);
            }
            memcpy(self->choice.utc_time.buf, update->choice.utc_time.buf, 8);
        }
        break;

        case Data_PR_quality:
        case Data_PR_dbpos:
        case Data_PR_tcmd:
        case Data_PR_bit_string:
        {
            int bitSize = getBitSizeOfBitString(self);
            int updateBitSize = getBitSizeOfBitString(update);
            if (bitSize == 0)
            {
                GspBIT_STRING_createBitString(&self->choice.bit_string, nullptr, update->choice.bit_string.size, update->choice.bit_string.bits_unused);
                GspMmsValue_newBitString(updateBitSize);
            }
            if (bitSize == updateBitSize)
            {
                memcpy(self->choice.bit_string.buf, update->choice.bit_string.buf, self->choice.bit_string.size);
            }
            else if (updateBitSize < bitSize)
            {
                for (int i = 0; i < updateBitSize; ++i)
                {
                    GspMmsValue_setBitStringBit(self, i, GspMmsValue_getBitStringBit(update, i));
                }
            }
        }
        break;

        case Data_PR_octet_string:
        {
            setVisibleStringValue(self, (const char *)update->choice.octet_string.buf);
        }
        break;

        case Data_PR_unicode_string:
        {
            setVisibleStringValue(self, (const char *)update->choice.unicode_string.buf);
        }
        break;

        case Data_PR_visible_string:
        {
            setVisibleStringValue(self, (const char *)update->choice.visible_string.buf);
        }
        break;

        case Data_PR_binary_time:
        {
            if (!self->choice.binary_time.buf)
            {
                OCTET_STRING_fromBuf(&self->choice.binary_time, (const char *)update->choice.binary_time.buf, update->choice.binary_time.size);
            }
            else
            {
                self->choice.binary_time.size = update->choice.binary_time.size;
                memcpy(self->choice.binary_time.buf, update->choice.binary_time.buf, update->choice.binary_time.size);
            }
        }
        break;

        case Data_PR_int8:
            self->choice.int8 = update->choice.int8;
            break;
        case Data_PR_int16:
            self->choice.int16 = update->choice.int16;
            break;
        case Data_PR_int32:
            self->choice.int32 = update->choice.int32;
            break;
        case Data_PR_int64:
            self->choice.int64 = update->choice.int64;
            break;
        case Data_PR_int8u:
            self->choice.int8u = update->choice.int8u;
            break;
        case Data_PR_int16u:
            self->choice.int16u = update->choice.int16u;
            break;
        case Data_PR_int32u:
            self->choice.int32u = update->choice.int32u;
            break;
        case Data_PR_int64u:
            self->choice.int64u = update->choice.int64u;
            break;
        default:
            return false;
        }
        return true;
    }
    else
    {
#ifdef USE_LOGGING_H
        NLOG_WARN("gsp mms value update, 源数据类型[{}]与目标数据类型不一致[{}]", self->present, update->present);
#endif
        return false;
    }
}

GspMmsValue *GspMmsValue_newDataAccessError(GspMmsDataAccessError accessError)
{
    GspMmsValue *self = GspMmsValue_new();

    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_newDataAccessError");
        return nullptr;
    }

    self->present = Data_PR_error;
    self->choice.error = accessError;

    return self;
}

GspMmsValue *GspMmsValue_newQuality()
{
    GspMmsValue *self = GspMmsValue_new();

    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_newQuality");
        return nullptr;
    }

    self->present = Data_PR_quality;
    createBitString(self, nullptr, 13);

    return self;
}

GspMmsValue *GspMmsValue_newBitString(int bitSize)
{
    GspMmsValue *self = GspMmsValue_new();

    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_newBitString");
        return nullptr;
    }

    self->present = Data_PR_bit_string;
    createBitString(self, nullptr, bitSize);

    return self;
}

void GspMmsValue_deleteAllBitStringBits(GspMmsValue *self)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_deleteAllBitStringBits");
        return;
    }

    size_t byteSize = self->choice.bit_string.size;
    memset(self->choice.bit_string.buf, 0, byteSize);
}

void GspMmsValue_setAllBitStringBits(GspMmsValue *self)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_setAllBitStringBits");
        return;
    }

    int byteSize = self->choice.bit_string.size;
    memset(self->choice.bit_string.buf, 0xff, byteSize);

    int padding = self->choice.bit_string.bits_unused;

    uint8_t paddingMask = 0;

    for (int i = 0; i < padding; i++)
    {
        paddingMask += (1 << i);
    }

    paddingMask = ~paddingMask;

    self->choice.bit_string.buf[byteSize - 1] = self->choice.bit_string.buf[byteSize - 1] & paddingMask;
}

int GspMmsValue_getBitStringSize(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getBitStringSize");
        return 0;
    }

    return getBitSizeOfBitString(self);
}

int GspMmsValue_getNumberOfSetBits(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getNumberOfSetBits");
        return 0;
    }

    int setBitsCount = 0;
    int byteSize = self->choice.bit_string.size;

    for (int i = 0; i < byteSize; i++)
    {
        /* deal with wrong padding */
        if (i == (byteSize - 1))
        {
            int paddingSize = self->choice.bit_string.bits_unused;

            uint8_t mask = 0;
            int k;
            for (k = 0; k < paddingSize; k++)
                mask += (1 << k);
            mask = ~mask;
            self->choice.bit_string.buf[i] = (self->choice.bit_string.buf[i] & mask);
        }

        uint8_t currentByte = self->choice.bit_string.buf[i];
        while (currentByte != 0)
        {
            if ((currentByte & 1) == 1)
                setBitsCount++;
            currentByte >>= 1;
        }
    }

    return setBitsCount;
}

void GspMmsValue_setBitStringBit(GspMmsValue *self, int bitPos, bool value)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_setBitStringBit");
        return;
    }

    int bitSize = getBitSizeOfBitString(self);
    if (bitPos < bitSize)
    {
        int bytePos = bitPos / 8;
        int bitPosInByte = 7 - (bitPos % 8);
        int bitMask = (1 << bitPosInByte);

        if (value)
        {
            self->choice.bit_string.buf[bytePos] |= bitMask;
        }
        else
        {
            self->choice.bit_string.buf[bytePos] &= (~bitMask);
        }
    }
}

uint8_t *GspMmsValue_getBitStringBuf(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getBitStringBuf");
        return self->choice.bit_string.buf;
    }
    return nullptr;
}

bool GspMmsValue_getBitStringBit(const GspMmsValue *self, int bitPos)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getBitStringBit");
        return false;
    }

    int bitSize = getBitSizeOfBitString(self);
    if (bitPos < bitSize)
    {
        int bytePos = bitPos / 8;
        int bitPosInByte = 7 - (bitPos % 8);
        int bitMask = (1 << bitPosInByte);

        if ((self->choice.bit_string.buf[bytePos] & bitMask) > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false; /* out of range bits are always zero */
    }
}

uint32_t GspMmsValue_getBitStringAsInteger(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getBitStringAsInteger");
        return 0;
    }

    uint32_t value = 0;

    int bitPos;
    int bitSize = getBitSizeOfBitString(self);

    for (bitPos = 0; bitPos < bitSize; bitPos++)
    {
        if (GspMmsValue_getBitStringBit(self, bitPos))
        {
            value += (1 << bitPos);
        }
    }

    return value;
}

void GspMmsValue_setBitStringFromInteger(GspMmsValue *self, uint32_t intValue)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_setBitStringFromInteger");
        return;
    }

    int bitSize = getBitSizeOfBitString(self);
    for (int bitPos = 0; bitPos < bitSize; bitPos++)
    {
        if ((intValue & 1) == 1)
            GspMmsValue_setBitStringBit(self, bitPos, true);
        else
            GspMmsValue_setBitStringBit(self, bitPos, false);

        intValue = intValue >> 1;
    }
}

uint32_t GspMmsValue_getBitStringAsIntegerBigEndian(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getBitStringAsIntegerBigEndian");
        return 0;
    }

    uint32_t value = 0;
    int bitSize = getBitSizeOfBitString(self);

    int bitPos;
    int i = 0;

    for (bitPos = (bitSize - 1); bitPos >= 0; bitPos--)
    {

        if (GspMmsValue_getBitStringBit(self, bitPos))
        {
            value += (1 << i);
        }

        i++;
    }

    return value;
}

void GspMmsValue_setBitStringFromIntegerBigEndian(GspMmsValue *self, uint32_t intValue)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_setBitStringFromIntegerBigEndian");
        return;
    }

    int bitPos;
    int bitSize = getBitSizeOfBitString(self);

    for (bitPos = (bitSize - 1); bitPos >= 0; bitPos--)
    {
        if ((intValue & 1) == 1)
            GspMmsValue_setBitStringBit(self, bitPos, true);
        else
            GspMmsValue_setBitStringBit(self, bitPos, false);

        intValue = intValue >> 1;
    }
}

void GspMmsValue_setBitStringFromString(GspMmsValue *self, const char *value)
{
    size_t strLen = strlen(value);
    size_t bitLen = GspMmsValue_getBitStringSize(self);
    for(size_t i = 0; i < min(strLen, bitLen); i++)
    {
        GspMmsValue_setBitStringBit(self, i, value[i] == '1');
    }
}

const char *GspMmsValue_getBitStringStr(const GspMmsValue *self)
{

    // 异常
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_setBitStringFromIntegerBigEndian");
        return nullptr;
    }

    // 大小
    int bitSize = getBitSizeOfBitString(self);

    // 内存分配
    char *bitStr = (char *)GspMemory_calloc(bitSize + 1, sizeof(char));

    // 逐个位置判断
    for (int bitPos = 0; bitPos < bitSize; ++bitPos)
    {
        bool tmpVal = GspMmsValue_getBitStringBit(self, bitPos);
        bitStr[bitPos] = tmpVal ? '1' : '0';
    }
    return bitStr;
}

GspMmsValue *GspMmsValue_newFloat(float value)
{
    GspMmsValue *self = GspMmsValue_new();
    self->present = Data_PR_float32;
    OCTET_STRING_fromBuf(&self->choice.float32, (const char *)&value, 4);
    return self;
}

void GspMmsValue_setFloat(GspMmsValue *self, float newFloatValue)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_setFloat");
        return;
    }

    memcpy(self->choice.float32.buf, &newFloatValue, 4);
}

void GspMmsValue_setDouble(GspMmsValue *self, double newDoubleValue)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_setDouble");
        return;
    }

    memcpy(self->choice.float64.buf, &newDoubleValue, 8);
}

GspMmsValue *GspMmsValue_newDouble(double value)
{
    GspMmsValue *self = GspMmsValue_new();

    self->present = Data_PR_float64;
    OCTET_STRING_fromBuf(&self->choice.float64, (const char *)&value, 8);

    return self;
}

GspMmsValue *GspMmsValue_newIntegerFromInt8(int8_t integer)
{
    GspMmsValue *self = GspMmsValue_new();

    if (self == nullptr)
        return nullptr;

    self->present = Data_PR_int8;
    self->choice.int8 = integer;

    return self;
}

GspMmsValue *GspMmsValue_newIntegerFromInt16(int16_t integer)
{
    GspMmsValue *self = GspMmsValue_new();

    if (self == nullptr)
        return nullptr;

    self->present = Data_PR_int16;
    self->choice.int16 = integer;

    return self;
}

void GspMmsValue_setInt8(GspMmsValue *self, int8_t integer)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_setInt8");
        return;
    }

    self->choice.int8 = integer;
}

void GspMmsValue_setInt16(GspMmsValue *self, int16_t integer)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_setInt16");
        return;
    }

    self->choice.int16 = integer;
}

void GspMmsValue_setInt32(GspMmsValue *self, int32_t integer)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_setInt32");
        return;
    }

    self->choice.int32 = integer;
}

void GspMmsValue_setInt64(GspMmsValue *self, int64_t integer)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_setInt64");
        return;
    }

    self->choice.int64 = integer;
}

void GspMmsValue_setUint32(GspMmsValue *self, uint32_t integer)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_setUint32");
        return;
    }

    self->choice.int32u = integer;
}

void GspMmsValue_setUint16(GspMmsValue *self, uint16_t integer)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_setUint16");
        return;
    }

    self->choice.int16u = integer;
}

void GspMmsValue_setUint8(GspMmsValue *self, uint8_t integer)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_setUint8");
        return;
    }

    self->choice.int8u = integer;
}

void GspMmsValue_setBoolean(GspMmsValue *self, bool boolValue)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_setBoolean");
        return;
    }

    self->choice.boolean = boolValue;
}

bool GspMmsValue_getBoolean(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_getBoolean");
        return false;
    }

    return self->choice.boolean;
}

bool GspMmsValue_toBoolean(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_toBoolean");
        return false;
    }

    return self->choice.boolean;
}

GspMmsValue *GspMmsValue_setUtcTime(GspMmsValue *self, uint32_t timeval)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_toBoolean");
        return nullptr;
    }

    uint8_t *timeArray = (uint8_t *)&timeval;
    uint8_t *valueArray = self->choice.utc_time.buf;

#if (ORDER_LITTLE_ENDIAN == 1)
    memcpyReverseByteOrder(valueArray, timeArray, 4);
#else
    memcpy(valueArray, timeArray, 4);
#endif

    return self;
}

void GspFillMmsValueToBitString(BIT_STRING_t &bitString, GspMmsValue *value)
{
    if (!value)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspFillMmsValueToBitString");
        return;
    }

    bitString.buf = (uint8_t *)calloc(value->choice.bit_string.size, sizeof(uint8_t));
    memcpy(bitString.buf, value->choice.bit_string.buf, value->choice.bit_string.size);
    bitString.size = value->choice.bit_string.size;
    bitString.bits_unused = value->choice.bit_string.bits_unused;
}

void GspFillMmsValueToBinaryTime(BinaryTime_t &binaryTime, GspMmsValue *value)
{
    if (!value)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspFillMmsValueToBinaryTime");
        return;
    }

    binaryTime.buf = (uint8_t *)calloc(value->choice.octet_string.size, sizeof(uint8_t));
    memcpy(binaryTime.buf, value->choice.octet_string.buf, value->choice.octet_string.size);
    binaryTime.size = value->choice.octet_string.size;
}

void GspFillMmsValueToOctetString(OCTET_STRING_t &octetString, GspMmsValue *value)
{
    if (!value)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspFillMmsValueToOctetString");
        return;
    }

    octetString.buf = (uint8_t *)calloc(value->choice.octet_string.size, sizeof(uint8_t));
    memcpy(octetString.buf, value->choice.octet_string.buf, value->choice.octet_string.size);
    octetString.size = value->choice.octet_string.size;
}

void GspFillMmsValueToUtcTime(UtcTime_t &utcTime, GspMmsValue *value)
{
    if (!value)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspFillMmsValueToUtcTime");
        return;
    }

    utcTime.buf = (uint8_t *)calloc(value->choice.octet_string.size, sizeof(uint8_t));
    memcpy(utcTime.buf, value->choice.octet_string.buf, value->choice.octet_string.size);
    utcTime.size = value->choice.octet_string.size;
}

GspMmsValue *GspMmsValue_setUtcTimeMs(GspMmsValue *self, uint64_t timeval)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_setUtcTimeMs");
        return nullptr;
    }

    self->present = Data_PR_utc_time;
    char buf[8] = "";
    OCTET_STRING_fromBuf(&self->choice.utc_time, buf, 8);
    uint32_t timeval32 = (timeval / 1000LL);

    uint8_t *timeArray = (uint8_t *)&timeval32;
    uint8_t *valueArray = self->choice.utc_time.buf;

#if (ORDER_LITTLE_ENDIAN == 1)
    memcpyReverseByteOrder(valueArray, timeArray, 4);
#else
    memcpy(valueArray, timeArray, 4);
#endif

    uint32_t remainder = (timeval % 1000LL);
    uint32_t fractionOfSecond = (remainder)*16777 + ((remainder * 216) / 1000);

    /* encode fraction of second */
    valueArray[4] = ((fractionOfSecond >> 16) & 0xff);
    valueArray[5] = ((fractionOfSecond >> 8) & 0xff);
    valueArray[6] = (fractionOfSecond & 0xff);

    /* encode time quality */
    valueArray[7] = 0x0a; /* 10 bit sub-second time accuracy */

    return self;
}

void GspMmsValue_setUtcTimeQuality(GspMmsValue *self, uint8_t timeQuality)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_setUtcTimeQuality");
        return;
    }

    self->choice.utc_time.buf[7] = timeQuality;
}

uint8_t GspMmsValue_getUtcTimeQuality(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_getUtcTimeQuality");
        return 0;
    }

    return self->choice.utc_time.buf[7];
}

void GspMmsValue_setUtcTimeByBuffer(GspMmsValue *self, const uint8_t *buffer)
{
    if (!buffer || !self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_getUtcTimeQuality");
        return;
    }

    uint8_t *valueArray = self->choice.utc_time.buf;
    int i;
    for (i = 0; i < 8; i++)
    {
        valueArray[i] = buffer[i];
    }
}

uint8_t *GspMmsValue_getUtcTimeBuffer(GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getUtcTimeBuffer");
        return nullptr;
    }

    return self->choice.utc_time.buf;
}

uint64_t GspMmsValue_getUtcTimeInMs(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getUtcTimeInMs");
        return 0;
    }

    uint32_t timeval32;
    const uint8_t *valueArray = self->choice.utc_time.buf;

#if (ORDER_LITTLE_ENDIAN == 1)
    memcpyReverseByteOrder((uint8_t *)&timeval32, valueArray, 4);
#else
    memcpy((uint8_t *)&timeval32, valueArray, 4);
#endif

    uint32_t fractionOfSecond = 0;

    fractionOfSecond = (valueArray[4] << 16);
    fractionOfSecond += (valueArray[5] << 8);
    fractionOfSecond += (valueArray[6]);

    uint32_t remainder = fractionOfSecond / 16777;
    uint64_t msVal = (timeval32 * 1000LL) + remainder;

    return msVal;
}

uint64_t GspMmsValue_getUtcTimeInMsWithUs(const GspMmsValue *self, uint32_t *usec)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getUtcTimeInMsWithUs");
        return 0;
    }

    uint32_t timeval32;
    const uint8_t *valueArray = self->choice.utc_time.buf;

#if (ORDER_LITTLE_ENDIAN == 1)
    memcpyReverseByteOrder((uint8_t *)&timeval32, valueArray, 4);
#else
    memcpy((uint8_t *)&timeval32, valueArray, 4);
#endif

    uint64_t fractionOfSecond = 0;

    fractionOfSecond = (valueArray[4] << 16);
    fractionOfSecond += (valueArray[5] << 8);
    fractionOfSecond += (valueArray[6]);

    uint64_t remainder = fractionOfSecond * 1000000ULL / 0x1000000ULL; /* in usec */

    uint64_t msVal = (timeval32 * 1000LL) + (remainder / 1000LL);

    if (usec != nullptr)
        *usec = remainder % 1000LL;

    return msVal;
}

GspMmsValue *GspMmsValue_newIntegerFromInt32(int32_t integer)
{
    GspMmsValue *self = GspMmsValue_new();

    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_newIntegerFromInt32");
        return nullptr;
    }

    self->present = Data_PR_int32;
    self->choice.int32 = integer;

    return self;
}

GspMmsValue *GspMmsValue_newUnsignedFromUint32(uint32_t integer)
{
    GspMmsValue *self = GspMmsValue_new();

    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_newUnsignedFromUint32");
        return nullptr;
    }

    self->present = Data_PR_int32u;
    self->choice.int32u = integer;

    return self;
}

GspMmsValue *GspMmsValue_newIntegerFromInt64(int64_t integer)
{
    GspMmsValue *self = GspMmsValue_new();

    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_newIntegerFromInt64");
        return nullptr;
    }

    self->present = Data_PR_int64u;
    self->choice.int64u = integer;
    return self;
}

int32_t GspMmsValue_toInt32(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_toInt32");
        return 0;
    }

    int32_t integerValue = 0;

    if (self == nullptr)
        return integerValue;

    switch (self->present)
    {
    case Data_PR_int8:
        integerValue = self->choice.int8;
        break;
    case Data_PR_int16:
        integerValue = self->choice.int16;
        break;
    case Data_PR_int32:
        integerValue = self->choice.int32;
        break;
    case Data_PR_int64:
        // TODO 这里需要做数据范围判断
        integerValue = self->choice.int64;
        break;
    case Data_PR_int8u:
        integerValue = self->choice.int8u;
        break;
    case Data_PR_int16u:
        integerValue = self->choice.int16u;
        break;
    case Data_PR_int32u:
        integerValue = self->choice.int32u;
        break;
    case Data_PR_int64u:
        // TODO 这里需要做数据范围判断
        integerValue = (int64_t)self->choice.int64u;
        break;
    default:
        break;
    }

    return integerValue;
}

uint32_t GspMmsValue_toUint32(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_toUint32");
        return 0;
    }

    uint32_t integerValue = 0;

    if (self == nullptr)
        return integerValue;

    switch (self->present)
    {
    case Data_PR_int8:
        integerValue = self->choice.int8;
        break;
    case Data_PR_int16:
        integerValue = self->choice.int16;
        break;
    case Data_PR_int32:
        integerValue = self->choice.int32;
        break;
    case Data_PR_int64:
        // TODO 这里需要做数据范围判断
        integerValue = self->choice.int64;
        break;
    case Data_PR_int8u:
        integerValue = self->choice.int8u;
        break;
    case Data_PR_int16u:
        integerValue = self->choice.int16u;
        break;
    case Data_PR_int32u:
        integerValue = self->choice.int32u;
        break;
    case Data_PR_int64u:
        // TODO 这里需要做数据范围判断
        integerValue = (int64_t)self->choice.int64u;
        break;
    default:
        break;
    }

    return integerValue;
}

int64_t GspMmsValue_toInt64(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_toInt64");
        return 0;
    }

    int64_t integerValue = 0;

    if (!self)
        return integerValue;

    switch (self->present)
    {
    case Data_PR_int8:
        integerValue = self->choice.int8;
        break;
    case Data_PR_int16:
        integerValue = self->choice.int16;
        break;
    case Data_PR_int32:
        integerValue = self->choice.int32;
        break;
    case Data_PR_int64:
        integerValue = self->choice.int64;
        break;
    case Data_PR_int8u:
        integerValue = self->choice.int8u;
        break;
    case Data_PR_int16u:
        integerValue = self->choice.int16u;
        break;
    case Data_PR_int32u:
        integerValue = self->choice.int32u;
        break;
    case Data_PR_int64u:
        integerValue = (int64_t)self->choice.int64u;
        break;
    default:
        break;
    }

    return integerValue;
}

uint64_t GspMmsValue_toUInt64(const GspMmsValue *self)
{

    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_toUInt64");
        return 0;
    }

    uint64_t integerValue = 0;

    if (self == nullptr)
        return integerValue;

    switch (self->present)
    {
    case Data_PR_int8:
        integerValue = self->choice.int8;
        break;
    case Data_PR_int16:
        integerValue = self->choice.int16;
        break;
    case Data_PR_int32:
        integerValue = self->choice.int32;
        break;
    case Data_PR_int64:
        integerValue = self->choice.int64;
        break;
    case Data_PR_int8u:
        integerValue = self->choice.int8u;
        break;
    case Data_PR_int16u:
        integerValue = self->choice.int16u;
        break;
    case Data_PR_int32u:
        integerValue = self->choice.int32u;
        break;
    case Data_PR_int64u:
        integerValue = (int64_t)self->choice.int64u;
        break;
    default:
        break;
    }

    return integerValue;
};

float GspMmsValue_toFloat(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_toFloat");
        return 0;
    }

    if (self->present == Data_PR_float32)
    {
        // 4 个字节
        float val;
        uint8_t *floatVal = (uint8_t *)&val;
#if (ORDER_LITTLE_ENDIAN == 1)
        floatVal[0] = self->choice.float32.buf[3];
        floatVal[1] = self->choice.float32.buf[2];
        floatVal[2] = self->choice.float32.buf[1];
        floatVal[3] = self->choice.float32.buf[0];
#else
        floatVal[0] = self->choice.float32.buf[0];
        floatVal[1] = self->choice.float32.buf[1];
        floatVal[2] = self->choice.float32.buf[2];
        floatVal[3] = self->choice.float32.buf[3];
#endif
        return val;
    }
    else if (self->present == Data_PR_float64)
    {
        // 8 个字节
        double val;
        uint8_t *floatVal = (uint8_t *)&val;
#if (ORDER_LITTLE_ENDIAN == 1)
        floatVal[0] = self->choice.float64.buf[7];
        floatVal[1] = self->choice.float64.buf[6];
        floatVal[2] = self->choice.float64.buf[5];
        floatVal[3] = self->choice.float64.buf[4];
        floatVal[4] = self->choice.float64.buf[3];
        floatVal[5] = self->choice.float64.buf[2];
        floatVal[6] = self->choice.float64.buf[1];
        floatVal[7] = self->choice.float64.buf[0];
#else
        floatVal[0] = self->choice.float64.buf[0];
        floatVal[1] = self->choice.float64.buf[1];
        floatVal[2] = self->choice.float64.buf[2];
        floatVal[3] = self->choice.float64.buf[3];
        floatVal[4] = self->choice.float64.buf[4];
        floatVal[5] = self->choice.float64.buf[5];
        floatVal[6] = self->choice.float64.buf[6];
        floatVal[7] = self->choice.float64.buf[7];
#endif
        return val;
    }

    return 0.f;
}

double GspMmsValue_toDouble(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_toDouble");
        return 0;
    }

    if (self->present == Data_PR_float32)
    {
        // 4 个字节
        float val;
        uint8_t *floatVal = (uint8_t *)&val;
#if (ORDER_LITTLE_ENDIAN == 1)
        floatVal[0] = self->choice.float32.buf[3];
        floatVal[1] = self->choice.float32.buf[2];
        floatVal[2] = self->choice.float32.buf[1];
        floatVal[3] = self->choice.float32.buf[0];
#else
        floatVal[0] = self->choice.float32.buf[0];
        floatVal[1] = self->choice.float32.buf[1];
        floatVal[2] = self->choice.float32.buf[2];
        floatVal[3] = self->choice.float32.buf[3];
#endif
        return val;
    }
    else if (self->present == Data_PR_float64)
    {
        // 8 个字节
        double val;
        uint8_t *floatVal = (uint8_t *)&val;
#if (ORDER_LITTLE_ENDIAN == 1)
        floatVal[0] = self->choice.float64.buf[7];
        floatVal[1] = self->choice.float64.buf[6];
        floatVal[2] = self->choice.float64.buf[5];
        floatVal[3] = self->choice.float64.buf[4];
        floatVal[4] = self->choice.float64.buf[3];
        floatVal[5] = self->choice.float64.buf[2];
        floatVal[6] = self->choice.float64.buf[1];
        floatVal[7] = self->choice.float64.buf[0];
#else
        floatVal[0] = self->choice.float64.buf[0];
        floatVal[1] = self->choice.float64.buf[1];
        floatVal[2] = self->choice.float64.buf[2];
        floatVal[3] = self->choice.float64.buf[3];
        floatVal[4] = self->choice.float64.buf[4];
        floatVal[5] = self->choice.float64.buf[5];
        floatVal[6] = self->choice.float64.buf[6];
        floatVal[7] = self->choice.float64.buf[7];
#endif
        return val;
    }

    return 0.f;
}

uint32_t GspMmsValue_toUnixTimestamp(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_toUnixTimestamp");
        return 0;
    }

    uint32_t timestamp;
    uint8_t *timeArray = (uint8_t *)&timestamp;

#if (ORDER_LITTLE_ENDIAN == 1)
    timeArray[0] = self->choice.utc_time.buf[3];
    timeArray[1] = self->choice.utc_time.buf[2];
    timeArray[2] = self->choice.utc_time.buf[1];
    timeArray[3] = self->choice.utc_time.buf[0];
#else
    timeArray[0] = self->choice.utc_time.buf[0];
    timeArray[1] = self->choice.utc_time.buf[1];
    timeArray[2] = self->choice.utc_time.buf[2];
    timeArray[3] = self->choice.utc_time.buf[3];
#endif

    return timestamp;
}

uint32_t GspMmsValue_getArraySize(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getArraySize");
        return 0;
    }

    return static_cast<uint32_t>(self->choice.array.list.count);
}

uint32_t GspMmsValue_getStructSize(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getStructSize");
        return 0;
    }

    return static_cast<uint32_t>(self->choice.structure.list.count);
}

GspMmsValue *GspMmsValue_newInteger(int size)
{
    GspMmsValue *self = GspMmsValue_new();

    if (self)
    {
        if (size <= 8)
        {
            self->choice.int8 = 0;
            self->present = Data_PR_int8;
        }
        else if (size > 8 && size <= 16)
        {
            self->choice.int16 = 0;
            self->present = Data_PR_int16;
        }
        else if (size > 16 && size <= 32)
        {
            self->choice.int32 = 0;
            self->present = Data_PR_int32;
        }
        else
        {
            self->choice.int64 = 0;
            self->present = Data_PR_int64;
        }
    }

    return self;
}

GspMmsValue *GspMmsValue_newUnsigned(int size)
{
    GspMmsValue *self = GspMmsValue_new();

    if (self)
    {
        if (size <= 8)
        {
            self->choice.int8u = 0;
            self->present = Data_PR_int8u;
        }
        else if (size > 8 && size <= 16)
        {
            self->choice.int16u = 0;
            self->present = Data_PR_int16u;
        }
        else if (size > 16 && size <= 32)
        {
            self->choice.int32u = 0;
            self->present = Data_PR_int32u;
        }
        else
        {
            self->choice.int64u = 0;
            self->present = Data_PR_int64u;
        }
    }

    return self;
}

GspMmsValue *GspMmsValue_newBoolean(bool boolean)
{
    GspMmsValue *self = GspMmsValue_new();
    self->present = Data_PR_boolean;
    self->choice.boolean = boolean;
    return self;
}

GspMmsValue *GspMmsValue_newOctetString(int size, int maxSize)
{
    GspMmsValue *self = GspMmsValue_new();

    if (self)
    {
        self->present = Data_PR_octet_string;
        self->choice.octet_string.buf = (uint8_t *)calloc(size, sizeof(uint8_t));
        self->choice.octet_string.size = size;
    }

    return self;
}

void GspMmsValue_setOctetString(GspMmsValue *self, uint8_t *buf, int size)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_setOctetString");
        return;
    }

    if (size <= self->choice.octet_string.size)
    {
        memcpy(self->choice.octet_string.buf, buf, size);
        self->choice.octet_string.size = size;
    }
}

uint16_t GspMmsValue_getOctetStringSize(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getOctetStringSize");
        return 0;
    }

    return self->choice.octet_string.size;
}

uint16_t GspMmsValue_getOctetStringMaxSize(GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getOctetStringMaxSize");
        return 0;
    }

    return self->choice.octet_string.size;
}

uint8_t *GspMmsValue_getOctetStringBuffer(GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getOctetStringBuffer");
        return nullptr;
    }

    return self->choice.octet_string.buf;
}

GspMmsValue *GspMmsValue_newStructure(const GspMmsVariableSpecification *typeSpec)
{
    if (!typeSpec)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_newStructure");
        return nullptr;
    }

    GspMmsValue *self = GspMmsValue_new();

    if (self)
    {
        self->present = Data_PR_structure;
        int componentCount = typeSpec->typeSpec.structure.elementCount;
        for (int i = 0; i < componentCount; i++)
        {
            ASN_SEQUENCE_ADD(&self->choice.structure, GspMmsValue_newDefaultValue(typeSpec->typeSpec.structure.elements[i]));
        }
    }

    return self;
}

GspMmsValue *GspMmsValue_newDefaultValue(const GspMmsVariableSpecification *typeSpec)
{
    if (!typeSpec)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_newDefaultValue");
        return nullptr;
    }

    GspMmsValue *self = nullptr;

    // 依据数据类型进行创建
    switch (typeSpec->type)
    {
    case GSP_MMS_INT8:
        self = GspMmsValue_newInteger(8);
        break;

    case GSP_MMS_INT16:
        self = GspMmsValue_newInteger(16);
        break;

    case GSP_MMS_INT32:
        self = GspMmsValue_newInteger(32);
        break;

    case GSP_MMS_INT64:
        self = GspMmsValue_newInteger(64);
        break;
    case GSP_MMS_UINT8:
        self = GspMmsValue_newUnsigned(8);
        break;

    case GSP_MMS_UINT16:
        self = GspMmsValue_newUnsigned(16);
        break;

    case GSP_MMS_UINT32:
        self = GspMmsValue_newUnsigned(32);
        break;

    case GSP_MMS_UINT64:
        self = GspMmsValue_newUnsigned(64);
        break;
    case GSP_MMS_FLOAT32:
        self = GspMmsValue_new();
        self->present = Data_PR_float32;
        self->choice.float32.buf = (uint8_t *)calloc(4, sizeof(uint8_t));
        self->choice.float32.size = 4;
        break;

    case GSP_MMS_FLOAT64:
        self = GspMmsValue_new();
        self->present = Data_PR_float64;
        self->choice.float64.buf = (uint8_t *)calloc(8, sizeof(uint8_t));
        self->choice.float64.size = 8;
        break;

    case GSP_MMS_BIT_STRING:
        self = GspMmsValue_new();
        self->choice.bit_string.bits_unused = 8;
        self->choice.bit_string.size = 0;
        self->choice.bit_string.buf = nullptr;
        self->present = Data_PR_bit_string;
        break;

    case GSP_MMS_OCTET_STRING:
        self = GspMmsValue_new();
        OCTET_STRING_fromBuf(&self->choice.octet_string, nullptr, -1);
        break;

    case GSP_MMS_VISIBLE_STRING:
        self = GspMmsValue_newVisibleStringWithSize(abs(typeSpec->typeSpec.visibleString));
        break;

    case GSP_MMS_UNICODE_STRING:
        self = GspMmsValue_newMmsStringWithSize(abs(typeSpec->typeSpec.unicodeString));
        break;

    case GSP_MMS_BOOLEAN:
        self = GspMmsValue_newBoolean(false);
        break;

    case GSP_MMS_UTC_TIME:
        self = GspMmsValue_newUtcTimeByMsTime(0);
        break;

    case GSP_MMS_ARRAY:
        self = GspMmsValue_createArray(typeSpec->typeSpec.array.elementTypeSpec, typeSpec->typeSpec.array.elementCount);
        break;

    case GSP_MMS_STRUCTURE:
        self = GspMmsValue_newStructure(typeSpec);
        break;

    case GSP_MMS_BINARY_TIME:
        if (typeSpec->typeSpec.binaryTime == 4)
        {
            self = GspMmsValue_newBinaryTime(true);
        }
        else
        {
            self = GspMmsValue_newBinaryTime(false);
        }
        break;
    case GSP_MMS_ENUM:
        self = GspMmsValue_newInteger(8);
        break;
    case GSP_MMS_QUALITY:
        self = GspMmsValue_newQuality();
        break;
    case GSP_MMS_DBPOS:
        self = GspMmsValue_newBitString(2);
        self->present = Data_PR_dbpos;
        break;
    case GSP_MMS_TCMD:
        self = GspMmsValue_newBitString(2);
        self->present = Data_PR_tcmd;
        break;
    default:
        break;
    }

    return self;
}

static GspMmsValue *MmsValue_newString(const char *string, Data_PR type)
{
    if (!string)
    {
        Global_LogString("mms_value MmsValue_newString 操作时,参数异常\n");
        assert(ERROR_JUST_LOG);
        return nullptr;
    }

    GspMmsValue *self = GspMmsValue_new();

    self->present = type;
    setVisibleStringValue(self, string);

    return self;
}

GspMmsValue *GspMmsValue_newVisibleString(const char *string)
{
    if (!string)
    {
        Global_LogString("mms_value GspMmsValue_newVisibleString 操作时,参数异常\n");
        assert(ERROR_JUST_LOG);
        return nullptr;
    }

    return MmsValue_newString(string, Data_PR_visible_string);
}

static GspMmsValue *MmsValue_newStringWithSize(int size, Data_PR type)
{
    GspMmsValue *self = GspMmsValue_new();
    self->present = type;
    return self;
}

GspMmsValue *GspMmsValue_newVisibleStringWithSize(int size)
{
    return MmsValue_newStringWithSize(size, Data_PR_visible_string);
}

GspMmsValue *GspMmsValue_newMmsString(const char *string)
{
    if (!string)
    {
        Global_LogString("mms_value GspMmsValue_newMmsString 操作时,参数异常\n");
        assert(ERROR_JUST_LOG);
        return nullptr;
    }

    return MmsValue_newString(string, Data_PR_unicode_string);
}

GspMmsValue *GspMmsValue_newMmsStringWithSize(int size)
{
    return MmsValue_newStringWithSize(size, Data_PR_unicode_string);
}

GspMmsValue *GspMmsValue_newBinaryTime(bool timeOfDay)
{
    GspMmsValue *self = GspMmsValue_new();

    if (self)
    {
        self->present = Data_PR_binary_time;
        if (timeOfDay)
        {
            OCTET_STRING_fromBuf(&self->choice.binary_time, "", 4);
        }
        else
        {
            OCTET_STRING_fromBuf(&self->choice.binary_time, "", 6);
        }
    }
    return self;
}

void BinaryTime_newTimeFromTimeStamp(BinaryTime_t *time, uint64_t timestamp)
{
    if (!time)
    {
        Global_LogString("mms_value BinaryTime_newTimeFromTimeStamp 操作时,参数异常\n");
        assert(ERROR_JUST_LOG);
        return;
    }

    uint64_t mmsTime;

    if (timestamp > 441763200000LL)
        mmsTime = timestamp - (441763200000LL);
    else
        mmsTime = 0;

    time->buf = (uint8_t *)calloc(1, 6);
    time->size = 6;
    uint8_t *binaryTimeBuf = time->buf;

    if (time->size == 6)
    {
        uint16_t daysDiff = mmsTime / (86400000LL);
        uint8_t *daysDiffBuf = (uint8_t *)&daysDiff;

#if (ORDER_LITTLE_ENDIAN == 1)
        binaryTimeBuf[4] = daysDiffBuf[1];
        binaryTimeBuf[5] = daysDiffBuf[0];
#else
        binaryTimeBuf[4] = daysDiffBuf[0];
        binaryTimeBuf[5] = daysDiffBuf[1];
#endif
    }

    uint32_t msSinceMidnight = mmsTime % (86400000LL);
    uint8_t *msSinceMidnightBuf = (uint8_t *)&msSinceMidnight;

#if (ORDER_LITTLE_ENDIAN == 1)
    binaryTimeBuf[0] = msSinceMidnightBuf[3];
    binaryTimeBuf[1] = msSinceMidnightBuf[2];
    binaryTimeBuf[2] = msSinceMidnightBuf[1];
    binaryTimeBuf[3] = msSinceMidnightBuf[0];
#else
    binaryTimeBuf[0] = msSinceMidnightBuf[0];
    binaryTimeBuf[1] = msSinceMidnightBuf[1];
    binaryTimeBuf[2] = msSinceMidnightBuf[2];
    binaryTimeBuf[3] = msSinceMidnightBuf[3];
#endif
}

void GspMmsValue_setBinaryTime(GspMmsValue *self, uint64_t timestamp)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_setBinaryTime");
        return;
    }

    uint64_t mmsTime;

    if (timestamp > 441763200000LL)
        mmsTime = timestamp - (441763200000LL);
    else
        mmsTime = 0;

    uint8_t *binaryTimeBuf = self->choice.binary_time.buf;

    if (self->choice.binary_time.size == 6)
    {
        uint16_t daysDiff = mmsTime / (86400000LL);
        uint8_t *daysDiffBuf = (uint8_t *)&daysDiff;

#if (ORDER_LITTLE_ENDIAN == 1)
        binaryTimeBuf[4] = daysDiffBuf[1];
        binaryTimeBuf[5] = daysDiffBuf[0];
#else
        binaryTimeBuf[4] = daysDiffBuf[0];
        binaryTimeBuf[5] = daysDiffBuf[1];
#endif
    }

    uint32_t msSinceMidnight = mmsTime % (86400000LL);
    uint8_t *msSinceMidnightBuf = (uint8_t *)&msSinceMidnight;

#if (ORDER_LITTLE_ENDIAN == 1)
    binaryTimeBuf[0] = msSinceMidnightBuf[3];
    binaryTimeBuf[1] = msSinceMidnightBuf[2];
    binaryTimeBuf[2] = msSinceMidnightBuf[1];
    binaryTimeBuf[3] = msSinceMidnightBuf[0];
#else
    binaryTimeBuf[0] = msSinceMidnightBuf[0];
    binaryTimeBuf[1] = msSinceMidnightBuf[1];
    binaryTimeBuf[2] = msSinceMidnightBuf[2];
    binaryTimeBuf[3] = msSinceMidnightBuf[3];
#endif
}

uint64_t GspMmsValue_getBinaryTimeAsUtcMs(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getBinaryTimeAsUtcMs");
        return 0;
    }

    uint64_t timestamp = 0;

    return BinaryTime_getAsUtcMs(const_cast<BinaryTime_t *>(&self->choice.binary_time));
}

uint64_t BinaryTime_getAsUtcMs(BinaryTime_t *time)
{
    uint64_t timestamp = 0;

    const uint8_t *binaryTimeBuf = time->buf;

    if (time->size == 6)
    {
        uint16_t daysDiff;
        daysDiff = binaryTimeBuf[4] * 256;
        daysDiff += binaryTimeBuf[5];
        uint64_t mmsTime;
        mmsTime = daysDiff * (86400000LL);
        timestamp = mmsTime + (441763200000LL);
    }

    uint32_t msSinceMidnight = 0;

    msSinceMidnight = binaryTimeBuf[0] << 24;
    msSinceMidnight += binaryTimeBuf[1] << 16;
    msSinceMidnight += binaryTimeBuf[2] << 8;
    msSinceMidnight += binaryTimeBuf[3];

    timestamp += msSinceMidnight;

    return timestamp;
}

uint8_t *GspMmsValue_getBinaryTimeBuffer(GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getBinaryTimeBuffer");
        return nullptr;
    }

    return self->choice.binary_time.buf;
}

int GspMmsValue_getBinaryTimeSize(const GspMmsValue *self)
{
    return self->choice.binary_time.size;
}

ServiceError_t GspMmsValue_getDataAccessError(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getDataAccessError");
        return 0;
    }

    return self->choice.error;
}

static GspMmsValue *MmsValue_newStringFromByteArray(const uint8_t *byteArray, int size, GspMmsType type)
{
    if (!byteArray)
    {
        Global_LogString("mms_value MmsValue_newStringFromByteArray 操作时,参数异常\n");
        assert(ERROR_JUST_LOG);
        return nullptr;
    }

    GspMmsValue *self = GspMmsValue_new();
    self->present = Data_PR_visible_string;
    OCTET_STRING_fromBuf(&self->choice.visible_string, (const char *)byteArray, size);
    return self;
}

GspMmsValue *GspMmsValue_newVisibleStringFromByteArray(uint8_t *byteArray, int size)
{
    if (!byteArray)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_newVisibleStringFromByteArray");
        return nullptr;
    }

    return MmsValue_newStringFromByteArray(byteArray, size, GSP_MMS_VISIBLE_STRING);
}

void GspMmsValue_setVisibleString(GspMmsValue *self, const char *string)
{
    if (!self || !string)
    {
        Global_LogString("mms_value GspMmsValue_setVisibleString 操作时,参数异常\n");
        assert(ERROR_JUST_LOG);
        return;
    }

    if (self->present == Data_PR_visible_string)
    {
        setVisibleStringValue(self, string);
    }
}

const char *GspMmsValue_toString(GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_toString");
        return nullptr;
    }

    return (const char *)self->choice.visible_string.buf;
}

int GspMmsValue_getStringSize(GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getStringSize");
        return 0;
    }

    return self->choice.unicode_string.size;
}

GspMmsValue *GspMmsValue_newUtcTime(uint32_t timeval)
{
    GspMmsValue *self = GspMmsValue_new();

    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_newUtcTime");
        return nullptr;
    }

    self->present = Data_PR_utc_time;

    // 分配内存
    OCTET_STRING_fromBuf(&self->choice.utc_time, "", 8);

    // 赋值
    uint8_t *timeArray = (uint8_t *)&timeval;
    uint8_t *valueArray = self->choice.utc_time.buf;

#if (ORDER_LITTLE_ENDIAN == 1)
    valueArray[0] = timeArray[3];
    valueArray[1] = timeArray[2];
    valueArray[2] = timeArray[1];
    valueArray[3] = timeArray[0];
#else
    valueArray[0] = timeArray[0];
    valueArray[1] = timeArray[1];
    valueArray[2] = timeArray[2];
    valueArray[3] = timeArray[3];
#endif
    return self;
}

GspMmsValue *GspMmsValue_newUtcTimeByMsTime(uint64_t timeval)
{
    GspMmsValue *self = GspMmsValue_new();

    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_newUtcTimeByMsTime");
        return nullptr;
    }

    self->present = Data_PR_utc_time;
    GspMmsValue_setUtcTimeMs(self, timeval);

    return self;
}

GspMmsValue *GspMmsValue_createArray(GspMmsVariableSpecification *elementType, int size)
{
    if (!elementType)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_createArray");
        return nullptr;
    }

    // 分配内存
    GspMmsValue *self = GspMmsValue_new();

    // 数据初始化
    for (int i = 0; i < size; i++)
    {
        ASN_SEQUENCE_ADD(&self->choice.structure, GspMmsValue_newDefaultValue(elementType));
    }
    return self;
}

GspMmsValue *GspMmsValue_createEmptyArray(int size)
{
    // 内存分配
    GspMmsValue *self = GspMmsValue_new();

    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_createArray");
        return nullptr;
    }

    // 数据初始化
    for (int i = 0; i < size; i++)
    {
        ASN_SEQUENCE_ADD(&self->choice.structure, (void *)(uintptr_t)0x1);
    }
    return self;
}

GspMmsValue *GspMmsValue_createEmptyStructure(int size)
{
    GspMmsValue *self = GspMmsValue_createEmptyArray(size);

    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_createEmptyStructure");
        return nullptr;
    }

    self->present = Data_PR_structure;

    return self;
}

void GspMmsValue_setElement(GspMmsValue *complexValue, int index, GspMmsValue *elementValue)
{
    if (!complexValue || !elementValue)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_setElement");
        return;
    }

    if ((complexValue->present != Data_PR_array) && (complexValue->present != Data_PR_structure))
        return;

    if ((index < 0) || (index >= complexValue->choice.structure.list.count))
        return;

    complexValue->choice.structure.list.array[index] = elementValue;
}

GspMmsValue *GspMmsValue_getElement(const GspMmsValue *complexValue, int index)
{
    if (!complexValue)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getElement");
        return nullptr;
    }

    if ((complexValue->present != Data_PR_array) && (complexValue->present != Data_PR_structure))
        return nullptr;

    if ((index < 0) || (index >= complexValue->choice.structure.list.count))
        return nullptr;

    return complexValue->choice.structure.list.array[index];
}

void GspMmsValue_setDeletable(GspMmsValue * /*self*/)
{
    // self->deleteValue = 1;
}

void GspMmsValue_setDeletableRecursive(GspMmsValue *self)
{
    if (!self)
    {
        NLOG_ERROR("mms_value {} 操作时，参数异常", "GspMmsValue_setDeletableRecursive");
        return;
    }

    if ((GspMmsValue_getType(self) == Data_PR_array) || (GspMmsValue_getType(self) == Data_PR_structure))
    {
        int i;
        int elementCount = GspMmsValue_getArraySize(self);
        for (i = 0; i < elementCount; i++)
        {
            GspMmsValue_setDeletableRecursive(GspMmsValue_getElement(self, i));
        }
    }

    GspMmsValue_setDeletable(self);
}

Data_PR GspMmsValue_getType(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getType");
        return Data_PR_NOTHING;
    }

    return self->present;
}

GspMmsValue *GspMmsValue_getSubElement(GspMmsValue *self, GspMmsVariableSpecification *varSpec, char *mmsPath)
{
    if (!self || !varSpec || !mmsPath)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_getSubElement");
        return nullptr;
    }

    return GSP::GspMmsVariableSpecification_getChildValue(varSpec, self, mmsPath);
}

GspMmsValue *GspMmsValue_newIntegerFromUint8(uint8_t integer)
{
    GspMmsValue *self = GspMmsValue_new();
    self->present = Data_PR_int8u;
    self->choice.int8u = integer;
    return self;
}

GspMmsValue *GspMmsValue_newIntegerFromUint16(uint16_t integer)
{
    GspMmsValue *self = GspMmsValue_new();
    self->present = Data_PR_int16u;
    self->choice.int16u = integer;
    return self;
}

GspMmsValue *GspMmsValue_newUnsignedFromUint64(uint64_t integer)
{
    GspMmsValue *self = GspMmsValue_new();
    self->present = Data_PR_int64u;
    self->choice.int64u = integer;
    return self;
}

void GspMmsValue_delete(GspMmsValue *self)
{
    // 内存释放配置
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_delete");
        return;
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_Data, self);
}

bool GspMmsValue_cloneFromOther(GspMmsValue *target, const GspMmsValue *source)
{
    // 异常判断
    if (!target || !source)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_cloneFromOther");
        return false;
    }

    // 类型复制
    target->present = source->present;
    switch (target->present)
    {
    case Data_PR_structure:
    case Data_PR_array:
    {
        // 元素个数
        int count = source->choice.structure.list.count;
        int size = source->choice.structure.list.size;
        target->choice.structure.list.count = count;
        target->choice.structure.list.size = size;

        // 分配内存
        target->choice.structure.list.array = (GspMmsValue **)GLOBAL_CALLOC(count, sizeof(GspMmsValue *));

        // 逐个递归

        for (int i = 0; i < count; i++)
        {
            GspMmsValue_cloneFromOther(target->choice.structure.list.array[i], source->choice.structure.list.array[i]);
        }
    }
    break;
    case Data_PR_boolean:
        target->choice.boolean = source->choice.boolean;
        break;
    case Data_PR_float64:
    {
        size_t size = source->choice.float64.size;
        target->choice.float64.buf = (uint8_t *)calloc(size, sizeof(uint8_t));
        target->choice.float64.size = size;
        memcpy(target->choice.float64.buf, source->choice.float64.buf, size);
    }
    break;
    case Data_PR_float32:
    {
        size_t size = source->choice.float32.size;
        target->choice.float32.buf = (uint8_t *)calloc(size, sizeof(uint8_t));
        target->choice.float32.size = size;
        memcpy(target->choice.float32.buf, source->choice.float32.buf, size);
    }
    break;
    case Data_PR_utc_time:
    {
        size_t size = source->choice.utc_time.size;
        target->choice.utc_time.buf = (uint8_t *)calloc(size, sizeof(uint8_t));
        target->choice.utc_time.size = size;
        memcpy(target->choice.utc_time.buf, source->choice.utc_time.buf, size);
    }
    break;
    case Data_PR_quality:
    {
        target->choice.quality.size = source->choice.quality.size;
        target->choice.quality.bits_unused = source->choice.quality.bits_unused;
        target->choice.quality.buf = (uint8_t *)calloc(target->choice.quality.size, sizeof(uint8_t));
        memcpy(target->choice.quality.buf, source->choice.quality.buf, target->choice.quality.size);
    }
    break;
    case Data_PR_bit_string:
    {
        target->choice.bit_string.size = source->choice.bit_string.size;
        target->choice.bit_string.bits_unused = source->choice.bit_string.bits_unused;
        target->choice.bit_string.buf = (uint8_t *)calloc(target->choice.bit_string.size, sizeof(uint8_t));
        memcpy(target->choice.bit_string.buf, source->choice.bit_string.buf, target->choice.bit_string.size);
    }
    break;
    case Data_PR_octet_string:
    {
        size_t size = source->choice.octet_string.size;
        target->choice.octet_string.buf = (uint8_t *)calloc(size, sizeof(uint8_t));
        target->choice.octet_string.size = size;
        memcpy(target->choice.octet_string.buf, source->choice.octet_string.buf, size);
    }
    break;
    case Data_PR_visible_string:
        GspMmsValue_setVisibleString(target, (const char *)source->choice.visible_string.buf);
        break;
    case Data_PR_unicode_string:
    {
        size_t size = source->choice.unicode_string.size;
        target->choice.unicode_string.buf = (uint8_t *)calloc(size, sizeof(uint8_t));
        target->choice.unicode_string.size = size;
        memcpy(target->choice.unicode_string.buf, source->choice.unicode_string.buf, size);
    }
    break;
    case Data_PR_binary_time:
    {
        size_t size = source->choice.binary_time.size;
        target->choice.binary_time.buf = (uint8_t *)calloc(size, sizeof(uint8_t));
        target->choice.binary_time.size = size;
        memcpy(target->choice.binary_time.buf, source->choice.binary_time.buf, size);
    }
    break;
    case Data_PR_int8:
        target->choice.int8 = source->choice.int8;
        break;
    case Data_PR_int16:
        target->choice.int16 = source->choice.int16;
        break;
    case Data_PR_int32:
        target->choice.int32 = source->choice.int32;
        break;
    case Data_PR_int64:
        target->choice.int64 = source->choice.int64;
        break;
    case Data_PR_int8u:
        target->choice.int8u = source->choice.int8u;
        break;
    case Data_PR_int16u:
        target->choice.int16u = source->choice.int16u;
        break;
    case Data_PR_int32u:
        target->choice.int32u = source->choice.int32u;
        break;
    case Data_PR_int64u:
        target->choice.int64u = source->choice.int64u;
        break;
    }

    return true;
}

GspMmsValue *GspMmsValue_clone(const GspMmsValue *self)
{
    // 异常判断
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_clone");
        return nullptr;
    }

    // 申请一块内存
    GspMmsValue *newValue = GspMmsValue_new();

    // 类型复制
    newValue->present = self->present;

    // 逐个类型克隆
    switch (self->present)
    {
    case Data_PR_structure:
    case Data_PR_array:
    {
        // 元素个数
        int count = self->choice.structure.list.count;
        int size = self->choice.structure.list.size;
        newValue->choice.structure.list.count = count;
        newValue->choice.structure.list.size = size;

        // 分配内存
        newValue->choice.structure.list.array = (GspMmsValue **)GLOBAL_CALLOC(count, sizeof(GspMmsValue *));

        // 逐个递归
        for (int i = 0; i < count; i++)
        {
            newValue->choice.structure.list.array[i] = GspMmsValue_clone(self->choice.structure.list.array[i]);
        }
    }
    break;
    case Data_PR_boolean:
        newValue->choice.boolean = self->choice.boolean;
        break;
    case Data_PR_float64:
    {
        size_t size = self->choice.float64.size;
        newValue->choice.float64.buf = (uint8_t *)calloc(size, sizeof(uint8_t));
        newValue->choice.float64.size = size;
        memcpy(newValue->choice.float64.buf, self->choice.float64.buf, size);
    }
    break;
    case Data_PR_float32:
    {
        size_t size = self->choice.float32.size;
        newValue->choice.float32.buf = (uint8_t *)calloc(size, sizeof(uint8_t));
        newValue->choice.float32.size = size;
        memcpy(newValue->choice.float32.buf, self->choice.float32.buf, size);
    }
    break;
    case Data_PR_utc_time:
    {
        size_t size = self->choice.utc_time.size;
        newValue->choice.utc_time.buf = (uint8_t *)calloc(size, sizeof(uint8_t));
        newValue->choice.utc_time.size = size;
        memcpy(newValue->choice.utc_time.buf, self->choice.utc_time.buf, size);
    }
    break;
    case Data_PR_quality:
    {
        newValue->choice.quality.size = self->choice.quality.size;
        newValue->choice.quality.bits_unused = self->choice.quality.bits_unused;
        newValue->choice.quality.buf = (uint8_t *)calloc(newValue->choice.quality.size, sizeof(uint8_t));
        memcpy(newValue->choice.quality.buf, self->choice.quality.buf, newValue->choice.quality.size);
    }
    break;
    case Data_PR_dbpos:
    {
        newValue->choice.dbpos.size = self->choice.dbpos.size;
        newValue->choice.dbpos.bits_unused = self->choice.dbpos.bits_unused;
        newValue->choice.dbpos.buf = (uint8_t *)calloc(newValue->choice.dbpos.size, sizeof(uint8_t));
        memcpy(newValue->choice.dbpos.buf, self->choice.dbpos.buf, newValue->choice.dbpos.size);
    }
    break;
    case Data_PR_tcmd:
    {
        newValue->choice.tcmd.size = self->choice.tcmd.size;
        newValue->choice.tcmd.bits_unused = self->choice.tcmd.bits_unused;
        newValue->choice.tcmd.buf = (uint8_t *)calloc(newValue->choice.tcmd.size, sizeof(uint8_t));
        memcpy(newValue->choice.tcmd.buf, self->choice.tcmd.buf, newValue->choice.tcmd.size);
    }
    break;
    case Data_PR_bit_string:

    {
        newValue->choice.bit_string.size = self->choice.bit_string.size;
        newValue->choice.bit_string.bits_unused = self->choice.bit_string.bits_unused;
        newValue->choice.bit_string.buf = (uint8_t *)calloc(newValue->choice.bit_string.size, sizeof(uint8_t));
        memcpy(newValue->choice.bit_string.buf, self->choice.bit_string.buf, newValue->choice.bit_string.size);
    }
    break;
    case Data_PR_octet_string:
    {
        size_t size = self->choice.octet_string.size;
        newValue->choice.octet_string.buf = (uint8_t *)calloc(size + 1, sizeof(uint8_t));
        newValue->choice.octet_string.size = size;
        memcpy(newValue->choice.octet_string.buf, self->choice.octet_string.buf, size);
    }
    break;
    case Data_PR_visible_string:
        GspMmsValue_setVisibleString(newValue, (const char *)self->choice.visible_string.buf);
        break;
    case Data_PR_unicode_string:
    {
        size_t size = self->choice.unicode_string.size;
        newValue->choice.unicode_string.buf = (uint8_t *)calloc(size + 1, sizeof(uint8_t));
        newValue->choice.unicode_string.size = size;
        memcpy(newValue->choice.unicode_string.buf, self->choice.unicode_string.buf, size);
    }
    break;
    case Data_PR_binary_time:
    {
        size_t size = self->choice.binary_time.size;
        newValue->choice.binary_time.buf = (uint8_t *)calloc(size, sizeof(uint8_t));
        newValue->choice.binary_time.size = size;
        memcpy(newValue->choice.binary_time.buf, self->choice.binary_time.buf, size);
    }
    break;
    case Data_PR_int8:
        newValue->choice.int8 = self->choice.int8;
        break;
    case Data_PR_int16:
        newValue->choice.int16 = self->choice.int16;
        break;

    case Data_PR_int32:
        newValue->choice.int32 = self->choice.int32;
        break;

    case Data_PR_int64:
        newValue->choice.int64 = self->choice.int64;
        break;

    case Data_PR_int8u:
        newValue->choice.int8u = self->choice.int8u;
        break;

    case Data_PR_int16u:
        newValue->choice.int16u = self->choice.int16u;
        break;

    case Data_PR_int32u:
        newValue->choice.int32u = self->choice.int32u;
        break;

    case Data_PR_int64u:
        newValue->choice.int64u = self->choice.int64u;
        break;
    default:
        break;
    }

    return newValue;
}

void GspBIT_STRING_createBitString(BIT_STRING_t *bitString, const char *buf, int size, int bitUnused)
{
    if (!bitString)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspBIT_STRING_createBitString");
        return;
    }

    if (!bitString->buf)
    {
        bitString->buf = (uint8_t *)calloc(size, sizeof(uint8_t));
    }

    if (buf)
    {
        memcpy(bitString->buf, buf, size);
    }

    bitString->size = size;
    bitString->bits_unused = bitUnused;
}

GspMmsValue *GspMmsValue_new()
{
    GspMmsValue *value = (GspMmsValue *)calloc(1, sizeof(GspMmsValue));
    return value;
}

void GspBIT_STRING_setBit(BIT_STRING_t *bitString, int bitPos, bool state)
{
    if (!bitString)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspBIT_STRING_setBit");
        return;
    }

    int bytePos = bitPos / 8;
    int bitPosInByte = 7 - (bitPos % 8);
    int bitMask = (1 << bitPosInByte);

    if (state)
    {
        bitString->buf[bytePos] |= bitMask;
    }
    else
    {
        bitString->buf[bytePos] &= (~bitMask);
    }
}

void GspMmsValue_printToBuffer(const GspMmsValue *self)
{
    if (!self)
    {
        NLOG_WARN("mms_value {} 操作时，参数异常", "GspMmsValue_printToBuffer");
        return;
    }
    xer_fprint(stdout, &asn_DEF_Data, self);
}

ServiceError_t GspMmsDataAccessErrorToServiceError(GspMmsDataAccessError dataError)
{
    ServiceError_t error = ServiceError_access_not_allowed_in_current_state;
    switch (dataError)
    {
    case GSP_DATA_ACCESS_ERROR_SUCCESS:
        error = ServiceError_no_error;
        break;
    case GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE:
    case GSP_DATA_ACCESS_ERROR_OBJECT_INVALIDATED:
    case GSP_DATA_ACCESS_ERROR_OBJECT_UNDEFINED:
    case GSP_DATA_ACCESS_ERROR_INVALID_ADDRESS:
    case GSP_DATA_ACCESS_ERROR_OBJECT_NONE_EXISTENT:
        error = ServiceError_instance_not_available;
        break;
    case GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED:
    case GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_UNSUPPORTED:
        error = ServiceError_access_violation;
        break;
    case GSP_DATA_ACCESS_ERROR_TYPE_UNSUPPORTED:
    case GSP_DATA_ACCESS_ERROR_TYPE_INCONSISTENT:
        error = ServiceError_class_not_supported;
        break;
    case GSP_DATA_ACCESS_ERROR_OBJECT_ATTRIBUTE_INCONSISTENT:
    case GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID:
        error = ServiceError_failed_due_to_server_constraint;
        break;
    case GSP_DATA_ACCESS_ERROR_HARDWARE_FAULT:
    case GSP_DATA_ACCESS_ERROR_NO_RESPONSE:
    case GSP_DATA_ACCESS_ERROR_UNKNOWN:
        break;
    default:
        break;
    }
    return error;
}

void GspMmsValueToBuffer(const GspMmsValue *self, vector<char> &buffer)
{
    // TODO
}

void GspMmsValueFromBuffer(GspMmsValue *self, const vector<char> &buffer)
{
    // TODO
}

string GspMmsValueToPrint(const GspMmsValue *self)
{
#ifdef USE_LOGGING_H
    if(!self)
#endif
    {
        return "";
    }
#ifdef USE_LOGGING_H
    string result;
    switch (self->present)
    {
    case Data_PR_NOTHING:
        break;
    case Data_PR_error:
        break;
    case Data_PR_array:
        break;
    case Data_PR_structure:
        break;
    case Data_PR_boolean:
    {
        result = (self->choice.boolean ? "True" : "False");
    }
    break;
    case Data_PR_int8:
    {
        result = fmt::format("{}", self->choice.int8);
    }
    break;
    case Data_PR_int16:
    {
        result = fmt::format("{}", self->choice.int16);
    }
    break;
    case Data_PR_int32:
    {
        result = fmt::format("{}", self->choice.int32);
    }
    break;
    case Data_PR_int64:
    {
        result = fmt::format("{}", self->choice.int64);
    }
    break;
    case Data_PR_int8u:
    {
        result = fmt::format("{}", self->choice.int8u);
    }
    break;
    case Data_PR_int16u:
    {
        result = fmt::format("{}", self->choice.int16u);
    }
    break;
    case Data_PR_int32u:
    {
        result = fmt::format("{}", self->choice.int32u);
    }
    break;
    case Data_PR_int64u:
    {
        result = fmt::format("{}", self->choice.int64u);
    }
    break;
    case Data_PR_float32:
    {
        result = fmt::format("{}", *(float *)self->choice.float32.buf);
    }
    break;
    case Data_PR_float64:
    {
        result = fmt::format("{}", *(double *)self->choice.float64.buf);
    }
    break;
    case Data_PR_bit_string:
    case Data_PR_quality:
    case Data_PR_dbpos:
    case Data_PR_tcmd:
    case Data_PR_check:
    {
        for(auto i = 0; i < self->choice.bit_string.size; ++i)
        {
            bitset<8> data(self->choice.bit_string.buf[i]);
            result += data.to_string();
        }
        
        for(auto i = 0; i < self->choice.bit_string.bits_unused; ++i)
        {
            result.pop_back();
        }
    }
        break;
    case Data_PR_octet_string:
    case Data_PR_visible_string:
    case Data_PR_unicode_string:
    {
        if(self->choice.visible_string.size)
        {
            result = (char *)self->choice.visible_string.buf;
        }
    }
        break;
    case Data_PR_utc_time:
    {
        auto ms = 0;
        uint32_t us = 0;
        ms = GspMmsValue_getUtcTimeInMsWithUs(self, &us);
        auto msTime = chrono::milliseconds(ms);
        chrono::time_point<chrono::system_clock> timePoint(msTime);
        result = fmt::format("{:%Y-%m-%d %H:%M:%S}", timePoint);
    }
        break;
    case Data_PR_binary_time:
    {
        auto ms = GspMmsValue_getBinaryTimeAsUtcMs(self);
        auto msTime = chrono::milliseconds(ms);
        chrono::time_point<chrono::system_clock> timePoint(msTime);
        result = fmt::format("{:%Y-%m-%d %H:%M:%S}", timePoint);
    }
        break;
    default:
        break;
    }
    return result;
#endif
}

GspMmsValue *GspMmsValueFromPrint(const string &value, int type)
{
#ifdef USE_LOGGING_H
    try
    {
    switch (type)
    {
    case Data_PR_NOTHING:
        break;
    case Data_PR_error:
        break;
    case Data_PR_array:
        break;
    case Data_PR_structure:
        break;
    case Data_PR_boolean:
    {
        return GspMmsValue_newBoolean(
            (strcasecmp(value.c_str(), "true") == 0 || value == "1") ? true : false
            );
    }
    break;
    case Data_PR_int8:
    {
        return GspMmsValue_newIntegerFromInt8((int8_t)stoi(value));
    }
    break;
    case Data_PR_int16:
    {
        return GspMmsValue_newIntegerFromInt16((int16_t)stoi(value));
    }
    break;
    case Data_PR_int32:
    {
        return GspMmsValue_newIntegerFromInt32((int32_t)stoi(value));
    }
    break;
    case Data_PR_int64:
    {
        return GspMmsValue_newIntegerFromInt64((int64_t)stol(value));
    }
    break;
    case Data_PR_int8u:
    {
        return GspMmsValue_newIntegerFromUint8((uint8_t)stoul(value));
    }
    break;
    case Data_PR_int16u:
    {
        return GspMmsValue_newIntegerFromUint16((uint16_t)stoul(value));
    }
    break;
    case Data_PR_int32u:
    {
        return GspMmsValue_newUnsignedFromUint32((uint32_t)stoul(value));
    }
    break;
    case Data_PR_int64u:
    {
        return GspMmsValue_newUnsignedFromUint64((uint64_t)stoul(value));
    }
    break;
    case Data_PR_float32:
    {
        return GspMmsValue_newFloat(stof(value));
    }
    break;
    case Data_PR_float64:
    {
        return GspMmsValue_newDouble(stod(value));
    }
    break;
    case Data_PR_bit_string:
    case Data_PR_quality:
    case Data_PR_dbpos:
    case Data_PR_tcmd:
    case Data_PR_check:
    {
        auto mmsValue = GspMmsValue_newBitString(value.size());
        for(size_t i = 0; i < value.size(); ++i)
        {
            GspBIT_STRING_setBit(&mmsValue->choice.bit_string, i, value[i] == '1');
        }
        return mmsValue;
    }
        break;
    case Data_PR_octet_string:
    case Data_PR_visible_string:
    case Data_PR_unicode_string:
    {
        auto mmsValue = GspMmsValue_newMmsStringWithSize(value.size());
#ifdef USE_LOGGING_H
        OCTET_STRING_fromString(&mmsValue->choice.octet_string, value.c_str());
#endif
        return mmsValue;
    }
        break;
    case Data_PR_utc_time:
    {
        // auto mmsValue = GspMmsValue_newUtcTimeByMsTime();
        // return mmsValue;
    }
        break;
    case Data_PR_binary_time:
    {
        // auto mmsValue = GspMmsValue_newBinaryTime(false);
        // GspMmsValue_setBinaryTime(mmsValue, ms);
        // return mmsValue;
    }
        break;
    default:
        break;
    }
    }
    catch(const std::invalid_argument &args)
    {
        return nullptr;
    }
#endif
    return nullptr;
}

int GspMmsValue_getDbPosSize(GspMmsValue *self)
{
    return self->choice.dbpos.size;
}
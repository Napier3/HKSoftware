#ifndef ATTRIBUTETYPE_H
#define ATTRIBUTETYPE_H

#include <map>
#include <string>
#include "common.h"

using namespace std;
namespace scd {

class AttributeType
{
public:
    enum TYPE {
        BOOLEAN, /* int */
        INT8, /* int8_t */
        INT16, /* int16_t */
        INT32, /* int32_t */
        INT64, /* int64_t */
        INT128,
        INT8U, /* uint8_t */
        INT16U, /* uint16_t */
        INT24U, /* uint32_t */
        INT32U, /* uint32_t */
        FLOAT32, /* float */
        FLOAT64, /* double */
        ENUMERATED,
        OCTET_STRING_64,
        OCTET_STRING_6,
        OCTET_STRING_8,
        VISIBLE_STRING_32,
        VISIBLE_STRING_64,
        VISIBLE_STRING_65,
        VISIBLE_STRING_129,
        VISIBLE_STRING_255,
        UNICODE_STRING_255,
        TIMESTAMP,
        QUALITY,
        CHECK,
        CODEDENUM,
        GENERIC_BITSTRING,
        CONSTRUCTED,
        ENTRY_TIME,
        PHYCOMADDR,
        CURRENCY,
        OPTFLDS,
        TRGOPS,
        DBPOS,
        TCMD
    };

    static AttributeType::TYPE createFromString(const string &typeString);
    static string toString(TYPE type);
    static map<string, TYPE> mStrIntMap;
    static map<TYPE, string> mIntStrMap;
};

}
#endif // ATTRIBUTETYPE_H

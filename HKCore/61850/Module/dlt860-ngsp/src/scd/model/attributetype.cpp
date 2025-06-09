#include "attributetype.h"

namespace scd {

map<string, AttributeType::TYPE> AttributeType::mStrIntMap;
map<AttributeType::TYPE, string> AttributeType::mIntStrMap;

AttributeType::TYPE AttributeType::createFromString(const string &typeString)
{
    if(mStrIntMap.empty())
    {
        mStrIntMap.insert(make_pair("BOOLEAN", BOOLEAN));
        mStrIntMap.insert(make_pair("INT8", INT8));
        mStrIntMap.insert(make_pair("INT16", INT16));
        mStrIntMap.insert(make_pair("INT32", INT32));
        mStrIntMap.insert(make_pair("INT64", INT64));
        mStrIntMap.insert(make_pair("INT128", INT128));
        mStrIntMap.insert(make_pair("INT8U", INT8U));
        mStrIntMap.insert(make_pair("INT16U", INT16U));
        mStrIntMap.insert(make_pair("INT24U", INT24U));
        mStrIntMap.insert(make_pair("INT32U", INT32U));
        mStrIntMap.insert(make_pair("FLOAT32", FLOAT32));
        mStrIntMap.insert(make_pair("FLOAT64", FLOAT64));
        mStrIntMap.insert(make_pair("Enum", ENUMERATED));
        mStrIntMap.insert(make_pair("Dbpos", DBPOS));
        mStrIntMap.insert(make_pair("Check", CHECK));
        mStrIntMap.insert(make_pair("Tcmd", TCMD));

        mStrIntMap.insert(make_pair("Octet64", OCTET_STRING_64));
        mStrIntMap.insert(make_pair("Quality", QUALITY));
        mStrIntMap.insert(make_pair("Timestamp", TIMESTAMP));
        mStrIntMap.insert(make_pair("Currency", CURRENCY));

        mStrIntMap.insert(make_pair("VisString32", VISIBLE_STRING_32));
        mStrIntMap.insert(make_pair("VisString64", VISIBLE_STRING_64));
        mStrIntMap.insert(make_pair("VisString65", VISIBLE_STRING_65));
        mStrIntMap.insert(make_pair("VisString129", VISIBLE_STRING_129));
        mStrIntMap.insert(make_pair("ObjRef", VISIBLE_STRING_129));
        mStrIntMap.insert(make_pair("VisString255", VISIBLE_STRING_129));
        mStrIntMap.insert(make_pair("Unicode255", UNICODE_STRING_255));

        mStrIntMap.insert(make_pair("OptFlds", OPTFLDS));

        mStrIntMap.insert(make_pair("TrgOps", TRGOPS));
        mStrIntMap.insert(make_pair("EntryID", OCTET_STRING_8));
        mStrIntMap.insert(make_pair("EntryTime", ENTRY_TIME));
        mStrIntMap.insert(make_pair("PhyComAddr", PHYCOMADDR));
        mStrIntMap.insert(make_pair("Struct", CONSTRUCTED));
    }

    if(mStrIntMap.count(typeString))
    {
        return mStrIntMap[typeString];
    }
    throw ParseException("unsupported attribute type " + typeString);
}

string AttributeType::toString(AttributeType::TYPE type)
{
    if(mIntStrMap.empty()) {
        mIntStrMap.insert(make_pair(BOOLEAN, "BOOLEAN"));
        mIntStrMap.insert(make_pair(INT8, "INT8"));
        mIntStrMap.insert(make_pair(INT16, "INT16"));
        mIntStrMap.insert(make_pair(INT32, "INT32"));
        mIntStrMap.insert(make_pair(INT64, "INT64"));
        mIntStrMap.insert(make_pair(INT128, "INT128"));
        mIntStrMap.insert(make_pair(INT8U, "INT8U"));
        mIntStrMap.insert(make_pair(INT16U, "INT16U"));
        mIntStrMap.insert(make_pair(INT24U, "INT24U"));
        mIntStrMap.insert(make_pair(INT32U, "INT32U"));
        mIntStrMap.insert(make_pair(FLOAT32, "FLOAT32"));
        mIntStrMap.insert(make_pair(FLOAT64, "FLOAT64"));
        mIntStrMap.insert(make_pair(ENUMERATED, "ENUMERATED"));
        mIntStrMap.insert(make_pair(OCTET_STRING_64, "OCTET_STRING_64"));
        mIntStrMap.insert(make_pair(OCTET_STRING_8, "OCTET_STRING_8"));
        mIntStrMap.insert(make_pair(OCTET_STRING_6, "OCTET_STRING_6"));
        mIntStrMap.insert(make_pair(CURRENCY, "CURRENCY"));
        mIntStrMap.insert(make_pair(VISIBLE_STRING_32, "VISIBLE_STRING_32"));
        mIntStrMap.insert(make_pair(VISIBLE_STRING_64, "VISIBLE_STRING_64"));
        mIntStrMap.insert(make_pair(VISIBLE_STRING_65, "VISIBLE_STRING_65"));
        mIntStrMap.insert(make_pair(VISIBLE_STRING_129, "VISIBLE_STRING_129"));
        mIntStrMap.insert(make_pair(VISIBLE_STRING_255, "VISIBLE_STRING_255"));
        mIntStrMap.insert(make_pair(UNICODE_STRING_255, "UNICODE_STRING_255"));
        mIntStrMap.insert(make_pair(TIMESTAMP, "TIMESTAMP"));
        mIntStrMap.insert(make_pair(QUALITY, "QUALITY"));
        mIntStrMap.insert(make_pair(CHECK, "CHECK"));
        mIntStrMap.insert(make_pair(CODEDENUM, "CODEDENUM"));
        mIntStrMap.insert(make_pair(GENERIC_BITSTRING, "GENERIC_BITSTRING"));
        mIntStrMap.insert(make_pair(CONSTRUCTED, "CONSTRUCTED"));

        mIntStrMap.insert(make_pair(ENTRY_TIME, "ENTRY_TIME"));
        mIntStrMap.insert(make_pair(PHYCOMADDR, "PHYCOMADDR"));

        mIntStrMap.insert(make_pair(CURRENCY, "CURRENCY"));
        mIntStrMap.insert(make_pair(OPTFLDS, "OPTFLDS"));
        mIntStrMap.insert(make_pair(TRGOPS, "TRGOPS"));
        mIntStrMap.insert(make_pair(DBPOS, "DBPOS"));
        mIntStrMap.insert(make_pair(TCMD, "TCMD"));

    }

    if(mIntStrMap.count(type))
    {
        return mIntStrMap[type];
    }
    throw ParseException("unsupported attribute type " + to_string(type));

}


}

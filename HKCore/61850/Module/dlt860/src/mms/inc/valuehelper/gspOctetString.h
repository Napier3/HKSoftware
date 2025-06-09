#ifndef GSP_OCTET_STRING
#define GSP_OCTET_STRING

#include "gspMmsValue.h"
namespace gsp {

class OctetString
{
public:
    static void serialize(OCTET_STRING_t *str, CharVec &bin);
    static void unserialize(const CharVec &bin, OCTET_STRING *str);
};
}

#endif

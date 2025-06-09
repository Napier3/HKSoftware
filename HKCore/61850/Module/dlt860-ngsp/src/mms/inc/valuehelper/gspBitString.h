#ifndef GSP_BIT_STRING
#define GSP_BIT_STRING
#include "gspMmsValue.h"

namespace gsp {

class BitString
{
public:
    static void serialize(BIT_STRING_t *str, CharVec &bin);
    static void unserialize(const CharVec &bin, BIT_STRING_t *str);
};
}
#endif

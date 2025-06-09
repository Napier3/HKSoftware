#include "gspOctetString.h"

namespace gsp {

void OctetString::serialize(OCTET_STRING_t *str, gsp::CharVec &bin)
{
    bin.resize(1 + str->size);
    memcpy(bin.data() + 1, str->buf, str->size);
}

void OctetString::unserialize(const CharVec &bin, OCTET_STRING *str)
{
    str->size = bin.size() - 1;
    str->buf = (uint8_t *)calloc(1, str->size);
    memcpy(str->buf, bin.data() + 1, str->size);
}

}

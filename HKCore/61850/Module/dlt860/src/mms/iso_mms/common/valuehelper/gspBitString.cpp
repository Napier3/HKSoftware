#include "gspBitString.h"

namespace gsp {

void BitString::serialize(BIT_STRING_t *bitStr, gsp::CharVec &bin)
{
    bin.push_back(char(bitStr->bits_unused));
    bin.resize(2 + bitStr->size);
    memcpy(bin.data() + 2, bitStr->buf, bitStr->size);
}

void BitString::unserialize(const CharVec &bin, BIT_STRING_t *str)
{
    str->bits_unused = bin[1];
    str->size = bin.size() - 2;
    str->buf = (uint8_t *)calloc(1, str->size);
    memcpy(str->buf, bin.data() + 2, str->size);
}

}

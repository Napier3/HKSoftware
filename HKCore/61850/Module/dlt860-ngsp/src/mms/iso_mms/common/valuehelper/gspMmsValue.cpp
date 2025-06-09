#include "gspMmsValue.h"
#include "gspBitString.h"
#include "gspOctetString.h"

namespace gsp {

void Value::serialize(GspMmsValue *value, CharVec &bin)
{
    char buf[65535];
    size_t bufSize = 0;
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_Data, NULL, value, buf, 65535);
    if(dVal.encoded > 0) {
        bufSize += (dVal.encoded / 8);
        if(dVal.encoded % 8 > 0) {
            bufSize += 1;
        }
    }
    bin.resize(bufSize);
    memcpy(&bin[0], buf, bufSize);
}

GspMmsValue *Value::unserialize(const CharVec &bin)
{
    void *requestData = nullptr;
    auto ret = aper_decode_complete(nullptr,
                                    &asn_DEF_Data,
                                    &requestData,
                                    &bin[0],
                                    bin.size()
                                    );
    if(ret.code == RC_OK)
    {
        return (Data_t *)requestData;
    }
    return nullptr;
}

}

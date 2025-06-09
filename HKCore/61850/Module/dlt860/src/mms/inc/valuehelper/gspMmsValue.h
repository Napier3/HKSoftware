#ifndef GSP_MMS_VALUE_
#define GSP_MMS_VALUE_

#include "gsp_mms_value.h"
#include <vector>

using namespace std;


namespace gsp {
using CharVec = vector<char>;

template <typename T>
void serializeStdValue(T *value, CharVec &bin)
{
    bin.resize(sizeof(T) + 1);
    memcpy(bin.data() + 1, (char *)value, sizeof(T));
}

template <typename T>
void unserializeStdValue(const char *data, T *value)
{
    auto length = sizeof(value);
    memcpy(value, data, length);
}

class Value {
public:
    static void serialize(GspMmsValue *value, CharVec &bin);
    static GspMmsValue *unserialize(const CharVec &bin);
};

}

#endif

#ifndef ENUMTYPE_H
#define ENUMTYPE_H

#include "scltype.h"
#include <string>
#include <vector>
#include <cstring>
#include "pugixml/pugixml.hpp"
#include "enumvalue.h"

using namespace std;
using namespace pugi;

namespace scd {

class EnumType : public SclType
{
public:
    EnumType(xml_node node);
    EnumType(const char *name);
    vector<EnumValue> &enumValues();
    int getOrdByEnumString(const char *name);
    bool isValidOrdValue(int ordValue);
    virtual int getClassType() {
        return ENUM_TYPE;
    }
private:
    vector<EnumValue> mEnumValues;
};

}
#endif // ENUMTYPE_H

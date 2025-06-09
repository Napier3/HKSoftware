#ifndef ENUMVALUE_H
#define ENUMVALUE_H

#include <string>
#include "common.h"

using namespace std;
using namespace pugi;

namespace scd {

class EnumValue
{
public:
    EnumValue(xml_node node);

    int getOrd() const;

    const char *getSymbolicName() const;

private:
    const char *symbolicName;
    int ord;
};

}
#endif // ENUMVALUE_H

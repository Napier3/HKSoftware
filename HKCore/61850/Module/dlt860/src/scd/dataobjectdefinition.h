#ifndef DATAOBJECTDEFINITION_H
#define DATAOBJECTDEFINITION_H

#include "pugixml/pugixml.hpp"
#include <string>
#include "common.h"

using namespace std;
using namespace pugi;

namespace scd {

class DataObjectDefinition
{
public:
    DataObjectDefinition(xml_node node);

    const char *getName() const;

    const char *getType() const;

    int getCount() const;

private:
    const char *name;
    const char *type;
    int count = 0;
};

}
#endif // DATAOBJECTDEFINITION_H

#ifndef DATAATTRIBUTETYPE_H
#define DATAATTRIBUTETYPE_H

#include "pugixml.hpp"
#include "dataattributedefinition.h"
#include <vector>
#include "scltype.h"
#include "common.h"
#include "scltype.h"

using namespace std;
using namespace pugi;

namespace scd {

class DataAttributeType : public SclType
{
public:
    DataAttributeType(xml_node node);
    DataAttributeDefinition *getDataAttributeByName(const char *name);
    vector<shared_ptr<DataAttributeDefinition>> &getSubDataAttributes() ;
    virtual int getClassType() {
        return DATA_ATTRIBUTE_TYPE;
    }
protected:
private:
    vector<shared_ptr<DataAttributeDefinition>> subDataAttributes;
};

}
#endif // DATAATTRIBUTETYPE_H

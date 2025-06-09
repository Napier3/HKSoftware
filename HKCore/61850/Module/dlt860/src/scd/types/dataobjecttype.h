#ifndef DATAOBJECTTYPE_H
#define DATAOBJECTTYPE_H

#include "common.h"
#include <vector>
#include <string>
#include "dataattributedefinition.h"
#include "dataobjectdefinition.h"
#include "pugixml.hpp"
#include "scltype.h"

using namespace std;
using namespace pugi;

namespace scd {

class DataObjectType : public SclType
{
public:
    DataObjectType(xml_node node);

    DataAttributeDefinition *getDaByName(const char *name);
    DataObjectDefinition *getDoByName(const char *name);
    const char *getCdc() const;

    vector<shared_ptr<DataObjectDefinition> > &getSubDataObjects() ;

    vector<shared_ptr<DataAttributeDefinition>> &getDataAttributes() ;
    virtual int getClassType() {
        return DATA_OBJECT_TYPE;
    }
protected:
private:
    const char *cdc;
    vector<shared_ptr<DataObjectDefinition>> subDataObjects;
    vector<shared_ptr<DataAttributeDefinition>> dataAttributes;
};

}
#endif // DATAOBJECTTYPE_H

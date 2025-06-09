#ifndef LOGICNODETYPE_H
#define LOGICNODETYPE_H

#include "dataobjectdefinition.h"
#include <vector>
#include "scltype.h"
#include "common.h"

using namespace std;
using namespace pugi;

namespace scd {

class LogicNodeType : public SclType
{
public:
    LogicNodeType(xml_node node);

    vector<shared_ptr<DataObjectDefinition> > &getDataObjects() ;
    virtual int getClassType() {
        return LOGIC_NODE_TYPE;
    }
protected:
    void parseAttr(xml_node node);
    void parseDoNodes(xml_node node);
    DataObjectDefinition *getObjectDefinitionByName(const char *name);
protected:
private:
    const char *lnClass = nullptr;
    vector<shared_ptr<DataObjectDefinition>> dataObjects;
};

}
#endif // LOGICNODETYPE_H

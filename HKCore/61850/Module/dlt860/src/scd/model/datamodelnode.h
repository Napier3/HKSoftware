#ifndef DATAMODELNODE_H
#define DATAMODELNODE_H

#include <string>
#include "types/scltype.h"

using namespace std;
namespace scd {

class DataModelNode
{
public:
    virtual string getName() const = 0;
    virtual DataModelNode *getChildByName(const string &childName) const = 0;
    virtual SclType *getSclType() const = 0;
    virtual DataModelNode *getParent() const = 0;

    enum {
        DATA_MODEL_NODE,
        DATA_ATTRIBUTE,
        DATA_OBJECT,
        LOGICAL_NODE,
    };

    virtual int getClassType() {
        return DATA_MODEL_NODE;
    }
};

}
#endif // DATAMODELNODE_H

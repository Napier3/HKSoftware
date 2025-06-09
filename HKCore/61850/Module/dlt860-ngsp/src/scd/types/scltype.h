#ifndef SCLTYPE_H
#define SCLTYPE_H

#include "pugixml/pugixml.hpp"
#include "dataobjectdefinition.h"
#include "common.h"
#include <vector>

using namespace std;
using namespace pugi;

namespace scd {

class SclType
{
public:
    enum {
        SCL_TYPE,
        DATA_ATTRIBUTE_TYPE,
        DATA_OBJECT_TYPE,
        ENUM_TYPE,
        LOGIC_NODE_TYPE,
    };
    SclType(xml_node node);
    SclType(const char *pId, const char *pDesc);

    void setUsed(bool used);
    virtual int getClassType() {
        return SCL_TYPE;
    }
    const char *getId() const;

    const char *getDesc() const;

    bool getUsed() const;

private:
    const char *id = nullptr;
    const char *desc = nullptr;
    bool used = false;
};

}
#endif // SCLTYPE_H

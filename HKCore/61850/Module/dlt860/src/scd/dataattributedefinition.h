#ifndef DATAATTRIBUTEDEFINITION_H
#define DATAATTRIBUTEDEFINITION_H

#include "pugixml.hpp"
#include <string>
#include "common.h"
#include "model/functionconstraint.h"
#include "model/attributetype.h"
#include "model/triggeroptions.h"
#include "model/datamodelvalue.h"

using namespace std;
using namespace pugi;

namespace scd {

class DataAttributeDefinition
{
public:
    DataAttributeDefinition(xml_node node);

    const char *getName() const;

    FunctionConstraint::FC getFc() const;

    int getCount() const;

    const char *getBType() const;

    const char *getType() const;

    AttributeType::TYPE getAttributeType() const;

    shared_ptr<TriggerOptions> getTriggerOptions() const;

    shared_ptr<DataModelValue> getValue() const;

private:
    const char *name;
    const char *bType;
    const char *type;
    int count;
    FunctionConstraint::FC fc;
    AttributeType::TYPE attributeType;
    shared_ptr<TriggerOptions> triggerOptions;
    shared_ptr<DataModelValue> value = nullptr;
};

}
#endif // DATAATTRIBUTEDEFINITION_H

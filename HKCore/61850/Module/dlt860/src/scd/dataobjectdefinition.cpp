#include "dataobjectdefinition.h"

namespace scd {

DataObjectDefinition::DataObjectDefinition(xml_node node)
{
    name = node.attribute("name").as_string(nullptr);
    type = node.attribute("type").as_string(nullptr);

    if(!type || !name)
        throw ParseException("DO misses required attribute");

    count = node.attribute("count").as_int();
}

const char *DataObjectDefinition::getName() const
{
    return name;
}

const char *DataObjectDefinition::getType() const
{
    return type;
}

int DataObjectDefinition::getCount() const
{
    return count;
}

}

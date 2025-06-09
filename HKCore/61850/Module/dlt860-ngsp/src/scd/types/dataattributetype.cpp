#include "dataattributetype.h"
#include <cstring>

namespace scd {

DataAttributeType::DataAttributeType(xml_node node)
    : SclType(node)
{
    for(auto &&child : node.children())
    {
        if(strcmp(child.name(), "BDA") == 0)
        {
            auto dad = std::make_shared<DataAttributeDefinition>(child);
            if(getDataAttributeByName(dad->getName()))
            {
                throw ParseException(string("DA type definition contains multiple elements of name ") + dad->getName());
            }

            subDataAttributes.push_back(dad);
        }
    }
}

DataAttributeDefinition *DataAttributeType::getDataAttributeByName(const char *name)
{
    for(auto &dad : subDataAttributes)
    {
        if(strcmp(dad->getName(), name) == 0)
        {
            return dad.get();
        }
    }

    return nullptr;
}

vector<shared_ptr<DataAttributeDefinition> > &DataAttributeType::getSubDataAttributes()
{
    return subDataAttributes;
}

}

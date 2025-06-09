#include "dataobjecttype.h"
#include <cstring>

namespace scd {

DataObjectType::DataObjectType(xml_node node)
    : SclType(node)
{
    cdc = node.attribute("cdc").as_string(nullptr);

    if(!cdc)
        throw ParseException("cdc is missing");

    for(auto &&child : node.children())
    {
        if(strcmp(child.name(), "DA") == 0)
        {
            auto dad = make_shared<DataAttributeDefinition>(child);
            auto pda = getDaByName(dad->getName());
            if(pda && dad->getFc() == pda->getFc())
            {
                throw ParseException(string("DO type definition contains multiple elements of name ") + dad->getName());
            }

            if(getDoByName(dad->getName()))
            {
                throw ParseException(string("DO type definition contains multiple elements of name ") + dad->getName());
            }

            dataAttributes.push_back(dad);
        }
        else if(strcmp(child.name(), "SDO") == 0)
        {
            auto dod = make_shared<DataObjectDefinition>(child);
            if(getDoByName(dod->getName()) || getDaByName(dod->getName()))
            {
                throw ParseException(string("DO type definition contains multiple elements of name ") + dod->getName());
            }
            subDataObjects.push_back(dod);
        }
    }
}

DataAttributeDefinition *DataObjectType::getDaByName(const char *name)
{
    for(auto &dad : dataAttributes)
    {
        if(strcmp(dad->getName(), name) == 0)
            return dad.get();
    }
    return nullptr;
}

DataObjectDefinition *DataObjectType::getDoByName(const char *name)
{
    for(auto &dod : subDataObjects)
    {
        if(strcmp(dod->getName(), name) == 0)
            return dod.get();
    }
    return nullptr;
}

const char *DataObjectType::getCdc() const
{
    return cdc;
}

vector<shared_ptr<DataObjectDefinition>> &DataObjectType::getSubDataObjects()
{
    return subDataObjects;
}

vector<shared_ptr<DataAttributeDefinition> > &DataObjectType::getDataAttributes()
{
    return dataAttributes;
}

}

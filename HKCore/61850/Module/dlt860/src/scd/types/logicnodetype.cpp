#include "logicnodetype.h"

namespace scd {

LogicNodeType::LogicNodeType(xml_node node) : SclType(node)
{
    parseAttr(node);
    parseDoNodes(node);
}

void LogicNodeType::parseAttr(xml_node node)
{
    lnClass = node.attribute("lnClass").as_string(nullptr);
    // NPRINTF("ln class %s\n", lnClass);

    if(!lnClass)
    {
        throw ParseException("no lnClass attribute");
    }
}

void LogicNodeType::parseDoNodes(xml_node node)
{
    for(auto &&child : node.children())
    {
        auto object = make_shared<DataObjectDefinition>(child);
        if(getObjectDefinitionByName(object->getName()))
            throw ParseException(string("Logical node contains multiple data objects with name ") + object->getName());

        dataObjects.push_back(object);
    }
}

DataObjectDefinition *LogicNodeType::getObjectDefinitionByName(const char *name)
{
    for(auto &&dod : dataObjects)
    {
        if(strcmp(dod->getName(), name) == 0)
        {
            return dod.get();
        }
    }
    return nullptr;
}

vector<shared_ptr<DataObjectDefinition>> &LogicNodeType::getDataObjects()
{
    return dataObjects;
}


}

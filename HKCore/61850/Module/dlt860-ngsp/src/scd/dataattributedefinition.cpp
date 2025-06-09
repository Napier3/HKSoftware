#include "dataattributedefinition.h"

namespace scd {

DataAttributeDefinition::DataAttributeDefinition(xml_node node)
{
    name = node.attribute("name").as_string(nullptr);
    bType = node.attribute("bType").as_string(nullptr);
    type = node.attribute("type").as_string(nullptr);
    const char *fcString = node.attribute("fc").as_string(nullptr);

    if(!name)
        throw ParseException(node, "attribute name is missing");

    if(fcString)
        fc = FunctionConstraint::createFromString(fcString);

    if(!bType)
        throw ParseException("attribute bType is missing");
    else
    {
        if(strcmp(bType, "Tcmd") == 0)
            type = "Tcmd";
        else if(strcmp(bType, "Dbpos") == 0)
            type = "Dbpos";
        else if(strcmp(bType, "Check") == 0)
            type = "Check";

        attributeType = AttributeType::createFromString(bType);
    } 

    bool dchgTrigger = false;
    bool qchgTrigger = false;
    bool dupdTrigger = false;

    const char *dchg = node.attribute("dchg").as_string(nullptr);
    if(dchg)
        dchgTrigger = (strcasecmp(dchg, "true") == 0);

    const char *dupd = node.attribute("dupd").as_string(nullptr);
    if(dupd)
        dupdTrigger = (strcasecmp(dupd, "true") == 0);

    const char *qchg = node.attribute("qchg").as_string(nullptr);
    if(qchg)
        qchgTrigger = (strcasecmp(qchg, "true") == 0);

    triggerOptions = std::make_shared<TriggerOptions>(dchgTrigger, dupdTrigger, qchgTrigger, false, false);

    count = node.attribute("count").as_int();

    if(bType)
    {
        for(auto &&child : node.children("Val"))
        {
            auto valueV = child.text().as_string();
            if(attributeType == AttributeType::ENUMERATED) {
                this->value = std::make_shared<DataModelValue>(this->type, valueV);
            } else {
                this->value = std::make_shared<DataModelValue>(attributeType, (SclType *)nullptr, valueV);
            }
        }
    }
}

const char *DataAttributeDefinition::getName() const
{
    return name;
}

FunctionConstraint::FC DataAttributeDefinition::getFc() const
{
    return fc;
}

int DataAttributeDefinition::getCount() const
{
    return count;
}

const char *DataAttributeDefinition::getBType() const
{
    return bType;
}

const char *DataAttributeDefinition::getType() const
{
    return type;
}

AttributeType::TYPE DataAttributeDefinition::getAttributeType() const
{
    return attributeType;
}

shared_ptr<TriggerOptions> DataAttributeDefinition::getTriggerOptions() const
{
    return triggerOptions;
}

shared_ptr<DataModelValue> DataAttributeDefinition::getValue() const
{
    return value;
}

}

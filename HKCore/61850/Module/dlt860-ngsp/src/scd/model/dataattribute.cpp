#include "dataattribute.h"
#include "types/dataattributetype.h"

namespace scd {

DataAttribute::DataAttribute(DataAttributeDefinition *daDefinition, TypeDeclarations *typeDeclarations,
                             int fcV, DataModelNode *parentV)
{
    name = daDefinition->getName();
    fc = daDefinition->getFc();
    type = daDefinition->getAttributeType();
    count = daDefinition->getCount();
    parent = parentV;
    definition = daDefinition;

    if(fcV >= 0)
    {
        fc = (FunctionConstraint::FC)fcV;
    }

    if(parent && parent->getClassType() == DATA_ATTRIBUTE)
    {
        triggerOptions = ((DataAttribute*)parent)->getTriggerOptions();
    }
    else
    {
        triggerOptions = daDefinition->getTriggerOptions();
    }

    if(this->type == AttributeType::CONSTRUCTED)
    {
        isBasicAttribute = false;
        createConstructedAttribute(daDefinition, typeDeclarations);
    }
    else if(this->type == AttributeType::ENUMERATED)
    {
        createEnumeratedAttribute(daDefinition, typeDeclarations);
    }

}

DataAttribute::~DataAttribute()
{

}

string DataAttribute::getName() const
{
    return name;
}

FunctionConstraint::FC DataAttribute::getFc() const
{
    return fc;
}

AttributeType::TYPE DataAttribute::getType() const
{
    return type;
}

vector<shared_ptr<DataAttribute> > &DataAttribute::getSubDataAttributes()
{
    return subDataAttributes;
}

bool DataAttribute::getIsBasicAttribute() const
{
    return isBasicAttribute;
}

int DataAttribute::getCount() const
{
    return count;
}

SclType *DataAttribute::getSclType() const
{
    return sclType;
}

const char *DataAttribute::getShortAddress() const
{
    return shortAddress ? shortAddress : "0";
}

shared_ptr<TriggerOptions> DataAttribute::getTriggerOptions() const
{
    return triggerOptions;
}

DataAttributeDefinition *DataAttribute::getDefinition() const
{
    return definition;
}

void DataAttribute::createEnumeratedAttribute(DataAttributeDefinition *daDefinition, TypeDeclarations *typeDeclarations)
{
    sclType = typeDeclarations->lookupType(daDefinition->getType());
    if(!this->sclType)
        throw ParseException(string("Missing type definition for enumerated data attribute: ") + daDefinition->getType());

    if(sclType->getClassType() != SclType::ENUM_TYPE)
    {
        throw ParseException("Wrong type definition for enumerated data attribute");
    }
    sclType->setUsed(true);
}

void DataAttribute::createConstructedAttribute(DataAttributeDefinition *daDefinition, TypeDeclarations *typeDeclarations)
{
    sclType = typeDeclarations->lookupType(daDefinition->getType());

    if(!sclType) {
        throw ParseException(string("Missing type definition for constructed data attribute: ") + daDefinition->getBType());
    }

    if(sclType->getClassType() != SclType::DATA_ATTRIBUTE_TYPE) {
        throw ParseException("Wrong type definition for constructed data attribute");
    }

    sclType->setUsed(true);

    auto dataAttributeType = (DataAttributeType*)sclType;
    auto daDefinitions = dataAttributeType->getSubDataAttributes();

    for(auto &&daDef : daDefinitions) {
        subDataAttributes.push_back(make_shared<DataAttribute>(daDef.get(), typeDeclarations, fc, this));
    }
}

void DataAttribute::setShortAddress(const char *value)
{
    shortAddress = value;
}

void DataAttribute::setValue(const shared_ptr<DataModelValue> &valueV)
{
    value = valueV;
}

}

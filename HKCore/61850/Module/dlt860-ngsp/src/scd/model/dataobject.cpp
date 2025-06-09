#include "dataobject.h"
#include "types/dataattributetype.h"

namespace scd {

DataObject::DataObject(DataObjectDefinition *doDefinition, TypeDeclarations *typeDeclarations, DataModelNode *parentV)
{
    name = doDefinition->getName();
    count = doDefinition->getCount();
    parent = parentV;

    sclType = typeDeclarations->lookupType(doDefinition->getType());

    if(!sclType)
        throw ParseException("type declaration missing for data object.");

    if(sclType->getClassType() != SclType::DATA_OBJECT_TYPE)
        throw ParseException("type name error.");

    sclType->setUsed(true);
    cdcType = ((DataObjectType*)sclType)->getCdc();
    createDataAttributes(typeDeclarations, sclType);
    createSubDataObjects(typeDeclarations, (DataObjectType*)sclType);
}

DataObject::~DataObject()
{
    for(auto &da : dataAttributes)
    {
        delete da;
    }
    for(auto &dataObject : subDataObjects)
    {
        delete dataObject;
    }
}

void DataObject::createSubDataObjects(TypeDeclarations *typeDeclarations, DataObjectType *doType)
{
    for(auto &sdoDefinition : doType->getSubDataObjects())
    {
        subDataObjects.push_back(new DataObject(sdoDefinition.get(), typeDeclarations, this));
    }
}

void DataObject::createDataAttributes(TypeDeclarations *typeDeclarations, SclType *sclType)
{
    if(sclType->getClassType() == SclType::DATA_OBJECT_TYPE) {
        for(auto &daDefinition : ((DataObjectType*)sclType)->getDataAttributes()) {
            if(daDefinition->getFc() == FunctionConstraint::SG) {
                this->dataAttributes.push_back(new DataAttribute(daDefinition.get(), typeDeclarations, FunctionConstraint::SE, this));
            } else if(daDefinition->getFc() == FunctionConstraint::SE) {
                continue;
            }
            this->dataAttributes.push_back(new DataAttribute(daDefinition.get(), typeDeclarations, -1, this));
        }
    }

    if(sclType->getClassType() == SclType::DATA_ATTRIBUTE_TYPE) {
        for(auto &daDefinition : ((DataAttributeType*)sclType)->getSubDataAttributes()) {
            if(daDefinition->getFc() == FunctionConstraint::SG) {
                this->dataAttributes.push_back(new DataAttribute(daDefinition.get(), typeDeclarations, FunctionConstraint::SE, this));
            } else if(daDefinition->getFc() == FunctionConstraint::SE) {
                continue;
            }
            this->dataAttributes.push_back(new DataAttribute(daDefinition.get(), typeDeclarations, -1, this));
        }
    }
}

DataModelNode *DataObject::getParent() const
{
    return parent;
}

DataModelNode *DataObject::getChildByName(const string &childName) const
{
    for(auto &dataAttribute : dataAttributes) {
        if(strcmp(childName.c_str(), dataAttribute->getName().c_str()) == 0)
            return dataAttribute;
    }

    for(auto &dataObject : subDataObjects) {
        if(strcmp(childName.c_str(), dataObject->getName().c_str()) == 0)
            return dataObject;
    }
    return nullptr;
}

SclType *DataObject::getSclType() const
{
    return sclType;
}

vector<DataObject*> &DataObject::getSubDataObjects()
{
    return subDataObjects;
}

vector<DataAttribute*> &DataObject::getDataAttributes()
{
    return dataAttributes;
}

int DataObject::getCount() const
{
    return count;
}

string DataObject::getName() const
{
    return name;
}

}

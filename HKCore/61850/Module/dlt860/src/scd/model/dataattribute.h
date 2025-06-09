#ifndef DATAATTRIBUTE_H
#define DATAATTRIBUTE_H

#include "common.h"
#include "functionconstraint.h"
#include "attributetype.h"
#include "datamodelvalue.h"
#include "datamodelnode.h"
#include "types/scltype.h"
#include "triggeroptions.h"
#include "dataattributedefinition.h"
namespace scd {

class DataAttribute : public DataModelNode
{
public:
    DataAttribute(DataAttributeDefinition *daDefinition,
                  TypeDeclarations *typeDeclarations,
                  int fcV,
                  DataModelNode *parentV);
    virtual ~DataAttribute();
    virtual string getName() const;

    FunctionConstraint::FC getFc() const;

    AttributeType::TYPE getType() const;

    vector<shared_ptr<DataAttribute> > &getSubDataAttributes();

    bool getIsBasicAttribute() const;

    int getCount() const;

    virtual SclType * getSclType() const;

    const char *getShortAddress() const;

    shared_ptr<TriggerOptions> getTriggerOptions() const;

    DataAttributeDefinition *getDefinition() const;

    virtual DataModelNode *getChildByName(const string &childName) const
    {
        for(auto &&dataAttribute: subDataAttributes)
        {
            if(strcmp(dataAttribute->getName().c_str(), childName.c_str()) == 0)
            {
                return dataAttribute.get();
            }
        }
        return nullptr;
    }

    virtual DataModelNode *getParent() const
    {
        return parent;
    }

    virtual int getClassType()
    {
        return DATA_ATTRIBUTE;
    }
    void setValue(const shared_ptr<DataModelValue> &value);
    DataModelValue *getValue() const { return value.get(); }

    void setShortAddress(const char *value);

private:
    void createEnumeratedAttribute(DataAttributeDefinition *daDefinition, TypeDeclarations *typeDeclarations);
    void createConstructedAttribute(DataAttributeDefinition *daDefinition, TypeDeclarations *typeDeclarations);
private:
    const char *name;
    FunctionConstraint::FC fc;
    AttributeType::TYPE type;
    bool isBasicAttribute = true;
    int count = 0;
    shared_ptr<DataModelValue> value = nullptr;
    const char *shortAddress = nullptr;
    DataModelNode *parent = nullptr;
    vector<shared_ptr<DataAttribute>> subDataAttributes;
    SclType *sclType = nullptr;
    shared_ptr<TriggerOptions> triggerOptions = nullptr;
    DataAttributeDefinition *definition = nullptr;

};

}
#endif // DATAATTRIBUTE_H

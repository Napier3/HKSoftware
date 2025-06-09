#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include "common.h"
#include "dataattribute.h"
#include "datamodelnode.h"
#include "types/dataobjecttype.h"
namespace scd {

class DataObject : public DataModelNode
{
public:
    DataObject(DataObjectDefinition *doDefinition, TypeDeclarations *typeDeclarations, DataModelNode *parent);
    virtual ~DataObject();
    virtual string getName() const;

    int getCount() const;

    vector<DataAttribute*> &getDataAttributes();

    vector<DataObject*> &getSubDataObjects();

    virtual SclType *getSclType() const;

    virtual DataModelNode *getParent() const;

    virtual int getClassType() {
        return DATA_OBJECT;
    }

    const char* getCdcType() const { return cdcType; }
    virtual DataModelNode *getChildByName(const string &childName) const;
private:
    void createSubDataObjects(TypeDeclarations *typeDeclarations, DataObjectType *doType);
    void createDataAttributes(TypeDeclarations *typeDeclarations, SclType *sclType);
private:
    const char *name = nullptr;
    int count = 0;
    vector<DataAttribute*> dataAttributes;
    vector<DataObject*> subDataObjects;
    SclType *sclType = nullptr;
    DataModelNode *parent = nullptr;
    const char* cdcType = nullptr;

};

}
#endif // DATAOBJECT_H

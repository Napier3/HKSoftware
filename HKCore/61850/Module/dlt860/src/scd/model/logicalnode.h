#ifndef LOGICALNODE_H
#define LOGICALNODE_H

#include "common.h"
#include "types/scltype.h"
#include "dataobject.h"
#include "dataset.h"
#include "reportcontrolblock.h"
#include "logcontrol.h"
#include "log.h"
#include "settingcontrol.h"
#include "logicaldevice.h"

namespace scd {

class LogicalNode : public DataModelNode
{
public:
    LogicalNode(xml_node node, TypeDeclarations *typeDeclarations, LogicalDevice *parent);
    const char *getLnClass() const;

    const char *getLnType() const;

    const char *getInst() const;

    const char *getDesc() const;

    const char *getPrefix() const;

    virtual SclType *getSclType() const;

    virtual string getName() const;

    virtual DataModelNode *getChildByName(const string &childName) const;
    LogicalDevice *getParentLogicalDevice() const;

    virtual DataModelNode* getParent() const { return nullptr; }

    virtual int getClassType() { return LOGICAL_NODE; }
    vector<shared_ptr<DataObject> > &getDataObjects();

    vector<shared_ptr<DataSet>> &getDataSets() { return dataSets; }
    vector<shared_ptr<ReportControlBlock>> &getReportControlBlocks() { return reportControlBlocks; }
    vector<shared_ptr<LogControl>> &getLogControlBlocks() { return logControlBlocks; }
    vector<shared_ptr<Log>> &getLogs() { return logs; }
    vector<shared_ptr<SettingControl>> &getSettingGroupControlBlocks() { return settingGroupControlBlocks; }
private:
    void parseDataAttributeNodes(xml_node doiNode, DataModelNode *dataObject);
    void parseSubDataInstances(xml_node doiNode, DataModelNode *dataObject);
    const char *lnClass = nullptr;
    const char *lnType = nullptr;
    const char *inst = nullptr;
    const char *desc = nullptr;
    const char *prefix = nullptr;
    SclType *sclType;

    vector<shared_ptr<DataObject>> dataObjects;
    vector<shared_ptr<DataSet>> dataSets;
    vector<shared_ptr<ReportControlBlock>> reportControlBlocks;
    vector<shared_ptr<LogControl>> logControlBlocks;
    vector<shared_ptr<Log>> logs;
    vector<shared_ptr<SettingControl>> settingGroupControlBlocks;

    LogicalDevice *parentLogicalDevice;
};

}
#endif // LOGICALNODE_H

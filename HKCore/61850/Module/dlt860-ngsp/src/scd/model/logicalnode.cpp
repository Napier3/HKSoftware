#include "logicalnode.h"
#include "types/logicnodetype.h"
#include "nlogging.h"
namespace scd {

LogicalNode::LogicalNode(xml_node node, TypeDeclarations *typeDeclarations, LogicalDevice *parent)
{
    lnClass = node.attribute("lnClass").as_string(nullptr);
    lnType = node.attribute("lnType").as_string(nullptr);
    inst = node.attribute("inst").as_string(nullptr);
    desc = node.attribute("desc").as_string(nullptr);
    prefix = node.attribute("prefix").as_string(nullptr);
    parentLogicalDevice = parent;


    if(!lnClass) {
        throw ParseException("required attribute \"lnClass\" is missing in logical node.");
    }

    if(!lnType) {
        throw ParseException("required attribute \"lnType\" is missing in logical node.");
    }

    if(!inst) {
        throw ParseException("required attribute \"inst\" is missing in logical node.");
    }

    sclType = typeDeclarations->lookupType(lnType);

    if(!sclType) {
        throw ParseException(string("missing type declaration ") + lnType);
    }

    if(sclType->getClassType() == SclType::LOGIC_NODE_TYPE) {
        auto type = (LogicNodeType *)sclType;
        type->setUsed(true);
        auto &doDefinitions = type->getDataObjects();
        for(auto &doDefinition : doDefinitions) {
            dataObjects.push_back(make_shared<DataObject>(doDefinition.get(), typeDeclarations, this));
        }
    } else {
        throw ParseException(string("wrong type ") + lnType + " for logical node");
    }

    for(auto &&child : node.children("DataSet")) {
        dataSets.push_back(make_shared<DataSet>(child));
    }

    for(auto &&child : node.children("ReportControl")) {
        reportControlBlocks.push_back(make_shared<ReportControlBlock>(child));
    }

    for(auto &&child : node.children("LogControl")) {
        logControlBlocks.push_back(make_shared<LogControl>(child));
    }
    //很多厂家没有Log节点，所以不再查找 Log 节点创建 logs, 改为从logControlBlocks中
    //获取logName来创建logs,如果LogControl不存在logName属性，则为该LogControl创建一个
    //默认的logName，名称为GeneralLog
    for(auto &&lc : logControlBlocks){
        xml_node log_node = node.append_child("Log");
        log_node.append_attribute("name").set_value("GeneralLog");
        log_node.attribute("name").set_value(lc->getLogName());
        logs.push_back(make_shared<Log>(log_node));
    }


//    for(auto &&child : node.children("Log")) {
//        logs.push_back(make_shared<Log>(child));
//    }

    auto sgNodes = node.children("SettingControl");
    if(strcmp("LLN0", lnClass) != 0 && sgNodes.begin() != sgNodes.end()) {
        throw ParseException("LN other than LN0 is not allowed to contain SettingControl");
    }

    int sgCount = 0;
    for(auto &sg : sgNodes) {
        sgCount += 1;
    }

    if(sgCount > 1) {
        throw ParseException("LN contains more then one SettingControl");
    }

    for(auto &sg : sgNodes) {
        settingGroupControlBlocks.push_back(make_shared<SettingControl>(sg));
    }

    for(auto &child : node.children("DOI")) {
        const char *doiName = child.attribute("name").as_string("");
        auto dataObject = (DataObject *)getChildByName(doiName);

        if(!dataObject) {
            //throw ParseException(child, string("Missing data object with name \"") + doiName + "\"");
            NLOG_WARN("没有找到DOI[{}]对应的DO，跳过", doiName);
            continue;
        }

        parseDataAttributeNodes(child, dataObject);

        parseSubDataInstances(child, dataObject);
    }
}

void LogicalNode::parseDataAttributeNodes(xml_node doiNode, DataModelNode *dataObject)
{
    for(auto &child : doiNode.children("DAI")) {
        const char *daiName = child.attribute("name").as_string(nullptr);

        auto dataAttribute = (DataAttribute *)dataObject->getChildByName(daiName);

        if(!dataAttribute) {
            NLOG_WARN("没有找到DAI '{}' 对应的DA", daiName);
            continue;
        }

        auto valNode = child.child("Val");
        if(valNode) {
            const char *value = valNode.text().as_string();
            dataAttribute->setValue(make_shared<DataModelValue>(dataAttribute->getType(), dataAttribute->getSclType(), value));
        }

        auto shortAddress = child.attribute("sAddr").as_string(nullptr);
        if(shortAddress) {
            if(strcmp(shortAddress, "") != 0) {
                dataAttribute->setShortAddress(shortAddress);
            }
        }
    }
}

void LogicalNode::parseSubDataInstances(xml_node doiNode, DataModelNode *dataObject)
{
    for(auto &child : doiNode.children("SDI")) {
        auto sdiName = child.attribute("name").as_string(nullptr);
        auto subDataAttribute = dataObject->getChildByName(sdiName);

        if(!subDataAttribute) {
            throw ParseException(string("subelement with name") + sdiName + " not found!");
        } else {
            parseDataAttributeNodes(child, subDataAttribute);
            parseSubDataInstances(child, subDataAttribute);
        }
    }
}

vector<shared_ptr<DataObject> > &LogicalNode::getDataObjects()
{
    return dataObjects;
}

LogicalDevice *LogicalNode::getParentLogicalDevice() const
{
    return parentLogicalDevice;
}

SclType *LogicalNode::getSclType() const
{
    return sclType;
}

string LogicalNode::getName() const
{
    string name;
    if(prefix) {
        name += prefix;
    }

    name += lnClass;
    name += inst;
    return name;
}

DataModelNode *LogicalNode::getChildByName(const string &childName) const
{
    for(auto &dataObject : dataObjects) {
        if(dataObject->getName().compare(childName) == 0) {
            return dataObject.get();
        }
    }
    return nullptr;
}

const char *LogicalNode::getPrefix() const
{
    return prefix;
}

const char *LogicalNode::getDesc() const
{
    return desc;
}

const char *LogicalNode::getInst() const
{
    return inst;
}

const char *LogicalNode::getLnType() const
{
    return lnType;
}

const char *LogicalNode::getLnClass() const
{
    return lnClass;
}

}

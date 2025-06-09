#include "optionfields.h"
namespace scd {

OptionFields::OptionFields(xml_node node)
{
    seqNum = node.attribute("seqNum").as_bool();
    timeStamp = node.attribute("timeStamp").as_bool();
    dataSet = node.attribute("dataSet").as_bool();
    reasonCode = node.attribute("reasonCode").as_bool();
    dataRef = node.attribute("dataRef").as_bool();
    entryID = node.attribute("entryID").as_bool();
    configRef = node.attribute("configRef").as_bool();
    bufOvfl = node.attribute("bufOvfl").as_bool();
}

bool OptionFields::getSeqNum() const
{
    return seqNum;
}

bool OptionFields::getTimeStamp() const
{
    return timeStamp;
}

bool OptionFields::getDataSet() const
{
    return dataSet;
}

bool OptionFields::getReasonCode() const
{
    return reasonCode;
}

bool OptionFields::getDataRef() const
{
    return dataRef;
}

bool OptionFields::getEntryID() const
{
    return entryID;
}

bool OptionFields::getConfigRef() const
{
    return configRef;
}

bool OptionFields::getBufOvfl() const
{
    return bufOvfl;
}

}

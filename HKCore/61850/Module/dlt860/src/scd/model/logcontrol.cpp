#include "logcontrol.h"

namespace scd {

LogControl::LogControl(xml_node node)
{
    name = node.attribute("name").as_string(nullptr);
    if(!name) {
        throw ParseException("LogControl is missing required attribute \"name\"");
    }

    desc = node.attribute("desc").as_string(nullptr);
    dataSet = node.attribute("datSet").as_string(nullptr);
    if(dataSet) {
        if(strcmp(dataSet, "") == 0) {
            dataSet = nullptr;
        }
    }

    ldInst = node.attribute("ldInst").as_string(nullptr);
    prefix = node.attribute("prefix").as_string(nullptr);

    lnClass = node.attribute("lnClass").as_string(lnClass);
    lnInst = node.attribute("lnInst").as_string(lnInst);

    logName = node.attribute("logName").as_string(logName);

//    if(strcmp(logName, "") == 0) {
//        logName = nullptr;
//    }

    intgPd = node.attribute("intgPd").as_int();
    logEna = node.attribute("logEna").as_bool(logEna);
    reasonCode = node.attribute("reasonCode").as_bool(reasonCode);
    auto trgOpsNode = node.child("TrgOps");

    if(trgOpsNode) {
        triggerOptions = make_shared<TriggerOptions>(trgOpsNode);
    } else {
        triggerOptions = make_shared<TriggerOptions>();
    }
}

const char *LogControl::getName() const
{
    return name;
}

const char *LogControl::getDesc() const
{
    return desc;
}

const char *LogControl::getDataSet() const
{
    return dataSet;
}

const char *LogControl::getLdInst() const
{
    return ldInst;
}

const char *LogControl::getPrefix() const
{
    return prefix;
}

const char *LogControl::getLnClass() const
{
    return lnClass;
}

const char *LogControl::getLnInst() const
{
    return lnInst;
}

const char *LogControl::getLogName() const
{
    return logName;
}

bool LogControl::getLogEna() const
{
    return logEna;
}

bool LogControl::getReasonCode() const
{
    return reasonCode;
}

int LogControl::getIntgPd() const
{
    return intgPd;
}

TriggerOptions *LogControl::getTriggerOptions()
{
    return triggerOptions.get();
}

}

#include "functionalconstraintdata.h"
#include "nlogging.h"

namespace scd {

FunctionalConstraintData::FunctionalConstraintData(xml_node node)
{
    ldInstance = node.attribute("ldInst").as_string(nullptr);
    prefix = node.attribute("prefix").as_string(nullptr);
    lnClass = node.attribute("lnClass").as_string(nullptr);
    lnInstance = node.attribute("lnInst").as_string(nullptr);
    doName = node.attribute("doName").as_string(nullptr);
    daName = node.attribute("daName").as_string(nullptr);
    auto fcV = node.attribute("fc").as_string(nullptr);
    if(fcV)
        fc = FunctionConstraint::createFromString(fcV);
    auto index = node.attribute("ix").as_string(nullptr);
    if(index){
        try {
            ix = stoi(index);
        } catch (const std::exception &ex) {
            ix = 0;
            NLOG_WARN("Warning: 模型文件不规范,FC值错误,值为{}\n", index);
        }
    }
}

const char *FunctionalConstraintData::getLdInstance() const
{
    return ldInstance;
}

const char *FunctionalConstraintData::getPrefix() const
{
    return prefix;
}

const char *FunctionalConstraintData::getLnClass() const
{
    return lnClass;
}

const char *FunctionalConstraintData::getLnInstance() const
{
    return lnInstance;
}

const char *FunctionalConstraintData::getDoName() const
{
    return doName;
}

const char *FunctionalConstraintData::getDaName() const
{
    return daName;
}

FunctionConstraint::FC FunctionalConstraintData::getFc() const
{
    return fc;
}

string FunctionalConstraintData::toString()
{
    string result;
    if(ldInstance) {
        result = result + ldInstance + "/";
    }

    if(lnClass) {
        if(prefix) {
            result += prefix;
        }

        result += lnClass;

        if(lnInstance) {
            result += ".";
        }
    }
    if(lnInstance) {
        result = result + lnInstance + ".";
    }

    if(doName) {
        result += doName;
    }

    if(daName) {
        result += daName;
    }

    return result;

}

}

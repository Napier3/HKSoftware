#include "reportcontrolblock.h"
namespace scd {

ReportControlBlock::ReportControlBlock(xml_node node)
{
    name = node.attribute("name").as_string(nullptr);
    desc = node.attribute("desc").as_string(nullptr);
    dataSet = node.attribute("datSet").as_string(nullptr);
    integrityPeriod = node.attribute("intgPd").as_llong();
    rptID = node.attribute("rptID").as_string(nullptr);
    confRef = node.attribute("confRev").as_llong();
    buffered = node.attribute("buffered").as_bool();
    bufferTime = node.attribute("bufTime").as_llong();
    triggerOptions = make_shared<TriggerOptions>(node.child("TrgOps"));
    optionFields = make_shared<OptionFields>(node.child("OptFields"));
    indexed = node.attribute("indexed").as_bool(true);
    rptEnabled = make_shared<RptEnabled>(node.child("RptEnabled"));
}

const char * ReportControlBlock::getName() const
{
    return name;
}

const char * ReportControlBlock::getDesc() const
{
    return desc;
}

const char * ReportControlBlock::getDataSet() const
{
    return dataSet;
}

int64_t ReportControlBlock::getIntegrityPeriod() const
{
    return integrityPeriod;
}

const char *ReportControlBlock::getRptID() const
{
    return rptID;
}

int64_t ReportControlBlock::getConfRef() const
{
    return confRef;
}

bool ReportControlBlock::getBuffered() const
{
    return buffered;
}

int64_t ReportControlBlock::getBufferTime() const
{
    return bufferTime;
}

TriggerOptions *ReportControlBlock::getTriggerOptions() const
{
    return triggerOptions.get();
}

OptionFields *ReportControlBlock::getOptionFields() const
{
    return optionFields.get();
}

bool ReportControlBlock::getIndexed() const
{
    return indexed;
}

RptEnabled *ReportControlBlock::getRptEnabled() const
{
    return rptEnabled.get();
}

}

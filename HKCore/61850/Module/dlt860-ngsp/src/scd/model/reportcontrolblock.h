#ifndef REPORTCONTROLBLOCK_H
#define REPORTCONTROLBLOCK_H

#include <string>
#include <memory>
#include "common.h"
#include "pugixml.hpp"
#include "optionfields.h"
#include "triggeroptions.h"
#include "rptenabled.h"

using namespace std;
using namespace pugi;
namespace scd {

class ReportControlBlock
{
public:
    ReportControlBlock(xml_node node);
    const char * getName() const;

    const char * getDesc() const;

    const char * getDataSet() const;

    int64_t getIntegrityPeriod() const;

    const char * getRptID() const;

    int64_t getConfRef() const;

    bool getBuffered() const;

    int64_t getBufferTime() const;

    TriggerOptions *getTriggerOptions() const;

    OptionFields *getOptionFields() const;

    bool getIndexed() const;

    RptEnabled *getRptEnabled() const;

private:
    const char *name;
    const char * desc;
    const char * dataSet;
    int64_t integrityPeriod = -1;
    const char * rptID;
    int64_t confRef;
    bool buffered = false;
    int64_t bufferTime = 0;
    shared_ptr<TriggerOptions> triggerOptions;
    shared_ptr<OptionFields> optionFields;
    bool indexed = true;
    shared_ptr<RptEnabled> rptEnabled;
};

}
#endif // REPORTCONTROLBLOCK_H

#ifndef LOGCONTROL_H
#define LOGCONTROL_H

#include "common.h"
#include "triggeroptions.h"
namespace scd {

class LogControl
{
public:
    LogControl(xml_node node);
    const char *getName() const;

    const char *getDesc() const;

    const char *getDataSet() const;

    const char *getLdInst() const;

    const char *getPrefix() const;

    const char *getLnClass() const;

    const char *getLnInst() const;

    const char *getLogName() const;

    bool getLogEna() const;

    bool getReasonCode() const;

    int getIntgPd() const;

    TriggerOptions *getTriggerOptions();

private:
    const char *name = nullptr;
    const char *desc = nullptr;
    const char *dataSet = nullptr;
    const char *ldInst = nullptr;
    const char *prefix = nullptr;
    const char *lnClass = "LLN0";
    const char *lnInst = "";
    const char *logName = "GeneralLog";
    bool logEna = true;
    bool reasonCode = true;
    int intgPd = 0;
    shared_ptr<TriggerOptions> triggerOptions;

};

}
#endif // LOGCONTROL_H

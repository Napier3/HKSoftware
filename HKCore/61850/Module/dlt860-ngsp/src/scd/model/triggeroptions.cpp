#include "triggeroptions.h"
namespace scd {

TriggerOptions::TriggerOptions(xml_node node)
{
    dchg = node.attribute("dchg").as_bool();
    qchg = node.attribute("qchg").as_bool();
    dupd = node.attribute("dupd").as_bool();
    period = node.attribute("period").as_bool();
    gi = node.attribute("gi").as_bool();
}

TriggerOptions::TriggerOptions(bool dchgV, bool qchgV, bool dupdV, bool periodV, bool giV)
    : dchg(dchgV)
    , qchg(qchgV)
    , dupd(dupdV)
    , period(periodV)
    , gi(giV)
{

}

bool TriggerOptions::getDchg() const
{
    return dchg;
}

bool TriggerOptions::getQchg() const
{
    return qchg;
}

bool TriggerOptions::getDupd() const
{
    return dupd;
}

bool TriggerOptions::getPeriod() const
{
    return period;
}

bool TriggerOptions::getGi() const
{
    return gi;
}

}

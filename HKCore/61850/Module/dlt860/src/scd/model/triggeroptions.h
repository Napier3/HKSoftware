#ifndef TRIGGEROPTIONS_H
#define TRIGGEROPTIONS_H

#include "pugixml.hpp"

using namespace pugi;

namespace scd {

class TriggerOptions
{
public:
    TriggerOptions() {}
    TriggerOptions(xml_node node);
    TriggerOptions(bool dchgV, bool qchgV, bool dupdV, bool periodV, bool giV);
    bool getDchg() const;

    bool getQchg() const;

    bool getDupd() const;

    bool getPeriod() const;

    bool getGi() const;

    int getIntValue() {
        int intValue = 0;

        if (dchg) intValue += 1;
        if (qchg) intValue += 2;
        if (dupd) intValue += 4;
        if (period) intValue += 8;
        if (gi) intValue += 16;

        return intValue;
    }
private:
    bool dchg = false; /* 1 */
    bool qchg = false; /* 2 */
    bool dupd = false; /* 4 */
    bool period = false; /* 8 */
    bool gi = true; /* 16 */
};

}
#endif // TRIGGEROPTIONS_H

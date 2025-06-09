#ifndef OPTIONFIELDS_H
#define OPTIONFIELDS_H
#include "common.h"
#include "pugixml.hpp"
#include <string>

using namespace std;
using namespace pugi;

namespace scd {

class OptionFields
{
public:
    OptionFields(xml_node node);
    bool getSeqNum() const;

    bool getTimeStamp() const;

    bool getDataSet() const;

    bool getReasonCode() const;

    bool getDataRef() const;

    bool getEntryID() const;

    bool getConfigRef() const;

    bool getBufOvfl() const;
    int getIntValue() {
        int intValue = 0;

        if (seqNum) intValue += 1;
        if (timeStamp) intValue += 2;
        if (reasonCode) intValue += 4;
        if (dataSet) intValue += 8;
        if (dataRef) intValue += 16;
        if (bufOvfl) intValue += 32;
        if (entryID) intValue += 64;
        if (configRef) intValue += 128;

        return intValue;
    }
private:
    bool seqNum = false;
    bool timeStamp = false;
    bool dataSet = false;
    bool reasonCode = false;
    bool dataRef = false;
    bool entryID = false;
    bool configRef = false;
    bool bufOvfl = true;
};

}
#endif // OPTIONFIELDS_H

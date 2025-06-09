#ifndef SMVOPTS_H
#define SMVOPTS_H

#include "pugixml.hpp"

using namespace pugi;

namespace scd {

class SmvOpts
{
public:
    SmvOpts(xml_node node);
    int intValue() {
        int value = 0;

        if (mRefreshTime) value += 1;
        if (mSampleSync) value += 2;
        if (mSampleRate) value += 4;
        if (mDataSet) value += 8;
        if (mSecurity) value += 16;
        return value;
    }
private:
    bool mRefreshTime = false;
    bool mSampleSync = false;
    bool mSampleRate = false;
    bool mDataSet = false;
    bool mSecurity = false;

};

}
#endif // SMVOPTS_H

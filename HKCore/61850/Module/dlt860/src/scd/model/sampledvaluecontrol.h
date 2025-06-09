#ifndef SAMPLEDVALUECONTROL_H
#define SAMPLEDVALUECONTROL_H

#include "pugixml.hpp"
#include <string>
#include "smvopts.h"

using namespace std;
using namespace pugi;
namespace scd {

class SampledValueControl
{
public:
    SampledValueControl(xml_node node);
    const char*  name() {
        return mNode.attribute("name").as_string(nullptr);
    }

    const char*  desc() {
        return mNode.attribute("desc").as_string(nullptr);
    }

    const char* datSet() {
        return mNode.attribute("datSet").as_string(nullptr);
    }

    int confRev() {
        return mNode.attribute("confRev").as_int();
    }

    bool multicase() {
        return mNode.attribute("multicase").as_bool();
    }

    int smpRate() {
        return mNode.attribute("smpRate").as_int();
    }

    int nofASDU() {
        return mNode.attribute("nofASDU").as_int();
    }

    SmvOpts smvOpts() { return mSmvOpts; }
private:
    xml_node mNode;
    SmvOpts mSmvOpts;
};

}
#endif // SAMPLEDVALUECONTROL_H

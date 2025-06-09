#ifndef CLIENTLN_H
#define CLIENTLN_H

#include "common.h"
#include "pugixml.hpp"
#include <string>

using namespace std;
using namespace pugi;
namespace scd {

class ClientLN
{
public:
    ClientLN(xml_node node);
    const char *iedName() {
        return mNode.attribute("iedName").as_string(nullptr);
    }

    const char * apRef() {
        return mNode.attribute("apRef").as_string(nullptr);
    }

    const char * ldInst() {
        return mNode.attribute("ldInst").as_string(nullptr);
    }

    const char * prefix() {
        return mNode.attribute("prefix").as_string(nullptr);
    }

    const char * lnClass() {
        return mNode.attribute("lnClass").as_string(nullptr);
    }

    const char * lnInst() {
        return mNode.attribute("lnInst").as_string(nullptr);
    }

    const char * desc() {
        return mNode.attribute("desc").as_string(nullptr);
    }
private:
    xml_node mNode;
};

}
#endif // CLIENTLN_H

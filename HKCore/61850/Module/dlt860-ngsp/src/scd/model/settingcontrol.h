#ifndef SETTINGCONTROL_H
#define SETTINGCONTROL_H

#include "pugixml.hpp"
#include <string>

using namespace std;
using namespace pugi;

namespace scd {

class SettingControl
{
public:
    SettingControl(xml_node node);
    const char* desc() {
        return mNode.attribute("desc").as_string(nullptr);
    }

    int numOfSGs() {
        return mNode.attribute("numOfSGs").as_int();
    }

    int actSG() {
        return mNode.attribute("actSG").as_int();
    }
private:
    xml_node mNode;
};

}
#endif // SETTINGCONTROL_H

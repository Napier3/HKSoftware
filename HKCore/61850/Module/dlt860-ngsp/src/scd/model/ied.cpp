#include "ied.h"
#include "nlogging.h"

namespace scd {

IED::IED(xml_node node, TypeDeclarations *typeDeclarationsV)
{
    this->name = node.attribute("name").as_string(nullptr);
    NLOG_DEBUG("开始解析IED[{}]", this->name);
    for(auto &&child : node.children("AccessPoint")) {
        accessPoints.push_back(make_shared<AccessPoint>(child, typeDeclarationsV));
    }

    typeDeclarations = typeDeclarationsV;
}

TypeDeclarations *IED::getTypeDeclarations() const
{
    return typeDeclarations;
}

vector<shared_ptr<AccessPoint> > &IED::getAccessPoints()
{
    return accessPoints;
}

const char *IED::getName() const
{
    return name;
}

}

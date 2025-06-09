#include "accesspoint.h"
namespace scd {

AccessPoint::AccessPoint(xml_node node, TypeDeclarations *typeDeclaration)
{
    name = node.attribute("name").as_string(nullptr);
    if(!name)
    {
        throw ParseException("AccessPoint as no name defined!");
    }

    auto serverNode = node.child("Server");

    if(!serverNode)
        mServer = nullptr;
    else
        mServer = make_shared<Server>(serverNode, typeDeclaration);
}

const char *AccessPoint::getName() const
{
    return name;
}

}

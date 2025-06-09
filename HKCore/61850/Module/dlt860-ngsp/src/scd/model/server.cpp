#include "server.h"
namespace scd {

Server::Server(xml_node node, TypeDeclarations *typeDeclaration)
{
    auto auth = node.child("Authentication");

    if(auth) {
        authentication = make_shared<Authentication>(auth);
    }

    auto lds = node.children("LDevice");

    if(lds.begin() == lds.end()) {
        throw ParseException(node, "No logical devices defined for AccessPoint");
    }

    for(auto &&ld : lds) {
        logicalDevices.push_back(make_shared<LogicalDevice>(ld, typeDeclaration));
    }
}

shared_ptr<Authentication> Server::getAuthentication() const
{
    return authentication;
}

vector<shared_ptr<LogicalDevice> > &Server::getLogicalDevices()
{
    return logicalDevices;
}

}

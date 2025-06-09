#ifndef SERVER_H
#define SERVER_H

#include "pugixml/pugixml.hpp"
#include "types/typedeclarations.h"
#include <string>
#include <vector>
#include <cstring>
#include "common.h"
#include "authentication.h"
#include "logicaldevice.h"

using namespace pugi;
using namespace std;

namespace scd {

class Server
{
public:
    Server(xml_node node, TypeDeclarations *typeDeclaration);
    shared_ptr<Authentication> getAuthentication() const;

    vector<shared_ptr<LogicalDevice> > &getLogicalDevices();

private:
    shared_ptr<Authentication> authentication;
    vector<shared_ptr<LogicalDevice>> logicalDevices;
};

}
#endif // SERVER_H

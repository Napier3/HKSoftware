#ifndef ACCESSPOINT_H
#define ACCESSPOINT_H

#include "server.h"
#include "common.h"
#include "types/typedeclarations.h"
#include <string>
#include <memory>

using namespace std;
using namespace pugi;

namespace scd {

class AccessPoint
{
public:
    AccessPoint(xml_node node, TypeDeclarations *typeDeclaration);
    Server *getServer() { return mServer.get(); }

    const char *getName() const;

private:
    const char *name;
    shared_ptr<Server> mServer;
};

}
#endif // ACCESSPOINT_H

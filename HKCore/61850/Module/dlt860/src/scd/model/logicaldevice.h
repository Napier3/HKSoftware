#ifndef LOGICALDEVICE_H
#define LOGICALDEVICE_H

#include "common.h"
#include "types/typedeclarations.h"

namespace scd {

class LogicalNode;
class LogicalDevice
{
public:
    LogicalDevice(xml_node ldNode, TypeDeclarations *typeDeclarations);
    const char *getInst() const;

    const char *getLdName() const;

    vector<shared_ptr<LogicalNode> > &getLogicalNodes();

private:
    void parseLogicalNodes(xml_node ldNode, TypeDeclarations *typeDeclarations);
private:
    const char *inst;
    const char *ldName;
    vector<shared_ptr<LogicalNode>> logicalNodes;
};

}
#endif // LOGICALDEVICE_H

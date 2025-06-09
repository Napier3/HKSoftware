#include "logicaldevice.h"
#include "logicalnode.h"
#include "nlogging.h"
namespace scd {

LogicalDevice::LogicalDevice(xml_node ldNode, TypeDeclarations *typeDeclarations)
{
    inst = ldNode.attribute("inst").as_string(nullptr);

    if(!inst) {
        throw ParseException("Logical devices misses inst attribute.");
    }

    ldName = ldNode.attribute("ldName").as_string(nullptr);
    parseLogicalNodes(ldNode, typeDeclarations);
}

void LogicalDevice::parseLogicalNodes(xml_node ldNode, TypeDeclarations *typeDeclarations)
{
    auto ln0Node = ldNode.child("LN0");

    if(!ln0Node) {
        throw ParseException("Logical device misses LN0.");
    }

    logicalNodes.push_back(std::make_shared<LogicalNode>(ln0Node, typeDeclarations, this));

    for(auto &&lnNode : ldNode.children("LN")) {
        try {
            logicalNodes.push_back(std::make_shared<LogicalNode>(lnNode, typeDeclarations, nullptr));
        } catch (const std::exception &ex) {
            NLOG_WARN("创建LNode[{}{}]失败，跳过此LNode，原因 {}",
                      lnNode.attribute("lnClass").as_string(),
                      lnNode.attribute("inst").as_string(), ex.what());
        }
    }
}

vector<shared_ptr<LogicalNode> > &LogicalDevice::getLogicalNodes()
{
    return logicalNodes;
}

const char *LogicalDevice::getLdName() const
{
    return ldName;
}

const char *LogicalDevice::getInst() const
{
    return inst;
}

}

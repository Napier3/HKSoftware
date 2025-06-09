#include "rptenabled.h"

namespace scd {

RptEnabled::RptEnabled(xml_node node)
{
    maxInstances = node.attribute("max").as_int();
    desc = node.attribute("desc").as_string(nullptr);
    for(auto &&child : node.children("ClientLN"))
    {
        clientLNs.push_back(make_shared<ClientLN>(child));
    }
}

int RptEnabled::getMaxInstances() const
{
    return maxInstances;
}

const char *RptEnabled::getDesc() const
{
    return desc;
}

vector<shared_ptr<ClientLN> > &RptEnabled::getClientLNs()
{
    return clientLNs;
}

}

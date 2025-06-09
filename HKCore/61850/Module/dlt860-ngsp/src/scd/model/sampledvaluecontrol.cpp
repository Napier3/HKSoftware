#include "sampledvaluecontrol.h"

namespace scd {

SampledValueControl::SampledValueControl(xml_node node)
    : mNode(node)
    , mSmvOpts(node.child("SmvOpts"))
{

}

}

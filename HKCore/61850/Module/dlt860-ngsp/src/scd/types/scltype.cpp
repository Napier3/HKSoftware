#include "scltype.h"

namespace scd {

SclType::SclType(xml_node node)
{
    id = node.attribute("id").as_string(nullptr);
    desc = node.attribute("desc").as_string(nullptr);

    if(!id) {
        throw ParseException(node, "id is missing");
    }
}

SclType::SclType(const char *pId, const char *pDesc)
    : id(pId)
    , desc(pDesc)
{

}

void SclType::setUsed(bool v)
{
    used = v;
}

const char *SclType::getId() const
{
    return id;
}

const char *SclType::getDesc() const
{
    return desc;
}

bool SclType::getUsed() const
{
    return used;
}

}

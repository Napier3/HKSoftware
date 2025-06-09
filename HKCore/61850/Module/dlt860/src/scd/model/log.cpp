#include "log.h"
namespace scd {

Log::Log(xml_node node)
{
    name = node.attribute("name").as_string(nullptr);
    if(!name) {
        name = "GeneralLog";
    }
}

const char *Log::getName() const
{
    return name;
}

}

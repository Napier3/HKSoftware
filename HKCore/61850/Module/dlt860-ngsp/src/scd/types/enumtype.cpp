#include "enumtype.h"
#include "nlogging.h"
namespace scd {

EnumType::EnumType(xml_node node)
    : SclType(node)
{
    for(auto &&child : node.children())
    {
        if(strcmp(child.name(), "EnumVal") == 0)
        {
            EnumValue value(child);
            mEnumValues.push_back(value);
        }
    }
}

EnumType::EnumType(const char *name)
    : SclType(name, "")
{

}

vector<EnumValue> &EnumType::enumValues()
{
    return mEnumValues;
}

int EnumType::getOrdByEnumString(const char *name)
{
    for(auto &value : mEnumValues)
    {
        if(strcmp(value.getSymbolicName(), name) == 0)
            return value.getOrd();
    }
    int tmp = 0;
    try {
        tmp = std::stoi(name);
    } catch (const std::exception &ex) {
        NLOG_WARN("没有找到{}对应的枚举值", name);
    }
    if(isValidOrdValue(tmp))
    {
        return tmp;
    }

    throw ParseException(string("Enum has no value ") + name);
}

bool EnumType::isValidOrdValue(int ordValue)
{
    for(auto &value : mEnumValues)
    {
        if(value.getOrd() == ordValue)
            return true;
    }
    return false;
}

}

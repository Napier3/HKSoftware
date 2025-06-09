#include "enumvalue.h"

namespace scd {

EnumValue::EnumValue(xml_node node)
{
    string ordString = node.attribute("ord").as_string();

    if(ordString.empty())
        throw ParseException("ord attribute missing");

    try {
        ord = std::stoi(ordString);
    } catch (const std::exception &ex) {
        printf("Warning: 模型文件不规范, EnumValue 枚举类型没有找到,这里对其做兼容, %s \n", ex.what());
    }
    symbolicName = node.text().as_string("");
}

int EnumValue::getOrd() const
{
    return ord;
}

const char *EnumValue::getSymbolicName() const
{
    return symbolicName;
}

}

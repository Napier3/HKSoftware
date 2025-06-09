#include "datamodelvalue.h"
#include "base64.h"
#include "attributetype.h"
#include <assert.h>
#include "nlogging.h"
#include "fmt/format.h"
namespace scd {

DataModelValue::DataModelValue()
{

}

DataModelValue::DataModelValue(const char *enumType, const char * value)
{
    try
    {
        this->enumType = enumType;
        this->mValue = stoi(value);
    }
    catch(const std::invalid_argument &ex)
    {
        this->enumType = enumType;
        this->unknownEnumValue = value;
    }

}

DataModelValue::DataModelValue(int type, SclType *sclType, const char *value)
{
    auto trimValue = trim_copy(value);
    if(trimValue != value)
    {
        NPRINTF("WARNING: value initializer contains leading or trailing whitespace\n");
    }

    switch (type) {
    case AttributeType::ENUMERATED:
    {
        auto enumType = static_cast<EnumType *>(sclType);
        try {
            mValue = enumType->getOrdByEnumString(value);
        } catch (const ParseException &ex) {

            int tmp = 0;
            try{
                tmp = std::stoi(value);
            } catch (const std::exception &ex) {
                NLOG_WARN("没有找到{}对应的枚举值", value);
                mValue = tmp;
            }
        }
    }
        break;
    case AttributeType::INT8:
    case AttributeType::INT16:
    case AttributeType::INT32:
    {
        if(trimValue.empty()) {
            mValue = int32_t(0);
        } else {
            try {
                mValue = stoi(trimValue);
            } catch (const std::exception &ex) {
                mValue = 0;
                NLOG_WARN("Warning: 模型文件不规范,值为{}", value);
            }
        }
        break;
    }
    case AttributeType::INT8U:
    case AttributeType::INT16U:
    case AttributeType::INT32U:
    case AttributeType::INT24U:
    case AttributeType::INT64:
    {
        if(trimValue.empty())
        {
            mValue = int64_t(0);
        }
        else
        {
            mValue = (int64_t)stoll(trimValue);
        }
    }
        break;
    case AttributeType::BOOLEAN:
    {
        if(trimValue.compare("true") == 0)
        {
            mValue = true;
        }
        else
        {
            mValue = false;
        }
    }
        break;
    case AttributeType::FLOAT32:
    {
        for(auto &c : trimValue)
        {
            if(c == ',')
                c = '.';
        }

        if(trimValue.empty())
        {
            mValue = float(0.0);
        }
        else
        {
            try {
                mValue = stof(trimValue);
            } catch (const std::exception &ex) {
                NLOG_WARN("float类型值转换错误，尝试转换值 '{}'", trimValue.data());
                mValue = float(0.0);
            }
        }
    }
        break;
    case AttributeType::FLOAT64:
        for(auto &c : trimValue)
        {
            if(c == ',')
                c = '.';
        }

        if(trimValue.empty())
        {
            mValue = double(0.0);
        }
        else
        {
            mValue = stod(trimValue);
        }
        break;
    case AttributeType::UNICODE_STRING_255:
        mValue = string(value);
        break;
    case AttributeType::OCTET_STRING_64:
    {
        string output;
        Base64::Decode(value, output);
        mValue = output;
    }
        break;
    case AttributeType::VISIBLE_STRING_32:
    case AttributeType::VISIBLE_STRING_64:
    case AttributeType::VISIBLE_STRING_65:
    case AttributeType::VISIBLE_STRING_129:
    case AttributeType::VISIBLE_STRING_255:
    case AttributeType::CURRENCY:
        mValue = string(value);
        break;
    case AttributeType::CHECK:
        NPRINTF("Warning: Initialization of CHECK is unsupported!");
        break;
    case AttributeType::CODEDENUM:
        if(strcmp(value, "intermediate-state") == 0)
            mValue = 0;
        else if(strcmp(value, "off") == 0)
            mValue = 1;
        else if(strcmp(value, "on") == 0)
            mValue = 2;
        else if(strcmp(value, "bad-state") == 0)
            mValue = 4;
        else if(strcmp(value, "stop") == 0)
            mValue = 0;
        else if(strcmp(value, "lower") == 0)
            mValue = 1;
        else if(strcmp(value, "higher") == 0)
            mValue = 2;
        else if(strcmp(value, "reserved") == 0)
            mValue = 4;
        else {
            try
            {
                int tmpValue = stoi(value);
                if(tmpValue <= 4)
                {
                    mValue = tmpValue;
                }
                else
                {
                    throw std::invalid_argument("");
                }
            }
            catch(const std::exception& e)
            {
                NLOG_WARN("CODEDENUM 尝试初始化为一个不支持的值 '{}'", value);
            }
        }
        break;
    case AttributeType::QUALITY:
        NLOG_WARN("不支持初始化QUALITY值");
        break;
    case AttributeType::TIMESTAMP:
    case AttributeType::ENTRY_TIME:
        for(auto &c : trimValue)
        {
            if(c == ',')
                c = '.';
        }
        break;
    case AttributeType::DBPOS:
        if (strcmp(value, "intermediate-state") == 0)
            mValue = 0;
        else if (strcmp(value, "off") == 0)
            mValue = 1;
        else if (strcmp(value, "on") == 0)
            mValue = 2;
        else if (strcmp(value, "bad-state") == 0)
            mValue = 3;
        else {
            try
            {
                int tmpValue = stoi(value);
                if (tmpValue < 4)
                {
                    mValue = tmpValue;
                }
                else
                {
                    throw std::invalid_argument("");
                }
            }
            catch (const std::exception& e)
            {
                NLOG_WARN("DBPOS 尝试初始化为一个不支持的值 '{}'", value);
                mValue = 0;
            }
        }
        break;
    case AttributeType::TCMD:
        if (strcmp(value, "stop") == 0)
            mValue = 0;
        else if (strcmp(value, "lower") == 0)
            mValue = 1;
        else if (strcmp(value, "higher") == 0)
            mValue = 2;
        else if (strcmp(value, "reserved") == 0)
            mValue = 3;
        else {
            try
            {
                int tmpValue = stoi(value);
                if (tmpValue < 4)
                {
                    mValue = tmpValue;
                }
                else
                {
                    throw std::invalid_argument("");
                }
            }
            catch (const std::exception& e)
            {
                NLOG_WARN("DBPOS 尝试初始化为一个不支持的值 '{}'", value);
                mValue = 0;
            }
        }
        break;
    default:
        throw ParseException(fmt::format("不支持的类型 {}", type));
        break;
    }
}

DataModelValue::Object &DataModelValue::getValue()
{
    return mValue;
}

const char *DataModelValue::getUnknownEnumValue() const
{
    return unknownEnumValue;
}

const char *DataModelValue::getEnumType() const
{
    return enumType;
}

}

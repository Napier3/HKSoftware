#ifndef DATAMODELVALUE_H
#define DATAMODELVALUE_H

#include <variant>
#include <string>
#include "types/typedeclarations.h"
#include "types/enumtype.h"

using namespace std;
namespace scd {

class DataModelValue
{
public:
    using Object = variant<std::monostate, int64_t, int32_t, string, bool, float, double>;
    DataModelValue();
    DataModelValue(const char *enumType, const char *value);
    DataModelValue(int type, SclType *sclType, const char *value);
    Object &getValue();

    void updateEnumOrdValue(TypeDeclarations *typeDecls)
    {
        if(enumType)
        {
            auto sclType = typeDecls->lookupType(enumType);
            if(sclType)
            {
                auto enumType = static_cast<EnumType*>(sclType);
                mValue = enumType->getOrdByEnumString(unknownEnumValue);
            }
        }
    }

    int64_t getLongValue() {
        return std::get<int64_t>(mValue);
    }

    int32_t getIntValue() {
        return std::get<int32_t>(mValue);
    }
    const char *getUnknownEnumValue() const;

    const char *getEnumType() const;

    const char *getBoolStr() const {
        return get<bool>(mValue) ? "true" : "false";
    }

    bool getBool() const {
        return get<bool>(mValue);
    }

    string getStrValue() {
        return get<string>(mValue);
    }

    float getFloatValue() {
        return get<float>(mValue);
    }

    double getDoubleValue() {
        return get<double>(mValue);
    }
private:
    Object mValue;
    const char *unknownEnumValue = nullptr;
    const char *enumType = nullptr;
};

}
#endif // DATAMODELVALUE_H

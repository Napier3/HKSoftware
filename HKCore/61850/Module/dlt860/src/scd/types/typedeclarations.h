#ifndef TYPEDECLARATIONS_H
#define TYPEDECLARATIONS_H

#include "scltype.h"
#include <string>
#include <cstring>
#include <vector>
#include "stringmap.h"
#include "common.h"

using namespace std;
using namespace pugi;

namespace scd {

class TypeDeclarations
{
public:
    TypeDeclarations();
    auto &typeDeclarations();
    void addType(shared_ptr<SclType> sclType)
    {
        mTypeDeclarations.insert({sclType->getId(), sclType});
    }

    SclType *lookupType(const char *typeId);
private:
    StrHashMap<shared_ptr<SclType>> mTypeDeclarations;
};

}
#endif // TYPEDECLARATIONS_H

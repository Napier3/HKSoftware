#include "typedeclarations.h"
namespace scd {

TypeDeclarations::TypeDeclarations()
{

}

auto &TypeDeclarations::typeDeclarations()
{
    return mTypeDeclarations;
}

SclType *TypeDeclarations::lookupType(const char *typeId)
{
    auto it = mTypeDeclarations.find(typeId);
    if(it != mTypeDeclarations.end())
    {
        return it->second.get();
    }
    return nullptr;
}

}

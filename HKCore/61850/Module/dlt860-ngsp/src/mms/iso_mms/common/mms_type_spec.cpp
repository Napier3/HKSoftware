/*
 *  mms_type_spec.c
 */

#include "libdlt860_platform_includes.h"
#include "gsp_mms_common.h"
#include "gsp_mms_type_spec.h"

using namespace GSP;

void GSP::GspMmsVariableSpecification_destroy(GspMmsVariableSpecification* typeSpec)
{
    if (typeSpec->name != nullptr)
        GLOBAL_FREEMEM(typeSpec->name);

    if (typeSpec->type == GSP_MMS_STRUCTURE) {
        int elementCount = typeSpec->typeSpec.structure.elementCount;
        int i;
        for (i = 0; i < elementCount; i++) {
            GSP::GspMmsVariableSpecification_destroy(typeSpec->typeSpec.structure.elements[i]);
        }

        GLOBAL_FREEMEM(typeSpec->typeSpec.structure.elements);
    }
    else if (typeSpec->type == GSP_MMS_ARRAY) {
        GSP::GspMmsVariableSpecification_destroy(typeSpec->typeSpec.array.elementTypeSpec);
    }

    GLOBAL_FREEMEM(typeSpec);
}

static size_t directChildStrLen(const char* childId)
{
    size_t i = 0;
    size_t childIdLen = strlen(childId);
    while (i < childIdLen) {
        if (*(childId + i) == '$')
            break;
        if (*(childId + i) == '.')
            break;

        i++;
    }

    return i;
}

GspMmsValue* GSP::GspMmsVariableSpecification_getChildValue(GspMmsVariableSpecification* typeSpec, GspMmsValue* value, const char* childId)
{
    if ((typeSpec->type == GSP_MMS_STRUCTURE) && (value->present == Data_PR_structure)) {
        size_t childLen = directChildStrLen(childId);
        int i;

        if (typeSpec->typeSpec.structure.elementCount != value->choice.structure.list.count)
            return nullptr;

        for (i = 0; i < typeSpec->typeSpec.structure.elementCount; i++) {

            if (strlen(typeSpec->typeSpec.structure.elements[i]->name) == childLen) {

                if (strncmp(typeSpec->typeSpec.structure.elements[i]->name, childId, childLen) == 0) {
                    if (childLen == strlen(childId)) {
                        return value->choice.structure.list.array[i];
                    } else {
                        return GSP::GspMmsVariableSpecification_getChildValue(typeSpec->typeSpec.structure.elements[i], value->choice.structure.list.array[i], childId + childLen + 1);
                    }
                }
            }
        }
        return nullptr;
    } else {
        return nullptr;
    }
}

GspMmsType GSP::GspMmsVariableSpecification_getType(GspMmsVariableSpecification* self)
{
    return self->type;
}

const char* GSP::GspMmsVariableSpecification_getName(GspMmsVariableSpecification* self)
{
    return self->name;
}

GspLinkedList GSP::GspMmsVariableSpecification_getStructureElements(GspMmsVariableSpecification* self)
{
    if (self->type != GSP_MMS_STRUCTURE)
        return nullptr;

    GspLinkedList elementNames = GspLinkedList_create();

    int i;
    for (i = 0; i < self->typeSpec.structure.elementCount; i++) {
        GspMmsVariableSpecification* typeSpec = self->typeSpec.structure.elements[i];

        GspLinkedList_add(elementNames, StringUtils_copyString(typeSpec->name));
    }

    return elementNames;
}

GspMmsVariableSpecification* GSP::GspMmsVariableSpecification_getNamedVariableRecursive(GspMmsVariableSpecification* variable, const char* nameId)
{
    const char* separator = strchr(nameId, '$');
    int i;
    if (separator == nullptr) {
        i = 0;
        if (variable->type == GSP_MMS_STRUCTURE) {
            for (i = 0; i < variable->typeSpec.structure.elementCount; i++) {
                if (strcmp(variable->typeSpec.structure.elements[i]->name, nameId) == 0) {
                    return variable->typeSpec.structure.elements[i];
                }
            }
        }
        return nullptr;
    } else {
        GspMmsVariableSpecification* namedVariable = nullptr;
        i = 0;
        for (i = 0; i < variable->typeSpec.structure.elementCount; i++) {
            if (strlen(variable->typeSpec.structure.elements[i]->name) == (unsigned) (separator - nameId)) {
                if (strncmp(variable->typeSpec.structure.elements[i]->name, nameId, separator - nameId) == 0) {
                    namedVariable = variable->typeSpec.structure.elements[i];
                    break;
                }
            }
        }
        if (namedVariable != nullptr) {
            if (namedVariable->type == GSP_MMS_STRUCTURE) {
                namedVariable = GSP::GspMmsVariableSpecification_getNamedVariableRecursive(namedVariable, separator + 1);
            } else if (namedVariable->type == GSP_MMS_ARRAY) {
                namedVariable = namedVariable->typeSpec.array.elementTypeSpec;

                namedVariable = GSP::GspMmsVariableSpecification_getNamedVariableRecursive(namedVariable, separator + 1);
            } else {
                return nullptr;
            }
        }
        return namedVariable;
    }
}

int GSP::GspMmsVariableSpecification_getSize(GspMmsVariableSpecification* self)
{
    switch (self->type) {
    case GSP_MMS_STRUCTURE:
        return self->typeSpec.structure.elementCount;
    case GSP_MMS_ARRAY:
        return self->typeSpec.array.elementCount;
    case GSP_MMS_INT8:
        return self->typeSpec.int8;
    case GSP_MMS_UINT8:
        return self->typeSpec.uint8;
    case GSP_MMS_FLOAT64:
    case GSP_MMS_FLOAT32:
        return self->typeSpec.floatingpoint.formatWidth;
    case GSP_MMS_BIT_STRING:
        return self->typeSpec.bitString;
    case GSP_MMS_BINARY_TIME:
        return self->typeSpec.binaryTime;
    case GSP_MMS_OCTET_STRING:
        return self->typeSpec.octetString;
    case GSP_MMS_VISIBLE_STRING:
        return self->typeSpec.visibleString;
    case GSP_MMS_UNICODE_STRING:
        return self->typeSpec.unicodeString;
    default:
        return -1;
    }
}

GspMmsVariableSpecification* GSP::GspMmsVariableSpecification_getChildSpecificationByIndex(GspMmsVariableSpecification* self, int index)
{
    if (self->type != GSP_MMS_STRUCTURE)
        return nullptr;

    if (index >= self->typeSpec.structure.elementCount)
        return nullptr;

    if (index < 0)
        return nullptr;

    return self->typeSpec.structure.elements[index];
}

GspMmsVariableSpecification* GSP::GspMmsVariableSpecification_getChildSpecificationByName(GspMmsVariableSpecification* self, const char* name, int* index)
{
    if (self->type != GSP_MMS_STRUCTURE)
        return nullptr;
    int i;
    for (i = 0; i < self->typeSpec.structure.elementCount; i++) {
        if (!strcmp(self->typeSpec.structure.elements[i]->name, name)) {

            if (index != nullptr)
                *index = i;
            return self->typeSpec.structure.elements[i];
        }
    }
    return nullptr;
}

GspMmsVariableSpecification* GSP::GspMmsVariableSpecification_getArrayElementSpecification(GspMmsVariableSpecification* self)
{
    if (self->type != GSP_MMS_ARRAY)
        return nullptr;
    return self->typeSpec.array.elementTypeSpec;
}

int GSP::GspMmsVariableSpecification_getExponentWidth(GspMmsVariableSpecification* self)
{
    if (self->type != GSP_MMS_FLOAT32)
        return -1;
    return (int) self->typeSpec.floatingpoint.exponentWidth;
}

/*
 *  gsp_mms_type_spec.h
 *  mms 数据类型参引
 */

#ifndef GSP_MMS_TYPE_SPEC_H_
#define GSP_MMS_TYPE_SPEC_H_

#include "libdlt860_common_api.h"
#include "gsp_mms_value.h"
#include "gsp_mms_common.h"
#include "gsp_mms_types.h"
#include "gsp_linked_list.h"

namespace GSP {

LIB860_API void GspMmsVariableSpecification_destroy(GspMmsVariableSpecification* self);

LIB860_API GspMmsValue* GspMmsVariableSpecification_getChildValue(GspMmsVariableSpecification* self, GspMmsValue* value, const char* childId);

LIB860_API GspMmsVariableSpecification* GspMmsVariableSpecification_getNamedVariableRecursive(GspMmsVariableSpecification* self, const char* nameId);

LIB860_API GspMmsType GspMmsVariableSpecification_getType(GspMmsVariableSpecification* self);

LIB860_API bool GspMmsVariableSpecification_isValueOfType(GspMmsVariableSpecification* self, GspMmsValue* value);

LIB860_API const char* GspMmsVariableSpecification_getName(GspMmsVariableSpecification* self);

LIB860_API GspLinkedList GspMmsVariableSpecification_getStructureElements(GspMmsVariableSpecification* self);

LIB860_API int GspMmsVariableSpecification_getSize(GspMmsVariableSpecification* self);

LIB860_API GspMmsVariableSpecification* GspMmsVariableSpecification_getChildSpecificationByIndex(GspMmsVariableSpecification* self, int index);

LIB860_API GspMmsVariableSpecification* GspMmsVariableSpecification_getChildSpecificationByName(GspMmsVariableSpecification* self, const char* name, int* index);

LIB860_API GspMmsVariableSpecification* GspMmsVariableSpecification_getArrayElementSpecification(GspMmsVariableSpecification* self);

LIB860_API int GspMmsVariableSpecification_getExponentWidth(GspMmsVariableSpecification* self);

}

#endif /* GSP_MMS_TYPE_SPEC_H_ */

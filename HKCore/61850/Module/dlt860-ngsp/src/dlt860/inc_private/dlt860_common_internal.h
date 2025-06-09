/*
 *  dlt860_common_internal.h
 */

#ifndef GSP_SRC_DLT860_INC_PRIVATE_DLT860_COMMON_INTERNAL_H_
#define GSP_SRC_DLT860_INC_PRIVATE_DLT860_COMMON_INTERNAL_H_

#include "dlt860_model.h"
#include "dlt860_common.h"

LIB860_INTERNAL char* GspMmsMapping_getMmsDomainFromObjectReference(const char* objectReference, char* buffer);

LIB860_INTERNAL char* GspMmsMapping_createMmsVariableNameFromObjectReference(const char* objectReference, GspFunctionalConstraint fc, char* buffer);

LIB860_INTERNAL GspMmsVariableAccessSpecification* GspMmsMapping_ObjectReferenceToVariableAccessSpec(char* objectReference);

LIB860_INTERNAL char* GspMmsMapping_varAccessSpecToObjectReference(GspMmsVariableAccessSpecification* varAccessSpec);

#endif

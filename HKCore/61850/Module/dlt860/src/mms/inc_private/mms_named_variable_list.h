/*
 *  mms_named_variable_list.h
 */

#ifndef GSP_MMS_NAMED_VARIABLE_LIST_H_
#define GSP_MMS_NAMED_VARIABLE_LIST_H_

#include "libdlt860_common_api.h"
#include "gsp_linked_list.h"
#include "gsp_mms_common.h"

using namespace GSP;

struct sGspMmsNamedVariableList {
	bool deletable;
	GspMmsDomain* domain;
	char* name;
	GspLinkedList listOfVariables;
};

LIB860_INTERNAL GspMmsNamedVariableListEntry MmsNamedVariableListEntry_create(GspMmsAccessSpecifier accessSpecifier);

LIB860_INTERNAL void MmsNamedVariableListEntry_destroy(GspMmsNamedVariableListEntry self);

LIB860_INTERNAL GspMmsDomain* MmsNamedVariableListEntry_getDomain(GspMmsNamedVariableListEntry self);

LIB860_INTERNAL char* MmsNamedVariableListEntry_getVariableName(GspMmsNamedVariableListEntry self);

LIB860_INTERNAL GspMmsNamedVariableList MmsNamedVariableList_create(GspMmsDomain* domain, char* name, bool deletable);

LIB860_INTERNAL char* MmsNamedVariableList_getName(GspMmsNamedVariableList self);

LIB860_INTERNAL GspMmsDomain* MmsNamedVariableList_getDomain(GspMmsNamedVariableList self);

LIB860_INTERNAL bool MmsNamedVariableList_isDeletable(GspMmsNamedVariableList self);

LIB860_INTERNAL void MmsNamedVariableList_addVariable(GspMmsNamedVariableList self, GspMmsNamedVariableListEntry variable);

LIB860_INTERNAL GspLinkedList MmsNamedVariableList_getVariableList(GspMmsNamedVariableList self);

LIB860_INTERNAL void MmsNamedVariableList_destroy(GspMmsNamedVariableList self);

#endif /* MMS_NAMED_VARIABLE_LIST_H_ */

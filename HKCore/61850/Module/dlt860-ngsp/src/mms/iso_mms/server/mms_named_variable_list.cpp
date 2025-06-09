/*
 *  mms_named_variable_list.c
 */

#include "libdlt860_platform_includes.h"

#include "mms_named_variable_list.h"

GspMmsNamedVariableListEntry
MmsNamedVariableListEntry_create(GspMmsAccessSpecifier accessSpecifier)
{
    GspMmsNamedVariableListEntry listEntry = (GspMmsNamedVariableListEntry) GLOBAL_MALLOC(sizeof(GspMmsAccessSpecifier));

	listEntry->domain = accessSpecifier.domain;
	listEntry->variableName = StringUtils_copyString(accessSpecifier.variableName);
	listEntry->arrayIndex = accessSpecifier.arrayIndex;

	if (accessSpecifier.componentName != NULL)
		listEntry->componentName = StringUtils_copyString(accessSpecifier.componentName);
	else
		listEntry->componentName = NULL;

	return listEntry;
}

void
MmsNamedVariableListEntry_destroy(GspMmsNamedVariableListEntry self)
{
	GLOBAL_FREEMEM(self->variableName);
	GLOBAL_FREEMEM(self);
}


GspMmsDomain*
MmsNamedVariableListEntry_getDomain(GspMmsNamedVariableListEntry self)
{
	return self->domain;
}

char*
MmsNamedVariableListEntry_getVariableName(GspMmsNamedVariableListEntry self) {
	return self->variableName;
}

GspMmsNamedVariableList
MmsNamedVariableList_create(GspMmsDomain* domain, char* name, bool deletable)
{
    GspMmsNamedVariableList self = (GspMmsNamedVariableList) GLOBAL_MALLOC(sizeof(struct sGspMmsNamedVariableList));

	self->deletable = deletable;
	self->name = StringUtils_copyString(name);
	self->listOfVariables = GspLinkedList_create();
	self->domain = domain;

	return self;
}

GspMmsDomain*
MmsNamedVariableList_getDomain(GspMmsNamedVariableList self)
{
    return self->domain;
}

char*
MmsNamedVariableList_getName(GspMmsNamedVariableList self)
{
	return self->name;
}

bool
MmsNamedVariableList_isDeletable(GspMmsNamedVariableList self)
{
	return self->deletable;
}

void
MmsNamedVariableList_addVariable(GspMmsNamedVariableList self, GspMmsNamedVariableListEntry variable)
{
	GspLinkedList_add(self->listOfVariables, variable);
}

GspLinkedList
MmsNamedVariableList_getVariableList(GspMmsNamedVariableList self)
{
	return self->listOfVariables;
}

static void
deleteVariableListEntry(void* listEntry)
{
    GspMmsNamedVariableListEntry entry = (GspMmsNamedVariableListEntry) listEntry;
	MmsNamedVariableListEntry_destroy(entry);
}

void
MmsNamedVariableList_destroy(GspMmsNamedVariableList self)
{
	GspLinkedList_destroyDeep(self->listOfVariables, deleteVariableListEntry);
	GLOBAL_FREEMEM(self->name);
	GLOBAL_FREEMEM(self);
}



/*
 * 	mms_domain.c
 */

#include "libdlt860_platform_includes.h"
#include "mms_device_model.h"
#include "mms_server_internal.h"

static void
freeNamedVariables(GspMmsVariableSpecification** variables, int variablesCount)
{
	int i;
	for (i = 0; i < variablesCount; i++) {
	    GspMmsVariableSpecification_destroy(variables[i]);
	}
}

GspMmsDomain*
GspMmsDomain_create(char* domainName)
{
    GspMmsDomain* self = new GspMmsDomain();

	self->domainName = StringUtils_copyString(domainName);
	self->namedVariableLists = GspLinkedList_create();
	self->journals = NULL;
	return self;
}

void
GspMmsDomain_destroy(GspMmsDomain* self)
{
	GLOBAL_FREEMEM(self->domainName);

	if (self->namedVariables != NULL) {
		freeNamedVariables(self->namedVariables,
				self->namedVariablesCount);

		GLOBAL_FREEMEM(self->namedVariables);
	}

	if (self->journals != NULL) {
	    GspLinkedList_destroyDeep(self->journals, (GspLinkedListValueDeleteFunction) GspMmsJournal_destroy);
	}

	GspLinkedList_destroyDeep(self->namedVariableLists, (GspLinkedListValueDeleteFunction) MmsNamedVariableList_destroy);

    delete self;
}

char*
GspMmsDomain_getName(GspMmsDomain* self)
{
	return self->domainName;
}

void
GspMmsDomain_addJournal(GspMmsDomain* self, const char* name)
{
    if (self->journals == NULL)
        self->journals = GspLinkedList_create();

    GspMmsJournal journal = GspMmsJournal_create(name);

    GspLinkedList_add(self->journals, (void*) journal);
}


GspMmsJournal
GspMmsDomain_getJournal(GspMmsDomain* self, const char* name)
{
    if (self->journals != NULL) {
		for(auto &item : *(self->journals))
		{
            GspMmsJournal mmsJournal = (GspMmsJournal) item;

            if (strcmp(mmsJournal->name, name) == 0)
                return mmsJournal;
        }
    }

    return NULL;
}

bool
GspMmsDomain_addNamedVariableList(GspMmsDomain* self, GspMmsNamedVariableList variableList)
{
	GspLinkedList_add(self->namedVariableLists, variableList);

	return true;
}

GspMmsNamedVariableList
GspMmsDomain_getNamedVariableList(GspMmsDomain* self, const char* variableListName)
{
	GspMmsNamedVariableList variableList = NULL;

	if (self == NULL)
	    goto exit_function;

    variableList = mmsServer_getNamedVariableListWithName(self->namedVariableLists, variableListName);

exit_function:
	return variableList;
}

void
GspMmsDomain_deleteNamedVariableList(GspMmsDomain* self, char* variableListName)
{
    // TODO kevin
    // mmsServer_deleteVariableList(self->namedVariableLists, variableListName);
}

GspLinkedList
GspMmsDomain_getNamedVariableLists(GspMmsDomain* self)
{
	return self->namedVariableLists;
}

GspMmsVariableSpecification*
GspMmsDomain_getNamedVariable(GspMmsDomain* self, char* nameId)
{
	if (self->namedVariables != NULL) {

		char* separator = strchr(nameId, '$');

		int i;

		if (separator == NULL) {

			for (i = 0; i < self->namedVariablesCount; i++) {
				if (strcmp(self->namedVariables[i]->name, nameId) == 0) {
					return self->namedVariables[i];
				}
			}

			return NULL;
		}
		else {
			GspMmsVariableSpecification* namedVariable = NULL;

			for (i = 0; i < self->namedVariablesCount; i++) {

				if (strlen(self->namedVariables[i]->name) == (unsigned) (separator - nameId)) {

					if (strncmp(self->namedVariables[i]->name, nameId, separator - nameId) == 0) {
						namedVariable = self->namedVariables[i];
						break;
					}
				}
			}

			if (namedVariable != NULL) {
				namedVariable = GspMmsVariableSpecification_getNamedVariableRecursive(namedVariable, separator + 1);
			}

			return namedVariable;
		}
	}
	return NULL;
}

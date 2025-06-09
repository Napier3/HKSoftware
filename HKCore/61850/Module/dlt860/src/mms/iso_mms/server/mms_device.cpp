/*
 *  mms_device.c
 */

#include "libdlt860_platform_includes.h"
#include "mms_server_internal.h"
#include "mms_device_model.h"
#include "stack_config.h"

GspMmsDevice*
GspMmsDevice_create(char* deviceName)
{
    GspMmsDevice* self = new GspMmsDevice();
    self->deviceName = deviceName;

    self->namedVariableLists = GspLinkedList_create();

    return self;
}

void
GspMmsDevice_destroy(GspMmsDevice* self)
{

    for(auto &item : self->domains)
    {
        GspMmsDomain_destroy(item.second);
    }

#if (CONFIG_MMS_SUPPORT_VMD_SCOPE_NAMED_VARIABLES == 1)
    if (self->namedVariables != NULL) {
        for (i = 0; i < self->namedVariablesCount; i++) {
            MmsVariableSpecification_destroy(self->namedVariables[i]);
        }

        GLOBAL_FREEMEM(self->namedVariables);
    }
#endif /* (CONFIG_MMS_SUPPORT_VMD_SCOPE_NAMED_VARIABLES == 1) */

    GspLinkedList_destroyDeep(self->namedVariableLists, (GspLinkedListValueDeleteFunction) MmsNamedVariableList_destroy);
    delete self;
}

GspMmsDomain*
GspMmsDevice_getDomain(GspMmsDevice* self, const char* domainId)
{
    int i;

    auto it = self->domains.find(domainId);
    if(it != self->domains.end())
    {
        return it->second;
    }
    return nullptr;
}

#if (CONFIG_MMS_SUPPORT_VMD_SCOPE_NAMED_VARIABLES == 1)
MmsVariableSpecification*
GspMmsDevice_getNamedVariable(MmsDevice* self, char* variableName)
{
    if (self->namedVariables != NULL) {
        char* separator = strchr(variableName, '$');

        int i;

        if (separator == NULL) {

            for (i = 0; i < self->namedVariablesCount; i++) {
                if (strcmp(self->namedVariables[i]->name, variableName) == 0) {
                    return self->namedVariables[i];
                }
            }

            return NULL;
        }
        else {
            MmsVariableSpecification* namedVariable = NULL;

            for (i = 0; i < self->namedVariablesCount; i++) {

                if (strlen(self->namedVariables[i]->name) == (unsigned) (separator - variableName)) {

                    if (strncmp(self->namedVariables[i]->name, variableName, separator - variableName) == 0) {
                        namedVariable = self->namedVariables[i];
                        break;
                    }
                }
            }

            if (namedVariable != NULL) {
                namedVariable = MmsVariableSpecification_getNamedVariableRecursive(namedVariable, separator + 1);
            }

            return namedVariable;
        }
    }

    return NULL;
}
#endif /* (CONFIG_MMS_SUPPORT_VMD_SCOPE_NAMED_VARIABLES == 1) */

GspLinkedList
GspMmsDevice_getNamedVariableLists(GspMmsDevice* self)
{
    return self->namedVariableLists;
}

GspMmsNamedVariableList
GspMmsDevice_getNamedVariableListWithName(GspMmsDevice* self, const char* variableListName)
{
    // TODO kevin
    return mmsServer_getNamedVariableListWithName(self->namedVariableLists, variableListName);
}


/*
 *  mms_model.h
 */

#ifndef GSP_MMS_DEVICE_MODEL_H_
#define GSP_MMS_DEVICE_MODEL_H_

#include "libdlt860_common_api.h"
#include "gsp_mms_type_spec.h"
#include "gsp_mms_common.h"
#include "mms_named_variable_list.h"
#include "logging_api.h"
#include "stringmap.h"

typedef struct {
    char* deviceName;

    /* MMS VMD scope variables support */
    int namedVariablesCount;
    GspMmsVariableSpecification** namedVariables;

    /* MMS VMD scope named variables list support */
    GspLinkedList namedVariableLists;

    /* MMS domain support */
    int domainCount;
    StrHashMap<GspMmsDomain*> domains;
} GspMmsDevice;


struct sGspMmsJournal {
    char* name;
    GspLogStorage logStorage;
};

typedef struct sGspMmsJournal* GspMmsJournal;

struct sGspMmsDomain {
    char* domainName;
    int namedVariablesCount;
    GspMmsVariableSpecification** namedVariables;
    GspLinkedList /*<MmsNamedVariableList>*/ namedVariableLists;
    GspLinkedList /* <MmsJournal> */ journals;
    const char *modelName;
};

LIB860_INTERNAL GspMmsDomain* GspMmsDomain_create(char* domainName);

LIB860_INTERNAL char* GspMmsDomain_getName(GspMmsDomain* self);

LIB860_INTERNAL void GspMmsDomain_addJournal(GspMmsDomain* self, const char* name);

LIB860_INTERNAL GspMmsJournal GspMmsDomain_getJournal(GspMmsDomain* self, const char* name);

LIB860_INTERNAL void GspMmsDomain_destroy(GspMmsDomain* self);

LIB860_INTERNAL bool GspMmsDomain_addNamedVariableList(GspMmsDomain* self, GspMmsNamedVariableList variableList);

LIB860_INTERNAL void GspMmsDomain_deleteNamedVariableList(GspMmsDomain* self, char* variableListName);

LIB860_INTERNAL GspMmsNamedVariableList GspMmsDomain_getNamedVariableList(GspMmsDomain* self, const char* variableListName);

LIB860_INTERNAL GspLinkedList GspMmsDomain_getNamedVariableLists(GspMmsDomain* self);

LIB860_INTERNAL GspLinkedList GspMmsDomain_getNamedVariableListValues(GspMmsDomain* self, char* variableListName);

LIB860_INTERNAL GspLinkedList GspMmsDomain_createNamedVariableListValues(GspMmsDomain* self, char* variableListName);

LIB860_INTERNAL GspMmsVariableSpecification* GspMmsDomain_getNamedVariable(GspMmsDomain* self, char* nameId);

LIB860_INTERNAL GspMmsDevice* GspMmsDevice_create(char* deviceName);

LIB860_INTERNAL void GspMmsDevice_destroy(GspMmsDevice* self);

LIB860_INTERNAL GspMmsDomain* GspMmsDevice_getDomain(GspMmsDevice* self, const char* domainId);

LIB860_INTERNAL GspMmsVariableSpecification* GspMmsDevice_getNamedVariable(GspMmsDevice* self, char* variableName);

LIB860_INTERNAL GspLinkedList GspMmsDevice_getNamedVariableLists(GspMmsDevice* self);

LIB860_INTERNAL GspMmsNamedVariableList GspMmsDevice_getNamedVariableListWithName(GspMmsDevice* self, const char* variableListName);

LIB860_INTERNAL GspMmsJournal GspMmsJournal_create(const char* name);

LIB860_INTERNAL void GspMmsJournal_destroy(GspMmsJournal self);


#endif /* MMS_DEVICE_MODEL_H_ */

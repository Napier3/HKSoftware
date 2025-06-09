/*
 *  mms_mapping_internal.h
 *
 */

#ifndef GSP_MMS_MAPPING_INTERNAL_H_
#define GSP_MMS_MAPPING_INTERNAL_H_

#include "stack_config.h"
#include "gsp_hal_thread.h"
#include "gsp_linked_list.h"
#include "map.h"
#include "stringmap.h"
#include <string>
#include "sgstorage.h"

using std::string;
using StrIedModelMap = StrHashMap<GspIedModel*>;
using StrLdMap = StrHashMap<GspLogicalDevice*>;
using StrDataSetMap = StrHashMap<GspDataSet*>;

struct sGspMmsMapping {

    GspIedModel* model;
    GspIedModel** modelss;
    GspMmsDevice* mmsDevice;
    GspMmsServer mmsServer;
    GspLinkedList reportControls;

#if (CONFIG_DLT860_LOG_SERVICE == 1)
    GspLinkedList logControls;
    GspLinkedList logInstances;
#endif

#if (CONFIG_INCLUDE_GOOSE_SUPPORT == 1)
    GspLinkedList gseControls;
    const char* gooseInterfaceId;
#endif

#if (CONFIG_IEC61850_SAMPLED_VALUES_SUPPORT == 1)
    GspLinkedList svControls;
    const char* svInterfaceId;
#endif

    GspLinkedList controlObjects;
    GspLinkedList attributeAccessHandlers;

#if (CONFIG_IEC61850_SUPPORT_USER_READ_ACCESS_CONTROL == 1)
    ReadAccessHandler readAccessHandler;
    void* readAccessHandlerParameter;
#endif

#if (CONFIG_DLT860_SETTING_GROUPS == 1)
    GspLinkedList settingGroups;
#endif

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    bool reportThreadRunning;
    GspThread reportWorkerThread;
#endif

    /* flag indicates if data model is locked --> prevents reports to be sent */
    bool isModelLocked;
    GspIedServer iedServer;
    GspIedConnectionIndicationHandler connectionIndicationHandler;
    void* connectionIndicationHandlerParameter;

    StrIedModelMap iedMap;
    StrIedModelMap domainIedMap;
    StrLdMap ldMap;
    SgStorage *sgStorage;
    StrDataSetMap dataSetMap;
};

#endif /* GSP_MMS_MAPPING_INTERNAL_H_ */

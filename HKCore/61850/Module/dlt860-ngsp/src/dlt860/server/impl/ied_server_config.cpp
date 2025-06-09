/*
 *  ied_server_config.c
 */

#include "dlt860_server.h"
#include "libdlt860_platform_includes.h"

#ifndef CONFIG_MMS_MAX_NUMBER_OF_DATA_SET_MEMBERS
#define CONFIG_MMS_MAX_NUMBER_OF_DATA_SET_MEMBERS 100
#endif

#ifndef CONFIG_MMS_MAX_NUMBER_OF_ASSOCIATION_SPECIFIC_DATA_SETS
#define CONFIG_MMS_MAX_NUMBER_OF_ASSOCIATION_SPECIFIC_DATA_SETS 10
#endif

#ifndef CONFIG_MMS_MAX_NUMBER_OF_DOMAIN_SPECIFIC_DATA_SETS
#define CONFIG_MMS_MAX_NUMBER_OF_DOMAIN_SPECIFIC_DATA_SETS 10
#endif

using namespace GSP;

GspIedServerConfig
GspIedServerConfig_create()
{
    GspIedServerConfig self = new sGspIedServerConfig();

    if (self) {
        self->reportBufferSize = CONFIG_REPORTING_DEFAULT_REPORT_BUFFER_SIZE;
        self->reportBufferSizeURCBs = CONFIG_REPORTING_DEFAULT_REPORT_BUFFER_SIZE;
        self->fileServiceBasepath = StringUtils_copyString(CONFIG_VIRTUAL_FILESTORE_BASEPATH);
        self->enableFileService = true;
        self->enableDynamicDataSetService = true;
        self->maxAssociationSpecificDataSets = CONFIG_MMS_MAX_NUMBER_OF_ASSOCIATION_SPECIFIC_DATA_SETS;
        self->maxDomainSpecificDataSets = CONFIG_MMS_MAX_NUMBER_OF_DOMAIN_SPECIFIC_DATA_SETS;
        self->maxDataSetEntries = CONFIG_MMS_MAX_NUMBER_OF_DATA_SET_MEMBERS;
        self->enableLogService = true;
        self->edition = DLT_860_EDITION_2;
        self->maxMmsConnections = 5;
    }

    return self;
}

void GspIedServerConfig_destroy(GspIedServerConfig config)
{
    delete config;
}
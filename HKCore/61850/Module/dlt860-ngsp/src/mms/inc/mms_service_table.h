#ifndef GSP_MMS_SERVICE_TABLE
#define GSP_MMS_SERVICE_TABLE
#include "mms_server_internal.h"
#include <stdio.h>
#include "asn_inc.h"
#include "mms_mapping.h"
#include "iso_server_private.h"
#include <vector>
#include <string>
#include <exception>
#include "nlogging.h"
#include "reporting.h"

struct ServiceFuncInfo;

typedef void *(*serviceFunc)(GspMmsServerConnection self, void *requestData);

struct ServiceFuncInfo
{
    serviceFunc func = nullptr;
    int index = 0;
    asn_TYPE_descriptor_t *requestAsn = nullptr;
    asn_TYPE_descriptor_t *responseAsn = nullptr;
    asn_TYPE_descriptor_t *errorAsn = nullptr;
};

int callServiceFunc(int index, GspMmsServerConnection self, GspByteBuffer *request, GspByteBuffer *response);

typedef void (*dataDumpCb)(const char *addr, const char *data, int type);

extern dataDumpCb g_dataDumpCb;
int xer_dump_to_string(const void *buffer, size_t size,
                                     void *application_specific_key);
void setDataDumpHandler(dataDumpCb func);
#endif
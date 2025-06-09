/*
 *  mms_common_internal.h
 *
 */

#ifndef GSP_MMS_COMMON_INTERNAL_H_
#define GSP_MMS_COMMON_INTERNAL_H_

#include "gsp_mms_value.h"
#include "conversions.h"
#include "byte_buffer.h"
#include "gsp_mms_server.h"

#define DEFAULT_MAX_SERV_OUTSTANDING_CALLING 5
#define DEFAULT_MAX_SERV_OUTSTANDING_CALLED 5
#define DEFAULT_DATA_STRUCTURE_NESTING_LEVEL 10

// 錯誤代碼描述
typedef struct sGspMmsServiceError
{
    int errorClass;
    int errorCode;
} GspMmsServiceError;

// mms 客户端内部参数
typedef union
{
    int32_t i32;
    uint32_t u32;
    void* ptr;
} GspMmsClientInternalParameter;

// 服务码
typedef enum {
    GSP_MMS_SC_NONE = 0,
    GSP_MMS_SC_Associate = 1,
    GSP_MMS_SC_Abort = 2,
    GSP_MMS_SC_Release = 3,
    GSP_MMS_SC_GetServerDirectory = 80,
    GSP_MMS_SC_GetLogicDeviceDirectory = 81,
    GSP_MMS_SC_GetLogicNodeDirectory = 82,
    GSP_MMS_SC_GetAllDataValues = 83,
    GSP_MMS_SC_GetAllDataDefinition = 155,
    GSP_MMS_SC_GetAllCBValues = 156,
    GSP_MMS_SC_GetDataValues = 48,
    GSP_MMS_SC_SetDataValues = 49,
    GSP_MMS_SC_GetDataDirectory = 50,
    GSP_MMS_SC_GetDataDefinition = 51,
    GSP_MMS_SC_CreateDataSet = 54,
    GSP_MMS_SC_DeleteDataSet = 55,
    GSP_MMS_SC_GetDataSetDirectory = 57,
    GSP_MMS_SC_GetDataSetValues = 58,
    GSP_MMS_SC_SetDataSetValues = 59,
    GSP_MMS_SC_Select = 68,
    GSP_MMS_SC_SelectWithValue = 69,
    GSP_MMS_SC_Cancel = 70,
    GSP_MMS_SC_Operate = 71,
    GSP_MMS_SC_CommandTermination = 72,
    GSP_MMS_SC_TimeActivatedOperate = 73,
    GSP_MMS_SC_TimeActivatedOperateTermination = 74,
    GSP_MMS_SC_SelectActiveSG = 84,
    GSP_MMS_SC_SelectEditSG = 85,
    GSP_MMS_SC_SetEditSGValue = 86,
    GSP_MMS_SC_ConfirmEditSGValues = 87,
    GSP_MMS_SC_GetEditSGValue = 88,
    GSP_MMS_SC_GetSGCBValues = 89,
    GSP_MMS_SC_Report = 90,
    GSP_MMS_SC_GetBRCBValues = 91,
    GSP_MMS_SC_SetBRCBValues = 92,
    GSP_MMS_SC_GetURCBValues = 93,
    GSP_MMS_SC_SetURCBValues = 94,
    GSP_MMS_SC_GetLCBValues = 95,
    GSP_MMS_SC_SetLCBValues = 96,
    GSP_MMS_SC_QueryLogByTime = 97,
    GSP_MMS_SC_QueryLogAfter = 98,
    GSP_MMS_SC_GetLogStatusValues = 99,
    GSP_MMS_SC_GetGoCBValues = 102,
    GSP_MMS_SC_SetGoCBValues = 103,
    GSP_MMS_SC_GetMSVCBValues = 105,
    GSP_MMS_SC_SetMSVCBValues = 106,
    GSP_MMS_SC_GetFile = 128,
    GSP_MMS_SC_SetFile = 129,
    GSP_MMS_SC_DeleteFile = 130,
    GSP_MMS_SC_GetFileAttributeValues = 131,
    GSP_MMS_SC_GetFileDirectory = 132,
    GSP_MMS_SC_GetRpcInterfaceDirectory = 110,
    GSP_MMS_SC_GetRpcMethodDirectory = 111,
    GSP_MMS_SC_GetRpcInterfaceDefinition = 112,
    GSP_MMS_SC_GetRpcMethodDefinition = 113,
    GSP_MMS_SC_RpcCall = 114,
    GSP_MMS_SC_Test = 153,
    GSP_MMS_SC_AssociateNegotiate = 154
} GSP_MMS_SC;

// mms 调用类型
struct sGspMmsOutstandingCall
{
    bool isUsed;
    uint32_t invokeId;
    GSP_MMS_SC type;
    void* userCallback;
    void* userParameter;
    GspMmsClientInternalParameter internalParameter;
    uint64_t timeout;
};
typedef struct sGspMmsOutstandingCall* GspMmsOutstandingCall;

#endif /* MMS_COMMON_INTERNAL */


#ifndef ASN_INC_H
#define ASN_INC_H

#include "INT8.h"
#include "INT16.h"
#include "INT32.h"
#include "INT64.h"
#include "INT8U.h"
#include "INT16U.h"
#include "INT32U.h"
#include "INT64U.h"
#include "FLOAT32.h"
#include "FLOAT64.h"
#include "VisibleString129.h"
#include "VisibleString255.h"
#include "UtcTime.h"
#include "BinaryTime.h"
#include "ObjectName.h"
#include "ObjectReference.h"
#include "SubReference.h"
#include "TimeStamp.h"
#include "Dbpos.h"
#include "Quality.h"
#include "Tcmd.h"
#include "EntryID.h"
#include "EntryTime.h"
#include "FileEntry.h"
#include "ServiceError.h"
#include "PHYCOMADDR.h"
#include "FunctionalConstraint.h"
#include "Originator.h"
#include "Check.h"
#include "AddCause.h"
#include "TriggerConditions.h"
#include "ReasonCode.h"
#include "RCBOptFlds.h"
#include "LCBOptFlds.h"
#include "MSVCBOptFlds.h"
#include "SmpMod.h"
#include "Data.h"
#include "DataDefinition.h"
#include "AssociateRequestPDU.h"
#include "AssociateResponsePDU.h"
#include "AssociateErrorPDU.h"
#include "ReleaseRequestPDU.h"
#include "ReleaseResponsePDU.h"
#include "ReleaseErrorPDU.h"
#include "AbortRequestPDU.h"
#include "GetServerDirectoryRequestPDU.h"
#include "GetServerDirectoryResponsePDU.h"
#include "GetServerDirectoryErrorPDU.h"
#include "GetLogicalDeviceDirectoryRequestPDU.h"
#include "GetLogicalDeviceDirectoryResponsePDU.h"
#include "GetLogicalDeviceDirectoryErrorPDU.h"
#include "ACSIClass.h"
#include "GetLogicalNodeDirectoryRequestPDU.h"
#include "GetLogicalNodeDirectoryResponsePDU.h"
#include "GetLogicalNodeDirectoryErrorPDU.h"
#include "GetAllDataValuesRequestPDU.h"
#include "GetAllDataValuesResponsePDU.h"
#include "GetAllDataValuesErrorPDU.h"
#include "GetAllDataDefinitionRequestPDU.h"
#include "GetAllDataDefinitionResponsePDU.h"
#include "GetAllDataDefinitionErrorPDU.h"
#include "GetAllCBValuesRequestPDU.h"
#include "GetAllCBValuesResponsePDU.h"
#include "GetAllCBValuesErrorPDU.h"
#include "GetDataValuesRequestPDU.h"
#include "GetDataValuesResponsePDU.h"
#include "GetDataValuesErrorPDU.h"
#include "SetDataValuesRequestPDU.h"
#include "GetDataSetValuesRequestPDUOld.h"
#include "SetDataValuesResponsePDU.h"
#include "SetDataValuesErrorPDU.h"
#include "GetDataDirectoryRequestPDU.h"
#include "GetDataDirectoryResponsePDU.h"
#include "GetDataDirectoryErrorPDU.h"
#include "GetDataDefinitionRequestPDU.h"
#include "GetDataDefinitionResponsePDU.h"
#include "GetDataDefinitionErrorPDU.h"
#include "GetDataSetValuesRequestPDU.h"
#include "GetDataSetValuesResponsePDU.h"
#include "GetDataSetValuesErrorPDU.h"
#include "SetDataSetValuesRequestPDU.h"
#include "SetDataSetValuesResponsePDU.h"
#include "SetDataSetValuesErrorPDU.h"
#include "CreateDataSetRequestPDU.h"
#include "CreateDataSetResponsePDU.h"
#include "CreateDataSetErrorPDU.h"
#include "DeleteDataSetRequestPDU.h"
#include "DeleteDataSetResponsePDU.h"
#include "DeleteDataSetErrorPDU.h"
#include "GetDataSetDirectoryRequestPDU.h"
#include "GetDataSetDirectoryResponsePDU.h"
#include "GetDataSetDirectoryErrorPDU.h"
#include "SelectActiveSGRequestPDU.h"
#include "SelectActiveSGResponsePDU.h"
#include "SelectActiveSGErrorPDU.h"
#include "SelectEditSGRequestPDU.h"
#include "SelectEditSGResponsePDU.h"
#include "SelectEditSGErrorPDU.h"
#include "SetEditSGValueRequestPDU.h"
#include "SetEditSGValueResponsePDU.h"
#include "SetEditSGValueErrorPDU.h"
#include "ConfirmEditSGValuesRequestPDU.h"
#include "ConfirmEditSGValuesResponsePDU.h"
#include "ConfirmEditSGValuesErrorPDU.h"
#include "GetEditSGValueRequestPDU.h"
#include "GetEditSGValueResponsePDU.h"
#include "GetEditSGValueErrorPDU.h"
#include "SGCB.h"
#include "GetSGCBValuesRequestPDU.h"
#include "GetSGCBValuesResponsePDU.h"
#include "GetSGCBValuesErrorPDU.h"
#include "ReportPDU.h"
#include "BRCB.h"
#include "GetBRCBValuesRequestPDU.h"
#include "GetBRCBValuesResponsePDU.h"
#include "GetBRCBValuesErrorPDU.h"
#include "SetBRCBValuesRequestPDU.h"
#include "SetBRCBValuesErrorPDU.h"
#include "URCB.h"
#include "GetURCBValuesRequestPDU.h"
#include "GetURCBValuesResponsePDU.h"
#include "GetURCBValuesErrorPDU.h"
#include "SetURCBValuesRequestPDU.h"
#include "SetURCBValuesErrorPDU.h"
#include "LogEntry.h"
#include "LCB.h"
#include "GetLCBValuesRequestPDU.h"
#include "GetLCBValuesResponsePDU.h"
#include "GetLCBValuesErrorPDU.h"
#include "SetLCBValuesRequestPDU.h"
#include "SetLCBValuesErrorPDU.h"
#include "QueryLogByTimeRequestPDU.h"
#include "QueryLogByTimeResponsePDU.h"
#include "QueryLogByTimeErrorPDU.h"
#include "QueryLogAfterRequestPDU.h"
#include "QueryLogAfterResponsePDU.h"
#include "QueryLogAfterErrorPDU.h"
#include "SendGOOSEMessage-PDU.h"
#include "GetGoReferenceRequestPDU.h"
#include "GetGoReferenceResponsePDU.h"
#include "GetGoReferenceErrorPDU.h"
#include "GetGOOSEElementNumberRequestPDU.h"
#include "GetGOOSEElementNumberResponsePDU.h"
#include "GetGOOSEElementNumberErrorPDU.h"
#include "GoCB.h"
#include "GetGoCBValuesRequestPDU.h"
#include "GetGoCBValuesResponsePDU.h"
#include "GetGoCBValuesErrorPDU.h"
#include "SetGoCBValuesRequestPDU.h"
#include "SetGoCBValuesErrorPDU.h"
#include "SendMSVMessage-PDU.h"
#include "MSVCB.h"
#include "GetMSVCBValuesRequestPDU.h"
#include "GetMSVCBValuesResponsePDU.h"
#include "GetMSVCBValuesErrorPDU.h"
#include "SetMSVCBValuesRequestPDU.h"
#include "SetMsvCBValuesErrorPDU.h"
#include "SelectRequestPDU.h"
#include "SelectResponsePDU.h"
#include "SelectErrorPDU.h"
#include "SelectWithValueRequestPDU.h"
#include "SelectWithValueResponsePDU.h"
#include "SelectWithValueErrorPDU.h"
#include "OperateRequestPDU.h"
#include "OperateResponsePDU.h"
#include "OperateErrorPDU.h"
#include "CancelRequestPDU.h"
#include "CancelResponsePDU.h"
#include "CancelErrorPDU.h"
#include "CommandTerminationRequestPDU.h"
#include "TimeActivatedOperateRequestPDU.h"
#include "TimeActivatedOperateResponsePDU.h"
#include "TimeActivatedOperateErrorPDU.h"
#include "TimeActivatedOperateTerminationRequestPDU.h"
#include "GetFileRequestPDU.h"
#include "GetFileResponsePDU.h"
#include "GetFileErrorPDU.h"
#include "SetFileRequestPDU.h"
#include "SetFileResponsePDU.h"
#include "SetFileErrorPDU.h"
#include "DeleteFileRequestPDU.h"
#include "DeleteFileResponsePDU.h"
#include "DeleteFileErrorPDU.h"
#include "GetFileAttributeValuesRequestPDU.h"
#include "GetFileAttributeValuesResponsePDU.h"
#include "GetFileAttributeValuesErrorPDU.h"
#include "GetFileDirectoryRequestPDU.h"
#include "GetFileDirectoryResponsePDU.h"
#include "GetFileDirectoryErrorPDU.h"
#include "GetRpcInterfaceDirectoryRequestPDU.h"
#include "GetRpcInterfaceDirectoryResponsePDU.h"
#include "GetRpcInterfaceDirectoryErrorPDU.h"
#include "GetRpcMethodDirectoryRequestPDU.h"
#include "GetRpcMethodDirectoryResponsePDU.h"
#include "GetRpcMethodDirectoryErrorPDU.h"
#include "GetRpcInterfaceDefinitionRequestPDU.h"
#include "GetRpcInterfaceDefinitionResponsePDU.h"
#include "GetRpcInterfaceDefinitionErrorPDU.h"
#include "GetRpcMethodDefinitionRequestPDU.h"
#include "GetRpcMethodDefinitionResponsePDU.h"
#include "GetRpcMethodDefinitionErrorPDU.h"
#include "RpcCallRequestPDU.h"
#include "RpcCallResponsePDU.h"
#include "RpcCallErrorPDU.h"
#include "AssociateNegotiateRequestPDU.h"
#include "AssociateNegotiateResponsePDU.h"
#include "AssociateNegotiateErrorPDU.h"
#include "GetLogStatusValuesRequestPDU.h"
#include "GetLogStatusValues-ResponsePDU.h"
#include "GetLogStatusValuesErrorPDU.h"

/******************************************* asn1 的类型特殊转�?********************************************/

// 报告控制块数据结�?
struct sGSPRCB
{
    // **************** 缓存和非缓存都有 *****************
    ObjectReference_t	 reference;
    VisibleString129_t	*rptID;	/* OPTIONAL */
    BOOLEAN_t	*rptEna;	/* OPTIONAL */
    ObjectReference_t	*datSet;	/* OPTIONAL */
    RCBOptFlds_t	*optFlds;	/* OPTIONAL */
    INT32U_t	*bufTm;	/* OPTIONAL */
    TriggerConditions_t	*trgOps;	/* OPTIONAL */
    INT32U_t	*intgPd;	/* OPTIONAL */
    BOOLEAN_t	*gi;	/* OPTIONAL */

    // *************** 缓存报告控制块特�?*****************
    BOOLEAN_t	*purgeBuf;	/* OPTIONAL */
    EntryID_t	*entryID;	/* OPTIONAL */
    INT16_t	*resvTms;	/* OPTIONAL */

    // **************** 非缓存控制块特有 ******************
    BOOLEAN_t	*resv;	/* OPTIONAL */
};
typedef sGSPRCB* GSPRCB;

// 缓存报告控制�?
struct sBRCBControlBlk {
    // 报告控制块信�?
    GSPRCB brcbControlBlk;
    // 报告控制块refs
    char* reportRefs;
};
typedef sBRCBControlBlk* BRCBControlBlk;

// 非缓存报告控制块
struct sURCBControlBlk {
    // 报告控制块信�?
    GSPRCB urcbControlBlk;
    // 报告控制块refs
    char* reportRefs;
};
typedef sURCBControlBlk* URCBControlBlk;

// 报告操作选项
typedef e_RCBOptFlds RCBOptFldType;

// 报告触发选项
typedef e_TriggerConditions RCBTriggerType;

// refs �?约束
struct sRefsFc {
    const char* objRefs;
    const char* fc;
};
typedef sRefsFc* RefsFC;

// refs �?�?
struct sRefsData {
    const char* objRefs;
    Data_t* data;
};
typedef sRefsData* RefsData;

// refs fc �?�?
struct sRefsFcData {
    const char* objRefs;
    const char* fc;
    Data_t* data;
};
typedef sRefsFcData* RefsFcData;

// 报告上送原�?
typedef e_ReasonCode GspReportReasonCode;

// 报告列表
typedef struct {
    ReportPDU__entry__entryData__Member **array;
    int count;
    int size;
#ifdef NOT_USE_IN_C11
	void (*free)(ReportPDU__entry__entryData__Member*); 
#else
    void (*free)(decltype(*array));
#endif
} GspReportList;

// RPC 回调结果
typedef struct {
    // 数据�?
    Data_t* data;

    // callid
    const char* callid;
} GspRPCCallResponse;

#endif // ASN_INC_H

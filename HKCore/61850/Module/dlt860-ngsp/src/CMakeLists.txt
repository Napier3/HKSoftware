# 编码调试用
# add_definitions(-DASN_EMIT_DEBUG -DASN_THREAD_SAFE)
set(CMAKE_CXX_FLAGS "-fpermissive")

# 设置共用代码
set (lib_common_SRCS
    ./common/map.cpp
    ./common/linked_list.cpp
    ./common/byte_buffer.cpp
    ./common/string_utilities.cpp
    ./common/buffer_chain.cpp
    ./common/conversions.cpp
    ./common/simple_allocator.cpp
    ./mms/iso_server/iso_connection.cpp
    ./mms/iso_server/iso_server.cpp
    ./mms/iso_cotp/cotp.cpp
    ./mms/iso_client/iso_client_connection.cpp
    ./mms/iso_common/iso_connection_parameters.cpp
    ./mms/iso_session/iso_session.cpp
    ./dlt860/client/ied_connection.cpp
    ./dlt860/common/dlt860_common.cpp
    ./dlt860/common/nlogging.cpp
    ./logging/log_storage.cpp
    ./logging/drivers/sqlite/log_storage_sqlite.cpp
    )

aux_source_directory(./dlt860/server/impl DLT860_SERVER_SRCS)
aux_source_directory(./dlt860/server/mms_mapping DLT860_SERVER_SRCS)
aux_source_directory(./dlt860/server/model DLT860_SERVER_SRCS)
aux_source_directory(./mms/iso_mms/common MMS_COMMON_SRCS)
aux_source_directory(./mms/iso_mms/server MMS_SERVER_SRCS)
aux_source_directory(./mms/iso_mms/client MMS_CLIENT_SRCS)
aux_source_directory(./mms/iso_mms/common/valuehelper VALUE_HELPER_SRCS)
aux_source_directory(./model MODEL_SRCS)
aux_source_directory(./sg SG_SRCS)

# sqlite3
set (sqlite3_SRCS
    ./../3rd_lib/sqlite/sqlite3.c
    )

# asn1c (860协议)
set (lib_asn1c_860_SRCS
    ./mms/iso_mms/asn1c_860/AbortRequestPDU.c
    ./mms/iso_mms/asn1c_860/ACSIClass.c
    ./mms/iso_mms/asn1c_860/AddCause.c
    ./mms/iso_mms/asn1c_860/ANY_aper.c
    ./mms/iso_mms/asn1c_860/ANY.c
    ./mms/iso_mms/asn1c_860/ANY_xer.c
    ./mms/iso_mms/asn1c_860/aper_decoder.c
    ./mms/iso_mms/asn1c_860/aper_encoder.c
    ./mms/iso_mms/asn1c_860/aper_opentype.c
    ./mms/iso_mms/asn1c_860/aper_support.c
    ./mms/iso_mms/asn1c_860/asn_application.c
    ./mms/iso_mms/asn1c_860/asn_bit_data.c
    ./mms/iso_mms/asn1c_860/asn_codecs_prim.c
    ./mms/iso_mms/asn1c_860/asn_codecs_prim_xer.c
    ./mms/iso_mms/asn1c_860/asn_internal.c
    ./mms/iso_mms/asn1c_860/asn_random_fill.c
    ./mms/iso_mms/asn1c_860/asn_SEQUENCE_OF.c
    ./mms/iso_mms/asn1c_860/asn_SET_OF.c
    ./mms/iso_mms/asn1c_860/AssociateErrorPDU.c
    ./mms/iso_mms/asn1c_860/AssociateNegotiateErrorPDU.c
    ./mms/iso_mms/asn1c_860/AssociateNegotiateRequestPDU.c
    ./mms/iso_mms/asn1c_860/AssociateNegotiateResponsePDU.c
    ./mms/iso_mms/asn1c_860/AssociateRequestPDU.c
    ./mms/iso_mms/asn1c_860/AssociateResponsePDU.c
    ./mms/iso_mms/asn1c_860/ber_tlv_length.c
    ./mms/iso_mms/asn1c_860/ber_tlv_tag.c
    ./mms/iso_mms/asn1c_860/BinaryTime.c
    ./mms/iso_mms/asn1c_860/BIT_STRING.c
    ./mms/iso_mms/asn1c_860/BIT_STRING_print.c
    ./mms/iso_mms/asn1c_860/BIT_STRING_rfill.c
    ./mms/iso_mms/asn1c_860/BIT_STRING_xer.c
    ./mms/iso_mms/asn1c_860/BOOLEAN_aper.c
    ./mms/iso_mms/asn1c_860/BOOLEAN.c
    ./mms/iso_mms/asn1c_860/BOOLEAN_print.c
    ./mms/iso_mms/asn1c_860/BOOLEAN_rfill.c
    ./mms/iso_mms/asn1c_860/BOOLEAN_xer.c
    ./mms/iso_mms/asn1c_860/BRCB.c
    ./mms/iso_mms/asn1c_860/CancelErrorPDU.c
    ./mms/iso_mms/asn1c_860/CancelRequestPDU.c
    ./mms/iso_mms/asn1c_860/CancelResponsePDU.c
    ./mms/iso_mms/asn1c_860/Check.c
    ./mms/iso_mms/asn1c_860/CommandTerminationRequestPDU.c
    ./mms/iso_mms/asn1c_860/ConfirmEditSGValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/ConfirmEditSGValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/ConfirmEditSGValuesResponsePDU.c
    ./mms/iso_mms/asn1c_860/constraints.c
    ./mms/iso_mms/asn1c_860/constr_CHOICE_aper.c
    ./mms/iso_mms/asn1c_860/constr_CHOICE.c
    ./mms/iso_mms/asn1c_860/constr_CHOICE_print.c
    ./mms/iso_mms/asn1c_860/constr_CHOICE_rfill.c
    ./mms/iso_mms/asn1c_860/constr_CHOICE_xer.c
    ./mms/iso_mms/asn1c_860/constr_SEQUENCE_aper.c
    ./mms/iso_mms/asn1c_860/constr_SEQUENCE.c
    ./mms/iso_mms/asn1c_860/constr_SEQUENCE_OF_aper.c
    ./mms/iso_mms/asn1c_860/constr_SEQUENCE_OF.c
    ./mms/iso_mms/asn1c_860/constr_SEQUENCE_OF_xer.c
    ./mms/iso_mms/asn1c_860/constr_SEQUENCE_print.c
    ./mms/iso_mms/asn1c_860/constr_SEQUENCE_rfill.c
    ./mms/iso_mms/asn1c_860/constr_SEQUENCE_xer.c
    ./mms/iso_mms/asn1c_860/constr_SET_OF_aper.c
    ./mms/iso_mms/asn1c_860/constr_SET_OF.c
    ./mms/iso_mms/asn1c_860/constr_SET_OF_print.c
    ./mms/iso_mms/asn1c_860/constr_SET_OF_rfill.c
    ./mms/iso_mms/asn1c_860/constr_SET_OF_xer.c
    ./mms/iso_mms/asn1c_860/constr_TYPE.c
    ./mms/iso_mms/asn1c_860/CreateDataSetErrorPDU.c
    ./mms/iso_mms/asn1c_860/CreateDataSetRequestPDU.c
    ./mms/iso_mms/asn1c_860/CreateDataSetResponsePDU.c
    ./mms/iso_mms/asn1c_860/Data.c
    ./mms/iso_mms/asn1c_860/DataDefinition.c
    ./mms/iso_mms/asn1c_860/Dbpos.c
    ./mms/iso_mms/asn1c_860/DeleteDataSetErrorPDU.c
    ./mms/iso_mms/asn1c_860/DeleteDataSetRequestPDU.c
    ./mms/iso_mms/asn1c_860/DeleteDataSetResponsePDU.c
    ./mms/iso_mms/asn1c_860/DeleteFileErrorPDU.c
    ./mms/iso_mms/asn1c_860/DeleteFileRequestPDU.c
    ./mms/iso_mms/asn1c_860/DeleteFileResponsePDU.c
    ./mms/iso_mms/asn1c_860/EntryID.c
    ./mms/iso_mms/asn1c_860/EntryTime.c
    ./mms/iso_mms/asn1c_860/EXTERNAL.c
    ./mms/iso_mms/asn1c_860/FileEntry.c
    ./mms/iso_mms/asn1c_860/FLOAT32.c
    ./mms/iso_mms/asn1c_860/FLOAT64.c
    ./mms/iso_mms/asn1c_860/FunctionalConstraint.c
    ./mms/iso_mms/asn1c_860/GetAllCBValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetAllCBValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetAllCBValuesResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetAllDataDefinitionErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetAllDataDefinitionRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetAllDataDefinitionResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetAllDataValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetAllDataValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetAllDataValuesResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetBRCBValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetBRCBValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetBRCBValuesResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetDataDefinitionErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetDataDefinitionRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetDataDefinitionResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetDataDirectoryErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetDataDirectoryRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetDataDirectoryResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetDataSetDirectoryErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetDataSetDirectoryRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetDataSetDirectoryResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetDataSetValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetDataSetValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetDataSetValuesRequestPDUOld.c
    ./mms/iso_mms/asn1c_860/GetDataSetValuesResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetDataValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetDataValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetDataValuesResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetEditSGValueErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetEditSGValueRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetEditSGValueResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetFileAttributeValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetFileAttributeValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetFileAttributeValuesResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetFileDirectoryErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetFileDirectoryRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetFileDirectoryResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetFileErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetFileRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetFileResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetGoCBValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetGoCBValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetGoCBValuesResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetGOOSEElementNumberErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetGOOSEElementNumberRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetGOOSEElementNumberResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetGoReferenceErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetGoReferenceRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetGoReferenceResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetLCBValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetLCBValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetLCBValuesResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetLogicalDeviceDirectoryErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetLogicalDeviceDirectoryRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetLogicalDeviceDirectoryResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetLogicalNodeDirectoryErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetLogicalNodeDirectoryRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetLogicalNodeDirectoryResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetLogStatusValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetLogStatusValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetLogStatusValues-ResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetMSVCBValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetMSVCBValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetMSVCBValuesResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetRpcInterfaceDefinitionErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetRpcInterfaceDefinitionRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetRpcInterfaceDefinitionResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetRpcInterfaceDirectoryErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetRpcInterfaceDirectoryRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetRpcInterfaceDirectoryResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetRpcMethodDefinitionErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetRpcMethodDefinitionRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetRpcMethodDefinitionResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetRpcMethodDirectoryErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetRpcMethodDirectoryRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetRpcMethodDirectoryResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetServerDirectoryErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetServerDirectoryRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetServerDirectoryResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetSGCBValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetSGCBValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetSGCBValuesResponsePDU.c
    ./mms/iso_mms/asn1c_860/GetURCBValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/GetURCBValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/GetURCBValuesResponsePDU.c
    ./mms/iso_mms/asn1c_860/GoCB.c
    ./mms/iso_mms/asn1c_860/GraphicString.c
    ./mms/iso_mms/asn1c_860/INT16.c
    ./mms/iso_mms/asn1c_860/INT16U.c
    ./mms/iso_mms/asn1c_860/INT32.c
    ./mms/iso_mms/asn1c_860/INT32U.c
    ./mms/iso_mms/asn1c_860/INT64.c
    ./mms/iso_mms/asn1c_860/INT64U.c
    ./mms/iso_mms/asn1c_860/INT8.c
    ./mms/iso_mms/asn1c_860/INT8U.c
    ./mms/iso_mms/asn1c_860/INTEGER_aper.c
    ./mms/iso_mms/asn1c_860/INTEGER.c
    ./mms/iso_mms/asn1c_860/INTEGER_print.c
    ./mms/iso_mms/asn1c_860/INTEGER_rfill.c
    ./mms/iso_mms/asn1c_860/INTEGER_xer.c
    ./mms/iso_mms/asn1c_860/LCB.c
    ./mms/iso_mms/asn1c_860/LCBOptFlds.c
    ./mms/iso_mms/asn1c_860/LogEntry.c
    ./mms/iso_mms/asn1c_860/MSVCB.c
    ./mms/iso_mms/asn1c_860/MSVCBOptFlds.c
    ./mms/iso_mms/asn1c_860/NativeInteger_aper.c
    ./mms/iso_mms/asn1c_860/NativeInteger.c
    ./mms/iso_mms/asn1c_860/NativeInteger_print.c
    ./mms/iso_mms/asn1c_860/NativeInteger_rfill.c
    ./mms/iso_mms/asn1c_860/NativeInteger_xer.c
    ./mms/iso_mms/asn1c_860/NULL_aper.c
    ./mms/iso_mms/asn1c_860/NULL.c
    ./mms/iso_mms/asn1c_860/NULL_print.c
    ./mms/iso_mms/asn1c_860/NULL_rfill.c
    ./mms/iso_mms/asn1c_860/NULL_xer.c
    ./mms/iso_mms/asn1c_860/ObjectDescriptor.c
    ./mms/iso_mms/asn1c_860/OBJECT_IDENTIFIER.c
    ./mms/iso_mms/asn1c_860/OBJECT_IDENTIFIER_print.c
    ./mms/iso_mms/asn1c_860/OBJECT_IDENTIFIER_rfill.c
    ./mms/iso_mms/asn1c_860/OBJECT_IDENTIFIER_xer.c
    ./mms/iso_mms/asn1c_860/ObjectName.c
    ./mms/iso_mms/asn1c_860/ObjectReference.c
    ./mms/iso_mms/asn1c_860/OCTET_STRING_aper.c
    ./mms/iso_mms/asn1c_860/OCTET_STRING.c
    ./mms/iso_mms/asn1c_860/OCTET_STRING_print.c
    ./mms/iso_mms/asn1c_860/OCTET_STRING_rfill.c
    ./mms/iso_mms/asn1c_860/OCTET_STRING_xer.c
    ./mms/iso_mms/asn1c_860/OPEN_TYPE_aper.c
    ./mms/iso_mms/asn1c_860/OPEN_TYPE.c
    ./mms/iso_mms/asn1c_860/OPEN_TYPE_xer.c
    ./mms/iso_mms/asn1c_860/OperateErrorPDU.c
    ./mms/iso_mms/asn1c_860/OperateRequestPDU.c
    ./mms/iso_mms/asn1c_860/OperateResponsePDU.c
    ./mms/iso_mms/asn1c_860/Originator.c
    ./mms/iso_mms/asn1c_860/per_decoder.c
    ./mms/iso_mms/asn1c_860/per_encoder.c
    ./mms/iso_mms/asn1c_860/per_opentype.c
    ./mms/iso_mms/asn1c_860/per_support.c
    ./mms/iso_mms/asn1c_860/PHYCOMADDR.c
    ./mms/iso_mms/asn1c_860/Quality.c
    ./mms/iso_mms/asn1c_860/QueryLogAfterErrorPDU.c
    ./mms/iso_mms/asn1c_860/QueryLogAfterRequestPDU.c
    ./mms/iso_mms/asn1c_860/QueryLogAfterResponsePDU.c
    ./mms/iso_mms/asn1c_860/QueryLogByTimeErrorPDU.c
    ./mms/iso_mms/asn1c_860/QueryLogByTimeRequestPDU.c
    ./mms/iso_mms/asn1c_860/QueryLogByTimeResponsePDU.c
    ./mms/iso_mms/asn1c_860/RCBOptFlds.c
    ./mms/iso_mms/asn1c_860/ReasonCode.c
    ./mms/iso_mms/asn1c_860/ReleaseErrorPDU.c
    ./mms/iso_mms/asn1c_860/ReleaseRequestPDU.c
    ./mms/iso_mms/asn1c_860/ReleaseResponsePDU.c
    ./mms/iso_mms/asn1c_860/ReportPDU.c
    ./mms/iso_mms/asn1c_860/RpcCallErrorPDU.c
    ./mms/iso_mms/asn1c_860/RpcCallRequestPDU.c
    ./mms/iso_mms/asn1c_860/RpcCallResponsePDU.c
    ./mms/iso_mms/asn1c_860/SelectActiveSGErrorPDU.c
    ./mms/iso_mms/asn1c_860/SelectActiveSGRequestPDU.c
    ./mms/iso_mms/asn1c_860/SelectActiveSGResponsePDU.c
    ./mms/iso_mms/asn1c_860/SelectEditSGErrorPDU.c
    ./mms/iso_mms/asn1c_860/SelectEditSGRequestPDU.c
    ./mms/iso_mms/asn1c_860/SelectEditSGResponsePDU.c
    ./mms/iso_mms/asn1c_860/SelectErrorPDU.c
    ./mms/iso_mms/asn1c_860/SelectRequestPDU.c
    ./mms/iso_mms/asn1c_860/SelectResponsePDU.c
    ./mms/iso_mms/asn1c_860/SelectWithValueErrorPDU.c
    ./mms/iso_mms/asn1c_860/SelectWithValueRequestPDU.c
    ./mms/iso_mms/asn1c_860/SelectWithValueResponsePDU.c
    ./mms/iso_mms/asn1c_860/SendGOOSEMessage-PDU.c
    ./mms/iso_mms/asn1c_860/SendMSVMessage-PDU.c
    ./mms/iso_mms/asn1c_860/ServiceError.c
    ./mms/iso_mms/asn1c_860/SetBRCBValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/SetBRCBValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/SetDataSetValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/SetDataSetValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/SetDataSetValuesResponsePDU.c
    ./mms/iso_mms/asn1c_860/SetDataValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/SetDataValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/SetDataValuesResponsePDU.c
    ./mms/iso_mms/asn1c_860/SetEditSGValueErrorPDU.c
    ./mms/iso_mms/asn1c_860/SetEditSGValueRequestPDU.c
    ./mms/iso_mms/asn1c_860/SetEditSGValueResponsePDU.c
    ./mms/iso_mms/asn1c_860/SetFileErrorPDU.c
    ./mms/iso_mms/asn1c_860/SetFileRequestPDU.c
    ./mms/iso_mms/asn1c_860/SetFileResponsePDU.c
    ./mms/iso_mms/asn1c_860/SetGoCBValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/SetGoCBValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/SetLCBValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/SetLCBValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/SetMsvCBValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/SetMSVCBValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/SetURCBValuesErrorPDU.c
    ./mms/iso_mms/asn1c_860/SetURCBValuesRequestPDU.c
    ./mms/iso_mms/asn1c_860/SGCB.c
    ./mms/iso_mms/asn1c_860/SmpMod.c
    ./mms/iso_mms/asn1c_860/SubReference.c
    ./mms/iso_mms/asn1c_860/Tcmd.c
    ./mms/iso_mms/asn1c_860/TimeActivatedOperateErrorPDU.c
    ./mms/iso_mms/asn1c_860/TimeActivatedOperateRequestPDU.c
    ./mms/iso_mms/asn1c_860/TimeActivatedOperateResponsePDU.c
    ./mms/iso_mms/asn1c_860/TimeActivatedOperateTerminationRequestPDU.c
    ./mms/iso_mms/asn1c_860/TimeStamp.c
    ./mms/iso_mms/asn1c_860/TriggerConditions.c
    ./mms/iso_mms/asn1c_860/URCB.c
    ./mms/iso_mms/asn1c_860/UtcTime.c
    ./mms/iso_mms/asn1c_860/UTF8String.c
    ./mms/iso_mms/asn1c_860/UTF8String_print.c
    ./mms/iso_mms/asn1c_860/UTF8String_rfill.c
    ./mms/iso_mms/asn1c_860/VisibleString129.c
    ./mms/iso_mms/asn1c_860/VisibleString255.c
    ./mms/iso_mms/asn1c_860/VisibleString.c
    ./mms/iso_mms/asn1c_860/xer_decoder.c
    ./mms/iso_mms/asn1c_860/xer_encoder.c
    ./mms/iso_mms/asn1c_860/xer_support.c
    )

# 设置 goose 源码
set (lib_goose_SRCS
    #./goose/goose_subscriber.c
    #./goose/goose_receiver.c
    #./goose/goose_publisher.c
    )

# 设置 sv 源码
set (lib_sv_SRCS
    #./sampled_values/sv_subscriber.c
    #./sampled_values/sv_publisher.c
    )

add_subdirectory(scd)

# 设置 linux 平台特有源码
set (lib_linux_SRCS
    )

# 设置 windows 平台特有源码
set (lib_windows_SRCS
    )

# 设置 bsd 平台特有源码
set (lib_bsd_SRCS
    )

# windows平台下源码设置
IF(WIN32)

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/winpcap/Lib/wpcap.lib")
        message("Found winpcap -> can compile with GOOSE support")
        set(WITH_WPCAP 1)
    endif()

    # asn1c 使用C编译器
    set_source_files_properties(${lib_asn1c_SRCS} PROPERTIES LANGUAGE C)

    # msvc 使用CXX编译器
    IF(MSVC)
        set_source_files_properties(${lib_common_SRCS} ${lib_windows_SRCS} PROPERTIES LANGUAGE CXX)
    ENDIF()

    # winpcap 编译器设置
    IF(WITH_WPCAP)
        IF(MSVC)
            set_source_files_properties(${lib_goose_SRCS} PROPERTIES LANGUAGE CXX)
            set_source_files_properties(${lib_sv_SRCS} PROPERTIES LANGUAGE CXX)
        ENDIF(MSVC)
    ELSE()
        add_definitions(-DEXCLUDE_ETHERNET_WINDOWS)
    ENDIF(WITH_WPCAP)
        include_directories(
            ../third_party/winpcap/include
            ../3rd_lib/sqlite
            logging
            )

        # 设置源码列表
        IF(WITH_WPCAP)
            set (library_SRCS
                ${lib_common_SRCS}
                ${lib_goose_SRCS}
                ${lib_sv_SRCS}
                ${lib_windows_SRCS}
                ${lib_asn1c_860_SRCS}
                ${MMS_COMMON_SRCS}
                ${MMS_SERVER_SRCS}
                ${MMS_CLIENT_SRCS}
                ${DLT860_SERVER_SRCS}
                ${MODEL_SRCS}
                ${SG_SRCS}
                ${VALUE_HELPER_SRCS}
                ${sqlite3_SRCS}
                )
        ELSE()
            set (library_SRCS
                ${lib_common_SRCS}
                ${lib_windows_SRCS}
                ${lib_asn1c_860_SRCS}
                ${MMS_COMMON_SRCS}
                ${MMS_SERVER_SRCS}
                ${MMS_CLIENT_SRCS}
                ${DLT860_SERVER_SRCS}
                ${MODEL_SRCS}
                ${SG_SRCS}
                ${VALUE_HELPER_SRCS}
                ${sqlite3_SRCS}
                )
    ENDIF(WITH_WPCAP)

ELSEIF(UNIX)
    IF(APPLE)
        # macos 平台下源码设置
        set (library_SRCS
            ${lib_common_SRCS}
            ${lib_asn1c_SRCS}
            ${lib_goose_SRCS}
            ${lib_sv_SRCS}
            ${lib_bsd_SRCS}
            )
    ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
        # bsd 平台下源码设置
        set (library_SRCS
            ${lib_common_SRCS}
            ${lib_asn1c_SRCS}
            ${lib_goose_SRCS}
            ${lib_sv_SRCS}
            ${lib_bsd_SRCS}
            )
    ELSE()
        # linux 平台下源码设置
        set (library_SRCS
            ${lib_common_SRCS}
            ${lib_asn1c_860_SRCS}
            ${lib_goose_SRCS}
            ${lib_sv_SRCS}
            ${lib_linux_SRCS}
            ${MMS_COMMON_SRCS}
            ${MMS_SERVER_SRCS}
            ${MMS_CLIENT_SRCS}
            ${DLT860_SERVER_SRCS}
            ${MODEL_SRCS}
            ${SG_SRCS}
            ${VALUE_HELPER_SRCS}
            ${sqlite3_SRCS}
            )
    ENDIF(APPLE)
ENDIF(WIN32)

include (GenerateExportHeader)

# 设置资源文件
set(RES_FILES "")
if ( WIN32 )
    # RC版本信息
    set(RES_FILES "${CMAKE_CURRENT_BINARY_DIR}/version.rc")
    message(STATUS "Generating RC file : ${RES_FILES}")
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/version.rc.in
        ${RES_FILES}
        @ONLY)
    set(library_SRCS ${library_SRCS} ${RES_FILES})
endif( WIN32 )

IF(UNIX)
# 创建动态库
add_library (dlt860-shared SHARED ${library_SRCS} )
set_target_properties(dlt860-shared PROPERTIES
    OUTPUT_NAME dlt860
    SOVERSION "${LIB_VERSION_MAJOR}.${LIB_VERSION_MINOR}.${LIB_VERSION_PATCH}"
    )
target_compile_definitions(dlt860-shared PRIVATE EXPORT_FUNCTIONS_FOR_DLL)
target_link_libraries(dlt860-shared dlt860hal)
GENERATE_EXPORT_HEADER(dlt860-shared
    BASE_NAME dlt860-shared
    EXPORT_MACRO_NAME dlt860-shared_EXPORT
    EXPORT_FILE_NAME dlt860-shared_export.h
    STATIC_DEFINE dlt860-shared_BUILT_AS_STATIC
    )
ENDIF(UNIX)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# 创建静态库
add_library (dlt860 STATIC ${library_SRCS})
target_link_libraries(dlt860 dlt860hal)

# 链接库依赖
IF(UNIX)
    IF (CONFIG_SYSTEM_HAS_CLOCK_GETTIME)
        target_link_libraries (dlt860
            -lpthread
            -lm
            scd
            -lrt
            -lstdc++fs
            -ldl
            )
    ELSE ()
        target_link_libraries (dlt860
            -lpthread
            scd
            -lm
            -lstdc++fs
            -ldl
            )
    ENDIF (CONFIG_SYSTEM_HAS_CLOCK_GETTIME)
ENDIF(UNIX)

if(MSVC)
    target_link_libraries (dlt860
        scd
        )
    target_compile_options(dlt860 PRIVATE "/MP")
endif(MSVC)


# winpcap 编译器时额外的链接库依赖
iF(WITH_WPCAP)
    target_link_libraries(dlt860
        ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/winpcap/lib/wpcap.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/winpcap/lib/packet.lib
        )
ENDIF(WITH_WPCAP)

# 安装行为定义
set(BINDIR "bin")
set(LIBDIR "lib")
if(UNIX)
    # debian 多架构支持
    include(GNUInstallDirs)
    set(LIBDIR ${CMAKE_INSTALL_LIBDIR})
    set(BINDIR ${CMAKE_INSTALL_BINDIR})

    # 配置版本信息
    configure_file(
        ${CMAKE_CURRENT_LIST_DIR}/libdlt860.pc.in
        ${CMAKE_CURRENT_BINARY_DIR}/libdlt860.pc @ONLY
        )
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libdlt860.pc" DESTINATION "${CMAKE_INSTALL_PREFIX}/share/pkgconfig")

    install (TARGETS dlt860-shared
        RUNTIME DESTINATION ${BINDIR} COMPONENT Applications
        ARCHIVE DESTINATION ${LIBDIR} COMPONENT Libraries
        LIBRARY DESTINATION ${LIBDIR} COMPONENT Libraries
        )
endif()

install (TARGETS dlt860
    RUNTIME DESTINATION ${BINDIR} COMPONENT Applications
    ARCHIVE DESTINATION ${LIBDIR} COMPONENT Libraries
    LIBRARY DESTINATION ${LIBDIR} COMPONENT Libraries
    )



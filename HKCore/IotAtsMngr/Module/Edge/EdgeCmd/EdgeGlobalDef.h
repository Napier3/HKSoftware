#pragma once


/////////////////////////////////////
//边设备命令主题类型
#define EDGE_CMD_TYPE_IDX_device		0x1
#define EDGE_CMD_TYPE_IDX_topo			0x2
#define EDGE_CMD_TYPE_IDX_container		0x3
#define EDGE_CMD_TYPE_IDX_app			0x4
#define EDGE_CMD_TYPE_IDX_service		0x5

//边设备命令主题类型ID
#define EDGE_CMD_STR_TYPE_ID_device			_T("device")
#define EDGE_CMD_STR_TYPE_ID_topo			_T("topo")
#define EDGE_CMD_STR_TYPE_ID_container		_T("container")
#define EDGE_CMD_STR_TYPE_ID_app			_T("app")
#define EDGE_CMD_STR_TYPE_ID_service		_T("service")

//边设备命令主题命令ID
#define EDGE_CMD_ID_command		_T("command")
#define EDGE_CMD_ID_reply		_T("reply")
#define EDGE_CMD_ID_request		_T("request")
#define EDGE_CMD_ID_response	_T("response")
#define EDGE_CMD_ID_data		_T("data")
#define EDGE_CMD_ID_event		_T("event")
#define EDGE_CMD_ID_file		_T("file")

//报文所属
#define EDGE_REPORT_JSON	0
#define EDGE_REPORT_HTTP	1
#define EDGE_REPORT_LINK	2

//边设备命令内容Type
#define EDGE_CMD_INFO_Type_DEV_EVENT_LINKUP			_T("EVENT_LINKUP")
#define EDGE_CMD_INFO_Type_DEV_EVENT_LINKDOWN		_T("EVENT_LINKDOWN")
#define EDGE_CMD_INFO_Type_DEV_CMD_SYS_UPGRADE		_T("CMD_SYS_UPGRADE")
#define EDGE_CMD_INFO_Type_DEV_CMD_STATUS_QUERY		_T("CMD_STATUS_QUERY")
#define EDGE_CMD_INFO_Type_DEV_REP_JOB_RESULT		_T("REP_JOB_RESULT")
#define EDGE_CMD_INFO_Type_DEV_REP_SYS_STATUS		_T("REP_SYS_STATUS")
#define EDGE_CMD_INFO_Type_DEV_CMD_SYS_STATUS		_T("CMD_SYS_STATUS")
#define EDGE_CMD_INFO_Type_DEV_CMD_INFO_QUERY		_T("CMD_INFO_QUERY")
#define EDGE_CMD_INFO_Type_DEV_CMD_SYS_SET_CONFIG	_T("CMD_SYS_SET_CONFIG")
#define EDGE_CMD_INFO_Type_DEV_CMD_DATETIME_SYN		_T("CMD_DATETIME_SYN")
#define EDGE_CMD_INFO_Type_DEV_EVENT_SYS_ALARM		_T("EVENT_SYS_ALARM")
#define EDGE_CMD_INFO_Type_DEV_CMD_SYS_LOG			_T("CMD_SYS_LOG")
#define EDGE_CMD_INFO_Type_DEV_EVENT_HEARTBEAT		_T("EVENT_HEARTBEAT")
#define EDGE_CMD_INFO_Type_TOPO_CMD_TOPO_ADD		_T("CMD_TOPO_ADD")
#define EDGE_CMD_INFO_Type_TOPO_CMD_TOPO_DEL		_T("CMD_TOPO_DEL")
#define EDGE_CMD_INFO_Type_TOPO_CMD_TOPO_UPDATE		_T("CMD_TOPO_UPDATE")
#define EDGE_CMD_INFO_Type_CON_CMD_CON_INSTALL		_T("CMD_CON_INSTALL")
#define EDGE_CMD_INFO_Type_CON_CMD_STATUS_QUERY		_T("CMD_STATUS_QUERY")
#define EDGE_CMD_INFO_Type_CON_REP_JOB_RESULT		_T("REP_JOB_RESULT")
#define EDGE_CMD_INFO_Type_CON_CMD_CON_START		_T("CMD_CON_START")
#define EDGE_CMD_INFO_Type_CON_CMD_CON_STOP			_T("CMD_CON_STOP")
#define EDGE_CMD_INFO_Type_CON_CMD_CON_REMOVE		_T("CMD_CON_REMOVE")
#define EDGE_CMD_INFO_Type_CON_CMD_CON_SET_CONFIG	_T("CMD_CON_SET_CONFIG")
#define EDGE_CMD_INFO_Type_CON_CMD_CON_GET_CONFIG	_T("CMD_CON_GET_CONFIG")
#define EDGE_CMD_INFO_Type_CON_CMD_CON_STATUS		_T("CMD_CON_STATUS")
#define EDGE_CMD_INFO_Type_CON_REP_CON_STATUS		_T("REP_CON_STATUS")
#define EDGE_CMD_INFO_Type_CON_EVENT_CON_ALARM		_T("EVENT_CON_ALARM")
#define EDGE_CMD_INFO_Type_CON_CMD_CON_UPGRADE		_T("CMD_CON_UPGRADE")
#define EDGE_CMD_INFO_Type_CON_CMD_CON_LOG			_T("CMD_CON_LOG")
#define EDGE_CMD_INFO_Type_APP_CMD_APP_INSTALL		_T("CMD_APP_INSTALL")
#define EDGE_CMD_INFO_Type_APP_CMD_STATUS_QUERY		_T("CMD_STATUS_QUERY")
#define EDGE_CMD_INFO_Type_APP_REP_JOB_RESULT		_T("REP_JOB_RESULT")
#define EDGE_CMD_INFO_Type_APP_CMD_APP_START		_T("CMD_APP_START")
#define EDGE_CMD_INFO_Type_APP_CMD_APP_STOP			_T("CMD_APP_STOP")
#define EDGE_CMD_INFO_Type_APP_CMD_APP_REMOVE		_T("CMD_APP_REMOVE")
#define EDGE_CMD_INFO_Type_APP_CMD_APP_ENABLE		_T("CMD_APP_ENABLE")
#define EDGE_CMD_INFO_Type_APP_CMD_APP_UNENABLE		_T("CMD_APP_UNENABLE")
#define EDGE_CMD_INFO_Type_APP_CMD_APP_SET_CONFIG	_T("CMD_APP_SET_CONFIG")
#define EDGE_CMD_INFO_Type_APP_CMD_APP_GET_CONFIG	_T("CMD_APP_GET_CONFIG")
#define EDGE_CMD_INFO_Type_APP_CMD_APP_STATUS		_T("CMD_APP_STATUS")
#define EDGE_CMD_INFO_Type_APP_REP_APP_STATUS		_T("REP_APP_STATUS")
#define EDGE_CMD_INFO_Type_APP_EVENT_APP_ALARM		_T("EVENT_APP_ALARM")
#define EDGE_CMD_INFO_Type_APP_CMD_APP_UPGRADE		_T("CMD_APP_UPGRADE")
#define EDGE_CMD_INFO_Type_APP_CMD_APP_LOG			_T("CMD_APP_LOG")
#define EDGE_CMD_INFO_Type_SVR_CMD_PROFILE			_T("CMD_PROFILE")
#define EDGE_CMD_INFO_Type_SVR_REP_DATA				_T("REP_DATA")
#define EDGE_CMD_INFO_Type_SVR_EVENT_DATA			_T("EVENT_DATA")
#define EDGE_CMD_INFO_Type_SVR_DATA_FILE			_T("DATA_FILE")
#define EDGE_CMD_INFO_Type_SVR_CMD_RPC				_T("CMD_RPC")
#define EDGE_CMD_INFO_Type_SVR_CMD_SERVICE			_T("CMD_SERVICE")

//param下的cmd的值
#define EDGE_PROCEDURE_CMD_ID_parameter_Get				_T("parameter_Get")
#define EDGE_PROCEDURE_CMD_ID_parameter_Set				_T("parameter_Set")
#define EDGE_PROCEDURE_CMD_ID_parameter_Activate		_T("parameter_Activate")
#define EDGE_PROCEDURE_CMD_ID_parameter_Cancel			_T("parameter_Cancel")
#define EDGE_PROCEDURE_CMD_ID_discrete_Get				_T("discrete_Get")
#define EDGE_PROCEDURE_CMD_ID_analog_Get				_T("analog_Get")
#define EDGE_PROCEDURE_CMD_ID_accumulator_Get			_T("accumulator_Get")
#define EDGE_PROCEDURE_CMD_ID_APPDir_Get				_T("APPDir_Get")
#define EDGE_PROCEDURE_CMD_ID_APPHFile_Get				_T("APPHFile_Get")
#define EDGE_PROCEDURE_CMD_ID_timeRead					_T("timeRead")
#define EDGE_PROCEDURE_CMD_ID_timeCheck					_T("timeCheck")
#define EDGE_PROCEDURE_CMD_ID_commad_HZ					_T("commad_HZ")
#define EDGE_PROCEDURE_CMD_ID_commad_TZ					_T("commad_TZ")
#define EDGE_PROCEDURE_CMD_ID_commad_ModelCtrl			_T("commad_ModelCtrl")
#define EDGE_PROCEDURE_CMD_ID_APP_CONFIG_Dir_Get		_T("APP_CONFIG_Dir_Get")
#define EDGE_PROCEDURE_CMD_ID_CMD_GET_APP_CONFIG		_T("CMD_GET_APP_CONFIG")
#define EDGE_PROCEDURE_CMD_ID_CMD_SET_APP_CONFIG		_T("CMD_SET_APP_CONFIG")

//边设备过程id列表
#define EDGE_PROCEDURE_ID_READ_DATASET				_T("ReadDataset")
#define EDGE_PROCEDURE_ID_READ_CMDRSLT				_T("ReadCmdRslt")

#define EDGE_PROCEDURE_ID_DEV_EVENT_LINKUP			_T("DEV_EVENT_LINKUP")
#define EDGE_PROCEDURE_ID_DEV_EVENT_LINKDOWN		_T("DEV_EVENT_LINKDOWN")
#define EDGE_PROCEDURE_ID_DEV_CMD_SYS_UPGRADE		_T("DEV_CMD_SYS_UPGRADE")
#define EDGE_PROCEDURE_ID_DEV_CMD_STATUS_QUERY		_T("DEV_CMD_STATUS_QUERY")
#define EDGE_PROCEDURE_ID_DEV_REP_JOB_RESULT		_T("DEV_REP_JOB_RESULT")
#define EDGE_PROCEDURE_ID_DEV_REP_SYS_STATUS		_T("DEV_REP_SYS_STATUS")
#define EDGE_PROCEDURE_ID_DEV_CMD_SYS_STATUS		_T("DEV_CMD_SYS_STATUS")
#define EDGE_PROCEDURE_ID_DEV_CMD_INFO_QUERY		_T("DEV_CMD_INFO_QUERY")
#define EDGE_PROCEDURE_ID_DEV_CMD_SYS_SET_CONFIG	_T("DEV_CMD_SYS_SET_CONFIG")
#define EDGE_PROCEDURE_ID_DEV_CMD_DATETIME_SYN		_T("DEV_CMD_DATETIME_SYN")
#define EDGE_PROCEDURE_ID_DEV_CMD_DATETIME_SYN_RESP _T("DEV_CMD_DATETIME_SYN_RESP")
#define EDGE_PROCEDURE_ID_DEV_EVENT_SYS_ALARM		_T("DEV_EVENT_SYS_ALARM")
#define EDGE_PROCEDURE_ID_DEV_CMD_SYS_LOG			_T("DEV_CMD_SYS_LOG")
#define EDGE_PROCEDURE_ID_DEV_EVENT_HEARTBEAT		_T("DEV_EVENT_HEARTBEAT")
#define EDGE_PROCEDURE_ID_DEV_SET_TOPO_ID			_T("SetTopoID")
#define EDGE_PROCEDURE_ID_DEV_SET_CONTAINER_ID		_T("SetContainerID")
#define EDGE_PROCEDURE_ID_DEV_SET_APP_ID			_T("SetAppID")
#define EDGE_PROCEDURE_ID_DEV_SET_ENABLE			_T("EnableLib")
#define EDGE_PROCEDURE_ID_DEV_SET_DISABLE			_T("DisableLib")

#define EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_ADD			_T("TOPO_CMD_TOPO_ADD")
#define EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_DEL			_T("TOPO_CMD_TOPO_DEL")
#define EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_UPDATE		_T("TOPO_CMD_TOPO_UPDATE")

#define EDGE_PROCEDURE_ID_CON_CMD_CON_INSTALL		_T("CON_CMD_CON_INSTALL")
#define EDGE_PROCEDURE_ID_CON_CMD_STATUS_QUERY		_T("CON_CMD_STATUS_QUERY")
#define EDGE_PROCEDURE_ID_CON_REP_JOB_RESULT		_T("CON_REP_JOB_RESULT")
#define EDGE_PROCEDURE_ID_CON_CMD_CON_START			_T("CON_CMD_CON_START")
#define EDGE_PROCEDURE_ID_CON_CMD_CON_STOP			_T("CON_CMD_CON_STOP")
#define EDGE_PROCEDURE_ID_CON_CMD_CON_REMOVE		_T("CON_CMD_CON_REMOVE")
#define EDGE_PROCEDURE_ID_CON_CMD_CON_SET_CONFIG	_T("CON_CMD_CON_SET_CONFIG")
#define EDGE_PROCEDURE_ID_CON_CMD_CON_GET_CONFIG	_T("CON_CMD_CON_GET_CONFIG")
#define EDGE_PROCEDURE_ID_CON_CMD_CON_STATUS		_T("CON_CMD_CON_STATUS")
#define EDGE_PROCEDURE_ID_CON_REP_CON_STATUS		_T("CON_REP_CON_STATUS")
#define EDGE_PROCEDURE_ID_CON_EVENT_CON_ALARM		_T("CON_EVENT_CON_ALARM")
#define EDGE_PROCEDURE_ID_CON_CMD_CON_UPGRADE		_T("CON_CMD_CON_UPGRADE")
#define EDGE_PROCEDURE_ID_CON_CMD_STATUS_QUERY		_T("CON_CMD_STATUS_QUERY")
#define EDGE_PROCEDURE_ID_CON_CMD_CON_LOG			_T("CON_CMD_CON_LOG")

#define EDGE_PROCEDURE_ID_APP_CMD_APP_INSTALL		_T("APP_CMD_APP_INSTALL")
#define EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY		_T("APP_CMD_STATUS_QUERY")
#define EDGE_PROCEDURE_ID_APP_REP_JOB_RESULT		_T("APP_REP_JOB_RESULT")
#define EDGE_PROCEDURE_ID_APP_CMD_APP_START			_T("APP_CMD_APP_START")
#define EDGE_PROCEDURE_ID_APP_CMD_APP_STOP			_T("APP_CMD_APP_STOP")
#define EDGE_PROCEDURE_ID_APP_CMD_APP_REMOVE		_T("APP_CMD_APP_REMOVE")
#define EDGE_PROCEDURE_ID_APP_CMD_APP_ENABLE		_T("APP_CMD_APP_ENABLE")
#define EDGE_PROCEDURE_ID_APP_CMD_APP_UNENABLE		_T("APP_CMD_APP_UNENABLE")
#define EDGE_PROCEDURE_ID_APP_CMD_APP_SET_CONFIG	_T("APP_CMD_APP_SET_CONFIG")
#define EDGE_PROCEDURE_ID_APP_CMD_APP_GET_CONFIG	_T("APP_CMD_APP_GET_CONFIG")
#define EDGE_PROCEDURE_ID_APP_CMD_APP_STATUS		_T("APP_CMD_APP_STATUS")
#define EDGE_PROCEDURE_ID_APP_REP_APP_STATUS		_T("APP_REP_APP_STATUS")
#define EDGE_PROCEDURE_ID_APP_EVENT_APP_ALARM		_T("APP_EVENT_APP_ALARM")
#define EDGE_PROCEDURE_ID_APP_CMD_APP_UPGRADE		_T("APP_CMD_APP_UPGRADE")
#define EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY		_T("APP_CMD_STATUS_QUERY")
#define EDGE_PROCEDURE_ID_APP_CMD_APP_LOG			_T("APP_CMD_APP_LOG")

#define EDGE_PROCEDURE_ID_SVR_CMD_PROFILE			_T("SVR_CMD_PROFILE")
#define EDGE_PROCEDURE_ID_SVR_REP_DATA				_T("SVR_REP_DATA")
#define EDGE_PROCEDURE_ID_SVR_EVENT_DATA			_T("SVR_EVENT_DATA")
#define EDGE_PROCEDURE_ID_SVR_DATA_FILE				_T("SVR_DATA_FILE")
#define EDGE_PROCEDURE_ID_SVR_CMD_RPC				_T("SVR_CMD_RPC")

#define EDGE_PROCEDURE_ID_parameter_Get				_T("parameter_Get")
#define EDGE_PROCEDURE_ID_parameter_Set				_T("parameter_Set")
#define EDGE_PROCEDURE_ID_parameter_Activate		_T("parameter_Activate")
#define EDGE_PROCEDURE_ID_parameter_Cancel			_T("parameter_Cancel")
#define EDGE_PROCEDURE_ID_discrete_Get				_T("discrete_Get")
#define EDGE_PROCEDURE_ID_analog_Get				_T("analog_Get")
#define EDGE_PROCEDURE_ID_accumulator_Get			_T("accumulator_Get")
#define EDGE_PROCEDURE_ID_APPDir_Get				_T("APPDir_Get")
#define EDGE_PROCEDURE_ID_APPHFile_Get				_T("APPHFile_Get")
#define EDGE_PROCEDURE_ID_timeRead					_T("timeRead")
#define EDGE_PROCEDURE_ID_timeCheck					_T("timeCheck")
#define EDGE_PROCEDURE_ID_commad_HZ					_T("commad_HZ")
#define EDGE_PROCEDURE_ID_commad_TZ					_T("commad_TZ")
#define EDGE_PROCEDURE_ID_commad_ModelCtrl			_T("commad_ModelCtrl")
#define EDGE_PROCEDURE_ID_APP_CONFIG_Dir_Get		_T("APP_CONFIG_Dir_Get")
#define EDGE_PROCEDURE_ID_CMD_GET_APP_CONFIG		_T("CMD_GET_APP_CONFIG")
#define EDGE_PROCEDURE_ID_CMD_SET_APP_CONFIG		_T("CMD_SET_APP_CONFIG")

#define Prcdr_RecordMode_None	_T("none")
#define Prcdr_RecordMode_Own	_T("own")
#define Prcdr_RecordMode_All	_T("all")

//yzj
#define EDGE_DATA_FORMAT_JSON _T("JSON")
#define EDGE_DATA_FORMAT_XML _T("XML")

#define EDGE_DATATYPE_LONG		_T("long")
#define EDGE_DATATYPE_DOUBLE	_T("double")
#define EDGE_DATATYPE_STRING	_T("string")

//yzj 边设备变量名称
#define EDGE_PROCEDURE_VAR_cmd	_T("cmd")
#define EDGE_PROCEDURE_VAR_jobId _T("jobId")
#define EDGE_PROCEDURE_VAR_dateTime _T("dateTime")
#define EDGE_PROCEDURE_VAR_timeZone _T("timeZone")
#define EDGE_PROCEDURE_VAR_DirReq _T("DirReq")
#define EDGE_PROCEDURE_VAR_DirResp _T("DirResp")
#define EDGE_PROCEDURE_VAR_body _T("body")
#define EDGE_PROCEDURE_VAR_policy _T("policy")
#define EDGE_PROCEDURE_VAR_version _T("version")
#define EDGE_PROCEDURE_VAR_appHash _T("appHash")
#define EDGE_PROCEDURE_VAR_srvNumber _T("srvNumber")
#define EDGE_PROCEDURE_VAR_process _T("process")
#define EDGE_PROCEDURE_VAR_upgradeType _T("upgradeType")
#define EDGE_PROCEDURE_VAR_file _T("file")
#define EDGE_PROCEDURE_VAR_File _T("File")
#define EDGE_PROCEDURE_VAR_name _T("name")
#define EDGE_PROCEDURE_VAR_status _T("status")
#define EDGE_PROCEDURE_VAR_url _T("url")
#define EDGE_PROCEDURE_VAR_size _T("size")
#define EDGE_PROCEDURE_VAR_fileType	_T("fileType")
#define EDGE_PROCEDURE_VAR_md5 _T("md5")
#define EDGE_PROCEDURE_VAR_sign _T("sign")
#define EDGE_PROCEDURE_VAR_dev _T("dev")
#define EDGE_PROCEDURE_VAR_cpu _T("cpu")
#define EDGE_PROCEDURE_VAR_mem _T("mem")
#define EDGE_PROCEDURE_VAR_disk _T("disk")
#define EDGE_PROCEDURE_VAR_temperature _T("temperature")
#define EDGE_PROCEDURE_VAR_os _T("os")
#define EDGE_PROCEDURE_VAR_links _T("links")
#define EDGE_PROCEDURE_VAR_linkState _T("linkState")
#define EDGE_PROCEDURE_VAR_apps _T("apps")
#define EDGE_PROCEDURE_VAR_appCfgs _T("appCfgs")
#define EDGE_PROCEDURE_VAR_contStatus _T("contStatus")
#define EDGE_PROCEDURE_VAR_repPeriod _T("repPeriod")
#define EDGE_PROCEDURE_VAR_hardVersion _T("hardVersion")
#define EDGE_PROCEDURE_VAR_devType _T("devType")
#define EDGE_PROCEDURE_VAR_devName _T("devName")
#define EDGE_PROCEDURE_VAR_mfgInfo _T("mfgInfo")
#define EDGE_PROCEDURE_VAR_devStatus _T("devStatus")
#define EDGE_PROCEDURE_VAR_cpus _T("cpus")
#define EDGE_PROCEDURE_VAR_frequency _T("frequency")
#define EDGE_PROCEDURE_VAR_cache _T("cache")
#define EDGE_PROCEDURE_VAR_arch _T("arch")
#define EDGE_PROCEDURE_VAR_cpuLmt _T("cpuLmt")
#define EDGE_PROCEDURE_VAR_memLmt _T("memLmt")
#define EDGE_PROCEDURE_VAR_diskLmt _T("diskLmt")
#define EDGE_PROCEDURE_VAR_memory	_T("memory")
#define EDGE_PROCEDURE_VAR_temLow _T("temLow")
#define EDGE_PROCEDURE_VAR_temHigh _T("temHigh")
#define EDGE_PROCEDURE_VAR_devPeriod _T("devPeriod")
#define EDGE_PROCEDURE_VAR_conPeriod _T("conPeriod")
#define EDGE_PROCEDURE_VAR_appPeriod _T("appPeriod")
#define EDGE_PROCEDURE_VAR_heartPeriod _T("heartPeriod")
#define EDGE_PROCEDURE_VAR_logType _T("logType")
#define EDGE_PROCEDURE_VAR_container _T("container")
#define EDGE_PROCEDURE_VAR_image	_T("image")
#define EDGE_PROCEDURE_VAR_withAPP	_T("withAPP")
#define EDGE_PROCEDURE_VAR_cfgCpu	_T("cfgCpu")
#define EDGE_PROCEDURE_VAR_cfgMem	_T("cfgMem")
#define EDGE_PROCEDURE_VAR_cfgDisk	_T("cfgDisk")
#define EDGE_PROCEDURE_VAR_port	_T("port")
#define EDGE_PROCEDURE_VAR_mount	_T("mount")
#define EDGE_PROCEDURE_VAR_networkMode	_T("networkMode")
#define EDGE_PROCEDURE_VAR_env	_T("env")
#define EDGE_PROCEDURE_VAR_Lmt	_T("Lmt")
#define EDGE_PROCEDURE_VAR_unit _T("unit")
#define EDGE_PROCEDURE_VAR_enable _T("enable")
#define EDGE_PROCEDURE_VAR_app _T("app")
#define EDGE_PROCEDURE_VAR_deviceIds _T("deviceIds")
#define EDGE_PROCEDURE_VAR_modelData _T("modelData")
#define EDGE_PROCEDURE_VAR_code _T("code")
#define EDGE_PROCEDURE_VAR_msg _T("msg")
#define EDGE_PROCEDURE_VAR_progress _T("progress")
#define EDGE_PROCEDURE_VAR_event _T("event")
#define EDGE_PROCEDURE_VAR_data _T("data")
#define EDGE_PROCEDURE_VAR_deviceInfos _T("deviceInfos")
#define EDGE_PROCEDURE_VAR_contPara _T("contPara")
#define EDGE_PROCEDURE_VAR_id _T("id")
#define EDGE_PROCEDURE_VAR_type _T("type")
#define EDGE_PROCEDURE_VAR_mac _T("mac")
#define EDGE_PROCEDURE_VAR_srvIndex _T("srvIndex")
#define EDGE_PROCEDURE_VAR_srvName _T("srvName")
#define EDGE_PROCEDURE_VAR_srvEnable _T("srvEnable")
#define EDGE_PROCEDURE_VAR_srvStatus _T("srvStatus")
#define EDGE_PROCEDURE_VAR_cpuRate _T("cpuRate")
#define EDGE_PROCEDURE_VAR_memUsed _T("memUsed")
#define EDGE_PROCEDURE_VAR_startTime _T("startTime")
#define EDGE_PROCEDURE_VAR_state _T("state")
#define EDGE_PROCEDURE_VAR_diskUsed _T("diskUsed")
#define EDGE_PROCEDURE_VAR_ip _T("ip")
#define EDGE_PROCEDURE_VAR_created _T("created")
#define EDGE_PROCEDURE_VAR_started _T("started")
#define EDGE_PROCEDURE_VAR_lifeTime _T("lifeTime")
#define EDGE_PROCEDURE_VAR_method _T("method")
#define EDGE_PROCEDURE_VAR_nodeId _T("nodeId")
#define EDGE_PROCEDURE_VAR_description _T("description")
#define EDGE_PROCEDURE_VAR_model _T("model")
#define EDGE_PROCEDURE_VAR_modelId _T("modelId")
#define EDGE_PROCEDURE_VAR_deviceId _T("deviceId")
#define EDGE_PROCEDURE_VAR_statusCode _T("statusCode")
#define EDGE_PROCEDURE_VAR_fileDir _T("fileDir")
#define EDGE_PROCEDURE_VAR_fileName _T("fileName")
#define EDGE_PROCEDURE_VAR_fileSize _T("fileSize")
#define EDGE_PROCEDURE_VAR_Content _T("Content")
#define EDGE_PROCEDURE_VAR_sendmsg _T("sendmsg")
#define EDGE_PROCEDURE_VAR_sendmsg_topic _T("sendmsg-topic")
#define EDGE_PROCEDURE_VAR_sendmsg_message _T("sendmsg-message")
#define EDGE_PROCEDURE_VAR_recvmsg _T("recvmsg")
#define EDGE_PROCEDURE_VAR_recvmsg_topic _T("recvmsg-topic")
#define EDGE_PROCEDURE_VAR_recvmsg_message _T("recvmsg-message")
#define EDGE_PROCEDURE_VAR_recvmsg_msg _T("recvmsg-msg")
#define EDGE_PROCEDURE_VAR_recvmsg_code _T("recvmsg-code")
#define EDGE_PROCEDURE_VAR_sendstate _T("sendstate")
#define EDGE_PROCEDURE_VAR_sendstate_topic _T("sendstate-topic")
#define EDGE_PROCEDURE_VAR_sendstate_message _T("sendstate-message")
#define EDGE_PROCEDURE_VAR_recvstate _T("recvstate")
#define EDGE_PROCEDURE_VAR_recvstate_topic _T("recvstate-topic")
#define EDGE_PROCEDURE_VAR_recvstate_message _T("recvstate-message")
#define EDGE_PROCEDURE_VAR_recvstate_msg _T("recvstate-msg")
#define EDGE_PROCEDURE_VAR_recvstate_code _T("recvstate-code")
#define EDGE_PROCEDURE_VAR_resultreport _T("resultreport")
#define EDGE_PROCEDURE_VAR_message _T("message")
#define EDGE_PROCEDURE_VAR_topic _T("topic")
#define EDGE_PROCEDURE_VAR_RequestAddr _T("RequestAddr")
#define EDGE_PROCEDURE_VAR_RequestMessage _T("RequestMessage")
#define EDGE_PROCEDURE_VAR_ResponseMessage _T("ResponseMessage")
#define EDGE_PROCEDURE_VAR_TopoAddResponse _T("TopoAddResponse")
#define EDGE_PROCEDURE_VAR_TopoAddResponseTopic _T("TopoAddResponseTopic")
#define EDGE_PROCEDURE_VAR_TopoAddResponseMsg _T("TopoAddResponseMsg")
#define EDGE_PROCEDURE_VAR_TopoAddRequest _T("TopoAddRequest")
#define EDGE_PROCEDURE_VAR_TopoAddRequestTopic _T("TopoAddRequestTopic")
#define EDGE_PROCEDURE_VAR_TopoAddRequestMsg _T("TopoAddRequestMsg")
#define EDGE_PROCEDURE_VAR_TopoDelResponse _T("TopoDelResponse")
#define EDGE_PROCEDURE_VAR_TopoDelResponseTopic _T("TopoDelResponseTopic")
#define EDGE_PROCEDURE_VAR_TopoDelResponseMsg _T("TopoDelResponseMsg")
#define EDGE_PROCEDURE_VAR_TopoDelRequest _T("TopoDelRequest")
#define EDGE_PROCEDURE_VAR_TopoDelRequestTopic _T("TopoDelRequestTopic")
#define EDGE_PROCEDURE_VAR_TopoDelRequestMsg _T("TopoDelRequestMsg")
#define EDGE_PROCEDURE_VAR_TopoUpdateResponse _T("TopoUpdateResponse")
#define EDGE_PROCEDURE_VAR_TopoUpdateResponseTopic _T("TopoUpdateResponseTopic")
#define EDGE_PROCEDURE_VAR_TopoUpdateResponseMsg _T("TopoUpdateResponseMsg")
#define EDGE_PROCEDURE_VAR_TopoUpdateRequest _T("TopoUpdateRequest")
#define EDGE_PROCEDURE_VAR_TopoUpdateRequestTopic _T("TopoUpdateRequestTopic")
#define EDGE_PROCEDURE_VAR_TopoUpdateRequestMsg _T("TopoUpdateRequestMsg")
#define EDGE_PROCEDURE_VAR_tempValue _T("tempValue")
#define EDGE_PROCEDURE_VAR_devDateTime _T("devDateTime")
#define EDGE_PROCEDURE_VAR_devStDateTime _T("devStDateTime")
#define EDGE_PROCEDURE_VAR_devRunTime _T("devRunTime")
#define EDGE_PROCEDURE_VAR_longitude _T("longitude")
#define EDGE_PROCEDURE_VAR_latitude	_T("latitude")
#define EDGE_PROCEDURE_VAR_errorinfo	_T("errorinfo")

//yzj 逻辑设备、数据集对应ID
#define EDGE_LDEV_ID_TEMPLATEPROT _T("TEMPLATEPROT")
#define EDGE_LDEV_ID_ServiceData _T("ServiceData")
#define EDGE_LDEV_ID_DeviceData _T("DeviceData")
#define EDGE_LDEV_ID_ContainerData _T("ContainerData")
#define EDGE_LDEV_ID_AppData _T("AppData")
#define EDGE_LDEV_ID_ConnectData _T("ConnectData")
#define EDGE_LDEV_ID_report _T("report")

//融合终端数据模型文件内的DatasetID
#define EDGE_DATASET_ID_ConnectRes	_T("ConnectRes")

#define EDGE_DATASET_ID_DEV_LinkUp _T("DeviceLinkUp")
#define EDGE_DATASET_ID_DEV_LinkDown _T("DeviceLinkDown")
#define EDGE_DATASET_ID_DEV_UpGrade _T("DeviceUpGrade")
#define EDGE_DATASET_ID_DEV_SysStatus _T("DeviceSysStatus")
#define EDGE_DATASET_ID_DEV_Info _T("DeviceInfo")
#define EDGE_DATASET_ID_DEV_SysPara _T("DeviceSysPara")
#define EDGE_DATASET_ID_DEV_SYN _T("DeviceSYN")
#define EDGE_DATASET_ID_DEV_Event _T("DeviceEvent")
#define EDGE_DATASET_ID_DEV_Log _T("DeviceLog")
#define EDGE_DATASET_ID_DEV_ChangeInfo _T("DeviceChangeInfo")
#define EDGE_DATASET_ID_TOPO_Admin _T("TopoAdmin")
#define EDGE_DATASET_ID_DEV_DeviceHeart	_T("DeviceHeart")

#define EDGE_DATASET_ID_CON_Install _T("ContainerInstall")
#define EDGE_DATASET_ID_CON_Control _T("ContainerControl")
#define EDGE_DATASET_ID_CON_Cfg _T("ContainerCfg")
#define EDGE_DATASET_ID_CON_State _T("ContainerState")
#define EDGE_DATASET_ID_CON_Event _T("ContainerEvent")
#define EDGE_DATASET_ID_CON_Upgrade _T("ContainerUpgrade")
#define EDGE_DATASET_ID_CON_Log _T("ContainerLog")
#define EDGE_DATASET_ID_CON_ChangeInfo _T("ContainerChangeInfo")

#define EDGE_DATASET_ID_APP_Install _T("AppInstall")
#define EDGE_DATASET_ID_APP_Control _T("AppControl")
#define EDGE_DATASET_ID_APP_Cfg _T("AppResourcesCfg")
#define EDGE_DATASET_ID_APP_Read _T("AppResourcesRead")
#define EDGE_DATASET_ID_APP_State _T("AppState")
#define EDGE_DATASET_ID_APP_Event _T("AppEvent")
#define EDGE_DATASET_ID_APP_Upgrade _T("AppUpgrade")
#define EDGE_DATASET_ID_APP_ChangeInfo _T("AppChangeInfo")
#define EDGE_DATASET_ID_APP_Log _T("AppLog")

#define EDGE_DATASET_ID_Parameter _T("Parameter")
#define EDGE_DATASET_ID_Din _T("Din")
#define EDGE_DATASET_ID_Ain _T("Ain")
#define EDGE_DATASET_ID_AccumulateData _T("Accumulate_data")
#define EDGE_DATASET_ID_TimeCheck _T("Time_check")
#define EDGE_DATASET_ID_RemCtl _T("RemCtl")
#define EDGE_DATASET_ID_4GModify _T("4G_modify")
#define EDGE_DATASET_ID_APPDirGet _T("APPDir")
#define EDGE_DATASET_ID_APPDirGet_HISTORY _T("HISTORY")
#define EDGE_DATASET_ID_APPHFileGet _T("APPHFile")
#define EDGE_DATASET_ID_APPCONFIG _T("APP_CONFIG_body")
#define EDGE_DATASET_ID_APPCONFIGDirGet _T("APP_CONFIG_array")
#define EDGE_DATASET_ID_SRV_Profile _T("ServiceProfile")
#define EDGE_DATASET_ID_SRV_Event _T("ServiceEvent")
#define EDGE_DATASET_ID_SRV_DataFile _T("ServiceDataFile")

#define EDGE_DATASET_ID_jsonpackage _T("jsonpackage")
#define EDGE_DATASET_ID_httppackage	_T("httppackage")
#define EDGE_DATASET_ID_Linkpackage _T("Linkpackage")

//边设备报文中的msg和code
#define EDGE_CODE_IDX_200	200
#define EDGE_CODE_IDX_202	202
#define EDGE_CODE_IDX_400	400
#define EDGE_CODE_IDX_401	401
#define EDGE_CODE_IDX_403	403
#define EDGE_CODE_IDX_404	404
#define EDGE_CODE_IDX_408	408
#define EDGE_CODE_IDX_500	500
#define EDGE_CODE_IDX_600	600

#define EDGE_CODE_STR_200	_T("请求成功")
#define EDGE_CODE_STR_202	_T("请求被接受，但是服务器未处理完")
#define EDGE_CODE_STR_400	_T("请求失败")
#define EDGE_CODE_STR_401	_T("请求未认证/认证错误")
#define EDGE_CODE_STR_403	_T("请求被拒绝")
#define EDGE_CODE_STR_404	_T("请求的资源不存在")
#define EDGE_CODE_STR_408	_T("请求超出了服务器的等待时间")
#define EDGE_CODE_STR_ERROE	_T("其他错误")

//边设备报文中可能出现的错误提示,需要写入报告
#define EDGE_ERR_TYPE_LONG	_T("错误原因:参数类型应该为[long];")
#define EDGE_ERR_TYPE_DOUBLE	_T("错误原因:参数类型应该为[double/float];")
#define EDGE_ERR_TYPE_STRING	_T("错误原因:参数类型应该为[string];")
#define EDGE_ERR_TYPE_ARRAY	_T("错误原因:参数类型应该为[array];")
#define EDGE_ERR_TYPE_MISSING	_T("错误原因:标签不存在;")


inline long edge_Code_Str_To_Idx_V4(const CString &strCode)
{
	if (strCode == EDGE_CODE_STR_200)
	{
		return EDGE_CODE_IDX_200;
	}
	else if (strCode == EDGE_CODE_STR_202)
	{
		return EDGE_CODE_IDX_202;
	}
	else if (strCode == EDGE_CODE_STR_400)
	{
		return EDGE_CODE_IDX_400;
	}
	else if (strCode == EDGE_CODE_STR_401)
	{
		return EDGE_CODE_IDX_401;
	}
	else if (strCode == EDGE_CODE_STR_403)
	{
		return EDGE_CODE_IDX_403;
	}
	else if (strCode == EDGE_CODE_STR_404)
	{
		return EDGE_CODE_IDX_404;
	}
	else if (strCode == EDGE_CODE_STR_ERROE)
	{
		return EDGE_CODE_IDX_600;
	}
	return 0;
}

inline long edge_Code_Str_To_Idx_V5(const CString &strCode)
{
	if (strCode == EDGE_CODE_STR_200)
	{
		return EDGE_CODE_IDX_200;
	}
	else if (strCode == EDGE_CODE_STR_202)
	{
		return EDGE_CODE_IDX_202;
	}
	else if (strCode == EDGE_CODE_STR_400)
	{
		return EDGE_CODE_IDX_400;
	}
	else if (strCode == EDGE_CODE_STR_401)
	{
		return EDGE_CODE_IDX_401;
	}
	else if (strCode == EDGE_CODE_STR_403)
	{
		return EDGE_CODE_IDX_403;
	}
	else if (strCode == EDGE_CODE_STR_404)
	{
		return EDGE_CODE_IDX_404;
	}
	else if (strCode == EDGE_CODE_STR_408)
	{
		return EDGE_CODE_IDX_408;
	}
	else if (strCode == EDGE_CODE_STR_ERROE)
	{
		return EDGE_CODE_IDX_500;	
	}
	return 0;
}

inline CString edge_Code_Idx_To_Str(long nCmdTypeNum)
{
	switch(nCmdTypeNum)
	{
	case EDGE_CODE_IDX_200:
		return EDGE_CODE_STR_200;
	case EDGE_CODE_IDX_202:
		return EDGE_CODE_STR_202;
	case EDGE_CODE_IDX_400:
		return EDGE_CODE_STR_400;
	case EDGE_CODE_IDX_401:
		return EDGE_CODE_STR_401;
	case EDGE_CODE_IDX_403:
		return EDGE_CODE_STR_403;
	case EDGE_CODE_IDX_404:
		return EDGE_CODE_STR_404;
	case EDGE_CODE_IDX_408:
		return EDGE_CODE_STR_408;
	case EDGE_CODE_IDX_500:
	case EDGE_CODE_IDX_600:
		return EDGE_CODE_STR_ERROE;
	default:
		break;
	}

	return _T("");
}

inline long edge_CmdTypeID_Str_To_Idx(const CString &strCmdTypeID)
{
	if (strCmdTypeID == EDGE_CMD_STR_TYPE_ID_device)
	{
		return EDGE_CMD_TYPE_IDX_device;
	}
	else if (strCmdTypeID == EDGE_CMD_STR_TYPE_ID_topo)
	{
		return EDGE_CMD_TYPE_IDX_topo;
	}
	else if (strCmdTypeID == EDGE_CMD_STR_TYPE_ID_container)
	{
		return EDGE_CMD_TYPE_IDX_container;
	}
	else if (strCmdTypeID == EDGE_CMD_STR_TYPE_ID_app)
	{
		return EDGE_CMD_TYPE_IDX_app;
	}
	else if (strCmdTypeID == EDGE_CMD_STR_TYPE_ID_service)
	{
		return EDGE_CMD_TYPE_IDX_service;
	}

	return 0;
}

inline CString edge_CmdTypeID_Idx_To_Str(long nCmdTypeNum)
{
	switch(nCmdTypeNum)
	{
	case EDGE_CMD_TYPE_IDX_device:
		return EDGE_CMD_STR_TYPE_ID_device;
	case EDGE_CMD_TYPE_IDX_topo:
		return EDGE_CMD_STR_TYPE_ID_topo;
	case EDGE_CMD_TYPE_IDX_container:
		return EDGE_CMD_STR_TYPE_ID_container;
	case EDGE_CMD_TYPE_IDX_app:
		return EDGE_CMD_STR_TYPE_ID_app;
	case EDGE_CMD_TYPE_IDX_service:
		return EDGE_CMD_STR_TYPE_ID_service;
	default:
		break;
	}

	return _T("");
}

inline CString edge_GetProcedureID(const CString& strCmdTypeID, const CString& strCmdInfoType, const CString& strCmdParasID = _T(""))
{
	if(strCmdTypeID == EDGE_CMD_STR_TYPE_ID_device)
	{
		if(strCmdInfoType == EDGE_CMD_INFO_Type_DEV_CMD_SYS_UPGRADE)
			return EDGE_PROCEDURE_ID_DEV_CMD_SYS_UPGRADE;
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_DEV_CMD_STATUS_QUERY)	
			return EDGE_PROCEDURE_ID_DEV_CMD_STATUS_QUERY;
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_DEV_REP_JOB_RESULT)
			return EDGE_PROCEDURE_ID_DEV_REP_JOB_RESULT;		
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_DEV_REP_SYS_STATUS)
			return EDGE_PROCEDURE_ID_DEV_REP_SYS_STATUS;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_DEV_CMD_SYS_STATUS)
			return EDGE_PROCEDURE_ID_DEV_CMD_SYS_STATUS;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_DEV_CMD_INFO_QUERY)
			return EDGE_PROCEDURE_ID_DEV_CMD_INFO_QUERY;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_DEV_CMD_SYS_SET_CONFIG)
			return EDGE_PROCEDURE_ID_DEV_CMD_SYS_SET_CONFIG;		
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_DEV_CMD_DATETIME_SYN)
		{
// 			if(strCmdID == EDGE_CMD_ID_response)
// 				return EDGE_PROCEDURE_ID_DEV_CMD_DATETIME_SYN_RESP;	
// 			else
				return EDGE_PROCEDURE_ID_DEV_CMD_DATETIME_SYN;		
		}
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_DEV_EVENT_SYS_ALARM)
			return EDGE_PROCEDURE_ID_DEV_EVENT_SYS_ALARM;	
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_DEV_CMD_SYS_LOG)
			return EDGE_PROCEDURE_ID_DEV_CMD_SYS_LOG;
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_DEV_EVENT_LINKDOWN)
			return EDGE_PROCEDURE_ID_DEV_EVENT_LINKDOWN;	
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_DEV_EVENT_HEARTBEAT)
			return EDGE_PROCEDURE_ID_DEV_EVENT_HEARTBEAT;	
	}
	else if(strCmdTypeID == EDGE_CMD_STR_TYPE_ID_topo)
	{
		if(strCmdInfoType == EDGE_CMD_INFO_Type_TOPO_CMD_TOPO_ADD)
			return EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_ADD;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_TOPO_CMD_TOPO_DEL)
			return EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_DEL;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_TOPO_CMD_TOPO_UPDATE)
			return EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_UPDATE;	
	}
	else if(strCmdTypeID == EDGE_CMD_STR_TYPE_ID_container)
	{
		if(strCmdInfoType == EDGE_CMD_INFO_Type_CON_CMD_CON_INSTALL)
			return EDGE_PROCEDURE_ID_CON_CMD_CON_INSTALL;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_CON_CMD_STATUS_QUERY)
			return EDGE_PROCEDURE_ID_CON_CMD_STATUS_QUERY;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_CON_REP_JOB_RESULT)
			return EDGE_PROCEDURE_ID_CON_REP_JOB_RESULT;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_CON_CMD_CON_START)
			return EDGE_PROCEDURE_ID_CON_CMD_CON_START;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_CON_CMD_CON_STOP)
			return EDGE_PROCEDURE_ID_CON_CMD_CON_STOP;				
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_CON_CMD_CON_REMOVE)
			return EDGE_PROCEDURE_ID_CON_CMD_CON_REMOVE;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_CON_CMD_CON_SET_CONFIG)
			return EDGE_PROCEDURE_ID_CON_CMD_CON_SET_CONFIG;		
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_CON_CMD_CON_GET_CONFIG)
			return EDGE_PROCEDURE_ID_CON_CMD_CON_GET_CONFIG;		
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_CON_CMD_CON_STATUS)
			return EDGE_PROCEDURE_ID_CON_CMD_CON_STATUS;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_CON_REP_CON_STATUS)
			return EDGE_PROCEDURE_ID_CON_REP_CON_STATUS;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_CON_EVENT_CON_ALARM)
			return EDGE_PROCEDURE_ID_CON_EVENT_CON_ALARM;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_CON_CMD_CON_UPGRADE)
			return EDGE_PROCEDURE_ID_CON_CMD_CON_UPGRADE;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_CON_CMD_STATUS_QUERY)
			return EDGE_PROCEDURE_ID_CON_CMD_STATUS_QUERY;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_CON_REP_JOB_RESULT)
			return EDGE_PROCEDURE_ID_CON_REP_JOB_RESULT;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_CON_CMD_CON_LOG)
			return EDGE_PROCEDURE_ID_CON_CMD_CON_LOG;
	}
	else if(strCmdTypeID == EDGE_CMD_STR_TYPE_ID_app)
	{
		if(strCmdInfoType == EDGE_CMD_INFO_Type_APP_CMD_APP_INSTALL)
			return EDGE_PROCEDURE_ID_APP_CMD_APP_INSTALL;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_APP_CMD_STATUS_QUERY)
			return EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_APP_REP_JOB_RESULT)
			return EDGE_PROCEDURE_ID_APP_REP_JOB_RESULT;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_APP_CMD_APP_START)	
			return EDGE_PROCEDURE_ID_APP_CMD_APP_START;		
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_APP_CMD_APP_STOP)	
			return EDGE_PROCEDURE_ID_APP_CMD_APP_STOP;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_APP_CMD_APP_REMOVE)	
			return EDGE_PROCEDURE_ID_APP_CMD_APP_REMOVE;		
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_APP_CMD_APP_ENABLE)	
			return EDGE_PROCEDURE_ID_APP_CMD_APP_ENABLE;		
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_APP_CMD_APP_UNENABLE)	
			return EDGE_PROCEDURE_ID_APP_CMD_APP_UNENABLE;		
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_APP_CMD_APP_SET_CONFIG)
			return EDGE_PROCEDURE_ID_APP_CMD_APP_SET_CONFIG;		
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_APP_CMD_APP_GET_CONFIG)	
			return EDGE_PROCEDURE_ID_APP_CMD_APP_GET_CONFIG;	
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_APP_CMD_APP_STATUS)	
			return EDGE_PROCEDURE_ID_APP_CMD_APP_STATUS;		
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_APP_REP_APP_STATUS)
			return EDGE_PROCEDURE_ID_APP_REP_APP_STATUS;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_APP_EVENT_APP_ALARM)	
			return EDGE_PROCEDURE_ID_APP_EVENT_APP_ALARM;		
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_APP_CMD_APP_UPGRADE)		
			return EDGE_PROCEDURE_ID_APP_CMD_APP_UPGRADE;	
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_APP_CMD_STATUS_QUERY)		
			return EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY;	
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_APP_REP_JOB_RESULT)	
			return EDGE_PROCEDURE_ID_APP_REP_JOB_RESULT;		
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_APP_CMD_APP_LOG)	
			return EDGE_PROCEDURE_ID_APP_CMD_APP_LOG;	
	}
	else if(strCmdTypeID == EDGE_CMD_STR_TYPE_ID_service)
	{
		if(strCmdInfoType == EDGE_CMD_INFO_Type_SVR_CMD_PROFILE)	
			return EDGE_PROCEDURE_ID_SVR_CMD_PROFILE;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_SVR_REP_DATA)	
			return EDGE_PROCEDURE_ID_SVR_REP_DATA;				
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_SVR_EVENT_DATA)
			return EDGE_PROCEDURE_ID_SVR_EVENT_DATA;				
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_SVR_DATA_FILE)	
			return EDGE_PROCEDURE_ID_SVR_DATA_FILE;			
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_SVR_CMD_RPC)	
			return EDGE_PROCEDURE_ID_SVR_CMD_RPC;				
		else if(strCmdInfoType == EDGE_CMD_INFO_Type_SVR_CMD_SERVICE)
		{
			if(strCmdParasID == EDGE_PROCEDURE_CMD_ID_parameter_Get)	
				return EDGE_PROCEDURE_ID_parameter_Get;			
			else if(strCmdParasID == EDGE_PROCEDURE_CMD_ID_parameter_Set)	
				return EDGE_PROCEDURE_ID_parameter_Set;				
			else if(strCmdParasID == EDGE_PROCEDURE_CMD_ID_parameter_Activate)
				return EDGE_PROCEDURE_ID_parameter_Activate;				
			else if(strCmdParasID == EDGE_PROCEDURE_CMD_ID_parameter_Cancel)	
				return EDGE_PROCEDURE_ID_parameter_Cancel;			
			else if(strCmdParasID == EDGE_PROCEDURE_CMD_ID_discrete_Get)	
				return EDGE_PROCEDURE_ID_discrete_Get;				
			else if(strCmdParasID == EDGE_PROCEDURE_CMD_ID_analog_Get)
				return EDGE_PROCEDURE_ID_analog_Get;
			else if(strCmdParasID == EDGE_PROCEDURE_CMD_ID_accumulator_Get)
				return EDGE_PROCEDURE_ID_accumulator_Get;
			else if(strCmdParasID == EDGE_PROCEDURE_CMD_ID_APPDir_Get)
				return EDGE_PROCEDURE_ID_APPDir_Get;
			else if(strCmdParasID == EDGE_PROCEDURE_CMD_ID_APPHFile_Get)
				return EDGE_PROCEDURE_ID_APPHFile_Get;
			else if(strCmdParasID == EDGE_PROCEDURE_CMD_ID_timeRead)
				return EDGE_PROCEDURE_ID_timeRead;
			else if(strCmdParasID == EDGE_PROCEDURE_CMD_ID_timeCheck)
				return EDGE_PROCEDURE_ID_timeCheck;
			else if(strCmdParasID == EDGE_PROCEDURE_CMD_ID_commad_HZ)
				return EDGE_PROCEDURE_ID_commad_HZ;
			else if(strCmdParasID == EDGE_PROCEDURE_CMD_ID_commad_TZ)
				return EDGE_PROCEDURE_ID_commad_TZ;	
			else if(strCmdParasID == EDGE_PROCEDURE_CMD_ID_commad_ModelCtrl)
				return EDGE_PROCEDURE_ID_commad_ModelCtrl;
			else if(strCmdParasID == EDGE_PROCEDURE_CMD_ID_APP_CONFIG_Dir_Get)
				return EDGE_PROCEDURE_ID_APP_CONFIG_Dir_Get;
			else if(strCmdParasID == EDGE_PROCEDURE_CMD_ID_CMD_GET_APP_CONFIG)
				return EDGE_PROCEDURE_ID_CMD_GET_APP_CONFIG;
			else if(strCmdParasID == EDGE_PROCEDURE_CMD_ID_CMD_SET_APP_CONFIG)
				return EDGE_PROCEDURE_ID_CMD_SET_APP_CONFIG;
		}
	}
	return _T("");
}

inline CString edge_GetCmdTypeID(const CString& strProcedureID)
{
	if(strProcedureID == EDGE_PROCEDURE_ID_DEV_EVENT_LINKUP
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_UPGRADE
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_STATUS_QUERY
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_REP_JOB_RESULT
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_REP_SYS_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_INFO_QUERY
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_SET_CONFIG
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_DATETIME_SYN
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_DATETIME_SYN_RESP
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_EVENT_SYS_ALARM
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_LOG
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_EVENT_HEARTBEAT)	
	{
		return EDGE_CMD_STR_TYPE_ID_device;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_ADD	
		|| strProcedureID == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_DEL
		|| strProcedureID == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_UPDATE)
	{
		return EDGE_CMD_STR_TYPE_ID_topo;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_INSTALL
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_STATUS_QUERY
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_REP_JOB_RESULT
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_START
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_STOP
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_REMOVE
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_SET_CONFIG
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_GET_CONFIG
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_REP_CON_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_EVENT_CON_ALARM
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_UPGRADE
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_STATUS_QUERY
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_REP_JOB_RESULT
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_LOG)
	{
		return EDGE_CMD_STR_TYPE_ID_container;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_INSTALL
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_REP_JOB_RESULT
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_START	
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_STOP	
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_REMOVE
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_ENABLE
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_UNENABLE
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_SET_CONFIG	
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_GET_CONFIG	
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_REP_APP_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_EVENT_APP_ALARM
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_UPGRADE
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_REP_JOB_RESULT
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_LOG)	
	{
		return EDGE_CMD_STR_TYPE_ID_app;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_SVR_CMD_PROFILE	
		|| strProcedureID == EDGE_PROCEDURE_ID_SVR_REP_DATA
		|| strProcedureID == EDGE_PROCEDURE_ID_SVR_EVENT_DATA	
		|| strProcedureID == EDGE_PROCEDURE_ID_SVR_DATA_FILE
		|| strProcedureID == EDGE_PROCEDURE_ID_SVR_CMD_RPC
		|| strProcedureID == EDGE_PROCEDURE_ID_parameter_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_parameter_Set
		|| strProcedureID == EDGE_PROCEDURE_ID_parameter_Activate
		|| strProcedureID == EDGE_PROCEDURE_ID_parameter_Cancel	
		|| strProcedureID == EDGE_PROCEDURE_ID_discrete_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_analog_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_accumulator_Get	
		|| strProcedureID == EDGE_PROCEDURE_ID_APPDir_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_APPHFile_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_timeRead	
		|| strProcedureID == EDGE_PROCEDURE_ID_timeCheck	
		|| strProcedureID == EDGE_PROCEDURE_ID_commad_HZ	
		|| strProcedureID == EDGE_PROCEDURE_ID_commad_TZ	
		|| strProcedureID == EDGE_PROCEDURE_ID_commad_ModelCtrl	
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CONFIG_Dir_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_CMD_GET_APP_CONFIG
		|| strProcedureID == EDGE_PROCEDURE_ID_CMD_SET_APP_CONFIG)
	{
		return EDGE_CMD_STR_TYPE_ID_service;
	}

	return _T("");
}

inline CString edge_GetCmdInfoType(const CString& strProcedureID)
{
	if(strProcedureID == EDGE_PROCEDURE_ID_DEV_EVENT_LINKUP)
	{
		return EDGE_CMD_INFO_Type_DEV_EVENT_LINKUP;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_DEV_EVENT_LINKDOWN)
	{
		return EDGE_CMD_INFO_Type_DEV_EVENT_LINKDOWN;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_DEV_EVENT_HEARTBEAT)
	{
		return EDGE_CMD_INFO_Type_DEV_EVENT_HEARTBEAT;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_UPGRADE)
	{
		return EDGE_CMD_INFO_Type_DEV_CMD_SYS_UPGRADE;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_STATUS_QUERY)
	{
		return EDGE_CMD_INFO_Type_DEV_CMD_STATUS_QUERY;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_DEV_REP_JOB_RESULT)
	{
		return EDGE_CMD_INFO_Type_DEV_REP_JOB_RESULT;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_DEV_REP_SYS_STATUS)
	{
		return EDGE_CMD_INFO_Type_DEV_REP_SYS_STATUS;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_STATUS)
	{
		return EDGE_CMD_INFO_Type_DEV_CMD_SYS_STATUS;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_INFO_QUERY)
	{
		return EDGE_CMD_INFO_Type_DEV_CMD_INFO_QUERY;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_SET_CONFIG)
	{
		return EDGE_CMD_INFO_Type_DEV_CMD_SYS_SET_CONFIG;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_DATETIME_SYN
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_DATETIME_SYN_RESP)
	{
		return EDGE_CMD_INFO_Type_DEV_CMD_DATETIME_SYN;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_DEV_EVENT_SYS_ALARM)
	{
		return EDGE_CMD_INFO_Type_DEV_EVENT_SYS_ALARM;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_LOG)	
	{
		return EDGE_CMD_INFO_Type_DEV_CMD_SYS_LOG;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_ADD)	
	{
		return EDGE_CMD_INFO_Type_TOPO_CMD_TOPO_ADD;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_DEL)	
	{
		return EDGE_CMD_INFO_Type_TOPO_CMD_TOPO_DEL;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_UPDATE)
	{
		return EDGE_CMD_INFO_Type_TOPO_CMD_TOPO_UPDATE;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_INSTALL)
	{
		return EDGE_CMD_INFO_Type_CON_CMD_CON_INSTALL;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_STATUS_QUERY)
	{
		return EDGE_CMD_INFO_Type_CON_CMD_STATUS_QUERY;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_CON_REP_JOB_RESULT)
	{
		return EDGE_CMD_INFO_Type_CON_REP_JOB_RESULT;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_START)	
	{
		return EDGE_CMD_INFO_Type_CON_CMD_CON_START;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_STOP)
	{
		return EDGE_CMD_INFO_Type_CON_CMD_CON_STOP;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_REMOVE)
	{
		return EDGE_CMD_INFO_Type_CON_CMD_CON_REMOVE;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_SET_CONFIG)	
	{
		return EDGE_CMD_INFO_Type_CON_CMD_CON_SET_CONFIG;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_GET_CONFIG)	
	{
		return EDGE_CMD_INFO_Type_CON_CMD_CON_GET_CONFIG;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_STATUS)
	{
		return EDGE_CMD_INFO_Type_CON_CMD_CON_STATUS;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_CON_REP_CON_STATUS)
	{
		return EDGE_CMD_INFO_Type_CON_REP_CON_STATUS;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_CON_EVENT_CON_ALARM)
	{
		return EDGE_CMD_INFO_Type_CON_EVENT_CON_ALARM;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_UPGRADE)
	{
		return EDGE_CMD_INFO_Type_CON_CMD_CON_UPGRADE;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_STATUS_QUERY)
	{
		return EDGE_CMD_INFO_Type_CON_CMD_STATUS_QUERY;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_CON_REP_JOB_RESULT)
	{
		return EDGE_CMD_INFO_Type_CON_REP_JOB_RESULT;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_LOG)	
	{
		return EDGE_CMD_INFO_Type_CON_CMD_CON_LOG;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_INSTALL)
	{
		return EDGE_CMD_INFO_Type_APP_CMD_APP_INSTALL;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY)
	{
		return EDGE_CMD_INFO_Type_APP_CMD_STATUS_QUERY;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_REP_JOB_RESULT)
	{
		return EDGE_CMD_INFO_Type_APP_REP_JOB_RESULT;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_START)	
	{
		return EDGE_CMD_INFO_Type_APP_CMD_APP_START;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_STOP)	
	{
		return EDGE_CMD_INFO_Type_APP_CMD_APP_STOP;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_REMOVE)
	{
		return EDGE_CMD_INFO_Type_APP_CMD_APP_REMOVE;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_ENABLE)
	{
		return EDGE_CMD_INFO_Type_APP_CMD_APP_ENABLE;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_UNENABLE)
	{
		return EDGE_CMD_INFO_Type_APP_CMD_APP_UNENABLE;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_SET_CONFIG)	
	{
		return EDGE_CMD_INFO_Type_APP_CMD_APP_SET_CONFIG;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_GET_CONFIG)	
	{
		return EDGE_CMD_INFO_Type_APP_CMD_APP_GET_CONFIG;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_STATUS)
	{
		return EDGE_CMD_INFO_Type_APP_CMD_APP_STATUS;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_REP_APP_STATUS)
	{
		return EDGE_CMD_INFO_Type_APP_REP_APP_STATUS;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_EVENT_APP_ALARM)
	{
		return EDGE_CMD_INFO_Type_APP_EVENT_APP_ALARM;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_UPGRADE)
	{
		return EDGE_CMD_INFO_Type_APP_CMD_APP_UPGRADE;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY)
	{
		return EDGE_CMD_INFO_Type_APP_CMD_STATUS_QUERY;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_REP_JOB_RESULT)
	{
		return EDGE_CMD_INFO_Type_APP_REP_JOB_RESULT;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_LOG)	
	{
		return EDGE_CMD_INFO_Type_APP_CMD_APP_LOG;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_SVR_CMD_PROFILE)	
	{
		return EDGE_CMD_INFO_Type_SVR_CMD_PROFILE;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_SVR_REP_DATA)
	{
		return EDGE_CMD_INFO_Type_SVR_REP_DATA;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_SVR_EVENT_DATA)	
	{
		return EDGE_CMD_INFO_Type_SVR_EVENT_DATA;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_SVR_DATA_FILE)
	{
		return EDGE_CMD_INFO_Type_SVR_DATA_FILE;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_SVR_CMD_RPC)
	{
		return EDGE_CMD_INFO_Type_SVR_CMD_RPC;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_parameter_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_parameter_Set
		|| strProcedureID == EDGE_PROCEDURE_ID_parameter_Activate
		|| strProcedureID == EDGE_PROCEDURE_ID_parameter_Cancel	
		|| strProcedureID == EDGE_PROCEDURE_ID_discrete_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_analog_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_accumulator_Get	
		|| strProcedureID == EDGE_PROCEDURE_ID_APPDir_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_APPHFile_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_timeRead
		|| strProcedureID == EDGE_PROCEDURE_ID_timeCheck	
		|| strProcedureID == EDGE_PROCEDURE_ID_commad_HZ	
		|| strProcedureID == EDGE_PROCEDURE_ID_commad_TZ	
		|| strProcedureID == EDGE_PROCEDURE_ID_commad_ModelCtrl	
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CONFIG_Dir_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_CMD_GET_APP_CONFIG
		|| strProcedureID == EDGE_PROCEDURE_ID_CMD_SET_APP_CONFIG)
	{
		return EDGE_CMD_INFO_Type_SVR_CMD_SERVICE;
	}

	return _T("");
}

//下发报文的topic类型 /v1/{edgeID}/{device...app}/xxx
inline CString edge_GetServerToEdgeCmdID(const CString& strProcedureID)
{
	if(strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_UPGRADE
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_STATUS_QUERY
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_INFO_QUERY
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_SET_CONFIG
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_DATETIME_SYN
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_LOG
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_INSTALL
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_STATUS_QUERY
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_START
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_STOP	
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_REMOVE
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_SET_CONFIG	
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_GET_CONFIG	
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_REP_CON_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_UPGRADE
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_LOG
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_INSTALL
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_START	
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_STOP	
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_REMOVE
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_ENABLE
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_UNENABLE
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_SET_CONFIG	
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_GET_CONFIG	
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_UPGRADE
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_LOG
		|| strProcedureID == EDGE_PROCEDURE_ID_SVR_CMD_PROFILE
		|| strProcedureID == EDGE_PROCEDURE_ID_parameter_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_parameter_Set
		|| strProcedureID == EDGE_PROCEDURE_ID_parameter_Activate
		|| strProcedureID == EDGE_PROCEDURE_ID_parameter_Cancel	
		|| strProcedureID == EDGE_PROCEDURE_ID_discrete_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_analog_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_accumulator_Get	
		|| strProcedureID == EDGE_PROCEDURE_ID_APPDir_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_APPHFile_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_timeRead	
		|| strProcedureID == EDGE_PROCEDURE_ID_timeCheck	
		|| strProcedureID == EDGE_PROCEDURE_ID_commad_HZ	
		|| strProcedureID == EDGE_PROCEDURE_ID_commad_TZ	
		|| strProcedureID == EDGE_PROCEDURE_ID_commad_ModelCtrl	
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CONFIG_Dir_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_CMD_GET_APP_CONFIG
		|| strProcedureID == EDGE_PROCEDURE_ID_CMD_SET_APP_CONFIG)
	{
		return EDGE_CMD_ID_command;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_DEV_EVENT_LINKUP
		|| strProcedureID == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_ADD
		|| strProcedureID == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_DEL
		|| strProcedureID == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_UPDATE
		|| strProcedureID == EDGE_PROCEDURE_ID_SVR_CMD_RPC
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_EVENT_HEARTBEAT)
	{
		return EDGE_CMD_ID_response;
	}

	return _T("");
}

//回复报文的topic类型 /v1/{edgeID}/{device...app}/xxx 
inline CString edge_GetEdgeToServerCmdID(const CString& strProcedureID)
{
	if(strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_UPGRADE
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_STATUS_QUERY
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_INFO_QUERY
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_SET_CONFIG
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_DATETIME_SYN
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_LOG
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_INSTALL
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_STATUS_QUERY
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_START
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_STOP	
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_REMOVE
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_SET_CONFIG	
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_GET_CONFIG	
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_REP_CON_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_UPGRADE
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_STATUS_QUERY
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_LOG
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_INSTALL
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_START	
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_STOP	
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_REMOVE
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_ENABLE
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_UNENABLE
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_SET_CONFIG	
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_GET_CONFIG	
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_UPGRADE
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_LOG
		|| strProcedureID == EDGE_PROCEDURE_ID_SVR_CMD_PROFILE
		|| strProcedureID == EDGE_PROCEDURE_ID_parameter_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_parameter_Set
		|| strProcedureID == EDGE_PROCEDURE_ID_parameter_Activate
		|| strProcedureID == EDGE_PROCEDURE_ID_parameter_Cancel	
		|| strProcedureID == EDGE_PROCEDURE_ID_discrete_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_analog_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_accumulator_Get	
		|| strProcedureID == EDGE_PROCEDURE_ID_APPDir_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_APPHFile_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_timeRead	
		|| strProcedureID == EDGE_PROCEDURE_ID_timeCheck	
		|| strProcedureID == EDGE_PROCEDURE_ID_commad_HZ	
		|| strProcedureID == EDGE_PROCEDURE_ID_commad_TZ	
		|| strProcedureID == EDGE_PROCEDURE_ID_commad_ModelCtrl	
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_CONFIG_Dir_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_CMD_GET_APP_CONFIG
		|| strProcedureID == EDGE_PROCEDURE_ID_CMD_SET_APP_CONFIG)
	{
		return EDGE_CMD_ID_reply;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_DEV_REP_JOB_RESULT
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_REP_SYS_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_EVENT_SYS_ALARM
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_REP_JOB_RESULT
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_REP_CON_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_EVENT_CON_ALARM
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_REP_JOB_RESULT
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_REP_JOB_RESULT
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_REP_APP_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_EVENT_APP_ALARM
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_REP_JOB_RESULT
		|| strProcedureID == EDGE_PROCEDURE_ID_SVR_REP_DATA)
	{
		return EDGE_CMD_ID_data;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_ADD
		|| strProcedureID == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_DEL
		|| strProcedureID == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_UPDATE
		|| strProcedureID == EDGE_PROCEDURE_ID_SVR_CMD_RPC
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_DATETIME_SYN_RESP)
	{
		return EDGE_CMD_ID_response;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_SVR_EVENT_DATA)
	{
		return EDGE_CMD_ID_event;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_SVR_DATA_FILE)
	{
		return EDGE_CMD_ID_file;
	}
	
	return _T("");
}

//通过过程ID获取对应的数据集ID
inline CString GetDatasetId(const CString& strProcedureID)
{
	CString strDatasetId;
	if(strProcedureID == EDGE_PROCEDURE_ID_parameter_Get
		|| strProcedureID == EDGE_PROCEDURE_ID_parameter_Set
		|| strProcedureID == EDGE_PROCEDURE_ID_parameter_Activate
		|| strProcedureID == EDGE_PROCEDURE_ID_parameter_Cancel)
	{
		strDatasetId = EDGE_DATASET_ID_Parameter;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_discrete_Get)
	{
		strDatasetId = EDGE_DATASET_ID_Din;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_analog_Get)
	{
		strDatasetId = EDGE_DATASET_ID_Ain;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_accumulator_Get)
	{
		strDatasetId = EDGE_DATASET_ID_AccumulateData;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_timeRead
		|| strProcedureID == EDGE_PROCEDURE_ID_timeCheck)
	{
		strDatasetId = EDGE_DATASET_ID_TimeCheck;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_commad_HZ
		|| strProcedureID == EDGE_PROCEDURE_ID_commad_TZ)
	{
		strDatasetId = EDGE_DATASET_ID_RemCtl;
	}	
	else if(strProcedureID == EDGE_PROCEDURE_ID_commad_ModelCtrl)
	{
		strDatasetId = EDGE_DATASET_ID_4GModify;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_APPDir_Get)
	{
		strDatasetId = EDGE_DATASET_ID_APPDirGet;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_APPHFile_Get)
	{
		strDatasetId = EDGE_DATASET_ID_APPHFileGet;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_APP_CONFIG_Dir_Get)
	{
		strDatasetId = EDGE_DATASET_ID_APPCONFIGDirGet;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_SVR_CMD_PROFILE)
	{
		strDatasetId = EDGE_DATASET_ID_SRV_Profile;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_SVR_DATA_FILE)
	{
		strDatasetId = EDGE_DATASET_ID_SRV_DataFile;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_SVR_EVENT_DATA
		|| strProcedureID == EDGE_PROCEDURE_ID_SVR_REP_DATA)
	{
		strDatasetId = EDGE_DATASET_ID_SRV_Event;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_CMD_GET_APP_CONFIG
		|| strProcedureID == EDGE_PROCEDURE_ID_CMD_SET_APP_CONFIG)
	{
		strDatasetId = EDGE_DATASET_ID_APPCONFIG;
	}
	//以下是设备
	else if (strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_UPGRADE
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_STATUS_QUERY)
	{
		strDatasetId = EDGE_DATASET_ID_DEV_UpGrade;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_DEV_REP_JOB_RESULT)
	{
		strDatasetId = EDGE_DATASET_ID_DEV_ChangeInfo;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_REP_SYS_STATUS)
	{
		strDatasetId = EDGE_DATASET_ID_DEV_SysStatus;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_INFO_QUERY)
	{
		strDatasetId = EDGE_DATASET_ID_DEV_Info;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_SET_CONFIG)
	{
		strDatasetId = EDGE_DATASET_ID_DEV_SysPara;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_DATETIME_SYN)
	{
		strDatasetId = EDGE_DATASET_ID_DEV_SYN;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_DEV_EVENT_HEARTBEAT)
	{
		strDatasetId = EDGE_DATASET_ID_DEV_DeviceHeart;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_DEV_EVENT_SYS_ALARM)
	{
		strDatasetId = EDGE_DATASET_ID_DEV_Event;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_LOG)
	{
		strDatasetId = EDGE_DATASET_ID_DEV_Log;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_ADD
		|| strProcedureID == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_DEL
		|| strProcedureID == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_UPDATE)
	{
		strDatasetId = EDGE_DATASET_ID_TOPO_Admin;
	}
	//以下是容器
	else if (strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_STATUS_QUERY)
	{
		strDatasetId = EDGE_DATASET_ID_CON_Install;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_GET_CONFIG)
	{
		strDatasetId = EDGE_DATASET_ID_CON_Cfg;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_CON_REP_CON_STATUS)
	{
		strDatasetId = EDGE_DATASET_ID_CON_State;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_CON_EVENT_CON_ALARM)
	{
		strDatasetId = EDGE_DATASET_ID_CON_Event;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_STATUS_QUERY)
	{
		strDatasetId = EDGE_DATASET_ID_CON_Upgrade;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_CON_REP_JOB_RESULT)
	{
		strDatasetId = EDGE_DATASET_ID_CON_ChangeInfo;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_CON_LOG)
	{
		strDatasetId = EDGE_DATASET_ID_CON_Log;
	}
	//以下是应用
	else if (strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY)
	{
		strDatasetId = EDGE_DATASET_ID_APP_Install;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_GET_CONFIG)
	{
		strDatasetId = EDGE_DATASET_ID_APP_Read;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_STATUS
		|| strProcedureID == EDGE_PROCEDURE_ID_APP_REP_APP_STATUS)
	{
		strDatasetId = EDGE_DATASET_ID_APP_State;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_APP_EVENT_APP_ALARM)
	{
		strDatasetId = EDGE_DATASET_ID_APP_Event;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY)
	{
		strDatasetId = EDGE_DATASET_ID_APP_Upgrade;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_REP_JOB_RESULT)
	{
		strDatasetId = EDGE_DATASET_ID_APP_ChangeInfo;
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_APP_LOG)
	{
		strDatasetId = EDGE_DATASET_ID_APP_Log;
	}


	return strDatasetId;
}

//获取过程ID对应的LDevice
inline CString GetLDeviceId(const CString& strProcedureID)
{
	CString strLDeviceId;

	if(edge_GetCmdTypeID(strProcedureID) == EDGE_CMD_STR_TYPE_ID_device
		|| edge_GetCmdTypeID(strProcedureID) == EDGE_CMD_STR_TYPE_ID_topo)
	{
		strLDeviceId = EDGE_LDEV_ID_DeviceData;
	}
	else if (edge_GetCmdTypeID(strProcedureID) == EDGE_CMD_STR_TYPE_ID_service)
	{
		strLDeviceId = EDGE_LDEV_ID_ServiceData;
	}
	else if (edge_GetCmdTypeID(strProcedureID) == EDGE_CMD_STR_TYPE_ID_container)
	{
		strLDeviceId = EDGE_LDEV_ID_ContainerData;
	}

	else if (edge_GetCmdTypeID(strProcedureID) == EDGE_CMD_STR_TYPE_ID_app)
	{
		strLDeviceId = EDGE_LDEV_ID_AppData;
	}

	return strLDeviceId;
}

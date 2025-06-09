#include "stdafx.h"
#include "EdgeCmdErrorMngr.h"
#include "EdgeGlobalDef.h"

void CEdgeCmdErrorMngr::AddErrorInfo(const BSTR strCodeKey, CXmlRWNodeBase &oNode, long nValType)
{
	CString strErrReason;

	long nJsonType = xml_GetAttibuteType(strCodeKey, oNode);
	//double类型包含long值,所以如果是long值但要求是double类型,则转换long值的类型
	if(nJsonType == CJSON_Int && nValType == CJSON_Double)
	{
		nJsonType = CJSON_Double;
	}

	switch(nValType)
	{
	case CJSON_Int: strErrReason = EDGE_ERR_TYPE_LONG; break;
	case CJSON_Double: strErrReason = EDGE_ERR_TYPE_DOUBLE; break;
	case CJSON_String: strErrReason = EDGE_ERR_TYPE_STRING; break;
	case CJSON_Array: strErrReason = EDGE_ERR_TYPE_ARRAY; break;
	default:
		break;
	}

 	CString strErrInfo;
	//节点存在且不为设置的检测类型值
	if(nJsonType != -1 && nJsonType != nValType)
	{
		strErrInfo.Format(_T("[%s]错误,%s"), CString(strCodeKey), strErrReason);
		AddCmdErrorInfo(strErrInfo);
	}
}

void CEdgeCmdErrorMngr::AddErrorInfo(const BSTR strCodeKey, CXmlRWNodeBase &oNode, long nValType, CString& strErrorInfo)
{
	CString strErrReason;

	long nJsonType = xml_GetAttibuteType(strCodeKey, oNode);
	//double类型包含long值,所以如果是long值但要求是double类型,则转换long值的类型
	if(nJsonType == CJSON_Int && nValType == CJSON_Double)
	{
		nJsonType = CJSON_Double;
	}

	switch(nValType)
	{
	case CJSON_Int: strErrReason = EDGE_ERR_TYPE_LONG; break;
	case CJSON_Double: strErrReason = EDGE_ERR_TYPE_DOUBLE; break;
	case CJSON_String: strErrReason = EDGE_ERR_TYPE_STRING; break;
	case CJSON_Array: strErrReason = EDGE_ERR_TYPE_ARRAY; break;
	default:
		break;
	}

	CString strErrInfo;
	//节点存在且不为设置的检测类型值
	if(nJsonType != -1 && nJsonType != nValType)
	{
		strErrInfo.Format(_T("[%s]错误,%s"), CString(strCodeKey), strErrReason);
		strErrorInfo += strErrInfo;
	}
}

void CEdgeCmdErrorMngr::AddErrorInfo(CJSON* pJson, long nValType)
{
	CString strErrReason;

	long nJsonType = pJson->type;
	if(nJsonType == CJSON_Number)
	{
		nJsonType = pJson->numType;
	}

	//double类型包含long值,所以如果是long值但要求是double类型,则转换long值的类型
	if(nJsonType == CJSON_Int && nValType == CJSON_Double)
	{
		nJsonType = CJSON_Double;
	}

	switch(nValType)
	{
	case CJSON_Int: strErrReason = EDGE_ERR_TYPE_LONG; break;
	case CJSON_Double: strErrReason = EDGE_ERR_TYPE_DOUBLE; break;
	case CJSON_String: strErrReason = EDGE_ERR_TYPE_STRING; break;
	case CJSON_Array: strErrReason = EDGE_ERR_TYPE_ARRAY; break;
	default:
		break;
	}

	CString strErrInfo;
	//节点存在且不为设置的检测类型值
	if(pJson && nJsonType != nValType)
	{
		strErrInfo.Format(_T("[%s]错误,%s"), pJson->string, strErrReason);
		AddCmdErrorInfo(strErrInfo);
	}
}

void CEdgeCmdErrorMngr::AddErrorInfo(CJSON* pJson, long nValType, CString& strErrorInfo)
{
	CString strErrReason;

	long nJsonType = pJson->type;
	if(nJsonType == CJSON_Number)
	{
		nJsonType = pJson->numType;
	}

	//double类型包含long值,所以如果是long值但要求是double类型,则转换long值的类型
	if(nJsonType == CJSON_Int && nValType == CJSON_Double)
	{
		nJsonType = CJSON_Double;
	}

	switch(nValType)
	{
	case CJSON_Int: strErrReason = EDGE_ERR_TYPE_LONG; break;
	case CJSON_Double: strErrReason = EDGE_ERR_TYPE_DOUBLE; break;
	case CJSON_String: strErrReason = EDGE_ERR_TYPE_STRING; break;
	case CJSON_Array: strErrReason = EDGE_ERR_TYPE_ARRAY; break;
	default:
		break;
	}

	CString strErrInfo;
	//节点存在且不为设置的检测类型值
	if(pJson && nJsonType != nValType)
	{
		strErrInfo.Format(_T("[%s]错误,%s"), pJson->string, strErrReason);
		strErrorInfo += strErrInfo;
	}
}

void CEdgeCmdErrorMngr::CheckIsError(CJSON* pJson, CString& strErrorInfo)
{
	if(!pJson)
	{
		return;
	}

	CString strID = pJson->string;
	if(strID == EDGE_PROCEDURE_VAR_jobId
		|| strID == EDGE_PROCEDURE_VAR_state
		|| strID == EDGE_PROCEDURE_VAR_progress
		|| strID == EDGE_PROCEDURE_VAR_code
		|| strID == EDGE_PROCEDURE_VAR_diskUsed
		|| strID == EDGE_PROCEDURE_VAR_tempValue
		|| strID == EDGE_PROCEDURE_VAR_devRunTime)
	{
		AddErrorInfo(pJson, CJSON_Int, strErrorInfo);
	}
	else if(strID == EDGE_PROCEDURE_VAR_cpuRate)
	{
		AddErrorInfo(pJson, CJSON_Double, strErrorInfo);
	}
	else if (strID == EDGE_PROCEDURE_VAR_msg
		|| strID == EDGE_PROCEDURE_VAR_devDateTime
		|| strID == EDGE_PROCEDURE_VAR_devStDateTime
		|| strID == EDGE_PROCEDURE_VAR_longitude
		|| strID == EDGE_PROCEDURE_VAR_latitude
		|| strID == EDGE_PROCEDURE_VAR_name
		|| strID == EDGE_PROCEDURE_VAR_status
		|| strID == EDGE_PROCEDURE_VAR_dateTime
		|| strID == EDGE_PROCEDURE_VAR_timeZone
		|| strID == EDGE_PROCEDURE_VAR_event
		|| strID == EDGE_PROCEDURE_VAR_container
		|| strID == EDGE_PROCEDURE_VAR_app)
	{
		AddErrorInfo(pJson, CJSON_String, strErrorInfo);
	}
}

void CEdgeCmdErrorMngr::CheckIsError(CJSON* pJson)
{
	if(!pJson)
	{
		return;
	}

	CString strID = pJson->string;
	if(strID == EDGE_PROCEDURE_VAR_jobId
		|| strID == EDGE_PROCEDURE_VAR_state
		|| strID == EDGE_PROCEDURE_VAR_progress
		|| strID == EDGE_PROCEDURE_VAR_code
		|| strID == EDGE_PROCEDURE_VAR_devRunTime
		|| strID == EDGE_PROCEDURE_VAR_policy)
	{
		AddErrorInfo(pJson, CJSON_Int);
	}
	else if(strID == EDGE_PROCEDURE_VAR_cpuRate
		|| strID == EDGE_PROCEDURE_VAR_diskUsed
		|| strID == EDGE_PROCEDURE_VAR_tempValue)
	{
		AddErrorInfo(pJson, CJSON_Double);
	}
	else if (strID == EDGE_PROCEDURE_VAR_msg
		|| strID == EDGE_PROCEDURE_VAR_devDateTime
		|| strID == EDGE_PROCEDURE_VAR_devStDateTime
		|| strID == EDGE_PROCEDURE_VAR_longitude
		|| strID == EDGE_PROCEDURE_VAR_latitude
		|| strID == EDGE_PROCEDURE_VAR_name
		|| strID == EDGE_PROCEDURE_VAR_status
		|| strID == EDGE_PROCEDURE_VAR_dateTime
		|| strID == EDGE_PROCEDURE_VAR_timeZone
		|| strID == EDGE_PROCEDURE_VAR_event
		|| strID == EDGE_PROCEDURE_VAR_container
		|| strID == EDGE_PROCEDURE_VAR_app
		|| strID == EDGE_PROCEDURE_VAR_port
		|| strID == EDGE_PROCEDURE_VAR_enable
		|| strID == EDGE_PROCEDURE_VAR_image
		|| strID == EDGE_PROCEDURE_VAR_version
		|| strID == EDGE_PROCEDURE_VAR_url
		|| strID == EDGE_PROCEDURE_VAR_app)
	{
		AddErrorInfo(pJson, CJSON_String);
	}
// 	else if (strID == EDGE_PROCEDURE_VAR_memUsed)
// 	{
// 		AddErrorInfo(pJson, CJSON_Object);
// 	}
// 	else if (strID == EDGE_PROCEDURE_VAR_links
// 		|| strID == EDGE_PROCEDURE_VAR_linkState)
// 	{
// 		AddErrorInfo(pJson, CJSON_Array);
// 	}
}
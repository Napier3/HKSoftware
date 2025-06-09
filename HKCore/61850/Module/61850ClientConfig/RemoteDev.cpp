//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RemoteDev.cpp  CRemoteDev


#include "stdafx.h"
#include "RemoteDev.h"
#include "../../../Module/API/StringApi.h"

#ifdef USE_61850CLient_STRCUT
#include "gsp_lib_memory.h"
#include "conversions.h"
#include "../dlt860/ClientCallBack.h"
//#include "../61850ClientAPI/61850ClientGlobal.h"
#include "../MmsApi.h"
#include "../61850ClientConfig/61850ClientConfig.h"

#include "../MmsWriteXml.h"
#include "../../../Module/GpsPcTime/GpsPcTime.h"
#include "../MmsGlobal.h"
#include "../dlt860/DLT860Engine.h"
#endif

#include "../../../Module/API/FileApi.h"
#include "../../../Module/API/StringConvert/String_Utf8_To_Gbk.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRemoteDev::CRemoteDev()
{
	//初始化属性
	m_nUseLocalIP = 0;

#ifdef USE_61850CLient_STRCUT
	//初始化成员变量
	m_oConnectIED = NULL;
	m_oErrorInfor = GSP_IED_ERROR_OK;
	memset(&m_oAcsiDevice,0,sizeof(ACSI_NODE));
	m_oAcsiDevice.nSGNum = 0;
	m_oCurBrcbControlBlk = NULL;
	m_oCurUrcbControlBlk = NULL;
	m_pAssociateID = NULL;
#endif
}

CRemoteDev::~CRemoteDev()
{
#ifdef USE_61850CLient_STRCUT
    long nMaxNum = m_vBrcbContrlBlk.GetCount();
	long nIndex = 0;

	for (nIndex = 0;nIndex<nMaxNum;nIndex++)
	{
		Gsp_BRCBControlBlk_Destory(m_vBrcbContrlBlk[nIndex]);
	}

    nMaxNum = m_vUrcbContrlBlk.GetCount();

	for (nIndex = 0;nIndex<nMaxNum;nIndex++)
	{
		Gsp_URCBControlBlk_Destory(m_vUrcbContrlBlk[nIndex]);
	}

    m_vBrcbContrlBlk.RemoveAll();
    m_vUrcbContrlBlk.RemoveAll();

	if (m_oCurBrcbControlBlk != NULL)
	{
		Gsp_BRCBControlBlk_Destory(m_oCurBrcbControlBlk);
		m_oCurBrcbControlBlk = NULL;
	}

	if (m_oCurUrcbControlBlk != NULL)
	{
		Gsp_URCBControlBlk_Destory(m_oCurUrcbControlBlk);
		m_oCurUrcbControlBlk = NULL;
	}

	if (m_oConnectIED != NULL)
	{
		Gsp_IedConnection_ReleaseAllReportCallBack(m_oConnectIED);
		Gsp_IedConnection_Destroy(m_oConnectIED);
		Gsp_IedConnection_FreeAssociateID(m_pAssociateID);
		m_oConnectIED = NULL;
	}

	Release_AcsiNode();
#endif
}

long CRemoteDev::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	C61850ClientCfgMngrXmlRWKeys *pXmlKeys = (C61850ClientCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIpKey, oNode, m_strIP);
	xml_GetAttibuteValue(pXmlKeys->m_strLocal_IpKey, oNode, m_strLocalIP);
	xml_GetAttibuteValue(pXmlKeys->m_strUse_Local_IpKey, oNode, m_nUseLocalIP);
	return 0;
}

long CRemoteDev::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	C61850ClientCfgMngrXmlRWKeys *pXmlKeys = (C61850ClientCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIpKey, oElement, m_strIP);
	xml_SetAttributeValue(pXmlKeys->m_strLocal_IpKey, oElement, m_strLocalIP);
	xml_SetAttributeValue(pXmlKeys->m_strUse_Local_IpKey, oElement, m_nUseLocalIP);
	return 0;
}

long CRemoteDev::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strIP);
		BinarySerializeCalLen(oBinaryBuffer, m_strLocalIP);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseLocalIP);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strIP);
		BinarySerializeRead(oBinaryBuffer, m_strLocalIP);
		BinarySerializeRead(oBinaryBuffer, m_nUseLocalIP);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strIP);
		BinarySerializeWrite(oBinaryBuffer, m_strLocalIP);
		BinarySerializeWrite(oBinaryBuffer, m_nUseLocalIP);
	}
	return 0;
}

void CRemoteDev::InitAfterRead()
{
}

BOOL CRemoteDev::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CRemoteDev *p = (CRemoteDev*)pObj;

	if(m_strIP != p->m_strIP)
	{
		return FALSE;
	}

	if(m_strLocalIP != p->m_strLocalIP)
	{
		return FALSE;
	}

	if(m_nUseLocalIP != p->m_nUseLocalIP)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRemoteDev::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CRemoteDev *p = (CRemoteDev*)pDest;

	p->m_strIP = m_strIP;
	p->m_strLocalIP = m_strLocalIP;
	p->m_nUseLocalIP = m_nUseLocalIP;
	return TRUE;
}

CBaseObject* CRemoteDev::Clone()
{
	CRemoteDev *p = new CRemoteDev();
	Copy(p);
	return p;
}

CBaseObject* CRemoteDev::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRemoteDev *p = new CRemoteDev();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

#ifdef USE_61850CLient_STRCUT

BOOL CRemoteDev::IsConnecting()
{
	if (m_oConnectIED == NULL)
	{
		return FALSE;
	}

	return m_oAcsiDevice.bConnect;
}

LD_NODE* CRemoteDev::GetLdNode(const long &nLdIndex)
{
	if ((m_oAcsiDevice.numLD<=nLdIndex)||(nLdIndex<0))
	{
		return NULL;
	}

	return &m_oAcsiDevice.LD[nLdIndex];
}

BOOL CRemoteDev::LinkDev()
{
	if (IsConnecting())
	{
		UnLinkDev();
	}

	if (m_oConnectIED == NULL)
	{
		m_oConnectIED = Gsp_IedConnection_Create();
//		Gsp_IedConnection_SetRequestTimeout(m_oConnectIED,20000);
	}

	// 链接到服务器
	if ((m_nUseLocalIP)&&(!m_strLocalIP.IsEmpty()))
	{
        Gsp_IedConnection_Connect(m_oConnectIED, &m_oErrorInfor, m_strIP.GetString(), DLT860_SERVER_PORT,m_strLocalIP.GetString());
	} 
	else
	{
        Gsp_IedConnection_Connect(m_oConnectIED, &m_oErrorInfor, m_strIP.GetString(), DLT860_SERVER_PORT);
	}

	if (m_oErrorInfor == GSP_IED_ERROR_OK)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,("链接到服务端成功."));
	} 
	else 
	{
#ifdef _PSX_QT_LINUX_
        CLogPrint::LogString(XLOGLEVEL_ERROR,_T("链接到服务端失败"));
#else
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("链接到服务端失败(%d)."),(int)m_oConnectIED);
#endif

		// 销毁链接
		Gsp_IedConnection_Destroy(m_oConnectIED);
		m_oConnectIED = NULL;
		return FALSE;
	}

	// 发生关联

	m_pAssociateID = Gsp_IedConnection_Associate(m_oConnectIED, &m_oErrorInfor, "S1");
	return TRUE;
}

BOOL CRemoteDev::UnLinkDev()
{
	if (m_oConnectIED == NULL)
	{
		return TRUE;
	}

 	Gsp_IedConnection_ReleaseAllReportCallBack(m_oConnectIED);
 	// 释放链接
 	Gsp_IedConnection_Release(m_oConnectIED, &m_oErrorInfor, m_pAssociateID);

	// 中止链接
	Gsp_IedConnection_Abort(m_oConnectIED, &m_oErrorInfor, GSP_IED_ABORT_OTHER, m_pAssociateID);

	Gsp_IedConnection_Destroy(m_oConnectIED);
	Gsp_IedConnection_FreeAssociateID(m_pAssociateID);
	m_oConnectIED = NULL;

	if (m_oErrorInfor != GSP_IED_ERROR_OK)
	{
#ifdef _PSX_QT_LINUX_
        CLogPrint::LogString(XLOGLEVEL_ERROR,_T("断开链接失败"));
#else
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("断开链接失败(%d)."),(int)m_oConnectIED);
#endif
	}

	return TRUE;
}


void CRemoteDev::LogPrint_GspLinkedList(GspLinkedList list)
{
	GspLinkedList element = list;

	int elementCount = 0;

	deque<void *> d = *list;
	long nLenth = 0;

	for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++)
	{
		char* item = (char*)(*it);
		nLenth = strlen(item);
		CLogPrint::LogString(XLOGLEVEL_INFOR,item);
//		printf("%s\n", item);
	}
}

void SetCharValue(char *pzfLd)
{
	int nTmp;

	for (int nIndex = 0;nIndex<500;nIndex++)
	{
		nTmp = pzfLd[nIndex];

		if (nTmp<0)
		{
			pzfLd[nIndex] = 0;
			break;
		}
	}
}

BOOL GetDataType(long nGspDataType,CString &strDataType)
{
	BOOL bRet = TRUE;

	if(nGspDataType == Data_PR_float32)
	{
		strDataType = _T("FLOAT");
	}
	else if (nGspDataType == Data_PR_boolean)
	{
		strDataType = _T("BOOL");
	}
	else if (nGspDataType == Data_PR_quality)
	{
		strDataType = _T("BVSTRING13");
	}
	else if (nGspDataType == Data_PR_utc_time)
	{
		strDataType = _T("UTCTIME");
	}
	else if (nGspDataType == Data_PR_int8)
	{
		strDataType = _T("INT");
	}
	else if (nGspDataType == Data_PR_int16)
	{
		strDataType = _T("INT");
	}
	else if (nGspDataType == Data_PR_int32)
	{
		strDataType = _T("INT");
	}
	else if (nGspDataType == Data_PR_int8u)
	{
		strDataType = _T("UINT");
	}
	else if (nGspDataType == Data_PR_int16u)
	{
		strDataType = _T("UINT");
	}
	else if (nGspDataType == Data_PR_int32u)
	{
		strDataType = _T("UINT");
	}
	else if (nGspDataType == Data_PR_visible_string)
	{
		strDataType = _T("V_STR");
	}	
	else if (nGspDataType == Data_PR_dbpos)
	{
		strDataType = _T("BOOL");
	}	
	else if (nGspDataType == Data_PR_unicode_string)
	{
		strDataType = _T("UTF8_STR");
	}	
	else if (nGspDataType == Data_PR_structure)
	{
		strDataType = _T("STRUCT");
	}
	else
	{
		bRet = FALSE;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GetDataType未知的数据类型(%ld)."),nGspDataType);
	}

	return bRet;
}

BOOL CRemoteDev::GetServerDirectory()
{
	if (!IsConnecting())
	{
		return FALSE;
	}

// 	// 发生关联
// 	Gsp_IedConnection_Associate(m_oConnectIED, &m_oErrorInfor, "S1");

	// 获取服务器逻辑设备的目录
	GspLinkedList sdList = Gsp_IedConnection_GetServerDirectory(m_oConnectIED, &m_oErrorInfor);
	long nCount = 0;

	if(sdList)
	{
		nCount = sdList->size();
		mms_New_ACSI_NODE_numLD(&m_oAcsiDevice, nCount, TRUE);
		const char *pzfLd = NULL;
		char zfValue[500];
		deque<void *> dObj = *sdList;
		long nIndex = 0;

		for(deque<void *>::const_iterator itObj = dObj.begin(); itObj != dObj.end(); itObj++)
		{
			pzfLd = (const char *)*itObj;
			_snprintf(zfValue, NAMESIZE-1, "%s", pzfLd);
			SetCharValue(zfValue);
			_snprintf(m_oAcsiDevice.LD[nIndex].LDName, NAMESIZE-1, "%s", zfValue);
			GspMemory_free((void*)pzfLd);
			nIndex++;
		}

		GspLinkedList_destroyStatic(sdList);
	} 
	else 
	{
		printf("获取服务目录错误，逻辑设备为空\n");
		return FALSE;
	}

	return TRUE;
}

BOOL CRemoteDev::GetLogicDeviceDirectory()
{
	if ((!IsConnecting())||(m_oAcsiDevice.numLD<=0))
	{
		return FALSE;
	}

	if (m_oAcsiDevice.nHasDeviceModel == 1)
	{//已经读取了XML模型文件，并且需要读取模型，则不处理数据集枚举
		return TRUE;
	}

	for (int nIndex=0; nIndex<m_oAcsiDevice.numLD; nIndex++)
	{
		GetLogicDeviceDirectory(&m_oAcsiDevice.LD[nIndex]);

		MMS_DATA_NODE *pHead_LN_NODE = m_oAcsiDevice.LD[nIndex].mms_data_node;
		MMS_DATA_NODE *pLN_NODE = pHead_LN_NODE;
		enum NODE_TYPE nTypeDepp_1 = DO_TYPE;

		do 
		{
			if (pLN_NODE == NULL)
			{
				break;
			}

			//获取LLN0的属性，因为LLN0对应的属性字符串过长，所以按照FC获取字符串，并解析获取的字符串并添加到树状模型中
#ifdef _use_mms_string
			if (strcmp(mms_string(&pLN_NODE->name),"LLN0")==0)
#else
			if (strcmp(pLN_NODE->name,"LLN0")==0)
#endif
			{
				nTypeDepp_1 = DO_TYPE;
			}
			else
			{
				nTypeDepp_1 = FC_TYPE;
			}

			MMS_DATA_NODE *FC_node = pLN_NODE->pFirstChild;
			MMS_DATA_NODE *Head_FC_node = pLN_NODE->pFirstChild;

			do 
			{
				if (FC_node == NULL)
				{
					break;
				}

				if(Get_LNX_Attributte(m_oAcsiDevice.LD[nIndex].LDName, FC_node, nTypeDepp_1)==SD_FAILURE)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "GetLogicalNodeAttributte failed! name is :%s", mms_string(&FC_node->name) );						
				}

				FC_node = FC_node->pNext;
			} while (FC_node != Head_FC_node);

			pLN_NODE = pLN_NODE->pNext;
		} while (pLN_NODE != pHead_LN_NODE);
	}

	return TRUE;
}

ST_RET CRemoteDev::Get_LNX_Attributte(ST_CHAR *pLDName,MMS_DATA_NODE* _FCNode, enum NODE_TYPE nTypeDepp_1)
{
	MMS_DATA_NODE *pParent = (MMS_DATA_NODE*)_FCNode->pParent;
	ST_RET ret;
// 	MVL_REQ_PEND *reqCtrl=NULL;
// 	GETVAR_REQ_INFO getvar_req={0};
// 	ST_CHAR tmpDataType[256000];
 	ST_CHAR item_id[256]={0};

//	getvar_req.req_tag = GETVAR_NAME;
//	getvar_req.name.object_tag = DOM_SPEC;
//	getvar_req.name.domain_id = pLDName;
	sprintf(item_id,"%s$%s", mms_string(&pParent->name) , mms_string(&_FCNode->name));
//	getvar_req.name.obj_name.item_id=item_id;
//
//	MVL_NET_INFO *connectInfo=NULL;
//	connectInfo = (MVL_NET_INFO*)(acsi_ctrl_table[_iNetInfo].pnet_info);
//	ret = mvla_getvar (connectInfo, &getvar_req, &reqCtrl);

//	if (ret == SD_SUCCESS)
//	{
//		ret = waitReqDone (reqCtrl, g_timeOut, _iNetInfo);
//	}

// 	if (ret != SD_SUCCESS)
// 	{
// #ifdef _use_mms_string
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Error getting type of variable '%s' in domain '%s'",(char*)mms_string(&_FCNode->name),pLDName);
// #else
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Error getting type of variable '%s' in domain '%s'",(char*)_FCNode->name, pLDName);
// #endif
// 	}
// 	else
// 	{
// 		ret = asn_type_to_local(reqCtrl->u.getvar.resp_info->type_spec.len, 
// 			reqCtrl->u.getvar.resp_info->type_spec.data, tmpDataType);
// 
// 		//解析LNX属性结构
// 		if (ret == SD_SUCCESS)
// 		{
// 			Pharse_LNX_Attributte(connectInfo,tmpDataType,pLDName, _FCNode, nTypeDepp_1);
// 		}
// 		else
// 		{
// #ifdef _use_mms_string
// 			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Error asn_type_to_local variable '%s' in domain '%s'[len=%d].",
// 				(char*)mms_string(&_FCNode->name),pLDName,reqCtrl->u.getvar.resp_info->type_spec.len);
// #else
// 			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Error asn_type_to_local variable '%s' in domain '%s'[len=%d].",
// 				(char*)_FCNode->name, pLDName,reqCtrl->u.getvar.resp_info->type_spec.len);
// #endif
// 		}
// 	}
// 
// 	mvl_free_req_ctrl (reqCtrl);

	return SD_SUCCESS;
}

BOOL CRemoteDev::GetLogicDeviceDirectory(LD_NODE*pLD)
{
	ASSERT(pLD);
	GspLinkedList ldList = Gsp_IedConnection_GetLogicDeviceDirectory(m_oConnectIED, &m_oErrorInfor, pLD->LDName);

	if(ldList)
	{
		long nCount = ldList->size();
		const char *pzfLN = NULL;
//		char zfValue[500];
		deque<void *> dObj = *ldList;
		long nIndex = 0;
		MMS_DATA_NODE *LLN0_node = NULL;
		ST_BOOLEAN flag;
		char *p = NULL, *pTemp = NULL;
		long nNodeLen = 0;
		CString strDataRef;

		for(deque<void *>::const_iterator itObj = dObj.begin(); itObj != dObj.end(); itObj++)
		{
			pzfLN = (const char *)*itObj;
// 			_snprintf(zfValue, NAMESIZE-1, "%s", pzfLN);
// 			SetCharValue(zfValue);
			LLN0_node = mms_node_append_sibling(NULL, &pLD->mms_data_node, (char*)pzfLN, FC_TYPE);
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "[%s] append LN:%s",pLD->LDName,pzfLN);

 			if (LLN0_node != NULL)
 			{
 				strDataRef.Format(_T("%s/%s"),pLD->LDName,pzfLN);
 				GetAllDataDefinition_LogicNode(LLN0_node,strDataRef,DLT860_FC_ST);
  				GetAllDataDefinition_LogicNode(LLN0_node,strDataRef,DLT860_FC_MX);
 				GetAllDataDefinition_LogicNode(LLN0_node,strDataRef,DLT860_FC_DC);
	   			GetAllDataDefinition_LogicNode(LLN0_node,strDataRef,DLT860_FC_SG);
 				GetAllDataDefinition_LogicNode(LLN0_node,strDataRef,DLT860_FC_SP);

				if (g_o61850ClientConfig.m_nUseDsDout)
				{
					GetAllDataDefinition_LogicNode(LLN0_node,strDataRef,DLT860_FC_CO);
				}

				GetAllDataDefinition_LogicNode(LLN0_node,strDataRef,DLT860_FC_CF);
 			}

 			GspMemory_free((void*)pzfLN);
			nIndex++;
		}

		GspLinkedList_destroyStatic(ldList);
		mms_XmlWriteNode(_T("d:\\121.xml"), &m_oAcsiDevice, FALSE);

		Get_Nodes_Detail();
		return TRUE;
	} 
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("逻辑设备(%s)下逻辑节点为空."),pLD->LDName);
		return FALSE;
	}
}

long CRemoteDev::GetReadDatasetNum(GspLinkedList allCBDataValue)
{
	if (allCBDataValue == NULL)
	{
		return 0;
	}

	deque<void *> dObj = *allCBDataValue;


	long nDatasetNum = 0;

	if (g_o61850ClientConfig.m_nSpecifiedDataset == 0)
	{
		nDatasetNum = dObj.size();
		return nDatasetNum;
	}

	char *pzfDatasetName = NULL;

	for(deque<void *>::const_iterator itObj = dObj.begin(); itObj != dObj.end(); itObj++)/*for(auto &item : *allCBDataValue)*/

	{
		pzfDatasetName = (char*)*itObj;/*item*///;
		
		if (GlobalHasSpecifiedDataset(pzfDatasetName))
		{
			nDatasetNum++;
		}
	}

	return nDatasetNum;
}

BOOL CRemoteDev::GetAllDatasets()
{
	GspLinkedList allCBDataValue = NULL;
	CString strLNRef;
	char *pzfDatasetName = NULL;

	for (int nIndex=0; nIndex<m_oAcsiDevice.numLD; nIndex++)
	{
		// 获取 所有控制块数据
		strLNRef.Format(_T("%s/LLN0"),m_oAcsiDevice.LD[nIndex].LDName);
        allCBDataValue = Gsp_IedConnection_GetLogicNodeDirectory(m_oConnectIED, &m_oErrorInfor, GSP_ACSIClass_data_set, strLNRef.GetString());

		// 获取数据并打印 测试
		if(allCBDataValue)
		{
			long nDatasetNum = 0;
			deque<void *> dObj = *allCBDataValue;

			nDatasetNum = GetReadDatasetNum(allCBDataValue);
			long nDatasetIndex = 0;

			if (g_o61850ClientConfig.m_nUseDsDout)
			{
				nDatasetNum++;
			}

			if ((g_o61850ClientConfig.m_nAutoGenModelDatas)&&(strLNRef.Find("PROT") >= 0))//自动添加对应数据集
			{
				nDatasetNum++;
			}

			mms_New_LD_NODE_numDataset(&m_oAcsiDevice.LD[nIndex], nDatasetNum);
			mms_New_LD_NODE_numJournal(&m_oAcsiDevice.LD[nIndex], nDatasetNum);

			for(deque<void *>::const_iterator itObj = dObj.begin(); itObj != dObj.end(); itObj++)/*for(auto &item : *allCBDataValue)*/

			{
				pzfDatasetName = (char*)*itObj;/*item*///;

				if ((g_o61850ClientConfig.m_nSpecifiedDataset)&&(!GlobalHasSpecifiedDataset(pzfDatasetName)))
				{
					continue;
				}

				ZeroMemory(m_oAcsiDevice.LD[nIndex].DataInfo[nDatasetIndex].DataSetID,NAMESIZE);
				_snprintf(m_oAcsiDevice.LD[nIndex].DataInfo[nDatasetIndex].DataSetID, NAMESIZE-1, "LLN0$%s", pzfDatasetName);
				GlobalSetDatasetName(m_oAcsiDevice.LD[nIndex].DataInfo[nDatasetIndex].DataSetID,m_oAcsiDevice.LD[nIndex].DataInfo[nDatasetIndex].DaSetDesc);
				GetDataSetDirectory(&m_oAcsiDevice.LD[nIndex],nDatasetIndex);
				mms_str_assign((&m_oAcsiDevice.LD[nIndex].JournalCtrls.LogInfo[nDatasetIndex].Dataset),
					m_oAcsiDevice.LD[nIndex].DataInfo[nDatasetIndex].DataSetID);
				free(pzfDatasetName);
				nDatasetIndex++;
			}

			if ((g_o61850ClientConfig.m_nAutoGenModelDatas)&&(strLNRef.Find("PROT") >= 0))//自动添加对应数据集
			{
				long nDsDevStdMsgIndex = dObj.size();
				strcpy(m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex].DataSetID, dsDevStdMsg);

				int nSize = 2;
				mms_New_LD_DATASET_INFO_numData(&m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex],nSize );
				mms_str_set(&m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex].DataSet[0].DAValue.mmsName,_T("LPHD1$DC$PhyNam$serNum"));
				mms_str_set(&m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex].DataSet[0].DADescri.Value.string,_T("装置识别代码"));
				strcpy(m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex].DataSet[0].DataType,_T("V_STR"));
				m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex].DataSet[0].Type_id = DA_DATATYE_VISIBLE_STR;

				mms_str_set(&m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex].DataSet[1].DAValue.mmsName,_T("LPHD1$DC$PhyNam$swRev"));
				mms_str_set(&m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex].DataSet[1].DADescri.Value.string,_T("装置程序版本"));
				strcpy(m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex].DataSet[1].DataType,_T("V_STR"));
				m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex].DataSet[1].Type_id = DA_DATATYE_VISIBLE_STR;
			}

			if (g_o61850ClientConfig.m_nUseDsDout)
			{
				strcpy(m_oAcsiDevice.LD[nIndex].DataInfo[nDatasetNum-1].DataSetID, dsDout);
			}
		}

		// 内存释放
		GspLinkedList_destroyStatic(allCBDataValue);
	}

	return TRUE;
}

BOOL CRemoteDev::GetDataSetDirectory(LD_NODE *pLD,const long &nDatasetIndex)
{
	CString strRef;
	strRef.Format(_T("%s/%s"),pLD->LDName,pLD->DataInfo[nDatasetIndex].DataSetID);
	strRef.Replace(_T("$"),_T("."));

    GspLinkedList datasetDirectoryList = Gsp_IedConnection_GetDataSetDirectory(m_oConnectIED, &m_oErrorInfor, strRef.GetString());

	if(!datasetDirectoryList)
	{
		// 获取数据失败处理
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取数据集目录失败."));
		// 释放内存
		GspLinkedList_destroyStatic(datasetDirectoryList);
		return 0;
	}

	long nDataNum = GspLinkedList_size(datasetDirectoryList);
	mms_New_LD_DATASET_INFO_numData(&pLD->DataInfo[nDatasetIndex], nDataNum);
	CString strFC,strTemp1,strTmp2,strTmp3;
	long nTmpIndex = 0;

	// 解析并打印内容信息
	for(int nIndex=0; nIndex < nDataNum; nIndex++)
	{
		// 获取元素值
		void* item = GspLinkedList_get(datasetDirectoryList, nIndex);
		RefsFC dataInfo = static_cast<RefsFC>(item);
		ASSERT(dataInfo);
		strFC.Format(_T("$%s"),dataInfo->fc);
		strTemp1 = dataInfo->objRefs;
		strTemp1.Replace(_T("."),_T("$"));
		nTmpIndex = strTemp1.Find('/');

		if (nTmpIndex != -1)
		{
			strTmp2 = strTemp1.Mid(nTmpIndex+1);
		}
		else
		{
			strTmp2 = strTemp1;
		}

		nTmpIndex = strTmp2.Find('$');

		if (nTmpIndex == -1)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前数据对象Ref错误(%s)."),dataInfo->objRefs);
			continue;
		}

		strTmp3 = strTmp2.Left(nTmpIndex);
		strTmp3 += strFC;
		strTmp3 += strTmp2.Mid(nTmpIndex);
        mms_str_set(&pLD->DataInfo[nDatasetIndex].DataSet[nIndex].DAValue.mmsName,strTmp3.GetString());
//		GetDataDefinition_DO_DA(&pLD->DataInfo[nDatasetIndex].DataSet[nIndex],dataInfo->objRefs,dataInfo->fc);
	}

	// 释放数据内存
	Gsp_GetDataSetDirectory_Destory(datasetDirectoryList);
	return TRUE;
}

BOOL GetFC_String(const int &nFC_Type,CString &strFC)
{
	if (nFC_Type == DLT860_FC_ST)
	{
		strFC = _T("ST");
		return TRUE;
	}
	else if (nFC_Type == DLT860_FC_SG)
	{
		strFC = _T("SG");
		return TRUE;
	}
	else if (nFC_Type == DLT860_FC_CO)
	{
		strFC = _T("CO");
		return TRUE;
	}
	else if (nFC_Type == DLT860_FC_LG)
	{
		strFC = _T("LG");
		return TRUE;
	}
	else if (nFC_Type == DLT860_FC_RP)
	{
		strFC = _T("RP");
		return TRUE;
	}
	else if (nFC_Type == DLT860_FC_BR)
	{
		strFC = _T("BR");
		return TRUE;
	}
	else if (nFC_Type == DLT860_FC_MX)
	{
		strFC = _T("MX");
		return TRUE;
	}
	else if (nFC_Type == DLT860_FC_SP)
	{
		strFC = _T("SP");
		return TRUE;
	}
	else if (nFC_Type == DLT860_FC_DC)
	{
		strFC = _T("DC");
		return TRUE;
	}
	else if (nFC_Type == DLT860_FC_CF)
	{
		strFC = _T("CF");
		return TRUE;
	}

	return FALSE;
}

BOOL CRemoteDev::GetAllDataDefinition_LogicNode(MMS_DATA_NODE *pLN,const CString &strDataRef,const int &nFC_Type)
{
	ASSERT(pLN);
	// 获取指定refs所有数据定义
    GspLinkedList allDataDefines = Gsp_IedConnection_GetAllDataDefinition(m_oConnectIED
                                                                          , &m_oErrorInfor, /*DLT860_FC_ALL*/(GspFunctionalConstraint)nFC_Type
                                                                          , strDataRef.GetString(), LNREFERENCE);

	if (!allDataDefines)
	{
		CString strFC;
		GetFC_String(nFC_Type,strFC);

		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取当前路径(%s)下的数据定义为空(FC==%s)."),strDataRef.GetString(),strFC.GetString());
		return FALSE;
	}

	if (GspLinkedList_size(allDataDefines)<=0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("LN(%s)对应功能约束(%d)下的子对象为空."),strDataRef.GetString(),nFC_Type);
		return TRUE;
	}

	CString strFC;
	MMS_DATA_NODE *pFC_Node = NULL;
	
	if (!GetFC_String(nFC_Type,strFC))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前功能约束查找失败(%d)."),nFC_Type);
		return FALSE;
	}

	if (mms_find_data_node_child(pLN, strFC.GetString()) == NULL)
	{
		pFC_Node = mms_node_append_child(pLN, strFC.GetString(), FC_TYPE);
		ASSERT(pFC_Node);

	}

	deque<void *> dDataList = *allDataDefines;

	const char *pzfDataDef = NULL;
	MMS_DATA_NODE *pChildNode = NULL;
	CString strChildDataRef;
	DataDefinition__structure__Member* dChildDataDefine = NULL;

	for(deque<void *>::const_iterator itObj = dDataList.begin(); itObj != dDataList.end(); itObj++)

	{
		GetAllDataDefinitionResponsePDU_t * innerItem = (GetAllDataDefinitionResponsePDU_t *)*itObj;

		// 打印测试
		for(int index=0; index<innerItem->data.list.count; ++index)
		{

			// 取出 GetAllDataDefinitionResponsePDU__data__Member
			GetAllDataDefinitionResponsePDU__data__Member* dfItem = innerItem->data.list.array[index];

			if (dfItem->definition.choice.structure.list.count == 0)
			{
// 				strChildDataRef.Format(_T("%s.%s"),strDataRef,(char*)dfItem->reference.buf);
// 				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("当前节点路径(%s)对应的FC(%s)子节点为空,忽略."),strChildDataRef.GetString(),strFC.GetString());
				continue;
			}

			if (mms_find_data_node_child(pFC_Node, (char*)dfItem->reference.buf) == NULL)
			{
				pChildNode = mms_node_append_child(pFC_Node, (char*)dfItem->reference.buf, FC_TYPE);

				if (pChildNode != NULL)
				{
                    strChildDataRef.Format(_T("%s.%s"),strDataRef.GetString(),(char*)dfItem->reference.buf);

					for (int nDA_Index = 0;nDA_Index<dfItem->definition.choice.structure.list.count;nDA_Index++)
					{
						dChildDataDefine = dfItem->definition.choice.structure.list.array[nDA_Index];
						GetAllDataDefinition_DO_DA(dChildDataDefine,pChildNode,strChildDataRef,nFC_Type);
					}
				}
			}
		}

		// 释放元素
		Gsp_FreeAllDataDefinition(innerItem);
	}

	GspLinkedList_destroyStatic(allDataDefines);
	return TRUE;
}

BOOL CRemoteDev::GetDataDefinition_DO_DA(tagDA* pDatasetTagDA,const char *pzfRef,const char *pzfFC)
{
// 	pzfRef = _T("P_M1112A4PROT/LLN0.FuncEna10");
// 	pzfFC = _T("XX");
	// 获取单点或者多点数据
	GspLinkedList requestList = GspLinkedList_create();

	RefsFC dataRefs = (RefsFC)GspMemory_calloc(1, sizeof(sRefsFc));

	// fc
	dataRefs->fc = (char*)GspMemory_calloc(3, sizeof(char));
	memcpy((char*)dataRefs->fc, pzfFC, 2);
	CString strDataRef;
	strDataRef = pzfRef;
	char *pzfNewRef = NULL;
	CString_to_char(strDataRef,&pzfNewRef);
	dataRefs->objRefs = pzfNewRef;
	GspLinkedList_add(requestList, dataRefs);

	// 获取数据定义
	GspLinkedList dataDefiniaionList = Gsp_IedConnection_GetDataDefinition(m_oConnectIED, &m_oErrorInfor, requestList);

	if(!dataDefiniaionList)
	{
		// 获取数据失败处理
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取数据失败(%s)."),strDataRef.GetString());

		// 释放内存
		GspLinkedList_destroyStatic(requestList);

		// 释放内存
		GspLinkedList_destroyStatic(dataDefiniaionList);
		return FALSE;
	}

	GetDataDefinitionResponsePDU_t* dataDefinitionInfo = NULL;

	// 解析并打印内容信息
	for(int index=0; index < GspLinkedList_size(dataDefiniaionList); ++index)
	{
		// 获取元素值
		void* item = GspLinkedList_get(dataDefiniaionList, index);
		dataDefinitionInfo = static_cast<GetDataDefinitionResponsePDU_t*>(item);

		// 打印信息
	}

	GspLinkedList_destroyStatic(dataDefiniaionList);
	GspMemory_free((char*)dataRefs->fc);
	GspMemory_free((char*)dataRefs->objRefs);
	GspMemory_free(dataRefs);
	GspLinkedList_destroyStatic(requestList);
	return TRUE;
}

BOOL CRemoteDev::GetAllDataDefinition_DO_DA(DataDefinition__structure__Member *pDataDefine,MMS_DATA_NODE *pDO_DA,const CString &strDataRef,const int &nFC_Type)
{
	MMS_DATA_NODE *pChildNode = NULL;
	CString strChildDataRef;
	DataDefinition__structure__Member* dChildDataDefine = NULL;

	if ((pDataDefine->type->present == Data_PR_structure)&&(pDataDefine->type->choice.structure.list.count == 0))
	{
		return FALSE;
	}

	if (mms_find_data_node_child(pDO_DA, (char*)pDataDefine->name.buf) == NULL)
	{
		pChildNode = mms_node_append_child(pDO_DA, (char*)pDataDefine->name.buf, FC_TYPE);

		if (pChildNode != NULL)
		{
            strChildDataRef.Format(_T("%s.%s"),strDataRef.GetString(),(char*)pDataDefine->name.buf);
			CString strDataType,strFC;
			GetFC_String(nFC_Type,strFC);

			if (pDataDefine->type->present == Data_PR_structure)
			{
				for (int nDA_Index = 0;nDA_Index<pDataDefine->type->choice.structure.list.count;nDA_Index++)
				{
					dChildDataDefine = pDataDefine->type->choice.structure.list.array[nDA_Index];
					GetAllDataDefinition_DO_DA(dChildDataDefine,pChildNode,strChildDataRef,nFC_Type);
				}

				return TRUE;
			}

			GetDataType(pDataDefine->type->present,strDataType);
			strDataType.MakeUpper();

			if (strDataType.GetLength()<=16)
			{
                strcpy(pChildNode->DataType,strDataType.GetString());
			} 
			else
			{
                CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前数据类型(%s)字节长度超过16字节."),strDataType.GetString());
				return FALSE;
			}

			pChildNode->type = IED_TYPE;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CRemoteDev::GetAllDataDefinition_DO_DA(MMS_DATA_NODE *pDO_DA,const CString &strDataRef,const int &nFC_Type)
{
	// 获取单点或者多点数据
    GspLinkedList allDataDefines = Gsp_IedConnection_GetAllDataDefinition(m_oConnectIED, &m_oErrorInfor, (GspFunctionalConstraint)nFC_Type, strDataRef.GetString(), LNREFERENCE);
 
 	if ((!allDataDefines)/*||(GspLinkedList_size(allDataDefines)<=0)*/)
 	{
 		CString strDataType,strFC;
 		GetFC_String(nFC_Type,strFC);
 
 		if (!ReadDataType(strDataRef,strFC,strDataType))
 		{
 			return FALSE;
 		}
 
 		strDataType.MakeUpper();
 		
 		if (strDataType.GetLength()<=16)
 		{
            strcpy(pDO_DA->DataType,strDataType.GetString());
 		} 
 		else
 		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前数据类型(%s)字节长度超过16字节."),strDataType.GetString());
 			return FALSE;
 		}
 
 		pDO_DA->type = IED_TYPE;
 		return TRUE;
 	}
 
 	deque<void *> dDataList = *allDataDefines;

//  	const char *pzfDataDef = NULL;
  	MMS_DATA_NODE *pChildNode = NULL;
  	CString strChildDataRef;
	DataDefinition__structure__Member* dChildDataDefine = NULL;
 
 	for(deque<void *>::const_iterator itObj = dDataList.begin(); itObj != dDataList.end(); itObj++)

 	{
 		GetAllDataDefinitionResponsePDU_t * innerItem = (GetAllDataDefinitionResponsePDU_t *)*itObj;
 
 		// 打印测试
 		for(int index=0; index<innerItem->data.list.count; ++index)
 		{
 
 			// 取出 GetAllDataDefinitionResponsePDU__data__Member
 			GetAllDataDefinitionResponsePDU__data__Member* dfItem = innerItem->data.list.array[index];

			if (mms_find_data_node_child(pDO_DA, (char*)dfItem->reference.buf) == NULL)
			{
				pChildNode = mms_node_append_child(pDO_DA, (char*)dfItem->reference.buf, FC_TYPE);

				if (pChildNode != NULL)
				{
                    strChildDataRef.Format(_T("%s.%s"),strDataRef.GetString(),(char*)dfItem->reference.buf);

					if (dfItem->definition.choice.structure.list.count == 0)
					{
						CString strDataType,strFC;
						GetFC_String(nFC_Type,strFC);
						CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("当前节点路径(%s)对应的FC(%s)子节点为空,未能获取实际数据类型."),strChildDataRef.GetString(),strFC.GetString());

// 						if (dfItem->definition->choice->el->present == Data_PR_structure)
// 						{
// 							return GetAllDataDefinition_DO_DA(pChildNode,strChildDataRef,nFC_Type);
// 						}
// 
// 						GetDataType(pDataDefine->type->present,strDataType);
// 						strDataType.MakeUpper();
// 
// 						if (strDataType.GetLength()<=16)
// 						{
// 							strcpy(pChildNode->DataType,strDataType);
// 						} 
// 						else
// 						{
// 							CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前数据类型(%s)字节长度超过16字节."),strDataType);
// 							return FALSE;
// 						}

						pChildNode->type = IED_TYPE;
						return TRUE;
					} 
					else
					{
						for (int nDA_Index = 0;nDA_Index<dfItem->definition.choice.structure.list.count;nDA_Index++)
						{
							dChildDataDefine = dfItem->definition.choice.structure.list.array[nDA_Index];
							GetAllDataDefinition_DO_DA(dChildDataDefine,pChildNode,strChildDataRef,nFC_Type);
						}
					}
				}
			}
 		}
 
 		// 释放元素
 		Gsp_FreeAllDataDefinition(innerItem);
 	}
 
 	GspLinkedList_destroyStatic(allDataDefines);
	return TRUE;
}

long CRemoteDev::GetDeviceIndex()
{
	CExBaseList *pParent = (CExBaseList*)GetParent();
	ASSERT(pParent);
	return pParent->FindIndex(this);
}

void CRemoteDev::Release_AcsiNode()
{
	mms_Free_ACSI_NODE(&m_oAcsiDevice);
// 	ST_INT nLdIndex = 0;
// 	ST_INT nIndex=0;
// 
// 	for (nLdIndex=0; nLdIndex<m_oAcsiDevice.numLD; nLdIndex++)
// 	{
// 		mms_Free_LD_NODE(m_oAcsiDevice.LD+nLdIndex);
// 	}
// 
// 	if (m_oAcsiDevice.LD != NULL)
// 	{
// 		free(m_oAcsiDevice.LD);
// 		m_oAcsiDevice.LD = NULL;
// 	}
// 
// 	if (m_oAcsiDevice.nCurrReportCount > 0)
// 	{
// 		for (nIndex=0; nIndex<m_oAcsiDevice.nCurrReportCount; nIndex++)
// 		{
// 			rpt_quit(&m_oAcsiDevice.Reports[nIndex]);
// 		}
// 	}
// 
// 	mms_file_sys_free(&m_oAcsiDevice.FileDir);
// 	mms_str_quit(&m_oAcsiDevice.RcdFilePath);
// 	mms_str_quit(&m_oAcsiDevice.IpAddr);
}

BOOL CRemoteDev::GetActiveSG(const long &nLdIndex)
{
	if (!IsConnecting()||(m_oAcsiDevice.numLD<=nLdIndex))
	{
		return FALSE;
	}
	// 读定值控制块的值
	ST_CHAR VarName[NAMESIZE+1];
	ZeroMemory(VarName,NAMESIZE+1);
	_snprintf(VarName, NAMESIZE-1, "%s/LLN0.SGCB", m_oAcsiDevice.LD[nLdIndex].LDName);
//	const char* VarName = "P_L2201APROT/LLN0.SGCB";
	GspLinkedList retList = Gsp_IedConnection_GetSGCBValues(m_oConnectIED, &m_oErrorInfor, VarName);

	// 打印调试
	if(retList)
	{
		GetSGCBValuesResponsePDU_t* sgcbValue = static_cast<GetSGCBValuesResponsePDU_t*>(retList->front());

		for(int index=0; index < sgcbValue->sgcb.list.count; ++index)
		{
			// 读取成员信息
			GetSGCBValuesResponsePDU__sgcb__Member* sgcbItem = sgcbValue->sgcb.list.array[index];

			if(sgcbItem->present != GetSGCBValuesResponsePDU__sgcb__Member_PR_value)
			{
				printf("该定制控制块的值有错误, 错误信息: %ld \n", sgcbItem->choice.error);
			} 
			else 
			{
				m_oAcsiDevice.nSGNum = sgcbItem->choice.value.numOfSG;
				m_oAcsiDevice.nEditSGIndex = sgcbItem->choice.value.editSG;
				m_oAcsiDevice.nRunSGIndex = sgcbItem->choice.value.actSG;
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("当前激活定制区号(%d),编辑定值区号(%d),定值区数量(%d)."),sgcbItem->choice.value.actSG,sgcbItem->choice.value.editSG,sgcbItem->choice.value.numOfSG);
			}
		}

		// 内存释放
		Gsp_FreeSGCBValues(sgcbValue);
		GspLinkedList_destroyStatic(retList);
	} 
	else 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("没有读取到定制控制块的值,错误代码: %d."), m_oErrorInfor);
		return FALSE;
	}

	return TRUE;
}

BOOL CRemoteDev::SetActiveSG(const long &nLdIndex,const long &nSG)
{
	if (!IsConnecting()||(m_oAcsiDevice.numLD<=nLdIndex))
	{
		sprintf(m_oAcsiDevice.InfoSetSG, _T("设置当前定值运行区号%d失败,(%d)."), nSG,m_oErrorInfor);
		CLogPrint::LogString(XLOGLEVEL_ERROR,m_oAcsiDevice.InfoSetSG);
		return FALSE;
	}

	// 选择激活定制组
	ST_CHAR sgcbRefs[NAMESIZE+1];
	ZeroMemory(sgcbRefs,NAMESIZE+1);
	_snprintf(sgcbRefs, NAMESIZE-1, "%s/LLN0.SGCB", m_oAcsiDevice.LD[nLdIndex].LDName);
	bool ret = Gsp_IedConnection_SelectActiveSG(m_oConnectIED, &m_oErrorInfor, sgcbRefs, nSG);

	// 调试信息
	if(ret)
	{
		sprintf(m_oAcsiDevice.InfoSetSG, "设置当前定值运行区号%d成功.", nSG);
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("选择激活定值区成功,切换到 %d 区."), nSG);
		m_oAcsiDevice.nRunSGIndex = nSG;
	} 
	else 
	{
		sprintf(m_oAcsiDevice.InfoSetSG, _T("设置当前定值运行区号%d失败,(%d)."), nSG,m_oErrorInfor);
		CLogPrint::LogString(XLOGLEVEL_ERROR,m_oAcsiDevice.InfoSetSG);
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("选择激活定值区失败,切换到 %d 区失败, 错误代码: %d."),nSG, m_oErrorInfor);
		return FALSE;
	}

	return TRUE;
}

BOOL GspMms_GetValue(Data* dataInfo,tagDAValue *pDAValue)
{
	if (dataInfo == NULL)
	{
		return FALSE;
	}

	Data_PR dataType = GspMmsValue_getType(dataInfo);

	switch (dataType) 
	{
	case Data_PR_error:
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取数据值失败(%s),错误的数据类型."),mms_string(&pDAValue->mmsName));		 
		}
		break;
	case Data_PR_boolean:
		{
			pDAValue->Value.i = GspMmsValue_getBoolean(dataInfo);			 
		}
		break;
	case Data_PR_int8:
	case Data_PR_int16:
	case Data_PR_int32:
		{
			pDAValue->Value.i = GspMmsValue_toInt32(dataInfo);			 
		}
		break;
	case Data_PR_int8u:
	case Data_PR_int16u:
	case Data_PR_int32u:
		{
			pDAValue->Value.u = GspMmsValue_toUint32(dataInfo);			 
		}
		break;	
	case Data_PR_float32:
		{
			pDAValue->Value.f = GspMmsValue_toFloat(dataInfo);
//			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,("当前值(%s=%f)."),mms_string(&pDAValue->mmsName),pDAValue->Value.f);
		}
		break;
	case Data_PR_quality:
		{
			CString strTmp;
			GspMmsValue_getBitStringAsCString(dataInfo,strTmp);
            mms_str_set(&pDAValue->Value.string, strTmp.GetString());
		}
		break;
	case Data_PR_bit_string:
		{
			CString strTmp;
			GspMmsValue_getBitStringAsCString(dataInfo,strTmp);
            mms_str_set(&pDAValue->Value.string, strTmp.GetString());
		}
		break;
	case Data_PR_dbpos:
		{
			CString strTmp;
			GspMmsValue_getBitStringAsCString(dataInfo,strTmp);

			if (strTmp == "01")
			{
				pDAValue->Value.i = 0;
			}
			else if (strTmp == "10")
			{
				pDAValue->Value.i = 1;
			}
			else
			{
				pDAValue->Value.i = 0;
			}
//			mms_str_set(&pDAValue->Value.string, strTmp);
		}
		break;	
	case Data_PR_visible_string:
		{
			CString strTmp;
			strTmp = GspMmsValue_toString(dataInfo);
			char *pUtfValue = NULL, *pGBK_Value = NULL;
			long nLength = 0;
			CString_to_char(strTmp,&pUtfValue);
//			charUtf8_to_charGBK(pUtfValue,strTmp.GetLength(),&pGBK_Value,nLength);
			mms_str_set(&pDAValue->Value.string, pUtfValue);
			delete pUtfValue;
//			delete pGBK_Value;
		}
		break;
	case Data_PR_unicode_string:
		{
			CString strTmp;
			strTmp = GspMmsValue_toString(dataInfo);
            char *pUtfValue = NULL;
            unsigned char *pGBK_Value = NULL;
			int nLength = 0;
			CString_to_char(strTmp,&pUtfValue);
            utf8_to_gbk_r((unsigned char*)pUtfValue,strTmp.GetLength(),&pGBK_Value, &nLength);
            mms_str_set(&pDAValue->Value.string, (char*)pGBK_Value);
			delete pUtfValue;
			delete pGBK_Value;
		}
		break;
	case Data_PR_utc_time:
		{
			CString strTime1,strTime2;
			uint32_t nUtcTime = 0;
			nUtcTime = GspMmsValue_toUnixTimestamp(dataInfo);

			uint64_t u64Time = convertUtcTimeToMs(dataInfo->choice.utc_time);
			mms_u64Time_to_utc_time(u64Time,pDAValue->Value.utctime);

// 			CTime tmValue = nUtcTime;
// 			strTime1 = tmValue.Format(_T("%Y-%m-%d %H:%M:%S"));
// 			mms_str_set(&pDAValue->Value.utctime, strTime1);
		}
		break;
	default:
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GspMms_GetValue未知的数据类型(%d)."),dataType);
		break;
	}

	return TRUE;
}

BOOL GetGspValue_String(Data* dataInfo,CString &strValue)
{
	if (dataInfo == NULL)
	{
		return FALSE;
	}

	Data_PR dataType = GspMmsValue_getType(dataInfo);

	switch (dataType) 
	{
	case Data_PR_error:
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取数据值失败(GetGspValue_String),错误的数据类型."));		 
		}
		break;
	case Data_PR_bit_string:
		{
			GspMmsValue_getBitStringAsCString(dataInfo,strValue);
		}
		break;	
	case Data_PR_visible_string:
		{
			strValue = GspMmsValue_toString(dataInfo);
		}
		break;
	case Data_PR_unicode_string:
		{
			CString strTmp;
			strTmp = GspMmsValue_toString(dataInfo);
            char *pUtfValue = NULL;
            unsigned char *pGBK_Value = NULL;
            int nLength = 0;
			CString_to_char(strTmp,&pUtfValue);
            utf8_to_gbk_r((unsigned char*)pUtfValue,strTmp.GetLength(),&pGBK_Value, &nLength);
            strValue = (char*)pGBK_Value;
			delete pUtfValue;
			delete pGBK_Value;
		}
		break;

	default:
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GspMms_GetValue_String失败数据类型(%d)."),dataType);
		break;
	}

	return TRUE;
}

BOOL CRemoteDev::ReadValue(tagDAValue *pDAValue,const CString &strDataRef,const CString &strFC)
{
	BOOL bRet = TRUE;
	// 获取单点或者多点数据
	GspLinkedList dataValue = ReadValue(strDataRef,strFC);

	if (dataValue == NULL)
	{
		return FALSE;
	}

	// 获取元素值
	void* item = GspLinkedList_get(dataValue, 0);
	Data* dataInfo = static_cast<Data*>(item);

	if(!GspMms_GetValue(dataInfo,pDAValue))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("解析结果对象为空."));
		bRet = FALSE;
	} 

	// 释放元素值
	GspMmsValue_delete(dataInfo);
	GspLinkedList_destroyStatic(dataValue);
	return bRet;

// 	GspLinkedList requestList = GspLinkedList_create();
// 	sRefsFc dataRefs;
// 	dataRefs.fc = strFC;
// 	dataRefs.objRefs = strDataRef;
// 	GspLinkedList_add(requestList, &dataRefs);
// 
// 	// 请求数据
// 	GspLinkedList dataValue = Gsp_IedConnection_GetDataValues(m_oConnectIED, &m_oErrorInfor, requestList);
// 
// 	if(!dataValue)
// 	{
// 		// 释放内存
// 		GspLinkedList_destroyStatic(requestList);
// 
// 		// 释放内存
// 		GspLinkedList_destroyStatic(dataValue);
// 
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取数据失败."));
// 		return FALSE;
// 	}
// 
// 	if (GspLinkedList_size(dataValue)<=0)
// 	{
// 		GspLinkedList_destroyStatic(requestList);
// 		GspLinkedList_destroyStatic(dataValue);
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取数据失败."));
// 		return FALSE;
// 	}
// 
// 	// 获取元素值
// 	void* item = GspLinkedList_get(dataValue, 0);
// 	Data* dataInfo = static_cast<Data*>(item);
// 
// 	if(!GspMms_GetValue(dataInfo,pDAValue))
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("解析结果对象为空."));
// 		bRet = FALSE;
// 	} 
// 
// 	// 释放元素值
// 	GspMmsValue_delete(dataInfo);
// 	GspLinkedList_destroyStatic(dataValue);
// 
// 	// 释放内存
// 	GspLinkedList_destroyStatic(requestList);
	return bRet;
}

GspLinkedList CRemoteDev::ReadValue(const CString &strDataRef,const CString &strFC)
{
	GspLinkedList requestList = GspLinkedList_create();
	sRefsFc dataRefs;
    dataRefs.fc = strFC.GetString();
    dataRefs.objRefs = strDataRef.GetString();
	GspLinkedList_add(requestList, &dataRefs);

	// 请求数据
	GspLinkedList dataValue = Gsp_IedConnection_GetDataValues(m_oConnectIED, &m_oErrorInfor, requestList);

	if(!dataValue)
	{
		// 释放内存
		GspLinkedList_destroyStatic(requestList);

		// 释放内存
		GspLinkedList_destroyStatic(dataValue);

		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取数据失败."));
		return NULL;
	}

	if (GspLinkedList_size(dataValue)<=0)
	{
		GspLinkedList_destroyStatic(requestList);
		GspLinkedList_destroyStatic(dataValue);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取数据失败."));
		return NULL;
	}

	GspLinkedList_destroyStatic(requestList);
	return dataValue;	
}

BOOL CRemoteDev::ReadDataType(const CString &strDataRef,const CString &strFC,CString &strDataType)
{
	BOOL bRet = TRUE;

// 	GspLinkedList requestList = GspLinkedList_create();
// 
// 	RefsFC dataRefs = (RefsFC)GspMemory_calloc(1, sizeof(sRefsFc));
// 
// 	// fc
// 	dataRefs->fc = (char*)GspMemory_calloc(3, sizeof(char));
// 	memcpy((char*)dataRefs->fc, strFC.GetString(), 2);
// 	char *pzfRef = NULL;
// 	CString_to_char(strDataRef,&pzfRef);
// 	dataRefs->objRefs = pzfRef;
// 	GspLinkedList_add(requestList, dataRefs);
// 
// 	// 获取数据定义
// 	GspLinkedList dataDefiniaionList = Gsp_IedConnection_GetDataDefinition(m_oConnectIED, &m_oErrorInfor, requestList);
// 
// 	if(!dataDefiniaionList)
// 	{
// 		// 获取数据失败处理
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取数据失败(%s)."),strDataRef);
// 
// 		// 释放内存
// 		GspLinkedList_destroyStatic(requestList);
// 
// 		// 释放内存
// 		GspLinkedList_destroyStatic(dataDefiniaionList);
// 		return FALSE;
// 	}
// 
// 	GetDataDefinitionResponsePDU_t* dataDefinitionInfo = NULL;
// 
// 	// 解析并打印内容信息
// 	for(int index=0; index < GspLinkedList_size(dataDefiniaionList); ++index)
// 	{
// 		// 获取元素值
// 		void* item = GspLinkedList_get(dataDefiniaionList, index);
// 		dataDefinitionInfo = static_cast<GetDataDefinitionResponsePDU_t*>(item);
// 
// 		// 打印信息
// 	}
// 
// 	GspLinkedList_destroyStatic(dataDefiniaionList);
// 	GspMemory_free((char*)dataRefs->fc);
// 	GspMemory_free((char*)dataRefs->objRefs);
// 	GspMemory_free(dataRefs);
// 	GspLinkedList_destroyStatic(requestList);


	// 获取单点或者多点数据
	GspLinkedList requestList = GspLinkedList_create();

	// 请求参数 001
	sRefsFc dataRefs;
    dataRefs.fc = strFC.GetString();
    dataRefs.objRefs = strDataRef.GetString();
	GspLinkedList_add(requestList, &dataRefs);

	// 请求数据
	GspLinkedList dataValue = Gsp_IedConnection_GetDataValues(m_oConnectIED, &m_oErrorInfor, requestList);

	if(!dataValue)
	{
		GspLinkedList_destroyStatic(requestList);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取数据失败."));
		return FALSE;
	}

	if (GspLinkedList_size(dataValue)<=0)
	{
		GspLinkedList_destroy(dataValue);
		GspLinkedList_destroyStatic(requestList);
		return FALSE;
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取数据失败."));
// 		return FALSE;
	}

	// 获取元素值
	void* item = GspLinkedList_get(dataValue, 0);
	Data* dataInfo = static_cast<Data*>(item);

	if(dataInfo)
	{
		// 打印调试信息
		//			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("数据类型%i."), GspMmsValue_getType(dataInfo));

		if(GspMmsValue_getType(dataInfo) == Data_PR_float32)
		{
			strDataType = _T("FLOAT");
		}
		else if (GspMmsValue_getType(dataInfo) == Data_PR_boolean)
		{
			strDataType = _T("BOOL");
		}
		else if (GspMmsValue_getType(dataInfo) == Data_PR_quality)
		{
			strDataType = _T("BVSTRING13");
		}
		else if (GspMmsValue_getType(dataInfo) == Data_PR_dbpos)
		{
			strDataType = _T("BOOL");
		}
		else if (GspMmsValue_getType(dataInfo) == Data_PR_utc_time)
		{
			strDataType = _T("UTCTIME");
		}
		else if (GspMmsValue_getType(dataInfo) == Data_PR_int8)
		{
			strDataType = _T("INT");
		}
		else if (GspMmsValue_getType(dataInfo) == Data_PR_int16)
		{
			strDataType = _T("INT");
		}
		else if (GspMmsValue_getType(dataInfo) == Data_PR_int32)
		{
			strDataType = _T("INT");
		}
		else if (GspMmsValue_getType(dataInfo) == Data_PR_int8u)
		{
			strDataType = _T("UINT");
		}
		else if (GspMmsValue_getType(dataInfo) == Data_PR_int16u)
		{
			strDataType = _T("UINT");
		}
		else if (GspMmsValue_getType(dataInfo) == Data_PR_int32u)
		{
			strDataType = _T("UINT");
		}
		else if (GspMmsValue_getType(dataInfo) == Data_PR_structure)
		{
			strDataType = _T("STRUCT");
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ReadDataType未知的数据类型(%d)."),GspMmsValue_getType(dataInfo));
		}
	} 
	else 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("解析结果为空."));
		bRet = FALSE;
	} 

	// 释放内存
	GspLinkedList_destroyStatic(requestList);
	GspLinkedList_destroy(dataValue);
	return bRet;
}

BOOL CRemoteDev::ReadValue(const char *pLdName,tagDA *pDA)
{
	if (!IsConnecting())
	{
		if (!LinkDev())
		{
			return FALSE;
		}
	}

	if (pDA == NULL)
	{
		return FALSE;
	}

	long nErorrNum = 0;
	BOOL bRet = TRUE;

	if (strstr(pDA->DataType,"STRUCT") && pDA->pSubDA)
	{
		for (int nSubIndex=0; nSubIndex<pDA->nSubDANum;nSubIndex++)
		{
			if (!ReadValue(pLdName,&pDA->pSubDA[nSubIndex]/*,bSettingSE*/))
			{
				nErorrNum++;
			}
		}

		if (nErorrNum == pDA->nSubDANum)
		{
			return FALSE;
		}
	}
	else
	{
		CString strFC,strDataRef;

		if (!GetDataRef(pLdName,mms_string(&pDA->DAValue.mmsName),strFC,strDataRef))
		{
			return FALSE;
		}

//		strFC = _T("ST");//zhouhj 20210609 暂时固定为ST
		bRet = ReadValue(&pDA->DAValue,strDataRef,strFC);
	}

	return bRet;
}

BOOL CRemoteDev::ReadSEValue(const char *pLdName,tagDA *pDA)
{
	if (!IsConnecting())
	{
		if (!LinkDev())
		{
			return FALSE;
		}
	}

	if (pDA == NULL)
	{
		return FALSE;
	}

	long nErorrNum = 0;
	BOOL bRet = TRUE;

	if (strstr(pDA->DataType,"STRUCT") && pDA->pSubDA)
	{
		for (int nSubIndex=0; nSubIndex<pDA->nSubDANum;nSubIndex++)
		{
			if (!ReadSEValue(pLdName,&pDA->pSubDA[nSubIndex]/*,bSettingSE*/))
			{
				nErorrNum++;
			}
		}

		if (nErorrNum == pDA->nSubDANum)
		{
			return FALSE;
		}
	}
	else
	{
		CString strFC,strDataRef;

		if (!GetDataRef(pLdName,mms_string(&pDA->DAValue.mmsName),strFC,strDataRef))
		{
			return FALSE;
		}

		// 获取单点或者多点数据
		GspLinkedList requestList = GspLinkedList_create();

		RefsFC tmpRefs01 = (RefsFC)GspMemory_calloc(1, sizeof(struct sRefsFc));
		tmpRefs01->fc = "SE";
        tmpRefs01->objRefs = strDataRef.GetString();
		GspLinkedList_add(requestList, tmpRefs01);

		// 请求数据
		GspLinkedList dataValue = Gsp_IedConnection_GetEditSGValue(m_oConnectIED, &m_oErrorInfor, requestList);

		if(!dataValue)
		{
			GspLinkedList_destroyStatic(requestList);
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取定值数据失败."));
			return FALSE;
		}

		if (GspLinkedList_size(dataValue)<=0)
		{
			GspLinkedList_destroy(dataValue);
			GspLinkedList_destroyStatic(requestList);
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取数据失败."));
			return FALSE;
		}

		// 获取元素值
		void* item = GspLinkedList_get(dataValue, 0);
		GetEditSGValueResponsePDU_t* tmpSgItem = static_cast<GetEditSGValueResponsePDU_t*>(item);

		if((tmpSgItem)&&(tmpSgItem->value.list.count>=1))
		{
			GspMmsValue* sgValueItem = tmpSgItem->value.list.array[0];

			if(!GspMms_GetValue(sgValueItem,&pDA->DAValue))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("解析结果对象为空."));
				bRet = FALSE;
			} 

		} 
		else 
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("解析结果数量为空."));
			bRet = FALSE;
		} 
			// 释放定值元素
		Gsp_FreeEditSGValues(tmpSgItem);
		// 释放定值列表
		GspLinkedList_destroyStatic(dataValue);

		// 定制参数内存释放
		deque<void *> d = *requestList;


		for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++)

		{
			RefsFC innerItem = (RefsFC)(*it);
			GspMemory_free(innerItem);
		}

		// 释放内存
		GspLinkedList_destroyStatic(requestList);
//		GspLinkedList_destroy(dataValue);
	}

	return bRet;
}

BOOL CRemoteDev::ConfirmEditSGValues(const char *pLdName)
{
	char zfRef[500];
	memset(zfRef,0,500);
	sprintf(zfRef, _T("%s/LLN0.SGCB"), pLdName);
	// 定值修改业务流 004 -> 确认定值修改操作
	if(!Gsp_IedConnection_ConfirmEditSGValues(m_oConnectIED, &m_oErrorInfor, zfRef))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("固化定值区失败(%s)."),zfRef);
		m_oAcsiDevice.nEditSGIndex = 0;
		return FALSE;
	} 

	m_oAcsiDevice.nEditSGIndex = 0;//固化定值区后,固定把编辑区置为0,下次读取时，需要重新设置编辑区,按电科院要求,适配深瑞保护装置  zhouhj20210903 
	return TRUE;
}

BOOL CRemoteDev::GetRCBEnableState(const char *pLdName,const char *pRcbItem,BOOL &bRptEna)
{
	// 获取报告控制块数据
	if ((strstr(pRcbItem,"$BR$"))||(strstr(pRcbItem,".brcb")))
	{
		return GetBRCBValues(pLdName,pRcbItem,bRptEna);
	}
	else if ((strstr(pRcbItem,"$RP$"))||(strstr(pRcbItem,".urcb")))
	{
		return GetURCBValues(pLdName,pRcbItem,bRptEna);
	}
	else
		return FALSE;
}

BOOL CRemoteDev::GetURCBValues(const char *pLdName,const char *pRcbItem,BOOL &bRptEna)
{
	CString strReportRefs;
	strReportRefs.Format(_T("%s/%s"),pLdName,pRcbItem);
	strReportRefs.Replace(_T("$RP$"),_T("."));
    m_oCurUrcbControlBlk = Gsp_IedConnection_GetURCBValues(m_oConnectIED, &m_oErrorInfor, strReportRefs.GetString());

	// 错误信息判断
	if(m_oErrorInfor != GSP_IED_ERROR_OK || m_oCurUrcbControlBlk == NULL)
	{
		Gsp_URCBControlBlk_Destory(m_oCurUrcbControlBlk);
		m_oCurUrcbControlBlk = NULL;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取报告控制块数据失败,错误代码: %d."), m_oErrorInfor);
		return FALSE;
	}

	if(m_oCurUrcbControlBlk->urcbControlBlk == NULL)
	{
		Gsp_URCBControlBlk_Destory(m_oCurUrcbControlBlk);
		m_oCurUrcbControlBlk = NULL;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取报告控制块数据为空."));
		return FALSE;
	}

	bRptEna = *m_oCurUrcbControlBlk->urcbControlBlk->rptEna;
// 	printf("报告ID: %s \n", currentUrcbControlBlk->urcbControlBlk->rptID->buf);
// 	printf("报告是否启用: %d \n", *currentUrcbControlBlk->urcbControlBlk->rptEna);
// 	printf("报告 datSet: %s \n", currentUrcbControlBlk->urcbControlBlk->datSet->buf);
// 	printf("报告 optFlds: ");
// 	Gsp_BitString_print(currentUrcbControlBlk->urcbControlBlk->optFlds);
// 	printf("报告 bufTm: %d \n", *currentUrcbControlBlk->urcbControlBlk->bufTm);
// 	printf("报告 trgOps: ");
// 	Gsp_BitString_print(currentUrcbControlBlk->urcbControlBlk->trgOps);
// 	printf("报告 intgPd: %d \n", *currentUrcbControlBlk->urcbControlBlk->intgPd);
// 	printf("报告 gi: %d \n", *currentUrcbControlBlk->urcbControlBlk->gi);
	return TRUE;
}

BOOL CRemoteDev::GetBRCBValues(const char *pLdName,const char *pRcbItem,BOOL &bRptEna)
{
	CString strReportRefs;
	strReportRefs.Format(_T("%s/%s"),pLdName,pRcbItem);
	strReportRefs.Replace(_T("$BR$"),_T("."));
    m_oCurBrcbControlBlk = Gsp_IedConnection_GetBRCBValues(m_oConnectIED, &m_oErrorInfor, strReportRefs.GetString());

	// 错误信息判断
	if(m_oErrorInfor != GSP_IED_ERROR_OK || m_oCurBrcbControlBlk == NULL)
	{
		Gsp_BRCBControlBlk_Destory(m_oCurBrcbControlBlk);
		m_oCurBrcbControlBlk = NULL;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取报告控制块数据失败,错误代码: %d."), m_oErrorInfor);
		return FALSE;
	}

	if(m_oCurBrcbControlBlk->brcbControlBlk == NULL)
	{
		Gsp_BRCBControlBlk_Destory(m_oCurBrcbControlBlk);
		m_oCurBrcbControlBlk = NULL;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取报告控制块数据为空."));
		return FALSE;
	}

	bRptEna = *m_oCurBrcbControlBlk->brcbControlBlk->rptEna;
// 	printf("报告是否启用: %d \n", );
// 	printf("报告 datSet: %s \n", currentBrcbControlBlk->brcbControlBlk->datSet->buf);
// 	printf("报告 optFlds: ");
// 	Gsp_BitString_print(currentBrcbControlBlk->brcbControlBlk->optFlds);
// 	printf("报告 bufTm: %d \n", *currentBrcbControlBlk->brcbControlBlk->bufTm);
// 	printf("报告 trgOps: ");
// 	Gsp_BitString_print(currentBrcbControlBlk->brcbControlBlk->trgOps);
// 	printf("报告 intgPd: %d \n", *currentBrcbControlBlk->brcbControlBlk->intgPd);
// 	printf("报告 gi: %d \n", currentBrcbControlBlk->brcbControlBlk->gi);
// 	printf("报告 purgeBuf: %d \n", *currentBrcbControlBlk->brcbControlBlk->purgeBuf);
// 	printf("报告 entryID: %s \n", currentBrcbControlBlk->brcbControlBlk->entryID->buf);
	return TRUE;
}

BOOL CRemoteDev::SetBRCBValues(RCB_NODE *pReportCB,const char *pLdName,const char *pRcbItem,long nOptFlds,long nTrgOps,long nEnbleGI,long nEntryID_Continue)
{
	if (m_oCurBrcbControlBlk == NULL)
	{
		BOOL bEnable = FALSE;

		if (!GetBRCBValues(pLdName,pRcbItem,bEnable))
		{
			return FALSE;
		}	
	}

	CString strReportRefs;
	strReportRefs.Format(_T("%s/%s"),pLdName,pRcbItem);
	strReportRefs.Replace(_T("$BR$"),_T("."));

	// 准备设置参数
	BRCBControlBlk targetBrcbControlBlk = static_cast<BRCBControlBlk>(GspMemory_calloc(1, sizeof(sBRCBControlBlk)));
	// 设置 refs(从获取的报告控制块中直接拷贝)
	Gsp_BRCBControlBlk_SetReportRefs(targetBrcbControlBlk, m_oCurBrcbControlBlk->reportRefs);

	// 设置操作选项(设置带着报告原因)
	if ((nOptFlds>>2)%2)
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_reason_for_inclusion, TRUE,FALSE);
	} 
	else
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_reason_for_inclusion, FALSE,FALSE);
	}

	// 设置操作选项(报告带着序列号)

	if ((nOptFlds)%2)
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_sequence_number, true, true);
	} 
	else
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_sequence_number, false, true);
	}

	// 设置操作选项(报告带着时间戳)
	if ((nOptFlds>>1)%2)
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_report_time_stamp, true, true);
	}
	else
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_report_time_stamp, false, true);
	}

	// 设置操作选项(报告带着数据集名字)
	if ((nOptFlds>>3)%2)
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_data_set_name, true, true);
	}
	else
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_data_set_name, false, true);
	}

	// 设置操作选项(报告带着数据参引串)
	if ((nOptFlds>>4)%2)
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_data_reference, true, true);
	}
	else
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_data_reference, false, true);
	}

	if ((nOptFlds>>5)%2)
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_buffer_overflow, true, true);
	}
	else
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_buffer_overflow, false, true);
	}

	// 设置操作选项(报告带着EntryID)

	if ((nOptFlds>>6)%2)
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_entryID, true, true);
	}
	else
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_entryID, false, true);
	}

	if ((nOptFlds>>7)%2)
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_conf_revision, true, true);
	}
	else
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_conf_revision, false, true);
	}

	if ((nOptFlds>>8)%2)
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_segmentation, true, true);
	}
	else
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_segmentation, false, true);
	}

	// 设置报告触发选项
	if(!Gsp_IedConnection_SetBRCBValues(m_oConnectIED, &m_oErrorInfor, targetBrcbControlBlk))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("设置操作选项失败(%s)(%d)."),m_oCurBrcbControlBlk->reportRefs,m_oErrorInfor);
	}

	BOOL bGI = (nTrgOps>>4)%2;//是否支持总召

	if (bGI)
	{
	// 设置支持总召唤
        Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, TriggerConditions_general_interrogation, TRUE,FALSE);
	} 
	else if (nEnbleGI)
	{
		nTrgOps += (1<<4);
        Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, TriggerConditions_general_interrogation, TRUE,FALSE);
	}
	else
	{
        Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, TriggerConditions_general_interrogation, FALSE,FALSE);
	}

	// 设置周期性上送
	BOOL bIntegrity = (nTrgOps>>3)%2;//是否周期上送

	if (bIntegrity)
	{
        Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, TriggerConditions_integrity, TRUE,TRUE);
	} 
	else
	{
        Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, TriggerConditions_integrity, FALSE,TRUE);
	}

	if ((nTrgOps)%2)//数据变化上送
	{
        Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, TriggerConditions_data_change, TRUE,TRUE);
	} 
	else
	{
        Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, TriggerConditions_data_change, FALSE,TRUE);
	}

	if ((nTrgOps>>1)%2)//品质变化上送
	{
        Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, TriggerConditions_quality_change, TRUE,TRUE);
	} 
	else
	{
        Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, TriggerConditions_quality_change, FALSE,TRUE);
	}

	if ((nTrgOps>>2)%2)//数据更新上送
	{
        Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, TriggerConditions_data_update, TRUE,TRUE);
	} 
	else
	{
        Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, TriggerConditions_data_update, FALSE,TRUE);
	}

	// 设置触发选项
	if(!Gsp_IedConnection_SetBRCBValues(m_oConnectIED, &m_oErrorInfor, targetBrcbControlBlk))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("设置触发选项失败(%s)(%d)."),m_oCurBrcbControlBlk->reportRefs,m_oErrorInfor);
	}

	if (bIntegrity)
	{
		// 设置周期性上送时间
		Gsp_BRCBControlBlk_IntgPd(targetBrcbControlBlk, g_o61850ClientConfig.GetIntgPdTime());

		// 设置周期性上送时间
		if(!Gsp_IedConnection_SetBRCBValues(m_oConnectIED, &m_oErrorInfor, targetBrcbControlBlk))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("设置周期性上送时间失败(%s)(%d)."),m_oCurBrcbControlBlk->reportRefs,m_oErrorInfor);
		}
	}

//	strcpy(pReportCB->RptID,strReportRefs); 
	CString strTmpRptID;
	strTmpRptID = Gsp_BRCBControlBlk_GetRptID(m_oCurBrcbControlBlk);
	strTmpRptID.Replace(_T("$BR$"),_T("."));
	strTmpRptID.Replace(_T("$RP$"),_T("."));

	// 设置RPTID
    Gsp_BRCBControlBlk_SetRPTID(targetBrcbControlBlk, strTmpRptID.GetString());

	// 设置报告控制块
	if(!Gsp_IedConnection_SetBRCBValues(m_oConnectIED, &m_oErrorInfor, targetBrcbControlBlk))
	{
		Gsp_BRCBControlBlk_Destory(m_oCurBrcbControlBlk);
		m_oCurBrcbControlBlk = NULL;
		Gsp_BRCBControlBlk_Destory(targetBrcbControlBlk);
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("设置报告控制块失败."));
		return FALSE;
	}

	// 安装报告回调
    Gsp_IedConnection_InstallReportCallBack(m_oConnectIED, strReportRefs.GetString(), strTmpRptID.GetString(),
		ClientCallBackHandler::ReportHandler_BRCB, (void*)this/*pReportCB->RptID*/);//zhouhj 改为传递对象指针

	// 设置报告控制块值(开启报告)
	Gsp_BRCBControlBlk_EnableRpt(targetBrcbControlBlk, true);

	if(!Gsp_IedConnection_SetBRCBValues(m_oConnectIED, &m_oErrorInfor, targetBrcbControlBlk))
	{
		Gsp_BRCBControlBlk_Destory(m_oCurBrcbControlBlk);
		m_oCurBrcbControlBlk = NULL;
		Gsp_BRCBControlBlk_Destory(targetBrcbControlBlk);
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("报告开启失败."));
		return FALSE;
	}

	if (bGI || nEnbleGI)
	{
		// 设置总召
		Gsp_BRCBControlBlk_GI(targetBrcbControlBlk, true);
		if(!Gsp_IedConnection_SetBRCBValues(m_oConnectIED, &m_oErrorInfor, targetBrcbControlBlk))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("设置总召失败(%s)(%d)."),m_oCurBrcbControlBlk->reportRefs,m_oErrorInfor);
		}
	}

	Gsp_BRCBControlBlk_Destory(m_oCurBrcbControlBlk);
	m_oCurBrcbControlBlk = NULL;
    m_vBrcbContrlBlk.AddTail(targetBrcbControlBlk);
	return TRUE;
}

BOOL CRemoteDev::SetURCBValues(RCB_NODE *pReportCB,const char *pLdName,const char *pRcbItem,long nOptFlds,long nTrgOps,long nEnbleGI)
{
	if (m_oCurUrcbControlBlk == NULL)
	{
		BOOL bEnable = FALSE;

		if (!GetURCBValues(pLdName,pRcbItem,bEnable))
		{
			return FALSE;
		}	
	}

	CString strReportRefs;
	strReportRefs.Format(_T("%s/%s"),pLdName,pRcbItem);
	strReportRefs.Replace(_T("$RP$"),_T("."));

	// 准备设置参数
	URCBControlBlk targetUrcbControlBlk = static_cast<URCBControlBlk>(GspMemory_calloc(1, sizeof(sURCBControlBlk)));
	// 设置 refs(从获取的报告控制块中直接拷贝)
	Gsp_URCBControlBlk_SetReportRefs(targetUrcbControlBlk, m_oCurUrcbControlBlk->reportRefs);

	// 设置操作选项(设置带着报告原因)
	if ((nOptFlds>>2)%2)
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_reason_for_inclusion, TRUE,FALSE);
	} 
	else
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_reason_for_inclusion, FALSE,FALSE);
	}

	// 设置操作选项(报告带着序列号)

	if ((nOptFlds)%2)
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_sequence_number, true, true);
	} 
	else
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_sequence_number, false, true);
	}

	// 设置操作选项(报告带着时间戳)
	if ((nOptFlds>>1)%2)
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_report_time_stamp, true, true);
	}
	else
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_report_time_stamp, false, true);
	}

	// 设置操作选项(报告带着数据集名字)
	if ((nOptFlds>>3)%2)
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_data_set_name, true, true);
	}
	else
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_data_set_name, false, true);
	}

	// 设置操作选项(报告带着数据参引串)
	if ((nOptFlds>>4)%2)
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_data_reference, true, true);
	}
	else
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_data_reference, false, true);
	}

	if ((nOptFlds>>5)%2)
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_buffer_overflow, true, true);
	}
	else
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_buffer_overflow, false, true);
	}

	// 设置操作选项(报告带着EntryID)

	if ((nOptFlds>>6)%2)
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_entryID, true, true);
	}
	else
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_entryID, false, true);
	}

	if ((nOptFlds>>7)%2)
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_conf_revision, true, true);
	}
	else
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_conf_revision, false, true);
	}

	if ((nOptFlds>>8)%2)
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_segmentation, true, true);
	}
	else
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_segmentation, false, true);
	}

	// 设置操作选项
	if(!Gsp_IedConnection_SetURCBValues(m_oConnectIED, &m_oErrorInfor, targetUrcbControlBlk))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("设置操作选项失败(%s)(%d)."),m_oCurUrcbControlBlk->reportRefs,m_oErrorInfor);
	}

	// 设置周期性上送
	BOOL bIntegrity = (nTrgOps>>3)%2;//是否周期上送

	if (bIntegrity)
	{
        Gsp_URCBControlBlk_SetTriggerConditions(targetUrcbControlBlk, TriggerConditions_integrity, TRUE,FALSE);
	} 
	else
	{
        Gsp_URCBControlBlk_SetTriggerConditions(targetUrcbControlBlk, TriggerConditions_integrity, FALSE,FALSE);
	}

	BOOL bGI = (nTrgOps>>4)%2;

	if (bGI)
	{
		// 设置支持总召唤
        Gsp_URCBControlBlk_SetTriggerConditions(targetUrcbControlBlk, TriggerConditions_general_interrogation, TRUE,TRUE);
	} 
	else if (nEnbleGI)
	{
//		nTrgOps += (1<<4);
        Gsp_URCBControlBlk_SetTriggerConditions(targetUrcbControlBlk, TriggerConditions_general_interrogation, TRUE,TRUE);
	}
	else
	{
        Gsp_URCBControlBlk_SetTriggerConditions(targetUrcbControlBlk, TriggerConditions_general_interrogation, FALSE,TRUE);
	}

	if ((nTrgOps)%2)//数据变化上送
	{
        Gsp_URCBControlBlk_SetTriggerConditions(targetUrcbControlBlk, TriggerConditions_data_change, TRUE,TRUE);
	} 
	else
	{
        Gsp_URCBControlBlk_SetTriggerConditions(targetUrcbControlBlk, TriggerConditions_data_change, FALSE,TRUE);
	}

	if ((nTrgOps>>1)%2)//品质变化上送
	{
        Gsp_URCBControlBlk_SetTriggerConditions(targetUrcbControlBlk, TriggerConditions_quality_change, TRUE,TRUE);
	} 
	else
	{
        Gsp_URCBControlBlk_SetTriggerConditions(targetUrcbControlBlk, TriggerConditions_quality_change, FALSE,TRUE);
	}

	if ((nTrgOps>>2)%2)//数据更新上送
	{
        Gsp_URCBControlBlk_SetTriggerConditions(targetUrcbControlBlk, TriggerConditions_data_update, TRUE,TRUE);
	} 
	else
	{
        Gsp_URCBControlBlk_SetTriggerConditions(targetUrcbControlBlk, TriggerConditions_data_update, FALSE,TRUE);
	}

	// 设置报告控制块
	if(!Gsp_IedConnection_SetURCBValues(m_oConnectIED, &m_oErrorInfor, targetUrcbControlBlk))
	{
		Gsp_URCBControlBlk_Destory(m_oCurUrcbControlBlk);
		m_oCurUrcbControlBlk = NULL;
		Gsp_URCBControlBlk_Destory(targetUrcbControlBlk);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("设置报告控制块失败(%s)(%d)."),m_oCurUrcbControlBlk->reportRefs,m_oErrorInfor);
		return FALSE;
	}

	if (bIntegrity)
	{
		// 设置周期性上送时间
		Gsp_URCBControlBlk_IntgPd(targetUrcbControlBlk, g_o61850ClientConfig.GetIntgPdTime());

		if(!Gsp_IedConnection_SetURCBValues(m_oConnectIED, &m_oErrorInfor, targetUrcbControlBlk))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("设置周期性上送时间失败(%s)(%d)."),m_oCurUrcbControlBlk->reportRefs,m_oErrorInfor);
		}
	}

//strcpy(pReportCB->RptID,strReportRefs); 
	CString strTmpRptID;
	strTmpRptID = Gsp_URCBControlBlk_GetRptID(m_oCurUrcbControlBlk);
	strTmpRptID.Replace(_T("$BR$"),_T("."));
	strTmpRptID.Replace(_T("$RP$"),_T("."));

	// 设置RPTID
    Gsp_URCBControlBlk_SetRPTID(targetUrcbControlBlk, strTmpRptID.GetString());

	if(!Gsp_IedConnection_SetURCBValues(m_oConnectIED, &m_oErrorInfor, targetUrcbControlBlk))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("设置RPTID失败(%s)(%d)."),m_oCurUrcbControlBlk->reportRefs,m_oErrorInfor);
	}

	// 安装报告回调
    Gsp_IedConnection_InstallReportCallBack(m_oConnectIED, strReportRefs.GetString(), strTmpRptID.GetString(),
		ClientCallBackHandler::ReportHandler_URCB, (void*)this/*pReportCB->RptID*/);

	// 设置报告控制块值(开启报告)
	Gsp_URCBControlBlk_EnableRpt(m_oCurUrcbControlBlk, true);

	if(!Gsp_IedConnection_SetURCBValues(m_oConnectIED, &m_oErrorInfor, m_oCurUrcbControlBlk))
	{
		Gsp_URCBControlBlk_Destory(m_oCurUrcbControlBlk);
		m_oCurUrcbControlBlk = NULL;
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("报告开启失败."));
		Gsp_URCBControlBlk_Destory(targetUrcbControlBlk);
		return FALSE;
	}

	if (bGI || nEnbleGI)
	{
		// 设置总召
		Gsp_URCBControlBlk_GI(targetUrcbControlBlk, true);

		if(Gsp_IedConnection_SetURCBValues(m_oConnectIED, &m_oErrorInfor, targetUrcbControlBlk))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("设置总召失败(%s)(%d)."),m_oCurUrcbControlBlk->reportRefs,m_oErrorInfor);
		}
	}

	Gsp_URCBControlBlk_Destory(m_oCurUrcbControlBlk);
	m_oCurUrcbControlBlk = NULL;
    m_vUrcbContrlBlk.AddTail(targetUrcbControlBlk);
	return TRUE;
}

BOOL CRemoteDev::SetRCBValueGI(const char *pLdName,const char *pRcbItem,BOOL bGI_Value)
{
	return TRUE;
}

BOOL CRemoteDev::check_prefix_and_suffix(const CString &strMsgPath,CString &strDirPath)
{
	strDirPath = strMsgPath;
	long nIndex = strMsgPath.Find('^');//查找具有时间段信息的连接符
	BOOL bTime,bNewNum;
	bTime = (nIndex != -1);

	if (bTime)
	{
		strDirPath = strMsgPath.Mid(nIndex+1);
		nIndex = strDirPath.Find('/');

		if (nIndex != -1)
		{
			strDirPath = strDirPath.Mid(nIndex);
		}
		else
			strDirPath = strMsgPath;
	}

	nIndex = strDirPath.Find("/NEWEST_");//查找最新条目数的后缀
	bNewNum = (nIndex != -1);

	if (bNewNum)
	{
		strDirPath = strDirPath.Left(nIndex+1);
	}

	return (bTime||bNewNum);
}

BOOL CRemoteDev::GetAllDir(const CString &strDirPath,BOOL bOnlyReadCfg)
{
	XMMS_FILE_SYS_OBJ *pTagFileDir = &m_oAcsiDevice.FileDir;

	if (pTagFileDir->subFiles.numOfData > 0)
	{
		pTagFileDir->bFirstRead = FALSE;
	}

	CString strActDirPath,strTmp;
	BOOL bMark = check_prefix_and_suffix(strDirPath,strActDirPath);//此函数检查路径中是否包含按时间段查找的前缀或按最新文件数查找的后缀，含有返回1，不包含返回0，将去除前缀、后缀后的文件路径返回给参数2
	strTmp = mms_string(&pTagFileDir->filedir.filename);

	if ((strTmp != strActDirPath)||(bMark))//文件查找路径变更后，清空源文件记录
	{
		mms_file_sys_free(&m_oAcsiDevice.FileDir);
		mms_str_init(&pTagFileDir->filedir.filename);
	}

	long nLenth = strActDirPath.GetLength();

	if (strActDirPath.IsEmpty())
	{
		strActDirPath = _T("/");
	}
	else if ((strActDirPath.ReverseFind('/') != (nLenth-1))&&(strActDirPath.ReverseFind('\\') != (nLenth-1)))
	{
		strActDirPath += _T("/");
	}

    mms_str_set(&pTagFileDir->filedir.filename,strActDirPath.GetString());
	m_oAcsiDevice.nRecordFileTotalNum = 0;
	GetDir(pTagFileDir,strDirPath,bOnlyReadCfg);
	GetAllSubDir(pTagFileDir,bOnlyReadCfg);
	m_oAcsiDevice.nRecordFileTotalNum = Global_GetSysObjFileNum_CurDir(pTagFileDir);
	return TRUE;
}

void CRemoteDev::GetAllSubDir(XMMS_FILE_SYS_OBJ *pTagFileDir,BOOL bOnlyReadCfg)
{
	if (pTagFileDir == NULL)
		return;

	XMMS_FILE_SYS_OBJ *pSubFileDir = NULL;
	int nIndex = 0;
	CString strFullPath;

	for(nIndex = 0;nIndex<pTagFileDir->subFiles.numOfData;nIndex++)
	{
		pSubFileDir = (XMMS_FILE_SYS_OBJ *)*(pTagFileDir->subFiles.Datas + nIndex);

		if (pSubFileDir->nType == 1)
		{
			strFullPath = Global_GetFileDirFullPath(pSubFileDir);
			GetDir(pSubFileDir,strFullPath,bOnlyReadCfg);
			GetAllSubDir(pSubFileDir,bOnlyReadCfg);
		}
	}

}

BOOL CRemoteDev::GetDir(XMMS_FILE_SYS_OBJ *pFileDir,const CString &strFullPath,BOOL bOnlyReadCfg)
{
	Global_MarkOldFile(pFileDir);
	BOOL bRet = TRUE;
 	XMMS_FILE_SYS_OBJ *pSubDir = NULL;
 	XMMS_FILE_SYS_OBJ *pFind = NULL;
	pFileDir->readfailed = FALSE;
	long nIndex = 0 ,nType = 0;
	CString strFileDirName,strContinueName,strTmp;
	strContinueName = _T("");

	// 获取文件目录
	bool bMoreData = FALSE;
	GspLinkedList fileDirs = NULL;

	do 
	{
        fileDirs = Gsp_IedConnection_GetFileDirectory(m_oConnectIED,&m_oErrorInfor,strFullPath.GetString(),NULL,NULL, NULL, bMoreData);

		if ((!fileDirs)||(m_oErrorInfor != GSP_IED_ERROR_OK))
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("读取目录(%s)失败(%d)."),strFullPath.GetString(),m_oErrorInfor);
			pFileDir->readfailed = TRUE;
			bRet = FALSE;
			break;
		}

		// 解析并打印
		deque<void *> d = *fileDirs;

		char zfEnd = 0;

		for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++)

		{
			GspFileDirectoryEntry fileItem = (GspFileDirectoryEntry)(*it);
			strContinueName = Gsp_FileDirEntry_GetFileName(fileItem);

			if (strContinueName.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("文件或目录名称为空."));
				continue;
			}

			strFileDirName = strContinueName;
			zfEnd = strContinueName.GetAt(strContinueName.GetLength()-1);

			if (zfEnd == '\\')
			{
				strFileDirName = strContinueName.Left(strContinueName.GetLength()-1);
				strFileDirName += '/';
				strContinueName = strFileDirName;
			}
			
			nIndex = strFileDirName.ReverseFind('/');

			nType = (nIndex == (strFileDirName.GetLength()-1));//如果最后一个字符为'/'则为目录

			if (nType)
			{
				strTmp = strFileDirName.Left(nIndex);
				nIndex = strTmp.ReverseFind('/');//如果除去最后一个字符外还有'/'，则为全路径,需要从路径中获取目录名称

				if (nIndex != -1)
				{
					strTmp = strFileDirName.Mid(nIndex+1);
					strFileDirName = strTmp;
				} 
			} 
			else
			{
				if (bOnlyReadCfg)//如果只读取录波文件，在此处根据文件名称进行过滤
				{
					if (strFileDirName.GetLength()<=4)//名称长度小于4,则肯定不是
					{
						continue;
					}

					strTmp = strFileDirName.Mid(strFileDirName.GetLength()-4);
					strTmp.MakeLower();

					if (strTmp != _T(".cfg"))//文件名最后4个字节不匹配,则忽略
					{
						continue;
					}
				}

				strTmp = strFileDirName;
			}

            pFind = Global_CheckRepeatOfSysobj(strFileDirName.GetString(),pFileDir);

			if (pFind != NULL)
			{
				pFind->bIsNew = FALSE;
			} 
			else
			{
				vector_set_add_data(&pFileDir->subFiles,(LPVOID*)&pSubDir,sizeof(XMMS_FILE_SYS_OBJ));
				pSubDir->filedir.fsize = Gsp_FileDirEntry_GetFileSize(fileItem);
				pSubDir->filedir.mtime = (double)Gsp_FileDirEntry_GetLastModified(fileItem)/1000;
				pSubDir->bIsNew = TRUE;
				pSubDir->nType = nType;
				mms_str_init(&pSubDir->filedir.filename);

                char *pUtfValue = NULL;
                unsigned char *pGBK_Value = NULL;
                int nLength = 0;
				CString_to_char(strFileDirName,&pUtfValue);
                utf8_to_gbk_r((unsigned char*)pUtfValue,strFileDirName.GetLength(),&pGBK_Value, &nLength);

                mms_str_set(&pSubDir->filedir.filename, (char*)pGBK_Value);
				delete pGBK_Value;
				delete pUtfValue;
				pSubDir->parent = pFileDir;
			}

			Gsp_FileDirEntry_Destroy(fileItem);
		}
	} while (bMoreData);

	return bRet;
}

BOOL CRemoteDev::SetFile(const CString &strLocalFile,const CString &strDevPath)
{
	CString strDevFilePath,strFileName;
	strFileName = GetFileNameFromFilePath(strLocalFile);

	if (strDevPath.IsEmpty())
	{
		strDevFilePath.Format(_T("/%s"),strFileName.GetString());
	} 
	else if (strDevPath.GetAt(strDevPath.GetLength()-1) == '\\')
	{
		strDevFilePath.Format(_T("%s%s"),strDevPath.GetString(),strFileName.GetString());
	}
	else if (strDevPath.GetAt(strDevPath.GetLength()-1) == '/')
	{
		strDevFilePath.Format(_T("%s%s"),strDevPath.GetString(),strFileName.GetString());
	}
	else
	{
		strDevFilePath.Format(_T("%s/%s"),strDevPath.GetString(),strFileName.GetString());
	}

	// 写文件
    FILE* pfile = fopen(strLocalFile.GetString(), "r+b");

	if (pfile == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("文件(%s)打开失败."),strLocalFile.GetString());
		return FALSE;
	}

	uint32_t nFilePostion = 1;
	char fileDataBlock[1024*16] = {0};
	long nSendIndex = 0;
	long nCount = 0;
	fseek(pfile, 0, SEEK_END);
	long nTotalLenth = ftell(pfile);
	fseek(pfile, 0, SEEK_SET);
	long nTotalLenth1 = ftell(pfile);

	while (nTotalLenth1<nTotalLenth/*!feof(pfile)*/) 
	{
		// 读取一定数量数据
		memset(fileDataBlock, 0 , sizeof(fileDataBlock));
		nCount = fread(fileDataBlock, sizeof (char), 1024*16, pfile);
		nSendIndex++;

		// 是否为空
		bool endFlag = false;
		nTotalLenth1 = ftell(pfile);

		if(nTotalLenth1>=nTotalLenth/*feof(pfile)*/)
		{
			endFlag = true;
		}

		// 发送文件
        bool bSendRet = Gsp_IedConnection_setFile(m_oConnectIED, &m_oErrorInfor, strDevFilePath.GetString(), nFilePostion, fileDataBlock,nCount, endFlag);
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("当前帧报文(%ld)字节数量(%ld),当前文件位置(%ld),总字节数(%ld)."),nSendIndex,nCount,nTotalLenth1,nTotalLenth);

		if (!bSendRet)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("下装文件(%s),DevPah(%s)当前帧报文(%ld)发送失败."),strLocalFile.GetString(),strDevFilePath.GetString(),nSendIndex);
		}

		nFilePostion += nCount;
//		filePostion++;
//		printf("写一帧文件, 字节数量:%d, 是否写成功:%d ", 1024, ret);
	}

    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("下装文件(%s),DevPah(%s),下发字节总数量(%ld),文件字节总数量(%ld).")
                               ,strLocalFile.GetString(),strDevFilePath.GetString(),nFilePostion,nTotalLenth);
	fclose(pfile);
	return TRUE;
}

BOOL CRemoteDev::ReadFile(const CString &strRemoteFilePath,const CString &strLocalRootFolderPath)
{
	CString strLocalFilePath;

	if (strLocalRootFolderPath.ReverseFind('\\') == (strLocalRootFolderPath.GetLength()-1))
	{
        strLocalFilePath = strLocalRootFolderPath + strRemoteFilePath;
	} 
	else
	{
        strLocalFilePath = strLocalRootFolderPath + strRemoteFilePath;
	}

	strLocalFilePath.Replace(_T("//"),_T("\\"));
	strLocalFilePath.Replace(_T("\\/"),_T("\\"));
	strLocalFilePath.Replace(_T("/"),_T("\\"));

	CString strFolderPath;
	strFolderPath = GetPathFromFilePathName(strLocalFilePath);
	CreateAllDirectories(strFolderPath);

	// 下载文件
#ifdef UNICODE
	char *pszFile = NULL;
	CString_to_char(strLocalFilePath, &pszFile);
	FILE *pfile = fopen(pszFile, "r+b");
	delete pszFile;
#else
	FILE *pfile = fopen(strLocalFilePath.GetString(), "w+b");
#endif

	if (pfile == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("创建文件(%s)失败."),strLocalFilePath.GetString());
		return FALSE;
	}

//	FILE* fp = fopen(strLocalFilePath, "w");
	uint32_t filePostion = 1;

    while (Gsp_IedConnection_GetFile(m_oConnectIED, &m_oErrorInfor
                                     ,strRemoteFilePath.GetString(), &filePostion, /*ClientCallBackHandler::*/ClientCallBack_GetFileHandler, (void*)pfile))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,("下载文件 %s 已下载数据 %d 字节."), strRemoteFilePath.GetString(), filePostion);
	}

	return TRUE;
}

BOOL CRemoteDev::ResetDev()
{
	if (ResetDev(_T("PROT")))
	{
		return TRUE;
	}

	return ResetDev(_T("LD0"));
}

BOOL CRemoteDev::ResetDev(const CString &strLDName)
{
	LD_NODE *pLD = NULL;

	for (int j=0; j<m_oAcsiDevice.numLD; j++)
	{
		pLD = &m_oAcsiDevice.LD[j]; 

		if (pLD != NULL)
		{
            if (strstr(pLD->LDName,strLDName.GetString())!=NULL)
			{
				break;
			}
		}
	}

	if (pLD == NULL)
	{
		return FALSE;
	}

	CString strRef;
	strRef.Format(_T("%s/LLN0.LEDRs"),pLD->LDName);
	long nValue = 1;
	// 设置值
	GspMmsValue* ctlVal = GspMmsValue_newBoolean(nValue);

	if (!CtrlWriteDA_Direct(strRef,ctlVal))
	{
		strRef.Format(_T("%s/LLN0.CBFlt"),pLD->LDName);
		// 设置值
		ctlVal = GspMmsValue_newBoolean(nValue);
		return CtrlWriteDA_Direct(strRef,ctlVal);
	}

	return TRUE;
}

BOOL CRemoteDev::ReadJournal(long long int nStartEntry,char *pszItemID,long nldIndex)
{
	return TRUE;
}

BOOL CRemoteDev::HasReadSettingZone()
{
	if (m_oAcsiDevice.nSGNum<=0)
	{
		return FALSE;
	}

	return TRUE;
}

void CRemoteDev::InitRptLogCB_Struct(LD_NODE *pLD)
{
	if (pLD == NULL)
	{
		return;
	}

	for (int nIndex = 0;nIndex<pLD->numDaSet;nIndex++)
	{
		pLD->DataInfo[nIndex].numRcb = 0;
	}

// 	mms_Free_LD_JOURNAL_CTRLS(&pLD->JournalCtrls);
// 	mms_JournalDataOfVector_Free(pLD->JournalDatas.Datas,pLD->JournalDatas.numOfData);
// 	vector_free(&pLD->JournalDatas);
}

BOOL CRemoteDev::GetRpcInterfaceDirectory()
{
 	// 获取 rpc 接口名字信息
 	GspLinkedList interfaceList = Gsp_IedConnection_GetRpcInterfaceDirectory(m_oConnectIED, &m_oErrorInfor);
 	long nInterIndex = 0,nInterNum = 0,nRpcInterfaceDefinitionIndex = 0,nRpcInterfaceDefinitionNum = 0,nRpcMethodDirectoryIndex = 0,nRpcMethodDirectoryNum = 0;
 
 	// 获取 rpc 方法信息
 	deque<void *> pD_InterfaceList = *interfaceList;
 	nInterNum = pD_InterfaceList.size();

 	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Gsp_IedConnection_GetRpcInterfaceDirectory获取总数量%ld."), nInterNum);
	CString strAllString;
 
 	for(deque<void *>::const_iterator itInterface = pD_InterfaceList.begin(); itInterface != pD_InterfaceList.end(); itInterface++)

 	{
 		nInterIndex++;
 		char *pInterfaceItem = (char*)*itInterface;
 		// 打印接口名字信息
 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("interface: %s,Index=%ld."), pInterfaceItem,nInterIndex);
 
 		// 获取 rpc 接口定义信息
 		GspLinkedList interfaceDefinitionList = Gsp_IedConnection_GetRpcInterfaceDefinition(m_oConnectIED, &m_oErrorInfor, (char*)pInterfaceItem);
 
 		deque<void *> pD_InterfaceDefinitionList = *interfaceDefinitionList;
 		nRpcInterfaceDefinitionNum = pD_InterfaceDefinitionList.size();

 		nRpcInterfaceDefinitionIndex = 0;
 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Gsp_IedConnection_GetRpcInterfaceDefinition获取总数量%ld."), nRpcInterfaceDefinitionNum);
 
 		for(deque<void *>::const_iterator itInterfaceDefinition = pD_InterfaceDefinitionList.begin(); itInterfaceDefinition != pD_InterfaceDefinitionList.end(); itInterfaceDefinition++)

 		{
 			// 获取接口定义信息
 			nRpcInterfaceDefinitionIndex++;
 			GetRpcInterfaceDefinitionResponsePDU_t* rpcdItem = (GetRpcInterfaceDefinitionResponsePDU_t*)(*itInterfaceDefinition);
 			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Gsp_IedConnection_GetRpcInterfaceDefinition,Index=%ld,rpcdItem->method.list.count = %d."),nRpcInterfaceDefinitionIndex,
 				rpcdItem->method.list.count);
 
 			// 打印接口定义信息
 			for(int index=0; index < rpcdItem->method.list.count; ++index)
 			{
 				GetRpcInterfaceDefinitionResponsePDU__method__Member* rpcdInnerItem = (GetRpcInterfaceDefinitionResponsePDU__method__Member*)rpcdItem->method.list.array[index];
				strAllString.Format(_T("%s.%s"),pInterfaceItem,rpcdInnerItem->name.buf);
                XDLT_RPC_METHOD* pRpcMethod = Global_RpcMethodAddNewMethod(&m_oAcsiDevice.oRpcMethods,strAllString.GetString());
				pRpcMethod->nVersion = rpcdInnerItem->version;
				pRpcMethod->nTimeout = rpcdInnerItem->timeout;
				pRpcMethod->nRequestType = rpcdInnerItem->request.present;
				pRpcMethod->nResponseType = rpcdInnerItem->response.present;
 				// name
 				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("RpcInterfaceDefinition--name: %s."), rpcdInnerItem->name.buf);
 				// version
 				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("RpcInterfaceDefinition--version: %lu."), rpcdInnerItem->version);
 				// timeout
 				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("RpcInterfaceDefinition--timeout: %lu."), rpcdInnerItem->timeout);
 				// request（剩余内部信息不在打印，类推即可）
 				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("RpcInterfaceDefinition--request->type: %u."), rpcdInnerItem->request.present);
 				// response（剩余内部信息不在打印，类推即可）
 				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("RpcInterfaceDefinition--response->type: %u."), rpcdInnerItem->response.present);
 			}
 		}
 
 		// 释放接口定义
 		Gsp_IedConnection_FreeRpcInterfaceDefinition(interfaceDefinitionList);
 
 		// 获取方法列表
 		GspLinkedList methodList = Gsp_IedConnection_GetRpcMethodDirectory(m_oConnectIED, &m_oErrorInfor, pInterfaceItem);
 		deque<void *> pD_MethodList = *methodList;

 		nRpcMethodDirectoryIndex = 0;
 		nRpcMethodDirectoryNum = pD_MethodList.size();
 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Gsp_IedConnection_GetRpcMethodDirectory获取总数量%ld."), nRpcMethodDirectoryNum);
 
 		for(deque<void *>::const_iterator itMethod = pD_MethodList.begin(); itMethod != pD_MethodList.end(); itMethod++)

 		{
 			char *pMethodItem = (char*)*itMethod;
 			nRpcMethodDirectoryIndex++;
 
 			// 打印信息
 			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("RpcMethodDirectory--interface: %s,Index=%ld."), pMethodItem,nRpcMethodDirectoryIndex);
			strAllString.Format(_T("%s.%s"),pInterfaceItem,pMethodItem);
            XDLT_RPC_METHOD* pRpcMethod = Global_RpcMethodAddNewMethod(&m_oAcsiDevice.oRpcMethods,strAllString.GetString());
 
 
 			// 获取 rpc 接口定义信息
 			GspLinkedList medthodDefinitionList = Gsp_IedConnection_GetRpcInterfaceDefinition(m_oConnectIED, &m_oErrorInfor, (char*)pInterfaceItem);
 
 			deque<void *> pD_MethodDefinitionList = *medthodDefinitionList;
 			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Gsp_IedConnection_GetRpcInterfaceDefinition获取总数量%d."), pD_MethodDefinitionList.size());
 
 
 			for(deque<void *>::const_iterator itMethodDefinition = pD_MethodDefinitionList.begin(); itMethodDefinition != pD_MethodDefinitionList.end(); itMethodDefinition++)

 			{
 				// 获取接口定义信息
 				GetRpcInterfaceDefinitionResponsePDU_t* rpcdItem = (GetRpcInterfaceDefinitionResponsePDU_t*)(*itMethodDefinition);
 
 				// 打印接口定义信息
 				for(int index=0; index < rpcdItem->method.list.count; ++index){
 					GetRpcInterfaceDefinitionResponsePDU__method__Member* rpcdInnerItem = (GetRpcInterfaceDefinitionResponsePDU__method__Member*)rpcdItem->method.list.array[index];
					mms_str_set(&pRpcMethod->paraCallName,(const char *)rpcdInnerItem->name.buf);
					pRpcMethod->nVersion = rpcdInnerItem->version;
					pRpcMethod->nTimeout = rpcdInnerItem->timeout;
					pRpcMethod->nRequestType = rpcdInnerItem->request.present;
					pRpcMethod->nResponseType = rpcdInnerItem->response.present;
					// name
 					CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("name: %s."), rpcdInnerItem->name.buf);
 					// version
 					CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("version: %lu."), rpcdInnerItem->version);
 					// timeout
 					CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("timeout: %lu."), rpcdInnerItem->timeout);
 					// request（剩余内部信息不在打印，类推即可）
 					CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("request->type: %u."), rpcdInnerItem->request.present);
 					// response（剩余内部信息不在打印，类推即可）
 					CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("response->type: %u."), rpcdInnerItem->response.present);
 				}
 
 				// TODO RPC 调用（需根据上一步实际测试结果进行调用）
 				// Gsp_IedConnection_RPCCall
 			}
 
 
 			// 释放方法定义
 			Gsp_IedConnection_FreeRpcMethodDefinition(medthodDefinitionList);
 		}
 
 		// 释放方法信息
 		Gsp_IedConnection_FreeRpcMethodDirectory(methodList);
 	}

	// 释放接口信息
	Gsp_IedConnection_FreeRpcInterfaceDirectory(interfaceList);
	return TRUE;
}

void ShowRpcValues(GspMmsValue* responsePDU,tagDA* pTagDA)
{
	if (responsePDU == NULL)
	{
		return;
	}

	Data_PR dataType = GspMmsValue_getType(responsePDU);

	switch (dataType) 
	{
	case Data_PR_error:
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取RPC数据值失败,错误的数据类型."));		 
		}
		break;
	case Data_PR_array:
		{
			strcpy(pTagDA->DataType,_T("ARRAY"));
			int numData = responsePDU->choice.structure.list.count;
			pTagDA->nSubDANum = numData;

			if (numData>0)
			{
				ST_INT nSize = sizeof(tagDA) * numData;
				pTagDA->pSubDA = (tagDA *)malloc(nSize);
				ASSERT (pTagDA->pSubDA != NULL);

				if (pTagDA->pSubDA != NULL)
				{
					memset(pTagDA->pSubDA, 0, nSize);
					mms_InitDatas(pTagDA->pSubDA, numData);

					for (long nIndex = 0; nIndex < numData; nIndex++) 
					{
						ShowRpcValues(responsePDU->choice.structure.list.array[nIndex],&pTagDA->pSubDA[nIndex]);
					}
				}
			}
		}
		break;
	case Data_PR_structure:
		{
			strcpy(pTagDA->DataType,_T("STRUCT"));
			int numData = responsePDU->choice.structure.list.count;
			pTagDA->nSubDANum = numData;

			if (numData>0)
			{
				ST_INT nSize = sizeof(tagDA) * numData;
				pTagDA->pSubDA = (tagDA *)malloc(nSize);
				ASSERT (pTagDA->pSubDA != NULL);

				if (pTagDA->pSubDA != NULL)
				{
					memset(pTagDA->pSubDA, 0, nSize);
					mms_InitDatas(pTagDA->pSubDA, numData);

					for (long nIndex = 0; nIndex < numData; nIndex++) 
					{
						ShowRpcValues(responsePDU->choice.structure.list.array[nIndex],&pTagDA->pSubDA[nIndex]);
					}
				}
			}
		}
		break;
// 	case Data_PR_structure:
// 		{
// 			int componentCount = responsePDU->choice.structure.list.count;
// 
// 			for (long nIndex = 0; nIndex < componentCount; nIndex++) 
// 			{
// 				ShowRpcValues(responsePDU->choice.structure.list.array[nIndex]);
// 			}
// 		}
// 		break;
	case Data_PR_boolean:
		{
			strcpy(pTagDA->DataType,_T("BOOL"));
			pTagDA->DAValue.Value.u = GspMmsValue_getBoolean(responsePDU);
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Rpc数据值(%d)(BOOL)."),pTagDA->DAValue.Value.u );		 
		}
		break;
	case Data_PR_int8:
	case Data_PR_int16:
	case Data_PR_int32:
		{
			strcpy(pTagDA->DataType,_T("INT"));
			pTagDA->DAValue.Value.l = GspMmsValue_toInt32(responsePDU);
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Rpc数据值(%d)(int)."),pTagDA->DAValue.Value.l);			 
		}
		break;
	case Data_PR_float32:
		{
			strcpy(pTagDA->DataType,_T("FLOAT"));
			pTagDA->DAValue.Value.f = GspMmsValue_toFloat(responsePDU);
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Rpc数据值(%f)(float)."),pTagDA->DAValue.Value.f);	
		}
		break;
	case Data_PR_quality:
		{
			CString strTmp;
			GspMmsValue_getBitStringAsCString(responsePDU,strTmp);
			strcpy(pTagDA->DataType,_T("QUALITY"));
#ifdef _use_mms_string
            mms_str_set2(&pTagDA->DAValue.mmsName, strTmp.GetString(), strTmp.GetLength());
#else
			memcpy(pTagDA->DAValue.mmsName, strTmp, strTmp.GetLength());
#endif
            CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Rpc数据值(%s)(quality)."),strTmp.GetString());
		}
		break;
	case Data_PR_bit_string:
		{
			CString strTmp;
			GspMmsValue_getBitStringAsCString(responsePDU,strTmp);
			strcpy(pTagDA->DataType,_T("BIT_STR"));
#ifdef _use_mms_string
            mms_str_set2(&pTagDA->DAValue.mmsName, strTmp.GetString(), strTmp.GetLength());
#else
			memcpy(pTagDA->DAValue.mmsName, strTmp, strTmp.GetLength());
#endif
            CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Rpc数据值(%s)(bit_string)."),strTmp.GetString());
		}
		break;
	case Data_PR_dbpos:
		{
			CString strTmp;
			GspMmsValue_getBitStringAsCString(responsePDU,strTmp);
			strcpy(pTagDA->DataType,_T("BOOL"));

			if (strTmp == "01")
			{
				pTagDA->DAValue.Value.u = 0;
			}
			else if (strTmp == "10")
			{
				pTagDA->DAValue.Value.u = 1;
			}
			else
			{
				pTagDA->DAValue.Value.u = 0;
			}

            CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Rpc数据值(%s)(dbpos)."),strTmp.GetString());
		}
		break;	
	case Data_PR_visible_string:
		{
			CString strTmp;
			strTmp = GspMmsValue_toString(responsePDU);
			strcpy(pTagDA->DataType,_T("V_STR"));
#ifdef _use_mms_string
            mms_str_set2(&pTagDA->DAValue.mmsName, strTmp.GetString(), strTmp.GetLength());
#else
			memcpy(pTagDA->DAValue.mmsName, strTmp, strTmp.GetLength());
#endif
            CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Rpc数据值(%s)(visible_string)."),strTmp.GetString());
		}
		break;
	case Data_PR_unicode_string:
		{
			CString strTmp;
			strTmp = GspMmsValue_toString(responsePDU);
            char *pUtfValue = NULL;
            unsigned char *pGBK_Value = NULL;
            int nLength = 0;
			CString_to_char(strTmp,&pUtfValue);
            utf8_to_gbk_r((unsigned char*)pUtfValue,strTmp.GetLength(),&pGBK_Value, &nLength);

			strcpy(pTagDA->DataType,_T("UTF8_STR"));
#ifdef _use_mms_string
            mms_str_set2(&pTagDA->DAValue.mmsName, (char*)pGBK_Value, nLength);
#else
			memcpy(pTagDA->DAValue.mmsName, pGBK_Value, strlen(pGBK_Value));
#endif

			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Rpc数据值(%s)(unicode_string)."),pGBK_Value);
			delete pUtfValue;
			delete pGBK_Value;
		}
		break;
	case Data_PR_utc_time:
		{
			CString strTime1,strTime2;
			uint32_t nUtcTime = 0;
			nUtcTime = GspMmsValue_toUnixTimestamp(responsePDU);
			CTime tmValue = nUtcTime;
            strTime1 = tmValue.Format((char*)("%Y-%m-%d %H:%M:%S"));

			strcpy(pTagDA->DataType,_T("UTC_TIME"));
#ifdef _use_mms_string
            mms_str_set2(&pTagDA->DAValue.mmsName, strTime1.GetString(), strTime1.GetLength());
#else
			memcpy(pTagDA->DAValue.mmsName, strTime1, strTime1.GetLength());
#endif
            CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Rpc数据值(%s)(utc_time)."),strTime1.GetString());
		}
		break;
	default:
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("Rpc数据值未知的数据类型(%d)."),dataType);
		break;
	}
}

BOOL CRemoteDev::RpcCall(const CString &strParaFunction,const CString &strParaCallName,const CString &strParaCallID,
						 ST_INT nVersion, ST_INT nTimeout, ST_INT nRequestType, ST_INT nResponseType)
{
	// RPC调用（在上述定义中随便找一个接口进行调用）
    GspMmsValue* reqParam = GspMmsValue_newMmsString(strParaCallName.GetString());
	void* response = NULL;

	if (strParaCallID.IsEmpty())
	{
        response = Gsp_IedConnection_RPCCall(m_oConnectIED, &m_oErrorInfor, strParaFunction.GetString(), reqParam);
	} 
	else
	{
        response = Gsp_IedConnection_RPCCall(m_oConnectIED, &m_oErrorInfor, strParaFunction.GetString(), reqParam,strParaCallID.GetString());
	}

	// 调用结果判断
	if(m_oErrorInfor == GSP_IED_ERROR_OK)
	{
        XDLT_RPC_METHOD* pRpcMethod = Global_FindRpcMethod(&m_oAcsiDevice.oRpcMethods,strParaFunction.GetString());
		// 获取结果
		GspMmsValue* responsePDU = Gsp_RPCCallResPonse_getData(response);
		ASSERT(pRpcMethod);
		mms_Free_tagDA(&pRpcMethod->oDataModel);
		mms_InitData(&pRpcMethod->oDataModel);
		// 依照数据类型进行获取内部的值，和渎值接口获取出来的值一致(TODO)
		ShowRpcValues(responsePDU,&pRpcMethod->oDataModel);

		// 释放内存
		Gsp_IedConnection_FreeRPCCallPDU(response);
	} 
	else 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("RPCCall 失败."));
		return FALSE;
	}

	return TRUE;
}

BOOL CRemoteDev::StopReport(const char *pLdName,const char *pRcbItem)
{
	BOOL bRet = FALSE;
	BOOL bEnableState = FALSE;

	if ((strstr(pRcbItem,"$BR$"))||(strstr(pRcbItem,".brcb")))
	{
		if (GetBRCBValues(pLdName,pRcbItem,bEnableState))
		{
			if (bEnableState)
			{
				Gsp_BRCBControlBlk_EnableRpt(m_oCurBrcbControlBlk, FALSE);

				if(Gsp_IedConnection_SetBRCBValues(m_oConnectIED, &m_oErrorInfor, m_oCurBrcbControlBlk))
				{
					CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("报告停止成功."));
					bRet = TRUE;
				}
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("报告已经停止."));
				bRet = TRUE;
			}

			Gsp_BRCBControlBlk_Destory(m_oCurBrcbControlBlk);
			m_oCurBrcbControlBlk = NULL;
		}
	}
	else if ((strstr(pRcbItem,"$RP$"))||(strstr(pRcbItem,".urcb")))
	{
		if (GetURCBValues(pLdName,pRcbItem,bEnableState))
		{
			if (bEnableState)
			{
				Gsp_URCBControlBlk_EnableRpt(m_oCurUrcbControlBlk, FALSE);

				if(Gsp_IedConnection_SetURCBValues(m_oConnectIED, &m_oErrorInfor, m_oCurUrcbControlBlk))
				{
					CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("报告停止成功."));
					bRet = TRUE;
				}
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("报告已经停止."));
				bRet = TRUE;
			}

			Gsp_URCBControlBlk_Destory(m_oCurUrcbControlBlk);
			m_oCurUrcbControlBlk = NULL;
		}
	}
	
	return bRet;
}

BOOL CRemoteDev::WriteSEValue(const char *pLdName,tagDA *pDA)
{
	if (!IsConnecting())
	{
		if (!LinkDev())
		{
			return FALSE;
		}
	}

	if (pDA == NULL)
	{
		return FALSE;
	}

	long nErorrNum = 0;
	BOOL bRet = TRUE;

	if (strstr(pDA->DataType,"STRUCT") && pDA->pSubDA)
	{
		for (int nSubIndex=0; nSubIndex<pDA->nSubDANum;nSubIndex++)
		{
			if (!WriteSEValue(pLdName,&pDA->pSubDA[nSubIndex]))
			{
				nErorrNum++;
			}
		}

		if (nErorrNum == pDA->nSubDANum)
		{
			return FALSE;
		}
	}
	else
	{
		CString strFC,strDataRef;

		if (!GetDataRef(pLdName,mms_string(&pDA->DAValue.mmsName),strFC,strDataRef))
		{
			return FALSE;
		}

		// 写定值控制块的值
		GspLinkedList writeSgValues = GspLinkedList_create();

		// 修改 bool 类型的定值
		RefsData sgvalue = (RefsData)GspMemory_calloc(1, sizeof (sRefsData));
        sgvalue->objRefs = strDataRef.GetString();

		switch (pDA->nDataType) 
		{
		case DA_DATATYE_BOOL:
			{
				sgvalue->data = GspMmsValue_newBoolean(pDA->DAValue.Value.i);				 
			}
			break;
		case DA_DATATYE_INT:
			{
				sgvalue->data = GspMmsValue_newInteger(32);	
				sgvalue->data->choice.int32 = pDA->DAValue.Value.i;

//  				char zfBuf[4];
//  				memcpy(zfBuf,&pDA->DAValue.Value.i,4);
//  				char *pBufInt = (char *)&sgvalue->data->choice.int32;
//  				pBufInt[0] = zfBuf[3];
//  				pBufInt[1] = zfBuf[2];
//  				pBufInt[2] = zfBuf[1];
//  				pBufInt[3] = zfBuf[0];
			}
			break;
		case DA_DATATYE_UINT:
			{
				sgvalue->data = GspMmsValue_newUnsigned(32);	
				sgvalue->data->choice.int32u = pDA->DAValue.Value.i;
			}
			break;
		case DA_DATATYE_FLOAT:
			{
				sgvalue->data = GspMmsValue_newFloat(pDA->DAValue.Value.f);	
				char zfBuf[4];
				zfBuf[0] = sgvalue->data->choice.float32.buf[0];
				zfBuf[1] = sgvalue->data->choice.float32.buf[1];
				zfBuf[2] = sgvalue->data->choice.float32.buf[2];
				zfBuf[3] = sgvalue->data->choice.float32.buf[3];

				sgvalue->data->choice.float32.buf[0] = zfBuf[3];
				sgvalue->data->choice.float32.buf[1] = zfBuf[2];
				sgvalue->data->choice.float32.buf[2] = zfBuf[1];
				sgvalue->data->choice.float32.buf[3] = zfBuf[0];
			}
			break;
			// TODO 这里需要按照需求打印一些测试东西
		default:
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("写定值时,遇到未知的数据类型(%d)."),pDA->nDataType);
		}

		GspLinkedList_add(writeSgValues, sgvalue);

		// 定值修改业务流 003 -> 写定值操作
		if(!Gsp_IedConnection_SetEditSGValue(m_oConnectIED, &m_oErrorInfor, writeSgValues))
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("修改定值(%s)失败,错误码(%d)."),strDataRef.GetString(),m_oErrorInfor);
			bRet = FALSE;
		}

		GspLinkedList_destroy(writeSgValues);
	}

	return bRet;
}

BOOL CRemoteDev::WriteValue(const char *pLdName,tagDA *pDA)
{
	if (!IsConnecting())
	{
		if (!LinkDev())
		{
			return FALSE;
		}
	}

	if (pDA == NULL)
	{
		return FALSE;
	}

	long nErorrNum = 0;
	BOOL bRet = TRUE;

	if (strstr(pDA->DataType,"STRUCT") && pDA->pSubDA)
	{
		for (int nSubIndex=0; nSubIndex<pDA->nSubDANum;nSubIndex++)
		{
			if (!WriteValue(pLdName,&pDA->pSubDA[nSubIndex]))
			{
				nErorrNum++;
			}
		}

		if (nErorrNum == pDA->nSubDANum)
		{
			return FALSE;
		}

		return TRUE;
	}
	else
	{
		CString strFC,strDataRef;

		if (!GetDataRef(pLdName,mms_string(&pDA->DAValue.mmsName),strFC,strDataRef))
		{
			return FALSE;
		}

		// 写数据的值
		GspLinkedList writeDataValues = GspLinkedList_create();

		// 修改 bool 类型的定值
		RefsFcData dataRefs = (RefsFcData)GspMemory_calloc(1, sizeof (sRefsFcData));

		// fc
		dataRefs->fc = (char*)GspMemory_calloc(3, sizeof(char));
		memcpy((char*)dataRefs->fc, strFC.GetString(), 2);

		// refs
		dataRefs->objRefs = (char*)GspMemory_calloc(strDataRef.GetLength()+1, sizeof(char));
		char *pzfRef = NULL;
		CString_to_char(strDataRef,&pzfRef);
		dataRefs->objRefs = pzfRef;
//		memcpy((char*), refsList[index], strlen(strDataRef.GetLength()));

		// data
		dataRefs->data = GspMmsValue_newBoolean(true);

		switch (pDA->nDataType) 
		{
		case DA_DATATYE_BOOL:
			{
				dataRefs->data = GspMmsValue_newBoolean(pDA->DAValue.Value.i);				 
			}
			break;
		case DA_DATATYE_INT:
			{
				dataRefs->data = GspMmsValue_newInteger(32);	
				dataRefs->data->choice.int32 = pDA->DAValue.Value.i;
// 				char zfBuf[4];
// 				memcpy(zfBuf,&pDA->DAValue.Value.i,4);
// 				char *pBufInt = (char *)&dataRefs->data->choice.int32;
// 				pBufInt[0] = zfBuf[3];
// 				pBufInt[1] = zfBuf[2];
// 				pBufInt[2] = zfBuf[1];
// 				pBufInt[3] = zfBuf[0];
			}
			break;
		case DA_DATATYE_FLOAT:
			{
				dataRefs->data = GspMmsValue_newFloat(pDA->DAValue.Value.f);	
				char zfBuf[4];
				zfBuf[0] = dataRefs->data->choice.float32.buf[0];
				zfBuf[1] = dataRefs->data->choice.float32.buf[1];
				zfBuf[2] = dataRefs->data->choice.float32.buf[2];
				zfBuf[3] = dataRefs->data->choice.float32.buf[3];

				dataRefs->data->choice.float32.buf[0] = zfBuf[3];
				dataRefs->data->choice.float32.buf[1] = zfBuf[2];
				dataRefs->data->choice.float32.buf[2] = zfBuf[1];
				dataRefs->data->choice.float32.buf[3] = zfBuf[0];
			}
			break;
			// TODO 这里需要按照需求打印一些测试东西
		default:
			return FALSE;
//			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("写数据时,遇到未知的数据类型(%d)."),pDA->nDataType);
		}

		// 添加到列表
		GspLinkedList_add(writeDataValues, dataRefs);

		// 请求数据
		GspLinkedList resultList = Gsp_IedConnection_SetDataValues(m_oConnectIED, &m_oErrorInfor, writeDataValues);

		if(!resultList)//zhouhj 20211201 接口部分还有问题,暂时默认修改成功
		{
			// 设置数据失败处理
//			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("写数据失败(%s)."),strDataRef);

			// 释放内存
			GspLinkedList_destroyStatic(writeDataValues);
			// 释放内存
			GspLinkedList_destroyStatic(resultList);
			return TRUE;
		}
		// 释放数据内存
		GspLinkedList_destroyStatic(resultList);
		// 释放参数内存
		GspLinkedList_destroyStatic(writeDataValues);
		return TRUE;
	}
}

BOOL CRemoteDev::Get_Nodes_Detail()
{
	int j = 0;

	for (j=0; j<m_oAcsiDevice.numLD; j++)
	{
		LD_NODE*pLD = &m_oAcsiDevice.LD[j];
		MMS_DATA_NODE *head_ln_data_node = pLD->mms_data_node;
		MMS_DATA_NODE *ln_data_node = head_ln_data_node;
		CStringArray straDatas;
		CString strData;

		CString strLDName = pLD->LDName;
		strLDName.MakeUpper();

		do 
		{
			if (ln_data_node == NULL)
			{
				break;
			}

			MMS_DATA_NODE *head_co = ln_data_node->pFirstChild;
			MMS_DATA_NODE *co_node = head_co;

			do 
			{
				if (co_node == NULL)
				{
					break;
				}

				if (g_o61850ClientConfig.m_nUseDsDout)//在添加控制类信号数据集的情况下,进行如下操作
				{
#ifdef _use_mms_string
					if (strcmp(mms_string(&co_node->name),"CO") == 0)
#else
					if (strcmp(co_node->name, "CO") == 0)
#endif
					{
						MMS_DATA_NODE *head_da = co_node->pFirstChild;
						MMS_DATA_NODE *da_node = head_da;

						do 
						{
							if (da_node == NULL)
							{
								break;
							}

							strData.Format("%s$ST$%s",mms_string(&ln_data_node->name),mms_string(&da_node->name));//zhouhj20190102设置dsDout数据集中的FC类型
							straDatas.Add(strData);

							da_node = da_node->pNext;
						} while (da_node != head_da);
					}
				}

				co_node = co_node->pNext;
			} while (co_node != head_co);

			ln_data_node = ln_data_node->pNext;
		} while (ln_data_node != head_ln_data_node);

		if (g_o61850ClientConfig.m_nUseDsDout)
		{
			int nSize = straDatas.GetSize();
			long nDatasetIndex = pLD->numDaSet-1;
			mms_New_LD_DATASET_INFO_numData(&pLD->DataInfo[nDatasetIndex],nSize );

			for (int nCount = 0; nCount < nSize; ++nCount)
			{
				mms_str_set(&pLD->DataInfo[nDatasetIndex].DataSet[nCount].DAValue.mmsName,
                    straDatas.GetAt(nCount).GetString());
			}
		}
	}

	return TRUE;
}

ST_INT GetDAValue_stValue(tagDA *pSbDA, ST_INT nNum,long &nDataType)
{
	ST_INT k;
	CString strTmp;

	for (k=0;k<nNum;k++)
	{
		if (mms_Is_SubDA_Value(pSbDA))
		{
			nDataType = pSbDA->nDataType;

			if (pSbDA->nDataType == DA_DATATYE_BIT_STR)
			{
				long nValue = 0;
				strTmp = mms_string(&pSbDA->DAValue.Value.string);
				nValue = CString_To_long(strTmp);

				if (nValue == 11)
				{
					nValue = 3;
				}
				else if (nValue == 10)
				{
					nValue = 2;
				}
				else if (nValue>3)
				{
					nValue = 0;
                    CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前位串值错误(%s),强制置为0."),strTmp.GetString());
				}

				return nValue;
			}
			else
			{
				return pSbDA->DAValue.Value.u;
			}
		}

		pSbDA++;
	}

	return 0;
}

BOOL CRemoteDev::CtrlWriteDA_SWV_Oper(const char *pLdName,tagDA *pDA,FIRE_CMD_MSG_FUNC pFunc,DWORD pFuncParaEx)
{
	if (!IsConnecting())
	{
		if (!LinkDev())
		{
			return FALSE;
		}
	}

	if (pDA==NULL)
		return FALSE;

	if (!pDA->bModify)
		return FALSE;

	if (strstr(pDA->DataType,"STRUCT") && pDA->pSubDA != NULL)
	{
		BOOL bRet = TRUE;
		CString strRef;
		strRef.Format(_T("%s/%s"),pLdName,mms_string(&pDA->DAValue.mmsName));
		strRef.Replace(_T("$CO$"),_T("$"));
		strRef.Replace(_T("$ST$"),_T("$"));
		strRef.Replace(_T("$"),_T("."));
		long nDataType =  DA_DATATYE_BOOL;
		long nValue = GetDAValue_stValue(pDA->pSubDA, pDA->nSubDANum,nDataType);

		// 创建控制对象
        GspControlObjectClient sboControl = Gsp_ControlObjectClient_Create(strRef.GetString(), m_oConnectIED);
		Gsp_ControlObjectClient_SetTestMode(sboControl,g_o61850ClientConfig.HasCtrlTest());
		Gsp_ControlObjectClient_SetSyncCheck(sboControl,g_o61850ClientConfig.HasCtrlSynCheck());
// 		Gsp_ControlObjectClientInit(sboControl,g_o61850ClientConfig.HasCtrlTest(),g_o61850ClientConfig.HasCtrlSynCheck(),
// 			g_o61850ClientConfig.HasCtrlInterlockCheck(),g_o61850ClientConfig.HasTimeActived());
		// 设置值
		GspMmsValue* ctlVal = NULL;

		if (nDataType == DA_DATATYE_BIT_STR)
		{
			if (nValue>1)
			{
				ctlVal = GspMmsValue_newBoolean(1);
			}
			else
			{
				ctlVal = GspMmsValue_newBoolean(0);
			}
// 			ctlVal = GspMmsValue_newBitString(2);
// 			GspMmsValue_setBitStringFromIntegerBigEndian(ctlVal, nValue);
		}
		else if (nDataType == DA_DATATYE_INT)
		{
// 			if (nValue>0)
// 			{
// 				ctlVal = GspMmsValue_newBoolean(1);
// 			}
// 			else
// 			{
// 				ctlVal = GspMmsValue_newBoolean(0);
// 			}
 			ctlVal = GspMmsValue_newBitString(2);
 			GspMmsValue_setBitStringFromIntegerBigEndian(ctlVal, nValue);
 //			ctlVal->choice.tcmd;
 			ctlVal->present = Data_PR_tcmd;
		}
		else
		{
			ctlVal = GspMmsValue_newBoolean(nValue);
		}

		CGpsPcTimeTickCount oTickCount32;
		oTickCount32.Enter();
		// 设置origin
		Gsp_ControlObjectClient_SetOriginator(sboControl, Originator__orCat_remoteControl, "test");

		if (pFunc != NULL)
		{
			pFunc(pFuncParaEx, 0); 
		}

		if(Gsp_IedConnection_SelectWithValue(sboControl,&m_oErrorInfor,ctlVal))
		{
			sprintf(m_oAcsiDevice.InfoSel
				, _T("选择压板【%s】【%d】成功"), strRef.GetString(), nValue);

			if (pFunc != NULL)
			{
				pFunc(pFuncParaEx, 1); 
			}

			m_oAcsiDevice.tmSel = oTickCount32.GetTickCountLong(TRUE);
			oTickCount32.Enter();
			::GetLocalTime(&m_oAcsiDevice.tmStartExc);

			if (pFunc != NULL)
			{
				pFunc(pFuncParaEx, 2); 
			}
			// 控制
			if(!Gsp_IedConnection_Operate(sboControl,&m_oErrorInfor, ctlVal, 0))
			{
				bRet = FALSE;
				sprintf(m_oAcsiDevice.InfoExec
					, _T("执行压板【%s】【%d】失败"), strRef.GetString(), nValue);
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%s"),m_oAcsiDevice.InfoExec);
			}
			else
			{
				sprintf(m_oAcsiDevice.InfoExec
					, _T("执行压板【%s】【%d】成功"),strRef.GetString(), nValue);
			}

// 			{
// 				bRet = FALSE;
// 				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("(%s)执行控制写失败(%d)."), strRef.GetString(),m_oErrorInfor);
// 			} 

			m_oAcsiDevice.tmExec = oTickCount32.GetTickCountLong();
			m_oAcsiDevice.tmTotal = m_oAcsiDevice.tmExec + m_oAcsiDevice.tmSel;

			if (pFunc != NULL)
			{
				pFunc(pFuncParaEx, 3); 
			}

			// 内存释放
//			GspMmsValue_delete(ctlVal);
		}
		else
		{
			bRet = FALSE;
			sprintf(m_oAcsiDevice.InfoSel
				, _T("选择压板【%s】【%d】失败"), strRef.GetString(), nValue);
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("(%s)执行选择操作失败(%d)."), strRef.GetString(),m_oErrorInfor);
		}

		// 资源释放
		Gsp_ControlObjectClient_Destroy(sboControl);
		return bRet;
	}
	else
	{
		return FALSE;
	}
}

BOOL CRemoteDev::CtrlWriteDA_SWV_Oper(const char *pLdName,tagDA *pDA,tagDA *pDA2,ST_INT iValue,ST_INT iValue2,ST_INT nTDelayAfterSel,FIRE_CMD_MSG_FUNC pFunc,DWORD pFuncParaEx)
{
	if (!IsConnecting())
	{
		if (!LinkDev())
		{
			return FALSE;
		}
	}

	if (pDA==NULL)
		return FALSE;

	if (pDA2==NULL)
		return FALSE;

	BOOL bRet = TRUE;
	CString strSelRef,strOperRef;
	strSelRef.Format(_T("%s/%s"),pLdName,mms_string(&pDA->DAValue.mmsName));
	strSelRef.Replace(_T("$CO$"),_T("$"));
	strSelRef.Replace(_T("$ST$"),_T("$"));
	strSelRef.Replace(_T("$"),_T("."));

	strOperRef.Format(_T("%s/%s"),pLdName,mms_string(&pDA2->DAValue.mmsName));
	strOperRef.Replace(_T("$CO$"),_T("$"));
	strOperRef.Replace(_T("$ST$"),_T("$"));
	strOperRef.Replace(_T("$"),_T("."));

	// 创建控制对象
    GspControlObjectClient pSelControl = Gsp_ControlObjectClient_Create(strSelRef.GetString(), m_oConnectIED);
 	Gsp_ControlObjectClient_SetTestMode(pSelControl,g_o61850ClientConfig.HasCtrlTest());
 	Gsp_ControlObjectClient_SetSyncCheck(pSelControl,g_o61850ClientConfig.HasCtrlSynCheck());
// 	Gsp_ControlObjectClient_SetLockCheck(pSelControl,g_o61850ClientConfig.HasCtrlInterlockCheck());
// 	Gsp_ControlObjectClient_SetLockCheck(pSelControl,g_o61850ClientConfig.HasCtrlInterlockCheck());
//	Gsp_ControlObjectClientInit(pSelControl,g_o61850ClientConfig.HasCtrlTest(),g_o61850ClientConfig.HasCtrlSynCheck(),
//		g_o61850ClientConfig.HasCtrlInterlockCheck(),g_o61850ClientConfig.HasTimeActived());
	// 设置值
	long nDataType =  DA_DATATYE_BOOL;
	GetDAValue_stValue(pDA->pSubDA, pDA->nSubDANum,nDataType);
	GspMmsValue* ctlVal = NULL;

	if (nDataType == DA_DATATYE_BIT_STR)
	{
		if (iValue>1)
		{
			ctlVal = GspMmsValue_newBoolean(1);
		}
		else
		{
			ctlVal = GspMmsValue_newBoolean(0);
		}
//		ctlVal = GspMmsValue_newBoolean(2);
//		ctlVal = GspMmsValue_newBitString(2);
//		GspMmsValue_setBitStringFromIntegerBigEndian(ctlVal, iValue);
	}
	else if (nDataType == DA_DATATYE_INT)
	{
		ctlVal = GspMmsValue_newBitString(2);
		GspMmsValue_setBitStringFromIntegerBigEndian(ctlVal, iValue);
		//			ctlVal->choice.tcmd;
		ctlVal->present = Data_PR_tcmd;
	}
	else
	{
		ctlVal = GspMmsValue_newBoolean(iValue);
	}

	CGpsPcTimeTickCount oTickCount32;
	oTickCount32.Enter();
	// 设置origin
	Gsp_ControlObjectClient_SetOriginator(pSelControl, Originator__orCat_remoteControl, "test");

	if (pFunc != NULL)
	{
		pFunc(pFuncParaEx, 0); 
	}

	if(Gsp_IedConnection_SelectWithValue(pSelControl,&m_oErrorInfor,ctlVal))
	{
		sprintf(m_oAcsiDevice.InfoSel
			, _T("选择压板【%s】【%d】成功"), strSelRef.GetString(), iValue);
		if (pFunc != NULL)
		{
			pFunc(pFuncParaEx, 1); 
		}

		m_oAcsiDevice.tmSel = oTickCount32.GetTickCountLong(TRUE);

		if (nTDelayAfterSel>0)
		{
			Sleep(nTDelayAfterSel);
		}

		oTickCount32.Enter();
        Gsp_ControlObjectClient_SetControlRefs(pSelControl, strOperRef.GetString());
//		GspControlObjectClient pOperControl = Gsp_ControlObjectClient_Create(strOperRef, m_oConnectIED);
		Gsp_ControlObjectClient_SetTestMode(pSelControl,g_o61850ClientConfig.HasCtrlTest());
		Gsp_ControlObjectClient_SetSyncCheck(pSelControl,g_o61850ClientConfig.HasCtrlSynCheck());
// 		Gsp_ControlObjectClientInit(pOperControl,g_o61850ClientConfig.HasCtrlTest(),g_o61850ClientConfig.HasCtrlSynCheck(),
// 			g_o61850ClientConfig.HasCtrlInterlockCheck(),g_o61850ClientConfig.HasTimeActived());

		GetDAValue_stValue(pDA2->pSubDA, pDA2->nSubDANum,nDataType);

		if (nDataType == DA_DATATYE_BIT_STR)
		{
			if (iValue2>1)
			{
				ctlVal = GspMmsValue_newBoolean(1);
			}
			else
			{
				ctlVal = GspMmsValue_newBoolean(0);
			}
// 			ctlVal = GspMmsValue_newBitString(2);
// 			GspMmsValue_setBitStringFromIntegerBigEndian(ctlVal, iValue2);
		} 
		else if (nDataType == DA_DATATYE_INT)
		{
			ctlVal = GspMmsValue_newBitString(2);
			GspMmsValue_setBitStringFromIntegerBigEndian(ctlVal, iValue2);
			//			ctlVal->choice.tcmd;
			ctlVal->present = Data_PR_tcmd;
		}
		else
		{
			ctlVal = GspMmsValue_newBoolean(iValue2);
		}

		::GetLocalTime(&m_oAcsiDevice.tmStartExc);

		if (pFunc != NULL)
		{
			pFunc(pFuncParaEx, 2); 
		}
		// 控制
		if(!Gsp_IedConnection_Operate(pSelControl,&m_oErrorInfor, ctlVal, 0))
		{
			bRet = FALSE;
			sprintf(m_oAcsiDevice.InfoExec
				, _T("执行压板【%s】【%d】失败"), strOperRef.GetString(), iValue2);
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%s"),m_oAcsiDevice.InfoExec);
		}
		else
		{
			sprintf(m_oAcsiDevice.InfoExec
				, _T("执行压板【%s】【%d】成功"),strOperRef.GetString(), iValue2);
		}

// 		{
// 			bRet = FALSE;
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("(%s)执行控制写失败(%d)."), strOperRef.GetString(),m_oErrorInfor);
// 		} 

		m_oAcsiDevice.tmExec = oTickCount32.GetTickCountLong();
		m_oAcsiDevice.tmTotal = m_oAcsiDevice.tmExec + m_oAcsiDevice.tmSel;

		if (pFunc != NULL)
		{
			pFunc(pFuncParaEx, 3); 
		}
		// 资源释放
		Gsp_ControlObjectClient_Destroy(pSelControl);
	}
	else
	{
		bRet = FALSE;
		sprintf(m_oAcsiDevice.InfoSel
			, _T("选择压板【%s】【%d】失败"), strSelRef.GetString(), iValue);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("(%s)执行选择操作失败(%d)."), strSelRef.GetString(),m_oErrorInfor);
		// 资源释放
		Gsp_ControlObjectClient_Destroy(pSelControl);
	}

	return bRet;
}

BOOL CRemoteDev::CtrlWriteDA_SBO_Oper(const char *pLdName,tagDA *pDA,FIRE_CMD_MSG_FUNC pFunc,DWORD pFuncParaEx)
{
	if (!IsConnecting())
	{
		if (!LinkDev())
		{
			return FALSE;
		}
	}

	if (pDA==NULL)
		return FALSE;

	if (!pDA->bModify)
		return FALSE;

	if (strstr(pDA->DataType,"STRUCT") && pDA->pSubDA != NULL)
	{
		BOOL bRet = TRUE;
		CString strRef;
		strRef.Format(_T("%s/%s"),pLdName,mms_string(&pDA->DAValue.mmsName));
		strRef.Replace(_T("$CO$"),_T("$"));
		strRef.Replace(_T("$ST$"),_T("$"));
		strRef.Replace(_T("$"),_T("."));
		long nDataType =  DA_DATATYE_BOOL;
		long nValue = GetDAValue_stValue(pDA->pSubDA, pDA->nSubDANum,nDataType);

		// 创建控制对象
        GspControlObjectClient sboControl = Gsp_ControlObjectClient_Create(strRef.GetString(), m_oConnectIED);
		Gsp_ControlObjectClient_SetTestMode(sboControl,g_o61850ClientConfig.HasCtrlTest());
		Gsp_ControlObjectClient_SetSyncCheck(sboControl,g_o61850ClientConfig.HasCtrlSynCheck());
// 		Gsp_ControlObjectClientInit(sboControl,g_o61850ClientConfig.HasCtrlTest(),g_o61850ClientConfig.HasCtrlSynCheck(),
// 			g_o61850ClientConfig.HasCtrlInterlockCheck(),g_o61850ClientConfig.HasTimeActived());
		CGpsPcTimeTickCount oTickCount32;
		oTickCount32.Enter();

		if (pFunc != NULL)
		{
			pFunc(pFuncParaEx, 0); 
		}

		if(Gsp_IedConnection_Select(sboControl,&m_oErrorInfor))
		{
			sprintf(m_oAcsiDevice.InfoSel
				, _T("选择压板【%s】【%d】成功"), strRef.GetString(), nValue);
			m_oAcsiDevice.tmSel = oTickCount32.GetTickCountLong(TRUE);

			if (pFunc != NULL)
			{
				pFunc(pFuncParaEx, 1); 
			}
			// 设置值
			GspMmsValue* ctlVal = NULL;

			if (nDataType == DA_DATATYE_BIT_STR)
			{
				if (nValue>1)
				{
					ctlVal = GspMmsValue_newBoolean(1);
				}
				else
				{
					ctlVal = GspMmsValue_newBoolean(0);
				}
// 				ctlVal = GspMmsValue_newBitString(2);
// 				GspMmsValue_setBitStringFromIntegerBigEndian(ctlVal, nValue);
			}
			else if (nDataType == DA_DATATYE_INT)
			{
				ctlVal = GspMmsValue_newBitString(2);
				GspMmsValue_setBitStringFromIntegerBigEndian(ctlVal, nValue);
				//			ctlVal->choice.tcmd;
				ctlVal->present = Data_PR_tcmd;
			}
			else
			{
				ctlVal = GspMmsValue_newBoolean(nValue);
			}

			// 设置origin
			Gsp_ControlObjectClient_SetOriginator(sboControl, Originator__orCat_remoteControl, "test");
			oTickCount32.Enter();

			::GetLocalTime(&m_oAcsiDevice.tmStartExc);

			if (pFunc != NULL)
			{
				pFunc(pFuncParaEx, 2); 
			}
			// 控制
			if(!Gsp_IedConnection_Operate(sboControl,&m_oErrorInfor, ctlVal, 0))
			{
				bRet = FALSE;
				sprintf(m_oAcsiDevice.InfoExec
					, _T("执行压板【%s】【%d】失败"), strRef.GetString(), nValue);
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%s"),m_oAcsiDevice.InfoExec);
			}
			else
			{
				sprintf(m_oAcsiDevice.InfoExec
					, _T("执行压板【%s】【%d】成功"),strRef.GetString(), nValue);
			}

			m_oAcsiDevice.tmExec = oTickCount32.GetTickCountLong();
			m_oAcsiDevice.tmTotal = m_oAcsiDevice.tmExec + m_oAcsiDevice.tmSel;

			if (pFunc != NULL)
			{
				pFunc(pFuncParaEx, 3); 
			}
			// 内存释放
//			GspMmsValue_delete(ctlVal);
		}
		else
		{
			bRet = FALSE;
			sprintf(m_oAcsiDevice.InfoSel
				, _T("选择压板【%s】【%d】失败"), strRef.GetString(), nValue);
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("(%s)执行选择操作失败(%d)."), strRef.GetString(),m_oErrorInfor);
		}

		// 资源释放
		Gsp_ControlObjectClient_Destroy(sboControl);
		return bRet;
	}
	else
	{
		return FALSE;
	}
}

BOOL CRemoteDev::CtrlWriteDA_Direct(const char *pLdName,tagDA *pDA)
{
	if (!IsConnecting())
	{
		if (!LinkDev())
		{
			return FALSE;
		}
	}

	if (pDA==NULL)
		return FALSE;

	if (!pDA->bModify)
		return FALSE;

	if (strstr(pDA->DataType,"STRUCT") && pDA->pSubDA != NULL)
	{
		CString strRef;
		strRef.Format(_T("%s/%s"),pLdName,mms_string(&pDA->DAValue.mmsName));
		strRef.Replace(_T("$ST$"),_T("$"));
		strRef.Replace(_T("$"),_T("."));
		long nValue = 0;

		long nDataType =  DA_DATATYE_BOOL;
		nValue = GetDAValue_stValue(pDA->pSubDA, pDA->nSubDANum,nDataType);
		// 设置值
		GspMmsValue* ctlVal = NULL;

		if (nDataType == DA_DATATYE_BIT_STR)
		{
			if (nValue>1)
			{
				ctlVal = GspMmsValue_newBoolean(1);
			}
			else
			{
				ctlVal = GspMmsValue_newBoolean(0);
			}
// 			ctlVal = GspMmsValue_newBitString(2);
// 			GspMmsValue_setBitStringFromIntegerBigEndian(ctlVal, nValue);
		} 
		else
		{
			ctlVal = GspMmsValue_newBoolean(nValue);
		}

		return CtrlWriteDA_Direct(strRef,ctlVal);
	}
	else
	{
		return FALSE;
	}
}

BOOL CRemoteDev::CtrlWriteDA_Direct(const CString &strRef,GspMmsValue* ctlVal)
{
	if (!IsConnecting())
	{
		if (!LinkDev())
		{
			return FALSE;
		}
	}

	BOOL bRet = TRUE;
	// 创建控制对象
    GspControlObjectClient directControl = Gsp_ControlObjectClient_Create(strRef.GetString(), m_oConnectIED);
	Gsp_ControlObjectClient_SetTestMode(directControl,g_o61850ClientConfig.HasCtrlTest());
	Gsp_ControlObjectClient_SetSyncCheck(directControl,g_o61850ClientConfig.HasCtrlSynCheck());
// 	Gsp_ControlObjectClientInit(directControl,g_o61850ClientConfig.HasCtrlTest(),g_o61850ClientConfig.HasCtrlSynCheck(),
// 		g_o61850ClientConfig.HasCtrlInterlockCheck(),g_o61850ClientConfig.HasTimeActived());

	// 设置origin
	Gsp_ControlObjectClient_SetOriginator(directControl, Originator__orCat_remoteControl, "test");

	::GetLocalTime(&m_oAcsiDevice.tmStartExc);
	// 控制
	if(!Gsp_IedConnection_Operate(directControl,&m_oErrorInfor, ctlVal, 0))
	{
		bRet = FALSE;
		sprintf(m_oAcsiDevice.InfoExec
			, _T("执行压板【%s】【%d】失败"), strRef.GetString(), ctlVal->choice.boolean);
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%s"),m_oAcsiDevice.InfoExec);
	}
	else
	{
		sprintf(m_oAcsiDevice.InfoExec
			, _T("执行压板【%s】【%d】成功"),strRef.GetString(), ctlVal->choice.boolean);
	}

// 	{
// 		bRet = FALSE;
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("(%s)控制写失败(%d)."), strRef.GetString(),m_oErrorInfor);
// 	} 

	// 内存释放
	Gsp_ControlObjectClient_Destroy(directControl);
	return bRet;
}

BOOL CRemoteDev::GetDataRef(const char *pLdName,const char *pMmsDataRef,CString &strFC,CString &strDataRef)
{
	CString strTmp,strTmp2;;
	strTmp = pMmsDataRef;
	long nIndex = strTmp.Find(_T("$"));

	if (nIndex<=0)
	{
		return FALSE;
	}

    strDataRef.Format(_T("%s/%s"),pLdName,strTmp.Left(nIndex).GetString());
	strTmp2 = strTmp.Mid(nIndex+1);

	nIndex = strTmp2.Find(_T("$"));

	if (nIndex<=0)
	{
		return FALSE;
	}

	strFC = strTmp2.Left(nIndex);
    strDataRef += strTmp2.Mid(nIndex);
	strDataRef.Replace(_T("$"),_T("."));
	return TRUE;
}

BOOL CRemoteDev::SetEditSG(const long &nLdIndex,const long &nSE)
{
	if (!IsConnecting()||(m_oAcsiDevice.numLD<=nLdIndex))
	{
		return FALSE;
	}

	// 选择编辑定制组
	ST_CHAR sgcbRefs[NAMESIZE+1];
	ZeroMemory(sgcbRefs,NAMESIZE+1);
	_snprintf(sgcbRefs, NAMESIZE-1, "%s/LLN0.SGCB", m_oAcsiDevice.LD[nLdIndex].LDName);
	bool ret = Gsp_IedConnection_SelectEditSG(m_oConnectIED, &m_oErrorInfor, sgcbRefs, nSE);

	// 调试信息
	if(ret)
	{
		m_oAcsiDevice.nEditSGIndex = nSE;
		sprintf(m_oAcsiDevice.InfoSetSE
			, _T("【%d】设置当前编辑区【%d】成功")
			, GetDeviceIndex(), nSE);
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("选择编辑定值区成功,切换到 %d 区."), nSE);
		return TRUE;
	} 
	else 
	{
		sprintf(m_oAcsiDevice.InfoSetSE
			, _T("【%d】设置当前编辑区【%d】失败.")
			, GetDeviceIndex(), nSE);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("选择编辑定值区失败,切换到 %d 区失败, 错误代码: %d."),nSE, m_oErrorInfor);
		return FALSE;
	}
}

LD_DATASET_INFO* GetDatasetStruct(LD_NODE *pLD,CString &strDatasetPath)//参数2的字符串被修改为不含LD的数据集名称
{
	if (pLD == NULL)
	{
		return NULL;
	}

	CString strDataset;
	strDataset = strDatasetPath;
	long nIndex = strDatasetPath.Find("/");

	if (nIndex != -1)
	{
		strDataset = strDatasetPath.Mid(nIndex+1);
	}

	for (nIndex = 0; nIndex< pLD->numDaSet;nIndex++)
	{
        if (strcmp(pLD->DataInfo[nIndex].DataSetID,strDataset.GetString()) == 0)
		{
			strDatasetPath = strDataset;
			return &pLD->DataInfo[nIndex];
		}
	}

	return NULL;
}

LD_LOG_INFO* GetLD_LOG_INFO_ByDataset(LD_NODE *pLD,CString &strDatasetPath)//参数2的字符串被修改为不含LD的数据集名称
{
	if (pLD == NULL)
	{
		return NULL;
	}

	if (pLD->JournalCtrls.LogInfo == NULL)
	{
		return NULL;
	}

	LD_LOG_INFO *pLogInfor = NULL;

	for (long nIndex = 0; nIndex < pLD->JournalCtrls.numData;nIndex++)
	{
        if (strcmp(mms_string(&pLD->JournalCtrls.LogInfo[nIndex].Dataset),strDatasetPath.GetString()) == 0)
		{
			return &pLD->JournalCtrls.LogInfo[nIndex];
		}
	}

	return NULL;
}

BOOL CRemoteDev::GetRptLogCB_GetAllCBValues(LD_NODE *pLD,long nGSP_ACSIClass)
{
	// 获取 所有控制块数据
	char zsGetCBRef[NAMESIZE];
	ZeroMemory(zsGetCBRef,NAMESIZE);
	_snprintf(zsGetCBRef, NAMESIZE-1, "%s/LLN0", pLD->LDName);

	GspLinkedList allCBDataValue = Gsp_IedConnection_GetAllCBValues(m_oConnectIED, &m_oErrorInfor, (GspACSICLASS)nGSP_ACSIClass, zsGetCBRef, LNREFERENCE);

	// 获取数据并打印 测试
	if(allCBDataValue)
	{
		CString strCBRef,strDatasetPath,strRptID;
		LD_DATASET_INFO			*pDatasetInfo = NULL;
		deque<void *> dObj = *allCBDataValue;


		for(deque<void *>::const_iterator itObj = dObj.begin(); itObj != dObj.end(); itObj++)/*for(auto &item : *allCBDataValue)*/

		{
			GetAllCBValuesResponsePDU_t * dataItem = (GetAllCBValuesResponsePDU_t*)*itObj;/*item*///;

			// 逐条解析
			for(int i=0; i< dataItem->cbValue.list.count; ++i)
			{

				// 获取数据
				GetAllCBValuesResponsePDU__cbValue__Member* item = dataItem->cbValue.list.array[i];
				strCBRef.Format(_T("LLN0.%s"),item->reference.buf);
// 				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,"************************** 控制块值测试(数据条目 %d/%d) ****************.", i+1, dataItem->cbValue.list.count);
// 				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,"控制块的 refs: %s \n", item->reference.buf);

				switch(item->value.present)
				{
				case GetAllCBValuesResponsePDU__cbValue__Member__value_PR_brcb:
					{
						// 打印测试
						BRCB_t itemData = item->value.choice.brcb;
                        strDatasetPath = (char*)itemData.datSet.buf;
						pDatasetInfo = GetDatasetStruct(pLD,strDatasetPath);

						if (pDatasetInfo != NULL)
						{
							if (pDatasetInfo->numRcb>=MAX_RCB_VMD)
							{
								CLogPrint::LogFormatString(XLOGLEVEL_INFOR,"当前报告控制块路径%s,数据集%s,对应的报告数据数量%d,超过最大报告数据数量.",
									strCBRef.GetString(),strDatasetPath.GetString(),pDatasetInfo->numRcb);
								break;
							}

							strRptID = (char*)itemData.rptID.buf;
							strRptID.Replace(_T("$BR$"),_T("."));
                            strcpy(pDatasetInfo->RCB[pDatasetInfo->numRcb].dsName,strDatasetPath.GetString());
                            strcpy(pDatasetInfo->RCB[pDatasetInfo->numRcb].rcbName,strCBRef.GetString());
                            strcpy(pDatasetInfo->RCB[pDatasetInfo->numRcb].RptID,strRptID.GetString());
							pDatasetInfo->numRcb++;
						}
					} 
					break;
				case GetAllCBValuesResponsePDU__cbValue__Member__value_PR_urcb: 
					{
					// 打印测试
						URCB_t itemData = item->value.choice.urcb;
                        strDatasetPath = (char*)itemData.datSet.buf;
						pDatasetInfo = GetDatasetStruct(pLD,strDatasetPath);

						if (pDatasetInfo != NULL)
						{
							if (pDatasetInfo->numRcb>=MAX_RCB_VMD)
							{
								CLogPrint::LogFormatString(XLOGLEVEL_INFOR,"当前报告控制块路径%s,数据集%s,对应的报告数据数量%d,超过最大报告数据数量.",
									strCBRef.GetString(),strDatasetPath.GetString(),pDatasetInfo->numRcb);
								break;
							}

							strRptID = (char*)itemData.rptID.buf;
							strRptID.Replace(_T("$RP$"),_T("."));
                            strcpy(pDatasetInfo->RCB[pDatasetInfo->numRcb].dsName,strDatasetPath.GetString());
                            strcpy(pDatasetInfo->RCB[pDatasetInfo->numRcb].rcbName,strCBRef.GetString());
                            strcpy(pDatasetInfo->RCB[pDatasetInfo->numRcb].RptID,strRptID.GetString());
							pDatasetInfo->numRcb++;
						}
																				
					} 
					break;
				case GetAllCBValuesResponsePDU__cbValue__Member__value_PR_lcb: 
					{
					// 打印测试
						LCB_t itemData = item->value.choice.lcb;
						strCBRef.Format(_T("LLN0$%s"),item->reference.buf);
						strCBRef.Replace(_T("$LG$"),_T("."));
						strCBRef.Replace(_T("$"),_T("."));
						strDatasetPath.Format(_T("LLN0$%s"),itemData.datSet.buf);
						LD_LOG_INFO* pLogInfor = GetLD_LOG_INFO_ByDataset(pLD,strDatasetPath);

						if ((pLogInfor != NULL)&&(pLD->JournalCtrls.LogInfo != NULL))
						{
//							mms_str_set(&pLogInfor->Dataset,strDatasetPath);
                            mms_str_set(&pLogInfor->Name,strCBRef.GetString());
							mms_str_set(&pLogInfor->logRef,(char*)itemData.logRef.buf);
						}
																			   
					} 
					break;
				case GetAllCBValuesResponsePDU__cbValue__Member__value_PR_sgcb: {
					// 打印测试
					SGCB_t itemData = item->value.choice.sgcb;
																				} break;
				case GetAllCBValuesResponsePDU__cbValue__Member__value_PR_gocb: {
					// 打印测试
					GoCB_t itemData = item->value.choice.gocb;
																				} break;
				case GetAllCBValuesResponsePDU__cbValue__Member__value_PR_msvcb: {
					// 打印测试
					MSVCB_t itemData = item->value.choice.msvcb;
																				 } break;
				default:
					break;
				}
			}

			// 内存释放
			Gsp_FreeAllCBValue(dataItem);
		}
		// 内存释放
		GspLinkedList_destroyStatic(allCBDataValue);
	}

	return TRUE;
}

ST_RET CRemoteDev::node_get_DataDescInfo(LD_NODE *pLD, tagDA*pDA)
{
	ST_INT ret = SD_FAILURE;
	ASSERT(pDA!=NULL);

	if (mms_str_length(&pDA->DADescri.mmsName) > 0)
	{
		CString strDataRef,strDescValue;
		strDataRef.Format(_T("%s/%s"),pLD->LDName,mms_string(&pDA->DADescri.mmsName));
		strDataRef.Replace(_T("$DC$"),_T("."));
		strDataRef.Replace(_T("$"),_T("."));
		GspLinkedList pRptDataList = ReadValue(strDataRef,_T("DC"));

		if (pRptDataList == NULL)
		{
			return SD_FAILURE;
		}

		void* item = GspLinkedList_get(pRptDataList, 0);
		Data* dataInfo = static_cast<Data*>(item);

		if (GetGspValue_String(dataInfo,strDescValue))
		{
			char *pDescValue = NULL;
			CString_to_char(strDescValue,&pDescValue);
			mms_str_set(&pDA->DADescri.Value.string, pDescValue);
			delete pDescValue;
		}
		
		// 释放元素值
		GspMmsValue_delete(dataInfo);
		GspLinkedList_destroyStatic(pRptDataList);
	}

	return ret;
}

ST_RET CRemoteDev::node_get_DataLimitValInfoAll(LD_NODE *pLD, tagDA*pDA)
{
	ST_RET ret = 0;

	//min value
	ret = node_get_DataLimitValInfo(pLD, pDA, 0);

	//max value
	ret = node_get_DataLimitValInfo(pLD, pDA, 1);

	//stepsize value
	ret = node_get_DataLimitValInfo(pLD, pDA, 2);

	//unit value
	ret = node_get_DataLimitValInfo(pLD, pDA, 3);

	return ret;
}

ST_RET CRemoteDev::node_get_DataLimitValInfo(LD_NODE *pLD,tagDA*pDA, ST_INT nLimitKind)
{
	ST_INT ret = SD_FAILURE;
	ST_INT Type_id = -1;
	CString strDataRef,strFC;

#ifdef tagDA_use_UNIT_MIN_MAX_STEP
	ASSERT(pDA!=NULL);

	if ((nLimitKind == 0)&&(mms_str_length(&pDA->MinVal.mmsName)>0))
	{
		strDataRef.Format(_T("%s/%s"),pLD->LDName,mms_string(&pDA->MinVal.mmsName));
	}
	else if ((nLimitKind == 1)&&(mms_str_length(&pDA->MaxVal.mmsName)>0))
	{
		strDataRef.Format(_T("%s/%s"),pLD->LDName,mms_string(&pDA->MaxVal.mmsName));
	}
	else if ((nLimitKind == 2)&&(mms_str_length(&pDA->StepSize.mmsName)>0))
	{
		strDataRef.Format(_T("%s/%s"),pLD->LDName,mms_string(&pDA->StepSize.mmsName));
	}
	else if ((nLimitKind == 3)&&(mms_str_length(&pDA->DAUnite.mmsName)>0))
	{
		strDataRef.Format(_T("%s/%s"),pLD->LDName,mms_string(&pDA->DAUnite.mmsName));
	}
	else
		return ret;


	strDataRef.Replace(_T("$CF$"),_T("."));
	strDataRef.Replace(_T("$"),_T("."));
	GspLinkedList pRptDataList = ReadValue(strDataRef,_T("CF"));

	if (pRptDataList == NULL)
	{
		return ret;
	}

	void* item = GspLinkedList_get(pRptDataList, 0);
	Data* dataInfo = static_cast<Data*>(item);
	CString strDescValue;
	BOOL bExcuteResult = FALSE;

	if (nLimitKind == 0)
	{
		bExcuteResult = GspMms_GetValue(dataInfo,&pDA->MinVal);
	}
	else if (nLimitKind == 1)
	{
		bExcuteResult = GspMms_GetValue(dataInfo,&pDA->MaxVal);
	}
	else if (nLimitKind == 2)
	{
		bExcuteResult = GspMms_GetValue(dataInfo,&pDA->StepSize);
	}
	else if (nLimitKind == 3)
	{
		bExcuteResult = GspMms_GetValue(dataInfo,&pDA->DAUnite);
	}

	if (bExcuteResult)
	{
		ret = SD_SUCCESS;
	}

	// 释放元素值
	GspMmsValue_delete(dataInfo);
	GspLinkedList_destroyStatic(pRptDataList);


#endif

	return ret;
}
#endif


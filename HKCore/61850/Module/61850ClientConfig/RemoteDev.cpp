//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
	//��ʼ������
	m_nUseLocalIP = 0;

#ifdef USE_61850CLient_STRCUT
	//��ʼ����Ա����
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

	// ���ӵ�������
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
		CLogPrint::LogString(XLOGLEVEL_INFOR,("���ӵ�����˳ɹ�."));
	} 
	else 
	{
#ifdef _PSX_QT_LINUX_
        CLogPrint::LogString(XLOGLEVEL_ERROR,_T("���ӵ������ʧ��"));
#else
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("���ӵ������ʧ��(%d)."),(int)m_oConnectIED);
#endif

		// ��������
		Gsp_IedConnection_Destroy(m_oConnectIED);
		m_oConnectIED = NULL;
		return FALSE;
	}

	// ��������

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
 	// �ͷ�����
 	Gsp_IedConnection_Release(m_oConnectIED, &m_oErrorInfor, m_pAssociateID);

	// ��ֹ����
	Gsp_IedConnection_Abort(m_oConnectIED, &m_oErrorInfor, GSP_IED_ABORT_OTHER, m_pAssociateID);

	Gsp_IedConnection_Destroy(m_oConnectIED);
	Gsp_IedConnection_FreeAssociateID(m_pAssociateID);
	m_oConnectIED = NULL;

	if (m_oErrorInfor != GSP_IED_ERROR_OK)
	{
#ifdef _PSX_QT_LINUX_
        CLogPrint::LogString(XLOGLEVEL_ERROR,_T("�Ͽ�����ʧ��"));
#else
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�Ͽ�����ʧ��(%d)."),(int)m_oConnectIED);
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GetDataTypeδ֪����������(%ld)."),nGspDataType);
	}

	return bRet;
}

BOOL CRemoteDev::GetServerDirectory()
{
	if (!IsConnecting())
	{
		return FALSE;
	}

// 	// ��������
// 	Gsp_IedConnection_Associate(m_oConnectIED, &m_oErrorInfor, "S1");

	// ��ȡ�������߼��豸��Ŀ¼
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
		printf("��ȡ����Ŀ¼�����߼��豸Ϊ��\n");
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
	{//�Ѿ���ȡ��XMLģ���ļ���������Ҫ��ȡģ�ͣ��򲻴������ݼ�ö��
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

			//��ȡLLN0�����ԣ���ΪLLN0��Ӧ�������ַ������������԰���FC��ȡ�ַ�������������ȡ���ַ�������ӵ���״ģ����
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
// 		//����LNX���Խṹ
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�߼��豸(%s)���߼��ڵ�Ϊ��."),pLD->LDName);
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
		// ��ȡ ���п��ƿ�����
		strLNRef.Format(_T("%s/LLN0"),m_oAcsiDevice.LD[nIndex].LDName);
        allCBDataValue = Gsp_IedConnection_GetLogicNodeDirectory(m_oConnectIED, &m_oErrorInfor, GSP_ACSIClass_data_set, strLNRef.GetString());

		// ��ȡ���ݲ���ӡ ����
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

			if ((g_o61850ClientConfig.m_nAutoGenModelDatas)&&(strLNRef.Find("PROT") >= 0))//�Զ���Ӷ�Ӧ���ݼ�
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

			if ((g_o61850ClientConfig.m_nAutoGenModelDatas)&&(strLNRef.Find("PROT") >= 0))//�Զ���Ӷ�Ӧ���ݼ�
			{
				long nDsDevStdMsgIndex = dObj.size();
				strcpy(m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex].DataSetID, dsDevStdMsg);

				int nSize = 2;
				mms_New_LD_DATASET_INFO_numData(&m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex],nSize );
				mms_str_set(&m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex].DataSet[0].DAValue.mmsName,_T("LPHD1$DC$PhyNam$serNum"));
				mms_str_set(&m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex].DataSet[0].DADescri.Value.string,_T("װ��ʶ�����"));
				strcpy(m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex].DataSet[0].DataType,_T("V_STR"));
				m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex].DataSet[0].Type_id = DA_DATATYE_VISIBLE_STR;

				mms_str_set(&m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex].DataSet[1].DAValue.mmsName,_T("LPHD1$DC$PhyNam$swRev"));
				mms_str_set(&m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex].DataSet[1].DADescri.Value.string,_T("װ�ó���汾"));
				strcpy(m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex].DataSet[1].DataType,_T("V_STR"));
				m_oAcsiDevice.LD[nIndex].DataInfo[nDsDevStdMsgIndex].DataSet[1].Type_id = DA_DATATYE_VISIBLE_STR;
			}

			if (g_o61850ClientConfig.m_nUseDsDout)
			{
				strcpy(m_oAcsiDevice.LD[nIndex].DataInfo[nDatasetNum-1].DataSetID, dsDout);
			}
		}

		// �ڴ��ͷ�
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
		// ��ȡ����ʧ�ܴ���
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡ���ݼ�Ŀ¼ʧ��."));
		// �ͷ��ڴ�
		GspLinkedList_destroyStatic(datasetDirectoryList);
		return 0;
	}

	long nDataNum = GspLinkedList_size(datasetDirectoryList);
	mms_New_LD_DATASET_INFO_numData(&pLD->DataInfo[nDatasetIndex], nDataNum);
	CString strFC,strTemp1,strTmp2,strTmp3;
	long nTmpIndex = 0;

	// ��������ӡ������Ϣ
	for(int nIndex=0; nIndex < nDataNum; nIndex++)
	{
		// ��ȡԪ��ֵ
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
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ���ݶ���Ref����(%s)."),dataInfo->objRefs);
			continue;
		}

		strTmp3 = strTmp2.Left(nTmpIndex);
		strTmp3 += strFC;
		strTmp3 += strTmp2.Mid(nTmpIndex);
        mms_str_set(&pLD->DataInfo[nDatasetIndex].DataSet[nIndex].DAValue.mmsName,strTmp3.GetString());
//		GetDataDefinition_DO_DA(&pLD->DataInfo[nDatasetIndex].DataSet[nIndex],dataInfo->objRefs,dataInfo->fc);
	}

	// �ͷ������ڴ�
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
	// ��ȡָ��refs�������ݶ���
    GspLinkedList allDataDefines = Gsp_IedConnection_GetAllDataDefinition(m_oConnectIED
                                                                          , &m_oErrorInfor, /*DLT860_FC_ALL*/(GspFunctionalConstraint)nFC_Type
                                                                          , strDataRef.GetString(), LNREFERENCE);

	if (!allDataDefines)
	{
		CString strFC;
		GetFC_String(nFC_Type,strFC);

		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡ��ǰ·��(%s)�µ����ݶ���Ϊ��(FC==%s)."),strDataRef.GetString(),strFC.GetString());
		return FALSE;
	}

	if (GspLinkedList_size(allDataDefines)<=0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("LN(%s)��Ӧ����Լ��(%d)�µ��Ӷ���Ϊ��."),strDataRef.GetString(),nFC_Type);
		return TRUE;
	}

	CString strFC;
	MMS_DATA_NODE *pFC_Node = NULL;
	
	if (!GetFC_String(nFC_Type,strFC))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ����Լ������ʧ��(%d)."),nFC_Type);
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

		// ��ӡ����
		for(int index=0; index<innerItem->data.list.count; ++index)
		{

			// ȡ�� GetAllDataDefinitionResponsePDU__data__Member
			GetAllDataDefinitionResponsePDU__data__Member* dfItem = innerItem->data.list.array[index];

			if (dfItem->definition.choice.structure.list.count == 0)
			{
// 				strChildDataRef.Format(_T("%s.%s"),strDataRef,(char*)dfItem->reference.buf);
// 				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��ǰ�ڵ�·��(%s)��Ӧ��FC(%s)�ӽڵ�Ϊ��,����."),strChildDataRef.GetString(),strFC.GetString());
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

		// �ͷ�Ԫ��
		Gsp_FreeAllDataDefinition(innerItem);
	}

	GspLinkedList_destroyStatic(allDataDefines);
	return TRUE;
}

BOOL CRemoteDev::GetDataDefinition_DO_DA(tagDA* pDatasetTagDA,const char *pzfRef,const char *pzfFC)
{
// 	pzfRef = _T("P_M1112A4PROT/LLN0.FuncEna10");
// 	pzfFC = _T("XX");
	// ��ȡ������߶������
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

	// ��ȡ���ݶ���
	GspLinkedList dataDefiniaionList = Gsp_IedConnection_GetDataDefinition(m_oConnectIED, &m_oErrorInfor, requestList);

	if(!dataDefiniaionList)
	{
		// ��ȡ����ʧ�ܴ���
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡ����ʧ��(%s)."),strDataRef.GetString());

		// �ͷ��ڴ�
		GspLinkedList_destroyStatic(requestList);

		// �ͷ��ڴ�
		GspLinkedList_destroyStatic(dataDefiniaionList);
		return FALSE;
	}

	GetDataDefinitionResponsePDU_t* dataDefinitionInfo = NULL;

	// ��������ӡ������Ϣ
	for(int index=0; index < GspLinkedList_size(dataDefiniaionList); ++index)
	{
		// ��ȡԪ��ֵ
		void* item = GspLinkedList_get(dataDefiniaionList, index);
		dataDefinitionInfo = static_cast<GetDataDefinitionResponsePDU_t*>(item);

		// ��ӡ��Ϣ
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
                CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ��������(%s)�ֽڳ��ȳ���16�ֽ�."),strDataType.GetString());
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
	// ��ȡ������߶������
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
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ��������(%s)�ֽڳ��ȳ���16�ֽ�."),strDataType.GetString());
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
 
 		// ��ӡ����
 		for(int index=0; index<innerItem->data.list.count; ++index)
 		{
 
 			// ȡ�� GetAllDataDefinitionResponsePDU__data__Member
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
						CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��ǰ�ڵ�·��(%s)��Ӧ��FC(%s)�ӽڵ�Ϊ��,δ�ܻ�ȡʵ����������."),strChildDataRef.GetString(),strFC.GetString());

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
// 							CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ��������(%s)�ֽڳ��ȳ���16�ֽ�."),strDataType);
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
 
 		// �ͷ�Ԫ��
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
	// ����ֵ���ƿ��ֵ
	ST_CHAR VarName[NAMESIZE+1];
	ZeroMemory(VarName,NAMESIZE+1);
	_snprintf(VarName, NAMESIZE-1, "%s/LLN0.SGCB", m_oAcsiDevice.LD[nLdIndex].LDName);
//	const char* VarName = "P_L2201APROT/LLN0.SGCB";
	GspLinkedList retList = Gsp_IedConnection_GetSGCBValues(m_oConnectIED, &m_oErrorInfor, VarName);

	// ��ӡ����
	if(retList)
	{
		GetSGCBValuesResponsePDU_t* sgcbValue = static_cast<GetSGCBValuesResponsePDU_t*>(retList->front());

		for(int index=0; index < sgcbValue->sgcb.list.count; ++index)
		{
			// ��ȡ��Ա��Ϣ
			GetSGCBValuesResponsePDU__sgcb__Member* sgcbItem = sgcbValue->sgcb.list.array[index];

			if(sgcbItem->present != GetSGCBValuesResponsePDU__sgcb__Member_PR_value)
			{
				printf("�ö��ƿ��ƿ��ֵ�д���, ������Ϣ: %ld \n", sgcbItem->choice.error);
			} 
			else 
			{
				m_oAcsiDevice.nSGNum = sgcbItem->choice.value.numOfSG;
				m_oAcsiDevice.nEditSGIndex = sgcbItem->choice.value.editSG;
				m_oAcsiDevice.nRunSGIndex = sgcbItem->choice.value.actSG;
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��ǰ���������(%d),�༭��ֵ����(%d),��ֵ������(%d)."),sgcbItem->choice.value.actSG,sgcbItem->choice.value.editSG,sgcbItem->choice.value.numOfSG);
			}
		}

		// �ڴ��ͷ�
		Gsp_FreeSGCBValues(sgcbValue);
		GspLinkedList_destroyStatic(retList);
	} 
	else 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("û�ж�ȡ�����ƿ��ƿ��ֵ,�������: %d."), m_oErrorInfor);
		return FALSE;
	}

	return TRUE;
}

BOOL CRemoteDev::SetActiveSG(const long &nLdIndex,const long &nSG)
{
	if (!IsConnecting()||(m_oAcsiDevice.numLD<=nLdIndex))
	{
		sprintf(m_oAcsiDevice.InfoSetSG, _T("���õ�ǰ��ֵ��������%dʧ��,(%d)."), nSG,m_oErrorInfor);
		CLogPrint::LogString(XLOGLEVEL_ERROR,m_oAcsiDevice.InfoSetSG);
		return FALSE;
	}

	// ѡ�񼤻����
	ST_CHAR sgcbRefs[NAMESIZE+1];
	ZeroMemory(sgcbRefs,NAMESIZE+1);
	_snprintf(sgcbRefs, NAMESIZE-1, "%s/LLN0.SGCB", m_oAcsiDevice.LD[nLdIndex].LDName);
	bool ret = Gsp_IedConnection_SelectActiveSG(m_oConnectIED, &m_oErrorInfor, sgcbRefs, nSG);

	// ������Ϣ
	if(ret)
	{
		sprintf(m_oAcsiDevice.InfoSetSG, "���õ�ǰ��ֵ��������%d�ɹ�.", nSG);
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ѡ�񼤻ֵ���ɹ�,�л��� %d ��."), nSG);
		m_oAcsiDevice.nRunSGIndex = nSG;
	} 
	else 
	{
		sprintf(m_oAcsiDevice.InfoSetSG, _T("���õ�ǰ��ֵ��������%dʧ��,(%d)."), nSG,m_oErrorInfor);
		CLogPrint::LogString(XLOGLEVEL_ERROR,m_oAcsiDevice.InfoSetSG);
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ѡ�񼤻ֵ��ʧ��,�л��� %d ��ʧ��, �������: %d."),nSG, m_oErrorInfor);
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
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡ����ֵʧ��(%s),�������������."),mms_string(&pDAValue->mmsName));		 
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
//			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,("��ǰֵ(%s=%f)."),mms_string(&pDAValue->mmsName),pDAValue->Value.f);
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GspMms_GetValueδ֪����������(%d)."),dataType);
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
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡ����ֵʧ��(GetGspValue_String),�������������."));		 
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GspMms_GetValue_Stringʧ����������(%d)."),dataType);
		break;
	}

	return TRUE;
}

BOOL CRemoteDev::ReadValue(tagDAValue *pDAValue,const CString &strDataRef,const CString &strFC)
{
	BOOL bRet = TRUE;
	// ��ȡ������߶������
	GspLinkedList dataValue = ReadValue(strDataRef,strFC);

	if (dataValue == NULL)
	{
		return FALSE;
	}

	// ��ȡԪ��ֵ
	void* item = GspLinkedList_get(dataValue, 0);
	Data* dataInfo = static_cast<Data*>(item);

	if(!GspMms_GetValue(dataInfo,pDAValue))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�����������Ϊ��."));
		bRet = FALSE;
	} 

	// �ͷ�Ԫ��ֵ
	GspMmsValue_delete(dataInfo);
	GspLinkedList_destroyStatic(dataValue);
	return bRet;

// 	GspLinkedList requestList = GspLinkedList_create();
// 	sRefsFc dataRefs;
// 	dataRefs.fc = strFC;
// 	dataRefs.objRefs = strDataRef;
// 	GspLinkedList_add(requestList, &dataRefs);
// 
// 	// ��������
// 	GspLinkedList dataValue = Gsp_IedConnection_GetDataValues(m_oConnectIED, &m_oErrorInfor, requestList);
// 
// 	if(!dataValue)
// 	{
// 		// �ͷ��ڴ�
// 		GspLinkedList_destroyStatic(requestList);
// 
// 		// �ͷ��ڴ�
// 		GspLinkedList_destroyStatic(dataValue);
// 
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡ����ʧ��."));
// 		return FALSE;
// 	}
// 
// 	if (GspLinkedList_size(dataValue)<=0)
// 	{
// 		GspLinkedList_destroyStatic(requestList);
// 		GspLinkedList_destroyStatic(dataValue);
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡ����ʧ��."));
// 		return FALSE;
// 	}
// 
// 	// ��ȡԪ��ֵ
// 	void* item = GspLinkedList_get(dataValue, 0);
// 	Data* dataInfo = static_cast<Data*>(item);
// 
// 	if(!GspMms_GetValue(dataInfo,pDAValue))
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�����������Ϊ��."));
// 		bRet = FALSE;
// 	} 
// 
// 	// �ͷ�Ԫ��ֵ
// 	GspMmsValue_delete(dataInfo);
// 	GspLinkedList_destroyStatic(dataValue);
// 
// 	// �ͷ��ڴ�
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

	// ��������
	GspLinkedList dataValue = Gsp_IedConnection_GetDataValues(m_oConnectIED, &m_oErrorInfor, requestList);

	if(!dataValue)
	{
		// �ͷ��ڴ�
		GspLinkedList_destroyStatic(requestList);

		// �ͷ��ڴ�
		GspLinkedList_destroyStatic(dataValue);

		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡ����ʧ��."));
		return NULL;
	}

	if (GspLinkedList_size(dataValue)<=0)
	{
		GspLinkedList_destroyStatic(requestList);
		GspLinkedList_destroyStatic(dataValue);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡ����ʧ��."));
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
// 	// ��ȡ���ݶ���
// 	GspLinkedList dataDefiniaionList = Gsp_IedConnection_GetDataDefinition(m_oConnectIED, &m_oErrorInfor, requestList);
// 
// 	if(!dataDefiniaionList)
// 	{
// 		// ��ȡ����ʧ�ܴ���
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡ����ʧ��(%s)."),strDataRef);
// 
// 		// �ͷ��ڴ�
// 		GspLinkedList_destroyStatic(requestList);
// 
// 		// �ͷ��ڴ�
// 		GspLinkedList_destroyStatic(dataDefiniaionList);
// 		return FALSE;
// 	}
// 
// 	GetDataDefinitionResponsePDU_t* dataDefinitionInfo = NULL;
// 
// 	// ��������ӡ������Ϣ
// 	for(int index=0; index < GspLinkedList_size(dataDefiniaionList); ++index)
// 	{
// 		// ��ȡԪ��ֵ
// 		void* item = GspLinkedList_get(dataDefiniaionList, index);
// 		dataDefinitionInfo = static_cast<GetDataDefinitionResponsePDU_t*>(item);
// 
// 		// ��ӡ��Ϣ
// 	}
// 
// 	GspLinkedList_destroyStatic(dataDefiniaionList);
// 	GspMemory_free((char*)dataRefs->fc);
// 	GspMemory_free((char*)dataRefs->objRefs);
// 	GspMemory_free(dataRefs);
// 	GspLinkedList_destroyStatic(requestList);


	// ��ȡ������߶������
	GspLinkedList requestList = GspLinkedList_create();

	// ������� 001
	sRefsFc dataRefs;
    dataRefs.fc = strFC.GetString();
    dataRefs.objRefs = strDataRef.GetString();
	GspLinkedList_add(requestList, &dataRefs);

	// ��������
	GspLinkedList dataValue = Gsp_IedConnection_GetDataValues(m_oConnectIED, &m_oErrorInfor, requestList);

	if(!dataValue)
	{
		GspLinkedList_destroyStatic(requestList);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡ����ʧ��."));
		return FALSE;
	}

	if (GspLinkedList_size(dataValue)<=0)
	{
		GspLinkedList_destroy(dataValue);
		GspLinkedList_destroyStatic(requestList);
		return FALSE;
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡ����ʧ��."));
// 		return FALSE;
	}

	// ��ȡԪ��ֵ
	void* item = GspLinkedList_get(dataValue, 0);
	Data* dataInfo = static_cast<Data*>(item);

	if(dataInfo)
	{
		// ��ӡ������Ϣ
		//			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��������%i."), GspMmsValue_getType(dataInfo));

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
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ReadDataTypeδ֪����������(%d)."),GspMmsValue_getType(dataInfo));
		}
	} 
	else 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�������Ϊ��."));
		bRet = FALSE;
	} 

	// �ͷ��ڴ�
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

//		strFC = _T("ST");//zhouhj 20210609 ��ʱ�̶�ΪST
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

		// ��ȡ������߶������
		GspLinkedList requestList = GspLinkedList_create();

		RefsFC tmpRefs01 = (RefsFC)GspMemory_calloc(1, sizeof(struct sRefsFc));
		tmpRefs01->fc = "SE";
        tmpRefs01->objRefs = strDataRef.GetString();
		GspLinkedList_add(requestList, tmpRefs01);

		// ��������
		GspLinkedList dataValue = Gsp_IedConnection_GetEditSGValue(m_oConnectIED, &m_oErrorInfor, requestList);

		if(!dataValue)
		{
			GspLinkedList_destroyStatic(requestList);
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡ��ֵ����ʧ��."));
			return FALSE;
		}

		if (GspLinkedList_size(dataValue)<=0)
		{
			GspLinkedList_destroy(dataValue);
			GspLinkedList_destroyStatic(requestList);
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡ����ʧ��."));
			return FALSE;
		}

		// ��ȡԪ��ֵ
		void* item = GspLinkedList_get(dataValue, 0);
		GetEditSGValueResponsePDU_t* tmpSgItem = static_cast<GetEditSGValueResponsePDU_t*>(item);

		if((tmpSgItem)&&(tmpSgItem->value.list.count>=1))
		{
			GspMmsValue* sgValueItem = tmpSgItem->value.list.array[0];

			if(!GspMms_GetValue(sgValueItem,&pDA->DAValue))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�����������Ϊ��."));
				bRet = FALSE;
			} 

		} 
		else 
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�����������Ϊ��."));
			bRet = FALSE;
		} 
			// �ͷŶ�ֵԪ��
		Gsp_FreeEditSGValues(tmpSgItem);
		// �ͷŶ�ֵ�б�
		GspLinkedList_destroyStatic(dataValue);

		// ���Ʋ����ڴ��ͷ�
		deque<void *> d = *requestList;


		for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++)

		{
			RefsFC innerItem = (RefsFC)(*it);
			GspMemory_free(innerItem);
		}

		// �ͷ��ڴ�
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
	// ��ֵ�޸�ҵ���� 004 -> ȷ�϶�ֵ�޸Ĳ���
	if(!Gsp_IedConnection_ConfirmEditSGValues(m_oConnectIED, &m_oErrorInfor, zfRef))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�̻���ֵ��ʧ��(%s)."),zfRef);
		m_oAcsiDevice.nEditSGIndex = 0;
		return FALSE;
	} 

	m_oAcsiDevice.nEditSGIndex = 0;//�̻���ֵ����,�̶��ѱ༭����Ϊ0,�´ζ�ȡʱ����Ҫ�������ñ༭��,�����ԺҪ��,�������𱣻�װ��  zhouhj20210903 
	return TRUE;
}

BOOL CRemoteDev::GetRCBEnableState(const char *pLdName,const char *pRcbItem,BOOL &bRptEna)
{
	// ��ȡ������ƿ�����
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

	// ������Ϣ�ж�
	if(m_oErrorInfor != GSP_IED_ERROR_OK || m_oCurUrcbControlBlk == NULL)
	{
		Gsp_URCBControlBlk_Destory(m_oCurUrcbControlBlk);
		m_oCurUrcbControlBlk = NULL;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡ������ƿ�����ʧ��,�������: %d."), m_oErrorInfor);
		return FALSE;
	}

	if(m_oCurUrcbControlBlk->urcbControlBlk == NULL)
	{
		Gsp_URCBControlBlk_Destory(m_oCurUrcbControlBlk);
		m_oCurUrcbControlBlk = NULL;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡ������ƿ�����Ϊ��."));
		return FALSE;
	}

	bRptEna = *m_oCurUrcbControlBlk->urcbControlBlk->rptEna;
// 	printf("����ID: %s \n", currentUrcbControlBlk->urcbControlBlk->rptID->buf);
// 	printf("�����Ƿ�����: %d \n", *currentUrcbControlBlk->urcbControlBlk->rptEna);
// 	printf("���� datSet: %s \n", currentUrcbControlBlk->urcbControlBlk->datSet->buf);
// 	printf("���� optFlds: ");
// 	Gsp_BitString_print(currentUrcbControlBlk->urcbControlBlk->optFlds);
// 	printf("���� bufTm: %d \n", *currentUrcbControlBlk->urcbControlBlk->bufTm);
// 	printf("���� trgOps: ");
// 	Gsp_BitString_print(currentUrcbControlBlk->urcbControlBlk->trgOps);
// 	printf("���� intgPd: %d \n", *currentUrcbControlBlk->urcbControlBlk->intgPd);
// 	printf("���� gi: %d \n", *currentUrcbControlBlk->urcbControlBlk->gi);
	return TRUE;
}

BOOL CRemoteDev::GetBRCBValues(const char *pLdName,const char *pRcbItem,BOOL &bRptEna)
{
	CString strReportRefs;
	strReportRefs.Format(_T("%s/%s"),pLdName,pRcbItem);
	strReportRefs.Replace(_T("$BR$"),_T("."));
    m_oCurBrcbControlBlk = Gsp_IedConnection_GetBRCBValues(m_oConnectIED, &m_oErrorInfor, strReportRefs.GetString());

	// ������Ϣ�ж�
	if(m_oErrorInfor != GSP_IED_ERROR_OK || m_oCurBrcbControlBlk == NULL)
	{
		Gsp_BRCBControlBlk_Destory(m_oCurBrcbControlBlk);
		m_oCurBrcbControlBlk = NULL;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡ������ƿ�����ʧ��,�������: %d."), m_oErrorInfor);
		return FALSE;
	}

	if(m_oCurBrcbControlBlk->brcbControlBlk == NULL)
	{
		Gsp_BRCBControlBlk_Destory(m_oCurBrcbControlBlk);
		m_oCurBrcbControlBlk = NULL;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡ������ƿ�����Ϊ��."));
		return FALSE;
	}

	bRptEna = *m_oCurBrcbControlBlk->brcbControlBlk->rptEna;
// 	printf("�����Ƿ�����: %d \n", );
// 	printf("���� datSet: %s \n", currentBrcbControlBlk->brcbControlBlk->datSet->buf);
// 	printf("���� optFlds: ");
// 	Gsp_BitString_print(currentBrcbControlBlk->brcbControlBlk->optFlds);
// 	printf("���� bufTm: %d \n", *currentBrcbControlBlk->brcbControlBlk->bufTm);
// 	printf("���� trgOps: ");
// 	Gsp_BitString_print(currentBrcbControlBlk->brcbControlBlk->trgOps);
// 	printf("���� intgPd: %d \n", *currentBrcbControlBlk->brcbControlBlk->intgPd);
// 	printf("���� gi: %d \n", currentBrcbControlBlk->brcbControlBlk->gi);
// 	printf("���� purgeBuf: %d \n", *currentBrcbControlBlk->brcbControlBlk->purgeBuf);
// 	printf("���� entryID: %s \n", currentBrcbControlBlk->brcbControlBlk->entryID->buf);
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

	// ׼�����ò���
	BRCBControlBlk targetBrcbControlBlk = static_cast<BRCBControlBlk>(GspMemory_calloc(1, sizeof(sBRCBControlBlk)));
	// ���� refs(�ӻ�ȡ�ı�����ƿ���ֱ�ӿ���)
	Gsp_BRCBControlBlk_SetReportRefs(targetBrcbControlBlk, m_oCurBrcbControlBlk->reportRefs);

	// ���ò���ѡ��(���ô��ű���ԭ��)
	if ((nOptFlds>>2)%2)
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_reason_for_inclusion, TRUE,FALSE);
	} 
	else
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_reason_for_inclusion, FALSE,FALSE);
	}

	// ���ò���ѡ��(����������к�)

	if ((nOptFlds)%2)
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_sequence_number, true, true);
	} 
	else
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_sequence_number, false, true);
	}

	// ���ò���ѡ��(�������ʱ���)
	if ((nOptFlds>>1)%2)
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_report_time_stamp, true, true);
	}
	else
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_report_time_stamp, false, true);
	}

	// ���ò���ѡ��(����������ݼ�����)
	if ((nOptFlds>>3)%2)
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_data_set_name, true, true);
	}
	else
	{
        Gsp_BRCBControlBlk_SetOptFlds(targetBrcbControlBlk, RCBOptFlds_data_set_name, false, true);
	}

	// ���ò���ѡ��(����������ݲ�����)
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

	// ���ò���ѡ��(�������EntryID)

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

	// ���ñ��津��ѡ��
	if(!Gsp_IedConnection_SetBRCBValues(m_oConnectIED, &m_oErrorInfor, targetBrcbControlBlk))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("���ò���ѡ��ʧ��(%s)(%d)."),m_oCurBrcbControlBlk->reportRefs,m_oErrorInfor);
	}

	BOOL bGI = (nTrgOps>>4)%2;//�Ƿ�֧������

	if (bGI)
	{
	// ����֧�����ٻ�
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

	// ��������������
	BOOL bIntegrity = (nTrgOps>>3)%2;//�Ƿ���������

	if (bIntegrity)
	{
        Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, TriggerConditions_integrity, TRUE,TRUE);
	} 
	else
	{
        Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, TriggerConditions_integrity, FALSE,TRUE);
	}

	if ((nTrgOps)%2)//���ݱ仯����
	{
        Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, TriggerConditions_data_change, TRUE,TRUE);
	} 
	else
	{
        Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, TriggerConditions_data_change, FALSE,TRUE);
	}

	if ((nTrgOps>>1)%2)//Ʒ�ʱ仯����
	{
        Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, TriggerConditions_quality_change, TRUE,TRUE);
	} 
	else
	{
        Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, TriggerConditions_quality_change, FALSE,TRUE);
	}

	if ((nTrgOps>>2)%2)//���ݸ�������
	{
        Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, TriggerConditions_data_update, TRUE,TRUE);
	} 
	else
	{
        Gsp_BRCBControlBlk_SetTriggerConditions(targetBrcbControlBlk, TriggerConditions_data_update, FALSE,TRUE);
	}

	// ���ô���ѡ��
	if(!Gsp_IedConnection_SetBRCBValues(m_oConnectIED, &m_oErrorInfor, targetBrcbControlBlk))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("���ô���ѡ��ʧ��(%s)(%d)."),m_oCurBrcbControlBlk->reportRefs,m_oErrorInfor);
	}

	if (bIntegrity)
	{
		// ��������������ʱ��
		Gsp_BRCBControlBlk_IntgPd(targetBrcbControlBlk, g_o61850ClientConfig.GetIntgPdTime());

		// ��������������ʱ��
		if(!Gsp_IedConnection_SetBRCBValues(m_oConnectIED, &m_oErrorInfor, targetBrcbControlBlk))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��������������ʱ��ʧ��(%s)(%d)."),m_oCurBrcbControlBlk->reportRefs,m_oErrorInfor);
		}
	}

//	strcpy(pReportCB->RptID,strReportRefs); 
	CString strTmpRptID;
	strTmpRptID = Gsp_BRCBControlBlk_GetRptID(m_oCurBrcbControlBlk);
	strTmpRptID.Replace(_T("$BR$"),_T("."));
	strTmpRptID.Replace(_T("$RP$"),_T("."));

	// ����RPTID
    Gsp_BRCBControlBlk_SetRPTID(targetBrcbControlBlk, strTmpRptID.GetString());

	// ���ñ�����ƿ�
	if(!Gsp_IedConnection_SetBRCBValues(m_oConnectIED, &m_oErrorInfor, targetBrcbControlBlk))
	{
		Gsp_BRCBControlBlk_Destory(m_oCurBrcbControlBlk);
		m_oCurBrcbControlBlk = NULL;
		Gsp_BRCBControlBlk_Destory(targetBrcbControlBlk);
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("���ñ�����ƿ�ʧ��."));
		return FALSE;
	}

	// ��װ����ص�
    Gsp_IedConnection_InstallReportCallBack(m_oConnectIED, strReportRefs.GetString(), strTmpRptID.GetString(),
		ClientCallBackHandler::ReportHandler_BRCB, (void*)this/*pReportCB->RptID*/);//zhouhj ��Ϊ���ݶ���ָ��

	// ���ñ�����ƿ�ֵ(��������)
	Gsp_BRCBControlBlk_EnableRpt(targetBrcbControlBlk, true);

	if(!Gsp_IedConnection_SetBRCBValues(m_oConnectIED, &m_oErrorInfor, targetBrcbControlBlk))
	{
		Gsp_BRCBControlBlk_Destory(m_oCurBrcbControlBlk);
		m_oCurBrcbControlBlk = NULL;
		Gsp_BRCBControlBlk_Destory(targetBrcbControlBlk);
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("���濪��ʧ��."));
		return FALSE;
	}

	if (bGI || nEnbleGI)
	{
		// ��������
		Gsp_BRCBControlBlk_GI(targetBrcbControlBlk, true);
		if(!Gsp_IedConnection_SetBRCBValues(m_oConnectIED, &m_oErrorInfor, targetBrcbControlBlk))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��������ʧ��(%s)(%d)."),m_oCurBrcbControlBlk->reportRefs,m_oErrorInfor);
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

	// ׼�����ò���
	URCBControlBlk targetUrcbControlBlk = static_cast<URCBControlBlk>(GspMemory_calloc(1, sizeof(sURCBControlBlk)));
	// ���� refs(�ӻ�ȡ�ı�����ƿ���ֱ�ӿ���)
	Gsp_URCBControlBlk_SetReportRefs(targetUrcbControlBlk, m_oCurUrcbControlBlk->reportRefs);

	// ���ò���ѡ��(���ô��ű���ԭ��)
	if ((nOptFlds>>2)%2)
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_reason_for_inclusion, TRUE,FALSE);
	} 
	else
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_reason_for_inclusion, FALSE,FALSE);
	}

	// ���ò���ѡ��(����������к�)

	if ((nOptFlds)%2)
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_sequence_number, true, true);
	} 
	else
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_sequence_number, false, true);
	}

	// ���ò���ѡ��(�������ʱ���)
	if ((nOptFlds>>1)%2)
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_report_time_stamp, true, true);
	}
	else
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_report_time_stamp, false, true);
	}

	// ���ò���ѡ��(����������ݼ�����)
	if ((nOptFlds>>3)%2)
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_data_set_name, true, true);
	}
	else
	{
        Gsp_URCBControlBlk_SetOptFlds(targetUrcbControlBlk, RCBOptFlds_data_set_name, false, true);
	}

	// ���ò���ѡ��(����������ݲ�����)
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

	// ���ò���ѡ��(�������EntryID)

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

	// ���ò���ѡ��
	if(!Gsp_IedConnection_SetURCBValues(m_oConnectIED, &m_oErrorInfor, targetUrcbControlBlk))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("���ò���ѡ��ʧ��(%s)(%d)."),m_oCurUrcbControlBlk->reportRefs,m_oErrorInfor);
	}

	// ��������������
	BOOL bIntegrity = (nTrgOps>>3)%2;//�Ƿ���������

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
		// ����֧�����ٻ�
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

	if ((nTrgOps)%2)//���ݱ仯����
	{
        Gsp_URCBControlBlk_SetTriggerConditions(targetUrcbControlBlk, TriggerConditions_data_change, TRUE,TRUE);
	} 
	else
	{
        Gsp_URCBControlBlk_SetTriggerConditions(targetUrcbControlBlk, TriggerConditions_data_change, FALSE,TRUE);
	}

	if ((nTrgOps>>1)%2)//Ʒ�ʱ仯����
	{
        Gsp_URCBControlBlk_SetTriggerConditions(targetUrcbControlBlk, TriggerConditions_quality_change, TRUE,TRUE);
	} 
	else
	{
        Gsp_URCBControlBlk_SetTriggerConditions(targetUrcbControlBlk, TriggerConditions_quality_change, FALSE,TRUE);
	}

	if ((nTrgOps>>2)%2)//���ݸ�������
	{
        Gsp_URCBControlBlk_SetTriggerConditions(targetUrcbControlBlk, TriggerConditions_data_update, TRUE,TRUE);
	} 
	else
	{
        Gsp_URCBControlBlk_SetTriggerConditions(targetUrcbControlBlk, TriggerConditions_data_update, FALSE,TRUE);
	}

	// ���ñ�����ƿ�
	if(!Gsp_IedConnection_SetURCBValues(m_oConnectIED, &m_oErrorInfor, targetUrcbControlBlk))
	{
		Gsp_URCBControlBlk_Destory(m_oCurUrcbControlBlk);
		m_oCurUrcbControlBlk = NULL;
		Gsp_URCBControlBlk_Destory(targetUrcbControlBlk);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("���ñ�����ƿ�ʧ��(%s)(%d)."),m_oCurUrcbControlBlk->reportRefs,m_oErrorInfor);
		return FALSE;
	}

	if (bIntegrity)
	{
		// ��������������ʱ��
		Gsp_URCBControlBlk_IntgPd(targetUrcbControlBlk, g_o61850ClientConfig.GetIntgPdTime());

		if(!Gsp_IedConnection_SetURCBValues(m_oConnectIED, &m_oErrorInfor, targetUrcbControlBlk))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��������������ʱ��ʧ��(%s)(%d)."),m_oCurUrcbControlBlk->reportRefs,m_oErrorInfor);
		}
	}

//strcpy(pReportCB->RptID,strReportRefs); 
	CString strTmpRptID;
	strTmpRptID = Gsp_URCBControlBlk_GetRptID(m_oCurUrcbControlBlk);
	strTmpRptID.Replace(_T("$BR$"),_T("."));
	strTmpRptID.Replace(_T("$RP$"),_T("."));

	// ����RPTID
    Gsp_URCBControlBlk_SetRPTID(targetUrcbControlBlk, strTmpRptID.GetString());

	if(!Gsp_IedConnection_SetURCBValues(m_oConnectIED, &m_oErrorInfor, targetUrcbControlBlk))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("����RPTIDʧ��(%s)(%d)."),m_oCurUrcbControlBlk->reportRefs,m_oErrorInfor);
	}

	// ��װ����ص�
    Gsp_IedConnection_InstallReportCallBack(m_oConnectIED, strReportRefs.GetString(), strTmpRptID.GetString(),
		ClientCallBackHandler::ReportHandler_URCB, (void*)this/*pReportCB->RptID*/);

	// ���ñ�����ƿ�ֵ(��������)
	Gsp_URCBControlBlk_EnableRpt(m_oCurUrcbControlBlk, true);

	if(!Gsp_IedConnection_SetURCBValues(m_oConnectIED, &m_oErrorInfor, m_oCurUrcbControlBlk))
	{
		Gsp_URCBControlBlk_Destory(m_oCurUrcbControlBlk);
		m_oCurUrcbControlBlk = NULL;
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("���濪��ʧ��."));
		Gsp_URCBControlBlk_Destory(targetUrcbControlBlk);
		return FALSE;
	}

	if (bGI || nEnbleGI)
	{
		// ��������
		Gsp_URCBControlBlk_GI(targetUrcbControlBlk, true);

		if(Gsp_IedConnection_SetURCBValues(m_oConnectIED, &m_oErrorInfor, targetUrcbControlBlk))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��������ʧ��(%s)(%d)."),m_oCurUrcbControlBlk->reportRefs,m_oErrorInfor);
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
	long nIndex = strMsgPath.Find('^');//���Ҿ���ʱ�����Ϣ�����ӷ�
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

	nIndex = strDirPath.Find("/NEWEST_");//����������Ŀ���ĺ�׺
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
	BOOL bMark = check_prefix_and_suffix(strDirPath,strActDirPath);//�˺������·�����Ƿ������ʱ��β��ҵ�ǰ׺�������ļ������ҵĺ�׺�����з���1������������0����ȥ��ǰ׺����׺����ļ�·�����ظ�����2
	strTmp = mms_string(&pTagFileDir->filedir.filename);

	if ((strTmp != strActDirPath)||(bMark))//�ļ�����·����������Դ�ļ���¼
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

	// ��ȡ�ļ�Ŀ¼
	bool bMoreData = FALSE;
	GspLinkedList fileDirs = NULL;

	do 
	{
        fileDirs = Gsp_IedConnection_GetFileDirectory(m_oConnectIED,&m_oErrorInfor,strFullPath.GetString(),NULL,NULL, NULL, bMoreData);

		if ((!fileDirs)||(m_oErrorInfor != GSP_IED_ERROR_OK))
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡĿ¼(%s)ʧ��(%d)."),strFullPath.GetString(),m_oErrorInfor);
			pFileDir->readfailed = TRUE;
			bRet = FALSE;
			break;
		}

		// ��������ӡ
		deque<void *> d = *fileDirs;

		char zfEnd = 0;

		for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++)

		{
			GspFileDirectoryEntry fileItem = (GspFileDirectoryEntry)(*it);
			strContinueName = Gsp_FileDirEntry_GetFileName(fileItem);

			if (strContinueName.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�ļ���Ŀ¼����Ϊ��."));
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

			nType = (nIndex == (strFileDirName.GetLength()-1));//������һ���ַ�Ϊ'/'��ΪĿ¼

			if (nType)
			{
				strTmp = strFileDirName.Left(nIndex);
				nIndex = strTmp.ReverseFind('/');//�����ȥ���һ���ַ��⻹��'/'����Ϊȫ·��,��Ҫ��·���л�ȡĿ¼����

				if (nIndex != -1)
				{
					strTmp = strFileDirName.Mid(nIndex+1);
					strFileDirName = strTmp;
				} 
			} 
			else
			{
				if (bOnlyReadCfg)//���ֻ��ȡ¼���ļ����ڴ˴������ļ����ƽ��й���
				{
					if (strFileDirName.GetLength()<=4)//���Ƴ���С��4,��϶�����
					{
						continue;
					}

					strTmp = strFileDirName.Mid(strFileDirName.GetLength()-4);
					strTmp.MakeLower();

					if (strTmp != _T(".cfg"))//�ļ������4���ֽڲ�ƥ��,�����
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

	// д�ļ�
    FILE* pfile = fopen(strLocalFile.GetString(), "r+b");

	if (pfile == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�ļ�(%s)��ʧ��."),strLocalFile.GetString());
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
		// ��ȡһ����������
		memset(fileDataBlock, 0 , sizeof(fileDataBlock));
		nCount = fread(fileDataBlock, sizeof (char), 1024*16, pfile);
		nSendIndex++;

		// �Ƿ�Ϊ��
		bool endFlag = false;
		nTotalLenth1 = ftell(pfile);

		if(nTotalLenth1>=nTotalLenth/*feof(pfile)*/)
		{
			endFlag = true;
		}

		// �����ļ�
        bool bSendRet = Gsp_IedConnection_setFile(m_oConnectIED, &m_oErrorInfor, strDevFilePath.GetString(), nFilePostion, fileDataBlock,nCount, endFlag);
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��ǰ֡����(%ld)�ֽ�����(%ld),��ǰ�ļ�λ��(%ld),���ֽ���(%ld)."),nSendIndex,nCount,nTotalLenth1,nTotalLenth);

		if (!bSendRet)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��װ�ļ�(%s),DevPah(%s)��ǰ֡����(%ld)����ʧ��."),strLocalFile.GetString(),strDevFilePath.GetString(),nSendIndex);
		}

		nFilePostion += nCount;
//		filePostion++;
//		printf("дһ֡�ļ�, �ֽ�����:%d, �Ƿ�д�ɹ�:%d ", 1024, ret);
	}

    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��װ�ļ�(%s),DevPah(%s),�·��ֽ�������(%ld),�ļ��ֽ�������(%ld).")
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

	// �����ļ�
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
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�����ļ�(%s)ʧ��."),strLocalFilePath.GetString());
		return FALSE;
	}

//	FILE* fp = fopen(strLocalFilePath, "w");
	uint32_t filePostion = 1;

    while (Gsp_IedConnection_GetFile(m_oConnectIED, &m_oErrorInfor
                                     ,strRemoteFilePath.GetString(), &filePostion, /*ClientCallBackHandler::*/ClientCallBack_GetFileHandler, (void*)pfile))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,("�����ļ� %s ���������� %d �ֽ�."), strRemoteFilePath.GetString(), filePostion);
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
	// ����ֵ
	GspMmsValue* ctlVal = GspMmsValue_newBoolean(nValue);

	if (!CtrlWriteDA_Direct(strRef,ctlVal))
	{
		strRef.Format(_T("%s/LLN0.CBFlt"),pLD->LDName);
		// ����ֵ
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
 	// ��ȡ rpc �ӿ�������Ϣ
 	GspLinkedList interfaceList = Gsp_IedConnection_GetRpcInterfaceDirectory(m_oConnectIED, &m_oErrorInfor);
 	long nInterIndex = 0,nInterNum = 0,nRpcInterfaceDefinitionIndex = 0,nRpcInterfaceDefinitionNum = 0,nRpcMethodDirectoryIndex = 0,nRpcMethodDirectoryNum = 0;
 
 	// ��ȡ rpc ������Ϣ
 	deque<void *> pD_InterfaceList = *interfaceList;
 	nInterNum = pD_InterfaceList.size();

 	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Gsp_IedConnection_GetRpcInterfaceDirectory��ȡ������%ld."), nInterNum);
	CString strAllString;
 
 	for(deque<void *>::const_iterator itInterface = pD_InterfaceList.begin(); itInterface != pD_InterfaceList.end(); itInterface++)

 	{
 		nInterIndex++;
 		char *pInterfaceItem = (char*)*itInterface;
 		// ��ӡ�ӿ�������Ϣ
 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("interface: %s,Index=%ld."), pInterfaceItem,nInterIndex);
 
 		// ��ȡ rpc �ӿڶ�����Ϣ
 		GspLinkedList interfaceDefinitionList = Gsp_IedConnection_GetRpcInterfaceDefinition(m_oConnectIED, &m_oErrorInfor, (char*)pInterfaceItem);
 
 		deque<void *> pD_InterfaceDefinitionList = *interfaceDefinitionList;
 		nRpcInterfaceDefinitionNum = pD_InterfaceDefinitionList.size();

 		nRpcInterfaceDefinitionIndex = 0;
 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Gsp_IedConnection_GetRpcInterfaceDefinition��ȡ������%ld."), nRpcInterfaceDefinitionNum);
 
 		for(deque<void *>::const_iterator itInterfaceDefinition = pD_InterfaceDefinitionList.begin(); itInterfaceDefinition != pD_InterfaceDefinitionList.end(); itInterfaceDefinition++)

 		{
 			// ��ȡ�ӿڶ�����Ϣ
 			nRpcInterfaceDefinitionIndex++;
 			GetRpcInterfaceDefinitionResponsePDU_t* rpcdItem = (GetRpcInterfaceDefinitionResponsePDU_t*)(*itInterfaceDefinition);
 			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Gsp_IedConnection_GetRpcInterfaceDefinition,Index=%ld,rpcdItem->method.list.count = %d."),nRpcInterfaceDefinitionIndex,
 				rpcdItem->method.list.count);
 
 			// ��ӡ�ӿڶ�����Ϣ
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
 				// request��ʣ���ڲ���Ϣ���ڴ�ӡ�����Ƽ��ɣ�
 				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("RpcInterfaceDefinition--request->type: %u."), rpcdInnerItem->request.present);
 				// response��ʣ���ڲ���Ϣ���ڴ�ӡ�����Ƽ��ɣ�
 				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("RpcInterfaceDefinition--response->type: %u."), rpcdInnerItem->response.present);
 			}
 		}
 
 		// �ͷŽӿڶ���
 		Gsp_IedConnection_FreeRpcInterfaceDefinition(interfaceDefinitionList);
 
 		// ��ȡ�����б�
 		GspLinkedList methodList = Gsp_IedConnection_GetRpcMethodDirectory(m_oConnectIED, &m_oErrorInfor, pInterfaceItem);
 		deque<void *> pD_MethodList = *methodList;

 		nRpcMethodDirectoryIndex = 0;
 		nRpcMethodDirectoryNum = pD_MethodList.size();
 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Gsp_IedConnection_GetRpcMethodDirectory��ȡ������%ld."), nRpcMethodDirectoryNum);
 
 		for(deque<void *>::const_iterator itMethod = pD_MethodList.begin(); itMethod != pD_MethodList.end(); itMethod++)

 		{
 			char *pMethodItem = (char*)*itMethod;
 			nRpcMethodDirectoryIndex++;
 
 			// ��ӡ��Ϣ
 			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("RpcMethodDirectory--interface: %s,Index=%ld."), pMethodItem,nRpcMethodDirectoryIndex);
			strAllString.Format(_T("%s.%s"),pInterfaceItem,pMethodItem);
            XDLT_RPC_METHOD* pRpcMethod = Global_RpcMethodAddNewMethod(&m_oAcsiDevice.oRpcMethods,strAllString.GetString());
 
 
 			// ��ȡ rpc �ӿڶ�����Ϣ
 			GspLinkedList medthodDefinitionList = Gsp_IedConnection_GetRpcInterfaceDefinition(m_oConnectIED, &m_oErrorInfor, (char*)pInterfaceItem);
 
 			deque<void *> pD_MethodDefinitionList = *medthodDefinitionList;
 			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Gsp_IedConnection_GetRpcInterfaceDefinition��ȡ������%d."), pD_MethodDefinitionList.size());
 
 
 			for(deque<void *>::const_iterator itMethodDefinition = pD_MethodDefinitionList.begin(); itMethodDefinition != pD_MethodDefinitionList.end(); itMethodDefinition++)

 			{
 				// ��ȡ�ӿڶ�����Ϣ
 				GetRpcInterfaceDefinitionResponsePDU_t* rpcdItem = (GetRpcInterfaceDefinitionResponsePDU_t*)(*itMethodDefinition);
 
 				// ��ӡ�ӿڶ�����Ϣ
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
 					// request��ʣ���ڲ���Ϣ���ڴ�ӡ�����Ƽ��ɣ�
 					CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("request->type: %u."), rpcdInnerItem->request.present);
 					// response��ʣ���ڲ���Ϣ���ڴ�ӡ�����Ƽ��ɣ�
 					CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("response->type: %u."), rpcdInnerItem->response.present);
 				}
 
 				// TODO RPC ���ã��������һ��ʵ�ʲ��Խ�����е��ã�
 				// Gsp_IedConnection_RPCCall
 			}
 
 
 			// �ͷŷ�������
 			Gsp_IedConnection_FreeRpcMethodDefinition(medthodDefinitionList);
 		}
 
 		// �ͷŷ�����Ϣ
 		Gsp_IedConnection_FreeRpcMethodDirectory(methodList);
 	}

	// �ͷŽӿ���Ϣ
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
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡRPC����ֵʧ��,�������������."));		 
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
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Rpc����ֵ(%d)(BOOL)."),pTagDA->DAValue.Value.u );		 
		}
		break;
	case Data_PR_int8:
	case Data_PR_int16:
	case Data_PR_int32:
		{
			strcpy(pTagDA->DataType,_T("INT"));
			pTagDA->DAValue.Value.l = GspMmsValue_toInt32(responsePDU);
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Rpc����ֵ(%d)(int)."),pTagDA->DAValue.Value.l);			 
		}
		break;
	case Data_PR_float32:
		{
			strcpy(pTagDA->DataType,_T("FLOAT"));
			pTagDA->DAValue.Value.f = GspMmsValue_toFloat(responsePDU);
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Rpc����ֵ(%f)(float)."),pTagDA->DAValue.Value.f);	
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
            CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Rpc����ֵ(%s)(quality)."),strTmp.GetString());
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
            CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Rpc����ֵ(%s)(bit_string)."),strTmp.GetString());
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

            CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Rpc����ֵ(%s)(dbpos)."),strTmp.GetString());
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
            CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Rpc����ֵ(%s)(visible_string)."),strTmp.GetString());
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

			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Rpc����ֵ(%s)(unicode_string)."),pGBK_Value);
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
            CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Rpc����ֵ(%s)(utc_time)."),strTime1.GetString());
		}
		break;
	default:
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("Rpc����ֵδ֪����������(%d)."),dataType);
		break;
	}
}

BOOL CRemoteDev::RpcCall(const CString &strParaFunction,const CString &strParaCallName,const CString &strParaCallID,
						 ST_INT nVersion, ST_INT nTimeout, ST_INT nRequestType, ST_INT nResponseType)
{
	// RPC���ã������������������һ���ӿڽ��е��ã�
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

	// ���ý���ж�
	if(m_oErrorInfor == GSP_IED_ERROR_OK)
	{
        XDLT_RPC_METHOD* pRpcMethod = Global_FindRpcMethod(&m_oAcsiDevice.oRpcMethods,strParaFunction.GetString());
		// ��ȡ���
		GspMmsValue* responsePDU = Gsp_RPCCallResPonse_getData(response);
		ASSERT(pRpcMethod);
		mms_Free_tagDA(&pRpcMethod->oDataModel);
		mms_InitData(&pRpcMethod->oDataModel);
		// �����������ͽ��л�ȡ�ڲ���ֵ������ֵ�ӿڻ�ȡ������ֵһ��(TODO)
		ShowRpcValues(responsePDU,&pRpcMethod->oDataModel);

		// �ͷ��ڴ�
		Gsp_IedConnection_FreeRPCCallPDU(response);
	} 
	else 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("RPCCall ʧ��."));
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
					CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("����ֹͣ�ɹ�."));
					bRet = TRUE;
				}
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�����Ѿ�ֹͣ."));
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
					CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("����ֹͣ�ɹ�."));
					bRet = TRUE;
				}
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�����Ѿ�ֹͣ."));
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

		// д��ֵ���ƿ��ֵ
		GspLinkedList writeSgValues = GspLinkedList_create();

		// �޸� bool ���͵Ķ�ֵ
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
			// TODO ������Ҫ���������ӡһЩ���Զ���
		default:
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("д��ֵʱ,����δ֪����������(%d)."),pDA->nDataType);
		}

		GspLinkedList_add(writeSgValues, sgvalue);

		// ��ֵ�޸�ҵ���� 003 -> д��ֵ����
		if(!Gsp_IedConnection_SetEditSGValue(m_oConnectIED, &m_oErrorInfor, writeSgValues))
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�޸Ķ�ֵ(%s)ʧ��,������(%d)."),strDataRef.GetString(),m_oErrorInfor);
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

		// д���ݵ�ֵ
		GspLinkedList writeDataValues = GspLinkedList_create();

		// �޸� bool ���͵Ķ�ֵ
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
			// TODO ������Ҫ���������ӡһЩ���Զ���
		default:
			return FALSE;
//			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("д����ʱ,����δ֪����������(%d)."),pDA->nDataType);
		}

		// ��ӵ��б�
		GspLinkedList_add(writeDataValues, dataRefs);

		// ��������
		GspLinkedList resultList = Gsp_IedConnection_SetDataValues(m_oConnectIED, &m_oErrorInfor, writeDataValues);

		if(!resultList)//zhouhj 20211201 �ӿڲ��ֻ�������,��ʱĬ���޸ĳɹ�
		{
			// ��������ʧ�ܴ���
//			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("д����ʧ��(%s)."),strDataRef);

			// �ͷ��ڴ�
			GspLinkedList_destroyStatic(writeDataValues);
			// �ͷ��ڴ�
			GspLinkedList_destroyStatic(resultList);
			return TRUE;
		}
		// �ͷ������ڴ�
		GspLinkedList_destroyStatic(resultList);
		// �ͷŲ����ڴ�
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

				if (g_o61850ClientConfig.m_nUseDsDout)//����ӿ������ź����ݼ��������,�������²���
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

							strData.Format("%s$ST$%s",mms_string(&ln_data_node->name),mms_string(&da_node->name));//zhouhj20190102����dsDout���ݼ��е�FC����
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
                    CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰλ��ֵ����(%s),ǿ����Ϊ0."),strTmp.GetString());
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

		// �������ƶ���
        GspControlObjectClient sboControl = Gsp_ControlObjectClient_Create(strRef.GetString(), m_oConnectIED);
		Gsp_ControlObjectClient_SetTestMode(sboControl,g_o61850ClientConfig.HasCtrlTest());
		Gsp_ControlObjectClient_SetSyncCheck(sboControl,g_o61850ClientConfig.HasCtrlSynCheck());
// 		Gsp_ControlObjectClientInit(sboControl,g_o61850ClientConfig.HasCtrlTest(),g_o61850ClientConfig.HasCtrlSynCheck(),
// 			g_o61850ClientConfig.HasCtrlInterlockCheck(),g_o61850ClientConfig.HasTimeActived());
		// ����ֵ
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
		// ����origin
		Gsp_ControlObjectClient_SetOriginator(sboControl, Originator__orCat_remoteControl, "test");

		if (pFunc != NULL)
		{
			pFunc(pFuncParaEx, 0); 
		}

		if(Gsp_IedConnection_SelectWithValue(sboControl,&m_oErrorInfor,ctlVal))
		{
			sprintf(m_oAcsiDevice.InfoSel
				, _T("ѡ��ѹ�塾%s����%d���ɹ�"), strRef.GetString(), nValue);

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
			// ����
			if(!Gsp_IedConnection_Operate(sboControl,&m_oErrorInfor, ctlVal, 0))
			{
				bRet = FALSE;
				sprintf(m_oAcsiDevice.InfoExec
					, _T("ִ��ѹ�塾%s����%d��ʧ��"), strRef.GetString(), nValue);
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%s"),m_oAcsiDevice.InfoExec);
			}
			else
			{
				sprintf(m_oAcsiDevice.InfoExec
					, _T("ִ��ѹ�塾%s����%d���ɹ�"),strRef.GetString(), nValue);
			}

// 			{
// 				bRet = FALSE;
// 				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("(%s)ִ�п���дʧ��(%d)."), strRef.GetString(),m_oErrorInfor);
// 			} 

			m_oAcsiDevice.tmExec = oTickCount32.GetTickCountLong();
			m_oAcsiDevice.tmTotal = m_oAcsiDevice.tmExec + m_oAcsiDevice.tmSel;

			if (pFunc != NULL)
			{
				pFunc(pFuncParaEx, 3); 
			}

			// �ڴ��ͷ�
//			GspMmsValue_delete(ctlVal);
		}
		else
		{
			bRet = FALSE;
			sprintf(m_oAcsiDevice.InfoSel
				, _T("ѡ��ѹ�塾%s����%d��ʧ��"), strRef.GetString(), nValue);
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("(%s)ִ��ѡ�����ʧ��(%d)."), strRef.GetString(),m_oErrorInfor);
		}

		// ��Դ�ͷ�
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

	// �������ƶ���
    GspControlObjectClient pSelControl = Gsp_ControlObjectClient_Create(strSelRef.GetString(), m_oConnectIED);
 	Gsp_ControlObjectClient_SetTestMode(pSelControl,g_o61850ClientConfig.HasCtrlTest());
 	Gsp_ControlObjectClient_SetSyncCheck(pSelControl,g_o61850ClientConfig.HasCtrlSynCheck());
// 	Gsp_ControlObjectClient_SetLockCheck(pSelControl,g_o61850ClientConfig.HasCtrlInterlockCheck());
// 	Gsp_ControlObjectClient_SetLockCheck(pSelControl,g_o61850ClientConfig.HasCtrlInterlockCheck());
//	Gsp_ControlObjectClientInit(pSelControl,g_o61850ClientConfig.HasCtrlTest(),g_o61850ClientConfig.HasCtrlSynCheck(),
//		g_o61850ClientConfig.HasCtrlInterlockCheck(),g_o61850ClientConfig.HasTimeActived());
	// ����ֵ
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
	// ����origin
	Gsp_ControlObjectClient_SetOriginator(pSelControl, Originator__orCat_remoteControl, "test");

	if (pFunc != NULL)
	{
		pFunc(pFuncParaEx, 0); 
	}

	if(Gsp_IedConnection_SelectWithValue(pSelControl,&m_oErrorInfor,ctlVal))
	{
		sprintf(m_oAcsiDevice.InfoSel
			, _T("ѡ��ѹ�塾%s����%d���ɹ�"), strSelRef.GetString(), iValue);
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
		// ����
		if(!Gsp_IedConnection_Operate(pSelControl,&m_oErrorInfor, ctlVal, 0))
		{
			bRet = FALSE;
			sprintf(m_oAcsiDevice.InfoExec
				, _T("ִ��ѹ�塾%s����%d��ʧ��"), strOperRef.GetString(), iValue2);
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%s"),m_oAcsiDevice.InfoExec);
		}
		else
		{
			sprintf(m_oAcsiDevice.InfoExec
				, _T("ִ��ѹ�塾%s����%d���ɹ�"),strOperRef.GetString(), iValue2);
		}

// 		{
// 			bRet = FALSE;
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("(%s)ִ�п���дʧ��(%d)."), strOperRef.GetString(),m_oErrorInfor);
// 		} 

		m_oAcsiDevice.tmExec = oTickCount32.GetTickCountLong();
		m_oAcsiDevice.tmTotal = m_oAcsiDevice.tmExec + m_oAcsiDevice.tmSel;

		if (pFunc != NULL)
		{
			pFunc(pFuncParaEx, 3); 
		}
		// ��Դ�ͷ�
		Gsp_ControlObjectClient_Destroy(pSelControl);
	}
	else
	{
		bRet = FALSE;
		sprintf(m_oAcsiDevice.InfoSel
			, _T("ѡ��ѹ�塾%s����%d��ʧ��"), strSelRef.GetString(), iValue);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("(%s)ִ��ѡ�����ʧ��(%d)."), strSelRef.GetString(),m_oErrorInfor);
		// ��Դ�ͷ�
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

		// �������ƶ���
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
				, _T("ѡ��ѹ�塾%s����%d���ɹ�"), strRef.GetString(), nValue);
			m_oAcsiDevice.tmSel = oTickCount32.GetTickCountLong(TRUE);

			if (pFunc != NULL)
			{
				pFunc(pFuncParaEx, 1); 
			}
			// ����ֵ
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

			// ����origin
			Gsp_ControlObjectClient_SetOriginator(sboControl, Originator__orCat_remoteControl, "test");
			oTickCount32.Enter();

			::GetLocalTime(&m_oAcsiDevice.tmStartExc);

			if (pFunc != NULL)
			{
				pFunc(pFuncParaEx, 2); 
			}
			// ����
			if(!Gsp_IedConnection_Operate(sboControl,&m_oErrorInfor, ctlVal, 0))
			{
				bRet = FALSE;
				sprintf(m_oAcsiDevice.InfoExec
					, _T("ִ��ѹ�塾%s����%d��ʧ��"), strRef.GetString(), nValue);
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%s"),m_oAcsiDevice.InfoExec);
			}
			else
			{
				sprintf(m_oAcsiDevice.InfoExec
					, _T("ִ��ѹ�塾%s����%d���ɹ�"),strRef.GetString(), nValue);
			}

			m_oAcsiDevice.tmExec = oTickCount32.GetTickCountLong();
			m_oAcsiDevice.tmTotal = m_oAcsiDevice.tmExec + m_oAcsiDevice.tmSel;

			if (pFunc != NULL)
			{
				pFunc(pFuncParaEx, 3); 
			}
			// �ڴ��ͷ�
//			GspMmsValue_delete(ctlVal);
		}
		else
		{
			bRet = FALSE;
			sprintf(m_oAcsiDevice.InfoSel
				, _T("ѡ��ѹ�塾%s����%d��ʧ��"), strRef.GetString(), nValue);
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("(%s)ִ��ѡ�����ʧ��(%d)."), strRef.GetString(),m_oErrorInfor);
		}

		// ��Դ�ͷ�
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
		// ����ֵ
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
	// �������ƶ���
    GspControlObjectClient directControl = Gsp_ControlObjectClient_Create(strRef.GetString(), m_oConnectIED);
	Gsp_ControlObjectClient_SetTestMode(directControl,g_o61850ClientConfig.HasCtrlTest());
	Gsp_ControlObjectClient_SetSyncCheck(directControl,g_o61850ClientConfig.HasCtrlSynCheck());
// 	Gsp_ControlObjectClientInit(directControl,g_o61850ClientConfig.HasCtrlTest(),g_o61850ClientConfig.HasCtrlSynCheck(),
// 		g_o61850ClientConfig.HasCtrlInterlockCheck(),g_o61850ClientConfig.HasTimeActived());

	// ����origin
	Gsp_ControlObjectClient_SetOriginator(directControl, Originator__orCat_remoteControl, "test");

	::GetLocalTime(&m_oAcsiDevice.tmStartExc);
	// ����
	if(!Gsp_IedConnection_Operate(directControl,&m_oErrorInfor, ctlVal, 0))
	{
		bRet = FALSE;
		sprintf(m_oAcsiDevice.InfoExec
			, _T("ִ��ѹ�塾%s����%d��ʧ��"), strRef.GetString(), ctlVal->choice.boolean);
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%s"),m_oAcsiDevice.InfoExec);
	}
	else
	{
		sprintf(m_oAcsiDevice.InfoExec
			, _T("ִ��ѹ�塾%s����%d���ɹ�"),strRef.GetString(), ctlVal->choice.boolean);
	}

// 	{
// 		bRet = FALSE;
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("(%s)����дʧ��(%d)."), strRef.GetString(),m_oErrorInfor);
// 	} 

	// �ڴ��ͷ�
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

	// ѡ��༭������
	ST_CHAR sgcbRefs[NAMESIZE+1];
	ZeroMemory(sgcbRefs,NAMESIZE+1);
	_snprintf(sgcbRefs, NAMESIZE-1, "%s/LLN0.SGCB", m_oAcsiDevice.LD[nLdIndex].LDName);
	bool ret = Gsp_IedConnection_SelectEditSG(m_oConnectIED, &m_oErrorInfor, sgcbRefs, nSE);

	// ������Ϣ
	if(ret)
	{
		m_oAcsiDevice.nEditSGIndex = nSE;
		sprintf(m_oAcsiDevice.InfoSetSE
			, _T("��%d�����õ�ǰ�༭����%d���ɹ�")
			, GetDeviceIndex(), nSE);
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ѡ��༭��ֵ���ɹ�,�л��� %d ��."), nSE);
		return TRUE;
	} 
	else 
	{
		sprintf(m_oAcsiDevice.InfoSetSE
			, _T("��%d�����õ�ǰ�༭����%d��ʧ��.")
			, GetDeviceIndex(), nSE);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ѡ��༭��ֵ��ʧ��,�л��� %d ��ʧ��, �������: %d."),nSE, m_oErrorInfor);
		return FALSE;
	}
}

LD_DATASET_INFO* GetDatasetStruct(LD_NODE *pLD,CString &strDatasetPath)//����2���ַ������޸�Ϊ����LD�����ݼ�����
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

LD_LOG_INFO* GetLD_LOG_INFO_ByDataset(LD_NODE *pLD,CString &strDatasetPath)//����2���ַ������޸�Ϊ����LD�����ݼ�����
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
	// ��ȡ ���п��ƿ�����
	char zsGetCBRef[NAMESIZE];
	ZeroMemory(zsGetCBRef,NAMESIZE);
	_snprintf(zsGetCBRef, NAMESIZE-1, "%s/LLN0", pLD->LDName);

	GspLinkedList allCBDataValue = Gsp_IedConnection_GetAllCBValues(m_oConnectIED, &m_oErrorInfor, (GspACSICLASS)nGSP_ACSIClass, zsGetCBRef, LNREFERENCE);

	// ��ȡ���ݲ���ӡ ����
	if(allCBDataValue)
	{
		CString strCBRef,strDatasetPath,strRptID;
		LD_DATASET_INFO			*pDatasetInfo = NULL;
		deque<void *> dObj = *allCBDataValue;


		for(deque<void *>::const_iterator itObj = dObj.begin(); itObj != dObj.end(); itObj++)/*for(auto &item : *allCBDataValue)*/

		{
			GetAllCBValuesResponsePDU_t * dataItem = (GetAllCBValuesResponsePDU_t*)*itObj;/*item*///;

			// ��������
			for(int i=0; i< dataItem->cbValue.list.count; ++i)
			{

				// ��ȡ����
				GetAllCBValuesResponsePDU__cbValue__Member* item = dataItem->cbValue.list.array[i];
				strCBRef.Format(_T("LLN0.%s"),item->reference.buf);
// 				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,"************************** ���ƿ�ֵ����(������Ŀ %d/%d) ****************.", i+1, dataItem->cbValue.list.count);
// 				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,"���ƿ�� refs: %s \n", item->reference.buf);

				switch(item->value.present)
				{
				case GetAllCBValuesResponsePDU__cbValue__Member__value_PR_brcb:
					{
						// ��ӡ����
						BRCB_t itemData = item->value.choice.brcb;
                        strDatasetPath = (char*)itemData.datSet.buf;
						pDatasetInfo = GetDatasetStruct(pLD,strDatasetPath);

						if (pDatasetInfo != NULL)
						{
							if (pDatasetInfo->numRcb>=MAX_RCB_VMD)
							{
								CLogPrint::LogFormatString(XLOGLEVEL_INFOR,"��ǰ������ƿ�·��%s,���ݼ�%s,��Ӧ�ı�����������%d,������󱨸���������.",
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
					// ��ӡ����
						URCB_t itemData = item->value.choice.urcb;
                        strDatasetPath = (char*)itemData.datSet.buf;
						pDatasetInfo = GetDatasetStruct(pLD,strDatasetPath);

						if (pDatasetInfo != NULL)
						{
							if (pDatasetInfo->numRcb>=MAX_RCB_VMD)
							{
								CLogPrint::LogFormatString(XLOGLEVEL_INFOR,"��ǰ������ƿ�·��%s,���ݼ�%s,��Ӧ�ı�����������%d,������󱨸���������.",
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
					// ��ӡ����
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
					// ��ӡ����
					SGCB_t itemData = item->value.choice.sgcb;
																				} break;
				case GetAllCBValuesResponsePDU__cbValue__Member__value_PR_gocb: {
					// ��ӡ����
					GoCB_t itemData = item->value.choice.gocb;
																				} break;
				case GetAllCBValuesResponsePDU__cbValue__Member__value_PR_msvcb: {
					// ��ӡ����
					MSVCB_t itemData = item->value.choice.msvcb;
																				 } break;
				default:
					break;
				}
			}

			// �ڴ��ͷ�
			Gsp_FreeAllCBValue(dataItem);
		}
		// �ڴ��ͷ�
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
		
		// �ͷ�Ԫ��ֵ
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

	// �ͷ�Ԫ��ֵ
	GspMmsValue_delete(dataInfo);
	GspLinkedList_destroyStatic(pRptDataList);


#endif

	return ret;
}
#endif


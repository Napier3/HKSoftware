//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgData.cpp  CTcpEdgePkgData


#include "stdafx.h"
#include "TcpEdgePkgData.h"
#include "TcpEdgePkgData_ConInstallReq.h"
#include "TcpEdgePkgData_TimeSyncReq.h"
#include "TcpEdgePkgData_DeviceUpdateReq.h"
#include "TcpEdgePkgData_DeviceUpdateStatusReq.h"
#include "TcpEdgePkgData_DeviceCtrlReq.h"
#include "TcpEdgePkgData_DeviceConfigReq.h"
#include "TcpEdgePkgData_ConStatusReq.h"
#include "TcpEdgePkgData_ConStartReq.h"
#include "TcpEdgePkgData_ConStopReq.h"
#include "TcpEdgePkgData_ConRestartReq.h"
#include "TcpEdgePkgData_ConRemoveReq.h"
#include "TcpEdgePkgData_ConGetConfigReq.h"
#include "TcpEdgePkgData_ConSetConfigReq.h"
#include "TcpEdgePkgData_ModelChange.h"
#include "TcpEdgePkgData_DevAdd.h"
#include "TcpEdgePkgData_DevUpdate.h"
#include "TcpEdgePkgData_ModelDevRead.h"
#include "TcpEdgePkgData_DataSubs.h"
#include "TcpEdgePkgData_GetDataSubs.h"
#include "TcpEdgePkgData_DataSpont.h"
#include "TcpEdgePkgData_DataRead.h"
#include "TcpEdgePkgData_ParaRead.h"
#include "TcpEdgePkgData_ParaCancel.h"
#include "TcpEdgePkgData_ParaActivate.h"
#include "TcpEdgePkgData_AppSetConfigReq.h"
#include "TcpEdgePkgData_AppGetConfigReq.h"
#include "TcpEdgePkgData_AppDisableReq.h"
#include "TcpEdgePkgData_AppEnableReq.h"
#include "TcpEdgePkgData_AppRemoveReq.h"
#include "TcpEdgePkgData_AppStopReq.h"
#include "TcpEdgePkgData_AppStartReq.h"
#include "TcpEdgePkgData_AppStatusReq.h"
#include "TcpEdgePkgData_TimeReadReq.h"
#include "TcpEdgePkgData_DeviceInfoReq.h"
#include "TcpEdgePkgData_DeviceStatusReq.h"
#include "TcpEdgePkgData_GetHisData.h"
#include "TcpEdgePkgData_ParaSet.h"
#include "TcpEdgePkgData_CtrlCmd.h"
#include "TcpEdgePkgData_GetTopoFile.h"
#include "TcpEdgePkgData_GetMessage.h"
#include "TcpEdgePkgData_FileGet.h"
#include "TcpEdgePkgData_AppInstallReq.h"
#include "TcpEdgePkgData_ContGetLogReq.h"
#include "TcpEdgePkgData_AppGetLogReq.h"
#include "TcpEdgePkgData_AppGetCfgFileReq.h"
#include "TcpEdgePkgData_AppSetCfgFileReq.h"
#include "TcpEdgePkgData_GetHisEvent.h"
#include "TcpEdgePkgData_GetModel.h"
#include "TcpEdgePkgData_DeviceGetLogReq.h"
#include "TcpEdgePkgData_AppInstallStatusReq.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData::CTcpEdgePkgData()
{
	//��ʼ������

	//��ʼ����Ա����
}

CTcpEdgePkgData::~CTcpEdgePkgData()
{
}

long CTcpEdgePkgData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTcpEdgePkgData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTcpEdgePkgData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CTcpEdgePkgData::InitAfterRead()
{
}

BOOL CTcpEdgePkgData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CTcpEdgePkgData *p = (CTcpEdgePkgData*)pObj;

	return TRUE;
}

BOOL CTcpEdgePkgData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData *p = (CTcpEdgePkgData*)pDest;

	return TRUE;
}

CBaseObject* CTcpEdgePkgData::Clone()
{
	CTcpEdgePkgData *p = new CTcpEdgePkgData();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData *p = new CTcpEdgePkgData();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

CDvmData* CTcpEdgePkgData::AddNewData(CDvmDataset* pDataset, const CString &strID, DWORD dwMust, CString strNote)
{
	CString strType = PkgData_Type_String + strNote;
	CDvmData* pData = pDataset->AddNewData(strID, strID, strType, "");
	pData->m_dwItemData = 1;
	pData->m_dwReserved = dwMust;
	return pData;
}

void CTcpEdgePkgData::AddNewData(CDvmDataset* pDataset, CDvmDataset* pObject, DWORD dwMust)
{
	pObject->m_dwItemData = 1;
	pObject->m_dwReserved = dwMust;
	pDataset->AddNewChild(pObject);
}

void CTcpEdgePkgData::AddNewDatas(CDvmDataset* pDataset, const CString &strID, DWORD dwMust)
{
	CDvmDatasetGroup* pDatasetArray = new CDvmDatasetGroup;
	pDatasetArray->m_strDataType = PkgData_Type_Array;
	pDatasetArray->m_strID = strID;
	pDatasetArray->m_dwItemData = 1;
	pDatasetArray->m_dwReserved = dwMust;
	pDataset->AddNewChild(pDatasetArray);
}

void CTcpEdgePkgData::AddNewDatas(CDvmDataset* pDataset, CDvmDataset* pObject, const CString &strID, DWORD dwMust)
{
	pObject->m_strDataType = PkgData_Type_Array;
	pObject->m_strID = strID;
	pObject->m_dwItemData = 1;
	pObject->m_dwReserved = dwMust;
	pDataset->AddNewChild(pObject);
}

CDvmDataset* CTcpEdgePkgData::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;
	return pDataset;
}

BOOL CTcpEdgePkgData::NewData(CDvmDatasetGroup* pArray)
{
	return FALSE;
}

//lmyע�ͣ�String���ж���ÿ�������н��д���, ֻ��array��String�ĵ��ô˺�����
//BOOL CTcpEdgePkgData::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
//{
	//�������жϱ����е�String�ֶ��Ƿ�����
	//CString strTemp;
	//CString strAttr(strAttrName);
	//CString strID(GetXmlElementKey());
	//BOOL bRet = oNode.xml_GetAttibuteValue(strAttrName,strAttrVal);
	//if(!strAttrVal.GetLength())
	//{
	//	//ֵ������ʱ����Ƿ����
	//	for(int i = 0; i < 64; i++)
	//	{
	//		if(m_arrayNotMust[i] == strAttr)
	//		{
	//			return bRet;
	//		}
	//	}

	//	strTemp.Format("[%s]=>[%s]�����ֶ�ȱʧ;\n", strID, strAttr);
	//	m_strErrorInfo += strTemp;
	//}
	//else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	//{
	//	//ֵ����ʱ��������Ƿ���ȷ
	//	strTemp.Format("[%s]=>[%s]�ֶ����ʹ���;\n", strID, strAttrName);
	//	m_strErrorInfo += strTemp;
	//}

//	return bRet;
//}

CTcpEdgePkgData* CTcpEdgePkgData::GetPrcdrDataByID(const CString& strPrcdrID)
{
	CTcpEdgePkgData* pPkgData = NULL;
 	if(strPrcdrID == PkgData_TimeSyncReq)
 	{
 		pPkgData = new CTcpEdgePkgData_TimeSyncReq;
 	}
	else if(strPrcdrID == PkgData_TimeReadReq)
	{
		pPkgData = new CTcpEdgePkgData_TimeReadReq;
	}
 	else if(strPrcdrID == PkgData_DeviceUpdateReq)   //�豸����
 	{
 		pPkgData = new CTcpEdgePkgData_DeviceUpdateReq();
 	}
 	else if(strPrcdrID == PkgData_DeviceUpdateStatusReq)
 	{
 		pPkgData = new CTcpEdgePkgData_DeviceUpdateStatusReq();
 	}
 	else if(strPrcdrID == PkgData_DeviceCtrlReq)     //�豸����
 	{
 		pPkgData = new CTcpEdgePkgData_DeviceCtrlReq();
 	}
	else if(strPrcdrID == PkgData_DeviceInfoReq)     //�豸����
	{
		pPkgData = new CTcpEdgePkgData_DeviceInfoReq();
	}
	else if(strPrcdrID == PkgData_DeviceStatusReq) 
	{
		pPkgData = new CTcpEdgePkgData_DeviceStatusReq();
	}
 	else if(strPrcdrID == PkgData_DeviceConfigReq)     //�豸���ò����޸�
 	{
 		pPkgData = new CTcpEdgePkgData_DeviceConfigReq();
 	}
 	else if(strPrcdrID == PkgData_ConInstallReq)     //������װ
 	{
 		pPkgData = new CTcpEdgePkgData_ConInstallReq();
 	}
 	else if(strPrcdrID == PkgData_ConStatusReq)     //����״̬��ѯ
 	{
 		pPkgData = new CTcpEdgePkgData_ConStatusReq();
 	}
 	else if(strPrcdrID == PkgData_ConStartReq)     //��������
 	{
 		pPkgData = new CTcpEdgePkgData_ConStartReq();
 	}	
 	else if(strPrcdrID == PkgData_ConStopReq)     //����ֹͣ
 	{
 		pPkgData = new CTcpEdgePkgData_ConStopReq();
 	}	
 	else if(strPrcdrID == PkgData_ConRestartReq)     //��������
 	{
 		pPkgData = new CTcpEdgePkgData_ConRestartReq();
 	}	
 	else if(strPrcdrID == PkgData_ConRemoveReq)     //����ɾ��
 	{
 		pPkgData = new CTcpEdgePkgData_ConRemoveReq();
 	}	
 	else if(strPrcdrID == PkgData_ConGetConfigReq)     //�������ò�ѯ
 	{
 		pPkgData = new CTcpEdgePkgData_ConGetConfigReq();
 	}
 	else if(strPrcdrID == PkgData_ConSetConfigReq)     //���������޸�
 	{
 		pPkgData = new CTcpEdgePkgData_ConSetConfigReq();
 	}
	else if(strPrcdrID == PkgData_ContGetLogReq)     //���������޸�
	{
		pPkgData = new CTcpEdgePkgData_ContGetLogReq();
	}
 	else if(strPrcdrID == PkgData_ModelChange)     //ģ�ͱ仯����
 	{
 		pPkgData = new CTcpEdgePkgData_ModelChange();
 	}
 	else if(strPrcdrID == PkgData_DevAdd)     //������豸
 	{
 		pPkgData = new CTcpEdgePkgData_DevAdd();
 	}
 	else if(strPrcdrID == PkgData_DevUpdate)     //�������豸״̬
 	{
 		pPkgData = new CTcpEdgePkgData_DevUpdate();
 	}
 	else if(strPrcdrID == PkgData_ModelDevRead)     //���豸��Ϣ��ѯ
 	{
 		pPkgData = new CTcpEdgePkgData_ModelDevRead();
 	}
	else if(strPrcdrID == PkgData_GetModel)     //���豸��Ϣ��ѯ
	{
		pPkgData = new CTcpEdgePkgData_GetModel();
	}
 	else if(strPrcdrID == PkgData_DataSubs)     //���ݶ���
 	{
 		pPkgData = new CTcpEdgePkgData_DataSubs();
 	}
 	else if(strPrcdrID == PkgData_GetDataSubs)     //���ݶ��Ĳ�ѯ
 	{
 		pPkgData = new CTcpEdgePkgData_GetDataSubs();
 	}
 	else if(strPrcdrID == PkgData_DataSpont)    //���������ϱ�
 	{
 		pPkgData = new CTcpEdgePkgData_DataSpont();
 	}
 	else if(strPrcdrID == PkgData_DataRead)     //���ݲ�ѯ
 	{
 		pPkgData = new CTcpEdgePkgData_DataRead();
 	}
 	else if(strPrcdrID == PkgData_ParaRead)     //��������ֵ��ѯ
 	{
 		pPkgData = new CTcpEdgePkgData_ParaRead();
 	}
 	else if(strPrcdrID == PkgData_ParaCancel)			//����������ֵԤ��
 	{
 		pPkgData = new CTcpEdgePkgData_ParaCancel();
 	}
 	else if (strPrcdrID == PkgData_ParaActivate)		//��������ֵ����
 	{
 		pPkgData = new CTcpEdgePkgData_ParaActivate();
 	}
 	else if (strPrcdrID == PkgData_AppSetConfigReq)		//Ӧ�������޸�
 	{
 		pPkgData = new CTcpEdgePkgData_AppSetConfigReq();
 	}
 	else if (strPrcdrID == PkgData_AppGetConfigReq)		//Ӧ�����ò�ѯ
 	{
 		pPkgData = new CTcpEdgePkgData_AppGetConfigReq();
 	}
 	else if (strPrcdrID == PkgData_AppDisableReq)		//Ӧ��ȥʹ��
 	{
 		pPkgData = new CTcpEdgePkgData_AppDisableReq();
 	}
 	else if (strPrcdrID == PkgData_AppEnableReq)		//Ӧ��ʹ��
 	{
 		pPkgData = new CTcpEdgePkgData_AppEnableReq();
 	}
 	else if (strPrcdrID == PkgData_AppRemoveReq)		//Ӧ��ж��
 	{
 		pPkgData = new CTcpEdgePkgData_AppRemoveReq();
 	}
 	else if (strPrcdrID == PkgData_AppStopReq)			//Ӧ��ֹͣ
 	{
 		pPkgData = new CTcpEdgePkgData_AppStopReq();
 	}
 	else if (strPrcdrID == PkgData_AppStartReq)			//Ӧ������
 	{
 		pPkgData = new CTcpEdgePkgData_AppStartReq();
 	}
 	else if (strPrcdrID == PkgData_AppStatusReq)		//Ӧ��״̬��ѯ
 	{
 		pPkgData = new CTcpEdgePkgData_AppStatusReq();
 	}
	else if (strPrcdrID == PkgData_AppGetLogReq)
	{
		pPkgData = new CTcpEdgePkgData_AppGetLogReq();
	}
	else if (strPrcdrID == PkgData_GetHisData)		
	{
		pPkgData = new CTcpEdgePkgData_GetHisData();
	}
	else if (strPrcdrID == PkgData_ParaSet)		
	{
		pPkgData = new CTcpEdgePkgData_ParaSet();
	}
	else if (strPrcdrID == PkgData_CtrlCmd)		
	{
		pPkgData = new CTcpEdgePkgData_CtrlCmd();
	}
	else if (strPrcdrID == PkgData_GetTopoFile)		
	{
		pPkgData = new CTcpEdgePkgData_GetTopoFile();
	}
	else if (strPrcdrID == PkgData_GetMessage)		
	{
		pPkgData = new CTcpEdgePkgData_GetMessage();
	}
	else if (strPrcdrID == PkgData_FileGet)		
	{
		pPkgData = new CTcpEdgePkgData_FileGet();
	}
	else if (strPrcdrID == PkgData_AppInstallReq)		
	{
		pPkgData = new CTcpEdgePkgData_AppInstallReq();
	}
	else if(strPrcdrID == PkgData_AppInstallStatusReq)
	{
		pPkgData = new CTcpEdgePkgData_AppInstallStatusReq();
	}
	else if(strPrcdrID == PkgData_AppGetCfgFileReq)
	{
		pPkgData = new CTcpEdgePkgData_AppGetCfgFileReq();
	}
	else if(strPrcdrID == PkgData_AppSetCfgFileReq)
	{
		pPkgData = new CTcpEdgePkgData_AppSetCfgFileReq();
	}
	else if(strPrcdrID == PkgData_GetHisEvent)
	{
		pPkgData = new CTcpEdgePkgData_GetHisEvent();
	}
	else if(strPrcdrID == PkgData_DeviceGetLogReq)
	{
		pPkgData = new CTcpEdgePkgData_DeviceGetLogReq();
	}

	return pPkgData;
}


//�ж������Ƿ�Ϸ�,��ʽ�Ƿ���ȷ
QString CTcpEdgePkgData::CheckTimeFormat(CString strID, CString strNodeID, CString strTime)
{
	QString strCheckResult = _T("");
	QDateTime dateTime = QDateTime::fromString(strTime, "yyyy-M-d H:m:s.z");
	bool bRet = dateTime.isValid();
	if(!bRet)
	{
		strCheckResult = QString(_T("�����󡿡�������Χ��%1��[Data]=>[%2]�ֶθ�ʽ������Χ;\n")).arg(strID).arg(strNodeID);
	}

	return strCheckResult;
}

QString CTcpEdgePkgData::CheckDateLegal(CString strID, CString strNodeID, long nyear, long nmonth, long nday, long nHour, long nMinute, long nSecond, long nMillisecond)
{
	QString strCheckResult = _T("");
	if(!isdigit(nyear))
	{
		strCheckResult = QString(_T("�����󡿡�������Χ��%1��[Data]=>[%2]�ֶ�������Year������Χ;\n")).arg(strID).arg(strNodeID);
		return strCheckResult;
	}
	else if (nmonth > 12 || nmonth < 1)
	{
		strCheckResult = QString(_T("�����󡿡�������Χ��%1��[Data]=>[%2]�ֶ�������Month������Χ;\n")).arg(strID).arg(strNodeID);
		return strCheckResult;
	}
	else
	{
		if (nyear % 4 == 0 && nyear % 100 != 0 || nyear % 400 == 0)//������
		{
			if (nmonth == 2)
			{
				if (nday > 29 || nday < 1)
				{
					strCheckResult = QString( _T("�����󡿡�������Χ��%1��[Data]=>[%2]�ֶ�������Day������Χ;\n")).arg(strID).arg(strNodeID);
					return strCheckResult;
				}
				else
				{
					strCheckResult = _T("");
					return strCheckResult;
				}
			}
		}

		if (nmonth == 4 || nmonth == 6 || nmonth == 9 || nmonth == 11)
		{
			if (nday < 1 || nday>30)
			{
				strCheckResult = QString( _T("�����󡿡�������Χ��%1��[Data]=>[%2]�ֶ�������Day������Χ;\n")).arg(strID).arg(strNodeID);
				return strCheckResult;
			}
			else 
			{
				strCheckResult = _T("");
				return strCheckResult;
			}
		}
		else if (nmonth != 2)
		{
			if (nday < 1 || nday>31)
			{
				strCheckResult = QString( _T("�����󡿡�������Χ��%1��[Data]=>[%2]�ֶ�������Day������Χ;\n")).arg(strID).arg(strNodeID);
				return strCheckResult;
			}
			else
			{
				strCheckResult = _T("");
				return strCheckResult;
			}
		}
		else
		{
			if (nday < 1 || nday>28)
			{
				strCheckResult = QString( _T("�����󡿡�������Χ��%1��[Data]=>[%2]�ֶ�������Day������Χ;\n")).arg(strID).arg(strNodeID);
				return strCheckResult;
			}
			else
			{
				strCheckResult = _T("");
				return strCheckResult;
			}
		}
	}

	if(nHour<0 || nHour>23)
	{
		strCheckResult = QString( _T("�����󡿡�������Χ��%1��[Data]=>[%2]�ֶ�������Hour������Χ;\n")).arg(strID).arg(strNodeID);
		return strCheckResult;
	}
	else
	{
		if(nMinute<0 || nMinute>60)
		{
			strCheckResult = QString(_T("�����󡿡�������Χ��%1��[Data]=>[%2]�ֶ�������Minute������Χ;\n")).arg(strID).arg(strNodeID);
			return strCheckResult;
		}
		else
		{
			if(nSecond<0 || nSecond>60)
			{
				strCheckResult = QString(_T("�����󡿡�������Χ��%1��[Data]=>[%2]�ֶ�������Second������Χ;\n")).arg(strID).arg(strNodeID);
				return strCheckResult;
			}
			else
			{
				if(nMillisecond<0 || nMillisecond>999)
				{
					strCheckResult = QString(_T("�����󡿡�������Χ��%1��[Data]=>[%2]�ֶ�������Millisecond������Χ;\n")).arg(strID).arg(strNodeID);
					return strCheckResult;
				}
			}
		}
	}

	return strCheckResult;
}


//�жϰٷֱ���Ĳ�����ʽ�ͷ�Χ�Ƿ���ȷ
QString CTcpEdgePkgData::CheckRangePer(CString strID, CString strNodeID, CString strNode)
{
	QString strTemp = _T("");
	BOOL bNum = FALSE;
	char* pTemp = const_cast<char*>(strNode.GetString());

	for(char a = '0'; a <= '9';a++)
	{
		if(pTemp[0] == a)
		{
			bNum = TRUE;
			break;
		}
	}
	if(bNum && pTemp[strNode.GetLength()-1] == '%')
	{
		CString strTemp = _T("");
		for(int i=0; i<strNode.GetLength()-1; i++)
		{
			strTemp += pTemp[i];
		}

		strNode = strTemp;
	}

	if(bNum)
	{
		if(atof(strNode.GetString())<0 || atof(strNode.GetString()) >100)
		{
			strTemp = QString(_T("�����󡿡�������Χ��%1: [Data]=>[%2]�ֶγ�����Χ;\n")).arg(strID).arg(strNodeID);
		}
	}
	else
	{
		strTemp = QString(_T("�����󡿡�������Χ��%1: [Data]=>[%2]�ֶθ�ʽ������Χ;\n")).arg(strID).arg(strNodeID);
	}


	return strTemp;
}

void CTcpEdgePkgData::SetDataFormat(CDvmData* pData, CString strFormat, long nParams, ...)
{
	pData->m_strFormat = strFormat;

	va_list list;
	va_start(list, nParams);

	for (int i = 0; i < nParams; i++)
	{
		CString strText = va_arg(list, char*);
		CDvmValue* pValue = new CDvmValue;
		pValue->m_strID = pValue->m_strValue = strText;
		pData->AddNewValue(pValue);
	}

	va_end(list);
}
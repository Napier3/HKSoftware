#include "stdafx.h"
#include "TcpEdgeDevice.h"
#include "TcpEdgeModelParser.h"
#include "TcpEdgeGlobalDef.h"
#include "Pkg/Pkg_DataSpontDevs.h"
#include "Pkg/Pkg_DataSpontDev.h"
#include "Pkg/Pkg_DataSpontDevSvcs.h"
#include "Pkg/Pkg_DataSpontDevSvc.h"
#include "Pkg/Pkg_DataSpontDevSvcDLs.h"
#include "Pkg/Pkg_DataSpontDevSvcDL.h"
#include <QFileInfo>

CTcpEdgeModelParser::CTcpEdgeModelParser()
{
	m_pDevice = NULL;
}

CTcpEdgeModelParser::~CTcpEdgeModelParser()
{

}

void CTcpEdgeModelParser::ParseFile(CJSON* pJson, CDvmDatasetGroup* pDatasetGroup)
{
	while (pJson)
	{
		if(pJson->type == CJSON_String)
		{
			pDatasetGroup->AddNewData(pJson->string,pJson->string,"string",pJson->valuestring);
		}
		else if(pJson->type == CJSON_Array)
		{
			CDvmDatasetGroup* pGroup = new CDvmDatasetGroup;
			pGroup->m_strID = pJson->string;
			pGroup->m_strDataType = "array";
			ParseFile(pJson->child, pGroup);
			pDatasetGroup->AddNewChild(pGroup);
		}
		else if(pJson->type == CJSON_Object)
		{
			CDvmDatasetGroup* pGroup = new CDvmDatasetGroup;
			pGroup->m_strID = pJson->string;
			pGroup->m_strDataType = "object";
			ParseFile(pJson->child, pGroup);
			pDatasetGroup->AddNewChild(pGroup);
		}
		pJson = pJson->next;
	}
}

void CTcpEdgeModelParser::ParseFile(const CString strFile)
{
	m_oGroup.DeleteAll();
	m_oDataMapping.DeleteAll();
	m_strParseErrorInfo.clear();

	QFileInfo find(strFile);
	if(!find.exists())
	{
		m_strParseErrorInfo = "�����󡿡�ģ�ͽ��������ļ�������!";
		return;
	}

	CJSON* pRoot = CJSON_Open_File(strFile.GetString());
	if(!pRoot)
	{
		//json��ʽ����ȷ
		m_strParseErrorInfo = "�����󡿡�ģ�ͽ�������JSON��ʽ����ʧ��!";
		m_oDataMapping.DeleteAll();
		return;
	}

	CJSON* pJson = pRoot->child;
	ParseFile(pJson, &m_oGroup);

	//services
	CDvmDatasetGroup* pServices = (CDvmDatasetGroup*)m_oGroup.FindByID(PkgData_Node_services);
	if(!pServices)
	{
		//������ң��ң�ŵȸ��ڵ�
		m_strParseErrorInfo = "�����󡿡�ģ�ͽ������󡿲�����Services��Ӧ�ڵ�!";
		return;
	}

	POS pos = pServices->GetHeadPosition();
	while (pos)
	{
		CDvmDatasetGroup* pService = (CDvmDatasetGroup*)pServices->GetNext(pos);
		if(pService)
		{
			CDvmData* pID = (CDvmData*)pService->FindByID(PkgData_Node_serviceId);
			if (!pID)
			{
				//������ң��ң��ӳ������
				m_strParseErrorInfo = "�����󡿡�ģ�ͽ������󡿲�����ServiceId��Ӧ�ڵ�!";
				m_oDataMapping.DeleteAll();
				return;
			}

			CDvmData* pServiceData = new CDvmData;
			pServiceData->m_strID = pServiceData->m_strName = pID->m_strValue;
			m_oDataMapping.AddNewChild(pServiceData);

			CString strDataType = pID->m_strValue;
			CDvmData* pDOs = (CDvmData*)pService->FindByID(PkgData_Node_DOs);
			if (!pDOs)
			{
				//������ң��ң��ӳ������
				m_strParseErrorInfo = "�����󡿡�ģ�ͽ������󡿲�����DOs��Ӧ�ڵ�!";
				m_oDataMapping.DeleteAll();
				return;
			}

			POS posDO = pDOs->GetHeadPosition();
			while (posDO)
			{
				CDvmDatasetGroup* pDO = (CDvmDatasetGroup*)pDOs->GetNext(posDO);
				CDvmData* pLDname = (CDvmData*)pDO->FindByID(PkgData_Node_LDname);
				CDvmData* pLNtype = (CDvmData*)pDO->FindByID(PkgData_Node_LNtype);
				CDvmData* pLNinst = (CDvmData*)pDO->FindByID(PkgData_Node_LNinst);
				CDvmData* pDOname = (CDvmData*)pDO->FindByID(PkgData_Node_DOname);
				CDvmData* pDesc = (CDvmData*)pDO->FindByID(PkgData_Node_description);
				if(pLDname && pLNtype && pLNinst && pDOname && pDesc)
				{
					QString strID, strDesc;
					strID = QString("%1.%2.%3.%4").arg(pLDname->m_strValue).arg(pLNtype->m_strValue).arg(pLNinst->m_strValue).arg(pDOname->m_strValue);
					strDesc = pDesc->m_strValue;

					CDvmValue* pValue = new CDvmValue;
					pValue->m_strID = strID;
					pValue->m_strName = strDesc;
					pValue->m_strDataType = strDataType;
					pServiceData->AddNewChild(pValue);
				}
				else
				{
					//ӳ���ϵ����
					m_strParseErrorInfo = "�����󡿡�ģ�ͽ������󡿵��ӳ��ڵ�ȱʧ!";
					m_oDataMapping.DeleteAll();
					return;
				}
			}
		}
	}

	CJSON_Delete(pRoot);
}

void CTcpEdgeModelParser::ParseDatas(CExBaseList* pNode, CExBaseList* pRecord)
{
	CPkg_DataSpontDevSvcDLs* pDLs = (CPkg_DataSpontDevSvcDLs*)pNode->FindByID(PkgData_Node_DataList);
	if(pDLs)
	{
		POS pos = pDLs->GetHeadPosition();
		while (pos)
		{
			CPkg_DataSpontDevSvcDL* pDL = (CPkg_DataSpontDevSvcDL*)pDLs->GetNext(pos);
			CDvmValue* pMappingValue = (CDvmValue*)pRecord->FindByID(pDL->m_strDataRefer);
			if(pMappingValue)
			{
				pMappingValue->m_strValue = pDL->m_strValue;
			}
			else
			{
				QString strLog = QString("�����󡿡�ģ��ӳ����󡿵��ڵ�[%1]ȱʧ!\n").arg(pDL->m_strDataRefer);
				m_strErrorInfo += strLog;
			}
		}
	}
	else
	{
		QString strLog = QString("�����󡿡�ģ��ӳ����󡿵��ڵ�[%1]ȱʧ!\n").arg(PkgData_Node_DataList);
		m_strErrorInfo += strLog;
	}
}

void CTcpEdgeModelParser::ParseServices(CExBaseList* pNode, CExBaseList* pRecord)
{
	CPkg_DataSpontDevSvcs* pSvcs = (CPkg_DataSpontDevSvcs*)pNode->FindByID(PkgData_Node_Services);
	if(pSvcs)
	{
		POS pos = pSvcs->GetHeadPosition();
		while (pos)
		{
			CPkg_DataSpontDevSvc* pSvc = (CPkg_DataSpontDevSvc*)pSvcs->GetNext(pos);
			QString strServiceId = pSvc->m_strServiceId;
			CExBaseList* pModelDatas = (CExBaseList*)pRecord->FindByID(strServiceId);
			if(pModelDatas)
			{
				ParseDatas(pSvc, pModelDatas);
			}
			else
			{
				QString strLog = QString("�����󡿡�ģ��ӳ����󡿵��ڵ�[%1]ȱʧ!\n").arg(strServiceId);
				m_strErrorInfo += strLog;
			}
		}
	}
	else
	{
		QString strLog = QString("�����󡿡�ģ��ӳ����󡿱��Ľڵ�[%1]ȱʧ!\n").arg(PkgData_Node_Services);
		m_strErrorInfo += strLog;
	}
}

void CTcpEdgeModelParser::ParseDevices(CExBaseList* pNode)
{
	CPkg_DataSpontDevs* pDevs = (CPkg_DataSpontDevs*)pNode->FindByID(PkgData_Node_Devices);
	if(pDevs)
	{
		//����dev�ֱ���벻ͬ��ģ���ж�
		POS pos = pDevs->GetHeadPosition();
		while (pos)
		{
			CPkg_DataSpontDev* pDev = (CPkg_DataSpontDev*)pDevs->GetNext(pos);
			QString strDeviceId = pDev->m_strDeviceId;
			CModelRecord* pRecord = m_pDevice->m_oRecord.FindModelByDeviceId(strDeviceId);
			if(pRecord)
			{	
				ParseServices(pDev, &pRecord->m_datas);
			}
			else
			{
				QString strLog = QString("�����桿��ģ��ӳ�侯�桿δ��⵽�豸[%1]��ģ�͵��!\n").arg(strDeviceId);
				m_strErrorInfo += strLog;
			}
		}
	}
	else
	{
		QString strLog = QString("�����󡿡�ģ��ӳ����󡿱��Ľڵ�[%1]ȱʧ!\n").arg(PkgData_Node_Devices);
		m_strErrorInfo += strLog;
	}
}

void CTcpEdgeModelParser::ParsePkg(CTcpEdgePkgData_DataSpont* pDataSpont)
{
	m_strErrorInfo.clear();
	ParseDevices(pDataSpont);
}
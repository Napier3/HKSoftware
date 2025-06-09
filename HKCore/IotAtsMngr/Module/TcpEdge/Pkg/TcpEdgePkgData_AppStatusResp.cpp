//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgData_AppStatusResp.cpp  CTcpEdgePkgData_AppStatusResp


#include "stdafx.h"
#include "TcpEdgePkgData_AppStatusResp.h"
#include "Pkg_AppStatusResp_AppStatus.h"
#include "Pkg_AppStatusResp_AppStatu.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_AppStatusResp::CTcpEdgePkgData_AppStatusResp()
{
	//��ʼ������

	//��ʼ����Ա����
}

CTcpEdgePkgData_AppStatusResp::~CTcpEdgePkgData_AppStatusResp()
{
}

BOOL CTcpEdgePkgData_AppStatusResp::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
{
	//�������жϱ����е�String�ֶ��Ƿ�����
	QString strTemp;
	CString strAttr(strAttrName);
	CString strID(GetXmlElementKey());
	BOOL bRet = oNode.xml_GetAttibuteValue(strAttrName,strAttrVal);
	if(!strAttrVal.GetLength())
	{
		//ֵ������ʱ����Ƿ����
		for(int i = 0; i < 64; i++)
		{
			if(m_arrayNotMust[i] == strAttr)
			{
				return bRet;
			}
		}

		strTemp = QString("�����󡿡�������ȱʧ��AppStatusResp��[%1]=>[%2]�����ֶ�ȱʧ;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//ֵ����ʱ��������Ƿ���ȷ
		strTemp = QString("�����󡿡����������AppStatusResp��[%1]=>[%2]�ֶ����ʹ���;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgData_AppStatusResp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strContainerKey, oNode, m_strContainer);

	//ȡ��JSON
	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	if(pJson == NULL)
	{
		return 0;
	}

	//���JSON�������Ƿ���ڽڵ㣬������̬���������
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_AppStatus);
	if(pDatasJson)
	{
		CPkg_AppStatusResp_AppStatus* pDatas = new CPkg_AppStatusResp_AppStatus;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_AppStatus;
		AddNewChild(pDatas);

		//����Devices����̬�����ӽṹ
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_AppStatusResp_AppStatu* pData = new CPkg_AppStatusResp_AppStatu;

			CJsonNode* pTempJsonNode = new CJsonNode(pDatasChild);
			//����������ĺ������������ݣ���������а������飬ȥ����ĸú����������ƴ���
			pData->m_strErrorInfo = m_strErrorInfo;
			pData->m_strNecessityLack = m_strNecessityLack;
			pData->m_strNecessityErr = m_strNecessityErr;
			pData->m_strRangeOut = m_strRangeOut;
			pData->m_strReturnFalse = m_strReturnFalse;
			pData->XmlReadOwn(*(CXmlRWNodeBase*)pTempJsonNode, pXmlRWKeys);
			m_strErrorInfo = pData->m_strErrorInfo;
			m_strNecessityLack = pData->m_strNecessityLack;
			m_strNecessityErr = pData->m_strNecessityErr;
			m_strRangeOut = pData->m_strRangeOut;
			m_strReturnFalse = pData->m_strReturnFalse;

			delete pTempJsonNode;
			//������ɺ���Ϊ�μ�������ӵ�pDevices
			pDatas->AddNewChild(pData);	

			pDatasChild = pDatasChild->next;
		}
	}
	else
	{
		QString strTemp;
		CString strID(GetXmlElementKey());
		strTemp = QString("�����󡿡�������ȱʧ��AppStatusResp��[%1]=>[%2] �����ֶ�arrayȱʧ;\n").arg(strID).arg(PkgData_Node_AppStatus);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}

	return 0;
}

long CTcpEdgePkgData_AppStatusResp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strContainerKey, oElement, m_strContainer);

			CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	if(pJson == NULL)
	{
		return 0;
	}

	CPkg_AppStatusResp_AppStatus* pDatas = (CPkg_AppStatusResp_AppStatus*)FindByID(PkgData_Node_AppStatus);
	if(pDatas == NULL)
	{
		return 0;
	}

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while(pos)
	{
		CPkg_AppStatusResp_AppStatu* pData = (CPkg_AppStatusResp_AppStatu*)pDatas->GetNext(pos);
		CJSON* pDataJson = CJSON_CreateObject();
		CJsonNode* pTempJsonNode = new CJsonNode(pDataJson);
		pData->XmlWriteOwn(oXMLDoc, *(CXmlRWElementBase*)pTempJsonNode, pXmlRWKeys);
		delete pTempJsonNode;

		CJSON_AddItemToArray(pDatasJson, pDataJson);
	}

	CJSON_AddItemToObject(pJson, PkgData_Node_AppStatus, pDatasJson);

	DeleteByID(PkgData_Node_AppStatus);
	return 0;
}

long CTcpEdgePkgData_AppStatusResp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strContainer);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strContainer);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strContainer);
	}
	return 0;
}

void CTcpEdgePkgData_AppStatusResp::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_AppStatusResp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_AppStatusResp *p = (CTcpEdgePkgData_AppStatusResp*)pObj;

	if(m_strContainer != p->m_strContainer)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_AppStatusResp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_AppStatusResp *p = (CTcpEdgePkgData_AppStatusResp*)pDest;

	p->m_strContainer = m_strContainer;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_AppStatusResp::Clone()
{
	CTcpEdgePkgData_AppStatusResp *p = new CTcpEdgePkgData_AppStatusResp();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_AppStatusResp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_AppStatusResp *p = new CTcpEdgePkgData_AppStatusResp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_AppStatusResp::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_AppStatusResp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_AppStatusResp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_AppStatusResp::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	return 0;
}

long CTcpEdgePkgData_AppStatusResp::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	return 0;
}


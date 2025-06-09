//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgData_GetModelResp.cpp  CTcpEdgePkgData_GetModelResp


#include "stdafx.h"
#include "TcpEdgePkgData_GetModelResp.h"
#include "Pkg_GetModelResp_Models.h"
#include "Pkg_GetModelResp_Model.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_GetModelResp::CTcpEdgePkgData_GetModelResp()
{
	//��ʼ������

	//��ʼ����Ա����
}

CTcpEdgePkgData_GetModelResp::~CTcpEdgePkgData_GetModelResp()
{
}

long CTcpEdgePkgData_GetModelResp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

		//ȡ��JSON
	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	if(pJson == NULL)
	{
		return 0;
	}

	//���JSON�������Ƿ����Links�ڵ㣬������̬����Links�����
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_Models);
	if(pDatasJson)
	{
		CPkg_GetModelResp_Models* pDatas = new CPkg_GetModelResp_Models;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_Models;
		AddNewChild(pDatas);

		//����Devices����̬�����ӽṹ
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_GetModelResp_Model* pData = new CPkg_GetModelResp_Model;

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
		strTemp = QString("�����󡿡�������ȱʧ��GetModelResp��[%1]=>[%2] �����ֶ�arrayȱʧ;\n").arg(strID).arg(PkgData_Node_Models);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	return 0;
}

long CTcpEdgePkgData_GetModelResp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

		CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	if(pJson == NULL)
	{
		return 0;
	}

	CPkg_GetModelResp_Models* pDatas = (CPkg_GetModelResp_Models*)FindByID(PkgData_Node_Models);
	if(pDatas == NULL)
	{
		return 0;
	}

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while(pos)
	{

		CPkg_GetModelResp_Model* pData = (CPkg_GetModelResp_Model*)pDatas->GetNext(pos);
		CJSON* pDataJson = CJSON_CreateObject();
		CJsonNode* pTempJsonNode = new CJsonNode(pDataJson);
		pData->XmlWriteOwn(oXMLDoc, *(CXmlRWElementBase*)pTempJsonNode, pXmlRWKeys);
		delete pTempJsonNode;

		CJSON_AddItemToArray(pDatasJson, pDataJson);
	}

	CJSON_AddItemToObject(pJson, PkgData_Node_Models, pDatasJson);

	DeleteByID(PkgData_Node_Models);

	return 0;
}

long CTcpEdgePkgData_GetModelResp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
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

void CTcpEdgePkgData_GetModelResp::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_GetModelResp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_GetModelResp *p = (CTcpEdgePkgData_GetModelResp*)pObj;

	return TRUE;
}

BOOL CTcpEdgePkgData_GetModelResp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_GetModelResp *p = (CTcpEdgePkgData_GetModelResp*)pDest;

	return TRUE;
}

CBaseObject* CTcpEdgePkgData_GetModelResp::Clone()
{
	CTcpEdgePkgData_GetModelResp *p = new CTcpEdgePkgData_GetModelResp();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_GetModelResp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_GetModelResp *p = new CTcpEdgePkgData_GetModelResp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_GetModelResp::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_GetModelResp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_GetModelResp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

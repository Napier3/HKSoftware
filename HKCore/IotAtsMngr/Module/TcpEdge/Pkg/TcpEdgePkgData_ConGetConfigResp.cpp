//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgData_ConGetConfigResp.cpp  CTcpEdgePkgData_ConGetConfigResp


#include "stdafx.h"
#include "TcpEdgePkgData_ConGetConfigResp.h"
#include "Pkg_ConGetConfigResp_ContCfg.h"
#include "Pkg_ConGetConfigResp_ContCfgs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_ConGetConfigResp::CTcpEdgePkgData_ConGetConfigResp()
{
	//��ʼ������

	//��ʼ����Ա����
}

CTcpEdgePkgData_ConGetConfigResp::~CTcpEdgePkgData_ConGetConfigResp()
{
}

long CTcpEdgePkgData_ConGetConfigResp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	//ȡ��JSON
	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	if(pJson == NULL)
	{
		return 0;
	}
	

	//���JSON�������Ƿ���ڽڵ㣬������̬���������
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_ContCfgs);
	if(pDatasJson)
	{
		CPkg_ConGetConfigResp_ContCfgs* pDatas = new CPkg_ConGetConfigResp_ContCfgs;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_ContCfgs;
		AddNewChild(pDatas);

		//����Devices����̬�����ӽṹ
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_ConGetConfigResp_ContCfg* pData = new CPkg_ConGetConfigResp_ContCfg;

			CJsonNode* pTempJsonNode = new CJsonNode(pDatasChild);
			//����������ĺ������������ݣ���������а������飬ȥ����ĸú����������ƴ���
			pData->m_strErrorInfo = m_strErrorInfo;
			pData->m_strNecessityLack = m_strNecessityLack;
			pData->m_strNecessityErr = m_strNecessityErr;
			pData->m_strRangeOut = m_strRangeOut;
			pData->m_strReturnFalse = m_strReturnFalse;
			pData->XmlRead(*(CXmlRWNodeBase*)pTempJsonNode, pXmlRWKeys);
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
		strTemp = QString("�����󡿡�������ȱʧ��ConGetConfigResp��[%1]=>[%2]�����ֶ�arrayȱʧ;\n").arg(strID).arg(PkgData_Node_ContCfgs);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}

	return 0;
}

long CTcpEdgePkgData_ConGetConfigResp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	if(pJson == NULL)
	{
		return 0;
	}

	CPkg_ConGetConfigResp_ContCfgs* pDatas = (CPkg_ConGetConfigResp_ContCfgs*)FindByID(PkgData_Node_ContCfgs);
	if(pDatas == NULL)
	{
		return 0;
	}

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while(pos)
	{

		CPkg_ConGetConfigResp_ContCfg* pData = (CPkg_ConGetConfigResp_ContCfg*)pDatas->GetNext(pos);
		CJSON* pDataJson = CJSON_CreateObject();
		CJsonNode* pTempJsonNode = new CJsonNode(pDataJson);
		pData->XmlWriteOwn(oXMLDoc, *(CXmlRWElementBase*)pTempJsonNode, pXmlRWKeys);
		pData->XmlWriteChildrenEx(pData, pDataJson);
		delete pTempJsonNode;

		CJSON_AddItemToArray(pDatasJson, pDataJson);
	}

	CJSON_AddItemToObject(pJson, PkgData_Node_ContCfgs, pDatasJson);

	DeleteByID(PkgData_Node_ContCfgs);
	return 0;
}

long CTcpEdgePkgData_ConGetConfigResp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CTcpEdgePkgData_ConGetConfigResp::InitAfterRead()
{
	/*if(m_strName == NULL)
	{
		m_StrError +=  "xxx ������";
	}*/

}

BOOL CTcpEdgePkgData_ConGetConfigResp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_ConGetConfigResp *p = (CTcpEdgePkgData_ConGetConfigResp*)pObj;

	return TRUE;
}

BOOL CTcpEdgePkgData_ConGetConfigResp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_ConGetConfigResp *p = (CTcpEdgePkgData_ConGetConfigResp*)pDest;

	return TRUE;
}

CBaseObject* CTcpEdgePkgData_ConGetConfigResp::Clone()
{
	CTcpEdgePkgData_ConGetConfigResp *p = new CTcpEdgePkgData_ConGetConfigResp();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_ConGetConfigResp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_ConGetConfigResp *p = new CTcpEdgePkgData_ConGetConfigResp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_ConGetConfigResp::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_ConGetConfigResp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_ConGetConfigResp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

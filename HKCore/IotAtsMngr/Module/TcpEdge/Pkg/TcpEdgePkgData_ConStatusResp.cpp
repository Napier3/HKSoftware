//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgData_ConStatusResp.cpp  CTcpEdgePkgData_ConStatusResp


#include "stdafx.h"
#include "TcpEdgePkgData_ConStatusResp.h"
#include "Pkg_ConStatusResp_ContStatu.h"
#include "Pkg_ConStatusResp_ContStatus.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_ConStatusResp::CTcpEdgePkgData_ConStatusResp()
{
	//��ʼ������

	//��ʼ����Ա����
}

CTcpEdgePkgData_ConStatusResp::~CTcpEdgePkgData_ConStatusResp()
{
}

long CTcpEdgePkgData_ConStatusResp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	//ȡ��JSON
	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	if(pJson == NULL)
	{
		return 0;
	}

	//���JSON�������Ƿ����LinkState�ڵ㣬������̬����LinkState�����
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_ContStatus);
	if(pDatasJson)
	{
		CPkg_ConStatusResp_ContStatus* pDatas = new CPkg_ConStatusResp_ContStatus;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_ContStatus;
		AddNewChild(pDatas);

		//����Devices����̬�����ӽṹ
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_ConStatusResp_ContStatu* pData = new CPkg_ConStatusResp_ContStatu;

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
		strTemp = QString("�����󡿡�������ȱʧ��ConStatusResp��[%1]=>[%2] �����ֶ�arrayȱʧ;\n").arg(strID).arg(PkgData_Node_ContStatus);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}

	return 0;
}

long CTcpEdgePkgData_ConStatusResp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	if(pJson == NULL)
	{
		return 0;
	}

	CPkg_ConStatusResp_ContStatus* pDatas = (CPkg_ConStatusResp_ContStatus*)FindByID(PkgData_Node_ContStatus);
	if(pDatas == NULL)
	{
		return 0;
	}

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while(pos)
	{
		/*�ַ�������
		CTcpEdgePkgString* pString = (CTcpEdgePkgString*)pDatas->GetNext(pos);
		CJSON* pStringJson = CJSON_CreateString(pString->m_strValue);
		CJSON_AddItemToArray(pDatasJson,pStringJson);
		*/

		CPkg_ConStatusResp_ContStatu* pData = (CPkg_ConStatusResp_ContStatu*)pDatas->GetNext(pos);
		CJSON* pDataJson = CJSON_CreateObject();
		CJsonNode* pTempJsonNode = new CJsonNode(pDataJson);
		pData->XmlWriteOwn(oXMLDoc, *(CXmlRWElementBase*)pTempJsonNode, pXmlRWKeys);
		delete pTempJsonNode;

		CJSON_AddItemToArray(pDatasJson, pDataJson);
	}

	CJSON_AddItemToObject(pJson, PkgData_Node_ContStatus, pDatasJson);

	DeleteByID(PkgData_Node_ContStatus);

	return 0;
}

long CTcpEdgePkgData_ConStatusResp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CTcpEdgePkgData_ConStatusResp::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_ConStatusResp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_ConStatusResp *p = (CTcpEdgePkgData_ConStatusResp*)pObj;

	return TRUE;
}

BOOL CTcpEdgePkgData_ConStatusResp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_ConStatusResp *p = (CTcpEdgePkgData_ConStatusResp*)pDest;

	return TRUE;
}

CBaseObject* CTcpEdgePkgData_ConStatusResp::Clone()
{
	CTcpEdgePkgData_ConStatusResp *p = new CTcpEdgePkgData_ConStatusResp();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_ConStatusResp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_ConStatusResp *p = new CTcpEdgePkgData_ConStatusResp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_ConStatusResp::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_ConStatusResp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_ConStatusResp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

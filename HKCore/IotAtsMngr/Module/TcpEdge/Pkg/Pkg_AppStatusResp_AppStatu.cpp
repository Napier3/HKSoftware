//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_AppStatusResp_AppStatu.cpp  CPkg_AppStatusResp_AppStatu


#include "stdafx.h"
#include "Pkg_AppStatusResp_AppStatu.h"
#include "Pkg_AppStatusResp_AppStaProcs.h"
#include "Pkg_AppStatusResp_AppStaProc.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPkg_AppStatusResp_AppStatu::CPkg_AppStatusResp_AppStatu()
{
	//初始化属性

	//初始化成员变量
}

CPkg_AppStatusResp_AppStatu::~CPkg_AppStatusResp_AppStatu()
{
}

BOOL CPkg_AppStatusResp_AppStatu::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
{
	//在这里判断报文中的String字段是否有误
	CString strTemp;
	CString strAttr(strAttrName);
	//CString strID(GetXmlElementKey());
	BOOL bRet = oNode.xml_GetAttibuteValue(strAttrName,strAttrVal);
	if(!strAttrVal.GetLength())
	{
		//值不存在时检查是否必需
		for(int i = 0; i < 64; i++)
		{
			if(m_arrayNotMust[i] == strAttr)
			{
				return bRet;
			}
		}

		strTemp = QString(_T("【错误】【必需项缺失】AppStatusResp：[%1]=>[%2$%3]必需字段缺失;\n")).arg(PkgData_Node_Data).arg(PkgData_Node_AppStatus).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString(_T("【错误】【必需项错误】AppStatusResp：[%1]=>[%2$%3]字段类型错误;\n")).arg(PkgData_Node_Data).arg(PkgData_Node_AppStatus).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CPkg_AppStatusResp_AppStatu::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strAppKey, oNode, m_strApp);
	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_strVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strAppHashKey, oNode, m_strAppHash);
	xml_GetAttibuteValue(pXmlKeys->m_strSrvNumberKey, oNode, m_strSrvNumber);

			//取到JSON
	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	if(pJson == NULL)
	{
		return 0;
	}
	

	//检测JSON报文中是否存在节点，存在则动态创建并添加
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_Process);
	if(pDatasJson)
	{
		CPkg_AppStatusResp_AppStaProcs* pDatas = new CPkg_AppStatusResp_AppStaProcs;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_Process;
		AddNewChild(pDatas);

		//遍历Devices，动态创建子结构
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_AppStatusResp_AppStaProc* pData = new CPkg_AppStatusResp_AppStaProc;

			CJsonNode* pTempJsonNode = new CJsonNode(pDatasChild);
			//调用子类里的函数来解析数据，如果子类中包含数组，去子类的该函数中做类似处理
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
			//解析完成后作为次级报文添加到pDevices
			pDatas->AddNewChild(pData);	

			pDatasChild = pDatasChild->next;
		}
	}
	else
	{
		QString strTemp;
		CString strID(GetXmlElementKey());
		strTemp = QString(_T("【错误】【必需项缺失】AppStatusResp：[%1]=>[%2$%3] 必需字段array缺失;\n")).arg(PkgData_Node_Data).arg(PkgData_Node_AppStatus).arg(PkgData_Node_Process);
		m_strErrorInfo += strTemp;
	}

	return 0;
}

long CPkg_AppStatusResp_AppStatu::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strAppKey, oElement, m_strApp);
	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_strVersion);
	xml_SetAttributeValue(pXmlKeys->m_strAppHashKey, oElement, m_strAppHash);
	xml_SetAttributeValue(pXmlKeys->m_strSrvNumberKey, oElement, m_strSrvNumber);

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	if(pJson == NULL)
	{
		return 0;
	}

	CPkg_AppStatusResp_AppStaProcs* pDatas = (CPkg_AppStatusResp_AppStaProcs*)FindByID(PkgData_Node_Process);
	if(pDatas == NULL)
	{
		return 0;
	}

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while(pos)
	{

		CPkg_AppStatusResp_AppStaProc* pData = (CPkg_AppStatusResp_AppStaProc*)pDatas->GetNext(pos);
		CJSON* pDataJson = CJSON_CreateObject();
		CJsonNode* pTempJsonNode = new CJsonNode(pDataJson);
		pData->XmlWriteOwn(oXMLDoc, *(CXmlRWElementBase*)pTempJsonNode, pXmlRWKeys);
		delete pTempJsonNode;

		CJSON_AddItemToArray(pDatasJson, pDataJson);
	}

	CJSON_AddItemToObject(pJson, PkgData_Node_Process, pDatasJson);

	DeleteByID(PkgData_Node_Process);
	return 0;
}

long CPkg_AppStatusResp_AppStatu::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strApp);
		BinarySerializeCalLen(oBinaryBuffer, m_strVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_strAppHash);
		BinarySerializeCalLen(oBinaryBuffer, m_strSrvNumber);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strApp);
		BinarySerializeRead(oBinaryBuffer, m_strVersion);
		BinarySerializeRead(oBinaryBuffer, m_strAppHash);
		BinarySerializeRead(oBinaryBuffer, m_strSrvNumber);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strApp);
		BinarySerializeWrite(oBinaryBuffer, m_strVersion);
		BinarySerializeWrite(oBinaryBuffer, m_strAppHash);
		BinarySerializeWrite(oBinaryBuffer, m_strSrvNumber);
	}
	return 0;
}

void CPkg_AppStatusResp_AppStatu::InitAfterRead()
{
}

BOOL CPkg_AppStatusResp_AppStatu::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_AppStatusResp_AppStatu *p = (CPkg_AppStatusResp_AppStatu*)pObj;

	if(m_strApp != p->m_strApp)
	{
		return FALSE;
	}

	if(m_strVersion != p->m_strVersion)
	{
		return FALSE;
	}

	if(m_strAppHash != p->m_strAppHash)
	{
		return FALSE;
	}

	if(m_strSrvNumber != p->m_strSrvNumber)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_AppStatusResp_AppStatu::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_AppStatusResp_AppStatu *p = (CPkg_AppStatusResp_AppStatu*)pDest;

	p->m_strApp = m_strApp;
	p->m_strVersion = m_strVersion;
	p->m_strAppHash = m_strAppHash;
	p->m_strSrvNumber = m_strSrvNumber;
	return TRUE;
}

CBaseObject* CPkg_AppStatusResp_AppStatu::Clone()
{
	CPkg_AppStatusResp_AppStatu *p = new CPkg_AppStatusResp_AppStatu();
	Copy(p);
	return p;
}

CBaseObject* CPkg_AppStatusResp_AppStatu::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPkg_AppStatusResp_AppStatu *p = new CPkg_AppStatusResp_AppStatu();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CPkg_AppStatusResp_AppStatu::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_AppStatusResp_AppStatu::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_AppStatusResp_AppStatu::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_AppStatusResp_AppStatu::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strAppKey, m_strApp);
	pRecordset->GetFieldValue(pXmlKeys->m_strVersionKey, m_strVersion);
	pRecordset->GetFieldValue(pXmlKeys->m_strAppHashKey, m_strAppHash);
	pRecordset->GetFieldValue(pXmlKeys->m_strSrvNumberKey, m_strSrvNumber);
	return 0;
}

long CPkg_AppStatusResp_AppStatu::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strAppKey, m_strApp);
	pRecordset->SetFieldValue(pXmlKeys->m_strVersionKey, m_strVersion);
	pRecordset->SetFieldValue(pXmlKeys->m_strAppHashKey, m_strAppHash);
	pRecordset->SetFieldValue(pXmlKeys->m_strSrvNumberKey, m_strSrvNumber);
	return 0;
}


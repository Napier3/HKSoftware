//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_AppGetConfigResp_AppCfg.cpp  CPkg_AppGetConfigResp_AppCfg

#include "stdafx.h"
#include "Pkg_AppGetConfigResp_AppCfg.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPkg_AppGetConfigResp_AppCfg::CPkg_AppGetConfigResp_AppCfg()
{
	//初始化属性

	//初始化成员变量
	m_pTcpEdgePkgCfgCpu = NULL;
	m_pTcpEdgePkgCfgMem = NULL;

	m_strObjectName[0] = _T(PkgData_Node_CfgCpu);
	m_strObjectName[1] = _T(PkgData_Node_CfgMem);

	for(int i = 0; i<2; i++)
	{
		m_bObjectMustExist[i] = FALSE;
	}
}

CPkg_AppGetConfigResp_AppCfg::~CPkg_AppGetConfigResp_AppCfg()
{
}

BOOL CPkg_AppGetConfigResp_AppCfg::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
{
	//在这里判断报文中的String字段是否有误
	QString strTemp;
	CString strAttr(strAttrName);
	CString strID(GetXmlElementKey());
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

		strTemp = QString(_T("【错误】【必需项缺失】AppGetConfigResp：[%1]=>[%2$%3]必需字段缺失;\n")).arg(PkgData_Node_Data).arg(PkgData_Node_AppCfgs).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;

	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString(_T("【错误】【必需项错误】AppGetConfigResp：[%1]=>[%2$%3]字段类型错误;\n")).arg(PkgData_Node_Data).arg(PkgData_Node_AppCfgs).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CPkg_AppGetConfigResp_AppCfg::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strAppKey, oNode, m_strApp);
	return 0;
}

long CPkg_AppGetConfigResp_AppCfg::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strAppKey, oElement, m_strApp);
	return 0;
}

long CPkg_AppGetConfigResp_AppCfg::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strApp);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strApp);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strApp);
	}
	return 0;
}

void CPkg_AppGetConfigResp_AppCfg::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGCPU)
		{
			m_pTcpEdgePkgCfgCpu = (CTcpEdgePkgCfgCpu*)p;
			m_strErrorInfo += m_pTcpEdgePkgCfgCpu->m_strErrorInfo;
			m_strNecessityLack += m_pTcpEdgePkgCfgCpu->m_strNecessityLack;
			m_strNecessityErr += m_pTcpEdgePkgCfgCpu->m_strNecessityErr;
		}
		else if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGMEM)
		{
			m_pTcpEdgePkgCfgMem = (CTcpEdgePkgCfgMem*)p;
			m_strErrorInfo += m_pTcpEdgePkgCfgMem->m_strErrorInfo;
			m_strNecessityLack += m_pTcpEdgePkgCfgMem->m_strNecessityLack;
			m_strNecessityErr += m_pTcpEdgePkgCfgMem->m_strNecessityErr;
		}
	}

	if (m_pTcpEdgePkgCfgCpu == NULL)
	{
		m_pTcpEdgePkgCfgCpu = (CTcpEdgePkgCfgCpu*)AddNewChild(new CTcpEdgePkgCfgCpu());
	}

	if (m_pTcpEdgePkgCfgMem == NULL)
	{
		m_pTcpEdgePkgCfgMem = (CTcpEdgePkgCfgMem*)AddNewChild(new CTcpEdgePkgCfgMem());
	}

	CString strTemp;
	CString strID(GetXmlElementKey());
	for(int i=0; i<2; i++)
	{
		if(! m_bObjectMustExist[i])
		{
			strTemp = QString(_T("【错误】【必需项缺失】AppGetConfigResp：[%1]=>[%2]必需字段object缺失;\n")).arg(PkgData_Node_Data).arg(m_strObjectName[i]);
			m_strErrorInfo += strTemp;
		}
	}
}

BOOL CPkg_AppGetConfigResp_AppCfg::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_AppGetConfigResp_AppCfg *p = (CPkg_AppGetConfigResp_AppCfg*)pObj;

	if(m_strApp != p->m_strApp)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_AppGetConfigResp_AppCfg::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_AppGetConfigResp_AppCfg *p = (CPkg_AppGetConfigResp_AppCfg*)pDest;

	p->m_strApp = m_strApp;
	return TRUE;
}

CBaseObject* CPkg_AppGetConfigResp_AppCfg::Clone()
{
	CPkg_AppGetConfigResp_AppCfg *p = new CPkg_AppGetConfigResp_AppCfg();
	Copy(p);
	return p;
}

CBaseObject* CPkg_AppGetConfigResp_AppCfg::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPkg_AppGetConfigResp_AppCfg *p = new CPkg_AppGetConfigResp_AppCfg();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CPkg_AppGetConfigResp_AppCfg::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGCPU)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGMEM)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CPkg_AppGetConfigResp_AppCfg::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTcpEdgePkgCfgCpuKey)
	{
		pNew = new CTcpEdgePkgCfgCpu();
		pNew->m_strID = _T("AppGetConfigResp");
		m_bObjectMustExist[0] = TRUE;
		pNew->m_strName = PkgData_Node_AppCfgs;
	}
	else if (strClassID == pXmlKeys->m_strCTcpEdgePkgCfgMemKey)
	{
		pNew = new CTcpEdgePkgCfgMem();
		pNew->m_strID = _T("AppGetConfigResp");
		m_bObjectMustExist[1] = TRUE;
		pNew->m_strName = PkgData_Node_AppCfgs;
	}

	return pNew;
}

CExBaseObject* CPkg_AppGetConfigResp_AppCfg::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGCPU)
	{
		pNew = new CTcpEdgePkgCfgCpu();
	}
	else if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGMEM)
	{
		pNew = new CTcpEdgePkgCfgMem();
	}

	return pNew;
}
long CPkg_AppGetConfigResp_AppCfg::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strAppKey, m_strApp);
	return 0;
}

long CPkg_AppGetConfigResp_AppCfg::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strAppKey, m_strApp);
	return 0;
}


//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecGenRuleMngr.cpp  CIecGenRuleMngr


#include "stdafx.h"
#include "IecGenRuleMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecGenRuleMngr g_oIecfgGenMngr;

CIecGenRuleMngr::CIecGenRuleMngr()
{
	//初始化属性

	//初始化成员变量
}

CIecGenRuleMngr::~CIecGenRuleMngr()
{
}

long CIecGenRuleMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNet_DescKey, oNode, m_strNetDesc);
	return 0;
}

long CIecGenRuleMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNet_DescKey, oElement, m_strNetDesc);
	return 0;
}

long CIecGenRuleMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strNetDesc);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strNetDesc);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strNetDesc);
	}
	return 0;
}

void CIecGenRuleMngr::InitAfterRead()
{
}

BOOL CIecGenRuleMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecGenRuleMngr *p = (CIecGenRuleMngr*)pObj;

	if(m_strNetDesc != p->m_strNetDesc)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecGenRuleMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIecGenRuleMngr *p = (CIecGenRuleMngr*)pDest;

	p->m_strNetDesc = m_strNetDesc;
	return TRUE;
}

CBaseObject* CIecGenRuleMngr::Clone()
{
	CIecGenRuleMngr *p = new CIecGenRuleMngr();
	Copy(p);
	return p;
}

CBaseObject* CIecGenRuleMngr::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecGenRuleMngr *p = new CIecGenRuleMngr();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIecGenRuleMngr::CanPaste(UINT nClassID)
{
	if (nClassID == GENRATECLASSID_CIECDEVICERULE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIecGenRuleMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecDeviceRuleKey)
	{
		pNew = new CIecDeviceRule();
	}

	return pNew;
}

CExBaseObject* CIecGenRuleMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GENRATECLASSID_CIECDEVICERULE)
	{
		pNew = new CIecDeviceRule();
	}

	return pNew;
}


BOOL CIecGenRuleMngr::OpenIecfgGenMnrFile(const CString &strIecfgGenMnrFile)
{
	if (strIecfgGenMnrFile.IsEmpty())
	{
		m_strID = _P_GetConfigPath();
		m_strID += IECFG_GEN_MNGR_FILE_NAME_DEFAULT;

	}
	else
	{
		m_strID = strIecfgGenMnrFile;
	}

	return OpenXmlFile(m_strID,CIecfgGenMngrXmlRWKeys::g_pXmlKeys);
}






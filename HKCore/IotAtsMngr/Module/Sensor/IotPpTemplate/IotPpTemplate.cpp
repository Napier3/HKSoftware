//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpTemplate.cpp  CIotPpTemplate


#include "stdafx.h"
#include "IotPpTemplate.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIotPpTemplate::CIotPpTemplate()
{
	//初始化属性

	//初始化成员变量
	m_pIotPpParses = NULL;
	m_pIotPpProduces = NULL;
	m_pIotPpProcedures = NULL;
}

CIotPpTemplate::~CIotPpTemplate()
{
}

long CIotPpTemplate::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDvm_FileKey, oNode, m_strDvm_File);
	return 0;
}

long CIotPpTemplate::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDvm_FileKey, oElement, m_strDvm_File);
	return 0;
}

long CIotPpTemplate::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDvm_File);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDvm_File);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDvm_File);
	}
	return 0;
}

void CIotPpTemplate::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == IOTCLASSID_CIOTPPPARSES)
		{
			m_pIotPpParses = (CIotPpParses*)p;
		}
		else if (nClassID == IOTCLASSID_CIOTPPPRODUCES)
		{
			m_pIotPpProduces = (CIotPpProduces*)p;
		}
		else if (nClassID == IOTCLASSID_CIOTPPPROCEDURES)
		{
			m_pIotPpProcedures = (CIotPpProcedures*)p;
		}
	}

	if (m_pIotPpParses == NULL)
	{
		m_pIotPpParses = (CIotPpParses*)AddNewChild(new CIotPpParses());
	}

	if (m_pIotPpProduces == NULL)
	{
		m_pIotPpProduces = (CIotPpProduces*)AddNewChild(new CIotPpProduces());
	}

	if (m_pIotPpProcedures == NULL)
	{
		m_pIotPpProcedures = (CIotPpProcedures*)AddNewChild(new CIotPpProcedures());
	}

}

BOOL CIotPpTemplate::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIotPpTemplate *p = (CIotPpTemplate*)pObj;

	if(m_strDvm_File != p->m_strDvm_File)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIotPpTemplate::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIotPpTemplate *p = (CIotPpTemplate*)pDest;

	p->m_strDvm_File = m_strDvm_File;
	return TRUE;
}

CBaseObject* CIotPpTemplate::Clone()
{
	CIotPpTemplate *p = new CIotPpTemplate();
	Copy(p);
	return p;
}

CBaseObject* CIotPpTemplate::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIotPpTemplate *p = new CIotPpTemplate();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIotPpTemplate::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOTPPPARSES)
	{
		return TRUE;
	}

	if (nClassID == IOTCLASSID_CIOTPPPRODUCES)
	{
		return TRUE;
	}

	if (nClassID == IOTCLASSID_CIOTPPPROCEDURES)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIotPpTemplate::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIotPpParsesKey)
	{
		pNew = new CIotPpParses();
	}
	else if (strClassID == pXmlKeys->m_strCIotPpProducesKey)
	{
		pNew = new CIotPpProduces();
	}
	else if (strClassID == pXmlKeys->m_strCIotPpProceduresKey)
	{
		pNew = new CIotPpProcedures();
	}

	return pNew;
}

CExBaseObject* CIotPpTemplate::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOTPPPARSES)
	{
		pNew = new CIotPpParses();
	}
	else if (nClassID == IOTCLASSID_CIOTPPPRODUCES)
	{
		pNew = new CIotPpProduces();
	}
	else if (nClassID == IOTCLASSID_CIOTPPPROCEDURES)
	{
		pNew = new CIotPpProcedures();
	}

	return pNew;
}

CIotPpParse *CIotPpTemplate::FindPpParse(const CString &strID)
{
	if (m_pIotPpParses == NULL)
	{
		return NULL;
	}

	return (CIotPpParse *)m_pIotPpParses->FindByID(strID);
}

CIotPpParse *CIotPpTemplate::FindPpParse(int nPkgType,int nCtrlType,int nRequestSetFlag)
{
	if(m_pIotPpParses == NULL)
	{
		return NULL;
	}

	POS pos = m_pIotPpParses->GetHeadPosition();
	CIotPpParse *p = NULL;
	CIotPpPkgHead *pPkgHead = NULL;

	while(pos != NULL)
	{
		p = (CIotPpParse *)m_pIotPpParses->GetNext(pos);

		pPkgHead = p->GetIotPpPkgHead();

		if (pPkgHead->IsMatchPkg(nPkgType,nCtrlType,nRequestSetFlag))
		{
			return p;
		}
	}

	return NULL;
}

CIotPpProduce *CIotPpTemplate::FindPpProduce(const CString &strID)
{
	if (m_pIotPpProduces == NULL)
	{
		return NULL;
	}

	return (CIotPpProduce *)m_pIotPpProduces->FindByID(strID);
}

CIotPpProcedure *CIotPpTemplate::FindPpProcedure(const CString &strID)
{
	if (m_pIotPpProcedures == NULL)
	{
		return NULL;
	}

	return (CIotPpProcedure *)m_pIotPpProcedures->FindByID(strID);
}
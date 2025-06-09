//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpProduce.cpp  CIotPpProduce


#include "stdafx.h"
#include "IotPpProduce.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIotPpProduce::CIotPpProduce()
{
	//初始化属性

	//初始化成员变量
	m_pIotPpInterface = NULL;
}

CIotPpProduce::~CIotPpProduce()
{
}

long CIotPpProduce::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIotPpParse::XmlReadOwn(oNode, pXmlRWKeys);
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpProduce::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIotPpParse::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpProduce::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CIotPpParse::SerializeOwn(oBinaryBuffer);
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

void CIotPpProduce::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == IOTCLASSID_CIOTPPPKGHEAD)
		{
			m_pIotPpPkgHead = (CIotPpPkgHead*)p;
		}
		else if (nClassID == IOTCLASSID_CIOTPPDATALIST)
		{
			m_pIotPpDataList = (CIotPpDataList*)p;
		}
		else if (nClassID == IOTCLASSID_CIOTPPINTERFACE)
		{
			m_pIotPpInterface = (CIotPpInterface*)p;
		}
	}

	if (m_pIotPpPkgHead == NULL)
	{
		m_pIotPpPkgHead = (CIotPpPkgHead*)AddNewChild(new CIotPpPkgHead());
	}

	if (m_pIotPpDataList == NULL)
	{
		m_pIotPpDataList = (CIotPpDataList*)AddNewChild(new CIotPpDataList());
	}

	if (m_pIotPpInterface == NULL)
	{
		m_pIotPpInterface = (CIotPpInterface*)AddNewChild(new CIotPpInterface());
	}

}

BOOL CIotPpProduce::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIotPpParse::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIotPpProduce *p = (CIotPpProduce*)pObj;

	return TRUE;
}

BOOL CIotPpProduce::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIotPpParse::CopyOwn(pDest);

	CIotPpProduce *p = (CIotPpProduce*)pDest;

	return TRUE;
}

CBaseObject* CIotPpProduce::Clone()
{
	CIotPpProduce *p = new CIotPpProduce();
	Copy(p);
	return p;
}

CBaseObject* CIotPpProduce::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIotPpProduce *p = new CIotPpProduce();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIotPpProduce::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOTPPINTERFACE)
	{
		return TRUE;
	}

	if (nClassID == IOTCLASSID_CIOTPPPKGHEAD)
	{
		return TRUE;
	}

	if (nClassID == IOTCLASSID_CIOTPPDATALIST)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIotPpProduce::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIotPpInterfaceKey)
	{
		pNew = new CIotPpInterface();
	}
	else if (strClassID == pXmlKeys->m_strCIotPpPkgHeadKey)
	{
		pNew = new CIotPpPkgHead();
	}
	else if (strClassID == pXmlKeys->m_strCIotPpDataListKey)
	{
		pNew = new CIotPpDataList();
	}

	return pNew;
}

CExBaseObject* CIotPpProduce::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOTPPINTERFACE)
	{
		pNew = new CIotPpInterface();
	}
	else if (nClassID == IOTCLASSID_CIOTPPPKGHEAD)
	{
		pNew = new CIotPpPkgHead();
	}
	else if (nClassID == IOTCLASSID_CIOTPPDATALIST)
	{
		pNew = new CIotPpDataList();
	}

	return pNew;
}

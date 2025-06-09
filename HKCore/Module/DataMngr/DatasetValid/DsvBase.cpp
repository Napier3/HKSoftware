//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DsvBase.cpp  CDsvBase


#include "stdafx.h"
#include "DsvBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDsvBase::CDsvBase()
{
	//初始化属性
	m_nMinOcc = 1;
	m_nMaxOcc = 1;

	//初始化成员变量
	m_bDsvSucc = FALSE;
}

CDsvBase::~CDsvBase()
{
	m_listDsvMatch.RemoveAll();
}

long CDsvBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMinOccKey, oNode, m_nMinOcc);
	xml_GetAttibuteValue(pXmlKeys->m_strMaxOccKey, oNode, m_nMaxOcc);

	return 0;
}

long CDsvBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMinOccKey, oElement, m_nMinOcc);
	xml_SetAttributeValue(pXmlKeys->m_strMaxOccKey, oElement, m_nMaxOcc);

	return 0;
}

long CDsvBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nMinOcc);
		BinarySerializeCalLen(oBinaryBuffer, m_nMaxOcc);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nMinOcc);
		BinarySerializeRead(oBinaryBuffer, m_nMaxOcc);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nMinOcc);
		BinarySerializeWrite(oBinaryBuffer, m_nMaxOcc);
	}
	return 0;
}

void CDsvBase::InitAfterRead()
{
}

BOOL CDsvBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDsvBase *p = (CDsvBase*)pObj;

	if(m_nMinOcc != p->m_nMinOcc)
	{
		return FALSE;
	}

	if(m_nMaxOcc != p->m_nMaxOcc)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDsvBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDsvBase *p = (CDsvBase*)pDest;

	p->m_nMinOcc = m_nMinOcc;
	p->m_nMaxOcc = m_nMaxOcc;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
CDsvBase* CDsvBase::GetFirstDsvElement()
{
	CDsvBase *pFirst = NULL;
	CDsvBase *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDsvBase *)GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDSVELEMENT)
		{
			pFirst = p;
			break;
		}
		else if (p->GetClassID() == DVMCLASSID_CDSVANYELEMENT)
		{
			continue;
		}
		else
		{
			pFirst = p->GetFirstDsvElement();

			if (pFirst != NULL)
			{
				break;
			}
		}
	}

	return pFirst;
}

BOOL CDsvBase::IsValidateSucc()
{
	CDsvBase *p = NULL;
	POS pos = GetHeadPosition();
	BOOL bSucc = TRUE;

	while (pos != NULL)
	{
		p = (CDsvBase *)GetNext(pos);

		if (p->IsElement())//p->GetClassID() == DVMCLASSID_CDSVELEMENT)
		{
			if (!p->IsAnyDsvObject())
			{
				if (!p->m_bDsvSucc)
				{
					bSucc = FALSE;
					break;
				}
			}
		}
		else
		{
			bSucc = p->IsValidateSucc();

			if (!bSucc)
			{
				break;
			}
		}
	}

	return bSucc;
}

//获得所有匹配成功的数据对象
long CDsvBase::GetAllMatchObjects(CExBaseList &listMatchObject, CExBaseList &listAnyDsvMatchObject)
{
	CDsvBase *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDsvBase *)GetNext(pos);

		if (p->IsElement())
		{
			if (p->IsAnyDsvObject())
			{
				listAnyDsvMatchObject.Append(p->m_listDsvMatch);
			}
			else
			{
				//如果是真正的element，则添加此element匹配成功的data对象
				listMatchObject.Append(p->m_listDsvMatch);
			}
		}
		else
		{
			p->GetAllMatchObjects(listMatchObject, listAnyDsvMatchObject);
		}
	}

	return listMatchObject.GetCount();
}

CString CDsvBase::GetText()
{
	CString strText;

    strText.Format(_T("%s【%d】~【%d】"), m_strName.GetString(), m_nMinOcc, m_nMaxOcc);

	return strText;
}

BOOL CDsvBase::IsElement()
{
	return dsv_IsElement(this);
}


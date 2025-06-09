#include "StdAfx.h"
#include "PpDataBinds.h"
#include "PpDataBind.h"
#include "../XLanguageResourcePp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpDataBinds::CPpDataBinds(void)
{
	 m_strDataBindTypeID="";
	 m_bHasInitBindsDataType = FALSE;
	 m_pBindData = NULL;

// 	 m_pOldBind = NULL;
// 	 m_pNewBind = new CPpDataBind();
}

CPpDataBinds::~CPpDataBinds(void)
{
	//获取绑定的末尾对象，如果与新的对象相同，表示更改变绑定
	//没有恢复绑定，所以删除
	//m_pOldBind，否则删除m_pNewBind
// 	POS pos = GetTailPosition();
// 
// 	if (pos != NULL)
// 	{
// 		CPpDataBind *p = (CPpDataBind*)GetAt(pos);
// 		
// 		if (p == m_pNewBind)
// 		{
// 			if (m_pOldBind != NULL)
// 			{
// 				delete m_pOldBind;
// 				m_pOldBind = NULL;
// 			}
// 		}
// 		else
// 		{
// 			delete m_pNewBind;
// 			m_pNewBind = NULL;
// 		}
// 	}
// 	else
// 	{
// 		delete m_pNewBind;
// 		m_pNewBind = NULL;
// 	}
}

long CPpDataBinds::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CPpDataBinds::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	return 0;
}

long CPpDataBinds::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{

	return 0;
}


CExBaseObject* CPpDataBinds::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataBindKey)
	{
		return new CPpDataBind();
	}

	return NULL;
}

CExBaseObject* CPpDataBinds::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpDataBinds::IsEqualOwn(CBaseObject* pObj)
{
	ASSERT (pObj == NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	if (this == pObj)
	{
		return TRUE;
	}

	if (m_strDataBindTypeID != ((CPpDataBinds*)pObj)->m_strDataBindTypeID)
	{
		return FALSE;
	}

	return CExBaseObject::IsEqualOwn(pObj);
}

CBaseObject* CPpDataBinds::Clone()
{
	CPpDataBinds* pNew = new CPpDataBinds();
	Copy(pNew);
	return pNew;
}

BOOL CPpDataBinds::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CPpDataBinds*)pDest)->m_strDataBindTypeID = m_strDataBindTypeID;

	return CExBaseObject::CopyOwn(pDest);
}

CPpDataBind* CPpDataBinds::GetInforIndexBind()
{
	CPpDataBind *pFind = (CPpDataBind*)GetHead();

	if (pFind == NULL)
	{
		CExBaseObject *p = (CExBaseObject*)GetAncestor(PPCLASSID_PPPARSEPACKGE);

		if (p == NULL)
		{
			p = (CExBaseObject*)GetAncestor(PPCLASSID_PPPRODUCEPACKGE);
		}

		if (g_bLogBindQueryErrorInfor)
		{
				if (p != NULL)
				{
                    CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_DataRltnshipError3.GetString()/*_T("%s : 数据绑定定义错误")*/
                                               , p->m_strName.GetString());
				}
				else
				{
					CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_DataRltnshipError2/*L"数据绑定定义错误"*/);
				}
		}

		return NULL;
	}
	
/*
	if (pFind->m_strDataType == g_strVariableDataTypeInfoIndexID)
	{
		return pFind;
	}
	else
*/
	{
		return NULL;
	}
}

long CPpDataBinds::GetDataBindCount()
{
	long nCount = GetCount();

	if (GetInforIndexBind() != NULL)
	{
		nCount--;
	}

	return nCount;
}


POS CPpDataBinds::GetFirstDataBindPos()
{
	CPpDataBind *pBind = NULL;
	POS pos = GetHeadPosition();

	if (GetInforIndexBind() != NULL)
	{
		GetNext(pos);
	}

	return pos;
}

CPpDataBind* CPpDataBinds::GetNextDataBind(POS &pos)
{
	CPpDataBind *pBind = (CPpDataBind*)GetNext(pos);
	return pBind;
}

CPpDataBind* CPpDataBinds::GetAtDataBind(POS &pos)
{
	CPpDataBind *pBind = NULL;

	if (pos != NULL)
	{
		pBind = (CPpDataBind*)GetAt(pos);
	}

	return pBind;
}

void CPpDataBinds::LogString(const CString &strTitle)
{
	CString strLog = strTitle;
	POS pos = GetHeadPosition();
	CPpDataBind *pBind = NULL;

	while (pos != NULL)
	{
		pBind = (CPpDataBind*)GetNext(pos);
        strLog.AppendFormat(_T("%s(%s) "), pBind->m_strDataType.GetString(), pBind->m_strDataAttrID.GetString());
	}

	CLogPrint::LogString(XLOGLEVEL_ERROR, strLog);
}

void CPpDataBinds::InitBindsDataType()
{
	if (m_bHasInitBindsDataType)
	{
		return;
	}

	m_bHasInitBindsDataType = TRUE;
	POS pos = GetHeadPosition();
	CPpDataBind *pBind = NULL;

	while (pos != NULL)
	{
		pBind = (CPpDataBind*)GetNext(pos);
		pBind->InitDataType();
	}
}

void CPpDataBinds::ValidateBinds()
{
	POS pos = GetFirstDataBindPos();
	CPpDataBind *pBind = NULL;
	POS posPrev = pos;

	while (pos != NULL)
	{
		posPrev = pos;
		pBind = GetNextDataBind(pos);

		if (pBind == NULL)
		{
			break;
		}

		if (!pBind->IsBindValid())
		{
			DeleteAt(posPrev);
			continue;
		}
	}
}


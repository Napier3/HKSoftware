//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapSerialConfig.cpp  CEpCapSerialConfig


#include "stdafx.h"
#include "EpCapSerialConfig.h"

CEpCapSerialConfig::CEpCapSerialConfig()
{
	//初始化属性

	//初始化成员变量
	m_pDirs = NULL;
}

CEpCapSerialConfig::~CEpCapSerialConfig()
{
}

long CEpCapSerialConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpCapSerialConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpCapSerialConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
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

void CEpCapSerialConfig::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == ECCLASSID_CEPCAPDIRS)
		{
			m_pDirs = (CEpCapDirs*)p;
		}
	}

	if (m_pDirs == NULL)
	{
		m_pDirs = (CEpCapDirs*)AddNewChild(new CEpCapDirs());
	}

}

BOOL CEpCapSerialConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpCapSerialConfig *p = (CEpCapSerialConfig*)pObj;

	return TRUE;
}

BOOL CEpCapSerialConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapSerialConfig *p = (CEpCapSerialConfig*)pDest;

	return TRUE;
}

CBaseObject* CEpCapSerialConfig::Clone()
{
	CEpCapSerialConfig *p = new CEpCapSerialConfig();
	Copy(p);
	return p;
}

long CEpCapSerialConfig::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CEpCapSerialConfig::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CEpCapSerialConfig::CanPaste(UINT nClassID)
{
	if (nClassID == ECCLASSID_CEPCAPSERIALGROUP)
	{
		return TRUE;
	}

	if (nClassID == ECCLASSID_CEPCAPDIRS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpCapSerialConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpCapSerialGroupKey)
	{
		pNew = new CEpCapSerialGroup();
	}
	else if (strClassID == pXmlKeys->m_strCEpCapDirsKey)
	{
		pNew = new CEpCapDirs();
	}

	return pNew;
}

CExBaseObject* CEpCapSerialConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ECCLASSID_CEPCAPSERIALGROUP)
	{
		pNew = new CEpCapSerialGroup();
	}
	else if (nClassID == ECCLASSID_CEPCAPDIRS)
	{
		pNew = new CEpCapDirs();
	}

	return pNew;
}

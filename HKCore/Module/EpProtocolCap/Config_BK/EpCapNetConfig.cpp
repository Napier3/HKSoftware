//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapNetConfig.cpp  CEpCapNetConfig


#include "stdafx.h"
#include "EpCapNetConfig.h"

CEpCapNetConfig::CEpCapNetConfig()
{
	//初始化属性

	//初始化成员变量
	m_pNetRemote = NULL;
	m_pNetLocal = NULL;
	m_pDirs = NULL;
}

CEpCapNetConfig::~CEpCapNetConfig()
{
}

long CEpCapNetConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpCapNetConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpCapNetConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEpCapNetConfig::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == ECCLASSID_CEPCAPNETREMOTE)
		{
			m_pNetRemote = (CEpCapNetRemote*)p;
		}
		else if (nClassID == ECCLASSID_CEPCAPNETLOCAL)
		{
			m_pNetLocal = (CEpCapNetLocal*)p;
		}
		else if (nClassID == ECCLASSID_CEPCAPDIRS)
		{
			m_pDirs = (CEpCapDirs*)p;
		}
	}

	if (m_pNetRemote == NULL)
	{
		m_pNetRemote = (CEpCapNetRemote*)AddNewChild(new CEpCapNetRemote());
	}

	if (m_pNetLocal == NULL)
	{
		m_pNetLocal = (CEpCapNetLocal*)AddNewChild(new CEpCapNetLocal());
	}

	if (m_pDirs == NULL)
	{
		m_pDirs = (CEpCapDirs*)AddNewChild(new CEpCapDirs());
	}

}

BOOL CEpCapNetConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpCapNetConfig *p = (CEpCapNetConfig*)pObj;

	return TRUE;
}

BOOL CEpCapNetConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapNetConfig *p = (CEpCapNetConfig*)pDest;

	return TRUE;
}

CBaseObject* CEpCapNetConfig::Clone()
{
	CEpCapNetConfig *p = new CEpCapNetConfig();
	Copy(p);
	return p;
}

long CEpCapNetConfig::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CEpCapNetConfig::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CEpCapNetConfig::CanPaste(UINT nClassID)
{
	if (nClassID == ECCLASSID_CEPCAPNETREMOTE)
	{
		return TRUE;
	}

	if (nClassID == ECCLASSID_CEPCAPNETLOCAL)
	{
		return TRUE;
	}

	if (nClassID == ECCLASSID_CEPCAPDIRS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpCapNetConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpCapNetRemoteKey)
	{
		pNew = new CEpCapNetRemote();
	}
	else if (strClassID == pXmlKeys->m_strCEpCapNetLocalKey)
	{
		pNew = new CEpCapNetLocal();
	}
	else if (strClassID == pXmlKeys->m_strCEpCapDirsKey)
	{
		pNew = new CEpCapDirs();
	}

	return pNew;
}

CExBaseObject* CEpCapNetConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ECCLASSID_CEPCAPNETREMOTE)
	{
		pNew = new CEpCapNetRemote();
	}
	else if (nClassID == ECCLASSID_CEPCAPNETLOCAL)
	{
		pNew = new CEpCapNetLocal();
	}
	else if (nClassID == ECCLASSID_CEPCAPDIRS)
	{
		pNew = new CEpCapDirs();
	}

	return pNew;
}

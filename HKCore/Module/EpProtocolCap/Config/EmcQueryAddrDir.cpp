//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EmcQueryAddrDir.cpp  CEmcQueryAddrDir


#include "stdafx.h"
#include "EmcQueryAddrDir.h"
#include "MonitorQueryConfig.h"

CEmcQueryAddrDir::CEmcQueryAddrDir()
{
	//初始化属性

	//初始化成员变量
	m_strName = _T("查询方向对象");
}

CEmcQueryAddrDir::~CEmcQueryAddrDir()
{
}

long CEmcQueryAddrDir::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEmcQueryAddrDir::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEmcQueryAddrDir::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CEmcQueryAddrDir::InitAfterRead()
{
}

BOOL CEmcQueryAddrDir::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEmcQueryAddrDir *p = (CEmcQueryAddrDir*)pObj;

	return TRUE;
}

BOOL CEmcQueryAddrDir::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CEmcQueryAddrDir *p = (CEmcQueryAddrDir*)pDest;

	return TRUE;
}

CBaseObject* CEmcQueryAddrDir::Clone()
{
	CEmcQueryAddrDir *p = new CEmcQueryAddrDir();
	Copy(p);
	return p;
}

CExBaseObject* CEmcQueryAddrDir::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEmcQueryAddrMapKey)
	{
		pNew = new CEmcQueryAddrMap();
	}

	return pNew;
}

CExBaseObject* CEmcQueryAddrDir::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EMCCLASSID_CEMCQUERYADDRMAP)
	{
		pNew = new CEmcQueryAddrMap();
	}

	return pNew;
}
long CEmcQueryAddrDir::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

long CEmcQueryAddrDir::InitListCtrlColumnsFunc(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 40);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 200);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

BOOL CEmcQueryAddrDir::ValidateDir()
{
	CStringArray astrMapFile;

	GetAllDvmFile(astrMapFile);

	if (astrMapFile.GetSize() != 1)
	{
		return FALSE;
	}
	else
	{
		return FALSE;
	}
}

void CEmcQueryAddrDir::GetAllDvmFile(CStringArray &astrMapFile)
{
	CMonitorQueryConfig *pConfig = (CMonitorQueryConfig*)GetAncestor(ECCLASSID_CMONITORQUERYCONFIG);
	CEmcNetsConfig *pNets = pConfig->m_pEmcNetsConfig;

	POS pos = GetHeadPosition();
	CEmcQueryAddrMap *pMap = NULL;
	CEmcNetConfig *pNet = NULL;

	while (pos != NULL)
	{
		pMap = (CEmcQueryAddrMap *)GetNext(pos);
		
		if (pMap->m_strSrc.GetLength() > 5)
		{
			pNet = (CEmcNetConfig*)pNets->FindByID(pMap->m_strSrc);

			if (pNet != NULL)
			{
				AddDvmFile(astrMapFile, pNet->m_strDvmFile);
			}
		}

		if (pMap->m_strDest.GetLength() > 5)
		{
			pNet = (CEmcNetConfig*)pNets->FindByID(pMap->m_strDest);

			if (pNet != NULL)
			{
				AddDvmFile(astrMapFile, pNet->m_strDvmFile);
			}
		}
	}
}

void CEmcQueryAddrDir::AddDvmFile(CStringArray &astrFile, const CString &strFile)
{
	long nCount = astrFile.GetCount();
	long nIndex = 0;
	CString strText;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strText = astrFile.GetAt(nIndex);

		if (strText == strFile)
		{
			return;
		}
	}

	astrFile.Add(strFile);
}

CString CEmcQueryAddrDir::GetDeviceModelFile()
{
	CStringArray astrMapFile;

	GetAllDvmFile(astrMapFile);

	if (astrMapFile.GetSize() == 0)
	{
		return _T("");
	}
	else
	{
		return astrMapFile.GetAt(0);
	}
}


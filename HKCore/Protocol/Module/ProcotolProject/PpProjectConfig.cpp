//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpProjectConfig.cpp  CPpProjectConfig


#include "stdafx.h"
#include "PpProjectConfig.h"
#include "../../../Module/API/FileApi.h"

CPpProjectConfig::CPpProjectConfig()
{
	//初始化属性
	m_pPpCfgDevices = NULL;
	m_pPpCfgOptrsMngr = NULL;

	//初始化成员变量
	m_bCreated = FALSE;
}

CPpProjectConfig::~CPpProjectConfig()
{
}

long CPpProjectConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpProjectConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpProjectConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPpProjectConfig::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == POCLASSID_CPPCFGDEVICES)
		{
			m_pPpCfgDevices = (CPpCfgDevices*)p;
		}
		else if (nClassID == POCLASSID_CPPCFGOPTRSMNGR)
		{
			m_pPpCfgOptrsMngr = (CPpCfgOptrsMngr*)p;
		}
	}

	if (m_pPpCfgDevices == NULL)
	{
		m_pPpCfgDevices = (CPpCfgDevices*)AddNewChild(new CPpCfgDevices());
	}

	if (m_pPpCfgOptrsMngr == NULL)
	{
		m_pPpCfgOptrsMngr = (CPpCfgOptrsMngr*)AddNewChild(new CPpCfgOptrsMngr());
	}


}

BOOL CPpProjectConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CPpProjectConfig *p = (CPpProjectConfig*)pObj;

	return TRUE;
}

BOOL CPpProjectConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPpProjectConfig *p = (CPpProjectConfig*)pDest;

	return TRUE;
}

CBaseObject* CPpProjectConfig::Clone()
{
	CPpProjectConfig *p = new CPpProjectConfig();
	Copy(p);
	return p;
}

long CPpProjectConfig::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPpProjectConfig::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
    pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

BOOL CPpProjectConfig::CanPaste(UINT nClassID)
{
	if (nClassID == POCLASSID_CPPCFGDEVICES)
	{
		return TRUE;
	}

	if (nClassID == POCLASSID_CPPCFGOPTRSMNGR)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CPpProjectConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCPpCfgDevicesKey)
	{
		pNew = new CPpCfgDevices();
	}
	else if (strClassID == pXmlKeys->m_strCPpCfgOptrsMngrKey)
	{
		pNew = new CPpCfgOptrsMngr();
	}

	return pNew;
}

CExBaseObject* CPpProjectConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == POCLASSID_CPPCFGDEVICES)
	{
		pNew = new CPpCfgDevices();
	}
	else if (nClassID == POCLASSID_CPPCFGOPTRSMNGR)
	{
		pNew = new CPpCfgOptrsMngr();
	}

	return pNew;
}

CPpCfgDevices* CPpProjectConfig::GetPpCfgDevices()
{
	if (m_pPpCfgDevices == NULL)
	{
		m_pPpCfgDevices = new CPpCfgDevices();
		AddNewChild(m_pPpCfgDevices);
	}

	return m_pPpCfgDevices;
}

CPpCfgOptrsMngr* CPpProjectConfig::GetPpCfgOptrsMngr()
{
	if (m_pPpCfgOptrsMngr == NULL)
	{
		m_pPpCfgOptrsMngr = new CPpCfgOptrsMngr();
		AddNewChild(m_pPpCfgOptrsMngr);
	}

	return m_pPpCfgOptrsMngr;
}

void CPpProjectConfig::NewPpProjectConfig()
{
	m_strPpCfgFilePath.Empty();
	ProjectUnload();
}

BOOL CPpProjectConfig::OpenProjectDB(const CString &strFile)
{
	m_strID = GetPathFileNameFromFilePathName(strFile);
	m_strName = m_strID;
	DeleteAll();

	m_strPpCfgFilePath = strFile;
	
	BOOL b= OpenXmlFile(strFile, CClassProcotolProjectXmlRWKeys::g_pXmlKeys->m_strCPpProjectConfigKey, CClassProcotolProjectXmlRWKeys::g_pXmlKeys);

    if (!b)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPpProjectConfig::SaveProjectDB(const CString &strFile)
{
	if (strFile.GetLength() > 5)
	{
		m_strPpCfgFilePath = strFile;
	}

	ASSERT(m_strPpCfgFilePath.GetLength() > 5);

	return SaveXmlFile(m_strPpCfgFilePath, CClassProcotolProjectXmlRWKeys::g_pXmlKeys);
}

BOOL CPpProjectConfig::Save()
{
	try
	{
		BOOL b = SaveXmlFile(m_strPpCfgFilePath,CClassProcotolProjectXmlRWKeys::g_pXmlKeys);

		return b;
	}
	catch (...)
	{
		return FALSE;
	}

}

void CPpProjectConfig::ProjectUnload()
{
	if (m_pPpCfgOptrsMngr != NULL)
	{
		m_pPpCfgOptrsMngr->DeleteAll();
	}

	if (m_pPpCfgDevices != NULL)
	{
		m_pPpCfgDevices->DeleteAll();
	}
}


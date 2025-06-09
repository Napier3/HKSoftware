//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpCfgDevices.cpp  CPpCfgDevices


#include "stdafx.h"
#include "PpCfgDevices.h"

CPpCfgDevices::CPpCfgDevices()
{
	//初始化属性

	//初始化成员变量
}

CPpCfgDevices::~CPpCfgDevices()
{
	m_listCmmCfgChannel.RemoveAll();
}

long CPpCfgDevices::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpCfgDevices::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpCfgDevices::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPpCfgDevices::InitAfterRead()
{
}

BOOL CPpCfgDevices::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CPpCfgDevices *p = (CPpCfgDevices*)pObj;

	return TRUE;
}

BOOL CPpCfgDevices::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPpCfgDevices *p = (CPpCfgDevices*)pDest;

	return TRUE;
}

CBaseObject* CPpCfgDevices::Clone()
{
	CPpCfgDevices *p = new CPpCfgDevices();
	Copy(p);
	return p;
}

long CPpCfgDevices::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(0, _T("名称"));
	pListCtrl->SetColumnWidth(0, 250);
	
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPpCfgDevices::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

BOOL CPpCfgDevices::CanPaste(UINT nClassID)
{
	if (nClassID == POCLASSID_CPPCFGDEVICE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CPpCfgDevices::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCPpCfgDeviceKey)
	{
		pNew = new CPpCfgDevice();
	}

	return pNew;
}

CExBaseObject* CPpCfgDevices::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == POCLASSID_CPPCFGDEVICE)
	{
		pNew = new CPpCfgDevice();
	}

	return pNew;
}

CPpCfgDevice* CPpCfgDevices::FindpPpCfgDevice(CExBaseObject *pDataRef)
{
	CPpCfgDevice *p = NULL;
	CPpCfgDevice *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CPpCfgDevice *)GetNext(pos);

		if (p->m_pEngineDataRef == pDataRef)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CPpCfgDevices::InitAllCmdCfgChannels()
{
	m_listCmmCfgChannel.RemoveAll();
	POS pos = GetHeadPosition();
	CPpCfgDevice *p = NULL;

	while (pos != NULL)
	{
		p = (CPpCfgDevice *)GetNext(pos);
		p->SelectCmmCfgChannel(m_listCmmCfgChannel);
	}
}

void CPpCfgDevices::SaveCfgDevicesFile(const CString &strFile)
{
	if (strFile.GetLength() == 0)
	{
		SaveXmlFile(m_strCfgDevicesFile, CClassProcotolProjectXmlRWKeys::g_pXmlKeys);
	}
	else
	{
		SaveXmlFile(strFile, CClassProcotolProjectXmlRWKeys::g_pXmlKeys);
		m_strCfgDevicesFile = strFile;
	}
}

void CPpCfgDevices::OpenCfgDevicesFile(const CString &strFile)
{
	if (strFile.GetLength() == 0)
	{
		OpenXmlFile(m_strCfgDevicesFile, CClassProcotolProjectXmlRWKeys::g_pXmlKeys);
	}
	else
	{
		OpenXmlFile(strFile, CClassProcotolProjectXmlRWKeys::g_pXmlKeys);
		m_strCfgDevicesFile = strFile;
	}
}
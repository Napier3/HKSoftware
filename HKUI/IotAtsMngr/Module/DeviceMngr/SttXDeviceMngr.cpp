//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttXDeviceMngr.cpp  CSttXDeviceMngr


#include "stdafx.h"
#include "SttXDeviceMngr.h"
#include "../../../Relaytest/Module/SttGlobalDef.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttXDeviceMngr::CSttXDeviceMngr()
{
	//初始化属性
	m_strID = XPARA_ID_devices;
	m_strDataType = XPARA_ID_devices;
	m_pMsgRcvWnd = NULL;

	//初始化成员变量
}

CSttXDeviceMngr::~CSttXDeviceMngr()
{
	
}


long CSttXDeviceMngr::QueryDevices(CExBaseList &oList, CDataGroup *pQuery)
{
	POS pos = GetHeadPosition();
	CSttXDevice *pDevice = NULL;

	while (pos != NULL)
	{
		pDevice = (CSttXDevice *)GetNext(pos);

		if (pDevice->Match(pQuery))
		{
			oList.AddTail(pDevice) ;
		}
	}

	return oList.GetCount();
}

long CSttXDeviceMngr::AddDevice(CDataGroup *pParas, BOOL bPostMsg)
{
	CSttXDevice *pNew = new CSttXDevice();
	pNew->AppendCloneEx(*pParas);
	pNew->InitDevice();
	CSttXDevice *pFind = (CSttXDevice*)FindByID(pNew->m_strSN);

	if (pFind != NULL)
	{
		//pFind->UpdateDevice(pNew);
		delete pNew;
		return 0;
	}

	AddNewChild(pNew);

	if (!bPostMsg)
	{
		return 0;
	}

	if (m_pMsgRcvWnd != NULL)
	{
		m_pMsgRcvWnd->PostMessage(WM_IOT_DEVICEMGR_ADD, (WPARAM)pNew, (LPARAM)pNew);
	}
	
	return 0;
}

long CSttXDeviceMngr::DeleteDevice(CDataGroup *pParas)
{
	//
	CSttXDevice *pNew = new CSttXDevice();
	pNew->AppendCloneEx(*pParas);
	pNew->InitDevice();
	CSttXDevice *pFinde = (CSttXDevice*)FindByID(pNew->m_strSN);

	if (pFinde == NULL)
	{
		return 0;
	}

#ifndef _PSX_IDE_QT_
	if (m_pMsgRcvWnd != NULL)
	{
		m_pMsgRcvWnd->SendMessage(WM_IOT_DEVICEMGR_DELETE, (WPARAM)pFinde, (LPARAM)pFinde);
	}
#endif

	delete pNew;
	Delete(pFinde);


	/*CString strSN;
	BOOL bFind = pParas->GetDataValue("SN", strSN);

	if (!bFind)
	{
		return 0;
	}

	CExBaseObject *pFind = FindByID(strSN);

	if (pFind == NULL)
	{
		return 0;
	}*/

	

	//if (m_pMsgRcvWnd != NULL)
	//{
	//	m_pMsgRcvWnd->PostMessage(WM_IOT_DEVICEMGR_DELETE, (WPARAM)pFind, (LPARAM)pFind);
	//}
	//Delete(pFind);

    return 0;
}

long CSttXDeviceMngr::UpdateDeviceState(CDataGroup *pDevices)
{
	POS pos = pDevices->GetHeadPosition();
	CDataGroup *pDevice = NULL;
	CSttXDevice *pFind = NULL;
	CString strSN;

	while (pos != NULL)
	{
		pDevice = (CDataGroup *)pDevices->GetNext(pos);

		if (pDevice->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		if (!pDevice->GetDataValue("SN", strSN))
		{
			continue;

		}

		pFind  =(CSttXDevice*)FindByID(strSN);

		if (pFind != NULL)
		{
			pFind->InitDataValues(pDevice, FALSE);

#ifndef _PSX_IDE_QT_
			if (m_pMsgRcvWnd != NULL)
			{
				m_pMsgRcvWnd->PostMessage(WM_IOT_DEVICEMGR_UPDATE, (WPARAM)pFind, (LPARAM)pFind);
			}
#endif
		}
	}

	return 0;
}

//添加多个设备
void CSttXDeviceMngr::AddDevices(CDataGroup *pParas, BOOL bPostMsg)
{
	POS pos = pParas->GetHeadPosition();
	CDataGroup *p = NULL;

	while (pos != NULL)
	{
		p = (CDataGroup *)pParas->GetNext(pos);

		if (p->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		if (p->m_strDataType != _T("device"))
		{
			continue;
		}

		AddDevice(p, FALSE);
	}

	if (!bPostMsg)
	{
		return;
	}

#ifndef _PSX_IDE_QT_
	if (m_pMsgRcvWnd != NULL)
	{
		m_pMsgRcvWnd->PostMessage(WM_IOT_DEVICEMGR_ADD, (WPARAM)0, (LPARAM)0);
	}
#endif
}

CSttXDevice* CSttXDeviceMngr::FindDevice(const CString &strAttrID, const CString &strAttrValue)
{
	POS pos = GetHeadPosition();
	CSttXDevice *p = NULL;
	CString strValue;

	while (pos != NULL)
	{
		p = (CSttXDevice *)GetNext(pos);

		if (!p->GetDataValue(strAttrID, strValue))
		{
			continue;
		}

		if (strValue == strAttrValue)
		{
			return p;
		}
	}

	return NULL;
}

long CSttXDeviceMngr::FindDevice(CExBaseList &listDevice, const CString &strAttrID, const CString &strAttrValue)
{
	POS pos = GetHeadPosition();
	CSttXDevice *p = NULL;
	CString strValue;

	while (pos != NULL)
	{
		p = (CSttXDevice *)GetNext(pos);

		if (!p->GetDataValue(strAttrID, strValue))
		{
			continue;
		}

		if (strValue == strAttrValue)
		{
			listDevice.AddTail(p);
		}
	}

	return listDevice.GetCount();
}

long CSttXDeviceMngr::GetAllSelectDevices(CExBaseList &listDevices)
{
	POS pos = GetHeadPosition();
	CSttXDevice *p = NULL;

	while (pos != NULL)
	{
		p = (CSttXDevice *)GetNext(pos);

		if (p->m_nSelect == 1)
		{
			listDevices.AddTail(p);
		}
	}

	return listDevices.GetCount();
}


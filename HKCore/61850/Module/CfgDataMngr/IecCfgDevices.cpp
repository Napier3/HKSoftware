//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDevices.cpp  CIecCfgDevices

#include "stdafx.h"
#include "IecCfgDevices.h"

CIecCfgDataBase* CIecCfgDevices::FindIecCfgData(PEPCAPBUFFERITEM pItemData)
{
	CIecCfgDevice* pCfgDevice = NULL;

	POS pos = GetHeadPosition();
	while (pos)
	{
		pCfgDevice = (CIecCfgDevice*)GetNext(pos);
		return pCfgDevice->FindIecCfgData(pItemData);
	}

	return NULL;
}

CIecCfgDataBase* CIecCfgDevices::FindIecCfgData(BYTE *pDstMac,BYTE *pSrcMac,UINT APPID,UINT nCMT,UINT nChCount)
{
	CIecCfgDevice* pCfgDevice = NULL;

	POS pos = GetHeadPosition();
	while (pos)
	{
		pCfgDevice = (CIecCfgDevice*)GetNext(pos);
		return pCfgDevice->FindIecCfgData(pDstMac,pSrcMac,APPID,nCMT,nChCount);
	}

	return NULL;
}

void CIecCfgDevices::AddIecCfgDevice(const CString& strIecCfgFile)
{
	if (!IsFileExist(strIecCfgFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Iec61850配置文件%s不存在."),strIecCfgFile);
		return;
	}

	CIecCfgDevice* pNew = new CIecCfgDevice;
	pNew->OpenIecCfgFile(strIecCfgFile);

	if (pNew->m_strID == _T(""))
	{
		MessageBox(NULL,_T("设备ID的配置不能为空."),_T("提示"),MB_OK);
		delete pNew;
		return;
	}

	CIecCfgDevice* pCfgDevice = (CIecCfgDevice*)FindByID(pNew->m_strID);
	if (pCfgDevice)
	{
		pCfgDevice->DeleteAll();
		pCfgDevice->AppendCloneEx(*pNew);

		delete pNew;
	}
	else
	{
		AddNewChild(pNew);
	}
}

void CIecCfgDevices::RemoveIecCfgDevice(CIecCfgDevice* pCfgDevice)
{
	Remove(pCfgDevice);
}
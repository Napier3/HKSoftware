#include "stdafx.h"
#include "NetworkInterface.h"

#ifdef _PSX_IDE_QT_
#include "QT/NetworkInterface_QT.cpp"
#else
#include "VC/NetworkInterface_VC.cpp"
#endif

//系统缺省使用NET_DEVICENAME， 如果需要更换，则设置g_str_Net_DeviceName
CString g_str_Net_DeviceName = NET_DEVICENAME;
/***
void stt_net_add_ip_para(CDataGroup *pDataGroup, const CString &strID, long nIndex, const CString &strIP, const CString &strMask)
{
	CDataGroup *pNew = NULL;

	if (nIndex==0)
	{
		pNew = pDataGroup->AddNewGroup(strID, strID, strID);
	}
	else
	{
		CString strTemp, strIndex;
		strIndex.Format(_T("%d"), nIndex);
		strTemp = strID;
		strTemp += strIndex;
		pNew = pDataGroup->AddNewGroup(strTemp, strTemp, strID);
	}

	pNew->AddNewData(STT_SYS_DATA_ID_IP, STT_SYS_DATA_ID_IP, STT_SYS_DATA_ID_IP, strIP);
	pNew->AddNewData(STT_SYS_DATA_ID_mask, STT_SYS_DATA_ID_mask, STT_SYS_DATA_ID_mask, strMask);
}

long stt_net_get_ip(CDataGroup *pDataGroup)
{
	CStringArray astrIP, astrMask;
	long nCount = stt_net_get_ip(astrIP, astrMask);

	if (nCount == 0)
	{
		return 0;
	}

	stt_net_add_ip_para(pDataGroup, STT_SYS_DATA_ID_DeviceIP, 0, astrIP.GetAt(0), astrMask.GetAt(0));
	
	for (long k=1; k<nCount; k++)
	{
		stt_net_add_ip_para(pDataGroup, STT_SYS_DATA_ID_SubIP, k, astrIP.GetAt(k), astrMask.GetAt(k));
	}

	return nCount;
}


long stt_net_set_ip(CDataGroup *pDataGroup, const CString &strID, long nIPBeginIndex)
{
	CExBaseList listGroup;
	pDataGroup->SelectAllGroups(listGroup, strID);

	if (listGroup.GetCount() == 0)
	{
		return 0;
	}

	POS pos = listGroup.GetHeadPosition();
	CDataGroup *p = NULL;
	CStringArray astrIP, astrMask;
	CString strIP, strMask;
	long nCount = 0;

	while (pos != NULL)
	{
		p = (CDataGroup*)listGroup.GetNext(pos);

		if (!p->GetDataValue(STT_SYS_DATA_ID_IP, strIP))
		{
			continue;
		}

		p->GetDataValue(STT_SYS_DATA_ID_mask, strMask);
		astrIP.Add(strIP);
		astrMask.Add(strMask);
		nCount++;
	}

	listGroup.RemoveAll();

	if (nCount == 0)
	{
		return 0;
	}

	stt_net_set_ip(astrIP, astrMask);

	return nCount;
}

long stt_net_set_ip(CDataGroup *pDataGroup)
{
	//不修改主IP

	//从第一个从IP地址修改
	return stt_net_set_ip(pDataGroup, STT_SYS_DATA_ID_SubIP, 1);
}
***/

#ifndef _PSX_QT_LINUX_
long stt_net_set_gateway(const CString &strGateWay)
{
	return 1;
}

long stt_net_set_gateway(const CString &strGateWay,long nMetric)
{
	return 1;
}

// long stt_net_set_gateway(const CStringArray &astrGateWay,long* nMetric)
// {
// 	return 1;
// }

#endif

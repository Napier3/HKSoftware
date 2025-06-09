//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MMS_STACK_CFG.cpp  CMMS_STACK_CFG


#include "stdafx.h"
#include "MMS_STACK_CFG.h"
#include "../../../System/Module/XAtsSysSvrGlobalDef.h"

#ifdef _PSX_IDE_QT_
#include "../../../Module/IniFileMngr/IniFileApi.h"
#endif

CMMS_STACK_CFG::CMMS_STACK_CFG()
{
	CMMS_STACK_CFGXmlRWKeys::Create();

	//初始化属性

	//初始化成员变量
	m_pNetworkAddressing = NULL;
}

CMMS_STACK_CFG::~CMMS_STACK_CFG()
{

	CMMS_STACK_CFGXmlRWKeys::Release();

}

long CMMS_STACK_CFG::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMMS_STACK_CFG::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMMS_STACK_CFG::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CMMS_STACK_CFG::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClasID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClasID = p->GetClassID();

		if (nClasID == MMSCLASSID_CSTKCFG_NETWORKADDRESSING)
		{
			m_pNetworkAddressing = (CStkCfg_NetworkAddressing *)p;
		}
	}
	
}

BOOL CMMS_STACK_CFG::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CMMS_STACK_CFG *p = (CMMS_STACK_CFG*)pObj;

	return TRUE;
}

BOOL CMMS_STACK_CFG::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CMMS_STACK_CFG *p = (CMMS_STACK_CFG*)pDest;

	return TRUE;
}

CBaseObject* CMMS_STACK_CFG::Clone()
{
	CMMS_STACK_CFG *p = new CMMS_STACK_CFG();
	Copy(p);
	return p;
}

BOOL CMMS_STACK_CFG::CanPaste(UINT nClassID)
{
	if (nClassID == MMSCLASSID_CSTKCFG_MMS)
	{
		return TRUE;
	}

	if (nClassID == MMSCLASSID_CSTKCFG_TRANSPORT)
	{
		return TRUE;
	}

	if (nClassID == MMSCLASSID_CSTKCFG_NETWORKADDRESSING)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CMMS_STACK_CFG::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCStkCfg_MMSKey)
	{
		pNew = new CStkCfg_MMS();
	}
	else if (strClassID == pXmlKeys->m_strCStkCfg_TransportKey)
	{
		pNew = new CStkCfg_Transport();
	}
	else if (strClassID == pXmlKeys->m_strCStkCfg_NetworkAddressingKey)
	{
		pNew = new CStkCfg_NetworkAddressing();
	}

	return pNew;
}

CExBaseObject* CMMS_STACK_CFG::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MMSCLASSID_CSTKCFG_MMS)
	{
		pNew = new CStkCfg_MMS();
	}
	else if (nClassID == MMSCLASSID_CSTKCFG_TRANSPORT)
	{
		pNew = new CStkCfg_Transport();
	}
	else if (nClassID == MMSCLASSID_CSTKCFG_NETWORKADDRESSING)
	{
		pNew = new CStkCfg_NetworkAddressing();
	}

	return pNew;
}


CString mms_CONFIG_PATH_Outer()
{
	CString strFile;
	strFile = atssys_GetProtocolPath();
	strFile += _T("Bin\\osicfg.xml");
	return strFile;
}


CString mms_VMD_PATH_Outer()
{
	CString strFile;
	strFile = atssys_GetProtocolPath();
	strFile += _T("Bin\\VMD.ini");
	return strFile;
}

void CMMS_STACK_CFG::Open_MMS_STACK_CFG_Outer()
{
	m_strFilePath = mms_CONFIG_PATH_Outer();

	OpenXmlFile(m_strFilePath, CMMS_STACK_CFGXmlRWKeys::g_pXmlKeys);
}

void CMMS_STACK_CFG::Save_MMS_STACK_CFG_Outer()
{
	m_strFilePath = mms_CONFIG_PATH_Outer();

	SaveXmlFile(m_strFilePath, CMMS_STACK_CFGXmlRWKeys::g_pXmlKeys);
}

void CMMS_STACK_CFG::WriteIpToVMDFile()
{
	CString strFile = mms_VMD_PATH_Outer();
	CStkCfg_RemoteAddressList *pRemoteAddressList = GetRemoteAddressList();
	POS pos = pRemoteAddressList->GetHeadPosition();
	CStkCfg_RemoteAddress *pAddr = NULL;
	long nIndex = 1;
	CString strDevice;
	CString strIP = _T("IP1");
	CString strModel = _T("MODEL");

	while (pos != NULL)
	{
		pAddr = (CStkCfg_RemoteAddress *)pRemoteAddressList->GetNext(pos);

		strDevice.Format(_T("DEVICE%d"), nIndex);

#ifdef _PSX_IDE_QT_
		IniFile::writeInit(strFile, strDevice, strIP, pAddr->GetIP());
		IniFile::writeInit(strFile, strDevice, strModel, pAddr->m_strModel);
		nIndex++;
#else
#ifdef UNICODE
		WritePrivateProfileString(
			(LPCWSTR)strDevice.GetString(),
			(LPCWSTR)strIP.GetString(),
			(LPCWSTR)pAddr->GetIP().GetString(),
			(LPCWSTR)strFile.GetString());
		nIndex++;

		WritePrivateProfileString(
			(LPCWSTR)strDevice.GetString(),
			(LPCWSTR)strModel.GetString(),
			(LPCWSTR)pAddr->m_strModel.GetString(),
			(LPCWSTR)strFile.GetString());
#else
		WritePrivateProfileString(
			strDevice,
			strIP,
			pAddr->GetIP(),
			strFile);
		nIndex++;

		WritePrivateProfileString(
			strDevice,
			strModel,
			pAddr->m_strModel,
			strFile);
#endif
#endif
	}
}

CStkCfg_RemoteAddressList* CMMS_STACK_CFG::GetRemoteAddressList()
{
	ASSERT (m_pNetworkAddressing != NULL);
	if (m_pNetworkAddressing == NULL)
	{
		return NULL;
	}

	return m_pNetworkAddressing->GetRemoteAddressList();
}



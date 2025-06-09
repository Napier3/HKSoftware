// SttNativeCfgMngrGlobal.cpp
//

#include "stdafx.h"
#include "SttNativeCfgMngrGlobal.h"

CSttNativeCfgXmlRWKeys* CSttNativeCfgXmlRWKeys::g_pXmlKeys = NULL;
long CSttNativeCfgXmlRWKeys::g_nSTTNATIVECFGXMLRef = 0;

// CSttNativeCfgXmlRWKeys

CSttNativeCfgXmlRWKeys::CSttNativeCfgXmlRWKeys():CVerUpdateHisXmlRWKeys()
{
	m_strSttNativeCfgKey = L"SttNativeCfg";
	m_strLiveUpdateKey = L"liveupdate";
	m_strHisVerKey = L"hisver";
	m_strYunKey = L"yun";
	m_strMntKey = L"mnt";
	m_strIPKey = L"ip";
	m_strPortKey = L"port";
	m_strFtpPortKey= L"ftpport";
	m_strID_SystemKey = L"ID_System";
	m_strIndex_SystemKey = L"Index_System";
	m_strRootFilesKey = L"rootfiles";
	m_strUpdateDeviceXml = L"UpdateDeviceXml";
}

CSttNativeCfgXmlRWKeys::~CSttNativeCfgXmlRWKeys()
{
}

CSttNativeCfgXmlRWKeys* CSttNativeCfgXmlRWKeys::Create()
{
	g_nSTTNATIVECFGXMLRef++;

	if (g_nSTTNATIVECFGXMLRef == 1)
	{
		g_pXmlKeys = new CSttNativeCfgXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CSttNativeCfgXmlRWKeys::Release()
{
	g_nSTTNATIVECFGXMLRef--;

	if (g_nSTTNATIVECFGXMLRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}

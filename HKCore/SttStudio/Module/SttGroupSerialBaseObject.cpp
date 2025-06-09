#include "stdafx.h"
#include "SttTestAppCfg.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/API/FileApi.h"
#include "../SttGlobalDef.h"

#include "../SttTestBase/SttXmlSerialize.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BSTR CSttTestAppCfg::m_strTypeKey = L"type";
BSTR CSttTestAppCfg::m_strTestAppCfgKey = L"stt-testapp-cfg";
BSTR CSttTestAppCfg::m_strLocalIPKey = L"local-ip";
BSTR CSttTestAppCfg::m_strTestAppIPKey = L"testapp-ip";
BSTR CSttTestAppCfg::m_strTestAppSNKey = L"testapp-sn";
BSTR CSttTestAppCfg::m_strTestServerPortKey = L"testserver-port";
BSTR CSttTestAppCfg::m_strNativeServerPortKey = L"nativeserver-port";
BSTR CSttTestAppCfg::m_strMulticastIPKey = L"multicast-ip";
BSTR CSttTestAppCfg::m_strMulticastPortKey = L"multicast-port";
BSTR CSttTestAppCfg::m_strMultiLocalPortKey = L"multicast-localport";
BSTR CSttTestAppCfg::m_strCloudIPKey = L"cloud-ip";
BSTR CSttTestAppCfg::m_strCloudServerPortKey = L"cloudserver-port";
BSTR CSttTestAppCfg::m_strCopNameKey = L"cop-name";
BSTR CSttTestAppCfg::m_strUserNameKey = L"user-name";
BSTR CSttTestApps::m_strTestAppsKey = L"stt-testapps";


/*
6.2.1ͨ������
���Զ��������֮��ͳһ����TCP/IPЭ�����ͨ�š�����ϵͳ��Ʒ����Ҫ�󣬲����ǵײ�Ĳ��Կ��Ʋ��֡��Զ�������Ϊ��ͬ�ķ���ˡ�
�����ǵײ���Է��񣺶˿ںŶ�Ϊ19814��1+1998+2014����
�����ǵײ��Զ����Է��񣺶˿ںŶ�Ϊ19815��
��ƽ̨Զ�̿��Ʒ��񣺶˿ں�Ϊ19816��
��ƽ̨�������񼴱��������������񣺶˿ں�Ϊ19817��
*/
CSttTestAppCfg::CSttTestAppCfg()
{
	m_strLocalIP = _T("127.0.0.1");
	m_strTestAppIP = _T("127.0.0.1");
	m_nTestServerPort = STT_PORT_TEST_SERVER;
	m_nNativeServerPort = STT_PORT_NATIVE_SERVER;
	m_strMulticastIP = _T("234.5.6.7");
	m_nMulticastPort = 8085;
	m_nMultiLocalPort = 8086;
	m_strCloudIP = _T("127.0.0.1");
	m_nCloudServerPort = STT_PORT_CLOUD_SERVER;
	m_strCopName = _T("�Ͼ����Ƶ���");
	m_strUserName = _T("test");
	m_strType = STT_TEST_APP_TYPE_LOCAL;
	m_strTestAppSN = _T("Ponovo-001");
}

CSttTestAppCfg::~CSttTestAppCfg()
{
	//Save();
}

CString CSttTestAppCfg::GetOldCfgFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("SttTestAppCfg.xml");

	return strFile;
}

long CSttTestAppCfg::Open()
{
	m_strFile = GetOldCfgFile();

	if (!IsFileExist(m_strFile))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�����������ļ���%s �Ҳ�����"),m_strFile.GetString());
		return 0;
	}

	return OpenXmlFile(m_strFile, m_strTestAppCfgKey, NULL);
}

long CSttTestAppCfg::Save()
{
#ifdef _PSX_QT_LINUX_
    return 1;
#endif

	if (m_strFile.GetLength() < 5)
	{
		return 0;
	}

	SaveXmlFile(m_strFile, NULL);

	return 1;
}

//2021-8-12  lijunqing
CString CSttTestAppCfg::GetSttCfgFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("TestAppConfig.xml");
	return strFile;
}

void CSttTestAppCfg::SttOpen(const CString &strFile)
{
	CString strTemp;

	if (IsFileExist(strFile))
	{
		strTemp = strFile;
	}
	else
	{
		strTemp = GetSttCfgFile();
	}
	
	CSttXmlSerializeTool oTool;
	CSttXmlSerializeBase *pXmlSierialize = oTool.CreateXmlSerializeRead(strTemp);

	if (pXmlSierialize != NULL)
	{
		if (stt_xml_serialize(pXmlSierialize))
		{//�ļ���ȡ�ɹ����򷵻�
			m_strFile = strTemp;
			return;
		}
	}

	//�ļ���ȡʧ�ܣ���ȡ�ϰ汾�ļ��������ϰ汾����
	Open();
}

void CSttTestAppCfg::SttSave(const CString &strFile)
{
	CString strTemp;

	if (strFile.GetLength() > 5)
	{
		strTemp = strFile;
	}
	else
	{
		strTemp = GetSttCfgFile();
	}

	CSttXmlSerializeTool oTool;
	CSttXmlSerializeBase *pXmlSierialize = oTool.CreateXmlSerializeWrite();
	stt_xml_serialize(pXmlSierialize);
	oTool.Stt_WriteFile(strTemp);
}

void CSttTestAppCfg::SttSetXml(const CString &strXml)
{
	CSttXmlSerializeTool oTool;
	CSttXmlSerializeBase *pXmlSierialize = oTool.CreateXmlSerializeRead_String(strXml);

	if (pXmlSierialize != NULL)
	{
		if (stt_xml_serialize(pXmlSierialize))
		{//�ļ���ȡ�ɹ����򷵻�
			m_strFile.Empty();
			return;
		}
	}
}

void CSttTestAppCfg::SttSetXml_UTF8(const CString &strXml)
{
	const char *pszXml = strXml.GetString();

	SttSetXml_UTF8((char*)pszXml, strXml.GetLength());
}

//SttSetXml_UTF8:
// 	CFile file;
// 	CString strSttFile = oSttTestAppCfg.GetSttCfgFile();
// 
// 	if (file.Open(strSttFile, CFile::modeRead))
// 	{
// 		long nLen = file.GetLength();
// 		char *pBuf = new char [nLen+10];
// 		file.Read(pBuf, nLen);
// 		pBuf[nLen] = 0;
// 		oSttTestAppCfg.SttSetXml_UTF8(pBuf, nLen);
// 		delete pBuf;
// 		file.Close();
// 	}
void CSttTestAppCfg::SttSetXml_UTF8(char *pszBuffer, long nLen)
{
	CSttXmlSerializeTool oTool;
	CSttXmlSerializeBase *pXmlSierialize = oTool.CreateXmlSerializeRead_String_UTF8(pszBuffer, nLen);

	if (pXmlSierialize != NULL)
	{
		if (stt_xml_serialize(pXmlSierialize))
		{//�ļ���ȡ�ɹ����򷵻�
			m_strFile.Empty();
			return;
		}
	}
}

BOOL CSttTestAppCfg::stt_xml_serialize(CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pSerialize =pXmlSierialize->xml_serialize("test-app config", "test-app", "test-app", stt_ParaGroupKey());

	if (pSerialize == NULL)
	{
		return FALSE;
	}

	pSerialize->xml_serialize("macro-type","macro-type","","string", m_strMacroFileID);
	pSerialize->xml_serialize("mode","mode","","string", m_strType);
	pSerialize->xml_serialize("local-ip","local-ip","","string", m_strLocalIP);
	pSerialize->xml_serialize("remote-ip","remote-ip","","string", m_strTestAppIP);
	pSerialize->xml_serialize("remote-port","remote-port","","number", m_nTestServerPort);
	pSerialize->xml_serialize("ats-server-port","ats-server-port","","number", m_nNativeServerPort);
	pSerialize->xml_serialize("multicast-ip","multicast-ip","","string", m_strMulticastIP);
	pSerialize->xml_serialize("multicast-port","multicast-port","","number", m_nMulticastPort);
	pSerialize->xml_serialize("multicast-local-port","multicast-local-port","","string", m_nMultiLocalPort);
	pSerialize->xml_serialize("cloud-server-ip","cloud-server-ip","","string", m_strCloudIP);
	pSerialize->xml_serialize("cloud-server-port","cloud-server-port","","number", m_nCloudServerPort);

	pSerialize->xml_serialize("cop-name","cop-name","","string", m_strCopName);
	pSerialize->xml_serialize("user-name","user-name","","string", m_strUserName);

	return TRUE;
}

void CSttTestAppCfg::SaveAfterConfig()
{
	if (m_strFile.GetLength() == 0)
	{//��ʾͨ���ⲿ���ã��������ļ�
		return;
	}

	//�������¸�ʽ�����ϸ�ʽ
	SttSave(_T(""));
}

long CSttTestAppCfg::XmlReadOwn(CXmlRWNodeBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_GetElementText(m_strTypeKey, oElement, m_strType);
	xml_GetElementText(m_strLocalIPKey, oElement, m_strLocalIP);
	xml_GetElementText(m_strTestAppIPKey, oElement, m_strTestAppIP);
	xml_GetElementText(m_strTestAppSNKey, oElement, m_strTestAppSN);
	xml_GetElementText(m_strTestServerPortKey, oElement, m_nTestServerPort);
	xml_GetElementText(m_strNativeServerPortKey, oElement, m_nNativeServerPort);
	xml_GetElementText(m_strMulticastIPKey, oElement, m_strMulticastIP);
	xml_GetElementText(m_strMulticastPortKey, oElement, m_nMulticastPort);
	xml_GetElementText(m_strMultiLocalPortKey, oElement, m_nMultiLocalPort);
	xml_GetElementText(m_strCloudIPKey, oElement, m_strCloudIP);
	xml_GetElementText(m_strCloudServerPortKey, oElement, m_nCloudServerPort);
	xml_GetElementText(m_strCopNameKey, oElement, m_strCopName);
	xml_GetElementText(m_strUserNameKey, oElement, m_strUserName);

	return 0;
}

long CSttTestAppCfg::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetElementText(m_strTypeKey, oXMLDoc, oElement, m_strType);
	xml_SetElementText(m_strLocalIPKey, oXMLDoc, oElement, m_strLocalIP);
	xml_SetElementText(m_strTestAppIPKey, oXMLDoc, oElement, m_strTestAppIP);
	xml_SetElementText(m_strTestAppSNKey, oXMLDoc, oElement, m_strTestAppSN);
	xml_SetElementText(m_strTestServerPortKey, oXMLDoc, oElement, m_nTestServerPort);
	xml_SetElementText(m_strNativeServerPortKey, oXMLDoc, oElement, m_nNativeServerPort);
	xml_SetElementText(m_strMulticastIPKey, oXMLDoc, oElement, m_strMulticastIP);
	xml_SetElementText(m_strMulticastPortKey, oXMLDoc, oElement, m_nMulticastPort);
	xml_SetElementText(m_strMultiLocalPortKey, oXMLDoc, oElement, m_nMultiLocalPort);
	xml_SetElementText(m_strCloudIPKey, oXMLDoc, oElement, m_strCloudIP);
	xml_SetElementText(m_strCloudServerPortKey, oXMLDoc, oElement, m_nCloudServerPort);
	xml_SetElementText(m_strCopNameKey, oXMLDoc, oElement, m_strCopName);
	xml_SetElementText(m_strUserNameKey, oXMLDoc, oElement, m_strUserName);

	return 0;
}



////////////////////////////////////////////////////////////////////////////////
//CSttTestApps
CSttTestApps* CSttTestApps::g_pSttTestApps = NULL;
long CSttTestApps::g_nSttTestAppsRef = 0;

CSttTestApps::CSttTestApps()
{

}

CSttTestApps::~CSttTestApps()
{

}

CSttTestApps* CSttTestApps::Create()
{
	g_nSttTestAppsRef++;

	if (g_nSttTestAppsRef == 1)
	{
		g_pSttTestApps = new CSttTestApps();

		if (!g_pSttTestApps->Open())
		{
			g_pSttTestApps->Save();
		}
	}

	return g_pSttTestApps;
}

void CSttTestApps::Release()
{
	g_nSttTestAppsRef--;

	if (g_nSttTestAppsRef == 0)
	{
		g_pSttTestApps->Save();
		delete g_pSttTestApps;
		g_pSttTestApps = NULL;
	}
}

CExBaseObject* CSttTestApps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	pNew = new CSttTestAppCfg();
	return pNew;
}

CExBaseObject* CSttTestApps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;
	pNew = new CSttTestAppCfg();

	return pNew;
}

long CSttTestApps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CSttTestApps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

CSttTestAppCfg* CSttTestApps::FindByMacroFileID(const CString &strMacroFileID)
{
	CSttTestAppCfg* pFind = NULL;
	CSttTestAppCfg* pApp = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pApp = (CSttTestAppCfg*)GetNext(pos);

		if (pApp->IsMacroFileID(strMacroFileID) )
		{
			pFind = pApp;
			break;
		}
	}

	return pFind;
}

long CSttTestApps::Save()
{
#ifdef _PSX_QT_LINUX_
	return 1;
#endif

	SaveXmlFile(m_strFile, NULL);
	return 1;
}

long CSttTestApps::Open()
{
	m_strFile = (CString)_P_GetConfigPath();
	m_strFile += _T("SttTestApps.xml");

	if (!IsFileExist(m_strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�����������ļ���%s �Ҳ�����"),m_strFile.GetString());
		return 0;
	}

	return OpenXmlFile(m_strFile, m_strTestAppsKey, NULL);
}

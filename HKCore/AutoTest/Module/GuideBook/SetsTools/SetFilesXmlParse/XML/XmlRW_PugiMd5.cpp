#include "stdafx.h"
#include "XmlRW_PugiMd5.h"
#include "../SetFilesXml_DSC.h"

#include"../../../../../../Module/API/StringConvert/String_Utf8_To_Gbk.h"
#ifndef _PSX_QT_LINUX_
#include "oleauto.h"
#endif
#include "../../../../../../Module/API/StringConvert/String_Gbk_To_Utf8.h"
#include "../../../../../../Module/API/Xmd5.h"

#ifdef XML_USE_PUGIXML


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXmlRWDoc_PugiMd5::CXmlRWDoc_PugiMd5()
{

}


CXmlRWDoc_PugiMd5::~CXmlRWDoc_PugiMd5()
{

}

BOOL CXmlRWDoc_PugiMd5::xml_OpenFile(const CString &strFile)
{
	long nRet = CXmlRWDoc_Pugi::xml_OpenFile(strFile);

	ValidateMd5();

	return nRet;
}

BOOL CXmlRWDoc_PugiMd5::SaveXml(const CString &strFilePath)
{
	CalMd5();

// 	char* pszFile = m_oDevice.get_xml_string();
// 	CFile oFile;

// 	if (oFile.Open(strFilePath, CFile::modeWrite))
// 	{
// 		oFile.Write(pszFile, strlen(pszFile));
// 		oFile.Close();
// 		delete []pszFile;
// 		return TRUE;
// 	}
// 	else
// 	{
// 		return FALSE;
// 	}

	return CXmlRWDoc_Pugi::SaveXml(strFilePath);
}

void Char_to_WChar(char *pSrc, wchar_t **ppDest)
{
	long nLen = strlen(pSrc);

	*ppDest = new wchar_t[nLen + 1];
	char* p1 = pSrc;
	wchar_t *p2 = *ppDest;

	while (*p1 != 0)
	{
		*p2 = *p1;
		p1++;
		p2++;
	}

	*p2 = 0;
}

void CXmlRWDoc_PugiMd5::CalMd5()
{
	return;
	m_oDevice = m_oPugiXmlDoc.child(CSetFileXmlParseXmlRWKeys::CSetFilesXml_DSCKey());

	pugi::xml_node ndHeader = GetHeader();
	pugi::xml_node ndHashInfo = GetHashInfo();
	pugi::xml_node ndUpdate = GetUpdate();
	pugi::xml_node ndevInfo = GetevInfo();
	pugi::xml_node ndFileInfo = GetFileInfo();
	pugi::xml_node ndRemark = GetRemark();

	long nSettings = GetSettingsCount();
	long k = 0;
	CString strSettingsTotal;
	char* pSettings = NULL;

	for (k=0; k<nSettings; k++)
	{
		//pugi::xml_node noSettings = GetSettings(k);
		pSettings = GetSettings_String(k);  //返回的是utf-8编码格式
		strSettingsTotal.AppendFormat(_T("%s"), pSettings);
		delete []pSettings;
		pSettings = NULL;
	}

	SYSTEMTIME oTime;
	::GetLocalTime(&oTime);
	CString strTime;
	strTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d")
		, oTime.wYear, oTime.wMonth, oTime.wDay, oTime.wHour, oTime.wMinute, oTime.wSecond);

	BSTR strAttr = L"updateTime";
	pugi::xml_attribute attrTime = ndHeader.attribute(strAttr);
	char* pszTime;
	CString_to_char(strTime, &pszTime);
	//attrTime.set_value((const char*)pszTime);
	wchar_t *pWTime = NULL;
	Char_to_WChar(pszTime, &pWTime);
	attrTime.set_value(pWTime);
	delete []pszTime;
	delete []pWTime;

	//去掉空格、制表符、回车符、换行符
	strSettingsTotal = RemoveWhitespace(strSettingsTotal);

	//已经是UTF-8编码，不用再转换了。转换反而不对
	char *pchVal = NULL;
	//char *pszUtf8 = NULL;
	int nSize = CString_to_char(strSettingsTotal,&pchVal);
	//int nDestLen = 0;
	//gbk_to_utf8_r((unsigned char*)pchVal, nSize, (unsigned char**)&pszUtf8, &nDestLen, 0);

	CXMD5 oMD5;
	oMD5.update(pchVal, nSize);
	string str = oMD5.toString();
	CString strMd5 = str.c_str();
	UpdateHeader(strMd5);

	delete []pchVal;
}

void CXmlRWDoc_PugiMd5::UpdateHeader(const CString strMd5)
{
	return;
	m_oDevice = m_oPugiXmlDoc.child(CSetFileXmlParseXmlRWKeys::CSetFilesXml_DSCKey());

	pugi::xml_node ndHeader = GetHeader();
	BSTR strAttr = L"md5";
	pugi::xml_attribute attrMd5 = ndHeader.attribute(strAttr);
	char* pszMd5;
	wchar_t *pWMd5 = NULL;
	CString_to_char(strMd5, &pszMd5);
	Char_to_WChar(pszMd5, &pWMd5);
	attrMd5.set_value(pWMd5);
	delete []pszMd5;
	delete []pWMd5;
}

CString CXmlRWDoc_PugiMd5::RemoveWhitespace(const CString& input)
{
	CString result;
	const char* whitespaceChars = " \t\n\r"; // 空格、制表符、换行符、回车符

	// 遍历输入字符串中的每个字符
	for (int i = 0; i < input.GetLength(); ++i)
	{
		// 如果当前字符不在whitespaceChars中，则添加到结果字符串
		if (strchr(whitespaceChars, input[i]) == NULL)
		{
			result += input[i];
		}
	}

	return result;
}

void CXmlRWDoc_PugiMd5::ValidateMd5()
{
	m_oDevice = m_oPugiXmlDoc.child(CSetFileXmlParseXmlRWKeys::CSetFilesXml_DSCKey());
	

// 	pugi::xml_node ndHeader = GetHeader();
// 	pugi::xml_node ndHashInfo = GetHashInfo();
// 	pugi::xml_node ndUpdate = GetUpdate();
// 	pugi::xml_node ndevInfo = GetevInfo();
// 	pugi::xml_node ndFileInfo = GetFileInfo();
// 	pugi::xml_node ndRemark = GetRemark();
// 
// 	long nSettings = GetSettingsCount();
// 	long k = 0;
// 
// 	for (k=0; k<nSettings; k++)
// 	{
// 		pugi::xml_node ndSettings = GetSettings(k);
// 		CalSettings(ndSettings);
// 	}

	long nSettings = GetSettingsCount();
	long k = 0;
	CString strSettingsTotal;
	char* pSettings = NULL;

	for (k=0; k<nSettings; k++)
	{
		//pugi::xml_node noSettings = GetSettings(k);
		pSettings = GetSettings_String(k);  //返回的是utf-8编码格式
		strSettingsTotal.AppendFormat(_T("%s"), pSettings);
		delete []pSettings;
		pSettings = NULL;
	}

	//去掉空格、制表符、回车符、换行符
	strSettingsTotal = RemoveWhitespace(strSettingsTotal);

	//已经是UTF-8编码，不用再转换了。转换反而不对
	char *pchVal = NULL;
	//char *pszUtf8 = NULL;
	int nSize = CString_to_char(strSettingsTotal,&pchVal);
	//int nDestLen = 0;
	//gbk_to_utf8_r((unsigned char*)pchVal, nSize, (unsigned char**)&pszUtf8, &nDestLen, 0);

	CXMD5 oMD5;
	oMD5.update(pchVal, nSize);
	string str = oMD5.toString();
	CString strMd5 = str.c_str();

	CFile oFile;
	CString strFile = _T("D:\\0\\SetsFileTest\\FileAfterOpen.txt");
	if (oFile.Open(strFile, CFile::modeWrite|CFile::modeCreate))
	{
		oFile.Write(pchVal, strlen(pchVal));
		oFile.Close();
	}
	
	delete []pchVal;

	pchVal = NULL;
	strSettingsTotal.Empty();
	for (k=0; k<nSettings; k++)
	{
		//pugi::xml_node noSettings = GetSettings(k);
		pSettings = GetSettings_String(k);  //返回的是utf-8编码格式
		strSettingsTotal.AppendFormat(_T("%s"), pSettings);
		delete []pSettings;
		pSettings = NULL;
	}

	//去掉空格、制表符、回车符、换行符
	strSettingsTotal = RemoveWhitespace(strSettingsTotal);
	nSize = CString_to_char(strSettingsTotal,&pchVal);
	CXMD5 oMD52;
	oMD52.update(pchVal, nSize);
	string str2 = oMD52.toString();
	CString strMd52 = str2.c_str();

	CFile oFile2;
	CString strFile2 = _T("D:\\0\\SetsFileTest\\FileAfterOpen2.txt");
	if (oFile2.Open(strFile2, CFile::modeWrite|CFile::modeCreate))
	{
		oFile2.Write(pchVal, strlen(pchVal));
		oFile2.Close();
	}

	delete []pchVal;
}


pugi::xml_node CXmlRWDoc_PugiMd5::GetHeader()
{
	return m_oDevice.child(CSetFileXmlParseXmlRWKeys::CSetsFileXml_HeaderKey());
}

pugi::xml_node CXmlRWDoc_PugiMd5::GetHashInfo()
{
	return m_oDevice.child(CSetFileXmlParseXmlRWKeys::CSetsFileXml_HashInfoKey());
}

pugi::xml_node CXmlRWDoc_PugiMd5::GetUpdate()
{
	return m_oDevice.child(CSetFileXmlParseXmlRWKeys::CSetsFileXml_UpdateKey());
}

pugi::xml_node CXmlRWDoc_PugiMd5::GetevInfo()
{
	return m_oDevice.child(CSetFileXmlParseXmlRWKeys::CSetsFileXml_DevInfoKey());
}

pugi::xml_node CXmlRWDoc_PugiMd5::GetFileInfo()
{
	return m_oDevice.child(CSetFileXmlParseXmlRWKeys::CSetsFileXml_FileInfoKey());
}

pugi::xml_node CXmlRWDoc_PugiMd5::GetRemark()
{
	return m_oDevice.child(CSetFileXmlParseXmlRWKeys::CSetsFileXml_RemarkKey());
}


long CXmlRWDoc_PugiMd5::GetSettingsCount()
{
	long nCount = 0;
	pugi::xml_node nd = m_oDevice.child(CSetFileXmlParseXmlRWKeys::CSetsFileXml_SettingsKey());

	while (! nd.empty())
	{
		nCount++;
		nd = nd.next_sibling(CSetFileXmlParseXmlRWKeys::CSetsFileXml_SettingsKey());
	}

	return nCount;
}

pugi::xml_node CXmlRWDoc_PugiMd5::GetSettings(long nIndex)
{
	long nCount = 0;
	pugi::xml_node nd = m_oDevice.child(CSetFileXmlParseXmlRWKeys::CSetsFileXml_SettingsKey());

	while (! nd.empty())
	{
		if (nCount == nIndex)
		{
			return nd;
		}

		nd = nd.next_sibling(CSetFileXmlParseXmlRWKeys::CSetsFileXml_SettingsKey());
		nCount++;
	}

	return pugi::xml_node();
}

//返回值是new出来的。注意释放
char* CXmlRWDoc_PugiMd5::GetSettings_String(long nIndex)
{
	pugi::xml_node oNode = GetSettings(nIndex);

	if (oNode.empty())
	{
		return NULL;
	}

	return oNode.get_xml_string();
}

void CXmlRWDoc_PugiMd5::CalSettings(pugi::xml_node ndSettings)
{
	//遍历Settings的属性
	pugi::xml_attribute attr = ndSettings.first_attribute();

	while (! attr.empty())
	{
		attr = attr.next_attribute();
	}

	//遍历InfoGrp
	pugi::xml_node ndInfoGrp = ndSettings.first_child();

	while (! ndInfoGrp.empty())
	{
		CalSettingsInfoGrp(ndInfoGrp);
		ndInfoGrp = ndInfoGrp.next_sibling();
	}
}

void CXmlRWDoc_PugiMd5::CalSettingsInfoGrp(pugi::xml_node ndInfoGrp)
{
	pugi::xml_attribute attr = ndInfoGrp.first_attribute();

	while (! attr.empty())
	{
		attr = attr.next_attribute();
	}


	//遍历SI
	pugi::xml_node ndSI = ndInfoGrp.first_child();

	while (! ndSI.empty())
	{
		CalSettingsInfoGrpSI(ndSI);
		ndSI = ndSI.next_sibling();
	}
}

void CXmlRWDoc_PugiMd5::CalSettingsInfoGrpSI(pugi::xml_node ndSI)
{
	pugi::xml_attribute attr = ndSI.first_attribute();

	while (! attr.empty())
	{
		attr = attr.next_attribute();
	}
}


#endif //XML_USE_PUGIXML

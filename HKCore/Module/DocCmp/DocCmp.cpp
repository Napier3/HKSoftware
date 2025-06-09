//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DocCmp.cpp  CDocCmp


#include "stdafx.h"
#include "DocCmp.h"

#include "DocXRead_Word.h"

long g_nDocmp_DebugGroup = 0;
long g_nDocToXmlFormat = _PUGI_XML_TYPE_;

void doctoxml_change_file_postfix(CString &strFile)
{
	if (g_nDocToXmlFormat == _PUGI_XML_TYPE_)
	{
		strFile = ChangeFilePostfix(strFile, _T("xml"));
	}
	else if (g_nDocToXmlFormat == _JSON_TYPE_)
	{
		strFile = ChangeFilePostfix(strFile, _T("jsn"));
	}
	else
	{
		strFile = ChangeFilePostfix(strFile, _T("xml"));
	}
}

CDataGroup* CDocCmp::m_pDocCmpConfig = NULL;

void CDocCmp::InitDocCmpConfig()
{
	if (m_pDocCmpConfig == NULL)
	{
		m_pDocCmpConfig = new CDataGroup();
		CString strFile;
		strFile = _P_GetConfigPath();
		strFile += _T("XDocCmpConfig.xml");

		m_pDocCmpConfig->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	}
}

void CDocCmp::FreeDocCmpConfig()
{
	if (m_pDocCmpConfig != NULL)
	{
		delete m_pDocCmpConfig;
		m_pDocCmpConfig = NULL;
	}
}

CDataGroup* CDocCmp::GetDocCmpConfig()
{
	return m_pDocCmpConfig;
}



CDocCmp::CDocCmp()
{
	//初始化属性
	m_pDocXReadInterface = NULL;

	//初始化成员变量

	OpenDocCmpConfig();
	m_pProgress = NULL;
}

CDocCmp::~CDocCmp()
{
	
}

void CDocCmp::OpenDocCmpConfig()
{
	
}

long CDocCmp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDocCmpXmlRWKeys *pXmlKeys = (CDocCmpXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDocCmp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDocCmpXmlRWKeys *pXmlKeys = (CDocCmpXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CDocCmp::InitAfterRead()
{
}

BOOL CDocCmp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CDocCmp *p = (CDocCmp*)pObj;

	return TRUE;
}

BOOL CDocCmp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDocCmp *p = (CDocCmp*)pDest;

	return TRUE;
}

CBaseObject* CDocCmp::Clone()
{
	CDocCmp *p = new CDocCmp();
	Copy(p);
	return p;
}

CExBaseObject* CDocCmp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDocCmpXmlRWKeys *pXmlKeys = (CDocCmpXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDocFileKey)
	{
		pNew = new CDocFile();
	}

	return pNew;
}

CExBaseObject* CDocCmp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DOCMPCLASSID_CDOCFILE)
	{
		pNew = new CDocFile();
	}

	return pNew;
}

void CDocCmp::DocCmp(int argc, TCHAR* argv[])
{
	if (argc < 3)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, "cmd error! XDocCmp file1_path file2_path");
		return;
	}

	//启动OfficeWord
	if (m_pDocXReadInterface == NULL)
	{
		return;
	}

	m_pDocXReadInterface->SetProgressInterface(m_pProgress);

	//打开两个文件
	if (! m_pDocXReadInterface->ReadDocFile(this, argv[1], argv[2]))
	{
		return;
	}

	//文件比较
	DocCmp();
}

void CDocCmp::DocCmp()
{
	CDocFile *pFile1 = (CDocFile*)GetAtIndex(0);
	CDocFile *pFile2 = (CDocFile*)GetAtIndex(1);

//2024-3-27  lijunqing 暂时不做基础性分类的比对
	pFile1->Group(m_pDocCmpConfig);
	pFile2->Group(m_pDocCmpConfig);

	pFile2->Cmp(pFile1);
}

void CDocCmp::DocCmpXml(const CString &strFile1, const CString &strFile2, const CString &strCmpFile)
{
	CDocFile *pFile1 = new CDocFile();
	pFile1->OpenDocDataFile(strFile1);
	AddNewChild(pFile1);

	CDocFile *pFile2 = new CDocFile();
	pFile2->OpenDocDataFile(strFile2);
	AddNewChild(pFile2);

	//2024-3-27  lijunqing 暂时不做基础性分类的比对
	pFile1->Group(m_pDocCmpConfig);
	pFile2->Group(m_pDocCmpConfig);

	pFile2->Cmp(pFile1);
	pFile1->InitTableTxtCmpID();
	pFile2->InitTableTxtCmpID();

	CDocCmpXmlRWKeys::SetSaveCmpMode(1);
	SaveDocCmpFile(strCmpFile);
	CDocCmpXmlRWKeys::SetSaveCmpMode(0);
}

void CDocCmp::SaveDocCmpFile(const CString &strFile)
{
	CString strPostfix;
	strPostfix = ParseFilePostfix(strFile);
	strPostfix.MakeLower();

	if (strPostfix == _T("xml"))
	{
		SaveXmlFile(strFile, CDocCmpXmlRWKeys::g_pXmlKeys, _PUGI_XML_TYPE_);
	}
	else
	{
		SaveXmlFile(strFile, CDocCmpXmlRWKeys::g_pXmlKeys, _JSON_TYPE_);
	}
}


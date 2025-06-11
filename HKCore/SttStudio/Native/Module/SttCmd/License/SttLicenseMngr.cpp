//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权

//SttLicenseMngr.cpp  CSttLicenseMngr


#include "stdafx.h"
#include "SttLicenseMngr.h"
#include "../../../../Module/API/GlobalConfigApi.h"

CSttLicenseMngr *g_pSttLicenseMngr = 0;

void stt_license_init_LicenseMngr()
{
    if (g_pSttLicenseMngr == 0)
    {
        g_pSttLicenseMngr = new CSttLicenseMngr();
        g_pSttLicenseMngr->OpenLicenseMngrFile();
        g_pSttLicenseMngr->GetLicenseFiles();
    }
}

void stt_license_free_LicenseMngr()
{
    if (g_pSttLicenseMngr != 0)
    {
        delete g_pSttLicenseMngr;
        g_pSttLicenseMngr = 0;
    }
}

CString stt_get_license_files_path()
{
    CString strPath;
    strPath = _P_GetConfigPath();
    strPath += _T("License/");

    return strPath;
}

CSttLicenseMngr::CSttLicenseMngr()
{
	//初始化属性
    m_bModifyFlag = false;

	//初始化成员变量
    m_pLicenseFiles = 0;
}

CSttLicenseMngr::~CSttLicenseMngr()
{
    if (m_pLicenseFiles != 0)
    {
        delete m_pLicenseFiles;
        m_pLicenseFiles = 0;
    }
}

long CSttLicenseMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttLicenseMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttLicenseMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttLicenseMngr::InitAfterRead()
{
}

BOOL CSttLicenseMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttLicenseMngr *p = (CSttLicenseMngr*)pObj;

	return TRUE;
}

BOOL CSttLicenseMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttLicenseMngr *p = (CSttLicenseMngr*)pDest;

	return TRUE;
}

CBaseObject* CSttLicenseMngr::Clone()
{
	CSttLicenseMngr *p = new CSttLicenseMngr();
	Copy(p);
	return p;
}

CExBaseObject* CSttLicenseMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttLicenseKey)
	{
		pNew = new CSttLicense();
	}

	return pNew;
}

CExBaseObject* CSttLicenseMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTCMDCLASSID_CSTTLICENSE)
	{
		pNew = new CSttLicense();
	}

	return pNew;
}


CString CSttLicenseMngr::GetLicenseMngrFile()
{
    CString strFile;
    strFile = _P_GetConfigPath();
    strFile += _T("SttLicenseMngr.sttlcs");

    return strFile;
}

//私有成员变量访问方法

CXFileMngr* CSttLicenseMngr::GetLicenseFiles()
{
    if (m_pLicenseFiles != 0)
    {
        return m_pLicenseFiles;
    }

    m_pLicenseFiles = new CXFileMngr();
    CString strPath = stt_get_license_files_path();

    CXFileType *pType = m_pLicenseFiles->AddFileType(_T("LicenseFile"), _T("sttlc"), _T(""), _T(""));
    pType->AddNewPostfix(_T("sttlc"), _T("sttlc") );
    m_pLicenseFiles->SetLibraryPath(strPath, FALSE);

    return m_pLicenseFiles;
}

void CSttLicenseMngr::OpenLicenseMngrFile()
{
    CString strFile;
    strFile = GetLicenseMngrFile();

    OpenXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void CSttLicenseMngr::SaveLicenseMngrFile()
{
    m_bModifyFlag = false;
    CString strFile;
    strFile = GetLicenseMngrFile();

    SaveXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

CSttLicense* CSttLicenseMngr::AddLicenseFile(const CString &strFile)
{
    CSttLicense *pLicense = new CSttLicense();
    BOOL b = pLicense->OpenXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

    if (!b)
    {
        delete pLicense;
        return false;
    }

    bool bIsNew = true;
    AddLicense(pLicense, bIsNew);

    if (bIsNew)
    {
        return pLicense;
    }
    else
    {
        return 0;
    }
}

bool CSttLicenseMngr::AddLicense(CSttLicense *pLicense, bool &bIsNew)
{
    CSttLicense *pFind = (CSttLicense*)FindByID(pLicense->m_strID);

    if (pFind == NULL)
    {
        bIsNew = true;
        m_bModifyFlag = true;
        AddNewChild(pLicense);
        return true;
    }

    bIsNew = false;

    if (pFind->AddLicense(pLicense))
    {
        m_bModifyFlag = true;
        delete pLicense;
        return true;
    }

    delete pLicense;

    return false;
}

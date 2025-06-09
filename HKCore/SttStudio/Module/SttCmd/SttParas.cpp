//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttParas.cpp  CSttParas


#include "stdafx.h"
#include "SttParas.h"

#ifndef STT_CMD_PARAS_NOT_USE_TEST  //2022-10-24  lijunqing
#include "SttRptMapDatas.h"
#include "SttChMaps.h"
#endif

#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
#include "GuideBook/SttItems.h"
#endif


#ifndef CLIENT_TEST_ENGINE_IN_LOCAL
#include "../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"
#endif

#include "GuideBook/SttContents.h"


#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttParas::CSttParas()
{
	//初始化属性
#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
    m_pGuideBook = NULL;
	m_pItems = NULL;
#endif

	//初始化成员变量
	m_strID.Empty();
	m_strName.Empty();
	m_bAttachParas = FALSE;

	m_pszTextParas = NULL;
	m_nLenTextParas = 0;

}

CSttParas::~CSttParas()
{
	if (m_bAttachParas)
	{
		RemoveAll();
	}

	FreeTextParasBuf();
}

CBaseObject* CSttParas::Clone()
{
	CSttParas *p = new CSttParas();
	Copy(p);
	return p;
}

CBaseObject* CSttParas::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttParas *p = new CSttParas();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttParas::CanPaste(UINT nClassID)
{
	return FALSE;
}


long CSttParas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CSttParas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}


CExBaseObject* CSttParas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
     CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strCDvmDatasetKey)
    {
        return new CDvmDataset();
    }
	else if (strClassID == pXmlKeys->m_strCDvmDeviceKey)
	{//2023-1-28  lijunqing 增加枚举装置模型的功能
		return new CDvmDevice();
	}
	else if (strClassID == pXmlKeys->m_strCDvmDatasetGroupKey)
	{
		return new CDvmDatasetGroup();
	}
#ifndef STT_CMD_PARAS_NOT_USE_TEST  //2022-10-24  lijunqing
	else if (strClassID == pXmlKeys->m_strCSttReportsKey)
	{
		return new CSttReports();
	}
	else if (strClassID == pXmlKeys->m_strCSttRptMapDatasKey)
	{
		return new CSttRptMapDatas();
	}
#endif

#ifndef CLIENT_TEST_ENGINE_IN_LOCAL
	else if (strClassID == CCfgDataMngrXmlRWKeys::CIecCfgDatasMngrKey())
	{
		return new CIecCfgDatasMngr();
	}
#endif


	else if (strClassID == pXmlKeys->m_strContentsKey)
	{
        return new CSttContents();//20230324 zhoulei 稳控用到了
	}
#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
    else if (strClassID ==  CSttCmdDefineXmlRWKeys::CSttGuideBookKey())
    {
        m_pGuideBook = new CSttGuideBook();
        return m_pGuideBook;
    }
	else if (strClassID ==  CSttCmdDefineXmlRWKeys::CSttItemsKey())
	{
		m_pItems = new CSttItems();
		return m_pItems;
	}
	else if (strClassID == pXmlKeys->m_strCDataTypesKey)
	{
		return new CDataTypes();
	}
 #endif
	else
    {
        return CDataGroup::CreateNewChild(strClassID, bAddToTail, pXmlKeys);
    }
}

CExBaseObject* CSttParas::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
    if (nClassID == DVMCLASSID_CDVMDATASET)
    {
        return new CDvmDataset();
    }
	else if (nClassID == DVMCLASSID_CDVMDATASETGROUP)
	{
		return new CDvmDatasetGroup();
	}
#ifndef STT_CMD_PARAS_NOT_USE_TEST  //2022-10-24  lijunqing
	else if (nClassID == STTCMDCLASSID_REPORTS)
	{
		return new CSttReports();
	}
	else if (nClassID == STTCMDCLASSID_CSTTRPTMAPDATAS)
	{
		return new CSttRptMapDatas();
	}
	else if (nClassID == STTCMDCLASSID_CSTTCHMAPS)
	{
		return new CSttChMaps();
	}
#endif
	else if (nClassID == CFGCLASSID_CIECCFGDATASMNGR)
	{
#ifndef CLIENT_TEST_ENGINE_IN_LOCAL
		return new CIecCfgDatasMngr();
#else
		return NULL;
#endif
	}
#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
	else if (nClassID == STTGBXMLCLASSID_CSTTCONTENTS)
	{
		return new CSttContents();
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
	{
		return new CSttItems();
	}
	else if (nClassID == DTMCLASSID_CDATATYPES)
	{
		return new CDataTypes();
	}
#endif
    else
    {
        return CDataGroup::CreateNewChild(nClassID);
    }
}

void CSttParas::AttachParas(CDataGroup *pParas)
{
	m_bAttachParas = true;
	Append(pParas);
}
// 
// BOOL CSttParas::GetDataValueByID(const CString &strValueID, CString &strValue)
// {
// 	CDvmData *pData = (CDvmData *)FindByID(strValueID);
// 
// 	if (pData != NULL)
// 	{
// 		strValue = pData->m_strValue;
// 		return TRUE;
// 	}
// 
// 	return FALSE;
// }
// 
// BOOL CSttParas::GetDataValueByID(const CString &strValueID, long &nValue)
// {
// 	CString strValue;
// 
// 	BOOL bRet = GetDataValueByID(strValueID, strValue);
// 	nValue = CString_To_long(strValue);
// 
// 	return bRet;
// }

CDvmData* CSttParas::AddNewData(const CString &strID, const CString &strValue, BOOL bUseFind)
{//2022-8-10  lijunqing
    CString strDataType = _T("string");

	if (bUseFind)
	{
		CDvmData *pFind = (CDvmData*)FindByID(strID);

		if (pFind == NULL)
		{
			return CDataGroup::AddNewData(strID, strID, strDataType, strValue);
		}
		else
		{
			pFind->m_strValue = strValue;
			return pFind;
		}
	}
	else
	{
		return CDataGroup::AddNewData(strID, strID, strDataType, strValue);
	}
}

CDvmData* CSttParas::AddNewData3(const CString &strID, const CString &strDataType, const CString &strValue)
{
    return CDataGroup::AddNewData(strID, strID, strDataType, strValue);
}

CDvmData* CSttParas::AddNewData(const CString &strID, long nValue, BOOL bUseFind)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);

	return AddNewData(strID, strValue, bUseFind);
}

CDvmData* CSttParas::AddNewData(const CString &strName,const CString &strID, long nValue)
{
	CString strDataType = _T("");
	CString strValue;
	strValue.Format(_T("%d"), nValue);

	return CDataGroup::AddNewData(strName, strID, strDataType, strValue);
}

CDvmData* CSttParas::AddNewData(const CString &strName,const CString &strID, __int64 n64Value)
{
	CString strDataType = _T("");
	CString strValue;
	strValue.Format(_T("%lld"), n64Value);

	return CDataGroup::AddNewData(strName, strID, strDataType, strValue);
}

CDvmData* CSttParas::SetDataAttr(const CString &strID, const CString &strValue)
{
	CDvmData *pData = (CDvmData *)FindByID(strID);

	if (pData != NULL)
	{
		pData->m_strValue = strValue;
	}
	else
	{
		pData = AddNewData(strID,strValue);
	}

	return pData;
}

CDvmData* CSttParas::SetDataAttr(const CString &strID, long nValue)
{
	CDvmData *pData = (CDvmData *)FindByID(strID);

	if (pData != NULL)
	{
		CString strValue;
		strValue.Format(_T("%d"), nValue);
		pData->m_strValue = strValue;
	}
	else
	{
		pData = AddNewData(strID,nValue);
	}

	return pData;
}

BOOL  CSttParas::GetDataValue(const CString &strID, CString &strValue)
{
    CDvmData *pData = (CDvmData *)FindByID(strID);

    if (pData == NULL)
    {
        return FALSE;
    }

    strValue = pData->m_strValue;

    return TRUE;
}

BOOL  CSttParas::GetDataValue(const CString &strID, long &nValue)
{
    CDvmData *pData = (CDvmData *)FindByID(strID);

    if (pData == NULL)
    {
        return FALSE;
    }

    nValue = CString_To_long (pData->m_strValue);

    return TRUE;
}

BOOL  CSttParas::GetDataValue(const CString &strID, double &dValue)
{
    CDvmData *pData = (CDvmData *)FindByID(strID);

    if (pData == NULL)
    {
        return FALSE;
    }

    dValue = CString_To_double(pData->m_strValue);

    return TRUE;
}

BOOL CSttParas::GetDataValue(const CString &strID, __int64 &n64Value)
{
	CDvmData *pData = (CDvmData *)FindByID(strID);

	if (pData == NULL)
	{
		return FALSE;
	}

	n64Value = CString_To_i64 (pData->m_strValue);

	return TRUE;
}

CDvmDataset* CSttParas::GetDvmDataset(BOOL bCreateNew)
{
    CDvmDataset *pFind = (CDvmDataset*)FindByClassID(DVMCLASSID_CDVMDATASET);

    if (bCreateNew)
    {
        if (pFind == NULL)
        {
            pFind = new CDvmDataset();
            AddNewChild(pFind);
        }
    }

    return pFind;
}

CDvmDatasetGroup* CSttParas::GetDvmDatasetGroup(BOOL bCreateNew)
{
	CDvmDatasetGroup *pFind = (CDvmDatasetGroup*)FindByClassID(DVMCLASSID_CDVMDATASETGROUP);

	if (bCreateNew)
	{
		if (pFind == NULL)
		{
			pFind = new CDvmDatasetGroup();
			AddNewChild(pFind);
		}
	}

	return pFind;
}

//2023-1-28  lijunqing 增加枚举装置模型的功能
CDvmDevice* CSttParas::GetDvmDevice(BOOL bCreateNew)
{
	CDvmDevice *pFind = (CDvmDevice*)FindByClassID(DVMCLASSID_CDVMDEVICE);

	if (bCreateNew)
	{
		if (pFind == NULL)
		{
			pFind = new CDvmDevice();
			AddNewChild(pFind);
		}
	}

	return pFind;
}

#ifndef STT_CMD_PARAS_NOT_USE_TEST  //2022-10-24  lijunqing
CSttReports* CSttParas::GetSttReports(BOOL bCreateNew)
{
    CSttReports *pFind = (CSttReports*)FindByClassID(STTCMDCLASSID_REPORTS);

    if (bCreateNew)
    {
        if (pFind == NULL)
        {
            pFind = new CSttReports();
            AddNewChild(pFind);
        }
    }

    return pFind;
}

CSttRptMapDatas* CSttParas::GetSttRptMapDatas(BOOL bCreateNew)
{
    CSttRptMapDatas *pFind = (CSttRptMapDatas*)FindByClassID(STTCMDCLASSID_CSTTRPTMAPDATAS);

    if (bCreateNew)
    {
        if (pFind == NULL)
        {
            pFind = new CSttRptMapDatas();
            AddNewChild(pFind);
        }
    }

    return pFind;
}

void CSttParas::AddDatas(CStringArray &astrTypes, long nValue)
{
	long nCount = astrTypes.GetCount();
	CString strType;

	for (long k=0; k<nCount; k++)
	{
		strType = astrTypes.GetAt(k);
		AddNewData(strType, strType, nValue);
	}
}
#endif

void CSttParas::AddContents(const CString &strID, const CString &strText)
{
	CSttContents *pCSttContents = NULL;
	CExBaseObject *pObj = FindByID(strID);

	if (pObj != NULL)
	{
		if (pObj->GetClassID() == STTGBXMLCLASSID_CSTTCONTENTS)
		{
			pCSttContents = (CSttContents *)pObj;
		}
	}

	if (pCSttContents == NULL)
	{
		pCSttContents = new CSttContents();
		pCSttContents->m_strID = strID;
		AddNewChild(pCSttContents);
	}

	pCSttContents->m_strText = strText;
}

#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
CSttGuideBook* CSttParas::NewGuideBook()
{
    if (m_pGuideBook == NULL)
    {
        m_pGuideBook = new CSttGuideBook();
        AddNewChild(m_pGuideBook);
    }

    return m_pGuideBook;
}

void CSttParas::AttatchGuideBook(CSttGuideBook *pGuideBook)
{
    m_pGuideBook = pGuideBook;

	if (pGuideBook)
	{
		AddNewChild(m_pGuideBook);
	}
}

void CSttParas::AttatchItems(CSttItems *pItems)
{
	m_pItems = pItems;
	AddNewChild(m_pItems);
}


#endif

//2022-3-23  lijunqing 曾经考虑使用XFileMngr，但是底层服务使用起来太麻烦，就直接添加此函数
void CSttParas::SearchFiles(const CString &strPath, long nGetSubDirs, long nGetFiles, const CString &strFileType)
{
	Search(this, strPath, nGetSubDirs, nGetFiles, strFileType);
}

#include "../../../Module/XfileMngrBase/XFileFindEx.h"
long CSttParas::Search(CDataGroup *pParent, const CString &strPath, long nGetSubDirs, long nGetFiles, const CString &strFileType)
{
	//CFileFind finder;
	CXFileFindEx finder;
	CString strFinder = strPath + _T("*.*");
	BOOL bIsFinded = finder.FindFile(strFinder);

	while(bIsFinded)
	{
		bIsFinded = (BOOL)finder.FindNextFile();

		if( !finder.IsDots())
		{
			if(finder.IsDirectory())
			{
				if (nGetSubDirs)
				{
					CDataGroup *pFolder = new CDataGroup();
					pFolder->m_strName = finder.GetFileName();
					pFolder->m_strID = pFolder->m_strName;
					pParent->AddNewChild(pFolder);
					CString strTemp;
					strTemp += strPath + pFolder->m_strID;
					strTemp += "/";
					Search(pFolder, strTemp, nGetSubDirs, nGetFiles, strFileType);
				}
			}
			else
			{
				if (!nGetFiles) 
				{
					continue;
				}

				//获取后缀
				CString strFileWithExtension = finder.GetFileName();
				int npos = strFileWithExtension.ReverseFind('.'); 

				if(npos != -1)
				{
					npos++;

					if (strFileType.CompareNoCase(strFileWithExtension.Mid(npos)) == 0)
					{
						CDvmData *pFile = new CDvmData();
						pFile->m_strID = strFileWithExtension;
						pFile->m_strName = strFileWithExtension;
						pParent->AddNewChild(pFile);
					}
				}
			}
		}
	}

	finder.Close();
	return GetCount();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//CSttResults
CSttResults::CSttResults()
{

}

CSttResults::~CSttResults()
{

}


CBaseObject* CSttResults::Clone()
{
	CSttResults *p = new CSttResults();
	Copy(p);
	return p;
}

CBaseObject* CSttResults::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttResults *p = new CSttResults();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//CSttSearchResults
CSttSearchResults::CSttSearchResults()
{

}

CSttSearchResults::~CSttSearchResults()
{

}


CBaseObject* CSttSearchResults::Clone()
{
	CSttSearchResults *p = new CSttSearchResults();
	Copy(p);
	return p;
}

CBaseObject* CSttSearchResults::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttSearchResults *p = new CSttSearchResults();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

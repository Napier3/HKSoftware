#include "StdAfx.h"
#include "DevcieModel.h"
#include "../../../../Module/API/FileApi.h"
#include "../../XLanguageResourcePp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpDvmDevice::CPpDvmDevice()
{
	m_pDevice = new CDvmDevice();
	m_pDevices = new CDvmDevices();
	m_nDvmDeviceMode = PPTEMPLATE_DEVICEMODE_SINGLE;

	AddNewChild(m_pDevice);
	AddNewChild(m_pDevices);
}

CPpDvmDevice::~CPpDvmDevice()
{
	int i = 0;
}

BOOL CPpDvmDevice::OpenDeviceFile(const CString &strFile)
{
	m_nDvmDeviceMode = PPTEMPLATE_DEVICEMODE_NONE;
	m_pDevices->DeleteAll();
	m_pDevice->DeleteAll();

	if (!IsFileExist(strFile))
	{
		return FALSE;
	}

	if (m_pDevices->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys->CDvmDevicesKey(), CDataMngrXmlRWKeys::g_pXmlKeys))
	{
		m_nDvmDeviceMode = PPTEMPLATE_DEVICEMODE_MULTI;
		return TRUE;
	}

	if (m_pDevices->OpenXmlFile(strFile, CDeviceModelXmlKeys::g_pXmlKeys->CDvmDevicesKey(), CDataMngrXmlRWKeys::g_pXmlKeys))
	{
		m_nDvmDeviceMode = PPTEMPLATE_DEVICEMODE_MULTI;
		return TRUE;
	}

	if (m_pDevice->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys->CDvmDeviceKey(), CDataMngrXmlRWKeys::g_pXmlKeys))
	{
		m_nDvmDeviceMode = PPTEMPLATE_DEVICEMODE_SINGLE;
		return TRUE;
	}

	if (m_pDevice->OpenXmlFile(strFile, CDeviceModelXmlKeys::g_pXmlRWKeys->CDvmDeviceKey(), CDataMngrXmlRWKeys::g_pXmlKeys))
	{
		m_nDvmDeviceMode = PPTEMPLATE_DEVICEMODE_SINGLE;
		return TRUE;
	}
// 
// 
// 	if (!IsFileExist(strFile))
// 	{
// 		return FALSE;
// 	}
// 
// 	MSXML2::IXMLDOMDocumentPtr oDoc = NULL;
// 
// 	try
// 	{
// 		if ( !xml_OpenFile(oDoc, strFile) )
// 		{
// 			return FALSE;
// 		}
// 	}
// 	catch (...)
// 	{
// 		return FALSE;
// 	}
// 
// 
// 	MSXML2::IXMLDOMNodePtr oDocRoot = oDoc->GetdocumentElement();
// 	MSXML2::IXMLDOMNodePtr oRoot = NULL;
// 
// 	_bstr_t bstr = L"//";
// 	bstr += CDataMngrXmlRWKeys::g_pXmlKeys->CDvmDevicesKey();
// 	oRoot = oDocRoot->selectSingleNode(bstr);
// 
// 	if (oRoot != NULL)
// 	{
// 		m_nDvmDeviceMode = PPTEMPLATE_DEVICEMODE_MULTI;
// 		m_pDevices->XmlRead(oRoot, CDataMngrXmlRWKeys::g_pXmlKeys);
// 		return TRUE;
// 	}
// 
// 	bstr = L"//";
// 	bstr += CDeviceModelXmlKeys::g_pXmlKeys->CDvmDevicesKey();
// 	oRoot = oDocRoot->selectSingleNode(bstr);
// 
// 	if (oRoot != NULL)
// 	{
// 		m_nDvmDeviceMode = PPTEMPLATE_DEVICEMODE_MULTI;
// 		m_pDevices->XmlRead(oRoot, CDataMngrXmlRWKeys::g_pXmlKeys);
// 		return TRUE;
// 	}
// 
// 	bstr = L"//";
// 	bstr += CDeviceModelXmlKeys::g_pXmlRWKeys->CDvmDeviceKey();
// 	oRoot = oDocRoot->selectSingleNode(bstr);
// 
// 	if (oRoot != NULL)
// 	{
// 		m_nDvmDeviceMode = PPTEMPLATE_DEVICEMODE_SINGLE;
// 		m_pDevice->XmlRead(oRoot, CDataMngrXmlRWKeys::g_pXmlKeys);
// 		return TRUE;
// 	}
// 
// 	bstr = L"//";
// 	bstr += CDataMngrXmlRWKeys::g_pXmlKeys->CDvmDeviceKey();
// 	oRoot = oDocRoot->selectSingleNode(bstr);
// 
// 	if (oRoot != NULL)
// 	{
// 		m_nDvmDeviceMode = PPTEMPLATE_DEVICEMODE_SINGLE;
// 		m_pDevice->XmlRead(oRoot, CDataMngrXmlRWKeys::g_pXmlKeys);
// 		return TRUE;
// 	}
// 

    CLogPrint::LogFormatString(XLOGLEVEL_TRACE
              , g_sLangTxt_DevDaraTmpFile.GetString()/*_T("设备数据模型文件不存在：%s")*/, strFile.GetString());
	return FALSE;
}


void CPpDvmDevice::IinitProtocolTestDvmAttrs()
{
	if (m_nDvmDeviceMode == PPTEMPLATE_DEVICEMODE_SINGLE)
	{
		CDvmDataset *pDevceAttrs = m_pDevice->GetDeviceAttrs();

		pDevceAttrs->AddNewDataEx(g_sLangTxt_CurrentActSet,       ATTRID_ACTSG, _T("INT"), _T("0"));//_T("当前活动定值区")
		pDevceAttrs->AddNewDataEx(g_sLangTxt_SettingTotalNo,           ATTRID_NUMOFSG, _T("INT"), _T("0"));//_T("定值区总数")
		pDevceAttrs->AddNewDataEx(g_sLangTxt_CommandTotalTime,           ATTRID_TMTOTAL, _T("INT"), _T("0"));//_T("命令总时间")
		pDevceAttrs->AddNewDataEx(g_sLangTxt_CommandExecuTime,         ATTRID_TMEXEC, _T("INT"), _T("0"));//_T("命令执行时间")
		pDevceAttrs->AddNewDataEx(g_sLangTxt_CommandChoseTime,         ATTRID_TMSEL, _T("INT"), _T("0"));//_T("命令选择时间")
		pDevceAttrs->AddNewDataEx(g_sLangTxt_CommandExecuMess,         ATTRID_InfoEXEC, _T("BIT_STR"), _T("0"));//_T("命令执行信息")
		pDevceAttrs->AddNewDataEx(g_sLangTxt_CommandChoseMess,         ATTRID_InfoSEL, _T("BIT_STR"), _T("0"));//_T("命令选择信息")
		pDevceAttrs->AddNewDataEx(g_sLangTxt_WrongMess,             ATTRID_ERRINFO, _T("INT"), _T("0"));//_T("错误信息")
		pDevceAttrs->AddNewDataEx(g_sLangTxt_RecordPath,             ATTRID_RECORD_PATH, _T("INT"), _T("0"));//_T("录波路径")
		pDevceAttrs->AddNewDataEx(g_sLangTxt_EnaChangeTime,     ATTRID_TimeGapEnaWrite, _T("INT"), _T("0"));//_T("压板修改间隔时间")
		pDevceAttrs->AddNewDataEx(g_sLangTxt_EnaChoseTime, ATTRID_TimeGapSelExec, _T("INT"), _T("0"));//_T("压板选择执行间隔时间")
		pDevceAttrs->AddNewDataEx(g_sLangTxt_MonitErrorTime,         ATTRID_LogMmsMsg, _T("INT"), _T("0"));//_T("监视错误信息")
		pDevceAttrs->AddNewDataEx(g_sLangTxt_BeforEnaRead,         ATTRID_EnaReadBeforeWrite, _T("INT"), _T("0"));//_T("投退压板前读状态")
		pDevceAttrs->AddNewDataEx(g_sLangTxt_BeforEnaReadTime,   ATTRID_TEnaReadBeforeWrite, _T("INT"), _T("0"));//_T("投退压板前读状态后延时")

		pDevceAttrs->AddNewDataEx(g_sLangTxt_WritDataMess,         ATTRID_InfoWriteData, _T("BIT_STR"), _T("0"));//_T("写数据信息")
		pDevceAttrs->AddNewDataEx(g_sLangTxt_SetEdtTime,         ATTRID_tmSetSE, _T("INT"), _T("0"));//_T("设置编辑区时间")
		pDevceAttrs->AddNewDataEx(g_sLangTxt_SetActTime,         ATTRID_tmSetSG, _T("INT"), _T("0"));//_T("设置活动区时间")
		pDevceAttrs->AddNewDataEx(g_sLangTxt_SetEdtMess,         ATTRID_InfoSetSE, _T("BIT_STR"), _T("0"));//_T("设置编辑区信息")
		pDevceAttrs->AddNewDataEx(g_sLangTxt_SetActMess,         ATTRID_InfoSetSG, _T("BIT_STR"), _T("0"));//_T("设置活动区信息")

		pDevceAttrs->AddNewDataEx(g_sLangTxt_TestConnSta,         ATTRID_TestLinkState, _T("INT"), _T("0"));//_T("测试连接状态")
	}
}


CExBaseList* CPpDvmDevice::GetDeviceModel()
{
	if (m_nDvmDeviceMode == PPTEMPLATE_DEVICEMODE_MULTI)
	{
		return m_pDevices;
	}

	if (m_nDvmDeviceMode == PPTEMPLATE_DEVICEMODE_SINGLE)
	{
		return m_pDevice;
	}

	return NULL;
}

BOOL CPpDvmDevice::GetDeviceAttribute(const CString &strAttrTag, CString &strAttrValue)
{
	if (m_nDvmDeviceMode == PPTEMPLATE_DEVICEMODE_MULTI)
	{
		return FALSE;
	}

	if (m_nDvmDeviceMode == PPTEMPLATE_DEVICEMODE_SINGLE)
	{
		return m_pDevice->GetDeviceAttribute(strAttrTag, strAttrValue);
	}

	return FALSE;
}

BOOL CPpDvmDevice::SetDeviceAttribute(const CString &strAttrTag, const CString &strAttrValue)
{
	if (m_nDvmDeviceMode == PPTEMPLATE_DEVICEMODE_MULTI)
	{
		return FALSE;
	}

	if (m_nDvmDeviceMode == PPTEMPLATE_DEVICEMODE_SINGLE)
	{
		return m_pDevice->SetDeviceAttribute(strAttrTag, strAttrValue);
	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
CDevcieModel::CDevcieModel(void)
{
	m_pDeviceCmmConfig = NULL;
	m_pPpDevice = NULL;

	m_strName = "DevcieModel";
	m_strID = m_strName;

}

CDevcieModel::~CDevcieModel(void)
{
}


void CDevcieModel::Init()
{

}


void CDevcieModel::InitAfterRead()
{
	
}

long CDevcieModel::XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);


	return 0;
}


long CDevcieModel::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	return 0;

}

BOOL CDevcieModel::IsEqualOwn(CBaseObject* pObj)
{
	return 0;
}

BOOL CDevcieModel::CopyOwn(CBaseObject* pDesObj)
{

	return TRUE;
}

CExBaseObject* CDevcieModel::Clone()
{
	CDevcieModel *pDevice= new CDevcieModel;

	if (Copy(pDevice))
	{
		return pDevice;
	}

	return NULL;
}


CExBaseObject* CDevcieModel::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	if(nClassID == DMCLASSID_DEVICECMMCONFIG)
	{
		m_pDeviceCmmConfig = new CDeviceCmmConfig();
		return m_pDeviceCmmConfig;
	}
	else if (nClassID == DVMCLASSID_CDVMDEVICE)
	{
		m_pPpDevice=new CPpDvmDevice();
		return m_pPpDevice;
	}

	return NULL;
}

CExBaseObject* CDevcieModel::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID==CDeviceModelXmlKeys::g_pXmlRWKeys->m_strCmmConfigKey)
	{
		m_pDeviceCmmConfig = new CDeviceCmmConfig();
		return m_pDeviceCmmConfig;
	}
	else if (strClassID==CDeviceModelXmlKeys::g_pXmlRWKeys->m_strDeviceKey)
	{
		m_pPpDevice=new CPpDvmDevice();
		return m_pPpDevice;
	}

	return NULL;
}

CString CDevcieModel::GetDeviceCmmCfgFile()
{
	return pp_GetDeviceCmmCfgFile(m_strDeviceModelFile);
}

BOOL CDevcieModel::OpenFile(const CString &strFile)
{
	m_strDeviceModelFile = strFile;
	GetDevice();
	GetDeviceCmmConfig();

	//m_pDevice->DeleteAll();
	m_pDeviceCmmConfig->DeleteAll();

	BOOL b1 = m_pPpDevice->OpenDeviceFile(m_strDeviceModelFile);
	m_pPpDevice->IinitProtocolTestDvmAttrs();

	//BOOL b1 = m_pDevice->OpenXmlFile(m_strDeviceModelFile, CDeviceModelXmlKeys::g_pXmlRWKeys->CDvmDeviceKey(), CDeviceModelXmlKeys::g_pXmlRWKeys);
	
	CString strCmmCfgFile = GetDeviceCmmCfgFile();
	BOOL b2 = m_pDeviceCmmConfig->OpenXmlFile(strCmmCfgFile, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strCmmConfigKey, CDeviceModelXmlKeys::g_pXmlRWKeys);

	if (!b1)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG
                  , g_sLangTxt_DevDaraTmpFile.GetString()/*_T("设备数据模型文件不存在：%s")*/
                  , strFile.GetString());
	}

    if (!b2)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG
                 , g_sLangTxt_CommunSetFile.GetString()/*_T("通讯配置文件不存在：%s")*/
                 , strCmmCfgFile.GetString());
	}

	return b1 && b2;
}

// 
// BOOL CDevcieModel::OpenXmlFile(const CString &strFile)
// {
// 	m_strDeviceModelFile = strFile;
// 
// 	//删除原来的数据
// 	DeleteAll();
// 	m_pDeviceCmmConfig = NULL;
// 	m_pDevice = NULL;
// 
// 	//读取文件数据
// 	MSXML2::IXMLDOMDocumentPtr oDoc = NULL;
// 
// 	if ( !xml_OpenFile(oDoc, strFile) )
// 	{
// 		return FALSE;
// 	}
// 
// 	MSXML2::IXMLDOMNodePtr oDocRoot = oDoc->GetdocumentElement();
// 	_bstr_t bstr = L"//";
// 	bstr += CDeviceModelXmlKeys::g_pXmlRWKeys->m_strDeviceModelKey;
// 
// 	MSXML2::IXMLDOMNodePtr oRoot = oDocRoot->selectSingleNode(bstr);
// 	ASSERT(oRoot != NULL);
// 
// 	if(oRoot == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	XmlRead(oRoot,CDeviceModelXmlKeys::g_pXmlRWKeys);
// 
// 	if(m_pDevice != NULL)
// 	{
// 		//m_pDevice->InitDmIndex();
// 	}
// 
// 	return TRUE;
// }

BOOL CDevcieModel::Save()
{
	return SaveFile(m_strDeviceModelFile);
}

BOOL CDevcieModel::SaveFile(const CString &strFile)
{
	if (strFile.GetLength() > 5)
	{
		m_strDeviceModelFile = strFile;
		return SaveXmlFile(m_strDeviceModelFile);
	}
	else
	{
#ifndef _PSX_IDE_QT_
        CString strFilePath = m_strDeviceModelFile;
		CString strFilter = _T("点表文件(*.xml)|*.xml||");
		CString strPostFix = _T("xml");

		if (PopupSaveAsFileDialog(AfxGetMainWnd(), strFilePath, strFilter, strPostFix) )
		{
			m_strDeviceModelFile = strFilePath;
			return SaveXmlFile(m_strDeviceModelFile);
		}
		else
		{
			return FALSE;
		}
#else
        return FALSE;
#endif
	}
}

BOOL CDevcieModel::SaveXmlFile(const CString &strFile)
{
	ClearFileReadOnlyAttr(strFile);
	CExBaseList *pDevice = m_pPpDevice->GetDeviceModel();

	if (pDevice == NULL)
	{
		return FALSE;
	}

	BOOL b1 = pDevice->SaveXmlFile(strFile, CDeviceModelXmlKeys::g_pXmlRWKeys);
	
	CString strCmmCfgFile = GetDeviceCmmCfgFile();
	ClearFileReadOnlyAttr(strCmmCfgFile);
	BOOL b2 = m_pDeviceCmmConfig->SaveXmlFile(strCmmCfgFile, CDeviceModelXmlKeys::g_pXmlRWKeys);

	return b1 && b2;
}

/************************************************************************/
/* 2011-01-13 添加 用于点表编辑                                                                     
*/
/************************************************************************/
void CDevcieModel::InsertNodeToTreeCtrl(CTreeCtrl* pTreeCtrl,HTREEITEM htiParent)
{
	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(g_sLangTxt_DevDataPoint/*_T("设备数据点表")*/,0,0,htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD_PTR)this);

	POS pos = this->GetHeadPosition();

	while(pos != NULL)
	{
		CExBaseObject* pObj = this->GetNext(pos);
		ASSERT(pObj != NULL);
		pObj->InsertTreeCtrl(pTreeCtrl,(HTREEITEM)m_dwItemData);
	}

#ifndef _PSX_IDE_QT_
    pTreeCtrl->Expand((HTREEITEM)m_dwItemData,TVE_EXPAND);
#endif
}

//2020-5-19  lijunqing
BOOL CDevcieModel::InitCmmConfig(CDataGroup *pGroup)
{
    if (m_pDeviceCmmConfig != NULL)
    {
        m_pDeviceCmmConfig->InitCmmConfig(pGroup);
    }

	return TRUE;
}


//XrioReadTool.cpp   CXrioReadTool

#include "stdafx.h"
#include "XrioReadTool.h"
#include "..\XrioCustomBlock.h"
#include "..\XrioCustomParameter.h"
#include "..\XrioObjectCfg.h"


//////////////////////////////////////////////////////////////////////////
//CXrioTplMapObj
CXrioTplMapObj::CXrioTplMapObj()
{

}

CXrioTplMapObj::CXrioTplMapObj(CXrioCustomParameter *pXrioParas, CDvmData *pTplSetting)
{
	m_pTplSetting = pTplSetting;
	m_pXrioParas = pXrioParas;

	if (m_pXrioParas != NULL && m_pTplSetting != NULL)
	{
		m_pTplSetting->m_strValue = m_pXrioParas->m_strValue;
	}
}

CXrioTplMapObj::~CXrioTplMapObj()
{
	m_listMapXrioParas.RemoveAll();

}
//////////////////////////////////////////////////////////////////////////
//CXrioReadTool
CXrioReadTool::CXrioReadTool()
{
	m_strXrioFilePath = _T("");
	m_bHasOpenXrioFile = FALSE;
}

CXrioReadTool::~CXrioReadTool()
{
	m_listCustomParas.RemoveAll();
	//m_listParaDestObject.RemoveAll();
	//m_listTplSettingObject.RemoveAll();
	m_bIsSameXrio = FALSE;
}

BOOL CXrioReadTool::OpenXrioFile(const CString &strXrioFilePath)
{
	m_oXrio.DeleteAll();

	if (!m_oXrio.ReadXRIOFile(strXrioFilePath))
	{
		return FALSE;
	}

	m_strXrioFilePath = strXrioFilePath;
	m_bHasOpenXrioFile = TRUE;
	return TRUE;
}

BOOL CXrioReadTool::OpenXrioFile()
{
	if (!ptt_PopOpenPowerTestXrioFileDlg(m_strXrioFilePath))
	{
		return FALSE;
	}

	m_oXrio.DeleteAll();
	m_bHasOpenXrioFile = TRUE;
	return m_oXrio.OpenXmlFile(m_strXrioFilePath, CXrioCfgMngrXmlRWKeys::XrioKey(), CXrioCfgMngrXmlRWKeys::g_pXmlKeys);
}

BOOL CXrioReadTool::Save_SettingMapsFile()
{
	if (!IsFileExist(m_strXrioFilePath))
	{
		return FALSE;
	}

	CString strMapxmlFilePath;
	strMapxmlFilePath = ChangeFilePostfix(m_strXrioFilePath,_T("mapxml"));
	m_oPowerTestSetMaps.SaveXmlFile(strMapxmlFilePath);
	return TRUE;
}

BOOL CXrioReadTool::OpenSetMapsFile()
{
	if (!IsFileExist(m_strXrioFilePath))
	{
		return FALSE;
	}

	m_oPowerTestSetMaps.DeleteAll();
	CString strSetMapsPath,strRefFilePath;
	strSetMapsPath = ChangeFilePostfix(m_strXrioFilePath,_T("mapxml"));
	strRefFilePath = ChangeFilePostfix(m_strXrioFilePath,_T("ref"));

	if (IsFileExist(strSetMapsPath))//如果"*.mapxml"文件存在，打开此文件
	{
		return m_oPowerTestSetMaps.OpenXmlFile(strSetMapsPath, CPowerTestSetMapsXmlRWKeys::g_pXmlKeys);
	}
	else if (IsFileExist(strRefFilePath))//如果"*.ref"文件存在，打开此文件
	{
		return m_oPTXrioRefParse.ReadFromRefFile(&m_oPowerTestSetMaps,strRefFilePath);
	}

	return FALSE;
}

BOOL CXrioReadTool::SaveXrioFile()
{
	if (!IsFileExist(m_strXrioFilePath))
	{
		return FALSE;
	}

	CString strTmp;
	strTmp = ChangeFilePostfix(m_strXrioFilePath,_T("txml"));
	CXrioCustom *pXrioCustom = m_oXrio.GetXrioCustom();

	if (pXrioCustom == NULL)
	{
		return FALSE;
	}

	return pXrioCustom->SaveXmlFile(strTmp, CXrioCfgMngrXmlRWKeys::g_pXmlKeys);
}

//添加Custom下的使能参数到m_listCustomParas链表
void CXrioReadTool::AddAllEnabledParastoListEx(CXrioCustom *pXrioCustom)
{
	if (m_bIsSameXrio == FALSE)
	{
		m_listCustomParas.RemoveAll();
	}

	POS pos = pXrioCustom->GetHeadPosition();
	CExBaseList* p = NULL;

	while(pos != NULL)
	{
		p = (CExBaseList*)pXrioCustom->GetNext(pos);

		if (p->GetClassID() == XRIOCLASSID_CUSTOMBLOCK && ((CXrioCustomBlock*)p)->m_strEnabled != _T("false"))
		{
			SetIsSameXrio(TRUE);
			AddAllEnabledParastoList((CXrioCustomBlock*)p);
		}
		else if (p->GetClassID() == XRIOCLASSID_CUSTOMPARAMETER && ((CXrioCustomParameter*)p)->m_strEnabled != _T("false"))
		{
			SpliceNameAndDecsription((CXrioCustomParameter*)p);

			if (((CXrioCustomParameter*)p)->m_strDataType == _T("Enumeration"))  
			{
				SetValueByText((CXrioCustomParameter*)p);
			}

			m_listCustomParas.AddNewChild((CExBaseObject*)p);
		}
	}
}

//添加Block下的使能参数到m_listCustomParas链表
void CXrioReadTool::AddAllEnabledParastoList(CXrioCustomBlock *pXrioCustomBlock)
{
	POS pos = pXrioCustomBlock->GetHeadPosition();
	CExBaseList* p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseList*)pXrioCustomBlock->GetNext(pos);

		if (p->GetClassID() == XRIOCLASSID_CUSTOMBLOCK  && ((CXrioCustomBlock*)p)->m_strEnabled != _T("false"))
		{
			AddAllEnabledParastoList((CXrioCustomBlock*)p);
		}
		else if (p->GetClassID() == XRIOCLASSID_CUSTOMPARAMETER && ((CXrioCustomParameter*)p)->m_strEnabled != _T("false"))
		{
			SpliceNameAndDecsription((CXrioCustomParameter*)p);

			if (((CXrioCustomParameter*)p)->m_strDataType == _T("Enumeration"))  
			{
				SetValueByText((CXrioCustomParameter*)p);
			}

			m_listCustomParas.AddNewChild((CExBaseObject*)p);
		}
	}
}

void CXrioReadTool::SetValueByText(CXrioCustomParameter *pXrioParameter)
{
	POS pos = pXrioParameter->GetHeadPosition();
	POS pos2 = NULL;
	CExBaseList* p = NULL;
	CXrioEnumValue* pXrioEnumValue = NULL;

	while (pos != NULL)
	{
		p = (CExBaseList*)pXrioParameter->GetNext(pos);
		if (p->GetClassID() == XRIOCLASSID_ENUMLIST)
		{
			pos2 = p->GetHeadPosition();

			while (pos2 != NULL)
			{
				pXrioEnumValue = (CXrioEnumValue*)p->GetNext(pos2);
				if (pXrioEnumValue->m_strEnumId == pXrioParameter->m_strValue)
				{
					pXrioParameter->m_strValue = pXrioEnumValue->m_strName;
				}
			}
		}
	}
}

void CXrioReadTool::SpliceNameAndDecsription(CXrioCustomParameter *pXrioParameter)
{
	if (pXrioParameter->m_strDescription == _T(""))
	{
		if (pXrioParameter->m_strName == _T(""))
		{
			pXrioParameter->m_strName = pXrioParameter->m_strID;
		}
	}
	else
	{
		if (pXrioParameter->m_strName == _T(""))
		{
			pXrioParameter->m_strName = pXrioParameter->m_strDescription;
		}
		else
			//pXrioParameter->m_strName.Format(_T("%s【%s】"), pXrioParameter->m_strName, pXrioParameter->m_strDescription);
			pXrioParameter->m_strName = pXrioParameter->m_strName + _T("【") + pXrioParameter->m_strDescription + _T("】");
	}
	
}

BOOL CXrioReadTool::TransXrioToDeviceModel(CCpus *pCpus)
{
	m_oPowerTestSetMaps.DeleteAll();
	CString strRefFilePath,strMapxmlFilePath;
	BOOL bHasMapxmlFile = FALSE;
	strRefFilePath = ChangeFilePostfix(m_strXrioFilePath,_T("ref"));
	strMapxmlFilePath = ChangeFilePostfix(m_strXrioFilePath,_T("mapxml"));

	if (IsFileExist(strMapxmlFilePath))
	{
		bHasMapxmlFile = TRUE;
		m_oPowerTestSetMaps.OpenXmlFile(strMapxmlFilePath, CPowerTestSetMapsXmlRWKeys::g_pXmlKeys);
	}
	else if (IsFileExist(strRefFilePath))
	{
		m_oPTXrioRefParse.ReadFromRefFile(&m_oPowerTestSetMaps,strRefFilePath);
	}
	else
		return FALSE;

	if (!TransXrioRefToDevModel(pCpus,bHasMapxmlFile))
	{
		return FALSE;
	}

	if (!bHasMapxmlFile)
	{
		m_oPowerTestSetMaps.SaveXmlFile(strMapxmlFilePath);
	}

	return TRUE;
}

BOOL CXrioReadTool::TransXrioToSysPara(CDataSet *pSysPara)
{
	ASSERT(pSysPara);
	CSysParaMap *pSysParaMap = NULL;
	CXrioCustomParameter *pParameter = NULL;
	CDataObj *pDataObj;
	POS pos_map = m_oPowerTestSetMaps.GetHeadPosition();
	CXrioCustom *pXrioCustom = m_oXrio.GetXrioCustom();

	if (pXrioCustom == NULL)
	{
		return FALSE;
	}

	while(pos_map)
	{
		pSysParaMap = (CSysParaMap *)m_oPowerTestSetMaps.GetNext(pos_map);

		if (pSysParaMap->GetClassID() != SETMAPMNGRCLASSID_CPARAMAP)
		{
			continue;
		}

		pParameter = (CXrioCustomParameter*)pXrioCustom->FindParaByFullPath(pSysParaMap->m_strMap);

		if (pParameter == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("参数(%s)在XRIO文件中未找到."),pSysParaMap->m_strMap);
			continue;
		}

		pDataObj = (CDataObj*)pSysPara->FindByID(pSysParaMap->m_strName);

		if (pDataObj == NULL)
		{
			pDataObj = new CDataObj;
			pSysPara->AddNewChild(pDataObj);
			pDataObj->m_strID = pDataObj->m_strName;
		}

		pDataObj->m_strName = pParameter->m_strName;
		pDataObj->m_strUnit = pParameter->m_strUnit;
		pDataObj->m_strDefaultValue = pSysParaMap->m_strMap;
		pParameter->GetParameterValue(pDataObj->m_strValue);
		pDataObj->m_dMinVal = CString_To_double(pParameter->m_strMinValue);
		pDataObj->m_dMaxVal = CString_To_double(pParameter->m_strMaxValue);
	}

	return TRUE;
}

BOOL CXrioReadTool::TransXrioRefToDevModel(CCpus *pCpus,BOOL bHasMapxmlFile)
{
	CSetMap *pSetMap = NULL;
	CXrioCustom *pXrioCustom = m_oXrio.GetXrioCustom();

	if (pXrioCustom == NULL)
	{
		return FALSE;
	}

	CXrioCustomBlock *pCustomBlock = (CXrioCustomBlock*)pXrioCustom->FindByID(m_oPowerTestSetMaps.m_strID);
	CXrioCustomParameter *pParameter = NULL;
	CDataObj *pDataObj;

	if ((pCustomBlock == NULL)&&(!bHasMapxmlFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("XRIO文件对应的ref文件的Custom节点ID(%s)不存在."),m_oPowerTestSetMaps.m_strID);
		return FALSE;
	}

	CDataSet *pFirstSetting = pCpus->GetDataSet_Setting();
	CDataSet oDatasetRef;

	pCpus->GetAllDatasByDatasetKey(&oDatasetRef,_T("dsSetting"));
	POS pos_map = m_oPowerTestSetMaps.GetHeadPosition();

	while(pos_map)
	{
		pSetMap = (CSetMap *)m_oPowerTestSetMaps.GetNext(pos_map);

		if (pSetMap->GetClassID() != SETMAPMNGRCLASSID_CSETMAP)
		{
			continue;
		}

		if (bHasMapxmlFile)
		{
			pParameter = (CXrioCustomParameter*)pXrioCustom->FindParaByFullPath(pSetMap->m_strMap);
		} 
		else
		{
			pParameter = (CXrioCustomParameter*)pCustomBlock->FindParaByName(pSetMap->m_strMap,pSetMap->m_strID);
		}

		if (pParameter == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("参数(%s)在XRIO文件中未找到."),pSetMap->m_strMap);
			continue;
		}

		pParameter->GetParameterFullPath(pSetMap->m_strMap);
		pDataObj = (CDataObj*)oDatasetRef.FindByID(pSetMap->m_strName);

		if (pDataObj == NULL)
		{
			pDataObj = new CDataObj;
			pFirstSetting->AddNewChild(pDataObj);
			pDataObj->m_strID = pSetMap->m_strName;
		}

		pDataObj->m_strName = pParameter->m_strName;
		pDataObj->m_strUnit = pParameter->m_strUnit;
		pDataObj->m_strDefaultValue = pSetMap->m_strMap;
		pParameter->GetParameterValue(pDataObj->m_strValue);
		pDataObj->m_dMinVal = CString_To_double(pParameter->m_strMinValue);
		pDataObj->m_dMaxVal = CString_To_double(pParameter->m_strMaxValue);
	}

	oDatasetRef.RemoveAll();
	return TRUE;
}

void CXrioReadTool::DvmSettingFilter(CDvmDevice *pDvmDevice, CXKeyDB *pXKeyDB)
{
	POS pos = pDvmDevice->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject*)pDvmDevice->GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDVMLOGICDEVICE)
		{
			DvmSettingFilter((CDvmLogicDevice*)p, pXKeyDB);
		}
		else if (p->GetClassID() == DVMCLASSID_CDVMDATASET)
		{
			DvmSettingFilter((CDvmDataset*)p, pXKeyDB);
		}
	}
}

void CXrioReadTool::DvmSettingFilter(CDvmLogicDevice *pDvmLogicDevice, CXKeyDB *pXKeyDB)
{
	POS pos = pDvmLogicDevice->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject*)pDvmLogicDevice->GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDVMDATASET)
		{
			DvmSettingFilter((CDvmDataset*)p, pXKeyDB);
		}
		else
		{
			continue;
		}
	}
}

void CXrioReadTool::DvmSettingFilter(CDvmDataset *pDvmDataset, CXKeyDB *pXKeyDB)
{
	POS pos = pDvmDataset->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject*)pDvmDataset->GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			DvmSettingFilter((CDvmData*)p, pXKeyDB);
		}
		else
		{
			continue;
		}
	}
}

void CXrioReadTool::DvmSettingFilter(CDvmData *pDvmData, CXKeyDB *pXKeyDB)
{
	ReplaceSetNameByMap(pDvmData);
	pXKeyDB->QueryKeys(pDvmData->m_strName, &m_listMatchSettingKeys);
	QueryByKeys(&m_listMatchSettingKeys/*, m_listParaDestObject, m_listTplSettingObject*/, pDvmData, pXKeyDB);
}

//将Tpl模板中的定值的名称，通过PowerTestSetMaps.xml中的set-map节点的map属性进行替换
void CXrioReadTool::ReplaceSetNameByMap(CDvmData *pDvmData)
{
	CSetMap *pSetMap = NULL;
	pSetMap = (CSetMap *)m_oPowerTestSetMaps.FindByID(pDvmData->m_strName);

	if (pSetMap != NULL)
	{
		pDvmData->m_strName = pSetMap->m_strMap;
	}
}

//传入一个Tpl定值名称的分词序列pKeysList，遍历所有Xrio Parameter，查找匹配的Parameter
long CXrioReadTool::QueryByKeys(CXKeyMatchRefList *pKeysList, /*CExBaseList &listParas, CExBaseList &listTplSettings,*/ CDvmData *pDvmData, CXKeyDB *pXKeyDB)
{
	POS pos = m_listCustomParas.GetHeadPosition();
	CXrioCustomParameter* p = NULL;
	long nRatio = 0;
	long nRatioMax = 0;
	BOOL bHasMapXrioPara = FALSE;

	while (pos != NULL)
	{
		p = (CXrioCustomParameter*)m_listCustomParas.GetNext(pos);

		//对Xrio Parameter的描述进行分词
		if (p->m_strDescription != _T(""))
		{
			pXKeyDB->QueryKeys(p->m_strDescription, &m_listMacthParaKeys);
		}
		else
		{
			pXKeyDB->QueryKeys(p->m_strName, &m_listMacthParaKeys);
		}

		if (m_listMacthParaKeys.Match(pKeysList, nRatio))
		{
			bHasMapXrioPara = TRUE;
			CXrioTplMapObj *pMapObj = NULL;
			pMapObj = (CXrioTplMapObj *)this->FindByID(pDvmData->m_strID);

			if (pMapObj == NULL)   //当前Setting还没有与之匹配的XrioParameter
			{
				pMapObj = new CXrioTplMapObj(p, pDvmData);   //默认第一个与之匹配的XrioParameter的匹配度最高
				nRatioMax = nRatio;
				AddNewChild(pMapObj);
				pMapObj->m_strID = pDvmData->m_strID;
				pMapObj->m_listMapXrioParas.AddNewChild(p);
			}
			
			else   
			{
				pMapObj->m_listMapXrioParas.AddNewChild(p);

				if (nRatio > nRatioMax)
				{
					nRatioMax = nRatio;
					pMapObj->m_pXrioParas = p;    //记录匹配度最高的XrioParameter
					pMapObj->m_listMapXrioParas.BringToHead(p);   //将匹配度最高的XrioParameter放置链表头
					pMapObj->m_pTplSetting->m_strValue = p->m_strValue;  //将XrioParameter参数的值赋给定值
				}
			}
		}
	}
 
	if (!bHasMapXrioPara)  //循环结束，当前Tpl定值没有与之匹配的XrioParameter
	{
		CXrioTplMapObj *pMapObj = new CXrioTplMapObj(NULL, pDvmData);
		AddNewChild(pMapObj);
		pMapObj->m_strID = pDvmData->m_strID;
	}

	return GetCount();
}

void CXrioReadTool::XrioParaAndSetMap(CXrioTplMapObj *pMapObj, CXrioCustomParameter *pXrioPara)
{
	pMapObj->m_pTplSetting->m_strValue = pXrioPara->m_strValue;
	pMapObj->m_pXrioParas = pXrioPara;
	pMapObj->m_listMapXrioParas.AddNewChild(pXrioPara);
}

CXrioTplMapObj* CXrioReadTool::FindMapObjByDvmData(CDvmData *pDvmData)
{
	POS pos = GetHeadPosition();
	CXrioTplMapObj *pMapObj = NULL;

	while (pos != NULL)
	{
		pMapObj = (CXrioTplMapObj *)GetNext(pos);

		if (pMapObj->m_pTplSetting == pDvmData)
		{
			return pMapObj;
		}
	}

	return NULL;
}

void CXrioReadTool::OnExportModelFile(CCpus *pCpus,CWnd *pParent)
{
	CString strFile;
	strFile = _P_GetLibraryPath();
	CString strFilter = _T("设备点表文件(*.xml)|*.xml||");

	if (!PopupSaveAsFileDialog(pParent, strFile, strFilter, _T("xml")))
	{
		return;
	}

	ASSERT(pCpus);
	pCpus->SaveModelFile(strFile);
}

BOOL ptt_PopOpenPowerTestXrioFileDlg(CString &strPath)
{
	return PopupOpenFileDialog(NULL, strPath, _T("xrio | *.xrio;|xrio (*.xrio)|*.xrio|"), _T("xrio"), _T("选择Xrio文件"));
}
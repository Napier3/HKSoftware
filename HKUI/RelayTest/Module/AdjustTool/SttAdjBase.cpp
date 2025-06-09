//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttAdjBase.cpp  CSttAdjBase


#include "stdafx.h"
#include "SttAdjBase.h"


#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttAdjBase::CSttAdjBase()
{
	//初始化属性
	m_pSttAdjRef = NULL;
	m_nStateCount = 20;
	m_nBinCount = 10;
	m_nBoutCount = 8;
	m_nSTModeSet = 0;
	m_nUartCount = 6;

	//初始化成员变量
  
}

CSttAdjBase::~CSttAdjBase()
{
}

void CSttAdjBase::AttatchAdjRef(CDataGroup *pSttAdjRef, BOOL bSetParent)
{
	m_pSttAdjRef  = pSttAdjRef;

	if (bSetParent)
	{
		m_pSttAdjRef->SetParent(this);
	}
}

void CSttAdjBase::DettachAdjRef(BOOL bDelete)
{
	if (bDelete)
	{
		if (m_pSttAdjRef != NULL)
		{
			delete m_pSttAdjRef;
		}
	}

	m_pSttAdjRef = NULL;
}

void CSttAdjBase::AddLongDataVal(const CString &strID, long &nValue)
{
	stt_AddLongDataVal(m_pSttAdjRef, strID, nValue);
}

BOOL CSttAdjBase::GetCountDataVal(const CString &strID, long &nValue)
{

	return stt_GetCountDataVal(m_pSttAdjRef,  strID,nValue );
	/*
	CDvmData *pData = (CDvmData*)m_pSttAdjRef->FindByID(strID);

	if (pData == NULL)
	{
		return FALSE;
	}

	nValue = CString_To_long(pData->m_strValue);

	return TRUE;
	*/
}

BOOL CSttAdjBase::SetCountDataVal(const CString &strID, long nValue)
{
	return stt_SetCountDataVal(m_pSttAdjRef,  strID,nValue );
	/*
	CDvmData *pData = (CDvmData*)m_pSttAdjRef->FindByID(strID);

	if (pData == NULL)
	{
		return FALSE;
	}

	pData->m_strValue.Format(_T("%d"), nValue);

	return TRUE;
	*/
}

void CSttAdjBase::IncreaseCountData(const CString &strID, long nValAdd)
{
	long nValue = 0;
	if (stt_GetCountDataVal(m_pSttAdjRef,  strID, nValue))
	{
		nValue += nValAdd;
		stt_SetCountDataVal(m_pSttAdjRef,  strID, nValue);
	}
	else
	{
		stt_AddLongDataVal(m_pSttAdjRef,  strID, nValue);
	}
	/*
	if (GetCountDataVal(strID, nValue))
	{
		nValue += nValAdd;
		SetCountDataVal(strID, nValue);
	}
	else
	{
		AddLongDataVal(strID, nValue);
	}
*/
}

void CSttAdjBase::DecreaseCountData(const CString &strID, long nValAdd)
{
	long nValue = 0;
	if (stt_GetCountDataVal(m_pSttAdjRef,  strID, nValue))
	{
		nValue -= nValAdd;
		stt_SetCountDataVal(m_pSttAdjRef,  strID, nValue);
	}
	else
	{
		stt_AddLongDataVal(m_pSttAdjRef,  strID, nValue);
	}
	/*
	if (GetCountDataVal(strID, nValue))
	{
		nValue += nValAdd;
		SetCountDataVal(strID, nValue);
	}
	else
	{
		AddLongDataVal(strID, nValue);
	}
	*/
}

long CSttAdjBase::GetGroupCount(const CString &strDataType)
{
	CExBaseList listGroup;
	long nCount = 0;
	m_pSttAdjRef->FindByDataType(strDataType, listGroup);
	nCount = listGroup.GetCount();
	listGroup.RemoveAll();

	return nCount;
}

long CSttAdjBase::GetGroupCount(CDataGroup *pDataGroup)
{
	return GetGroupCount(pDataGroup->m_strDataType);
}

long CSttAdjBase::GetGroupIndex(CDataGroup *pDataGroup)
{
	CExBaseList listGroup;
	long nIndex = -1;
	m_pSttAdjRef->FindByDataType(pDataGroup->m_strDataType, listGroup);
	nIndex = listGroup.FindIndex(pDataGroup);
	listGroup.RemoveAll();

	return nIndex;
}

CDataGroup* CSttAdjBase::DeleteGroup(CDataGroup *pDataGroup)
{
	CDataGroup *pNext = NULL;
	CExBaseList listGroup;
	long nIndex = -1;

	m_pSttAdjRef->FindByDataType(pDataGroup->m_strDataType, listGroup);
	nIndex = listGroup.FindIndex(pDataGroup);
	m_pSttAdjRef->Delete(pDataGroup);
	listGroup.Remove(pDataGroup);

	if (listGroup.GetCount() > 0)
	{
		pNext = (CDataGroup*)listGroup.GetAtIndex(nIndex);

		if (pNext == NULL)
		{
			pNext =  (CDataGroup*)listGroup.GetAtIndex(nIndex-1);
		}
	}

	listGroup.RemoveAll();

	return pNext;
}

//获取DvmData在链表中的索引；
long CSttAdjBase::GetDvmDataIndex(CDvmData *pData)
{
	long nIndex = -1;
	nIndex = m_pSttAdjRef->FindIndex(pData);
	return nIndex;
}

CDvmData* CSttAdjBase::DeleteDvmData(CDvmData *pDvmData)
{
	CDvmData *pNext = NULL;
	CExBaseList listGroup;
	long nIndex = -1;
	nIndex = m_pSttAdjRef->FindIndex(pDvmData);
	m_pSttAdjRef->Delete(pDvmData);
	if (m_pSttAdjRef->GetCount()  >  0)
	{
		pNext  = (CDvmData *)m_pSttAdjRef->GetAtIndex(nIndex);

		if (pNext == NULL)
		{
			pNext =   (CDvmData *)m_pSttAdjRef->GetAtIndex(nIndex  -  1);
		}
	}
	
	return pNext;

/*
	m_pSttAdjRef->FindByDataType(pDataGroup->m_strDataType, listGroup);
	nIndex = listGroup.FindIndex(pDataGroup);
	m_pSttAdjRef->Delete(pDataGroup);
	listGroup.Remove(pDataGroup);

	if (listGroup.GetCount() > 0)
	{
		pNext = (CDataGroup*)listGroup.GetAtIndex(nIndex);

		if (pNext == NULL)
		{
			pNext =  (CDataGroup*)listGroup.GetAtIndex(nIndex-1);
		}
	}

	listGroup.RemoveAll();
	

	return pNext;*/
}

//xxy
void CSttAdjBase::GenerateDBCommAttrs(CDvmData *pRecord,BOOL bModel)
{
	GetAttrs();

	pRecord->AddValue(STT_ADJ_ID_Model,m_strModel);
	//添加装置类型：1代表Device,0代表Module
	pRecord->AddValue(STT_ADJ_ID_ModuleType,GetModelType());

	if (!bModel)
	{
		pRecord->AddValue(STT_ADJ_ID_SN, m_strSN);
		pRecord->AddValue(STT_ADJ_ID_FACTORY, m_strFactory);
		pRecord->AddValue(STT_ADJ_ID_DATEFAC, m_strDateFac);
	}
}

/*******************************
<group name="" id="" data-type="" value="">
	<group name="" id="Adj_Model" data-type="Records" value="">
		<data name="" id="" data-type="Record" value="">
			<value name="" id="Model" value="xxx"/>
			<value name="" id="Type" value="1"/>
		</data>
		……
	</group>
</group>
*******************************/
CDataGroup *CSttAdjBase::GenerateDBCommAttrs(BOOL bModel)
{
	CString strTaleName = SttAdj_GetTabelName(bModel);

	CDataGroup *pDBGroup = new CDataGroup;
	CDataGroup *pRecords = pDBGroup->AddNewGroup(_T(""), strTaleName, CommDBData_ID_Records);
	CDvmData *pRecord = pRecords->AddNewData(_T(""),_T(""),_T(""),CommDBData_ID_Record);
	GenerateDBCommAttrs(pRecord,bModel);

	return pDBGroup;
}

CDataGroup *CSttAdjBase::AddNewDeviceModelByVersionViewCfg(CDataGroup *pVersionViewCfgGroup)
{
	CDataGroup *pDevice = new CDataGroup;
	CDataGroup *pDeviceAttr = pDevice->AddNewGroup(_T("装置属性"),"DeviceAttrs","DeviceAttrs");
	AddDeviceAttrsByVersionViewCfg(pVersionViewCfgGroup,pDeviceAttr);
	AddAllModuleAttrsByVersionViewCfg(pVersionViewCfgGroup,pDevice);
	return pDevice;
}

void CSttAdjBase::AddDeviceAttrsByVersionViewCfg(CDataGroup *pConfigFile,CDataGroup *pDeviceAttr)
{
	CDataGroup *pDeviceAttrsCfg = (CDataGroup*)pConfigFile->FindByID(_T("DeviceAttrs"));

	if (pDeviceAttrsCfg == NULL)
	{
		return;
	}

	CDataGroup* pModelDeviceGroup = m_pSttAdjRef->FindByDataType(STT_ADJ_DATA_TYPE_DeviceAttrs);

	if (pModelDeviceGroup == NULL)
	{
		return;
	}

	POS pos = pDeviceAttrsCfg->GetHeadPosition();
	CDvmData *pDeviceAttrCfg = NULL,*pCurrDeviceAttr = NULL;

	while(pos)
	{
		pDeviceAttrCfg = (CDvmData *)pDeviceAttrsCfg->GetNext(pos);
		pCurrDeviceAttr = (CDvmData *)pModelDeviceGroup->FindByID(pDeviceAttrCfg->m_strID);

		if (pCurrDeviceAttr == NULL)
		{
			continue;
		}
		
		pDeviceAttr->AddNewData(pDeviceAttrCfg->m_strName,pDeviceAttrCfg->m_strID,
			pDeviceAttrCfg->m_strDataType,pCurrDeviceAttr->m_strValue);
	}
}

void CSttAdjBase::AddAllModuleAttrsByVersionViewCfg(CDataGroup *pConfigFile,CDataGroup *pDevice)
{
	if (m_pSttAdjRef == NULL)
	{
		return;
	}

	CDataGroup *pModuleGroup_Cfg = (CDataGroup*)pConfigFile->FindByID(_T("ModuleAttrs"));

	if (pModuleGroup_Cfg == NULL)
	{
		return;
	}

	CExBaseObject *pCurrObj = NULL;
	CDataGroup *pCurrModuleAttrs = NULL,*pModuleGroup = NULL,*pNewModuleAttrs = NULL;
	CString strName, strID;
	long nIndex = 0;
	POS pos = m_pSttAdjRef->GetHeadPosition();

	while (pos)
	{
		pCurrObj = m_pSttAdjRef->GetNext(pos);

		if (pCurrObj->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		pModuleGroup = (CDataGroup*)pCurrObj;

		if (pModuleGroup->m_strDataType != _T("Module"))
		{
			continue;
		}
		
		pCurrModuleAttrs = (CDataGroup*)pModuleGroup->FindByID(_T("ModuleAttrs"));
		strName = _T("模块");
		strID = "Module";
		strName.AppendFormat("%ld", nIndex);
		strID.AppendFormat("%ld", nIndex);
		pModuleGroup = pDevice->AddNewGroup(strName, strID, "Module");
		pNewModuleAttrs = pModuleGroup->AddNewGroup(_T("模块属性"),_T("ModuleAttrs"),_T("ModuleAttrs"));
		GetModuleAttrDataByConfig(pModuleGroup_Cfg,pCurrModuleAttrs,pNewModuleAttrs);
		nIndex++;
	}
}

void CSttAdjBase::GetModuleAttrDataByConfig(CDataGroup *pModuleGroup_Cfg,CDataGroup *pCurrModuleAttrs,CDataGroup *pNewModuleAttrs)
{
	POS pos = pModuleGroup_Cfg->GetHeadPosition();
	CDvmData *pModuleAttrCfg = NULL,*pCurrModuleAttr = NULL;

	while(pos)
	{
		pModuleAttrCfg = (CDvmData *)pModuleGroup_Cfg->GetNext(pos);
		pCurrModuleAttr = (CDvmData *)pCurrModuleAttrs->FindByID(pModuleAttrCfg->m_strID);

		if (pCurrModuleAttr == NULL)
		{
			continue;
		}

		pNewModuleAttrs->AddNewData(pModuleAttrCfg->m_strName,pModuleAttrCfg->m_strID,
			pModuleAttrCfg->m_strDataType,pCurrModuleAttr->m_strValue);
	}
}

//////////////////////////////////////////////////////////////////////////
void stt_adj_init_cmb_hdgear_type(CComboBox *pComboBox)
{

	long nIndex = 0;
	nIndex = pComboBox->AddString("独立直流电流通道硬件档位");
	pComboBox->SetItemData(nIndex, 0);

	nIndex = pComboBox->AddString("独立直流电压通道硬件档位");
	pComboBox->SetItemData(nIndex, 1);

	nIndex = pComboBox->AddString("模块通道档位");
	pComboBox->SetItemData(nIndex, 2);

	pComboBox->SetCurSel(nIndex);
}

CString stt_adj_get_cur_hdgear_type(CComboBox *pComboBox)
{
	long nIndex = 0;
	nIndex = pComboBox->GetCurSel();

	if (nIndex == CB_ERR)
	{
		return STT_ADJ_HD_GEAR_ID_MODULE;
	}

	nIndex = pComboBox->GetItemData(nIndex);

	if (nIndex == 0)
	{
		return STT_ADJ_HD_GEAR_ID_IDC;
	}

	if (nIndex == 1)
	{
		return STT_ADJ_HD_GEAR_ID_UDC;
	}

	return STT_ADJ_HD_GEAR_ID_MODULE;
}


void stt_adj_init_cmb_channel(CComboBox *pComboBox)
{
	CString strID;
	long nIndex = 0;

	//暂时确定为6个通道，最大化，多少后续再完善
	for (long nCh=0; nCh<6; nCh++)
	{
		strID.Format(_T("通道%d"), nCh+1);
		nIndex = pComboBox->AddString(strID);
		pComboBox->SetItemData(nIndex, nCh);
	}

	nIndex = 6;
	nIndex = pComboBox->AddString("独立直流电流Idc");
	pComboBox->SetItemData(nIndex,6);

	nIndex = pComboBox->AddString("独立直流电压Udc");
	pComboBox->SetItemData(nIndex, 7);

	pComboBox->SetCurSel(0);
}

CString stt_adj_get_cur_channel(CComboBox *pComboBox)
{
	long nIndex = 0;
	nIndex = pComboBox->GetCurSel();

	if (nIndex == CB_ERR)
	{
		return STT_ADJ_ID_Ch0_Module;
	}

	nIndex = pComboBox->GetItemData(nIndex);

	if (nIndex == 6)
	{
		return STT_ADJ_ID_Ch_Idc;
	}

	if (nIndex == 7)
	{
		return STT_ADJ_ID_Ch_Udc;
	}

	CString strID;
	strID.Format(_T("%s%d"), STT_ADJ_ID_Ch_Module, nIndex);

	return strID;
}

void stt_adj_init_cmb_ch_wave(CComboBox *pComboBox, long nHarmCount)
{
	pComboBox->ResetContent();
	long nIndex = 0;
	nIndex = pComboBox->AddString("直流");
	pComboBox->SetItemData(nIndex, 0);

	nIndex = pComboBox->AddString("基波");
	pComboBox->SetItemData(nIndex, 1);
	CString strID;

	//暂时确定为6个通道，最大化，多少后续再完善
	for (long nHarm=2; nHarm<=nHarmCount; nHarm++)
	{
		strID.Format(_T("%d次谐波"), nHarm);
		nIndex = pComboBox->AddString(strID);
		pComboBox->SetItemData(nIndex, nHarm);
	}

	pComboBox->SetCurSel(0);
}

CString stt_adj_get_cur_ch_wave(CComboBox *pComboBox)
{
	long nIndex = 0;
	nIndex = pComboBox->GetCurSel();

	if (nIndex == CB_ERR)
	{
		return STT_ADJ_ID_Ch_Wave_Base;
	}

	nIndex = pComboBox->GetItemData(nIndex);

	if (nIndex == 0)
	{
		return STT_ADJ_ID_Ch_Wave_DC;
	}

	if (nIndex == 1)
	{
		return STT_ADJ_ID_Ch_Wave_Base;
	}

	CString strID;
	strID.Format(_T("%s%d"), STT_ADJ_ID_Ch_Wave_Harm, nIndex);

	return strID;
}

//////////////////////////////////////////////////////////////////////////

void stt_AddLongDataVal(CDataGroup *pParent, const CString &strID, long &nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);
	pParent->AddNewData(strID, strID, _T("long"), strValue);
}

BOOL stt_GetCountDataVal(CDataGroup *pParent, const CString &strID, long &nValue)
{
	if (pParent == NULL)
		return FALSE;
	CDvmData *pData = (CDvmData*)pParent->FindByID(strID);

	if (pData == NULL)
	{
		return FALSE;
	}

	nValue = CString_To_long(pData->m_strValue);

	return TRUE;
}

BOOL stt_SetCountDataVal(CDataGroup *pParent, const CString &strID, long nValue)
{
	CDvmData *pData = (CDvmData*)pParent->FindByID(strID);

	if (pData == NULL)
	{
		return FALSE;
	}

	pData->m_strValue.Format(_T("%d"), nValue);

	return TRUE;
}

void stt_IncreaseCountData(CDataGroup *pParent, const CString &strID, long nValAdd)
{
	long nValue = 0;

	if (pParent==NULL)
		return;
	if (stt_GetCountDataVal(pParent,strID, nValue))
	{
		nValue += nValAdd;
		stt_SetCountDataVal(pParent,strID, nValue);
	}
	else
	{
		stt_AddLongDataVal(pParent,strID, nValue);
	}
}

void stt_DecreaseCountData(CDataGroup *pParent, const CString &strID, long nValAdd)
{
	long nValue = 0;

	if (pParent==NULL)
		return;
	if (stt_GetCountDataVal(pParent,strID, nValue))
	{
		nValue += nValAdd;
		stt_SetCountDataVal(pParent,strID, nValue);
	}
	else
	{
		stt_AddLongDataVal(pParent,strID, nValue);
	}
}

CString SttAdj_GetTabelName(BOOL bModel)
{
	CString strTaleName;
	if (bModel)
	{
		strTaleName = STT_ADJ_ID_ADJ_MODEL;
	}
	else
	{
		strTaleName = STT_ADJ_ID_ADJ_DEVICE;
	}
	return strTaleName;
}
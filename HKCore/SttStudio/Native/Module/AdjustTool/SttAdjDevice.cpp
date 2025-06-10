//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttAdjDevice.cpp  CSttAdjDevice


#include "stdafx.h"
#include "SttAdjDevice.h"
#include "SttAdjModule.h"

#include "SttMesLocalDb.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif




CSttAdjDevice::CSttAdjDevice()
{
	//初始化属性

	//初始化成员变量
	m_bModifiedFlag = FALSE;
	m_pDataGroupOldRatio = NULL;
}

CSttAdjDevice::~CSttAdjDevice()
{
	if (m_pSttAdjRef != NULL)
	{
		delete m_pSttAdjRef;
		m_pSttAdjRef = NULL;
	}
}



void CSttAdjDevice::SetModifiedFlagOwn(BOOL bModified)
{
	m_bModifiedFlag = bModified;
}

BOOL CSttAdjDevice::GetModifiedFlagOwn()
{
	return m_bModifiedFlag;
}

void CSttAdjDevice::SaveBaseObject()
{
	SaveSttAdjFile();
	CBaseObject::SaveBaseObject();
}

BOOL CSttAdjDevice::OpenSttAdjFile(const CString &strFile)
{
	if (m_pSttAdjRef == NULL)
	{
		m_pSttAdjRef = new CDataGroup();
		m_pSttAdjRef->SetParent(this);
	}
	
	m_pSttAdjRef->DeleteAll();
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	BOOL bRet = m_pSttAdjRef->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

	TransModuleTypeFromLongToString();

	return bRet;
}

//2021-5-4  lijunqing  将模块类型由整数转换为字符串，兼容老版本校准系数文件
void CSttAdjDevice::TransModuleTypeFromLongToString()
{
	CExBaseList oList;
	m_pSttAdjRef->FindByDataType(STT_ADJ_DATA_TYPE_Module, oList);
	POS pos = oList.GetHeadPosition();
	CDataGroup *pModule = NULL;
	CSttAdjModule oAdjModule;

	while (pos != NULL)
	{
		pModule = (CDataGroup *)oList.GetNext(pos);
		oAdjModule.AttatchAdjRef(pModule);
		oAdjModule.TransModuleTypeFromLongToString();
	}

	oList.RemoveAll();
}

BOOL CSttAdjDevice::SaveSttAdjFile(const CString &strFile)
{
	if (m_pSttAdjRef == NULL)
	{
		return FALSE;
	}

	BOOL bRet = m_pSttAdjRef->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	return bRet;
}

BOOL CSttAdjDevice::SaveSttAdjFile()
{
	if (m_strID == STT_ADJ_ID_EmptyDevice)
	{
		m_strID = stt_get_adj_sys_para_file_path();
		m_strID.MakeLower();
	}

	return SaveSttAdjFile(m_strID);
}

CDataGroup* CSttAdjDevice::GetDeviceAttrs()
{
	if (m_pSttAdjRef == NULL)
	{
		return NULL;
	}

	return m_pSttAdjRef->FindByDataType(STT_ADJ_DATA_TYPE_DeviceAttrs);
}

CDataGroup* CSttAdjDevice::GetBoutTrunOnValueDef()
{
	return m_pSttAdjRef->FindByDataType(STT_ADJ_DATA_TYPE_BoutTrunOnValueDef);
}

//2022-3-18  lijunqing
void CSttAdjDevice::GetDeviceVersioninfors(CDataGroup &oDeviceInfors) 
{
	CDataGroup *p = GetDeviceAttrs();

	if (p != NULL)
	{
		oDeviceInfors.AddNewChild((CExBaseObject*)p->Clone());
	}

	CExBaseList listModules;
	GetAllModules(&listModules);
	POS pos = listModules.GetHeadPosition();
	CDataGroup *pModule = NULL;
	CSttAdjModule oModule;
	CDataGroup *pNewModule = NULL;

	while (pos != NULL)
	{
		pModule = (CDataGroup *)listModules.GetNext(pos);
		oModule.AttatchAdjRef(pModule);
		pNewModule = (CDataGroup*)pModule->CloneEx();
		oDeviceInfors.AddNewChild(pNewModule);
		oModule.GetModuleAttrs(pNewModule, TRUE);
	}

	listModules.RemoveAll();
}

CDataGroup* CSttAdjDevice::AddModule(const CString &strSelModuleClass)
{
	CDataGroup *pModule = CSttMesLocalDb::CreateSttModuleClass(strSelModuleClass);

	if (pModule == NULL)
	{
		return pModule;
	}

	IncreaseCountData(STT_ADJ_ID_ModuleCount, 1);
	m_pSttAdjRef->AddNewChild(pModule, TRUE);

	SetModifiedFlagOwn(TRUE);
	return pModule;
}

CDataGroup* CSttAdjDevice::ReplaceModule(CDataGroup *pOldModule, const CString &strSelModuleClass)
{
	CDataGroup *pModule = CSttMesLocalDb::CreateSttModuleClass(strSelModuleClass);

	if (pModule == NULL)
	{
		return NULL;
	}

	POS pos = m_pSttAdjRef->Find(pOldModule);
	ASSERT( pos != NULL );
	m_pSttAdjRef->SetAt(pos, pModule);
	SetModifiedFlagOwn(TRUE);

	return pModule;
}

long CSttAdjDevice::GetModuleCount()
{
	long nCount = GetGroupCount(STT_ADJ_DATA_TYPE_Module);
	SetCountDataVal(STT_ADJ_ID_ModuleCount, nCount);

	return nCount;
}

long CSttAdjDevice::GetModuleIndex(CDataGroup *pModule)
{
	return GetGroupIndex(pModule);
}

CDataGroup* CSttAdjDevice::DeleteModule(CDataGroup *pModule)
{
	DecreaseCountData(STT_ADJ_ID_ModuleCount);
	return DeleteGroup(pModule);
}

CDataGroup* CSttAdjDevice::GetModule(const CString &strModuleType, long nModuleIndex)
{
	CExBaseList listModule;
	GetAllModules(&listModule, strModuleType);
	CDataGroup *pModule = (CDataGroup*)listModule.GetAtIndex(nModuleIndex);
	listModule.RemoveAll();

	return pModule;
}

CDataGroup* CSttAdjDevice::GetModule2(const CString &strModuleType, long nModulePos)
{
	CExBaseList listModule;
	GetAllModules(&listModule, strModuleType);
	CSttAdjModule oModule;
	POS pos = listModule.GetHeadPosition();
	CDataGroup *p = NULL, *pFind = NULL;
	long nPos = 0;

	while (pos != NULL)
	{
		p = (CDataGroup *)listModule.GetNext(pos);
		oModule.AttatchAdjRef(p);
		
		if (oModule.GetModulePos(nPos))
		{
			if (nPos == nModulePos)
			{
				pFind = p;
				break;
			}
		}
	}

	listModule.RemoveAll();

	return pFind;
}

CString CSttAdjDevice::GetAdjFileName()
{
	CString strFileName;

	CDataGroup *pAttr = GetDeviceAttrs();
	CDvmData *pSN = NULL;
	CDvmData *pModel = NULL;

	if (pAttr != NULL)
	{
		pSN = (CDvmData*)pAttr->FindByID(STT_ADJ_ID_SN);
		pModel = (CDvmData*)pAttr->FindByID(STT_ADJ_ID_Model);
	}

	if (pModel != NULL)
	{
		strFileName = pModel->m_strValue;
	}

	if (pSN != NULL)
	{
		if (strFileName.GetLength() > 0)
		{
			strFileName += _T("_");
		}

		strFileName += pSN->m_strValue;
	}

	SYSTEMTIME oSysTime;
	::GetLocalTime(&oSysTime);
	CString strTime;
	strTime.Format(_T("%4d%2d%2d"), oSysTime.wYear, oSysTime.wMonth, oSysTime.wDay);

	strFileName += _T("_");
	strFileName += strTime;

	return strFileName;
}

void CSttAdjDevice::GetAttrs()
{
	CDataGroup* pAttrGroup = GetDeviceAttrs();

	if (pAttrGroup == NULL)
	{
		return;
	}

	pAttrGroup->GetDataValue(STT_ADJ_ID_Model, m_strModel);
	pAttrGroup->GetDataValue(STT_ADJ_ID_SN, m_strSN);
	pAttrGroup->GetDataValue(STT_ADJ_ID_FACTORY, m_strFactory);
	pAttrGroup->GetDataValue(STT_ADJ_ID_DATEFAC, m_strDateFac);

	pAttrGroup->GetDataValue(STT_ADJ_ID_StateCount, m_nStateCount);
	pAttrGroup->GetDataValue(STT_ADJ_ID_BinCount, m_nBinCount);
	pAttrGroup->GetDataValue(STT_ADJ_ID_BoutCount, m_nBoutCount);
	pAttrGroup->GetDataValue(STT_ADJ_ID_STModeSet, m_nSTModeSet);
	pAttrGroup->GetDataValue(STT_ADJ_ID_UartCount,m_nUartCount);
}

//如果装置SN与模块SN一致，则是集成整机，校准记录上传时不更新模块信息，也没有装置模块信息
BOOL CSttAdjDevice::IsIntegrationDevice()
{
	GetAttrs();

	BOOL bRet = FALSE;
	POS pos = m_pSttAdjRef->GetHeadPosition();
	CDataGroup *pModule = NULL;
	CSttAdjModule oAdjModule;
	CExBaseObject *p = NULL;

	while(pos != NULL)
	{
		p = m_pSttAdjRef->GetNext(pos);

		if (p->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		pModule = (CDataGroup *)p;
		if (pModule->m_strDataType != STT_ADJ_DATA_TYPE_Module)
		{
			continue;
		}

		oAdjModule.AttatchAdjRef(pModule);
		oAdjModule.GetAttrs();

		if (m_strSN == oAdjModule.m_strSN)
		{
			bRet = TRUE;
		}
		break;
	}

	return bRet;
}

void   CSttAdjDevice::ImportOldRatio(const CString &strFile)
{

	AddOldRatio(strFile);
	CDataGroup *pDataGroup = NULL;
	pDataGroup = m_pDataGroupOldRatio->FindByDataType(STT_ADJ_DATA_TYPE_Module);


	CString strName,  strID;
	this->GetNewModuleNameID(strName,  strID);
	pDataGroup->m_strName = strName;
	pDataGroup->m_strID = strID;

	m_pSttAdjRef->AddNewChild(pDataGroup);
	stt_IncreaseCountData(m_pSttAdjRef, STT_ADJ_ID_ModuleCount);
	int adf = 0;
}

void  CSttAdjDevice::GetNewModuleNameID( CString &strName,  CString &strID)
{
	CDvmData *pDvmData = (CDvmData *)m_pSttAdjRef->FindByID(STT_ADJ_ID_ModuleCount);
	long nCount  = CString_To_long(pDvmData->m_strValue);
	strName.Format(_T("模块%d"), nCount + 1);
	strID.Format(_T("Module%d"), nCount);
}


void  CSttAdjDevice::AddOldRatio(const CString &strFile)
{
	if (m_pDataGroupOldRatio == NULL)
	{
		m_pDataGroupOldRatio = new CDataGroup();
		m_pDataGroupOldRatio->SetParent(this);
	}

	m_pDataGroupOldRatio->DeleteAll();
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	BOOL bRet = m_pDataGroupOldRatio->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

BOOL CSttAdjDevice::IsSttAdjModuleObj(CExBaseObject *pObj)
{
	if (pObj->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return FALSE;
	}

	CDataGroup *pModule1 = (CDataGroup *)pObj;

	if (pModule1->m_strDataType != STT_ADJ_DATA_TYPE_Module)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttAdjDevice::SortModules()
{
	if (m_pSttAdjRef == NULL)
	{
		return FALSE;
	}

	CSttAdjModule oAdjModule;
	POS pos1 = m_pSttAdjRef->GetHeadPosition();
	POS pos2 = pos1;
	long nCurPos = 0,nNextPos = -1;

	CExBaseObject *p1 = NULL, *p2 = NULL;

	while (pos1 != NULL)
	{
		p1 = (CExBaseObject*)m_pSttAdjRef->GetAt(pos1);

		if (IsSttAdjModuleObj(p1))//从第一个开始,查找所有模块对象
		{
			oAdjModule.AttatchAdjRef((CDataGroup*)p1);

			if (oAdjModule.GetModulePos(nCurPos))//理论上所有模块都应该有位置属性，如果无位置属性，则将该模块忽略，并报错
			{
				pos2 = pos1;
				m_pSttAdjRef->GetNext(pos2);//从当前模块往后遍历

				while (pos2 != NULL)
				{
					p2  = (CExBaseObject*)m_pSttAdjRef->GetAt(pos2);
					oAdjModule.AttatchAdjRef((CDataGroup*)p2);

					if (IsSttAdjModuleObj(p2)&&(oAdjModule.GetModulePos(nNextPos)))//遇到模块对象后，获取其位置
					{
						if (nCurPos>nNextPos)//如果nCurPos位置比nNextPos大，则两者交换链表中数据对象位置
						{
							m_pSttAdjRef->SetAt(pos1, p2);
							m_pSttAdjRef->SetAt(pos2, p1);
							p1 = p2;
							nCurPos = nNextPos;
						}
					}

					m_pSttAdjRef->GetNext(pos2);//往后移动一个，保证当前链表中的Module位置为最小的
				}
			}
			else
			{
                CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取当前模块位置失败(name=%s;id=%s)."),p1->m_strName.GetString(),p1->m_strID.GetString());
			}
		}

		m_pSttAdjRef->GetNext(pos1);
	}

	return TRUE;
}

void CSttAdjDevice::AddMaxVolCurrValue_VolCurrModule()
{
	if (m_pSttAdjRef == NULL)
	{
		return;
	}

	CSttAdjModule oAdjModule;
	POS pos = m_pSttAdjRef->GetHeadPosition();
	CExBaseObject *pCurrObject = NULL;
	long nModuleType = -1;

	while (pos != NULL)
	{
		pCurrObject = (CExBaseObject*)m_pSttAdjRef->GetNext(pos);

		if (IsSttAdjModuleObj(pCurrObject))//从第一个开始,查找所有模块对象
		{
			oAdjModule.AttatchAdjRef((CDataGroup*)pCurrObject);

			if (oAdjModule.GetModuleType(nModuleType) && (nModuleType == STT_MODULE_TYPE_VOLT_CURRENT))
			{
				oAdjModule.AddMaxVolCurrValue_VolCurrModule();
			}
		}
	}
}

BOOL CSttAdjDevice::GetAllModules(CExBaseList *pCurModuleListRef,const long &nModuleType)
{
	if (m_pSttAdjRef == NULL)
	{
		return FALSE;
	}

	CExBaseList oList;
	m_pSttAdjRef->FindByDataType(STT_ADJ_DATA_TYPE_Module, oList);
	POS pos = oList.GetHeadPosition();
	CDataGroup *pModule = NULL;
	CSttAdjModule oAdjModule;
	long nCurModuleType = 0;

	while (pos != NULL)
	{
		pModule = (CDataGroup *)oList.GetNext(pos);
		oAdjModule.AttatchAdjRef(pModule);

		if (!oAdjModule.GetModuleType(nCurModuleType))
		{
			continue;
		}

		if (nModuleType != nCurModuleType)
		{
			continue;
		}

		pCurModuleListRef->AddTail(pModule);
	}

	oList.RemoveAll();
	return TRUE;
}

BOOL CSttAdjDevice::GetAllModules(CExBaseList *pCurModuleListRef, const CString &strModuleType)
{
	if (m_pSttAdjRef == NULL)
	{
		return FALSE;
	}

	CExBaseList oList;
	m_pSttAdjRef->FindByDataType(STT_ADJ_DATA_TYPE_Module, oList);
	POS pos = oList.GetHeadPosition();
	CDataGroup *pModule = NULL;
	CSttAdjModule oAdjModule;
	CString strCurModuleType;

	while (pos != NULL)
	{
		pModule = (CDataGroup *)oList.GetNext(pos);
		oAdjModule.AttatchAdjRef(pModule);

		if (!oAdjModule.GetModuleType(strCurModuleType))
		{
			continue;
		}

		if (strModuleType != strCurModuleType)
		{
			continue;
		}

		pCurModuleListRef->AddTail(pModule);
	}

	oList.RemoveAll();
	return TRUE;
}

BOOL CSttAdjDevice::GetAllModules(CExBaseList *pCurModuleList)
{
	if (m_pSttAdjRef == NULL)
	{
		return FALSE;
	}

	m_pSttAdjRef->FindByDataType(STT_ADJ_DATA_TYPE_Module, *pCurModuleList);
	
	return TRUE;
}


//2022-2-9  lijunqing 
void CSttAdjDevice::InitChannelsID()
{
	CExBaseList listModules;
	GetAllModules(&listModules);

	CUIntArray arModuleType;
	GetModuleTypes(&listModules, arModuleType);

	long nModuleIndex = 0 , nIndex = 0;
	long nModuleType = 0, nTemp = 0;
	long nCount = arModuleType.GetCount();
	CSttAdjModule oAdjModule;
	POS pos = NULL;
	CDataGroup *p = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		nModuleIndex = 0;
		nModuleType = arModuleType.GetAt(nIndex);
		pos = listModules.GetHeadPosition();
		
		while (pos != NULL)
		{
			p = (CDataGroup*)listModules.GetNext(pos);
			oAdjModule.AttatchAdjRef(p);
			nModuleIndex++;

			if (! oAdjModule.GetModuleType(nTemp))
			{
				continue;
			}

			if (nTemp != nModuleType)
			{
				continue;;
			}

			oAdjModule.InitChannelsID();
		}
	}

	listModules.RemoveAll();
}

BOOL CSttAdjDevice::CheckModulePos()
{
	CExBaseList listModules;
	GetAllModules(&listModules);

	POS pos = listModules.GetHeadPosition();
	CDataGroup *p = NULL, *pCurr= NULL;
	CSttAdjModule oAdjModule;
	long nPos1=0, nPos2=0;
	POS posCurr = NULL;
	long nModuleIndex = 0, nModuleIndex2 = 0;
	BOOL bSucc = TRUE;

	while (pos != NULL)
	{
		p = (CDataGroup*)listModules.GetNext(pos);
		posCurr = pos;
		oAdjModule.AttatchAdjRef(p);
		nModuleIndex++;
		
		if (! oAdjModule.GetModulePos(nPos1))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Module %d not def pos"), nModuleIndex);
			bSucc = FALSE;
			continue;
		}

		nModuleIndex2 = nModuleIndex;

		while (posCurr != NULL)
		{
			nModuleIndex2++;
			pCurr = (CDataGroup *)listModules.GetNext(posCurr);
			oAdjModule.AttatchAdjRef(pCurr);

			if (! oAdjModule.GetModulePos(nPos2))
			{
				continue;
			}

			if (nPos2 == nPos1)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Error:Module%d pos[%d] == Module%d pos[%d]"), nModuleIndex, nPos1, nModuleIndex2, nPos2);;
				bSucc = FALSE;
			}
		}
	}

	listModules.RemoveAll();
	return bSucc;
}


void CSttAdjDevice::GetModuleTypes(CExBaseList *pModuleList, CUIntArray &arModuleType)
{
	POS pos = pModuleList->GetHeadPosition();
	CDataGroup *p = NULL;
	CSttAdjModule oAdjModule;
	long nModuleType = 0, nTemp = 0;

	while (pos != NULL)
	{
		p = (CDataGroup*)pModuleList->GetNext(pos);
		oAdjModule.AttatchAdjRef(p);
		
		if (oAdjModule.GetModuleType(nModuleType) )
		{
			AddModuleType(arModuleType, nModuleType);
		}
	}


}

void CSttAdjDevice::AddModuleType(CUIntArray &arModuleType, long nModuleType)
{
	long nCount = arModuleType.GetCount();
	long nIndex = 0;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		if (nModuleType == arModuleType.GetAt(nIndex))
		{
			return;
		}
	}

	arModuleType.Add(nModuleType);
}

void CSttAdjDevice::InitModuleChannelsID(CDataGroup *pModule, long nModuleType, long nIndex)
{

}


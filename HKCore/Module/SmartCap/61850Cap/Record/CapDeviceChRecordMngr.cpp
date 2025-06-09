//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceChRecordMngr.cpp  CCapDeviceChRecordMngr


#include "stdafx.h"
#include "CapDeviceChRecordMngr.h"
#ifndef _USE_NO_GUI_
#include "../../../Record/Draw/DrawGlobalDef.h"
#endif
#include "../CapDevice/CapDeviceSmvBase.h"

//////////////////////////////////////////////////////////////////////////
CCapDeviceChRecord::CCapDeviceChRecord()
{
	m_pRecfCh = NULL;
	m_crColor = RGB(255, 255, 0);
	m_nMinValue = 6553600;
	m_nMaxValue = -6553600;
	m_pRcdCalVarRef = NULL;
}

CCapDeviceChRecord::~CCapDeviceChRecord()
{

}

CString CCapDeviceChRecord::GetName()
{
	if(m_pRecfCh == NULL)
	{
		return _T("");
	}
	else
	{
		return m_pRecfCh->m_strName;
	}
}

//////////////////////////////////////////////////////////////////////////
CCapDeviceSmvChRecord::CCapDeviceSmvChRecord()
{
    m_fChRate = 1.0f;
	m_oBufferUShort.SetBufferLength(CAP_RECORD_POINTS);
}

CCapDeviceSmvChRecord::~CCapDeviceSmvChRecord()
{


}

double CCapDeviceSmvChRecord::GetRange()
{
	double dValue = CCapDeviceChRecord::GetRange();
	dValue *= GetChRateVal();
	return dValue;
}

//////////////////////////////////////////////////////////////////////////
CCapDeviceGooseChRecord::CCapDeviceGooseChRecord()
{
	m_oBufferUShort.SetBufferLength(CAP_RECORD_POINTS_GS);
}

CCapDeviceGooseChRecord::~CCapDeviceGooseChRecord()
{

}


//////////////////////////////////////////////////////////////////////////
CCapDeviceChRecordMngr::CCapDeviceChRecordMngr()
{
	m_pRecordTest = g_theRecordApp.CreateNewCrecordTest();
	m_pRecordTest->SetCalPointByPoint(FALSE); //非逐点计算
	m_pRecordTest->init_RTATTRIBUTECAL_MIN_BUFFER_LEN(4000);
	m_pRecordTest->InitAttrsBuffer(1000); //1000个计算数值的缓冲，相当于40秒左右的计算值	
}

CCapDeviceChRecordMngr::~CCapDeviceChRecordMngr()
{
	m_listRemove.DeleteAll();
	m_pRecordTest = NULL;
}

CCapDeviceChRecord* CCapDeviceChRecordMngr::FindByCh(CCapDeviceChBase *pCh)
{
	POS pos = GetHeadPosition();
	CCapDeviceChRecord *p = NULL, *pFind = NULL;

	while (pos != NULL)
	{
		p = (CCapDeviceChRecord *)GetNext(pos);

		if (p->m_pRecfCh == pCh)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

long g_nSmvFirstChIsTdelay = 1;

void CCapDeviceChRecordMngr::RecordDevice(CCapDeviceBase *pCapDevice)
{
	POS pos = pCapDevice->GetHeadPosition();
	CCapDeviceChBase *pCh = NULL;
	CExBaseList *pParent = (CExBaseList*)pCapDevice->GetParent();
	long nDvIndex = pParent->FindIndex(pCapDevice) + 1;
	CCapDeviceChRecord *pRcdCh = NULL;

	if (pCapDevice->GetClassID() == CPDCLASSID_DEVICE92)
	{
		if (g_nSmvFirstChIsTdelay)
		{
			if (pos != NULL)
			{
				pCh = (CCapDeviceChBase *)pCapDevice->GetNext(pos);
				pCh->m_nChType = CAPDEVICE_CHTYPE_T;
				pCh->InitAfterSetChType();
				pRcdCh = AddRecordCh(pCh);
				pRcdCh->SetHdIndex(0);
			}
		}
	}

	while (pos != NULL)
	{
		pCh = (CCapDeviceChBase *)pCapDevice->GetNext(pos);
		pRcdCh = AddRecordCh(pCh);
		pRcdCh->SetHdIndex(nDvIndex);
	}

	//设置抓包，开辟时间缓冲区
	pCapDevice->SetCapSelect(TRUE);
}

BOOL CCapDeviceChRecordMngr::IsChRecordCreated(CCapDeviceChRecord *pChRecord)
{
	CRtSingleVariable* pVariable = NULL;
	POS pos = m_pRecordTest->m_pVariables->GetHeadPosition();

	while (pos != NULL)
	{
		pVariable = (CRtSingleVariable*)m_pRecordTest->m_pVariables->GetNext(pos);

		if (pVariable->m_pRefRecordData == pChRecord)
		{
			return TRUE;
		}
	}

	return FALSE;
}

void CCapDeviceChRecordMngr::InitRecordTest()
{
	POS pos = GetHeadPosition();
	CCapDeviceChRecord *p = NULL;
	UINT nClassID = 0;
	long nIndex = m_pRecordTest->m_pVariables->GetCount();
	long nAddCount = 0;

	while (pos != NULL)
	{
		p = (CCapDeviceChRecord *)GetNext(pos);
		nClassID = p->m_pRecfCh->GetClassID();

		if (IsChRecordCreated(p))
		{
			continue;
		}

		if (nClassID == CPDCLASSID_GOOSECH)
		{
			CCapDeviceGooseChRecord *pGsCh = (CCapDeviceGooseChRecord*)p;
			InitBinaryVariable(pGsCh, nIndex);
			nAddCount++;
		}
		else if (nClassID == CPDCLASSID_SMVCH)
		{
			CCapDeviceSmvChRecord *pSvmCh = (CCapDeviceSmvChRecord*)p;
			InitAnalogVariable(pSvmCh, nIndex);
			nAddCount++;
		}
	}

	if (nAddCount == 0)
	{
		return;
	}

	m_pRecordTest->m_pVariables->AdjustStaticAttrs();

	PRECORDDRAWOBJECTCONTROL pRecordDrawObjcontrol = m_pRecordTest->m_oMR1200SysAnalyseMngr.oDrawControl;
	pos = m_pRecordTest->m_pVariables->GetHeadPosition();
	CRtVariable *pVariable = NULL;
	nIndex = 0;

	//创建的时候，全部录波
	while (pos != NULL)
	{
		pVariable = (CRtVariable *)m_pRecordTest->m_pVariables->GetNext(pos);
		pVariable->SetVariableUseState(1);

		//lijunqing 2020-6-13
		if (pVariable->m_strID.GetLength() == 0)
		{
			pVariable->m_strID.Format(_T("%CH%d"), nIndex+1);
			pVariable->m_strName = pVariable->m_strName;
	
			if (nIndex < 12)
			{
				pRecordDrawObjcontrol[nIndex].nShow = 1;
				pRecordDrawObjcontrol[nIndex].nUse = 1;
			}
			else
			{
				pRecordDrawObjcontrol[nIndex].nShow = 0;
				pRecordDrawObjcontrol[nIndex].nUse = 0;
			}
		}
		else
		{
			pRecordDrawObjcontrol[nIndex].nShow = 1;
			pRecordDrawObjcontrol[nIndex].nUse = 1;
		}

		pRecordDrawObjcontrol->dRange = 1;
		nIndex++;
	}

	g_theRecordApp.InitDrawControlByRecordTest(m_pRecordTest);
	
// 	CRtVariable* pRefVariable = (CRtVariable*)m_pRecordTest->m_pVariables->GetHead();
// 	m_pRecordTest->m_pVariables->SetRefVariable(pRefVariable);

	m_pRecordTest->InitDataAttributeCalFunc(FALSE); //1000个计算数值的缓冲，相当于40秒左右的计算值
	
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_EffecValue, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_AverageValue, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm02Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm03Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm04Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm05Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm06Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm07Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm08Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm09Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm10Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm11Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm12Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm13Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm14Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm15Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm16Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm17Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm18Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm19Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm20Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm21Value, 1);//20220615 zhouhj  按实际增加到25
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm22Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm23Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm24Value, 1);
	m_pRecordTest->SetAttrUse(SingleVariableAttrID_Harm25Value, 1);

	UpdateAllRefRtVariable();
}

void CCapDeviceChRecordMngr::UpdateAllRefRtVariable()
{
	if (m_pRecordTest == NULL)
	{
		return;
	}

	POS pos = m_pRecordTest->GetHeadPosition();
	CExBaseObject *pCurrObj = NULL,*pParentList = NULL, *pRefObj = NULL;
	CRtVariables *pCurrRtVariables = NULL;
	CRtVariable *pVariable = NULL;
	CCapDeviceChRecord *pCapDeviceChRecord = NULL;
	CCapDeviceSmvCh *pCapDeviceSmvCh = NULL;
	CCapDeviceSmvBase *pCapDeviceSmv = NULL;
	long nVariableIndex = 0;
	DWORD *pDW_RtVariables = NULL;

	while(pos)
	{
		pCurrObj = m_pRecordTest->GetNext(pos);

		if (pCurrObj->GetClassID() != RTCLASSID_VARIABLES)
		{
			continue;
		}

		pCurrRtVariables = (CRtVariables*)pCurrObj;
		pDW_RtVariables = pCurrRtVariables->GetVariablesAddr();

		POS pos_RtVariable = pCurrRtVariables->GetHeadPosition();

		while(pos_RtVariable)
		{
			pVariable = (CRtVariable*)pCurrRtVariables->GetNext(pos_RtVariable);
			pCapDeviceChRecord = (CCapDeviceChRecord*)FindByID(pVariable->m_strID);

			if ((pCapDeviceChRecord == NULL)||
				(pCapDeviceChRecord->m_pRecfCh == NULL))
			{
				pVariable->m_pRefRtVariable = NULL;
				continue;
			}

			pParentList = (CExBaseList*)pCapDeviceChRecord->m_pRecfCh->GetParent();

			if ((pParentList == NULL)||
				((pParentList->GetClassID() != CPDCLASSID_DEVICE92)
				&&(pParentList->GetClassID() != CPDCLASSID_DEVICE6044)))
			{
				pVariable->m_pRefRtVariable = NULL;
				continue;
			}

			pCapDeviceSmv = (CCapDeviceSmvBase*)pParentList;
			pCapDeviceSmvCh = (CCapDeviceSmvCh*)pCapDeviceSmv->GetRefCh();

			if (pCapDeviceSmvCh == NULL)
			{
				pVariable->m_pRefRtVariable = NULL;
				continue;
			}

			pRefObj = FindByID(pCapDeviceSmvCh->m_strID);
			nVariableIndex = FindIndex(pRefObj);

			if (nVariableIndex <0 )
			{
				pVariable->m_pRefRtVariable = NULL;
				continue;
			}
			
			pVariable->m_pRefRtVariable = (CRtVariable*)pDW_RtVariables[nVariableIndex];
		}
	}
}

void CCapDeviceChRecordMngr::ChangeChRecordState(CCapDeviceChBase *pCh, long nState)
{
	if (nState == 1)
	{
		AddRecordCh(pCh);
	}
	else
	{
		RemoveRecord(pCh);
	}
}


CCapDeviceChRecord* CCapDeviceChRecordMngr::AddRecordCh(CCapDeviceChBase *pCh)
{
	CCapDeviceChRecord *pFind = FindByCh(pCh);

	if (pFind != NULL)
	{
		return pFind;
	}

	long nIndex = GetCount();
	UINT nClassID = pCh->GetClassID();

	if (nClassID == CPDCLASSID_GOOSECH)
	{
		CCapDeviceGooseChRecord *pGsCh = new CCapDeviceGooseChRecord();
		pGsCh->m_pRecfCh = pCh;
		AddNewChild(pGsCh);
		pFind = pGsCh;
	}
	else if (nClassID == CPDCLASSID_SMVCH)
	{
		CCapDeviceSmvChRecord *pSvmCh = new CCapDeviceSmvChRecord();
		pSvmCh->m_pRecfCh = pCh;
		AddNewChild(pSvmCh);
		pFind = pSvmCh;
	}

	if (pFind != NULL)
	{
		pCh->AttachCapRecord(pFind);
		pFind->m_strName = pCh->m_strName;
		pFind->m_strID = pCh->m_strID;
	}

	return pFind;
}

CCapDeviceChRecord* CCapDeviceChRecordMngr::RemoveRecord(CCapDeviceChBase *pCh)
{
	CCapDeviceChRecord *pFind = FindByCh(pCh);

	if (pFind != NULL)
	{
		if (m_listRemove.Find(pFind) == NULL)
		{
			m_listRemove.AddTail(pFind);
		}

		POS pos = Find(pFind);

		if (pos != NULL)
		{
			RemoveAt(pos);
		}
	}

	return pFind;
}

void CCapDeviceChRecordMngr::AdjustRecordChRange()
{
	CRtVariables *pVariables = m_pRecordTest->m_pVariables;
	POS pos = pVariables->GetHeadPosition();
	CRtVariable *pVariable = NULL;
	double dRange = 0;
	CCapDeviceSmvChRecord *pSmv = NULL;
	long nIndex = 0;

	while (pos != NULL)
	{
		pVariable = (CRtVariable *)pVariables->GetNext(pos);

		if (pVariable->GetClassID() == RTCLASSID_SINGLEVARIABLE)
		{
			pSmv  =(CCapDeviceSmvChRecord*)pVariable->m_pRefRecordData;
			dRange = pSmv->GetRange();
			((CRtSingleVariable*)pVariable)->SetRange(dRange);
			//m_pRecordTest->g_pCoefValue[nIndex] = pSmv->GetChRateVal();
		}

		nIndex++;
	}
}

void CCapDeviceChRecordMngr::BeginCap(BOOL bClearDevices)
{
	if (bClearDevices)
	{
		DeleteAll();
	}
	else
	{
	}
}

void CCapDeviceChRecordMngr::ClearCap()
{
	CRtVariables *pRtVariables= m_pRecordTest->m_pVariables;
	pRtVariables->InitRtCalVariables();
	pRtVariables->DeleteAll();

	DeleteAll();
}

void CCapDeviceChRecordMngr::InitVariablePhaseID(CRtSingleVariable *pVariable)
{
	if (pVariable->m_strID.Find(_T("_Ia")))
	{
		pVariable->m_strPhaseID = _T("A");
		pVariable->m_strUnit = _T("A");
	}
	else if (pVariable->m_strID.Find(_T("_Ib")))
	{
		pVariable->m_strPhaseID = _T("B");
		pVariable->m_strUnit = _T("A");
	}
	else if (pVariable->m_strID.Find(_T("_Ic")))
	{
		pVariable->m_strPhaseID = _T("C");
		pVariable->m_strUnit = _T("A");
	}
	else if (pVariable->m_strID.Find(_T("_Ua")))
	{
		pVariable->m_strPhaseID = _T("A");
		pVariable->m_strUnit = _T("V");
	}
	else if (pVariable->m_strID.Find(_T("_Ub")))
	{
		pVariable->m_strPhaseID = _T("B");
		pVariable->m_strUnit = _T("V");
	}
	else if (pVariable->m_strID.Find(_T("_Uc")))
	{
		pVariable->m_strPhaseID = _T("C");
		pVariable->m_strUnit = _T("V");
	}
}

CRtSingleVariable* CCapDeviceChRecordMngr::InitAnalogVariable(CCapDeviceSmvChRecord* pAnalog, long &nIndex)
{
	CString strID,str;
	CRtSingleVariable* pVariable = NULL;

	if (pAnalog == NULL)
	{
		return NULL;
	}

	pVariable = new CRtSingleVariable();
	pVariable->m_pRefRecordData = pAnalog;
	pAnalog->m_pRcdCalVarRef = pVariable;
	m_pRecordTest->m_pVariables->AddNewChild(pVariable);
	pVariable->m_pAttachRecordBuffer = pAnalog->GetRecordBuffer();
	pVariable->Set_ChIndex(nIndex);
	pVariable->m_strID		= pAnalog->m_strID;  //关联和绑定配置文件的ID  2020-06-13 lijunqing
	pVariable->m_strName    = pAnalog->m_strName;
	InitVariablePhaseID(pVariable);
	pVariable->m_strDCAC    = g_pszKeyVariableACDC;
	m_pRecordTest->g_pCoefValue[nIndex]    = pAnalog->GetChRateVal();
	m_pRecordTest->g_pZeroValue[nIndex]    = 0;
	double dRange = 1;//后续动态计算调整
#ifndef _USE_NO_GUI_
	dRange = MrDraw::GetFloatCarryValue2(dRange);
#endif
	pVariable->SetRange(dRange);
	pVariable->m_pChannelBuffer = NULL;
	pVariable->m_nType = RTVARIABLE_TYPE_NONE;

	//根据相别添加颜色
	pVariable->m_crColor = GetPhaseColorByPhaseID(pVariable->m_strPhaseID, pVariable->m_strID);
	pVariable->CreateStaticAttrs(pAnalog->m_strName);
	nIndex++;

	return pVariable;
}

CRtBinaryVariable* CCapDeviceChRecordMngr::InitBinaryVariable(CCapDeviceGooseChRecord *pBinary, long& nIndex)
{
	CRtBinaryVariable* pVariable = NULL;

	if (pBinary != NULL)
	{
		return NULL;
	}

	pVariable = new CRtBinaryVariable();
	pBinary->m_pRcdCalVarRef = pVariable;
	pVariable->m_pRefRecordData = pBinary;
	m_pRecordTest->m_pVariables->AddNewChild(pVariable);
	pVariable->m_pAttachRecordBuffer = pBinary->GetRecordBuffer();
	pVariable->Set_ChIndex(nIndex);
	pVariable->m_pChannelBuffer = NULL;
	pVariable->m_strName = pBinary->m_strName;
	pVariable->m_nIndex  = 0;
	pVariable->m_crColor = RGB(0,255,0);

	CRtDataAttributes* pAttrs = new CRtDataAttributes();
	pVariable->m_pDataAttrs = pAttrs;
	pAttrs->SetParent(pVariable);
	pVariable->AddTail(pAttrs);
	nIndex++;

	return pVariable;
}


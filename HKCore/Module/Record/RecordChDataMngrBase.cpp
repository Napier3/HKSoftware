//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceChRecordMngr.cpp  CRecordChDataMngrBase


#include "stdafx.h"
#include "RecordChDataMngrBase.h"
#include "Draw/DrawGlobalDef.h"
#include "Draw/RecordTestDrawBase.h"

//////////////////////////////////////////////////////////////////////////
CRecordChDataBase::CRecordChDataBase()
{
	m_pExternChRef = NULL;
	m_crColor = RGB(255, 255, 0);
	m_pRcdCalVarRef = NULL;
	m_pMemBuffer = NULL;
}

CRecordChDataBase::~CRecordChDataBase()
{

}

void CRecordChDataBase::SetBufferLen(long nLen)
{
	if (m_pMemBuffer != NULL)
	{
		m_pMemBuffer->SetBufferLength(nLen);
	}
}

CString CRecordChDataBase::GetName()
{
	if(m_pExternChRef == NULL)
	{
		return _T("");
	}
	else
	{
		return m_pExternChRef->m_strName;
	}
}

//////////////////////////////////////////////////////////////////////////
CRecordChDataAnalog::CRecordChDataAnalog()
{
	m_fMinValue = 6553600;
	m_fMaxValue = -6553600;
    m_fChRate = 1.0f;
	m_pMemBuffer = m_pBufferLong;
	m_pBufferLong = NULL;
	m_pBufferFloat = NULL;
}

CRecordChDataAnalog::~CRecordChDataAnalog()
{
	if (m_pBufferLong != NULL)
	{
		delete m_pBufferLong;
	}

	if (m_pBufferFloat != NULL)
	{
		delete m_pBufferFloat;
	}
}

void CRecordChDataAnalog::AddRcdData(WORD wValue)
{
	if (m_pBufferLong != NULL)
	{
		m_pBufferLong->AddValue(wValue);
	}
}

void CRecordChDataAnalog::AddRcdData(long nValue)
{
	if (m_pBufferLong != NULL)
	{
		m_pBufferLong->AddValue(nValue);
	}
}

void CRecordChDataAnalog::AddRcdData(float fValue)
{
	if (m_pBufferFloat != NULL)
	{
		m_pBufferFloat->AddValue(fValue);
	}
}

void CRecordChDataAnalog::AddRcdData(double dValue)
{
	if (m_pBufferFloat != NULL)
	{
		m_pBufferFloat->AddValue(dValue);
	}
}

void CRecordChDataAnalog::AddRcdData(long wValue, long nPos)
{
	if (m_pBufferLong != NULL)
	{
		m_pBufferLong->SetValue(wValue, nPos);
	}
}

void CRecordChDataAnalog::AddRcdData(WORD wValue, long nPos)
{
}

void CRecordChDataAnalog::AddRcdData(float fValue, long nPos)
{
	if (m_pBufferFloat != NULL)
	{
		m_pBufferFloat->SetValue(fValue, nPos);
	}
}

void CRecordChDataAnalog::AddRcdData(double dValue, long nPos)
{
	if (m_pBufferFloat != NULL)
	{
		m_pBufferFloat->SetValue(dValue, nPos);
	}
}

double CRecordChDataAnalog::GetRange()
{
	double dValue = 0;
	double dRange1 = abs(m_fMinValue);
	double dRange2 = abs(m_fMaxValue);

	if (dRange1 > dRange2)
	{
		dValue = dRange1;
	}
	else
	{
		dValue = dRange2;
	}

	dValue *= GetChRateVal();

	return dValue;
}

double CRecordChDataAnalog::GetChRateVal()
{
	return m_fChRate;
}

double* CRecordChDataAnalog::GetChRate()
{
	return &m_fChRate;
}

UINT CRecordChDataAnalog::GetChType()
{
	return 0;
}

void CRecordChDataAnalog::CalMinMax()
{
	if (m_pBufferLong != NULL)
	{
		CalMinMax_Long();
	}

	if (m_pBufferFloat != NULL)
	{
		CalMinMax_Float();
	}
}

void CRecordChDataAnalog::CalMinMax_Long()
{
	long k = 0;
	long nLen = m_pBufferLong->GetDataLength();
	long *pBuffer = m_pBufferLong->GetBuffer_long();
	m_fMinValue = 0;
	m_fMaxValue = 0;

	for (k=0; k<nLen; k++)
	{
		m_fMaxValue = max(m_fMaxValue, *pBuffer);
		m_fMinValue = min(m_fMinValue, *pBuffer);
		pBuffer++;
	}
}

void CRecordChDataAnalog::CalMinMax_Float()
{
	long k = 0;
	long nLen = m_pBufferFloat->GetDataLength();
	float *pBuffer = m_pBufferFloat->GetBuffer_float();
	m_fMinValue = 0;
	m_fMaxValue = 0;

	for (k=0; k<nLen; k++)
	{
		m_fMaxValue = max(m_fMaxValue, *pBuffer);
		m_fMinValue = min(m_fMinValue, *pBuffer);
		pBuffer++;
	}
}

void CRecordChDataAnalog::SetMemBuffer_Long()
{
	if (m_pBufferFloat != NULL)
	{
		delete m_pBufferFloat;
		m_pBufferFloat = NULL;
	}

	if (m_pBufferLong == NULL)
	{
		m_pBufferLong = new CMemBuffer_Long();
	}

	m_pMemBuffer = m_pBufferLong;
}

void CRecordChDataAnalog::SetMemBuffer_Float()
{
	if (m_pBufferLong != NULL)
	{
		delete m_pBufferLong;
		m_pBufferLong = NULL;
	}

	if (m_pBufferFloat == NULL)
	{
		m_pBufferFloat = new CMemBuffer_Float();
	}

	m_pMemBuffer = m_pBufferFloat;
}



//////////////////////////////////////////////////////////////////////////
CRecordChDataBinary::CRecordChDataBinary()
{
	m_pMemBuffer = &m_oBufferUShort;
}

CRecordChDataBinary::~CRecordChDataBinary()
{

}


//////////////////////////////////////////////////////////////////////////
CRecordChDataMngrBase::CRecordChDataMngrBase()
{
	m_pRecordTest = NULL;
	m_pVariableMngr = NULL;
	m_pViewAnalyse = NULL;
	m_nCurrRcdChIndex = 0;
	m_nChCountPerPage = RECORD_WAVE_DRAW_CHS_PER_PAGE;
	m_bInitTimeAxis = TRUE;
}

CRecordChDataMngrBase::~CRecordChDataMngrBase()
{
	m_listRcdVariable.RemoveAll();
	m_listRemove.DeleteAll();
	m_pRecordTest = NULL;
}

void CRecordChDataMngrBase::InitRecordChDataMngr()
{
	if (m_pRecordTest != NULL)
	{
		return;
	}

	m_pRecordTest = g_theRecordApp.CreateNewCrecordTest();
	m_pRecordTest->SetCalPointByPoint(FALSE); //非逐点计算
	m_pRecordTest->init_RTATTRIBUTECAL_MIN_BUFFER_LEN(4000);
	m_pRecordTest->InitAttrsBuffer(1000); //1000个计算数值的缓冲，相当于40秒左右的计算值	
}

void CRecordChDataMngrBase::ExitRecordChDataMngr()
{
	m_pRecordTest = NULL;
	DeleteAll();
}

CRecordChDataBase* CRecordChDataMngrBase::FindByExternCh(CExBaseObject *pExternChRef)
{
	POS pos = GetHeadPosition();
	CRecordChDataBase *p = NULL, *pFind = NULL;

	while (pos != NULL)
	{
		p = (CRecordChDataBase *)GetNext(pos);

		if (p->m_pExternChRef == pExternChRef)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

long CRecordChDataMngrBase::GetHdIndex(CExBaseList *pListExternCh)
{
	return 0;
}

void CRecordChDataMngrBase::Record(CExBaseList *pListExternCh)
{
	POS pos = pListExternCh->GetHeadPosition();
	CExBaseObject *pCh = NULL;
	long nDvIndex = GetHdIndex(pListExternCh);
	CRecordChDataBase *pRcdCh = NULL;

	while (pos != NULL)
	{
		pCh = pListExternCh->GetNext(pos);
		pRcdCh = AddRecordCh(pCh);
		pRcdCh->SetHdIndex(nDvIndex);
	}
}

BOOL CRecordChDataMngrBase::IsChRecordCreated(CRecordChDataBase *pChRecord)
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

void CRecordChDataMngrBase::InitRecordTest()
{
	long nAddCount =CreateVariables();

	if (nAddCount == 0)
	{
		return;
	}

	InitRecordDrawObjcontrol();
	g_theRecordApp.InitDrawControlByRecordTest(m_pRecordTest);
	InitRecordTest_Attrs();

	GetCurrDeviceAllRcdVariables();
}

long CRecordChDataMngrBase::CreateVariables()
{
	POS pos = GetHeadPosition();
	CRecordChDataBase *p = NULL;
	UINT nClassID = 0;
	long nIndex = m_pRecordTest->m_pVariables->GetCount();
	long nAddCount = 0;

	while (pos != NULL)
	{
		p = (CRecordChDataBase *)GetNext(pos);
		nClassID = p->GetClassID();

		if (IsChRecordCreated(p))
		{
			continue;
		}

		if (nClassID == RCDCHDATA_BINARY)
		{
			CRecordChDataBinary *pBinary = (CRecordChDataBinary*)p;
			InitBinaryVariable(pBinary, nIndex);
			nAddCount++;
		}
		else if (nClassID == RCDCHDATA_ANALOG)
		{
			CRecordChDataAnalog *pAnalog = (CRecordChDataAnalog*)p;
			InitAnalogVariable(pAnalog, nIndex);
			nAddCount++;
		}
	}

	return m_pRecordTest->m_pVariables->GetCount();
}

void CRecordChDataMngrBase::InitRecordDrawObjcontrol()
{
	PRECORDDRAWOBJECTCONTROL pRecordDrawObjcontrol = m_pRecordTest->m_oMR1200SysAnalyseMngr.oDrawControl;
	POS pos = m_pRecordTest->m_pVariables->GetHeadPosition();
	CRtVariable *pVariable = NULL;
	long nIndex = 0;

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
}

void CRecordChDataMngrBase::InitRecordTest_Attrs()
{
	m_pRecordTest->m_pVariables->AdjustStaticAttrs();

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
}

void CRecordChDataMngrBase::GetCurrDeviceAllRcdVariables()
{
	m_listRcdVariable.RemoveAll();
	m_listRcdVariable.Append(m_pRecordTest->m_pVariables);
}

BOOL CRecordChDataMngrBase::IsExternCh_Analog(CExBaseObject *pExternCh)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("------------ IsExternCh_Analog ------------"));
	return TRUE;
}

BOOL CRecordChDataMngrBase::IsExternCh_Binary(CExBaseObject *pExternCh)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("------------ IsExternCh_Binary ------------"));
	return FALSE;
}

void CRecordChDataMngrBase::AttachToExternCh(CExBaseObject *pExternCh, CRecordChDataBase *pRcdChData)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("------------ AttachToExternCh ------------"));
}

CRecordChDataBase* CRecordChDataMngrBase::AddRecordCh(CExBaseObject *pCh)
{
	CRecordChDataBase *pFind = FindByExternCh(pCh);

	if (pFind != NULL)
	{
		return pFind;
	}

	long nIndex = GetCount();
	
	if (IsExternCh_Binary(pCh))
	{
		CRecordChDataBinary *pBinary = NewRcdChDataBinary();
		pBinary->m_pExternChRef = pCh;
		AddNewChild(pBinary);
		pFind = pBinary;
	}
	else if (IsExternCh_Analog(pCh))
	{
		CRecordChDataAnalog *pAnalog = NewRcdChDataAnalog();
		pAnalog->m_pExternChRef = pCh;
		AddNewChild(pAnalog);
		pFind = pAnalog;
	}

	if (pFind != NULL)
	{
		AttachToExternCh(pCh, pFind);
		pFind->m_strName = pCh->m_strName;
		pFind->m_strID = pCh->m_strID;
	}

	return pFind;
}

CRecordChDataAnalog* CRecordChDataMngrBase::NewRcdChDataAnalog()
{
	return new CRecordChDataAnalog();
}

CRecordChDataBinary* CRecordChDataMngrBase::NewRcdChDataBinary()
{
	return new CRecordChDataBinary();
}

void CRecordChDataMngrBase::SetBufferLen(long nLen)
{
	POS pos = GetHeadPosition();
	CRecordChDataBase *p = NULL;

	while (pos != NULL)
	{
		p = (CRecordChDataBase *)GetNext(pos);
		p->SetBufferLen(nLen);
	}
}

CRecordChDataBase* CRecordChDataMngrBase::RemoveRecord(CExBaseObject *pCh)
{
	CRecordChDataBase *pFind = FindByExternCh(pCh);

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

void CRecordChDataMngrBase::AdjustRecordChRange()
{
	CRtVariables *pVariables = m_pRecordTest->m_pVariables;
	POS pos = pVariables->GetHeadPosition();
	CRtVariable *pVariable = NULL;
	double dRange = 0;
	CRecordChDataAnalog *pSmv = NULL;
	long nIndex = 0;

	while (pos != NULL)
	{
		pVariable = (CRtVariable *)pVariables->GetNext(pos);

		if (pVariable->GetClassID() == RTCLASSID_SINGLEVARIABLE)
		{
			pSmv  =(CRecordChDataAnalog*)pVariable->m_pRefRecordData;
			dRange = pSmv->GetRange();
			((CRtSingleVariable*)pVariable)->SetRange(dRange);
			//m_pRecordTest->g_pCoefValue[nIndex] = pSmv->GetChRateVal();
		}

		nIndex++;
	}
}

void CRecordChDataMngrBase::Release()
{
	CRtVariables *pRtVariables= m_pRecordTest->m_pVariables;
	pRtVariables->InitRtCalVariables();
	pRtVariables->DeleteAll();

	DeleteAll();
}

void CRecordChDataMngrBase::InitVariablePhaseID(CRtSingleVariable *pVariable)
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

CRtSingleVariable* CRecordChDataMngrBase::InitAnalogVariable(CRecordChDataAnalog* pAnalog, long &nIndex)
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

	dRange = MrDraw::GetFloatCarryValue2(dRange);
	pVariable->SetRange(dRange);
	pVariable->m_pChannelBuffer = NULL;
	pVariable->m_nType = RTVARIABLE_TYPE_NONE;

	//根据相别添加颜色
	pVariable->m_crColor = GetPhaseColorByPhaseID(pVariable->m_strPhaseID, pVariable->m_strID);
	pVariable->CreateStaticAttrs(pAnalog->m_strName);
	nIndex++;

	return pVariable;
}

CRtBinaryVariable* CRecordChDataMngrBase::InitBinaryVariable(CRecordChDataBinary *pBinary, long& nIndex)
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

//////////////////////////////////////////////////////////////////////////
//

void CRecordChDataMngrBase::SetViewAnalyse(CViewAnalyse *p)
{
	m_pViewAnalyse = p;
	m_pVariableMngr = &p->m_oVariableMngr;
}

void CRecordChDataMngrBase::CalIndex_NextPage()
{
	long nBinarys = 0;
	long nAnalogs = 0;
	long nChsCount = 0;
	BOOL bNeedAdjust = FALSE;

	CDrawVariable *pDrawVariable = NULL;
	//CRtVariables *pVariables = m_pRecordTest->m_pVariables;  //2022-6-12  lijunqing  只显示当前CapDevice的通道
	CRtVariable* pVariable =NULL;
	long nAnalogChanAmount = 0;
	long nCurrentChans = 0;
	long nIndex = m_nCurrRcdChIndex;

	for (nIndex=m_nCurrRcdChIndex; ; nIndex++)
	{
		//pVariable = (CRtVariable*)pVariables->GetAtIndex(nIndex);  //2022-6-12  lijunqing  只显示当前CapDevice的通道
		pVariable = (CRtVariable*)m_listRcdVariable.GetAtIndex(nIndex);

		if (pVariable == NULL)
		{
			break;
		}

		if (! pVariable->CanCal())
		{
			continue;
		}

		nAnalogChanAmount++;
		nCurrentChans++;

		if (nCurrentChans >= m_nChCountPerPage)
		{
			break;
		}
	}

	//if (nIndex >= pVariables->GetCount()) //2022-6-12  lijunqing  只显示当前CapDevice的通道
	if (nIndex >= m_listRcdVariable.GetCount())
	{
		m_nCurrRcdChIndex = 0;
	}
	else
	{
		m_nCurrRcdChIndex = nIndex;
	}
}

void CRecordChDataMngrBase::CalIndex_PrevPage()
{
	long nBinarys = 0;
	long nAnalogs = 0;
	long nChsCount = 0;
	BOOL bNeedAdjust = FALSE;

	CDrawVariable *pDrawVariable = NULL;
	//CRtVariables *pVariables = m_pRecordTest->m_pVariables;  //2022-6-12  lijunqing  只显示当前CapDevice的通道
	CRtVariable* pVariable =NULL;
	long nAnalogChanAmount = 0;
	long nCurrentChans = 0;
	long nIndex = 0;

	if (m_nCurrRcdChIndex == 0)
	{
		//nIndex = pVariables->GetCount()-1;  //2022-6-12  lijunqing  只显示当前CapDevice的通道
		nIndex = m_listRcdVariable.GetCount()-1;
	}
	else
	{
		nIndex = m_nCurrRcdChIndex;
	}

	while (TRUE)
	{
		//pVariable = (CRtVariable*)pVariables->GetAtIndex(nIndex);  //2022-6-12  lijunqing  只显示当前CapDevice的通道
		pVariable = (CRtVariable*)m_listRcdVariable.GetAtIndex(nIndex);

		if (pVariable == NULL)
		{
			break;
		}

		if (! pVariable->CanCal())
		{
			continue;
		}

		nAnalogChanAmount++;
		nCurrentChans++;

		if (nCurrentChans >= m_nChCountPerPage)
		{
			break;
		}

		nIndex--;
	}

	if (nIndex <= 0)
	{
		m_nCurrRcdChIndex = 0;
	}
	else
	{
		m_nCurrRcdChIndex = nIndex;
	}
}

void CRecordChDataMngrBase::UpdateDrawVariablesRange()
{
	POS pos = m_pVariableMngr->GetHeadPosition();
	CDrawAnalogVariable *pDrawVariable = NULL;
	CRtSingleVariable* pSingle = NULL;
	double dCurrVal = 0;
	double dRange = 0;

	while (pos != NULL)
	{
		pDrawVariable = (CDrawAnalogVariable *)m_pVariableMngr->GetNext(pos);
		pSingle = (CRtSingleVariable*)pDrawVariable->m_pXDrawDataRef;
		dCurrVal = pSingle->m_oCurrValue.dEffecValue;
		dRange = pDrawVariable->GetRange();

		if (dCurrVal > dRange)
		{
			pDrawVariable->SetRange(dCurrVal);
		}
		else if (dRange > (2*dCurrVal))//20220625 zhouhj 如果当前有效值大于2倍的最大量程值时,对量程进行调整
		{
			pDrawVariable->SetRange(dCurrVal*1.2);
		}
	}
}

void CRecordChDataMngrBase::SetDrawVariablesRange()
{
	POS pos = m_pVariableMngr->GetHeadPosition();
	CDrawAnalogVariable *pDrawVariable = NULL;
	CRtSingleVariable* pSingle = NULL;
	double dCurrVal = 0;

	while (pos != NULL)
	{
		pDrawVariable = (CDrawAnalogVariable *)m_pVariableMngr->GetNext(pos);
		pSingle = (CRtSingleVariable*)pDrawVariable->m_pXDrawDataRef;
		dCurrVal = pSingle->m_oCurrValue.dEffecValue;
		pDrawVariable->SetRange(dCurrVal);
	}
}

void CRecordChDataMngrBase::InitVariablesRangeByRcdChData()
{
	POS pos = m_listRcdVariable.GetHeadPosition();
	CDrawAnalogVariable *pDrawVariable = NULL;
	CRtVariable* pVariable = NULL;
	double dCurrVal = 0;
	CRecordChDataBase *pRcdCh = NULL;
	RECORDDRAWOBJECTCONTROL *p =  m_pRecordTest->m_oMR1200SysAnalyseMngr.oDrawControl;

	while (pos != NULL)
	{
		pVariable = (CRtVariable*)m_listRcdVariable.GetNext(pos);
		pRcdCh = (CRecordChDataBase*)pVariable->m_pRefRecordData;
		pRcdCh->CalMinMax();
		p->dRange = pRcdCh->GetRange();
		p++;
	}
}

LRESULT CRecordChDataMngrBase::OnVariableAddRemoved(WPARAM wParam, LPARAM lParam)
{
	if (m_pRecordTest == NULL)
	{
		return 0;
	}

	long nBinarys = 0;
	long nAnalogs = 0;
	long nChsCount = 0;
	BOOL bNeedAdjust = FALSE;

	m_pVariableMngr->DeleteAll();
	CDrawVariable *pDrawVariable = NULL;
	CRtVariable* pVariable =NULL;
	long nAnalogChanAmount = 0;
	long nCurrentChans = 0;
	long nIndex = m_nCurrRcdChIndex;

	for (nIndex=m_nCurrRcdChIndex; ; nIndex++)
	{
		pVariable = (CRtVariable*)m_listRcdVariable.GetAtIndex(nIndex);

		if (pVariable == NULL)
		{
			break;
		}

		if (! pVariable->CanCal())
		{
			continue;
		}

		pDrawVariable = m_pViewAnalyse->AddAnalogDrawVariable(pVariable, nCurrentChans, nAnalogChanAmount);

		if (NULL == pDrawVariable)
		{
			continue;
		}

		pDrawVariable->m_strName = pVariable->m_strID;
		pDrawVariable->m_strID = pVariable->m_strID;
		nAnalogChanAmount++;
		nCurrentChans++;

		if (nCurrentChans >= m_nChCountPerPage)
		{
			break;
		}
	}

	pDrawVariable = (CDrawVariable *)GetHead();
	bNeedAdjust = TRUE;

	InitMR1200SysAnalyseMngrDrawControl(m_pRecordTest->m_oMR1200SysAnalyseMngr, nAnalogChanAmount,0);

	//InitCapViewDraw();
	//OnSizeEx(0, 0, 0);
	//m_pViewAnalyse->InitTimeAxis();

	return 0;
}


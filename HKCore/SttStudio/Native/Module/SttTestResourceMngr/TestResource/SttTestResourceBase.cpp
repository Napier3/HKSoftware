#include "stdafx.h"
#include "SttTestResourceBase.h"
#ifndef STT_NOT_TESTCNTRFRAME
#include "../../XLangResource_Native.h"
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSttChResource::CSttChResource()
{
	m_bHasMapHdRs = FALSE;
}

long CSttChResource::GetChIndex()
{
	ASSERT(m_strID.GetLength()>1);
	CString strValue;
	strValue = m_strID.Mid(1);

	long nValue = CString_To_long(strValue);

	if (nValue<1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰͨ��(Name=%s;ID=%s;)��Ŵ���,���ֵС��1."),m_strName.GetString(),m_strID.GetString());
		nValue = 1;
	}

	return nValue;
}

long CSttChResource::GetChIndex_FromZero()
{
	long nValue = GetChIndex();
	nValue--;
	return nValue;
}

BOOL CSttChResource::IsVolCh()
{
	if (m_strID.GetAt(0) == 'U')
	{
		return TRUE;
	}

	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CSttChGroupResource::HasVolCh()
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while(pos)
	{
		pObj = GetNext(pos);

		if (pObj->m_strID.GetAt(0) == 'U')
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CSttChGroupResource::HasCurCh()
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while(pos)
	{
		pObj = GetNext(pos);

		if (pObj->m_strID.GetAt(0) == 'I')
		{
			return TRUE;
		}
	}

	return FALSE;
}

long CSttChGroupResource::GetHeadChIndex_FromZero()
{
	if (GetCount() == 0)
	{
		ASSERT(FALSE);//��Ӧ��Ϊ��
		return 0;
	}

	long nHeadChIndex = 100;
	long nCurChIndex = 0;
	POS pos = GetHeadPosition();
	CSttChResource *pObj = NULL;

	while(pos)
	{
		pObj = (CSttChResource*)GetNext(pos);
		nCurChIndex = pObj->GetChIndex_FromZero();

		if (nHeadChIndex>nCurChIndex)
		{
			nHeadChIndex = nCurChIndex;
		}
	}

	return nHeadChIndex;
}

void CSttChGroupResource::GetVolChs(CSttChGroupResource *pListRef)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while(pos)
	{
		pObj = GetNext(pos);

		if (pObj->m_strID.GetAt(0) == 'U')
		{
			pListRef->AddTail(pObj);
		}
	}
}

void CSttChGroupResource::GetCurChs(CSttChGroupResource *pListRef)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while(pos)
	{
		pObj = GetNext(pos);

		if (pObj->m_strID.GetAt(0) == 'I')
		{
			pListRef->AddTail(pObj);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSttTestResourceBase::CSttTestResourceBase(void)
{
}

CSttTestResourceBase::~CSttTestResourceBase(void)
{
	ClearAll();
}

void CSttTestResourceBase::CreateSoftResource()
{
//	DeleteAll();
// 	CString strID;
// 
// 	for (int nIndex = 0;nIndex<nCurChNum;nIndex++)
// 	{
// 		strID.Format(_T("I%d"),nIndex+1);
// 		AddNewData(_T(""), strID);
// 	}
// 
// 	for (int nIndex = 0;nIndex<nVolChNum;nIndex++)
// 	{
// 		strID.Format(_T("U%d"),nIndex+1);
// 		AddNewData(_T(""), strID,_T(""),_T(""));
// 	}
}

void CSttTestResourceBase::CreateSoftResourceByChMaps(CExBaseList *pCExBaseList)
{
	DeleteAll();
	POS pos = pCExBaseList->GetHeadPosition();
	CExBaseObject *pCurrObj = NULL;

	while(pos)
	{
		pCurrObj = m_oListGroups.GetNext(pos);
		AddNewData(pCurrObj->m_strName,pCurrObj->m_strID);
	}
}
// BOOL CSttTestResourceBase::SetChNameByID(const CString &strID,const CString &strName)
// {
// 	CDvmData *pCh = (CDvmData*)FindByID(strID);
// 
// 	if (pCh == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	pCh->m_strName = strName;
// 	return TRUE;
// }

CSttChResource* CSttTestResourceBase::AddNewData(const CString &strName,const CString &strID)
{
	CSttChResource *pNew = new CSttChResource();
	pNew->m_strName = strName;
	pNew->m_strID = strID;
	AddNewChild(pNew);

	if (strID.Find(_T("U")) == 0)
	{
		m_oVolChRsListRef.AddTail(pNew);
	} 
	else
	{
		m_oCurChRsListRef.AddTail(pNew);
	}

	return pNew;
}

void CSttTestResourceBase::ClearAll()
{
	DeleteAll();
	m_oVolChRsListRef.RemoveAll();
	m_oCurChRsListRef.RemoveAll();
	ClearGroups();
}

CString CSttTestResourceBase::GetChMapFileName()
{
	CString strChMapsName;
	strChMapsName = _T("ChMapConfig.") + GetChMapsFilePostfix();
	return strChMapsName;
}

void CSttTestResourceBase::ClearGroups()
{
	POS pos = m_oListGroups.GetHeadPosition();
	CSttChGroupResource *pGroup = NULL;

	while(pos)
	{
		pGroup = (CSttChGroupResource *)m_oListGroups.GetNext(pos);
		pGroup->RemoveAll();
	}

	m_oListGroups.DeleteAll();
}

void CSttTestResourceBase::InitAfterCreated()
{
	InitGroup();
}
void CSttTestResourceBase::InitGroup()
{
	if (m_oListGroups.GetCount()>0)//���֮ǰ���黹�ڣ��������
	{
		ClearGroups();
	}

	CSttChGroupResource *pGroup = NULL;
	CExBaseList oVolListRef,oCurListRef;
	oVolListRef.Append(&m_oVolChRsListRef);
	oCurListRef.Append(&m_oCurChRsListRef);

	if ((oVolListRef.GetCount() <= 4)&&(oVolListRef.GetCount()>0))//���ֻ��4�飬�����һ��
	{
		pGroup = new CSttChGroupResource;
		pGroup->m_strID = _T("Group1");
		pGroup->Append(&oVolListRef);
		m_oListGroups.AddNewChild(pGroup);
		oVolListRef.RemoveAll();
	}

	if ((oCurListRef.GetCount() <= 4)&&(oCurListRef.GetCount()>0))//���ֻ��4�飬�����һ��
	{
		pGroup = (CSttChGroupResource*)m_oListGroups.FindByID(_T("Group1"));

		if (pGroup == NULL)
		{
			pGroup = new CSttChGroupResource;
			pGroup->m_strID = _T("Group1");
			m_oListGroups.AddNewChild(pGroup);
		}

		pGroup->Append(&oCurListRef);
		oCurListRef.RemoveAll();
	}

	long nGroupIndex = 0,nChIndex = 0;
	POS pos = oVolListRef.GetHeadPosition();
	CSttChResource *pMacroCh = NULL;
	CString strTmp;

	while(pos)//��ѹͨ���������������4�������ÿ3��һ����з���,�Ҵ�ʱ�����������Ҫnew
	{
		pMacroCh = (CSttChResource *)oVolListRef.GetNext(pos);

		if (nChIndex%3 == 0)
		{
			nGroupIndex++;
			strTmp.Format(_T("Group%ld"),nGroupIndex);
			pGroup = (CSttChGroupResource*)m_oListGroups.FindByID(strTmp);

			if (pGroup == NULL)
			{
				pGroup = new CSttChGroupResource;
				pGroup->m_strID = strTmp;
				m_oListGroups.AddNewChild(pGroup);
			}
		}

		pGroup->AddTail(pMacroCh);
		nChIndex++;
	}

	nGroupIndex = 0;
	nChIndex = 0;
	pos = oCurListRef.GetHeadPosition();//����ͨ���������������4�������ÿ3��һ����з��飬��Ҫ�Ȳ��Ҹ������Ƿ���ڣ���������ڣ���new

	while(pos)
	{
		pMacroCh = (CSttChResource *)oCurListRef.GetNext(pos);

		if (nChIndex%3 == 0)
		{
			nGroupIndex++;
			strTmp.Format(_T("Group%ld"),nGroupIndex);
			pGroup = (CSttChGroupResource*)m_oListGroups.FindByID(strTmp);

			if (pGroup == NULL)
			{
				pGroup = new CSttChGroupResource;
				pGroup->m_strID = strTmp;
				m_oListGroups.AddNewChild(pGroup);
			}
		}

		pGroup->AddTail(pMacroCh);
		nChIndex++;
	}

	oVolListRef.RemoveAll();
	oCurListRef.RemoveAll();
}

void CSttTestResourceBase::AddGradientChs(CDataType &oGradientChs, BOOL bUseAllFreq)
{
	oGradientChs.DeleteAll();
	CSttChResource *pUa1 = (CSttChResource*)m_oVolChRsListRef.GetAtIndex(0),*pUb1 = (CSttChResource*)m_oVolChRsListRef.GetAtIndex(1),*pUc1 = (CSttChResource*)m_oVolChRsListRef.GetAtIndex(2);
	CSttChResource *pUa2 = (CSttChResource*)m_oVolChRsListRef.GetAtIndex(3),*pUb2 = (CSttChResource*)m_oVolChRsListRef.GetAtIndex(4),*pUc2 = (CSttChResource*)m_oVolChRsListRef.GetAtIndex(5);
	CSttChResource *pIa1 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(0),*pIb1 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(1),*pIc1 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(2);
	CSttChResource *pIa2 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(3),*pIb2 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(4),*pIc2 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(5);
	AddGradientCh(&oGradientChs,pUa1,va1_type);
	AddGradientCh(&oGradientChs,pUb1,vb1_type);
	AddGradientCh(&oGradientChs,pUc1,vc1_type);
	AddGradientCh(&oGradientChs,pUa1,pUb1,vab1_type);
	AddGradientCh(&oGradientChs,pUb1,pUc1,vbc1_type);
	AddGradientCh(&oGradientChs,pUc1,pUa1,vca1_type);
	AddGradientCh(&oGradientChs,pUa1,pUb1,pUc1,vabc1_type);

	AddGradientCh(&oGradientChs,pUa2,va2_type);
	AddGradientCh(&oGradientChs,pUb2,vb2_type);
	AddGradientCh(&oGradientChs,pUc2,vc2_type);
	AddGradientCh(&oGradientChs,pUa2,pUb2,pUc2,vabc2_type);

	AddGradientCh(&oGradientChs,pIa1,ia1_type);
	AddGradientCh(&oGradientChs,pIb1,ib1_type);
	AddGradientCh(&oGradientChs,pIc1,ic1_type);
	AddGradientCh(&oGradientChs,pIa1,pIb1,iab1_type);
	AddGradientCh(&oGradientChs,pIb1,pIc1,ibc1_type);
	AddGradientCh(&oGradientChs,pIc1,pIa1,ica1_type);
	AddGradientCh(&oGradientChs,pIa1,pIb1,pIc1,iabc1_type);

	AddGradientCh(&oGradientChs,pIa2,ia2_type);
	AddGradientCh(&oGradientChs,pIb2,ib2_type);
	AddGradientCh(&oGradientChs,pIc2,ic2_type);
	AddGradientCh(&oGradientChs,pIa2,pIb2,pIc2,iabc2_type);

	AddGradientCh(&oGradientChs,pUa1,pUb1,pUc1,pUa2,pUb2,pUc2,vall_type);
	AddGradientCh(&oGradientChs,pIa1,pIb1,pIc1,pIa2,pIb2,pIc2,iall_type);

	if (bUseAllFreq)
	{
#ifdef STT_NOT_TESTCNTRFRAME
		AddGradientCh(&oGradientChs, _T("ȫ��Ƶ��(ǰ����)"), freAll_type);
#else
		AddGradientCh(&oGradientChs, /*_T("ȫ��Ƶ��(ǰ����)")*/g_sLangTxt_Native_AllFreq, freAll_type);
#endif
	}
}

void CSttTestResourceBase::AddGradientSequence(CDataType &oGradientChs)
{
	oGradientChs.DeleteAll();
	long nVolGroupNum = m_oVolChRsListRef.GetCount()/3;
	long nCurrGroupNum = m_oCurChRsListRef.GetCount()/3;

	if (nVolGroupNum>0)
	{
		oGradientChs.AddNewValue(_T("U1-1"),_T("U1-1"),0);
		oGradientChs.AddNewValue(_T("U1-2"),_T("U1-2"),1);
		oGradientChs.AddNewValue(_T("U1-0"),_T("U1-0"),2);

// 		if (nVolGroupNum>1)  //zhouhj 2023.8.8 ������ݱ�ײ�ֻ֧��1��
// 		{
// 			oGradientChs.AddNewValue(_T("U2-1"),_T("U2-1"),3);
// 			oGradientChs.AddNewValue(_T("U2-2"),_T("U2-2"),4);
// 			oGradientChs.AddNewValue(_T("U2-0"),_T("U2-0"),5);
// 		}
	}

	if (nCurrGroupNum>0)
	{
		oGradientChs.AddNewValue(_T("I1-1"),_T("I1-1"),6);
		oGradientChs.AddNewValue(_T("I1-2"),_T("I1-2"),7);
		oGradientChs.AddNewValue(_T("I1-0"),_T("I1-0"),8);

// 		if (nCurrGroupNum>1)
// 		{
// 			oGradientChs.AddNewValue(_T("I2-1"),_T("I2-1"),9);
// 			oGradientChs.AddNewValue(_T("I2-2"),_T("I2-2"),10);
// 			oGradientChs.AddNewValue(_T("I2-0"),_T("I2-0"),11);
// 		}
	}
}

void CSttTestResourceBase::AddGradientLineVolt(CDataType &oGradientChs)
{
	oGradientChs.DeleteAll();
	long nVolGroupNum = m_oVolChRsListRef.GetCount()/3;//������2
	long nCurrGroupNum = m_oCurChRsListRef.GetCount()/3;

	if (nVolGroupNum>0)
	{
		oGradientChs.AddNewValue(_T("Uab1"),_T("Uab1"),LineVolt_vab1_type);
		oGradientChs.AddNewValue(_T("3U1-0"),_T("3U1-0"),LineVolt_v1_0_type);
// 		oGradientChs.AddNewValue(_T("Uab2"),_T("Uab2"),LineVolt_vab2_type);
// 		oGradientChs.AddNewValue(_T("3U2-0"),_T("3U2-0"),LineVolt_v2_0_type);


		/*if (nVolGroupNum>1)
		{
			oGradientChs.AddNewValue(_T("Uab2"),_T("Uab2"),3);
			oGradientChs.AddNewValue(_T("Ubc2"),_T("Ubc2"),4);
			oGradientChs.AddNewValue(_T("Uca2"),_T("Uca2"),5);
		}*/
	}

	CSttChResource *pIa1 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(0),*pIb1 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(1),*pIc1 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(2);
	CSttChResource *pIa2 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(3),*pIb2 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(4),*pIc2 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(5);

	AddGradientCh(&oGradientChs,pIa1,LineVolt_ia1_type);
	AddGradientCh(&oGradientChs,pIb1,LineVolt_ib1_type);
	AddGradientCh(&oGradientChs,pIc1,LineVolt_ic1_type);

// 	AddGradientCh(&oGradientChs,pIa2,LineVolt_ia2_type);
// 	AddGradientCh(&oGradientChs,pIb2,LineVolt_ib2_type);
// 	AddGradientCh(&oGradientChs,pIc2,LineVolt_ic2_type);
}

void CSttTestResourceBase::AddGradientChs_All(CDataType &oGradientChs)
{
	oGradientChs.DeleteAll();
	CSttChResource *pUa1 = (CSttChResource*)m_oVolChRsListRef.GetAtIndex(0),*pUb1 = (CSttChResource*)m_oVolChRsListRef.GetAtIndex(1),*pUc1 = (CSttChResource*)m_oVolChRsListRef.GetAtIndex(2);
	CSttChResource *pUa2 = (CSttChResource*)m_oVolChRsListRef.GetAtIndex(3),*pUb2 = (CSttChResource*)m_oVolChRsListRef.GetAtIndex(4),*pUc2 = (CSttChResource*)m_oVolChRsListRef.GetAtIndex(5);
	CSttChResource *pIa1 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(0),*pIb1 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(1),*pIc1 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(2);
	CSttChResource *pIa2 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(3),*pIb2 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(4),*pIc2 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(5);
	AddGradientCh(&oGradientChs,pIa1,ia1_type);
	AddGradientCh(&oGradientChs,pIb1,ib1_type);
	AddGradientCh(&oGradientChs,pIc1,ic1_type);
	AddGradientCh(&oGradientChs,pIa1,pIb1,iab1_type);
	AddGradientCh(&oGradientChs,pIb1,pIc1,ibc1_type);
	AddGradientCh(&oGradientChs,pIc1,pIa1,ica1_type);
	AddGradientCh(&oGradientChs,pIa1,pIb1,pIc1,iabc1_type);
	AddGradientCh_Plus(&oGradientChs,pIa1,pIb1,pIc1,iabcAdd_type);

	AddGradientCh(&oGradientChs,pIa2,ia2_type);
	AddGradientCh(&oGradientChs,pIb2,ib2_type);
	AddGradientCh(&oGradientChs,pIc2,ic2_type);
	AddGradientCh(&oGradientChs,pIa2,pIb2,pIc2,iabc2_type);
	AddGradientCh_Plus(&oGradientChs,pIa2,pIb2,pIc2,ia2b2c2Add_type);

	AddGradientCh(&oGradientChs,pUa1,va1_type);
	AddGradientCh(&oGradientChs,pUb1,vb1_type);
	AddGradientCh(&oGradientChs,pUc1,vc1_type);
	AddGradientCh(&oGradientChs,pUa1,pUb1,vab1_type);
	AddGradientCh(&oGradientChs,pUb1,pUc1,vbc1_type);
	AddGradientCh(&oGradientChs,pUc1,pUa1,vca1_type);
	AddGradientCh(&oGradientChs,pUa1,pUb1,pUc1,vabc1_type);
//	AddGradientCh_Plus(&oGradientChs,pUa1,pUb1,pUc1,vabcAdd_type);		//yyj 20210924 ��������Ҫ��

	AddGradientCh(&oGradientChs,pUa2,va2_type);
	AddGradientCh(&oGradientChs,pUb2,vb2_type);
	AddGradientCh(&oGradientChs,pUc2,vc2_type);
	AddGradientCh(&oGradientChs,pUa2,pUb2,pUc2,vabc2_type);
//	AddGradientCh_Plus(&oGradientChs,pUa2,pUb2,pUc2,va2b2c2Add_type);	//yyj 20210924 ��������Ҫ��

	AddGradientCh(&oGradientChs,pUa1,pUb1,pUc1,pUa2,pUb2,pUc2,vall_type);
	AddGradientCh(&oGradientChs,pIa1,pIb1,pIc1,pIa2,pIb2,pIc2,iall_type);

#ifdef STT_NOT_TESTCNTRFRAME
	AddGradientCh(&oGradientChs, _T("ȫ��Ƶ��"),freAll_type);
#else
	AddGradientCh(&oGradientChs, /*_T("ȫ��Ƶ��")*/g_sLangTxt_Gradient_AllFreq,freAll_type);
#endif
}

void CSttTestResourceBase::AddDcVoltageChs(CDataType &oDcVoltageChs)
{
	oDcVoltageChs.DeleteAll();
	POS pos = m_oVolChRsListRef.GetHeadPosition();
	CExBaseObject *pCurrObj = NULL;
	int index = 0;

	while(pos)
	{
		pCurrObj = m_oVolChRsListRef.GetNext(pos);
		if (g_oSystemParas.m_nHasDigital && (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC))
		{
			if (index < 6)//������������������ֱ���������ֱ(FT3),������ѹͨ����ȡ
			{
				oDcVoltageChs.AddNewValue(pCurrObj->m_strName,pCurrObj->m_strID,index);
			}
		}
		else
		{
		oDcVoltageChs.AddNewValue(pCurrObj->m_strName,pCurrObj->m_strID,index);
		}

		index++;
	}
}

void CSttTestResourceBase::AddDcCurrentChs(CDataType &oDcVoltageCurChs)
{
	oDcVoltageCurChs.DeleteAll();
	POS pos = m_oCurChRsListRef.GetHeadPosition();
	CExBaseObject *pCurrObj = NULL;
	int index = 0;

	while (pos)
	{
		pCurrObj = m_oCurChRsListRef.GetNext(pos);
		if (g_oSystemParas.m_nHasDigital && (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC))
		{
			if (index < 12)
			{
				oDcVoltageCurChs.AddNewValue(pCurrObj->m_strName, pCurrObj->m_strID, index);
			}
		}
		else
		{
		oDcVoltageCurChs.AddNewValue(pCurrObj->m_strName, pCurrObj->m_strID, index);
		}
		

		index++;
	}
}

void CSttTestResourceBase::AddDCOverLoadCurChs(CDataType &oDCOverLoadChs)
{
	oDCOverLoadChs.DeleteAll();

// 	oDCOverLoadChs.AddNewValue(_T("I1-1"),_T("I1-1"),0);
// 	oDCOverLoadChs.AddNewValue(_T("I1-2"),_T("I1-2"),1);
// 	oDCOverLoadChs.AddNewValue(_T("I1-3"),_T("I1-3"),2);
// 	oDCOverLoadChs.AddNewValue(_T("I2-1"),_T("I2-1"),3);
// 	oDCOverLoadChs.AddNewValue(_T("I2-2"),_T("I2-2"),4);
// 	oDCOverLoadChs.AddNewValue(_T("I2-3"),_T("I2-3"),5);
// 	oDCOverLoadChs.AddNewValue(_T("I3-1"),_T("I3-1"),6);
// 	oDCOverLoadChs.AddNewValue(_T("I3-2"),_T("I3-2"),7);
// 	oDCOverLoadChs.AddNewValue(_T("I3-3"),_T("I3-3"),8);
// 	oDCOverLoadChs.AddNewValue(_T("I4-1"),_T("I4-1"),9);
// 	oDCOverLoadChs.AddNewValue(_T("I4-2"),_T("I4-2"),10);
// 	oDCOverLoadChs.AddNewValue(_T("I4-3"),_T("I4-3"),11);

	POS pos = m_oCurChRsListRef.GetHeadPosition();
	CExBaseObject *pCurrObj = NULL;
	int index = 0;

	while (pos)
	{
		pCurrObj = m_oCurChRsListRef.GetNext(pos);
		if (index < 12)
		{
			oDCOverLoadChs.AddNewValue(pCurrObj->m_strName, pCurrObj->m_strID, index);
		}
		index++;
	}
}

void CSttTestResourceBase::AddACOverLoadCurChs(CDataType &oOverLoadChs)
{
	oOverLoadChs.DeleteAll();
// 	oOverLoadChs.AddNewValue(_T("Ia1"),_T("Ia1"),0);
// 	oOverLoadChs.AddNewValue(_T("Ib1"),_T("Ib1"),1);
// 	oOverLoadChs.AddNewValue(_T("Ic1"),_T("Ic1"),2);
	POS pos = m_oCurChRsListRef.GetHeadPosition();
	CExBaseObject *pCurrObj = NULL;
	int index = 0;

	while (pos)
	{
		pCurrObj = m_oCurChRsListRef.GetNext(pos);
		oOverLoadChs.AddNewValue(pCurrObj->m_strName, pCurrObj->m_strID, index);
		index++;
	}
}

void CSttTestResourceBase::AddGradientRemoteMeasChs(CDataType &oGradientChs)
{
	oGradientChs.DeleteAll();
	CSttChResource *pUa1 = (CSttChResource*)m_oVolChRsListRef.GetAtIndex(0),*pUb1 = (CSttChResource*)m_oVolChRsListRef.GetAtIndex(1),*pUc1 = (CSttChResource*)m_oVolChRsListRef.GetAtIndex(2);
	CSttChResource *pUa2 = (CSttChResource*)m_oVolChRsListRef.GetAtIndex(3),*pUb2 = (CSttChResource*)m_oVolChRsListRef.GetAtIndex(4),*pUc2 = (CSttChResource*)m_oVolChRsListRef.GetAtIndex(5);
	CSttChResource *pIa1 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(0),*pIb1 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(1),*pIc1 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(2);
	CSttChResource *pIa2 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(3),*pIb2 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(4),*pIc2 = (CSttChResource*)m_oCurChRsListRef.GetAtIndex(5);
	AddGradientCh(&oGradientChs,pUa1,va1_type);
	AddGradientCh(&oGradientChs,pUb1,vb1_type);
	AddGradientCh(&oGradientChs,pUc1,vc1_type);
	AddGradientCh(&oGradientChs,pUa1,pUb1,vab1_type);
	AddGradientCh(&oGradientChs,pUb1,pUc1,vbc1_type);
	AddGradientCh(&oGradientChs,pUc1,pUa1,vca1_type);
	AddGradientCh(&oGradientChs,pUa1,pUb1,pUc1,vabc1_type);
	AddGradientCh(&oGradientChs,pUa2,va2_type);

	AddGradientCh(&oGradientChs,pIa1,ia1_type);
	AddGradientCh(&oGradientChs,pIb1,ib1_type);
	AddGradientCh(&oGradientChs,pIc1,ic1_type);
	AddGradientCh(&oGradientChs,pIa1,pIb1,iab1_type);
	AddGradientCh(&oGradientChs,pIb1,pIc1,ibc1_type);
	AddGradientCh(&oGradientChs,pIc1,pIa1,ica1_type);
	AddGradientCh(&oGradientChs,pIa1,pIb1,pIc1,iabc1_type);
	AddGradientCh(&oGradientChs,pIa2,ia2_type);
}
void CSttTestResourceBase::AddGradientPower(CDataType &oGradientChs)
{
	oGradientChs.DeleteAll();
	long nVolGroupNum = m_oVolChRsListRef.GetCount()/3;
	long nCurrGroupNum = m_oCurChRsListRef.GetCount()/3;

	if (nCurrGroupNum>0)
	{
		oGradientChs.AddNewValue(_T("Sa(Pa,Qa)"),_T("Sa(Pa,Qa)"),0);
		oGradientChs.AddNewValue(_T("Sb(Pb,Qb)"),_T("Sb(Pb,Qb)"),1);
		oGradientChs.AddNewValue(_T("Sc(Pc,Qc)"),_T("Sc(Pc,Qc)"),2);
		oGradientChs.AddNewValue(_T("S(P,Q)"),_T("S(P,Q)"),3);
		oGradientChs.AddNewValue(_T("Pa"),_T("Pa"),4);
		oGradientChs.AddNewValue(_T("Pb"),_T("Pb"),5);
		oGradientChs.AddNewValue(_T("Pc"),_T("Pc"),6);
		oGradientChs.AddNewValue(_T("Pa,Pb,Pc"),_T("Pa,Pb,Pc"),7);
		oGradientChs.AddNewValue(_T("Qa"),_T("Qa"),8);
		oGradientChs.AddNewValue(_T("Qb"),_T("Qb"),9);
		oGradientChs.AddNewValue(_T("Qc"),_T("Qc"),10);
		oGradientChs.AddNewValue(_T("Qa,Qb,Qc"),_T("Qa,Qb,Qc"),11);
	}
}
void CSttTestResourceBase::AddGradientCh(CDataType *pGradientChSelList,const CString &strChName,int nChRealIndex)
{
	pGradientChSelList->AddNewValue(strChName,strChName,nChRealIndex);
}

long CSttTestResourceBase::GetChIndexLinevoltByChName(CString strName,BOOL bVol)
{
	long nChIndex = 0;
	CString strLeft,strRight;
	strRight = strName.Right(1);
	long nIndex = strName.Find(_T("-"));
	long nRight = CString_To_long(strRight);
	
	if (strName.Find(_T("U")) >= 0/*contains("U")*/)
	{
		strName.Replace(_T("3U"),_T(""));
		strLeft = strName.Left(1);
		long nLeft = CString_To_long(strLeft);
		if(nIndex==3)
		{
			nRight = nLeft;
		}
		nChIndex += ((nRight-1)*2);
		if (strName.Find(_T("-")) >= 0/*contains("-")*/)
		{
			nChIndex++;
		}
	} 
	else 
	{
		nChIndex += ((nRight-1)*3);
		 if (strName.Find(_T("b")) >= 0/*contains("b")*/)
		{
			nChIndex++;
		}
		else if (strName.Find(_T("c")) >= 0/*contains("c")*/)
			nChIndex+=2;	
	}

	return nChIndex;
}

long CSttTestResourceBase::GetChIndexSequenceByChName(CString strName,BOOL bVol)
{
	long nChIndex = 0;
	strName.Replace(_T("U"),_T(""));
	strName.Replace(_T("I"),_T(""));
	long nIndex = strName.Find(_T("-"));

	if (nIndex<0)
	{
		return 0;
	}

	if (!bVol)
	{
		nChIndex = 6;
	}

	CString strLeft,strRight;
	strLeft = strName.Left(nIndex);
	strRight = strName.Mid(nIndex+1);
	long nLeft = CString_To_long(strLeft);
	long nRight = CString_To_long(strRight);

	nChIndex += ((nLeft-1)*3);

	if (nRight == 2)
	{
		nChIndex++;
	}
	else if (nRight == 0)
	{
		nChIndex += 2;
	}
	return nChIndex;
}
long CSttTestResourceBase::GetChIndexPowerByChName(CString strName,BOOL bVol)
{
	long nChIndex = 0;

    //if (strName.contains(_T("a")))
	if (strName.Find(_T("a")) >= 0)
    {
        nChIndex = 0;
    } 
    //else if (strName.contains(_T("b")))
	else if (strName.Find(_T("b")) >= 0)
    {
        nChIndex = 1;
    }
	//else if (strName.contains(_T("c")))
	else if (strName.Find(_T("c")) >= 0)
	{
		nChIndex = 2;
	}
	else
	{
        nChIndex = 3;//���⴦��S(P,Q)
	}

	return nChIndex;
}

void CSttTestResourceBase::GetCurrVolGroupNum(long &nCurrGroupNum,long &nVolGroupNum)
{
	POS pos = m_oListGroups.GetHeadPosition();
	CSttChGroupResource *pObj = NULL;
	nCurrGroupNum = 0;
	nVolGroupNum = 0;

	while(pos)
	{
		pObj = (CSttChGroupResource*)m_oListGroups.GetNext(pos);

		if (pObj->HasVolCh())
		{
			nVolGroupNum++;
		}

		if (pObj->HasCurCh())
		{
			nCurrGroupNum++;
		}
	}
}

void CSttTestResourceBase::AddGradientCh(CDataType *pGradientChSelList,CSttChResource *pCh,int nChRealIndex)
{
	if (pCh == NULL)
	{
		return;
	}

	if (!pCh->m_bHasMapHdRs)
	{
		return;
	}

	pGradientChSelList->AddNewValue(pCh->m_strName,pCh->m_strName,nChRealIndex);
}

void CSttTestResourceBase::AddGradientCh(CDataType *pGradientChSelList,CSttChResource *pCh1,CSttChResource *pCh2,int nChRealIndex)
{
	if ((pCh1 == NULL)||(pCh2 == NULL))
	{
		return;
	}

	CString strChName;
	strChName.Format(_T("%s,%s"),pCh1->m_strName.GetString(),pCh2->m_strName.GetString());
	pGradientChSelList->AddNewValue(strChName,strChName,nChRealIndex);
}

void CSttTestResourceBase::AddGradientCh(CDataType *pGradientChSelList,CSttChResource *pCh1,CSttChResource *pCh2,CSttChResource *pCh3,int nChRealIndex)
{
	if  ((pCh1 == NULL)||(pCh2 == NULL))//���ֻ�е�һ��ͨ��,��ͨ���仯��ģʽ�Ѿ�����,��ʱ�����ٴ���,����ǰ������ͨ�������ڲ�������
	{
		return;
	}

	if ((!pCh1->m_bHasMapHdRs)||(!pCh2->m_bHasMapHdRs))
	{
		return;
	}

	CDvmData *pComboxCh = NULL;
	CString strTmp;

	if ((pCh3 == NULL)||(!pCh3->m_bHasMapHdRs))
	{
		strTmp.Format(_T("%s,%s"),pCh1->m_strName.GetString(),pCh2->m_strName.GetString());
		pComboxCh = (CDvmData*)pGradientChSelList->FindByID(strTmp);

		if (pComboxCh == NULL)
		{
			pGradientChSelList->AddNewValue(strTmp,strTmp,nChRealIndex);
		}
	} 
	else
	{
		strTmp.Format(_T("%s,%s,%s"),pCh1->m_strName.GetString(),pCh2->m_strName.GetString(),pCh3->m_strName.GetString());
		pGradientChSelList->AddNewValue(strTmp,strTmp,nChRealIndex);
	}
}

void CSttTestResourceBase::AddGradientCh_Plus(CDataType *pGradientChSelList,CSttChResource *pCh1,CSttChResource *pCh2,CSttChResource *pCh3,int nChRealIndex)
{
	if  ((pCh1 == NULL)||(pCh2 == NULL))//���ֻ�е�һ��ͨ��,��ͨ���仯��ģʽ�Ѿ�����,��ʱ�����ٴ���,����ǰ������ͨ�������ڲ�������
	{
		return;
	}

	if ((!pCh1->m_bHasMapHdRs)||(!pCh2->m_bHasMapHdRs))
	{
		return;
	}

	CDvmData *pComboxCh = NULL;
	CString strTmp;

	if ((pCh3 == NULL)||(!pCh3->m_bHasMapHdRs))
	{
		strTmp.Format(_T("%s+%s"),pCh1->m_strName.GetString(),pCh2->m_strName.GetString());
		pComboxCh = (CDvmData*)pGradientChSelList->FindByID(strTmp);

		if (pComboxCh == NULL)
		{
			pGradientChSelList->AddNewValue(strTmp,strTmp,nChRealIndex);
		}
	} 
	else
	{
		strTmp.Format(_T("%s+%s+%s"),pCh1->m_strName.GetString(),pCh2->m_strName.GetString(),pCh3->m_strName.GetString());
		pGradientChSelList->AddNewValue(strTmp,strTmp,nChRealIndex);
	}
}

void CSttTestResourceBase::AddGradientCh(CDataType *pGradientChSelList,CSttChResource *pCh1,CSttChResource *pCh2,CSttChResource *pCh3,
										 CSttChResource *pCh4,CSttChResource *pCh5,CSttChResource *pCh6,int nChRealIndex)
{
	if  ((pCh1 == NULL)||(pCh2 == NULL)||(pCh3 == NULL)||(pCh4 == NULL))//���ֻ�е�3ͨ��,3ͨ���仯��ģʽ�Ѿ�����,��ʱ�����ٴ���,����ǰ��4��ͨ�������ڲ�������
	{
		return;
	}

	if  ((!pCh1->m_bHasMapHdRs)||(!pCh2->m_bHasMapHdRs)||(!pCh3->m_bHasMapHdRs)||(!pCh4->m_bHasMapHdRs))//���ֻ�е�3ͨ��,3ͨ���仯��ģʽ�Ѿ�����,��ʱ�����ٴ���,����ǰ��4��ͨ�������ڲ�������
	{
		return;
	}

	CString strTmp;

	if (pCh5 == NULL)
	{
		strTmp.Format(_T("%s,%s,%s,%s"),pCh1->m_strName.GetString(),pCh2->m_strName.GetString(),pCh3->m_strName.GetString(),pCh4->m_strName.GetString());
	}
	else if (!pCh5->m_bHasMapHdRs)
	{
		strTmp.Format(_T("%s,%s,%s,%s"),pCh1->m_strName.GetString(),pCh2->m_strName.GetString(),pCh3->m_strName.GetString(),pCh4->m_strName.GetString());
	}
	else if (pCh6 == NULL)
	{
		strTmp.Format(_T("%s,%s,%s,%s,%s"),pCh1->m_strName.GetString(),pCh2->m_strName.GetString(),pCh3->m_strName.GetString(),pCh4->m_strName.GetString(),pCh5->m_strName.GetString());
	}
	else if (!pCh6->m_bHasMapHdRs)
	{
		strTmp.Format(_T("%s,%s,%s,%s,%s"),pCh1->m_strName.GetString(),pCh2->m_strName.GetString(),pCh3->m_strName.GetString(),pCh4->m_strName.GetString(),pCh5->m_strName.GetString());
	}
	else
	{
		strTmp.Format(_T("%s,%s,%s,%s,%s,%s"),pCh1->m_strName.GetString(),pCh2->m_strName.GetString(),pCh3->m_strName.GetString(),pCh4->m_strName.GetString(),pCh5->m_strName.GetString(),pCh6->m_strName.GetString());
	}

	pGradientChSelList->AddNewValue(strTmp,strTmp,nChRealIndex);
}

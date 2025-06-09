#include "StdAfx.h"
#include "SttMacroChannels.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSttMacroChannel::CSttMacroChannel(void)
{
	m_oHisMagBuf.AllocMemBuffer(STT_HISDATA_MEMBUFFER_MAX_NUM);
	m_oHisDataBuf.AllocMemBuffer(STT_HISDATA_MEMBUFFER_MAX_NUM);	//yyj add 2021-08-25
}

CSttMacroChannel::~CSttMacroChannel(void)
{
	m_oHisMagBuf.FreeMemBuffer();
	m_oHisDataBuf.FreeMemBuffer();		//yyj add 2021-08-25
}

void CSttMacroChannel::ResetDatas()
{
	m_oHisDataBuf.ResetOffsetDataFillBeginPosition();
	m_oRtDataCh.m_fMag = 0;
	m_oRtDataCh.m_fAng = 0;
	m_oRtDataCh.m_fFreq = 50.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CMacroChGroup::CMacroChGroup(void)
{
}

CMacroChGroup::~CMacroChGroup(void)
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSttMacroChannels::CSttMacroChannels(void)
{
	m_oHisTimesBuf.AllocMemBuffer(STT_HISDATA_MEMBUFFER_MAX_NUM);
	m_oHisRealTimesBuf.AllocMemBuffer(STT_HISDATA_MEMBUFFER_MAX_NUM);
	m_oUfCh.m_strID = STT_MACRO_ID_FAULT_CH_VOL;
	m_oIfCh.m_strID = STT_MACRO_ID_FAULT_CH_CUR;
	m_oZ_Fault.m_strID = STT_MACRO_ID_FAULT_CH_Z;
	m_oUfCh.m_strName = STT_MACRO_ID_FAULT_CH_VOL;
	m_oIfCh.m_strName = STT_MACRO_ID_FAULT_CH_CUR;
	m_oZ_Fault.m_strName = STT_MACRO_ID_FAULT_CH_Z;
// 	m_dZImp = 0;
// 	m_dZAngle = 0;
}

CSttMacroChannels::~CSttMacroChannels(void)
{
	m_oHisTimesBuf.FreeMemBuffer();
	m_oHisRealTimesBuf.FreeMemBuffer();
	ClearAllChs();

}

void CSttMacroChannels::InitGroup()
{
	if (m_oListGroups.GetCount()>0)//如果之前分组还在，清除分组
	{
		ClearGroups();
	}

	CMacroChGroup *pGroup = NULL;
	CExBaseList oVolListRef,oCurListRef;
	oVolListRef.Append(&m_oVolChListRef);
	oCurListRef.Append(&m_oCurChListRef);

	if ((oVolListRef.GetCount() <= 4)&&(oVolListRef.GetCount()>0))//如果只有4组，则放入一起
	{
		pGroup = new CMacroChGroup;
		pGroup->m_strID = _T("Group1");
		pGroup->Append(&oVolListRef);
		m_oListGroups.AddNewChild(pGroup);
		oVolListRef.RemoveAll();
	}

	if ((oCurListRef.GetCount() <= 4)&&(oCurListRef.GetCount()>0))//如果只有4组，则放入一起
	{
		pGroup = (CMacroChGroup*)m_oListGroups.FindByID(_T("Group1"));

		if (pGroup == NULL)
		{
			pGroup = new CMacroChGroup;
			pGroup->m_strID = _T("Group1");
			m_oListGroups.AddNewChild(pGroup);
		}
		
		pGroup->Append(&oCurListRef);
		oCurListRef.RemoveAll();
	}

	long nGroupIndex = 0,nChIndex = 0;
	POS pos = oVolListRef.GetHeadPosition();
	CSttMacroChannel *pMacroCh = NULL;
	CString strTmp;

	while(pos)//电压通道如果总数量大于4，则进行每3个一组进行分组,且此时分组链表必须要new
	{
		pMacroCh = (CSttMacroChannel *)oVolListRef.GetNext(pos);

		if (nChIndex%3 == 0)
		{
			nGroupIndex++;
			strTmp.Format(_T("Group%ld"),nGroupIndex);
			pGroup = (CMacroChGroup*)m_oListGroups.FindByID(strTmp);

			if (pGroup == NULL)
			{
				pGroup = new CMacroChGroup;
				m_oListGroups.AddNewChild(pGroup);
			}
		}

		pGroup->AddTail(pMacroCh);
		nChIndex++;
	}

	nGroupIndex = 0,nChIndex = 0;
	pos = oCurListRef.GetHeadPosition();//电流通道如果总数量大于4，则进行每3个一组进行分组，需要先查找该链表是否存在，如果不存在，则new

	while(pos)
	{
		pMacroCh = (CSttMacroChannel *)oCurListRef.GetNext(pos);

		if (nChIndex%3 == 0)
		{
			nGroupIndex++;
			strTmp.Format(_T("Group%ld"),nGroupIndex);
			pGroup = (CMacroChGroup*)m_oListGroups.FindByID(strTmp);

			if (pGroup == NULL)
			{
				pGroup = new CMacroChGroup;
				m_oListGroups.AddNewChild(pGroup);
			}
		}
		pGroup->AddTail(pMacroCh);
		nChIndex++;
	}

	oVolListRef.RemoveAll();
	oCurListRef.RemoveAll();
}

void CSttMacroChannels::ClearGroups()
{
	POS pos = m_oListGroups.GetHeadPosition();
	CMacroChGroup *pGroup = NULL;

	while(pos)
	{
		pGroup = (CMacroChGroup *)m_oListGroups.GetNext(pos);
		pGroup->RemoveAll();
	}

	m_oListGroups.DeleteAll();
}

void CSttMacroChannels::ClearAllChs()
{
	ClearHisDatas();
	ClearGroups();
	DeleteAll();
	m_oCurChListRef.RemoveAll();
	m_oVolChListRef.RemoveAll();
	
}

void CSttMacroChannels::ClearHisDatas()
{
	m_oHisTimesBuf.ResetOffsetDataFillBeginPosition();
	m_oHisRealTimesBuf.ResetOffsetDataFillBeginPosition();
	m_oIfCh.ResetDatas();
// 	m_oIfCh.m_oHisDataBuf.ResetOffsetDataFillBeginPosition();	
// 	m_oIfCh.m_oRtDataCh.m_fMag = 0;
// 	m_oIfCh.m_oRtDataCh.m_fAng = 0;  
// 	m_oIfCh.m_oRtDataCh.m_fFreq = 50.0f;
	m_oUfCh.ResetDatas();
	m_oZ_Fault.ResetDatas();
// 	m_oUfCh.m_oHisDataBuf.ResetOffsetDataFillBeginPosition();
// 	m_oUfCh.m_oRtDataCh.m_fMag = 0;
// 	m_oUfCh.m_oRtDataCh.m_fAng = 0;
// 	m_oUfCh.m_oRtDataCh.m_fFreq = 50.0f;

	POS pos = GetHeadPosition();
	CSttMacroChannel *pMacroCh = NULL;

	while(pos)
	{
		pMacroCh = (CSttMacroChannel *)GetNext(pos);
//		pMacroCh->m_oHisMagBuf.ResetOffsetDataFillBeginPosition();	//yyj delete 2021-08-25
		pMacroCh->m_oHisDataBuf.ResetOffsetDataFillBeginPosition();	//yyj add 2021-08-25

		pMacroCh->m_oRtDataCh.m_fMag = 0;	//yyj clear cur data 2021-11-05
		pMacroCh->m_oRtDataCh.m_fAng = 0;   //yyj clear cur data 2021-11-05
		pMacroCh->m_oRtDataCh.m_fFreq = 50; //yyj clear cur data 2021-11-05
	}
}

CSttMacroChannel* CSttMacroChannels::AddNewCh(const CString &strName,const CString &strID,CSttChMap *pHdMaps)
{
	CSttMacroChannel* pCh = new CSttMacroChannel;
	pCh->m_strName = strName;
	pCh->m_strID = strID;
	pCh->m_pHdMaps = pHdMaps;

	if (pCh->m_strID.Find(_T("U")) == 0)
	{
		pCh->m_nChannelType = STT_MACRO_CH_TYPE_VOL;
		m_oVolChListRef.AddTail(pCh);
	} 
	else
	{
		pCh->m_nChannelType = STT_MACRO_CH_TYPE_CUR;
		m_oCurChListRef.AddTail(pCh);
	}

	AddNewChild(pCh);
	return pCh;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSttBinChlMngr::CSttBinChlMngr()
{

}

CSttBinChlMngr::~CSttBinChlMngr()
{

}
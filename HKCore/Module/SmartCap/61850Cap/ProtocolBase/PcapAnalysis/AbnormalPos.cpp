#include "StdAfx.h"
#include "AbnormalPos.h"

CAbnormalPos::CAbnormalPos(void)
{
	m_strMacDes  = _T("");
	m_nAllNum  = 0;
	m_nGooseBitChangePos = -1;
}

CAbnormalPos::~CAbnormalPos(void)
{
}

CString CAbnormalPos::GetInfor()
{
	CString strResult = _T("");
	// 	if (m_AbnormalGlobalPos.size()>0)
	// 	{
	// 		CString strN;
	// 		strN.Format(_T("%d"),m_AbnormalGlobalPos.size());
	// 		strResult += _T("�쳣�ܼ�:");
	// 		strResult +=strN;
	// 		strResult +=_T("\r\n");
	// 	}

	if (m_LostPointGlobalPos.size()  >  0)
	{
		CString strN;
		strN.Format(_T("%d"),  m_LostPointGlobalPos.size());
		strResult += _T("��֡����:");
		strResult +=  strN;
		strResult+=_T("\r\n");

		//strResult += _T("  ");
	}

	if (m_SetpOutGlobalPos.size()  >  0)
	{
		CString strN;
		strN.Format(_T("%d"),  m_SetpOutGlobalPos.size());
		strResult += _T("ʧ��:");
		strResult +=  strN;
		strResult+=_T("\r\n");
		//strResult += _T("  ");
	}
	if (m_ErrorNumGlobalPos.size()  >  0)
	{
		CString strN;
		strN.Format(_T("%d"),  m_ErrorNumGlobalPos.size());
		strResult +=  _T("��������:");
		strResult +=  strN;
		strResult+=_T("\r\n");
		//strResult +=  _T("  ");
	}

	if (m_LostSmSycGlobalPos.size()  >  0)
	{
		CString strN;
		strN.Format(_T("%d"),m_LostSmSycGlobalPos.size());
		strResult   +=  _T("ͬ���źŶ�ʧ:");
		strResult   +=  strN;
		strResult+=_T("\r\n");
		//strResult   +=  _T("  ");
	}

	if (m_SMVFactorChangeGlobalPos.size()  >  0)
	{
		CString strN;
		strN.Format(_T("%d"),  m_SMVFactorChangeGlobalPos.size());
		strResult   +=  _T("Ʒ�ʸı�:");
		strResult  += strN;	
		strResult+=_T("\r\n");
		//strResult  += _T("  ");
	}

	if (m_SMVFlyPointGlobalPos.size()  >  0)
	{
		CString strN;
		strN.Format(_T("%d"),m_SMVFlyPointGlobalPos.size());
		strResult += _T("�ɵ�:");
		strResult +=strN;
		strResult +=_T("�����쳣:");
	}

	if (m_GooseBitChangeGlobalPos.size()  >  0)
	{
		CString strN;
		strN.Format(_T("%d"),m_GooseBitChangeGlobalPos.size());
		strResult += _T("��λ:");
		strResult +=strN;
		strResult+=_T("\r\n");
		//strResult +=_T("  ");
	}

	if(m_GooseClockAbnormalGlobalPos.size() > 0)
	{
		CString strN;
		strN.Format(_T("%d"),m_GooseClockAbnormalGlobalPos.size());
		strResult += _T("ʱ���쳣:");
		strResult +=strN;
		strResult+=_T("\r\n");
		//strResult +=_T("  ");
	}

	if(m_GooseClockErrorGlobalPos.size()  >  0)
	{
		CString strN;
		strN.Format(_T("%d"),m_GooseClockErrorGlobalPos.size());
		strResult += _T("ʱ�� fault:");
		strResult +=strN;
		strResult+=_T("\r\n");
		//strResult +=_T("  ");
	}

	if(m_GooseClockUnSyncGlobalPos.size()  > 0)
	{
		CString strN;
		strN.Format(_T("%d"),m_GooseClockUnSyncGlobalPos.size());
		strResult += _T("δͬ��:");
		strResult +=strN;
		strResult+=_T("\r\n");
		//strResult +=_T("  ");
	}

	if (m_GooseVitrualBitChangeAndCountErrorGlobalPos.size()  >  0)
	{
		CString strN;
		strN.Format(_T("%d"),m_GooseVitrualBitChangeAndCountErrorGlobalPos.size());
		strResult += _T("���λ:");
		strResult +=strN;
		strResult+=_T("\r\n");
		//strResult +=_T("  ");
	}

	if (m_GooseLostSTNumGlobalPos.size()  >  0)
	{
		CString strN;
		strN.Format(_T("%d"),m_GooseLostSTNumGlobalPos.size());
		strResult += _T("STNum ��ʧ:");
		strResult +=strN;
		strResult+=_T("\r\n");
		//	strResult +=_T("  ");
	}

	if (m_GooseBitChangeAndCountErrorGlobalPos.size()  >  0)
	{
		CString strN;
		strN.Format(_T("%d"),  m_GooseBitChangeAndCountErrorGlobalPos.size());
		strResult += _T("װ������:");
		strResult +=strN;
		strResult+=_T("\r\n");
		//strResult +=_T("  ");
	}

	if (m_GooseSqNumRepeatGlobalPos.size()  >  0)
	{
		CString strN;
		strN.Format(_T("%d"),  m_GooseSqNumRepeatGlobalPos.size());
		strResult += _T("SqNum �ظ�:");
		strResult +=strN;
		strResult+=_T("\r\n");
		//strResult +=_T("  ");
	}

	if (m_GooseLostSqNumGlobalPos.size()  >  0)
	{
		CString strN;
		strN.Format(_T("%d"),m_GooseLostSqNumGlobalPos.size());
		strResult += _T("SqNum ��ʧ:");
		strResult +=strN;
		strResult+=_T("\r\n");
		//strResult +=_T("  ");
	}

	return strResult;
}
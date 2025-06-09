#include "SttBinRecord_RT.h"
#include "QApplication"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceRcdCh.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceRecord.h"
#include "../../../../Module/SmartCap/XSttCap_61850.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "SttBinRecordDefine.h"
#include "../../XLangResource_Native.h"

CSttBinRecord_RT::CSttBinRecord_RT(QWidget* pparent) :CSttIecChsGridBase(pparent)
{
	m_pIecRcdFuncWidget = this;
	installEventFilter(this);
	m_strPixPathOpen = _P_GetResourcePath();
	m_strPixPathOpen += _T("switch_open.png");
	m_strPixPathClose = _P_GetResourcePath();
	m_strPixPathClose += _T("switch_close.png");
}


CSttBinRecord_RT::~CSttBinRecord_RT()
{
}

void CSttBinRecord_RT::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	if (pCapDevice == NULL)
	{
		return;
	}
	m_pCapDevice = pCapDevice;
	CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();
	ShowDatas(pDvmDataset);
}

void CSttBinRecord_RT::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	pXSttCap_61850->UpdateDvmDeviceDatas();

	UpdateDatas();
}

void CSttBinRecord_RT::Release()
{
	delete this;
}

void CSttBinRecord_RT::mousePressEvent(QMouseEvent *event)
{
	m_oTickCount.Enter();
	// 	QExBaseListGridBase::mousePressEvent(event);
	if (m_bRunning)
	{
		QExBaseListGridBase::mousePressEvent(event);
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick, event->pos(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
	QApplication::postEvent(this, pEvent);
	QExBaseListGridBase::mousePressEvent(event);
}

void CSttBinRecord_RT::mouseReleaseEvent(QMouseEvent *event)
{
	mouseReleaseEventBase(event);
	QExBaseListGridBase::mouseReleaseEvent(event);
}

bool CSttBinRecord_RT::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = FALSE;
		return  true;
	}

	return QExBaseListGridBase::eventFilter(obj, event);
}

CExBaseList* CSttBinRecord_RT::GetCurrCapDevice()
{
	return (CExBaseList*)m_pCapDevice;
}

void CSttBinRecord_RT::InitGridTitle()
{
	CString astrGridTitle[5] = { /*_T("通道描述")*/g_sLangTxt_IEC_ChDescription, /*_T("通道类型")*/g_sLangTxt_IEC_ChType, /*_T("通道映射")*/g_sLangTxt_IEC_ChMaps, /*_T("幅值")*/g_sLangTxt_Native_Amplitude, /*_T("相位")*/g_sLangTxt_Native_Phase };
	int iGridWidth[5] = { 200, 150, 150, 150, 150 };
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, STT_BINRECORD_ID_NFIVE);
}

void CSttBinRecord_RT::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow /*= TRUE*/)
{
	ASSERT(pData)
	CDvmData *pChData = (CDvmData*)pData;
	Show_StaticString(pData, nRow, STT_BINRECORD_ID_NZERO, &pChData->m_strName);//通道描述
	showEType(pData, nRow);
//	Show_StaticString(pData, nRow, 1, &pChData->m_strDataType);//通道类型
	showChMap(pData, nRow);//通道映射
	showChValue(pData, nRow);//数值
	ShowAttrValue(pChData, nRow, STT_BINRECORD_ID_NFOUR, _T("$ang"), STT_BINRECORD_ID_NTHREE);
	showChfValue(pData, nRow);
	nRow++;
}

//2024-10-12zhouyangyong 新增用于解决有效值不刷新的问题
void CSttBinRecord_RT::UpdateData(CExBaseObject *pData, int nRow)
{
	ShowData(pData, nRow);
}

void CSttBinRecord_RT::showEType(CExBaseObject *pData, int& nRow)
{
	CCapDeviceRecord *pCapDevice = (CCapDeviceRecord*)m_pCapDevice;
	CCapDeviceRcdCh *pCh = (CCapDeviceRcdCh*)pCapDevice->GetAtIndex(nRow);
	if (pCh->m_nEType == STT_BINRECORD_ID_NZERO)
	{
		Show_StaticString(pData, nRow, STT_BINRECORD_ID_NONE, g_sLangTxt_BinRecord_Invalid);//无效
	}
	else if (pCh->m_nEType == STT_BINRECORD_ID_NONE)
	{
		Show_StaticString(pData, nRow, STT_BINRECORD_ID_NONE, _T("电压"));
	}
	else if (pCh->m_nEType == STT_BINRECORD_ID_NTWO)
	{
		Show_StaticString(pData, nRow, STT_BINRECORD_ID_NONE, _T("电流"));
	}
	else if (pCh->m_nEType == STT_BINRECORD_ID_NTHREE)
	{
		Show_StaticString(pData, nRow, STT_BINRECORD_ID_NONE, g_sLangTxt_BinRecord_BinPassive);
	}
	else if (pCh->m_nEType == STT_BINRECORD_ID_NFOUR)
	{
		Show_StaticString(pData, nRow, STT_BINRECORD_ID_NONE, g_sLangTxt_BinRecord_BinActive);
	}
}

void CSttBinRecord_RT::showChMap(CExBaseObject *pData, int& nRow)
{
	CCapDeviceRecord *pCapDevice = (CCapDeviceRecord*)m_pCapDevice;
	CCapDeviceRcdCh *pCh = (CCapDeviceRcdCh*)pCapDevice->GetAtIndex(nRow);
	if (pCh->m_nEType != STT_BINRECORD_ID_NZERO && pCh->m_nEType != STT_BINRECORD_ID_NONE)
	{
		Show_StaticString(pData, nRow, STT_BINRECORD_ID_NTWO, _T("--"));
	}
	else if (pCh->m_nChAngType == STT_BINRECORD_ID_NZERO)
	{
		Show_StaticString(pData, nRow, STT_BINRECORD_ID_NTWO, /*_T("A相")*/g_sLangTxt_Aphase);
	}
	else if (pCh->m_nChAngType == STT_BINRECORD_ID_NONE)
	{
		Show_StaticString(pData, nRow, STT_BINRECORD_ID_NTWO, /*_T("B相")*/g_sLangTxt_Bphase);
	}
	else if (pCh->m_nChAngType == STT_BINRECORD_ID_NTWO)
	{
		Show_StaticString(pData, nRow, STT_BINRECORD_ID_NTWO, /*_T("C相")*/g_sLangTxt_Cphase);
	}
	else if (pCh->m_nChAngType == STT_BINRECORD_ID_NTHREE)
	{
		Show_StaticString(pData, nRow, STT_BINRECORD_ID_NTWO, /*_T("零序")*/g_sLangTxt_Iec_ZeroSeq);
	}
}

void CSttBinRecord_RT::showChValue(CExBaseObject *pData, int& nRow)
{
	CDvmData *pChData = (CDvmData*)pData;
	CCapDeviceRecord *pCapDevice = (CCapDeviceRecord*)m_pCapDevice;
	CCapDeviceRcdCh *pCh = (CCapDeviceRcdCh*)pCapDevice->GetAtIndex(nRow);
	if (pCh->m_nEType == STT_BINRECORD_ID_NONE || pCh->m_nEType == STT_BINRECORD_ID_NTWO)//记录类型是电压或者电流的时候显示幅值
	{
		ShowAttrValue(pChData, nRow, STT_BINRECORD_ID_NTHREE, _T("$mag"), STT_BINRECORD_ID_NTHREE);
	}
	else if (pCh->m_nEType == STT_BINRECORD_ID_NTHREE)//记录类型是开关量的时候显示0/1
	{
		BOOL bHasSetItem = FALSE;
		QGV_ITEM *pItem = AddItem(nRow, STT_BINRECORD_ID_NTHREE, _T(""), bHasSetItem);
		pItem->nDataType = QT_GVET_NOEDIT;
		pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		pItem->setFlags((Qt::ItemIsEnabled));

		PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, (CString*)NULL, pData, NULL, NULL);
		pItem->lParam = (LPARAM)pVCellData;
		pVCellData->nVt = VCD_STRING;

		if (!bHasSetItem)
		{
			setItem(nRow, STT_BINRECORD_ID_NTHREE, pItem);
		}
		//无源开关量电压值<6.23时为闭合
		if (pCh->m_fValue < STT_BINRECORD_ID_NSIXDOTTWENTYTHREE)
		{
			QPixmap pPixMap(m_strPixPathOpen);
			pItem->setIcon(QIcon(pPixMap));
		}
		else
		{
			QPixmap pPixMap(m_strPixPathClose);
			pItem->setIcon(QIcon(pPixMap));
		}
	}
	else if (pCh->m_nEType == STT_BINRECORD_ID_NFOUR)//有源开关量
	{
		//有源开关量大于设置的门槛值时为闭合
		BOOL bHasSetItem = FALSE;
		QGV_ITEM *pItem = AddItem(nRow, STT_BINRECORD_ID_NTHREE, _T(""), bHasSetItem);
		pItem->nDataType = QT_GVET_NOEDIT;
		pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		pItem->setFlags((Qt::ItemIsEnabled));

		PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, (CString*)NULL, pData, NULL, NULL);
		pItem->lParam = (LPARAM)pVCellData;
		pVCellData->nVt = VCD_STRING;

		if (!bHasSetItem)
		{
			setItem(nRow, STT_BINRECORD_ID_NTHREE, pItem);
		}
		if (pCh->m_fValue > pCh->m_fSwitchVolt)
		{
			QPixmap pPixMap(m_strPixPathOpen);
			pItem->setIcon(QIcon(pPixMap));
		}
		else
		{
			QPixmap pPixMap(m_strPixPathClose);
			pItem->setIcon(QIcon(pPixMap));
		}
	}
}

void CSttBinRecord_RT::showChfValue(CExBaseObject *pData, int& nRow)
{
	CCapDeviceRecord *pCapDevice = (CCapDeviceRecord*)m_pCapDevice;
	CCapDeviceRcdCh *pCh = (CCapDeviceRcdCh*)pCapDevice->GetAtIndex(nRow);
	Show_Float(pData, nRow, 5, 3, &pCh->m_fValue);
}

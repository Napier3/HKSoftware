#include "SttIecSmvGrid_EffecValue.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include <QApplication>

CSttIecSmvGrid_EffecValue::CSttIecSmvGrid_EffecValue(QWidget* pparent):CSttIecChsGridBase(pparent)
{
	m_pIecRcdFuncWidget = this;

// 	m_bRunning = FALSE;
	installEventFilter(this);
	LoadRefChPic();

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("长按通道进行相位基准选择"));
}

CSttIecSmvGrid_EffecValue::~CSttIecSmvGrid_EffecValue()
{

}

void CSttIecSmvGrid_EffecValue::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	CCapDeviceSmvBase *pCapDeviceSmvBase = NULL;

	if (m_pCapDevice != NULL)
	{
		pCapDeviceSmvBase = (CCapDeviceSmvBase*)m_pCapDevice;
		SetItemPic_RefCh(pCapDeviceSmvBase->m_nRefChIndex,0,FALSE);
	}

	m_pCapDevice = pCapDevice;
	CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();
	ShowDatas(pDvmDataset);

	if (m_pCapDevice != NULL)
	{
		pCapDeviceSmvBase = (CCapDeviceSmvBase*)m_pCapDevice;
		SetItemPic_RefCh(pCapDeviceSmvBase->m_nRefChIndex,0);
	}
}

void CSttIecSmvGrid_EffecValue::Release()
{
	delete this;
}

void CSttIecSmvGrid_EffecValue::InitGridTitle()
{
	CString astrGridTitle[4];
	xlang_GetLangStrByFile(astrGridTitle[0], _T("Native_Channel"));
	xlang_GetLangStrByFile(astrGridTitle[1],_T("Native_Amplitude"));
	xlang_GetLangStrByFile(astrGridTitle[2], _T("Native_Angle"));
	xlang_GetLangStrByFile(astrGridTitle[3], _T("Native_Freq"));
	//= {"通道", "幅值","相位",_T("频率")};
	int iGridWidth[4]={400, 150, 100, 100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 4);

	connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(slot_doubleClicked(int,int)));
}

void CSttIecSmvGrid_EffecValue::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pChData = (CDvmData*)pData;

	if (bInsertRow)
	{
		insertRow(NULL);
	}

	Show_StaticString(pData, nRow, 0, &pChData->m_strName);
	ShowAttrValue(pChData, nRow, 1, _T("$mag"),3);
	ShowAttrValue(pChData, nRow, 2, _T("$ang"), 3);
	ShowAttrValue(pChData, nRow, 3, _T("$freq"), 3);

	nRow++;
}


void CSttIecSmvGrid_EffecValue::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	//pXCapPkgBufferMngr->LogBufferPos();
	pXSttCap_61850->UpdateDvmDeviceDatas();

	UpdateDatas();
}

CExBaseList* CSttIecSmvGrid_EffecValue::GetCurrCapDevice()
{
	return (CExBaseList*)m_pCapDevice;
}

void CSttIecSmvGrid_EffecValue::UpdateData(CExBaseObject *pData, int nRow)
{
	CDvmData *pChData = (CDvmData*)pData;

	ShowAttrValue(pChData, nRow, 1, _T("$mag"),3);
	ShowAttrValue(pChData, nRow, 2, _T("$ang"), 3);
	ShowAttrValue(pChData, nRow, 3, _T("$freq"), 3);
}

void CSttIecSmvGrid_EffecValue::mousePressEvent(QMouseEvent * event)
{
	m_oTickCount.Enter();
		QExBaseListGridBase::mousePressEvent(event);

// 	if (m_bRunning)
// 	{
// 		QExBaseListGridBase::mousePressEvent(event);
// 		return;
// 	}
// 
// 	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
// 	QApplication::postEvent(this,pEvent);
// 	QExBaseListGridBase::mousePressEvent(event);
}

void CSttIecSmvGrid_EffecValue::mouseReleaseEvent(QMouseEvent *event)
{
	mouseReleaseEventBase(event);
	QExBaseListGridBase::mouseReleaseEvent(event);
}

// bool CSttIecSmvGrid_EffecValue::eventFilter(QObject *obj, QEvent *event)
// {
// 	if (event->type() == QEvent::MouseButtonDblClick)
// 	{
// 		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
// 		m_bRunning = TRUE;
// 		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
// 		m_bRunning = FALSE;
// 		return  true;
// 	}
// 
// 	return QExBaseListGridBase::eventFilter(obj,event);
// 
// }


void CSttIecSmvGrid_EffecValue::slot_doubleClicked(int nRow,int nCol)
{
	CCapDeviceSmvBase *pCapDeviceSmvBase = NULL;

	if (m_pCapDevice != NULL)
	{
		pCapDeviceSmvBase = (CCapDeviceSmvBase*)m_pCapDevice;
		SetItemPic_RefCh(pCapDeviceSmvBase->m_nRefChIndex,0,FALSE);
		pCapDeviceSmvBase->m_nRefChIndex = nRow;
		SetItemPic_RefCh(pCapDeviceSmvBase->m_nRefChIndex,0);
	}
}
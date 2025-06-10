#include "QAinDataMapGrid.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"
#include "../../SttTestCntrFrameBase.h"
#include <QApplication>

QAinDataMapGrid::QAinDataMapGrid(QWidget* pParent) : QExBaseListGridBase(pParent)
{

}

QAinDataMapGrid::~QAinDataMapGrid()
{

}


void QAinDataMapGrid::InitGrid()
{
	InitGridTitle();
	SetDefaultRowHeight(50);
	SetEditable(FALSE);
}

void QAinDataMapGrid::InitGridTitle()
{
	CString astrGridTitle[3];
        astrGridTitle[0] = /* _T("�Զ�������") */ g_sLangTxt_Native_CustomName;
        astrGridTitle[1] = /* _T("ʵ��װ�õ���������") */ g_sLangTxt_Native_RealDevData;
        astrGridTitle[2] = /* _T("�����������ݼ�") */ g_sLangTxt_Native_DataInSet;

	int iGridWidth[3]={100, 200, 200};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 3);
}

//2023-9-4  ���ڴ��ݱ���ʱ��ֻ������name��id��value��data-type��
//��¼���ݼ�·�������ԣ���format��Ϊdata-type
void QAinDataMapGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT(pData);
	CDvmData *pDvmData = (CDvmData *)pData;
	Show_StaticString(pData,nRow, 0, pDvmData->m_strName);
	Show_StaticString(pData,nRow, 1, pDvmData->m_strValue);
	Show_StaticString(pData,nRow, 2,  pDvmData->m_strDataType);
	nRow++;
}

bool QAinDataMapGrid::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = FALSE;
		return  true;
	}

	return QExBaseListGridBase::eventFilter(obj,event);

}

void QAinDataMapGrid::mousePressEvent(QMouseEvent * event)
{
	if (m_bRunning)
	{
		QExBaseListGridBase::mousePressEvent(event);
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
	QApplication::postEvent(this,pEvent);
	QExBaseListGridBase::mousePressEvent(event);

}



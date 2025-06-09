#include "QSclSelectCtrlsGrid.h"

#include <QApplication>


#include "../../../../../61850/Module/SCL/SclIecCfgDatas.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../../XLangResource_Native.h"


QSclSelectCtrlsGrid::QSclSelectCtrlsGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_pChType_DelegBase = NULL;
	m_bRunning = FALSE;
	installEventFilter(this);
}

QSclSelectCtrlsGrid::~QSclSelectCtrlsGrid()
{
}

void QSclSelectCtrlsGrid::InitGrid()
{
	InitGridTitle();
	m_pChType_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(0,m_pChType_DelegBase);

	SetEditable(TRUE);
}

void QSclSelectCtrlsGrid::InitGridTitle()
{
	CString strChoose,strType,strDataSets;
	xlang_GetLangStrByFile(strType,"sType");
	xlang_GetLangStrByFile(strDataSets,"sDataSets");

	CString astrGridTitle[SCL_SCLCTRLS__GRID_COLS] = {strType, _T("APPID"), strDataSets, _T("IED")};
	int iGridWidth[SCL_SCLCTRLS__GRID_COLS]={140, 80, 80, 80};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, SCL_SCLCTRLS__GRID_COLS);
}

void QSclSelectCtrlsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{

	CSclIed *pSclIed = (CSclIed *)pData->GetParent()->GetParent();
	CSclCtrlBase *pSclCtrl = (CSclCtrlBase *)pData;

	CString strTmp;
	Show_DataType_Val(pSclCtrl, nRow, 0,iecfg_TesterSubPubDataType, (long *)&pSclCtrl->m_dwItemData);
	strTmp.Format(_T("0X%04X"),pSclCtrl->m_dwAppID);
	Show_StaticString(pData,nRow,1,&strTmp);
	Show_StaticString(pData,nRow,2,&pSclCtrl->m_strDataSetDesc);
	
	//Show_StaticString(pData,nRow,2,&pSclCtrl->m_strDataSet); 

	if(pData->GetClassID() == SCLIECCLASSID_CTRL_GS_OUT)
	{
		Show_StaticString(pSclIed,nRow,3,&pSclIed->m_strName);
	}
	else if(pData->GetClassID() == SCLIECCLASSID_CTRL_GS_IN)
	{
		CSclCtrlGsIn *pSclGsIn = (CSclCtrlGsIn*)pSclCtrl;
		Show_StaticString(pData,nRow,3,&pSclGsIn->m_strExIedDesc); 
	}
	else if(pData->GetClassID() == SCLIECCLASSID_CTRL_SMV_OUT)
	{
		Show_StaticString(pSclIed,nRow,3,&pSclIed->m_strName);
	}
	else if(pData->GetClassID() == SCLIECCLASSID_CTRL_SMV_IN)
	{
		CSclCtrlSmvIn *pSclSmvIn = (CSclCtrlSmvIn*)pSclCtrl;
		Show_StaticString(pData,nRow,3,&pSclSmvIn->m_strExIedDesc);
	}
	else
	{
		return;
	}

	nRow++;
}

CDataType* QSclSelectCtrlsGrid::FindDataType(const CString &strDataType)
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(strDataType);

	return pDataType;
}



bool QSclSelectCtrlsGrid::eventFilter(QObject *obj, QEvent *event)
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

void QSclSelectCtrlsGrid::mousePressEvent(QMouseEvent * event)
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




#include "QSttAntiShakeTimeDinEventGroupGrid.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../UI/SttTestCntrFrameBase.h"
#include "../Module/SttGlobalDef.h"
#include"../../../../Module/XLangResource_Native.h"
#include "../../../Module/XLanguage/XLanguageResource.h"
#include "../QSttMacroParaEditViewAntiShakeTime.h"

QSttAntiShakeTimeDinEventGroupGrid::QSttAntiShakeTimeDinEventGroupGrid(QWidget *parent)
#ifdef _PSX_QT_LINUX_
: QScrollTableWidget(parent)
#else
: QTableWidget(parent)
#endif
{
	m_pCurrKeyboardItem = NULL;
	m_bRunning = FALSE;
	installEventFilter(this);
}

QSttAntiShakeTimeDinEventGroupGrid::~QSttAntiShakeTimeDinEventGroupGrid()
{

}

void QSttAntiShakeTimeDinEventGroupGrid::InitUI()
{
	QHeaderView* pLeft = verticalHeader();
	pLeft->setDefaultSectionSize(36);
	pLeft->setVisible(false);
	QHeaderView* pHeadTop =horizontalHeader();
	pHeadTop->setSectionsClickable(false);
	pHeadTop->setSectionsMovable(false);
	QFont font1 = this->horizontalHeader()->font();
	font1.setBold(true);
	this->horizontalHeader()->setFont(font1);
	horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	setEditTriggers(QAbstractItemView::DoubleClicked);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色

	QFontMetrics fontHeaderViewMe = QFontMetrics(font1);
	m_nHeaderViewHeight = fontHeaderViewMe.height() + 20;
	QFont font2 = this->font();
	font2.setPointSize(20);
	this->setFont(font2);
	QFontMetrics fontRowMe = QFontMetrics(font2);
	m_nRowHeight = fontRowMe.height() + 15;
	setFont(*g_pSttGlobalFont);
	horizontalHeader()->setFont(*g_pSttGlobalFont);   
	InitTable();
}


void QSttAntiShakeTimeDinEventGroupGrid::InitTable()
{
	QStringList  HStrList;
	HStrList << _T("编号") <<  _T("间隔") << _T("YX通道") << _T("事件描述")<< _T("事件发生时间") ;
	setColumnCount(5);
	setHorizontalHeaderLabels(HStrList);
	QFontMetrics fontMetrics = QFontMetrics(this->font());
	this->setColumnWidth(0,100);
	this->setColumnWidth(1,150);
	this->setColumnWidth(2,200);
	this->setColumnWidth(3,220);
	this->setColumnWidth(4,200);
}

void QSttAntiShakeTimeDinEventGroupGrid::UpdateText( const QString &strText )
{

}

void QSttAntiShakeTimeDinEventGroupGrid::AddShowReports( CDvmDataset *pSoeRptDataset )
{
	if (pSoeRptDataset == NULL)
	{
		return;
	}

	long nCurrRowIndex = rowCount();
// 	long nRowCount = nCurrRowIndex + pSoeRptDataset->GetCount();
// 	setRowCount(nRowCount);

	QTableWidgetItem *item = NULL; 
	POS pos = pSoeRptDataset->GetHeadPosition();
	CDvmData *pCurrData = NULL;
	CString strTmpString;

	while(pos)
	{
		pCurrData = (CDvmData*)pSoeRptDataset->GetNext(pos); 

		if (pCurrData == NULL)
		{
			continue;
		}
		if (g_pAntiShakeTime->m_SelectTestObjetcList.contains(pCurrData->m_strID))

		//if (pCurrData->m_strID == _T("Din_1") || pCurrData->m_strID == _T("Din_2") || pCurrData->m_strID == _T("Din_5"))
		{
			if (nCurrRowIndex >= rowCount())
			{
				setRowCount(nCurrRowIndex + 1);
			}

		//编号
		item = new QTableWidgetItem;
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		item->setText(QString::number(nCurrRowIndex+1));
		setItem(nCurrRowIndex,0,item);

		//间隔
		item = new QTableWidgetItem;
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		CDvmDataset *pCurrDataset = (CDvmDataset*)g_pAntiShakeTime->m_pCmbIntervalSelect->GetCurrSelObject();
		if (pCurrDataset)
		{
			strTmpString = pCurrDataset->m_strName;
		}
		else
		{
			strTmpString = "---";
		}

		item->setText(pCurrDataset->m_strName);
		setItem(nCurrRowIndex,1,item);

		//YX通道
		item = new QTableWidgetItem;
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		if (pCurrData->m_strName.IsEmpty())
		{
			item->setText(pCurrData->m_strID);
		}
		else
		{
			item->setText(pCurrData->m_strName);
		}
		setItem(nCurrRowIndex,2,item);

		//事件描述
		item = new QTableWidgetItem;
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		strTmpString = _T("遥信值:");
		strTmpString = strTmpString + pCurrData->m_strValue;

		if (pCurrData->m_strName.IsEmpty())
		{
			strTmpString = strTmpString + _T("(")+ pCurrData->m_strID + _T(")");
		}
		else
		{
			strTmpString = strTmpString + _T("(")+ pCurrData->m_strName + _T(")");
		}
		item->setText(strTmpString);
		setItem(nCurrRowIndex,3,item);

		//事件发生时间
		item = new QTableWidgetItem;
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
		item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		strTmpString = GetAttrValue(pCurrData,"$t");
// #ifdef _PSX_QT_LINUX_
// 			QDateTime dateTime = QDateTime::fromString(strTmpString, "yyyy-MM-dd HH:mm:ss.zzz");
// 			dateTime.setTimeSpec(Qt::UTC);
// 			dateTime = dateTime.addSecs(g_oSystemParas.m_nTimeZone * 3600); 
// 			strTmpString = dateTime.toString("yyyy-MM-dd hh:mm:ss.zzz");
// #endif
		item->setText(strTmpString);
		setItem(nCurrRowIndex,4,item);

		nCurrRowIndex++;
		}
	}
}

CString QSttAntiShakeTimeDinEventGroupGrid::GetAttrValue( CDvmData *pCurrData,const CString &strSearchID )
{
	CString strText;
	strText = "---";
	POS pos = pCurrData->GetHeadPosition();
	CDvmValue *pCurrValue = NULL;

	while(pos)
	{
		pCurrValue = (CDvmValue*)pCurrData->GetNext(pos);

		if (pCurrValue->m_strID.Find(strSearchID) != -1)
		{
			strText = pCurrValue->m_strValue;
			break;
		}
	}

	return strText;
}

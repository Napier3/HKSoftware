#include "QMannualCheckSettingGrid.h"
#include "..\..\Module\UI\Module\QExBaseListGridBase\QGridDefine.h"
#include <QHeaderView>
#include "..\SclCheckDataMngr\SclCheckObjectsSet.h"
#include "..\SclCheckDataMngr\SclCheckMngrGlobal.h"

QMannualCheckSettingGrid::QMannualCheckSettingGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_pCheckBoxDelegateBase = NULL;
	m_pDelegTokenType = NULL;
	m_TestMenu = new QMenu(this);
	m_SelectAll = new QAction(tr("全选"), this);
	m_TestMenu->addAction(m_SelectAll);
	m_UnSelectAll = new QAction(tr("全不选"), this);
	m_TestMenu->addAction(m_UnSelectAll);
	m_Reverse = new QAction(tr("反选"), this);
	m_TestMenu->addAction(m_Reverse);
	connect(m_SelectAll, SIGNAL(triggered()), this, SLOT(slot_SelectAll()));
	connect(m_UnSelectAll, SIGNAL(triggered()), this, SLOT(slot_UnSelectAll()));
	connect(m_Reverse, SIGNAL(triggered()), this, SLOT(slot_Reverse()));
}

QMannualCheckSettingGrid::~QMannualCheckSettingGrid()
{
	delete m_pCheckBoxDelegateBase;
	m_pCheckBoxDelegateBase = NULL;
}

void QMannualCheckSettingGrid::InitGrid()
{
	verticalHeader()->setVisible(false);
	InitGridTitle();
	if (m_pCheckBoxDelegateBase == NULL)
	{
		m_pCheckBoxDelegateBase = new QExBaseListCheckBoxDelegate(this);
	}
	setItemDelegateForColumn(1,m_pCheckBoxDelegateBase);
	if (m_pDelegTokenType == NULL)
	{
		m_pDelegTokenType = new QExBaseListComBoxDelegBase(this);
	}
	setItemDelegateForColumn(3,m_pDelegTokenType);

}

void QMannualCheckSettingGrid::InitGridTitle()
{
	CString astrGridTitle[MANNUALCHECKSETTINGGRID_COLS] = {_T("序号"),_T("选择"),_T("检测项目内容"),_T("标记方式")};
	int  iColType[MANNUALCHECKSETTINGGRID_COLS]={QT_GVET_NOEDIT, QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT};
	int iGridWidth[MANNUALCHECKSETTINGGRID_COLS]={50, 50, 800, 100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, MANNUALCHECKSETTINGGRID_COLS);
}

void QMannualCheckSettingGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT(pData);
	m_nIndex = long(nRow+1);
	CCheckObject *pMannualSetting = (CCheckObject*)pData;
//	Show_Index(pMannualSetting, nRow, 0);
	Show_Long(pMannualSetting, nRow, 0, &m_nIndex);
	Show_Check(pMannualSetting, nRow, 1, &pMannualSetting->m_nChoose);
	Show_StaticString(pMannualSetting, nRow, 2, &pMannualSetting->m_strName);
	Show_DataType_Val(pMannualSetting, nRow, 3, "checkObjectSetDataTypeID", &pMannualSetting->m_strErrorType);
	nRow++;
}

CDataType* QMannualCheckSettingGrid::FindDataType(const CString &strDataType)
{
	CDataType *pDataType = CSclCheckMngrConstGlobal::FindIecRtdDataType(strDataType);

	return pDataType;
}
void QMannualCheckSettingGrid::mousePressEvent(QMouseEvent *event)
{
	if (event->button()==Qt::RightButton)
	{
		QExBaseListGridBase::mousePressEvent(event);
		m_TestMenu->exec(QCursor::pos());
	}
	if (event->button()==Qt::LeftButton)
	{
		QExBaseListGridBase::mousePressEvent(event);
	}
}

void QMannualCheckSettingGrid::slot_SelectAll()
{
	emit sig_SelectAll();

}

void QMannualCheckSettingGrid::slot_UnSelectAll()
{
	emit sig_UnSelectAll();
}

void QMannualCheckSettingGrid::slot_Reverse()
{
	emit sig_Reverse();
}
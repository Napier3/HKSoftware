#include "QSchemaCheckSettingGrid.h"
#include "..\..\Module\UI\Module\QExBaseListGridBase\QGridDefine.h"
#include <QHeaderView>
#include "../TestWinFrame/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "..\SclCheckDataMngr\SclCheckObjectsSet.h"
#include "..\SclCheckDataMngr\SclCheckMngrGlobal.h"

QSchemaCheckSettingGrid::QSchemaCheckSettingGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_pCheckBoxDelegateBase = NULL;
	m_pDelegXmlMethod = NULL;
	m_pDelegVersion = NULL;
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

QSchemaCheckSettingGrid::~QSchemaCheckSettingGrid()
{

}

void QSchemaCheckSettingGrid::InitGrid()
{
	verticalHeader()->setVisible(false); 
	InitGridTitle();
  	if (m_pCheckBoxDelegateBase == NULL)
	{
		m_pCheckBoxDelegateBase = new QExBaseListCheckBoxDelegate(this);
	}
	setItemDelegateForColumn(1,m_pCheckBoxDelegateBase);
	if (m_pDelegVersion == NULL)
	{
		m_pDelegVersion = new QExBaseListComBoxDelegBase(this);
	}
	setItemDelegateForColumn(3,m_pDelegVersion);
	if (m_pDelegXmlMethod == NULL)
	{
		m_pDelegXmlMethod = new QExBaseListComBoxDelegBase(this);
	}
	setItemDelegateForColumn(4,m_pDelegXmlMethod);

}

void QSchemaCheckSettingGrid::InitGridTitle()
{
	CString astrGridTitle[SCHEMACHECKSETTINGGRID_COLS] = {_T("序号"),_T("选择"),_T("检测项目内容"),_T("版本选择"),_T("xml解析方法")};
	int  iColType[SCHEMACHECKSETTINGGRID_COLS]={QT_GVET_NOEDIT, QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT};
	int iGridWidth[SCHEMACHECKSETTINGGRID_COLS]={50, 50, 700, 100, 100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, SCHEMACHECKSETTINGGRID_COLS);
}

void QSchemaCheckSettingGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT(pData);
	m_nIndex  = long(nRow + 1);
	CSchemaCheckObject *pSchemaSetting = (CSchemaCheckObject*)pData;
//	Show_Index(pSchemaSetting, nRow, 0);
	Show_Long(pSchemaSetting, nRow, 0, &m_nIndex);
	Show_Check(pSchemaSetting, nRow, 1, &pSchemaSetting->m_nChoose );
	Show_StaticString(pSchemaSetting, nRow, 2, &pSchemaSetting->m_strName);
	Show_DataType_Val(pSchemaSetting, nRow, 3, "schemaCheckVertionTypeID", &pSchemaSetting->m_strVertionType);
	Show_DataType_Val(pSchemaSetting, nRow, 4, "schemaCheckMethodTypeID", &pSchemaSetting->m_strCheckType);
	nRow++;
}

CDataType* QSchemaCheckSettingGrid::FindDataType(const CString &strDataType)
{
	CDataType *pDataType = CSclCheckMngrConstGlobal::FindIecRtdDataType(strDataType);
	return pDataType;
}
void QSchemaCheckSettingGrid::mousePressEvent(QMouseEvent *event)
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

void QSchemaCheckSettingGrid::slot_SelectAll()
{
	emit sig_SelectAll();

}

void QSchemaCheckSettingGrid::slot_UnSelectAll()
{
	emit sig_UnSelectAll();
}

void QSchemaCheckSettingGrid::slot_Reverse()
{
	emit sig_Reverse();
}
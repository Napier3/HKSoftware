#include "StateEditDlg.h"
#include "../../SttTest/Common/tmt_state_test.h"
#include <QGridLayout>
#include <QDialog>
#include <QPushButton>
#include "../../Module/XLangResource_Native.h"
#include "../../../../Module/XLanguage/XLanguageResource.h"
#include "../../../../AutoTest/Module/XLanguageResourceAts.h"


QStateEditGrid::QStateEditGrid(QWidget* pParent) : QExBaseListGridBase(pParent)
{

}

QStateEditGrid::~QStateEditGrid()
{

}

void QStateEditGrid::InitGrid()
{
	InitGridTitle();
	SetDefaultRowHeight(50);
	SetEditable(TRUE);

	m_pSelectSclIedDelegate = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(0,m_pSelectSclIedDelegate);
	
}

void QStateEditGrid::InitGridTitle()
{
	//CString strTest = _T("选择"), strName = _T("状态名"), strDesc = _T("描述");
    CString strTest = g_sLangTxt_Select, strName = g_sLangTxt_State_Statusname, strDesc = g_sLangTxt_State_Description;
	CString astrGridTitle[3] = {strTest, strName, strDesc};
	int iGridWidth[3]={50, 100, 100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 3);
	
}

void QStateEditGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
 	Show_Check(pData, nRow, 0, (long*)&pData->m_dwItemData);
 	Show_StaticString(pData, nRow, 1, pData->m_strID);
 	Show_String(pData, nRow, 2, &pData->m_strName);
	nRow++;	
}

//2023-3-15 全选
void QStateEditGrid::SelectedAll()
{

	POS pos = m_pDatas->GetHeadPosition();
	CExBaseObject *pData = NULL;

	while (pos != NULL)
	{
		pData = m_pDatas->GetNext(pos);
		pData->m_dwItemData = 1;
	}



	UpdateSelectCol();
}
//2023-3-15 更新
void QStateEditGrid::UpdateSelectCol()
{
	CExBaseObject *pData = NULL;	
	POS pos = m_pDatas->GetHeadPosition();
	int nRowIndex = 0;

	while (pos != NULL)
	{
		pData = m_pDatas->GetNext(pos);
		Show_Check(pData, nRowIndex, 0, (long*)&pData->m_dwItemData);
		nRowIndex++;
	}
}

//2023-3-15 全不选
void QStateEditGrid::UnSelectedAll()
{

	POS pos = m_pDatas->GetHeadPosition();
	CExBaseObject *pData = NULL;

	while (pos != NULL)
	{
		pData = m_pDatas->GetNext(pos);
		pData->m_dwItemData = 0;
	}


	UpdateSelectCol();
}
//2023-3-15 反选
void QStateEditGrid::ReverseSelection()
{
	POS pos = m_pDatas->GetHeadPosition();
	CExBaseObject *pData = NULL;

	while (pos != NULL)
	{
		pData = m_pDatas->GetNext(pos);

		if (pData->m_dwItemData == 0)
		{
			pData->m_dwItemData = 1;
		}
		else
		{
			pData->m_dwItemData = 0;
		}
	}

	UpdateSelectCol();
}


QStateEditDlg::QStateEditDlg(QWidget *parent)
{
	setParent(parent);
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	//CString strTitle = _T("状态编辑");
	setWindowTitle(g_sLangTxt_State_StatusEdition);
	setMinimumSize(400,400);

	QGridLayout* pLayout = new QGridLayout(this);
	setLayout(pLayout);

	m_pStateList = NULL;
	m_pEditGrid = new QStateEditGrid(this);
	m_pEditGrid->InitGrid();
	
	pLayout->addWidget(m_pEditGrid);
	QHBoxLayout* pHLayout = new QHBoxLayout(this);
	pLayout->addLayout(pHLayout, 1, 0);


    CString strText;
	QPushButton* pBtnSelectAll = new QPushButton(this);
	//CString strText = _T("全选");
	pBtnSelectAll->setText(g_sLangTxt_SelAll);//lcq
	//pBtnSelectAll->setFixedSize(200,50);

	QPushButton* pBtnUnSelectAll = new QPushButton(this);
	//strText = _T("全不选");
	pBtnUnSelectAll->setText(g_sLangTxt_SelNone);//lcq
	//pBtnUnSelectAll->setFixedSize(200,50);

	QPushButton* pBtnReverseSelect = new QPushButton(this);
	//strText = _T("反选");
	pBtnReverseSelect->setText(g_sLangTxt_Gradient_Inverse); //lcq
	//pBtnReverseSelect->setFixedSize(200,50);

	QPushButton* pBtnOK = new QPushButton(this);
	//strText = _T("确定");
	pBtnOK->setText(g_sLangTxt_OK); //lcq
	//pBtnOK->setFixedSize(200,50);

	QPushButton* pBtnCancel = new QPushButton(this);
	//strText = _T("取消");
	pBtnCancel->setText(g_sLangTxt_Cancel); //lcq
	//pBtnCancel->setFixedSize(200,50);


	
	
	pHLayout->addWidget(pBtnSelectAll);
	pHLayout->addWidget(pBtnReverseSelect);
	pHLayout->addWidget(pBtnUnSelectAll);
	pHLayout->addWidget(pBtnOK);
	pHLayout->addWidget(pBtnCancel);
	


	connect(pBtnOK, SIGNAL(clicked(bool)), this, SLOT(accept()));
	connect(pBtnCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
	connect(pBtnSelectAll, SIGNAL(clicked(bool)), this, SLOT(slot_SelectedAll()));
	connect(pBtnReverseSelect, SIGNAL(clicked(bool)), this, SLOT(slot_ReverseSelect()));
	connect(pBtnUnSelectAll, SIGNAL(clicked(bool)), this, SLOT(slot_UnSelectedAll()));

	
}

void QStateEditDlg::slot_SelectedAll()
{
	
	m_pEditGrid->SelectedAll();
}

void QStateEditDlg::slot_ReverseSelect()
{
	m_pEditGrid->ReverseSelection();
}
void QStateEditDlg::slot_UnSelectedAll()
{
	m_pEditGrid->UnSelectedAll();
	
}

QStateEditDlg::~QStateEditDlg()
{
	if(m_pEditGrid)
	{
		delete m_pEditGrid;
		m_pEditGrid = NULL;
	}
}
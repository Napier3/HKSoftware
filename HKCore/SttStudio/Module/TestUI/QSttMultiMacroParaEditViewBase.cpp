#include "QSttMultiMacroParaEditViewBase.h"

QSttMultiMacroParaEditViewBase::QSttMultiMacroParaEditViewBase(const CString &strGridFile,QWidget *parent)
	: CSttMacroParaEditViewOriginal(parent)
{
	CString strPath;
	strPath = _P_GetDBPath();
	strPath += "atsgen/";
	strPath += strGridFile;

	if (!m_oSttTestGridDefine.OpenXmlFile(strPath,CSttTestGridDefineXmlRWKeys::g_pXmlKeys))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�򿪲��Թ��ܱ�������ļ�(%s)ʧ��."),strPath.GetString());
	}
	
	m_pSingleItemEditTab = NULL;
	m_pSingleItemParaEditWidget = NULL;
	m_pGoosePubsWidget = NULL;
	m_pCurrMacroParaEditGrid = NULL;
	m_pMultiMacroGridTab = NULL;
	m_pAddOneItemBtn = NULL;
	m_pAddMultiItemBtn = NULL;
	m_pCommonParasBtn = NULL;
	m_pBinarysBtn = NULL;
	m_pDeleteItemBtn = NULL;
	m_pClearResultBtn = NULL;
	m_pCurrRootItems = NULL;
	m_pMainVboxLayout = NULL;
	m_pBottomHboxLayout = NULL;

}

QSttMultiMacroParaEditViewBase::~QSttMultiMacroParaEditViewBase()
{

}


//���������ܶ�����
void QSttMultiMacroParaEditViewBase::InitUI_OneMacro()
{
	setFont(*g_pSttGlobalFont);

	CString strText;
	m_pSingleItemEditTab = new QTabWidget();

	m_pCurrMacroParaEditGrid = new QSttMacroParaEditGrid(this);
//	m_pCurrMacroParaEditGrid->InitGrid();

	m_pBottomHboxLayout = new QHBoxLayout();
	strText = "ͨ�ò���";
	m_pCommonParasBtn = new QPushButton(strText);
	strText = "������";
	m_pBinarysBtn = new QPushButton(strText);
	strText = "ɾ��������";
	m_pDeleteItemBtn = new QPushButton(strText);
	strText = "������Խ��";
	m_pClearResultBtn = new QPushButton(strText);

	m_pBottomHboxLayout->addWidget(m_pCommonParasBtn);
	m_pBottomHboxLayout->addWidget(m_pBinarysBtn);
	m_pBottomHboxLayout->addWidget(m_pDeleteItemBtn);
	m_pBottomHboxLayout->addWidget(m_pClearResultBtn);

	m_pMainVboxLayout = new QVBoxLayout();

	m_pMainVboxLayout->addWidget(m_pSingleItemEditTab);
	m_pMainVboxLayout->addWidget(m_pCurrMacroParaEditGrid);
	m_pMainVboxLayout->addLayout(m_pBottomHboxLayout);
	setLayout(m_pMainVboxLayout);
}

//�����๦�ܶ�����
void QSttMultiMacroParaEditViewBase::InitUI_MultiMacro()
{

}

void QSttMultiMacroParaEditViewBase::InitDatas()
{
	DisConnectAll_SigSlot();
}

void QSttMultiMacroParaEditViewBase::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{

}

void QSttMultiMacroParaEditViewBase::ConnectAll_SigSlot()
{
	connect(m_pCommonParasBtn,SIGNAL(clicked()),this,SLOT(on_m_btnCommonParas_clicked()));
	connect(m_pBinarysBtn,SIGNAL(clicked()),this,SLOT(on_m_btnBinarys_clicked()));
	connect(m_pDeleteItemBtn,SIGNAL(clicked()),this,SLOT(on_m_btnDeleteItem_clicked()));
	connect(m_pClearResultBtn,SIGNAL(clicked()),this,SLOT(on_m_btnClearResult_clicked()));
}

void QSttMultiMacroParaEditViewBase::DisConnectAll_SigSlot()
{
	disconnect(m_pCommonParasBtn,SIGNAL(clicked()),this,SLOT(on_m_btnCommonParas_clicked()));
	disconnect(m_pBinarysBtn,SIGNAL(clicked()),this,SLOT(on_m_btnBinarys_clicked()));
	disconnect(m_pDeleteItemBtn,SIGNAL(clicked()),this,SLOT(on_m_btnDeleteItem_clicked()));
	disconnect(m_pClearResultBtn,SIGNAL(clicked()),this,SLOT(on_m_btnClearResult_clicked()));
}

void QSttMultiMacroParaEditViewBase::slot_AddOneItemBtnClick()//��ӵ���������
{

}

void QSttMultiMacroParaEditViewBase::slot_AddMultiItemBtnClick()//���ϵ��
{

}

void QSttMultiMacroParaEditViewBase::slot_CommonParasBtnClick()//ͨ�ò���
{

}

void QSttMultiMacroParaEditViewBase::slot_BinarysBtnClick()//������
{

}

void QSttMultiMacroParaEditViewBase::slot_DeleteItemBtnClick()//ɾ��������
{

}

void QSttMultiMacroParaEditViewBase::slot_ClearResultBtnClick()//������Խ��
{

}
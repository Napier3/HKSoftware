#include "SttMultiMacroParaEditViewDistance.h"
//#include "ui_SttMultiMacroParaEditViewDistance.h"


QSttMultiMacroParaEditViewDistance::QSttMultiMacroParaEditViewDistance(const CString &strGridFile,QWidget *parent) :
    QSttMultiMacroParaEditViewBase(strGridFile,parent)
{
	m_pAddMultiItemSelectDlg = NULL;
	m_pParas = NULL;
	//20240619 luozibing 测试使用
	CString strConfigPath =  _P_GetConfigPath();
	CString strTestMacroFile = strConfigPath;
	strTestMacroFile += "RelayTest/TestMacro.xml";

	CTestMacros *pTestMacros = new CTestMacros();
	pTestMacros->OpenXmlFile(strTestMacroFile, CTestMacroXmlRWKeys::g_pXmlKeys);
	CTestMacro *pTmp = (CTestMacro *)pTestMacros->FindByID("Distance");
	if(pTmp != NULL)
	{
		m_pParas = (CDataGroup *)pTmp->GetFaultParas();
	}

	m_pZPhiGridInst = NULL;
	m_pRXGridInst = NULL;
}

QSttMultiMacroParaEditViewDistance::~QSttMultiMacroParaEditViewDistance()
{
}

void QSttMultiMacroParaEditViewDistance::InitUI_OneMacro()
{
	QSttMultiMacroParaEditViewBase::InitUI_OneMacro();
	m_pSingleItemParaEditWidget = new QDistanceItemParaEditWidget();

	CString strText;
	strText = "功能参数";
	m_pSingleItemEditTab->insertTab(0,m_pSingleItemParaEditWidget,strText);

	strText = "添加单项";
	m_pAddOneItemBtn = new QPushButton(strText);
	strText = "添加系列";
	m_pAddMultiItemBtn = new QPushButton(strText);
	
	m_pBottomHboxLayout->insertWidget(0,m_pAddOneItemBtn);
	m_pBottomHboxLayout->insertWidget(1,m_pAddMultiItemBtn);
	InitDatas();
}

void QSttMultiMacroParaEditViewDistance::InitDatas()
{
	m_pRXGridInst = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_Distance,STT_MULTI_MACRO_DISTANCE_PARAS_GRID_ID_RX);
	m_pZPhiGridInst = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_Distance,STT_MULTI_MACRO_DISTANCE_PARAS_GRID_ID_ZPhi);
	QSttMultiMacroParaEditViewBase::InitDatas();
	m_pSingleItemParaEditWidget->UpdateParas((CSttMacroTest*)m_pParas);
	ConnectAll_SigSlot();
}

void QSttMultiMacroParaEditViewDistance::ConnectAll_SigSlot()
{
	QSttMultiMacroParaEditViewBase::ConnectAll_SigSlot();
	connect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(on_m_btnAddOneItem_clicked()));
	connect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(on_m_btnAddMultiItem_clicked()));
}

void QSttMultiMacroParaEditViewDistance::DisConnectAll_SigSlot()
{
	QSttMultiMacroParaEditViewBase::DisConnectAll_SigSlot();
	disconnect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(on_m_btnAddOneItem_clicked()));
	disconnect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(on_m_btnAddMultiItem_clicked()));
}

void QSttMultiMacroParaEditViewDistance::on_m_btnAddOneItem_clicked()
{
	//20240619 luozibing 测试使用
	CString strConfigPath =  _P_GetConfigPath();
	CString strTestMacroFile = strConfigPath;
	strTestMacroFile += "RelayTest/TestMacro_DeBug.xml";
	m_pParas->SaveXmlFile(strTestMacroFile, CTestMacroXmlRWKeys::g_pXmlKeys);
}

void QSttMultiMacroParaEditViewDistance::on_m_btnAddMultiItem_clicked()
{
	if (m_pAddMultiItemSelectDlg == NULL)
	{
		m_pAddMultiItemSelectDlg = new QDialog(this);
		m_pAddMultiItemSelectDlg->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint ); 
		m_pAddMultiItemSelectDlg->setFont(*g_pSttGlobalFont);

		QGridLayout *pLayout = new QGridLayout(m_pAddMultiItemSelectDlg);
		QPushButton *pBtnAddOne_LN= new QPushButton("添加单个区段-接地故障");
		QPushButton *pBtnAddOne_LL= new QPushButton("添加单个区段-相间故障");
		QPushButton *pBtnAddMult= new QPushButton("添加多个区段");

		pLayout->addWidget(pBtnAddOne_LN,0,0);
		pLayout->addWidget(pBtnAddOne_LL,1,0);
		pLayout->addWidget(pBtnAddMult,2,0);

		connect(pBtnAddOne_LN,SIGNAL(clicked()),this,SLOT(on_m_btnAddOne_LN_clicked()));
		connect(pBtnAddOne_LL,SIGNAL(clicked()),this,SLOT(on_m_btnAddOne_LL_clicked()));
		connect(pBtnAddMult,SIGNAL(clicked()),this,SLOT(on_m_btnAddMult_clicked()));
	}

	QPoint ParentPos = this->mapToGlobal(QPoint(0, 0));
	QPoint Pos = m_pAddMultiItemBtn->pos();

	int tmp = m_pAddMultiItemSelectDlg->height();
	m_pAddMultiItemSelectDlg->move(ParentPos.x()+Pos.x(),ParentPos.y()+Pos.y()-130);
	m_pAddMultiItemSelectDlg->show();
}
void QSttMultiMacroParaEditViewDistance::on_m_btnAddOne_LN_clicked()
{
	m_pAddMultiItemSelectDlg->hide();
}
void QSttMultiMacroParaEditViewDistance::on_m_btnAddOne_LL_clicked()
{
	m_pAddMultiItemSelectDlg->hide();
}
void QSttMultiMacroParaEditViewDistance::on_m_btnAddMult_clicked()
{
	m_pAddMultiItemSelectDlg->hide();
	//20240620 luozibing 添加多个区段页面
	QDistanceAddMultDlg oQDistanceAddMultDlg;
	CDataGroup *pPara = oQDistanceAddMultDlg.OpenDisTanceParasFile(_T("Distance_Paras.xml"));
	oQDistanceAddMultDlg.SetDatas(pPara);

	if(oQDistanceAddMultDlg.exec() == QDialog::Accepted)
	{
		oQDistanceAddMultDlg.GetDatas(pPara);
	}
}
void QSttMultiMacroParaEditViewDistance::on_m_btnCommonParas_clicked()
{
	//20240620 luozibing 通用参数页面
	QDistanceCommonParasDlg oQDistanceCommonParasDlg;
	oQDistanceCommonParasDlg.SetDatas(m_pParas);

	if(oQDistanceCommonParasDlg.exec() == QDialog::Accepted)
	{
		oQDistanceCommonParasDlg.GetDatas(m_pParas);
	}
}

void QSttMultiMacroParaEditViewDistance::on_m_btnBinarys_clicked()
{
	//20240620 luozibing 开入量、开出量页面
	QDistanceBinarysDlg oQDistanceBinarysDlg;
	oQDistanceBinarysDlg.SetDatas(m_pParas);

	if(oQDistanceBinarysDlg.exec() == QDialog::Accepted)
	{
		oQDistanceBinarysDlg.GetDatas(m_pParas);
	}
}

void QSttMultiMacroParaEditViewDistance::on_m_btnDeleteItem_clicked()
{

}

void QSttMultiMacroParaEditViewDistance::on_m_btnClearResult_clicked()
{

}
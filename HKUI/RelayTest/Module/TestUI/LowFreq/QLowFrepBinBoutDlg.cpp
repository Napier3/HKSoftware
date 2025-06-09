 #include "QLowFrepAddMultDlg.h"
 #include <QLabel>
 #include "../../UI/SoftKeyboard/SoftKeyBoard.h"
 #include "../../UI/Module/CommonMethod/commonMethod.h"
 
 QLowFrepBinBoutDlg::QLowFrepBinBoutDlg(CDataGroup *m_oLowFrepDataGroup, QWidget *parent /*= 0*/) : QDialog(parent),
 ui(new Ui::QLowFrepBinBoutDlg)
 {
	m_oLowFrepBinBoutDataGroup = m_oLowFrepDataGroup;
	ui->setupUi(this);
	
	InitDatas();
	InitFont();
	InitConnects();
 }
 
 QLowFrepBinBoutDlg::~QLowFrepBinBoutDlg()
 {
 
 }

 void QLowFrepBinBoutDlg::InitDatas()
 {
	 CDvmData *pData = NULL;
	 long nValue;
	 float fValue;

	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("A");
	 if (pData != NULL)
	 {
		 nValue = CString_To_long(pData->m_strValue);
		 ui->m_cbBinA->setChecked(nValue);
	 }

	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("B");
	 if (pData != NULL)
	 {
		 nValue = CString_To_long(pData->m_strValue);
		 ui->m_cbBinB->setChecked(nValue);
	 }

	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("C");
	 if (pData != NULL)
	 {
		 nValue = CString_To_long(pData->m_strValue);
		 ui->m_cbBinC->setChecked(nValue);
	 }

	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("R");
	 if (pData != NULL)
	 {
		 nValue = CString_To_long(pData->m_strValue);
		 ui->m_cbBinD->setChecked(nValue);
	 }

	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("E");
	 if (pData != NULL)
	 {
		 nValue = CString_To_long(pData->m_strValue);
		 ui->m_cbBinE->setChecked(nValue);
	 }

	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("F");
	 if (pData != NULL)
	 {
		 nValue = CString_To_long(pData->m_strValue);
		 ui->m_cbBinF->setChecked(nValue);
	 }

	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("G");
	 if (pData != NULL)
	 {
		 nValue = CString_To_long(pData->m_strValue);
		 ui->m_cbBinG->setChecked(nValue);
	 }

	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("H");
	 if (pData != NULL)
	 {
		 nValue = CString_To_long(pData->m_strValue);
		 ui->m_cbBinH->setChecked(nValue);
	 }

	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("_B01");
	 if (pData != NULL)
	 {
		 nValue = CString_To_long(pData->m_strValue);
		 ui->m_cbBOut1->setChecked(nValue);
	 }

	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("_B02");
	 if (pData != NULL)
	 {
		 nValue = CString_To_long(pData->m_strValue);
		 ui->m_cbBOut2->setChecked(nValue);

	 }

	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("_B03");
	 if (pData != NULL)
	 {
		 nValue = CString_To_long(pData->m_strValue);
		 ui->m_cbBOut3->setChecked(nValue);
	 }

	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("_B04");
	 if (pData != NULL)
	 {
		 nValue = CString_To_long(pData->m_strValue);
		 ui->m_cbBOut4->setChecked(nValue);
	 }

	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("_B05");
	 if (pData != NULL)
	 {
		 nValue = CString_To_long(pData->m_strValue);
		 ui->m_cbBOut5->setChecked(nValue);
	 }

	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("_B06");
	 if (pData != NULL)
	 {
		 nValue = CString_To_long(pData->m_strValue);
		 ui->m_cbBOut6->setChecked(nValue);

	 }

	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("_B07");
	 if (pData != NULL)
	 {
		 nValue = CString_To_long(pData->m_strValue);
		 ui->m_cbBOut7->setChecked(nValue);
	 }

	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("_B08");
	 if (pData != NULL)
	 {
		 nValue = CString_To_long(pData->m_strValue);
		 ui->m_cbBOut8->setChecked(nValue);
	 }

	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("_AndOr");
	 if (pData != NULL)
	 {
		 nValue = CString_To_long(pData->m_strValue);
		 ui->m_rbOr->setChecked(nValue);
	 }

 }

 void QLowFrepBinBoutDlg::InitFont()
 {
	ui->m_cbBinA->setFont(*g_pSttGlobalFont);
	ui->m_cbBinB->setFont(*g_pSttGlobalFont);
	ui->m_cbBinC->setFont(*g_pSttGlobalFont);
	ui->m_cbBinD->setFont(*g_pSttGlobalFont);
	ui->m_cbBinE->setFont(*g_pSttGlobalFont);
	ui->m_cbBinF->setFont(*g_pSttGlobalFont);
	ui->m_cbBinG->setFont(*g_pSttGlobalFont);
	ui->m_cbBinH->setFont(*g_pSttGlobalFont);

	ui->m_cbBOut1->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut2->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut3->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut4->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut5->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut6->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut7->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut8->setFont(*g_pSttGlobalFont);

	ui->m_BtnOk->setFont(*g_pSttGlobalFont);
	ui->m_BtnCancel->setFont(*g_pSttGlobalFont);

	ui->m_rbAnd->setFont(*g_pSttGlobalFont);
	ui->m_rbOr->setFont(*g_pSttGlobalFont);
 }
 
 void QLowFrepBinBoutDlg::InitConnects()
 {
	connect(ui->m_BtnOk,SIGNAL(clicked()),this,SLOT(slot_OK()));
	connect(ui->m_BtnCancel,SIGNAL(clicked()),this,SLOT(slot_Cancel()));
 }


 void QLowFrepBinBoutDlg::slot_OK()
 {
	 CDvmData *pData;

	 long nBinA = ui->m_cbBinA->checkState();
	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("A");
	 if (pData != NULL)
	 {
		 pData->m_strValue = QString::number(nBinA);
		 ui->m_cbBinA->setChecked(nBinA);
	 }
		
	 long nBinB = ui->m_cbBinB->checkState();
	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("B");
	 if (pData != NULL)
	 {
		 pData->m_strValue = QString::number(nBinB);
		 ui->m_cbBinB->setChecked(nBinB);
	 }

	 long nBinC = ui->m_cbBinC->checkState();
	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("C");
	 if (pData != NULL)
	 {
		 pData->m_strValue = QString::number(nBinC);
		 ui->m_cbBinC->setChecked(nBinC);
	 }

	 long nBinD  = ui->m_cbBinD->checkState();
	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("R");
	 if (pData != NULL)
	 {
		 pData->m_strValue = QString::number(nBinD);
		 ui->m_cbBinD->setChecked(nBinD);
	 }

	 long nBinE  = ui->m_cbBinE->checkState();
	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("E");
	 if (pData != NULL)
	 {
		 pData->m_strValue = QString::number(nBinE);
		 ui->m_cbBinE->setChecked(nBinE);
	 }

	 long nBinF  = ui->m_cbBinF->checkState();
	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("F");
	 if (pData != NULL)
	 {
		 pData->m_strValue = QString::number(nBinF);
		 ui->m_cbBinF->setChecked(nBinF);
	 }

	 long nBinG  = ui->m_cbBinG->checkState();
	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("G");
	 if (pData != NULL)
	 {
		 pData->m_strValue = QString::number(nBinG);
		 ui->m_cbBinG->setChecked(nBinG);
	 }

	 long nBinH = ui->m_cbBinH->checkState();
	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("H");
	 if (pData != NULL)
	 {
		 pData->m_strValue = QString::number(nBinH);
		 ui->m_cbBinH->setChecked(nBinH);
	 }

	 long nBOut1 = ui->m_cbBOut1->checkState();
	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("_B01");
	 if (pData != NULL)
	 {
		 pData->m_strValue = QString::number(nBOut1);
		 ui->m_cbBOut1->setChecked(nBOut1);
	 }

	 long nBOut2 = ui->m_cbBOut2->checkState();
	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("_B02");
	 if (pData != NULL)
	 {
		 pData->m_strValue = QString::number(nBOut2);
		 ui->m_cbBOut2->setChecked(nBOut2);

	 }

	 long nBOut3 = ui->m_cbBOut3->checkState();
	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("_B03");
	 if (pData != NULL)
	 {
		 pData->m_strValue = QString::number(nBOut3);
		 ui->m_cbBOut3->setChecked(nBOut3);
	 }

	 long nBOut4 = ui->m_cbBOut4->checkState();
	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("_B04");
	 if (pData != NULL)
	 {
		 pData->m_strValue = QString::number(nBOut4);
		 ui->m_cbBOut4->setChecked(nBOut4);
	 }

	 long nBOut5 = ui->m_cbBOut5->checkState();
	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("_B05");
	 if (pData != NULL)
	 {
		 pData->m_strValue = QString::number(nBOut5);
		 ui->m_cbBOut5->setChecked(nBOut5);
	 }

	 long nBOut6 = ui->m_cbBOut6->checkState();
	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("_B06");
	 if (pData != NULL)
	 {
		 pData->m_strValue = QString::number(nBOut6);
		 ui->m_cbBOut6->setChecked(nBOut6);

	 }

	 long nBOut7 = ui->m_cbBOut7->checkState();
	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("_B07");
	 if (pData != NULL)
	 {
		 pData->m_strValue = QString::number(nBOut7);
		 ui->m_cbBOut7->setChecked(nBOut7);
	 }

	 long nBOut8 = ui->m_cbBOut8->checkState();
	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("_B08");
	 if (pData != NULL)
	 {
		 pData->m_strValue = QString::number(nBOut8);
		 ui->m_cbBOut8->setChecked(nBOut8);
	 }

	 long nrbOr = ui->m_rbOr->isCheckable();
	 pData = (CDvmData *)m_oLowFrepBinBoutDataGroup->FindByID("_AndOr");
	 if (pData != NULL)
	 {
		 pData->m_strValue = QString::number(nrbOr);
		 ui->m_rbOr->setChecked(nrbOr);
	 }
	 accept();
 }

 void QLowFrepBinBoutDlg::slot_Cancel()
 {
	 reject();
 }
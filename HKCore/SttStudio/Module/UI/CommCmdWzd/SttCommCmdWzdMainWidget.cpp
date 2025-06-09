#include "SttCommCmdWzdMainWidget.h"
#include "ui_SttCommCmdWzdMainWidget.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../SttGlobalDef.h"
#include "../SttTestCntrFrameBase.h"

#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"


#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
#include "../Config/MacroTestUI/SttMacroTestUI_TestMacroUIDB.h"
extern CGbSmartGenWzd *g_theGbSmartGenWzd;

void QSttCommCmdWzdMainWidget::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
	UpdateCmdGrid_ShowCurrStep(FALSE);
}

QSttCommCmdWzdMainWidget::QSttCommCmdWzdMainWidget(QFont font, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttCommCmdWzdMainWidget)
{
    ui->setupUi(this);
	

	xlang_SetLangStrToWidget_Txt(ui->pushButton_Pre,g_sLangTxt_Native_PrevStep,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->pushButton_Next,g_sLangTxt_NextStep,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->pushButton_Cancel,g_sLangTxt_Cancel,XLang_Ctrls_QPushButton);

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);

	m_font = font;
	m_pParentItem = NULL;
	m_bClickedFinish = FALSE;
	m_pGridWzd = new CSttCommCmdWzdGrid(this);
	m_pRegisterWidget = new CSttCmdWzdGrid_Register(this);

	UI_SetFont();

	m_pGridWzd->verticalHeader()->setHidden(true);
	m_pGridWzd->InitGrid();
	ui->horizontalLayoutWzd->insertWidget(0,m_pGridWzd);
	m_pGridWzd->AttachDataViewOptrInterface(this);

	//ѡ���ܼ�ͨѶ��������
    m_pSttSelMacroWidget = new QSttCommCmdWzd_SelMacroWidget(font, this);
    m_pSttSelMacroWidget->hide();

	//��ָ��
	m_pReadDsWidget = new QSttCommCmdWzd_DsReadWidget(font, this);
	m_pReadDsWidget->hide();

	//registerָ��
	m_pRegisterWidget->InitGrid();
	m_pRegisterWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_pRegisterWidget->hide();

	//дָ��
	m_pWriteDsWidget = new QSttCommCmdWzd_DsWriteWidget(font, this);
	m_pWriteDsWidget->hide();

	//�������
	m_pErrorValueWidget = new QSttCommCmdWzd_ErrorValueWidget(font, this);
	m_pErrorValueWidget->hide();

    ui->verticalLayout_Step->insertWidget(0,m_pSttSelMacroWidget);
	ui->verticalLayout_Step->insertWidget(0,m_pReadDsWidget);
	ui->verticalLayout_Step->insertWidget(0,m_pRegisterWidget);
	ui->verticalLayout_Step->insertWidget(0,m_pWriteDsWidget);
	ui->verticalLayout_Step->insertWidget(0,m_pErrorValueWidget);

	m_pSttSelMacroWidget->show();

	connect(ui->pushButton_Pre,SIGNAL(clicked()),this,SLOT(slot_PreClick()));
	connect(ui->pushButton_Next,SIGNAL(clicked()),this,SLOT(slot_NextClick()));
	connect(ui->pushButton_Cancel,SIGNAL(clicked()),this,SLOT(slot_CancelClick()));
	connect(this,SIGNAL(sig_Show_Hide_Widget(QWidget*, bool)),this,SLOT(slot_Show_Hide_Widget(QWidget*, bool)));
	connect(this,SIGNAL(sig_DisableNextBtn(bool)),this,SLOT(slot_DisableNextBtn(bool)));
	connect(this,SIGNAL(sig_DisablePreBtn(bool)),this,SLOT(slot_DisablePreBtn(bool)));
	connect(this,SIGNAL(sig_SetNextBtnText(const CString&)),this,SLOT(slot_SetNextBtnText(const CString&)));
	connect(this,SIGNAL(sig_SetNextBtnTextEx(const CString&)),this,SLOT(slot_SetNextBtnTextEx(const CString&)), Qt::BlockingQueuedConnection);
	connect(this,SIGNAL(sig_UpdateShowDsWrite(CDataGroup*)),this,SLOT(slot_UpdateShowDsWrite(CDataGroup*)));
	connect(this,SIGNAL(sig_OnAtsGenerateItems_CmdWzd(CExBaseList*)),this,SLOT(slot_OnAtsGenerateItems_CmdWzd(CExBaseList*)));
	//connect(this, SIGNAL(sig_FreeCommCmdWzdWidget()), g_theTestCntrFrame, SLOT(slot_FreeCommCmdWzdWidget()));

	m_strBFDelayTime_Setting = "2000";
	m_strAFTDelayTime_Setting = "2000";
	m_strBFDelayTime_Ena = "2000";
	m_strAFTDelayTime_Ena = "2000";
	m_strBFDelayTime_Parameter = "2000";
	m_strAFTDelayTime_Parameter = "2000";

	m_pGridWzd->hide();
}

QSttCommCmdWzdMainWidget::~QSttCommCmdWzdMainWidget()
{
    delete ui;
	delete m_pGridWzd;
    delete m_pSttSelMacroWidget;
	delete m_pReadDsWidget;
	delete m_pRegisterWidget;
	delete m_pWriteDsWidget;
}

void QSttCommCmdWzdMainWidget::NewGbMacroGenWzd(CString &strParentItemsID)
{
	m_pGbMacroGenWzd = g_theGbSmartGenWzd->NewGbMacroGenWzd();
	m_pGbMacroGenWzd->m_strParentItemsID = strParentItemsID;
	m_pGridWzd->ShowDatas(m_pGbMacroGenWzd);
	UpdateCmdGrid_ShowCurrStep(FALSE);
	EnableBtns(m_pSttSelMacroWidget);
	m_pSttSelMacroWidget->ShowGbMacroGenWzd();

	if (! m_pSttSelMacroWidget->IsHasCmdSelected())
	{
		SetNextBtnText(/*_T("���")*/g_sLangTxt_Native_Enter);
	}
}

void QSttCommCmdWzdMainWidget::UI_SetFont()
{
	ui->pushButton_Pre->setFont(m_font);
	ui->pushButton_Next->setFont(m_font);
	ui->pushButton_Cancel->setFont(m_font);
}

void QSttCommCmdWzdMainWidget::EnableBtns(QWidget *pWidget)
{
	ui->pushButton_Pre->setDisabled(false);
	ui->pushButton_Next->setDisabled(false);

	if (pWidget == m_pSttSelMacroWidget)
	{
		ui->pushButton_Pre->setDisabled(true);

		if (m_pGbMacroGenWzd->m_strTestClass.isEmpty()
			|| m_pSttSelMacroWidget->m_pCurrUIRef == NULL
			|| m_pGbMacroGenWzd->m_strItemsID.isEmpty()
			|| m_pGbMacroGenWzd->m_strItemsName.isEmpty())
		{
			ui->pushButton_Next->setDisabled(true);
		}

		if (m_pParentItem != NULL)
		{
			if (m_pParentItem->FindByID(m_pGbMacroGenWzd->m_strItemsID) != NULL)
			{
				ui->pushButton_Next->setDisabled(true);
			}

			if (m_pParentItem->FindByName(m_pGbMacroGenWzd->m_strItemsName) != NULL)
			{
				ui->pushButton_Next->setDisabled(true);
			}
		}
	}
}

//������Ͻǡ�����ȡ�������
void QSttCommCmdWzdMainWidget::reject()
{
	if (m_bClickedFinish)
	{
		return;
	}

	slot_CancelClick();
}

void QSttCommCmdWzdMainWidget::accept()
{
	emit sig_FreeCommCmdWzdWidget();
}

void QSttCommCmdWzdMainWidget::SetNextBtnText(const CString &strText)
{
	ui->pushButton_Next->setText(strText);
}

void QSttCommCmdWzdMainWidget::slot_PreClick()
{
	UpdateCmdGrid_ShowCurrStep(TRUE);  //�ָ���һ������ʾ�ɰ�ɫ��
	CSttCmdWzd_Step *pCurrSetpWzd = m_pGbMacroGenWzd->GetPreStep();
	//pCurrSetpWzd->RecoverCmdGrpRef();
	long nRet = Shwo_Hide_Widgets(FALSE);

	if (m_pGbMacroGenWzd->IsFirstSetp(pCurrSetpWzd))
	{
		m_pGbMacroGenWzd->m_pCmdGenParas->DeleteAll();
		m_pGbMacroGenWzd->GetFirstStep();
		m_pGridWzd->ShowDatas(m_pGbMacroGenWzd);
		ui->pushButton_Pre->setDisabled(true);
	}

	UpdateCmdGrid_ShowCurrStep(FALSE);  //������ʾ��ǰ����

	//emit sig_SetNextBtnText("��һ��");
	ui->pushButton_Next->setText(/*"��һ��"*/g_sLangTxt_NextStep);

	AutoClick(nRet);
}

void QSttCommCmdWzdMainWidget::slot_NextClick()
{
	CSttCmdWzd_Step *pCurrStep = m_pGbMacroGenWzd->CurrStep();
	
	//��ʼ״̬�£��ս����򵼣���ǰ����Ϊ���ڵ�
	if (m_pGbMacroGenWzd->IsFirstSetp(pCurrStep))
	{
		if (m_pSttSelMacroWidget->IsHasCmdSelected())
		{
			NextClick_Init();   //����ѡ��Ĺ��ܡ���ѡ��ͨѶ����·�cmd-wzdָ��
		}
		else
		{
			g_theGbSmartGenWzd->UpdateGbMacroGenWzdInit();
			NextClick_Finish();  //û�й�ѡͨѶ�����ֱ�ӽ���
		}
		return;
	}

	if (pCurrStep->m_pCmdGrpRef->m_strDataType == COMMCMD_RWOPTR_READ)
	{
		NextClick_Step_Read();
	}

	if (pCurrStep->m_pCmdGrpRef->m_strDataType == COMMCMD_RWOPTR_WRITE)
	{
		NextClick_Step_Write();
	}

	if (pCurrStep->m_pCmdGrpRef->m_strDataType == COMMCMD_RWOPTR_REGISTER)
	{
		NextClick_Step_Register();
	}

	if (m_pGbMacroGenWzd->IsLastSetp())
	{
		NextClick_Finish();
		return;
	}

	UpdateCmdGrid_ShowCurrStep(TRUE);  //�ָ���һ������ʾ�ɰ�ɫ��
	pCurrStep = m_pGbMacroGenWzd->GetNextStep();

	if (pCurrStep == NULL)
	{
		NextClick_Finish();
		return;
	}

	if (m_bClickedFinish)
	{
		return;
	}

	long nRet = Shwo_Hide_Widgets();
	UpdateCmdGrid_ShowCurrStep(FALSE);  //������ʾ��ǰ����

	if (m_pGbMacroGenWzd->IsLastSetp())
	{
		//emit sig_SetNextBtnText("���");
		ui->pushButton_Next->setText(/*"���"*/g_sLangTxt_Native_Enter);
	}

	AutoClick(nRet);
}

void QSttCommCmdWzdMainWidget::slot_CancelClick()
{
	g_theGbSmartGenWzd->CancelMacroGenWzd();
	emit sig_FreeCommCmdWzdWidget();
}

void QSttCommCmdWzdMainWidget::slot_Show_Hide_Widget(QWidget *pWidget, bool bShow)
{
	if (bShow)
	{
		pWidget->show();

		if (pWidget == m_pWriteDsWidget)
		{
			//���ɺ�ĵ�һ��������Ȼstep�ڵ�ֵ��2000,������û��ˢ��,��Ȼ��ʾΪ0,������Ҫ����һ��
			long nIndex = m_pWriteDsWidget->m_cmbDelayBft->findText("2000");
			m_pWriteDsWidget->m_cmbDelayBft->setCurrentIndex(nIndex);
			nIndex = m_pWriteDsWidget->m_cmbDelayAft->findText("2000");
			m_pWriteDsWidget->m_cmbDelayAft->setCurrentIndex(nIndex);
		}
	}
	else
	{
		pWidget->hide();
	}
}

void QSttCommCmdWzdMainWidget::slot_DisableNextBtn(bool bDisable)
{
	ui->pushButton_Next->setDisabled(bDisable);
}

void QSttCommCmdWzdMainWidget::slot_DisablePreBtn(bool bDisable)
{
	ui->pushButton_Pre->setDisabled(bDisable);
}

void QSttCommCmdWzdMainWidget::slot_SetNextBtnText(const CString& strText)
{
	ui->pushButton_Next->setText(strText);
}

void QSttCommCmdWzdMainWidget::slot_SetNextBtnTextEx(const CString& strText)
{
	slot_SetNextBtnText(strText);
}

void QSttCommCmdWzdMainWidget::slot_UpdateShowDsWrite(CDataGroup *pCmdGrp)
{
	m_pWriteDsWidget->UpdateShow(pCmdGrp);
}

void QSttCommCmdWzdMainWidget::slot_OnAtsGenerateItems_CmdWzd(CExBaseList *pCmdGrp)
{
	m_pGbMacroGenWzd->OnAtsGenerateItems_CmdWzd(pCmdGrp);
	delete pCmdGrp;   //���źŹ�������new������
	pCmdGrp = NULL;

	AddErrorEvaluteStep();

	for (int i = 0; i < m_pGbMacroGenWzd->m_oListCmdWzdStep.GetCount(); i++)
	{
		CSttCmdWzd_Step* pStep = (CSttCmdWzd_Step*)m_pGbMacroGenWzd->m_oListCmdWzdStep[i];

		if(!pStep->m_pCmdGrpBk)
		{
			continue;
		}

		if(pStep->m_pCmdGrpBk->m_strDataType == "write")
		{
			if(pStep->m_pCmdGrpBk->m_strID == "WriteSetting")
			{
				pStep->m_strDelayBft = m_strBFDelayTime_Setting;
				pStep->m_strDelayAft = m_strAFTDelayTime_Setting;
			}
			else if(pStep->m_pCmdGrpBk->m_strID == "WriteEna")
			{
				pStep->m_strDelayBft = m_strBFDelayTime_Ena;
				pStep->m_strDelayAft = m_strAFTDelayTime_Ena;
			}
			else if(pStep->m_pCmdGrpBk->m_strID == "WriteParameter")
			{
				pStep->m_strDelayBft = m_strBFDelayTime_Parameter;
				pStep->m_strDelayAft = m_strAFTDelayTime_Parameter;
			}
		}
	}

	// 	CString strFile;
	// 	strFile = _T("D:\\0\\ret.xml");
	// 	m_pGrpCmdWzdRet->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	//m_pGridWzd->ShowDatas(m_pGrpCmdWzdRet); 
	m_pGridWzd->ShowDatas(m_pGbMacroGenWzd); 
	//�յ�Ӧ��󣬽�����һ������ť�óɿɵ�״̬
	ui->pushButton_Next->setDisabled(false);
	ui->pushButton_Pre->setDisabled(false);
// 	emit sig_DisableNextBtn(false);
// 	emit sig_DisablePreBtn(false);

	//�յ�Ӧ�𣬱�ʾ��һ����ѡ����Թ��ܺ�ͨѶ����Ѿ����������ȡ��һ����
	//UpdateCmdGrid_ShowCurrStep(TRUE);  //����һ���ָ��ɰ�ɫ��ʾ
	m_pGbMacroGenWzd->GetNextStep();

	long nRet = Shwo_Hide_Widgets();
	//UpdateCmdGrid_ShowCurrStep(FALSE);  //������ʾ��ǰ����

	if (m_pGbMacroGenWzd->IsLastSetp())
	{
		//emit sig_SetNextBtnTextEx("���");
		ui->pushButton_Next->setText(/*"���"*/g_sLangTxt_Native_Enter);

	} 

// 	CTickCount32 oTick;
// 
// 	while ( !m_nInitFinished )
// 	{
// 		oTick.DoEvents(10);
// 	}

	AutoClick(nRet);
}

void QSttCommCmdWzdMainWidget::OnAtsGenerateItems_CmdWzd(CExBaseList *pCmdGrp)
{
	emit sig_OnAtsGenerateItems_CmdWzd(pCmdGrp);
}

//�ڻ�ȡ����һ���󣬸�����һ����ָ�ˢ�¶�Ӧ�Ľ������ʾ������
//����0 = �޲�����1 = ��һ����2 = ��һ����3 = ���
long QSttCommCmdWzdMainWidget::Shwo_Hide_Widgets(BOOL bNext)
{
	CSttCmdWzd_Step *pCurrStep = m_pGbMacroGenWzd->CurrStep();

	if (pCurrStep == NULL)
	{
		return 0;
	}

	//��ʼ״̬�£��ս����򵼣���ǰ����Ϊ���ڵ�
	if (m_pGbMacroGenWzd->IsFirstSetp(pCurrStep))
	{
// 		emit sig_Show_Hide_Widget(m_pWriteDsWidget, false);
// 		emit sig_Show_Hide_Widget(m_pRegisterWidget, false);
// 		emit sig_Show_Hide_Widget(m_pReadDsWidget, false);
// 		emit sig_Show_Hide_Widget(m_pSttSelMacroWidget, true);
// 		emit sig_Show_Hide_Widget(m_pErrorValueWidget, false);

		slot_Show_Hide_Widget(m_pWriteDsWidget, false);
		slot_Show_Hide_Widget(m_pRegisterWidget, false);
		slot_Show_Hide_Widget(m_pReadDsWidget, false);
		slot_Show_Hide_Widget(m_pSttSelMacroWidget, true);
		slot_Show_Hide_Widget(m_pErrorValueWidget, false);
		return 0;
	}

	if (pCurrStep->m_pCmdGrpRef->m_strDataType == COMMCMD_RWOPTR_READ)
	{
// 		emit sig_Show_Hide_Widget(m_pWriteDsWidget, false);
// 		emit sig_Show_Hide_Widget(m_pRegisterWidget, false);
// 		emit sig_Show_Hide_Widget(m_pSttSelMacroWidget, false);
// 		emit sig_Show_Hide_Widget(m_pReadDsWidget, true);
// 		m_pReadDsWidget->ShowDatas(pCurrStep);
		if(bNext)
		{
			//slot_NextClick();
			return 1;
		}
		else
		{
			//slot_PreClick();
			return 2;
		}
	}

	if (pCurrStep->m_pCmdGrpRef->m_strDataType == COMMCMD_RWOPTR_WRITE)
	{
		m_pWriteDsWidget->m_pSetpWzd = pCurrStep;

		if(((CDataGroup*)pCurrStep->m_pCmdGrpRef->GetParent())->m_strID == STT_CMD_PARA_After_Test)
		{
			//slot_NextClick();
			return 1;
		}

// 		emit sig_Show_Hide_Widget(m_pReadDsWidget, false);
// 		emit sig_Show_Hide_Widget(m_pSttSelMacroWidget, false);
//  	emit sig_Show_Hide_Widget(m_pRegisterWidget, false);
//  	emit sig_Show_Hide_Widget(m_pWriteDsWidget, true);
// 		emit sig_Show_Hide_Widget(m_pErrorValueWidget, false);

		slot_Show_Hide_Widget(m_pReadDsWidget, false);
		slot_Show_Hide_Widget(m_pSttSelMacroWidget, false);
		slot_Show_Hide_Widget(m_pRegisterWidget, false);
		slot_Show_Hide_Widget(m_pWriteDsWidget, true);
		slot_Show_Hide_Widget(m_pErrorValueWidget, false);

		//emit sig_UpdateShowDsWrite(pCurrStep->m_pCmdGrpRef);
		m_pWriteDsWidget->ShowDatas(pCurrStep->m_pCmdGrpRef, pCurrStep->m_pCmdGrpBk);
		return 0;
	}

	if (pCurrStep->m_pCmdGrpRef->m_strDataType == COMMCMD_RWOPTR_REGISTER)
	{
		/*
		emit sig_Show_Hide_Widget(m_pWriteDsWidget, false);
		emit sig_Show_Hide_Widget(m_pSttSelMacroWidget, false);
		emit sig_Show_Hide_Widget(m_pReadDsWidget, false);
		emit sig_Show_Hide_Widget(m_pRegisterWidget, true);
		emit sig_Show_Hide_Widget(m_pErrorValueWidget, false);
		m_pRegisterWidget->ShowDatas(pCurrStep);
		return;
		*/
		if(bNext)
		{
			//slot_NextClick();
			return 1;
		}
		else
		{
			//slot_PreClick();
			return 2;
		}
	}

	if (pCurrStep->m_pCmdGrpRef->m_strDataType == "")
	{
// 		emit sig_Show_Hide_Widget(m_pWriteDsWidget, false);
// 		emit sig_Show_Hide_Widget(m_pSttSelMacroWidget, false);
// 		emit sig_Show_Hide_Widget(m_pReadDsWidget, false);
// 		emit sig_Show_Hide_Widget(m_pRegisterWidget, false);
// 		emit sig_Show_Hide_Widget(m_pErrorValueWidget, true);

		slot_Show_Hide_Widget(m_pWriteDsWidget, false);
		slot_Show_Hide_Widget(m_pSttSelMacroWidget, false);
		slot_Show_Hide_Widget(m_pReadDsWidget, false);
		slot_Show_Hide_Widget(m_pRegisterWidget, false);
		slot_Show_Hide_Widget(m_pErrorValueWidget, true);

		m_pErrorValueWidget->ShowDatas(&g_theTestCntrFrame->m_oErrorValueWzdGroup);
	}

	return 0;
}

void QSttCommCmdWzdMainWidget::UpdateCmdGrid_ShowCurrStep(BOOL bReset)
{
	CSttCmdWzd_Step *pCurrStep = m_pGbMacroGenWzd->CurrStep();

	if (pCurrStep == NULL)
	{
		return;
	}

	m_pGridWzd->Update_ShowCurr(pCurrStep->m_pCmdGrpRef, bReset);
}

/*
pCommCmdCfg�����ݽṹ���£�

<group name="����ǰ׼��" id="cmd-bft" data-type="cmd-bft">
	<data name="����ֵ" id="ReadSetting" format="dsSetting" value="ReadSetting"/>
	<data name="����ѹ��" id="ReadEna" format="dsEna" value="ReadEna"/>
	<data name="�޸Ķ�ֵ" id="WriteSetting" format="dsSetting" value="WriteSetting"/>
	<data name="Ͷ����ѹ��" id="WriteEna" format="dsEna" value="WriteEna"/>
	<data name="��װ�ò���" id="ReadParameter" format="dsParameter" value="ReadParameter"/>
	<data name="�޸�װ�ò���" id="WriteParameter" format="dsParameter" value="WriteParameter"/>
	<data name="��������" id="RegisterReport" format="all" value="RegisterReport"/>
	<data name="ֹͣ����" id="UnRegisterReport" format="all" value="UnRegisterReport"/>
</group>
<group name="���Ժ�ָ�" id="cmd-aft" data-type="cmd-aft">
	<data name="�޸Ķ�ֵ" id="WriteSetting" format="dsSetting" value="WriteSetting"/>
	<data name="Ͷ����ѹ��" id="WriteEna" format="dsEna" value="WriteEna"/>
	<data name="�޸�װ�ò���" id="WriteParameter" format="dsParameter" value="WriteParameter"/>
	<data name="ֹͣ����" id="UnRegisterReport" format="all" value="UnRegisterReport"/>
</group>
*/
void QSttCommCmdWzdMainWidget::NextClick_Init()
{
	CDataGroup oCommCmd;
	BOOL bAdd_AFT = g_theTestCntrFrame->IsNeedAddAft();
	m_pGbMacroGenWzd->NextClick_Init(oCommCmd, bAdd_AFT);

	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_GenrateItems_CmdWzd(m_pParentItem, &oCommCmd
		, m_pSttSelMacroWidget->m_pCurrUIRef->m_strName, m_pGbMacroGenWzd->m_strTestClass, STT_CMD_Send_Async);

	if (nRet == 3/*STT_CMD_ExecStatus_SUCCESS*/)
	{
		//���ͳɹ������ûң��ȴ�Ӧ��
		//ui->pushButton_Next->setDisabled(true);
	}

	//2022-10-4  lijunqing ���䱣��ΪĬ��ѡ��
	g_theGbSmartGenWzd->UpdateGbMacroGenWzdInit();
}

void QSttCommCmdWzdMainWidget::NextClick_Step_Write()
{
	CSttCmdWzd_Step *pCurrStep = m_pGbMacroGenWzd->CurrStep();

	if (pCurrStep == NULL)
	{
		return;
	}

	if (pCurrStep->m_pCmdGrpRef->m_strDataType != COMMCMD_RWOPTR_WRITE)
	{
		return;
	}

	//дָ�ֻ��һ���������ݼ�����˿���ֱ��GetHead
	CDataGroup *pCmdDatas = (CDataGroup *)pCurrStep->m_pCmdGrpRef->GetHead();
	CSttCmdWzd_Step *pRelatedStep = m_pGbMacroGenWzd->GetRelatedStep(pCurrStep);

	if (pRelatedStep == NULL)
	{
		return;
	}

	//���ݵ�ǰ����Ĳ�������ͨѶ��ָ��еĲ������Զ��Ļ�Ĭ��ֵ
	//дָ�ֻ��һ���������ݼ�����˿���ֱ��GetHead
	CDataGroup *pGrpDs = (CDataGroup *)pRelatedStep->m_pCmdGrpRef->GetHead();
	CDataGroup *pGrpDsBk = (CDataGroup *)pRelatedStep->m_pCmdGrpBk->GetHead();
	POS pos = pCmdDatas->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pCmdData = (CDvmData *)pCmdDatas->GetNext(pos);
		CDvmData *pFind = (CDvmData *)pGrpDs->FindByID(pCmdData->m_strID);

		if (pFind != NULL)
		{
			//pFind->m_strValue = pFind->m_strDefaultValue;
			pFind->m_strDefaultValue = pCmdData->m_strValue;
		}

		//���ݵ���������ͬ�Ĵ���
		pFind = (CDvmData *)pGrpDsBk->FindByID(pCmdData->m_strID);

		if (pFind != NULL)
		{
			//pFind->m_strValue = pFind->m_strDefaultValue;
			pFind->m_strDefaultValue = pCmdData->m_strValue;
		}
	}
}

void QSttCommCmdWzdMainWidget::NextClick_Step_Register()
{
	CSttCmdWzd_Step *pCurrStep = m_pGbMacroGenWzd->CurrStep();

	if (pCurrStep == NULL)
	{
		return;
	}

	if (pCurrStep->m_pCmdGrpRef->m_strDataType != COMMCMD_RWOPTR_REGISTER)
	{
		return;
	}
}

void QSttCommCmdWzdMainWidget::NextClick_Step_Read()
{
	CSttCmdWzd_Step *pCurrStep = m_pGbMacroGenWzd->CurrStep();

	if (pCurrStep == NULL)
	{
		return;
	}

	if (pCurrStep->m_pCmdGrpRef->m_strDataType != COMMCMD_RWOPTR_READ)
	{
		return;
	}	
}

void QSttCommCmdWzdMainWidget::ResetDataset(CDataGroup* pDataGroup)
{
	//���ϲ������ݷ��ص����������ݼ���
	POS pos = pDataGroup->GetHeadPosition();
	while (pos)
	{
		CDataGroup* pDataset = (CDataGroup*)pDataGroup->GetNext(pos);
		POS posChild = pDataset->GetHeadPosition();
		while (posChild)
		{
			CDataGroup* pChild = (CDataGroup*)pDataset->GetNext(posChild);
			POS posData = pChild->GetHeadPosition();
			while (posData)
			{
				CDvmData* pData = (CDvmData*)pChild->GetNext(posData);

				if (!pData->m_nChange)
				{
					pChild->Delete(pData);
					continue;
				}

				if(pData->GetParent() != pChild)
				{
					CDataGroup* pSrcGroup = (CDataGroup*)pData->GetParent();
					pChild->Remove(pData);
					pSrcGroup->AddTail(pData);
				}
			}
		}
	}
}

//�ƶ���CDvmData��  shaolei 2023-7-28
// CDvmValue* QSttCommCmdWzdMainWidget::GetDataValue(CDvmData *pData)
// {
// 	if (pData->GetCount() == 0)
// 	{
// 		return (CDvmValue*)pData->GetHead();
// 	}
// 
// 	POS pos = pData->GetHeadPosition();
// 	CDvmValue *p = NULL;
// 	CString strRight;
// 
// 	while (pos != NULL)
// 	{
// 		p = (CDvmValue *)pData->GetNext(pos);
// 		strRight = p->m_strID.right(2);
// 
// 		if (strRight == "$t" || strRight == "$q")
// 		{
// 			continue;
// 		}
// 
// 		return p;
// 	}
// 
// 	return (CDvmValue*)pData->GetHead();
// }

void QSttCommCmdWzdMainWidget::AutoCompleteAfterTest()
{
	CDataGroup* pBF = (CDataGroup*)m_pGbMacroGenWzd->m_pCmdGenParas->GetHead();  //����ǰ׼��
	CDataGroup* pAFT = (CDataGroup*)m_pGbMacroGenWzd->m_pCmdGenParas->GetTail();  //���Ժ�ָ�

	//CString strIDPath;
	POS pos = pAFT->GetHeadPosition();
	while(pos)
	{
		CDataGroup* pChild = (CDataGroup*)pAFT->GetNext(pos);   //��Ӧһ��ͨѶ������һ��
		if(pChild->m_strDataType == "read")
		{
			//������ָ��
			continue;
		}

		/*
		strIDPath = pChild->m_strID;
		pChild = (CDataGroup*)pChild->GetHead();
		strIDPath += "&";
		strIDPath += pChild->m_strID;
		strIDPath += "&";
		*/
		CDataGroup *pdsGrp = (CDataGroup *)pChild->GetHead();  //��Ӧ���ݼ�·����һ����һ��ͨѶ�����Ӧһ�����ݼ�
		POS posChild = pdsGrp->GetHeadPosition();

		while(posChild)
		{
			CDvmData* pAFTData = (CDvmData*)pdsGrp->GetNext(posChild);
	
			if((pAFTData->m_strName.Find("Զ��Ͷ��ѹ��") != -1)
				|| (pAFTData->m_strName.Find("Զ���л���ֵ��") != -1)
				|| (pAFTData->m_strName.Find("Զ���޸Ķ�ֵ") != -1)
				|| (pAFTData->m_strName.Find("Զ��������ѹ��") != -1))
			{
				continue;
			}

			//CDvmValue* pAFTValue = pAFTData->GetDataValue();
			//CDvmData* pData = (CDvmData*)pBF->SelectData(strIDPath + pAFTData->m_strID, "&");
			CDvmData* pData = (CDvmData *)SelectReleatedData(pBF, pdsGrp, pAFTData);  //�Ӳ���ǰ׼���У��ҵ���Ӧ��ͨѶ������

			if (pData == NULL)
			{
				continue;
			}

			CDvmValue* pValue = pData->GetDataValue();

			if(pValue)
			{
				if(pData && pValue->m_strDataType == "BOOL" && pData->m_nChange)
				{
					if(pData->m_strValue == "0")
					{
						pAFTData->m_strValue = "1";
					}
					else
					{
						pAFTData->m_strValue = "0";
					}
					pAFTData->m_nChange = 1;
				}
			}
			else
			{
				if(pData && pData->m_strDataType == "BOOL" && pData->m_nChange)
				{
					if(pData->m_strValue == "0")
					{
						pAFTData->m_strValue = "1";
					}
					else
					{
						pAFTData->m_strValue = "0";
					}
					pAFTData->m_nChange = 1;
				}
			}
		}
	}

	//ȷ�ϵ�ǰ���޸ĵ�ֵ�Ƿ����ڵ�ǰ���ݼ�,������˵���Ӧ�����ݼ���
	ResetDataset(pBF);
	ResetDataset(pAFT);
}

//�β�1����Ӧһ��ͨѶ�����Group����
//�β�2����Ӧ���ݼ���group
//�β�3��һ��ͨѶ�����ͨѶ����
CDvmData* QSttCommCmdWzdMainWidget::SelectReleatedData(CDataGroup *pSrcGrp, CDataGroup* pSrcdsGrp, CDvmData *pDestData)
{
	if (pSrcdsGrp == NULL || pSrcGrp == NULL || pDestData == NULL)
	{
		return NULL;
	}

	if (pSrcGrp->GetCount() == 0)
	{
		return NULL;
	}

	CDataGroup *pParent = (CDataGroup *)pSrcdsGrp->GetParent();
	POS pos = pSrcGrp->GetHeadPosition();

	while (pos != NULL)
	{
		CDataGroup *pChild = (CDataGroup *)pSrcGrp->GetNext(pos);

		if (pChild->m_strName != pParent->m_strName
			|| pChild->m_strID != pParent->m_strID
			|| pChild->m_strDataType != pParent->m_strDataType)
		{
			continue;
		}

		//���ҵ���Ӧ��ͬ���͵�ͨѶ����
		CDataGroup *pHead = (CDataGroup *)pChild->GetHead();

		if (pHead->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		if (pHead->m_strID != pSrcdsGrp->m_strID)
		{
			//���ݼ���һ�£���ʾ����ͬһ��ͨѶ����
			continue;
		}

		return (CDvmData *)pHead->FindByID(pDestData->m_strID);
	}

	return NULL;
}

void QSttCommCmdWzdMainWidget::AddErrorEvaluteStep()
{
	//����޸�������
	CSttMacroTestUI_TestMacroUI* pMacro = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(m_pGbMacroGenWzd->m_strTestMacroUI);
	g_theTestCntrFrame->m_oErrorValueWzdGroup.DeleteAll();
	m_pErrorValueWidget->m_strTestMacroID = pMacro->m_strID;

	if(pMacro->m_strUI_ParaFile.GetLength())
	{
		CDataGroup oGroup, oTempGroup;
		CString strPath = _P_GetDBPath();
		strPath += "atsgen/";
		strPath += pMacro->m_strUI_ParaFile;
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
		oGroup.OpenXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

		if (pMacro->m_strID == STT_CMD_ATS_MACRO_ID_StateTest)
		{
			//״̬�������⴦��
			CDataGroup *pGrp = (CDataGroup *)oGroup.FindByID(_T("rslt_evaluation"));
			g_theTestCntrFrame->m_oErrorValueWzdGroup.AppendEx(*pGrp);
			oGroup.Remove(pGrp);
		}
		else
		{
			oGroup.SelectDatas_IDHas("_AbsErr", oTempGroup, TRUE);
			oGroup.SelectDatas_IDHas("_RelErr", oTempGroup, TRUE);

			if (oTempGroup.GetCount() == 0)
			{
				return;
			}

			g_theTestCntrFrame->m_oErrorValueWzdGroup.AppendCloneEx(oTempGroup);
			oTempGroup.RemoveAll();
		}

		if(g_theTestCntrFrame->m_oErrorValueWzdGroup.GetCount())
		{
			CSttCmdWzd_Step* pCmdDatasets = new CSttCmdWzd_Step;
			pCmdDatasets->m_pCmdGrpRef = &g_theTestCntrFrame->m_oErrorValueWzdGroup;
			// 	pCmdDatasets->m_strID = pErrorData->m_strID;
			// 	pCmdDatasets->m_strName = pErrorData->m_strName;

			CDataGroup oBF, oAFT;
			for (int i = m_pGbMacroGenWzd->m_oListCmdWzdStep.GetCount() - 1; i >= 0; i--)
			{
				CSttCmdWzd_Step* pStep = (CSttCmdWzd_Step*)m_pGbMacroGenWzd->m_oListCmdWzdStep.GetAt(i);
				if(pStep->m_strType == STT_ITEMS_ID_AFTERTEST)
				{
					oAFT.AddHead(pStep);
				}
				else
				{
					oBF.AddHead(pStep);
				}
				m_pGbMacroGenWzd->m_oListCmdWzdStep.RemoveAt(i);
			}
			oBF.AddTail(pCmdDatasets);

			for(int i = 0; i < oBF.GetCount(); i++)
			{
				m_pGbMacroGenWzd->m_oListCmdWzdStep.AddNewChild(oBF.GetAt(i));
			}
			for(int i = 0; i < oAFT.GetCount(); i++)
			{
				m_pGbMacroGenWzd->m_oListCmdWzdStep.AddNewChild(oAFT.GetAt(i));
			}
			oBF.RemoveAll();
			oAFT.RemoveAll();
		}
	}
}

void QSttCommCmdWzdMainWidget::AutoClick(long nOptr)
{
	switch (nOptr)
	{
	case 1:
		slot_NextClick();
		break;
	case 2:
		slot_PreClick();
		break;
	case 3:
		NextClick_Finish();
		break;
	default:
		break;
	}
}

void QSttCommCmdWzdMainWidget::OnChangeDelayTime(CDataGroup* pDataGroup)
{
	if(pDataGroup->m_strID == "WriteSetting")
	{
		CDvmData* pData = (CDvmData*)pDataGroup->FindByID(STT_CMD_PARA_DelayAfterCmd);
		pData->m_strValue = m_strAFTDelayTime_Setting;
		pData = (CDvmData*)pDataGroup->FindByID(STT_CMD_PARA_DelayBeforeCmd);
		pData->m_strValue = m_strBFDelayTime_Setting;
	}
	else if(pDataGroup->m_strID == "WriteEna")
	{
		CDvmData* pData = (CDvmData*)pDataGroup->FindByID(STT_CMD_PARA_DelayAfterCmd);
		pData->m_strValue = m_strAFTDelayTime_Ena;
		pData = (CDvmData*)pDataGroup->FindByID(STT_CMD_PARA_DelayBeforeCmd);
		pData->m_strValue = m_strBFDelayTime_Ena;
	}
	else if (pDataGroup->m_strID == "WriteParameter")
	{
		CDvmData* pData = (CDvmData*)pDataGroup->FindByID(STT_CMD_PARA_DelayAfterCmd);
		pData->m_strValue = m_strAFTDelayTime_Parameter;
		pData = (CDvmData*)pDataGroup->FindByID(STT_CMD_PARA_DelayBeforeCmd);
		pData->m_strValue = m_strBFDelayTime_Parameter;
	}
}

void QSttCommCmdWzdMainWidget::NextClick_Finish()
{
	AutoCompleteAfterTest();
	m_pErrorValueWidget->FinishEditDatas(&g_theTestCntrFrame->m_oErrorValueWzdGroup);

	m_bClickedFinish = TRUE;
	//emit sig_DisableNextBtn(true);
	ui->pushButton_Next->setDisabled(true);
	setEnabled(false);
	//ui->pushButton_Next->setDisabled(true);

	//��������GenerateItems���ģ���comm-cmd����
	CDataGroup oCommCmd;
	m_pGbMacroGenWzd->NextClick_Finish(oCommCmd);
	m_pGbMacroGenWzd->m_nRepeatTimes = m_pSttSelMacroWidget->GetRepeatTimes();
	m_pGbMacroGenWzd->m_nRptTitle = m_pSttSelMacroWidget->GetRptTitle();
	m_pGbMacroGenWzd->m_nTitleLevel = m_pSttSelMacroWidget->GetTitleLevel();

	CDataGroup* pBF = (CDataGroup*)oCommCmd.GetHead();
	CDataGroup* pAFT = (CDataGroup*)oCommCmd.GetTail();
	for (int i = 0; i < pBF->GetCount(); i++)
	{
		CDataGroup* pGroup = (CDataGroup*)pBF->GetAt(i);
		OnChangeDelayTime(pGroup);
	}

	for (int i = 0; i < pAFT->GetCount(); i++)
	{
		CDataGroup* pGroup = (CDataGroup*)pAFT->GetAt(i);
		OnChangeDelayTime(pGroup);
	}

	if (m_pSttSelMacroWidget->IsHasCmdSelected())
	{
		g_theTestCntrFrame->SelectTestMacro_CmdWzd(m_pGbMacroGenWzd->m_strTestMacroUI, m_pGbMacroGenWzd->m_strItemsName
			, m_pGbMacroGenWzd->m_strItemsID, &oCommCmd, m_pGbMacroGenWzd->m_strTestClass
			, g_theGbSmartGenWzd->m_pDvmDevice->m_strID, m_pGbMacroGenWzd->m_nRepeatTimes
			, m_pGbMacroGenWzd->m_nRptTitle, m_pGbMacroGenWzd->m_nTitleLevel);
	}
	else
	{
		g_theTestCntrFrame->SelectTestMacro_CmdWzd(m_pGbMacroGenWzd->m_strTestMacroUI, m_pGbMacroGenWzd->m_strItemsName
			, m_pGbMacroGenWzd->m_strItemsID, NULL, m_pGbMacroGenWzd->m_strTestClass
			, g_theGbSmartGenWzd->m_pDvmDevice->m_strID, m_pGbMacroGenWzd->m_nRepeatTimes
			, m_pGbMacroGenWzd->m_nRptTitle, m_pGbMacroGenWzd->m_nTitleLevel);
	}

	//2022-9-12 lijunqing ��¼�ͱ�����Թ��ܲ�����
	g_theTestCntrFrame->SaveMacroParasToCurrWzd(&oCommCmd);

	accept();
	//close();//close����õ�reject()?

// 	if(g_theTestCntrFrame->m_pSttGbTreeView->m_pCurrSelRootNode->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
// 	{
// 		CSttItems* pSttItems = (CSttItems*)g_theTestCntrFrame->m_pSttGbTreeView->m_pCurrSelRootNode;
// 		pSttItems->m_nRepeatTimes = m_pSttSelMacroWidget->GetRepeatTimes();
// 	}

	//emit sig_FreeCommCmdWzdWidget();
	//slot_OnFreeCommCmdWzdWidget();
}

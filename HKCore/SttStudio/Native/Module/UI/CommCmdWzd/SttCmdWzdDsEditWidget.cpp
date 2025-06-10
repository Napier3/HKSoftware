#include "SttCmdWzdDsEditWidget.h"
#include "ui_SttCmdWzdDsEditWidget.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../SttGlobalDef.h"
#include "../SttTestCntrFrameBase.h"
#include "SettingZoneComboBox.h"
#include "CmdDelayComboBox.h"
#include "SttCmdWzdDataAddWidget.h"
#include "../../../../Module/BaseClass/QT/ExBaseListComboBox.h"

#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
extern CGbSmartGenWzd *g_theGbSmartGenWzd;

void QSttCmdWzdDsEditWidget::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
	EnableBtns();
}

QSttCmdWzdDsEditWidget::QSttCmdWzdDsEditWidget(QFont font, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttCmdWzdDsEditWidget)
{
    ui->setupUi(this);
	InitLanguage();
	m_bIsCommcmdChanged = FALSE;
	m_bAutoSave = TRUE;
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	m_pEditGrid_Write = new CSttCmdWzdDsEditGrid(this);
	m_pEditGrid_Write->InitTypeRwOptr(COMMCMD_RWOPTR_WRITE);
	m_pEditGrid_Write->InitGrid();
	m_pEditGrid_Write->AttachDataViewOptrInterface(this);
	ui->verticalLayout->insertWidget(2, m_pEditGrid_Write);
	//m_pEditGrid->setVisible(false);

	m_pEditGrid_Read = new CSttCmdWzdDsEditGrid(this);
	m_pEditGrid_Read->InitTypeRwOptr(COMMCMD_RWOPTR_READ);
	m_pEditGrid_Read->InitGrid();
	m_pEditGrid_Read->AttachDataViewOptrInterface(this);
	ui->verticalLayout->insertWidget(3, m_pEditGrid_Read);

	m_pRegisterGrid = new CSttCmdWzdDsEditGrid_Register(this);
	m_pRegisterGrid->InitGrid();
	m_pRegisterGrid->AttachDataViewOptrInterface(this);
	ui->verticalLayout->insertWidget(4, m_pRegisterGrid);
	//m_pRegisterGrid->setVisible(false);

	UI_SetFont(font);
	SettingZoneComboBox_Init(ui->m_cmbSetZone);
	CmdDelayComboBox_Init(ui->m_cmbDelayBft, g_theGbSmartGenWzd->m_pCmdDelay);
	CmdDelayComboBox_Init(ui->m_cmbDelayAft, g_theGbSmartGenWzd->m_pCmdDelay);

	m_pCurrCmdItem = NULL;
	m_pCurrDataset = NULL;
	m_pCommCmdAdd = NULL;
	m_pCurrWzd = NULL;

	connect(this, SIGNAL(sig_Show_CommCmd()), this, SLOT(slot_Show_CommCmd()));

	connect(m_pEditGrid_Write,SIGNAL(sig_CmdWzd_UpdateData(CDvmData*)),this,
		SLOT(slot_CmdWzd_UpdateData(CDvmData*)),Qt::DirectConnection);

	connect(m_pEditGrid_Write,SIGNAL(sig_CmdWzd_UpdateData_Value(CValue*)),this,
		SLOT(slot_CmdWzd_UpdateData_Value(CValue*)),Qt::DirectConnection);

	connect(m_pRegisterGrid,SIGNAL(sig_CmdWzd_UpdateData_Value(CValue*)),this,
		SLOT(slot_CmdWzd_UpdateData_Value(CValue*)),Qt::DirectConnection);
	/*
	connect(m_pRegisterGrid,SIGNAL(sig_CmdWzd_UpdateData_Value(CValue*)),this,
		SLOT(slot_CmdWzd_UpdateData_Value(CValue*)),Qt::DirectConnection);
		*/
}

QSttCmdWzdDsEditWidget::~QSttCmdWzdDsEditWidget()
{
    delete ui;

	if (m_bAutoSave)
	{
		AutoSave_AfterEdit();
	}
	
	m_listDataset.RemoveAll();
}

void QSttCmdWzdDsEditWidget::ShowCmd(CSttItemBase *pSttItem)
{
	m_pCurrCmdItem = (CSttCommCmd*)pSttItem;
	CExBaseObject *pParent = NULL;
	CString strPath;
	CDvmData *pCmdCfgData = NULL;
	m_pCommCmdAdd = NULL;
	m_pCurrWzd = NULL;

	//2022-9-19  lijunqing  
	pParent = (CExBaseObject*)m_pCurrCmdItem->GetParent();
	strPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	CGbWzdXItemBase* pBase = g_theGbSmartGenWzd->FindXItemBase(m_pCurrCmdItem->m_strID, strPath);

	if (pBase != NULL)
	{
		if (pBase->GetClassID() == DVMCLASSID_GBWZDCOMMCMDADD)
		{
			m_pCommCmdAdd = (CGbWzdCommCmdAdd *)pBase;
		}
	}
	
	CSttItems *pRootItems = (CSttItems *)Stt_GetFirstParentItems(pSttItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);

	if (m_pCommCmdAdd != NULL)
	{
		//������ӵ�ͨ������,m_pCurrWzd��������Ϊ��
		m_pCurrWzd = NULL;

		if (m_pCommCmdAdd->GetClassID() != DVMCLASSID_GBWZDCOMMCMDADD)
		{
			//�˴��������δ���
			//???
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, /*_T("��Ŀ��%s����Ӧ���򵼲�����Ϣ����ȷ��")*/g_sLangTxt_wizard.GetString()
				, m_pCurrCmdItem->m_strName.GetString());
		}

		//����m_strCommCmdID�����������������
		pCmdCfgData = g_theGbSmartGenWzd->GetCmdCfgData(m_pCommCmdAdd->m_strCommCmdID, STT_CMD_PARA_CMDSINGLE);
	}
	else if (m_pCommCmdAdd == NULL && pRootItems != NULL && pSttItem->m_strID.Find(_T("Reset")) < 0)//װ�ø���̬��ͨѶ���ID�̶�������Reset��
	{//ͨ������ǵ�����ӵ�ͨ�����ͨ������ӵ������������ǰ׼�������Ժ�ظ��е��������������װ�ø���̬�е����
		//��ȡ��Ŀ���ڵ���Ŀ�����Ŀ¼
		//���ݸ�Ŀ¼����򵼶���  CGbMacroGenWzd
		pParent = (CExBaseObject*)pRootItems->GetParent();
		strPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

		//�������ӵ������ܡ������������
		m_pCurrWzd = g_theGbSmartGenWzd->FindMacroGen(pRootItems->m_strID, pRootItems->m_strName, strPath);

		//����m_strCommCmdID�����������������
		CExBaseObject *pParent = (CExBaseObject *)m_pCurrCmdItem->GetParent();

		CString strCfgID = STT_CMD_PARA_CMDBFT;  //Ĭ���ǲ���ǰ׼��

		if (pParent->m_strID == STT_CMD_PARA_After_Test)
		{
			strCfgID = STT_CMD_PARA_CMDAFT;
		}

		pCmdCfgData = g_theGbSmartGenWzd->GetCmdCfgData(m_pCurrCmdItem->m_strCommCmdID, strCfgID);

		if (pCmdCfgData == NULL)
		{
			//˵��������ͨ������ճ���ķ�ʽ��ӵ�ͨѶ������Ŀ
			pCmdCfgData = g_theGbSmartGenWzd->GetCmdCfgData(m_pCurrCmdItem->m_strCommCmdID, STT_CMD_PARA_CMDSINGLE);
		}

		CDataGroup *pCmdGenParas = m_pCurrWzd->GetCmdGenParas();

		if (pCmdGenParas->GetCount() == 0)
		{
			//˵��ͨѶ�����ͨ�����򵼡���ӣ�Ҳ����ͨ����ѡ���ܡ���ť���
			//ͨѶ�����ǵ�����ӵġ�����ǰ����ͨѶ��ϡ�������װ�ø���̬����ͨ��comm-cmd-update����
			m_pCurrWzd = NULL;
		}
	}
	else
	{
		//����װ�ø���̬�У���ӵ�ͨѶ����
		m_pCurrWzd = NULL;
		//����m_strCommCmdID�����������������
		pCmdCfgData = g_theGbSmartGenWzd->GetCmdCfgData(m_pCurrCmdItem->m_strCommCmdID, STT_CMD_PARA_CMDSINGLE);
	}
	

	if (pCmdCfgData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("QSttCmdWzdDsEditWidget::ShowCmd(CSttItemBase *pSttItem)   ----1"));
		return;
	}

	//���������������ݵ�Format��Key�����������������ݼ�
	if (pCmdCfgData->m_strFormat == _T("all"))
	{
		m_strDatasetKey = pCmdCfgData->m_strFormat;
		CStringArray strArrayKey;

		if (m_pCurrWzd != NULL)
		{
			//ֻ������ӵ�ͨѶ�������ͨ��TestClass���н�һ��ɸѡ
			//commcmd-wzd-cfg.xml�У����ݲ������ͣ����н�һ��ɸѡ
			CDataGroup *pTestClass = (CDataGroup *)g_theGbSmartGenWzd->m_pTestClass->FindByID(m_pCurrWzd->m_strTestClass);
			CDataGroup *pTestClassCmd = (CDataGroup *)pTestClass->FindByID(pCmdCfgData->m_strID);

			if (pTestClassCmd != NULL)
			{
				POS pos = pTestClassCmd->GetHeadPosition();

				while (pos != NULL)
				{
					CDvmData *pData = (CDvmData *)pTestClassCmd->GetNext(pos);
					GetDsKey(strArrayKey, pData->m_strID);
				}
			}
		}

		if (strArrayKey.GetCount() == 0)
		{
			strArrayKey.Add(m_strDatasetKey);
		}

		m_listDataset.RemoveAll();
		g_theGbSmartGenWzd->m_pDvmDevice->GetDatasetList(strArrayKey, m_listDataset);

		ex_InsertChildreComboBox(&m_listDataset, ui->m_cmbDataset, TRUE, -1);
	}
	else if (m_strDatasetKey != pCmdCfgData->m_strFormat)
	{
		m_listDataset.RemoveAll();
		m_strDatasetKey = pCmdCfgData->m_strFormat;

		long nPos = m_strDatasetKey.Find(_T("ds"));

		if (nPos < 0)
		{
			g_theGbSmartGenWzd->m_pDvmDevice->GetDatasetList(m_strDatasetKey, m_listDataset);
		}
		else
		{
			g_theGbSmartGenWzd->m_pDvmDevice->GetDatasetList(m_strDatasetKey.Mid(nPos + 2), m_listDataset);
		}
		
		ex_InsertChildreComboBox(&m_listDataset, ui->m_cmbDataset, TRUE, -1);
	}
}


//2022-9-13  lijunqing
/*
<commcmd name="��ʼ����ѹ��Ena1" id="_INIT_Ena1" tkid="65535" select="1" show="1" enable="1" exectype="0" batch-item="0" mdv-test-each="0" state="0" type="WriteEna" rw-optr="write" sort-soe="0" dsv-run-after-rst="0" mgbrpt-cmd-mode="0">
	<script-init name="" id="" is-ref="0"><![CDATA[]]></script-init>
	<script-name name="" id="" is-ref="0"><![CDATA[]]></script-name>
	<script-result name="" id="" is-ref="0"><![CDATA[]]></script-result>
	<cmd name="" id="" dataset-path="XLBH931PROT$LLN0$dsRelayEna1" delaybeforecmd="g_TComBef" delayaftercmd="g_TComAft" delaybefortry="0" maxretrytimes="0" retrytimes="0" rpt-fill-no-repeat="0" cal-mode="none" timelong="" timegap="" usecurrsetdata="1" usedeviceex="255" begin-mode="synchro" use-connect="0" zone-index="0">
		<value id="PTRC3$ST$TrStrp" value="1"/>
		<value id="PTRC3$ST$StrBFStrp" value="0"/>
		<value id="PTRC3$ST$BlkRecStrp" value="0"/>
		<value id="RREC1$ST$OpStrp" value="1"/>
	</cmd>
	<datas name="" id=""/>
	<dsv-script name="" id="" minocc="1" maxocc="1" in-dataset="" type="">
		<eliminate name="���ݼ�" id="dataset" data-type="" write-mode="0" index="0"/>
	</dsv-script>
	<rpt-map name="������" id="_rpt_map"/>
</commcmd>
*/
void QSttCmdWzdDsEditWidget::OnAtsQueryItem(CExBaseObject *pItemPara)
{
	CSttContents *pContents = (CSttContents*)pItemPara;
	m_oSttCommCmd.DeleteAll();
	BSTR bstrParas;
	bstrParas = pContents->m_strText.AllocSysString();
	m_oSttCommCmd.SetXml(bstrParas, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

#ifdef _PSX_IDE_QT_
	delete bstrParas;
#else
	::SysFreeString(bstrParas);// �����ͷ�
#endif

	CSttCommCmdData *pSttCmdData = m_oSttCommCmd.GetCommCmdData(TRUE);

	if (pSttCmdData->m_strDatasetPath.isEmpty())
	{
		//Ĭ�ϵ�һ�����ݼ�
		CDvmDataset *pDataset = (CDvmDataset *)m_listDataset.GetHead();

		if (pDataset != NULL)
		{
			CDvmLogicDevice *pLd = (CDvmLogicDevice *)pDataset->GetParent();
			pSttCmdData->m_strDatasetPath = pLd->m_strID + _T("$") + pDataset->m_strID;
		}	
	}
	//2022-11-8  lijunqing
	m_oSttCommCmd.UpdateEx(m_pCurrCmdItem);

	emit sig_Show_CommCmd();
}

void QSttCmdWzdDsEditWidget::AutoSave_AfterEdit()
{
	if (! IsCommCmdChanged())
	{
		return;
	}

	on_m_btnSave_clicked();
}

void QSttCmdWzdDsEditWidget::GetDsKey(CStringArray &strKeyArray, const CString &strKey)
{
	long nPos = strKey.Find(_T("ds"));

	if (nPos < 0)
	{
		strKeyArray.Add(strKey);
	}
	else
	{
		strKeyArray.Add(strKey.Mid(nPos + 2));
	}
}

void QSttCmdWzdDsEditWidget::UI_SetFont(QFont font)
{
 	ui->m_cmbDataset->setFont(font);
	ui->m_txtDataset->setFont(font);
	ui->m_cmbSetZone->setFont(font);
	ui->m_txtSetZone->setFont(font);
	ui->m_btnInsertData->setFont(font);
	ui->m_btnDeleteData->setFont(font);
	ui->m_btnSave->setFont(font);
	ui->m_cmbDelayBft->setFont(font);
	ui->m_txtBFT->setFont(font);
	ui->m_cmbDelayAft->setFont(font);
	ui->m_txtAFT->setFont(font);
	ui->m_btnExecCmd->setFont(font);
}

void QSttCmdWzdDsEditWidget::on_m_btnInsertData_clicked()
{
// 	QSttCmdWzdDataAddWidget dlg(this);
// 	dlg.m_pCommCmdRef = &m_oSttCommCmd;
// 	dlg.m_pEditGrid->ShowDatas(m_pCurrDataset);
// 	connect(&dlg,SIGNAL(sig_CmdWzd_AddData(CDvmData*)),this,
// 		SLOT(slot_CmdWzd_AddData(CDvmData*)));
// 
// 	dlg.exec();
// 
// 	disconnect(&dlg,SIGNAL(sig_CmdWzd_AddData(CDvmData*)),this,
// 		SLOT(slot_CmdWzd_AddData(CDvmData*)));
}

void QSttCmdWzdDsEditWidget::on_m_btnDeleteData_clicked()
{
	CDvmData *pValue = (CDvmData *)m_pEditGrid_Write->GetCurrSelData();

	if (pValue == NULL)
	{
		return;
	}

	CString strDataID = pValue->m_strID;
	DeleteDataFromSttCommCmd(pValue);

	if (m_pCurrWzd != NULL)
	{//��ģʽ��
		DeleteDataFromWzdCmdCfg(strDataID);
	}
	else
	{//��ӵ��������ģʽ
		DeleteDataFromWzdCmdCfg_Single(strDataID);
	}
}

void QSttCmdWzdDsEditWidget::on_m_cmbDataset_currentIndexChanged(int index)
{
	//CString strDatasetID = ui->m_cmbDataset->currentText();  //�˴���ӵ���Name
	//CDvmDataset *pDataset = (CDvmDataset *)m_listDataset.FindByName(strDatasetID);

	//��ͬ�߼��豸�µ����ݼ������ƺ�ID����һ�£��˴���Ϊ�����Ų���
	long nIndex = ui->m_cmbDataset->currentIndex();
	CDvmDataset *pDataset = (CDvmDataset *)m_listDataset.GetAt(nIndex);

	if (pDataset == m_pCurrDataset)
	{
		return;
	}

	m_pCurrDataset = pDataset;

	if (pDataset == NULL)
	{
		return;
	}

	if (m_oSttCommCmd.m_strRwOptr == COMMCMD_RWOPTR_WRITE)
	{
		m_pEditGrid_Write->m_pDataset = m_pCurrDataset;
	}
	else if (m_oSttCommCmd.m_strRwOptr == COMMCMD_RWOPTR_READ)
	{
		m_pEditGrid_Read->m_pDataset = m_pCurrDataset;
	}

	CSttCommCmdData *pSttCmdData = m_oSttCommCmd.GetCommCmdData(TRUE);

	if (pSttCmdData != NULL)
	{
		if (m_oSttCommCmd.m_strCommCmdID != _T("RegisterReport"))
		{
			//�л����ݼ���ɾ��ԭ�����еĲ���
			pSttCmdData->DeleteAll();
			if (m_oSttCommCmd.m_strRwOptr == COMMCMD_RWOPTR_WRITE)
			{
				m_pEditGrid_Write->m_pValues = pSttCmdData;
				m_pEditGrid_Write->ShowDatas(m_pCurrDataset);
			}
			else if (m_oSttCommCmd.m_strRwOptr == COMMCMD_RWOPTR_READ)
			{
				m_pEditGrid_Read->ShowDatas(m_pCurrDataset);
			}
		}

		CDvmLogicDevice *pLd = (CDvmLogicDevice *)m_pCurrDataset->GetParent();
		pSttCmdData->m_strDatasetPath = pLd->m_strID + _T("$") + pDataset->m_strID;
	}

	if (m_oSttCommCmd.m_strRwOptr != COMMCMD_RWOPTR_REGISTER)
	{
		DeleteAllDatasToWzdCmdCfg();
	}

	//���ڶ�ָ�����Ҫ���ͨѶ���ݡ����ǵ����ݼ��ı�ʱ����Ҫ���������ݼ�
	AddDataToWzdCmdCfg_Single(NULL);
}

void QSttCmdWzdDsEditWidget::on_m_cmbSetZone_currentIndexChanged(int index)
{
	CSttCommCmdData *pSttCmdData = m_oSttCommCmd.GetCommCmdData(TRUE);

	if (pSttCmdData == NULL)
	{
		return;
	}

	if (pSttCmdData->m_nZoneIndex == index)
	{
		return;
	}

	pSttCmdData->m_nZoneIndex = index;

	if (m_pCurrWzd != NULL)
	{
		//��ģʽ�´�����ͨѶ������¶�ֵ���Ĳ���
		CSttItems *pRootItems = (CSttItems *)Stt_GetFirstParentItems(m_pCurrCmdItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);
		CExBaseObject *pParent = (CExBaseObject*)m_pCurrCmdItem->GetParent();
		m_pCurrWzd->UpdateZoneIndexToWzdCmdCfg(pParent->m_strID, m_oSttCommCmd.m_strCommCmdID, pSttCmdData->m_strDatasetPath, index);
	}
	else if (m_pCommCmdAdd != NULL)
	{
		//������ӵ�ͨѶ������¶�ֵ���Ĳ���
		m_pCommCmdAdd->UpdateZoneIndexToWzdCmdCfg(index);
	}
}

void QSttCmdWzdDsEditWidget::on_m_cmbDelayBft_currentIndexChanged(int index)
{
	CSttCommCmdData *pSttCmdData = m_oSttCommCmd.GetCommCmdData(TRUE);

	if (pSttCmdData == NULL)
	{
		return;
	}

	CString strDelay = CmdDelayComboBox_GetCmdDelay(ui->m_cmbDelayBft);

	if (pSttCmdData->m_strDelayBeforeCmd == strDelay)
	{
		return;
	}

	pSttCmdData->m_strDelayBeforeCmd = strDelay;

	if (m_pCurrWzd != NULL)
	{
		//��ģʽ�´�����ͨѶ������¶�ֵ���Ĳ���
		CSttItems *pRootItems = (CSttItems *)Stt_GetFirstParentItems(m_pCurrCmdItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);
		CExBaseObject *pParent = (CExBaseObject*)m_pCurrCmdItem->GetParent();
		m_pCurrWzd->UpdateDelayBftToWzdCmdCfg(pParent->m_strID, m_oSttCommCmd.m_strCommCmdID, pSttCmdData->m_strDatasetPath, strDelay);
	}
	else if (m_pCommCmdAdd != NULL)
	{
		//������ӵ�ͨѶ������¶�ֵ���Ĳ���
		m_pCommCmdAdd->UpdateDelayBftToWzdCmdCfg(strDelay);
	}
}

void QSttCmdWzdDsEditWidget::on_m_cmbDelayAft_currentIndexChanged(int index)
{
	CSttCommCmdData *pSttCmdData = m_oSttCommCmd.GetCommCmdData(TRUE);

	if (pSttCmdData == NULL)
	{
		return;
	}

	CString strDelay = CmdDelayComboBox_GetCmdDelay(ui->m_cmbDelayAft);

	if (pSttCmdData->m_strDelayAfterCmd == strDelay)
	{
		return;
	}

	pSttCmdData->m_strDelayAfterCmd = strDelay;

	if (m_pCurrWzd != NULL)
	{
		//��ģʽ�´�����ͨѶ������¶�ֵ���Ĳ���
		CSttItems *pRootItems = (CSttItems *)Stt_GetFirstParentItems(m_pCurrCmdItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);
		CExBaseObject *pParent = (CExBaseObject*)m_pCurrCmdItem->GetParent();
		m_pCurrWzd->UpdateDelayAftToWzdCmdCfg(pParent->m_strID, m_oSttCommCmd.m_strCommCmdID, pSttCmdData->m_strDatasetPath, strDelay);
	}
	else if (m_pCommCmdAdd != NULL)
	{
		//������ӵ�ͨѶ������¶�ֵ���Ĳ���
		m_pCommCmdAdd->UpdateDelayAftToWzdCmdCfg(strDelay);
	}
}

void QSttCmdWzdDsEditWidget::slot_Show_CommCmd()
{
	CSttCommCmdData *pSttCmdData = m_oSttCommCmd.GetCommCmdData(TRUE);

	CString strDatasetPath, strLDeviceID;
	strDatasetPath = pSttCmdData->m_strDatasetPath;
	long nPos = strDatasetPath.Find('$');
	strLDeviceID = strDatasetPath.Left(nPos);
	strDatasetPath = strDatasetPath.Mid(nPos + 1);

	CExBaseList oList;
	//��ͬ�߼��豸�£����ܴ�����ͬID�����ݼ�
	long nCount = m_listDataset.QueryByID(strDatasetPath, oList);

	if (nCount == 1)
	{
		m_pCurrDataset = (CDvmDataset*)oList.GetHead();
	}
	else
	{
		POS pos = oList.GetHeadPosition();

		while (pos != NULL)
		{
			CDvmDataset *pDataset = (CDvmDataset *)oList.GetNext(pos);
			CExBaseObject *pParent = (CExBaseObject *)pDataset->GetParent();

			if (pParent->m_strID == strLDeviceID)
			{
				m_pCurrDataset = pDataset;
				break;
			}
		}
	}
	
	oList.RemoveAll();
	//�˴�����ֱ��ͨ��ID���ң���Ϊ��ͬ�߼��豸�£����ܴ�����ͬID�����ݼ�
	//m_pCurrDataset = (CDvmDataset*)m_listDataset.FindByID(strDatasetPath);
	if (m_oSttCommCmd.m_strRwOptr == COMMCMD_RWOPTR_WRITE)
	{
		m_pEditGrid_Write->m_pValues = pSttCmdData;
		m_pEditGrid_Write->m_pDataset = m_pCurrDataset;
	}
	else if (m_oSttCommCmd.m_strRwOptr == COMMCMD_RWOPTR_READ)
	{
		m_pEditGrid_Read->m_pDataset = m_pCurrDataset;
	}

	long nIndex = m_listDataset.FindIndex(m_pCurrDataset);
	ui->m_cmbDataset->setCurrentIndex(nIndex);
	//m_pEditGrid_Write->InitTypeRwOptr(m_oSttCommCmd.m_strRwOptr);
	//UpDateDataset(m_pCurrDataset, pSttCmdData);

	if (m_oSttCommCmd.m_strCommCmdID == _T("RegisterReport"))
	{
		m_pEditGrid_Write->setVisible(false);
		m_pEditGrid_Write->ShowDatas(NULL);
		m_pEditGrid_Read->setVisible(false);
		m_pEditGrid_Read->ShowDatas(NULL);
		m_pRegisterGrid->setVisible(true);
		m_pRegisterGrid->ShowDatas(pSttCmdData);
	}
	else if (m_oSttCommCmd.m_strRwOptr == COMMCMD_RWOPTR_WRITE)
	{
		m_pRegisterGrid->setVisible(false);
		m_pRegisterGrid->ShowDatas(NULL);
		m_pEditGrid_Read->setVisible(false);
		m_pEditGrid_Read->ShowDatas(NULL);

		m_pEditGrid_Write->ShowDatas(NULL);
		m_pEditGrid_Write->setVisible(true);
		m_pEditGrid_Write->ShowDatas(m_pCurrDataset);
	}
	else 
	{
		m_pRegisterGrid->setVisible(false);
		m_pRegisterGrid->ShowDatas(NULL);
		m_pEditGrid_Write->setVisible(false);
		m_pEditGrid_Write->ShowDatas(NULL);

		m_pEditGrid_Read->ShowDatas(NULL);
		m_pEditGrid_Read->setVisible(true);
		m_pEditGrid_Read->ShowDatas(m_pCurrDataset);
	}

	//2023-7-12 yzj �������ʼ��ͨѶ�������ʱ����(�Ҽ����)
	if(m_pCommCmdAdd)
	{
		CDvmData* pData = (CDvmData*)m_pCommCmdAdd->FindByID(STT_CMD_PARA_DelayBeforeCmd);
		if(pData)
		{
			pSttCmdData->m_strDelayBeforeCmd = pData->m_strValue;
		}
		pData = (CDvmData*)m_pCommCmdAdd->FindByID(STT_CMD_PARA_DelayAfterCmd);
		if(pData)
		{
			pSttCmdData->m_strDelayAfterCmd = pData->m_strValue;
		}
	}

	EnableSettingZone();
	Show_CommCmd_DelayBft();
	Show_CommCmd_DelayAft();
// 	ui->m_btnInsertData->setDisabled(false);
	EnableBtns();

// 	if (m_oSttCommCmd.m_strRwOptr != COMMCMD_RWOPTR_WRITE)
// 	{
// 		ui->m_btnInsertData->setDisabled(true);
// 	}
}

void QSttCmdWzdDsEditWidget::AddDataToSttCommCmd(CDvmData *pData)
{
	CSttCommCmdData *pSttCmdData = m_oSttCommCmd.GetCommCmdData(FALSE);
	CValue *pValue = (CValue*)pSttCmdData->FindByID(pData->m_strID);

	if (pValue == NULL)
	{
		pValue = pSttCmdData->AddValue(pData->m_strID, pData->m_strValue);
		//m_pEditGrid->InsertData(pValue);
	}
	else
	{
		pValue->m_strValue = pData->m_strValue;
	}
}

/*
<macro-gen id="" data-type="" value="" test-class="���Ȳ���" items-name="ww" items-id="ww" test-macro-ui-id="ManualTest" parent-items-id="">
	<group id="cmd-gen-paras" data-type="cmd-gen-paras" value="">
		<group id="_BeforeTest_" data-type="" value="">
			<group id="WriteSetting" data-type="write" value="">
				<group id="XLBH931PROT$LLN0$dsSetting" data-type="" value="">
					<data id="LLN0$SG$DPFCStr" data-type="STRUCT" value="0.200000" />
					<data id="LLN0$SG$ROCStr" data-type="STRUCT" value="0.200000" />
					<data id="PDIF1$SG$StrValSG" data-type="STRUCT" value="10.000000" />
*/
//�÷���������ģʽ�£��������
void QSttCmdWzdDsEditWidget::AddDataToWzdCmdCfg(CDvmData *pData)
{
	if (m_pCurrWzd == NULL)
	{
		return;
	}

	CSttCommCmdData *pSttCmdData = m_oSttCommCmd.GetCommCmdData(TRUE);
	//CSttItems *pRootItems = (CSttItems *)Stt_GetFirstParentItems(m_pCurrCmdItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);
	CExBaseObject *pParent = (CExBaseObject*)m_pCurrCmdItem->GetParent();

	m_pCurrWzd->AddDataToWzdCmd(pParent->m_strID, m_oSttCommCmd.m_strCommCmdID, pSttCmdData->m_strDatasetPath, pData);
}

//�÷������ڵ���ͨѶ����ģʽ�£��������
void QSttCmdWzdDsEditWidget::AddDataToWzdCmdCfg_Single(CDvmData *pData)
{
	if (m_pCommCmdAdd == NULL)
	{
		return;
	}

	m_pCommCmdAdd->AddDataToWzdCmdCfg(pData, m_pCurrDataset);
}

//�÷���������ģʽ�£��������
void QSttCmdWzdDsEditWidget::AddDataToWzdCmdCfg_Value(CValue *pValue)
{
	if (m_pCurrWzd == NULL)
	{
		return;
	}

	CSttCommCmdData *pSttCmdData = m_oSttCommCmd.GetCommCmdData(TRUE);
	CSttItems *pRootItems = (CSttItems *)Stt_GetFirstParentItems(m_pCurrCmdItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);
	CExBaseObject *pParent = (CExBaseObject*)m_pCurrCmdItem->GetParent();

	m_pCurrWzd->AddDataToWzdCmd(pParent->m_strID, m_oSttCommCmd.m_strCommCmdID, pSttCmdData->m_strDatasetPath, pValue);
}

//�÷������ڵ���ͨѶ����ģʽ�£��������
void QSttCmdWzdDsEditWidget::AddDataToWzdCmdCfg_Single_Value(CValue *pValue)
{
	if (m_pCommCmdAdd == NULL)
	{
		return;
	}

	m_pCommCmdAdd->AddDataToWzdCmdCfg(pValue, m_pCurrDataset);
}

//������Ĭ��ֵ�Ƚϣ�����޸Ĺ��Ĳ�����ͨѶ����
void QSttCmdWzdDsEditWidget::AddDataToSttCommCmd_ByDefaultVal()  
{
	//��ɾ��ȫ���Ĳ���
	CSttCommCmdData *pSttCmdData = m_oSttCommCmd.GetCommCmdData(TRUE);
	pSttCmdData->DeleteAll();
	DeleteAllDatasToWzdCmdCfg();

	if (m_pCurrDataset == NULL)
	{
		return;
	}

	POS pos = m_pCurrDataset->GetHeadPosition();

	while(pos != NULL)
	{
		CDvmData *pData = (CDvmData *)m_pCurrDataset->GetNext(pos);

		if (pData->m_strValue != pData->m_strDefaultValue)
		{
			slot_CmdWzd_AddData(pData);
		}
	}
}

void QSttCmdWzdDsEditWidget::DeleteDataFromSttCommCmd(CDvmData *pDvmData)
{
	m_pEditGrid_Write->DeleteDataRow(pDvmData);
}

//�÷���������ģʽ�£��������
void QSttCmdWzdDsEditWidget::DeleteDataFromWzdCmdCfg(const CString &strDataID)
{
	if (m_pCurrWzd == NULL)
	{
		return;
	}

	CSttCommCmdData *pSttCmdData = m_oSttCommCmd.GetCommCmdData(TRUE);
	CSttItems *pRootItems = (CSttItems *)Stt_GetFirstParentItems(m_pCurrCmdItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);
	CExBaseObject *pParent = (CExBaseObject*)m_pCurrCmdItem->GetParent();

	m_pCurrWzd->DeleteDataFromWzdCmd(pParent->m_strID, m_oSttCommCmd.m_strCommCmdID, pSttCmdData->m_strDatasetPath, strDataID);
}

void QSttCmdWzdDsEditWidget::DeleteDataFromWzdCmdCfg_Single(const CString &strDataID)
{
	if (m_pCommCmdAdd == NULL)
	{
		return;
	}

	m_pCommCmdAdd->DeleteDataFromWzdCmdCfg(strDataID);
}

void QSttCmdWzdDsEditWidget::UpdateDataToWzdCmdCfg(CDvmData *pDvmData)
{
	if (m_pCurrWzd != NULL)
	{
		//��ģʽ�´�����ͨѶ�����������
		CSttCommCmdData *pSttCmdData = m_oSttCommCmd.GetCommCmdData(TRUE);
		CSttItems *pRootItems = (CSttItems *)Stt_GetFirstParentItems(m_pCurrCmdItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);
		CExBaseObject *pParent = (CExBaseObject*)m_pCurrCmdItem->GetParent();

		m_pCurrWzd->UpdateDataToWzdCmdCfg(pParent->m_strID, m_oSttCommCmd.m_strCommCmdID, pSttCmdData->m_strDatasetPath, pDvmData);
	}
	else if (m_pCommCmdAdd != NULL)
	{
		//������ӵ�ͨѶ�����������
		m_pCommCmdAdd->UpdateDataToWzdCmdCfg(pDvmData);
	}
}

void QSttCmdWzdDsEditWidget::DeleteAllDatasToWzdCmdCfg()
{
	if (m_pCurrWzd != NULL)
	{
		//��ģʽ�´�����ͨѶ���ɾ������ͨѶ����
		CSttCommCmdData *pSttCmdData = m_oSttCommCmd.GetCommCmdData(TRUE);
		CSttItems *pRootItems = (CSttItems *)Stt_GetFirstParentItems(m_pCurrCmdItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);
		CExBaseObject *pParent = (CExBaseObject*)m_pCurrCmdItem->GetParent();

		m_pCurrWzd->DeleteAllDatasToWzdCmdCfg(pParent->m_strID, m_oSttCommCmd.m_strCommCmdID, pSttCmdData->m_strDatasetPath);
	}
	else if (m_pCommCmdAdd != NULL)
	{
		//������ӵ�ͨѶ���ɾ������ͨѶ����
		m_pCommCmdAdd->DeleteAllDatasToWzdCmdCfg();
	}
}

//ͨ��QueryItem��ȡ����Ŀ�󣬸�����Ŀ�Ĳ������������ݼ�
//��������Ŀ�ģ��Ǳ����ʱ����ͳһ����ֵ��Ĭ��ֵ�ıȽ�ȷ������Ĳ���
void QSttCmdWzdDsEditWidget::UpDateDataset(CDvmDataset *pDataset, CSttCommCmdData *pCmdDatas)
{
	if (pCmdDatas == NULL || pDataset == NULL)
	{
		return;
	}

	POS pos = pCmdDatas->GetHeadPosition();

	while (pos != NULL)
	{
		CValue *pValue = (CValue *)pCmdDatas->GetNext(pos);
		CDvmData *pFind = (CDvmData *)pDataset->FindByID(pValue->m_strID);

		if (pFind != NULL)
		{
			pFind->m_strDefaultValue = pFind->m_strValue;
			pFind->m_strValue = pValue->m_strValue;
		}
	}
}

//ͨѶ����ִ�н�����ˢ�±༭ҳ����ʾ���ݼ�
void QSttCmdWzdDsEditWidget::UpdateShowDataset(const CString &strDsPath)
{
	CDvmDataset *pDsLocal = g_theGbSmartGenWzd->m_pDvmDevice->FindDatasetByPath(strDsPath);

	if (pDsLocal != m_pCurrDataset)
	{
		return;
	}

	if (m_oSttCommCmd.m_strRwOptr == COMMCMD_RWOPTR_WRITE)
	{
		m_pEditGrid_Write->ShowDatas(m_pCurrDataset);
	}
	else if(m_oSttCommCmd.m_strRwOptr == COMMCMD_RWOPTR_READ)
	{
		m_pEditGrid_Read->ShowDatas(m_pCurrDataset);
	}
}

//����ʱ��ɾ��ͨѶ������ֵΪ���ַ����Ĳ���
void QSttCmdWzdDsEditWidget::ClearEmptyCmdParas()
{
	CSttCommCmdData* pCmdData = m_oSttCommCmd.GetCommCmdData(FALSE);

	if (m_oSttCommCmd.m_strRwOptr == COMMCMD_RWOPTR_WRITE)
	{
		if (pCmdData != NULL)
		{
			POS pos = pCmdData->GetHeadPosition();

			while(pos != NULL)
			{
				CValue *pValue = (CValue *)pCmdData->GetNext(pos);

				if (pValue->m_strValue.IsEmpty())
				{
					pCmdData->Delete(pValue);
				}
			}

			m_pEditGrid_Write->ShowDatas(m_pCurrDataset);
		}
	}

	CSttItems *pRootItems = (CSttItems *)Stt_GetFirstParentItems(m_pCurrCmdItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);
	CExBaseObject *pParent = (CExBaseObject*)m_pCurrCmdItem->GetParent();

	if (m_pCurrWzd != NULL)
	{//��ģʽ��
		if (pCmdData != NULL)
		{
			m_pCurrWzd->ClearEmptyCmdParas(pParent->m_strID, m_oSttCommCmd.m_strCommCmdID, pCmdData->m_strDatasetPath);
		}
	}
	else
	{//��ӵ��������ģʽ
		if (m_pCommCmdAdd != NULL)
		{
			m_pCommCmdAdd->ClearEmptyCmdParas(m_pCurrDataset);
		}
	}
}

BOOL QSttCmdWzdDsEditWidget::IsCommCmdChanged()
{
	if (m_bIsCommcmdChanged)
	{
		return TRUE;
	}

	if (m_pCurrCmdItem == NULL)
	{
		return FALSE;
	}

	// 	if (m_oSttCommCmd.IsEqual(m_pCurrCmdItem))
	// 	{
	// 		return FALSE;
	// 	}

	//if(m_oSttCommCmd.m_strRwOptr != COMMCMD_RWOPTR_WRITE)
	{
		CSttCommCmdData *pCmdData1 = m_oSttCommCmd.GetCommCmdData(FALSE);
		CSttCommCmdData *pCmdData2 = m_pCurrCmdItem->GetCommCmdData(FALSE);

		if  (pCmdData2 == NULL)
		{
			return FALSE;
		}

		if (m_oSttCommCmd.IsEqualOwn(m_pCurrCmdItem) && pCmdData1->IsEqual(pCmdData2))
		{
			return FALSE;
		}
	}

	m_bIsCommcmdChanged = TRUE;
	return TRUE;
}

void QSttCmdWzdDsEditWidget::slot_CmdWzd_AddData(CDvmData *pData)
{
	//�ĵ��ڱ���б༭����ֱ�����  2023-3-24
	//AddDataToSttCommCmd(pData);

	if (m_pCurrWzd != NULL)
	{//��ģʽ��
		AddDataToWzdCmdCfg(pData);
	}
	else
	{//��ӵ��������ģʽ
		AddDataToWzdCmdCfg_Single(pData);
	}
}

void QSttCmdWzdDsEditWidget::slot_CmdWzd_UpdateData(CDvmData *pDvmData)
{
	slot_CmdWzd_AddData(pDvmData);
	//UpdateDataToWzdCmdCfg(pDvmData);
}

void QSttCmdWzdDsEditWidget::slot_CmdWzd_UpdateData_Value(CValue *pValue)
{
	if (m_pCurrWzd != NULL)
	{//��ģʽ��
		AddDataToWzdCmdCfg_Value(pValue);
	}
	else
	{//��ӵ��������ģʽ
		AddDataToWzdCmdCfg_Single_Value(pValue);
	}
}


//////////////////////////////////////////////////////////////////////////

CSttItems* Stt_GetSiblingItems(CExBaseObject *pObj, const CString &strType, BOOL bType)
{
	if (pObj == NULL)
	{
		return NULL;
	}

	CExBaseList *pParent = (CExBaseList*)pObj->GetParent();

	if (pParent == NULL)
	{
		return NULL;
	}

	UINT nClassID = 0;
	CExBaseObject *p = NULL;
	CSttItems *pItem = NULL;
	POS pos = pParent->GetHeadPosition();

	while (pos != NULL)
	{
		p = pParent->GetNext(pos);

		if (p->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
		{
			if (bType)
			{
				if ( ((CSttItems*)p)->m_strType == strType)
				{
					return (CSttItems*)p;
				}
			}
		}
	}

	return NULL;
}

CSttItems* stt_cmd_wzd_GetRootItems(CSttCommCmd *pItem)
{
	//��Ϊ�򵼵��Ӷ���
	CSttItems *pItems = (CSttItems *)Stt_GetFirstParentItems(pItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);

	if (pItems != NULL)
	{
		return pItems;
	}

	//ͬ�����ֵܶ���
	pItems = Stt_GetSiblingItems(pItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);

	if (pItems != NULL)
	{
		return pItems;
	}

	//��������ֵܶ���
	pItems = Stt_GetSiblingItems((CExBaseObject*)pItem->GetParent(), GBITEMS_NODETYPE_ROOTNODE, TRUE);

	return pItems;
}

//�򲻵��ѣ���ʱ��ô�޸�
#include "../../../Local/TestCtrlCntrWin/SttTestCntrFrameWin.h"
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbWzdAi/GbWzdAiTool.h"
CSttTestMacroUiParas* stt_cmd_wzd_GetCurrTestMacroUiParas(CSttCommCmd *pItem)
{
	CSttItems *pRootItems = stt_cmd_wzd_GetRootItems(pItem);

	if (pRootItems == NULL)
	{
		return NULL;
	}

	CSttMacroTestUI_TestMacroUI *pTestMacroUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(pRootItems->m_strstxmlFile);
	CSttTestMacroUiParas *pUIParas = ((QSttTestCntrFrameWin*)g_theTestCntrFrame)->GetTestMacroUiParas(pRootItems);
	return pUIParas;
}

void stt_cmd_wzd_UpdateDeviceDataset(CSttCommCmd *pItem)
{
	CSttCommCmdData *pCmdData = (CSttCommCmdData*)pItem->FindByClassID(STTGBXMLCLASSID_CSTTCOMM_DATA);

	if (pCmdData == NULL)
	{
		return;
	}

	CDvmDataset *pDataset = g_theGbSmartGenWzd->m_pDvmDevice->FindDatasetByPath(pCmdData->m_strDatasetPath);

	if (pDataset == NULL)
	{
		return;
	}
	
	POS pos = pCmdData->GetHeadPosition();
	CValue *pVal = NULL;
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pVal = (CValue*)pCmdData->GetNext(pos);
		pData = (CDvmData *)pDataset->FindByID(pVal->m_strID);

		if (pData == NULL)
		{
			continue;
		}

		//������ʱֵ�޸�m_strValue��������stVal����������
		pData->m_strValue = pVal->m_strValue;
	}

}

 void stt_cmd_wzd_UpdateTestMacroUiParas(CSttCommCmd *pItem)
 {
 	if (pItem->m_strCommCmdID != "WriteSetting")
 	{
 		return;
 	}
 
 	stt_cmd_wzd_UpdateDeviceDataset(pItem);
 	CSttItems *pRootItems = stt_cmd_wzd_GetRootItems(pItem);
 
 	if (pRootItems == NULL)
 	{
 		return;
 	}
 
 	CSttMacroTestUI_TestMacroUI *pTestMacroUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(pRootItems->m_strstxmlFile);
 	CSttTestMacroUiParas *pUIParas = ((QSttTestCntrFrameWin*)g_theTestCntrFrame)->GetTestMacroUiParas(pRootItems);
 
 	if (pUIParas == NULL || pTestMacroUI == NULL)
 	{
 		return;
 	}
 
 	CDataGroup oParas;
 	BSTR bstrText = pUIParas->m_strParaText.AllocSysString();
 	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
 	oParas.SetXml(bstrText, CDataMngrXmlRWKeys::g_pXmlKeys);
 	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
 
 	CString strAiFile = stt_ui_GetParasAiFile(pTestMacroUI->m_strUI_ParaFile);
 
 	if (!IsFileExist(strAiFile))
 	{
 		return;
 	}
 
 	g_theGbWzdAiTool->GbWzdAi(strAiFile, &oParas);
 	//oParas.SaveXmlFile(_T("D:/Paras.xml"), CDataMngrXmlRWKeys::g_pXmlKeys);
 
 	//���ף�����Ӹ�����ҳ����������ģ��Ĵ���
 	oParas.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, pUIParas->m_strParaText);
 
 	CString strRootItemPath;
 	strRootItemPath = pRootItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE); 
 	//��ʾ����ҳ
 
 	if (strRootItemPath == g_theTestCntrFrame->m_pSttGbTreeView->m_strCurrSelRootNodePath)
 	{
 		g_theTestCntrFrame->SetDatas(&oParas);
 	}
 	
 	//����ģ�����ɣ����������ɶ�ֵ�����Ĳ�����Ŀ
 	g_theTestCntrFrame->OnSaveCurr(pRootItems);
 
 	g_pTheSttTestApp->m_pTestCtrlCntr->WaitCmdReplyProcess();
 
 	g_theTestCntrFrame->m_pSttGbTreeView->After_SaveCurr(strRootItemPath);
 
 }

void QSttCmdWzdDsEditWidget::on_m_btnSave_clicked()
{
 	if (m_oSttCommCmd.m_strRwOptr == COMMCMD_RWOPTR_WRITE)
 	{
 		//ֻ��д�Ĳ�����Ҫ������ͨ������
		m_pEditGrid_Write->FillCmdValues();
 	}

	//����ʱ���ȱ���ͨѶ����Ĳ�����ɾ��ֵΪ���ַ����Ĳ���
	ClearEmptyCmdParas();

	CString strPath = m_pCurrCmdItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	CString strItemParas;
	m_oSttCommCmd.GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, strItemParas);

	if (m_pCommCmdAdd != NULL)
	{//��ӵ��������ģʽ������ͼ�¼�������
		m_pCommCmdAdd->SetParas(strItemParas);
	}

	//Ϊ�˽�ʡ��19815��������Դ��
	//1������������ӵ�ͨѶ����༭����ʱ��������ֱ�Ӹ��µ���Ӧ�Ķ���m_pCurrWzd��
	//2�����ڵ�����ӵ�ͨѶ����༭����ʱ��������ֱ�Ӹ��µ���Ӧ�Ķ���m_pCommCmdAdd�У�
	//3�����ڡ�װ�ø���̬���е�ͨѶ����༭����ʱ��������g_theGbSmartGenWzd������comm-cmd-update����
	if (m_pCommCmdAdd == NULL && m_pCurrWzd == NULL)
	{
		//��װ�ø���̬���е�ͨѶ������²���
		if (IsCommCmdChanged())
		{
			CString strParentPath;
			CExBaseObject *pParent = (CExBaseObject *)m_pCurrCmdItem->GetParent();
			strParentPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
			g_theGbSmartGenWzd->CommCmdUpdate(strParentPath, m_oSttCommCmd.m_strID, m_oSttCommCmd.m_strName, strItemParas);
		}
	}

	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_UpdateItem(strPath, strItemParas, _T("commcmd"));
	//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
	m_oSttCommCmd.UpdateEx(m_pCurrCmdItem);

	stt_cmd_wzd_UpdateTestMacroUiParas(m_pCurrCmdItem);
	m_bIsCommcmdChanged = FALSE;
}

void QSttCmdWzdDsEditWidget::EnableSettingZone()
{
	if (m_strDatasetKey.Find(_T("Setting")) >= 0)
	{
		ui->m_cmbSetZone->setDisabled(false);

		CSttCommCmdData *pCmdData = m_oSttCommCmd.GetCommCmdData(FALSE);
		int index = pCmdData->m_nZoneIndex;
		ui->m_cmbSetZone->setCurrentIndex(index);
	}
	else
	{
		ui->m_cmbSetZone->setDisabled(true);
	}
}

void QSttCmdWzdDsEditWidget::Show_CommCmd_DelayBft()
{
	CSttCommCmdData *pCmdData = m_oSttCommCmd.GetCommCmdData(FALSE);
	CString strDelayBft = pCmdData->m_strDelayBeforeCmd;
	CDvmData *pData = (CDvmData *)g_theGbSmartGenWzd->m_pCmdDelay->FindByID(strDelayBft);

	if (pData == NULL)
	{
		pData = g_theGbSmartGenWzd->m_pCmdDelay->AddNewData(strDelayBft, strDelayBft);
	}

	long nIndex = g_theGbSmartGenWzd->m_pCmdDelay->FindIndex(pData);
	ui->m_cmbDelayBft->setCurrentIndex(nIndex);
}

void QSttCmdWzdDsEditWidget::Show_CommCmd_DelayAft()
{
	CSttCommCmdData *pCmdData = m_oSttCommCmd.GetCommCmdData(FALSE);
	CString strDelayAft = pCmdData->m_strDelayAfterCmd;
	CDvmData *pData = (CDvmData *)g_theGbSmartGenWzd->m_pCmdDelay->FindByID(strDelayAft);

	if (pData == NULL)
	{
		pData = g_theGbSmartGenWzd->m_pCmdDelay->AddNewData(strDelayAft, strDelayAft);
	}

	long nIndex = g_theGbSmartGenWzd->m_pCmdDelay->FindIndex(pData);
	ui->m_cmbDelayAft->setCurrentIndex(nIndex);
}

void QSttCmdWzdDsEditWidget::EnableBtns()
{
	ui->m_btnDeleteData->setDisabled(true);
	ui->m_btnInsertData->setDisabled(true);
	ui->m_btnDeleteData->setVisible(false);
	ui->m_btnInsertData->setVisible(false);
// 	ui->m_btnDeleteData->setDisabled(false);
// 	CValue *pValue = (CValue *)m_pEditGrid->GetCurrSelData();
// 
// 	if (pValue == NULL)
// 	{
// 		ui->m_btnDeleteData->setDisabled(true);
// 	}
}

void QSttCmdWzdDsEditWidget::on_m_btnExecCmd_clicked()
{

}

void QSttCmdWzdDsEditWidget::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->m_txtDataset,g_sLangTxt_DataSets,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_txtSetZone,g_sLangTxt_FixedValueRegion,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_txtBFT,g_sLangTxt_ComictnFront+"(ms)",XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_txtAFT,g_sLangTxt_ComictnLater+"(ms)",XLang_Ctrls_QLabel);

	xlang_SetLangStrToWidget_Txt(ui->m_btnExecCmd,g_sLangTxt_Native_ExecComm,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_btnInsertData,g_sLangTxt_Native_InsData,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_btnDeleteData,g_sLangTxt_Native_DelSelData,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_btnSave,g_sLangTxt_Save,XLang_Ctrls_QPushButton);
}

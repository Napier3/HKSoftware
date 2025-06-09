#include "LowFreqCommonParasDlg.h"
#include "ui_LowFreqCommonParasDlg.h"
#include <cmath>
#include "../../XLangResource_Native.h"
extern CFont *g_pSttGlobalFont;

QLowFreqCommonParasDlg::QLowFreqCommonParasDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QLowFreqCommonParasDlg)
{
    ui->setupUi(this);
	m_pParas = NULL;
    m_nModify = 0;
	m_nVType = 0; //0:���ѹ, 1:�ߵ�ѹ
	InitUI();
}

QLowFreqCommonParasDlg::~QLowFreqCommonParasDlg()
{
    delete ui;
}
void QLowFreqCommonParasDlg::InitUI()
{	//20340617 luozibing ���ҳ����ʾ����
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	setFont(*g_pSttGlobalFont);

	ui->m_labPreFaultTime->setText(g_sLangTxt_Native_SteadyTime + "(s):");
	ui->m_labFaultTrig->setText(g_sLangTxt_LowFreq_FreqFaultTrig + ":");
	ui->m_cmb_VBlock->addItems(QStringList() <</*"�ߵ�ѹ"*/g_sLangTxt_linevolt
		<</*"���ѹ"*/g_sLangTxt_LowFreq_PhaseV);
	ui->m_rBtn_SettingValue->setText(g_sLangTxt_LowFreq_SettingBegin);
	ui->m_rBtn_FreqChange->setText(g_sLangTxt_LowFreq_FreqChangeBegin);
	ui->m_btnOK->setText(/*ȷ��*/g_sLangTxt_OK);
	ui->m_btnCancel->setText(/*ȡ��*/g_sLangTxt_Cancel);
	setWindowTitle(g_sLangTxt_LowFreq_CommonParaSet);
}

void QLowFreqCommonParasDlg::SetDatas(CExBaseList *pParas)
{
	//20240617 luozibing ��ȡ����ת����������
	if(pParas == NULL)
		return;
	m_pParas = pParas;
	CheckAllPresence(m_pParas);
    m_nModify = 0;
	POS pos = m_pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)m_pParas->GetNext(pos);
		SetValueToPage(pData);
	}
}
void QLowFreqCommonParasDlg::SetValueToPage(CSttMacroTestParaData *pData)
{

	if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_PREFAULTTIME)
	{
		ui->m_txt_SteadyTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_USETMODE )
	{
		ui->m_cmb_VBlock->setCurrentIndex(pData->m_strValue.toFloat() < 0.00001);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_TIMEZERO)
	{
		if ( 1 != pData->m_strValue.toInt())
		{
			ui->m_rBtn_FreqChange->setChecked(false);
		}
		else
		{
			ui->m_rBtn_FreqChange->setChecked(true);
		}
	}
}
void QLowFreqCommonParasDlg::GetDatas(CExBaseList *pParas)
{
	//20240617 luozibing ���������ò��������
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
}
void QLowFreqCommonParasDlg::GetPageToValue(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_PREFAULTTIME)
	{
		pData->m_strValue = ui->m_txt_SteadyTime->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_USETMODE )
	{
		//���ѹΪ0���ߵ�ѹΪ1
		m_nVType = 1 - ui->m_cmb_VBlock->currentIndex();
		pData->m_strValue.Format("%d",m_nVType);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_TIMEZERO)
	{	//0:����ֵ��Ϊ��ʱ���, 1:Ƶ�ʱ仯��Ϊ��ʱ���
		pData->m_strValue.Format("%d", ui->m_rBtn_FreqChange->isChecked());
	}
}
void QLowFreqCommonParasDlg::on_m_txt_SteadyTime_editingFinished()
{
	ui->m_txt_SteadyTime->setText(CheckDataMinMax(ui->m_txt_SteadyTime->text(),999.999,0,3));
}

void QLowFreqCommonParasDlg::on_m_cmb_VBlock_currentIndexChanged(int index)
{
	
}
void QLowFreqCommonParasDlg::on_m_rBtn_FreqChange_toggled(bool checked)
{
    
}

void QLowFreqCommonParasDlg::on_m_btnOK_clicked()
{
	this->done(Accepted);
}

void QLowFreqCommonParasDlg::on_m_btnCancel_clicked()
{
	this->close();
}
void QLowFreqCommonParasDlg::CheckAllPresence(CExBaseList *pParas)
{
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_PREFAULTTIME);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_TIMEZERO);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWFREQ_PARAS_ID_USETMODE);
}
void QLowFreqCommonParasDlg::UpdataAllCommonParas(CExBaseList *pAllItems)
{//20240625 luozibing ͨ�ò����޸ĺ��޸ı��������������ͨ�ò���
    CSttMacroTest *pSttMacroTest = NULL;
    CExBaseList *pItem = NULL;
    CSttMacroTestParaDatas *pParaDatas = NULL;

	POS pos = pAllItems->GetHeadPosition();

	while (pos!= NULL)
	{
        pItem = (CExBaseList*)pAllItems->GetNext(pos);

		if(pItem->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
		{
            pSttMacroTest = (CSttMacroTest *)pItem;
            pSttMacroTest->m_nModified = 1;
            pParaDatas = pSttMacroTest->GetSttMacroTestParaDatas(FALSE,"");

            if(pParaDatas != NULL)
			{
				CheckAllPresence(pParaDatas);
				GetDatas(pParaDatas);
			}
		}
	}
}
BOOL QLowFreqCommonParasDlg::CheckItemsModify(CExBaseList *pItem)
{
    if (pItem == NULL)
    {
        return FALSE;
    }
    CSttMacroTestParaDatas paraDatas;
    CheckAllPresence(&paraDatas);
    GetDatas(&paraDatas);
    POS pos = pItem->GetHeadPosition();
    while(pos != NULL)
    {
        CSttMacroTestParaData *pData = (CSttMacroTestParaData *)pItem->GetNext(pos);
        CSttMacroTestParaData *pData_New = (CSttMacroTestParaData *)paraDatas.FindByID(pData->m_strID);
        if (pData_New == NULL)
        {
            continue;
        }
        if(pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_TIMEZERO||
            pData->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_USETMODE)
        {
            if (pData->m_strValue != pData_New->m_strValue)
            {
                m_nModify = 1;
                return TRUE;
            }
        }
        else
        {//�������жϲ�ֵ�ľ���ֵ
            if (fabs(pData->m_strValue.toFloat() - pData_New->m_strValue.toFloat())>0.0001)
            {
                m_nModify = 1;
                return TRUE;
            }
        }

    }
    return FALSE;
}

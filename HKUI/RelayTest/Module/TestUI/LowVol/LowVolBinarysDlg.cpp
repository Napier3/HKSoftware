#include "LowVolBinarysDlg.h"
#include "ui_LowVolBinarysDlg.h"
#include "../../XLangResource_Native.h"
#include "../../UI/SttTestCntrFrameBase.h"
extern CFont *g_pSttGlobalFont;

QLowVolBinarysDlg::QLowVolBinarysDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QLowVolBinarysDlg)
{
    ui->setupUi(this);
	m_pParas = NULL;
    m_nModify= 0;
	InitUI();
}

QLowVolBinarysDlg::~QLowVolBinarysDlg()
{
    delete ui;
}
void QLowVolBinarysDlg::InitUI()
{	//20340617 luozibing 添加页面显示数据
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	setFont(*g_pSttGlobalFont);
	ui->groupBox->setTitle(/*开入量设置*/g_sLangTxt_Native_InputSet);
	ui->groupBox_2->setTitle(/*开出量设置*/g_sLangTxt_Gradient_BoutSet);
	ui->m_rbtn_LogicAnd->setText(/*逻辑与*/g_sLangTxt_Native_LogicAnd);
	ui->m_rbtn_LogicOr->setText(/*逻辑或*/g_sLangTxt_Native_LogicOr);
	ui->m_btnOK->setText(/*确定*/g_sLangTxt_OK);
	ui->m_btnCancel->setText(/*取消*/g_sLangTxt_Cancel);
	setWindowTitle(/*开关量设置*/g_sLangTxt_Native_Switch);
	SetBinBoutName();
}
void QLowVolBinarysDlg::SetBinBoutName()
{
	//开入开出映射修改
	//开入量
	QString strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 0);
	ui->m_check_A->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 1);
	ui->m_check_B->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 2);
	ui->m_check_C->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 3);
	ui->m_check_D->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 4);
	ui->m_check_E->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 5);
	ui->m_check_F->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 6);
	ui->m_check_G->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BIN, 7);
	ui->m_check_H->setText(strName);

	//开出量
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 0);
	ui->m_check_B01->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 1);
	ui->m_check_B02->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 2);
	ui->m_check_B03->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 3);
	ui->m_check_B04->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 4);
	ui->m_check_B05->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 5);
	ui->m_check_B06->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 6);
	ui->m_check_B07->setText(strName);
	strName = Stt_Global_GetBinBoutNameForIndex(MAPS_BINARY_TYPE_BOUT, 7);
	ui->m_check_B08->setText(strName);
}
void QLowVolBinarysDlg::SetDatas(CExBaseList *pParas)
{
	//20240617 luozibing 读取数据转换到界面中
	if(pParas == NULL)
		return;

	m_pParas = pParas;
	CheckAllPresence(m_pParas);
	POS pos = m_pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)m_pParas->GetNext(pos);
		SetValueToPage(pData);
	}
}
void QLowVolBinarysDlg::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_A)
	{
		ui->m_check_A->setChecked((bool)pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_B)
	{
		ui->m_check_B->setChecked((bool)pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_C)
	{
		ui->m_check_C->setChecked((bool)pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_D)
	{
		ui->m_check_D->setChecked((bool)pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_E)
	{
		ui->m_check_E->setChecked((bool)pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_F)
	{
		ui->m_check_F->setChecked((bool)pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_G)
	{
		ui->m_check_G->setChecked((bool)pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_H)
	{
		ui->m_check_H->setChecked((bool)pData->m_strValue.toInt());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_AndOr)
	{
		if (1 != pData->m_strValue.toInt())
		{
			ui->m_rbtn_LogicOr->setChecked(true);
		}
		else
		{
			ui->m_rbtn_LogicAnd->setChecked(true);
		}
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID__B01)
	{
		ui->m_check_B01->setChecked((bool)pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID__B02)
	{
		ui->m_check_B02->setChecked((bool)pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID__B03)
	{
		ui->m_check_B03->setChecked((bool)pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID__B04)
	{
		ui->m_check_B04->setChecked((bool)pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID__B05)
	{
		ui->m_check_B05->setChecked((bool)pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID__B06)
	{
		ui->m_check_B06->setChecked((bool)pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID__B07)
	{
		ui->m_check_B07->setChecked((bool)pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID__B08)
	{
		ui->m_check_B08->setChecked((bool)pData->m_strValue.toInt());
	}
}
void QLowVolBinarysDlg::GetDatas(CExBaseList *pParas)
{
	//20240617 luozibing 将界面设置参数填到链表
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
}
void QLowVolBinarysDlg::GetPageToValue(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_A)
	{
		pData->m_strValue.setNum((int)ui->m_check_A->isChecked());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_B)
	{
		pData->m_strValue.setNum((int)ui->m_check_B->isChecked());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_C)
	{
		pData->m_strValue.setNum((int)ui->m_check_C->isChecked());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_D)
	{
		pData->m_strValue.setNum((int)ui->m_check_D->isChecked());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_E)
	{
		pData->m_strValue.setNum((int)ui->m_check_E->isChecked());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_F)
	{
		pData->m_strValue.setNum((int)ui->m_check_F->isChecked());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_G)
	{
		pData->m_strValue.setNum((int)ui->m_check_G->isChecked());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_H)
	{
		pData->m_strValue.setNum((int)ui->m_check_H->isChecked());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_AndOr)
	{
		pData->m_strValue.setNum((int)ui->m_rbtn_LogicAnd->isChecked());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID__B01)
	{
		pData->m_strValue.setNum((int)ui->m_check_B01->isChecked());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID__B02)
	{
		pData->m_strValue.setNum((int)ui->m_check_B02->isChecked());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID__B03)
	{
		pData->m_strValue.setNum((int)ui->m_check_B03->isChecked());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID__B04)
	{
		pData->m_strValue.setNum((int)ui->m_check_B04->isChecked());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID__B05)
	{
		pData->m_strValue.setNum((int)ui->m_check_B05->isChecked());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID__B06)
	{
		pData->m_strValue.setNum((int)ui->m_check_B06->isChecked());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID__B07)
	{
		pData->m_strValue.setNum((int)ui->m_check_B07->isChecked());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID__B08)
	{
		pData->m_strValue.setNum((int)ui->m_check_B08->isChecked());
	}
	
}

void QLowVolBinarysDlg::on_m_btnOK_clicked()
{
	this->done(Accepted);
}

void QLowVolBinarysDlg::on_m_btnCancel_clicked()
{
	this->close();
}
void QLowVolBinarysDlg::CheckAllPresence(CExBaseList *pParas)
{
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_A);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_B);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_C);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_D);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_E);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_F);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_G);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_H);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID_AndOr);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID__B01);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID__B02);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID__B03);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID__B04);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID__B05);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID__B06);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID__B07);
	CheckForPresence(pParas,STT_MULTI_MACRO_LOWVOL_PARAS_ID__B08);
}
void QLowVolBinarysDlg::UpdataAllBinarys(CExBaseList *pAllParas)
{
	//20240626 luozibing 通用参数修改后，修改表格中所有项数据开入开出量设置
	CSttMacroTest *pSttMacroTest = NULL;
	CExBaseList *pItem = NULL;
	CSttMacroTestParaDatas *pParaDatas = NULL;
	POS pos = pAllParas->GetHeadPosition();

	while (pos != NULL)
	{
		pItem = (CExBaseList*)pAllParas->GetNext(pos);
		if (pItem->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
		{
			pSttMacroTest = (CSttMacroTest *)pItem;
			pSttMacroTest->m_nModified = 1;
			pParaDatas = pSttMacroTest->GetSttMacroTestParaDatas(FALSE, "");

			if (pParaDatas != NULL)
			{
				CheckAllPresence(pParaDatas);
				GetDatas(pParaDatas);
			}
		}
	}
	return;
}


BOOL QLowVolBinarysDlg::CheckItemsModify(CExBaseList *pItem)
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
        if (pData->m_strValue != pData_New->m_strValue)
        {
            m_nModify = 1;
            return TRUE;
        }
    }
    return FALSE;
}

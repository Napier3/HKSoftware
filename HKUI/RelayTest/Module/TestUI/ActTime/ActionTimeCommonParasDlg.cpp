#include "ActionTimeCommonParasDlg.h"
#include "ui_ActionTimeCommonParasDlg.h"
#include "ActionTimeCommon.h"
#include "SttMultiMacroActionTimeParasDefine.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include <cmath>
#include "../../XLangResource_Native.h"

extern CFont *g_pSttGlobalFont;

QActionTimeCommonParasDlg::QActionTimeCommonParasDlg(QWidget *parent) :
QDialog(parent),
ui(new Ui::QActionTimeCommonParasDlg)
{
	ui->setupUi(this);
    m_nInputWidgetWidth = 150;
	InitUI();
    m_nModify= 0;
}

QActionTimeCommonParasDlg::~QActionTimeCommonParasDlg()
{
	delete ui;
}

void QActionTimeCommonParasDlg::InitUI()
{
	this->setFont(*g_pSttGlobalFont);

	CString strPngPath;
#ifdef _PSX_QT_WINDOWS_
    strPngPath = _P_GetResourcePath();
    strPngPath = strPngPath + _T("images/ActionTimeTest.png");
#else
    strPngPath =  ":/ctrls/images/ActionTimeTest.png";
#endif
    this->setWindowIcon(QIcon(QPixmap(strPngPath)));

    ui->m_editFaultTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editIPre->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editPreAngle->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editPreFaultTime->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editPreFre->setFixedWidth(m_nInputWidgetWidth);
    ui->m_editUPre->setFixedWidth(m_nInputWidgetWidth);

    this->setWindowTitle(g_sLangTxt_Gradient_CommonParas);
    ui->m_gbNormal->setTitle(g_sLangTxt_Gradient_Norm);
    ui->m_gbFault->setTitle(g_sLangTxt_Gradient_Failure);
    ui->m_labTimePre->setText(g_sLangTxt_Impedance_NormalTime);
    ui->m_labUPre->setText(g_sLangTxt_ActionTime_NormalVol);
    ui->m_labIPre->setText(g_sLangTxt_ActionTime_NormalCur);
    ui->m_labPreAng->setText(g_sLangTxt_ActionTime_NormalAngle);
    ui->m_labPreFre->setText(g_sLangTxt_ActionTime_NormalFre);
    ui->m_labFaultTime->setText(g_sLangTxt_ActionTime_FaultTime);
    ui->m_btnOk->setText(g_sLangTxt_OK);
    ui->m_btnCancel->setText(g_sLangTxt_Cancel);

    return;
}

void QActionTimeCommonParasDlg::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREFAULTTIME)
	{
		ui->m_editPreFaultTime->setText(ActTimeValueCheck(pData->m_strValue, PREFAULTTIME_MAX, PREFAULTTIME_MIN, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_UPRE)
	{
        ui->m_editUPre->setText(ActTimeValueCheck(pData->m_strValue, UPRE_MAX, UPRE_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_IPRE)
	{
        ui->m_editIPre->setText(ActTimeValueCheck(pData->m_strValue, IPRE_MAX, IPRE_MIN, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREANGLE)
	{
        ui->m_editPreAngle->setText(ActTimeValueCheck(pData->m_strValue, PREANGLE_MAX, PREANGLE_MIN, 2));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREFRE)
	{
        ui->m_editPreFre->setText(ActTimeValueCheck(pData->m_strValue, PREFRE_MAX, PREFRE_MIN, 3));
	}
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTTIME)
    {
        ui->m_editFaultTime->setText(ActTimeValueCheck(pData->m_strValue, FAULTTIME_MAX, FAULTTIME_MIN, 3));
    }

	return;
}

void QActionTimeCommonParasDlg::GetPageToValue(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREFAULTTIME)
	{
		pData->m_strValue = ui->m_editPreFaultTime->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_UPRE)
	{
		pData->m_strValue = ui->m_editUPre->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_IPRE)
	{
		pData->m_strValue = ui->m_editIPre->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREANGLE)
	{
		pData->m_strValue = ui->m_editPreAngle->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREFRE)
	{
		pData->m_strValue = ui->m_editPreFre->text();
	}
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTTIME)
    {
        pData->m_strValue = ui->m_editFaultTime->text();
    }

	return;
}

void QActionTimeCommonParasDlg::CheckAllPresence(CExBaseList *pParas)
{
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREFAULTTIME);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_UPRE);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_IPRE);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREANGLE);
	ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREFRE);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTTIME);

	return;
}

void QActionTimeCommonParasDlg::GetDatas(CExBaseList *pParas)
{
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
}

void QActionTimeCommonParasDlg::SetDatas(CExBaseList *pParas)
{
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

	return;
}

void QActionTimeCommonParasDlg::UpdateCurrentCommonParas(CExBaseList *pItem)
{
	CSttMacroTest *pSttMacroTest = NULL;

	pSttMacroTest = (CSttMacroTest *)pItem;
	pSttMacroTest->m_nModified = 1;
	CheckAllPresence(pItem);
	GetDatas(pItem);

	return;
}

void QActionTimeCommonParasDlg::UpdateAllCommonParas(CExBaseList *pAllItems)
{
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

	return;
}

void QActionTimeCommonParasDlg::on_m_editPreFaultTime_editingFinished()
{
	ui->m_editPreFaultTime->setText(ActTimeValueCheck(ui->m_editPreFaultTime->text(),PREFAULTTIME_MAX, PREFAULTTIME_MIN, 3));
	return;
}

void QActionTimeCommonParasDlg::on_m_editUPre_editingFinished()
{
	ui->m_editUPre->setText(ActTimeValueCheck(ui->m_editUPre->text(),UPRE_MAX, UPRE_MIN, 3));
	return;  
}

void QActionTimeCommonParasDlg::on_m_editIPre_editingFinished()
{
	ui->m_editIPre->setText(ActTimeValueCheck(ui->m_editIPre->text(),IPRE_MAX, IPRE_MIN, 3));
	return;  
}

void QActionTimeCommonParasDlg::on_m_editPreAngle_editingFinished()
{
    ui->m_editPreAngle->setText(ActTimeValueCheck(ui->m_editPreAngle->text(),PREANGLE_MAX, PREANGLE_MIN, 2));
	return;  
}

void QActionTimeCommonParasDlg::on_m_editPreFre_editingFinished()
{
	ui->m_editPreFre->setText(ActTimeValueCheck(ui->m_editPreFre->text(),PREFRE_MAX, PREFRE_MIN, 3));
	return;  
}

void QActionTimeCommonParasDlg::on_m_editFaultTime_editingFinished()
{
    ui->m_editFaultTime->setText(ActTimeValueCheck(ui->m_editFaultTime->text(), FAULTTIME_MAX, FAULTTIME_MIN, 3));
}

BOOL QActionTimeCommonParasDlg::CheckItemsModify(CExBaseList *pAllItems)
{
    if (pAllItems == NULL)
    {
        return FALSE;
    }
    CSttMacroTestParaDatas paraDatas;
    CheckAllPresence(&paraDatas);
    GetDatas(&paraDatas);
    POS pos = pAllItems->GetHeadPosition();
    while(pos != NULL)
    {
        CSttMacroTestParaData *pData = (CSttMacroTestParaData *)pAllItems->GetNext(pos);
        CSttMacroTestParaData *pData_New = (CSttMacroTestParaData *)paraDatas.FindByID(pData->m_strID);
        if(pData_New == NULL)
        {
            continue;
        }

        if(fabs(pData->m_strValue.toFloat() - pData_New->m_strValue.toFloat())>0.0001)
        {
            m_nModify = 1;
            return TRUE;
        }
    }
    return FALSE;
}


void QActionTimeCommonParasDlg::on_m_btnOk_clicked()
{
	this->done(Accepted);
}

void QActionTimeCommonParasDlg::on_m_btnCancel_clicked()
{
	this->close();
}

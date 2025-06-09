#include "QSingleCharCurveEditDlg.h"
#include "ui_QSingleCharCurveEditDlg.h"
#include "../../../../../../Module/XLanguage/XLanguageResource.h"
#include "../../../../XLangResource_Native.h"
#include "../../ZKCharaCurve/QCharElementDlg.h"
#include "CharEditWidget_Distance_Eng.h"
#include "../../ZKCharaCurve/QCharElementDlg.h"
#include "../../ZKCharaCurve/QZKFeatureAddDig.h"
#include "../../../SttTestCntrFrameAPI.h"
#include "../../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/CommonMethod/commonMethod.h"
#include "../QCharacteristicEditDlg.h"
#include "../../../../../../AutoTest/Module/XLanguageResourceAts.h"
#include "CharEditMainDialog.h"
#include "../../../../../../Module/System/TickCount32.h"
#include <QProcess>
#include"../../../../TestUI/SttMultiMacroParasDefine.h"
#include "../../../../UI/SttTestCntrCmdDefine.h"
#include <QMessageBox>
#include <QSplitter>
#include "../../../../HtmlReport/SttXHtmlRptGenFactoryBase.h"

QSingleCharCurveEditDlg::QSingleCharCurveEditDlg(CCharacteristic *pCCharacteristic, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSingleCharCurveEditDlg)
{
    ui->setupUi(this);

    m_pCharacteristic_Exter = pCCharacteristic;
    m_pCharacteristic_Inner = NULL;
    m_pCharacteristic_Inner = (CCharacteristic *)pCCharacteristic->Clone();
    m_pCharacteristics_Inner = NULL;
    m_pCharacteristics_Inner = new CCharacteristics;
    m_pCharacteristics_Inner->AddNewChild(m_pCharacteristic_Inner);
    m_pGridTestPoint = 0;
    m_pCharactEditWidget = NULL;

    InitUI();
	UpdateDrawCharacters();
    UpdateCharElement();
    UpdateBtnEnable();
}

QSingleCharCurveEditDlg::~QSingleCharCurveEditDlg()
{
    if(m_pCharacteristics_Inner != NULL)
    {
        delete m_pCharacteristics_Inner;
        m_pCharacteristics_Inner = NULL;
    }
    else if(m_pCharacteristic_Inner != NULL)
    {
        delete m_pCharacteristic_Inner;
        m_pCharacteristic_Inner = NULL;
    }

    delete ui;
}

void QSingleCharCurveEditDlg::InitUI()
{
    this->setWindowTitle(/*_T("曲线编辑")*/g_sLangTxt_Gradient_CurveEditing);
    this->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    ui->m_btnInsert->setText(/*_T("插入元素")*/g_sLangTxt_Gradient_InsertElement);
    ui->m_btnModify->setText(/*_T("修改元素")*/g_sLangTxt_Gradient_ModifyElement);
    ui->m_btnDelete->setText(/*_T("删除元素")*/g_sLangTxt_Gradient_DeleteElement);
    ui->m_cbAutoClose->setText(/*_T("边界自动闭合")*/g_sLangTxt_DistanceSearch_AutoClose);
    ui->m_btnInsert->setFont(*g_pSttGlobalFont);
    ui->m_btnModify->setFont(*g_pSttGlobalFont);
    ui->m_btnDelete->setFont(*g_pSttGlobalFont);
    ui->m_cbAutoClose->setFont(*g_pSttGlobalFont);

    m_pGridTestPoint = new QCharEditGrid_TestPoint(this);
    m_pGridTestPoint->InitGrid();
    m_pGridTestPoint->AttachDataViewOptrInterface(this);
    ui->m_pEditGridVLayout->insertWidget(1, m_pGridTestPoint);
    m_pGridTestPoint->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_pCharactEditWidget = new QCharactEditWidget_Eng(m_pCharacteristics_Inner, this, true, true, true);
    m_pCharactEditWidget->m_pCharacterDrawView->UpdateAxisType(AXIS_TYPE_ID_CARTES,TRUE);
    m_pCharactEditWidget->SetChangePlot(TRUE);
    m_pCharactEditWidget->EnableSetting(TRUE);
    m_pCharactEditWidget->setObjectName(QString::fromUtf8("QCharactEditWidget_Eng"));
    m_pCharactEditWidget->SetAxisName(/*_T("R/Ω ")*/g_sLangTxt_DistanceSearch_XAxisName,/*_T("X/Ω ")*/g_sLangTxt_DistanceSearch_YAxisName,g_sLangTxt_Distance_ImpActBorder/*("阻抗动作边界")*/);
    m_pCharactEditWidget->m_pCharacterDrawView->SetIsShowAng(true);
    m_pCharactEditWidget->m_pCharacterDrawView->SetIsShowText(false);
	QWidget *pCharWidget = new QWidget(this);
	QVBoxLayout *pCharVLayout = new QVBoxLayout(pCharWidget);
	pCharVLayout->setContentsMargins(0, 0, 0, 0);
	pCharVLayout->addWidget(m_pCharactEditWidget);	//m_pCharactEditWidget基类QImpCharactWidget的resizeEvent会resize为父窗口大小，套一层widget适应窗口大小
	m_pCharactEditWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);	
	ui->m_pCharWidgetHLayout->addWidget(pCharWidget);
	pCharWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->m_btnOk->setText(g_sLangTxt_OK);
    ui->m_btnCancel->setText(g_sLangTxt_Cancel);

    if(m_pCharacteristic_Inner->m_nAutoClose)
        ui->m_cbAutoClose->setChecked(true);
    else
        ui->m_cbAutoClose->setChecked(false);

}

void QSingleCharCurveEditDlg::UpdateCharElement()
{
    if(m_pCharacteristic_Inner != NULL)
    {
        m_pGridTestPoint->ShowDatas(m_pCharacteristic_Inner->GetCharacterArea());
    }
    else
    {
        m_pGridTestPoint->ShowDatas(NULL);
    }
}

void QSingleCharCurveEditDlg::UpdateBtnEnable()
{
    if(m_pGridTestPoint == NULL)
        return;

    if (m_pGridTestPoint->GetCurrSelData() != NULL)
    {
        ui->m_btnModify->setEnabled(true);
        ui->m_btnDelete->setEnabled(true);
    }
    else
    {
        ui->m_btnModify->setEnabled(false);
        ui->m_btnDelete->setEnabled(false);
    }
}

void QSingleCharCurveEditDlg::UpdateDrawCharacters()
{
	if (m_pCharactEditWidget != NULL)
	{
		m_pCharactEditWidget->slot_UpdateDrawCharacters(NULL);
	}
}

void QSingleCharCurveEditDlg::on_m_btnModify_clicked()
{
    CCharElement *pObj = (CCharElement*)m_pGridTestPoint->GetCurrSelData();

    if ((pObj == NULL)||(m_pCharacteristic_Inner == NULL))
        return;

    CCharacterArea *pCharArea = m_pCharacteristic_Inner->GetCharacterArea();
    CCharacterArea *pCharAreaTemp  = new CCharacterArea;
    CCharElement *pObjTemp = (CCharElement*)pObj->Clone();
    pCharAreaTemp->AddNewChild(pObjTemp);

    QCharElementDlg dlg(pObj,this);
    dlg.InitParaCache(pCharAreaTemp);
    dlg.setFont(*g_pSttGlobalFont);

    if (dlg.exec() != QDialog::Accepted)
    {
        return;
    }

    if (dlg.GetNewElement()->GetClassID() == CHARCLASSID_CCHARELEMENTMHO)
    {
        pCharArea->DeleteChildren();
        pCharArea->AddNewChild(dlg.GetNewElement());
    }
    else if (pObj->GetClassID() == dlg.GetNewElement()->GetClassID())
    {
        dlg.GetNewElement()->Copy(pObj);
    }
    else
    {
        CCharElement* pNewElement = dlg.GetNewElement();
        pCharArea->InsertAfter(pCharArea->Find(pObj),pNewElement);
        pCharArea->Delete(pObj);
        pNewElement->SetParent(pCharArea);
    }

    UpdateDrawCharacters();
    UpdateCharElement();
    delete pCharAreaTemp;
}

void QSingleCharCurveEditDlg::on_m_btnDelete_clicked()
{
    CExBaseObject *pCurrLine = m_pGridTestPoint->GetCurrSelData();

    if (m_pCharacteristic_Inner == NULL)
        return;

    m_pGridTestPoint->DeleteDataRow(pCurrLine);

	UpdateDrawCharacters();
    m_pGridTestPoint->setCurrentCell(0,2);
    UpdateCharElement();
    UpdateBtnEnable();
}

void QSingleCharCurveEditDlg::on_m_btnInsert_clicked()
{	
    QCharElementDlg dlg(NULL,this);
    dlg.InitParaCache(&m_oLineCache);
    dlg.setFont(*g_pSttGlobalFont);

    if (dlg.exec() != QDialog::Accepted)
    {
        return;
    }

    if (m_pCharacteristic_Inner == NULL)
        return;

    CCharacterArea *pCharArea = m_pCharacteristic_Inner->GetCharacterArea();
    CCharElement *pNew = dlg.GetNewElement();
    CCharElement *pCurrSelElement = (CCharElement*)m_pGridTestPoint->GetCurrSelData();

    if (pNew->GetClassID() == CHARCLASSID_CCHARELEMENTMHO)
    {
        pCharArea->DeleteChildren();
        pCharArea->AddNewChild(pNew);
    }
    else if (pCurrSelElement != NULL)
    {
        pCharArea->InsertAfter(pCharArea->Find(pCurrSelElement), pNew);
        pNew->SetParent(pCharArea);
    }
    else
    {
        pCharArea->AddNewChild(pNew);
    }

    int rowCount = m_pGridTestPoint->rowCount();
    m_pGridTestPoint->ShowDatas(pCharArea);
    m_pGridTestPoint->setFocus();
    m_pGridTestPoint->setCurrentCell(rowCount,2);

	UpdateDrawCharacters();

    ui->m_btnDelete->setEnabled(true);
    UpdateCharElement();
}

void QSingleCharCurveEditDlg::on_m_cbAutoClose_stateChanged(int arg1)
{
    if (m_pCharacteristic_Inner != NULL)
    {
        if (ui->m_cbAutoClose->isChecked())
            m_pCharacteristic_Inner->m_nAutoClose = 1;
        else
            m_pCharacteristic_Inner->m_nAutoClose = 0;

		UpdateDrawCharacters();
    }
}

void QSingleCharCurveEditDlg::on_m_btnOk_clicked()
{
    m_pCharacteristic_Exter->DeleteAll();
    m_pCharacteristic_Exter->AppendClone(m_pCharacteristic_Inner, TRUE);
    m_pCharacteristic_Exter->InitAfterRead();
    m_pCharacteristic_Inner->CopyOwn(m_pCharacteristic_Exter);
    this->done(Accepted);
}

void QSingleCharCurveEditDlg::on_m_btnCancel_clicked()
{
    this->close();
}

void QSingleCharCurveEditDlg::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
    UpdateBtnEnable();
    if (pGridCtrl == m_pGridTestPoint)
    {
        CCharElement *pCurrSelElement = (CCharElement*)m_pGridTestPoint->GetCurrSelData();
        if (pCurrSelElement != NULL)
        {
			m_pCharactEditWidget->UI_SetActiveElement((CXDrawElement*)pCurrSelElement->m_pDataRef);
            m_pCharactEditWidget->update(); //更新编辑曲线界面坐标轴显示当前选中
        }
    }
}

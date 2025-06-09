#include "CharEditWidget_Diff.h"

#include "../../SttTestCntrFrameBase.h"
#include "../../Module/CommonMethod/commonMethod.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/DataMngr/DvmValues.h"
#include "../../../XLangResource_Native.h"
#include "QCharEditRadioHarmWidget.h"
#include "QCharEditRadioNormalWidget.h"
#include "../../../../../Module/XLanguage/XLanguageResource.h"

//////////////////////////////////////////////////////////////////////////
//QCharEditGrid_Character
QCharEditGrid_DiffLine::QCharEditGrid_DiffLine(QWidget* pParent) : QCharEditGridBase(pParent)
{
	connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(slot_doubleClicked(int,int)),Qt::UniqueConnection);
}

QCharEditGrid_DiffLine::~QCharEditGrid_DiffLine()
{

}

void QCharEditGrid_DiffLine::InitGridTitle()
{
	CString astrGridTitle[DIFF_GRID_CLOS] = {_T("扫描线段"), _T("系统点数"), _T("自定义点数"), _T("误差带")};
	xlang_GetLangStrByFile(astrGridTitle[0],"State_Scanlinesegments");
	xlang_GetLangStrByFile(astrGridTitle[1],"Native_SyStempoints");
	xlang_GetLangStrByFile(astrGridTitle[2],"Native_Custompoints");
	xlang_GetLangStrByFile(astrGridTitle[3],"sErrorBand");
	int iGridWidth[DIFF_GRID_CLOS]={110, 80, 95, 70};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, DIFF_GRID_CLOS);
}

void QCharEditGrid_DiffLine::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CCharElementLined* pLine = (CCharElementLined*)pData;

	if(pLine->m_strName.GetLength())
	{
		Show_StaticString(pData, nRow, 0, pData->m_strName);
		Show_Long(pData, nRow, 1, pLine->GetTestPointsRef(), TRUE, _T(""), EndEditCell_TestPoints);
		CString strUserPoints;
		strUserPoints.Format("%d", pLine->GetUserTestPoints());
		Show_StaticString(pData, nRow, 2, strUserPoints);
		Show_String(pData, nRow, 3, &pLine->m_strErrLength, EndEditCell_ErrorBand);

		nRow++;
	}
}

void QCharEditGrid_DiffLine::EndEditCell_TestPoints(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pObj != NULL);
	long nCurrPoints = CString_To_long(pCell->text());

	if(*(pVCellData->pnValue) != nCurrPoints)
	{
		*(pVCellData->pnValue) = nCurrPoints;
		((QCharEditGrid_DiffLine*)pGrid)->EmitTestPointsErrorBandChanged();
	}
}

void QCharEditGrid_DiffLine::EndEditCell_ErrorBand(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pObj != NULL);
	if(*(pVCellData->pString) != pCell->text())
	{
		*(pVCellData->pString) = pCell->text();
		((QCharEditGrid_DiffLine*)pGrid)->EmitTestPointsErrorBandChanged();
	}
}

void QCharEditGrid_DiffLine::EmitTestPointsErrorBandChanged()
{
	emit sig_TestPointsErrorBandChanged();
}

void QCharEditGrid_DiffLine::EmitCharChanged()
{
	emit sig_DiffCharChanged();
}


void QCharEditGrid_DiffLine::slot_doubleClicked(int nRow,int nCol)
{
	GridDoubleClicked_ShowKeyBoard(nRow,nCol);
}


void QCharEditGrid_DiffLine::GridDoubleClicked_ShowKeyBoard(int nRow,int nCol)
{
	if (nCol <= 0)
	{
		return;
	}

	QGV_ITEM *pParamItem = GetCell(nRow,nCol); 


	if (pParamItem == NULL)
	{
		return;
	}

	switch(nCol)
	{

	case 1:
	case 2: 
		{
			QString strValue = pParamItem->text();
			GetWidgetBoard_DigitData(4,strValue,pParamItem, parentWidget()->parentWidget());
			//pParamItem->setText(strValue);
		}
		break;
	default:
		break;

	}

}

void QCharEditGrid_DiffLine::slot_CurrentCellChanged( int currentRow, int currentColumn, int previousRow, int previousColumn )
{
	if(currentRow == previousRow)
	{
		return;
	}

	if (currentRow>=0)
	{
		OnDataSelChanged(currentRow,currentColumn);
	}
}	

///////////////////////////////////////////////////////////////线路差动///////////////////////////////////////////////////////////////////////////////////////

//QCharEditWidget_LineDiff
QCharEditWidget_LineDiff::QCharEditWidget_LineDiff(BOOL bShowIp2,QWidget *parent)
: QWidget(parent)
{
	m_pCharEditWidget = this;
	m_bShowIp2 = bShowIp2;
	m_oDiffCharCal.m_bFixYMax = TRUE;
//	ui.setupUi(this);
//	ui.m_layoutVert->insertWidget(1, m_pGridCharLine);

	m_pMainWidget = (QCharEditMainWidget*)parentWidget();

	InitUI();
	InitConnect();
	InitChar();
//	UpdateChar(FALSE,FALSE,FALSE);
	SetDiffFont();
}

QCharEditWidget_LineDiff::~QCharEditWidget_LineDiff()
{

}

void QCharEditWidget_LineDiff::InitUI()
{
	CString strText;
	m_pMain_VLayout = new QVBoxLayout(this);
	m_pDiffChar_GridLayout = new QGridLayout(this);

	strText = /*_T("名称")*/g_sLangTxt_Name; //lcq
	m_pCharName_Label = new QLabel(strText);
	strText = /*_T("定值")*/g_sLangTxt_FixedValue; //lcq
	m_pCharSetting_Label = new QLabel(strText);
     strText = /*_T("电流(A)")*/g_sLangTxt_State_Acurrent; //lcq
	m_pCharCurrent_Label = new QLabel(strText);
	strText = /*_T("斜率")*/g_sLangTxt_Gradient_Slope;//lcq
	m_pCharK_Label = new QLabel(strText);
	m_pDiffChar_GridLayout->addWidget(m_pCharName_Label,0,0);
	m_pDiffChar_GridLayout->addWidget(m_pCharSetting_Label,0,1);
	m_pDiffChar_GridLayout->addWidget(m_pCharCurrent_Label,0,2);
	m_pDiffChar_GridLayout->addWidget(m_pCharK_Label,0,3);

	strText = /*_T("启动门槛")*/g_sLangTxt_Gradient_StartTs; //lcq
	m_pIcdqd_Label = new QLabel(strText);
	strText = /*_T("启动电流")*/g_sLangTxt_Gradient_StartCur; //lcq
	m_pIcdqd_SettingLabel = new QLabel(strText);
	m_pIcdqd_Edit = new QSttLineEdit(this);
	m_pKcdqd_Edit = new QSttLineEdit(this);
	m_pKcdqd_Edit->setEnabled(false);
	m_pDiffChar_GridLayout->addWidget(m_pIcdqd_Label,1,0);
	m_pDiffChar_GridLayout->addWidget(m_pIcdqd_SettingLabel,1,1);
	m_pDiffChar_GridLayout->addWidget(m_pIcdqd_Edit,1,2);
	m_pDiffChar_GridLayout->addWidget(m_pKcdqd_Edit,1,3);

	strText = /*_T("斜率1")*/g_sLangTxt_Gradient_Slope + '1'; //lcq
	m_pK1_Label = new QLabel(strText);
	strText = /*_T("拐点1")*/g_sLangTxt_Gradient_Inflectp + '1'; //lcq
	m_pK1_SettingLabel = new QLabel(strText);
	m_pIp1_Edit = new QSttLineEdit(this);
	m_pIp1_Edit->setEnabled(false);
	m_pKp1_Edit = new QSttLineEdit(this);
	m_pDiffChar_GridLayout->addWidget(m_pK1_Label,2,0);
	m_pDiffChar_GridLayout->addWidget(m_pK1_SettingLabel,2,1);
	m_pDiffChar_GridLayout->addWidget(m_pIp1_Edit,2,2);
	m_pDiffChar_GridLayout->addWidget(m_pKp1_Edit,2,3);

	strText = /*_T("斜率2")*/g_sLangTxt_Gradient_Slope + '2'; //lcq
	m_pK2_CheckBox = new QSttCheckBox(strText);
	strText = /*_T("拐点2")*/g_sLangTxt_Gradient_Inflectp + '2'; //lcq
	m_pK2_SettingLabel = new QLabel(strText);
	m_pIp2_Edit = new QSttLineEdit(this);
	m_pKp2_Edit = new QSttLineEdit(this);
	m_pDiffChar_GridLayout->addWidget(m_pK2_CheckBox,3,0);
	m_pDiffChar_GridLayout->addWidget(m_pK2_SettingLabel,3,1);
	m_pDiffChar_GridLayout->addWidget(m_pIp2_Edit,3,2);
	m_pDiffChar_GridLayout->addWidget(m_pKp2_Edit,3,3);

	m_pK2_CheckBox->setVisible(m_bShowIp2);
	m_pK2_SettingLabel->setVisible(m_bShowIp2);
	m_pIp2_Edit->setVisible(m_bShowIp2);
	m_pKp2_Edit->setVisible(m_bShowIp2);

	strText = /*_T("差流极值")*/g_sLangTxt_Gradient_DiffFlowEx; //lcq
	m_pMaxId_Label = new QLabel(strText);
	m_pMaxId_Edit = new QSttLineEdit(this);
	m_pDiffChar_GridLayout->addWidget(m_pMaxId_Label,4,1);
	m_pDiffChar_GridLayout->addWidget(m_pMaxId_Edit,4,2);


	m_pGridCharLine = new QCharEditGrid_DiffLine(this);
	m_pGridCharLine->InitGrid();
	m_pGridCharLine->AttachDataViewOptrInterface(this);

	m_pCustomAdd_HLayout = new QHBoxLayout(this);
	strText = /*_T("制动电流(A)")*/g_sLangTxt_Native_Acurrent; //lcq
	m_pIdCustom_Label = new QLabel(strText);
	m_pIdCustom_Edit = new QSttLineEdit(this);
	m_pAddCustom_HorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	strText = /*_T("添加自定义点")*/g_sLangTxt_Gradient_AddCusp; //lcq
	m_pAddCustomPoint_PushButton = new QPushButton(strText);
	strText =/* _T("清空自定义点")*/g_sLangTxt_Gradient_Emptycusp; //lcq
	m_pClearCustomPoint_PushButton = new QPushButton(strText);
	m_pCustomAdd_HLayout->addWidget(m_pIdCustom_Label);
	m_pCustomAdd_HLayout->addWidget(m_pIdCustom_Edit);
	m_pCustomAdd_HLayout->addItem(m_pAddCustom_HorizontalSpacer);
	m_pCustomAdd_HLayout->addWidget(m_pAddCustomPoint_PushButton);
	m_pCustomAdd_HLayout->addWidget(m_pClearCustomPoint_PushButton);

	m_pMain_VLayout->addLayout(m_pDiffChar_GridLayout);
	m_pMain_VLayout->addWidget(m_pGridCharLine);
	m_pMain_VLayout->addLayout(m_pCustomAdd_HLayout);

	m_pCharName_Label->setAlignment(Qt::AlignCenter);
	m_pCharSetting_Label->setAlignment(Qt::AlignCenter);
	m_pCharCurrent_Label->setAlignment(Qt::AlignCenter);
	m_pCharK_Label->setAlignment(Qt::AlignCenter);
	m_pK1_Label->setAlignment(Qt::AlignRight);

	initMaxPositiveEdit(m_pIcdqd_Edit);
	initMaxPositiveEdit(m_pIp1_Edit);
	initMaxPositiveEdit(m_pIp2_Edit);
	initMaxPositiveEdit(m_pMaxId_Edit);
	initMaxPositiveEdit(m_pKcdqd_Edit);
	initMaxPositiveEdit(m_pKp1_Edit);
	initMaxPositiveEdit(m_pKp2_Edit);
	initMaxPositiveEdit(m_pIdCustom_Edit);
	m_pIdCustom_Edit->setText("1.5");


	m_pIp2_Edit->setEnabled(false);
	m_pKp2_Edit->setEnabled(false);
}
void QCharEditWidget_LineDiff::SetDiffFont()
{
	m_pGridCharLine->setFont(*g_pSttGlobalFont);
	m_pGridCharLine->horizontalHeader()->setFont(*g_pSttGlobalFont);

	m_pCharName_Label->setFont(*g_pSttGlobalFont);
	m_pCharSetting_Label->setFont(*g_pSttGlobalFont);
	m_pCharCurrent_Label->setFont(*g_pSttGlobalFont);
	m_pCharK_Label->setFont(*g_pSttGlobalFont);

	m_pIcdqd_Label->setFont(*g_pSttGlobalFont);
	m_pK1_Label->setFont(*g_pSttGlobalFont);
	m_pK2_CheckBox->setFont(*g_pSttGlobalFont);

	m_pIcdqd_SettingLabel->setFont(*g_pSttGlobalFont);
	m_pK1_SettingLabel->setFont(*g_pSttGlobalFont);
	m_pK2_SettingLabel->setFont(*g_pSttGlobalFont);
	m_pMaxId_Label->setFont(*g_pSttGlobalFont);

	m_pIcdqd_Edit->setFont(*g_pSttGlobalFont);
	m_pIp1_Edit->setFont(*g_pSttGlobalFont);
	m_pIp2_Edit->setFont(*g_pSttGlobalFont);
	m_pMaxId_Edit->setFont(*g_pSttGlobalFont);

	m_pKcdqd_Edit->setFont(*g_pSttGlobalFont);
	m_pKp1_Edit->setFont(*g_pSttGlobalFont);
	m_pKp2_Edit->setFont(*g_pSttGlobalFont);


	//添加自定义点相关控件
	m_pIdCustom_Label->setFont(*g_pSttGlobalFont);
	m_pIdCustom_Edit->setFont(*g_pSttGlobalFont);
	m_pAddCustomPoint_PushButton->setFont(*g_pSttGlobalFont);
	m_pClearCustomPoint_PushButton->setFont(*g_pSttGlobalFont);
}

void QCharEditWidget_LineDiff::OnLeftButtonDown()
{
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	m_pMainWidget->m_pImpCharactWidget->CalPointVertHorzLine(0, CHAR_TESTLINE_MODE_ID_VERT);
	UpdateEdit_IrValueUserPoint();
}

void QCharEditWidget_LineDiff::InitConnect()
{
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	connect(this, SIGNAL(sig_CharChanged(CExBaseObject *,int)), m_pMainWidget,SLOT(slot_UpdateDrawCharacters(CExBaseObject *,int)));
	connect(m_pGridCharLine, SIGNAL(sig_CharChanged(CExBaseObject *)), m_pMainWidget,SLOT(slot_UpdateDrawCharacters(CExBaseObject *)));

	connect(m_pGridCharLine, SIGNAL(sig_TestPointsErrorBandChanged()), this,SLOT(slot_TestPointsErrorBandChanged()));
	connect(m_pGridCharLine, SIGNAL(sig_DiffCharChanged()), this,SLOT(slot_DiffCharChanged()));
	connect(m_pAddCustomPoint_PushButton, SIGNAL(clicked(bool)), this,SLOT(slot_btnUserAdd(bool)));
	connect(m_pClearCustomPoint_PushButton, SIGNAL(clicked(bool)), this,SLOT(slot_btnUserClear(bool)));
	connect(m_pIdCustom_Edit,  SIGNAL(editingFinished ()), this, SLOT(slot_IdValue_editingFinished()));

	connect(m_pIcdqd_Edit,SIGNAL(editingFinished()),this,SLOT(on_m_edtSet_Istart_editingFinished()));
	connect(m_pKcdqd_Edit,SIGNAL(editingFinished()),this,SLOT(on_m_edtSet_Kstart_editingFinished()));
	connect(m_pIp1_Edit,SIGNAL(editingFinished()),this,SLOT(on_m_edtSet_Ip1_editingFinished()));
	connect(m_pKp1_Edit,SIGNAL(editingFinished()),this,SLOT(on_m_edtSet_K1_editingFinished()));
	connect(m_pIp2_Edit,SIGNAL(editingFinished()),this,SLOT(on_m_edtSet_Ip2_editingFinished()));
	connect(m_pKp2_Edit,SIGNAL(editingFinished()),this,SLOT(on_m_edtSet_K2_editingFinished()));
	connect(m_pMaxId_Edit,SIGNAL(editingFinished()),this,SLOT(slot_MaxIdEditingFinished()));

	connect(m_pK2_CheckBox,SIGNAL(clicked()),this,SLOT(on_m_chkLine2_clicked()));

#ifdef _PSX_QT_LINUX_

	connect(m_pIcdqd_Edit,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(m_pKcdqd_Edit,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(m_pIp1_Edit,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(m_pKp1_Edit,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(m_pIp2_Edit,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(m_pKp2_Edit,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(m_pMaxId_Edit,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));

#endif

}

void QCharEditWidget_LineDiff::on_m_onlineEdit_Changed()
{
	QSttLineEdit* pEditLine = qobject_cast<QSttLineEdit*>(sender());

	if (pEditLine->text().isEmpty())
	{
		pEditLine->setText("0.0");
	}

	QString str = pEditLine->text();
	GetWidgetBoard_DigitData(4,str,pEditLine,this);

	if (str.right(1).contains("."))
	{
		str.append("000");
	}
	
	m_pMainWidget->m_bCharChanged = TRUE;

	// 	pEditLine->setText(str);
	// 	pEditLine->SetEditFinished();
}

void QCharEditWidget_LineDiff::slot_TestPointsErrorBandChanged()
{
	GetTestPointNumErrorBand();
	emit sig_CharChanged(GetCurrentCharacter(),TRUE);	
}

void QCharEditWidget_LineDiff::slot_DiffCharChanged()
{
	emit sig_CharChanged(GetCurrentCharacter(),TRUE);	
}

void QCharEditWidget_LineDiff::slot_IdValue_editingFinished()
{
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	CString strIdValue = m_pIdCustom_Edit->text();
	m_pMainWidget->m_pImpCharactWidget->UpdateVertLine(CString_To_double(strIdValue));

	m_pMainWidget->m_bCharChanged = TRUE;
}

void QCharEditWidget_LineDiff::slot_MaxIdEditingFinished()
{
	float fv = SetParaI(m_pMaxId_Edit, m_oDiffCharCal.m_fYMax);
	long nMinValue = 0;

	if (m_pK2_CheckBox->isChecked())
	{
		float y1 = m_oDiffCharCal.m_fIp1*m_oDiffCharCal.m_fKid0 + m_oDiffCharCal.m_fIcdqd;
		nMinValue = y1 + (m_oDiffCharCal.m_fIp2-m_oDiffCharCal.m_fIp1)*m_oDiffCharCal.m_fKid1; //拐点2的Y坐标
	} 
	else
	{
		nMinValue = m_oDiffCharCal.m_fIcdqd + m_oDiffCharCal.m_fIp1*m_oDiffCharCal.m_fKid0;
	}

	if (m_oDiffCharCal.m_fYMax <= nMinValue)
	{
		m_oDiffCharCal.m_fYMax = nMinValue*1.4;
		m_pMaxId_Edit->setText(QString::number(m_oDiffCharCal.m_fYMax,'f',3));
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("差流极值设置不能小于拐点电流对应差流值.")*/g_sLangTxt_Gradient_NoLessCor.GetString()); //lcq
	}

	UpdateChar();
}


void QCharEditWidget_LineDiff::UpdateEdit_IrValueUserPoint()
{
    CXDrawLine* pLine = stt_Frame_GetCharLibLeftButtonLine();
	CXDrawPoint* pPoint = (CXDrawPoint*)pLine->GetHead();

	if(!pPoint)
	{
		return;
	}

	CString strValue;
	strValue.Format(_T("%.03f"),pPoint->m_fX);
	disconnect(m_pIdCustom_Edit,  SIGNAL(editingFinished ()), this, SLOT(slot_IdValue_editingFinished()));
	m_pIdCustom_Edit->setText(strValue);
	connect(m_pIdCustom_Edit,  SIGNAL(editingFinished ()), this, SLOT(slot_IdValue_editingFinished()));
}

void QCharEditWidget_LineDiff::slot_btnUserAdd(bool bState)
{
    CXDrawLine* pLine = stt_Frame_GetCharLibLeftButtonLine();
	CXDrawPoint* pPoint = (CXDrawPoint*)pLine->GetHead();
	if(!pPoint)
	{
		return;
	}

	CCharacteristic* pChar = GetCurrentCharacter();

	if (pChar == NULL)
	{
		return;
	}

	CCharacterArea* pArea = pChar->GetCharacterArea();
	CCharElementLined* pCharLine = NULL;
	POS pos = pArea->GetHeadPosition();

	long nIndex = 0;
	while (pos)
	{
		pCharLine = (CCharElementLined*)pArea->GetNext(pos);
		double dXb = 0, dYb = 0, dXe = 0, dYe = 0;
		pCharLine->GetLine(dXb, dYb, dXe, dYe);
		if(dXb < pPoint->m_fX && pPoint->m_fX < dXe)
		{
			break;
		}
		nIndex++;
	}

	CCharTestLine* pTestLine = new CCharTestLine();
	pTestLine->m_strType = CHAR_TEST_LINE_TYPE_USER;
	pTestLine->m_nTestLineID = char_GetTestLineID(pCharLine, nIndex);
	pTestLine->m_fPos = pPoint->m_fX;
	pTestLine->m_fXset = pPoint->m_fX;
	pTestLine->m_fYset = pPoint->m_fY;
	pTestLine->m_fXb = pPoint->m_fX;
	pTestLine->m_fXe = pPoint->m_fX;
	pTestLine->m_fYb = pPoint->m_fY + pCharLine->GetErrorLength();
	pTestLine->m_fYe = pPoint->m_fY - pCharLine->GetErrorLength();
	pCharLine->AddNewChild(pTestLine);
	pCharLine->SetUserTestPoint(pCharLine->GetUserTestPoints() + 1);

	UpdateChar(TRUE);
}

void QCharEditWidget_LineDiff::slot_btnUserClear(bool bState)
{
	CCharacteristic* pChar = GetCurrentCharacter();

	if (pChar == NULL)
	{
		return;
	}

	CCharacterArea* pArea = pChar->GetCharacterArea();
	CCharElementLined* pCharLine = NULL;
	POS pos = pArea->GetHeadPosition();
	long nIndex = 0;
	while (pos)
	{
		pCharLine = (CCharElementLined*)pArea->GetNext(pos);
		for (int i = pCharLine->GetCount() - 1; i >= 0; i-- )
		{
			CCharTestLine* pTestLine = (CCharTestLine*)pCharLine->GetAt(i);
			if(pTestLine->m_strType == CHAR_TEST_LINE_TYPE_USER)
			{
				pCharLine->DeleteAt(i);
			}
		}
		pCharLine->SetUserTestPoint(0);
	}
	UpdateChar(TRUE);
}

void QCharEditWidget_LineDiff::on_m_chkLine2_clicked()
{
	bool bEnable = false;

	if(m_pK2_CheckBox->isChecked())
	{
		bEnable = true;
		m_oDiffCharCal.m_nKneePoints = CharDiff_RateCoef2_Index;
	}
	else
	{
		m_oDiffCharCal.m_nKneePoints = CharDiff_RateCoef1_Index;
	}

	m_pIp2_Edit->setEnabled(bEnable);
	m_pKp2_Edit->setEnabled(bEnable);
	UpdateChar();
}

float QCharEditWidget_LineDiff::SetParaI(QLineEdit* pEdit, float& fv)
{
	if (pEdit->text().isEmpty())
	{
		pEdit->setText("0.000");
	}

	QString str = pEdit->text();
	if (str.right(1).contains("."))
	{
		str.append(000);
	}

	fv = str.toFloat();
	fv = SetLimit(0,999.999,fv);
	pEdit->setText(QString::number(fv,'f',3));
	return fv;
}

float QCharEditWidget_LineDiff::SetParaK(QLineEdit* pEdit, float& fv)
{
	if (pEdit->text().isEmpty())
	{
		pEdit->setText("0.000");
	}

	QString str = pEdit->text();
	if (str.right(1).contains("."))
	{
		str.append(000);
	}

	fv = str.toFloat();
	fv = SetLimit(0,999.999,fv);
	pEdit->setText(QString::number(fv,'f',3));
	return fv;
}

void QCharEditWidget_LineDiff::InitDiffData()
{
	CString strText;

	strText.Format("%.3f", m_oDiffCharCal.m_fIcdqd);
	m_pIcdqd_Edit->setText(strText);

	strText.Format("%.3f", m_oDiffCharCal.m_fIp2);
	m_pIp2_Edit->setText(strText);

	m_oDiffCharCal.m_fKid0 = 0.0f;
//	strText.Format("%.3f", m_oDiffCharCal.m_fKid0);
	m_pKcdqd_Edit->setText(_T("0.000"));
	strText.Format("%.3f", m_oDiffCharCal.m_fKid1);
	m_pKp1_Edit->setText(strText);
	strText.Format("%.3f", m_oDiffCharCal.m_fKid2);
	m_pKp2_Edit->setText(strText);

	m_oDiffCharCal.m_fIp1 = m_oDiffCharCal.m_fIcdqd/m_oDiffCharCal.m_fKid1;
	strText.Format("%.3f", m_oDiffCharCal.m_fIp1);
	m_pIp1_Edit->setText(strText);

	strText.Format("%.3f", m_oDiffCharCal.m_fYMax);
	m_pMaxId_Edit->setText(strText);

	InitUI_Unit();
}

void QCharEditWidget_LineDiff::InitUI_Unit()
{
	CString strText,strText_IrAxis,strText_IdAxis;

	strText_IrAxis = _T("Ir(A)");
	strText_IdAxis = _T("Id(A)");

	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();

	if (m_pMainWidget != NULL)
	{
		m_pMainWidget->m_pImpCharactWidget->SetAxisName(strText_IrAxis,strText_IdAxis,_T(" "));
	}
}

void QCharEditWidget_LineDiff::InitChar()
{
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	m_pMainWidget->UpdateCharAxisType(AXIS_TYPE_ID_CARTES,FALSE);
	m_pMainWidget->m_pImpCharactWidget->EnableSetting(FALSE);
	m_pMainWidget->m_pImpCharactWidget->setObjectName(QString::fromUtf8("QDiffCurr6ICharactWidget"));
	m_pMainWidget->m_pImpCharactWidget->SetAxisName(_T("Ir(A)"),_T("Id(A)"),_T(" "));
	m_pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(_T("A"),_T("A"));
	m_pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(false);
	m_pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowAng(false);

	CCharacteristic* pChar =  GetCurrentCharacter();

	if(!pChar)
	{
		//没有配置文件,则初始化
        stt_Frame_Characteristics()->InitEmptyCharacter(AXIS_TYPE_ID_CARTES);
		pChar = GetCurrentCharacter();
		pChar->InitAfterRead();
		pChar->m_strTestLineMode = CHAR_TESTLINE_MODE_ID_VERT;
	}
	else
	{
		CCharacterArea* pArea = pChar->GetCharacterArea();
		//设置门槛值
		CCharElementLined* pLine = (CCharElementLined*)pArea->GetHead();
		m_oDiffCharCal.m_fIcdqd = CString_To_double(pLine->m_strYb);
		m_oDiffCharCal.m_fKid0 = CalLineK(pLine);

		//设置拐点
		switch(pArea->GetCount())
		{
		case 5:
			pLine = (CCharElementLined*)pArea->GetAt((long)3);
			m_oDiffCharCal.m_fKid3 = CalLineK(pLine);
			m_oDiffCharCal.m_fIp3 = CString_To_double(pLine->m_strXb);
		case 4:
			pLine = (CCharElementLined*)pArea->GetAt((long)2);
			m_oDiffCharCal.m_fKid2 = CalLineK(pLine);
			m_oDiffCharCal.m_fIp2 = CString_To_double(pLine->m_strXb);
			m_pK2_CheckBox->setChecked(true);
			m_pIp2_Edit->setEnabled(true);
			m_pKp2_Edit->setEnabled(true);
		case 3:
			pLine = (CCharElementLined*)pArea->GetAt((long)1);
			m_oDiffCharCal.m_fKid1 = CalLineK(pLine);
			m_oDiffCharCal.m_fIp1 = CString_To_double(pLine->m_strXb);
			break;
		default:
			break;
		}

		m_oDiffCharCal.m_nKneePoints = pArea->GetCount() - 2;

		//设置速断
		pLine = (CCharElementLined*)pArea->GetTail();
		m_oDiffCharCal.m_fIsd = CString_To_double(pLine->m_strYb);
	}

	InitDiffData();
}

void QCharEditWidget_LineDiff::UpdateEditsDisEnable()
{
	if (m_oDiffCharCal.m_nKneePoints>=2)
	{
		m_pIp2_Edit->setEnabled(true);
		m_pKp2_Edit->setEnabled(true);
	} 
	else
	{
		m_pIp2_Edit->setEnabled(false);
		m_pKp2_Edit->setEnabled(false);
	}
}

void QCharEditWidget_LineDiff::UpdateChar(BOOL bUpdateTable,BOOL bCharTypeChanged,BOOL bParasChanged )
{
	long bChanged = m_oDiffCharCal.m_oPoints.GetCount();
	m_oDiffCharCal.m_nSelectSd = 0;
	m_oDiffCharCal.m_fIp1 = m_oDiffCharCal.m_fIcdqd/m_oDiffCharCal.m_fKid1;

	CString strText;
	strText.Format("%.3f", m_oDiffCharCal.m_fIp1);
	m_pIp1_Edit->setText(strText);

	m_oDiffCharCal.Cal();	

	CCharacteristic* pChar = GetCurrentCharacter();

	if (pChar == NULL)
	{
		return;
	}

	pChar->m_bXMin = TRUE;
	pChar->m_bXMax = TRUE;
	pChar->m_bYMin = TRUE;
	pChar->m_bYMax = TRUE;
	pChar->m_fXMin = 0.0f;
	pChar->m_fYMin = 0.0f;
	pChar->m_fXMax = m_oDiffCharCal.m_fXMax;
	pChar->m_fYMax = m_oDiffCharCal.m_fYMax;
	pChar->m_strXMin = _T("0.0");
	pChar->m_strYMin = _T("0.0");
	pChar->m_strXMax.Format(_T("%lf"),pChar->m_fXMax);
	pChar->m_strYMax.Format(_T("%lf"),pChar->m_fYMax);
	CCharacterArea* pArea = pChar->GetCharacterArea();

	if((!bCharTypeChanged) && (bChanged != m_oDiffCharCal.m_oPoints.GetCount()))
	{
		//段数改变
		pArea->DeleteAll();
		CCharElement *pCharElement = pArea->GetCharBisector();

		if (pCharElement != NULL)//20230206 zhouhj  拐点等线段也删除
		{
			pCharElement->DeleteAll();
		}

		POS pos = m_oDiffCharCal.m_oPoints.GetHeadPosition();
		CXDrawData_Point* pLast = NULL;
		CString strFX, strFY;
		long nLineIndex = 0;

		while (pos)
		{
			CXDrawData_Point* pt = (CXDrawData_Point*)m_oDiffCharCal.m_oPoints.GetNext(pos);

			if(pLast)
			{
				CCharElementLined* pLine = new CCharElementLined;
				strFX.Format("%.3f", pLast->m_fX);
				strFY.Format("%.3f", pLast->m_fY);
				pLine->SetBeginPoint(strFX, strFY);
				strFX.Format("%.3f", pt->m_fX);
				strFY.Format("%.3f", pt->m_fY);
				pLine->SetEndPoint(strFX, strFY);
				pArea->AddNewChild(pLine);
				nLineIndex++;
			}

			pLast = pt;
		}

		ShowDatas_Table();
	}
	else
	{
		POS pos = m_oDiffCharCal.m_oPoints.GetHeadPosition();
		CXDrawData_Point* pLast = NULL;
		CString strFX, strFY;
		long nIndex = 0;
		while (pos)
		{
			CXDrawData_Point* pt = (CXDrawData_Point*)m_oDiffCharCal.m_oPoints.GetNext(pos);
			if(pLast)
			{
				CCharElementLined* pLine = (CCharElementLined*)pArea->GetAt((long)nIndex);
				strFX.Format("%.3f", pLast->m_fX);
				strFY.Format("%.3f", pLast->m_fY);
				pLine->SetBeginPoint(strFX, strFY);
				strFX.Format("%.3f", pt->m_fX);
				strFY.Format("%.3f", pt->m_fY);
				pLine->SetEndPoint(strFX, strFY);
				nIndex++;
			}
			pLast = pt;
		}

		if (bUpdateTable)
		{
			ShowDatas_Table();
		}
	}

	emit sig_CharChanged(GetCurrentCharacter(),bParasChanged);	
}

void QCharEditWidget_LineDiff::ShowDatas_Table()
{
	CCharacteristic* pChar = GetCurrentCharacter();

	if (pChar == NULL)
	{
		return;
	}


	CCharacterArea* pArea = pChar->GetCharacterArea();

	if (pArea == NULL)
	{
		return;
	}

	CCharElementLined* pLine1 = (CCharElementLined*)pArea->GetHead();
	CCharElementLined* pLineSd = NULL;
	CCharElementLined* pCurrLine = NULL;

	if (m_oDiffCharCal.m_nSelectSd > 0)
	{
		m_oDiffCharCal.m_nSelectSd = 0;
//		pLineSd = (CCharElementLined*)pArea->GetTail();
	}

	CString strStartCurr, strRatiobraking, strParagraph, strTripping, strHarmBrake;
	xlang_GetLangStrByFile(strStartCurr, "CharLib_StartCurr");
	xlang_GetLangStrByFile(strRatiobraking, "CharLib_Ratiobraking");
	xlang_GetLangStrByFile(strParagraph, "CharLib_Paragraph");
	xlang_GetLangStrByFile(strTripping, "CharLib_Tripping");
	xlang_GetLangStrByFile(strHarmBrake, "State_Harmonicbraking");

	//line本身Name是其类型的名称,不是所需要的段名
	pLine1->m_strName = strStartCurr;
	pLine1->SetTestPoint(m_oDiffCharCal.m_nPointNum[0]);
	pLine1->m_strErrLength.Format(_T("%.03f") ,m_oDiffCharCal.m_fErrorBand[0]);
	POS pos = pArea->GetHeadPosition();
	pArea->GetNext(pos);
	long nIndex = 1;
	CString strAppend;

	while(pos)
	{
		pCurrLine = (CCharElementLined*)pArea->GetNext(pos);

		if(pCurrLine == pLineSd)
		{
			break;
		}

		pCurrLine->m_strName = strRatiobraking;
		strAppend.Format(_T("%ld"), nIndex);
		pCurrLine->m_strName += strAppend;
		//pCurrLine->m_strName.AppendFormat(_T("%ld"),nIndex);
		pCurrLine->m_strName += _T(strParagraph);
		pCurrLine->SetTestPoint(m_oDiffCharCal.m_nPointNum[nIndex]);
		pCurrLine->m_strErrLength.Format(_T("%.03f") ,m_oDiffCharCal.m_fErrorBand[nIndex]);
		nIndex++;
	}

// 	if (m_oDiffCharCal.m_nSelectSd)
// 	{
// 		pLineSd->m_strName = strTripping;
// 		pLineSd->SetTestPoint(m_oDiffCharCal.m_nPointNum[4]);
// 		pLineSd->m_strErrLength.Format(_T("%.03f") ,m_oDiffCharCal.m_fErrorBand[4]);
// 	}

	m_pGridCharLine->ShowDatas(pArea);
}

CCharacteristic* QCharEditWidget_LineDiff::GetCurrentCharacter()
{
	return (CCharacteristic*)stt_Frame_Characteristics()->FindByClassID(CHARCLASSID_CCHARACTERISTIC);
}

void QCharEditWidget_LineDiff::GetTestPointNumErrorBand()
{
	CCharacteristic* pChar = GetCurrentCharacter();

	if (pChar == NULL)
	{
		return;
	}

	CCharacterArea* pArea = pChar->GetCharacterArea();

	if (pArea == NULL)
	{
		return;
	}

	//line本身Name是其类型的名称,不是所需要的段名
	CCharElementLined* pLine1 = (CCharElementLined*)pArea->GetHead();
	CCharElementLined* pLineSd = (CCharElementLined*)pArea->GetTail();
	CCharElementLined* pCurrLine = NULL;
	m_oDiffCharCal.m_nPointNum[0] = *pLine1->GetTestPointsRef();
	m_oDiffCharCal.m_fErrorBand[0] = CString_To_double(pLine1->m_strErrLength);
	POS pos = pArea->GetHeadPosition();
	pArea->GetNext(pos);
	long nIndex = 1;

	while(pos)
	{
		pCurrLine = (CCharElementLined*)pArea->GetNext(pos);

		m_oDiffCharCal.m_nPointNum[nIndex] = *pCurrLine->GetTestPointsRef();
		m_oDiffCharCal.m_fErrorBand[nIndex] = CString_To_double(pCurrLine->m_strErrLength);
		nIndex++;
	}

// 	if (m_oDiffCharCal.m_nSelectSd)
// 	{
// 		m_oDiffCharCal.m_nPointNum[4] = *pLineSd->GetTestPointsRef();
// 		m_oDiffCharCal.m_fErrorBand[4] = CString_To_double(pLineSd->m_strErrLength);
// 	}
}

void QCharEditWidget_LineDiff::on_m_edtSet_Istart_editingFinished()
{
	float fv = SetParaI(m_pIcdqd_Edit, m_oDiffCharCal.m_fIcdqd);
	UpdateChar();
}

void QCharEditWidget_LineDiff::on_m_edtSet_Kstart_editingFinished()
{
	float fv = SetParaK(m_pKcdqd_Edit, m_oDiffCharCal.m_fKid0);
	UpdateChar();
}

void QCharEditWidget_LineDiff::on_m_edtSet_Ip1_editingFinished()
{
	SetParaI(m_pIp1_Edit, m_oDiffCharCal.m_fIp1);

	UpdateChar();
}

void QCharEditWidget_LineDiff::on_m_edtSet_K1_editingFinished()
{
	float fv = SetParaK(m_pKp1_Edit, m_oDiffCharCal.m_fKid1);
	UpdateChar();
}

void QCharEditWidget_LineDiff::on_m_edtSet_Ip2_editingFinished()
{
	float fv = SetParaI(m_pIp2_Edit, m_oDiffCharCal.m_fIp2);
	UpdateChar();
}

void QCharEditWidget_LineDiff::on_m_edtSet_K2_editingFinished()
{
	float fv = SetParaK(m_pKp2_Edit, m_oDiffCharCal.m_fKid2);
	UpdateChar();
}

float QCharEditWidget_LineDiff::SetLimit(float min,float max,float val)
{
	if (val<min)
	{
		val = min;
	}
	else if (val>max)
	{
		val = max;
	}
	return val;
}

float QCharEditWidget_LineDiff::CalLineK(CCharElementLined* pLine)
{
	float fXb, fXe, fYb, fYe;
	fXb = CString_To_double(pLine->m_strXb);
	fXe = CString_To_double(pLine->m_strXe);
	fYb = CString_To_double(pLine->m_strYb);
	fYe = CString_To_double(pLine->m_strYe);
	return (fYe - fYb) / (fXe - fXb);
}

void QCharEditWidget_LineDiff::GroupDatasToChar(CDataGroup *pDatas)
{
	stt_GetDataValueByID(pDatas,CharDiff_ID_IDoor,m_oDiffCharCal.m_fIcdqd);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_IQuickSetting,m_oDiffCharCal.m_fIsd);
	//zhouhj 2023.12.2 线路差动和母线差动中,斜率1固定经过坐标原点,拐点1是通过门槛值和比率1斜率计算出来,固拐点1参数无需保存
//	stt_GetDataValueByID(pDatas,CharDiff_ID_Limp1,m_oDiffCharCal.m_fIp1);
	stt_GetDataValueByID(pDatas,CharDiff_ID_Limp2,m_oDiffCharCal.m_fIp2);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_Limp3,m_oDiffCharCal.m_fIp3);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_StartCurr_Kid,m_oDiffCharCal.m_fKid0);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef_Kid1,m_oDiffCharCal.m_fKid1);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef_Kid2,m_oDiffCharCal.m_fKid2);
//	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef_Kid3,m_oDiffCharCal.m_fKid3);
// 	stt_GetDataValueByID(pDatas,CharDiff_ID_RateHarm,m_oDiffCharCal.m_fHarmCoef);
// 	stt_GetDataValueByID(pDatas,CharDiff_ID_MinAxis,m_oDiffCharCal.m_nMinAxis);
// 	stt_GetDataValueByID(pDatas,CharDiff_ID_Insel,m_oDiffCharCal.m_nInsel);
// 	stt_GetDataValueByID(pDatas,CharDiff_ID_In,m_oDiffCharCal.m_fInSet);

//	stt_GetDataValueByID(pDatas,CharDiff_ID_HarmIndex,m_oDiffCharCal.m_nHarmIndex);

	stt_GetDataValueByID(pDatas,CharDiff_ID_StartCurrPointNum,m_oDiffCharCal.m_nPointNum[0]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef1PointNum,m_oDiffCharCal.m_nPointNum[1]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef2PointNum,m_oDiffCharCal.m_nPointNum[2]);
// 	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef3PointNum,m_oDiffCharCal.m_nPointNum[3]);
// 	stt_GetDataValueByID(pDatas,CharDiff_ID_QuickCurrPointNum,m_oDiffCharCal.m_nPointNum[4]);

	stt_GetDataValueByID(pDatas,CharDiff_ID_StartCurrErrorBand,m_oDiffCharCal.m_fErrorBand[0]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef1ErrorBand,m_oDiffCharCal.m_fErrorBand[1]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef2ErrorBand,m_oDiffCharCal.m_fErrorBand[2]);
// 	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef3ErrorBand,m_oDiffCharCal.m_fErrorBand[3]);
// 	stt_GetDataValueByID(pDatas,CharDiff_ID_QuickCurrErrorBand,m_oDiffCharCal.m_fErrorBand[4]);

	long nStartCurrCheck = 1,nRateCoef1Check = 1,nRateCoef2Check = 1/*,nRateCoef3Check = 1*//*,nQuickCurrCheck = 1*/;
// 	stt_GetDataValueByID(pDatas,CharDiff_ID_StartCurr_Check,nStartCurrCheck);
// 	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef1_Check,nRateCoef1Check);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef2_Check,nRateCoef2Check);
// 	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef3_Check,nRateCoef3Check);
// 	stt_GetDataValueByID(pDatas,CharDiff_ID_QuickCurr_Check,m_oDiffCharCal.m_nSelectSd);

	if (!m_bShowIp2)
	{
		nRateCoef2Check = 0;
	}

	m_oDiffCharCal.m_nKneePoints = nRateCoef1Check + nRateCoef2Check/* + nRateCoef3Check*/;
	m_pK2_CheckBox->setChecked(nRateCoef2Check);
	InitDiffData();
	UpdateEditsDisEnable();
	UpdateChar(TRUE,FALSE,FALSE);
}

void QCharEditWidget_LineDiff::CharToGroupDatas(CDataGroup *pDatas)
{
	GetTestPointNumErrorBand();
	pDatas->SetDataValue(CharDiff_ID_IDoor,m_oDiffCharCal.m_fIcdqd,TRUE);
//	pDatas->SetDataValue(CharDiff_ID_IQuickSetting,m_oDiffCharCal.m_fIsd,TRUE);
	//zhouhj 2023.12.2 线路差动和母线差动中,斜率1固定经过坐标原点,拐点1是通过门槛值和比率1斜率计算出来,固拐点1参数无需保存
//	pDatas->SetDataValue(CharDiff_ID_Limp1,m_oDiffCharCal.m_fIp1,TRUE);
//	pDatas->SetDataValue(CharDiff_ID_Limp3,m_oDiffCharCal.m_fIp3,TRUE);
//	pDatas->SetDataValue(CharDiff_ID_StartCurr_Kid,m_oDiffCharCal.m_fKid0,TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef_Kid1,m_oDiffCharCal.m_fKid1,TRUE);
//	pDatas->SetDataValue(CharDiff_ID_RateCoef_Kid3,m_oDiffCharCal.m_fKid3,TRUE);
//	pDatas->SetDataValue(CharDiff_ID_RateHarm,m_oDiffCharCal.m_fHarmCoef,TRUE);

//	pDatas->SetDataValue(CharDiff_ID_MinAxis,m_oDiffCharCal.m_nMinAxis,TRUE);
// 	pDatas->SetDataValue(CharDiff_ID_Insel,m_oDiffCharCal.m_nInsel,TRUE);
// 	pDatas->SetDataValue(CharDiff_ID_HarmIndex,m_oDiffCharCal.m_nHarmIndex,TRUE);
// 	pDatas->SetDataValue(CharDiff_ID_In,m_oDiffCharCal.m_fInSet,TRUE);

	pDatas->SetDataValue(CharDiff_ID_StartCurrPointNum,m_oDiffCharCal.m_nPointNum[0],TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef1PointNum,m_oDiffCharCal.m_nPointNum[1],TRUE);
// 	pDatas->SetDataValue(CharDiff_ID_RateCoef3PointNum,m_oDiffCharCal.m_nPointNum[3],TRUE);
// 	pDatas->SetDataValue(CharDiff_ID_QuickCurrPointNum,m_oDiffCharCal.m_nPointNum[4],TRUE);

	pDatas->SetDataValue(CharDiff_ID_StartCurrErrorBand,m_oDiffCharCal.m_fErrorBand[0],TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef1ErrorBand,m_oDiffCharCal.m_fErrorBand[1],TRUE);
// 	pDatas->SetDataValue(CharDiff_ID_RateCoef3ErrorBand,m_oDiffCharCal.m_fErrorBand[3],TRUE);
// 	pDatas->SetDataValue(CharDiff_ID_QuickCurrErrorBand,m_oDiffCharCal.m_fErrorBand[4],TRUE);

	long nStartCurrCheck = 1,nRateCoef1Check = 1,nRateCoef2Check = 1,nRateCoef3Check = 1,nQuickCurrCheck = 0;

	if (m_oDiffCharCal.m_nKneePoints == 2)
	{
		nRateCoef3Check = 0;
	}
	else if (m_oDiffCharCal.m_nKneePoints == 1)
	{
		nRateCoef2Check = 0;
		nRateCoef3Check = 0;
	}

	pDatas->SetDataValue(CharDiff_ID_StartCurr_Check,nStartCurrCheck,TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef1_Check,nRateCoef1Check,TRUE);

	if (m_bShowIp2)
	{
		pDatas->SetDataValue(CharDiff_ID_Limp2,m_oDiffCharCal.m_fIp2,TRUE);
		pDatas->SetDataValue(CharDiff_ID_RateCoef_Kid2,m_oDiffCharCal.m_fKid2,TRUE);
		pDatas->SetDataValue(CharDiff_ID_RateCoef2PointNum,m_oDiffCharCal.m_nPointNum[2],TRUE);
		pDatas->SetDataValue(CharDiff_ID_RateCoef2ErrorBand,m_oDiffCharCal.m_fErrorBand[2],TRUE);
		pDatas->SetDataValue(CharDiff_ID_RateCoef2_Check,nRateCoef2Check,TRUE);
	}
// 	pDatas->SetDataValue(CharDiff_ID_RateCoef3_Check,nRateCoef3Check,TRUE);
// 	pDatas->SetDataValue(CharDiff_ID_QuickCurr_Check,nQuickCurrCheck,TRUE);
}

void QCharEditWidget_LineDiff::OnDataSelChanged( QTableWidget *pGridCtrl, int nRow, int nCol )
{
	CCharElement *pCurrSelElement = (CCharElement*)m_pGridCharLine->GetCurrSelData();

	if (pCurrSelElement == NULL)
	{
		return;
	}

	QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();

	if (pMainWidget != NULL)
	{
		pMainWidget->UI_SetActiveElement((CXDrawElement*)pCurrSelElement->m_pDataRef);
	}
}

///////////////////////////////////////////////////////////////变压器差动///////////////////////////////////////////////////////////////////////////////////////
//QCharEditWidget_Diff
QCharEditWidget_Diff::QCharEditWidget_Diff(QWidget *parent)
	: QWidget(parent)
{
	m_pCharEditWidget = this;
	ui.setupUi(this);
	ui.m_lbHarmIndex->setVisible(false);
	ui.m_cbHarmIndex->setVisible(false);
	ui.m_lbHarmCoef->setVisible(false);
	ui.m_editHarmCoef->setVisible(false);

	m_pGridCharLine = new QCharEditGrid_DiffLine(this);
	m_pGridCharLine->InitGrid();
	m_pGridCharLine->AttachDataViewOptrInterface(this);

	ui.m_layoutVert->insertWidget(1, m_pGridCharLine);
	
	m_pMainWidget = (QCharEditMainWidget*)parentWidget();
	
	InitUI();
	InitConnect();
	InitChar();
//	UpdateChar(FALSE,FALSE,FALSE); //2023.4.23 zhouhj 在获取特性曲线后,再刷新相关界面
	SetDiffFont();
}

QCharEditWidget_Diff::~QCharEditWidget_Diff()
{

}

void QCharEditWidget_Diff::InitUI()
{
	ui.m_cbSettingMinAxis->ShowDataType(CTestDataTypeMngrConstGlobal::FindTestDataType(_T("DifferMarkType")));
	ui.m_cbInSel->ShowDataType(CTestDataTypeMngrConstGlobal::FindTestDataType(_T("BasicCurrSelect")));
	ui.m_cbHarmIndex->ShowDataType(CTestDataTypeMngrConstGlobal::FindTestDataType(_T("DiffHarmIndex")));
	initMaxPositiveEdit(ui.m_edtSet_Istart);
	initMaxPositiveEdit(ui.m_edtSet_Ip1);
	initMaxPositiveEdit(ui.m_edtSet_Ip2);
	initMaxPositiveEdit(ui.m_edtSet_Ip3);
	initMaxPositiveEdit(ui.m_edtSet_Isd);
	initMaxPositiveEdit(ui.m_edtSet_Kstart);
	initMaxPositiveEdit(ui.m_edtSet_K1);
	initMaxPositiveEdit(ui.m_edtSet_K2);
	initMaxPositiveEdit(ui.m_edtSet_K3);
	initMaxPositiveEdit(ui.m_editSet_IdValue);
	initMaxPositiveEdit(ui.m_editInSet);
	initMaxPositiveEdit(ui.m_editHarmCoef);
	ui.m_editSet_IdValue->setText("1.5");

	ui.m_chkStart->setEnabled(false);
	ui.m_chkLine1->setEnabled(false);
//	ui.m_chkLineSd->setEnabled(false);
	ui.m_chkStart->setChecked(true);
	ui.m_chkLine1->setChecked(true);
	ui.m_chkLineSd->setChecked(true);
	ui.m_edtSet_Ip2->setEnabled(false);
	ui.m_edtSet_K2->setEnabled(false);
	ui.m_edtSet_Ip3->setEnabled(false);
	ui.m_edtSet_K3->setEnabled(false);
}
void QCharEditWidget_Diff::SetDiffFont()
{
	m_pGridCharLine->setFont(*g_pSttGlobalFont);
	m_pGridCharLine->horizontalHeader()->setFont(*g_pSttGlobalFont);

	ui.m_edtSet_Istart->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_Kstart->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleStart->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleCurr->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleK->setFont(*g_pSttGlobalFont);
	ui.m_chkLine1->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_Ip1->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleLine1->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_K1->setFont(*g_pSttGlobalFont);
	ui.m_chkStart->setFont(*g_pSttGlobalFont);
	ui.m_chkLine3->setFont(*g_pSttGlobalFont);
	ui.m_chkLine2->setFont(*g_pSttGlobalFont);
	ui.m_chkLineSd->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleLine2->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleLine3->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleLineSd->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_Ip2->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_Ip3->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_Isd->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_K2->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_K3->setFont(*g_pSttGlobalFont);
	ui.m_btnUserClear->setFont(*g_pSttGlobalFont);
	ui.m_btnUserAdd->setFont(*g_pSttGlobalFont);
	ui.m_lbIdValue->setFont(*g_pSttGlobalFont);
	ui.m_editSet_IdValue->setFont(*g_pSttGlobalFont);
	ui.m_radioNormal->setFont(*g_pSttGlobalFont);
	ui.m_radioHarm->setFont(*g_pSttGlobalFont);

	ui.m_lbSettingMinAxis->setFont(*g_pSttGlobalFont);
	ui.m_cbSettingMinAxis->setFont(*g_pSttGlobalFont);
	ui.m_lbInSel->setFont(*g_pSttGlobalFont);
	ui.m_cbInSel->setFont(*g_pSttGlobalFont);
	ui.m_lbInSet->setFont(*g_pSttGlobalFont);
	ui.m_editInSet->setFont(*g_pSttGlobalFont);

	ui.m_lbName->setFont(*g_pSttGlobalFont);
	ui.m_lbSetting->setFont(*g_pSttGlobalFont);

	ui.m_lbHarmIndex->setFont(*g_pSttGlobalFont);
	ui.m_cbHarmIndex->setFont(*g_pSttGlobalFont);
	ui.m_lbHarmCoef->setFont(*g_pSttGlobalFont);
	ui.m_editHarmCoef->setFont(*g_pSttGlobalFont);
}

void QCharEditWidget_Diff::OnLeftButtonDown()
{
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	if(IsNotHarm())
	{
		m_pMainWidget->m_pImpCharactWidget->CalPointVertHorzLine(0, CHAR_TESTLINE_MODE_ID_VERT);
	}
	else
	{
		m_pMainWidget->m_pImpCharactWidget->CalPointVertHorzLine(0, CHAR_TESTLINE_MODE_ID_HORZ);
	}
	UpdateEdit_IrValueUserPoint();
}

void QCharEditWidget_Diff::InitConnect()
{
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	connect(this, SIGNAL(sig_CharChanged(CExBaseObject *,int)), m_pMainWidget,SLOT(slot_UpdateDrawCharacters(CExBaseObject *,int)));
	connect(m_pGridCharLine, SIGNAL(sig_CharChanged(CExBaseObject *)), m_pMainWidget,SLOT(slot_UpdateDrawCharacters(CExBaseObject *)));

	connect(m_pGridCharLine, SIGNAL(sig_TestPointsErrorBandChanged()), this,SLOT(slot_TestPointsErrorBandChanged()));
	connect(m_pGridCharLine, SIGNAL(sig_DiffCharChanged()), this,SLOT(slot_DiffCharChanged()));
	connect(ui.m_btnUserAdd, SIGNAL(clicked(bool)), this,SLOT(slot_btnUserAdd(bool)));
	connect(ui.m_btnUserClear, SIGNAL(clicked(bool)), this,SLOT(slot_btnUserClear(bool)));
	connect(ui.m_editSet_IdValue,  SIGNAL(editingFinished ()), this, SLOT(slot_IdValue_editingFinished()));

	connect(ui.m_radioNormal, SIGNAL(clicked()), this, SLOT(slot_radioNormal_Clicked()));//谐波制动
	connect(ui.m_radioHarm, SIGNAL(clicked()), this, SLOT(slot_radioHarm_Clicked()));//比率差动

	connect(ui.m_cbSettingMinAxis,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbSettingMinAxisIndexChanged(int)));
	connect(ui.m_cbInSel,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbInSeIndexChanged(int)));
	connect(ui.m_cbHarmIndex,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbHarmIndexChanged(int)));
	connect(ui.m_editInSet, SIGNAL(editingFinished()), this, SLOT(slot_InSet_editingFinished()));
	connect(ui.m_editHarmCoef, SIGNAL(editingFinished()), this, SLOT(slot_HarmCoef_editingFinished()));

#ifdef _PSX_QT_LINUX_

	connect(ui.m_edtSet_Istart,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_Ip1,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_Ip2,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_Ip3,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_Isd,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_Kstart,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_K1,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_K2,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_K3,SIGNAL(clicked()),this,SLOT(on_m_onlineEdit_Changed()));

 #endif

}


void QCharEditWidget_Diff::slot_CmbSettingMinAxisIndexChanged(int nIndex)//定值整定方式
{
	m_oDiffCharCal.m_nMinAxis = ui.m_cbSettingMinAxis->GetSelectIndex2();
	UpdateEditsDisEnable();
	InitUI_Unit();
	emit sig_CharChanged(GetCurrentCharacter(),TRUE);	
	m_pMainWidget->m_bCharChanged = TRUE;
}

void QCharEditWidget_Diff::slot_CmbInSeIndexChanged(int nIndex)//基准电流选择
{
	m_oDiffCharCal.m_nInsel = ui.m_cbInSel->GetSelectIndex2();
	UpdateEditsDisEnable();
	m_pMainWidget->m_bCharChanged = TRUE;
}

void QCharEditWidget_Diff::slot_CmbHarmIndexChanged(int nIndex)//谐波次数
{
	m_oDiffCharCal.m_nHarmIndex = ui.m_cbHarmIndex->GetSelectIndex2();
	m_pMainWidget->m_bCharChanged = TRUE;
}

void QCharEditWidget_Diff::slot_InSet_editingFinished()
{
	SetParaI(ui.m_editInSet, m_oDiffCharCal.m_fInSet);
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	m_pMainWidget->m_bCharChanged = TRUE;
} 

void QCharEditWidget_Diff::slot_HarmCoef_editingFinished()
{
	SetParaK(ui.m_editHarmCoef, m_oDiffCharCal.m_fHarmCoef);
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	m_pMainWidget->m_bCharChanged = TRUE;
}

void QCharEditWidget_Diff::EnableEdit(long nIndex)
{
// 	ui.m_edtSet_Ip2->setEnabled(false);
// 	ui.m_edtSet_K2->setEnabled(false);
// 	ui.m_edtSet_Ip3->setEnabled(false);
// 	ui.m_edtSet_K3->setEnabled(false);

	switch(nIndex)
	{
	case CharDiff_RateCoef2_Index:
		ui.m_edtSet_Ip2->setEnabled(true);
		ui.m_edtSet_K2->setEnabled(true);

		if(!ui.m_chkLine2->isChecked())
		{
			ui.m_chkLine2->setChecked(true);
		}

		m_oDiffCharCal.m_nKneePoints = nIndex;
		break;
	case CharDiff_RateCoef3_Index:

		ui.m_edtSet_Ip2->setEnabled(true);
		ui.m_edtSet_K2->setEnabled(true);

		if(!ui.m_chkLine2->isChecked())
		{
			ui.m_chkLine2->setChecked(true);
		}

		ui.m_edtSet_Ip3->setEnabled(true);
		ui.m_edtSet_K3->setEnabled(true);

		if(!ui.m_chkLine3->isChecked())
		{
			ui.m_chkLine3->setChecked(true);
		}

		m_oDiffCharCal.m_nKneePoints = nIndex;
		break;
	case CharDiff_QuickCurr_Index:
		ui.m_edtSet_Isd->setEnabled(true);
		m_oDiffCharCal.m_nSelectSd = 1;
		break;

	default:
		break;
	}

	UpdateChar();
}

void QCharEditWidget_Diff::DisableEdit(long nIndex)
{
	switch(nIndex)
	{
	case CharDiff_RateCoef2_Index:
		ui.m_edtSet_Ip2->setEnabled(false);
		ui.m_edtSet_K2->setEnabled(false);

		if(ui.m_chkLine2->isChecked())
		{
			ui.m_chkLine2->setChecked(false);
		}

		ui.m_edtSet_Ip3->setEnabled(false);
		ui.m_edtSet_K3->setEnabled(false);

		if(ui.m_chkLine3->isChecked())
		{
			ui.m_chkLine3->setChecked(false);
		}

		m_oDiffCharCal.m_nKneePoints = nIndex - 1;
		break;
	case CharDiff_RateCoef3_Index:

		ui.m_edtSet_Ip3->setEnabled(false);
		ui.m_edtSet_K3->setEnabled(false);

		if(ui.m_chkLine3->isChecked())
		{
			ui.m_chkLine3->setChecked(false);
		}

		m_oDiffCharCal.m_nKneePoints = nIndex - 1;
		break;
	case CharDiff_QuickCurr_Index:
		ui.m_edtSet_Isd->setEnabled(false);
		m_oDiffCharCal.m_nSelectSd = 0;
		break;

	default:
		break;
	}

	UpdateChar();
}

void QCharEditWidget_Diff::on_m_onlineEdit_Changed()
{
 	QSttLineEdit* pEditLine = qobject_cast<QSttLineEdit*>(sender());

	if (pEditLine->text().isEmpty())
	{
		pEditLine->setText("0.0");
	}

	QString str = pEditLine->text();
	GetWidgetBoard_DigitData(4,str,pEditLine,this);

	if (str.right(1).contains("."))
	{
		str.append("000");
	}

	m_pMainWidget->m_bCharChanged = TRUE;
// 	pEditLine->setText(str);
// 	pEditLine->SetEditFinished();
}

void QCharEditWidget_Diff::slot_TestPointsErrorBandChanged()
{
	GetTestPointNumErrorBand();
	emit sig_CharChanged(GetCurrentCharacter(),TRUE);	
}

void QCharEditWidget_Diff::slot_DiffCharChanged()
{
	emit sig_CharChanged(GetCurrentCharacter(),TRUE);	
}

void QCharEditWidget_Diff::slot_IdValue_editingFinished()
{
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	CString strIdValue = ui.m_editSet_IdValue->text();
	if(IsNotHarm())
	{
		m_pMainWidget->m_pImpCharactWidget->UpdateVertLine(CString_To_double(strIdValue));
	}
	else
	{
		m_pMainWidget->m_pImpCharactWidget->UpdateHorzLine(CString_To_double(strIdValue));
	}
}

void QCharEditWidget_Diff::UpdateEdit_IrValueUserPoint()
{
    CXDrawLine* pLine = stt_Frame_GetCharLibLeftButtonLine();
	CXDrawPoint* pPoint = (CXDrawPoint*)pLine->GetHead();

	if(!pPoint)
	{
		return;
	}

	CString strValue;
	if(IsNotHarm())
	{
		strValue.Format(_T("%.03f"),pPoint->m_fX);
	}
	else
	{
		strValue.Format(_T("%.03f"),pPoint->m_fY);
	}
	disconnect(ui.m_editSet_IdValue,  SIGNAL(editingFinished ()), this, SLOT(slot_IdValue_editingFinished()));
	ui.m_editSet_IdValue->setText(strValue);
	connect(ui.m_editSet_IdValue,  SIGNAL(editingFinished ()), this, SLOT(slot_IdValue_editingFinished()));
}

void QCharEditWidget_Diff::slot_btnUserAdd(bool bState)
{
    CXDrawLine* pLine = stt_Frame_GetCharLibLeftButtonLine();
	CXDrawPoint* pPoint = (CXDrawPoint*)pLine->GetHead();
	if(!pPoint)
	{
		return;
	}

 	CCharacteristic* pChar = GetCurrentCharacter();

	if (pChar == NULL)
	{
		return;
	}

 	CCharacterArea* pArea = pChar->GetCharacterArea();
	CCharElementLined* pCharLine = NULL;
	POS pos = pArea->GetHeadPosition();

	if(IsNotHarm())
	{
		long nIndex = 0;
		while (pos)
		{
			pCharLine = (CCharElementLined*)pArea->GetNext(pos);
			double dXb = 0, dYb = 0, dXe = 0, dYe = 0;
			pCharLine->GetLine(dXb, dYb, dXe, dYe);
			if(dXb < pPoint->m_fX && pPoint->m_fX < dXe)
			{
				break;
			}
			nIndex++;
		}

		CCharTestLine* pTestLine = new CCharTestLine();
		pTestLine->m_strType = CHAR_TEST_LINE_TYPE_USER;
 		pTestLine->m_nTestLineID = char_GetTestLineID(pCharLine, nIndex);
		pTestLine->m_fPos = pPoint->m_fX;
		pTestLine->m_fXset = pPoint->m_fX;
		pTestLine->m_fYset = pPoint->m_fY;
		pTestLine->m_fXb = pPoint->m_fX;
		pTestLine->m_fXe = pPoint->m_fX;
		pTestLine->m_fYb = pPoint->m_fY + pCharLine->GetErrorLength();
		pTestLine->m_fYe = pPoint->m_fY - pCharLine->GetErrorLength();
		pCharLine->AddNewChild(pTestLine);
		pCharLine->SetUserTestPoint(pCharLine->GetUserTestPoints() + 1);
	}
	else
	{
		pCharLine = (CCharElementLined*)pArea->GetAt(1);
		double dXb = 0, dYb = 0, dXe = 0, dYe = 0;
		pCharLine->GetLine(dXb, dYb, dXe, dYe);

		CCharTestLine* pTestLine = new CCharTestLine();
		pTestLine->m_strType = CHAR_TEST_LINE_TYPE_USER;
		pTestLine->m_nTestLineID = char_GetTestLineID(pCharLine, pCharLine->GetUserTestPoints());
		pTestLine->m_fPos = pPoint->m_fY;
		pTestLine->m_fXset = pPoint->m_fX;
		pTestLine->m_fYset = pPoint->m_fY;
		pTestLine->m_fXb = pPoint->m_fX + pCharLine->GetErrorLength();
		pTestLine->m_fXe = pPoint->m_fX - pCharLine->GetErrorLength();
		pTestLine->m_fYb = pPoint->m_fY;
		pTestLine->m_fYe = pPoint->m_fY;
		pCharLine->AddNewChild(pTestLine);
		pCharLine->SetUserTestPoint(pCharLine->GetUserTestPoints() + 1);
	}

	UpdateChar(TRUE);
}

void QCharEditWidget_Diff::slot_btnUserClear(bool bState)
{
	CCharacteristic* pChar = GetCurrentCharacter();

	if (pChar == NULL)
	{
		return;
	}

	CCharacterArea* pArea = pChar->GetCharacterArea();
	CCharElementLined* pCharLine = NULL;
	POS pos = pArea->GetHeadPosition();
	long nIndex = 0;
	while (pos)
	{
		pCharLine = (CCharElementLined*)pArea->GetNext(pos);
		for (int i = pCharLine->GetCount() - 1; i >= 0; i-- )
		{
			CCharTestLine* pTestLine = (CCharTestLine*)pCharLine->GetAt(i);
			if(pTestLine->m_strType == CHAR_TEST_LINE_TYPE_USER)
			{
				pCharLine->DeleteAt(i);
			}
		}
		pCharLine->SetUserTestPoint(0);
	}
	UpdateChar(TRUE);
}

void QCharEditWidget_Diff::slot_radioNormal_Clicked()//比率差动
{
	ui.m_lblTitleLine1->setVisible(true);
	ui.m_edtSet_Ip1->setVisible(true);

	ui.m_lbHarmIndex->setVisible(false);
	ui.m_cbHarmIndex->setVisible(false);
	ui.m_lbHarmCoef->setVisible(false);
	ui.m_editHarmCoef->setVisible(false);

//  	CString strText = "拐点1";
//  	ui.m_lblTitleLine1->setText(strText);
	ui.m_lbName->setVisible(true);
	ui.m_chkStart->setVisible(true);
	ui.m_chkLine1->setVisible(true);
	ui.m_chkLineSd->setVisible(true);

	ui.m_lblTitleK->setVisible(true);
	ui.m_edtSet_Kstart->setVisible(true);
	ui.m_edtSet_K1->setVisible(true);
//	ui.m_lblTitleLine1->setVisible(true);
	ui.m_edtSet_Ip1->setText(QString::number(m_oDiffCharCal.m_fIp1));

	ui.m_chkLine2->setVisible(true);
	ui.m_edtSet_Ip2->setVisible(true);
	ui.m_edtSet_K2->setVisible(true);
	ui.m_lblTitleLine2->setVisible(true);

	ui.m_chkLine3->setVisible(true);
	ui.m_edtSet_Ip3->setVisible(true);
	ui.m_edtSet_K3->setVisible(true);
	ui.m_lblTitleLine3->setVisible(true);

	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	m_pMainWidget->UpdateAxisDesc(_T("Ir(A)"),_T("Id(A)"),_T(" "),_T("A"),_T("A"));
	OnLeftButtonDown();
	UpdateChar(TRUE, TRUE);
}

void QCharEditWidget_Diff::slot_radioHarm_Clicked()//谐波制动
{
	ui.m_lblTitleLine1->setVisible(false);
	ui.m_edtSet_Ip1->setVisible(false);

	ui.m_lbHarmIndex->setVisible(true);
	ui.m_cbHarmIndex->setVisible(true);
	ui.m_lbHarmCoef->setVisible(true);
	ui.m_editHarmCoef->setVisible(true);

// 	CString strText = "谐波制动系数";
// 	ui.m_lblTitleLine1->setText(strText);
	ui.m_lbName->setVisible(false);
	ui.m_chkStart->setVisible(false);
	ui.m_chkLine1->setVisible(false);
	ui.m_chkLineSd->setVisible(false);
	ui.m_lblTitleK->setVisible(false);
	ui.m_edtSet_Kstart->setVisible(false);
	ui.m_edtSet_K1->setVisible(false);
//	ui.m_lblTitleLine1->setVisible(false);
//	ui.m_edtSet_Ip1->setText(QString::number(m_oDiffCharCal.m_fHarmCoef));

	ui.m_chkLine2->setVisible(false);
	ui.m_edtSet_Ip2->setVisible(false);
	ui.m_edtSet_K2->setVisible(false);
	ui.m_lblTitleLine2->setVisible(false);

	ui.m_chkLine3->setVisible(false);
	ui.m_edtSet_Ip3->setVisible(false);
	ui.m_edtSet_K3->setVisible(false);
	ui.m_lblTitleLine3->setVisible(false);

	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	m_pMainWidget->UpdateAxisDesc(_T("(%)"),_T("Id(A)"),_T(" "),_T("%"),_T("A"));
	OnLeftButtonDown();

	UpdateChar(TRUE, TRUE);
}

void QCharEditWidget_Diff::on_m_chkStart_clicked()
{
	if(!ui.m_chkStart->isChecked())
	{
		ui.m_chkStart->setChecked(true);
	}
}

void QCharEditWidget_Diff::on_m_chkLine1_clicked()
{
	if(!ui.m_chkLine1->isChecked())
	{
		ui.m_chkLine1->setChecked(true);
	}
}

void QCharEditWidget_Diff::on_m_chkLine2_clicked()
{
	if(ui.m_chkLine2->isChecked())
	{
		EnableEdit(CharDiff_RateCoef2_Index);
	}
	else
	{
		DisableEdit(CharDiff_RateCoef2_Index);
	}
}

void QCharEditWidget_Diff::on_m_chkLine3_clicked()
{
	if(ui.m_chkLine3->isChecked())
	{
		EnableEdit(CharDiff_RateCoef3_Index);
	}
	else
	{
		DisableEdit(CharDiff_RateCoef3_Index);
	}
}

void QCharEditWidget_Diff::on_m_chkLineSd_clicked()
{
	if(ui.m_chkLineSd->isChecked())
	{
		EnableEdit(CharDiff_QuickCurr_Index);
//		ui.m_chkLineSd->setChecked(true);
	}
	else
	{
		DisableEdit(CharDiff_QuickCurr_Index);
	}
}

float QCharEditWidget_Diff::SetParaI(QLineEdit* pEdit, float& fv)
{
	if (pEdit->text().isEmpty())
	{
		pEdit->setText("0.000");
	}

	QString str = pEdit->text();
	if (str.right(1).contains("."))
	{
		str.append(000);
	}

	fv = str.toFloat();
	fv = SetLimit(0,999.999,fv);
	pEdit->setText(QString::number(fv,'f',3));
	return fv;
}

float QCharEditWidget_Diff::SetParaK(QLineEdit* pEdit, float& fv)
{
	if (pEdit->text().isEmpty())
	{
		pEdit->setText("0.000");
	}

	QString str = pEdit->text();
	if (str.right(1).contains("."))
	{
		str.append(000);
	}

	fv = str.toFloat();
	fv = SetLimit(0,999.999,fv);
	pEdit->setText(QString::number(fv,'f',3));
	return fv;
}

void QCharEditWidget_Diff::InitDiffData()
{
	disconnect(ui.m_cbSettingMinAxis,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbSettingMinAxisIndexChanged(int)));
	disconnect(ui.m_cbInSel,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbInSeIndexChanged(int)));
	disconnect(ui.m_cbHarmIndex,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbHarmIndexChanged(int)));

	ui.m_cbSettingMinAxis->SetSelByIndex(m_oDiffCharCal.m_nMinAxis);
	ui.m_cbInSel->SetSelByIndex(m_oDiffCharCal.m_nInsel);
	ui.m_cbHarmIndex->SetSelByIndex(m_oDiffCharCal.m_nHarmIndex);

	CString strText;

	strText.Format("%.3f", m_oDiffCharCal.m_fInSet);
	ui.m_editInSet->setText(strText);

	strText.Format("%.3f", m_oDiffCharCal.m_fHarmCoef);
	ui.m_editHarmCoef->setText(strText);

	strText.Format("%.3f", m_oDiffCharCal.m_fIcdqd);
	ui.m_edtSet_Istart->setText(strText);
	strText.Format("%.3f", m_oDiffCharCal.m_fIsd);
	ui.m_edtSet_Isd->setText(strText);	

	strText.Format("%.3f", m_oDiffCharCal.m_fIp2);
	ui.m_edtSet_Ip2->setText(strText);
	strText.Format("%.3f", m_oDiffCharCal.m_fIp3);
	ui.m_edtSet_Ip3->setText(strText);

	strText.Format("%.3f", m_oDiffCharCal.m_fKid0);
	ui.m_edtSet_Kstart->setText(strText);
	strText.Format("%.3f", m_oDiffCharCal.m_fKid1);
	ui.m_edtSet_K1->setText(strText);
	strText.Format("%.3f", m_oDiffCharCal.m_fKid2);
	ui.m_edtSet_K2->setText(strText);
	strText.Format("%.3f", m_oDiffCharCal.m_fKid3);
	ui.m_edtSet_K3->setText(strText);

	strText.Format("%.3f", m_oDiffCharCal.m_fIp1);
	ui.m_edtSet_Ip1->setText(strText);


	InitUI_Unit();

	connect(ui.m_cbSettingMinAxis,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbSettingMinAxisIndexChanged(int)));
	connect(ui.m_cbInSel,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbInSeIndexChanged(int)));
	connect(ui.m_cbHarmIndex,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbHarmIndexChanged(int)));
}

void QCharEditWidget_Diff::InitUI_Unit()
{
	CString strText,strText_IrAxis,strText_IdAxis,strCustomText;

	if(IsNotHarm())
	{
		if (m_oDiffCharCal.m_nMinAxis)
		{
			strText = /*_T("电流(Ie)")*/g_sLangTxt_State_Iecurrent;
			strText_IrAxis = _T("Ir(Ie)");
			strText_IdAxis = _T("Id(Ie)");
			strCustomText = /*_T("制动电流(Ie)")*/g_sLangTxt_Native_Iecurrent;
		} 
		else
		{
			strText = /*_T("电流(A)")*/g_sLangTxt_State_Acurrent;
			strText_IrAxis = _T("Ir(A)");
			strText_IdAxis = _T("Id(A)");
			strCustomText = /*_T("制动电流(A)")*/g_sLangTxt_Native_Acurrent;
		}

		ui.m_lblTitleCurr->setText(strText);
		ui.m_lbIdValue->setText(strCustomText);
	}
	else
	{
		strText_IrAxis = _T("%");

		if (m_oDiffCharCal.m_nMinAxis)
		{
			strText = /*_T("电流(Ie)")*/g_sLangTxt_State_Iecurrent;

			strText_IdAxis = _T("Id(Ie)");
		} 
		else
		{
			strText = /*_T("电流(A)")*/g_sLangTxt_State_Acurrent;
			strText_IdAxis = _T("Id(A)");
		}

		ui.m_lblTitleCurr->setText(strText);
	}

	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();

	if (m_pMainWidget != NULL)
	{
		m_pMainWidget->m_pImpCharactWidget->SetAxisName(strText_IrAxis,strText_IdAxis,_T(" "));
	}
}

void QCharEditWidget_Diff::InitChar()
{
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	m_pMainWidget->UpdateCharAxisType(AXIS_TYPE_ID_CARTES,FALSE);
	m_pMainWidget->m_pImpCharactWidget->EnableSetting(FALSE);
	m_pMainWidget->m_pImpCharactWidget->setObjectName(QString::fromUtf8("QDiffCurr6ICharactWidget"));
	m_pMainWidget->m_pImpCharactWidget->SetAxisName(_T("Ir(A)"),_T("Id(A)"),_T(" "));
	m_pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(_T("A"),_T("A"));
	m_pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(false);
	m_pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowAng(false);

	CCharacteristic* pChar =  GetCurrentCharacter();

	if(!pChar)
	{
		//没有配置文件,则初始化
        stt_Frame_Characteristics()->InitEmptyCharacter(AXIS_TYPE_ID_CARTES);
		pChar = GetCurrentCharacter();
		pChar->InitAfterRead();
		pChar->m_strTestLineMode = CHAR_TESTLINE_MODE_ID_VERT;
	}
	else
	{
		CCharacterArea* pArea = pChar->GetCharacterArea();
		//设置门槛值
		CCharElementLined* pLine = (CCharElementLined*)pArea->GetHead();
		m_oDiffCharCal.m_fIcdqd = CString_To_double(pLine->m_strYb);
		m_oDiffCharCal.m_fKid0 = CalLineK(pLine);

		//设置拐点
		switch(pArea->GetCount())
		{
		case 5:
			pLine = (CCharElementLined*)pArea->GetAt((long)3);
			m_oDiffCharCal.m_fKid3 = CalLineK(pLine);
			m_oDiffCharCal.m_fIp3 = CString_To_double(pLine->m_strXb);
			ui.m_chkLine3->setChecked(true);
			ui.m_edtSet_Ip3->setEnabled(true);
			ui.m_edtSet_K3->setEnabled(true);
		case 4:
			pLine = (CCharElementLined*)pArea->GetAt((long)2);
			m_oDiffCharCal.m_fKid2 = CalLineK(pLine);
			m_oDiffCharCal.m_fIp2 = CString_To_double(pLine->m_strXb);
			ui.m_chkLine2->setChecked(true);
			ui.m_edtSet_Ip2->setEnabled(true);
			ui.m_edtSet_K2->setEnabled(true);
		case 3:
			pLine = (CCharElementLined*)pArea->GetAt((long)1);
			m_oDiffCharCal.m_fKid1 = CalLineK(pLine);
			m_oDiffCharCal.m_fIp1 = CString_To_double(pLine->m_strXb);
			break;
		default:
			break;
		}

		m_oDiffCharCal.m_nKneePoints = pArea->GetCount() - 2;

		//设置速断
		pLine = (CCharElementLined*)pArea->GetTail();
		m_oDiffCharCal.m_fIsd = CString_To_double(pLine->m_strYb);
	}

	InitDiffData();
}

void QCharEditWidget_Diff::UpdateEditsDisEnable()
{
	switch(m_oDiffCharCal.m_nKneePoints)
	{
	case 3:
		ui.m_edtSet_Ip2->setEnabled(true);
		ui.m_edtSet_K2->setEnabled(true);
		ui.m_edtSet_Ip3->setEnabled(true);
		ui.m_edtSet_K3->setEnabled(true);
		break;
	case 2:
		ui.m_edtSet_Ip2->setEnabled(true);
		ui.m_edtSet_K2->setEnabled(true);
		ui.m_edtSet_Ip3->setEnabled(false);
		ui.m_edtSet_K3->setEnabled(false);
		break;
	case 1:
		ui.m_edtSet_Ip2->setEnabled(false);
		ui.m_edtSet_K2->setEnabled(false);
		ui.m_edtSet_Ip3->setEnabled(false);
		ui.m_edtSet_K3->setEnabled(false);
		break;
	default:
		ui.m_edtSet_Ip2->setEnabled(false);
		ui.m_edtSet_K2->setEnabled(false);
		ui.m_edtSet_Ip3->setEnabled(false);
		ui.m_edtSet_K3->setEnabled(false);
		break;
	}

	if (m_oDiffCharCal.m_nMinAxis == 0)
	{
		ui.m_cbInSel->setEnabled(false);
		ui.m_editInSet->setEnabled(false);
	}
	else
	{
		ui.m_cbInSel->setEnabled(true);

		if (m_oDiffCharCal.m_nInsel == 1)
		{
			ui.m_editInSet->setEnabled(true);
		} 
		else
		{
			ui.m_editInSet->setEnabled(false);
		}
	}
}

void QCharEditWidget_Diff::UpdateChar(BOOL bUpdateTable,BOOL bCharTypeChanged,BOOL bParasChanged)
{
	//yzj 2023/11/3
	//bChanged判断不准确,初始2段以上的特性图都会存在这个问题
	//切换和添加新的测试功能都会保留之前的点数,而新建的Area没有与其匹配的段数
	//long bChanged = m_oDiffCharCal.m_oPoints.GetCount();
	if(IsNotHarm())
	{
		m_oDiffCharCal.Cal();		
	}
	else
	{
		m_oDiffCharCal.CalHarm();
	}
	
	CCharacteristic* pChar = GetCurrentCharacter();

	if (pChar == NULL)
	{
		return;
	}

	pChar->m_bXMin = TRUE;
	pChar->m_bXMax = TRUE;
	pChar->m_bYMin = TRUE;
	pChar->m_bYMax = TRUE;
	pChar->m_fXMin = 0.0f;
	pChar->m_fYMin = 0.0f;
	pChar->m_fXMax = m_oDiffCharCal.m_fXMax;
	pChar->m_fYMax = m_oDiffCharCal.m_fYMax;
	pChar->m_strXMin = _T("0.0");
	pChar->m_strYMin = _T("0.0");
	pChar->m_strXMax.Format(_T("%lf"),pChar->m_fXMax);
	pChar->m_strYMax.Format(_T("%lf"),pChar->m_fYMax);
	CCharacterArea* pArea = pChar->GetCharacterArea();

	long bChanged = pArea->GetCount() + 1;//线段+1等于点数
	if((!bCharTypeChanged) && (bChanged != m_oDiffCharCal.m_oPoints.GetCount()))
	{
		//段数改变
		pArea->DeleteAll();
		CCharElement *pCharElement = pArea->GetCharBisector();

		if (pCharElement != NULL)//20230206 zhouhj  拐点等线段也删除
		{
			pCharElement->DeleteAll();
		}

		POS pos = m_oDiffCharCal.m_oPoints.GetHeadPosition();
		CXDrawData_Point* pLast = NULL;
		CString strFX, strFY;
		long nLineIndex = 0;

		while (pos)
		{
			CXDrawData_Point* pt = (CXDrawData_Point*)m_oDiffCharCal.m_oPoints.GetNext(pos);

			if(pLast)
			{
				CCharElementLined* pLine = new CCharElementLined;
				strFX.Format("%.3f", pLast->m_fX);
				strFY.Format("%.3f", pLast->m_fY);
				pLine->SetBeginPoint(strFX, strFY);
				strFX.Format("%.3f", pt->m_fX);
				strFY.Format("%.3f", pt->m_fY);
				pLine->SetEndPoint(strFX, strFY);
				pArea->AddNewChild(pLine);
				nLineIndex++;
			}

			pLast = pt;
		}

		ShowDatas_Table();
	}
	else
	{
		POS pos = m_oDiffCharCal.m_oPoints.GetHeadPosition();
		CXDrawData_Point* pLast = NULL;
		CString strFX, strFY;
		long nIndex = 0;
		while (pos)
		{
			CXDrawData_Point* pt = (CXDrawData_Point*)m_oDiffCharCal.m_oPoints.GetNext(pos);
			if(pLast)
			{
				CCharElementLined* pLine = (CCharElementLined*)pArea->GetAt((long)nIndex);
				strFX.Format("%.3f", pLast->m_fX);
				strFY.Format("%.3f", pLast->m_fY);
				pLine->SetBeginPoint(strFX, strFY);
				strFX.Format("%.3f", pt->m_fX);
				strFY.Format("%.3f", pt->m_fY);
				pLine->SetEndPoint(strFX, strFY);
				nIndex++;
			}
			pLast = pt;
		}

		if (bUpdateTable)
		{
			ShowDatas_Table();
		}
	}

	emit sig_CharChanged(GetCurrentCharacter(),bParasChanged);	
}

void QCharEditWidget_Diff::ShowDatas_Table()
{
	CCharacteristic* pChar = GetCurrentCharacter();

	if (pChar == NULL)
	{
		return;
	}


	CCharacterArea* pArea = pChar->GetCharacterArea();

	if (pArea == NULL)
	{
		return;
	}

	CCharElementLined* pLine1 = (CCharElementLined*)pArea->GetHead();
	CCharElementLined* pLineSd = NULL;
	CCharElementLined* pCurrLine = NULL;

	if (m_oDiffCharCal.m_nSelectSd > 0)
	{
		pLineSd = (CCharElementLined*)pArea->GetTail();
	}

	CString strStartCurr, strRatiobraking, strParagraph, strTripping, strHarmBrake;
	xlang_GetLangStrByFile(strStartCurr, "CharLib_StartCurr");
	xlang_GetLangStrByFile(strRatiobraking, "CharLib_Ratiobraking");
	xlang_GetLangStrByFile(strParagraph, "CharLib_Paragraph");
	xlang_GetLangStrByFile(strTripping, "CharLib_Tripping");
	xlang_GetLangStrByFile(strHarmBrake, "State_Harmonicbraking");

	if(IsNotHarm())
	{
		//line本身Name是其类型的名称,不是所需要的段名
		pLine1->m_strName = strStartCurr;
		pLine1->SetTestPoint(m_oDiffCharCal.m_nPointNum[0]);
		pLine1->m_strErrLength.Format(_T("%.03f") ,m_oDiffCharCal.m_fErrorBand[0]);
		POS pos = pArea->GetHeadPosition();
		pArea->GetNext(pos);
		long nIndex = 1;
		CString strAppend;

		while(pos)
		{
			pCurrLine = (CCharElementLined*)pArea->GetNext(pos);

			if(pCurrLine == pLineSd)
			{
				break;
			}

			pCurrLine->m_strName = strRatiobraking;
			strAppend.Format(_T("%ld"), nIndex);
			pCurrLine->m_strName += strAppend;
			//pCurrLine->m_strName.AppendFormat(_T("%ld"),nIndex);
			pCurrLine->m_strName += _T(strParagraph);
			pCurrLine->SetTestPoint(m_oDiffCharCal.m_nPointNum[nIndex]);
			pCurrLine->m_strErrLength.Format(_T("%.03f") ,m_oDiffCharCal.m_fErrorBand[nIndex]);
			nIndex++;
		}

		if (m_oDiffCharCal.m_nSelectSd)
		{
			pLineSd->m_strName = strTripping;
			pLineSd->SetTestPoint(m_oDiffCharCal.m_nPointNum[4]);
			pLineSd->m_strErrLength.Format(_T("%.03f") ,m_oDiffCharCal.m_fErrorBand[4]);
		}
	}
	else
	{
		pLine1->m_strName = "";

		pCurrLine = (CCharElementLined*)pArea->GetAt(1);
		pCurrLine->m_strName = strHarmBrake;
		pCurrLine->SetTestPoint(*pCurrLine->GetTestPointsRef());
		pCurrLine->m_strErrLength.Format(_T("%.03f") ,m_oDiffCharCal.m_fErrorBand[1]);

		if (m_oDiffCharCal.m_nSelectSd)
		{
			pLineSd->m_strName = "";
		}
	}

	m_pGridCharLine->ShowDatas(pArea);
}

CCharacteristic* QCharEditWidget_Diff::GetCurrentCharacter()
{
	CCharacteristics *pCharacteristics = stt_Frame_Characteristics();

	if(IsNotHarm())
	{
		return (CCharacteristic*)pCharacteristics->FindByClassID(CHARCLASSID_CCHARACTERISTIC);
	}

	return pCharacteristics->GetTail_Char();
}

bool QCharEditWidget_Diff::IsNotHarm()
{
	return ui.m_radioNormal->isChecked();
}

void QCharEditWidget_Diff::GetTestPointNumErrorBand()
{
	CCharacteristic* pChar = GetCurrentCharacter();

	if (pChar == NULL)
	{
		return;
	}

	CCharacterArea* pArea = pChar->GetCharacterArea();

	if (pArea == NULL)
	{
		return;
	}

	//line本身Name是其类型的名称,不是所需要的段名
	CCharElementLined* pLine1 = (CCharElementLined*)pArea->GetHead();
	CCharElementLined* pLineSd = (CCharElementLined*)pArea->GetTail();
	CCharElementLined* pCurrLine = NULL;
	if(IsNotHarm())
	{
		m_oDiffCharCal.m_nPointNum[0] = *pLine1->GetTestPointsRef();
		m_oDiffCharCal.m_fErrorBand[0] = CString_To_double(pLine1->m_strErrLength);
		POS pos = pArea->GetHeadPosition();
		pArea->GetNext(pos);
		long nIndex = 1;

		while(pos)
		{
			pCurrLine = (CCharElementLined*)pArea->GetNext(pos);

			//zhouhj 2023.11.24 如果已经是最后一段,并且选择了速断,则不需要再赋值,防止误覆盖,导致参数比对不一致
			if ((pos == NULL)&&(m_oDiffCharCal.m_nSelectSd))
			{
				break;
			}

			m_oDiffCharCal.m_nPointNum[nIndex] = *pCurrLine->GetTestPointsRef();
			m_oDiffCharCal.m_fErrorBand[nIndex] = CString_To_double(pCurrLine->m_strErrLength);
			nIndex++;
		}

		if (m_oDiffCharCal.m_nSelectSd)
		{
			m_oDiffCharCal.m_nPointNum[4] = *pLineSd->GetTestPointsRef();
			m_oDiffCharCal.m_fErrorBand[4] = CString_To_double(pLineSd->m_strErrLength);
		}
	}
	else
	{
		pCurrLine = (CCharElementLined*)pArea->GetAt(1);
		m_oDiffCharCal.m_fErrorBand[1] = CString_To_double(pCurrLine->m_strErrLength);
	}
}

void QCharEditWidget_Diff::on_m_edtSet_Istart_editingFinished()
{
	float fv = SetParaI(ui.m_edtSet_Istart, m_oDiffCharCal.m_fIcdqd);
	UpdateChar();
}

void QCharEditWidget_Diff::on_m_edtSet_Kstart_editingFinished()
{
	float fv = SetParaK(ui.m_edtSet_Kstart, m_oDiffCharCal.m_fKid0);
	UpdateChar();
}

void QCharEditWidget_Diff::on_m_edtSet_Ip1_editingFinished()
{
	SetParaI(ui.m_edtSet_Ip1, m_oDiffCharCal.m_fIp1);

	UpdateChar();
}

void QCharEditWidget_Diff::on_m_edtSet_K1_editingFinished()
{
	float fv = SetParaK(ui.m_edtSet_K1, m_oDiffCharCal.m_fKid1);
	UpdateChar();
}

void QCharEditWidget_Diff::on_m_edtSet_Ip2_editingFinished()
{
	float fv = SetParaI(ui.m_edtSet_Ip2, m_oDiffCharCal.m_fIp2);
	UpdateChar();
}

void QCharEditWidget_Diff::on_m_edtSet_K2_editingFinished()
{
	float fv = SetParaK(ui.m_edtSet_K2, m_oDiffCharCal.m_fKid2);
	UpdateChar();
}

void QCharEditWidget_Diff::on_m_edtSet_K3_editingFinished()
{
	float fv = SetParaK(ui.m_edtSet_K3, m_oDiffCharCal.m_fKid3);
	UpdateChar();
}

void QCharEditWidget_Diff::on_m_edtSet_Ip3_editingFinished()
{
	float fv = SetParaI(ui.m_edtSet_Ip3, m_oDiffCharCal.m_fIp3);
	UpdateChar();
}

void QCharEditWidget_Diff::on_m_edtSet_Isd_editingFinished()
{
	float fv = SetParaI(ui.m_edtSet_Isd, m_oDiffCharCal.m_fIsd);
	UpdateChar();
}

float QCharEditWidget_Diff::SetLimit(float min,float max,float val)
{
	if (val<min)
	{
		val = min;
	}
	else if (val>max)
	{
		val = max;
	}
	return val;
}

float QCharEditWidget_Diff::CalLineK(CCharElementLined* pLine)
{
	float fXb, fXe, fYb, fYe;
	fXb = CString_To_double(pLine->m_strXb);
	fXe = CString_To_double(pLine->m_strXe);
	fYb = CString_To_double(pLine->m_strYb);
	fYe = CString_To_double(pLine->m_strYe);
	return (fYe - fYb) / (fXe - fXb);
}

void QCharEditWidget_Diff::GroupDatasToChar(CDataGroup *pDatas)
{
	stt_GetDataValueByID(pDatas,CharDiff_ID_IDoor,m_oDiffCharCal.m_fIcdqd);
	stt_GetDataValueByID(pDatas,CharDiff_ID_IQuickSetting,m_oDiffCharCal.m_fIsd);
	stt_GetDataValueByID(pDatas,CharDiff_ID_Limp1,m_oDiffCharCal.m_fIp1);
	stt_GetDataValueByID(pDatas,CharDiff_ID_Limp2,m_oDiffCharCal.m_fIp2);
	stt_GetDataValueByID(pDatas,CharDiff_ID_Limp3,m_oDiffCharCal.m_fIp3);
	stt_GetDataValueByID(pDatas,CharDiff_ID_StartCurr_Kid,m_oDiffCharCal.m_fKid0);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef_Kid1,m_oDiffCharCal.m_fKid1);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef_Kid2,m_oDiffCharCal.m_fKid2);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef_Kid3,m_oDiffCharCal.m_fKid3);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateHarm,m_oDiffCharCal.m_fHarmCoef);
	stt_GetDataValueByID(pDatas,CharDiff_ID_MinAxis,m_oDiffCharCal.m_nMinAxis);
	stt_GetDataValueByID(pDatas,CharDiff_ID_Insel,m_oDiffCharCal.m_nInsel);
	stt_GetDataValueByID(pDatas,CharDiff_ID_In,m_oDiffCharCal.m_fInSet);

	stt_GetDataValueByID(pDatas,CharDiff_ID_HarmIndex,m_oDiffCharCal.m_nHarmIndex);

	stt_GetDataValueByID(pDatas,CharDiff_ID_StartCurrPointNum,m_oDiffCharCal.m_nPointNum[0]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef1PointNum,m_oDiffCharCal.m_nPointNum[1]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef2PointNum,m_oDiffCharCal.m_nPointNum[2]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef3PointNum,m_oDiffCharCal.m_nPointNum[3]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_QuickCurrPointNum,m_oDiffCharCal.m_nPointNum[4]);

	stt_GetDataValueByID(pDatas,CharDiff_ID_StartCurrErrorBand,m_oDiffCharCal.m_fErrorBand[0]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef1ErrorBand,m_oDiffCharCal.m_fErrorBand[1]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef2ErrorBand,m_oDiffCharCal.m_fErrorBand[2]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef3ErrorBand,m_oDiffCharCal.m_fErrorBand[3]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_QuickCurrErrorBand,m_oDiffCharCal.m_fErrorBand[4]);

	long nStartCurrCheck = 1,nRateCoef1Check = 1,nRateCoef2Check = 1,nRateCoef3Check = 1,nQuickCurrCheck = 1;
	stt_GetDataValueByID(pDatas,CharDiff_ID_StartCurr_Check,nStartCurrCheck);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef1_Check,nRateCoef1Check);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef2_Check,nRateCoef2Check);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef3_Check,nRateCoef3Check);
	stt_GetDataValueByID(pDatas,CharDiff_ID_QuickCurr_Check,m_oDiffCharCal.m_nSelectSd);
	m_oDiffCharCal.m_nKneePoints = nRateCoef1Check + nRateCoef2Check + nRateCoef3Check;
	ui.m_chkLine2->setChecked(nRateCoef2Check);
	ui.m_chkLine3->setChecked(nRateCoef3Check);
	ui.m_chkLineSd->setChecked(m_oDiffCharCal.m_nSelectSd);


	InitDiffData();
	UpdateEditsDisEnable();
	UpdateChar(TRUE,FALSE,FALSE);
}

void QCharEditWidget_Diff::CharToGroupDatas(CDataGroup *pDatas)
{
	GetTestPointNumErrorBand();
	pDatas->SetDataValue(CharDiff_ID_IDoor,m_oDiffCharCal.m_fIcdqd,TRUE);
	pDatas->SetDataValue(CharDiff_ID_IQuickSetting,m_oDiffCharCal.m_fIsd,TRUE);
	pDatas->SetDataValue(CharDiff_ID_Limp1,m_oDiffCharCal.m_fIp1,TRUE);
	pDatas->SetDataValue(CharDiff_ID_Limp2,m_oDiffCharCal.m_fIp2,TRUE);
	pDatas->SetDataValue(CharDiff_ID_Limp3,m_oDiffCharCal.m_fIp3,TRUE);
	pDatas->SetDataValue(CharDiff_ID_StartCurr_Kid,m_oDiffCharCal.m_fKid0,TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef_Kid1,m_oDiffCharCal.m_fKid1,TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef_Kid2,m_oDiffCharCal.m_fKid2,TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef_Kid3,m_oDiffCharCal.m_fKid3,TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateHarm,m_oDiffCharCal.m_fHarmCoef,TRUE);

	pDatas->SetDataValue(CharDiff_ID_MinAxis,m_oDiffCharCal.m_nMinAxis,TRUE);
	pDatas->SetDataValue(CharDiff_ID_Insel,m_oDiffCharCal.m_nInsel,TRUE);
	pDatas->SetDataValue(CharDiff_ID_HarmIndex,m_oDiffCharCal.m_nHarmIndex,TRUE);
	pDatas->SetDataValue(CharDiff_ID_In,m_oDiffCharCal.m_fInSet,TRUE);

	pDatas->SetDataValue(CharDiff_ID_StartCurrPointNum,m_oDiffCharCal.m_nPointNum[0],TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef1PointNum,m_oDiffCharCal.m_nPointNum[1],TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef2PointNum,m_oDiffCharCal.m_nPointNum[2],TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef3PointNum,m_oDiffCharCal.m_nPointNum[3],TRUE);
	pDatas->SetDataValue(CharDiff_ID_QuickCurrPointNum,m_oDiffCharCal.m_nPointNum[4],TRUE);

	pDatas->SetDataValue(CharDiff_ID_StartCurrErrorBand,m_oDiffCharCal.m_fErrorBand[0],TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef1ErrorBand,m_oDiffCharCal.m_fErrorBand[1],TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef2ErrorBand,m_oDiffCharCal.m_fErrorBand[2],TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef3ErrorBand,m_oDiffCharCal.m_fErrorBand[3],TRUE);
	pDatas->SetDataValue(CharDiff_ID_QuickCurrErrorBand,m_oDiffCharCal.m_fErrorBand[4],TRUE);

	long nStartCurrCheck = 1,nRateCoef1Check = 1,nRateCoef2Check = 1,nRateCoef3Check = 1,nQuickCurrCheck = m_oDiffCharCal.m_nSelectSd;

	if (m_oDiffCharCal.m_nKneePoints == 2)
	{
		nRateCoef3Check = 0;
	}
	else if (m_oDiffCharCal.m_nKneePoints == 1)
	{
		nRateCoef2Check = 0;
		nRateCoef3Check = 0;
	}

	pDatas->SetDataValue(CharDiff_ID_StartCurr_Check,nStartCurrCheck,TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef1_Check,nRateCoef1Check,TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef2_Check,nRateCoef2Check,TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef3_Check,nRateCoef3Check,TRUE);
	pDatas->SetDataValue(CharDiff_ID_QuickCurr_Check,nQuickCurrCheck,TRUE);
}

void QCharEditWidget_Diff::OnDataSelChanged( QTableWidget *pGridCtrl, int nRow, int nCol )
{
	CCharElement *pCurrSelElement = (CCharElement*)m_pGridCharLine->GetCurrSelData();

	if (pCurrSelElement == NULL)
	{
		return;
	}

	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();

	if (m_pMainWidget != NULL)
	{
		m_pMainWidget->UI_SetActiveElement((CXDrawElement*)pCurrSelElement->m_pDataRef);
	}
}

//////////////////////////////////////////////////////牵引变差动//////////////////////////////////////////////////////////////////////////////////////
QCharEditWidget_ElecRailwayDiff::QCharEditWidget_ElecRailwayDiff(QWidget *parent) 
 : QWidget(parent)
{
	m_pCharEditWidget = this;	
	m_qCharRadioHarmWidget = new QCharEditRadioHarmWidget(this,&m_oDiffCharCal);
	m_qCharRadioNormalWidget= new QCharEditRadioNormalWidget(this,&m_oDiffCharCal);
	
	m_pMainWidget = (QCharEditMainWidget*)parentWidget();

	InitUI();
	InitChar();//初始化特征曲线图	
	SetDiffFont();
	InitConnect();
	m_stackedWidget->addWidget(this->m_qCharRadioNormalWidget);
	m_qCharRadioNormalWidget->setParent(m_stackedWidget);
	m_stackedWidget->addWidget(m_qCharRadioHarmWidget);
	m_qCharRadioNormalWidget->setParent(m_stackedWidget);

	m_stackedWidget->setCurrentWidget(m_qCharRadioNormalWidget);
}

QCharEditWidget_ElecRailwayDiff::~QCharEditWidget_ElecRailwayDiff()
{

}
void QCharEditWidget_ElecRailwayDiff::InitUI()
{
	resize(480,560);
		
	m_mainQVBoxLayout = new QVBoxLayout;
	m_QHBoxLayout = new QHBoxLayout;
	m_QHBoxWidget = new QWidget;
	m_radioNormal = new QRadioButton;
	m_radioHarm = new QRadioButton;
	m_stackedWidget = new QStackedWidget;


	this->setLayout(m_mainQVBoxLayout);
	m_radioHarm->setText(/*tr("谐波制动")*/g_sLangTxt_State_Harmonicbraking);
	m_radioNormal->setText(/*tr("比率差动")*/g_sLangTxt_Gradient_RatioDiff);

	m_QHBoxLayout->setDirection(QBoxLayout::LeftToRight);
	m_QHBoxLayout->addWidget(m_radioNormal);
	m_QHBoxLayout->addWidget(m_radioHarm);

	m_QHBoxLayout->setSpacing(0);
	m_QHBoxLayout->setMargin(0);//设置外边距
	m_QHBoxLayout->setSpacing(0);//设置内边距
	m_mainQVBoxLayout->addLayout(m_QHBoxLayout);
	m_mainQVBoxLayout->addWidget(m_stackedWidget);

	m_mainQVBoxLayout->setMargin(0);//设置外边距
	m_mainQVBoxLayout->setSpacing(0);//设置内边距

	m_mainQVBoxLayout->setContentsMargins(0,0,0,0);

	m_radioNormal->setChecked(TRUE);

}
void QCharEditWidget_ElecRailwayDiff::SetDiffFont()
{
	m_radioNormal->setFont(*g_pSttGlobalFont);
	m_radioHarm->setFont(*g_pSttGlobalFont);

}

void QCharEditWidget_ElecRailwayDiff::OnLeftButtonDown()
{
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	if(IsNotHarm())
	{
		m_pMainWidget->m_pImpCharactWidget->CalPointVertHorzLine(0, CHAR_TESTLINE_MODE_ID_VERT);
		m_qCharRadioNormalWidget->UpdateEdit_IrValueUserPoint();
	}
	else
	{
		m_pMainWidget->m_pImpCharactWidget->CalPointVertHorzLine(0, CHAR_TESTLINE_MODE_ID_HORZ);
		m_qCharRadioHarmWidget->UpdateEdit_IrValueUserPoint();

	}
}

void QCharEditWidget_ElecRailwayDiff::InitConnect()
{
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	connect(m_qCharRadioNormalWidget, SIGNAL(sig_CharChanged(CExBaseObject *,int)), m_pMainWidget,SLOT(slot_UpdateDrawCharacters(CExBaseObject *,int)));
	connect(m_qCharRadioHarmWidget, SIGNAL(sig_CharChanged(CExBaseObject *,int)), m_pMainWidget,SLOT(slot_UpdateDrawCharacters(CExBaseObject *,int)));
	connect(this, SIGNAL(sig_CharChanged(CExBaseObject *,int)), m_pMainWidget,SLOT(slot_UpdateDrawCharacters(CExBaseObject *,int)));

	connect(m_qCharRadioNormalWidget,SIGNAL(sig_IdValue_editingFinished(CString)),this,SLOT(IdValue_NormalEditing(CString)));
	connect(m_qCharRadioHarmWidget,SIGNAL(sig_IdValue_editingFinished(CString)),this,SLOT(IdValue_NormalEditing(CString)));

	connect(m_qCharRadioNormalWidget,SIGNAL(sig_MainWidgetCharChange()),this,SLOT(ChangeMainWin_Char()));
	connect(m_qCharRadioHarmWidget,SIGNAL(sig_MainWidgetCharChange()),this,SLOT(ChangeMainWin_Char()));

	connect(m_radioNormal, SIGNAL(clicked()), this, SLOT(slot_radioNormal_Clicked()));
	connect(m_radioHarm, SIGNAL(clicked()), this, SLOT(slot_radioHarm_Clicked()));
	
	connect(m_qCharRadioNormalWidget,SIGNAL(sig_ChangeICMAxisName()),this,SLOT(slot_ChangeICMAxisName()));
	connect(m_qCharRadioHarmWidget,SIGNAL(sig_ChangeICMAxisName()),this,SLOT(slot_ChangeICMAxisName()));

	connect(m_qCharRadioNormalWidget,SIGNAL(sig_ChangeTranSortIndex(int)),m_qCharRadioHarmWidget,SLOT(slot_normalChangeTransSort(int)));
	connect(m_qCharRadioHarmWidget,SIGNAL(sig_ChangeTranSortIndex(int)),m_qCharRadioNormalWidget,SLOT(slot_HarmChangeTransSort(int)));
	connect(m_qCharRadioNormalWidget,SIGNAL(sig_ChangeSettingMinAxisIndex(int)),m_qCharRadioHarmWidget,SLOT(slot_normalChangeSettingMinAxis(int)));
	connect(m_qCharRadioHarmWidget,SIGNAL(sig_ChangeSettingMinAxisIndex(int)),m_qCharRadioNormalWidget,SLOT(slot_HarmChangeSettingMinAxis(int)));
	connect(m_qCharRadioNormalWidget,SIGNAL(sig_ChangeInset(float)),m_qCharRadioHarmWidget,SLOT(slot_normalChangeInSet(float)));
	connect(m_qCharRadioHarmWidget,SIGNAL(sig_ChangeInset(float)),m_qCharRadioNormalWidget,SLOT(slot_HarmChangeInSet(float)));
	connect(m_qCharRadioNormalWidget,SIGNAL(sig_ChangeCTPoint(bool)),m_qCharRadioHarmWidget,SLOT(slot_normalChangeCTPoint( bool)));
	connect(m_qCharRadioHarmWidget,SIGNAL(sig_ChangeCTPoint(bool)),m_qCharRadioNormalWidget,SLOT(slot_HarmChangeCTPoint( bool)));

	connect(m_qCharRadioNormalWidget, SIGNAL(sig_UpdateChar(bool,bool,bool)), this,SLOT(slot_UpdateChar(bool ,bool ,bool )));
	connect(m_qCharRadioHarmWidget, SIGNAL(sig_UpdateChar(bool,bool,bool)), this,SLOT(slot_UpdateChar(bool,bool,bool)));

	connect(m_qCharRadioNormalWidget, SIGNAL(sig_ChangeIstart(float)), m_qCharRadioHarmWidget,SLOT(slot_normalChangeIstart(float)));
	connect(m_qCharRadioHarmWidget, SIGNAL(sig_ChangeIstart(float)), m_qCharRadioNormalWidget,SLOT(slot_HarmChangeIstart(float)));

	connect(m_qCharRadioNormalWidget, SIGNAL(sig_ChangeIsd(float)), m_qCharRadioHarmWidget,SLOT(slot_normalChangeIsd(float)));
	connect(m_qCharRadioHarmWidget, SIGNAL(sig_ChangeIsd(float)), m_qCharRadioNormalWidget,SLOT(slot_HarmChangeIsd(float)));

	
	connect(m_qCharRadioNormalWidget, SIGNAL(sig_TestPointsErrorBandChanged()), this,SLOT(slot_TestPointsErrorBandChanged()));
	connect(m_qCharRadioHarmWidget, SIGNAL(sig_TestPointsErrorBandChanged()), this,SLOT(slot_TestPointsErrorBandChanged()));

	connect(m_qCharRadioNormalWidget, SIGNAL(sig_ActiveSegment(CCharElement *)), this,SLOT(slot_ActiveSegment(CCharElement *)));
	connect(m_qCharRadioHarmWidget, SIGNAL(sig_ActiveSegment(CCharElement *)), this,SLOT(slot_ActiveSegment(CCharElement *)));

}


void QCharEditWidget_ElecRailwayDiff::on_m_onlineEdit_Changed()
{
 	QSttLineEdit* pEditLine = qobject_cast<QSttLineEdit*>(sender());

	if (pEditLine->text().isEmpty())
	{
		pEditLine->setText("0.0");
	}

	QString str = pEditLine->text();
	GetWidgetBoard_DigitData(4,str,pEditLine,this);

	if (str.right(1).contains("."))
	{
		str.append("000");
	}

	m_pMainWidget->m_bCharChanged = TRUE;

}

void QCharEditWidget_ElecRailwayDiff::slot_TestPointsErrorBandChanged()
{
	GetTestPointNumErrorBand();
	emit sig_CharChanged(GetCurrentCharacter(),TRUE);	
}

void QCharEditWidget_ElecRailwayDiff::slot_DiffCharChanged()
{
	emit sig_CharChanged(GetCurrentCharacter(),TRUE);	
}

void QCharEditWidget_ElecRailwayDiff::IdValue_NormalEditing(CString strIdValue)
{
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	if(IsNotHarm())
	{
		m_pMainWidget->m_pImpCharactWidget->UpdateVertLine(CString_To_double(strIdValue));

	}
	else
	{
		m_pMainWidget->m_pImpCharactWidget->UpdateHorzLine(CString_To_double(strIdValue));
	}
}

void QCharEditWidget_ElecRailwayDiff::slot_radioNormal_Clicked()
{
	m_qCharRadioNormalWidget->UpdateEditsDisEnable();
	InitUI_Unit();
	OnLeftButtonDown();
	UpdateChar(TRUE,TRUE);
	m_stackedWidget->setCurrentWidget(this->m_qCharRadioNormalWidget);

}

void QCharEditWidget_ElecRailwayDiff::slot_radioHarm_Clicked()
{	
	m_qCharRadioHarmWidget->UpdateEditsDisEnable();	
	InitUI_Unit();
	OnLeftButtonDown();
	UpdateChar(TRUE,TRUE);
	m_stackedWidget->setCurrentWidget(m_qCharRadioHarmWidget);
}

float QCharEditWidget_ElecRailwayDiff::SetParaI(QLineEdit* pEdit, float& fv)
{
	if (pEdit->text().isEmpty())
	{
		pEdit->setText("0.000");
	}

	QString str = pEdit->text();
	if (str.right(1).contains("."))
	{
		str.append(000);
	}

	fv = str.toFloat();
	fv = SetLimit(0,999.999,fv);
	pEdit->setText(QString::number(fv,'f',3));
	return fv;
}

float QCharEditWidget_ElecRailwayDiff::SetParaK(QLineEdit* pEdit, float& fv)
{
	if (pEdit->text().isEmpty())
	{
		pEdit->setText("0.000");
	}

	QString str = pEdit->text();
	if (str.right(1).contains("."))
	{
		str.append(000);
	}

	fv = str.toFloat();
	fv = SetLimit(0,999.999,fv);
	pEdit->setText(QString::number(fv,'f',3));
	return fv;
}


void QCharEditWidget_ElecRailwayDiff::InitChar()
{
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	m_pMainWidget->UpdateCharAxisType(AXIS_TYPE_ID_CARTES,FALSE);
	m_pMainWidget->m_pImpCharactWidget->EnableSetting(FALSE);
	m_pMainWidget->m_pImpCharactWidget->setObjectName(QString::fromUtf8("QElecRailwayDiffCharactWidget"));
	m_pMainWidget->m_pImpCharactWidget->SetAxisName(_T("Ir(A)"),_T("Id(A)"),_T(" "));
	m_pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(_T("A"),_T("A"));
	m_pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(false);
	m_pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowAng(false);
	
	//UpdateChar();

}

void QCharEditWidget_ElecRailwayDiff::UpdateChar(BOOL bUpdateTable,BOOL bCharTypeChanged,BOOL bParasChanged)
{
	long bChanged = m_oDiffCharCal.m_oPoints.GetCount();
	if(IsNotHarm())
	{
		m_oDiffCharCal.Cal();		
	}
	else
	{
		m_oDiffCharCal.CalHarm();
	}
	
	CCharacteristic* pChar = GetCurrentCharacter();

	if (pChar == NULL)
	{
		return;
	}

	pChar->m_bXMin = TRUE;
	pChar->m_bXMax = TRUE;
	pChar->m_bYMin = TRUE;
	pChar->m_bYMax = TRUE;
	pChar->m_fXMin = 0.0f;
	pChar->m_fYMin = 0.0f;
	pChar->m_fXMax = m_oDiffCharCal.m_fXMax;
	pChar->m_fYMax = m_oDiffCharCal.m_fYMax;
	pChar->m_strXMin = _T("0.0");
	pChar->m_strYMin = _T("0.0");
	pChar->m_strXMax.Format(_T("%lf"),pChar->m_fXMax);
	pChar->m_strYMax.Format(_T("%lf"),pChar->m_fYMax);
	CCharacterArea* pArea = pChar->GetCharacterArea();

	if((!bCharTypeChanged) && (bChanged != m_oDiffCharCal.m_oPoints.GetCount()))
	{
		//段数改变
		pArea->DeleteAll();
		CCharElement *pCharElement = pArea->GetCharBisector();

		if (pCharElement != NULL)//20230206 zhouhj  拐点等线段也删除
		{
			pCharElement->DeleteAll();
		}

		POS pos = m_oDiffCharCal.m_oPoints.GetHeadPosition();
		CXDrawData_Point* pLast = NULL;
		CString strFX, strFY;
		long nLineIndex = 0;

		while (pos)
		{
			CXDrawData_Point* pt = (CXDrawData_Point*)m_oDiffCharCal.m_oPoints.GetNext(pos);

			if(pLast)
			{
				CCharElementLined* pLine = new CCharElementLined;
				strFX.Format("%.3f", pLast->m_fX);
				strFY.Format("%.3f", pLast->m_fY);
				pLine->SetBeginPoint(strFX, strFY);
				strFX.Format("%.3f", pt->m_fX);
				strFY.Format("%.3f", pt->m_fY);
				pLine->SetEndPoint(strFX, strFY);
				pArea->AddNewChild(pLine);
				nLineIndex++;
			}

			pLast = pt;
		}

		ShowDatas_Table();
	}
	else
	{
		POS pos = m_oDiffCharCal.m_oPoints.GetHeadPosition();
		CXDrawData_Point* pLast = NULL;
		CString strFX, strFY;
		long nIndex = 0;
		while (pos)
		{
			CXDrawData_Point* pt = (CXDrawData_Point*)m_oDiffCharCal.m_oPoints.GetNext(pos);
			if(pLast)
			{
				CCharElementLined* pLine = (CCharElementLined*)pArea->GetAt((long)nIndex);
				strFX.Format("%.3f", pLast->m_fX);
				strFY.Format("%.3f", pLast->m_fY);
				pLine->SetBeginPoint(strFX, strFY);
				strFX.Format("%.3f", pt->m_fX);
				strFY.Format("%.3f", pt->m_fY);
				pLine->SetEndPoint(strFX, strFY);
				nIndex++;
			}
			pLast = pt;
		}

		if (bUpdateTable)
		{
			ShowDatas_Table();
		}
	}

	emit sig_CharChanged(GetCurrentCharacter(),bParasChanged);	
}

void QCharEditWidget_ElecRailwayDiff::ShowDatas_Table()
{
	CCharacteristic* pChar = GetCurrentCharacter();

	if (pChar == NULL)
	{
		return;
	}


	CCharacterArea* pArea = pChar->GetCharacterArea();

	if (pArea == NULL)
	{
		return;
	}

	CCharElementLined* pLine1 = (CCharElementLined*)pArea->GetHead();
	CCharElementLined* pLineSd = NULL;
	CCharElementLined* pCurrLine = NULL;

	if (m_oDiffCharCal.m_nSelectSd > 0)
	{
		pLineSd = (CCharElementLined*)pArea->GetTail();
	}

	CString strStartCurr, strRatiobraking, strParagraph, strTripping, strHarmBrake;
	xlang_GetLangStrByFile(strStartCurr, "CharLib_StartCurr");
	xlang_GetLangStrByFile(strRatiobraking, "CharLib_Ratiobraking");
	xlang_GetLangStrByFile(strParagraph, "CharLib_Paragraph");
	xlang_GetLangStrByFile(strTripping, "CharLib_Tripping");
	xlang_GetLangStrByFile(strHarmBrake, "State_Harmonicbraking");

	if(IsNotHarm())
	{
		//line本身Name是其类型的名称,不是所需要的段名
		pLine1->m_strName = strStartCurr;
		pLine1->SetTestPoint(m_oDiffCharCal.m_nPointNum[0]);
		pLine1->m_strErrLength.Format(_T("%.03f") ,m_oDiffCharCal.m_fErrorBand[0]);
		POS pos = pArea->GetHeadPosition();
		pArea->GetNext(pos);
		long nIndex = 1;
		CString strAppend;

		while(pos)
		{
			pCurrLine = (CCharElementLined*)pArea->GetNext(pos);

			if(pCurrLine == pLineSd)
			{
				break;
			}

			pCurrLine->m_strName = strRatiobraking;
			strAppend.Format(_T("%ld"), nIndex);
			pCurrLine->m_strName += strAppend;
			//pCurrLine->m_strName.AppendFormat(_T("%ld"),nIndex);
			pCurrLine->m_strName += _T(strParagraph);
			pCurrLine->SetTestPoint(m_oDiffCharCal.m_nPointNum[nIndex]);
			pCurrLine->m_strErrLength.Format(_T("%.03f") ,m_oDiffCharCal.m_fErrorBand[nIndex]);
			nIndex++;
		}

		if (m_oDiffCharCal.m_nSelectSd)
		{
			pLineSd->m_strName = strTripping;
			pLineSd->SetTestPoint(m_oDiffCharCal.m_nPointNum[4]);
			pLineSd->m_strErrLength.Format(_T("%.03f") ,m_oDiffCharCal.m_fErrorBand[4]);
		}
	}
	else
	{
		pLine1->m_strName = "";

		pCurrLine = (CCharElementLined*)pArea->GetAt(1);
		pCurrLine->m_strName = strHarmBrake;
		pCurrLine->SetTestPoint(*pCurrLine->GetTestPointsRef());
		pCurrLine->m_strErrLength.Format(_T("%.03f") ,m_oDiffCharCal.m_fErrorBand[1]);

		if (m_oDiffCharCal.m_nSelectSd)
		{
			pLineSd->m_strName = "";
		}
	}
	m_qCharRadioNormalWidget->m_pGridCharLine->ShowDatas(pArea);
	m_qCharRadioHarmWidget->m_pGridCharLine->ShowDatas(pArea);
}

CCharacteristic* QCharEditWidget_ElecRailwayDiff::GetCurrentCharacter()
{
	CCharacteristics *pCharacteristics = stt_Frame_Characteristics();

	if(IsNotHarm())
	{
		return (CCharacteristic*)stt_Frame_Characteristics()->FindByClassID(CHARCLASSID_CCHARACTERISTIC);
	}

	return pCharacteristics->GetTail_Char();
}

bool QCharEditWidget_ElecRailwayDiff::IsNotHarm()
{
	return m_radioNormal->isChecked();
}

void QCharEditWidget_ElecRailwayDiff::GetTestPointNumErrorBand()
{
	CCharacteristic* pChar = GetCurrentCharacter();

	if (pChar == NULL)
	{
		return;
	}

	CCharacterArea* pArea = pChar->GetCharacterArea();

	if (pArea == NULL)
	{
		return;
	}

	//line本身Name是其类型的名称,不是所需要的段名
	CCharElementLined* pLine1 = (CCharElementLined*)pArea->GetHead();
	CCharElementLined* pLineSd = (CCharElementLined*)pArea->GetTail();
	CCharElementLined* pCurrLine = NULL;
	if(IsNotHarm())
	{
		m_oDiffCharCal.m_nPointNum[0] = *pLine1->GetTestPointsRef();
		m_oDiffCharCal.m_fErrorBand[0] = CString_To_double(pLine1->m_strErrLength);
		POS pos = pArea->GetHeadPosition();
		pArea->GetNext(pos);
		long nIndex = 1;

		while(pos)
		{
			pCurrLine = (CCharElementLined*)pArea->GetNext(pos);

			m_oDiffCharCal.m_nPointNum[nIndex] = *pCurrLine->GetTestPointsRef();
			m_oDiffCharCal.m_fErrorBand[nIndex] = CString_To_double(pCurrLine->m_strErrLength);
			nIndex++;
		}

		if (m_oDiffCharCal.m_nSelectSd)
		{
			m_oDiffCharCal.m_nPointNum[4] = *pLineSd->GetTestPointsRef();
			m_oDiffCharCal.m_fErrorBand[4] = CString_To_double(pLineSd->m_strErrLength);
		}
	}
	else
	{
		pCurrLine = (CCharElementLined*)pArea->GetAt(1);
		m_oDiffCharCal.m_fErrorBand[1] = CString_To_double(pCurrLine->m_strErrLength);
	}
}


float QCharEditWidget_ElecRailwayDiff::SetLimit(float min,float max,float val)
{
	if (val<min)
	{
		val = min;
	}
	else if (val>max)
	{
		val = max;
	}
	return val;
}

float QCharEditWidget_ElecRailwayDiff::CalLineK(CCharElementLined* pLine)
{
	float fXb, fXe, fYb, fYe;
	fXb = CString_To_double(pLine->m_strXb);
	fXe = CString_To_double(pLine->m_strXe);
	fYb = CString_To_double(pLine->m_strYb);
	fYe = CString_To_double(pLine->m_strYe);
	return (fYe - fYb) / (fXe - fXb);
}

void QCharEditWidget_ElecRailwayDiff::GroupDatasToChar(CDataGroup *pDatas)
{
	float fKid0 = 0.0f;
	stt_GetDataValueByID(pDatas,CharDiff_ID_IDoor,m_oDiffCharCal.m_fIcdqd);
	stt_GetDataValueByID(pDatas,CharDiff_ID_CTPoint,m_nCTPoint);
	stt_GetDataValueByID(pDatas,CharDiff_ID_IQuickSetting,m_oDiffCharCal.m_fIsd);
	stt_GetDataValueByID(pDatas,CharDiff_ID_Limp1,m_oDiffCharCal.m_fIp1);
	stt_GetDataValueByID(pDatas,CharDiff_ID_Limp2,m_oDiffCharCal.m_fIp2);
	stt_GetDataValueByID(pDatas,CharDiff_ID_Limp3,m_oDiffCharCal.m_fIp3);
	stt_GetDataValueByID(pDatas,CharDiff_ID_StartCurr_Kid,fKid0/*m_oDiffCharCal.m_fKid0*/);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef_Kid1,m_oDiffCharCal.m_fKid1);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef_Kid2,m_oDiffCharCal.m_fKid2);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef_Kid3,m_oDiffCharCal.m_fKid3);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateHarm,m_oDiffCharCal.m_fHarmCoef);
	stt_GetDataValueByID(pDatas,CharDiff_ID_MinAxis,m_oDiffCharCal.m_nMinAxis);
	stt_GetDataValueByID(pDatas,CharDiff_ID_Insel,m_oDiffCharCal.m_nInsel);
	stt_GetDataValueByID(pDatas,CharDiff_ID_In,m_oDiffCharCal.m_fInSet);

	stt_GetDataValueByID(pDatas,CharDiff_ID_HarmIndex,m_oDiffCharCal.m_nHarmIndex);

	stt_GetDataValueByID(pDatas,CharDiff_ID_StartCurrPointNum,m_oDiffCharCal.m_nPointNum[0]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef1PointNum,m_oDiffCharCal.m_nPointNum[1]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef2PointNum,m_oDiffCharCal.m_nPointNum[2]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef3PointNum,m_oDiffCharCal.m_nPointNum[3]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_QuickCurrPointNum,m_oDiffCharCal.m_nPointNum[4]);

	stt_GetDataValueByID(pDatas,CharDiff_ID_StartCurrErrorBand,m_oDiffCharCal.m_fErrorBand[0]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef1ErrorBand,m_oDiffCharCal.m_fErrorBand[1]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef2ErrorBand,m_oDiffCharCal.m_fErrorBand[2]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef3ErrorBand,m_oDiffCharCal.m_fErrorBand[3]);
	stt_GetDataValueByID(pDatas,CharDiff_ID_QuickCurrErrorBand,m_oDiffCharCal.m_fErrorBand[4]);

	long nStartCurrCheck = 1,nRateCoef1Check = 1,nRateCoef2Check = 1,nRateCoef3Check = 1,nQuickCurrCheck = 1;
	stt_GetDataValueByID(pDatas,CharDiff_ID_StartCurr_Check,nStartCurrCheck);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef1_Check,nRateCoef1Check);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef2_Check,nRateCoef2Check);
	stt_GetDataValueByID(pDatas,CharDiff_ID_RateCoef3_Check,nRateCoef3Check);
	stt_GetDataValueByID(pDatas,CharDiff_ID_QuickCurr_Check,m_oDiffCharCal.m_nSelectSd);
	m_oDiffCharCal.m_nKneePoints = nRateCoef1Check + nRateCoef2Check + nRateCoef3Check;

	//20230718-wxy-修改比率差动和谐波制动CT极性值
	bool bCTPoint;
	if(m_nCTPoint == 0)
	{
		bCTPoint = false;
	}
	else if(m_nCTPoint == 1)
	{
		bCTPoint = true;
	}
	m_qCharRadioNormalWidget->m_bAmbo = bCTPoint;
	m_qCharRadioHarmWidget->m_bAmbo = bCTPoint;

	
	

	m_qCharRadioHarmWidget->InitDataToChar();
	m_qCharRadioNormalWidget->InitDataToChar(nRateCoef2Check);

}

void QCharEditWidget_ElecRailwayDiff::CharToGroupDatas(CDataGroup *pDatas)
{
	GetTestPointNumErrorBand();
	pDatas->SetDataValue(CharDiff_ID_IDoor,m_oDiffCharCal.m_fIcdqd,TRUE);
	pDatas->SetDataValue(CharDiff_ID_IQuickSetting,m_oDiffCharCal.m_fIsd,TRUE);
	pDatas->SetDataValue(CharDiff_ID_Limp1,m_oDiffCharCal.m_fIp1,TRUE);
	pDatas->SetDataValue(CharDiff_ID_Limp2,m_oDiffCharCal.m_fIp2,TRUE);
	pDatas->SetDataValue(CharDiff_ID_Limp3,m_oDiffCharCal.m_fIp3,TRUE);
	pDatas->SetDataValue(CharDiff_ID_StartCurr_Kid,m_oDiffCharCal.m_fKid0,TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef_Kid1,m_oDiffCharCal.m_fKid1,TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef_Kid2,m_oDiffCharCal.m_fKid2,TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef_Kid3,m_oDiffCharCal.m_fKid3,TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateHarm,m_oDiffCharCal.m_fHarmCoef,TRUE);

	pDatas->SetDataValue(CharDiff_ID_MinAxis,m_oDiffCharCal.m_nMinAxis,TRUE);
	pDatas->SetDataValue(CharDiff_ID_Insel,m_oDiffCharCal.m_nInsel,TRUE);
	pDatas->SetDataValue(CharDiff_ID_HarmIndex,m_oDiffCharCal.m_nHarmIndex,TRUE);
	pDatas->SetDataValue(CharDiff_ID_In,m_oDiffCharCal.m_fInSet,TRUE);

	pDatas->SetDataValue(CharDiff_ID_StartCurrPointNum,m_oDiffCharCal.m_nPointNum[0],TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef1PointNum,m_oDiffCharCal.m_nPointNum[1],TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef2PointNum,m_oDiffCharCal.m_nPointNum[2],TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef3PointNum,m_oDiffCharCal.m_nPointNum[3],TRUE);
	pDatas->SetDataValue(CharDiff_ID_QuickCurrPointNum,m_oDiffCharCal.m_nPointNum[4],TRUE);

	pDatas->SetDataValue(CharDiff_ID_StartCurrErrorBand,m_oDiffCharCal.m_fErrorBand[0],TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef1ErrorBand,m_oDiffCharCal.m_fErrorBand[1],TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef2ErrorBand,m_oDiffCharCal.m_fErrorBand[2],TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef3ErrorBand,m_oDiffCharCal.m_fErrorBand[3],TRUE);
	pDatas->SetDataValue(CharDiff_ID_QuickCurrErrorBand,m_oDiffCharCal.m_fErrorBand[4],TRUE);

	long nStartCurrCheck = 1,nRateCoef1Check = 1,nRateCoef2Check = 1,nRateCoef3Check = 1,nQuickCurrCheck = m_oDiffCharCal.m_nSelectSd;

	if (m_oDiffCharCal.m_nKneePoints == 2)
	{
		nRateCoef3Check = 0;
	}
	else if (m_oDiffCharCal.m_nKneePoints == 1)
	{
		nRateCoef2Check = 0;
		nRateCoef3Check = 0;
	}

	pDatas->SetDataValue(CharDiff_ID_StartCurr_Check,nStartCurrCheck,TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef1_Check,nRateCoef1Check,TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef2_Check,nRateCoef2Check,TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef3_Check,nRateCoef3Check,TRUE);
	pDatas->SetDataValue(CharDiff_ID_QuickCurr_Check,nQuickCurrCheck,TRUE);
	
}


void QCharEditWidget_ElecRailwayDiff::slot_ChangeICMAxisName()
{
	CString strText,strText_IrAxis,strText_IdAxis,strCustomText;

	if(IsNotHarm())
	{
		if (m_oDiffCharCal.m_nMinAxis)
		{
			strText_IrAxis = _T("Ir(Ie)");
			strText_IdAxis = _T("Id(Ie)");
		} 
		else
		{
			strText_IrAxis = _T("Ir(A)");
			strText_IdAxis = _T("Id(A)");
		}
		m_qCharRadioNormalWidget->InitUI_Unit();
	}
	else
	{
		strText_IrAxis = _T("%");

		if (m_oDiffCharCal.m_nMinAxis)
		{
			strText_IdAxis = _T("Id(Ie)");
		} 
		else
		{
			strText_IdAxis = _T("Id(A)");
		}
		m_qCharRadioHarmWidget->InitUI_Unit();

	}

	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();

	if (m_pMainWidget != NULL)
	{
		m_pMainWidget->m_pImpCharactWidget->SetAxisName(strText_IrAxis,strText_IdAxis,_T(" "));
	}
	emit sig_CharChanged(GetCurrentCharacter(),TRUE);	
}

void QCharEditWidget_ElecRailwayDiff::ChangeMainWin_Char()
{
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	m_pMainWidget->m_bCharChanged = TRUE;
}

void QCharEditWidget_ElecRailwayDiff::InitUI_Unit()
{
	CString strText,strText_IrAxis,strText_IdAxis,strCustomText;

	if(IsNotHarm())
	{
		if (m_oDiffCharCal.m_nMinAxis)
		{
			strText_IrAxis = _T("Ir(Ie)");
			strText_IdAxis = _T("Id(Ie)");
		} 
		else
		{
			strText_IrAxis = _T("Ir(A)");
			strText_IdAxis = _T("Id(A)");
		}
		m_qCharRadioNormalWidget->InitUI_Unit();
	}
	else
	{
		strText_IrAxis = _T("%");

		if (m_oDiffCharCal.m_nMinAxis)
		{
			strText_IdAxis = _T("Id(Ie)");
		} 
		else
		{
			strText_IdAxis = _T("Id(A)");
		}
		m_qCharRadioHarmWidget->InitUI_Unit();
	}

	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();

	if (m_pMainWidget != NULL)
	{
		m_pMainWidget->m_pImpCharactWidget->SetAxisName(strText_IrAxis,strText_IdAxis,_T(" "));
	}
}


void QCharEditWidget_ElecRailwayDiff::slot_UpdateChar( bool bUpdateTable,bool bCharTypeChanged,bool bParasChanged )
{
	UpdateChar(bUpdateTable,bCharTypeChanged,bParasChanged);
}

void QCharEditWidget_ElecRailwayDiff::slot_ActiveSegment( CCharElement *pCurrSelElement )
{
	if(pCurrSelElement == NULL)
	{
		return;
	}

	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();

	if (m_pMainWidget != NULL)
	{
		m_pMainWidget->UI_SetActiveElement((CXDrawElement*)pCurrSelElement->m_pDataRef);
	}
	
}





#include "StateEstimateDlg.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"

#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QHeaderView>
#include "../Controls/SttCheckBox.h"
StateEstimateGrid::StateEstimateGrid(int rows, int columns, QWidget* parent) : QTableWidget(rows, columns, parent)
{
	m_pParas = NULL;
	m_bRunning = FALSE;
	installEventFilter(this);
}

StateEstimateGrid::~StateEstimateGrid()
{

}

void StateEstimateGrid::InitGrid()
{
	CString strSelect, strName, strStart, strEnd, strErrorType, strRelError, strAbsError, strSettingValue, strBin;

	xlang_GetLangStrByFile(strSelect, "sSelect");
	xlang_GetLangStrByFile(strName, "sName");
	xlang_GetLangStrByFile(strStart, "StateEstimate_Start");
	//xlang_GetLangStrByFile(strEnd, "StateEstimate_End");
	xlang_GetLangStrByFile(strErrorType, "StateEstimate_ErrorType");
	//xlang_GetLangStrByFile(strRelError, "Native_Name");
	//xlang_GetLangStrByFile(strAbsError, "Native_Choose");
	xlang_GetLangStrByFile(strSettingValue, "StateEstimate_SettingValue");
	xlang_GetLangStrByFile(strBin, "Native_BinX");

// 	strStart = "��ʱ���";
	strEnd = g_sLangTxt_StateEstimate_End;
// 	strErrorType = "�������";
 	strRelError = g_sLangTxt_StateEstimate_RelError;
	strRelError += "(%)";
	strAbsError = g_sLangTxt_StateEstimate_AbsError;
	strAbsError += "(s)";

// 	strSettingValue = "����ֵ(s)";
// 	strBin = "����";
	setHorizontalHeaderLabels(QStringList() << strSelect << strName << strStart << strBin << strEnd << strBin << strErrorType << strRelError << strAbsError << strSettingValue);
	setColumnWidth(0, 40);
	setColumnWidth(3, 120);
	setColumnWidth(5, 120);
	setColumnWidth(6, 150);
	setColumnWidth(7, 80);
	setColumnWidth(8, 70);
	setColumnWidth(9, 60);
	this->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //���ñ�ͷ����ɫ
	this->setStyleSheet("selection-background-color: grey;selection-color: black");
	//this->verticalHeader()->setDefaultSectionSize(40);
}


void StateEstimateGrid::slot_StateBinChanged(const QString& strText)
{
	QComboBox* pCbb = (QComboBox*)sender();
	long nRow = rowAt(pCbb->pos().y());
	long nCol = columnAt(pCbb->pos().x());
	CString strName;
	tmt_StatePara* pPara = NULL;
	for (int i = 0; i < m_pParas->m_nStateNumbers; i++)
	{
		pPara = &m_pParas->m_paraState[i];

		xlang_GetLangStrByFile(strName, "sState");
		strName += QString::number(i + 1);

// 		CString strName = pPara->m_strName;
		if(strName == strText)
		{
			break;
		}
	}

	pCbb = (QComboBox*)cellWidget(nRow, nCol + 1);
	pCbb->clear();
	if(strText != /*"���봥��"*/g_sLangTxt_StateEstimate_BinTrigger)
	{
		for (int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			if(pPara->m_binIn[i].nSelect)
			{
				char ch = 'A' + i;
				CString strText = /*"����"*/g_sLangTxt_Native_BinX;
				strText += ch;
				pCbb->addItem(strText + " 0->1");
				pCbb->addItem(strText + " 1->0");
			}
		}
	}
	pCbb->addItem("--");
}

void StateEstimateGrid::InitStateBin(CString strStateName, long nRow, long nCol)
{
	QComboBox* pCbbStatesBin = new QComboBox(this);

	CString strName;
	if(strStateName != /*"���봥��"*/g_sLangTxt_StateEstimate_BinTrigger)
	{
		tmt_StatePara* pPara = NULL;
		for (int i = 0; i < m_pParas->m_nStateNumbers; i++)
		{
			pPara = &m_pParas->m_paraState[i];

			xlang_GetLangStrByFile(strName, "sState");
			strName += QString::number(i + 1);
// 			CString strName = pPara->m_strName;
			
			if(strName == strStateName)
			{
				break;
			}
		}

		for (int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			if(pPara->m_binIn[i].nSelect)
			{
				char ch = 'A' + i;
				CString strText = /*"����"*/g_sLangTxt_Native_BinX;
				strText += ch;
				pCbbStatesBin->addItem(strText + " 0->1");
				pCbbStatesBin->addItem(strText + " 1->0");
			}
		}
		pCbbStatesBin->addItem("--");

		CString strText;
		if(nCol == 3)
		{
			strText = m_pParas->m_paraEstimates[nRow].m_strTtripBegin_Bin;
		}
		else if(nCol == 5)
		{
			strText = m_pParas->m_paraEstimates[nRow].m_strTtripEnd_Bin;
		}

		if(strText == "")
		{
			strText = "--";
		}
		else
		{
			CString strBin = strText.Mid(0, strText.Find("$"));
			CString strTemp = strText.Mid(strText.GetLength() - 1);
			long nCh = CString_To_long(strBin.Mid(strBin.Find("_") + 1));
			char ch = 'A' + nCh;
			if (strTemp == "0")
			{
				strText = /*"����"*/g_sLangTxt_Native_BinX;
				strText += ch;
				strText += " 1->0";
			}
			else
			{
				strText = /*"����"*/g_sLangTxt_Native_BinX;
				strText += ch;
				strText +=" 0->1";
			}
		}

		long nIndex = pCbbStatesBin->findText(strText);
		if(nIndex == -1)
		{
			nIndex = 0;
		}
		pCbbStatesBin->setCurrentIndex(nIndex);
	}
	setCellWidget(nRow, nCol, pCbbStatesBin);

	ComboxModelStyle(pCbbStatesBin);
}

void StateEstimateGrid::ComboxModelStyle(QComboBox *pCombox)
{
	pCombox->setEditable(true);
	pCombox->lineEdit()->setAlignment(Qt::AlignCenter);
	pCombox->lineEdit()->setReadOnly(true);
	pCombox->lineEdit()->setMouseTracking(true);
	pCombox->lineEdit()->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	pCombox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);
}

void StateEstimateGrid::InitStateData(long nIndexEstimate)
{
	QComboBox* pCbbStatesStart_State = new QComboBox(this);
	QComboBox* pCbbStatesEnd_State = new QComboBox(this);
	for(int i = 0; i < m_pParas->m_nStateNumbers; i++)
	{
		tmt_StatePara* pPara = &m_pParas->m_paraState[i];
		if(pPara->m_bSelected)
		{
			CString strName = pPara->m_strName;
			if(strName.GetLength())
			{
				pCbbStatesStart_State->addItem(strName);
				pCbbStatesEnd_State->addItem(strName);
			}
			else
			{
				xlang_GetLangStrByFile(strName, "sState");
				strName += QString::number(i + 1);
				pCbbStatesStart_State->addItem(strName);
				pCbbStatesEnd_State->addItem(strName);
				//strcpy(pPara->m_strName, strName.GetString());//20230911 suyang ���ṹ�帳ֵ�ᵼ���ڲ���ʱ״̬����ظ�
			}
		}
	}
	pCbbStatesStart_State->addItem(/*"���봥��"*/g_sLangTxt_StateEstimate_BinTrigger);
	pCbbStatesEnd_State->addItem(/*"���봥��"*/g_sLangTxt_StateEstimate_BinTrigger);

	CString strText = m_pParas->m_paraEstimates[nIndexEstimate].m_strTtripBegin_State;
	if(strText == "BinTrig")
	{
		strText = /*"���봥��"*/g_sLangTxt_StateEstimate_BinTrigger;
	}
	else
	{
		strText.Format("״̬%d", CString_To_long(strText.Mid(6)) + 1);
	}
	long nIndex = pCbbStatesStart_State->findText(strText);
	if(nIndex == -1)
	{
		nIndex = 0;
	}
	pCbbStatesStart_State->setCurrentIndex(nIndex);
	InitStateBin(pCbbStatesStart_State->currentText(), nIndexEstimate, 3);
	strText = m_pParas->m_paraEstimates[nIndexEstimate].m_strTtripEnd_State;
	if(strText == "BinTrig")
	{
		strText = /*"���봥��"*/g_sLangTxt_StateEstimate_BinTrigger;
	}
	else
	{
		strText.Format("״̬%d", CString_To_long(strText.Mid(6)) + 1);	
	}
	nIndex = pCbbStatesEnd_State->findText(strText);
	if(nIndex == -1)
	{
		nIndex = 0;
	}
	pCbbStatesEnd_State->setCurrentIndex(nIndex);
	InitStateBin(pCbbStatesEnd_State->currentText(), nIndexEstimate, 5);

	setCellWidget(nIndexEstimate, 2, pCbbStatesStart_State);
	setCellWidget(nIndexEstimate, 4, pCbbStatesEnd_State);

	connect(pCbbStatesStart_State, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_StateBinChanged(const QString &)));
	connect(pCbbStatesEnd_State, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_StateBinChanged(const QString &)));

	ComboxModelStyle(pCbbStatesStart_State);
	ComboxModelStyle(pCbbStatesEnd_State);
}

void StateEstimateGrid::InitData(tmt_StateParas* pParas)
{
	m_pParas = pParas;
	//��ȡ״̬��
	for (int i = 0; i < 10; i++)
	{
		InitStateData(i);

		CString strText;

		QComboBox *pCbbError = new QComboBox(this);
		pCbbError->addItem(/*"�������"*/g_sLangTxt_StateEstimate_AbsError);
		pCbbError->addItem(/*"������"*/g_sLangTxt_StateEstimate_RelError);
		strText = g_sLangTxt_StateEstimate_AbsError +"or"+g_sLangTxt_StateEstimate_RelError;

		pCbbError->addItem(/*"������or�������"*/strText);
		strText = g_sLangTxt_StateEstimate_AbsError +"&"+g_sLangTxt_StateEstimate_RelError;

		pCbbError->addItem(/*"������&�������"*/strText);
		pCbbError->addItem(/*"������"*/g_sLangTxt_StateEstimate_CombinationError);

		CString strActTime;
		xlang_GetLangStrByFile(strActTime, "Native_ActionTime");

		//cl20230726 QSttCheckBox����
		QWidget *UserWidget = new QWidget();
		QHBoxLayout *UserLayout = new QHBoxLayout();
		QSttCheckBox* pCbUser = new QSttCheckBox(this);
		UserLayout->addWidget(pCbUser);
		UserLayout->setMargin(0);
		UserLayout->setAlignment(pCbUser, Qt::AlignCenter);  
		UserWidget->setLayout(UserLayout);
		setCellWidget(i, 0, UserWidget);
		
		setItem(i, 1, new QTableWidgetItem(strActTime));
		item(i, 1)->setFlags(item(i, 1)->flags() & ~Qt::ItemIsEditable);

		setCellWidget(i, 6, pCbbError);
		pCbUser->setChecked(pParas->m_paraEstimates[i].m_bUseError);
		pCbbError->setCurrentIndex(pParas->m_paraEstimates[i].m_nErrorLogic);
		setItem(i, 7, new QTableWidgetItem(QString::number(pParas->m_paraEstimates[i].m_fActT_RelErr)));
		setItem(i, 8, new QTableWidgetItem(QString::number(pParas->m_paraEstimates[i].m_fActT_AbsErr)));
		setItem(i, 9, new QTableWidgetItem(QString::number(pParas->m_paraEstimates[i].m_fTset)));

		item(i,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		item(i,7)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		item(i,8)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		item(i,9)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

		ComboxModelStyle(pCbbError);

 		QString str = pCbbError->currentText();	
		CbbErrorType(i,str);

		connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
		connect(pCbbError, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	}
}

void StateEstimateGrid::CbbErrorType(int nIndex, CString strText)
{
	if (strText==g_sLangTxt_StateEstimate_AbsError)
	{
		item(nIndex, 7)->setFlags(item(nIndex, 7)->flags() & ~Qt::ItemIsEditable);
		item(nIndex, 8)->setFlags(item(nIndex, 8)->flags() &  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
	}
	else if (strText==g_sLangTxt_StateEstimate_RelError)
	{
		item(nIndex, 7)->setFlags(item(nIndex, 7)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		item(nIndex, 8)->setFlags(item(nIndex, 8)->flags() & ~Qt::ItemIsEditable);
	}
	else
	{
		item(nIndex, 7)->setFlags(item(nIndex, 7)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		item(nIndex, 8)->setFlags(item(nIndex, 8)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
	}
}

void StateEstimateGrid::slot_cmbErrorChanged(const QString& strText)
{
	int nRow = currentRow();

	CbbErrorType(nRow,strText);
}

void StateEstimateGrid::slot_OnCellChanged(int row,int col)
{
	if (row  <  0)
	{
		return;
	}

	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));

	QTableWidgetItem  *pItem  = this->item(row,col);

	if (pItem == NULL)
	{
		return;
	} 

	QString str = pItem->text();
	float fv =str.toFloat();

	if(col==7)//������
	{
		fv=setLimit(0,100,fv);
		pItem->setText(QString::number(fv));
	}

	if(col==8)//�������
	{
		fv=setLimit(0,200,fv);
		pItem->setText(QString::number(fv));
	}

	if(col==9)//����ֵ
	{		
		fv=setLimit(0,999,fv);
		pItem->setText(QString::number(fv));
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

bool StateEstimateGrid::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = FALSE;
		return true;
	}

	return QTableWidget::eventFilter(obj,event);
}

void StateEstimateGrid::mousePressEvent(QMouseEvent * event)
{
	if (m_bRunning)
	{
		QTableWidget::mousePressEvent(event);
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
	QApplication::postEvent(this,pEvent);
	QTableWidget::mousePressEvent(event);
}


StateEstimateDlg::StateEstimateDlg(tmt_StateParas* pParas, QWidget* parent) : QDialog(parent)
{
	m_pGrid = NULL;
	m_pParas = pParas;
	InitUI();
}

StateEstimateDlg::~StateEstimateDlg()
{

}

void StateEstimateDlg::InitUI()
{
	CString strTitle = /*"�������"*/g_sLangTxt_StateEstimate_ResultEstimate;
	setWindowTitle(strTitle);
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);

	QVBoxLayout* pVLayout = new QVBoxLayout(this);
	setLayout(pVLayout);

	QHBoxLayout* pHLayout = new QHBoxLayout(this);
	m_pGrid = new StateEstimateGrid(10, 10, this);
	m_pGrid->InitGrid();
	m_pGrid->InitData(m_pParas);
	pHLayout->addWidget(m_pGrid);
	pVLayout->addLayout(pHLayout);
	
	CString strText;
	pHLayout = new QHBoxLayout(this);
	pHLayout->addStretch();
	QPushButton* pBtn = new QPushButton(this);
	xlang_GetLangStrByFile(strText, "sOK");
	pBtn->setText(strText);
	connect(pBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	pHLayout->addWidget(pBtn);
	pBtn = new QPushButton(this);
	xlang_GetLangStrByFile(strText, "sCancel");
	pBtn->setText(strText);
	connect(pBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
	pHLayout->addWidget(pBtn);
	pHLayout->addStretch();
	pVLayout->addLayout(pHLayout);

	resize(1000, 520);
}

CString StateEstimateDlg::SaveState(long nRow, long nCol)
{
	QComboBox* pCbbState = (QComboBox*)m_pGrid->cellWidget(nRow, nCol);
	long nIndex = pCbbState->currentIndex();
	CString strText;
	if(nIndex == pCbbState->count() - 1)
	{
		if(nCol == 2)
		{
			strText = strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripBegin_State, "BinTrig");
		}
		else
		{
			strText = strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripEnd_State, "BinTrig");
		}
	}
	else
	{
		strText = "state_" + QString::number(nIndex);
		if(nCol == 2)
		{
			strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripBegin_State, strText.GetString());
		}
		else
		{
			strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripEnd_State, strText.GetString());
		}
	}
	return strText;
}

CString StateEstimateDlg::SaveStateBin(long nRow, long nCol)
{
	QComboBox* pCbbBin = (QComboBox*)m_pGrid->cellWidget(nRow, nCol);
	CString strBin = pCbbBin->currentText();
	if(strBin.GetLength())
	{
		if(strBin == "--")
		{
			if(nCol == 3)
			{
				strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripBegin_Bin, "");
			}
			else
			{
				strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripEnd_Bin, "");
			}
			return "";
		}

		strBin = strBin.Mid(2);

		int i = 0;
		for (; i < MAX_BINARYIN_COUNT; i++)
		{
			char ch = 'A' + i;
			CString strTemp;
			strTemp += ch;
			if(strTemp == strBin.Mid(0, 1))
			{
				break;
			}
		}

		CString str1;
		str1.Format("ActBin_%d", i);
		CString str2 = "$" + strBin.Mid(strBin.GetLength() - 1);
		CString strText = str1 + str2;
		if(nCol == 3)
		{
			strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripBegin_Bin, strText.GetString());
		}
		else
		{
			strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripEnd_Bin, strText.GetString());
		}

		return strText;
	}
	else
	{
		if(nCol == 3)
		{
			strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripBegin_Bin, "");
		}
		else
		{
			strcpy(m_pParas->m_paraEstimates[nRow].m_strTtripEnd_Bin, "");
		}
	}
	return "";
};

void StateEstimateDlg::slot_btnOK_Clicked()
{
	for (int i = 0; i < 10; i++)
	{
		QWidget* pUseWidget = (QWidget*)m_pGrid->cellWidget(i, 0);
		QSttCheckBox* pCbUse = (QSttCheckBox*)pUseWidget->children().at(1); //cl20230808
		m_pParas->m_paraEstimates[i].m_bUseError = pCbUse->isChecked();

		SaveState(i, 2);
		SaveStateBin(i, 3);
		SaveState(i, 4);
		SaveStateBin(i, 5);

		QComboBox* pCbbErrorType = (QComboBox*)m_pGrid->cellWidget(i, 6);
		m_pParas->m_paraEstimates[i].m_nErrorLogic = pCbbErrorType->currentIndex();

		m_pParas->m_paraEstimates[i].m_fActT_RelErr = m_pGrid->item(i, 7)->text().toFloat();
		m_pParas->m_paraEstimates[i].m_fActT_AbsErr = m_pGrid->item(i, 8)->text().toFloat();
		m_pParas->m_paraEstimates[i].m_fTset = m_pGrid->item(i, 9)->text().toFloat();
	}

	accept();
}

void StateEstimateDlg::slot_btnCancel_Clicked()
{
	reject();
}
#include "ThreeRecloseCommonParasDlg.h"
#include "../SttTestCntrFrameBase.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"


QThreeRecloseCommonParasDlg::QThreeRecloseCommonParasDlg(CDataGroup* pParas, QWidget* parent ): QDialog(parent)
{	
	m_pParas = pParas;
	setWindowTitle(_T("通用参数"));
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	resize(370, 570);

	InitUI();
	InitConnections();
	InitData();
}

QThreeRecloseCommonParasDlg::~QThreeRecloseCommonParasDlg()
{

}

void QThreeRecloseCommonParasDlg::InitUI()
{
	CString strText;
	m_pTableWidget = new QTabWidget(this);
	m_pTableWidget->setFont(*g_pSttGlobalFont);
	QWidget *pCommonParasWidget = new QWidget(this); 
    m_pTableWidget->addTab(pCommonParasWidget, "g_sLangTxt_Gradient_CommonParas");
	QLabel *pLabFaultTrigMode = new QLabel(this); 
	strText = _T("故障触发方式:");
	pLabFaultTrigMode->setText(strText);
	pLabFaultTrigMode->setFont(*g_pSttGlobalFont);
	QLabel *pLabPTPos = new QLabel(this);
	strText = _T("TV安装位置:");
	pLabPTPos->setText(strText);
	pLabPTPos->setFont(*g_pSttGlobalFont);
	QLabel *pLabCTPos = new QLabel(this); 
	strText = _T("TA正极性:");
	pLabCTPos->setText(strText);
	pLabCTPos->setFont(*g_pSttGlobalFont);
	QLabel *pLabLoadCur = new QLabel(this); 
	strText = _T("负荷电流(A):");
	pLabLoadCur->setText(strText);
	pLabLoadCur->setFont(*g_pSttGlobalFont);
	QLabel *pLabLoadAng = new QLabel(this); 
	strText = _T("负荷角度(°):");
	pLabLoadAng->setText(strText);
	pLabLoadAng->setFont(*g_pSttGlobalFont);
	QLabel *pLabSimulateBreakerDelay = new QLabel(this);
	strText = _T("断路器模拟:");
	pLabSimulateBreakerDelay->setText(strText);
	pLabSimulateBreakerDelay->setFont(*g_pSttGlobalFont);
	QLabel *pLabBrkBreakTime = new QLabel(this);  
	strText = _T("分闸时间(ms):");
	pLabBrkBreakTime->setText(strText);
	pLabBrkBreakTime->setFont(*g_pSttGlobalFont);
	QLabel *pLabBrkCloseTime = new QLabel(this);    
	strText = _T("合闸时间(ms):");
	pLabBrkCloseTime->setText(strText);
	pLabBrkCloseTime->setFont(*g_pSttGlobalFont);


	m_pCmbFaultTrigMode = new QComboBox(this);   //故障触发方式
	m_pCmbFaultTrigMode->setFont(*g_pSttGlobalFont);
    m_pCmbFaultTrigMode->addItem("时间触发");
    m_pCmbFaultTrigMode->addItem("手动触发");
    m_pCmbFaultTrigMode->addItem("开入量触发");
	m_pCmbPTPos = new QComboBox(this);			  //TV安装位置
	m_pCmbPTPos->setFont(*g_pSttGlobalFont);
    m_pCmbPTPos->addItem("母线侧");
    m_pCmbPTPos->addItem("线路侧");
	m_pCmbCTPos = new QComboBox(this);	          //TA正极性
	m_pCmbCTPos->setFont(*g_pSttGlobalFont);
    m_pCmbCTPos->addItem("指向母线");
    m_pCmbCTPos->addItem("指向线路");

	m_pEditLoadCur = new QSttLineEdit(this);
	m_pEditLoadCur->setFont(*g_pSttGlobalFont);
	m_pEditLoadAng = new QSttLineEdit(this);
	m_pEditLoadAng->setFont(*g_pSttGlobalFont);
	m_pEditBrkBreakTime = new QSttLineEdit(this);  
	m_pEditBrkBreakTime->setFont(*g_pSttGlobalFont);
	m_pEditBrkCloseTime = new QSttLineEdit(this);   
	m_pEditBrkCloseTime->setFont(*g_pSttGlobalFont);
	

	m_pCmbSimulateBreakerDelay = new QComboBox(this);//断路器模拟
	m_pCmbSimulateBreakerDelay->setFont(*g_pSttGlobalFont);
    m_pCmbSimulateBreakerDelay->addItem("不模拟");
    m_pCmbSimulateBreakerDelay->addItem("模拟");

	QGridLayout *pCommonParasLayout = new QGridLayout();
	pCommonParasWidget->setLayout(pCommonParasLayout);
	pCommonParasLayout->addWidget(pLabFaultTrigMode, 0, 0);
	pCommonParasLayout->addWidget(pLabPTPos, 1, 0);
	pCommonParasLayout->addWidget(pLabCTPos, 2, 0);
	pCommonParasLayout->addWidget(pLabLoadCur, 3, 0);
	pCommonParasLayout->addWidget(pLabLoadAng, 4, 0);
	pCommonParasLayout->addWidget(pLabSimulateBreakerDelay, 5, 0);
	pCommonParasLayout->addWidget(pLabBrkBreakTime, 6, 0);
	pCommonParasLayout->addWidget(pLabBrkCloseTime, 7, 0);
	pCommonParasLayout->addWidget(m_pCmbFaultTrigMode, 0, 1);
	pCommonParasLayout->addWidget(m_pCmbPTPos, 1, 1);
	pCommonParasLayout->addWidget(m_pCmbCTPos, 2, 1);
	pCommonParasLayout->addWidget(m_pEditLoadCur, 3, 1);
	pCommonParasLayout->addWidget(m_pEditLoadAng, 4, 1);
	pCommonParasLayout->addWidget(m_pCmbSimulateBreakerDelay, 5, 1);
	pCommonParasLayout->addWidget(m_pEditBrkBreakTime, 6, 1);
	pCommonParasLayout->addWidget(m_pEditBrkCloseTime, 7, 1);

	
	QWidget *pBinWidget = new QWidget(this); 
	m_pTableWidget->addTab(pBinWidget, _T("开入量"));
	QGridLayout *pBinLayout = new QGridLayout();
	pBinWidget->setLayout(pBinLayout);
	QStringList BinList;
	BinList  << _T("跳闸") << _T("重合");
    QLabel *pLabBinSelect= new QLabel(_T("开入选择"),this);
	pLabBinSelect->setFont(*g_pSttGlobalFont);
    QLabel *pLabBinA= new QLabel(_T("开入A"),this);
	pLabBinA->setFont(*g_pSttGlobalFont);
    QLabel *pLabBinB= new QLabel(_T("开入B"),this);
	pLabBinB->setFont(*g_pSttGlobalFont);
    QLabel *pLabBinC= new QLabel(_T("开入C"),this);
	pLabBinC->setFont(*g_pSttGlobalFont);
    QLabel *pLabBinD= new QLabel(_T("开入D"),this);
	pLabBinD->setFont(*g_pSttGlobalFont);
    QLabel *pLabBinE= new QLabel(_T("开入E"),this);
	pLabBinE->setFont(*g_pSttGlobalFont);
    QLabel *pLabBinF= new QLabel(_T("开入F"),this);
	pLabBinF->setFont(*g_pSttGlobalFont);
    QLabel *pLabBinG= new QLabel(_T("开入G"),this);
	pLabBinG->setFont(*g_pSttGlobalFont);
    QLabel *pLabBinH= new QLabel(_T("开入H"),this);
	pLabBinH->setFont(*g_pSttGlobalFont);

	m_pCmbBinSelect = new QComboBox(this);           //开入量选择
	m_pCmbBinSelect->setFont(*g_pSttGlobalFont);
	m_pCmbBinSelect->addItem(_T("开入A-B-C-D"));
	m_pCmbBinSelect->addItem(_T("开入E-F-G-H"));

	pBinLayout->addWidget(pLabBinSelect, 0, 0);
	pBinLayout->addWidget(pLabBinA, 1, 0);
	pBinLayout->addWidget(pLabBinB, 2, 0);
	pBinLayout->addWidget(pLabBinC, 3, 0);
	pBinLayout->addWidget(pLabBinD, 4, 0);
	pBinLayout->addWidget(pLabBinE, 5, 0);
	pBinLayout->addWidget(pLabBinF, 6, 0);
	pBinLayout->addWidget(pLabBinG, 7, 0);
	pBinLayout->addWidget(pLabBinH, 8, 0);

	QStringList oList;
	oList << _T("A") << _T("B") << _T("C")<< _T("R") << _T("E") << _T("F") <<  _T("G")<< _T("H");
	pBinLayout->addWidget(m_pCmbBinSelect, 0, 1);

	int nBinCount = g_nBinCount;
	if (g_nBinCount > 8)
	{
		nBinCount = 8;//dingxy 20241115 防止崩溃
	}
	for (int i=0; i<nBinCount; i++)
	{
		QComboBox *pCmbBin = new QComboBox(this);            
		pCmbBin->setFont(*g_pSttGlobalFont);
		pCmbBin->addItems(BinList);
		m_pBinComboBoxList.append(pCmbBin);
		pBinLayout->addWidget(pCmbBin, i+1, 1);
		pCmbBin->setObjectName(oList.at(i));
		GetComboxValue(pCmbBin,oList.at(i),true);
	}


	QStringList BoutList;
	BoutList  << _T("断开") << _T("闭合");
	QWidget *pBoutWidget = new QWidget(this); 
	m_pTableWidget->addTab(pBoutWidget, _T("开出量"));
	QGridLayout *pBoutLayout = new QGridLayout();
	pBoutWidget->setLayout(pBoutLayout);
	for (int i = 0; i < g_nBoutCount; i++)
	{
		strText.Format(_T("开出%d"), i+1);
		QLabel *pLabBout = new QLabel(this);
		pLabBout->setFont(*g_pSttGlobalFont);
		pLabBout->setText(strText);
		QComboBox *pCmbBout = new QComboBox(this);  
		pCmbBout->setFont(*g_pSttGlobalFont);
		pCmbBout->addItems(BoutList);
		pBoutLayout->addWidget(pLabBout, i+1, 0);
		pBoutLayout->addWidget(pCmbBout, i+1, 1);
		m_pBoutComboBoxList.append(pCmbBout);
		strText.Format(_T("_B0%d"), i+1);
		pCmbBout->setObjectName(strText);
		GetComboxValue(pCmbBout,strText);
	}

	QPushButton* pOKBtn = new QPushButton(this);
	strText = _T("确定");
	pOKBtn->setFont(*g_pSttGlobalFont);
	pOKBtn->setText(strText);
	QPushButton* pCancelBtn = new QPushButton(this);
	strText = _T("取消");
	pCancelBtn->setFont(*g_pSttGlobalFont);
	pCancelBtn->setText(strText);
	QHBoxLayout* pOkCancel_HBoxLayout = new QHBoxLayout;
	pOkCancel_HBoxLayout->addStretch();
	pOkCancel_HBoxLayout->addWidget(pOKBtn);
	pOkCancel_HBoxLayout->addSpacing(10);
	pOkCancel_HBoxLayout->addWidget(pCancelBtn);
	pOkCancel_HBoxLayout->addStretch();
	pOkCancel_HBoxLayout->setDirection(QBoxLayout::LeftToRight);

	QVBoxLayout* pMainVLayout = new QVBoxLayout(this);
	pMainVLayout->addWidget(m_pTableWidget);
	pMainVLayout->addLayout(pOkCancel_HBoxLayout);
	setLayout(pMainVLayout);


	connect(pOKBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	connect(pCancelBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
}

void QThreeRecloseCommonParasDlg::GetLineEditValue( QSttLineEdit * pLineEdit,const CString strID,long nPrecssion)
{
	CDvmData* pCurData = (CDvmData*)m_pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	pLineEdit->setText(QString::number(fValue,'f',nPrecssion));
}


void QThreeRecloseCommonParasDlg::GetComboxValue( QComboBox * pComboBox,const CString strID,bool b /*= false*/ )
{
	CDvmData* pCurData = (CDvmData*)m_pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	long nIndex = CString_To_long(pCurData->m_strValue);
	if (nIndex < 0)
	{
		return;
	}
	if (b)
	{
		nIndex = nIndex - 1;
	}
	pComboBox->setCurrentIndex(nIndex);
}

void QThreeRecloseCommonParasDlg::InitData()
{
	m_pCmbFaultTrigMode->setObjectName(_T("FaultTrigMode"));
	GetComboxValue(m_pCmbFaultTrigMode,_T("FaultTrigMode"));
	m_pCmbPTPos->setObjectName(_T("PTPosition"));
	GetComboxValue(m_pCmbPTPos,_T("PTPosition"));
	m_pCmbCTPos->setObjectName(_T("CTPos"));
	GetComboxValue(m_pCmbCTPos,_T("CTPos"));
	m_pCmbSimulateBreakerDelay->setObjectName(_T("SimulateBreakerDelay"));
	GetComboxValue(m_pCmbSimulateBreakerDelay,_T("SimulateBreakerDelay"));
	m_pCmbBinSelect->setObjectName(_T("BinSelect"));
	GetComboxValue(m_pCmbBinSelect,_T("BinSelect"));
	slot_CmbBinSelect(m_pCmbBinSelect->currentIndex());

	m_pEditLoadCur->setObjectName(_T("ILoad"));
	GetLineEditValue(m_pEditLoadCur,_T("ILoad"),3);
	m_pEditLoadAng->setObjectName(_T("ILoadPh"));
	GetLineEditValue(m_pEditLoadAng,_T("ILoadPh"),1);
	m_pEditBrkBreakTime->setObjectName(_T("BrkBreakTime"));
	GetLineEditValue(m_pEditBrkBreakTime,_T("BrkBreakTime"),0);
	m_pEditBrkCloseTime->setObjectName(_T("BrkCloseTime"));
	GetLineEditValue(m_pEditBrkCloseTime,_T("BrkCloseTime"),0);
	
	slot_CmbBinSelect(m_pCmbBinSelect->currentIndex());
	slot_CmbSimulateBreakerDelay(m_pCmbSimulateBreakerDelay->currentIndex());
}

void QThreeRecloseCommonParasDlg::InitConnections()
{
	//connect(m_pCmbFaultTrigMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbFaultTrigMode(int)));
	//connect(m_pCmbPTPos,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbPTPos(int)));
	//connect(m_pCmbCTPos,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbCTPos(int)));
	connect(m_pCmbSimulateBreakerDelay,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbSimulateBreakerDelay(int)));
	connect(m_pCmbBinSelect,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbBinSelect(int)));


	connect(m_pEditLoadCur,SIGNAL(editingFinished()),this,SLOT(slot_EditLoadCur()));
	connect(m_pEditLoadAng,SIGNAL(editingFinished()),this,SLOT(slot_EditLoadAng()));
	connect(m_pEditBrkBreakTime,SIGNAL(editingFinished()),this,SLOT(slot_EditBrkBreakTime()));
	connect(m_pEditBrkCloseTime,SIGNAL(editingFinished()),this,SLOT(slot_EditCloseBreakTime()));
}

void QThreeRecloseCommonParasDlg::slot_btnOK_Clicked()
{
	m_pParas->SetDataValue(m_pCmbFaultTrigMode->objectName(),long(m_pCmbFaultTrigMode->currentIndex()));
	m_pParas->SetDataValue(m_pCmbPTPos->objectName(),long(m_pCmbPTPos->currentIndex()));
	m_pParas->SetDataValue(m_pCmbCTPos->objectName(),long(m_pCmbCTPos->currentIndex()));
	m_pParas->SetDataValue(m_pCmbSimulateBreakerDelay->objectName(),long(m_pCmbSimulateBreakerDelay->currentIndex()));
	m_pParas->SetDataValue(m_pCmbBinSelect->objectName(),long(m_pCmbBinSelect->currentIndex()));

	for (int i = 0; i < m_pBinComboBoxList.size(); ++i) 
	{
		m_pParas->SetDataValue(m_pBinComboBoxList[i]->objectName(),long(m_pBinComboBoxList[i]->currentIndex()+1));
	}
	for (int i = 0; i < m_pBoutComboBoxList.size(); ++i) 
	{
		m_pParas->SetDataValue(m_pBoutComboBoxList[i]->objectName(),long(m_pBoutComboBoxList[i]->currentIndex()));
	}

	m_pParas->SetDataValue(m_pEditLoadCur->objectName(),m_pEditLoadCur->text());
	m_pParas->SetDataValue(m_pEditLoadAng->objectName(),m_pEditLoadAng->text());
	m_pParas->SetDataValue(m_pEditBrkBreakTime->objectName(),m_pEditBrkBreakTime->text());
	m_pParas->SetDataValue(m_pEditBrkCloseTime->objectName(),m_pEditBrkCloseTime->text());


	accept();
}

void QThreeRecloseCommonParasDlg::slot_btnCancel_Clicked()
{
	close();
}

void QThreeRecloseCommonParasDlg::slot_CmbSimulateBreakerDelay( int nIndex )
{
	if (nIndex == 0)
	{
		m_pEditBrkBreakTime->setEnabled(false);
		m_pEditBrkCloseTime->setEnabled(false);
	}
	if (nIndex == 1)
	{
		m_pEditBrkBreakTime->setEnabled(true);
		m_pEditBrkCloseTime->setEnabled(true);
	}
}

void QThreeRecloseCommonParasDlg::slot_CmbBinSelect( int nIndex )
{
	if (nIndex == 0)
	{
		for (int i = 0; i < m_pBinComboBoxList.size(); ++i) 
		{
			if (i < 4) 
			{
				m_pBinComboBoxList[i]->setEnabled(true);  
			} 
			else 
			{
				m_pBinComboBoxList[i]->setEnabled(false); 
			}
		}             
	}
	if (nIndex == 1)
	{
		for (int i = 0; i < m_pBinComboBoxList.size(); ++i) 
		{
			if (i < 4) 
			{
				m_pBinComboBoxList[i]->setEnabled(false);  
			} 
			else 
			{
				m_pBinComboBoxList[i]->setEnabled(true); 
			}
		}    
	}
}

void QThreeRecloseCommonParasDlg::slot_EditLoadCur()
{
	float fv = m_pEditLoadCur->text().toFloat();
	fv = setLimit(0,20,fv);
	m_pEditLoadCur->setText(QString::number(fv, 'f', 3));
}

void QThreeRecloseCommonParasDlg::slot_EditLoadAng()
{
	float fv = m_pEditLoadAng->text().toFloat();
	fv = setLimit(-360.0,360.0,fv);
	m_pEditLoadAng->setText(QString::number(fv, 'f', 1));
}

void QThreeRecloseCommonParasDlg::slot_EditBrkBreakTime()
{
	float fv = m_pEditBrkBreakTime->text().toFloat();
	fv = setLimit(0,999999,fv);
	m_pEditBrkBreakTime->setText(QString::number(fv));
}

void QThreeRecloseCommonParasDlg::slot_EditCloseBreakTime()
{
	float fv = m_pEditBrkCloseTime->text().toFloat();
	fv = setLimit(0,999999,fv);
	m_pEditBrkCloseTime->setText(QString::number(fv));
}


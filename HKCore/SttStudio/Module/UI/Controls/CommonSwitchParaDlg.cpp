#include "CommonSwitchParaDlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>

#include "../../XLangResource_Native.h"


CommonSwitchParaDlg::CommonSwitchParaDlg(QWidget *parent): QDialog(parent)
{
	initUI(); 
	m_pLogicOr = NULL;
	m_pLogicAnd = NULL;
	setWindowFlags(Qt::WindowCloseButtonHint);
}

CommonSwitchParaDlg::~CommonSwitchParaDlg()
{
	
}

void CommonSwitchParaDlg::initUI()
{
	QFont font;
	font.setFamily(/*tr("宋体")*/g_sLangTxt_LetterForm);
	font.setPointSize(18);
	setFont(font);

	setWindowTitle(/*tr("开关量设置")*/g_sLangTxt_Native_Switch);
}

void CommonSwitchParaDlg::copyConfig(tmt_BinaryConfig*pSrcCfg, tmt_BinaryConfig*pDstCfg)
{
	if (pSrcCfg == NULL || pDstCfg == NULL)
	{
		return;
	}

	memcpy(pDstCfg,pSrcCfg,sizeof(tmt_BinaryConfig));
}

bool CommonSwitchParaDlg::compareConfig(tmt_BinaryConfig*pSrcCfg, tmt_BinaryConfig*pDstCfg)
{
	int i=0;

	if (pSrcCfg->m_nBinLogic != pDstCfg->m_nBinLogic)
	{
		return false;
	}

	for (i=0;i<MAX_BINARYIN_COUNT;i++)
	{
		if (pSrcCfg->m_binIn[i].nSelect != pDstCfg->m_binIn[i].nSelect)
		{
			return false;
		}
	}

	for (i=0;i<MAX_BINARYOUT_COUNT;i++)
	{
		if (pSrcCfg->m_binOut[i].nState != pDstCfg->m_binOut[i].nState)
		{
			return false;
		}
	}
	
	for (i=0;i<MAX_ExBINARY_COUNT;i++)
	{
		if (pSrcCfg->m_binInEx[i].nSelect != pDstCfg->m_binInEx[i].nSelect)
		{
			return false;
		}
	}

	for (i=0;i<MAX_ExBINARY_COUNT;i++)
	{
		if (pSrcCfg->m_binOutEx[i].nState != pDstCfg->m_binOutEx[i].nState)
		{
			return false;
		}
	}
	
	for (i=0;i<MAX_BINARYOUT_COUNT;i++)
	{
		if (pSrcCfg->m_binFaultOut[i].nState != pDstCfg->m_binFaultOut[i].nState)
		{
			return false;
		}
	}

	for (i=0;i<MAX_ExBINARY_COUNT;i++)
	{
		if (pSrcCfg->m_binFaultOutEx[i].nState != pDstCfg->m_binFaultOutEx[i].nState)
		{
			return false;
		}
	}
	
	return true;
}

void CommonSwitchParaDlg::setData(tmt_BinaryConfig *pBinaryCfg,int nInNum,int nOutNum,int nFaultOutNum)
{
	m_pBinaryCfg = pBinaryCfg;
	copyConfig(m_pBinaryCfg,&m_oTempConfig);

	m_nInNum = nInNum;
	if(m_nInNum > MAX_BINARYIN_COUNT)
	{
		m_nInNum = MAX_BINARYIN_COUNT;
	}

	m_nOutNum = nOutNum;
	if(m_nOutNum > MAX_BINARYOUT_COUNT)
	{
		m_nOutNum = MAX_BINARYOUT_COUNT;
	}

	m_nFaultOutNum = nFaultOutNum;
	if(m_nFaultOutNum > MAX_BINARYOUT_COUNT)
	{
		m_nFaultOutNum = MAX_BINARYOUT_COUNT;
	}

	int nGroupNum;
	CString strTemp;

	QGroupBox* groupInBox;

	if (nInNum > 0)
	{
		groupInBox = new QGroupBox(/*tr("开入量设置")*/g_sLangTxt_Native_InputSet,this);
		groupInBox->setObjectName(QString::fromUtf8("groupInBox"));

		QGridLayout* gridInLayout = new QGridLayout();
		gridInLayout->setObjectName(QString::fromUtf8("gridInLayout"));
		gridInLayout->setSpacing(6);
		gridInLayout->setContentsMargins(11, 11, 11, 11);

		
		//横向每5个一组，最底下一行逻辑与、逻辑或
		nGroupNum = (m_nInNum%5 == 0)?(m_nInNum/5):(m_nInNum/5+1);
		CString str1 = _T("开入");
		CString strBinName;
		//前10个开入命名为ABCDEFGHIJ
		char pszBInName[11]="ABCDEFGHIJ";
		for (int i=0;i<nGroupNum;i++)
		{
			for(int j=0;j<5;j++)
			{
				if (i*5+j+1<=m_nInNum)
				{
					if (i*5+j+1 <= 10)
					{
						strTemp.Format("%c",pszBInName[i*5+j]);
					}
					else
					{
						strTemp.Format(_T("%d"),i*5+j+1);
					}
					strBinName = str1 + strTemp;
					m_pChIns[i*5+j] = new QCheckBox(strBinName,groupInBox);
					gridInLayout->addWidget(m_pChIns[i*5+j], i, j, 1, 1);
				}
				else
				{
					break;
				}
			}
		}

		//插入逻辑与、逻辑或
		m_pLogicAnd = new QRadioButton(/*tr("逻辑与")*/g_sLangTxt_Native_LogicAnd,groupInBox);
		m_pLogicOr = new QRadioButton(/*tr("逻辑或")*/g_sLangTxt_Native_LogicOr,groupInBox);
		QHBoxLayout *pHLayAndOr = new QHBoxLayout();
		pHLayAndOr ->addWidget(m_pLogicAnd);
		pHLayAndOr ->addWidget(m_pLogicOr);

		QVBoxLayout *pVLay1=new QVBoxLayout;
		pVLay1->addLayout(gridInLayout);
		pVLay1->addLayout(pHLayAndOr);
		groupInBox->setLayout(pVLay1);
	}

	QGroupBox* groupOutBox;

	if(m_nOutNum > 0)
	{
		if (m_nFaultOutNum > 0)  //没有故障态的话,就叫开出量设置,有故障态就叫常态开出设置 sf 20210812
		{
			groupOutBox = new QGroupBox(/*tr("常态开出设置")*/g_sLangTxt_Native_NormOutputSet,this);
		}
		else
		{
			groupOutBox = new QGroupBox(/*tr("开出量设置")*/g_sLangTxt_Gradient_BoutSet,this);
		}
		groupOutBox->setObjectName(QString::fromUtf8("groupOutBox"));

		QGridLayout* gridOutLayout = new QGridLayout();
		gridOutLayout->setObjectName(QString::fromUtf8("groupOutBox"));
		gridOutLayout->setSpacing(6);
		gridOutLayout->setContentsMargins(11, 11, 11, 11);

		nGroupNum = (m_nOutNum%5 == 0)?(m_nOutNum/5):(m_nOutNum/5+1);
		CString strBoutName;
		CString str2 =/* _T("开出")*/g_sLangTxt_Native_BoutX;

		for (int i=0;i<nGroupNum;i++)
		{
			for(int j=0;j<5;j++)
			{
				if (i*5+j+1<=m_nOutNum)
				{
					strTemp.Format(_T("%d"),i*5+j+1);
					strBoutName = str2 + strTemp;
					m_pChOuts[i*5+j] = new QCheckBox(strBoutName,this);
					gridOutLayout->addWidget(m_pChOuts[i*5+j], i, j, 1, 1);
				}
				else
				{
					break;
				}
			}
		}

		groupOutBox->setLayout(gridOutLayout);
	}

	QGroupBox* groupFaultOutBox; // sf 20210812 add

	if(m_nFaultOutNum > 0)
	{
		groupFaultOutBox = new QGroupBox(/*tr("故障态开出设置")*/g_sLangTxt_Native_FaultOutputSet,this);

		groupFaultOutBox->setObjectName(QString::fromUtf8("groupFaultOutBox"));

		QGridLayout* gridOutLayout = new QGridLayout();
		gridOutLayout->setObjectName(QString::fromUtf8("groupFaultOutBox"));
		gridOutLayout->setSpacing(6);
		gridOutLayout->setContentsMargins(11, 11, 11, 11);

		nGroupNum = (m_nFaultOutNum%5 == 0)?(m_nFaultOutNum/5):(m_nFaultOutNum/5+1);
		CString strBoutName;
		CString str2 = /*_T("开出")*/g_sLangTxt_Native_BoutX;

		for (int i = 0;i < nGroupNum; i++)
		{
			for(int j = 0;j < 5;j++)
			{
				if (i*5+j+1 <= m_nFaultOutNum)
				{
					strTemp.Format(_T("%d"),i*5+j+1);
					strBoutName = str2 + strTemp;
					m_pChFaultOuts[i*5+j] = new QCheckBox(strBoutName,this);
					gridOutLayout->addWidget(m_pChFaultOuts[i*5+j], i, j, 1, 1);
				}
				else
				{
					break;
				}
			}
		}

		groupFaultOutBox->setLayout(gridOutLayout);
	}
		
	m_pbtnOK = new QPushButton(/*tr("确定")*/g_sLangTxt_OK,this);
	m_pbtnOK->setIcon (QPixmap( "./images/Check.png"));
	m_pbtnCancel = new QPushButton(/*tr("取消")*/g_sLangTxt_Cancel,this);
	m_pbtnCancel->setIcon (QPixmap( "./images/Cancel.png"));
	QHBoxLayout *pHLayLast = new QHBoxLayout;
	pHLayLast ->addStretch();
	pHLayLast ->addWidget(m_pbtnOK);
	pHLayLast->addSpacing(20);
	pHLayLast ->addWidget(m_pbtnCancel);
	pHLayLast ->addStretch();

	QVBoxLayout *pVLay=new QVBoxLayout;
	if (m_nInNum > 0)
	{
		pVLay->addWidget(groupInBox);
	}
	
	if (m_nOutNum > 0)
	{
		pVLay->addWidget(groupOutBox);
	}

	if (m_nFaultOutNum > 0)
	{
		pVLay->addWidget(groupFaultOutBox);
	}
	
	pVLay->addLayout(pHLayLast);

	setLayout(pVLay);

	initConnections();
	initParas();
}

void CommonSwitchParaDlg::initParas()
{
// 	m_pbtnOK->setIcon (QPixmap( ":/images/Check.png"));
// 	m_pbtnCancel->setIcon (QPixmap( ":/images/Cancel.png"));

	if (m_pBinaryCfg == NULL)
	{
		return;
	}

	//开入量
	for (int i=0;i<m_nInNum;i++)
	{
		if (m_pBinaryCfg->m_binIn[i].nSelect == 1)
		{
			m_pChIns[i]->setCheckState(Qt::Checked);
		}
		else
		{
			m_pChIns[i]->setCheckState(Qt::Unchecked);
		}
	}
	if (m_nInNum > 0) //存在开入量设置时
	{
		if(m_pBinaryCfg->m_nBinLogic == 1)
		{
			m_pLogicAnd->setChecked(true);
			m_pLogicOr->setChecked(false);
		}
		else
		{
			m_pLogicAnd->setChecked(false);
			m_pLogicOr->setChecked(true);
		}
	}
	

	//开出量
	for (int j=0;j<m_nOutNum;j++)
	{
		if(m_pBinaryCfg->m_binOut[j].nState == 1)
		{
			m_pChOuts[j]->setCheckState(Qt::Checked);
		}
		else
		{
			m_pChOuts[j]->setCheckState(Qt::Unchecked);
		}
	}
	//故障态开出量 sf 20210812 add
	for (int j = 0;j < m_nFaultOutNum;j++)
	{
		if(m_pBinaryCfg->m_binFaultOut[j].nState == 1)
		{
			m_pChFaultOuts[j]->setCheckState(Qt::Checked);
		}
		else
		{
			m_pChFaultOuts[j]->setCheckState(Qt::Unchecked);
		}
	}
}

void CommonSwitchParaDlg::slot_OkClicked()
{
	for (int i=0;i<m_nInNum;i++)
	{
		if (m_pChIns[i]->checkState() == Qt::Checked)
		{
			m_pBinaryCfg->m_binIn[i].nSelect = 1;
		}
		else
		{
			m_pBinaryCfg->m_binIn[i].nSelect = 0;
		}
	}
	if (m_nInNum > 0) //存在开入量设置时
	{
		if(m_pLogicAnd->isChecked())
		{
			m_pBinaryCfg->m_nBinLogic = 1;
		}
		else if (m_pLogicOr->isChecked())
		{
			m_pBinaryCfg->m_nBinLogic = 0;
		}
	}
	
	for (int j=0;j<m_nOutNum;j++)
	{
		if (m_pChOuts[j]->checkState() == Qt::Checked)
		{
			m_pBinaryCfg->m_binOut[j].nState = 1;
		}
		else
		{
			m_pBinaryCfg->m_binOut[j].nState = 0;
		}
	}

	for (int j=0;j<m_nFaultOutNum;j++)
	{
		if (m_pChFaultOuts[j]->checkState() == Qt::Checked)
		{
			m_pBinaryCfg->m_binFaultOut[j].nState = 1;
		}
		else
		{
			m_pBinaryCfg->m_binFaultOut[j].nState = 0;
		}
	}

	if(!compareConfig(m_pBinaryCfg,&m_oTempConfig))
	{
		//g_theSttXTestMngrBaseApp->SetModifyPara();
	}

	close();
}

void CommonSwitchParaDlg::slot_CancelClicked()
{
	close();
}

void CommonSwitchParaDlg::slot_radio_AndStateChanged(bool)
{
	if (m_pBinaryCfg == NULL)
	{
		return;
	}

	if (m_pLogicAnd->isChecked())
	{
		//m_pBinaryCfg->m_nBinLogic = 1; //不保存值,否则点取消的时候会保存上 sf 20210826
		m_pLogicOr->setChecked(false);
	}
	else
	{
		//m_pBinaryCfg->m_nBinLogic = 0;//不保存值,否则点取消的时候会保存上 sf 20210826
		m_pLogicOr->setChecked(true);
	}
}

void CommonSwitchParaDlg::slot_radio_OrStateChanged(bool)
{
	if (m_pBinaryCfg == NULL)
	{
		return;
	}

	if (m_pLogicOr->isChecked())
	{
		//m_pBinaryCfg->m_nBinLogic = 0;//不保存值,否则点取消的时候会保存上 sf 20210826
		m_pLogicAnd->setChecked(false);
	}
	else
	{
		//m_pBinaryCfg->m_nBinLogic = 1;//不保存值,否则点取消的时候会保存上 sf 20210826
		m_pLogicAnd->setChecked(true);
	}
}

void CommonSwitchParaDlg::initConnections()
{
	connect(m_pbtnOK, SIGNAL(clicked()), this, SLOT(slot_OkClicked()));
	connect(m_pbtnCancel, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	if (m_pLogicAnd != NULL)
	{
		connect(m_pLogicAnd, SIGNAL(toggled(bool )), this, SLOT(slot_radio_AndStateChanged(bool)));
	}
	if (m_pLogicOr != NULL)
	{
		connect(m_pLogicOr, SIGNAL(toggled(bool )), this, SLOT(slot_radio_OrStateChanged(bool)));
	}
}

void CommonSwitchParaDlg::keyPressEvent(QKeyEvent *event)
{
	int key = event->key();
	if (key == Qt::Key_Enter||key == Qt::Key_Return)
	{

	}
}
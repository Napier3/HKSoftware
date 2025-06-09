#include "LuminousPowerDlg.h"
#include "../../SttTestCntrFrameBase.h"
#include "../CommonMethod/commonMethod.h"
#include <QHeaderView>
#include "../../../../../Module/API/GlobalConfigApi.h"
#include <QLabel>
#include "../../../XLangResource_Native.h"


QLuminousPowerDlg::QLuminousPowerDlg(QWidget* parent)
: QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	
	m_bHasClosed = FALSE;
	m_pbtnClose = NULL;
	m_pEvenLuminousPowerGrid = NULL;
	m_pOddLuminousPowerGrid =NULL;
	m_pFiberGroup = NULL;
	InitUI();
	InitConnection();

	m_nTimerID = startTimer(1000);
}

QLuminousPowerDlg::~QLuminousPowerDlg()
{
	m_oEvenLuminousPowerList.RemoveAll();
	m_oOddLuminousPowerList.RemoveAll();

	if (m_pFiberGroup != NULL)
	{
		delete m_pFiberGroup;
		m_pFiberGroup = NULL;
	}
}

void QLuminousPowerDlg::InitUI()
{
	CString strTitle; 
	resize(800,500);
	this->setFixedWidth(800);
	this->setFixedHeight(500);
    strTitle = g_sLangTxt_Gradient_OpticalPower; //lcq
	this->setWindowTitle(strTitle);

	m_pMainLayout = new QVBoxLayout(this);
    CString strText=g_sLangTxt_Close; //lcq
	m_pbtnClose=new QPushButton(this);
	xlang_SetLangStrToWidget(m_pbtnClose,"sClose", XLang_Ctrls_QPushButton);
	m_pbtnClose->setFont(*g_pSttGlobalFont);
	m_pbtnClose->setText(strText);
	m_pbtnClose->setFixedWidth(80);
	
	m_pOddLuminousPowerGrid =new QLuminousPowerGrid(this);
	m_pOddLuminousPowerGrid->setFont(*g_pSttGlobalFont);
	m_pOddLuminousPowerGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pOddLuminousPowerGrid->InitGrid();

	m_pEvenLuminousPowerGrid =new QLuminousPowerGrid(this);
	m_pEvenLuminousPowerGrid->setFont(*g_pSttGlobalFont);
	m_pEvenLuminousPowerGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pEvenLuminousPowerGrid->InitGrid();

	QGridLayout* pLayout = new QGridLayout(this);
    pLayout->addWidget(m_pEvenLuminousPowerGrid,0,0);
	pLayout->addWidget(m_pOddLuminousPowerGrid,0,1);

	m_pCloseLayout=new QHBoxLayout(this);
	m_pCloseLayout->addStretch();
	m_pCloseLayout->addWidget(m_pbtnClose);
	m_pMainLayout->addLayout(pLayout);
	m_pMainLayout->addLayout(m_pCloseLayout);
	setLayout(m_pMainLayout);
}

void QLuminousPowerDlg::InitConnection()
{
	connect(m_pbtnClose,SIGNAL(clicked()), this, SLOT(slot_CloseClicked()));
}

void QLuminousPowerDlg::slot_CloseClicked()
{
	m_bHasClosed = TRUE;
//	ExitHideKeyboardWidget();
	close();
}

void QLuminousPowerDlg::InitData(CDataGroup *pDataGroup)
{
	m_pFiberGroup = pDataGroup;
	long nEvenIndex = 0;
	long nOddIndex = 0;
	POS pos=pDataGroup->GetHeadPosition();
    CDvmData *pDvmData=NULL;
	long nIndex=0;
    //CString strName;
    //2024-7-26 wuxinyi 修改光功率表格中的光口名称乱码
    QString strName;
	while(pos)
	{
		pDvmData=(CDvmData*)pDataGroup->GetNext(pos);
		if (nIndex%2==0)
		{	
            //strName.Format(g_sLangTxt_Gradient_POpticalPort.GetString(),nIndex+1); //lcq
            strName = g_sLangTxt_IEC_FI + QString("%1").arg(nIndex+1);
			pDvmData->m_strName = strName;
			m_oEvenLuminousPowerList.AddNewChild(pDvmData);
			nEvenIndex++;
		}
		else
		{
            //strName.Format(g_sLangTxt_Gradient_POpticalPort.GetString(),nIndex+1); //lcq
            strName = g_sLangTxt_IEC_FI + QString("%1").arg(nIndex+1);
			pDvmData->m_strName = strName;
			m_oOddLuminousPowerList.AddNewChild(pDvmData);
			nOddIndex++;
		}
		nIndex++;
	}
    m_pOddLuminousPowerGrid->ShowDatas(&m_oOddLuminousPowerList); 
	m_pEvenLuminousPowerGrid->ShowDatas(&m_oEvenLuminousPowerList); 
	
// 	UpdateStatusPic(m_pEvenLuminousPowerGrid,&m_oEvenLuminousPowerList);
//     UpdateStatusPic(m_pOddLuminousPowerGrid,&m_oOddLuminousPowerList);
}

void QLuminousPowerDlg::UpdateStatusPic(QLuminousPowerGrid* pGrid,CExBaseList *pList)
{
#ifdef _PSX_QT_WINDOWS_
		CString strPicPath1 = _P_GetResourcePath();
		strPicPath1 +="circle_green.png";

		CString strPicPath2 = _P_GetResourcePath();
		strPicPath2 +="circle_black.png";
#else
		CString strPicPath1 = ":/ctrls/images/circle_green.png";
		CString strPicPath2 = ":/ctrls/images/circle_black.png";		
#endif
	POS pos=pList->GetHeadPosition();
	CDvmData *pData = NULL;
	int nRow = 0;
	QLabel *pLabelWidget = NULL;

	while(pos)
	{
		pData = (CDvmData *)pList->GetNext(pos);
		double dValue=CString_To_double(pData->m_strValue);
		pLabelWidget = (QLabel*)pGrid->cellWidget(nRow,0);

		if (pLabelWidget == NULL)
		{
			pLabelWidget = new QLabel(pGrid);
		}

		if ((dValue <0.001f) &&(dValue > -53.0f))
		{
			pLabelWidget->setPixmap(QPixmap(strPicPath1));
		}
		else
		{		
			pLabelWidget->setPixmap(QPixmap(strPicPath2));
		}

		pLabelWidget->setAlignment(Qt::AlignCenter); 
		pGrid->setCellWidget(nRow,0,pLabelWidget);
		nRow++;	
	}
} 
void QLuminousPowerDlg::UpdateData()
{	
	if (m_pFiberGroup != NULL)
	{
		delete m_pFiberGroup;
	}
	m_oOddLuminousPowerList.RemoveAll();
	m_oEvenLuminousPowerList.RemoveAll();
	m_pFiberGroup=(CDataGroup*)(&g_oSttTestResourceMngr.m_oFiberMsgGroup)->Clone();
	InitData(m_pFiberGroup);
	m_pOddLuminousPowerGrid->UpdateData(&m_oOddLuminousPowerList); 
	m_pEvenLuminousPowerGrid->UpdateData(&m_oEvenLuminousPowerList); 
}

void QLuminousPowerDlg::timerEvent(QTimerEvent * event)
{
	if (m_bHasClosed)
	{
		return;
	}

	if(event->timerId() == m_nTimerID)
	{  
		UpdateData();
	} 
}

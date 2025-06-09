#include "stdafx.h"
#include "QCharElementDlg.h"
//#include "../../SttTestCntrFrameBase.h"
#include "../../../Module/XLangResource_Native.h"
#include "../../../../../Module//OSInterface/QT/XMessageBox.h"
#include "../../../XLangResource_Native.h"


QCharElementDlg::QCharElementDlg( CCharElement *pCharElement, QWidget *parent )
	:QDialog(parent)
{
	//this->setWindowTitle("特性曲线边元素"); 
    this->setWindowTitle(g_sLangTxt_State_CharCurEdgeElements); //特性曲线边元素 lcq 3.15

	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	m_bIsAmpAngleChecked = true;
	m_pCurCharElement = pCharElement;
	m_pNewCharElement = NULL;
	InitTopUI();
	InitParaUI(GetElementType());
	InitButton();

	if (m_bIsAmpAngleChecked)
	{
		m_rBtnAmpAngle->setChecked(true);
	}
	else
	{
		m_rBtnRX->setChecked(true);
	} 

	if (m_pCurCharElement != NULL)
	{
		SetParaData();
	}
}

QCharElementDlg::~QCharElementDlg()
{

}

void QCharElementDlg::InitTopUI()
{
// 	m_strlistEleType<<tr("线段(lined)")<<tr("圆(mho)")<<tr("透镜(lens)")<<tr("射线(liner)")<<tr("直线(line)")<<tr("圆弧(arc)")<<tr("圆弧(arcp)");
// 	m_strlistDir<<tr("LEFT")<<tr("RIGHT");
// 	m_strlistClockDir<<tr("逆时针")<<tr("顺时针");

	m_strlistEleType<<g_sLangTxt_Lined<<g_sLangTxt_Mho<<g_sLangTxt_Lens<<g_sLangTxt_Liner<<g_sLangTxt_Line<<g_sLangTxt_Arc<<g_sLangTxt_Arcp;
	m_strlistDir<<tr("LEFT")<<tr("RIGHT");
	m_strlistClockDir<<g_sLangTxt_Gradient_Anticlockwise<<g_sLangTxt_Gradient_Clockwise; //lcq 3.15

	m_MainLayout = new QVBoxLayout();

	m_TopLayout = new QGridLayout();
	m_ParaLayout = new QGridLayout();
	m_ImpedanceLayout = new QHBoxLayout();
	m_BottomLayout = new QHBoxLayout();

	//QFont ft("Microsoft YaHei", 10); //2022-10-31 sy 采用g_pSttGlobalFont
	int nHeight = 25;

	m_MainLayout->addLayout(m_TopLayout);
	m_MainLayout->addLayout(m_ParaLayout);
	m_MainLayout->addLayout(m_ImpedanceLayout);
	m_MainLayout->addStretch();
	m_MainLayout->addLayout(m_BottomLayout);
	setLayout(m_MainLayout);

	m_labelElementType = new QLabel();
	m_labelElementType->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_labelElementType->setText(g_sLangTxt_State_TheEdgeElementType); //边元素类型 lcq 3.15
	//m_labelElementType->setFont(ft);
	m_labelElementType->setFixedHeight(nHeight);
	m_labelElementType->setFixedWidth(100);
	m_TopLayout->addWidget(m_labelElementType,0,0);
	m_cmbElementType = new QComboBox;
	m_cmbElementType->addItems(m_strlistEleType);
	m_cmbElementType->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_cmbElementType->setCurrentIndex(GetElementType());
	//m_cmbElementType->setFont(ft);
	m_cmbElementType->setFixedHeight(nHeight);
	m_TopLayout->addWidget(m_cmbElementType,0,1);

    //20241018 wanmj 特性曲线编辑窗口根据误差评估计算误差带长度，这里去掉误差带长度修改
//	m_labelErrorLen = new QLabel();
//	m_labelErrorLen->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
//	m_labelErrorLen->setText(g_sLangTxt_State_ErrorBandLength);// 误差带长度 lcq 3.15
//	//m_labelErrorLen->setFont(ft);
//	m_labelErrorLen->setFixedHeight(nHeight);
//	m_labelErrorLen->setFixedWidth(100);
//	m_TopLayout->addWidget(m_labelErrorLen,1,0);
//	m_editErrorLen = new QLineEdit;
//	m_editErrorLen->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
//	//m_editErrorLen->setFont(ft);
//	m_editErrorLen->setFixedHeight(nHeight);
//	m_editErrorLen->setText("1");
//	m_TopLayout->addWidget(m_editErrorLen,1,1);

	m_labelTestPoint = new QLabel();
	m_labelTestPoint->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_labelTestPoint->setText(g_sLangTxt_State_EdgeTestPoints); //边测试点数 lcq 3.15
	//m_labelTestPoint->setFont(ft);
	m_labelTestPoint->setFixedHeight(nHeight);
	m_labelTestPoint->setFixedWidth(100);
    m_TopLayout->addWidget(m_labelTestPoint,1,0);
	m_editTestPoint = new QLineEdit;
	m_editTestPoint->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	//m_editTestPoint->setFont(ft);
	m_editTestPoint->setFixedHeight(nHeight);
	m_editTestPoint->setText("1");
    m_TopLayout->addWidget(m_editTestPoint,1,1);
	
	if (m_pCurCharElement)
	{
//		m_editErrorLen->setText(m_pCurCharElement->m_strErrLength);
		long *nTestPoint = m_pCurCharElement->GetTestPointsRef();
		m_editTestPoint->setText(QString::number(*nTestPoint));
	}

	m_ImpedanceLabel = new QLabel();
	m_ImpedanceLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	CString strText = _T("阻抗表达方式");
	m_ImpedanceLabel->setText(strText);
	m_ImpedanceLabel->setFont(*g_pSttGlobalFont);
	m_ImpedanceLabel->setFixedHeight(nHeight);
	m_ImpedanceLabel->setFixedWidth(110);
	m_ImpedanceLayout->addWidget(m_ImpedanceLabel);
	m_rBtnAmpAngle = new QRadioButton();
	m_rBtnAmpAngle->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    strText = _T("幅值相位");
	m_rBtnAmpAngle->setText(strText);
	m_rBtnAmpAngle->setFont(*g_pSttGlobalFont);
	m_rBtnAmpAngle->setFixedHeight(nHeight);
	m_ImpedanceLayout->addWidget(m_rBtnAmpAngle);

	m_rBtnRX = new QRadioButton();
	m_rBtnRX->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_rBtnRX->setText(_T("R-X"));
	m_rBtnRX->setFont(*g_pSttGlobalFont);
	m_rBtnRX->setFixedHeight(nHeight);
	m_ImpedanceLayout->addWidget(m_rBtnRX);
	
	connect(m_cmbElementType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ElementTypeChanged(int)));
    connect(m_rBtnAmpAngle,SIGNAL(toggled(bool)),this,SLOT(slot_ImpedanceChanged(bool)));
}

void QCharElementDlg::InitParaUI(int nType)
{
	for (int i = 0 ; i < m_labelList.size(); i++)
	{
		delete m_labelList[i];
		m_labelList[i] = NULL;
	}

	for (int i = 0 ; i < m_cmbList.size(); i++)
	{
		delete m_cmbList[i];
		m_cmbList[i] = NULL;
	}

	for (int i = 0 ; i < m_editList.size(); i++)
	{
		delete m_editList[i];
		m_editList[i] = NULL;
	}

	m_labelList.clear();
	m_cmbList.clear();
	m_editList.clear();

	if (nType == STT_CHAR_ELEMENT_TYPE_LINED)//线段
	{

		//AddLabelToList(QObject::tr("起始点-R"),0,0); 
		AddLabelToList(g_sLangTxt_State_startingPointR,0,0); //起始点-R lcq 3.15
		AddEditToList(0,1);

		//AddLabelToList(QObject::tr("起始点-X"),1,0);
		AddLabelToList(g_sLangTxt_State_EdgeTestPointX,1,0); //起始点-X lcq 3.15
		AddEditToList(1,1);

		//AddLabelToList(QObject::tr("终止点-R"),2,0);
		AddLabelToList(g_sLangTxt_State_EndPointR,2,0); //终止点-R lcq 3.15
		AddEditToList(2,1);
        //AddLabelToList(QObject::tr("终止点-X"),3,0);
		AddLabelToList(g_sLangTxt_State_EndPointX,3,0); //终止点-X lcq 3.15
		AddEditToList(3,1);
		
		//AddLabelToList(QObject::tr("方向"),4,0);
		AddLabelToList(g_sLangTxt_State_Direction,4,0); //方向 lcq 3.15
		QComboBox *cmbTemp = new QComboBox;
		cmbTemp->addItems(m_strlistDir);
		cmbTemp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		cmbTemp->setCurrentIndex(0);
		m_ParaLayout->addWidget(cmbTemp,4,1);
		m_cmbList.append(cmbTemp);

		AddrBtnImpedance(true);
	}
	else if (nType == STT_CHAR_ELEMENT_TYPE_MHO)
	{
		//AddLabelToList(QObject::tr("正向到达"),0,0);
		AddLabelToList(g_sLangTxt_State_PositiveArrival,0,0); //正向到达 lcq 3.15
		AddEditToList(0,1);

		//AddLabelToList(QObject::tr("角度"),1,0);
		AddLabelToList(g_sLangTxt_State_Angle,1,0);  //角度 lcq 3.15
		AddEditToList(1,1);

		//AddLabelToList(QObject::tr("偏移"),2,0);
		AddLabelToList(g_sLangTxt_State_Offset,2,0); //偏移 lcq 3.15
		AddEditToList(2,1);
		AddrBtnImpedance(false);
	}
	else if (nType == STT_CHAR_ELEMENT_TYPE_LENS)
	{
		//AddLabelToList(QObject::tr("正向到达"),0,0);
		AddLabelToList(g_sLangTxt_State_PositiveArrival,0,0); //正向到达 lcq 3.15
		AddEditToList(0,1);
        //AddLabelToList(QObject::tr("角度"),1,0);
		AddLabelToList(g_sLangTxt_State_Angle,1,0); //角度 lcq 3.15
		AddEditToList(1,1);
        //AddLabelToList(QObject::tr("偏移"),2,0);
		AddLabelToList(g_sLangTxt_State_Offset,2,0); //偏移 lcq 3.15
		AddEditToList(2,1);
        //AddLabelToList(QObject::tr("宽度"),3,0); 
		AddLabelToList(g_sLangTxt_State_Width,3,0); //宽度 lcq 3.15
		AddEditToList(3,1);
		AddrBtnImpedance(false);
	}
	else if (nType == STT_CHAR_ELEMENT_TYPE_LINER)
	{
		
		AddLabelToList(g_sLangTxt_State_startingPointR,0,0); //lcq 3.15
		AddEditToList(0,1);

		AddLabelToList(g_sLangTxt_State_EdgeTestPointX,1,0); //lcq 3.15
		AddEditToList(1,1);
		
		AddLabelToList(g_sLangTxt_State_Angle,2,0); //lcq 3.15
		AddEditToList(2,1);

		AddLabelToList(g_sLangTxt_State_Direction,3,0); //lcq 3.15
		QComboBox *cmbTemp = new QComboBox;
		cmbTemp->addItems(m_strlistDir);
		cmbTemp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		cmbTemp->setCurrentIndex(0);
		m_ParaLayout->addWidget(cmbTemp,3,1);
		m_cmbList.append(cmbTemp);
		AddrBtnImpedance(true);
	}
	else if (nType == STT_CHAR_ELEMENT_TYPE_LINE)
	{
		AddLabelToList(g_sLangTxt_State_startingPointR,0,0); //lcq 3.15
		AddEditToList(0,1);

		AddLabelToList(g_sLangTxt_State_EdgeTestPointX,1,0); //lcq 3.15
		AddEditToList(1,1);
		
		AddLabelToList(g_sLangTxt_State_Angle,2,0); //lcq 3.15
		AddEditToList(2,1);

		AddLabelToList(g_sLangTxt_State_Direction,3,0); //lcq 3.15
		QComboBox *cmbTemp = new QComboBox;
		cmbTemp->addItems(m_strlistDir);
		cmbTemp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		cmbTemp->setCurrentIndex(0);
		m_ParaLayout->addWidget(cmbTemp,3,1);
		m_cmbList.append(cmbTemp);
		AddrBtnImpedance(true);
	}
	else if (nType == STT_CHAR_ELEMENT_TYPE_ARC)
	{

		AddLabelToList(g_sLangTxt_State_CenterX,0,0); //lcq 3.15
		AddEditToList(0,1);

		AddLabelToList(g_sLangTxt_State_CenterY,1,0); //lcq 3.15
		AddEditToList(1,1);
		
		AddLabelToList(g_sLangTxt_State_Radius,2,0);  //lcq 3.15
		AddEditToList(2,1);

		AddLabelToList(g_sLangTxt_State_StartingAngle,3,0);  //lcq 3.15
		AddEditToList(3,1);

		AddLabelToList(g_sLangTxt_State_TerminationAngle,4,0); //lcq 3.15
		AddEditToList(4,1);

		AddLabelToList(g_sLangTxt_State_Direction,5,0);  //lcq 3.15
		QComboBox *cmbTemp = new QComboBox;
		cmbTemp->addItems(m_strlistDir);
		cmbTemp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		cmbTemp->setCurrentIndex(0);
		m_ParaLayout->addWidget(cmbTemp,5,1);
		m_cmbList.append(cmbTemp);

		AddLabelToList(g_sLangTxt_State_ClockDirection,6,0);  //lcq 3.15
		cmbTemp = new QComboBox;
		cmbTemp->addItems(m_strlistClockDir);
		cmbTemp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		cmbTemp->setCurrentIndex(0);
		m_ParaLayout->addWidget(cmbTemp,6,1);
		m_cmbList.append(cmbTemp);
		AddrBtnImpedance(true);
	}
	else if (nType == STT_CHAR_ELEMENT_TYPE_ARCP)
	{
		AddLabelToList(g_sLangTxt_State_CenterX,0,0);  //lcq 3.15
		AddEditToList(0,1);

		AddLabelToList(g_sLangTxt_State_CenterY,1,0);  //lcq 3.15
		AddEditToList(1,1);
		
		AddLabelToList(g_sLangTxt_State_Radius,2,0);  //lcq 3.15
		AddEditToList(2,1);

		AddLabelToList(g_sLangTxt_State_StartingAngle,3,0);  //lcq 3.15
		AddEditToList(3,1);

		AddLabelToList(g_sLangTxt_State_TerminationAngle,4,0);  //lcq 3.15
		AddEditToList(4,1);

		AddLabelToList(g_sLangTxt_State_Direction,5,0);  //lcq 3.15
		QComboBox *cmbTemp = new QComboBox;
		cmbTemp->addItems(m_strlistDir);
		cmbTemp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		cmbTemp->setCurrentIndex(0);
		m_ParaLayout->addWidget(cmbTemp,5,1);
		m_cmbList.append(cmbTemp);

		AddLabelToList(g_sLangTxt_State_ClockDirection,6,0);  //lcq 3.15
		cmbTemp = new QComboBox;
		cmbTemp->addItems(m_strlistClockDir);
		cmbTemp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		cmbTemp->setCurrentIndex(0);
		m_ParaLayout->addWidget(cmbTemp,6,1);
		m_cmbList.append(cmbTemp);
		AddrBtnImpedance(true);
	}
	slot_ImpedanceChanged(m_bIsAmpAngleChecked);
}

void QCharElementDlg::InitParaCache(CExBaseList* pParamCache)
{
	m_pParamCache = pParamCache;
	UpdateParaCache();
}

void QCharElementDlg::UpdateParaCache()
{
	CCharElementLined* pElementLined = (CCharElementLined*)m_pParamCache->FindByID("lined");
	CCharElementMho* pElementMho = (CCharElementMho*)m_pParamCache->FindByID("mho");
	CCharElementLens* pElementLens = (CCharElementLens*)m_pParamCache->FindByID("lens");
	CCharElementLiner* pElementLiner = (CCharElementLiner*)m_pParamCache->FindByID("liner");
	CCharElementLine* pElementLine = (CCharElementLine*)m_pParamCache->FindByID("line");
	CCharElementArc* pElementArc = (CCharElementArc*)m_pParamCache->FindByID("arc");
	CCharElementArcp* pElementArcp = (CCharElementArcp*)m_pParamCache->FindByID("arcp");

//	m_editErrorLen->setText("1");
	m_editTestPoint->setText("1");
	for (int i = 0; i < m_editList.size(); i++)
	{
		m_editList[i]->setText("1");
	}
	for (int i = 0; i < m_cmbList.size(); i++)
	{
		m_cmbList[i]->setCurrentIndex(0);
	}

	switch(m_cmbElementType->currentIndex())
	{
	case STT_CHAR_ELEMENT_TYPE_LINED:
		if(pElementLined)
		{
//			m_editErrorLen->setText(pElementLined->m_strErrLength);
			long nPts = *(pElementLined->GetTestPointsRef());
			QString strTemp = QString("%1").arg(nPts);
			m_editTestPoint->setText(strTemp);
			if (m_bIsAmpAngleChecked)
			{
				m_editList[0]->setText(GetImpedanceByXY("Amp",pElementLined->m_strXb,pElementLined->m_strYb));
				m_editList[1]->setText(GetImpedanceByXY("Angle",pElementLined->m_strXb,pElementLined->m_strYb));
				m_editList[2]->setText(GetImpedanceByXY("Amp",pElementLined->m_strXe,pElementLined->m_strYe));
				m_editList[3]->setText(GetImpedanceByXY("Angle",pElementLined->m_strXe,pElementLined->m_strYe));
			}
			else
			{
			m_editList[0]->setText(pElementLined->m_strXb);
			m_editList[1]->setText(pElementLined->m_strYb);
			m_editList[2]->setText(pElementLined->m_strXe);
			m_editList[3]->setText(pElementLined->m_strYe);
			}
			m_cmbList[0]->setCurrentIndex(m_cmbList[0]->findText(pElementLined->m_strDir));
		}
		break;
	case STT_CHAR_ELEMENT_TYPE_MHO:
		if(pElementMho)
		{
//			m_editErrorLen->setText(pElementMho->m_strErrLength);
			long nPts = *(pElementMho->GetTestPointsRef());
			QString strTemp = QString("%1").arg(nPts);
			m_editTestPoint->setText(strTemp);
			m_editList[0]->setText(pElementMho->m_strForwardReach);
			m_editList[1]->setText(pElementMho->m_strAngle);
			m_editList[2]->setText(pElementMho->m_strOffset);
		}
		break;
	case STT_CHAR_ELEMENT_TYPE_LENS:
		if(pElementLens)
		{
//			m_editErrorLen->setText(pElementLens->m_strErrLength);
			long nPts = *(pElementLens->GetTestPointsRef());
			QString strTemp = QString("%1").arg(nPts);
			m_editTestPoint->setText(strTemp);
			m_editList[0]->setText(pElementLens->m_strForwardReach);
			m_editList[1]->setText(pElementLens->m_strAngle);
			m_editList[2]->setText(pElementLens->m_strOffset);
			m_editList[3]->setText(pElementLens->m_strWidth);
		}
		break;
	case STT_CHAR_ELEMENT_TYPE_LINER:
		if(pElementLiner)
		{
//			m_editErrorLen->setText(pElementLiner->m_strErrLength);
			long nPts = *(pElementLiner->GetTestPointsRef());
			QString strTemp = QString("%1").arg(nPts);
			m_editTestPoint->setText(strTemp);
			if (m_bIsAmpAngleChecked)
			{
				m_editList[0]->setText(GetImpedanceByXY("Amp",pElementLiner->m_strXb,pElementLiner->m_strYb));
				m_editList[1]->setText(GetImpedanceByXY("Angle",pElementLiner->m_strXb,pElementLiner->m_strYb));
			}
			else
			{
			m_editList[0]->setText(pElementLiner->m_strXb);
			m_editList[1]->setText(pElementLiner->m_strYb);
			}
			m_editList[2]->setText(pElementLiner->m_strAngle);
			m_cmbList[0]->setCurrentIndex(m_cmbList[0]->findText(pElementLiner->m_strDir));
		}
		break;
	case STT_CHAR_ELEMENT_TYPE_LINE:
		if(pElementLine)
		{
//			m_editErrorLen->setText(pElementLine->m_strErrLength);
			long nPts = *(pElementLine->GetTestPointsRef());
			QString strTemp = QString("%1").arg(nPts);
			m_editTestPoint->setText(strTemp);
			if (m_bIsAmpAngleChecked)
			{
				m_editList[0]->setText(GetImpedanceByXY("Amp",pElementLine->m_strX,pElementLine->m_strY));
				m_editList[1]->setText(GetImpedanceByXY("Angle",pElementLine->m_strX,pElementLine->m_strY));
			}
			else
			{
			m_editList[0]->setText(pElementLine->m_strX);
			m_editList[1]->setText(pElementLine->m_strY);
			}
			m_editList[2]->setText(pElementLine->m_strAngle);
			m_cmbList[0]->setCurrentIndex(m_cmbList[0]->findText(pElementLine->m_strDir));
		}
		break;
	case STT_CHAR_ELEMENT_TYPE_ARC:
		if(pElementArc)
		{
//			m_editErrorLen->setText(pElementArc->m_strErrLength);
			long nPts = *(pElementArc->GetTestPointsRef());
			QString strTemp = QString("%1").arg(nPts);
			m_editTestPoint->setText(strTemp);
			if (m_bIsAmpAngleChecked)
			{
				m_editList[0]->setText(GetImpedanceByXY("Amp",pElementArc->m_strXCenter,pElementArc->m_strYCenter));
				m_editList[1]->setText(GetImpedanceByXY("Angle",pElementArc->m_strXCenter,pElementArc->m_strYCenter));
			}
			else
			{
			m_editList[0]->setText(pElementArc->m_strXCenter);
			m_editList[1]->setText(pElementArc->m_strYCenter);
			}
			m_editList[2]->setText(pElementArc->m_strRadius);
			m_editList[3]->setText(pElementArc->m_strAngleBegin);
			m_editList[4]->setText(pElementArc->m_strAngleEnd);
			m_cmbList[0]->setCurrentIndex(m_cmbList[0]->findText(pElementArc->m_strDir));
			if(pElementArc->m_strClockwise == "CCW")
			{
				m_cmbList[1]->setCurrentIndex(0);
			}
			else
			{
				m_cmbList[1]->setCurrentIndex(1);
			}
		}
		break;
	case STT_CHAR_ELEMENT_TYPE_ARCP:
		if(pElementArcp)
		{
//			m_editErrorLen->setText(pElementArcp->m_strErrLength);
			long nPts = *(pElementArcp->GetTestPointsRef());
			QString strTemp = QString("%1").arg(nPts);
			m_editTestPoint->setText(strTemp);
			if (m_bIsAmpAngleChecked)
			{
				m_editList[0]->setText(GetImpedanceByXY("Amp",pElementArcp->m_strZ,pElementArcp->m_strPh));
				m_editList[1]->setText(GetImpedanceByXY("Angle",pElementArcp->m_strZ,pElementArcp->m_strPh));
			}
			else
			{
			m_editList[0]->setText(pElementArcp->m_strZ);
			m_editList[1]->setText(pElementArcp->m_strPh);
			}
			m_editList[2]->setText(pElementArcp->m_strRadius);
			m_editList[3]->setText(pElementArcp->m_strAngleBegin);
			m_editList[4]->setText(pElementArcp->m_strAngleEnd);
			m_cmbList[0]->setCurrentIndex(m_cmbList[0]->findText(pElementArcp->m_strDir));
			m_cmbList[1]->setCurrentIndex(m_cmbList[1]->findText(pElementArcp->m_strClockwise));
		}
		break;
	default:
		break;
	}
}

void QCharElementDlg::InitButton()
{
	m_pbtnOK = new QPushButton(this);
	m_pbtnOK->setText(g_sLangTxt_OK);
	m_pbtnOK->setFixedSize(100,26);
	m_pbtnOK->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
#ifdef _PSX_QT_WINDOWS_
	m_pbtnOK->setIcon (QPixmap( "./images/Check.png"));
#else
    m_pbtnOK->setIcon (QPixmap( ":/ctrls/images/Check.png"));
#endif
	m_BottomLayout->addWidget(m_pbtnOK);

	m_pbtnCancel = new QPushButton(this);
	m_pbtnCancel->setText(g_sLangTxt_Cancel);
	m_pbtnCancel->setFixedSize(100,26);
	m_pbtnCancel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
#ifdef _PSX_QT_WINDOWS_
	m_pbtnCancel->setIcon (QPixmap( "./images/Cancel.png"));
#else
	m_pbtnCancel->setIcon (QPixmap( ":/ctrls/images/Cancel.png"));
#endif
	m_BottomLayout->addWidget(m_pbtnCancel);

	connect(m_pbtnOK, SIGNAL(clicked ()), this, SLOT(slot_PbnOkClicked()));
	connect(m_pbtnCancel, SIGNAL(clicked ()), this, SLOT(slot_PbnCancelClicked()));
}

void QCharElementDlg::SetParaData()
{
	int nIndex = m_cmbElementType->currentIndex();

	if (m_pCurCharElement != NULL && nIndex == GetElementType())
	{
		switch (nIndex)
		{
		case STT_CHAR_ELEMENT_TYPE_LINED:
			{
				CCharElementLined *pChar = (CCharElementLined *)m_pCurCharElement;
//				m_editErrorLen->setText(pChar->m_strErrLength);
				long nPts = *(pChar->GetTestPointsRef());
				QString strTemp = QString("%1").arg(nPts);
				m_editTestPoint->setText(strTemp);
				if (m_bIsAmpAngleChecked)
				{
					m_editList[0]->setText(GetImpedanceByXY("Amp",pChar->m_strXb,pChar->m_strYb));
					m_editList[1]->setText(GetImpedanceByXY("Angle",pChar->m_strXb,pChar->m_strYb));
					m_editList[2]->setText(GetImpedanceByXY("Amp",pChar->m_strXe,pChar->m_strYe));
					m_editList[3]->setText(GetImpedanceByXY("Angle",pChar->m_strXe,pChar->m_strYe));
				}
				else
				{
				m_editList[0]->setText(pChar->m_strXb);
				m_editList[1]->setText(pChar->m_strYb);
				m_editList[2]->setText(pChar->m_strXe);
				m_editList[3]->setText(pChar->m_strYe);
				}
				SetComboIndex(0,pChar->m_strDir);
				
			}break;
		case STT_CHAR_ELEMENT_TYPE_MHO:
			{
				CCharElementMho *pChar = (CCharElementMho *)m_pCurCharElement;
//				m_editErrorLen->setText(pChar->m_strErrLength);
				long nPts = *(pChar->GetTestPointsRef());
				QString strTemp = QString("%1").arg(nPts);
				m_editTestPoint->setText(strTemp);
				m_editList[0]->setText(pChar->m_strForwardReach);
				m_editList[1]->setText(pChar->m_strAngle);
				m_editList[2]->setText(pChar->m_strOffset);
			}break;
		case STT_CHAR_ELEMENT_TYPE_LENS:
			{
				CCharElementLens *pChar = (CCharElementLens *)m_pCurCharElement;
//				m_editErrorLen->setText(pChar->m_strErrLength);
				long nPts = *(pChar->GetTestPointsRef());
				QString strTemp = QString("%1").arg(nPts);
				m_editTestPoint->setText(strTemp);
				m_editList[0]->setText(pChar->m_strForwardReach);
				m_editList[1]->setText(pChar->m_strAngle);
				m_editList[2]->setText(pChar->m_strOffset);
				m_editList[3]->setText(pChar->m_strWidth);
			}break;
		case STT_CHAR_ELEMENT_TYPE_LINER:
			{
				CCharElementLiner *pChar = (CCharElementLiner *)m_pCurCharElement;
//				m_editErrorLen->setText(pChar->m_strErrLength);
				long nPts = *(pChar->GetTestPointsRef());
				QString strTemp = QString("%1").arg(nPts);
				m_editTestPoint->setText(strTemp);
				if (m_bIsAmpAngleChecked)
				{
					m_editList[0]->setText(GetImpedanceByXY("Amp",pChar->m_strXb,pChar->m_strYb));
					m_editList[1]->setText(GetImpedanceByXY("Angle",pChar->m_strXb,pChar->m_strYb));
				}
				else
				{
				m_editList[0]->setText(pChar->m_strXb);
				m_editList[1]->setText(pChar->m_strYb);
				}
				m_editList[2]->setText(pChar->m_strAngle);
				SetComboIndex(0,pChar->m_strDir);
			}break;
		case STT_CHAR_ELEMENT_TYPE_LINE:
			{
				CCharElementLine *pChar = (CCharElementLine *)m_pCurCharElement;
//				m_editErrorLen->setText(pChar->m_strErrLength);
				long nPts = *(pChar->GetTestPointsRef());
				QString strTemp = QString("%1").arg(nPts);
				m_editTestPoint->setText(strTemp);
				if (m_bIsAmpAngleChecked)
				{
					m_editList[0]->setText(GetImpedanceByXY("Amp",pChar->m_strX,pChar->m_strY));
					m_editList[1]->setText(GetImpedanceByXY("Angle",pChar->m_strX,pChar->m_strY));
				}
				else
				{
				m_editList[0]->setText(pChar->m_strX);
				m_editList[1]->setText(pChar->m_strY);
				}
				m_editList[2]->setText(pChar->m_strAngle);
				SetComboIndex(0,pChar->m_strDir);
			}break;
		case STT_CHAR_ELEMENT_TYPE_ARC:
			{
				CCharElementArc *pChar = (CCharElementArc *)m_pCurCharElement;
//				m_editErrorLen->setText(pChar->m_strErrLength);
				long nPts = *(pChar->GetTestPointsRef());
				QString strTemp = QString("%1").arg(nPts);
				m_editTestPoint->setText(strTemp);
				if (m_bIsAmpAngleChecked)
				{
					m_editList[0]->setText(GetImpedanceByXY("Amp",pChar->m_strXCenter,pChar->m_strYCenter));
					m_editList[1]->setText(GetImpedanceByXY("Angle",pChar->m_strXCenter,pChar->m_strYCenter));
				}
				else
				{
				m_editList[0]->setText(pChar->m_strXCenter);
				m_editList[1]->setText(pChar->m_strYCenter);
				}
				m_editList[2]->setText(pChar->m_strRadius);
				m_editList[3]->setText(pChar->m_strAngleBegin);
				m_editList[4]->setText(pChar->m_strAngleEnd);
				SetComboIndex(0,pChar->m_strDir);
				SetComboIndex(1,pChar->m_strClockwise);
			}break;
		case STT_CHAR_ELEMENT_TYPE_ARCP:
			{
				CCharElementArcp *pChar = (CCharElementArcp *)m_pCurCharElement;
//				m_editErrorLen->setText(pChar->m_strErrLength);
				long nPts = *(pChar->GetTestPointsRef());
				QString strTemp = QString("%1").arg(nPts);
				m_editTestPoint->setText(strTemp);
				if (m_bIsAmpAngleChecked)
				{
					m_editList[0]->setText(GetImpedanceByXY("Amp",pChar->m_strZ,pChar->m_strPh));
					m_editList[1]->setText(GetImpedanceByXY("Angle",pChar->m_strZ,pChar->m_strPh));
				}
				else
				{
				m_editList[0]->setText(pChar->m_strZ);
				m_editList[1]->setText(pChar->m_strPh);
				}
				m_editList[2]->setText(pChar->m_strRadius);
				m_editList[3]->setText(pChar->m_strAngleBegin);
				m_editList[4]->setText(pChar->m_strAngleEnd);
				SetComboIndex(0,pChar->m_strDir);
				SetComboIndex(1,pChar->m_strClockwise);
			}break;
		}
	}
}

CString QCharElementDlg::GetCurrClockwiseID()
{
	CString strName;
	strName = m_cmbList.at(1)->currentText();
	CDataType* pDataType = CCharacteristicConstGlobal::ClockwiseDataType();
	CDataTypeValue *pDataTypeValue =  (CDataTypeValue*)pDataType->FindByName(strName);

	if (pDataTypeValue == NULL)
	{
		pDataTypeValue = (CDataTypeValue*)pDataType->GetHead();
	}

	return pDataTypeValue->m_strID;
}

CString QCharElementDlg::GetCurrDirID()
{
	CString strName;
	strName = m_cmbList.at(0)->currentText();
	CDataType* pDataType = CCharacteristicConstGlobal::DirDataType();
	CDataTypeValue *pDataTypeValue =  (CDataTypeValue*)pDataType->FindByName(strName);

	if (pDataTypeValue == NULL)
	{
		pDataTypeValue = (CDataTypeValue*)pDataType->GetHead();
	}

	return pDataTypeValue->m_strID;
}

void QCharElementDlg::CreateNewElement()
{
	int nIndex = m_cmbElementType->currentIndex();
	
	switch (nIndex)
	{
	case STT_CHAR_ELEMENT_TYPE_LINED:
		{
			m_pNewCharElement = new CCharElementLined;
			if (m_bIsAmpAngleChecked)
			{
                ((CCharElementLined*)m_pNewCharElement)->m_strXb = GetXYByImpedance("X",m_editList[0]->text(),m_editList[1]->text());
				((CCharElementLined*)m_pNewCharElement)->m_strYb = GetXYByImpedance("Y",m_editList[0]->text(),m_editList[1]->text());
				((CCharElementLined*)m_pNewCharElement)->m_strXe = GetXYByImpedance("X",m_editList[2]->text(),m_editList[3]->text());
				((CCharElementLined*)m_pNewCharElement)->m_strYe = GetXYByImpedance("Y",m_editList[2]->text(),m_editList[3]->text());
			}
			else
			{
			((CCharElementLined*)m_pNewCharElement)->m_strXb = m_editList[0]->text();
			((CCharElementLined*)m_pNewCharElement)->m_strYb = m_editList[1]->text();
			((CCharElementLined*)m_pNewCharElement)->m_strXe = m_editList[2]->text();
			((CCharElementLined*)m_pNewCharElement)->m_strYe = m_editList[3]->text();
			}

			int n = m_cmbList.at(0)->currentIndex();
			if (n < 0 || n > 1)
			{
				n = 0;
			}
			((CCharElementLined*)m_pNewCharElement)->m_strDir = m_strlistDir.at(n);
		}break;
	case STT_CHAR_ELEMENT_TYPE_MHO:
		{
			m_pNewCharElement = new CCharElementMho;
			((CCharElementMho*)m_pNewCharElement)->m_strForwardReach = m_editList[0]->text();
			((CCharElementMho*)m_pNewCharElement)->m_strAngle = m_editList[1]->text();
			((CCharElementMho*)m_pNewCharElement)->m_strOffset = m_editList[2]->text();
		}break;
	case STT_CHAR_ELEMENT_TYPE_LENS:
		{
			m_pNewCharElement = new CCharElementLens;
			((CCharElementLens*)m_pNewCharElement)->m_strForwardReach = m_editList[0]->text();
			((CCharElementLens*)m_pNewCharElement)->m_strAngle = m_editList[1]->text();
			((CCharElementLens*)m_pNewCharElement)->m_strOffset = m_editList[2]->text();
			((CCharElementLens*)m_pNewCharElement)->m_strWidth = m_editList[3]->text();
		}break;
	case STT_CHAR_ELEMENT_TYPE_LINER:
		{
			m_pNewCharElement = new CCharElementLiner;
			if (m_bIsAmpAngleChecked)
			{
				((CCharElementLiner*)m_pNewCharElement)->m_strXb = GetXYByImpedance("X",m_editList[0]->text(),m_editList[1]->text());
				((CCharElementLiner*)m_pNewCharElement)->m_strYb = GetXYByImpedance("Y",m_editList[0]->text(),m_editList[1]->text());
			}
			else
			{
			((CCharElementLiner*)m_pNewCharElement)->m_strXb = m_editList[0]->text();
			((CCharElementLiner*)m_pNewCharElement)->m_strYb = m_editList[1]->text();
			}
			((CCharElementLiner*)m_pNewCharElement)->m_strAngle = m_editList[2]->text();
			int n = m_cmbList.at(0)->currentIndex();
			if (n < 0 || n > 1)
			{
				n = 0;
			}
			((CCharElementLiner*)m_pNewCharElement)->m_strDir = m_strlistDir.at(n);
		}break;
	case STT_CHAR_ELEMENT_TYPE_LINE:
		{
			m_pNewCharElement = new CCharElementLine;
			if (m_bIsAmpAngleChecked)
			{
				((CCharElementLine*)m_pNewCharElement)->m_strX = GetXYByImpedance("X",m_editList[0]->text(),m_editList[1]->text());
				((CCharElementLine*)m_pNewCharElement)->m_strY = GetXYByImpedance("Y",m_editList[0]->text(),m_editList[1]->text());
			}
			else
			{
			((CCharElementLine*)m_pNewCharElement)->m_strX = m_editList[0]->text();
			((CCharElementLine*)m_pNewCharElement)->m_strY = m_editList[1]->text();
				
			}
			((CCharElementLine*)m_pNewCharElement)->m_strAngle = m_editList[2]->text();
			int n = m_cmbList.at(0)->currentIndex();
			if (n < 0 || n > 1)
			{
				n = 0;
			}
			((CCharElementLine*)m_pNewCharElement)->m_strDir = m_strlistDir.at(n);
		}break;
	case STT_CHAR_ELEMENT_TYPE_ARC:
		{
			m_pNewCharElement = new CCharElementArc;
			if (m_bIsAmpAngleChecked)
			{
				((CCharElementArc*)m_pNewCharElement)->m_strXCenter = GetXYByImpedance("X",m_editList[0]->text(),m_editList[1]->text());
				((CCharElementArc*)m_pNewCharElement)->m_strYCenter = GetXYByImpedance("Y",m_editList[0]->text(),m_editList[1]->text());
			}
			else
			{
			((CCharElementArc*)m_pNewCharElement)->m_strXCenter = m_editList[0]->text();
			((CCharElementArc*)m_pNewCharElement)->m_strYCenter = m_editList[1]->text();
			}
			((CCharElementArc*)m_pNewCharElement)->m_strRadius = m_editList[2]->text();
			((CCharElementArc*)m_pNewCharElement)->m_strAngleBegin = m_editList[3]->text();
			((CCharElementArc*)m_pNewCharElement)->m_strAngleEnd = m_editList[4]->text();
			
			((CCharElementArc*)m_pNewCharElement)->m_strDir = GetCurrDirID();
			((CCharElementArc*)m_pNewCharElement)->m_strClockwise = GetCurrClockwiseID();
		}break;
	case STT_CHAR_ELEMENT_TYPE_ARCP:
		{
			m_pNewCharElement = new CCharElementArcp;
			if (m_bIsAmpAngleChecked)
			{
				((CCharElementArcp*)m_pNewCharElement)->m_strZ = GetXYByImpedance("X",m_editList[0]->text(),m_editList[1]->text());
				((CCharElementArcp*)m_pNewCharElement)->m_strPh = GetXYByImpedance("Y",m_editList[0]->text(),m_editList[1]->text());
			}
			else
			{
			((CCharElementArcp*)m_pNewCharElement)->m_strZ = m_editList[0]->text();
			((CCharElementArcp*)m_pNewCharElement)->m_strPh = m_editList[1]->text();
			}
			((CCharElementArcp*)m_pNewCharElement)->m_strRadius = m_editList[2]->text();
			((CCharElementArcp*)m_pNewCharElement)->m_strAngleBegin = m_editList[3]->text();
			((CCharElementArcp*)m_pNewCharElement)->m_strAngleEnd = m_editList[4]->text();
			int n = m_cmbList.at(0)->currentIndex();
			if (n < 0 || n > 1)
			{
				n = 0;
			}
			int n1 = m_cmbList.at(1)->currentIndex();
			if (n1 < 0 || n1 > 1)
			{
				n1 = 0;
			}
			((CCharElementArcp*)m_pNewCharElement)->m_strDir = m_strlistDir.at(n);
			((CCharElementArcp*)m_pNewCharElement)->m_strClockwise = m_strlistClockDir.at(n1);
		}break;
	}

//	m_pNewCharElement->m_strErrLength = m_editErrorLen->text();
	long *nTestPoint = m_pNewCharElement->GetTestPointsRef();
	long nPoint =  m_editTestPoint->text().toLong();

	if (nPoint <1)
	{
		nPoint = 1;
	}

	*nTestPoint = nPoint;
}

void QCharElementDlg::slot_ElementTypeChanged(int nIndex)
{
	InitParaUI(nIndex);
	
	if (m_pCurCharElement != NULL)
	{
		long nFindIndex = m_cmbElementType->findText(m_pCurCharElement->m_strName);
		if(nFindIndex == nIndex)
		{
			SetParaData();
			return;
		}	
	}

	UpdateParaCache();
}

void QCharElementDlg::slot_PbnOkClicked()
{
	if (IsEditText())
	{
		return;
	}
	CreateNewElement();
	accept();
}

void QCharElementDlg::slot_PbnCancelClicked()
{
	close();
}

int QCharElementDlg::GetElementType()
{
	int nIndex = 0;

	if (m_pCurCharElement == NULL)
	{
		return 0;
	}
	if (m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTLINED)
		nIndex = STT_CHAR_ELEMENT_TYPE_LINED;
	else if (m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTMHO)
		nIndex = STT_CHAR_ELEMENT_TYPE_MHO;
	else if (m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTLENS)
		nIndex = STT_CHAR_ELEMENT_TYPE_LENS;
	else if (m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTLINER)
		nIndex = STT_CHAR_ELEMENT_TYPE_LINER;
	else if (m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTLINE)
		nIndex = STT_CHAR_ELEMENT_TYPE_LINE;
	else if (m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTARC)
		nIndex = STT_CHAR_ELEMENT_TYPE_ARC;
	else if (m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTARCP)
		nIndex = STT_CHAR_ELEMENT_TYPE_ARCP;

	return nIndex;
}

void QCharElementDlg::AddLabelToList( QString str,int nRow,int nCol )
{
	//QFont ft("Microsoft YaHei", 10); //2022-10-31 sy 采用g_pSttGlobalFont
	int nHeight = 25;

	QLabel *tempLabel = new QLabel;
	tempLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	tempLabel->setText(str);
	tempLabel->setFont(*g_pSttGlobalFont);
	tempLabel->setFixedHeight(nHeight);
	tempLabel->setFixedWidth(100);
	m_ParaLayout->addWidget(tempLabel,nRow,nCol);
	m_labelList.append(tempLabel);
}

void QCharElementDlg::AddEditToList( int nRow,int nCol )
{
	//QFont ft("Microsoft YaHei", 10); //2022-10-31 sy 采用g_pSttGlobalFont
	int nHeight = 25;

	QLineEdit *tempEdit = new QLineEdit;
	tempEdit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	tempEdit->setFont(*g_pSttGlobalFont);
	tempEdit->setFixedHeight(nHeight);
	tempEdit->setText("1");
	m_ParaLayout->addWidget(tempEdit,nRow,nCol);
	m_editList.append(tempEdit);

}

void QCharElementDlg::AddrBtnImpedance (bool bIsShow)
{

	m_ImpedanceLabel->setVisible(bIsShow);
	m_rBtnAmpAngle->setVisible(bIsShow);
	m_rBtnRX->setVisible(bIsShow);

	if (m_bIsAmpAngleChecked)
	{
		m_rBtnAmpAngle->setChecked(true);
	}
	else
	{
		m_rBtnRX->setChecked(true);
	} 
 
}

void QCharElementDlg::SetComboIndex( int nIndex, QString strText )
{
	if (nIndex == 0)
	{
		if (strText == m_strlistDir.at(0))
		{
			m_cmbList[nIndex]->setCurrentIndex(0);
		}
		else if (strText == m_strlistDir.at(1))
		{
			m_cmbList[nIndex]->setCurrentIndex(1);
		}
		else
			m_cmbList[nIndex]->setCurrentIndex(-1);
	}
	else if (nIndex == 1)
	{
		CDataType* pDataType = CCharacteristicConstGlobal::ClockwiseDataType();
		CDataTypeValue *pDataTypeValue =  (CDataTypeValue*)pDataType->FindByID(strText);

		if (pDataTypeValue != NULL)
		{
			if (pDataTypeValue->m_strName == m_strlistClockDir.at(0))
			{
				m_cmbList[nIndex]->setCurrentIndex(0);
			}
			else if (pDataTypeValue->m_strName == m_strlistClockDir.at(1))
			{
				m_cmbList[nIndex]->setCurrentIndex(1);
			}
			else
				m_cmbList[nIndex]->setCurrentIndex(-1);
		}
		else
			m_cmbList[nIndex]->setCurrentIndex(-1);
	}
}

void  QCharElementDlg::SetCharElementDlgFont()
{
	m_cmbElementType->setFont(*g_pSttGlobalFont);
//	m_editErrorLen->setFont(*g_pSttGlobalFont);
	m_editTestPoint->setFont(*g_pSttGlobalFont);
	m_labelElementType->setFont(*g_pSttGlobalFont);
//	m_labelErrorLen->setFont(*g_pSttGlobalFont);
	m_labelTestPoint->setFont(*g_pSttGlobalFont);
}


BOOL QCharElementDlg::IsEditText()
{
	if (m_editTestPoint->text().isEmpty())
	{
        CXMessageBox::information(this, g_sLangTxt_Message,  /* "请输入数值，不能为空！" */ g_sLangTxt_Native_EnterNum);
		return true;
	}

//	if(m_editErrorLen->text().isEmpty())
//	{
//        CXMessageBox::information(this, g_sLangTxt_Message, /* "请输入数值，不能为空！" */ g_sLangTxt_Native_EnterNum);
//		return true;
//	}

	for(int i = 0;i <m_editList.size();i++)
	{
		CString strEditText = m_editList.at(i)->text();

		if (strEditText.isEmpty())
		{
            CXMessageBox::information(this, g_sLangTxt_Message, /* "请输入数值，不能为空！" */ g_sLangTxt_Native_EnterNum);
			return true;
		}
	}

	return FALSE;
}
void QCharElementDlg::slot_ImpedanceChanged(bool bIsrBtnAmpAngleChecked)
{
  
	QString strEdit1 ;
	QString strEdit2 ;

   if (bIsrBtnAmpAngleChecked)
   {
      m_bIsAmpAngleChecked = true;
      
	  switch (m_cmbElementType->currentIndex())
	  {
	  case STT_CHAR_ELEMENT_TYPE_LINED:
		  {		
			CString strText = _T("起始点-幅值");
			m_labelList[0]->setText(strText);
            strText = _T("起始点-相位");
			m_labelList[1]->setText(strText);
			strText = _T("终止点-幅值");
			m_labelList[2]->setText(strText);
			strText = _T("终止点-相位");
			m_labelList[3]->setText(strText);

			strEdit1 = GetImpedanceByXY("Amp",m_editList[0]->text(),m_editList[1]->text());
            strEdit2 = GetImpedanceByXY("Angle",m_editList[0]->text(),m_editList[1]->text());
			m_editList[0]->setText(strEdit1);
			m_editList[1]->setText(strEdit2);
			strEdit1 = GetImpedanceByXY("Amp",m_editList[2]->text(),m_editList[3]->text());
			strEdit2 = GetImpedanceByXY("Angle",m_editList[2]->text(),m_editList[3]->text());
			m_editList[2]->setText(strEdit1);
			m_editList[3]->setText(strEdit2);
		}	
		break;
	  case STT_CHAR_ELEMENT_TYPE_LINER:
		{
			CString strText = _T("起始点-幅值");
			m_labelList[0]->setText(strText);
			strText = _T("起始点-相位");
			m_labelList[1]->setText(strText);

			strEdit1 = GetImpedanceByXY("Amp",m_editList[0]->text(),m_editList[1]->text());
			strEdit2 = GetImpedanceByXY("Angle",m_editList[0]->text(),m_editList[1]->text());
			m_editList[0]->setText(strEdit1);
			m_editList[1]->setText(strEdit2);
		}break;
	  case STT_CHAR_ELEMENT_TYPE_LINE:
		 {

			CString strText = _T("起始点-幅值");
			m_labelList[0]->setText(strText);
			strText = _T("起始点-相位");
			m_labelList[1]->setText(strText);

			strEdit1 = GetImpedanceByXY("Amp",m_editList[0]->text(),m_editList[1]->text());
			strEdit2 = GetImpedanceByXY("Angle",m_editList[0]->text(),m_editList[1]->text());
			m_editList[0]->setText(strEdit1);
			m_editList[1]->setText(strEdit2);
		 }break;
	  case STT_CHAR_ELEMENT_TYPE_ARC:
		  {
			CString strText = _T("幅值-圆心");
			m_labelList[0]->setText(strText);
			strText = _T("相位-圆心");
		    m_labelList[1]->setText(strText);

			strEdit1 = GetImpedanceByXY("Amp",m_editList[0]->text(),m_editList[1]->text());
			strEdit2 = GetImpedanceByXY("Angle",m_editList[0]->text(),m_editList[1]->text());
			m_editList[0]->setText(strEdit1);
			m_editList[1]->setText(strEdit2);
		  }break;
	  case STT_CHAR_ELEMENT_TYPE_ARCP:
		  {
			CString strText = _T("幅值-圆心");
			m_labelList[0]->setText(strText);
			strText = _T("相位-圆心");
			m_labelList[1]->setText(strText);

			strEdit1 = GetImpedanceByXY("Amp",m_editList[0]->text(),m_editList[1]->text());
			strEdit2 = GetImpedanceByXY("Angle",m_editList[0]->text(),m_editList[1]->text());
			m_editList[0]->setText(strEdit1);
			m_editList[1]->setText(strEdit2);
		  }break;
	  }
   } 
   else
   {
	   m_bIsAmpAngleChecked = false;
	   switch (m_cmbElementType->currentIndex())
	   {
	   case STT_CHAR_ELEMENT_TYPE_LINED:
		   {		
			   m_labelList[0]->setText(g_sLangTxt_State_startingPointR);
			   m_labelList[1]->setText(g_sLangTxt_State_EdgeTestPointX);
			   m_labelList[2]->setText(g_sLangTxt_State_EndPointR);
			   m_labelList[3]->setText(g_sLangTxt_State_EndPointX);

			   strEdit1 = GetXYByImpedance("X",m_editList[0]->text(),m_editList[1]->text());
			   strEdit2 = GetXYByImpedance("Y",m_editList[0]->text(),m_editList[1]->text());
			   m_editList[0]->setText(strEdit1);
			   m_editList[1]->setText(strEdit2);
			   strEdit1 = GetXYByImpedance("X",m_editList[2]->text(),m_editList[3]->text());
			   strEdit2 = GetXYByImpedance("Y",m_editList[2]->text(),m_editList[3]->text());
			   m_editList[2]->setText(strEdit1);
			   m_editList[3]->setText(strEdit2);

		   }	
		   break;
	   case STT_CHAR_ELEMENT_TYPE_LINER:
		   {

			   m_labelList[0]->setText(g_sLangTxt_State_startingPointR);
			   m_labelList[1]->setText(g_sLangTxt_State_EdgeTestPointX);

			   strEdit1 = GetXYByImpedance("X",m_editList[0]->text(),m_editList[1]->text());
			   strEdit2 = GetXYByImpedance("Y",m_editList[0]->text(),m_editList[1]->text());
			   m_editList[0]->setText(strEdit1);
			   m_editList[1]->setText(strEdit2);

		   }break;
	   case STT_CHAR_ELEMENT_TYPE_LINE:
		   {

			   m_labelList[0]->setText(g_sLangTxt_State_startingPointR);
			   m_labelList[1]->setText(g_sLangTxt_State_EdgeTestPointX);

			   strEdit1 = GetXYByImpedance("X",m_editList[0]->text(),m_editList[1]->text());
			   strEdit2 = GetXYByImpedance("Y",m_editList[0]->text(),m_editList[1]->text());
			   m_editList[0]->setText(strEdit1);
			   m_editList[1]->setText(strEdit2);
			  
		   }break;
	   case STT_CHAR_ELEMENT_TYPE_ARC:
		   {
			   m_labelList[0]->setText(g_sLangTxt_State_CenterX);
			   m_labelList[1]->setText(g_sLangTxt_State_CenterY);

			   strEdit1 = GetXYByImpedance("X",m_editList[0]->text(),m_editList[1]->text());
			   strEdit2 = GetXYByImpedance("Y",m_editList[0]->text(),m_editList[1]->text());
			   m_editList[0]->setText(strEdit1);
			   m_editList[1]->setText(strEdit2);

		   }break;
	   case STT_CHAR_ELEMENT_TYPE_ARCP:
		   {
			   m_labelList[0]->setText(g_sLangTxt_State_CenterX);
			   m_labelList[1]->setText(g_sLangTxt_State_CenterY);

			   strEdit1 = GetXYByImpedance("X",m_editList[0]->text(),m_editList[1]->text());
			   strEdit2 = GetXYByImpedance("Y",m_editList[0]->text(),m_editList[1]->text());
			   m_editList[0]->setText(strEdit1);
			   m_editList[1]->setText(strEdit2);

		   }break;
	   }
   }
}
CString QCharElementDlg::GetXYByImpedance(QString strXY,QString strAmp,QString strAngle)
{
	double  dCoordsValue ;

    if(strXY.compare("X") == 0)
	{
		dCoordsValue = strAmp.toDouble() * cos(strAngle.toDouble() * _PI / 180);
	}
	else
	{
		dCoordsValue = strAmp.toDouble() * sin(strAngle.toDouble() * _PI / 180);
	}
	return QString::number(dCoordsValue, 'f', 2);
}
CString QCharElementDlg::GetImpedanceByXY(QString strAmpAngle,CString strAmp,CString strAngle)
{
	double  dImpedanceValue ;

	if(strAmpAngle.compare("Amp") == 0)
	{
		dImpedanceValue = sqrt(strAmp.toDouble() * strAmp.toDouble()+strAngle.toDouble() * strAngle.toDouble());
		return QString::number(dImpedanceValue, 'f', 2);
	}
	else
	{
		dImpedanceValue = atan2(strAngle.toDouble(),strAmp.toDouble()) * 180 / _PI;
		return QString::number(dImpedanceValue, 'f', 0);
	}
	
}
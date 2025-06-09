#include "stdafx.h"
#include "QCharElementDlg.h"
#include "../ReportView/XLangResource_PowerTestWin.h"

QCharElementDlg::QCharElementDlg( CCharElement *pCharElement, QWidget *parent )
	:QDialog(parent)
{
	this->setWindowTitle(/*QObject::tr("特性曲线边元素")*/g_sLangTxt_State_CharCurEdgeElements);

	m_pCurCharElement = pCharElement;
	m_pNewCharElement = NULL;
	InitTopUI();
	InitParaUI(GetElementType());
	InitButton();

	if (m_pCurCharElement != NULL)
	{
		SetParaData();
	}
	setLayout(m_MainLayout);
	m_nIsOK = 0;
}

QCharElementDlg::~QCharElementDlg()
{

}

void QCharElementDlg::InitTopUI()
{
	m_strlistEleType<</*tr("线段(lined)")*/g_sLangTxt_Lined<</*tr("圆(mho)")*/g_sLangTxt_Mho<</*tr("透镜(lens)")*/g_sLangTxt_Lens<</*tr("射线(liner)")*/g_sLangTxt_Liner<</*tr("直线(line)")*/g_sLangTxt_Line<</*tr("圆弧(arc)")*/g_sLangTxt_Arc<</*tr("圆弧(arcp)")*/g_sLangTxt_Arcp;
	m_strlistDir<<tr("LEFT")<<tr("RIGHT");
	m_strlistClockDir<</*tr("逆时针")*/g_sLangTxt_Gradient_Anticlockwise<</*tr("顺时针")*/g_sLangTxt_Gradient_Clockwise;

	m_MainLayout = new QVBoxLayout();

	m_TopLayout = new QGridLayout();
	m_ParaLayout = new QGridLayout();
	m_BottomLayout = new QHBoxLayout();

	QFont ft("Microsoft YaHei", 10);
	int nHeight = 25;

	m_MainLayout->addLayout(m_TopLayout);
	m_MainLayout->addLayout(m_ParaLayout);
	m_MainLayout->addStretch();
	m_MainLayout->addLayout(m_BottomLayout);

	m_labelElementType = new QLabel();
	m_labelElementType->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_labelElementType->setText(/*QObject::tr("边元素类型")*/g_sLangTxt_State_TheEdgeElementType);
	m_labelElementType->setFont(ft);
	m_labelElementType->setFixedHeight(nHeight);
	m_labelElementType->setFixedWidth(100);
	m_TopLayout->addWidget(m_labelElementType,0,0);
	m_cmbElementType = new QComboBox;
	m_cmbElementType->addItems(m_strlistEleType);
	m_cmbElementType->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_cmbElementType->setCurrentIndex(GetElementType());
	m_cmbElementType->setFont(ft);
	m_cmbElementType->setFixedHeight(nHeight);
	m_TopLayout->addWidget(m_cmbElementType,0,1);

	m_labelErrorLen = new QLabel();
	m_labelErrorLen->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_labelErrorLen->setText(/*QObject::tr("误差带长度")*/g_sLangTxt_State_ErrorBandLength);
	m_labelErrorLen->setFont(ft);
	m_labelErrorLen->setFixedHeight(nHeight);
	m_labelErrorLen->setFixedWidth(100);
	m_TopLayout->addWidget(m_labelErrorLen,1,0);
	m_editErrorLen = new QLineEdit;
	m_editErrorLen->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_editErrorLen->setFont(ft);
	m_editErrorLen->setFixedHeight(nHeight);
	m_TopLayout->addWidget(m_editErrorLen,1,1);

	m_labelTestPoint = new QLabel();
	m_labelTestPoint->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_labelTestPoint->setText(/*QObject::tr("边测试点数")*/g_sLangTxt_State_EdgeTestPoints);
	m_labelTestPoint->setFont(ft);
	m_labelTestPoint->setFixedHeight(nHeight);
	m_labelTestPoint->setFixedWidth(100);
	m_TopLayout->addWidget(m_labelTestPoint,2,0);
	m_editTestPoint = new QLineEdit;
	m_editTestPoint->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_editTestPoint->setFont(ft);
	m_editTestPoint->setFixedHeight(nHeight);
	m_TopLayout->addWidget(m_editTestPoint,2,1);
	
	if (m_pCurCharElement)
	{
		m_editErrorLen->setText(m_pCurCharElement->m_strErrLength);
		long *nTestPoint = m_pCurCharElement->GetTestPointsRef();
		m_editTestPoint->setText(QString::number(*nTestPoint));
	}

	connect(m_cmbElementType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ElementTypeChanged(int)));
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

	if (nType == 0)
	{
		AddLabelToList(/*QObject::tr("起始点-R")*/g_sLangTxt_State_startingPointR,0,0);
		AddEditToList(0,1);

		AddLabelToList(/*QObject::tr("起始点-X")*/g_sLangTxt_State_EdgeTestPointX,1,0);
		AddEditToList(1,1);

		AddLabelToList(/*QObject::tr("终止点-R")*/g_sLangTxt_State_EndPointR,2,0);
		AddEditToList(2,1);

		AddLabelToList(/*QObject::tr("终止点-X")*/g_sLangTxt_State_EndPointX,3,0);
		AddEditToList(3,1);

		AddLabelToList(/*QObject::tr("方向")*/g_sLangTxt_State_Direction,4,0);
		QComboBox *cmbTemp = new QComboBox;
		cmbTemp->addItems(m_strlistDir);
		cmbTemp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		cmbTemp->setCurrentIndex(-1);
		m_ParaLayout->addWidget(cmbTemp,4,1);
		m_cmbList.append(cmbTemp);
	}
	else if (nType == 1)
	{
		AddLabelToList(/*QObject::tr("正向到达")*/g_sLangTxt_State_PositiveArrival,0,0);
		AddEditToList(0,1);

		AddLabelToList(/*QObject::tr("角度")*/g_sLangTxt_State_ANgle,1,0);
		AddEditToList(1,1);

		AddLabelToList(/*QObject::tr("偏移")*/g_sLangTxt_State_Offset,2,0);
		AddEditToList(2,1);
	}
	else if (nType == 2)
	{
		AddLabelToList(/*QObject::tr("正向到达")*/g_sLangTxt_State_PositiveArrival,0,0);
		AddEditToList(0,1);

		AddLabelToList(/*QObject::tr("角度")*/g_sLangTxt_State_ANgle,1,0);
		AddEditToList(1,1);

		AddLabelToList(/*QObject::tr("偏移")*/g_sLangTxt_State_Offset,2,0);
		AddEditToList(2,1);

		AddLabelToList(/*QObject::tr("宽度")*/g_sLangTxt_State_Width,3,0);
		AddEditToList(3,1);
	}
	else if (nType == 3)
	{
		AddLabelToList(/*QObject::tr("起始点-R")*/g_sLangTxt_State_startingPointR,0,0);
		AddEditToList(0,1);

		AddLabelToList(/*QObject::tr("起始点-X")*/g_sLangTxt_State_EdgeTestPointX,1,0);
		AddEditToList(1,1);

		AddLabelToList(/*QObject::tr("角度")*/g_sLangTxt_State_ANgle,2,0);
		AddEditToList(2,1);

		AddLabelToList(/*QObject::tr("方向")*/g_sLangTxt_State_Direction,3,0);
		QComboBox *cmbTemp = new QComboBox;
		cmbTemp->addItems(m_strlistDir);
		cmbTemp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		cmbTemp->setCurrentIndex(-1);
		m_ParaLayout->addWidget(cmbTemp,3,1);
		m_cmbList.append(cmbTemp);
	}
	else if (nType == 4)
	{
		AddLabelToList(/*QObject::tr("起始点-R")*/g_sLangTxt_State_startingPointR,0,0);
		AddEditToList(0,1);

		AddLabelToList(/*QObject::tr("起始点-X")*/g_sLangTxt_State_EdgeTestPointX,1,0);
		AddEditToList(1,1);

		AddLabelToList(/*QObject::tr("角度")*/g_sLangTxt_State_ANgle,2,0);
		AddEditToList(2,1);

		AddLabelToList(/*QObject::tr("方向")*/g_sLangTxt_State_Direction,3,0);
		QComboBox *cmbTemp = new QComboBox;
		cmbTemp->addItems(m_strlistDir);
		cmbTemp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		cmbTemp->setCurrentIndex(-1);
		m_ParaLayout->addWidget(cmbTemp,3,1);
		m_cmbList.append(cmbTemp);
	}
	else if (nType == 5)
	{
		AddLabelToList(/*QObject::tr("x-圆心")*/g_sLangTxt_State_CenterX,0,0);
		AddEditToList(0,1);

		AddLabelToList(/*QObject::tr("y-圆心")*/g_sLangTxt_State_CenterY,1,0);
		AddEditToList(1,1);

		AddLabelToList(/*QObject::tr("半径")*/g_sLangTxt_State_Radius,2,0);
		AddEditToList(2,1);

		AddLabelToList(/*QObject::tr("起始角度")*/g_sLangTxt_State_StartingAngle,3,0);
		AddEditToList(3,1);

		AddLabelToList(/*QObject::tr("终止角度")*/g_sLangTxt_State_TerminationAngle,4,0);
		AddEditToList(4,1);

		AddLabelToList(/*QObject::tr("方向")*/g_sLangTxt_State_Direction,5,0);
		QComboBox *cmbTemp = new QComboBox;
		cmbTemp->addItems(m_strlistDir);
		cmbTemp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		cmbTemp->setCurrentIndex(-1);
		m_ParaLayout->addWidget(cmbTemp,5,1);
		m_cmbList.append(cmbTemp);

		AddLabelToList(/*QObject::tr("时钟方向")*/g_sLangTxt_State_ClockDirection,6,0);
		cmbTemp = new QComboBox;
		cmbTemp->addItems(m_strlistClockDir);
		cmbTemp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		cmbTemp->setCurrentIndex(-1);
		m_ParaLayout->addWidget(cmbTemp,6,1);
		m_cmbList.append(cmbTemp);
	}
	else if (nType == 6)
	{
		AddLabelToList(/*QObject::tr("x-圆心")*/g_sLangTxt_State_CenterX,0,0);
		AddEditToList(0,1);

		AddLabelToList(/*QObject::tr("y-圆心")*/g_sLangTxt_State_CenterY,1,0);
		AddEditToList(1,1);

		AddLabelToList(/*QObject::tr("半径")*/g_sLangTxt_State_Radius,2,0);
		AddEditToList(2,1);

		AddLabelToList(/*QObject::tr("起始角度")*/g_sLangTxt_State_StartingAngle,3,0);
		AddEditToList(3,1);

		AddLabelToList(/*QObject::tr("终止角度")*/g_sLangTxt_State_TerminationAngle,4,0);
		AddEditToList(4,1);

		AddLabelToList(/*QObject::tr("方向")*/g_sLangTxt_State_Direction,5,0);
		QComboBox *cmbTemp = new QComboBox;
		cmbTemp->addItems(m_strlistDir);
		cmbTemp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		cmbTemp->setCurrentIndex(-1);
		m_ParaLayout->addWidget(cmbTemp,5,1);
		m_cmbList.append(cmbTemp);

		AddLabelToList(/*QObject::tr("时钟方向")*/g_sLangTxt_State_ClockDirection,6,0);
		cmbTemp = new QComboBox;
		cmbTemp->addItems(m_strlistClockDir);
		cmbTemp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		cmbTemp->setCurrentIndex(-1);
		m_ParaLayout->addWidget(cmbTemp,6,1);
		m_cmbList.append(cmbTemp);
	}
}

void QCharElementDlg::InitButton()
{
	m_pbtnOK = new QPushButton(this);
	m_pbtnOK->setText(/*QObject::tr("确认")*/g_sLangTxt_Native_Confm);
	m_pbtnOK->setFixedSize(100,26);
	m_pbtnOK->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_pbtnOK->setIcon (QPixmap( "./images/Check.png"));
	m_BottomLayout->addWidget(m_pbtnOK);

	m_pbtnCancel = new QPushButton(this);
	m_pbtnCancel->setText(/*QObject::tr("取消")*/g_sLangTxt_Cancel);
	m_pbtnCancel->setFixedSize(100,26);
	m_pbtnCancel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_pbtnCancel->setIcon (QPixmap( "./images/Cancel.png"));
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
		case 0:
			{
				CCharElementLined *pChar = (CCharElementLined *)m_pCurCharElement;
				m_editList[0]->setText(pChar->m_strXb);
				m_editList[1]->setText(pChar->m_strYb);
				m_editList[2]->setText(pChar->m_strXe);
				m_editList[3]->setText(pChar->m_strYe);
				SetComboIndex(0,pChar->m_strDir);
			}break;
		case 1:
			{
				CCharElementMho *pChar = (CCharElementMho *)m_pCurCharElement;
				m_editList[0]->setText(pChar->m_strForwardReach);
				m_editList[1]->setText(pChar->m_strAngle);
				m_editList[2]->setText(pChar->m_strOffset);
			}break;
		case 2:
			{
				CCharElementLens *pChar = (CCharElementLens *)m_pCurCharElement;
				m_editList[0]->setText(pChar->m_strForwardReach);
				m_editList[1]->setText(pChar->m_strAngle);
				m_editList[2]->setText(pChar->m_strOffset);
				m_editList[3]->setText(pChar->m_strWidth);
			}break;
		case 3:
			{
				CCharElementLiner *pChar = (CCharElementLiner *)m_pCurCharElement;
				m_editList[0]->setText(pChar->m_strXb);
				m_editList[1]->setText(pChar->m_strYb);
				m_editList[2]->setText(pChar->m_strAngle);
				SetComboIndex(0,pChar->m_strDir);
			}break;
		case 4:
			{
				CCharElementLine *pChar = (CCharElementLine *)m_pCurCharElement;
				m_editList[0]->setText(pChar->m_strX);
				m_editList[1]->setText(pChar->m_strY);
				m_editList[2]->setText(pChar->m_strAngle);
				SetComboIndex(0,pChar->m_strDir);
			}break;
		case 5:
			{
				CCharElementArc *pChar = (CCharElementArc *)m_pCurCharElement;
				m_editList[0]->setText(pChar->m_strXCenter);
				m_editList[1]->setText(pChar->m_strYCenter);
				m_editList[2]->setText(pChar->m_strRadius);
				m_editList[3]->setText(pChar->m_strAngleBegin);
				m_editList[4]->setText(pChar->m_strAngleEnd);
				SetComboIndex(0,pChar->m_strDir);
				SetComboIndex(1,pChar->m_strClockwise);
			}break;
		case 6:
			{
				CCharElementArcp *pChar = (CCharElementArcp *)m_pCurCharElement;
				m_editList[0]->setText(pChar->m_strZ);
				m_editList[1]->setText(pChar->m_strPh);
				m_editList[2]->setText(pChar->m_strRadius);
				m_editList[3]->setText(pChar->m_strAngleBegin);
				m_editList[4]->setText(pChar->m_strAngleEnd);
				SetComboIndex(0,pChar->m_strDir);
				SetComboIndex(1,pChar->m_strClockwise);
			}break;
		}
	}
}

void QCharElementDlg::CreateNewElement()
{
	int nIndex = m_cmbElementType->currentIndex();
	
	switch (nIndex)
	{
	case 0:
		{
			m_pNewCharElement = new CCharElementLined;
			((CCharElementLined*)m_pNewCharElement)->m_strXb = m_editList[0]->text();
			((CCharElementLined*)m_pNewCharElement)->m_strYb = m_editList[1]->text();
			((CCharElementLined*)m_pNewCharElement)->m_strXe = m_editList[2]->text();
			((CCharElementLined*)m_pNewCharElement)->m_strYe = m_editList[3]->text();
			int n = m_cmbList.at(0)->currentIndex();
			if (n < 0 || n > 1)
			{
				n = 0;
			}
			((CCharElementLined*)m_pNewCharElement)->m_strDir = m_strlistDir.at(n);
		}break;
	case 1:
		{
			m_pNewCharElement = new CCharElementMho;
			((CCharElementMho*)m_pNewCharElement)->m_strForwardReach = m_editList[0]->text();
			((CCharElementMho*)m_pNewCharElement)->m_strAngle = m_editList[1]->text();
			((CCharElementMho*)m_pNewCharElement)->m_strOffset = m_editList[2]->text();
		}break;
	case 2:
		{
			m_pNewCharElement = new CCharElementLens;
			((CCharElementLens*)m_pNewCharElement)->m_strForwardReach = m_editList[0]->text();
			((CCharElementLens*)m_pNewCharElement)->m_strAngle = m_editList[1]->text();
			((CCharElementLens*)m_pNewCharElement)->m_strOffset = m_editList[2]->text();
			((CCharElementLens*)m_pNewCharElement)->m_strWidth = m_editList[3]->text();
		}break;
	case 3:
		{
			m_pNewCharElement = new CCharElementLiner;
			((CCharElementLiner*)m_pNewCharElement)->m_strXb = m_editList[0]->text();
			((CCharElementLiner*)m_pNewCharElement)->m_strYb = m_editList[1]->text();
			((CCharElementLiner*)m_pNewCharElement)->m_strAngle = m_editList[2]->text();
			int n = m_cmbList.at(0)->currentIndex();
			if (n < 0 || n > 1)
			{
				n = 0;
			}
			((CCharElementLiner*)m_pNewCharElement)->m_strDir = m_strlistDir.at(n);
		}break;
	case 4:
		{
			m_pNewCharElement = new CCharElementLine;
			((CCharElementLine*)m_pNewCharElement)->m_strX = m_editList[0]->text();
			((CCharElementLine*)m_pNewCharElement)->m_strY = m_editList[1]->text();
			((CCharElementLine*)m_pNewCharElement)->m_strAngle = m_editList[2]->text();
			int n = m_cmbList.at(0)->currentIndex();
			if (n < 0 || n > 1)
			{
				n = 0;
			}
			((CCharElementLine*)m_pNewCharElement)->m_strDir = m_strlistDir.at(n);
		}break;
	case 5:
		{
			m_pNewCharElement = new CCharElementArc;
			((CCharElementArc*)m_pNewCharElement)->m_strXCenter = m_editList[0]->text();
			((CCharElementArc*)m_pNewCharElement)->m_strYCenter = m_editList[1]->text();
			((CCharElementArc*)m_pNewCharElement)->m_strRadius = m_editList[2]->text();
			((CCharElementArc*)m_pNewCharElement)->m_strAngleBegin = m_editList[3]->text();
			((CCharElementArc*)m_pNewCharElement)->m_strAngleEnd = m_editList[4]->text();
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
			((CCharElementArc*)m_pNewCharElement)->m_strDir = m_strlistDir.at(n);
			((CCharElementArc*)m_pNewCharElement)->m_strClockwise = m_strlistClockDir.at(n1);
		}break;
	case 6:
		{
			m_pNewCharElement = new CCharElementArcp;
			((CCharElementArcp*)m_pNewCharElement)->m_strZ = m_editList[0]->text();
			((CCharElementArcp*)m_pNewCharElement)->m_strPh = m_editList[1]->text();
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

	m_pNewCharElement->m_strErrLength = m_editErrorLen->text();
	long *nTestPoint = m_pNewCharElement->GetTestPointsRef();
	*nTestPoint = m_editTestPoint->text().toLong();
}

void QCharElementDlg::slot_ElementTypeChanged(int nIndex)
{
	InitParaUI(nIndex);
	if (m_pCurCharElement != NULL)
	{
		SetParaData();
	}
}

void QCharElementDlg::slot_PbnOkClicked()
{
	CreateNewElement();
	m_nIsOK = 1;
	close();
}

void QCharElementDlg::slot_PbnCancelClicked()
{
	m_nIsOK = 2;
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
		nIndex = 0;
	else if (m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTMHO)
		nIndex = 1;
	else if (m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTLENS)
		nIndex = 2;
	else if (m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTLINER)
		nIndex = 3;
	else if (m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTLINE)
		nIndex = 4;
	else if (m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTARC)
		nIndex = 5;
	else if (m_pCurCharElement->GetClassID() == CHARCLASSID_CCHARELEMENTARCP)
		nIndex = 6;

	return nIndex;
}

void QCharElementDlg::AddLabelToList( QString str,int nRow,int nCol )
{
	QFont ft("Microsoft YaHei", 10);
	int nHeight = 25;

	QLabel *tempLabel = new QLabel;
	tempLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	tempLabel->setText(str);
	tempLabel->setFont(ft);
	tempLabel->setFixedHeight(nHeight);
	tempLabel->setFixedWidth(100);
	m_ParaLayout->addWidget(tempLabel,nRow,nCol);
	m_labelList.append(tempLabel);
}

void QCharElementDlg::AddEditToList( int nRow,int nCol )
{
	QFont ft("Microsoft YaHei", 10);
	int nHeight = 25;

	QLineEdit *tempEdit = new QLineEdit;
	tempEdit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	tempEdit->setFont(ft);
	tempEdit->setFixedHeight(nHeight);
	m_ParaLayout->addWidget(tempEdit,nRow,nCol);
	m_editList.append(tempEdit);
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
		if (strText == m_strlistClockDir.at(0))
		{
			m_cmbList[nIndex]->setCurrentIndex(0);
		}
		else if (strText == m_strlistClockDir.at(1))
		{
			m_cmbList[nIndex]->setCurrentIndex(1);
		}
		else
			m_cmbList[nIndex]->setCurrentIndex(-1);
	}
}


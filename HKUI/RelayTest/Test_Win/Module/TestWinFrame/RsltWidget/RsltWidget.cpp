#include "RsltWidget.h"
#include <QGridLayout>
#include "QExprComboBox.h"
#include "../../SttXTestMngrBaseApp.h"
#include <QFont>

//////////////////////////////////////////////////////////////////////////
QRsltWidget::QRsltWidget(PTMT_PARAS_HEAD pPTMT_PARAS_HEAD, QWidget *parent)
: QWidget(parent)
{
	m_pTmt_Paras_Head  =  pPTMT_PARAS_HEAD ;
	m_MainLayout = NULL;
	for ( int i = 0; i < MAX_EXPR_CNT; i++)
		m_strUnit[i]  =  tr(" (s) ");

}

QRsltWidget::~QRsltWidget()
{

}

void QRsltWidget::SetUnit(int nCount, QString strUnit[])
{
	for (int i = 0; i < nCount; i++)
		m_strUnit[i]   =  strUnit[i];
}

int QRsltWidget::GetMaxCountExpr(CDataGroup *pList)
{
	POS pos = pList->GetHeadPosition();
	int i = 0;
	CDvmData *pData = NULL;
	CString strExprText;
	int nCount = 0;



	QFont  f  = QWidget::font();

	QFontMetrics fm(f);


	while (pos != NULL)
	{
		pData = (CDvmData*)pList->GetNext(pos);

		//调用将表达式转换成文本的函数
		strExprText = g_oTmtTestRsltExprImp.GetExprScriptText(pData->m_strValue);

		QRect rec = fm.boundingRect(strExprText);

		//QRect rec = fm.boundingRect("这是要获取宽度和高度的字符串");
		//字符串所占的像素宽度,高度

		int textWidth = rec.width();

		if (nCount < textWidth)
			nCount = textWidth;
		//insertItem(i++,strExprText);
	}

	return nCount;
}

//创建相关控件布局等
void QRsltWidget::InitUI()
{	
	Reset();//假如原来已经创建了控件，删除掉；

	CString strMacroID = m_pTmt_Paras_Head->m_pszMacroID;
	CSttTmtRsltExprDefine*  pSttTmtRsltExprDefine  = g_oSttTmtRsltExprDefineMngr.FindRsltExprDefine(strMacroID);


	if (pSttTmtRsltExprDefine->m_pExprDatasDef == NULL&& pSttTmtRsltExprDefine->m_pExprViewDatasDef==NULL)
		return;

	POS pos  =  pSttTmtRsltExprDefine->m_pExprDatasDef->GetHeadPosition();
	CDvmData *pDvmData = NULL;

	 m_listName.clear();
	 m_listExpr.clear();
	 m_listRsltName.clear();
	 m_listRsltValue.clear();

	 m_MainLayout = new QGridLayout();
	 //	m_MainLayout->setSpacing(10);
	 //m_MainLayout->setMargin(5);

	QLabel * tempLabel;

// 
// 	QFont font1 = QWidget::font();
// 	int nFontWidth = f.width();
// 
// 	QFontMetrics fm(font1);
// 	//QRect rec = fm.boundingRect("这是要获取宽度和高度的字符串");
// 	//字符串所占的像素宽度,高度
// 
// 	int textWidth = rec.width();

	int nIndex = 0;

	CString strRsltValue[JDG_COUNT];

	//例如“Common”
	QRsltExprMngr::InitDataGroupByID(m_pTmt_Paras_Head->m_oRsltExprMngr.m_pszExprGroupID);
	CDataGroup *pDataExpr = NULL;
	PTMT_PARAS_RSLT_EXPR  pExpr = NULL;

	QExprComboBox *pCmbFaultTrigMode;        
	QFloatLineEdit *pFloatLineEdit;                  

	while(pos)
	{
		pExpr = &m_pTmt_Paras_Head->m_oRsltExprMngr.m_RsltExprs[nIndex];
		pDvmData = (CDvmData*)pSttTmtRsltExprDefine->m_pExprDatasDef->GetNext(pos);
		pDataExpr = QRsltExprMngr::FindDataGroupByID(pDvmData->m_strID);
		int nExprCnt  = pDataExpr->GetCount();
	
		tempLabel = new QLabel();
		tempLabel->setSizePolicy(QSizePolicy::Preferred,  QSizePolicy::Expanding);//20211030 sf 自适应分辨率
		tempLabel->setText(pDvmData->m_strName);
		//tempLabel->setFixedWidth(80); 		
		tempLabel->setFixedHeight(30); //内容宽
		tempLabel->setAlignment(Qt::AlignCenter);

		//m_MainLayout->setColumnStretch(0, 1); 
		m_MainLayout->addWidget(tempLabel,   nIndex,  0);	
		m_listName.append(tempLabel);

		int  nMaxCount = GetMaxCountExpr(pDataExpr);

		pCmbFaultTrigMode = new QExprComboBox(pDataExpr, pExpr->m_pRsltExpr , this);
		pCmbFaultTrigMode->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		//pCmbFaultTrigMode->setFixedWidth(580); //内容宽
		pCmbFaultTrigMode->setFixedHeight(30); //内容宽	
		pCmbFaultTrigMode->setSizeAdjustPolicy(QExprComboBox::AdjustToMinimumContentsLengthWithIcon );//AdjustToContents
		connect(pCmbFaultTrigMode, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_currentIndex(int)));


		float maxLen = nMaxCount*1.02;
		pCmbFaultTrigMode->setStyleSheet("QAbstractItemView{min-width:" + QString::number(maxLen) + "px;}");

		m_MainLayout->addWidget(pCmbFaultTrigMode,   nIndex,  1);
		m_listExpr.append(pCmbFaultTrigMode);
		//m_MainLayout->setColumnStretch(1,  4); 
		nIndex++;
	}

	m_MainLayout -> setColumnStretch(0,  1);  
	m_MainLayout -> setColumnStretch(1,  5);  
	
	
	nIndex = 0;
	pos  =  pSttTmtRsltExprDefine->m_pExprViewDatasDef->GetHeadPosition();
	while(pos)
	{
		pDvmData = (CDvmData*)pSttTmtRsltExprDefine->m_pExprViewDatasDef->GetNext(pos);
		g_pTmt_TestItemResultRef->GetDataValue(pDvmData->m_strID,  strRsltValue[nIndex]);//根据ID，获取结果DataGroup中的value

		tempLabel = new QLabel();
		tempLabel->setSizePolicy(QSizePolicy::Expanding,  QSizePolicy::Expanding);
		tempLabel->setText(pDvmData->m_strName + m_strUnit[nIndex]);
		tempLabel->setFixedWidth(180); 		
		tempLabel->setFixedHeight(30); //内容宽
		//m_MainLayout->setColumnStretch(0, 1); 
		m_MainLayout->addWidget(tempLabel,   nIndex,  2);	
		m_listRsltName.append(tempLabel);

		pFloatLineEdit = new QFloatLineEdit(this);
		pFloatLineEdit->setSizePolicy(QSizePolicy::Expanding,  QSizePolicy::Expanding);

		pFloatLineEdit->setFixedWidth(80);							//内容宽
		pFloatLineEdit->setFixedHeight(30);							//内容宽	
		pFloatLineEdit->SetValue(strRsltValue[nIndex].toFloat());
		pFloatLineEdit->setDisabled(true);
		m_MainLayout->addWidget(pFloatLineEdit,   nIndex,  3);
		m_listRsltValue.append(pFloatLineEdit);
		nIndex++;
	}

	m_MainLayout -> setColumnStretch(2,  1);  
	m_MainLayout -> setColumnStretch(3,  5);  

	setLayout(m_MainLayout);

	if (g_theSttXTestMngrBaseApp->m_bViewTestStarted)
	{
		startInit();
	}
	else
	{
		stopInit();
	}
}

void QRsltWidget::Reset()
{
	 if (m_MainLayout != NULL)
	 {		
		 delete m_MainLayout;
		 m_MainLayout = NULL;
	 }

	 for (int i = 0; i < m_listExpr.size(); i++)
	 {
		 if (m_listExpr[i] != NULL)
		 {
			 delete m_listExpr[i];
			 m_listExpr[i] = NULL;
		 }
	 }

	 for (int i = 0; i < m_listRsltValue.size(); i++)
	 {
		 if (m_listRsltValue[i] != NULL)
		 {
			 delete m_listRsltValue[i];
			 m_listRsltValue[i] = NULL;
		 }
	 }

	 for (int i = 0; i < m_listName.size(); i++)
	 {
		 if (m_listName[i] != NULL)
		 {
			 delete m_listName[i];
			 m_listName[i] = NULL;
		 }
	 }

	 for (int i = 0; i < m_listRsltName.size(); i++)
	 {
		 if (m_listRsltName[i] != NULL)
		 {
			 delete m_listRsltName[i];
			 m_listRsltName[i] = NULL;
		 }
	 }
}

void QRsltWidget::SetParasHead(PTMT_PARAS_HEAD pPTMT_PARAS_HEAD)
{
	m_pTmt_Paras_Head = pPTMT_PARAS_HEAD;
}


void QRsltWidget::slot_currentIndex(int nIndex)
{
// 	QComboBox *pCombo = (QComboBox * )(sender()); //获取发送者sender（）
// 
// 	int nItemCom = 0;
// 	for (nItemCom = 0;   nItemCom < m_listExpr.size();  nItemCom++)
// 	{		
// 		if (m_listExpr[nItemCom] ==  pCombo)
// 		{
// 			break;
// 		}
// 	}
// 	CString strValue = pCombo->itemText(nIndex);
// 	CString_to_char(strValue,  m_pTmt_Paras_Head->m_oRsltExprMngr.m_RsltExprs[nItemCom].m_pRsltExpr);
	//yyj add
	if (g_theSttXTestMngrBaseApp)
	{
		g_theSttXTestMngrBaseApp->SetModifyPara();
	}
}

//yyj add 
void QRsltWidget::startInit()
{
	for (int i = 0; i < m_listExpr.size(); i++)
	{
		if (m_listExpr[i] != NULL)
		{
			m_listExpr[i]->setDisabled(true);
		}
	}

	for (int i = 0; i < m_listRsltValue.size(); i++)
	{
		if (m_listRsltValue[i] != NULL)
		{
			m_listRsltValue[i]->setDisabled(true);
		}
	}
}

void QRsltWidget::stopInit()
{
	for (int i = 0; i < m_listExpr.size(); i++)
	{
		if (m_listExpr[i] != NULL)
		{
			m_listExpr[i]->setDisabled(false);
		}
	}

	for (int i = 0; i < m_listRsltValue.size(); i++)
	{
		if (m_listRsltValue[i] != NULL)
		{
			m_listRsltValue[i]->setDisabled(false);
		}
	}
}

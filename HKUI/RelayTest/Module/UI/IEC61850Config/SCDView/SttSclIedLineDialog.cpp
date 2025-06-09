#include "SttSclIedLineDialog.h"
#include "../../../XLangResource_Native.h"

QSttSclIedLineDialog::QSttSclIedLineDialog(QList<CSclVirtualSubend> *pSubData,QList<CSclVirtualSubend > *pInputData,long nType ,QDialog *parent):QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	resize(800, 600);
	setWindowTitle(g_sLangTxt_Native_vTerminalConnectDia);//tr("虚端子连接图"))
	//setCursor(Qt::ClosedHandCursor);
	m_pBtnZoomIn = NULL;
	m_pBtnZoomOut = NULL;
	m_pBtnExit = NULL;
	m_pGraphicsScene = NULL;
	m_pGraphicsView = NULL;
	m_pInputRect = NULL;
	m_pOutputRect = NULL;
	m_pAllInputCheckBox = NULL;
	m_pMainLayout = NULL;
	m_pInputData = pInputData;
	m_pOutputData = pSubData;
	m_nType = nType;
	InitData(pSubData,pInputData,nType,true);
	InitUI();
}


QSttSclIedLineDialog::~QSttSclIedLineDialog()
{
	Release();
}

void QSttSclIedLineDialog::InitUI()
{
	CString strText;
	m_pBtnZoomOut = new QPushButton(this);
	strText = g_sLangTxt_State_Magnify;
	m_pBtnZoomOut->setText(strText);
	m_pBtnZoomOut->setFont(*g_pSttGlobalFont);
	m_pBtnZoomIn = new QPushButton(this);
	strText = g_sLangTxt_State_Shrink;
	m_pBtnZoomIn->setFont(*g_pSttGlobalFont);
	m_pBtnZoomIn->setText(strText);
	m_pBtnExit = new QPushButton(this);
	strText = g_sLangTxt_Quit;//_T("退出");
	m_pBtnExit->setFont(*g_pSttGlobalFont);
	m_pBtnExit->setText(strText);

	QHBoxLayout *pHBoxLayout = new QHBoxLayout;
	m_pAllInputCheckBox = new QSttCheckBox;
	m_pAllInputCheckBox->setFont(*g_pSttGlobalFont);

	strText = g_sLangTxt_IECConfig_Screen;//_T("筛选");
	m_pAllInputCheckBox->setText(strText);
	m_pAllInputCheckBox->setChecked(false);
	pHBoxLayout->addItem(new QSpacerItem(10, 0, QSizePolicy::Fixed, QSizePolicy::Minimum)); 
	pHBoxLayout->addWidget(m_pAllInputCheckBox);
	pHBoxLayout->setMargin(0);
	pHBoxLayout->addStretch();
	pHBoxLayout->addWidget(m_pBtnZoomOut);
	pHBoxLayout->addWidget(m_pBtnZoomIn);
	pHBoxLayout->addWidget(m_pBtnExit);

	m_pMainLayout = new QVBoxLayout;
	m_pMainLayout->setMargin(0);
	m_pMainLayout->addLayout(pHBoxLayout);
	
	m_pMainLayout->addWidget(m_pGraphicsView);
	setLayout(m_pMainLayout);

	InitConnection();
}

void QSttSclIedLineDialog::UpdateUIScene()
{
	if (m_pGraphicsScene == NULL)
	{
		m_pGraphicsScene = new QGraphicsScene();
		m_pGraphicsView = new QCustomGraphicsView();
		m_pGraphicsView->setScene(m_pGraphicsScene);
	}
	else
	{
		m_pGraphicsScene->clear();
	}

	m_pGraphicsScene->addItem(m_pInputRect);
	m_pGraphicsScene->addItem(m_pOutputRect);


	for (int i = 0; i < m_pChInRightRect.size(); ++i)
	{
		if (m_pChInRightRect[i] != NULL)
		{
			m_pGraphicsScene->addItem(m_pChInRightRect[i]);
		}
	}

	for (int i = 0; i < m_pChInLeftRect.size(); ++i)
	{
		if (m_pChInLeftRect[i] != NULL)
		{
			m_pGraphicsScene->addItem(m_pChInLeftRect[i]);
		}
	}
	for (int i = 0; i < m_pArrowLine.size(); ++i)
	{
		if (m_pArrowLine[i] != NULL)
		{
			m_pGraphicsScene->addItem(m_pArrowLine[i]);
		}
	}
}

void QSttSclIedLineDialog::InitConnection()
{
	connect(m_pBtnZoomOut, SIGNAL(clicked()), this,SLOT(slot_ZoomOut()));
	connect(m_pBtnZoomIn, SIGNAL(clicked()),this, SLOT(slot_ZoomIn()));
	connect(m_pBtnExit, SIGNAL(clicked()), this,SLOT(slot_Exit()));
	connect(m_pAllInputCheckBox,SIGNAL(stateChanged(int)),this,SLOT(slot_checkbox(int)));
}

void QSttSclIedLineDialog::slot_ZoomIn()
{
	m_pGraphicsView->scale(0.8, 0.8);
}

void QSttSclIedLineDialog::slot_ZoomOut()
{
	m_pGraphicsView->scale(1.25, 1.25);
}

void QSttSclIedLineDialog::slot_Exit()
{
	close();
}

void QSttSclIedLineDialog::InitData(QList<CSclVirtualSubend> *pSubData,QList<CSclVirtualSubend> *pInputData,long nType,bool bDrawAllRects)
{
	long nHeight = 50;
	QString strName;
	if (nType == 0)//发送
	{
		for (int i = 0; i < pSubData->size(); ++i)
		{
			CSclVirtualSubend subend = pSubData->at(i);
			if (i == 0)
			{
				int index = subend.strAppID.indexOf(" "); 
				strName = subend.strAppID.left(index);
				strName = strName + " " +_T("接收");
				QSttCustomRect *pChInRect = new QSttCustomRect(QPointF(70, nHeight), 200, 40, strName, NULL);
				pChInRect->setFillColor(QColor(250, 167, 243));
				m_pChInLeftRect.append(pChInRect);

				nHeight = nHeight + 40;
			}

			strName = QString::number(subend.nInIndex) + _T("-") + subend.strIndoDesc;
			QSttCustomRect *pChRect = new QSttCustomRect(QPointF(70, nHeight), 200, 40, strName, NULL);
			pChRect->setFillColor(QColor(200, 200, 200));
			m_pChInLeftRect.append(pChRect);

			nHeight = nHeight + 40;


			if (i == pSubData->size()-1)
			{
				m_pInputRect = new QSttCustomRect(QPointF(50, 0), 250, nHeight + 30, subend.m_strID, NULL);
				m_pInputRect->setFillColor(QColor(196,243,196));
				m_pInputRect->setTextOffset(0, 20); 
				m_pInputRect->setCenterText(false);
			}
		}
		
		nHeight = 50;

		for (int i = 0; i < pInputData->size(); ++i)
		{
			CSclVirtualSubend subend = pInputData->at(i);
			if (i == 0)
			{
				QSttCustomRect *pChAppIDRect = new QSttCustomRect(QPointF(475, nHeight), 200, 40, subend.strAppID, NULL);
				pChAppIDRect->setFillColor(QColor(250, 167, 243));
				m_pChInRightRect.append(pChAppIDRect);

				nHeight = nHeight + 40;
			}

			strName = QString::number(subend.nOutIndex) + "-" + subend.strfcdaDesc;
			QSttCustomRect *pChInRect = new QSttCustomRect(QPointF(475, nHeight), 200, 40, strName, NULL);
			pChInRect->setFillColor(QColor(200, 200, 200));
			m_pChInRightRect.append(pChInRect);

			nHeight = nHeight + 40;
			
			if (i == pInputData->size()-1)
			{
				m_pOutputRect = new QSttCustomRect(QPointF(450, 0), 250, nHeight + 30, subend.m_strName, NULL);
				m_pOutputRect->setFillColor(QColor(229,242,196));
				m_pOutputRect->setTextOffset(0, 20); 
				m_pOutputRect->setCenterText(false);
			}
		}
	}
	
	if (nType == 1)//接收
	{
		for (int i = 0; i < pSubData->size(); ++i)
		{
			CSclVirtualSubend subend = pSubData->at(i);
			if (i == 0)
			{
				int index = subend.strAppID.indexOf(" "); 
				strName = subend.strAppID.left(index);
				strName = strName + " " +_T("接收");

				QSttCustomRect *pChAppIDRect = new QSttCustomRect(QPointF(475, nHeight), 200, 40, strName, NULL);
				pChAppIDRect->setFillColor(QColor(250, 167, 243));
				m_pChInRightRect.append(pChAppIDRect);

				nHeight = nHeight + 40;
			}

			strName = QString::number(subend.nInIndex) + _T("-") + subend.strIndoDesc;
			QSttCustomRect *pChInRect = new QSttCustomRect(QPointF(475, nHeight), 200, 40, strName, NULL);
			pChInRect->setFillColor(QColor(200, 200, 200));
			m_pChInRightRect.append(pChInRect);

			nHeight = nHeight + 40;

			if (i == pSubData->size()-1)
			{
				m_pInputRect = new QSttCustomRect(QPointF(50, 0), 250, nHeight + 30, subend.m_strName, NULL);
				m_pInputRect->setFillColor(QColor(196,243,196));
				m_pInputRect->setTextOffset(0, 20); 
				m_pInputRect->setCenterText(false);

				m_pOutputRect = new QSttCustomRect(QPointF(450, 0), 250, nHeight + 30, subend.m_strID, NULL);
				m_pOutputRect->setFillColor(QColor(229,242,196));
				m_pOutputRect->setTextOffset(0, 20); 
				m_pOutputRect->setCenterText(false);
			}
		}

		nHeight = 50;
		for (int i = 0; i < pInputData->size(); ++i)
		{
		
			CSclVirtualSubend subend = pInputData->at(i);
			if (i == 0)
			{
				QSttCustomRect *pChInRect = new QSttCustomRect(QPointF(70, nHeight), 200, 40, subend.strAppID, NULL);
				pChInRect->setFillColor(QColor(250, 167, 243));
				m_pChInLeftRect.append(pChInRect);
				nHeight = nHeight + 40;
			}

			strName = QString::number(subend.nOutIndex) + "-" + subend.strfcdaDesc;
			QSttCustomRect *pChRect = new QSttCustomRect(QPointF(70, nHeight), 200, 40, strName, NULL);
			pChRect->setFillColor(QColor(200, 200, 200));
			m_pChInLeftRect.append(pChRect);

			nHeight = nHeight + 40;
			
			if (i == pInputData->size()-1)
			{
				m_pInputRect->setHeight(nHeight);
			}
		}
	}

	DrawLine(pInputData,pSubData,nType,bDrawAllRects);
 
	UpdateUIScene();
}


void QSttSclIedLineDialog::DrawLine(QList<CSclVirtualSubend > *pInputData,QList<CSclVirtualSubend> *pOutputData,long nType,bool bDrawAllRects)
{
	QPointF start,end;
	CString strRectText;

	for (int i = 0; i < pInputData->size(); ++i) 
	{
		CSclVirtualSubend inputSubend = pInputData->at(i);
		CString inputID = inputSubend.m_strID;

		for (int j = 0; j < pOutputData->size(); ++j)
		{
			CSclVirtualSubend outputSubend = pOutputData->at(j);
			CString outputID = outputSubend.strfcdaDesc;

			if (inputID == outputID) 
			{
				CString strInputText,strOutputText;

				if (nType == 0)
				{
					strInputText = QString::number(inputSubend.nOutIndex) +"-" + inputSubend.strfcdaDesc;//输入端
					strOutputText =  QString::number(outputSubend.nInIndex) +"-" + outputSubend.strIndoDesc;//输出端
				}
				else
				{
					strOutputText = QString::number(inputSubend.nOutIndex) +"-" + inputSubend.strfcdaDesc;
					strInputText =  QString::number(outputSubend.nInIndex) +"-" + outputSubend.strIndoDesc;
				}

				for (int i = 0; i < m_pChInLeftRect.size(); ++i)
				{
					QSttCustomRect* leftRect = m_pChInLeftRect.at(i);
					strRectText = leftRect->getText();

					if (strOutputText == strRectText) 
					{
			 			end = leftRect->getRightCenter();
						break;
					}
				}

				for (int j = 0; j < m_pChInRightRect.size(); ++j) 
				{
					QSttCustomRect* rightRect = m_pChInRightRect.at(j);
					strRectText= rightRect->getText();

					if (strInputText == strRectText) 
					{
						start = rightRect->getLeftCenter();
						break;
					}
				}

				if (nType == 0)
				{
			QSttCustomArrowLine *pArrow = new QSttCustomArrowLine(start,end,NULL);
			pArrow->setLineColor(QColor(238, 187, 107));
			pArrow->setHoverColor(QColor(238, 187, 107));
			m_pArrowLine.append(pArrow);
				}
	 			else
				{
		 			QSttCustomArrowLine *pArrow = new QSttCustomArrowLine(end,start,NULL);
		 			pArrow->setLineColor(QColor(238, 187, 107));
		 			pArrow->setHoverColor(QColor(238, 187, 107));
		 			m_pArrowLine.append(pArrow);
				}
			}
		}
	}


	if (!bDrawAllRects)
	{	
		if (nType == 0)
		{
			for (int i = 1; i < m_pChInRightRect.size(); ++i)
			{
				QSttCustomRect* RightRect = m_pChInRightRect.at(i);
				bool isLineConnected = false;

				// 判断当前矩形是否有箭头线与之相连
				for (int j = 0; j < m_pArrowLine.size(); ++j)
				{
					QSttCustomArrowLine* arrowLine = m_pArrowLine.at(j);
					if (RightRect->getLeftCenter() == arrowLine->getStartPoint()) 
					{
						isLineConnected = true;
						break;
					}
				}

				// 如果当前矩形没有与任何箭头线相连，则将其从场景中移除并从列表中删除
				if (!isLineConnected)
				{
					m_pChInRightRect.removeAt(i);
					delete RightRect;
					--i; 
				}
			}

			for (int i = 1; i < m_pChInRightRect.size(); ++i)
			{
				QSttCustomRect* Rect = m_pChInRightRect.at(i);
				Rect->setPosition(QPointF(m_pChInRightRect.at(i-1)->getPosition().x(), m_pChInRightRect.at(i-1)->getPosition().y() + 40));
				m_pArrowLine.at(i-1)->setStartPoint(Rect->getLeftCenter());
				m_pOutputRect->setHeight(m_pInputRect->getHeight());
			}
		}
		else if (nType == 1)
		{
			for (int i = 1; i < m_pChInLeftRect.size(); ++i)
			{
				QSttCustomRect* LeftRect = m_pChInLeftRect.at(i);
				bool isLineConnected = false;

				for (int j = 0; j < m_pArrowLine.size(); ++j)
				{
					QSttCustomArrowLine* arrowLine = m_pArrowLine.at(j);
					if (LeftRect->getRightCenter() == arrowLine->getStartPoint()) 
					{
						isLineConnected = true;
						break;
					}
				}

				if (!isLineConnected)
				{
					m_pChInLeftRect.removeAt(i);
					delete LeftRect;
					--i; 
				}
			}

			for (int i = 1; i < m_pChInLeftRect.size(); ++i)
			{
				QSttCustomRect* Rect = m_pChInLeftRect.at(i);
				Rect->setPosition(QPointF(m_pChInLeftRect.at(i-1)->getPosition().x(), m_pChInLeftRect.at(i-1)->getPosition().y() + 40));
				m_pArrowLine.at(i-1)->setStartPoint(Rect->getRightCenter());
				m_pInputRect->setHeight(m_pOutputRect->getHeight());
			}
		}
	}
}

void QSttSclIedLineDialog::slot_checkbox(int nState)
{		
	Release();
	if (nState == Qt::Checked)
	{
		InitData(m_pOutputData,m_pInputData,m_nType,false);
	}
	else
			{
		InitData(m_pOutputData,m_pInputData,m_nType,true);
	}
}

void QSttSclIedLineDialog::Release()
{
	if (m_pInputRect != NULL)
	{
		delete m_pInputRect;
		m_pInputRect = NULL;
	}
	if (m_pOutputRect != NULL)
	{
		delete m_pOutputRect;
		m_pOutputRect = NULL;
			}

	for (int i = 0; i< m_pChInLeftRect.size();i++)
	{
		delete m_pChInLeftRect[i];
		m_pChInLeftRect[i] = NULL;
		}
	m_pChInLeftRect.removeAll(NULL);

	for (int i = 0; i< m_pChInRightRect.size();i++)
	{
		delete m_pChInRightRect[i];
		m_pChInRightRect[i] = NULL;
	}
	m_pChInRightRect.removeAll(NULL);

	for (int i = 0; i< m_pArrowLine.size();i++)
	{
		delete m_pArrowLine[i];
		m_pArrowLine[i] = NULL;
	}
	m_pArrowLine.removeAll(NULL);
}



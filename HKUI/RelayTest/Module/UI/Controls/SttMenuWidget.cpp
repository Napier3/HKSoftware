#include "SttMenuWidget.h"
#include <QEvent>
#include "../SttTestCntrFrameAPI.h"


QSttMenuWidget::QSttMenuWidget(CSttFrame_Menus *pMenus, CString strTestState,QFont font, QWidget *parent) : QWidget(parent)
{
	m_nMaxRow = 0;
    m_nWidth = 0;
    m_nHeight = 0;
    m_pMenus = pMenus;
	
	m_strTestState = strTestState;

    m_font = font;

	 m_bTestMacroUI = TRUE;

	for (int i=0;i<Button_Max_Col;i++)
	{
		m_nButtonMaxWidth[i] = 0;
	}

	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
//	setVisible(false);
}

void QSttMenuWidget::Init()
{
	this->setAutoFillBackground(true); 

	m_pMainLayout = new QGridLayout;
	this->setLayout(m_pMainLayout);

	int nRow = 0;
	int nCol = 0;
	CSttFrame_Menu *pCurrFrame_Menu = NULL;
	CSttFrame_Item *pCurrFrame_Item = NULL;
	POS pos = m_pMenus->GetHeadPosition();

	if (stt_Frame_TestMacroUI() == NULL)
	{
		m_bTestMacroUI = false;
	}

	while(pos != NULL)
	{
		pCurrFrame_Menu = (CSttFrame_Menu*)m_pMenus->GetNext(pos);
		AddTitleLabelToLayout(pCurrFrame_Menu,nCol);
		nRow = 1;
		POS pos_item = pCurrFrame_Menu->GetHeadPosition();

		while (pos_item != NULL)
		{
			pCurrFrame_Item = (CSttFrame_Item*)pCurrFrame_Menu->GetNext(pos_item);
			bool bflag = true;

			for (int i = 0;i < m_strHideButton.size(); i++)
			{
				if (pCurrFrame_Item->m_strID == m_strHideButton.at(i))
				{
					bflag = false;
					break;
				}	
			}

			if (bflag)
			{
				//2023-10-31 suyang 报文探测界面需要不同功能按钮
				if (!m_bTestMacroUI)
				{
					if (pCurrFrame_Item->m_nMacroUse !=	0)
					{
				AddButtonToLayout(pCurrFrame_Item,nRow,nCol);
				nRow++;
			}

				}
				else
				{
					AddButtonToLayout(pCurrFrame_Item,nRow,nCol);
					nRow++;
				}
				
			}
		}

		nCol++;

		if (m_nMaxRow <= nRow)
		{
			m_nMaxRow = nRow;
		}
	}

	AdjustButtonWidth();

	int nWidth = 0;

	for (int i=0;i<nCol;i++)
	{
		nWidth += m_nButtonMaxWidth[i] + 30;
	}

	if (m_Btnlist.size()>0)
	{
		resize(nWidth,m_nMaxRow * (m_Btnlist.at(0)->height() + 5));
	}
}

void QSttMenuWidget::AddTitleLabelToLayout(CExBaseObject *pMenu,int nCol)
{
	QLabel *pMenuLabel = new QLabel(pMenu->m_strName,this);
	pMenuLabel->setFont(m_font);
	QFontMetrics fm(m_font);
	QRect rec = fm.boundingRect(pMenu->m_strName);
	pMenuLabel->setFixedHeight(rec.height() + 10);
	if(rec.width() > m_nButtonMaxWidth[nCol])
		m_nButtonMaxWidth[nCol] = rec.width();

	m_pMainLayout->addWidget(pMenuLabel,0,nCol,Qt::AlignHCenter | Qt::AlignVCenter);
}

void QSttMenuWidget::AddButtonToLayout(CExBaseObject *pItem, int nRow, int nCol)
{
    QSttItemButton *pButton = new QSttItemButton(pItem,m_font,this);
	pButton->UpdateEnableState(m_strTestState);
    QFontMetrics fm(m_font);
    QRect rec = fm.boundingRect(pItem->m_strName);
    pButton->setFixedHeight(rec.height() + 10);
    if(rec.width() > m_nButtonMaxWidth[nCol])
         m_nButtonMaxWidth[nCol] = rec.width();

    m_pMainLayout->addWidget(pButton,nRow,nCol,Qt::AlignHCenter | Qt::AlignVCenter);
    m_Btnlist.append(pButton);

    connect(pButton,SIGNAL(sig_clicked(QString)),stt_Frame_TestCtrlFrame(),SLOT(slot_MenuButtonClick(QString)));
}

void QSttMenuWidget::AdjustButtonWidth()
{
	int nCol = 0;
	int nCount = 0;
	POS pos = m_pMenus->GetHeadPosition();

	CSttFrame_Item *pCurrFrame_Item = NULL;

	while(pos != NULL)
	{
		CExBaseObject *pObj = m_pMenus->GetNext(pos);
		if(pObj != NULL)
		{
			CSttFrame_Menu *pMenu = (CSttFrame_Menu*)pObj;
			POS posC = pMenu->GetHeadPosition();
			while (posC != NULL)
			{
				//CExBaseObject *pObjC = pMenu->GetNext(posC);
				pCurrFrame_Item = (CSttFrame_Item*)pMenu->GetNext(posC);

				if(pCurrFrame_Item /*pObjC*/!= NULL)
				{
					bool bflag = true;
					for (int i = 0;i < m_strHideButton.size(); i++)
					{
						if (pCurrFrame_Item/*pObjC*/->m_strID == m_strHideButton.at(i))
						{
							bflag = false;
							break;
						}	
					}
					if (bflag)
					{
						if (!m_bTestMacroUI)
						{
							if (pCurrFrame_Item->m_nMacroUse !=	0)
							{
								m_Btnlist.at(nCount++)->setFixedWidth(m_nButtonMaxWidth[nCol] + 20);
							}

						}
						else
						{
						m_Btnlist.at(nCount++)->setFixedWidth(m_nButtonMaxWidth[nCol] + 20);
					}
						
					}
				}
			}
			nCol++;
		}
	}
}

bool QSttMenuWidget::event(QEvent *event)
{
#ifndef _PSX_QT_LINUX_
	if(QEvent::WindowDeactivate == event->type()) 
	{
		hide(); 
	}
#endif	

// 	long nType = event->type();
// 	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("QSttMenuWidget(%d)."),nType);
	return QWidget::event(event);
}


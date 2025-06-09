#include "SttPanelBase.h"
#include "../Module/ScrollCtrl/ScrollTextEdit.h"
#include <QDesktopWidget>
#include <QApplication>

extern long SttFrame_Vert_Gap;  //框架按钮垂直方向上的间隔，系统为工具栏、状态栏绘制边框
extern long SttFrame_Line_Pix;    //绘制边框的像素点

QSttPanelBase::QSttPanelBase(CSttFrame_Panal *pPanel,QSttBarDataBtnsMngr &oDataBunsMngr,  QFont font,QWidget *parent) : QWidget(parent)
{
	m_font = font;
    m_pPanel = pPanel;
    m_nWidth = 0;
	show();
	CSttFrame_BarBase *pFrame_BarBase = (CSttFrame_BarBase*)pPanel->GetParent();
	setFixedHeight(pFrame_BarBase->m_nHeight);
//	CreateByData(oDataBunsMngr);
}

QSttPanelBase::~QSttPanelBase()
{

}

void QSttPanelBase::CreateByData(QSttBarDataBtnsMngr &oDataBunsMngr)
{
    POS pos = m_pPanel->GetHeadPosition();
    while(pos != NULL)
    {
        CExBaseObject *pBase = m_pPanel->GetNext(pos);
        QSttToolButtonBase *pNew = CreateButton(pBase);

        if (pNew == NULL)
        {
            continue;
        }

		pBase->m_dwItemData = (unsigned long)pNew;
        m_listCtrls.append(pNew);

        if(pBase->GetClassID() == MNGRCLASSID_CSTTFRAME_DATA)
        {
            oDataBunsMngr.append(pNew);
        }
    }
}

int QSttPanelBase::AdjustCtrls()
{
    int nXStartPos;

    nXStartPos = SttFrame_Interval;
    for(int i = 0;i < m_listCtrls.size();i++)
    {
        QSttToolButtonBase *pBtn = m_listCtrls.at(i);
		pBtn->setVisible(pBtn->m_bShow);
        if(pBtn->m_bShow || m_nWidth == 0)
        {
           QRect rect = pBtn->rect();
           pBtn->setGeometry(nXStartPos, SttFrame_Vert_Gap, rect.width(), rect.height());
           nXStartPos += rect.width() + SttFrame_Interval;
        }
    }
    m_nWidth = nXStartPos;
    this->setFixedWidth(m_nWidth);
    return nXStartPos;
}
QSttToolButtonBase* QSttPanelBase::CreateButton(CExBaseObject *pObject)
{
    if(pObject->GetClassID() == MNGRCLASSID_CSTTFRAME_BUTTON)
    {
        QSttToolButton *p = new QSttToolButton(pObject,m_font,this);
        connect(p,SIGNAL(sig_clicked(QString)),
                this->parentWidget()->parentWidget(),SLOT(slot_MenuButtonClick(QString)));
        return p;
    }

    CSttFrame_Data *pObj = (CSttFrame_Data*)pObject;

    if(pObj->m_strType == CString("sd"))
    {
        return new QSttSdCardButton(pObj,m_font,this);
    }
    else if(pObj->m_strType == CString("battery"))
    {
        return new QSttBatteryButton(pObj,m_font,this);
    }
    else if(pObj->m_strType == CString("light"))
    {
        return new QSttLightButton(pObj,m_font,this);
    }
    else if(pObj->m_strType == CString("bin"))
    {
        return new QSttBinButton(pObj,m_font,this);
    }
    else if(pObj->m_strType == CString("bout"))
    {
        return new QSttBoutButton(pObj,m_font,this);
    }
	else if(pObj->m_strType == CString("netstat"))
	{
		return new QSttNetStatButton(pObj,m_font,this);
	}
	else if(pObj->m_strType == CString("gps"))
	{
		return new QSttGpsButton(pObj,m_font,this);
	}
	else if(pObj->m_strType == CString("4G"))
	{
		return new QStt4GButton(pObj,m_font,this);
	}
	else if(pObj->m_strType == CString("usb"))
	{
		return new QSttUSBButton(pObj,m_font,this);
	}
	else if(pObj->m_strType == CString("bluetooth"))
	{
		return new QSttBlueToothButton(pObj,m_font,this);
	}
	else if(pObj->m_strType == CString("wifi"))
	{
		return new QSttWifiButton(pObj,m_font,this);
	}

	return NULL;
}


void QSttPanelBase::UpdateEnableState(const CString &strState)
{
	QSttToolButtonBase *pBtn = NULL;

	for(int i = 0;i < m_listCtrls.size();i++)
	{
		pBtn = m_listCtrls.at(i);
		pBtn->UpdateEnableState(strState);
	}
}


//////////////////////////////////////////
/// \brief QSttFloatPanelBase::QSttFloatPanelBase
///

QSttFloatPanelBase::QSttFloatPanelBase(CSttFrame_Panal *pPanel,QSttBarDataBtnsMngr &oDataBunsMngr, QFont font, QWidget *parent)
	: QSttPanelBase(pPanel,oDataBunsMngr,font,parent)
{
	m_nFloatWidth = 0;
}

int QSttFloatPanelBase::AdjustCtrls()
{
	int nXStartPos;

	nXStartPos = SttFrame_Interval;
	for(int i = 0;i < m_listCtrls.size();i++)
	{
		QSttToolButtonBase *pBtn = m_listCtrls.at(i);
		if(pBtn->m_bShow || m_nWidth == 0)
		{
			QRect rect = pBtn->rect();
			pBtn->setGeometry(nXStartPos, SttFrame_Vert_Gap, rect.width(),rect.height());
			nXStartPos += rect.width() + SttFrame_Interval;
		}
	}

	m_nWidth = m_nFloatWidth;
	return 0;
}
//////////////////////////////////////////
/// \brief QSttFloatPanel::QSttFloatPanel
///

QSttFloatPanel::QSttFloatPanel(CSttFrame_Panal *pPanel,QSttBarDataBtnsMngr &oDataBunsMngr, QFont font, QWidget *parent)
    : QSttFloatPanelBase(pPanel,oDataBunsMngr,font,parent)
{
    m_nBtnIndex = 0;
    m_bCanRightMove = true;
	m_nCurrShowBtnNum = 0;
	m_nCurrIntervalHideBtnNum = 0;
//	CreateByData(oDataBunsMngr);
}

void QSttFloatPanel::CreateByData(QSttBarDataBtnsMngr &oDataBunsMngr)
{
    QSttPanelBase::CreateByData(oDataBunsMngr);
    m_pBtnMoveLeft = new QPushButton(this);
    m_pBtnMoveLeft->setParent(this);
    m_pBtnMoveLeft->setFont(m_font);
    m_pBtnMoveLeft->show();
    m_pBtnMoveLeft->setText("<<");

    m_pBtnMoveRight = new QPushButton(this);
    m_pBtnMoveRight->setParent(this);
    m_pBtnMoveRight->setFont(m_font);
    m_pBtnMoveRight->show();
    m_pBtnMoveRight->setText(">>");

	m_pBtnMoveLeft->setDisabled(true);

    connect(m_pBtnMoveRight,SIGNAL(clicked()),this,SLOT(slot_FloatRightMove()));
    connect(m_pBtnMoveLeft,SIGNAL(clicked()),this,SLOT(slot_FloatLeftMove()));
}

int QSttFloatPanel::AdjustCtrls()
{
    int nXStartPos = SttFrame_Interval;
    int nXEndPos;
    QFontMetrics fm(m_font);
    QRect rec = fm.boundingRect(m_pBtnMoveLeft->text());
    CSttFrame_BarBase *pTool = (CSttFrame_BarBase*)m_pPanel->GetParent();
    m_pBtnMoveLeft->setGeometry(nXStartPos, SttFrame_Vert_Gap, rec.width() + 10,pTool->GetBtnHeight());
    m_pBtnMoveRight->setGeometry(m_nFloatWidth - rec.width() - 10, SttFrame_Vert_Gap, rec.width() + 10,pTool->GetBtnHeight());
    nXStartPos += rec.width() + 10 + SttFrame_Interval;
    nXEndPos = m_nFloatWidth - rec.width() - 10 - SttFrame_Interval;

	//先把所有的按钮隐藏
    for(int j=0;j< m_listCtrls.size();j++)
        m_listCtrls.at(j)->hide();
	
	//计算可以放几个按钮以及多出来的空间
	int nRedundant = nXEndPos - nXStartPos;
	int nCurrShowBtnNum = 0,nCurrHideBtnNum = 0;

	for(int nIndex = m_nBtnIndex;nIndex < m_listCtrls.size();nIndex++)
	{
		QSttToolButtonBase *pBtn = m_listCtrls.at(nIndex);

		if (!pBtn->m_bShow)//如果该按钮不需要显示,则不显示
		{
			nCurrHideBtnNum++;
			continue;
		}

		QRect rect = pBtn->rect();
		if(nRedundant > rect.width() + SttFrame_Interval)
		{
			pBtn->show();
			nCurrShowBtnNum++;
			nRedundant -= (rect.width() + SttFrame_Interval);
		}
		else
		{
			m_bCanRightMove = true;
//			m_pBtnMoveRight->setDisabled(false);
			break;
		}
	}

	m_nCurrShowBtnNum = nCurrShowBtnNum;
	m_nCurrIntervalHideBtnNum = nCurrHideBtnNum;
	//最后一个按钮显示出来了，就不能向右移动了
	if((m_nBtnIndex + nCurrShowBtnNum + nCurrHideBtnNum) >= m_listCtrls.size())
	{
		m_bCanRightMove = false;
//		m_pBtnMoveRight->setDisabled(true);
	}

	//将所有显示的按钮，平均分配多余的空间
	int nInterval = nRedundant / (nCurrShowBtnNum + 1); //中间n个按钮，一共n+1个空隙，同时也能防止极端情况下nButtonNum为0的问题
	nXStartPos += nInterval;

	//按钮归位！ sf 20220118
	long nCurrAllBtnNum = nCurrShowBtnNum + nCurrHideBtnNum;

    for(int nIndex = 0;nIndex < nCurrAllBtnNum ; nIndex++)
    {
        QSttToolButtonBase *pBtn = m_listCtrls.at(nIndex + m_nBtnIndex);

		if (!pBtn->m_bShow)
		{
			continue;
		}

        QRect rect = pBtn->rect();
        pBtn->setGeometry(nXStartPos, SttFrame_Vert_Gap, rect.width() + nInterval, rect.height());
        nXStartPos += rect.width() + SttFrame_Interval + nInterval;
    }
    
	m_nWidth = m_nFloatWidth;
	EnableLeftRightMoveBtn();

	//zhouhj 2023.9.13 如果中间没有相关按钮,则将其隐藏
	if (m_listCtrls.size() <=0)
	{
		m_pBtnMoveLeft->hide();
		m_pBtnMoveRight->hide();
	}
	return 0;
}
void QSttFloatPanel::slot_FloatLeftMove()
{
    if(SetBtnIndex_LeftMove())
    {
        AdjustCtrls();
//		EnableLeftRightMoveBtn();
    }
}

void QSttFloatPanel::slot_FloatRightMove()
{
    if(SetBtnIndex_RightMove())
    {
        AdjustCtrls();
//		EnableLeftRightMoveBtn();
    }
}

bool QSttFloatPanel::SetBtnIndex_LeftMove()
{
	if (m_nBtnIndex<=0)
	{
		return false;
	}

	int nXStartPos = SttFrame_Interval;
	int nXEndPos;
	QFontMetrics fm(m_font);
	QRect rec = fm.boundingRect(m_pBtnMoveLeft->text());
	nXStartPos += rec.width() + 10 + SttFrame_Interval;
	nXEndPos = m_nFloatWidth - rec.width() - 10 - SttFrame_Interval;
	int nRedundant = nXEndPos - nXStartPos;
	int nShowBtnNum = 0,nHideBtnNum = 0;
	QSttToolButtonBase *pBtn = NULL;

	for(int nIndex = m_nBtnIndex - 1;nIndex >= 0;nIndex--)
	{
		pBtn = m_listCtrls.at(nIndex);

		if (!pBtn->m_bShow)
		{
			nHideBtnNum++;
			continue;
		}

		QRect rect = pBtn->rect();

		if(nRedundant <= (rect.width() + SttFrame_Interval))
			break;

		nRedundant -= (rect.width() + SttFrame_Interval);
		nShowBtnNum++;
	}

	m_nBtnIndex -= (nShowBtnNum + nHideBtnNum);

	if (m_nBtnIndex<=0)
	{
		m_nBtnIndex = 0;
	}

	return true;
}

bool QSttFloatPanel::SetBtnIndex_RightMove()
{
	if ((m_nBtnIndex + m_nCurrShowBtnNum + m_nCurrIntervalHideBtnNum+ 1) > m_listCtrls.size())
	{
		return false;
	}

	m_nBtnIndex += (m_nCurrShowBtnNum+m_nCurrIntervalHideBtnNum);
	int nXStartPos = SttFrame_Interval;
	int nXEndPos;
	QFontMetrics fm(m_font);
	QRect rec = fm.boundingRect(m_pBtnMoveLeft->text());
	nXStartPos += rec.width() + 10 + SttFrame_Interval;
	nXEndPos = m_nFloatWidth - rec.width() - 10 - SttFrame_Interval;
	int nRedundant = nXEndPos - nXStartPos;
	int nShowBtnNum = 0,nHideBtnNum = 0;
	QSttToolButtonBase *pBtn = NULL;

	for(int nIndex = m_listCtrls.size()-1;nIndex >= 0;nIndex--)
	{
		pBtn = m_listCtrls.at(nIndex);

		if (!pBtn->m_bShow)
		{
			nHideBtnNum++;
			continue;
		}

		QRect rect = pBtn->rect();

		if(nRedundant <= (rect.width() + SttFrame_Interval))
			break;

		nRedundant -= (rect.width() + SttFrame_Interval);
		nShowBtnNum++;
	}

	if (m_nBtnIndex > (m_listCtrls.size() - (nShowBtnNum + nHideBtnNum)))
    {
		m_nBtnIndex = (m_listCtrls.size() - (nShowBtnNum + nHideBtnNum));
    }

// 	if ((m_nBtnIndex + m_nCurrShowBtnNum + 1) >= m_listCtrls.size())
// 	{
// 		m_nBtnIndex = (m_listCtrls.size()-1);
// 	}

	return true;
}

void QSttFloatPanel::UpdateCurrShowButton()
{
	if (m_nBtnIndex<0)
	{
		m_nBtnIndex = 0;
	}

	AdjustCtrls();
}

void QSttFloatPanel::EnableLeftRightMoveBtn()
{
	BOOL bCanLeftMove = FALSE;
	QSttToolButtonBase *pBtn = NULL;

	for(int nIndex = m_nBtnIndex - 1;nIndex >= 0;nIndex--)
	{
		pBtn = m_listCtrls.at(nIndex);

		if (pBtn->m_bShow)//如果该按钮不需要显示,则不显示
		{
			bCanLeftMove = TRUE;
			break;
		}
	}

	m_pBtnMoveLeft->setEnabled(bCanLeftMove);
	m_pBtnMoveRight->setEnabled(m_bCanRightMove);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSttResultPanel::QSttResultPanel(CSttFrame_Panal *pPanel,QSttBarDataBtnsMngr &oDataBunsMngr, QFont font, QWidget *parent)
: QSttPanelBase(pPanel,oDataBunsMngr,font,parent)
{
	m_pMainLayout = NULL;
	m_pTextEdit = NULL;
	CSttFrame_BarBase *pFrame_BarBase = (CSttFrame_BarBase*)pPanel->GetParent();
	m_nWidth = pFrame_BarBase->m_nWidth;

	m_oErrorFormat.setForeground(QBrush(QColor(255,0,0)));
	m_oNormalFormat.setForeground(QBrush(QColor(0,0,0)));
}

int QSttResultPanel::AdjustCtrls()
{
	this->setFixedWidth(m_nWidth);
	return m_nWidth;
}

void QSttResultPanel::InitUI()
{
	m_pMainLayout = new QVBoxLayout(this);
	m_pMainLayout->setContentsMargins(1, 0, 0, 2);
	m_pTextEdit = new QScrollTextEdit(this);
	m_pMainLayout->addWidget(m_pTextEdit);
	setLayout(m_pMainLayout);
	connect(this, SIGNAL(sig_refreshLog(long,QString)), this, SLOT(slot_refreshOutput(long,QString)));
	connect(this, SIGNAL(sig_ClearAll()), this, SLOT(slot_ClearAll()));
}

void QSttResultPanel::ClearAll()
{
	emit sig_ClearAll();
}

long QSttResultPanel::OnRecvLiveUpdate(CSttSysState &oSysState)
{
	if(oSysState.GetSttParas())
	{
		CDvmData* pData = (CDvmData*)oSysState.GetSttParas()->FindByID(STT_CMD_PARA_LIVEUPDATE_UPDATEINFO);
		if(pData)
		{
			emit sig_refreshLog(XLOGLEVEL_INFOR,pData->m_strValue);
		}
	}
	return 1;
}

void QSttResultPanel::slot_ClearAll()
{
	if (m_pTextEdit == NULL)
		return;

	m_pTextEdit->clear();
}

void QSttResultPanel::slot_refreshOutput(long nLevel,QString strLog)
{
	if (m_pTextEdit == NULL)
		return;

//是否使用自定义的时间对象
#ifdef USE_Custom_CDateTime
	QString time;
	CString strTimeText;
	CDateTime::GetDateTime_HHMMSSZZZ(strTimeText);
	time = strTimeText;
#else
 	QString time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
#endif
	time += " ";
	time += strLog;

#ifndef _PSX_QT_LINUX_
	time = QString::fromLocal8Bit(time.toStdString().c_str());
#endif
	QTextCursor cursor = m_pTextEdit->textCursor();

	if (nLevel == XLOGLEVEL_ERROR)
	{
		cursor.mergeCharFormat(m_oErrorFormat);
		m_pTextEdit->mergeCurrentCharFormat(m_oErrorFormat);
	}

	m_pTextEdit->append(time);
	cursor.movePosition(QTextCursor::End);
	m_pTextEdit->setTextCursor(cursor);

	if (nLevel == XLOGLEVEL_ERROR)
	{
		cursor.mergeCharFormat(m_oNormalFormat);
		m_pTextEdit->mergeCurrentCharFormat(m_oNormalFormat);
	}
}

void QSttResultPanel::LogString(long nLevel, const CString &strMsg)
{
	emit sig_refreshLog(nLevel,strMsg);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////
/// \brief QSttBarBase::QSttBarBase
/// \param parent
///
QSttBarBase::QSttBarBase(CSttFrame_BarBase *pBarBase, QSttBarDataBtnsMngr &oDataBunsMngr, QFont font,QWidget *parent)
    : QWidget(parent)
{
	m_bDrawFrame = TRUE;
	m_pToolBar = pBarBase;
	pBarBase->m_dwItemData = (DWORD)this;
	m_font = font;

    CreatByData(pBarBase,oDataBunsMngr);
    AdjustPanels();
	setParent(parent);
	show();
}

void QSttBarBase::CreatByData(CSttFrame_BarBase *pToolBar, QSttBarDataBtnsMngr &oDataBunsMngr)
{
    POS pos = pToolBar->GetHeadPosition();

	QSttPanelBase *pPanelBase = NULL;

    while (pos != NULL)
    {
        CSttFrame_Panal *pPanal = (CSttFrame_Panal*)pToolBar->GetNext(pos);

        if(pPanal->m_strType == CString("float"))
		{
            pPanelBase = new QSttFloatPanel(pPanal,oDataBunsMngr,m_font,this);
			pPanelBase->CreateByData(oDataBunsMngr);
		}
		else if (pPanal->m_strType == CString("float-single"))
		{
			pPanelBase = new QSttFloatPanelBase(pPanal,oDataBunsMngr,m_font,this);
			pPanelBase->CreateByData(oDataBunsMngr);
		}
		else if (pPanal->m_strType == CString("result"))
		{
			pPanelBase = new QSttResultPanel(pPanal,oDataBunsMngr,m_font,this);
			pPanelBase->CreateByData(oDataBunsMngr);
			QSttResultPanel *pSttResultPanel = (QSttResultPanel *)pPanelBase;
			pSttResultPanel->InitUI();
		}
        else
		{
            pPanelBase = new QSttPanelBase(pPanal,oDataBunsMngr,m_font,this);
			pPanelBase->CreateByData(oDataBunsMngr);
		}

        m_plistPanel.append(pPanelBase);
    }
}


QSttFloatPanelBase* QSttBarBase::FindFloatPanel()
{
	QSttFloatPanelBase *pFind = NULL;
	QSttPanelBase *p = NULL;

	for(int i = 0;i < m_plistPanel.size(); i++)
	{
		p = m_plistPanel.at(i);

		if((p->m_pPanel->m_strType == CString("float"))||(p->m_pPanel->m_strType == CString("float-single")))
		{
			pFind = (QSttFloatPanelBase*)p;
			break;
		}
	}

	return pFind;
}

QSttResultPanel* QSttBarBase::FindResultPanel()
{
	QSttResultPanel *pFind = NULL;
	QSttPanelBase *p = NULL;

	for(int i = 0;i < m_plistPanel.size(); i++)
	{
		p = m_plistPanel.at(i);

		if(p->m_pPanel->m_strType == CString("result"))
		{
			pFind = (QSttResultPanel*)p;
			break;
		}
	}

	return pFind;
}

void QSttBarBase::UpdateEnableState(const CString &strState)
{
	QSttPanelBase *p = NULL;

	for(int i = 0;i < m_plistPanel.size(); i++)
	{
		p = m_plistPanel.at(i);
		p->UpdateEnableState(strState);
	}
}

void QSttBarBase::on_UpdateEnableState(const CString &strState)
{
	QSttPanelBase *p = NULL;

	for(int i = 0;i < m_plistPanel.size(); i++)
	{
		p = m_plistPanel.at(i);
		p->UpdateEnableState(strState);
	}
}

void QSttBarBase::AdjustPanels()
{
    int nfloatLen = m_pToolBar->m_nWidth;
	long nStaticWidth = 0;
	QSttPanelBase *pPanel = NULL;

	for(int i = 0;i < m_plistPanel.size(); i++)
	{
		pPanel = m_plistPanel.at(i);

		if((pPanel->m_pPanel->m_strType == CString("static"))||(pPanel->m_pPanel->m_strType == CString("result")))
		{
            nStaticWidth += pPanel->AdjustCtrls();
		}
	}


#ifdef _PSX_QT_WINDOWS_
	//20240225  suyang 适配6.4合并单元
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();

	long nFloatWidth = rect.width()- nStaticWidth ;
#else

	long nFloatWidth = m_pToolBar->m_nWidth - nStaticWidth;

#endif

    QSttFloatPanelBase *pFind = FindFloatPanel();

	if (pFind != NULL)
	{
        pFind->m_nFloatWidth = nFloatWidth;
        pFind->AdjustCtrls();
	}

	int nXPos = 0;
	for(int i = 0;i < m_plistPanel.size(); i++)
	{
		pPanel = m_plistPanel.at(i);

		pPanel->setGeometry(nXPos, SttFrame_Vert_Gap, pPanel->m_nWidth,m_pToolBar->m_nHeight);
		nXPos += pPanel->m_nWidth;
	}
}

void QSttBarBase::paintEvent(QPaintEvent *event)
{
	if (!m_bDrawFrame)
	{
		return;
	}

	if (SttFrame_Vert_Gap == 0)
	{
		return;
	}

	QPainter p(this);
	p.setPen(QColor(128, 128, 128)); //设置画笔记颜色
	p.drawRect(0, 0, width()-1, height()-1); //绘制边框
}


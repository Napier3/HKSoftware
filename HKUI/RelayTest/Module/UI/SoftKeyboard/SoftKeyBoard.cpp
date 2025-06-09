#include "SoftKeyBoard.h"
#include "../../XLangResource_Native.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResourceBase.h"
#include "../../../../Module/API/MathApi.h"
#include <QApplication>

QSoftKeyBoard* g_pSoftKeyBoard = NULL;


QSoftKeyBoard::QSoftKeyBoard()
{
#ifdef QT_USE_WEBKIT
    m_pCurWebFrame = NULL;
#endif
    m_pKeyBoard = NULL;
	m_pMainWidget = NULL;
}

QSoftKeyBoard::~QSoftKeyBoard()
{
	Release();
}

void QSoftKeyBoard::SetUserFunc(bool bUserFun, const QString& strFun1, const QString& strFun2,
				 const QString& strFun3, const QString& strFun4)
{
	m_pKeyBoard->SetUserFunSetup(bUserFun);
	if(bUserFun)
	{
		m_pKeyBoard->SetUserFunString(strFun1, strFun2, strFun3, strFun4);
	}
}

void QSoftKeyBoard::DisableUserFunc()
{
	if(g_pSoftKeyBoard)
	{
		g_pSoftKeyBoard->SetUserFunc(false);
	}
}

void QSoftKeyBoard::SetDefaultFunc()
{
	m_pKeyBoard->SetUserFunSetup(false);
	m_pKeyBoard->SetInputType(Keyboard::ONLYNUMBER);
}

void QSoftKeyBoard::SetLanguageFunc()
{
	m_pKeyBoard->SetDefaultFunc();
	m_pKeyBoard->SetInputType(Keyboard::NUMBER);
}

void QSoftKeyBoard::SetLanguageKeyboard()
{
	if(g_pSoftKeyBoard)
	{
		g_pSoftKeyBoard->SetLanguageFunc();
	}
}

void QSoftKeyBoard::SetDefaultKeyboard()
{
	if(g_pSoftKeyBoard)
	{
		g_pSoftKeyBoard->SetDefaultFunc();
	}
}

void QSoftKeyBoard::SetSmoothState(bool bSmooth)
{
	m_pKeyBoard->SetSmooth(bSmooth);
}

void QSoftKeyBoard::ShowPanel()
{
	m_pKeyBoard->ShowSmoothEdit();
}

void QSoftKeyBoard::HidePanel()
{
	m_pKeyBoard->HidePanel();
}

void QSoftKeyBoard::AttachObj(QWidget* pWidget,Keyboard::tagMode oDefault)
{
	if(g_pSoftKeyBoard)
	{
		g_pSoftKeyBoard->Attach(pWidget,oDefault);
	}
}

#ifdef QT_USE_WEBKIT
void QSoftKeyBoard::AttachObj(QWebView* pWebView)
{
	if(g_pSoftKeyBoard)
	{
		g_pSoftKeyBoard->AttachWeb(pWebView);
	}
}

void QSoftKeyBoard::AttachObj(QWebPage* pWebPage)
{
	if(g_pSoftKeyBoard)
	{
		g_pSoftKeyBoard->AttachWeb(pWebPage);
	}
}
#endif

void QSoftKeyBoard::ReAttach()
{
	if (m_vecModeStack.size()>0)
	{
		m_vecModeStack.pop_back();

		if(m_vecModeStack.size()>0)
		{
			QModePair pair = m_vecModeStack.at(m_vecModeStack.size() - 1);
			Attach(pair.first, pair.second, false);
		}
	}
}

void QSoftKeyBoard::ReAttachObj()
{
	//将堆栈最后一个值抛出后设置当前键盘为栈顶mode
	if(g_pSoftKeyBoard)
	{
		g_pSoftKeyBoard->ReAttach();
	}
}

void QSoftKeyBoard::Attach(QWidget* pWidget, Keyboard::tagMode oDefault, bool bStack)
{
	Release();

	m_pKeyBoard = new Keyboard(pWidget,oDefault);
	if(bStack)
	{
		bool bSame = false;
		if(m_vecModeStack.size())
		{
			//确定是否在同一个界面记录了两次一模一样的键盘配置
			QModePair lastPair = m_vecModeStack.at(m_vecModeStack.size() - 1);
			if(lastPair.first == pWidget && lastPair.second == oDefault)
			{
				bSame = true;
			}
		}

		if(!bSame)
		{
			QModePair pair(pWidget, oDefault);
			m_vecModeStack.push_back(pair);
		}
	}
	
	m_pMainWidget = pWidget;
	pWidget->installEventFilter(this);
	m_pKeyBoard->setAttribute(Qt::WA_ShowWithoutActivating,true);
	m_pKeyBoard->setVisible(false);
	m_pKeyBoard->installEventFilter(pWidget);

	connect(m_pKeyBoard, SIGNAL(sig_clickFunc1(QPushButton*)), this, SLOT(slot_clickFunc1(QPushButton*)));
	connect(m_pKeyBoard, SIGNAL(sig_clickFunc2(QPushButton*)), this, SLOT(slot_clickFunc2(QPushButton*)));
	connect(m_pKeyBoard, SIGNAL(sig_clickFunc3(QPushButton*)), this, SLOT(slot_clickFunc3(QPushButton*)));
	connect(m_pKeyBoard, SIGNAL(sig_clickFunc4(QPushButton*)), this, SLOT(slot_clickFunc4(QPushButton*)));
	connect(m_pKeyBoard, SIGNAL(sig_clickEnter()), this, SLOT(slot_clickEnter()));

	connect(m_pKeyBoard, SIGNAL(sig_updateChanged(const QString&)), this, SLOT(updateChanged(const QString&)));
	connect(m_pKeyBoard, SIGNAL(sig_deleteChanged()), this, SLOT(deleteChanged()));

	if(pWidget->inherits("QDialog"))
	{
		m_pKeyBoard->SetIsDialog(true);
		m_pKeyBoard->setWindowFlags(Qt::ToolTip);
//  	connect(&m_oTimer, SIGNAL(timeout()), this, SLOT(OnTimer()));
//  	m_oTimer.start(10);
	}

#ifdef QT_USE_WEBKIT
    QList<QWebView *> view = pWidget->findChildren<QWebView *>();
	foreach (QWebView *v, view) 
	{
		AttachWeb(v);
	}

	QList<QWebPage *> page = pWidget->findChildren<QWebPage *>();
	foreach (QWebPage *p, page) 
	{
		AttachWeb(p);
	}
#endif
}

#ifdef QT_USE_WEBKIT
void QSoftKeyBoard::AttachWeb(QWebView* pWebView)
{
	connect(pWebView->page(), SIGNAL(microFocusChanged()), this, SLOT(microFocusChanged()), Qt::UniqueConnection);
}

void QSoftKeyBoard::AttachWeb(QWebPage* pWebPage)
{
	connect(pWebPage, SIGNAL(microFocusChanged()), this, SLOT(microFocusChanged()), Qt::UniqueConnection);
}
#endif

void QSoftKeyBoard::Release()
{
	if(m_pKeyBoard)
	{
		disconnect(&m_oTimer, SIGNAL(timeout()), this, SLOT(OnTimer()));
		delete m_pKeyBoard;
		m_pKeyBoard = NULL;
	}
}

bool QSoftKeyBoard::eventFilter(QObject *watched, QEvent *event)
{
	if(watched == m_pMainWidget)
	{
		switch (event->type()) 
		{
		case QEvent::MouseButtonPress:
			m_pKeyBoard->HidePanel();
			m_pMainWidget->setFocus();
			break;
		default:
			break;
		}
	}

	if(watched == m_pKeyBoard)
	{
		switch (event->type()) 
		{
		case QEvent::Hide:
			break;
		case QEvent::Show:
			m_pKeyBoard->HidePanel();
			return false;  
		default:
			break;
		}
	}

	//将事件传递给父类
	return QObject::eventFilter(watched,event);
}

void QSoftKeyBoard::OnTimer()
{
	if(!m_pMainWidget->isActiveWindow())
	{
		m_pMainWidget->activateWindow();
	}
}

void QSoftKeyBoard::updateChanged(const QString& strValue)
{
	QKeyEvent keyPress(QEvent::KeyPress, 0, Qt::NoModifier, QString(strValue));
#ifdef QT_USE_WEBKIT
    QApplication::sendEvent(m_pCurWebFrame->parent()->parent(), &keyPress);
#endif
}

void QSoftKeyBoard::deleteChanged()
{
	QKeyEvent keyPress(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier, QString());
#ifdef QT_USE_WEBKIT
    QApplication::sendEvent(m_pCurWebFrame->parent()->parent(), &keyPress);
#endif
}

void QSoftKeyBoard::microFocusChanged()
{
#ifdef QT_USE_WEBKIT
    QWebView* pObj = (QWebView*)sender()->parent();
	QWebPage* pPage = pObj->page();
	QWebFrame* pFrame = pPage->mainFrame();

	QVariant var = pFrame->evaluateJavaScript("document.activeElement.attributes.type.value");
	QString strlocalName = var.toString();
	if(strlocalName == "input"
		|| strlocalName == "text")
	{	
		//input数字键盘
		m_pKeyBoard->SetUserFunSetup(false);
		m_pCurWebFrame = pFrame;
		var = pFrame->evaluateJavaScript("document.activeElement.id");
		QString strID = var.toString();
		bool bIsSameCtrlID = m_pKeyBoard->IsSameWebCtrlID(strID);
		m_pKeyBoard->SetWebAttribute(m_pCurWebFrame, strID);
		var = pFrame->evaluateJavaScript("document.activeElement.value");
		QString strVal = var.toString();
		m_pKeyBoard->ShowWebPanel(strVal);
		var = pFrame->evaluateJavaScript("document.activeElement.getBoundingClientRect()");
		QMap<QString, QVariant> map = var.toMap();
		QVariant varX = map.value("left");
		QVariant varY = map.value("top");
		QVariant varWidth = map.value("width");
		QVariant varHeight = map.value("height");
		m_pKeyBoard->UpdateShowRect(varX.toInt(), varY.toInt(), varWidth.toInt(), varHeight.toInt());
		m_pKeyBoard->UpdateBtnsRect();

		if (!bIsSameCtrlID)
		{
			m_pKeyBoard->m_strOriginalText = strVal;
		}

		if (!m_pKeyBoard->GetSelectAll())//初次弹出键盘时,选中全部字符内容
		{
			pFrame->evaluateJavaScript("document.activeElement.setSelectionRange(0, document.activeElement.value.length)");
		}
	}
	else
#endif
    {
		m_pKeyBoard->CheckWebAttribute();
		m_pKeyBoard->setVisible(false);
	}
}

void QSoftKeyBoard::GetFuncNum(QString& strText)
{
	if(strText.indexOf("V") == strText.length() - 1)
	{
		strText = strText.left(strText.length() - 1);
	}
	else if(strText.indexOf("A") == strText.length() - 1)
	{
		strText = strText.left(strText.length() - 1);
	}
	else if(strText.indexOf("Hz") == strText.length() - 2)
	{
		strText = strText.left(strText.length() - 2);
	}
}

void QSoftKeyBoard::slot_clickFunc1(QPushButton* pBtn)
{
	//向外转发
	long nSig = receivers(SIGNAL(sig_clickFunc1(QString)));
	if(nSig)
	{
		emit sig_clickFunc1(m_pKeyBoard->GetCurWidgetText());
	}
	else
	{
		QString strText = pBtn->text();
		GetFuncNum(strText);
		m_pKeyBoard->SetCurWidgetText(strText);
	}
}

void QSoftKeyBoard::slot_clickFunc2(QPushButton* pBtn)
{
	//向外转发
	long nSig = receivers(SIGNAL(sig_clickFunc2(QString)));
	if(nSig)
	{
		emit sig_clickFunc2(m_pKeyBoard->GetCurWidgetText());
	}
	else
	{
		QString strText = pBtn->text();
		GetFuncNum(strText);
		m_pKeyBoard->SetCurWidgetText(strText);
	}
}

void QSoftKeyBoard::slot_clickFunc3(QPushButton* pBtn)
{
	//向外转发
	long nSig = receivers(SIGNAL(sig_clickFunc3(QString)));
	if(nSig)
	{
		emit sig_clickFunc3(m_pKeyBoard->GetCurWidgetText());
	}
	else
	{
		QString strText = pBtn->text();
		GetFuncNum(strText);
		m_pKeyBoard->SetCurWidgetText(strText);
	}
}

void QSoftKeyBoard::slot_clickEnter()
{
	emit sig_clickEnter();
}

void QSoftKeyBoard::slot_clickFunc4(QPushButton* pBtn)
{
	//向外转发
	long nSig = receivers(SIGNAL(sig_clickFunc4(QString)));
	if(nSig)
	{
		emit sig_clickFunc4(m_pKeyBoard->GetCurWidgetText());
	}
	else
	{
		QString strText = pBtn->text();
		GetFuncNum(strText);
		m_pKeyBoard->SetCurWidgetText(strText);
	}
}

void QSoftKeyBoard::ShowSmoothKeyboard()
{
	if(g_pSoftKeyBoard)
	{
		g_pSoftKeyBoard->SetSmoothState(false);
		g_pSoftKeyBoard->ShowPanel();
	}
}

void QSoftKeyBoard::HideSmoothKeyboard()
{
	if(g_pSoftKeyBoard)
	{
		g_pSoftKeyBoard->SetSmoothState(true);
	}
}

void QSoftKeyBoard::SetSoftKeyBoardType(long nType)
{
	//2023/8/16 wjs 将传入的百分比类型给KeyBoard
	m_pKeyBoard->SetKeyBoardType(nType);
}

void QSoftKeyBoard::SetMinusBtnText(QString strText)
{
	m_pKeyBoard->SetMinusBtnText(strText);
}

void QSoftKeyBoard::Attach330Channel(QObject* pReceiver, long nType)
{
	if(g_pSoftKeyBoard)
	{
		g_oKeyBoardBtnDescs.m_strVolFunc1.Format(_T("%dV"), (int)g_oSystemParas.m_fVNom);
		g_oKeyBoardBtnDescs.m_strVolFunc2.Format(_T("%0.3fV"), g_oSystemParas.m_fVNom/SQRT3);
		g_oKeyBoardBtnDescs.m_strCurFunc3.Format(_T("%dA"), (int)g_oSystemParas.m_fINom);
		g_oKeyBoardBtnDescs.m_strFreqFunc2.Format(_T("%dHz"), (int)g_oSystemParas.m_fFNom);

		g_pSoftKeyBoard->disconnect(SIGNAL(sig_clickFunc1(QString)));
		g_pSoftKeyBoard->disconnect(SIGNAL(sig_clickFunc2(QString)));
		g_pSoftKeyBoard->disconnect(SIGNAL(sig_clickFunc3(QString)));
		g_pSoftKeyBoard->disconnect(SIGNAL(sig_clickFunc4(QString)));
		switch(nType)
		{
		case 0:
			g_pSoftKeyBoard->SetSoftKeyBoardType(nType);
			g_pSoftKeyBoard->SetUserFunc(true, g_oKeyBoardBtnDescs.m_strVolFunc1, g_oKeyBoardBtnDescs.m_strVolFunc2,
				g_oKeyBoardBtnDescs.m_strVolFunc3, /*"等\n幅值"*/g_sLangTxt_Native_EqualAmp);
			g_pSoftKeyBoard->SetMinusBtnText(g_oKeyBoardBtnDescs.m_strVolMinus);
			//g_pSoftKeyBoard->SetUserFunc(true, "100V", "57.735V", "10V", "等幅值");
			connect(g_pSoftKeyBoard, SIGNAL(sig_clickFunc4(QString)), pReceiver, SLOT(slot_UpdataVamp(QString)), Qt::UniqueConnection);
			break;
		case 1:
			g_pSoftKeyBoard->SetSoftKeyBoardType(nType);
			g_pSoftKeyBoard->SetUserFunc(true, g_oKeyBoardBtnDescs.m_strCurFunc1, g_oKeyBoardBtnDescs.m_strCurFunc2,
				g_oKeyBoardBtnDescs.m_strCurFunc3, g_sLangTxt_Native_EqualAmp); 
			g_pSoftKeyBoard->SetMinusBtnText(g_oKeyBoardBtnDescs.m_strCurMinus);
			//g_pSoftKeyBoard->SetUserFunc(true, "10A", "5A", "1A", "等幅值"); 
			connect(g_pSoftKeyBoard, SIGNAL(sig_clickFunc4(QString)), pReceiver, SLOT(slot_UpdataIamp(QString)), Qt::UniqueConnection);
			break;
		case 2: 
			g_pSoftKeyBoard->SetUserFunc(true, "", /*"零序"*/g_sLangTxt_Native_ZeroSeq,/* "负序"*/g_sLangTxt_Native_NegativeSeq,
				/* "正序"*/g_sLangTxt_Native_PositiveSeq); 
			g_pSoftKeyBoard->SetMinusBtnText("-");
			connect(g_pSoftKeyBoard, SIGNAL(sig_clickFunc4(QString)), pReceiver, SLOT(slot_UpdataZX(QString)), Qt::UniqueConnection);
			connect(g_pSoftKeyBoard, SIGNAL(sig_clickFunc3(QString)), pReceiver, SLOT(slot_UpdataFX(QString)), Qt::UniqueConnection);
			connect(g_pSoftKeyBoard, SIGNAL(sig_clickFunc2(QString)), pReceiver, SLOT(slot_UpdataLX()), Qt::UniqueConnection);
			break;
		case 3:	
			g_pSoftKeyBoard->SetUserFunc(true, "", g_oKeyBoardBtnDescs.m_strFreqFunc1, g_oKeyBoardBtnDescs.m_strFreqFunc2, /*"等频率"*/g_sLangTxt_Native_EqualFreq); 
			g_pSoftKeyBoard->SetMinusBtnText("-");
			connect(g_pSoftKeyBoard, SIGNAL(sig_clickFunc4(QString)), pReceiver, SLOT(slot_UpdataHzamp(QString)), Qt::UniqueConnection);
			break;
		default:
			g_pSoftKeyBoard->SetUserFunc(false);
			g_pSoftKeyBoard->SetMinusBtnText("-");
			break;
		}
	}
}

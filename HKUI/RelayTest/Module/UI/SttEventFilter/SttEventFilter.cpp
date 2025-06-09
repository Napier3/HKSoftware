#include "SttEventFilter.h"
#include <QPushButton>
#include "../SttStyleSheetGlobalDefine.h"
//#include "../SttTestCntrFrameBase.h"

CString g_strBackStyleFocusOut =  "";

QSttEventFilter::QSttEventFilter()
{
    m_pWidgetForHide = NULL;
    m_pCurrentWidget = NULL;
    m_pCurrentLineEdit = NULL;
    m_pCurrentTextEdit = NULL;
    m_pCurrentPlain = NULL;
    m_pCurrentBrowser = NULL;
    m_strCurrentEditType = "";
	m_pPrevPressedWidget = NULL;
//	m_bMenuBtnFocusOut = FALSE;

	CString strStyleSheet;
#ifndef _PSX_QT_WINDOWS_
	strStyleSheet.Format(" QCheckBox::indicator:checked {image: url(:/ctrls/images/checked.png);} QCheckBox::indicator:unchecked {image: url(:/ctrls/images/unchecked.png);}");
#endif
	m_strCheckBoxStyleFocusOut = strStyleSheet;
	m_strCheckBoxStyleFocusIn.Format(_T("QCheckBox:hover{%s} %s"),STT_StyleSheet_Common_Ctrls_Pressed,strStyleSheet.GetString());
	m_strRadioStyleFocusIn.Format("QRadioButton:hover{%s}",_T("background-color:rgb(1, 196, 202);"));//(255,192,203)


	m_pPreLineEdit = NULL;
//	m_pPreLineEdit =new QLineEdit;
	//m_pPreLineEdit->text()="";
}

QSttEventFilter::~QSttEventFilter()
{
   
}


//事件过滤器,用于识别鼠标单击汉字标签处获取对应汉字
bool QSttEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    bool bRet = QObject::eventFilter(obj, event);

	QWidget *pWidget = qobject_cast <QWidget *>(obj);
//	long nFontSize1 = 0,nFontSize2 = 0;

	if (pWidget == NULL)
	{
		return bRet;
	}
	if (!pWidget->isEnabled())
	{
		return bRet;
	}

	QWidget *pParentWidget = (QWidget*)pWidget->parent();

    if (event->type()==QEvent::FocusIn)
    {
		QWidget *pWidgetForHide = m_pWidgetForHide;

        if (pWidgetForHide != NULL)
        {
            if (pWidgetForHide != pParentWidget)
            {
                pWidgetForHide->hide();
                m_pWidgetForHide = NULL;
            }
        }

        if (obj->inherits("QDialog"))
        {
            return bRet;
        }
    }
	else if (event->type()==QEvent::MouseButtonPress)
	{
		m_oCurrFont = pWidget->font();
		m_pPrevPressedWidget = pWidget;
//		nFontSize2 = m_oCurrFont.pixelSize();

		if (obj->inherits("QRadioButton"))
		{
			pWidget->setStyleSheet(m_strRadioStyleFocusIn);
		}
		else if (obj->inherits("QCheckBox"))
		{
			pWidget->setStyleSheet(m_strCheckBoxStyleFocusIn);
		}
		else if (obj->inherits("QPushButton"))
		{
			QPushButton *pQPushButton = (QPushButton *)pWidget;
			long nWidth = pQPushButton->width();
			long nHeight = pQPushButton->height();
			pQPushButton->setFixedWidth(nWidth);
			pQPushButton->setFixedHeight(nHeight);
			pWidget->setStyleSheet(STT_StyleSheet_Common_Ctrls_Pressed);
		}
	}
    else if (event->type()==QEvent::FocusOut)
    {
        if ( obj->inherits("QDialog"))
        {
            return bRet;
        }
// 		else if (obj->inherits("QCheckBox"))
// 		{
// 			pWidget->setStyleSheet(m_strCheckBoxStyleFocusOut);
// 		}
    }
//     else if (event->type()==QEvent::HoverEnter)
//     {
//         if ( obj->inherits("QDialog"))
//         {
//             return bRet;
//         }
// 		else if (obj->inherits("QRadioButton"))
// 		{
// 			pWidget->setStyleSheet(m_strRadioStyleFocusIn);
// 		}
// 		else if (obj->inherits("QCheckBox"))
// 		{
// 			pWidget->setStyleSheet(m_strCheckBoxStyleFocusIn);
// 		}
//     }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
		bool bNeedCheckFont = false;
 
        if (obj->inherits("QLineEdit"))
        {
            QLineEdit *pEdit = qobject_cast <QLineEdit *>(obj);

			if (!pEdit->isReadOnly())
			{
				//cl20230901第一次全选，第二次光标点在任意位置
				if (pEdit != m_pPreLineEdit/*pEdit->geometry() != m_pPreLineEdit->geometry()*/)
				{
					pEdit->selectAll();
				}
			}

			m_pPreLineEdit = pEdit;
        }
		else if (obj->inherits("QRadioButton"))
		{
			pWidget->setStyleSheet(g_strBackStyleFocusOut);
			bNeedCheckFont = true;
		}
		else if (obj->inherits("QCheckBox"))
		{
			pWidget->setStyleSheet(m_strCheckBoxStyleFocusOut);
			bNeedCheckFont = true;
		}
		else if (obj->inherits("QPushButton")/*||obj->inherits("QRadioButton")*/)
		{
			pWidget->setStyleSheet(g_strBackStyleFocusOut);
			bNeedCheckFont = true;
		}

		if (bNeedCheckFont && (m_oCurrFont != pWidget->font()) &&(m_pPrevPressedWidget == pWidget))
		{
// 			nFontSize1 = pWidget->font().pixelSize();
// 			nFontSize2 = m_oCurrFont.pixelSize();
			pWidget->setFont(m_oCurrFont);
		}
    }

    return bRet;
}

void QSttEventFilter::focusChanged(QWidget *oldWidget, QWidget *nowWidget)
{
    //qDebug() << "oldWidget:" << oldWidget << "nowWidget:" << nowWidget;
    if (nowWidget != 0 )//&& !this->isAncestorOf(nowWidget))
    {
        //在Qt5和linux系统中(嵌入式linux除外),当输入法面板关闭时,焦点会变成无,然后焦点会再次移到焦点控件处
        //这样导致输入法面板的关闭按钮不起作用,关闭后马上有控件获取焦点又显示.
        //为此,增加判断,当焦点是从有对象转为无对象再转为有对象时不要显示.
        //这里又要多一个判断,万一首个窗体的第一个焦点就是落在可输入的对象中,则要过滤掉

        //如果对应属性noinput为真则不显示
        if (nowWidget->property("noinput").toBool())
        {
            //QTimer::singleShot(0, this, SLOT(hidePanel()));
            return;
        }

        m_strCurrentFlag = nowWidget->property("flag").toString();

        if (nowWidget->inherits("QLineEdit"))
        {
            m_pCurrentLineEdit = (QLineEdit *)nowWidget;

            if (!m_pCurrentLineEdit->isReadOnly())
            {
                m_strCurrentEditType = "QLineEdit";
                //showPanel(nowWidget);
            }
            else
            {
                m_strCurrentEditType = "";
                //hidePanel();
            }
        }
        else if (nowWidget->inherits("QTextEdit"))
        {
            m_pCurrentTextEdit = (QTextEdit *)nowWidget;

            if (!m_pCurrentTextEdit->isReadOnly())
            {
                m_strCurrentEditType = "QTextEdit";
                //showPanel(nowWidget);
            }
            else
            {
                m_strCurrentEditType = "";
                //hidePanel();
            }
        }
        else
        {
            //需要将输入法切换到最初的原始状态--小写,同时将之前的对象指针置为零
            m_pCurrentWidget = NULL;
            m_pCurrentLineEdit = NULL;
            m_pCurrentTextEdit = NULL;
            m_pCurrentPlain = NULL;
            m_pCurrentBrowser = NULL;
            m_strCurrentEditType = "";
            //setInputType("english");
            //hidePanel();
        }

        //根据用户选择的输入法位置设置-居中显示-底部填充-显示在输入框正下方
        //int height = this->height();
//        if(fatherObject->geometry().height()<480)
//            height=150;
        //嵌入式设备，只设置在底部
        //this->setGeometry(0, deskHeight - height, deskWidth, height);
    }
}

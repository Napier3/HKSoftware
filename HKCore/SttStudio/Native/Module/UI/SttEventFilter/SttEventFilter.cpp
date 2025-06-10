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


//�¼�������,����ʶ����굥�����ֱ�ǩ����ȡ��Ӧ����
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
				//cl20230901��һ��ȫѡ���ڶ��ι���������λ��
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
        //��Qt5��linuxϵͳ��(Ƕ��ʽlinux����),�����뷨���ر�ʱ,���������,Ȼ�󽹵���ٴ��Ƶ�����ؼ���
        //�����������뷨���Ĺرհ�ť��������,�رպ������пؼ���ȡ��������ʾ.
        //Ϊ��,�����ж�,�������Ǵ��ж���תΪ�޶�����תΪ�ж���ʱ��Ҫ��ʾ.
        //������Ҫ��һ���ж�,��һ�׸�����ĵ�һ������������ڿ�����Ķ�����,��Ҫ���˵�

        //�����Ӧ����noinputΪ������ʾ
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
            //��Ҫ�����뷨�л��������ԭʼ״̬--Сд,ͬʱ��֮ǰ�Ķ���ָ����Ϊ��
            m_pCurrentWidget = NULL;
            m_pCurrentLineEdit = NULL;
            m_pCurrentTextEdit = NULL;
            m_pCurrentPlain = NULL;
            m_pCurrentBrowser = NULL;
            m_strCurrentEditType = "";
            //setInputType("english");
            //hidePanel();
        }

        //�����û�ѡ������뷨λ������-������ʾ-�ײ����-��ʾ����������·�
        //int height = this->height();
//        if(fatherObject->geometry().height()<480)
//            height=150;
        //Ƕ��ʽ�豸��ֻ�����ڵײ�
        //this->setGeometry(0, deskHeight - height, deskWidth, height);
    }
}

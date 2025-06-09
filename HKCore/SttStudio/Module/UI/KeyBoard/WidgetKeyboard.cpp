/*
 * Copyright 2009 EMBITEL (http://www.embitel.com)
 * 
 * This file is part of Virtual Keyboard Project.
 * 
 * Virtual Keyboard is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation
 * 
 * Virtual Keyboard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Virtual Keyboard. If not, see <http://www.gnu.org/licenses/>.
 */

#include "WidgetKeyboard.h"
#include <QLineEdit>
#include <QtGui>
//#include"../GlobalShare/global.h"
#include <QStackedWidget>

WidgetKeyboard::WidgetKeyboard(QWidget *parent) : QDialog(0)
{
    int FontSize  = 20;

    setupUi(this);
    resize(0,0);
    this->setWindowFlags(Qt::Tool);

    setWindowFlags(Qt::FramelessWindowHint) ;

	m_pParent = parent;
	QRect rc = parent->topLevelWidget()->geometry();

    m_pKeyBoardZ_ABC = new WidgetKeyboardZ(stackedWidget);
    m_pKeyBoardZ_ABC->showToEdit();
    m_pKeyBoardZ_ABC->setGeometry(rc.left(), rc.top() + 210, 1024, 350);

    m_pKeyBoardV_123 = new WidgetKeyboardV(stackedWidget);
    m_pKeyBoardV_123->showToEdit();
    m_pKeyBoardV_123->setGeometry(rc.left(), rc.top() + 210, 1024, 350);

    m_pKeyBoardF = new WidgetKeyboardF(stackedWidget);
    m_pKeyBoardF->showToEdit();
    m_pKeyBoardF->setGeometry(rc.left(), rc.top() + 210, 1024, 350);

    QObject::connect(m_pKeyBoardZ_ABC, SIGNAL(NotifySuccess(int)), this, SLOT(OnLoadSuccess(int)));
    QObject::connect(m_pKeyBoardV_123, SIGNAL(NotifySuccessV(int)), this, SLOT(OnLoadSuccess(int)));
    QObject::connect(m_pKeyBoardF, SIGNAL(NotifySuccessF(int)), this, SLOT(OnLoadSuccess(int)));

    stackedWidget->insertWidget(0,m_pKeyBoardZ_ABC);
    stackedWidget->insertWidget(1,m_pKeyBoardF);
    stackedWidget->insertWidget(2,m_pKeyBoardV_123);
    stackedWidget->setCurrentIndex(0);
   // stackedWidget->installEventFilter(this);
}

WidgetKeyboard::~WidgetKeyboard()
{
}

void WidgetKeyboard::showToEdit()
{    
	QRect rc = m_pParent->topLevelWidget()->geometry();
	long nHeight = 210 + rc.height() - 600;
	setGeometry(rc.left(), rc.top() + nHeight, 1024, 350);
    int nIndex = stackedWidget->currentIndex();
    if (nIndex==0)
    {
        if (m_pKeyBoardZ_ABC->lineEdit)
        {
            m_pKeyBoardZ_ABC->lineEdit->setText(m_InputString);
            m_pKeyBoardZ_ABC->lineEdit->setFocus(Qt::MouseFocusReason);
			m_pKeyBoardZ_ABC->lineEdit->selectAll();
        }
    }
    else if (nIndex==1)
    {
        if (m_pKeyBoardF->lineEdit)
        {
            m_pKeyBoardF->lineEdit->setText(m_InputString);
            m_pKeyBoardF->lineEdit->setFocus(Qt::MouseFocusReason);
			m_pKeyBoardF->lineEdit->selectAll();
        }
    }
    else if (nIndex==2)
    {
        if (m_pKeyBoardV_123->lineEdit)
        {
            m_pKeyBoardV_123->lineEdit->setText(m_InputString);
            m_pKeyBoardV_123->lineEdit->setFocus(Qt::MouseFocusReason);
			m_pKeyBoardV_123->lineEdit->selectAll();
        }
    }
}

void WidgetKeyboard::getEditString()
{
    int nIndex = stackedWidget->currentIndex();
    if (nIndex==0)
    {
        if (m_pKeyBoardZ_ABC->lineEdit)
            m_InputString = m_pKeyBoardZ_ABC->lineEdit->text();
    }
    else if (nIndex==1)
    {
        if (m_pKeyBoardF->lineEdit)
            m_InputString = m_pKeyBoardF->lineEdit->text();
    }
    else if (nIndex==2)
    {
        if (m_pKeyBoardV_123->lineEdit)
            m_InputString = m_pKeyBoardV_123->lineEdit->text();
    }
    this->accepted();
}

void WidgetKeyboard::OnLoadSuccess(int a)
{
    if (a==0||a==5)
        m_InputString = m_pKeyBoardZ_ABC->lineEdit->text();
    else if (a==1||a==6)
        m_InputString = m_pKeyBoardF->lineEdit->text();
    else if (a==2||a==7)
        m_InputString = m_pKeyBoardV_123->lineEdit->text();

    m_pKeyBoardZ_ABC->m_strEditInfo = m_InputString;
    m_pKeyBoardZ_ABC->showToEdit();
    m_pKeyBoardZ_ABC->lineEdit->setFocus(Qt::MouseFocusReason);

    m_pKeyBoardF->m_strEditInfo = m_InputString;
    m_pKeyBoardF->showToEdit();
    m_pKeyBoardF->lineEdit->setFocus(Qt::MouseFocusReason);

    m_pKeyBoardV_123->m_strEditInfo = m_InputString;
    m_pKeyBoardV_123->showToEdit();
    m_pKeyBoardV_123->lineEdit->setFocus(Qt::MouseFocusReason);
    if (a==5||a==6||a==7)
        this->accept();
}

int WidgetKeyboard::isPosiDigitstr( QString str )
{
	QByteArray ba = str.toLatin1();//QString 转换为 char*  
	const char *s = ba.data();  
	int dot = 0;
	int fDigNum = 0;
	while(*s)
	{
		if(*s == '.' && fDigNum != 0) 
		{
			if(dot == 0)
			{
				dot++;
				s++;
				continue;
			}
			else
			{
				//emit(sendWarnLog(tr("enter valid value,pls！")));
				return -1;
			}
		}

		if(*s >='0' && *s<='9')
		{
		}
		else 
		{
			//emit(sendWarnLog(tr("enter valid value,pls！")));
			return -1;
		}
		s++;
		fDigNum++;
	}

	return dot;
}
void WidgetKeyboard::setDigitOnly(bool b)
{
	m_pKeyBoardV_123->setDigitOnly(b);
}

void WidgetKeyboard::setDigitNumbers(unsigned int count)
{
	m_pKeyBoardV_123->setDigitNumbers(count);
}

/*
void WidgetKeyboard::reject()
{
    //关闭窗口，不一定非得是close()，可以重新执行其他事件
    this->close();
}

void WidgetKeyboard::keyPressEvent(QKeyEvent *event)
{
   switch(event->key())
   {
      //进行界面退出，重写Esc键，否则重写reject()方法
     case Qt::Key_Escape:
       this->close();
       break;
    default:
       QDialog::keyPressEvent(event);
   }
}
*/

bool WidgetKeyboard::eventFilter( QObject *obj, QEvent *event )
{
    if(event->type() == QEvent::KeyPress)
    {
       QKeyEvent *pe = (QKeyEvent*)event;
       if (pe->key()==Qt::Key_Home)
       {
//           homeActive(this);
           return true;
       }
    }
    return QDialog::eventFilter(obj,event);
}


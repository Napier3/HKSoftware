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

#include "WidgetKeyboardZ.h"
#include <QLineEdit>
#include <QtGui>
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include"../../../../Module/OSInterface/OSInterface.h"
#include "../../../../Module/OSInterface/QT/XMessageBox.h"

WidgetKeyboardZ::WidgetKeyboardZ(QWidget *parent) : QDialog(0)
{
    int FontSize  = 20;
    setupUi(this);
    resize(0,0);
    this->setWindowFlags(Qt::Tool);

	CString strText;
	xlang_GetLangStrByFile(strText, "Native_Enter");
	btnReturn->setText(strText);
	xlang_GetLangStrByFile(strText, "Native_Esc");
	btnEsc->setText(strText);
	xlang_GetLangStrByFile(strText, "Native_Delete");
	btnBackSpace->setText(strText);
	xlang_GetLangStrByFile(strText, "Native_Space");
	btnSpace->setText(strText);
	xlang_GetLangStrByFile(strText, "Native_Caps");
	btnCaps->setText(strText);

    setWindowFlags(Qt::FramelessWindowHint) ;

    //把要输入的数字输入到其编辑框和父窗口中；
    m_pParent = parent;
    isCaps = false;
    isShift = false;
    isCtrl = false;
    //isAlt = false;
    isIns = false;
    changeTextCaps(false);
    m_pSignalMapper = new QSignalMapper(this);
    //sliderOpacity->setRange(20,100);
    m_pButtonsList = findChildren<QToolButton *>();
    for (int i = 0; i < m_pButtonsList.count(); i++)
    {
        connect(m_pButtonsList.at(i), SIGNAL(clicked()), m_pSignalMapper, SLOT(map()));
		m_pButtonsList.at(i)->setFont(QFont("宋体", FontSize, 2));
		m_pButtonsList.at(i)->setStyleSheet("QToolButton{background-color: #313131;border-style: flat;color:white;}"
			"QToolButton:pressed{background-color: #414141;border-style: flat;}");
        m_pSignalMapper->setMapping(m_pButtonsList.at(i), i);
    }
    connect(m_pSignalMapper, SIGNAL(mapped(int)), this, SLOT(on_btn_clicked(int)));
	btnCaps->setStyleSheet("QToolButton{background-color: #191615;border-style: flat;color:white;}"
		"QToolButton:pressed{background-color: #414141;border-style: flat;}");
	btnBackSpace->setStyleSheet("QToolButton{background-color: #191615;border-style: flat;color:white;}"
		"QToolButton:pressed{background-color: #414141;border-style: flat;}");
	btnReturn->setStyleSheet("QToolButton{background-color: #191615;border-style: flat;color:white;}"
		"QToolButton:pressed{background-color: #414141;border-style: flat;}");
	btnEsc->setStyleSheet("QToolButton{background-color: #191615;border-style: flat;color:white;}"
		"QToolButton:pressed{background-color: #414141;border-style: flat;}");
	btnSpace->setStyleSheet("QToolButton{background-color: #191615;border-style: flat;color:white;}"
		"QToolButton:pressed{background-color: #414141;border-style: flat;}");

	btn123->setStyleSheet("QToolButton{background-color: #577b7c;border-style: flat;color:white;}"
		"QToolButton:pressed{background-color: #414141;border-style: flat;}");
	btnFuhao->setStyleSheet("QToolButton{background-color: #577b7c;border-style: flat;color:white;}"
		"QToolButton:pressed{background-color: #414141;border-style: flat;}");

    lineEdit->setFocus(Qt::MouseFocusReason);
	lineEdit->setFont(QFont("宋体", FontSize, 2));
    lineEdit->installEventFilter(this);
}

WidgetKeyboardZ::~WidgetKeyboardZ()
{
    delete m_pSignalMapper;
}

void WidgetKeyboardZ::on_btn_clicked(int btn)
{
    QString strKeyId;
    strKeyId = m_pButtonsList.at(btn)->accessibleName();
    bool isOk;
    int keyId = strKeyId.toInt(&isOk, 16);
    if (strKeyId.isEmpty() || !isOk)
    {
        CXMessageBox::information(0,0,"Key Not Found");
        return;
    }
    
    if (keyId==Qt::Key_Shift||keyId==Qt::Key_Control||keyId==Qt::Key_Alt)
        return;

    int involvedKeys = 1;
    Qt::KeyboardModifiers Modifier = Qt::NoModifier;
    if (isCtrl)
    {
        Modifier = Modifier | Qt::ControlModifier;
        involvedKeys++;
    }
    if (isShift)
    {
        Modifier = Modifier | Qt::ShiftModifier;
        involvedKeys++;
    }
//    if (isAlt) {
//        Modifier = Modifier | Qt::AltModifier;
//        involvedKeys++;
//    }
    
    bool isTextKey = false;

	if(keyId==Qt::Key_Insert && !isShift)
		return;

	QString ch = m_pButtonsList.at(btn)->text().trimmed();
    if (ch=="&&")
        ch = "&";
	else if (keyId==Qt::Key_Space)
        ch = " ";
    else if (checkNotTextKey(keyId))
		ch = QString();
	else
		isTextKey = true;	    

    if(isIns && isTextKey)
    {
		QKeyEvent keyEventIns(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier);
        QApplication::sendEvent(lineEdit, &keyEventIns);
        QApplication::sendEvent(m_pParent->focusWidget(), &keyEventIns);
	}

	CString strText;
	xlang_GetLangStrByFile(strText, "Native_Delete");
 	if (ch==strText)
         keyId = Qt::Key_Backspace;

	QKeyEvent keyEvent(QEvent::KeyPress, keyId, Modifier, ch, false, involvedKeys);
    QApplication::sendEvent(lineEdit/*->focusWidget()*/, &keyEvent);

}

void WidgetKeyboardZ::on_btnCaps_toggled(bool checked)
{
    changeTextCaps(checked);
    isCaps = checked;
}


void WidgetKeyboardZ::changeTextShift(bool isShift)
{
}

void WidgetKeyboardZ::changeTextCaps(bool isCaps)
{    
    if (isCaps)
    {
        btnQ->setText(QChar('Q'));
        btnW->setText(QChar('W'));
        btnE->setText(QChar('E'));
        btnR->setText(QChar('R'));
        btnT->setText(QChar('T'));
        btnY->setText(QChar('Y'));
        btnU->setText(QChar('U'));
        btnI->setText(QChar('I'));
        btnO->setText(QChar('O'));
        btnP->setText(QChar('P'));

        btnA->setText(QChar('A'));
        btnS->setText(QChar('S'));
        btnD->setText(QChar('D'));
        btnF->setText(QChar('F'));
        btnG->setText(QChar('G'));
        btnH->setText(QChar('H'));
        btnJ->setText(QChar('J'));
        btnK->setText(QChar('K'));
        btnL->setText(QChar('L'));
                
        btnZ->setText(QChar('Z'));
        btnX->setText(QChar('X'));
        btnC->setText(QChar('C'));
        btnV->setText(QChar('V'));
        btnB->setText(QChar('B'));
        btnN->setText(QChar('N'));
        btnM->setText(QChar('M'));        
    }
    else
    {
        btnQ->setText(QChar('q'));
        btnW->setText(QChar('w'));
        btnE->setText(QChar('e'));
        btnR->setText(QChar('r'));
        btnT->setText(QChar('t'));
        btnY->setText(QChar('y'));
        btnU->setText(QChar('u'));
        btnI->setText(QChar('i'));
        btnO->setText(QChar('o'));
        btnP->setText(QChar('p'));

        btnA->setText(QChar('a'));
        btnS->setText(QChar('s'));
        btnD->setText(QChar('d'));
        btnF->setText(QChar('f'));
        btnG->setText(QChar('g'));
        btnH->setText(QChar('h'));
        btnJ->setText(QChar('j'));
        btnK->setText(QChar('k'));
        btnL->setText(QChar('l'));
        
        btnZ->setText(QChar('z'));
        btnX->setText(QChar('x'));
        btnC->setText(QChar('c'));
        btnV->setText(QChar('v'));
        btnB->setText(QChar('b'));
        btnN->setText(QChar('n'));
        btnM->setText(QChar('m'));
    }
}

bool WidgetKeyboardZ::checkNotTextKey(int keyId)
{
	if (keyId==Qt::Key_Shift
            || keyId==Qt::Key_Control
            || keyId==Qt::Key_Tab
            || keyId==Qt::Key_Escape
            || keyId==Qt::Key_Return
            || keyId==Qt::Key_Insert
            || keyId==Qt::Key_NumLock
            || keyId==Qt::Key_F1
            || keyId==Qt::Key_F2
            || keyId==Qt::Key_F3
            || keyId==Qt::Key_F4
            || keyId==Qt::Key_F5
            || keyId==Qt::Key_F6
            || keyId==Qt::Key_F7
            || keyId==Qt::Key_F8
            || keyId==Qt::Key_F9
            || keyId==Qt::Key_F10
            || keyId==Qt::Key_F11
            || keyId==Qt::Key_F12
            || keyId==Qt::Key_Print
            || keyId==Qt::Key_Pause
            || keyId==Qt::Key_ScrollLock
            || keyId==Qt::Key_Enter
            || keyId==Qt::Key_Home
            || keyId==Qt::Key_End
            || keyId==Qt::Key_CapsLock
            || keyId==Qt::Key_Insert
            || keyId==Qt::Key_Delete
            || keyId==Qt::Key_PageUp
            || keyId==Qt::Key_PageDown
            || keyId==Qt::Key_Down
            || keyId==Qt::Key_Up
            || keyId==Qt::Key_Left
            || keyId==Qt::Key_Right
            || keyId==Qt::Key_Alt)
    {
        return true;
    }
	else
        return false;
}

void WidgetKeyboardZ::showToEdit()
{
    lineEdit->setText(m_strEditInfo);
	lineEdit->setFocus(Qt::MouseFocusReason);
    lineEdit->setCursorPosition(lineEdit->text().size());
	//lineEdit->setText("");
}

void WidgetKeyboardZ::on_btnReturn_clicked(bool checked)
{
    QStackedWidget *stackedWidget = (QStackedWidget *)this->parentWidget()->parentWidget();
    stackedWidget->close();
    emit NotifySuccess(5);
}

void WidgetKeyboardZ::on_btnEsc_clicked(bool checked)
{
    QStackedWidget *stackedWidget = (QStackedWidget *)this->parentWidget()->parentWidget();
    stackedWidget->close();
}

void WidgetKeyboardZ::on_btnFuhao_clicked(bool checked)
{
    QStackedWidget *stackedWidget = (QStackedWidget *)this->parentWidget();
    stackedWidget->setCurrentIndex(1);
    emit NotifySuccess(0);
}

void WidgetKeyboardZ::on_btn123_clicked(bool checked)
{
    QStackedWidget *stackedWidget = (QStackedWidget *)this->parentWidget();
    stackedWidget->setCurrentIndex(2);
    emit NotifySuccess(0);
}

void WidgetKeyboardZ::keyPressEvent(QKeyEvent *event)
{
   switch(event->key())
   {
   //进行界面退出，重写Esc键，否则重写reject()方法
   case Qt::Key_Escape:
   {
      // this->close();
       on_btnEsc_clicked(true);
   }
    break;
   case Qt::Key_Return:
   {
       //this->close();
       on_btnReturn_clicked(true);
   }
    break;
   case Qt::Key_Home:
   {
       //this->close();
//       homeActive(this);
   }
    break;
   default:
       QDialog::keyPressEvent(event);
   }
}

bool WidgetKeyboardZ::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *pe = (QKeyEvent*)event;
        if (pe->key()==Qt::Key_Home)
        {
//            homeActive(this);
            return true;
        }
    }
    return QDialog::eventFilter(obj,event);
}

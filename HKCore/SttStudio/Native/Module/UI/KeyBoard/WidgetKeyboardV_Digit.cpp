#include "stdafx.h"
#include "WidgetKeyboardV_Digit.h"
#include <QLineEdit>
#include <QtGui>
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/OSInterface/QT/XMessageBox.h"
//#include"../GlobalShare/global.h"
//#include "../GlobalShare/QLangue.h"

WidgetKeyboardV_Digit::WidgetKeyboardV_Digit()
{
	m_pSignalMapper = NULL;
	m_pExternalCtrl = NULL;
	m_bTableWidget = 0;
}

WidgetKeyboardV_Digit::WidgetKeyboardV_Digit( long nType, QWidget *parent):m_nType(nType)
{
	m_pSignalMapper = NULL;
	m_pExternalCtrl = NULL;
	m_bTableWidget = 0;
	Init(parent);
	if (nType == 0)
	{
		InitTypeV();
	}
	else if (nType == 1)
	{
		InitTypeA();
	}
	else if (nType == 2)
	{
		InitTypePh();
	}
	else if(nType == 3)
	{
		InitTypeHz();
	}
	else
	{
		InitTpyeNor();
	}
}

void WidgetKeyboardV_Digit::IntUI_ModalLess(long nType,QString& strText,CCommonCtrlInterface *pCommonCtrl
											,QWidget *parent,int bTableWidget)
{
	m_nType = nType;
	m_pExternalCtrl = pCommonCtrl;
	m_bTableWidget = bTableWidget;
	Init(parent);
	if (nType == 0)
	{
		InitTypeV();
	}
	else if (nType == 1)
	{
		InitTypeA();
	}
	else if (nType == 2)
	{
		InitTypePh();
	}
	else if(nType == 3)
	{
		InitTypeHz();
	}
	else
	{
		InitTpyeNor();
	}

	m_strEditInfo = strText;
	showToEdit();
//	update()
}

void WidgetKeyboardV_Digit::ExitHide_ModalLess(bool bUpdateText)
{
	ClearExternAttach_ModalLess(bUpdateText);
	hide();
}

void WidgetKeyboardV_Digit::ClearExternAttach_ModalLess(bool bUpdateText)
{
	if (bUpdateText && (m_pExternalCtrl != NULL))
	{
		m_strEditInfo = lineEdit->text();
		m_pExternalCtrl->UpdateText(m_strEditInfo);
	}

	if (m_bTableWidget)
	{
		if (m_pParent != NULL)
		{
			disconnect(this,SIGNAL(sig_Vamp(QString)),m_pParent,SLOT(slot_UpdataVamp(QString)));
			disconnect(this,SIGNAL(sig_Aamp(QString)),m_pParent,SLOT(slot_UpdataIamp(QString)));
			disconnect(this,SIGNAL(sig_Hzamp(QString)),m_pParent,SLOT(slot_UpdataHzamp(QString)));
			disconnect(this,SIGNAL(sig_ZX(QString)),m_pParent,SLOT(slot_UpdataZX(QString)));
			disconnect(this,SIGNAL(sig_FX(QString)),m_pParent,SLOT(slot_UpdataFX(QString)));
			disconnect(this,SIGNAL(sig_LX()),m_pParent,SLOT(slot_UpdataLX()));
		}

		m_bTableWidget = 0;
	}

	if (m_pExternalCtrl != NULL)
	{
		m_pExternalCtrl = NULL;
	}
}

void WidgetKeyboardV_Digit::EnableBtns()
{
	btn_57V->show();
	btn_10V->show();
	btn_100V->show();
	btn_50V->show();
	btn_20V->show();
	btn_30V->show();
	btn_amp->show();
	btn_abc->show();
}

void WidgetKeyboardV_Digit::InitTypeV()
{
	EnableBtns();

	btn_57V->setText("57.74V");
	btn_10V->setText("10V");
	btn_100V->setText("100V");
	btn_50V->setText("50V");
	btn_20V->setText("20V");
	btn_30V->setText("30V");
	btn_amp->setText(m_strAmp);
}

void WidgetKeyboardV_Digit::InitTypeA()
{
	EnableBtns();

	btn_57V->setText("10A");
	btn_10V->setText("+0.5A");
	btn_100V->setText("20A");
	btn_50V->setText("5A");
	btn_20V->setText("0.5A");
	btn_30V->setText("1A");
	btn_amp->setText(m_strAmp);
}

void WidgetKeyboardV_Digit::InitTypeHz()
{
	EnableBtns();

	btn_10V->setText("50Hz");
	btn_20V->setText("60Hz");
	btn_30V->hide();
	btn_50V->hide();
	btn_57V->hide();
	btn_100V->hide();
	btn_amp->setText(m_strFreq);
}

void WidgetKeyboardV_Digit::InitTypePh()
{
	EnableBtns();

	btn_abc->setEnabled (true );
	btn_abc->setStyleSheet("QToolButton{background-color: #313131;border-style: flat;color:white;}"
		"QToolButton:pressed{background-color: #414141;border-style: flat;}");
	btn_10V->setText("90°");
	btn_20V->setText("120°");
	btn_30V->setText("180°");
	btn_50V->setText("240°");
#ifndef _PSX_QT_LINUX_
	btn_10V->setText(QString::fromLocal8Bit("90°"));
	btn_20V->setText(QString::fromLocal8Bit("120°"));
	btn_30V->setText(QString::fromLocal8Bit("180°"));
	btn_50V->setText(QString::fromLocal8Bit("240°"));
#endif
	btn_57V->setText(m_strPosi);
	btn_100V->setText(m_strNega);
	btn_amp->setText(m_strZero);
	btn_57V->setStyleSheet("QToolButton{background-color: #577b7c;border-style: flat;color:white;}"
		"QToolButton:pressed{background-color: #414141;border-style: flat;}");
	btn_100V->setStyleSheet("QToolButton{background-color: #577b7c;border-style: flat;color:white;}"
		"QToolButton:pressed{background-color: #414141;border-style: flat;}");
}

void WidgetKeyboardV_Digit::InitTpyeNor()
{
	//2022-1-17 yzj 普通模式
	btn_57V->hide();
	btn_10V->hide();
	btn_100V->hide();
	btn_50V->hide();
	btn_amp->hide();
	btn_abc->hide();
	btn_20V->hide();
	btn_30V->hide();
}

void WidgetKeyboardV_Digit::Init(QWidget* parent)
{
	m_pParent = parent;

	if (m_pSignalMapper == NULL)
	{
		int FontSize  = 16;
		m_nCurSelPos = -1;
		setupUi(this);
		resize(0,0);
		this->setWindowFlags(Qt::Tool);

		if (isModal())
		{
			setWindowFlags(Qt::FramelessWindowHint) ;
		}
		else
		{
			setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
		}

		m_pSignalMapper = new QSignalMapper(this);
		m_pButtonsList.clear();
		//m_pButtonsList = findChildren<QToolButton *>();
		xlang_GetLangStrByFile(m_strFreq, "Native_EqualFreq");
		xlang_GetLangStrByFile(m_strAmp, "Native_EqualAmp");
		btn_amp->setText(m_strAmp);
		xlang_GetLangStrByFile(m_strDelete, "Native_Delete");
		btn_dele->setText(m_strDelete);
		xlang_GetLangStrByFile(m_strEnter, "Native_Enter");
		btn_enter->setText(m_strEnter);
		//xlang_GetLangStrByFile(m_strEsc, "Native_Esc");
		//btn_esc->setText(m_strEsc);
		xlang_GetLangStrByFile(m_strNega, "Native_NegativeSeq");
		xlang_GetLangStrByFile(m_strZero, "Native_ZeroSeq");
		xlang_GetLangStrByFile(m_strPosi, "Native_PositiveSeq");

		m_pButtonsList.push_back(btn_1);
		m_pButtonsList.push_back(btn_2);
		m_pButtonsList.push_back(btn_3);
		m_pButtonsList.push_back(btn_57V);
		m_pButtonsList.push_back(btn_10V);
		m_pButtonsList.push_back(btn_4);
		m_pButtonsList.push_back(btn_5);
		m_pButtonsList.push_back(btn_6);
		m_pButtonsList.push_back(btn_100V);
		m_pButtonsList.push_back(btn_50V);
		m_pButtonsList.push_back(btn_7);
		m_pButtonsList.push_back(btn_8);
		m_pButtonsList.push_back(btn_9);
		m_pButtonsList.push_back(btn_amp);
		m_pButtonsList.push_back(btn_dele);
		m_pButtonsList.push_back(btn_abc);
		m_pButtonsList.push_back(btn_0);
		m_pButtonsList.push_back(btn_dol);
		m_pButtonsList.push_back(btn_enter);
		m_pButtonsList.push_back(btn_20V);
		m_pButtonsList.push_back(btn_30V);

		for (int i = 0; i < m_pButtonsList.count(); i++)
		{
			m_pButtonsList.at(i)->setFont(QFont("宋体", FontSize, 2));
			m_pButtonsList.at(i)->setStyleSheet("QToolButton{background-color: #313131;border-style: flat;color:white;}"
				"QToolButton:pressed{background-color: #414141;border-style: flat;}");
			connect(m_pButtonsList.at(i), SIGNAL(clicked()), m_pSignalMapper, SLOT(map()));
			m_pSignalMapper->setMapping(m_pButtonsList.at(i), i);
		}
		connect(m_pSignalMapper, SIGNAL(mapped(int)), this, SLOT(on_btn_clicked(int)));

		btn_abc->setEnabled(false);
		btn_abc->setStyleSheet("QToolButton{background-color: #313131;border-style: flat;}"
			"QToolButton:pressed{background-color: #414141;border-style: flat;}");
		btn_amp->setStyleSheet("QToolButton{background-color: #577b7c;border-style: flat;color:white;}"
			"QToolButton:pressed{background-color: #414141;border-style: flat;}");
		btn_57V->setStyleSheet("QToolButton{background-color: #59503c;border-style: flat;color:white;}"
			"QToolButton:pressed{background-color: #414141;border-style: flat;}");
		btn_10V->setStyleSheet("QToolButton{background-color: #59503c;border-style: flat;color:white;}"
			"QToolButton:pressed{background-color: #414141;border-style: flat;}");
		btn_100V->setStyleSheet("QToolButton{background-color: #59503c;border-style: flat;color:white;}"
			"QToolButton:pressed{background-color: #414141;border-style: flat;}");
		btn_50V->setStyleSheet("QToolButton{background-color: #59503c;border-style: flat;color:white;}"
			"QToolButton:pressed{background-color: #414141;border-style: flat;}");
		btn_dele->setStyleSheet("QToolButton{background-color: #191615;border-style: flat;color:white;}"
			"QToolButton:pressed{background-color: #414141;border-style: flat;}");
		btn_enter->setStyleSheet("QToolButton{background-color: #191615;border-style: flat;color:white;}"
			"QToolButton:pressed{background-color: #414141;border-style: flat;}");
		btn_20V->setStyleSheet("QToolButton{background-color: #59503c;border-style: flat;color:white;}"
			"QToolButton:pressed{background-color: #414141;border-style: flat;}");
		btn_30V->setStyleSheet("QToolButton{background-color: #59503c;border-style: flat;color:white;}"
			"QToolButton:pressed{background-color: #414141;border-style: flat;}");

		btn_enter->setText(m_strEnter);

		lineEdit->setFocus(Qt::MouseFocusReason);
		//lineEdit->setFocusPolicy(Qt::NoFocus);
		lineEdit->setFont(QFont("宋体", FontSize, 2));
		lineEdit->selectAll();
		//lineEdit->setSelection(0,20);
		//widget->setFocus();
		//widget->installEventFilter(this);
		lineEdit->installEventFilter(this);
	}
	else
	{
		lineEdit->setFocus(Qt::MouseFocusReason);
		lineEdit->selectAll();
	}

	//this->setFixedSize(800,350);
}

WidgetKeyboardV_Digit::~WidgetKeyboardV_Digit()
{
	if (m_pSignalMapper != NULL)
	{
		delete m_pSignalMapper;
		m_pSignalMapper = NULL;
	}
}

void WidgetKeyboardV_Digit::keyPressEvent( QKeyEvent *event )
{
	int nKey = event->key();
	switch(event->key())
	{
		//进行界面退出，重写Esc键，否则重写reject()方法
	case Qt::Key_Escape:
		{
			on_btnEsc_clicked(true);
		}
		break;
	case Qt::Key_Return:
		{
			on_btnReturn_clicked(true);
			//on_btn_clicked(m_nCurSelPos);
		}
		break;
	case Qt::Key_Home:
		{

//			homeActive(this);
		}
		break;
	case Qt::Key_F1:
		{
			on_btnEsc_clicked(true);
		}
		break;
	case  Qt::Key_F2:
		{
			on_btnReturn_clicked(true);
		}
		break;
	case  Qt::Key_F3:
		{
			QString ch(m_strDelete);
			Qt::KeyboardModifiers Modifier = Qt::NoModifier;
			int keyId = Qt::Key_Backspace;
			QKeyEvent keyEvent(QEvent::KeyPress, keyId, Modifier, ch, false,1);
			QApplication::sendEvent(lineEdit/*->focusWidget()*/, &keyEvent);
		}
		break;
	default:
		QDialog::keyPressEvent(event);
	}
}

bool WidgetKeyboardV_Digit::eventFilter( QObject *obj, QEvent *event )
{
    if(event->type() == QEvent::KeyPress)
    {
       QKeyEvent *pe = (QKeyEvent*)event;
       if (pe->key()==Qt::Key_Home)
       {
//           homeActive(this);
           return true;
       }

	   if (pe->key()==Qt::Key_Right )
	   {
		   if (m_nCurSelPos>= 0 && m_nCurSelPos < 19)
		   {
			   m_nCurSelPos +=1;

		   }
		   else
		   {
				m_nCurSelPos = 18;
		   }
		   setSelState(m_nCurSelPos);
		   return true;
	   }

	   if (pe->key()==Qt::Key_Left )
	   {
		   if (m_nCurSelPos> 0 && m_nCurSelPos < 20)
		   {
			   m_nCurSelPos -=1;

		   }
		   else
		   {

		   }

		   setSelState(m_nCurSelPos);
		   return true;
	   }

	   if (pe->key()==Qt::Key_Up )
	   {
		   if (m_nCurSelPos >= 5 && m_nCurSelPos < 16)
		   {
			   m_nCurSelPos -=5;
		   }
		   else if (m_nCurSelPos >=16)
		   {
			   m_nCurSelPos-=4;
		   }
		   else if (m_nCurSelPos > 0 && m_nCurSelPos< 6)
		   {
			   m_nCurSelPos=-1;
		   }
		   else
		   {
			   lineEdit->setFocus(Qt::MouseFocusReason);
			   lineEdit->selectAll();
			   m_nCurSelPos=0;
		   }

		   setSelState(m_nCurSelPos);
		   return true;
	   }

	   if (pe->key()==Qt::Key_Down )
	   {
		   if (m_nCurSelPos >= 0 && m_nCurSelPos < 11)
		   {
			   m_nCurSelPos +=5;
		   }
		   else if (m_nCurSelPos >=11 && m_nCurSelPos<=15)
		   {
			   m_nCurSelPos+=4;
		   }
		   else if (m_nCurSelPos == -1)
		   {
			   m_nCurSelPos+=1;
		   }
		   else
		   {
			   //m_nCurSelPos=0;
		   }

		   setSelState(m_nCurSelPos);
		   return true;
	   }
    }
	return QDialog::eventFilter(obj,event);
}

void WidgetKeyboardV_Digit::showToEdit()
{
	QRect rc = m_pParent->topLevelWidget()->geometry();
	long nHeight = 210 + rc.height() - 600;
	setGeometry(rc.left(), rc.top() + nHeight, 1024, 350);
	//lineEdit->setFocus(Qt::MouseFocusReason);
	if (m_strEditInfo.toInt() == 0 && m_strEditInfo.toFloat() == 0.0)
	{
		lineEdit->setText("0");
	}
	else
	{
		lineEdit->setText(m_strEditInfo);
		lineEdit->setFocus(Qt::MouseFocusReason);
		lineEdit->selectAll();
	}
}

void WidgetKeyboardV_Digit::CloseOrHideDlg()
{
	if (isModal())
	{
		close();
	} 
	else
	{
		ExitHide_ModalLess();
	}
}

void WidgetKeyboardV_Digit::on_btn_clicked( int btn )
{
	QString strKeyId;
    if(btn == -1)
    {
        CloseOrHideDlg();
        return;
    }

	strKeyId = m_pButtonsList.at(btn)->accessibleName();
	bool isOk;
	int keyId = strKeyId.toInt(&isOk, 16);
	if (strKeyId.isEmpty() || !isOk)
	{
		CXMessageBox::information(0,0,"Key Not Found");
		return;
	}

	bool isTextKey = false;
	Qt::KeyboardModifiers Modifier = Qt::NoModifier;

	QString ch = m_pButtonsList.at(btn)->text().trimmed();
    if (ch.compare(m_strEsc, Qt::CaseInsensitive) == 0)
	{
		CloseOrHideDlg();
		return;
	}
    if (ch.compare(m_strEnter, Qt::CaseInsensitive) == 0)
	{
		on_btnReturn_clicked(true);
		return;
	}
	if (ch.compare(m_strDelete, Qt::CaseInsensitive) == 0)
	{
		QWidget *receiver = QApplication::focusWidget();
		QKeyEvent keyPress(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier, QString(""));
		QKeyEvent keyRelease(QEvent::KeyRelease, Qt::Key_Backspace, Qt::NoModifier, QString(""));
		QApplication::sendEvent(receiver, &keyPress);
		QApplication::sendEvent(receiver, &keyRelease);
		return;
	}
	if (m_nType == 2)
	{
		if (ch == "-")
		{
			QString str= lineEdit->text();
			//str = str.left(str.length() -1);
			str = "-"+str;
			lineEdit->clear();
			lineEdit->setText(str);
			return;
		}

        if (ch.compare(m_strPosi, Qt::CaseInsensitive) == 0)
		{
			QString str= lineEdit->text();
			emit(sig_ZX(str));
			//lineEdit->clear();
			CloseOrHideDlg();
		}
        else if (ch.compare(m_strNega, Qt::CaseInsensitive) == 0)
		{
			QString str= lineEdit->text();
			emit(sig_FX(str));
			//lineEdit->clear();
			CloseOrHideDlg();
		}
        else if (ch.compare(m_strZero, Qt::CaseInsensitive) == 0)
		{
			emit(sig_LX());
			//lineEdit->clear();
			CloseOrHideDlg();
		}
		else if (ch.indexOf("120") != -1)
		{
			lineEdit->clear();
		}
		else if (ch.indexOf("240") != -1)
		{
			lineEdit->clear();
		}
		else if (ch.indexOf("90") != -1)
		{
			lineEdit->clear();
		}
		else if (ch.indexOf("180") != -1)
		{
			lineEdit->clear();
		}
	}
	else if (m_nType == 1)
	{
		if (ch ==m_strAmp )
		{
			QString value = lineEdit->text();
			emit(sig_Aamp(value));
			CloseOrHideDlg();
		}
		else if (ch == "0.5A")
		{
			lineEdit->clear();
		}
		else if (ch == "10A")
		{
			lineEdit->clear();
		}
		else if (ch == "20A")
		{
			lineEdit->clear();
		}
		else if (ch == "1A")
		{
			lineEdit->clear();
		}
		else if (ch == "5A")
		{
			lineEdit->clear();
		}
	}
	else if (m_nType  == 0)
	{
		if (ch ==m_strAmp )
		{
			QString value = lineEdit->text();
			emit(sig_Vamp(value));
			CloseOrHideDlg();
		}
		else if (ch == "57.74V")
		{
			lineEdit->clear();
		}
		else if (ch == "10V")
		{
			lineEdit->clear();
		}
		else if (ch == "20V")
		{
			lineEdit->clear();
		}
		else if (ch == "30V")
		{
			lineEdit->clear();
		}
		else if (ch == "50V")
		{
			lineEdit->clear();
		}
		else if (ch == "100V")
		{
			lineEdit->clear();
		}
	}
	else if (m_nType == 3)
	{
		if (ch == m_strFreq)
		{
			QString value = lineEdit->text();
			emit(sig_Hzamp(value));
			CloseOrHideDlg();
		}
		else if (ch == "50Hz")
		{
			lineEdit->clear();
		}
		else if (ch == "60Hz")
		{
			lineEdit->clear();
		}
	}

	if (ch=="&&")
	{
		ch = "&";
	}
	else if (keyId==Qt::Key_Space)
	{
		ch = " ";
	}
	else if (checkNotTextKey(keyId))
	{
		ch = QString();
	}
	else if (ch == "-")
	{
		ch = "-";
	}
	else
	{
		isTextKey = true;
	}

	
	if (ch=="Backspace")
		keyId = Qt::Key_Backspace;


	int num =0 ;
	if (isTextKey && (isDigit(ch)  == false))
	{	
		if(m_nType == 3)
		{
			ch = ch.left(ch.length() - 2);
		}
		else
		{
			ch = ch.left(ch.length() - 1);	
		}
	}
	if (ch == "+0.5")
	{
		QString str = lineEdit->text().trimmed();
		float temp = str.toFloat();
		temp += 0.5;
		
		lineEdit->setText(QString::number(temp));
		return;
	}

	QKeyEvent keyEvent(QEvent::KeyPress, keyId, Modifier, ch, false,1);
	QApplication::sendEvent(lineEdit/*->focusWidget()*/, &keyEvent);
}

bool WidgetKeyboardV_Digit::checkNotTextKey( int keyId )
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

void WidgetKeyboardV_Digit::on_btnReturn_clicked( bool checked )
{
	m_strEditInfo = lineEdit->text();

	if (isModal())
	{
		this->accept();
	}
	else
	{
		if (m_pExternalCtrl != NULL)
		{
			m_pExternalCtrl->UpdateText(m_strEditInfo);
		}

		ExitHide_ModalLess();
	}
}

void WidgetKeyboardV_Digit::on_btnEsc_clicked( bool checked )
{
	this->CloseOrHideDlg();
}

bool WidgetKeyboardV_Digit::isDigit(QString src)
{
	QByteArray ba = src.toLatin1();//QString 转换为 char*  
	const char *s = ba.data();  

	while((*s && *s>='0' && *s<='9') || (*s =='.')) s++;  

	if (*s)  
	{ //不是纯数字  
		return false;  
	}  
	else  
	{ //纯数字  
		return true;  
	}  
}

int WidgetKeyboardV_Digit::isPosiDigitstr(QString str)
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
			//emit(sendWarnLog(tr("output valid value,pls！")));
			return -1;
		}
		s++;
		fDigNum++;
	}

	return dot;
}

void WidgetKeyboardV_Digit::setSelState( int selPos)
{
	for(int i =0;i<m_pButtonsList.size();i++)
	{
		QToolButton * pEdit = static_cast<QToolButton*>(m_pButtonsList[i]);
		if (pEdit == NULL)
		{
			continue;
		}
		if(i==selPos)
		{
			//pEdit->setFocus();
			pEdit->setStyleSheet(QString("color:white ; background-color: darkgray"));
		}
		else
		{
			if (pEdit == btn_57V || pEdit == btn_10V || pEdit == btn_100V || pEdit == btn_50V )
			{
				pEdit->setStyleSheet("QToolButton{background-color: #59503c;border-style: flat;color:white;}"
					"QToolButton:pressed{background-color: #414141;border-style: flat;}");
			}
			else if (pEdit == btn_dele || pEdit == btn_enter /*|| pEdit==btn_esc*/)
			{
				pEdit->setStyleSheet("QToolButton{background-color: #191615;border-style: flat;color:white;}"
					"QToolButton:pressed{background-color: #414141;border-style: flat;}");
			}
			else
			{
				pEdit->setStyleSheet("QToolButton{background-color: #313131;border-style: flat;color:white;}"
					"QToolButton:pressed{background-color: #414141;border-style: flat;}");
			}
		}
	}
}

void WidgetKeyboardV_Digit::selectAll()
{
	lineEdit->setText(m_strEditInfo);
	lineEdit->setFocus(Qt::MouseFocusReason);
	lineEdit->selectAll();
}

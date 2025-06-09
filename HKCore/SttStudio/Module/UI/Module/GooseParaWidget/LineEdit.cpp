#include "LineEdit.h"
#include <QtGui>

CLineEdit::CLineEdit(TEXT_TYPE _type, const QString &_strValue, QWidget *parent)
	: QLineEdit(parent),m_type(_type),m_flag(0),m_strPre(_strValue)
{
	switch(m_type)
	{
	case MAC_TEXT:
		{
			setInputMask(">HH-HH-HH-HH-HH-HH");
			break;
		}
	case APPID_TEXT:
		{
			setInputMask("9A>HHHH");
			break;
		}
	case CHANNAL_NUM:
		{
			QRegExp regExp("^([1-9]\\d{0,1}|1\\d\\d|2[0-4]\\d|25[0-6])$");
			QValidator *validator = new QRegExpValidator(regExp,this);
			setValidator(validator);
		}
	default:
		break;
	}

	connect(this,SIGNAL(textChanged(QString)),SLOT(OnTextChanged(QString)));
	connect(this,SIGNAL(cursorPositionChanged(int, int)),SLOT(OnCursorPositionChanged(int, int)));
}

CLineEdit::~CLineEdit()
{

}

void CLineEdit::OnTextChanged(const QString &text)
{
	switch(m_type)
	{
	case MAC_TEXT:
		{
			if(m_flag < 2)
			{
				setText(m_strPre);
				setCursorPosition(0);
				m_flag++;
			}

			break;
		}
	case APPID_TEXT:
		{
			if(m_flag < 2)
			{
				setText(m_strPre);
				setCursorPosition(2);
				m_flag++;
			}

			break;
		}
	case CHANNAL_NUM:
		{
			if (text == "")
			{
				setText("1");
			}
			break;
		}
	default:
		break;
	}
}

void CLineEdit::OnCursorPositionChanged(int /*oldPos*/, int newPos)
{
	switch(m_type)
	{
	case APPID_TEXT:
		{
			if(newPos == 0 || newPos == 1 || newPos == 6)
				setCursorPosition(2);
			break;
		}
	case MAC_TEXT:
		{
			if(newPos == 0 || newPos == 17)
				setCursorPosition(0);
			break;
		}
	default:
		break;
	}
}

void CLineEdit::keyPressEvent(QKeyEvent *event)
{
	switch(m_type)
	{
	case APPID_TEXT:
	case MAC_TEXT:
		{
			if (event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete)
				return ;
		}
	default:
		break;
	}
	
	QLineEdit::keyPressEvent(event);
}
#include "QIecLineEdit.h"
#include <QValidator>
#include <QKeyEvent>

QIecLineEdit::QIecLineEdit(TEXT_TYPE _type, const QString &_strValue, QWidget *parent)
	: QLineEdit(parent),m_oTextType(_type),m_nFlag(0)/*,m_strPre(_strValue)*/
{
	switch(m_oTextType)
	{
	case MAC_TEXT:
		{
			setInputMask(">HH-HH-HH-HH-HH-HH");
			break;
		}
	case HEX_TEXT:
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

void QIecLineEdit::InitHexFormat(long nHexLenth)
{
	QString strTmp = "9A>";

	while(nHexLenth>0)
	{
		strTmp += "HH";
		nHexLenth--;
	}

	setInputMask(strTmp);
}

QIecLineEdit::~QIecLineEdit()
{

}

void QIecLineEdit::OnTextChanged(const QString &text)
{
	switch(m_oTextType)
	{
	case MAC_TEXT:
		{
			if(m_nFlag < 2)
			{
				//setText(m_strPre);
				setCursorPosition(0);
				m_nFlag++;
			}

			break;
		}
	case HEX_TEXT:
		{
			if(m_nFlag < 1)//cl20230905修改APPID输入第一位重复输入两次问题
			{
				//setText(m_strPre);
				setCursorPosition(2);
				m_nFlag++;
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

	//qDebug()<<text;
}

void QIecLineEdit::OnCursorPositionChanged(int /*oldPos*/, int newPos)
{
	switch(m_oTextType)
	{
	case HEX_TEXT:
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

void QIecLineEdit::keyPressEvent(QKeyEvent *event)
{
	switch(m_oTextType)
	{
	case HEX_TEXT:
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
void QIecLineEdit::mousePressEvent(QMouseEvent *event)
{
	//如果单击了就触发clicked信号
	if (event->button() == Qt::LeftButton)
	{
		//触发clicked信号
		emit clicked();
	}

	//将该事件传给父类处理
	QLineEdit::mousePressEvent(event);
}
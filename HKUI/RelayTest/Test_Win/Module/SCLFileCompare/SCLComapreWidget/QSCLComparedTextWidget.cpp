#include "QSCLComparedTextWidget.h"
#include "../../../../Module/OSInterface/QT/CString_QT.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTextCodec>

QSCLComparedTextWidget::QSCLComparedTextWidget(QWidget *parent):QWidget(parent)
{
	m_pCompLabel = NULL;
	m_pSourLabel = NULL;
	m_pTextComparedSplitter = NULL;
 	m_pSourTextEdit = NULL;
 	m_pCompTextEdit = NULL;

	InitUI();
}

QSCLComparedTextWidget::~QSCLComparedTextWidget()
{

}

void QSCLComparedTextWidget::InitUI()
{
	CString strText;
	strText = _T("源文件");
	m_pSourLabel = new QLabel(strText);
	strText = _T("比对文件");
	m_pCompLabel = new QLabel(strText);

	m_pCompTextEdit = new QLineNumberTextEdit();
	m_pSourTextEdit = new QLineNumberTextEdit();
// 	m_pSourTextEdit->setReadOnly(true); 
// 	m_pCompTextEdit->setReadOnly(true); 

	m_pSourTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
	m_pCompTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);

	QScrollArea *scrollAreaSour = new QScrollArea;
	scrollAreaSour->setWidgetResizable(true);
	scrollAreaSour->setWidget(m_pSourTextEdit);
	scrollAreaSour->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	QScrollArea *scrollAreaComp = new QScrollArea;
	scrollAreaComp->setWidgetResizable(true);
	scrollAreaComp->setWidget(m_pCompTextEdit);
	scrollAreaComp->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	QVBoxLayout *pSourLayout = new QVBoxLayout;
	pSourLayout->addWidget(m_pSourLabel);
	pSourLayout->addWidget(scrollAreaSour);
	QWidget *pSourWidget = new QWidget;
	pSourWidget->setLayout(pSourLayout);

	QVBoxLayout *pCompLayout = new QVBoxLayout;
	pCompLayout->addWidget(m_pCompLabel);
	pCompLayout->addWidget(scrollAreaComp);
	QWidget *pCompWidget = new QWidget;
	pCompWidget->setLayout(pCompLayout);

	m_pTextComparedSplitter = new QSplitter(Qt::Horizontal);
	m_pTextComparedSplitter->addWidget(pSourWidget);
	m_pTextComparedSplitter->addWidget(pCompWidget);

	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(m_pTextComparedSplitter);
	setLayout(pMainLayout);
}


void QSCLComparedTextWidget::ShowText(CString& strSourText, CString& strCompText)
{
 	m_pSourTextEdit->setPlainText(strSourText);
 	m_pCompTextEdit->setPlainText(strCompText);

	CompareAndMarkDifference();// 进行文件内容的比较，并标记不同之处
}


void QSCLComparedTextWidget::CompareAndMarkDifference()
{
//  	CString strSourText = m_pSourTextEdit->toPlainText();
//  	CString strCompTex = m_pCompTextEdit->toPlainText();
//  
//  	QList<QTextEdit::ExtraSelection> selections;
//  
//  	// 比较两个文本内容，找出不同之处
//  	int index = 0;
//  	while (index < strSourText.length() || index < strCompTex.length())
//  	{QPlainTextEdit
//  		if (strSourText.at(index) != strCompTex.at(index))
//  		{
//  			// 记录不同之处的起始位置和长度
//  			int startPos = index;
//  			int length = 0;
//  
//  			// 找出差异的结束位置
//  			while (index < strSourText.length() && strSourText.at(index) != strCompTex.at(index))
//  			{
//  				++index;
//  				++length;
//  			}
//  
//  			// 创建一个 ExtraSelection 对象，并设置颜色
//  			QTextEdit::ExtraSelection selection;
//  			selection.cursor = m_pSourTextEdit->textCursor();
//  			selection.cursor.setPosition(startPos);
//  			selection.cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, length);
//  			selection.format.setBackground(Qt::yellow);
//  			selections.append(selection);
//  		}
//  		else
//  		{
//  			++index;
//  		}
//  	}
//  
//  	// 设置不同之处的颜色
//  	m_pSourTextEdit->setExtraSelections(selections);
}



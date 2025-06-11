#include "SttIecFT3LineNumberPlanTextEdit.h"
#include <QPaintEvent>
#include <QScrollBar>
#include <QTextLayout>
#include <QFontMetrics>
#include <QAbstractTextDocumentLayout>
#include <QSize>
#include <QPainter>
#include <QTextBlock>
#include "../../../../../Module/API/GlobalConfigApi.h"

QSttIecFT3LineNumberPlanTextEdit::QSttIecFT3LineNumberPlanTextEdit(QWidget *parent) : QPlainTextEdit(parent)//
{
	m_pLineNumberArea = new QLineNumberArea(this);

	connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
	connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
	connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

	updateLineNumberAreaWidth(0);
}
int QSttIecFT3LineNumberPlanTextEdit::lineNumberAreaWidth()
{
	/*int digits = 1;
	int max = qMax(1, blockCount());
	while (max >= 10) 
	{
		max /= 10;
		++digits;
	}

	int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;*/
	int digits = 4; // 行号最多有8位，例如 00000000
	int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

	return space;
}

void QSttIecFT3LineNumberPlanTextEdit::updateLineNumberAreaWidth(int /* newBlockCount */)
{
	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void QSttIecFT3LineNumberPlanTextEdit::updateLineNumberArea(const QRect &rect, int dy)
{
	if (dy)
	{
		m_pLineNumberArea->scroll(0, dy);
	}
	else
	{
		m_pLineNumberArea->update(0, rect.y(), m_pLineNumberArea->width(), rect.height());
	}

	if (rect.contains(viewport()->rect()))
	{
		updateLineNumberAreaWidth(0);
	}
}

void QSttIecFT3LineNumberPlanTextEdit::resizeEvent(QResizeEvent *e)
{
	QPlainTextEdit::resizeEvent(e);

	QRect cr = contentsRect();
	m_pLineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}
void QSttIecFT3LineNumberPlanTextEdit::highlightCurrentLine()
{
 	QList<QTextEdit::ExtraSelection> extraSelections;
 
 	QTextEdit::ExtraSelection selection;
 
 	QColor lineColor = QColor(Qt::yellow).lighter(160);
 
 	selection.format.setBackground(lineColor);
 	selection.format.setProperty(QTextFormat::FullWidthSelection, true);
 	selection.cursor = textCursor();
 	selection.cursor.clearSelection();
 	extraSelections.append(selection);
 
 	setExtraSelections(extraSelections);
}

void QSttIecFT3LineNumberPlanTextEdit::lineNumberAreaPaintEvent(QPaintEvent *event)
{
	QPainter painter(m_pLineNumberArea);
	painter.fillRect(event->rect(), Qt::lightGray);

	QTextBlock block = firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = (int)blockBoundingGeometry(block).translated(contentOffset()).top();
	int bottom = top + (int)blockBoundingRect(block).height();

	while (block.isValid() && top <= event->rect().bottom())
	{
		if (block.isVisible() && bottom >= event->rect().top())
		{
			QString number = QString("%1").arg(blockNumber * 16, 4, 16, QChar('0')).toLower();
			painter.setPen(Qt::black);
			QFontMetrics fm = fontMetrics();
			int width = fm.width(number);
			int x = lineNumberAreaWidth() - width - 2;
			painter.drawText(x, top, width, fm.height(),
				Qt::AlignRight, number.prepend("0000 "));
		}

		block = block.next();
		top = bottom;
		bottom = top + (int)blockBoundingRect(block).height();
		++blockNumber;
	}
}

void QSttIecFT3LineNumberPlanTextEdit::SetHexValue(char *pValue, long nLenth)
{
	CString strHex;
	strHex = "";
	char hex[3];
	memset(hex,0,3);
	long nHexCountIndex = 1;

	for(int nIndex = 0;  nIndex<nLenth; nIndex++)
	{
		ValueToHex((BYTE)pValue[nIndex], hex, false ,false);	//	转换为16进制

		strHex.append(hex);

		if(nHexCountIndex >= 16)
		{
			strHex += "\n ";
			nHexCountIndex = 1;
		}
		else if(nHexCountIndex == 8)
		{
			strHex += "  ";
			++nHexCountIndex;
		}
		else
		{
			strHex += " ";
			++nHexCountIndex;
		}
	}

	setPlainText(strHex);
}

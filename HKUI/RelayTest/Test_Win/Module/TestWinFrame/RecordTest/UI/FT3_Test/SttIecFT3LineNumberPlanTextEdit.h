#ifndef SttIecFT3LineNumberPlanTextEdit_H
#define SttIecFT3LineNumberPlanTextEdit_H

#include <QPlainTextEdit>
#include <QWidget>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QPainter>

class QLineNumberArea;

class QSttIecFT3LineNumberPlanTextEdit : public QPlainTextEdit
{
	Q_OBJECT

public:
	QSttIecFT3LineNumberPlanTextEdit(QWidget *parent = 0);
	void lineNumberAreaPaintEvent(QPaintEvent *event);
	int lineNumberAreaWidth();

	void SetHexValue(char *pValue, long nLenth);

protected:
	void resizeEvent(QResizeEvent *event) /*override*/;//

private slots:
	void updateLineNumberAreaWidth(int newBlockCount);
	void highlightCurrentLine();
	void updateLineNumberArea(const QRect &, int);

private:
	QWidget *m_pLineNumberArea;
};

class QLineNumberArea : public QWidget
{
public:
	QLineNumberArea(QSttIecFT3LineNumberPlanTextEdit *pLineNumberTextEdit) : QWidget(pLineNumberTextEdit) 
	{
		m_pLineNumberPlanTextEdit = pLineNumberTextEdit;
	}

	QSize sizeHint() const /*override*/ 
	{
		return QSize(m_pLineNumberPlanTextEdit->lineNumberAreaWidth(), 0);
	}

protected:
	void paintEvent(QPaintEvent *event) /*override*/ 
	{
		m_pLineNumberPlanTextEdit->lineNumberAreaPaintEvent(event);
	}

private:
	QSttIecFT3LineNumberPlanTextEdit *m_pLineNumberPlanTextEdit;
};

#endif	//SttIecFT3LineNumberPlanTextEdit_H


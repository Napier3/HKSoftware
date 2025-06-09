#ifndef QLINENUMBEREDIT_H
#define QLINENUMBEREDIT_H

#include <QPlainTextEdit>
#include <QWidget>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QPainter>

class QLineNumberArea;

class QLineNumberTextEdit : public QPlainTextEdit
{
	Q_OBJECT

public:
	QLineNumberTextEdit(QWidget *parent = 0);
	void lineNumberAreaPaintEvent(QPaintEvent *event);
	int lineNumberAreaWidth();

protected:
	void resizeEvent(QResizeEvent *event) override;

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
	QLineNumberArea(QLineNumberTextEdit *pLineNumberTextEdit) : QWidget(pLineNumberTextEdit) 
	{
		m_pLineNumberTextEdit = pLineNumberTextEdit;
	}

	QSize sizeHint() const override 
	{
		return QSize(m_pLineNumberTextEdit->lineNumberAreaWidth(), 0);
	}

protected:
	void paintEvent(QPaintEvent *event) override 
	{
		m_pLineNumberTextEdit->lineNumberAreaPaintEvent(event);
	}

private:
	QLineNumberTextEdit *m_pLineNumberTextEdit;
};

#endif


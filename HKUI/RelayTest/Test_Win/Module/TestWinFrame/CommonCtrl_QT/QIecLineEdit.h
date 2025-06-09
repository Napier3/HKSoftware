/************************************************************************/
/* 该类用于实现table中嵌入的QLineEdit控制                                                                     */
/************************************************************************/
#ifndef QIECLINEEDIT_H
#define QIECLINEEDIT_H
#include <QLineEdit>
#include <QMouseEvent>

class QIecLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	//指定text的类型，来指定不同的输入掩码{MAC地址，APPID，通道数目}
	enum TEXT_TYPE{STRING_TEXT, MAC_TEXT, HEX_TEXT, CHANNAL_NUM}; 

	QIecLineEdit(TEXT_TYPE _type, const QString &_strValue="", QWidget *parent=NULL);
	~QIecLineEdit();

	void InitHexFormat(long nHexLenth);

	void SetEditFinished()//20220309 sf 键盘需要
	{
		emit editingFinished();
	}

protected:
	virtual void keyPressEvent (QKeyEvent *event);

private:
	TEXT_TYPE m_oTextType;
	int m_nFlag; //双击编辑lineEdit时，控制光标的位置

private slots:
	void OnTextChanged(const QString &text);
	void OnCursorPositionChanged(int oldPos, int newPos);

protected:
	virtual void mousePressEvent(QMouseEvent *event);

signals:
	void clicked();
};

#endif // QIECLINEEDIT_H

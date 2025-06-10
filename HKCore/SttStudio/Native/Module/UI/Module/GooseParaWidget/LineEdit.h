/************************************************************************/
/* 该类用于实现table中嵌入的QLineEdit控制                                                                     */
/************************************************************************/
#ifndef LINEEDIT_H
#define LINEEDIT_H

//#include "SingleTon.h"
#include <QLineEdit>

class CLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	//指定text的类型，来指定不同的输入掩码{MAC地址，APPID，通道数目}
	enum TEXT_TYPE{STRING_TEXT, MAC_TEXT, APPID_TEXT, CHANNAL_NUM}; 

	CLineEdit(TEXT_TYPE _type, const QString &_strValue="", QWidget *parent=NULL);
	~CLineEdit();

protected:
	virtual void keyPressEvent (QKeyEvent *event);

private:
	TEXT_TYPE m_type;
	QString m_strPre; //前一个值
	int m_flag; //双击编辑lineEdit时，控制光标的位置

private slots:
	void OnTextChanged(const QString &text);
	void OnCursorPositionChanged(int oldPos, int newPos);
};

#endif // LINEEDIT_H

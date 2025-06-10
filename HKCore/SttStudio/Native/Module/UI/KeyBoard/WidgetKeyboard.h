

#ifndef __WIDGETKEYBOARDS_H_
#define __WIDGETKEYBOARDS_H_

#include <QDialog>
#include <QKeyEvent>
#include <QSignalMapper>
#include <QTextEdit>
#include "ui_WidgetKeyboard.h"


#include "WidgetKeyboardZ.h"
#include "WidgetKeyboardF.h"
#include "WidgetKeyboardV.h"

class WidgetKeyboard : public QDialog, public Ui::WidgetKeyboard
{
    Q_OBJECT
public:
    WidgetKeyboard(QWidget *parent = NULL);
   ~WidgetKeyboard();
private:

public:
	QWidget *m_pParent;
    WidgetKeyboardZ* m_pKeyBoardZ_ABC;//字母键盘
    WidgetKeyboardV* m_pKeyBoardV_123;//数字键盘
    WidgetKeyboardF* m_pKeyBoardF;//符号键盘
    bool eventFilter(QObject *obj, QEvent *event);
public slots:
    void OnLoadSuccess(int a);

public:
 //   QString m_strEditInfo;
    QString m_InputString;

    void showToEdit();
    void getEditString();
	int isPosiDigitstr(QString str);
	void setDigitOnly(bool b);
	void setDigitNumbers(unsigned int count);
Q_SIGNALS://自定义信号

   // void keyPressEvent(QKeyEvent *event);
   // void reject();
//    bool eventFilter(QObject *obj, QEvent *event);

};
#endif /*__WIDGETKEYBOARDS_H_*/

#ifndef SttEventFilter_H
#define SttEventFilter_H

#include <QObject>
#include <QEvent>
#include <QMouseEvent>
#include <QWidget>
#include <QTimer>
#include <QLineEdit>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QTextBrowser>

#include "../../../../Module/API/GlobalConfigApi.h"

class QSttEventFilter : public QObject
{
    Q_OBJECT

public:
    explicit QSttEventFilter();
    ~QSttEventFilter();

    QWidget *m_pWidgetForHide;

private:
	 QWidget *m_pPrevPressedWidget;//前一个按下的widget
    //当前焦点的对象
    QWidget *m_pCurrentWidget;
    //当前焦点的单行文本框
    QLineEdit *m_pCurrentLineEdit;
    //当前焦点的多行文本框
    QTextEdit *m_pCurrentTextEdit;
    //当前焦点的富文本框
    QPlainTextEdit *m_pCurrentPlain;
    //当前焦点的文本浏览框
    QTextBrowser *m_pCurrentBrowser;
    //当前焦点控件的类型
    QString m_strCurrentEditType;
    //当前焦点控件属性
    QString m_strCurrentFlag;

	CString m_strCheckBoxStyleFocusIn;
	CString m_strCheckBoxStyleFocusOut;
	CString m_strRadioStyleFocusIn;
//	BOOL m_bMenuBtnFocusOut;
	QFont m_oCurrFont;
	
	QLineEdit *m_pPreLineEdit;//上一个获得焦点的文本框

protected:
    //事件过滤器,处理鼠标在汉字标签处单击操作
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    //焦点改变事件槽函数处理
    void focusChanged(QWidget *oldWidget, QWidget *nowWidget);

};

#endif // SttEventFilter_H

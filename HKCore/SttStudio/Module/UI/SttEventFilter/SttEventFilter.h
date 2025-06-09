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
	 QWidget *m_pPrevPressedWidget;//ǰһ�����µ�widget
    //��ǰ����Ķ���
    QWidget *m_pCurrentWidget;
    //��ǰ����ĵ����ı���
    QLineEdit *m_pCurrentLineEdit;
    //��ǰ����Ķ����ı���
    QTextEdit *m_pCurrentTextEdit;
    //��ǰ����ĸ��ı���
    QPlainTextEdit *m_pCurrentPlain;
    //��ǰ������ı������
    QTextBrowser *m_pCurrentBrowser;
    //��ǰ����ؼ�������
    QString m_strCurrentEditType;
    //��ǰ����ؼ�����
    QString m_strCurrentFlag;

	CString m_strCheckBoxStyleFocusIn;
	CString m_strCheckBoxStyleFocusOut;
	CString m_strRadioStyleFocusIn;
//	BOOL m_bMenuBtnFocusOut;
	QFont m_oCurrFont;
	
	QLineEdit *m_pPreLineEdit;//��һ����ý�����ı���

protected:
    //�¼�������,��������ں��ֱ�ǩ����������
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    //����ı��¼��ۺ�������
    void focusChanged(QWidget *oldWidget, QWidget *nowWidget);

};

#endif // SttEventFilter_H

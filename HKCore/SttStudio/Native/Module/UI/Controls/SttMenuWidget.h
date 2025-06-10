#ifndef QSTTMENUWIDGET_H
#define QSTTMENUWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

#include "../Config/Frame/SttFrame_Menus.h"
#include "SttItemButton.h"

#define Button_Max_Col   10

class QSttMenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QSttMenuWidget(CSttFrame_Menus *pMenus,CString strTestState,QFont font,QWidget *parent = 0);
	void Init();
	void AddTitleLabelToLayout(CExBaseObject *pMenu,int nCol);
    void AddButtonToLayout(CExBaseObject *pItem,int nRow,int nCol);
	void AdjustButtonWidth();
// 	bool eventFilter(QObject *obj, QEvent *event);

protected:
	virtual bool event(QEvent *event);

public:
    QGridLayout *m_pMainLayout;

    CSttFrame_Menus *m_pMenus;
    QFont m_font;
	int m_nMaxRow;
    int m_nWidth;
    int m_nHeight;
    QList<QSttItemButton*> m_Btnlist;
	QList<CString> m_strHideButton;
	int m_nButtonMaxWidth[Button_Max_Col];

	CString m_strTestState;

	bool m_bTestMacroUI;
signals:

public slots:
};

#endif // QSTTMENUWIDGET_H

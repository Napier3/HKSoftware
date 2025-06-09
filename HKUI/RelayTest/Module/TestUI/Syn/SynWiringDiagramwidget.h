#ifndef SYNWIRINGDIAGRAMWIDGET_H
#define SYNWIRINGDIAGRAMWIDGET_H

#include "stdafx.h"
#include <QWidget>
#include "../../SttCmd/GuideBook/SttMacroTest.h"

#define SYN_WIRING_UDEFINEONE			 0//系统->Ua1,待并->Ub1
#define SYN_WIRING_UDEFINETWO			 1//系统->Ua1,待并->Ubc1
#define SYN_WIRING_UDEFINETHREE		 2//系统->Ua2/Uz,待并->Uabc1
#define SYN_WIRING_UDEFINEFOUR			 3//系统->Uabc1,待并->Uabc2

namespace Ui {
	class QSynWiringDiagramWidget;
}

class QSynWiringDiagramWidget : public QWidget
{
	Q_OBJECT

public:
	explicit QSynWiringDiagramWidget(QWidget *parent = 0);
	~QSynWiringDiagramWidget();

	virtual void resizeEvent(QResizeEvent *);

	void SetRightPicLabel(const CString &strPicName);//设置接线图
	void UpdateWiringUI(int nType);//更新接线图
	//void setCommonData(CExBaseList* pCommonParaTest);//遍历链表获取电压定义

private:
	Ui::QSynWiringDiagramWidget *ui;

	int m_nType;//电压定义
signals:

	void sizeChanged();

public slots:

	void slot_UpdateUIPosition();
};

#endif // SYNWIRINGDIAGRAMWIDGET_H
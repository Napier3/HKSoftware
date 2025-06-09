#ifndef SYNWIRINGDIAGRAMWIDGET_H
#define SYNWIRINGDIAGRAMWIDGET_H

#include "stdafx.h"
#include <QWidget>
#include "../../SttCmd/GuideBook/SttMacroTest.h"

#define SYN_WIRING_UDEFINEONE			 0//ϵͳ->Ua1,����->Ub1
#define SYN_WIRING_UDEFINETWO			 1//ϵͳ->Ua1,����->Ubc1
#define SYN_WIRING_UDEFINETHREE		 2//ϵͳ->Ua2/Uz,����->Uabc1
#define SYN_WIRING_UDEFINEFOUR			 3//ϵͳ->Uabc1,����->Uabc2

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

	void SetRightPicLabel(const CString &strPicName);//���ý���ͼ
	void UpdateWiringUI(int nType);//���½���ͼ
	//void setCommonData(CExBaseList* pCommonParaTest);//���������ȡ��ѹ����

private:
	Ui::QSynWiringDiagramWidget *ui;

	int m_nType;//��ѹ����
signals:

	void sizeChanged();

public slots:

	void slot_UpdateUIPosition();
};

#endif // SYNWIRINGDIAGRAMWIDGET_H
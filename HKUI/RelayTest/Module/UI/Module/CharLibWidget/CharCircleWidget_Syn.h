#ifndef CharCircleWidget_Syn_H
#define CharCircleWidget_Syn_H

#include <QWidget>
#include <cmath> // 包含三角函数
#include <QLabel>
#include "../../../../../AutoTest/Module/Characteristic/Characteristic.h"

#include "CharEditWidgetBase.h"
class QCharCircleWidget_Syn : public QWidget
{
	Q_OBJECT  
public:
	QCharCircleWidget_Syn(QWidget *parent = 0);

	int m_nStartAngle; // 起始度数  
	int m_nSpanAngle; // 跨越度数

	float m_fAngleDegrees;	//箭头线段的角度

	CString strStartAngle; // 起始度数  
	CString strSpanAngle; // 跨越度数
	

	void SetAngle(int nStartAngle, int nSpanAngle);
	void SetArrowhead(float fAngleDegrees);

protected:  
#ifdef _PSX_QT_LINUX_
        virtual void paintEvent(QPaintEvent *event) ;
#else
	void paintEvent(QPaintEvent *event) override;
#endif
};

#endif 
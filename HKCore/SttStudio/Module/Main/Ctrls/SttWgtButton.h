#ifndef QSTTWGTBUTTON_H
#define	QSTTWGTBUTTON_H

#include <QToolButton>
#include "../Module/SttWgtBase.h"

class QSttWgtButton : public QSttWgtBase, public QToolButton
{
public:
	QSttWgtButton(QWidget* pParent = NULL);
	virtual ~QSttWgtButton();

public:
	virtual void InitUIOwn(CExBaseObject *pSttXuiData);
	void OnClick();
	void CalcGeometry(long& nX, long nCy, long nInset);//¼ÆËãÆ«ÒÆ

private: 
	void mousePressEvent(QMouseEvent *e);

};

#endif//!QSTTWGTBUTTON_H
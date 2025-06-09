#ifndef QSTTWGTBUTTONGROUP_H
#define	QSTTWGTBUTTONGROUP_H

#include <QWidget>
#include "../Module/SttWgtBaseList.h"
#include "../SttXuiData/SttXuiDataBtnsGroup.h"
#include "../SttXuiData/SttXuiDataTestBtnsGroup.h"

class QSttWgtButtonGroup : public QSttWgtBaseList, public QWidget
{
public:
	QSttWgtButtonGroup(QWidget* pParent = NULL);
	virtual ~QSttWgtButtonGroup();

private:
	void InitTestBtnsGroup(CExBaseObject *pSttXuiData);
	void InitBtnsGroup(CExBaseObject *pSttXuiData);
	virtual void InitTestBtnsGroupChildren(CExBaseObject *pSttXuiData);
	virtual void InitBtnsGroupChildren(CExBaseObject *pSttXuiData);

public:
	virtual void InitUIOwn(CExBaseObject *pSttXuiData);
	virtual void InitUIChildren(CExBaseObject *pSttXuiData);

};

#endif//!QSTTWGTBUTTONGROUP_H
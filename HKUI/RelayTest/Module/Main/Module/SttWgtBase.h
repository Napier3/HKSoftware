#ifndef QSTTWGTBASE_H
#define QSTTWGTBASE_H

#include "../Ctrls/SttWgtStyle.h"
#include "../../../Module/BaseClass/ExBaseList.h"
#include <QWidget>
#include <QFont>

class QSttWgtBase
{
public:
	QSttWgtBase(QWidget* pParent = NULL);
	virtual ~QSttWgtBase();

public:
	QWidget* m_pParent;
	QSttWgtBase* m_pWgtRef;
	CExBaseObject* m_pXuiData;

public:
	virtual void InitUI(CExBaseObject *pSttXuiData);
	virtual void InitUIOwn(CExBaseObject *pSttXuiData);
	virtual void InitUIChildren(CExBaseObject *pSttXuiData);
	virtual QSttWgtBase* FindWgtBase(CExBaseObject *pXuiData);

	virtual QSttWgtStyle* GetWgtStyle(const CString& strStyleType, const CString& strStyleID);
	virtual void SetWgtStyle(QWidget* pWidget, QSttWgtStyle* pStyle);

};

extern QFont *g_pSttGlobalFont; 

#endif//!QSTTWGTBASE_H
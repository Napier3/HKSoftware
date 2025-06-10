#ifndef QSTTWGTFILEMNGRGRID_H
#define	QSTTWGTFILEMNGRGRID_H

#include <QTableWidget>
#include "../Module/SttWgtBase.h"

class QSttWgtFileMngrGrid : public QSttWgtBase, public QTableWidget
{
public:
	QSttWgtFileMngrGrid(QWidget* pParent = NULL);
	virtual ~QSttWgtFileMngrGrid();

public:
	virtual void InitUIOwn(CExBaseObject *pSttXuiData);
	void LoadFiles(const CString& strPath, const CString& strStyle);
	void InitUI();
	void Clear();
};

#endif//!QSTTWGTFILEMNGRGRID_H

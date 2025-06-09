#ifndef QSTTWGTFILEMNGRGRID_H
#define	QSTTWGTFILEMNGRGRID_H

#include <QTableWidget>
#include "../Module/SttWgtBase.h"
#include "../SttXuiData/SttXuiDataFileMngrGrid.h"
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
	void RefreshFiles();
protected:
	CSttXuiDataFileTypes* m_pFileTypes;//�ļ�����
};

#endif//!QSTTWGTFILEMNGRGRID_H

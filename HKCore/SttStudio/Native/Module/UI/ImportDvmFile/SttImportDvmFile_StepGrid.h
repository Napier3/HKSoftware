#ifndef SttImportDvmFile_StepGrid_H
#define SttImportDvmFile_StepGrid_H

#include "../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"

//通讯命令向导，该表格用于显示向导中的步骤
class CSttImportDvmFile_StepGrid : public QExBaseListGridBase
{
public:
	CSttImportDvmFile_StepGrid(QWidget* pparent);
	virtual ~CSttImportDvmFile_StepGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	void Update_ShowCurr(CExBaseObject *pData, BOOL bReset);

public:
	QExBaseListCheckBoxDelegate *m_pSelect;

};

#endif // SttImportDvmFile_StepGrid_H

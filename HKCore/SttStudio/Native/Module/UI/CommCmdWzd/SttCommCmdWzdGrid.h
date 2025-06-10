#ifndef SttCommCmdWzdGrid_H
#define SttCommCmdWzdGrid_H

#include "../Module/QExBaseListGridBase/QExBaseListGridBase.h"

//ͨѶ�����򵼣��ñ��������ʾ���еĲ���
class CSttCommCmdWzdGrid : public QExBaseListGridBase
{
public:
	CSttCommCmdWzdGrid(QWidget* pparent);
	virtual ~CSttCommCmdWzdGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual long GetDatasCount();
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	void Update_ShowCurr(CExBaseObject *pData, BOOL bReset);

public:

};

#endif // SttCommCmdWzdGrid_H

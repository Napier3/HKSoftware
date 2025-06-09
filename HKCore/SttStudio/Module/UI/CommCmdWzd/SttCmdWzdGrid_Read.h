#ifndef SttCmdWzdGrid_Read_H
#define SttCmdWzdGrid_Read_H

#include "../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"

class CSttCmdWzdGrid_Read : public QExBaseListGridBase
{
public:
	CSttCmdWzdGrid_Read(QWidget* pparent);
	virtual ~CSttCmdWzdGrid_Read();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

public:

protected:
	QExBaseListCheckBoxDelegate *m_pSelect;

};

#endif // SttCmdWzdGrid_Read_H

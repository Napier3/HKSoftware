#ifndef SttCmdWzdGrid_DsData_H
#define SttCmdWzdGrid_DsData_H

#include "../Module/QExBaseListGridBase/QExBaseListGridBase.h"

#define DSDATA_GRID_TYPE_SRC  0
#define DSDATA_GRID_TYPE_DES  1

//�ñ��������ʾ��writeָ����������ݼ�������
class CSttCmdWzdGrid_DsData : public QExBaseListGridBase
{
public:
	CSttCmdWzdGrid_DsData(QWidget* pparent);
	virtual ~CSttCmdWzdGrid_DsData();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

public:
	UINT m_nGridType; //����������SRC������DES��DES��ֵ�ɱ༭

};

#endif // SttCmdWzdGrid_Read_H

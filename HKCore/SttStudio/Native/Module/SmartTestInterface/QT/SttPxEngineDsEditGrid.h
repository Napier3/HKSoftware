#ifndef SttPxEngineDsEditGrid_H
#define SttPxEngineDsEditGrid_H

#include "../../UI/Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../Module/DataMngr/DvmDataset.h"
#include "../../../../Module/DataMngr/Value.h"

//�ñ��������ʾ��writeָ����������ݼ�������
class CSttPxEngineDsEditGrid : public QExBaseListGridBase
{
	Q_OBJECT
public:
	CSttPxEngineDsEditGrid(QWidget* pparent);
	virtual ~CSttPxEngineDsEditGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	static void EndEditCell_CmdDataValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_CmdDataValue_BOOL(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_CmdDataValue_Hex(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	CDvmValue* GetDataValue(CDvmData *pData);

	void UpdateChangeState();
// signals:
// 	void sig_PxEngine_UpdateData(CValue *pValue);
};



#endif // SttPxEngineGrid_Read_H

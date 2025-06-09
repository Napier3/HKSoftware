#ifndef IECCFGGOUTCHANNELSGRID_H
#define IECCFGGOUTCHANNELSGRID_H

#include "IecCfgChsGridBase.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgGoutCh.h"


#define IECCFGSMVGOUTCHANNELS_GRID_COLS		5


class CIecCfgGoutChannelsGrid : public CIecCfgChsGridBase
{
public:
	CIecCfgGoutChannelsGrid(QWidget* pparent);
	virtual ~CIecCfgGoutChannelsGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);
	void UpdateData_ByDataType(CIecCfgGoutCh *pIecCfgGoutCh,int nRow);
	void UpdateData_ByChMap(CIecCfgGoutCh *pGoutCh,int nRow);//ͨ��ӳ��ı��

public:
	//�༭������
	static void EndEditCell_GoutChSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_AppCh_GoutDefaultValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//zhouhj 20210912 ���ӶԲ�ͬ�������͵ĳ�ʼֵ���ж�

protected:
	QExBaseListComBoxDelegBase *m_pValue_DelegBase;
};

#endif // IECCFGGOUTCHANNELSGRID_H

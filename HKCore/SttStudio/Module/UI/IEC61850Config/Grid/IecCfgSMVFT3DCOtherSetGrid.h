#ifndef CIECCFGSMVFT3DCOTHERSETGRID_H
#define CIECCFGSMVFT3DCOTHERSETGRID_H

#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"

#define IECCFGSMVFT3DCOTHERSET_GRID_COLS	            	3
#define IECCFGPROTMEASCURRCODE_GRID_COLS	            	4

#define IECCFGSMV_DCFT3_DCVOL_GRID                          0 //ֱ����ѹ���
#define IECCFGSMV_DCFT3_DCCUR_GRID                          1 //ֱ���������
#define IECCFGSMV_DCFT3_ACVOL_GRID			                2//������ѹ���
#define IECCFGSMV_DCFT3_ACCUR_GRID	                     	3//�����������
#define IECCFGSMV_FT3_VOL_GRID				                4//��ѹ���
#define IECCFGSMV_FT3_CUR_GRID			                    5//�������
#define IECCFGSMV_FT3_CUR_PROT_MEAS_GRID			        6//�������(���ֱ�������������)


class CIecCfgSMVFT3DCOtherSetGrid : public QExBaseListGridBase
{
	Q_OBJECT
public:
	CIecCfgSMVFT3DCOtherSetGrid(QWidget* pparent, long nValueType);
	~CIecCfgSMVFT3DCOtherSetGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);

public:
	//�༭������
	BOOL m_bRunning;
	long m_nCodeValueGridType; //��¼��ǰ�ǵ�ѹ���/�������
	static void EndEditCell_CodeValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//������ֵ��Χ
	static void EndEditCell_PrimValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//����һ�ζֵ

public slots:
	virtual void slot_doubleClicked(int nRow,int nCol);
};

class CIecCfgProtMaesCurrCodeSetGrid : public CIecCfgSMVFT3DCOtherSetGrid
{
	Q_OBJECT
public:
	CIecCfgProtMaesCurrCodeSetGrid(QWidget* pparent);
	virtual ~CIecCfgProtMaesCurrCodeSetGrid();

	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

public slots:
	virtual	void slot_doubleClicked(int nRow,int nCol);
};

#endif//CIECCFGSMVFT3DCOTHERSETGRID_H

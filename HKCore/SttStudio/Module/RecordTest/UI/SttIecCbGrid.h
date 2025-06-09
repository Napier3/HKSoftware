#ifndef SttIecCbGrid_H
#define SttIecCbGrid_H

#include "../../UI/Module/QExBaseListGridBase/QExBaseListGridBase.h"


#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceBase.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceSmvCh.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceGooseCh.h"

//�����ʾ���ͷ�Ϊ����,��9-2,GOOSE�� FT3��������Ҫ��ʾ���в�ͬ
#define STT_IECCBGRID_SHOW_TYPE_61850                  0
#define STT_IECCBGRID_SHOW_TYPE_60044                  1





class CSttIecCbGrid : public QExBaseListGridBase
{
public:
	CSttIecCbGrid(QWidget* pparent);
	virtual ~CSttIecCbGrid();

	BOOL m_bViewSmv;
	BOOL m_bViewGoose;
	BOOL m_bViewFT3;
	CExBaseList *m_pAllSelCBs;  //����ѡ��Ŀ��ƿ�
	long m_nIecCbShowType;
public:
	virtual void InitGrid();
	virtual void InitGridTitle();
// 	void UpdateGridTitle();//dingxy 20240902 ���¿��ƿ��ͷ

	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

public:
	virtual void Show_Mac(CExBaseObject *pStData, const int& nRow, const int& nCol, BYTE *pMac);
	virtual void Show_61850Type(CExBaseObject *pStData, const int& nRow, const int& nCol, UINT nType);
	virtual void Show_Fiber(CExBaseObject *pStData, const int& nRow, const int& nCol, UINT nFiberIndex);
	virtual void UpdateDatas();
	void AddCapDevice(CExBaseObject *pCapDevice);
	void UpdateCapDevice(CExBaseObject *pCapDevice);//���±���е�ĳһ��
	void SelectRecordDevice(CExBaseObject *pStData, BOOL bSel);

	//��UpdateData�������ĵ������� shaolei 20220902
	//virtual BOOL UpdateData(CExBaseObject *pData);

	void UpdateCapDeviceLinkState();
	CExBaseObject* GetCurrSelData_BySelect();
	CExBaseList* GetAllSelectedCbs();
 	BOOL ValidSetSelectCbsState(CCapDeviceBase *pCapDeviceBase);

	static void EndEditCell_SelectCB(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

protected:
	void InitGridTitle_61850();
	void InitGridTitle_60044();

	void ShowData_61850(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void ShowData_60044(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
public slots:
	void slot_UpdateSelectCbsState();
};

void ShowColorRow(QExBaseListGridBase* pGridCtrl, int nMatchState, int nRow, int nCols);

#endif // SttIecCbGrid_H

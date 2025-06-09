#ifndef SCLCTRLSGRIDBASE_H
#define SCLCTRLSGRIDBASE_H

#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../Module/CommonCtrl_QT/QIecWidgetDelegate.h"
#include "../../../../61850/Module/SCL/SclIecCfgDatas.h"


class CSclCtrlsGridBase : public QExBaseListGridBase
{
	Q_OBJECT//zhouhj 20210715 Ҫʹ���źš��۱���Ҫ�Ӵ�
public:
	CSclCtrlsGridBase(QWidget* pparent);
	virtual ~CSclCtrlsGridBase();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual CDataType* FindDataType(const CString &strDataType);

	void UpdateSelectedState();
	//����3����Ƿ���¿��ƿ�ѡ����
	virtual void UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow,BOOL UpdateCtrlSelectGrid = FALSE);//���¶��ķ�������
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);

	void Attach_SelCtrlsRef(CExBaseList *pSelectedSclCtrlsRef)
	{
		m_pSelectedSclCtrlsRef = pSelectedSclCtrlsRef;
	}

	//2023/9/16 wjs ��Ӹ������ݺ���
	virtual void OnDataSelChanged(int nRow=-1, int nCol=-1);

public:
	//�༭������
	static void EndEditCell_CheckChanged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//zhouhj 20211027 ����ѡ�ı�

	//���ƿ鱻��ѡѡ�к���뵽��������
	CExBaseList *m_pSelectedSclCtrlsRef;

protected:
	QExBaseListComBoxDelegBase *m_pTypeSel_DelegBase;
	BOOL m_bRunning;

signals:
	void sig_UpdateSelectCtrlsGrid();

};

#endif // SCLCTRLSGRIDBASE_H

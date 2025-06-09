#ifndef CIECCFGGOUTCHSGRID_H
#define CIECCFGGOUTCHSGRID_H

#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgDataMngrGlobal.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGoutCh.h"

#define IECCFGGOUTCHSGRID_GRID_COLS		5


class QIecCfgGoutChsCheckBoxDelegate : public QExBaseListCheckBoxDelegate
{
public:
	QIecCfgGoutChsCheckBoxDelegate(QObject *parent=NULL);
	~QIecCfgGoutChsCheckBoxDelegate();

private:
	virtual void paint(QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index) const;
	virtual bool editorEvent(QEvent * event, QAbstractItemModel * model,
		const QStyleOptionViewItem & option, const QModelIndex & index);

	QPixmap m_oEmptyPixmap;
};

class CIecCfgGoutChsGrid : public QExBaseListGridBase
{
	Q_OBJECT
public:
	CIecCfgGoutChsGrid(QWidget* pparent);
	virtual ~CIecCfgGoutChsGrid();

	BOOL m_bIsUpdateParas;//�жϵ�ǰ�Ƿ��ڸ��²���;�������·����²�������ʱ,CtickCount�������DoEvents����,�����ظ����͸��²�������  20220816 zhouhj

public:
	void SetRunState(long nRunState);//���ñ��״̬,��Ϊ3��:1��ֹͣ���״̬(���޸��������͡�ͨ��ӳ��ֵ��);2��һ������״̬(��ʵʱ�޸�����ֵ);3���ݱ�״̬(�����ȫ���ɱ༭)
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual CDataType* FindDataType(const CString &strDataType);

	virtual void ShowCheck_BOOLEAN(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void ShowCheck_Dbpos(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc=NULL);

	void EnableInverseCol(BOOL bEnable);

	bool eventFilter(QObject *obj, QEvent *event);
//	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
public:
	//�༭������
	static void EndEditCell_GoutChSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_AppCh_GoutDefaultValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//zhouhj 20210912 ���ӶԲ�ͬ�������͵ĳ�ʼֵ���ж�

	void UpdateData_AllValues(long nCheckState);//���ݵ�ǰѡ��״̬,����ȫ��ֵ
protected:
	void UpdateData_ByDataType(CIecCfgGoutCh *pGoutCh,int nRow);
	void UpdateData_ByChMap(CIecCfgGoutCh *pGoutCh,int nRow);//ͨ��ӳ��ı��
	void UpdateData_Value(CIecCfgGoutCh *pGoutCh,int nRow);
	void UpdateData_Inverse(QGV_ITEM *pCell,int nRow);
	BOOL IsCheckedState_ChValue(const CString &strChValue);

private:
	QExBaseListComBoxDelegBase *m_pDataType_DelegBase;
	QExBaseListComBoxDelegBase *m_pMap_DelegBase;
	QExBaseListComBoxDelegBase *m_pValue_DelegBase;
	QExBaseListCheckBoxDelegate *m_pExBaseListCheckBoxDelegate;

signals:
//	void sig_Iec61850Cfg_Changed();//����61850���ø����ź�
	void sig_GoutValue_Changed();//����Goose����ֵ�����ź�
	void sig_GoutMap_Changed();//�������ڿ����������͸ı���߿���ӳ��ı�

 protected slots:
 	void slot_GridCellClicked(int row, int column);
};


#endif // CHMAPSGRID_H

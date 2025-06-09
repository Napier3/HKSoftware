#ifndef QGRADIENTGROUPGRID_H
#define QGRADIENTGROUPGRID_H

#include "../Module/QExBaseListGridBase/QExBaseListGridBase.h"

class QGradientGroupData : public CExBaseList
{
public:
//	CString m_strName;//zhouhj 2023.8.25 删除与基类重复
	float* m_pfAmp;
	float* m_pfAngle;
	float* m_pfFreq;

	float m_fDefaultAmp;
	float m_fDefaultAngle;
	float m_fDefaultFreq;

public:
	QGradientGroupData() { m_pfFreq = m_pfAngle = m_pfAmp = NULL; }
	virtual ~QGradientGroupData() {} //绑定值的地址,所以不需要析构
};

class QGradientGroupGrid : public QExBaseListGridBase
{
	Q_OBJECT
private:
	long m_moudleType;
	QMenu *m_MenuAmp;
	QMenu *m_MenuPhase;
	QMenu *m_MenuFre;

	QAction *m_ActUAmpED; 
	QAction *m_ActUZero;
	QAction *m_ActUEqualAmp;
	QAction *m_ActIAmp1; 
	QAction *m_ActIAmp5; 
	QAction *m_ActIAmp0; 
	QAction *m_ActIqualAmp;
	QAction *m_ActIAmpED;

	float m_fAmpMax;
	float m_fAmpMin;
	float m_fEDVal;

	BOOL m_bRunning;
	BOOL m_bDC;

public:
	QGradientGroupGrid(QWidget* pParent);
	virtual ~QGradientGroupGrid();

public:
	virtual void InitGrid(long nType);
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	void CreatTableMenu(long nType);

	long GetRow(long nCol, CString strName);
	long GetColumn(long nRow, CString strName);

	virtual void focusOutEvent(QFocusEvent *event);
	virtual void slot_GridShowMenu(QPoint pos);
	static void EndEditCell_Value_Float(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	CExBaseList *m_pChDatas;
	void SetDatas(CExBaseList *pList);//2023-10-30 suyang  有四个通道更新等幅值，相位
private:
    void Act_setUIAmpValue(QTableWidgetItem *pItem,float fVal,bool bAll=TRUE);
	void Act_setPrasePValue(int nSwitch,int nOffset,float fv);
	void Act_setPraseNValue(int nSwitch,int nOffset,float fv);
	void Act_setPraseZValue(int nStart,int nEnd);
	void Act_setHzEqualValue(int nStart,int nEnd,float fv);

protected slots:
	void slot_cellDoubleClicked(int nRow, int nCol);
	virtual void slot_CurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
	void slot_ActUAmpEDClicked();
	void slot_ActPerUAmpEDClicked();
	void slot_ActUZeroClicked();
	void slot_ActUEqualAmpClicked();

	void slot_ActIAmp1Clicked();
	void slot_ActIAmp5Clicked();
	void slot_ActIAmp0Clicked();
	void slot_ActIqualAmpClicked();
	void slot_ActIAmpEDClicked();
	void slot_ActPerIAmpEDClicked();

	void slot_ActPhasePClicked();
	void slot_ActPhaseNClicked();
	void slot_ActPhaseZClicked();
	void slot_ActHz50Clicked();
	void slot_ActHz60Clicked();
	void slot_ActHzEqualClicked();

protected slots:

	void slot_UpdataVamp(QString strValue);
	void slot_UpdataIamp(QString strValue);
	void slot_UpdataZX(QString strValue);//正序
	void slot_UpdataFX(QString strValue);//负序
	void slot_UpdataLX();//零序
	void slot_UpdataHzamp(QString strValue);

};
#endif
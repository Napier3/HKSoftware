#ifndef QSttIecSmvVectorMainWidget_H
#define QSttIecSmvVectorMainWidget_H

#include <QWidget>
#include <QToolButton>
#include <QMouseEvent>
#include <QBoxLayout>
#include <QToolButton>
#include <QFont>

#include "SttIecRcdFuncInterface.h"
#include "SttIecChsGridBase.h"

#include "SttIecSmvPolarWidget.h"

class CSttIecSmvVectorGroup : public CExBaseObject
{
public:
	CSttIecSmvVectorGroup();
	virtual ~CSttIecSmvVectorGroup();

	CDvmData *m_pVectorU, *m_pVectorI;

	long GetVectorCount();
	void InitVectors(POLAR_VECTORS_MNGR *pVectorsMngr);
};

//////////////////////////////////////////////////////////////////////////
class CSttIecSmvGrid_Vector : public CSttIecChsGridBase
{//矢量图显示表格
public:
	CSttIecSmvGrid_Vector(QWidget* parent);

	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE){};

	void ShowVector(CDvmData *pVector, long nRow, POLAR_VECTORS *pRetArrVector);
	void ShowVector_Empty();
	void ShowVector(CSttIecSmvVectorGroup *pVectorGroup, POLAR_VECTORS_MNGR *pRetArrVectors);

};

//////////////////////////////////////////////////////////////////////////
class QSttIecSmvVectorMainWidget : public QWidget, public CSttIecRcdFuncInterface
{//矢量图主窗口
public:
	explicit QSttIecSmvVectorMainWidget(QWidget *parent = 0);

public://CSttIecRcdFuncInterface
	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual BOOL NeedConfig(){return TRUE;}
	virtual void Release();

	virtual BOOL NeedNextAndPrev();
	virtual void NextPage();
	virtual void PrevPage();

private:
	void AddVector(CDvmData *pDvmVector);
	CDvmDataset* GetDvmDataset();
	void ShowCurrVector();
	void InitVectorsMngr();

	CSttIecSmvGrid_Vector *m_pGridVector;
	QSttIecSmvPolarWidget *m_pWndVector;
	QHBoxLayout *m_pLayout;

	CDvmDataset *m_pDvmDataset;
	CSttIecSmvVectorGroup *m_pCurrVector;
	long m_nCurrVectorIndex;
	CExBaseList m_listVector;

	POLAR_VECTORS_MNGR m_oVectorsMngr;
};

#endif // QSttIecSmvVectorMainWidget_H

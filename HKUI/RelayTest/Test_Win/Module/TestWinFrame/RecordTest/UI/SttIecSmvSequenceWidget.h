#ifndef QSttIecSmvSequenceMainWidget_H
#define QSttIecSmvSequenceMainWidget_H

#include <QWidget>
#include <QToolButton>
#include <QMouseEvent>
#include <QBoxLayout>
#include <QToolButton>
#include <QFont>

#include "SttIecRcdFuncInterface.h"
#include "SttIecChsGridBase.h"

#include "SttIecSmvPolarWidget.h"

//////////////////////////////////////////////////////////////////////////
class CSttIecSmvGrid_Sequence : public CSttIecChsGridBase
{//矢量图显示表格
public:
	CSttIecSmvGrid_Sequence(QWidget* parent);

	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE){};

	void ShowVector(CDvmData *pVector, POLAR_VECTORS *pRetArrVector);
};

//////////////////////////////////////////////////////////////////////////
class QSttIecSmvSequenceMainWidget : public QWidget, public CSttIecRcdFuncInterface
{//矢量图主窗口
public:
	explicit QSttIecSmvSequenceMainWidget(QWidget *parent = 0);

public://CSttIecRcdFuncInterface
	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual BOOL NeedConfig(){return TRUE;}
	virtual void Release();

	virtual BOOL NeedNextAndPrev();
	virtual void NextPage();
	virtual void PrevPage();

private:
//	void AddSequence(CDvmData *pDvmSequence);
	CDvmDataset* GetDvmDataset();
	void ShowCurrSequence();
	void InitSequencesMngr();

	CSttIecSmvGrid_Sequence *m_pGridSequence;
	QSttIecSmvPolarWidget *m_pWndVector;
	QHBoxLayout *m_pLayout;

	CDvmDataset *m_pDvmDataset;
	long m_nCurrSequenceIndex;
	CDvmData *m_pCurrVector;
	POLAR_VECTORS_MNGR m_oVectorsMngr;
};

#endif // QSttIecSmvSequenceMainWidget_H

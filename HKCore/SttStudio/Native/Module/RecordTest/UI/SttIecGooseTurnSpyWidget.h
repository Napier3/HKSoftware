#ifndef QSttIecGooseTurnSpyWidget_H
#define QSttIecGooseTurnSpyWidget_H

#include <QWidget>
#include "SttIecRcdFuncInterface.h"
#include "SttIecGsBinaryDraw.h"
#include "SttIecGsBinaryDrawView.h"
#include "../../../../Module/MemBuffer/TxRingPtrBuffer.h"

#define GOOSE_TURNSPY_MAX_DATAS_NUM                            2000

//////////////////////////////////////////////////////////////////////////
#ifdef QT_Wnd_USE_QWIDGET
class QSttIecGooseTurnSpyWidget :  public CWnd, public CSttIecRcdFuncInterface
#else
class QSttIecGooseTurnSpyWidget : public QWidget, public CWnd, public CSttIecRcdFuncInterface
#endif
{//矢量图绘图
public:
	QSttIecGooseTurnSpyWidget(QWidget* parent=0);
	virtual ~QSttIecGooseTurnSpyWidget();

	EPCAPPARSEDATAS m_oDatas;
	EPCAPPARSEDATAS m_oGsDatas[GOOSE_TURNSPY_MAX_DATAS_NUM];
	CSttIecGsBinaryDrawView m_oSttIecGsBinaryDrawView;

	bool m_bIsDrawing;

public://CXWndInterface
	//重载函数OnWndMsg，实现消息处理
	virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);
	virtual void OnWndTimer(unsigned int nIDEvent) ;

public://CSttIecRcdFuncInterface
	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual void Release();
	virtual BOOL NeedAddToSubPub(){return TRUE;}

public:
	virtual void paintEvent(QPaintEvent *event);
	virtual void resizeEvent(QResizeEvent *);

	BOOL DrawTurnSpy();

protected:
//	CTxRingPtrBuffer<EPCAPPARSEDATAS> m_oGsCapRingDatas;
};

#endif


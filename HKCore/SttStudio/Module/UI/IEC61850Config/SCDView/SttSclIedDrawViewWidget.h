#ifndef STTSCLVIEWWIDGET_H  
#define STTSCLVIEWWIDGET_H

#include "../../Module/CommonCtrl_QT/Draw/QSttCustomArrowLine.h"
#include "../../Module/CommonCtrl_QT/Draw/QSttCustomRect.h"
#include "../../../../../61850/Module/SCL/SclIecCfgDatas.h"
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QColor>
#include <QPair>
#include <QMap>
#include "SttSclIedLineDialog.h"


class QSttSclIedDrawViewWidget : public QWidget
{
	Q_OBJECT
public:
	QSttSclIedDrawViewWidget(QWidget *parent=NULL);
 	virtual ~QSttSclIedDrawViewWidget();

	void InitUI();
	void InitConnect();
	void InitData(CSclIed *pSclIed);
	void IedDataInfo(CSclIed *pSclIed);
	void Release();
	void ReleaseList();
    void OutPutDataPairs(CSclIed *pSclIed,const QList<QPair<CString, CString> >& dataPairs, QList<QSttCustomRect*>& blockRects, int& height);
	void CompareSmv(QPair<CString, CString>& dataPairs);
	void CompareGoose(QPair<CString, CString>& dataPairs);
	CString FindSclIedName(CString search);
	void SMVSubendInfo(CSclChSmvIn* pChSmvIn ,CString strID ,CString strName,CString strAppID);
	void GooseSubendInfo(CSclChGsIn* pChGsIn,CString strID ,CString strName,CString strAppID);
	void SMVSubInputInfos(CSclChSmvOut* pChSmvOut ,CString strID ,CString strAppID,long nIndex);
	void GsSubInputInfos(CSclChGsOut* pChGsOut,CString strID ,CString strAppID,long nIndex);

	QCustomGraphicsView * m_pGraphicsView;
	QGraphicsScene* m_pGraphicsScene;
    QList<CString> m_strNameList;

public slots:
	void slot_Subend();

protected:
	virtual void resizeEvent ( QResizeEvent * );
	virtual void mousePressEvent(QMouseEvent* event);

private:
	QSttCustomRect* m_pCustomRect;//中间大的矩形
	
	//控制块矩形
	QList<QSttCustomRect*>m_pSmvInBlockRect;
	QList<QSttCustomRect*>m_pGooseInBlockRect;
	QList<QSttCustomRect*>m_pSmvOutBlockRect;
	QList<QSttCustomRect*>m_pGooseoutBlockRect;

	//箭头
	QList<QSttCustomArrowLine*>m_pArrowLine;
	QList<QSttCustomArrowLine*>m_pReceiveArrowLine;

	//输入矩形
	QList<QSttCustomRect*>m_pInputLeftRect;
	QList<QSttCustomRect*>m_pInputRightRect;
	QList<QSttCustomRect*>m_pReceiveRect;
	QList<QSttCustomRect*>m_pInputRect;
	QList<QSttCustomRect*>m_pInputBlockRect;
	QList<QSttCustomRect*>m_pReceiveBlockRect;
	QList<QSttCustomRect*>m_pReceiveInputRect;

    QList<QPair <CString, CString> > m_strAppIdGsOut;
    QList<QPair <CString, CString> > m_strAppIdGsIn;
    QList<QPair <CString, CString> > m_strAppIdSmvOut;
    QList<QPair <CString, CString> > m_strAppIdSmvIn;
    QList<QPair <CString, CString> > m_strRecvAppIdIedGs;
    QList<QPair <CString, CString> > m_strRecvAppIdIedSmv;
    QList<QPair <CString, CString> > m_strRecvAppIdGs;
    QList<QPair <CString, CString> > m_strRecvAppIdSmv;

	int m_nHeightLeft ;
	int m_nHeightRight;

    QMap<CString, QList<CSclVirtualSubend> > m_SmvSubList;
    QMap<CString, QList<CSclVirtualSubend> > m_GsSubList;
	//20240106chenling SMV、Goose虚端子窗口的所有输入端
	QMap<CString, QList<CSclVirtualSubend> > m_SmvInputLists;
	QMap<CString, QList<CSclVirtualSubend> > m_GsInputLists;

};



#endif

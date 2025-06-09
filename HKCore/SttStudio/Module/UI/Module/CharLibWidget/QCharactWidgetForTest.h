#ifndef QCHARACTWIDGETFORTEST_H
#define QCHARACTWIDGETFORTEST_H

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QAction>
#include <QMenu>
#include "../../../../../AutoTest/Module/Characteristic/CharacteristicLib.h"
#include "PsuCharDrawView.h"

class QCharactWidgetForTest : public QWidget
{
    Q_OBJECT

public:
    explicit QCharactWidgetForTest(QWidget *parent = 0,  BOOL bUseMouseMoveChar=FALSE);
    ~QCharactWidgetForTest();

public:
	void InitCharacteristic(const CString &strMacroID);
	void SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle);
	void UpdateCurrTestPoint(const CString &strCharaID,const CString &strIndex,
		double dX,double dY);//���²��Ե�,����1:�������LN/LL/ALL ����2:����ID��ӦI/II/III��
	void AddTestResultPoint(CExBaseList* pValue);//��Ӳ��Խ����
	void ClearSearchPoints();
	void ClearSearchPoint(long nPtIndex);
	void ClearSearchPointsFrom(long nPtIndex);
	BOOL IsViewTestLines();

    CCharacteristics *m_pCharacteristics;
    CPsuCharDrawView *m_pCharacterDrawView;

	CString m_strXAxis, m_strYAxis , m_strTitle;	//���ݷ�ʱ�ޱ��� 20211013 sf

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void wheelEvent(QWheelEvent *);
	virtual void paintEvent(QPaintEvent *event);
	virtual void resizeEvent(QResizeEvent *);
private:
	void initPlot();	
	BOOL UpdateDrawCharacters();
	void UpdateCharDesc(const CString &strMacroID, const CString &strCharID);
	BOOL m_bUseMouseMoveChar;
	 CCharacteristic *m_pCurrCharacteristic;
	 CString m_strCurrMacroID;
	 BOOL m_bCharHasChanged;//��ǵ�ǰ�������Ѹı�,��Ҫˢ����������

signals:
	 void sig_UpdateCurrTestPoint(QString strCharaID,QString strIndex,double dX,double dY);

public slots:
	void slot_UpdateCurrTestPoint(QString strCharaID,QString strIndex,double dX,double dY);
	void slot_UpdateDrawCharacters();	//20210915
};

#endif // QCHARACTWIDGETFORTEST_H

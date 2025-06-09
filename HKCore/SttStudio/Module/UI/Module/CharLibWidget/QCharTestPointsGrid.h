#ifndef QCHARTESTPOINTSGRID_H
#define QCHARTESTPOINTSGRID_H

#include <QObject>
#include "../../../../../AutoTest/Module/Characteristic/Characteristics.h"
#include "../../../../../AutoTest/Module/Characteristic/Characteristic.h"
#include "../QExBaseListGridBase/QExBaseListGridBase.h"

#define CHARTESTPOINTS_GRID_COLS	  	6

class QCharTestPointsGrid : public QExBaseListGridBase
{
	Q_OBJECT

public:
	QCharTestPointsGrid(CCharacteristics *pCharacteristics,QWidget *parent);
	virtual ~QCharTestPointsGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void ShowCharacteristic(CCharacteristic *pCharacteristic);

	void InitMacroID(const CString &strMacroID);
	void UpdateCurrTestPoint(const CString &strCharaID,const CString &strIndex,
		double dX,double dY);//���²��Ե�,����1:�������LN/LL/ALL ����2:����ID��ӦI/II/III��
	void AddTestResultPoint(double dX,double dY,BOOL bHasAct,double dX_set,double dY_set);//��Ӳ��Խ����
	void ClearSearchPoints();
	void ClearSearchPoint(long nPtIndex);
	void ClearSearchPointsFrom(long nPtIndex);
	void UpdateResult(CExBaseObject *pData,double dX,double dY,BOOL bHasAct);
	BOOL IsDiffHarmTest();

	CString m_strTestPointDescX;
	CString m_strTestPointDescY;

private:
	CExBaseList m_oTestPointsList;
//	CExBaseList m_oTestLinesList;
	CString m_strCurrMacroID;
	 CCharacteristic *m_pCurrCharacteristic;
	 CCharacteristics *m_pCharacteristics;

public:

signals:
	void sig_UpdateCurrTestPoint(QString strCharaID,QString strIndex,double dX,double dY);

public slots:
	void slot_UpdateCurrTestPoint(QString strCharaID,QString strIndex,double dX,double dY);
};

#endif // QCHARTESTPOINTSGRID_H

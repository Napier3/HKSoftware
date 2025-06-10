#ifndef QLINEVOLGRADIENTGROUPWIDGET_H
#define QLINEVOLGRADIENTGROUPWIDGET_H
#include "../Gradient/GradientGroupGrid.h"
#include "../../SttTest/Common/tmt_gradient_test.h"
#include "../../SttCmd/SttChMaps.h"
#include "../Gradient/GradientGroupWidget.h"
#include "../../SttTest/Common/LineVolt/tmt_linevolt_gradient_test.h"

class QLineVolGradientGroupWidget:public QWidget
{
	Q_OBJECT
public:
	QLineVolGradientGroupWidget(QWidget* pParent = NULL);
	virtual ~QLineVolGradientGroupWidget();

	void InitLineVolChMaps();
	void InitLineVolGrid(tmt_LineVolGradientParasEx* pGradientParas);
	void InitLineVolGridData(tmt_LineVolGradientParasEx* pGradientParas);
	void Update();
	void UpdateFaultEditState(CDataTypeValue *pCurDataTypeValue);
	void SetEnabledUI(BOOL bEnable);

private:
	CSttChMaps m_oLineVolChMaps;

	QGradientGroupGrid* m_pVoltGrid;
	QGradientGroupGrid* m_pCurGrid;
	QGradientGroupGrid* m_pFaultVoltGrid;
	QGradientGroupGrid* m_pFaultCurGrid;

	CExBaseList m_oNormalVoltList;
	CExBaseList m_oNormalCurList;
	CExBaseList m_oFaultVoltList;
	CExBaseList m_oFaultCurList;

	tmt_LineVolGradientParasEx* m_pParas;
	void InitUI();
	long GetFaultSymIndex(CString strName);
	void UpdateFaultEditState(CString strName);
	void ClearFaultEditState();
	void ClearFaultEditState(QGradientGroupGrid* pGrid);
	void HideFreqCol();



};
extern QFont *g_pSttGlobalFont;
#endif
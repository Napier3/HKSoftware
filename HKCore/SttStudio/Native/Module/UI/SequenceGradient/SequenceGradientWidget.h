#ifndef QSEQUENCEGRADIENTWIDGET_H
#define QSEQUENCEGRADIENTWIDGET_H
#include "../../SttTest/Common/Sequence/tmt_sequence_gradient_test.h"
#include "../Gradient/GradientGroupGrid.h"
#include "../SttTestCntrFrameBase.h"
#include <QWidget>
#include "../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../Module/API/StringApi.h"

class QSequenceGradientWidget : public QWidget
{
	Q_OBJECT

public:
	QGradientGroupGrid* m_pVoltGrid;//电压表头
	QGradientGroupGrid* m_pCurGrid;//电流表头

	QGradientGroupGrid* m_pFaultVoltGrid;//故障的电压表头
	QGradientGroupGrid* m_pFaultCurGrid;//故障电流表头

	CExBaseList m_oNormalVoltList;
	CExBaseList m_oNormalCurList;
	CExBaseList m_oFaultVoltList;
	CExBaseList m_oFaultCurList;

	tmt_GradientParasEx* m_pParas;
//	CDataType m_oSequenceGradientChs;
	tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];

public:
	QSequenceGradientWidget(QWidget* pParent = NULL);
	virtual ~QSequenceGradientWidget();
	void SetEnabledUI(BOOL bEnable);

private:
	void InitUI();//初始化正常态和故障态的ui界面
	long GetFaultSymIndex(CString strName);
	void UpdateFaultEditState(CString strName);
	void ClearFaultEditState();//设置故障态表格中所有状态以及背景颜色
	void ClearFaultEditState(QGradientGroupGrid* pGrid);

public:
	void Init(tmt_GradientParasEx* pGradientParas);//初始化界面以及初始化值
	void InitData(tmt_GradientParasEx* pGradientParas);
	void Update();//展示更新后链表的数据
	void UpdateFaultEditState(CDataTypeValue *pCurDataTypeValue);//更新相位的值以及背景色
	void HideFreCol();//隐藏表格频率一列
};

extern QFont *g_pSttGlobalFont;
#endif
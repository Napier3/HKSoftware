#ifndef QGRADIENTGROUPWIDGET_H
#define QGRADIENTGROUPWIDGET_H
#include "GradientGroupGrid.h"
#include "../../SttTest/Common/tmt_gradient_test.h"

class QGradientGroupWidget : public QWidget
{
	Q_OBJECT
private:
	QGradientGroupGrid* m_pVoltGrid;
	QGradientGroupGrid* m_pCurGrid;

	QGradientGroupGrid* m_pFaultVoltGrid;
	QGradientGroupGrid* m_pFaultCurGrid;

	CExBaseList m_oNormalVoltList;
	CExBaseList m_oNormalCurList;
	CExBaseList m_oFaultVoltList;
	CExBaseList m_oFaultCurList;

	tmt_GradientParasEx* m_pParas;

public:
	QGradientGroupWidget(QWidget* pParent = NULL);
	virtual ~QGradientGroupWidget();

	void SetEnabledUI(BOOL bEnable);

private:
	void InitUI();
	void UpdateFaultEditState(CString strName,int GradientcbbVar = 1);//wangtao 20240621 增加缺省参数，区分第一第二变量
	void ClearFaultEditState();
	void ClearFaultEditState(QGradientGroupGrid* pGrid);

public:
	long GetFaultSymIndex(CString strName);
	void Init(tmt_GradientParasEx* pGradientParas);
	void InitData(tmt_GradientParasEx* pGradientParas);//dingxy 20240520 抽出初始化数据以便于调用
	void Update();
	void UpdateFaultEditState(CDataTypeValue *pCurDataTypeValue,CDataTypeValue *pCurDataTypeValue2);
	void SetDefaultFaultValue(long nIndex, bool bVolt = true);
};

extern CFont *g_pSttGlobalFont;
#endif
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
	QGradientGroupGrid* m_pVoltGrid;//��ѹ��ͷ
	QGradientGroupGrid* m_pCurGrid;//������ͷ

	QGradientGroupGrid* m_pFaultVoltGrid;//���ϵĵ�ѹ��ͷ
	QGradientGroupGrid* m_pFaultCurGrid;//���ϵ�����ͷ

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
	void InitUI();//��ʼ������̬�͹���̬��ui����
	long GetFaultSymIndex(CString strName);
	void UpdateFaultEditState(CString strName);
	void ClearFaultEditState();//���ù���̬���������״̬�Լ�������ɫ
	void ClearFaultEditState(QGradientGroupGrid* pGrid);

public:
	void Init(tmt_GradientParasEx* pGradientParas);//��ʼ�������Լ���ʼ��ֵ
	void InitData(tmt_GradientParasEx* pGradientParas);
	void Update();//չʾ���º����������
	void UpdateFaultEditState(CDataTypeValue *pCurDataTypeValue);//������λ��ֵ�Լ�����ɫ
	void HideFreCol();//���ر��Ƶ��һ��
};

extern QFont *g_pSttGlobalFont;
#endif
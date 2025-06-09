#include "CharactEditWidget_Eng.h"

QCharactEditWidget_Eng::QCharactEditWidget_Eng(CCharacteristics *pCharacteristics,QWidget *parent, bool bUseOptrButtons, BOOL bUseMouseMoveChar, BOOL bChangePlot) :
QImpCharactWidget(pCharacteristics, parent, bUseOptrButtons, bUseMouseMoveChar)
{
    m_bChangePlot = bChangePlot;
}

QCharactEditWidget_Eng::~QCharactEditWidget_Eng(void)
{
}
void QCharactEditWidget_Eng::SetChangePlot(BOOL bChangePlot)
{
	m_bChangePlot = bChangePlot;
}
void QCharactEditWidget_Eng::initPlot()
{
	if (m_bChangePlot)
	{
		CAxisInterface *pAxisInterface = NULL;
		m_pCharacterDrawView->GetAxisInterface(&pAxisInterface);

		if (pAxisInterface != NULL)
		{
			CDataGroup oAxisConfig;
			oAxisConfig.AddNewData(AXIS_CONFIG_ID_WorkAreaBkColor,(long)RGB(255, 255, 255));
			oAxisConfig.AddNewData(AXIS_CONFIG_ID_XAxisGridLineColor,(long)RGB(0, 0, 0));
			oAxisConfig.AddNewData(AXIS_CONFIG_ID_YAxisGridLineColor,(long)RGB(0, 0, 0));
			oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisCenterLineWidth,(long)1);
			oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisCenterColor,(long)RGB(0, 0, 0));
			oAxisConfig.AddNewData(AXIS_CONFIG_ID_XAxisWorkAreaBackColorFrom,(long)RGB(255, 255, 255));
			oAxisConfig.AddNewData(AXIS_CONFIG_ID_YAxisWorkAreaBackColorFrom,(long)RGB(255, 255, 255));
			oAxisConfig.AddNewData(AXIS_CONFIG_ID_XAxisWorkAreaBackColorTo,(long)RGB(255, 255, 255));
			oAxisConfig.AddNewData(AXIS_CONFIG_ID_YAxisWorkAreaBackColorTo,(long)RGB(255, 255, 255));
			oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisScaleFont,(long)12);
			oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisNameFont,(long)14);
			oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisTopGap,(long)26);
			pAxisInterface->SetAxisConfig(&oAxisConfig);

			m_pCharacterDrawView->InitDrawLineColor(RGB(0, 190, 255));  //20240806 zhangyq 曲线编辑中曲线的颜色设置
		}
	}
	else
	{
		QImpCharactWidget::initPlot();
	}
	
}

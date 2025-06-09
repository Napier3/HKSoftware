#include "QParaSetBase.h"
#include "../../../SttTestSysGlobalPara.h"
#include "QBasicTestParaSet.h"

QParaSetBase::QParaSetBase(QWidget *parent)
	: QWidget(parent)
{	
	m_pArrUIVOL = NULL;
	m_pArrUICUR = NULL;
	m_pParaSetSttTestResource = NULL;
	m_MacroType = 0;
	m_type = P_Common;
}

QParaSetBase::~QParaSetBase()
{
	Release();
}

void QParaSetBase::initUI(CSttTestResourceBase *pSttTestResource)
{
	Release();

	if (pSttTestResource != NULL)
	{
		m_pParaSetSttTestResource = pSttTestResource;
	}
}

void QParaSetBase::setPropertyOfParaSet(plugin_type type,CSttTestResourceBase *pSttTestResource,
				tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR,bool bDC)
{
	ASSERT(pSttTestResource);
	ASSERT( pArrUIVOL != NULL);
	ASSERT( pArrUICUR != NULL);

	m_type = type;
	m_pArrUIVOL = pArrUIVOL;
	m_pArrUICUR = pArrUICUR;
	m_pParaSetSttTestResource = pSttTestResource;
	m_bDC = bDC;

	initUI(pSttTestResource);
	initData();
}

void QParaSetBase::setData(tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR)
{
	ASSERT( pArrUIVOL != NULL);
	ASSERT( pArrUICUR != NULL);

	m_pArrUIVOL = pArrUIVOL;
	m_pArrUICUR = pArrUICUR;
}

void QParaSetBase::setMaxMinAndEDVal()
{
	setUAmpMaxMinValue();
	setIAmpMaxMinValue();

	setUAmpEDValue(g_oSystemParas.m_fVNom);
	setIAmpEDValue(g_oSystemParas.m_fINom);
}

void QParaSetBase::setUAmpEDValue(float fUEDVal){}
void QParaSetBase::setIAmpEDValue(float fIEDVal){}
void QParaSetBase::setChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC){}//valueFalg: 0:幅值 1：相位 2：频率

void QParaSetBase::startInit(bool bEnable)
{
	setDisabled(!bEnable);
}

void QParaSetBase::stopInit(bool bEnable)
{
	setDisabled(!bEnable);
}

void QParaSetBase::slot_ChannelValueChanged(MOUDLEType moudleType,int channelNum,int valueFlag,float datavalue)
{
	QBasicTestParaSet *pBasicTestParaSet = (QBasicTestParaSet*)parent(); 
	pBasicTestParaSet->Send_UpdataParas();
}

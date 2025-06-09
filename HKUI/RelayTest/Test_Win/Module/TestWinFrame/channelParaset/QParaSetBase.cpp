#include "QParaSetBase.h"
#include <QDebug>

QParaSetBase::QParaSetBase(QWidget *parent)
	: QWidget(parent)
{	
	m_pArrUIVOL = NULL;
	m_pArrUICUR = NULL;
	m_pSttTestResource = NULL;
	m_MacroType = 0;
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
		m_pSttTestResource = pSttTestResource;
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
	m_pSttTestResource = pSttTestResource;
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

void QParaSetBase::startInit(bool bEnable)
{
	setDisabled(!bEnable);
}

void QParaSetBase::stopInit(bool bEnable)
{
	setDisabled(!bEnable);
}

void QParaSetBase::slot_ChannelValueChanged(MOUDLEType moudleType,/*int moudleID,*/int channelNum,int valueFlag,float datavalue)
{
	emit sig_updataParas();
}
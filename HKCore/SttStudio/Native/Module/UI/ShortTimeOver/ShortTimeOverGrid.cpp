#include "ShortTimeOverGrid.h"

QShortTimeOverGrid::QShortTimeOverGrid(QWidget *parent)
: QSttInfWidgetBase(parent)
{
	m_pnHarmIndex = NULL;
	m_pParaSetImp = NULL;
	m_pParaSetSttTestResource = NULL;

	m_pArrUIVOL = NULL;
	m_pArrUICUR = NULL;
	m_bDC = false;

	m_MacroType = -1;
	m_fIEDVal = -1;
	m_fIEDVal = -1;
	m_ndc_type = -1;
}

QShortTimeOverGrid::~QShortTimeOverGrid()
{
	delete m_pParaSetImp;
}

void QShortTimeOverGrid::DCStateChanged(int type,bool bdc)
{
	m_ndc_type = type;
	m_bDC = bdc;

	if (m_pParaSetImp != NULL)
	{
		DCStateChanged();
	}
}

void QShortTimeOverGrid::DCStateChanged()
{
	if (m_ndc_type == -1)
	{
		return;
	}

	m_pParaSetImp->DCStateChanged(m_ndc_type, m_bDC);
}

void QShortTimeOverGrid::setUAmpMaxMinValue()
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->setUAmpMaxMinValue();
	}
}

void QShortTimeOverGrid::setIAmpMaxMinValue()
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->setIAmpMaxMinValue();
	}
}

void QShortTimeOverGrid::setUAmpEDValue(float fUEDVal)
{
	m_fUEDVal = fUEDVal;

	if (m_pParaSetImp != NULL)
	{
		setUAmpEDValue();
	}
}

void QShortTimeOverGrid::setIAmpEDValue(float fIEDVal)
{
	m_fIEDVal = fIEDVal;

	if (m_pParaSetImp != NULL)
	{
		setIAmpEDValue();
	}
}

void QShortTimeOverGrid::setUAmpEDValue()
{
	if (m_fUEDVal < 0.0001)
	{//已经初始化过，则设置，临时中介变量
		return;
	}

	m_pParaSetImp->setUAmpEDValue(m_fUEDVal);
}

void QShortTimeOverGrid::setIAmpEDValue()
{
	if (m_fIEDVal < 0.0001)
	{//已经初始化过，则设置，临时中介变量
		return;
	}

	m_pParaSetImp->setIAmpEDValue(m_fIEDVal);
}

//递变槽
void QShortTimeOverGrid::setChannelTableItemValue_Sequence(QString str,float fstep,int valueFlag,int AddOrMinus)
{
	m_strChannelTableItemValue = str;
	m_fChannelTableItemValue_Step = fstep;
	m_nChannelTableItemValue_ValueFlag = valueFlag;
	m_nChannelTableItemValue_AndOrMinus = AddOrMinus;

	if (m_pParaSetImp != NULL)
	{
		setChannelTableItemValue_Sequence();
	}
}

void QShortTimeOverGrid::setChannelTableItemValue_Sequence()
{
	if (m_strChannelTableItemValue.size() == 0)
	{//已经初始化过，则设置，临时中介变量
		return;
	}
	m_pParaSetImp->setChannelTableItemValue_Sequence(m_strChannelTableItemValue
		, m_fChannelTableItemValue_Step
		, m_nChannelTableItemValue_ValueFlag
		, m_nChannelTableItemValue_AndOrMinus);
}

//递变槽
void QShortTimeOverGrid::setChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC)
{
	m_strChannelTableItemValue = str;
	m_fChannelTableItemValue_Step = fstep;
	m_nChannelTableItemValue_ValueFlag = valueFlag;
	m_nChannelTableItemValue_AndOrMinus = AddOrMinus;
	m_bDC = bDC;

	if (m_pParaSetImp != NULL)
	{
		setChannelTableItemValue();
	}
}
void QShortTimeOverGrid::setChannelTableItemValue()
{
	if (m_strChannelTableItemValue.size() == 0)
	{//已经初始化过，则设置，临时中介变量
		return;
	}

	m_pParaSetImp->setChannelTableItemValue(m_strChannelTableItemValue
		, m_fChannelTableItemValue_Step
		, m_nChannelTableItemValue_ValueFlag
		, m_nChannelTableItemValue_AndOrMinus
		, m_bDC);
}

void QShortTimeOverGrid::initUI(CSttTestResourceBase *pSttTestResource)
{
	m_pParaSetSttTestResource = pSttTestResource;

	if (m_pParaSetImp != NULL)
	{
		initUI();
	}
}

void QShortTimeOverGrid::initUI()
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->initUI(m_pParaSetSttTestResource);
	}
}

void QShortTimeOverGrid::initData()
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->initData();
	}
}

void QShortTimeOverGrid::Release()
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->Release();
	}
}

void QShortTimeOverGrid::UpdateTables()
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->UpdateTables();
	}
}

void QShortTimeOverGrid::UpdateValidTableDatas()
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->UpdateValidTableDatas();
	}
}

void QShortTimeOverGrid::setHarmIndex(int *pnHarmIndex)
{
	m_pnHarmIndex = pnHarmIndex;

	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->setHarmIndex(pnHarmIndex);
	}
}

void QShortTimeOverGrid::setPropertyOfParaSet(plugin_type type,CSttTestResourceBase *pSttTestResource
											 ,tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR,bool bDC)
{
	m_type = type;
	m_pParaSetSttTestResource = pSttTestResource;
	m_pArrUIVOL = pArrUIVOL;
	m_pArrUICUR = pArrUICUR;
	m_bDC = bDC;

	if (m_pParaSetImp != NULL)
	{
		setPropertyOfParaSet();
	}
}

void QShortTimeOverGrid::setPropertyOfParaSet()
{
	m_pParaSetImp->setPropertyOfParaSet(m_type, m_pParaSetSttTestResource, m_pArrUIVOL, m_pArrUICUR, m_bDC);
}

void QShortTimeOverGrid::setData(tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR)
{
	m_pArrUIVOL = pArrUIVOL;
	m_pArrUICUR = pArrUICUR;

	if (m_pParaSetImp != NULL)
	{
		setData();
	}
}

void QShortTimeOverGrid::setData()
{
	if (m_pArrUIVOL != NULL)
	{//已经初始化过，则设置，临时中介变量
		m_pParaSetImp->setData(m_pArrUIVOL, m_pArrUICUR);
	}
}

void QShortTimeOverGrid::setMacroType(int type)
{ 
	m_MacroType = type;

	if (m_pParaSetImp != NULL)
	{
		setMacroType();
	}
}


void QShortTimeOverGrid::setMacroType()
{ 
	if (m_MacroType != -1)
	{//已经初始化过，则设置，临时中介变量
		m_pParaSetImp->setMacroType(m_MacroType);
	}
}

void QShortTimeOverGrid::SetBasicTestParaSetImp(QShortTimeOverGridImp* pParaSetImp)
{
	m_pParaSetImp = pParaSetImp;
}

void QShortTimeOverGrid::setMaxMinAndEDVal()
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->setMaxMinAndEDVal();
	}
}

void QShortTimeOverGrid::startInit(bool bEnable)
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->startInit(bEnable);
	}
}

void QShortTimeOverGrid::stopInit(bool bEnable)
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->stopInit(bEnable);
	}
}

void QShortTimeOverGrid::showEvent(QShowEvent *)
{
	if (m_pParaSetImp != NULL)
	{
		return;
	}

	m_pParaSetImp = new QShortTimeOverGridImp(this);
	setMacroType();

	if (m_pnHarmIndex!= NULL)//2023.7.29 zhouhj  谐波界面设置谐波次数
	{
		m_pParaSetImp->setHarmIndex(m_pnHarmIndex);
	}

	InitSttInfWidget(m_pParaSetImp);

	initUI();

	setPropertyOfParaSet();//20230313 zhouhj 改为先初始化界面,再设置最大最小值
	setMaxMinAndEDVal();

	initData();
	DCStateChanged();
}

void QShortTimeOverGrid::Send_UpdataParas()
{
	emit sig_updataParas();
}
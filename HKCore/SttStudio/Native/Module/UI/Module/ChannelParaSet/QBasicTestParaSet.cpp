#include "QBasicTestParaSet.h"

QBasicTestParaSet::QBasicTestParaSet(QWidget *parent)
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
	m_nParaSetSecondValue = 1;
	m_fHistoryUMax = 0;
	m_fHistoryIMax = 0;
}

QBasicTestParaSet::~QBasicTestParaSet()
{
	delete m_pParaSetImp;
}

void QBasicTestParaSet::DCStateChanged(int type,bool bdc)
{
	m_ndc_type = type;
	m_bDC = bdc;

	if (m_pParaSetImp != NULL)
	{
		DCStateChanged();
	}
}

void QBasicTestParaSet::SetParaSetSecondValue(int nParaSetSecondValue)
{
	m_nParaSetSecondValue = nParaSetSecondValue;
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->SetParaSetSecondValue(m_nParaSetSecondValue);
	}
}

void QBasicTestParaSet::DCStateChanged()
{
	if (m_ndc_type == -1)
	{
		return;
	}

	m_pParaSetImp->DCStateChanged(m_ndc_type, m_bDC);
}

void QBasicTestParaSet::setUAmpMaxMinValue(bool bCanUpdateTable)
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->setUAmpMaxMinValue(bCanUpdateTable);
	}
}

void QBasicTestParaSet::setIAmpMaxMinValue(bool bCanUpdateTable)
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->setIAmpMaxMinValue(bCanUpdateTable);
	}
}

void QBasicTestParaSet::setUAmpEDValue(float fUEDVal)
{
	m_fUEDVal = fUEDVal;

	if (m_pParaSetImp != NULL)
	{
		setUAmpEDValue();
	}
}

void QBasicTestParaSet::setIAmpEDValue(float fIEDVal)
{
	m_fIEDVal = fIEDVal;

	if (m_pParaSetImp != NULL)
	{
		setIAmpEDValue();
	}
}

void QBasicTestParaSet::setUAmpEDValue()
{
	if (m_fUEDVal < 0.0001)
	{//已经初始化过，则设置，临时中介变量
		return;
	}

	m_pParaSetImp->setUAmpEDValue(m_fUEDVal);
}

void QBasicTestParaSet::setIAmpEDValue()
{
	if (m_fIEDVal < 0.0001)
	{//已经初始化过，则设置，临时中介变量
		return;
	}

	m_pParaSetImp->setIAmpEDValue(m_fIEDVal);
}

//递变槽
void QBasicTestParaSet::setChannelTableItemValue_Sequence(QString str,float fstep,int valueFlag,int AddOrMinus)
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

void QBasicTestParaSet::setChannelTableItemValue_Sequence()
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
void QBasicTestParaSet::setChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC)
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
void QBasicTestParaSet::setChannelTableItemValue()
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

void QBasicTestParaSet::initUI(CSttTestResourceBase *pSttTestResource)
{
	m_pParaSetSttTestResource = pSttTestResource;

	if (m_pParaSetImp != NULL)
	{
		initUI();
	}
}

void QBasicTestParaSet::initUI()
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->initUI(m_pParaSetSttTestResource);
	}
}

void QBasicTestParaSet::initData(bool bCanUpdateTable)
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->initData(bCanUpdateTable);
	}
}

void QBasicTestParaSet::Release()
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->Release();
	}
}

void QBasicTestParaSet::UpdateTables()
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->UpdateTables();
	}
}

void QBasicTestParaSet::UpdateValidTableDatas()
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->UpdateValidTableDatas();
	}
}

void QBasicTestParaSet::setHarmIndex(int *pnHarmIndex)
{
	m_pnHarmIndex = pnHarmIndex;

	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->setHarmIndex(pnHarmIndex);
	}
}

void QBasicTestParaSet::setPropertyOfParaSet(plugin_type type,CSttTestResourceBase *pSttTestResource
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

void QBasicTestParaSet::setPropertyOfParaSet()
{
	m_pParaSetImp->setPropertyOfParaSet(m_type, m_pParaSetSttTestResource, m_pArrUIVOL, m_pArrUICUR, m_bDC);
}

void QBasicTestParaSet::setData(tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR)
{
	m_pArrUIVOL = pArrUIVOL;
	m_pArrUICUR = pArrUICUR;

	if (m_pParaSetImp != NULL)
	{
		setData();
	}
}

void QBasicTestParaSet::setData()
{
	if (m_pArrUIVOL != NULL)
	{//已经初始化过，则设置，临时中介变量
		m_pParaSetImp->setData(m_pArrUIVOL, m_pArrUICUR);
	}
}

void QBasicTestParaSet::setMacroType(int type)
{ 
	m_MacroType = type;

	if (m_pParaSetImp != NULL)
	{
		setMacroType();
	}
}


void QBasicTestParaSet::setMacroType()
{ 
	if (m_MacroType != -1)
	{//已经初始化过，则设置，临时中介变量
		m_pParaSetImp->setMacroType(m_MacroType);
	}
}

void QBasicTestParaSet::SetBasicTestParaSetImp(QBasicTestParaSetImp* pParaSetImp)
{
	m_pParaSetImp = pParaSetImp;
}

void QBasicTestParaSet::setMaxMinAndEDVal(bool bCanUpdateTable)
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->setMaxMinAndEDVal(bCanUpdateTable);
	}
}

void QBasicTestParaSet::startInit(bool bEnable)
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->startInit(bEnable);
	}
}

void QBasicTestParaSet::stopInit(bool bEnable)
{
	if (m_pParaSetImp != NULL)
	{
		m_pParaSetImp->stopInit(bEnable);
	}
}

void QBasicTestParaSet::showEvent(QShowEvent *)
{
	if (m_pParaSetImp != NULL)
	{
		return;
	}

	m_pParaSetImp = new QBasicTestParaSetImp(this);
	setMacroType();

	if (m_pnHarmIndex!= NULL)//2023.7.29 zhouhj  谐波界面设置谐波次数
	{
		m_pParaSetImp->setHarmIndex(m_pnHarmIndex);
	}

	InitSttInfWidget(m_pParaSetImp);

	//initUI();  	//2024-9-15 lijunqing 优化程序启动速度  在setPropertyOfParaSet中会调用，因此注释掉此行，避免重复多次调用

	setPropertyOfParaSet();//20230313 zhouhj 改为先初始化界面,再设置最大最小值
	setMaxMinAndEDVal(false);

	m_pParaSetImp->SetParaSetSecondValue(m_nParaSetSecondValue);
	initData(true);
	DCStateChanged();
}

void QBasicTestParaSet::Send_UpdataParas()
{
	emit sig_updataParas();
}

void QBasicTestParaSet::GetUIMaxMinValue(double& dUMin,double& dUMax,double& dIMin,double& dIMax,bool bStart)
{
	int i=0;
	float fValue = 0.0f;
	float fUMin = dUMin;
	float fUMax = dUMax;
	float fIMin = dIMin;
	float fIMax = dIMax;

	for (i=0;i<MAX_VOLTAGE_COUNT;i++)
	{
		if (!m_pArrUIVOL)
		{
			break;
		}

		fValue = m_pArrUIVOL[i].Harm[1].fAmp;
		if (fValue > fUMax)
		{
			fUMax = fValue;
			if (bStart)
			{
				if (fUMax > m_fHistoryUMax)
				{
					m_fHistoryUMax = fUMax;
				}
				else
				{
					fUMax = m_fHistoryUMax;
				}
			}
		}

		if(fValue < fUMin)
		{
			fUMin = fValue;
		}
	}

	for (i=0;i<MAX_CURRENT_COUNT;i++)
	{
		if (!m_pArrUICUR)
		{
			break;
		}

		fValue = m_pArrUICUR[i].Harm[1].fAmp;
		if (fValue > fIMax)
		{
			fIMax = fValue;
		}
		if (bStart)
		{
			if (fIMax > m_fHistoryUMax)
			{
				m_fHistoryIMax = fIMax;
			}
			else
			{
				fIMax = m_fHistoryIMax;
			}
		}

		if(fValue < fIMin)
		{
			fIMin = fValue;
		}
	}

	dUMin = (double)fUMin;
	dUMax = (double)fUMax;
	dIMin = (double)fIMin;
	dIMax = (double)fIMax;
}
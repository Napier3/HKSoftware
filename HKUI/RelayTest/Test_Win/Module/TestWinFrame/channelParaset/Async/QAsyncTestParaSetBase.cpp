#include "QAsyncTestParaSetBase.h"

QAsyncTestParaSetBase::QAsyncTestParaSetBase(tmt_async_modules *pModules,QWidget *parent )
{
	m_pAsyncModules = pModules;
	m_bDc = false;

// 	initData();
// 	initUI();
}

QAsyncTestParaSetBase::~QAsyncTestParaSetBase(void)
{

}


void QAsyncTestParaSetBase::UpdateModulesData( tmt_async_modules *pModules )
{
	if(!pModules)
	{
		return;
	}
	m_pAsyncModules = pModules;

	UpdateTableData();
}

void QAsyncTestParaSetBase::setData( tmt_async_modules *pModules )
{
	if(!pModules)
	{
		return;
	}
	m_pAsyncModules = pModules;
}

// void QAsyncTestParaSetBase::UpdateTableData()
// {
// 	
// }

void QAsyncTestParaSetBase::DCStateChanged( bool bDc )
{
	m_bDc = bDc;
}

void QAsyncTestParaSetBase::setChannelTableItemValue( QAsyncChannelTable *pTable,CString strChName,float fstep,int valueFlag,int AddOrMinus,bool bDC )
{
	tmt_async_channel *pCh = pTable->GetChFromName(strChName);
	if(!pCh)
	{
		return;
	}

	float fv;
	int nChIndex = pTable->getRowIndexByChName(strChName);
	int nType = -1;

	switch (valueFlag)
	{
	case 0:
		nType = ASYNCTABLE_AMP;
		break;
	case 1:
		nType = ASYNCTABLE_ANGLE;
		break;
	case 2:
		nType = ASYNCTABLE_FREQ;
		break;
	}

	switch (valueFlag)
	{					
	case amplitude_type:	
		{
			fv = pTable->getItemValue(nChIndex,nType);
			fv = fv+fstep*AddOrMinus;
			if (!bDC)
			{
				if (fv<=0)
				{
					fv = 0;
				}
			}
			pTable->setItemValue(nChIndex,nType,fv);
		}
		break;
	case phasor_type:
		{
			fv =pTable->getItemValue(nChIndex,nType);
			fv = fv+fstep*AddOrMinus;
			pTable->setItemValue(nChIndex,nType,fv);
		}
		break;
	case fre_type:
		{
			fv =pTable->getItemValue(nChIndex,nType);
			fv = fv+fstep*AddOrMinus;
			if (fv<0)
			{
				fv = 0;
			}
			pTable->setItemValue(nChIndex,nType,fv);
		}
		break;
	default:
		break;
	}
}


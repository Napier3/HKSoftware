#include "stdafx.h"
#include "SttWgtFactory.h"

#include "../SttXuiData/SttXuiDataMainConfig.h"
#include "../Ctrls/SttWgtButton.h"
#include "../Ctrls/SttWgtButtonGroup.h"
#include "../Ctrls/SttWgtFileMngrGrid.h"
#include "../Ctrls/SttWgtTabCtrl.h"
#include "../Ctrls/SttWgtText.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif 

QSttWgtFactory* g_pSttWgtFactory = NULL;
long g_nSttWgtFactoryRef = 0;

QSttWgtFactory::QSttWgtFactory()
{
	
}

QSttWgtFactory::~QSttWgtFactory()
{

}

QSttWgtFactory *QSttWgtFactory::Create()
{
	g_nSttWgtFactoryRef++;

	if (g_nSttWgtFactoryRef == 1)
	{
		g_pSttWgtFactory = new QSttWgtFactory;
	}

	return g_pSttWgtFactory;
}

QSttWgtBase* QSttWgtFactory::CreateSttWgt(CSttXuiDataBase *pSttXuiData, QWidget* pParent)
{
	QSttWgtBase *pWgtBase = NULL;

	if (pSttXuiData->GetClassID() == MNGRCLASSID_CSTTXUIDATATABS)
	{
		pWgtBase = new QSttWgtTabCtrl(pParent);
	}
	else if (pSttXuiData->GetClassID() == MNGRCLASSID_CSTTXUIDATATAB)
	{
		pWgtBase = new QSttWgtTab(pParent);
	}
	else if (pSttXuiData->GetClassID() == MNGRCLASSID_CSTTXUIDATATEXT)
	{
		pWgtBase = new QSttWgtText(pParent);
	}
	else if (pSttXuiData->GetClassID() == MNGRCLASSID_CSTTXUIDATATESTBTNSGROUP
		|| pSttXuiData->GetClassID() == MNGRCLASSID_CSTTXUIDATABTNSGROUP)
	{
		pWgtBase = new QSttWgtButtonGroup(pParent);
	}
	else if (pSttXuiData->GetClassID() == MNGRCLASSID_CSTTXUIDATABUTTON)
	{
		pWgtBase = new QSttWgtButton(pParent);
	}
	else if (pSttXuiData->GetClassID() == MNGRCLASSID_CSTTXUIDATAFILEMNGRGRID)
	{
		pWgtBase = new QSttWgtFileMngrGrid(pParent);
	}

	if(pWgtBase)
	{
		pWgtBase->m_pWgtRef = pWgtBase;
		pWgtBase->m_pXuiData = pSttXuiData;
		pWgtBase->InitUI(pSttXuiData);
	}

	return pWgtBase;
}

void QSttWgtFactory::Release()
{
	g_nSttWgtFactoryRef--;

	if (g_nSttWgtFactoryRef == 0)
	{
		delete g_pSttWgtFactory;
		g_pSttWgtFactory = NULL;
	}
}

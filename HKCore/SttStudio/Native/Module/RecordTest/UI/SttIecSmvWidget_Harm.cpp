#include "SttIecSmvWidget_Harm.h"
#include "SttIecSmvGrid_Harm_Content.h"
#include "SttIecSmvWidget_Harm_Histogram.h"
#include "SttIecSmvGrid_Harm.h"

CSttIecSmvWidget_Harm::CSttIecSmvWidget_Harm(QWidget *parent):QWidget(parent)
{
	m_pIecRcdFuncWidget = this;
	m_pSttIecRcdFuncInterface = NULL;
}

CSttIecSmvWidget_Harm::~CSttIecSmvWidget_Harm()
{

}

void CSttIecSmvWidget_Harm::Release()
{
	delete this;
}


void CSttIecSmvWidget_Harm::HarmFunc_Create(int index)
{
	if (m_pSttIecRcdFuncInterface != NULL)
	{
		m_pSttIecRcdFuncInterface->Release();
		m_pSttIecRcdFuncInterface = NULL;
	}

 	if (index == IECRCD_FUNC_Smv_Harm_ValidValue)
 	{
 		CSttIecSmvGrid_Harm *pGrid = new CSttIecSmvGrid_Harm(this);
 		pGrid->setFont(*g_pSttGlobalFont);

 		pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
 		pGrid->InitGrid();
 		m_pSttIecRcdFuncInterface = pGrid;
 	}
 	else if (index == IECRCD_FUNC_Smv_Harm_Content)
 	{
 		CSttIecSmvGrid_Harm_Content *pGrid= new CSttIecSmvGrid_Harm_Content(this);
 		pGrid->setFont(*g_pSttGlobalFont);
 		pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
 		pGrid->InitGridTitle();
 		m_pSttIecRcdFuncInterface = pGrid;
 	}
 	else if (index == IECRCD_FUNC_Smv_Harm_Histogram)
 	{
 		CSttIecSmvWidget_Harm_Histogram *pHistogram= new CSttIecSmvWidget_Harm_Histogram(this);
 		m_pSttIecRcdFuncInterface = pHistogram;
 	}
}



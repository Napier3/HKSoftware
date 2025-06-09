#include "SttWgtButton.h"
#include "SttWgtButtonGroup.h"
#include "../Module/SttWgtFactory.h"

QSttWgtButtonGroup::QSttWgtButtonGroup(QWidget* pParent)
{
	m_pParent = pParent;
	setParent(pParent);
}

QSttWgtButtonGroup::~QSttWgtButtonGroup()
{

}

void QSttWgtButtonGroup::InitTestBtnsGroup(CExBaseObject *pSttXuiData)
{
	CSttXuiDataTestBtnsGroup* pData = (CSttXuiDataTestBtnsGroup*)pSttXuiData;
	setObjectName(pData->m_strID);
	setGeometry(pData->m_nX*g_dUIShowCoef, pData->m_nY*g_dUIShowCoef, pData->m_nCx*g_dUIShowCoef, pData->m_nCy*g_dUIShowCoef);
	QSttWgtStyle* pStyle = GetWgtStyle(WGT_TYPE_FONT, pData->m_strFont);
	SetWgtStyle(this, pStyle);
}

void QSttWgtButtonGroup::InitBtnsGroup(CExBaseObject *pSttXuiData)
{
	CSttXuiDataBtnsGroup* pData = (CSttXuiDataBtnsGroup*)pSttXuiData;
	setObjectName(pData->m_strID);
	setGeometry(pData->m_nX*g_dUIShowCoef, pData->m_nY*g_dUIShowCoef, pData->m_nCx*g_dUIShowCoef, pData->m_nCy*g_dUIShowCoef);
	QSttWgtStyle* pStyle = GetWgtStyle(WGT_TYPE_FONT, pData->m_strFont);
	SetWgtStyle(this, pStyle);
}

void QSttWgtButtonGroup::InitUIOwn(CExBaseObject *pSttXuiData)
{
	if(pSttXuiData)
	{
		CSttXuiDataBase* pData = (CSttXuiDataBase*)pSttXuiData;
		if(pData->GetClassID() == MNGRCLASSID_CSTTXUIDATATESTBTNSGROUP)
		{
			InitTestBtnsGroup(pSttXuiData);
		}
		else
		{
			InitBtnsGroup(pSttXuiData);
		}
	}
}

void QSttWgtButtonGroup::InitTestBtnsGroupChildren(CExBaseObject *pSttXuiData)
{
	CSttXuiDataTestBtnsGroup* pData = (CSttXuiDataTestBtnsGroup*)pSttXuiData;
	long nInset = pData->m_nInset*g_dUIShowCoef;
	long nX = 0;
	long nCy = pData->m_nCy;
	POS pos = pData->GetHeadPosition();
	while (pos)
	{
		CSttXuiDataBase* pNode = (CSttXuiDataBase*)pData->GetNext(pos);
		QSttWgtButton* pWgt = (QSttWgtButton*)QSttWgtFactory::CreateSttWgt(pNode, this);
		pWgt->CalcGeometry(nX, nCy, nInset);
	}
}

void QSttWgtButtonGroup::InitBtnsGroupChildren(CExBaseObject *pSttXuiData)
{
	CSttXuiDataBtnsGroup* pData = (CSttXuiDataBtnsGroup*)pSttXuiData;
	long nInset = pData->m_nInset*g_dUIShowCoef;
	long nX = 0;
	long nCy = pData->m_nCy*g_dUIShowCoef;
	POS pos = pData->GetHeadPosition();
	while (pos)
	{
		CSttXuiDataBase* pNode = (CSttXuiDataBase*)pData->GetNext(pos);
		QSttWgtButton* pWgt = (QSttWgtButton*)QSttWgtFactory::CreateSttWgt(pNode, this);
		pWgt->CalcGeometry(nX, nCy, nInset);
	}
}

void QSttWgtButtonGroup::InitUIChildren(CExBaseObject *pSttXuiData)
{
	if(pSttXuiData)
	{
		CSttXuiDataBase* pData = (CSttXuiDataBase*)pSttXuiData;
		if(pData->GetClassID() == MNGRCLASSID_CSTTXUIDATATESTBTNSGROUP)
		{
			InitTestBtnsGroupChildren(pSttXuiData);
		}
		else
		{
			InitBtnsGroupChildren(pSttXuiData);
		}
	}
}
#include "OscillogramGroupWidget.h"
#include"CString_QT.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include"../../Module/XLangResource_Native.h"


OscillogramGroupWidget::OscillogramGroupWidget(QWidget *parent ):QWidget(parent)
{
	m_pTabWidget = NULL;
	m_pGridLayout = NULL;
	m_nRealGroupCnt = 0;
	m_nGroupIndexI = 0;
	m_nGroupIndexV = 0;
	m_nVolCurIndex = 0;
	m_nVolCurFlag = 0;
	m_pSttTestResource = NULL;
	for(int i = 0; i < TAB_CNT; i++)
	{
		m_pOscillogramWidget[i] = NULL;
		m_nVolChCnt[i] = 0;
		m_nCurChCnt[i] = 0;
	}
}
OscillogramGroupWidget::~OscillogramGroupWidget()
{

}

void OscillogramGroupWidget::Clear()
{
	if(m_pTabWidget)
	{
		delete m_pTabWidget;
		m_pTabWidget = NULL;
	}
	if(m_pGridLayout)
	{
		delete m_pGridLayout;
		m_pGridLayout = NULL;
	}
	return;
	for(int i = 0; i < m_nRealGroupCnt; i++)
	{
		if(m_pOscillogramWidget[i])
		{
			//m_pOscillogramWidget[i]->close();
			delete m_pOscillogramWidget[i];
			m_pOscillogramWidget[i] = NULL;
		}
	}
}

int OscillogramGroupWidget::GetGroupIndexFromChIndex(int nChIndex)
{
	int nRealVChCnt = 0;
	//CSttTestResourceBase * pSttTestResource;
	if(m_nVolCurFlag == 1)//表示电压
	{
		nRealVChCnt = m_pSttTestResource->m_oVolChRsListRef.GetCount();
		if(nRealVChCnt <= 4)
		{
			return 0;
		}
		else 
		{
			return nChIndex/3;
		}
	}
	else if(m_nVolCurFlag ==2)
	{
		nRealVChCnt = m_pSttTestResource->m_oCurChRsListRef.GetCount();
		if(nRealVChCnt <= 4)
		{
			return 0;
		}
		else 
		{
			return nChIndex/3;
		}
	}

	return 0;
}
void OscillogramGroupWidget::initUI(CSttTestResourceBase *pSttTestResource)
{
	m_pSttTestResource = pSttTestResource;
	m_pTabWidget = new QTabWidget;
	m_pTabWidget->setFont(*g_pSttGlobalFont);
	m_pGridLayout = new QGridLayout;
	pSttTestResource->GetCurrVolGroupNum(m_nGroupIndexI,m_nGroupIndexV);
	m_nRealGroupCnt = pSttTestResource->m_oListGroups.GetCount();
	int nVolChCnt = 0;
	int nCurChCnt = 0;
	for(int nGroupIndex = 0; nGroupIndex < m_nRealGroupCnt; nGroupIndex++)
	{
		m_pOscillogramWidget[nGroupIndex] = new QOscillogramWidget(this);
		m_pOscillogramWidget[nGroupIndex]->m_nGroupIndex = nGroupIndex;
		m_pOscillogramWidget[nGroupIndex]->setSttTestResource(pSttTestResource);
		m_pOscillogramWidget[nGroupIndex]->getSttChGroupResource_Vol();
		m_pOscillogramWidget[nGroupIndex]->getSttChGroupResource_Cur();

		if(nGroupIndex >= 1)
		{
			nVolChCnt += m_pOscillogramWidget[nGroupIndex-1]->getSttChGroupResource_Vol_ChCnt();
			nCurChCnt += m_pOscillogramWidget[nGroupIndex-1]->getSttChGroupResource_Cur_ChCnt();
		}

		m_nVolChCnt[nGroupIndex] = m_pOscillogramWidget[nGroupIndex]->getSttChGroupResource_Vol_ChCnt();
		m_nCurChCnt[nGroupIndex] = m_pOscillogramWidget[nGroupIndex]->getSttChGroupResource_Cur_ChCnt();
		m_pOscillogramWidget[nGroupIndex]->setArrUIVOL(m_pArrUIVOL + nVolChCnt);
		m_pOscillogramWidget[nGroupIndex]->setArrUICUR(m_pArrUICUR + nCurChCnt);
		//m_pOscillogramWidget[nGroupIndex]->InitArrUIValue(); //dingxy 20240411 每次读取上一次模板值，不需要初始化
		m_pOscillogramWidget[nGroupIndex]->InitArrUIContent();//仅初始化基波含有率
		m_pOscillogramWidget[nGroupIndex]->updateWidget();
		m_pOscillogramWidget[nGroupIndex]->selectDataChanged();

		//QString str = QString::fromLocal8Bit("第%1组");
		CString strTmp;
		xlang_GetLangStrByFile(strTmp, "Native_Group");
		//m_pTabWidget->addTab(m_pOscillogramWidget[nGroupIndex],str.arg(nGroupIndex+1));
		m_pTabWidget->addTab(m_pOscillogramWidget[nGroupIndex], QString("%1").arg(nGroupIndex+1)+ strTmp );

	}
	m_pGridLayout->addWidget(m_pTabWidget);
	this->setLayout(m_pGridLayout);
	//setArrUIAdress();
}

void OscillogramGroupWidget::slot_ValueChanged(int nVolCurIndex, int nVolCurFlag)
{
	m_nVolCurIndex = nVolCurIndex;
	m_nVolCurFlag = nVolCurFlag;
}

void OscillogramGroupWidget::setArrUIVOL(tmt_channel *pArrUIVOL)
{
	m_pArrUIVOL = pArrUIVOL;
}

void OscillogramGroupWidget::setArrUICUR(tmt_channel *pArrUICUR)
{
	m_pArrUICUR = pArrUICUR;
}

void OscillogramGroupWidget::slot_ChnIndexChanged(int nIndex)
{
	m_nGroupIndex = GetGroupIndexFromChIndex(m_nVolCurIndex);
	if(m_nVolCurFlag == 1)//表示电压
	{
		if(m_nGroupIndex >=1)
		{	
			//2024-8-14 wuxinyi 偏移位置错误导致修改UC2时会导致Ua2和Ub2相位变为0；
			//m_pOscillogramWidget[m_nGroupIndex]->setArrUIVOL(m_pArrUIVOL + m_nVolCurIndex);
			int nGroupHeadIndex = 3 * m_nGroupIndex;
			m_pOscillogramWidget[m_nGroupIndex]->setArrUIVOL(m_pArrUIVOL + nGroupHeadIndex);
		}
		else
		{
			m_pOscillogramWidget[m_nGroupIndex]->setArrUIVOL(m_pArrUIVOL);
		}
		m_pOscillogramWidget[m_nGroupIndex]->selectDataChanged();
	}
	else if(m_nVolCurFlag == 2)//表示电流
	{
		if(m_nGroupIndex >= 1)
		{
			//m_pOscillogramWidget[m_nGroupIndex]->setArrUICUR(m_pArrUICUR + m_nVolCurIndex);
			int nGroupHeadIndex = 3 * m_nGroupIndex;
			m_pOscillogramWidget[m_nGroupIndex]->setArrUICUR(m_pArrUICUR + nGroupHeadIndex);
		}
		else
		{
			m_pOscillogramWidget[m_nGroupIndex]->setArrUICUR(m_pArrUICUR);
		}
		//m_pOscillogramWidget[0]->setArrUIVOL(m_pArrUIVOL);
		m_pOscillogramWidget[m_nGroupIndex]->selectDataChanged();
	}
}
void OscillogramGroupWidget::slot_updateOscillogramGroup()
{
	for(int i = 0;i < m_nRealGroupCnt; i++)
	{
		m_pOscillogramWidget[i]->selectDataChanged();
	}
}
void OscillogramGroupWidget::slot_SetToZero()
{
	//setArrUIAdress();
	POS pos = m_pSttTestResource->m_oListGroups.GetHeadPosition();
	CSttChGroupResource *pObj = NULL;
	int nIndexV = 0;
	int nIndexI = 0;

	while(pos)
	{
		pObj = (CSttChGroupResource *)m_pSttTestResource->m_oListGroups.GetNext(pos);
		if(pObj->HasVolCh())
		{
			POS postemp = pObj->GetHeadPosition();
			CSttChResource *pChResource = NULL;
			long nChIndex = 0;
			m_pOscillogramWidget[nIndexV]->HarmSetZero();
			m_pOscillogramWidget[nIndexV]->selectDataChanged();
			nIndexV++;
		}
		if(pObj->HasCurCh())
		{
			POS postemp = pObj->GetHeadPosition();
			CSttChResource *pChResource = NULL;
			long nChIndex = 0;
			m_pOscillogramWidget[nIndexI]->HarmSetZero();
			m_pOscillogramWidget[nIndexI]->selectDataChanged();
			nIndexI++;
		}
	}
}

void OscillogramGroupWidget::setArrUIAdress()
{
	CSttChGroupResource *pObj = NULL;
	POS pos = m_pSttTestResource->m_oListGroups.GetHeadPosition();
	int nIndexV = 0;
	int nIndexI = 0;

	while(pos)
	{
		pObj = (CSttChGroupResource *)m_pSttTestResource->m_oListGroups.GetNext(pos);
		if(pObj->HasVolCh())
		{
			POS postemp = pObj->GetHeadPosition();
			CSttChResource *pChResource = NULL;
			long nChIndex = 0;
			while(postemp)
			{
				pChResource = (CSttChResource *)pObj->GetNext(postemp);
				nChIndex = pChResource->GetChIndex_FromZero();
			}

			m_pOscillogramWidget[nIndexV]->setArrUIVOL(&m_pArrUIVOL[nChIndex]);
			m_pOscillogramWidget[nIndexV]->HarmSetZero();
			m_pOscillogramWidget[nIndexV]->selectDataChanged();

			nIndexV++;
		}
		if(pObj->HasCurCh())
		{
			POS postemp = pObj->GetHeadPosition();
			CSttChResource *pChResource = NULL;
			long nChIndex = 0;
			while(postemp)
			{
				pChResource = (CSttChResource *)pObj->GetNext(postemp);
				nChIndex = pChResource->GetChIndex_FromZero();
			}

			m_pOscillogramWidget[nIndexI]->setArrUIVOL(&m_pArrUIVOL[nChIndex]);
			m_pOscillogramWidget[nIndexI]->HarmSetZero();
			m_pOscillogramWidget[nIndexI]->selectDataChanged();

			nIndexI++;
		}
	}
}

void OscillogramGroupWidget::setValue()
{
	m_nGroupIndex = GetGroupIndexFromChIndex(m_nVolCurIndex);
	if(m_nVolCurFlag == 1)
	{
		m_pOscillogramWidget[m_nGroupIndex]->selectDataChanged();
	}
	else if(m_nVolCurFlag == 2)
	{
		m_pOscillogramWidget[m_nGroupIndex]->selectDataChanged();
	}
}void OscillogramGroupWidget::UpdateUI(CSttTestResourceBase *pSttTestResource)
{
	QTabWidget *temp = new QTabWidget; 
	temp->setFont(*g_pSttGlobalFont);
	QGridLayout * pGL = new QGridLayout;
	pSttTestResource->GetCurrVolGroupNum(m_nGroupIndexI,m_nGroupIndexV);
	m_nRealGroupCnt = pSttTestResource->m_oListGroups.GetCount();
	int nVolChCnt = 0;
	int nCurChCnt = 0;
	for(int nGroupIndex = 0; nGroupIndex < m_nRealGroupCnt; nGroupIndex++)
	{
		m_pOscillogramWidget[nGroupIndex] = new QOscillogramWidget(this);
		m_pOscillogramWidget[nGroupIndex]->m_nGroupIndex = nGroupIndex;
		m_pOscillogramWidget[nGroupIndex]->setSttTestResource(pSttTestResource);
		m_pOscillogramWidget[nGroupIndex]->getSttChGroupResource_Vol();
		m_pOscillogramWidget[nGroupIndex]->getSttChGroupResource_Cur();

		if(nGroupIndex >= 1)
		{
			nVolChCnt += m_pOscillogramWidget[nGroupIndex-1]->getSttChGroupResource_Vol_ChCnt();
			nCurChCnt += m_pOscillogramWidget[nGroupIndex-1]->getSttChGroupResource_Cur_ChCnt();
		}

		m_nVolChCnt[nGroupIndex] = m_pOscillogramWidget[nGroupIndex]->getSttChGroupResource_Vol_ChCnt();
		m_nCurChCnt[nGroupIndex] = m_pOscillogramWidget[nGroupIndex]->getSttChGroupResource_Cur_ChCnt();
		m_pOscillogramWidget[nGroupIndex]->setArrUIVOL(m_pArrUIVOL + nVolChCnt);
		m_pOscillogramWidget[nGroupIndex]->setArrUICUR(m_pArrUICUR + nCurChCnt);
		m_pOscillogramWidget[nGroupIndex]->InitArrUIValue();
		m_pOscillogramWidget[nGroupIndex]->updateWidget();
		m_pOscillogramWidget[nGroupIndex]->selectDataChanged();

		//QString str = QString::fromLocal8Bit("第%1组");
		xlang_GetLangStrByFile(g_sLangTxt_Manual_FirGroup,"Manual_FirGroup");//LCQ
		temp->addTab(m_pOscillogramWidget[nGroupIndex],g_sLangTxt_Manual_FirGroup.arg(nGroupIndex+1));

	}
	pGL->addWidget(temp);
	this->setLayout(pGL);
	this->show();
}
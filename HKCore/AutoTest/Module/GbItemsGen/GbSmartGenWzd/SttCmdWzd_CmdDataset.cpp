#include "SttCmdWzd_CmdDataset.h"
#include "GbSmartGenWzd.h"

CSttCmdWzd_CmdDataset::CSttCmdWzd_CmdDataset(void)
{
	m_pCmdGrpRef = NULL;

	m_nSelect = 1;
	m_nChange = 1;
	m_nPeriod = 1;
	m_nQuqlity = 1;
	m_nPeriod_Time = 10000;
}

CSttCmdWzd_CmdDataset::~CSttCmdWzd_CmdDataset(void)
{
	m_pCmdGrpRef = NULL;
}

///////////////////////////////////////////////////////////////
CSttCmdWzd_Step::CSttCmdWzd_Step(void)
{
	m_pCmdGrpRef = NULL;
	m_pCmdGrpBk = NULL;
	m_nZoneIndex = -1;
}

CSttCmdWzd_Step::~CSttCmdWzd_Step(void)
{
	m_pCmdGrpRef = NULL;

	if (m_pCmdGrpBk != NULL)
	{
		delete m_pCmdGrpBk;
		m_pCmdGrpBk = NULL;
	}
}

void CSttCmdWzd_Step::RecoverCmdGrpRef()
{
	if (m_pCmdGrpRef == NULL || m_pCmdGrpBk == NULL)
	{
		return;
	}

	if (m_pCmdGrpRef->m_strDataType != COMMCMD_RWOPTR_WRITE)
	{
		return;
	}

	CDataGroup *pCmdDatasRef = (CDataGroup *)m_pCmdGrpRef->GetHead();
	CDataGroup *pCmdDatasBk = (CDataGroup *)m_pCmdGrpBk->GetHead();

	POS pos = pCmdDatasBk->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pCmdDataBk = (CDvmData *)pCmdDatasBk->GetNext(pos);
		CDvmData *pCmdDataRef = (CDvmData *)pCmdDatasRef->FindByID(pCmdDataBk->m_strID);

		if (pCmdDataRef != NULL)
		{
			pCmdDataBk->m_strValue = pCmdDataRef->m_strValue;
		}
	}

	pCmdDatasRef->DeleteAll();
	pCmdDatasRef->AppendCloneEx(*pCmdDatasBk, TRUE);
}
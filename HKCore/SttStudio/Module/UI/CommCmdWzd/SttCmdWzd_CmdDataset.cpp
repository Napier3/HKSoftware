#include "SttCmdWzd_CmdDataset.h"

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
CSttCmdWzd_CmdDatasets::CSttCmdWzd_CmdDatasets(void)
{
	m_pCmdGrpRef = NULL;
	m_nZoneIndex = -1;
}

CSttCmdWzd_CmdDatasets::~CSttCmdWzd_CmdDatasets(void)
{
	m_pCmdGrpRef = NULL;
}

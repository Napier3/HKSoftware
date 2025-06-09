// CmdBarButton.cpp: implementation of the CWordCommandBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WordCommandBar.h"
#include "..\Api\GlobalConfigApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CWordCommandBar::CWordCommandBar()
{
	m_bEnable = 0;
	m_bVisible = 0;
	m_nIndex = 0;
}

CWordCommandBar::~CWordCommandBar()
{
	
}

long CWordCommandBar::SerializeOwn(CBinarySerialBuffer &oBuff)
{
	if (oBuff.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBuff,m_strName);
		BinarySerializeCalLen(oBuff,m_strID);
		oBuff.AddBufferLength(sizeof(m_bEnable));
		oBuff.AddBufferLength(sizeof(m_bVisible));
		oBuff.AddBufferLength(sizeof(m_nIndex));
	}
	else if (oBuff.IsReadMode())
	{
		BinarySerializeRead(oBuff, m_strName);
		BinarySerializeRead(oBuff, m_strID);
		BinarySerializeRead(oBuff, m_bEnable);
		BinarySerializeRead(oBuff, m_bVisible);
		BinarySerializeRead(oBuff, m_nIndex);
	}
	else if (oBuff.IsWriteMode())
	{
		BinarySerializeWrite(oBuff, m_strName);
		BinarySerializeWrite(oBuff, m_strID);
		BinarySerializeWrite(oBuff, m_bEnable);
		BinarySerializeWrite(oBuff, m_bVisible);
		BinarySerializeWrite(oBuff, m_nIndex);
	}

	return 0;
}

CWordCommandBarMngrBase::CWordCommandBarMngrBase()
{
}

CWordCommandBarMngrBase::~CWordCommandBarMngrBase()
{

}

void CWordCommandBarMngrBase::Init()
{
	m_strCmdBarsCfgFile = CString(_P_GetConfigPath());
	m_strCmdBarsCfgFile += L"WordCommandBar.ctp";
}

void CWordCommandBarMngrBase::EndIt()
{
	DeleteAll();
}

BOOL CWordCommandBarMngrBase::SaveWordCommandBarMngr()
{
	CBinarySerialBuffer oBuff;

	oBuff.SetCalSizeMode();
	Serialize(oBuff);
	oBuff.AllocBuffer(0);
	oBuff.ResetBufferPointer();
	oBuff.SetWriteMode();
	Serialize(oBuff);
	oBuff.SaveToFile(m_strCmdBarsCfgFile);

	return TRUE;
}

long CWordCommandBarMngrBase::SerializeOwn(CBinarySerialBuffer &oBuff)
{
	return 0;
}

CExBaseObject* CWordCommandBarMngrBase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	return new CWordCommandBar();
}

// D:\WorkLiJQ\Source\SttStudio\Module\MfcCtrl\SttTrangeComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "SttTrangeComboBox.h"
#include "..\AdjustTool\SttAdjBase.h"

//////////////////////////////////////////////////////////////////////////
// CSttTrangeComboBox
CSttTrangeComboBox::CSttTrangeComboBox()
{
	
}

CSttTrangeComboBox::~CSttTrangeComboBox()
{
}

// CSttTrangeComboBox 消息处理程序

BOOL CSttTrangeComboBox::CanAdd(CExBaseObject *pObj)
{
	if (pObj->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return FALSE;
	}

	CDataGroup *pGroup = (CDataGroup*)pObj;

	if (pGroup->m_strDataType == STT_ADJ_DATA_TYPE_TRange)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

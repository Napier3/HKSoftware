//DataGroupRefBase.cpp  CDataGroupRefBase


#include "stdafx.h"
#include "DataGroupRefBase.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDataGroupRefBase::CDataGroupRefBase()
{
	//初始化属性

	//初始化成员变量
}

CDataGroupRefBase::CDataGroupRefBase(CDataGroup *pRoot)
{
	Attacth(pRoot);
}

CDataGroupRefBase::~CDataGroupRefBase()
{
}

void CDataGroupRefBase::Attacth(CDataGroup *pRoot)
{
	m_pRoot = pRoot;
	InitAfterAttach();
}


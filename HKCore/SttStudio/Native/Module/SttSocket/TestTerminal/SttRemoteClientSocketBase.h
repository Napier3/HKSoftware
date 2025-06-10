#pragma  once

#include "SttClientSocketBase.h"

class CSttRemoteClientSocketBase : public CSttClientSocketBase
{
public:
	CSttRemoteClientSocketBase();
	virtual ~CSttRemoteClientSocketBase();

	CString m_strCode_Register;
};
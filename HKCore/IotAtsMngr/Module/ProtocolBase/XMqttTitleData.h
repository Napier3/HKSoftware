#pragma once

#include "../../../Module/MemBuffer/BufferBase.h"

class CXMqttTitleData:public CExBaseList
{
public:
	CXMqttTitleData();
	virtual ~CXMqttTitleData();

	//m_strID:����
	CBufferBase m_oBuffer;

};
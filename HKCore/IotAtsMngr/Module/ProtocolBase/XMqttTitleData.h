#pragma once

#include "../../../Module/MemBuffer/BufferBase.h"

class CXMqttTitleData:public CExBaseList
{
public:
	CXMqttTitleData();
	virtual ~CXMqttTitleData();

	//m_strID:Ö÷Ìâ
	CBufferBase m_oBuffer;

};
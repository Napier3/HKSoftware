#ifndef _AUDIOCMDINTERFACE_H_
#define _AUDIOCMDINTERFACE_H_

#include "Audio/AudioData.h"

//����ӿ�
class CAudioCmdInterface
{
public:
	CAudioCmdInterface() {}
	virtual ~CAudioCmdInterface() {}

	virtual void DoCmd(CAudioData* pCmdData) = 0;
};

#endif
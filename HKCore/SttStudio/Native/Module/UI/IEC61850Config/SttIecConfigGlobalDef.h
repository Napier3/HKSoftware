#ifndef STT_IECCONFIG_GLOBAL_DEF_H
#define STT_IECCONFIG_GLOBAL_DEF_H

class CIecConfigInterface
{
public:
	virtual ~CIecConfigInterface(){}
	virtual void SaveData() = 0;

//	QFont m_oIecFont;
};


#endif // STT_IECCONFIG_GLOBAL_DEF_H

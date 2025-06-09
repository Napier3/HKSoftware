#ifndef SettingZoneComboBox_H
#define SettingZoneComboBox_H

#include "../Module/ScrollCtrl/ScrollComboBox.h"

class CSettingZoneComboBox : public QScrollComboBox
{
public:
	CSettingZoneComboBox(QWidget* pparent);
	virtual ~CSettingZoneComboBox();

	void Init();
	long GetZone();
	
};

void SettingZoneComboBox_Init(QComboBox *pComboBox);
long SettingZoneComboBox_GetZone(QComboBox *pComboBox);


#endif // SettingZoneComboBox_H

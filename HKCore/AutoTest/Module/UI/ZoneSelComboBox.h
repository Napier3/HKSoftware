#pragma once

class CZoneSelComboBox :	public CComboBox
{
public:
	CZoneSelComboBox(void);
	~CZoneSelComboBox(void);

public:
	void InitComboBox();
	long GetZoneSelIndex();
	void SetZoneSelIndex(long nZoneIndex);
};

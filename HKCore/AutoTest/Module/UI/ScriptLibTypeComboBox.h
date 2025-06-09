#pragma once

class CScriptLibTypeComboBox :	public CComboBox
{
public:
	CScriptLibTypeComboBox(void);
	~CScriptLibTypeComboBox(void);

public:
	void InitComboBox(CExBaseObject *pItem);
	CExBaseObject* GetScriptLib();
	
protected:
	CExBaseObject *m_pGuideBook;
};

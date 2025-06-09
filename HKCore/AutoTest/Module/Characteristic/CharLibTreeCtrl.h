#pragma once


#include "CharacteristicLib.h"

class CCharLibTreeCtrl : public CTreeCtrl
{
public:
	CCharLibTreeCtrl();
	virtual ~CCharLibTreeCtrl();

public:
	CCharacteristic* GetCurrSelChar();
	CCharacterFolder* GetCurrSelFolder(BOOL bHasRoot=TRUE);
	CExBaseObject* GetSelObject();

	void ShowCharLib(CCharacteristicLib *pLib, BOOL bOnllyShowFolder=FALSE);
	void InsertCharTemp(CCharacteristic *pCharTemp);
	void UpdateCharTemp(CCharacteristic *pCharTemp);

	void InsertCharFolder(CCharacterFolder *pCharFolder);
	void UpdateCharFolder(CCharacterFolder *pCharFolder);

protected:
	HTREEITEM ShowCharFolder(CCharacterFolder *pRootFolder, HTREEITEM hParent=TVI_ROOT);
	CCharacteristicLib *m_pCharacteristicLib;
	BOOL m_bOnllyShowFolder;
};


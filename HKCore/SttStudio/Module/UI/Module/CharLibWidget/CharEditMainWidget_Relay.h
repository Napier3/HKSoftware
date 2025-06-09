#ifndef CharEditMainWidget_Relay_H
#define CharEditMainWidget_Relay_H


#include "CharEditMainWidget.h"

class QCharEditMainWidget_Relay : public QCharEditMainWidget
{
public:
	QCharEditMainWidget_Relay(QWidget* pParent = NULL);
	virtual ~QCharEditMainWidget_Relay();

private:
	void InitUI();
	void InitTableWidget();
	void InitCharactWidget();
	void InitConnect();
	void InitAreaData();

	void UpdateInterfaceData();
	void UpdateAreaData();
	void UpdateCharacters();

	void AddCharacter(CCharacteristic *pChar);
	CXDrawList* GetDrawListByID(const CString& strID);

private slots:

protected:
	virtual void CreateCharEditWidgetByLib();
	QCharEditWidgetBase *m_pCharEditWidget;
	CString m_strLastCharLibID;

//2022-9-3  lijunqing
public:
	virtual void InitCharacteristicsLib(const CString &strCharLibFile);
	virtual void ShowCharacteristics(CCharacteristics *pCharacteristics);
};

#endif//!CharEditMainWidget_Relay_H
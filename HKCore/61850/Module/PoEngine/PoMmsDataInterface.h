
#pragma once

#include "../MmsGlobal.h"
#include "../../../Module/DataMngr/DataGroup.h"

// CPoMmsDataInterface ÃüÁîÄ¿±ê

class CPoMmsDataInterface 
{
public:
	CPoMmsDataInterface();
	virtual ~CPoMmsDataInterface();

	virtual void OnFinalRelease();
	void AddData2(const CString &strID, const CString &strValue);

	static CPoMmsDataInterface* _New_CPoMmsDataInterface(CExBaseList *pDataInterface)
	{
		ASSERT (pDataInterface != NULL);

		CPoMmsDataInterface *pPoDataInterface = new CPoMmsDataInterface();
		pPoDataInterface->m_pDataInterface = pDataInterface;
		return pPoDataInterface;
	}

private:
	CExBaseList *m_pDataInterface;

public:
	long Reset(void);
	long AddData(const CString &bstrID, const CString &bstrValue);


    //2020-5-21  lijunqing
    void InitDataInterface(CDataGroup *pParas);
    void InitDataInterface(CDvmData *pData);
    void SetDataInterface(CExBaseList *p)   {   m_pDataInterface = p;   }

};



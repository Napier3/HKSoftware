
#pragma once

#include "../../../Module/DataMngr/DataGroup.h"


// CPxiDataInterface 

class CPxiDataInterface
{
public:
	CPxiDataInterface();
	virtual ~CPxiDataInterface();

	virtual void OnFinalRelease();
	void AddData2(const CString &strID, const CString &strValue);

	static CPxiDataInterface* _New_CPxiDataInterface(CExBaseList *pDataInterface)
	{
		ASSERT (pDataInterface != NULL);

		CPxiDataInterface *pPoDataInterface = new CPxiDataInterface();
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



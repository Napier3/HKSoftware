#pragma once

#include "../Device.h"
#include "../../../../Module/FileImExPortBase/FileToolsFactory.h"

class CStesFileToolsFactory : public CFileToolsFactory
{
private:
	CStesFileToolsFactory(void);
	virtual ~CStesFileToolsFactory(void);

	static CStesFileToolsFactory *g_pStesFileToolsFactory;
	static long g_nStesFileToolsFactoryRef;

public:
	static CStesFileToolsFactory* Create();
	static void Release();

	static void SetsFileImport(const CString &strFileType);

protected:
	virtual void AfterImportFile(CExBaseObject *pRefObject, CExBaseObject *pNewObject);
};


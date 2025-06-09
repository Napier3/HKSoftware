#ifndef SttIecGooseGrid_PkgAnalyze_H
#define SttIecGooseGrid_PkgAnalyze_H

#include "SttIecSmvGrid_PkgAnalyze.h"

//Goose   有效值 
class CSttIecGooseGrid_PkgAnalyze : public CSttIecSmvGrid_PkgAnalyze
{
public:
	CSttIecGooseGrid_PkgAnalyze(QWidget* pparent);
	virtual ~CSttIecGooseGrid_PkgAnalyze();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void Release();
	virtual BOOL NeedAddToSubPub(){return TRUE;}
};

#endif // SttIecGooseGrid_PkgAnalyze_H

//Ep104Frame_Group_68.h  
#ifndef _Ep104Frame_Group_68_H__
#define _Ep104Frame_Group_68_H__

#include "Ep104Frame_68.h"

#include "Ep101Frame_68_Asdu01.h"
#include "Ep101Frame_68_Asdu0D.h"
#include "Ep101Frame_68_Asdu1E.h"
#include "Ep101Frame_68_Asdu24.h"
#include "Ep101Frame_68_Asdu2E.h"
#include "Ep101Frame_68_Asdu30.h"
#include "Ep101Frame_68_Asdu64.h"
#include "Ep101Frame_68_Asdu67.h"

class CEp104Frame_Group_68 : public CEpFrameGroup
{
public:
	CEp104Frame_Group_68(void);
	~CEp104Frame_Group_68(void);
	
	friend class CEp104Frame_68_Head;
	friend class CEp104Frame_68_Tail;
//  Ù–‘
public:

public:
	virtual UINT GetClassID() {        return EPCLASSID_101_TFRAME_68_GROUP;    }

	virtual long IsEqual(CExBaseObject* pObj) { return 0; }
	virtual long Copy(CExBaseObject* pDesObj) { return 0; }
	virtual CBaseObject* Clone()  { return NULL; }

	virtual DWORD Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList);
	virtual CEpFrameBase* Match(PEPBUFFERPOS pBufferPos);
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos);
};


#endif //_Ep104Frame_Group_68_H__
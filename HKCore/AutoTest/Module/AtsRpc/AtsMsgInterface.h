#ifndef _AtsMsgInterface_h__
#define _AtsMsgInterface_h__

class CAtsMsgInterface : public CExBaseList
{
public:
	virtual BOOL OnMmsReport(WPARAM wParam,LPARAM lParam) = 0;
	virtual BOOL OnMmsCmdFinish(WPARAM wParam,LPARAM lParam) = 0;
	virtual BOOL OnMmsError(WPARAM wParam,LPARAM lParam) = 0;

	virtual BOOL OnAloneOperCmdFinish(WPARAM wParam,LPARAM lParam) = 0;
};

#endif // _AtsMsgInterface_h__


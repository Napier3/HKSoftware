#ifndef _os_XWndInterface_h__
#define _os_XWndInterface_h__


class CXWndInterface
{
public:
	virtual unsigned int XSetTimer(unsigned int nIDEvent, unsigned int nElapse, void* pFunc) = 0;
	virtual BOOL XKillTimer(unsigned int nIDEvent) = 0;
	virtual void XPostMessage(unsigned int nMsgID, unsigned long wParam=0, unsigned long  lParam=0) = 0;

};


#endif   //_os_XWndInterface_h__

// FigureDrawInterface.h: interface for the IFigureDrawInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_FIGUREDRAW_INTERFACE_H__)
#define _FIGUREDRAW_INTERFACE_H__

class IFigureDrawInterface
{
public:
	virtual BSTR GetDrawData();
	virtual long GetDrawDataString(IStringSerializeBuffer *buff);
	virtual long GetDrawDataBinary(ISerializeBuffer *buff);
	virtual long GetDrawData(LPCSTR pszValue);
	virtual long InitDrawDataBinary(ISerializeBuffer *buff);
	virtual long Draw(long lDC, double fZoomRatio,long lOriginX,long lOriginY);
	virtual long DrawEx(long lDC, IAxis *axis, double fZoomRatio,long lOriginX,long lOriginY);
	virtual long InitDraw(IAxis *axis);
};


#endif // !defined(_FIGUREDRAW_INTERFACE_H__)

#if !defined _AXISSCALEDATA_H___
#define _AXISSCALEDATA_H___

class CAxisScaleData : public CObject
{
public:
	float lVal;
	float fVal;
	int   iKind;
	CPoint cPt;
	
	double m_dAxisScaleVal;
	CPoint m_ptAxisScale;

	CAxisScaleData();
	~CAxisScaleData();
	void FillIt(double dVal,CPoint point);
	void FillIt2(float,float,int,CPoint);
};

int FloatValToInt(double f,BOOL bCaryy=1);
LPSTR chop(LPSTR cStr);
long GetIntVal(double fVal);

#endif //_AXISSCALEDATA_H_
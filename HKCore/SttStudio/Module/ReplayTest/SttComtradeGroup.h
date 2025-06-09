//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttParas.h  CSttParas

#pragma once

#include "SttCmtrdCfgDefineGlobal.h"
#include "../../../Module/DataMngr/DataGroup.h"
#include "../../../Module/Record/RtMemBuffer/MemBuffer_Float.h"

#if 0

class CSttComtradeGroup : public CDataGroup
{//��������ģ�顢ͨ��
public:
	CSttComtradeGroup();
	virtual ~CSttComtradeGroup();

public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTMAPGROUP;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmtrdCfgDefineXmlRWKeys::CSttMapGroupKey();     }
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
    virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
    virtual CExBaseObject* CreateNewChild(long nClassID/ *, BOOL &bAddToTail* /);

public:
	//�������ͨ��,���ֵ���ط�ͨ���������Ч
	double m_fMaxAbs;	//������ֵ
	CComplexMemBuffer_Float *m_pReplayBuf;//�ط�ͨ������

public:
	//�������ͨ��
	double CalcChannelMaxValue();
	BOOL IsChannelSelected();
	//��ʼ��ͨ���طŻ���
	void InitChReplayBuf(long nMaxPoints);
	//���ͨ���طŻ���
	void ResetChReplayBuf();

	//�������ģ��
	BOOL IsModuleType_U()	{	return (m_strDataType == _T("U"));}
	BOOL IsModuleType_I()	{	return (m_strDataType == _T("I"));}
	BOOL IsModuleSelected();
	double CalcChMaxValueByIndex(long nChIndex);
	double GetModuleMaxValue();
	void ScalingModuleMaxValue(float fK);
	void InitModuleReplayBuf(long nMaxPoints);
	void ResetModuleReplayBuf();

	long GetMaxPoints();//��ȡ��ǰͨ���ܵ���
	long GetValue_DataA();
	long GetValue_DataB();
	double GetValue_DataK();
};

///////////////////////////////////

CDvmData* Stt_SetDataAttr(CDataGroup *pGroup,const CString &strID, const CString &strValue);
CDvmData* Stt_SetDataAttr(CDataGroup *pGroup,const CString &strID, long nValue);
CDvmData* Stt_SetDataAttr(CDataGroup *pGroup,const CString &strID, double fValue, long nDecimal);

BOOL Stt_GetDataAttr(CDataGroup *pGroup,const CString &strID, CString &strValue);
BOOL Stt_GetDataAttr(CDataGroup *pGroup,const CString &strID, long &nValue);
BOOL Stt_GetDataAttr(CDataGroup *pGroup,const CString &strID, double &fValue,double fDefaultVal=0);
BOOL Stt_GetDataAttr(CDataGroup *pGroup,const CString &strID, float &fValue,float fDefaultVal=0);
#endif

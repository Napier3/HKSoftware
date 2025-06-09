#pragma once

#include "tmt_distance_test.h"
#include "../SearchBase/tmt_complex_search.h"

typedef struct tmt_distance_search_paras :public tmt_DistanceParas,public tmt_ComplexSearch
{

public:
	//2022.5.16 caoxc	增加项目名称
	char m_pszTestName[32];

	virtual void init()
	{
		tmt_DistanceParas::init();

		m_fScanFrom=1.000;
		m_fScanFromAngle=80.000;
		m_fScanTo=5.000;
		m_fScanToAngle=80.000;
		m_fStep=0.100f;

		m_fSearchBegin = 0;
		m_fSearchBeginAngle = 0;
		m_fCurrScanVal = 0;
		m_fCurrScanValAngle = 0;
		m_fSearchEnd = 0;
		m_fSearchEndAngle = 0;
		m_fSearchArea = 0;
		m_fMarginTime = 0.0f;
//		m_bCurrSearchSwitch = 0;

		//2022.5.16 caoxc
		memset(m_pszTestName, 0, 32);
	}
	void CopyOwn_DistanceSearchParas(tmt_distance_search_paras* pDest)
	{
		tmt_DistanceParas::CopyOwn(pDest);
		//tmt_ComplexSearch::CopyOwn(pDest);  //暂无,待后续添加 sf 20210715
	}

}tmt_DistanceSearchParas;

typedef struct tmt_distance_search_paras_I :virtual public tmt_DistanceSearchParas
{
public:
    int m_nBinState[MAX_BINARYIN_COUNT];//开入量状态.
    int m_nBinLogic;//0-或 1-与

    virtual void init()
    {
        tmt_DistanceSearchParas::init();
        m_nBinLogic = 0;
        for (int nIndex = 0;  nIndex  <  MAX_BINARYIN_COUNT;  nIndex++)
        {
            m_nBinState[nIndex] = 0;
        }
    }
}tmt_DistanceSearchParas_I;


typedef struct tmt_distance_search_results :public tmt_DistanceResults
{
public:
	int m_nActZ;

public:
	virtual void init()
	{
		tmt_DistanceResults::init();
		m_nActZ = 0;
	} 
	void CopyOwn(tmt_distance_search_results* pDest)
	{
		tmt_DistanceResults::CopyOwn(pDest);
		pDest->m_nActZ = m_nActZ;
	}
}tmt_DistanceSearchResults;

typedef struct tmt_distance_search_test : public TMT_PARAS_HEAD
{
public:
	tmt_DistanceSearchParas m_oDistanceSearchParas;
	tmt_DistanceSearchResults m_oDistanceSearchResults;
	void init()
	{
		init_head(); //20210918 zhouhj
		strcpy(m_pszMacroID, STT_MACRO_ID_DistanceSearch);
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oDistanceSearchParas.init();
		m_oDistanceSearchResults.init();
	}

	tmt_distance_search_test(){	init();}
	virtual void clear_result(){	m_oDistanceSearchResults.init();	}
	virtual ~tmt_distance_search_test(){}
}tmt_DistanceSearchTest;

typedef struct tmt_distance_search_test_I : public TMT_PARAS_HEAD
{
public:
    tmt_DistanceSearchParas_I m_oDistanceSearchParas;
    tmt_DistanceSearchResults m_oDistanceSearchResults;
    void init()
    {
        init_head(); //20210918 zhouhj
        strcpy(m_pszMacroID, STT_MACRO_ID_DistanceSearch_I);
        m_nVersion = 0x00010001;
        m_nTestState = 0;

        m_oDistanceSearchParas.init();
        m_oDistanceSearchResults.init();
//		init_head(); //2021-9-13  lijunqing
    }

    tmt_distance_search_test_I(){	init();}
    virtual void clear_result(){	m_oDistanceSearchResults.init();	}
    virtual ~tmt_distance_search_test_I(){}
}tmt_DistanceSearchTest_I;

void stt_init_paras(tmt_DistanceSearchParas *pParas);
void stt_init_paras(tmt_DistanceSearchParas_I *pParas);
void stt_init_results(tmt_DistanceSearchResults *pResults);

void stt_xml_serialize_Search(tmt_DistanceSearchParas *pParas, CSttXmlSerializeBase *pXmlSierialize,long nBinExNum,long nBoutExNum);
void stt_xml_serialize_Search(tmt_DistanceSearchParas_I *pParas, CSttXmlSerializeBase *pXmlSierialize,long nBinExNum,long nBoutExNum);
void stt_xml_serialize_SearchReport(tmt_DistanceSearchParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_Search(tmt_DistanceSearchResults *pResults, CSttXmlSerializeBase *pXmlSierialize,long nBinExNum,long nBoutExNum);
CSttXmlSerializeBase* stt_xml_serialize(tmt_DistanceSearchTest *pTests, CSttXmlSerializeBase *pXmlSerialize,long nBinExNum,long nBoutExNum);
CSttXmlSerializeBase* stt_xml_serialize(tmt_DistanceSearchTest_I *pTests, CSttXmlSerializeBase *pXmlSerialize,long nBinExNum,long nBoutExNum);



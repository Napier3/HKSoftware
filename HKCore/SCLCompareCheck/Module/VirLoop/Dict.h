#ifndef _DICT_H_040401_
#define _DICT_H_040401_

#include <string>
#include <map>

#include <cstdlib>
using namespace std;


class CDict
{

public:
	CDict();
	~CDict();

	map<int ,string > m_mapResult;

	bool FindKey(string&) ;
	bool OpenDict(CString strDictPath);	

	void SegKeyAndFind ( string) ;
	void MMChSegment ( string) ;
	bool IsDigOrAlph(unsigned char ch) ;
	bool IsGBWord(unsigned char *strSource) ;

	map<string, int> m_mapDict;  
};

#endif /* _DICT_H_040401_ */

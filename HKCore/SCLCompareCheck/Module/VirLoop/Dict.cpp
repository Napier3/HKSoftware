#include "StdAfx.h"
#include "Dict.h"

const unsigned int MAX_WORD_LENGTH = 12;

CDict::CDict()
{
}

CDict::~CDict()
{
	m_mapDict.clear();
}

bool CDict::OpenDict(CString strDictPath)
{
	FILE *fpDict;

	if ((fpDict = fopen(strDictPath, "r")) == NULL) {
		return false;
	}

	int freq;
	char word[16];
	while (fscanf(fpDict, "%s %d", word, &freq) != EOF) 
	{
//		m_mapDict.insert(map<string,int>::value_type (word, freq));
		m_mapDict.insert(make_pair(word, freq));
	}

	fclose(fpDict);
	return true;
}

bool CDict::FindKey(string& str) 
{
	bool bRet = false;

	map<string, int>::iterator iter;
	iter = m_mapDict.find(str);

	if (iter!= m_mapDict.end())
	{
		m_mapResult.insert(make_pair(iter->second ,iter->first));
		bRet = true;
	}

	return bRet;
}

//LB_c: 基于正向最大匹配法（Max Matching method）的中文分词函数
void CDict::MMChSegment ( string s1) 
{
	bool bGBWord = false;
	while (!s1.empty()) { 
		unsigned int len=s1.size();
		if (len>MAX_WORD_LENGTH) len=MAX_WORD_LENGTH;

		string w=s1.substr(0, len);// the candidate word
		bool isw = FindKey(w);

		while (len>2 && isw==false) {	// if not a word

			len--;	
			w=w.substr(0, len);
			isw = FindKey(w);
		}

		if (w.size()>2)
		{
			s1 = s1.substr(w.size());
		} 
		else if (IsGBWord((unsigned char*)&s1[0]))
		{
			s1 = s1.substr(2);
		}
		else
		{
			s1 = s1.substr(1);
		}
	}
}
//LB_c: 中文分词前的预处理，包括对英文字符和中文特殊字符的处理等
void CDict::SegKeyAndFind ( string strSource) 
{
	unsigned int i,len;

	while (!strSource.empty()) 
	{
		unsigned char ch = (unsigned char) strSource[0];
		if (!IsDigOrAlph(ch)&&(ch < 128 ))	// deal with ASCII
		{ 			
			i = 1;
			len = strSource.size();
			while ( i<len && 
				((unsigned char)strSource[i]<128) && 
				(strSource[i]!=10) && (strSource[i]!=13) &&(!IsDigOrAlph(strSource[i])))	// LF, CR
			{ 
				i++;
			}

			if ( i <= strSource.size() )
			{
				strSource = strSource.substr(i);
			}
			else 
			{
				break;
			}

			continue;
		} 
		else 
		{ 
			// 中文标点等非汉字字符
			if (!IsDigOrAlph(ch)&&(ch < 176)) 
			{ 
				i = 0;
				len = strSource.length();

				while ( i<len 
					&& ((unsigned char)strSource[i]<176) 
					&& ((unsigned char)strSource[i]>=161)
					//LB_c: 不为、 。 · ˉ ˇ ¨ 〃
					&& (!((unsigned char)strSource[i]==161 && ((unsigned char)strSource[i+1]>=162 && (unsigned char)strSource[i+1]<=168)))
					//LB_c: 不为～ ‖ … ‘ ’“ ” 〔 〕 〈 〉 《 》 「 」 『 』 〖 〗 【 】
					&& (!((unsigned char)strSource[i]==161 && ((unsigned char)strSource[i+1]>=171 && (unsigned char)strSource[i+1]<=191)))
					//LB_c: 不为，！（ ）： ；？
					&& (!((unsigned char)strSource[i]==163 && ((unsigned char)strSource[i+1]==172 || (unsigned char)strSource[i+1]==161) 
					|| (unsigned char)strSource[i+1]==168 || (unsigned char)strSource[i+1]==169 || (unsigned char)strSource[i+1]==186 
					|| (unsigned char)strSource[i+1]==187 || (unsigned char)strSource[i+1]==191) ) 
					) 
				{ 
					i = i + 2; // 假定没有半个汉字
				}

				if ( i == 0 ) 
				{
					i = i + 2;
				}

				// 不处理中文空格
				if ( !( ch==161 && (unsigned char)strSource[1]==161 ) ) 
				{ 
					if ( i > strSource.size() )
					{
						break;
					}
				}

				if ( i <= strSource.size() )
				{
					strSource = strSource.substr(i);
				}
				else 
				{
					break;
				}

				continue;
			}
		}
		i = 0;
		len = strSource.length();
		bool bIndex = (IsGBWord((unsigned char*)&strSource[i]));
		while ( i<len && (bIndex||(IsDigOrAlph(strSource[i]))) ) 
		{
			if (bIndex)
			{
				i+=2;
			} 
			else
			{
				i++;
			}
			bIndex = (IsGBWord((unsigned char*)&strSource[i]));
		}

		MMChSegment(strSource.substr(0,i));
		if (i <= len)
		{
			strSource=strSource.substr(i);
		}
		else 
		{
			break;
		}
	}
}

bool CDict::IsDigOrAlph(unsigned char ch) 
{
	if ((ch>47)&&(ch<58))
	{
		return true;
	}
	else if ((ch>64)&&(ch<91))
	{
		return true;
	}
	else if ((ch>96)&&(ch<123))
	{
		return true;
	}
	return false;
}

bool CDict::IsGBWord(unsigned char *pszSource) 
{
	if (pszSource[0]<128)
	{
		return false;
	}
	if(((unsigned char)pszSource[0]<176) 
		&& ((unsigned char)pszSource[0]>=161)
		//LB_c: 不为、 。 · ˉ ˇ ¨ 〃
		&& (!((unsigned char)pszSource[0]==161 && ((unsigned char)pszSource[1]>=162 && (unsigned char)pszSource[1]<=168)))
		//LB_c: 不为～ ‖ … ‘ ’“ ” 〔 〕 〈 〉 《 》 「 」 『 』 〖 〗 【 】
		&& (!((unsigned char)pszSource[0]==161 && ((unsigned char)pszSource[1]>=171 && (unsigned char)pszSource[1]<=191)))
		//LB_c: 不为，！（ ）： ；？
		&& (!((unsigned char)pszSource[0]==163 && ((unsigned char)pszSource[1]==172 || (unsigned char)pszSource[1]==161) 
		|| (unsigned char)pszSource[1]==168 || (unsigned char)pszSource[1]==169 || (unsigned char)pszSource[1]==186) 
		|| (unsigned char)pszSource[1]==187 || (unsigned char)pszSource[1]==191))
		return false;

	return true;
}
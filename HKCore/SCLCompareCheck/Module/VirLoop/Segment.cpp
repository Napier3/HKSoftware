#include "StdAfx.h"
#include "Segment.h"

const unsigned int MAX_WORD_LENGTH = 10;


CSegment::CSegment(void)
{
}


CSegment::~CSegment(void)
{
}

//LB_c: �����������ƥ�䷨��Max Matching method�������ķִʺ���
void CSegment::MMChSegment (CDict &dict, string s1) const
{
	bool bGBWord = false;
	while (!s1.empty()) { 
		unsigned int len=s1.size();
		if (len>MAX_WORD_LENGTH) len=MAX_WORD_LENGTH;

		string w=s1.substr(0, len);// the candidate word
		bool isw=dict.FindKey(w);
        
		while (len>2 && isw==false) {	// if not a word

			len--;	
			w=w.substr(0, len);
			isw=dict.FindKey(w);
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
//LB_c: ���ķִ�ǰ��Ԥ����������Ӣ���ַ������������ַ��Ĵ����
void CSegment::SegKeyAndFind (CDict &dict, string strSource) const
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
			// ���ı��ȷǺ����ַ�
			if (!IsDigOrAlph(ch)&&(ch < 176)) 
			{ 
				i = 0;
				len = strSource.length();

				while ( i<len 
					&& ((unsigned char)strSource[i]<176) 
					&& ((unsigned char)strSource[i]>=161)
					//LB_c: ��Ϊ�� �� �� �� �� �� ��
					&& (!((unsigned char)strSource[i]==161 && ((unsigned char)strSource[i+1]>=162 && (unsigned char)strSource[i+1]<=168)))
					//LB_c: ��Ϊ�� �� �� �� ���� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��
					&& (!((unsigned char)strSource[i]==161 && ((unsigned char)strSource[i+1]>=171 && (unsigned char)strSource[i+1]<=191)))
					//LB_c: ��Ϊ������ ���� ����
					&& (!((unsigned char)strSource[i]==163 && ((unsigned char)strSource[i+1]==172 || (unsigned char)strSource[i+1]==161) 
					|| (unsigned char)strSource[i+1]==168 || (unsigned char)strSource[i+1]==169 || (unsigned char)strSource[i+1]==186 
					|| (unsigned char)strSource[i+1]==187 || (unsigned char)strSource[i+1]==191) ) 
					) 
				{ 
					i = i + 2; // �ٶ�û�а������
				}

				if ( i == 0 ) 
				{
					i = i + 2;
				}

				// ���������Ŀո�
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

		MMChSegment(dict, strSource.substr(0,i));
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

bool CSegment::IsDigOrAlph(unsigned char ch) const
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

bool CSegment::IsGBWord(unsigned char *pszSource) const
{
	if (pszSource[0]<128)
	{
		return false;
	}
	if(((unsigned char)pszSource[0]<176) 
		&& ((unsigned char)pszSource[0]>=161)
		//LB_c: ��Ϊ�� �� �� �� �� �� ��
		&& (!((unsigned char)pszSource[0]==161 && ((unsigned char)pszSource[1]>=162 && (unsigned char)pszSource[1]<=168)))
		//LB_c: ��Ϊ�� �� �� �� ���� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��
		&& (!((unsigned char)pszSource[0]==161 && ((unsigned char)pszSource[1]>=171 && (unsigned char)pszSource[1]<=191)))
		//LB_c: ��Ϊ������ ���� ����
		&& (!((unsigned char)pszSource[0]==163 && ((unsigned char)pszSource[1]==172 || (unsigned char)pszSource[1]==161) 
		|| (unsigned char)pszSource[1]==168 || (unsigned char)pszSource[1]==169 || (unsigned char)pszSource[1]==186) 
		|| (unsigned char)pszSource[1]==187 || (unsigned char)pszSource[1]==191))
		return false;

	return true;
}
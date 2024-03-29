#include "StdAfx.h"
#include "ini.h"
 
#define MAX_ALLSECTIONS 2048  //全部的段名
#define MAX_SECTION 50  //一个段名长度
#define MAX_ALLKEYS 6000  //全部的键名
#define MAX_KEY 50  //一个键名长度
#define MAX_BUFFER 2500
 
CIni::CIni()
{
}

BOOL CIni::SetFileName(LPCTSTR lpFileName)
{
	CFile file;
	CFileStatus status;
 
	if(!file.GetStatus(lpFileName,status))
		return TRUE;

	m_strFileName=lpFileName;
	return FALSE;
}
 
CString CIni::GetFileName(void)
{
	return m_strFileName;
}
 
BOOL CIni::SetValue(LPCTSTR lpSection, LPCTSTR lpKey, LPCTSTR lpValue,bool bCreate)
{
	TCHAR lpTemp[MAX_BUFFER] ={0};
 
	//以下if语句表示如果设置bCreate为false时，当没有这个键名时则返回TRUE（表示出错）
	//!*&*none-value*&!* 这是个垃圾字符没有特别意义，这样乱写是防止凑巧相同。
	if (!bCreate)
	{
		GetPrivateProfileString(lpSection,lpKey,"!*&*none-value*&!*",lpTemp,MAX_BUFFER,m_strFileName);
		if(strcmp(lpTemp,"!*&*none-value*&!*")==0)
			return TRUE;
	}
 
	if(WritePrivateProfileString(lpSection,lpKey,lpValue,m_strFileName))
		return FALSE;
	else
		return GetLastError();
}
 
CString CIni::GetStringValue(LPCTSTR lpSection, LPCTSTR lpKey)
{
	DWORD dValue;
	TCHAR lpValue[MAX_BUFFER] ={0};

	dValue=GetPrivateProfileString(lpSection,lpKey,"",lpValue,MAX_BUFFER,m_strFileName);
	return lpValue;
}

UINT CIni::GetIntValue(LPCTSTR lpSection, LPCTSTR lpKey)
{
	return GetPrivateProfileInt(lpSection,lpKey,0,m_strFileName);
}
 
BOOL CIni::SetSection(LPCTSTR lpSection)
{
	return WriteProfileSection(m_strFileName,lpSection);
}

BOOL CIni::DelSection(LPCTSTR lpSection)
{
	if(WritePrivateProfileString(lpSection,NULL,NULL,m_strFileName))
		return FALSE;
	else
		return GetLastError();
}
 
BOOL CIni::DelKey(LPCTSTR lpSection, LPCTSTR lpKey)
{
	if(WritePrivateProfileString(lpSection,lpKey,NULL,m_strFileName))
		return FALSE;
	else
		return GetLastError();
}
 
int CIni::GetSections(CStringArray& arrSection)
{
	/*
	本函数基础：
	GetPrivateProfileSectionNames - 从 ini 文件中获得 Section 的名称
	如果 ini 中有两个 Section: [sec1] 和 [sec2]，则返回的是 'sec1',0,'sec2',0,0 ，当你不知道  
	ini 中有哪些 section 的时候可以用这个 api 来获取名称 
	*/
	int i;  
	int iPos=0;  
	int iMaxCount;
	TCHAR chSectionNames[MAX_ALLSECTIONS]={0}; //总的提出来的字符串
	TCHAR chSection[MAX_SECTION]={0}; //存放一个段名。
	GetPrivateProfileSectionNames(chSectionNames,MAX_ALLSECTIONS,m_strFileName);
	
	//以下循环，截断到两个连续的0
	for(i=0;i<MAX_ALLSECTIONS;i++)
	{
		if (chSectionNames[i]==0)
			if (chSectionNames[i]==chSectionNames[i+1])
				break;
	}
 
	iMaxCount=i+1; //要多一个0号元素。即找出全部字符串的结束部分。
	arrSection.RemoveAll();//清空原数组
	
	for(i=0;i<iMaxCount;i++)
	{
		chSection[iPos++]=chSectionNames[i];
		if(chSectionNames[i]==0)
		{   
			arrSection.Add(chSection);
			memset(chSection,0,MAX_SECTION);
			iPos=0;
		}
	}
 
	return (int)arrSection.GetSize();
}
 
int CIni::GetKeyValues(CStringArray& arrKey,CStringArray& arrValue, LPCTSTR lpSection)
{
	/*
	本函数基础：
	GetPrivateProfileSection- 从 ini 文件中获得一个Section的全部键名及值名
	如果ini中有一个段，其下有 "段1=值1" "段2=值2"，则返回的是 '段1=值1',0,'段2=值2',0,0 ，当你不知道  
	获得一个段中的所有键及值可以用这个。 
	*/
	int i;  
	int iPos=0;
	CString strKeyValue;
	int iMaxCount;
	TCHAR chKeyNames[MAX_ALLKEYS]={0}; //总的提出来的字符串
	TCHAR chKey[MAX_KEY]={0}; //提出来的一个键名

	GetPrivateProfileSection(lpSection,chKeyNames,MAX_ALLKEYS,m_strFileName);

	for(i=0;i<MAX_ALLKEYS;i++)
	{
		if (chKeyNames[i]==0)
			if (chKeyNames[i]==chKeyNames[i+1])
				break;
	}
	
	iMaxCount=i+1; //要多一个0号元素。即找出全部字符串的结束部分。
	arrKey.RemoveAll();//清空原数组
	arrValue.RemoveAll();
	
	for(i=0;i<iMaxCount;i++)
	{
		chKey[iPos++]=chKeyNames[i];
		if(chKeyNames[i]==0)
		{
			strKeyValue=chKey;
			arrKey.Add(strKeyValue.Left(strKeyValue.Find("=")));
			arrValue.Add(strKeyValue.Mid(strKeyValue.Find("=")+1));
			memset(chKey,0,MAX_KEY);
			iPos=0;
		}
	}
 
	return (int)arrKey.GetSize();
}
 
BOOL CIni::DelAllSections()
{
	int nSection;
	CStringArray arrSection;
	nSection=GetSections(arrSection);
	for(int i=0;i<nSection;i++)
	{
		if(DelSection(arrSection[i]))
			return GetLastError();
	}
	return FALSE;
}
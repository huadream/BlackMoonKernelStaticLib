#include "stdafx.h"
#include "Myfunctions.h"

//�ı����� - ��ȫ��
/*
    ���ø�ʽ�� ���ı��͡� ��ȫ�� ���ı��� ���任���ı��� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�QJCase
    ���ı��еİ����ĸ���ո�����ֱ任Ϊȫ�ǣ����ر任��Ľ���ı���������Ϊ�������
    ����<1>������Ϊ�����任���ı���������Ϊ���ı��ͣ�text������

' ���ַ�Χ163��ͷ��176--185
' ��д��ĸ��163��ͷ��193--218
' Сд��ĸ��163��ͷ��225--250
' ///////////����Ϊȫ�ǵģ������ǰ�ǵ�
' ���ַ�Χ��48--57
' ��д��ĸ��65--90
' Сд��ĸ��97-122
���ֽڼ� (��������)  ' 163,174,163,173
*/
LIBAPI(char*, krnln_QJCase)
{
	PMDATA_INF pArgInf = &ArgInf;
	size_t nLen = mystrlen(ArgInf.m_pText);
	if (nLen == 0) return NULL;
	
	char* pszLast = ArgInf.m_pText + nLen;
	char* pszFirst = ArgInf.m_pText;
	char* pszSrc = (char*)malloc(nLen * 2 + 1);
	char* pszTmp = pszSrc;
	size_t sSublen;
	for (;;)
	{
		char* pPos = strstr(pszFirst, "\\");
		if (!pPos) break;
		sSublen = pPos - pszFirst;
		if (sSublen > 0)
		{
			memcpy(pszTmp, pszFirst, sSublen);
		}

		*(short*)(pszTmp + sSublen) = *(short*)"��";
		pszTmp += sSublen + 2;
		pszFirst = pPos	+ 1;
	}
	sSublen = pszLast - pszFirst;
	if (sSublen > 0)
	{
		memcpy(pszTmp, pszFirst, sSublen);
		pszTmp += sSublen;
	}
	pszTmp[0] = '\0';
	
	INT nBufLen = nLen * 2 + 1;
	nLen = mystrlen(pszSrc);

	char *pQJText = (char*)E_MAlloc(nBufLen);
	LCMapString (2052, LCMAP_FULLWIDTH, pszSrc, nLen, pQJText, nBufLen);
	free(pszSrc);
	return pQJText;
}

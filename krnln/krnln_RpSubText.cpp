#include "stdafx.h"
#include "mem.h"
#include "Myfunctions.h"
//�ı����� - ���ı��滻
/*
    ���ø�ʽ�� ���ı��͡� ���ı��滻 ���ı��� �����滻���ı����ı��� �����滻�����ı������ı��� �����滻�����ı��ݣ��������� �����滻����ʼλ�ãݣ��������� �滻���еĴ����ݣ��߼��� �Ƿ����ִ�Сд�� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�RpSubText
    ����һ���ı������ı���ָ�������ı��ѱ��滻����һ���ı��������滻�����Ĵ���Ҳ�Ǳ�ָ���ġ�������Ϊ�������
    ����<1>������Ϊ�������滻���ı���������Ϊ���ı��ͣ�text������
    ����<2>������Ϊ�������滻�����ı���������Ϊ���ı��ͣ�text������
    ����<3>������Ϊ�������滻�����ı���������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ������������ʡ�ԣ�Ĭ��Ϊ���ı���
    ����<4>������Ϊ�������滻����ʼλ�á�������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�����ֵָ�����滻���ı�����ʼ����λ�á����ʡ�ԣ�Ĭ�ϴ� 1 ��ʼ��
    ����<5>������Ϊ���滻���еĴ�����������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�����ֵָ�������ı������滻�Ĵ��������ʡ�ԣ�Ĭ�Ͻ������п��ܵ��滻��
    ����<6>������Ϊ���Ƿ����ִ�Сд��������Ϊ���߼��ͣ�bool��������ʼֵΪ���桱��Ϊ�����ִ�Сд��Ϊ�ٲ����֡�


char* StrCpyForE(char* pSrc)
{
	INT nLen = strlen(pSrc);
	char *pText = (char*)E_MAlloc(nLen+1);
	strcpy(pText,pSrc);
	return pText;
}*/
LIBAPI(char*, krnln_RpSubText)
{// �����ߺ� ��
	PMDATA_INF pArgInf = &ArgInf;
	char* pSrc = pArgInf[0].m_pText;
	if (!pSrc || !*pSrc) return NULL;
	//��ʼ�滻λ��
	INT nStart;
	if (pArgInf[3].m_dtDataType == _SDT_NULL || pArgInf[3].m_int <= 1)
		nStart = 0;
	else
		nStart = pArgInf[3].m_int - 1;
	//�жϿ�ʼλ��
	char* cp = pSrc;
	char* pStart = pSrc + nStart;
	for (; *cp && cp < pStart; cp++)
		if (*cp < 0) cp++; // ����
	//MessageBox(NULL,"1","432",MB_OK);
	if (!*cp)
		return CloneTextData(pSrc, cp - pSrc);

	INT nSLen = (cp + mystrlen(cp)) - pSrc;
	//MessageBox(NULL,"2","432",MB_OK);
	//�������ı�
	char* pDes = pArgInf[1].m_pText;
	INT nDLen = 0;
	if (pDes)
		nDLen = mystrlen(pDes);
	//�滻����
	//MessageBox(NULL,"3","432",MB_OK);
	INT nCount = pArgInf[4].m_int;
	if (pArgInf[4].m_dtDataType == _SDT_NULL)
		nCount = 0x7FFFFFFF;// ����滻����21��
	//MessageBox(NULL,"4","432",MB_OK);
	if (nDLen <=0 || nCount<=0) // �ؼ��������Ϸ���ֱ�ӷ���ԭ�ı�
		return CloneTextData(pSrc, nSLen);
	//MessageBox(NULL,"5","432",MB_OK);
	char* pSub = NULL;
	INT nSubLen = 0;
	if (pArgInf[2].m_dtDataType != _SDT_NULL)
	{
		pSub = pArgInf[2].m_pText;
		if (pSub)
			nSubLen = mystrlen(pSub);
	}
	//MessageBox(NULL,"6","432",MB_OK);
	// ��ʼ����
	PTB pTb = initSubTb();
	if (!pTb)
		return CloneTextData(pSrc, nSLen);
	//MessageBox(NULL,"123","432",MB_OK);

	INT nPos;
	char* pFirst = pSrc;
	char* pLast = pSrc + nSLen;
	//char* pMsg = (char*)malloc(256);
	//sprintf(pMsg,"addr:%x",pTb);
	//MessageBox(NULL,pMsg,"432",MB_OK);
	if (pArgInf[5].m_bool) // ���ִ�Сд
	{
		for (; nCount > 0; nCount--)
		{
			nPos = mystrstr((char*)cp, (char*)pDes);
			if (nPos == -1)
				break;
			if (cp + nPos - pFirst > 0)
				recSub(&pTb, pFirst, cp + nPos - pFirst);
		
			if (nSubLen > 0)
				recSub(&pTb, pSub, nSubLen);
		
			cp += nPos + nDLen;
			pFirst = cp;
		}
	}
	else
	{
		for (; nCount > 0; nCount--)
		{
			nPos = mystristr((char*)cp, (char*)pDes);
			if (nPos == -1)
				break;
			if (cp + nPos - pFirst > 0)
				recSub(&pTb, pFirst, cp + nPos - pFirst);
			
			if (nSubLen > 0)
				recSub(&pTb, pSub, nSubLen);
			
			cp += nPos + nDLen;
			pFirst = cp;
		}
	}
	//MessageBox(NULL,"8","432",MB_OK);
	if (pLast - pFirst > 0)
		recSub(&pTb, pFirst, pLast - pFirst);
	
	//MessageBox(NULL,"9","432",MB_OK);
	// ���Ƽ�����
	char* pRetn = SubTbtoString(pTb);
	if (pTb)
		free(pTb);
	//MessageBox(NULL,"12","432",MB_OK);
	return pRetn;
}


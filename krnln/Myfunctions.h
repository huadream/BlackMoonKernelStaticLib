#ifndef _MY_FUNCS_
#define _MY_FUNCS_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _MEMSP_{
	char* pData;
	int nLen;
}MEMSP, *PMEMSP;

typedef struct _TBRECORD{
	PVOID	addr;	//���ݵ�ַ
	DWORD	len;	//���ݳ���
}TBRECORD, *PTBRECORD;

typedef struct _TB{
	DWORD		size;	//�ڴ���С
	DWORD		count;	//��¼����
	DWORD		len;	//��¼�ܳ�
	TBRECORD	rec[1]; //��¼����
}TB, *PTB;

extern unsigned char lowtable[];
extern unsigned char uptable[];

int __fastcall mymemchr(unsigned char *pSrc, int nLen, unsigned char Des);
int BoyerMoore(unsigned char *text, int n, unsigned char *pattern, int m);

int inline MyMemCmp(unsigned char* a, unsigned char* b, int len);

typedef size_t (*MYSTRLEN)(const char *str);
// ȡ�ַ�������
extern MYSTRLEN mystrlen;

int __fastcall myinstring(unsigned char *src, int slen,unsigned char *des, int dlen);
PTB __cdecl initSubTb();
void __fastcall recSub(PTB* tb, PVOID addr, DWORD len);
char* __cdecl SubTbtoString(PTB ptb);
INT __fastcall mystristr(char* str1, char* str2);
INT __fastcall mystrstr(char* str1, char* str2);

void swap_hex(unsigned char* string, int length);
void E_RC4_init(unsigned char* keytable, unsigned char* key, int keylen);
void E_RC4_updatetable(int len, unsigned char* keytable);
void E_RC4(unsigned char* data, int datalen, unsigned char* keytable);
BOOL E_RC4_Calc(int pos, unsigned char *pData,int nDlen, unsigned char *pKeytable, int nCryptStart, unsigned char *pMD5);

#endif

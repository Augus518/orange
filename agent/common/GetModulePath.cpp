/**
	\file	GetModulePathA.cpp
	\author	KimPro
	\date	2005.04.04

  */
#include "pch.h"
YAGENT_COMMON_BEGIN

/**	\brief	���� ȣ��� ���(��������)�� ��θ� ��� �Լ�.

	\param	LPCTSTR	szPath	���� ��� ���ڿ�
	\param	DWORD	dwSize	���� ������ ���ڿ��M �ִ� ����.
	\return	bool: ���� - TRUE, ���� - FALSE


*/
bool	GetModulePath(OUT LPTSTR szPath, IN DWORD dwSize)
{
	return GetInstancePath(NULL, szPath, dwSize);
}

bool	GetInstancePath(IN HINSTANCE hInstance, OUT LPTSTR szPath, IN DWORD dwSize)
{
	LPTSTR	ps;
	TCHAR	szBuf[LBUFSIZE];

	if( ::GetModuleFileName(hInstance, szBuf, sizeof(szBuf)) )
	{
		ps	= _tcsrchr(szBuf, TEXT('\\'));
		if( ps )
		{
			*ps	= NULL;

			/*
				2013/05/05	kimpro
				����ü �Ʒ� ���� ó���� ���������� ��� �� +4���� ����������??
				
			if( _T('\\') == szBuf[0] )
			{
				::StringCbCopy(szPath, dwSize, szBuf + 4);
			}
			else
			{
				::StringCbCopy(szPath, dwSize, szBuf);
			}
			*/
			::StringCbCopy(szPath, dwSize, szBuf);

			return true;
		}
	}
	return false;
}
YAGENT_COMMON_END

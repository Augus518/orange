#include "pch.h"
YAGENT_COMMON_BEGIN
BOOL	CreateDirectory(LPCTSTR lpPath)
{
	TCHAR	szDir[LBUFSIZE];
	TCHAR	szPath[LBUFSIZE];
	LPTSTR	ps;

	try
	{
		//_nlog(_T("files"), _T("CREATE_DIRECTORY:%s"), lpPath);
		if( IsDirectory(lpPath) )
		{
			// lpPath�� ���丮��� TRUE�� ��ȯ�Ѵ�.
			return TRUE;
		}

		StringCbCopy(szPath, sizeof(szPath), lpPath);

		ps = szPath;

		while( ps ) 
		{
			ps = _tcschr(ps, _T('\\'));
			if( NULL == ps )
			{
				break;
			}

			::StringCbCopyN(szDir, sizeof(szDir), szPath, (ps - szPath + 1) * sizeof(TCHAR));
			::CreateDirectory(szDir, 0);

			ps++;
		}

		if( FALSE == ::CreateDirectory(lpPath, 0) )
		{
			if( ERROR_ALREADY_EXISTS == GetLastError() )
			{
				return TRUE;
			}
		}
	}
	catch(...)
	{
		
	}
	return IsDirectory(lpPath);
}
BOOL	MakeDirectory(IN LPCTSTR lpPath)
{
	if( _T('\\') == lpPath[0] && _T('\\') != lpPath[1] )
	{
		// �־��� Path�� ���� ��ΰ� �ƴ� ��� ����̴�.
		TCHAR	szPath[LBUFSIZE];

		GetModulePath(szPath, sizeof(szPath));
		::StringCbCat(szPath, sizeof(szPath), lpPath);

		return CreateDirectory(szPath);
	}
	return CreateDirectory(lpPath);
}
YAGENT_COMMON_END
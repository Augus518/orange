#include "pch.h"

YAGENT_COMMON_BEGIN

DWORD64	GetFileSize64(IN HANDLE hFile)
{
	DWORD	dwHi, dwLo;
	DWORD64	dwFileSize	= 0, dwSize;

	dwLo	= ::GetFileSize(hFile, &dwHi);
	dwSize	= dwHi; 

	dwFileSize	= (dwSize<<32)|dwLo;

	return dwFileSize;
}

DWORD64	GetFileSize64ByPath(IN LPCTSTR lpPath)
{
	DWORD64	dwSize	= 0;
	HANDLE	hFile;

	hFile	= ::CreateFile(lpPath, GENERIC_READ, FILE_SHARE_READ, NULL, 
					OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if( INVALID_HANDLE_VALUE == hFile )
	{
		// �׷� ������ �����.
		return dwSize;			
	}

	dwSize	= GetFileSize64(hFile);
	::CloseHandle(hFile);

	return dwSize;
}

bool	IsWindows9x()
{
	return false;
}
bool	FindFile(IN LPCTSTR lpPath, OUT WIN32_FIND_DATA *fd)
{
	WIN32_FIND_DATA		fData;
	//HANDLE				hFile;	-> ���� �ּ��� ���ö�.
	HANDLE				hFind;
	LPCTSTR				pPath;
	TCHAR				szShortPath[MBUFSIZE];

	if( IsWindows9x() && ::GetShortPathName(lpPath, szShortPath, sizeof(szShortPath)) )
	{
		pPath	= szShortPath;
	}
	else
	{
		pPath	= lpPath;
	}

	hFind	= ::FindFirstFile(pPath, &fData);
	if( INVALID_HANDLE_VALUE == hFind )
	{
		return false;
	}

	if( fd )
	{
		::CopyMemory(fd, &fData, sizeof(fData));
	}
	::FindClose(hFind);
	
	return true;
}


bool	IsFileExist(IN LPCTSTR lpPath)
{
	WIN32_FIND_DATA		fData;
	HANDLE				hFind;
	LPCTSTR				pPath;
	TCHAR				szPath[LBUFSIZE]		= _T("");

	// 2012/02/03	������
	// lpPath�� Ǯ�н��� �ƴ� �ܼ� ���ϸ��̶��?
	// �׷��ٸ� ���� ���丮���� �ش� ������ �����ϴ��� Ȯ���Ѵ�.

	if( lpPath && *lpPath && 
		(	
			lpPath[1] == _T(':') ||
			(lpPath[0] == _T('\\') && lpPath[1] == _T('\\'))
			
		)
	)
	{
		// Ǯ�н��� �����Ǿ� �ִ�.
		::StringCbCopy(szPath, sizeof(szPath), lpPath);
	}
	else
	{
		// �ܼ� ���ϸ� - ���� ���丮���� ã�´�.
		LPTSTR	pStr	= NULL;

		::GetModuleFileName(NULL, szPath, sizeof(szPath));
		pStr	= _tcsrchr(szPath, _T('\\'));
		if( pStr )
		{
			*(pStr + 1)	= NULL;
			::StringCbCat(szPath, sizeof(szPath), lpPath);
		}
	}

	pPath	= szPath;

	hFind	= ::FindFirstFile(pPath, &fData);
	if( INVALID_HANDLE_VALUE == hFind )
	{
		//_log(_T("error: NOT_FOUND[%s], code = %d"), pPath, ::GetLastError());
		return false;
	}

	::FindClose(hFind);

	return true;
}

DWORD	GetFileSize32(IN LPCTSTR lpPath, OUT bool * bExist)
{
	WIN32_FIND_DATA		fData;
	//HANDLE				hFile;	-> ���� �ּ��� ���ö�.
	HANDLE				hFind;
	DWORD				dwSize;
	LPCTSTR				pPath;
	TCHAR				szShortPath[MBUFSIZE];

	if( IsWindows9x() && ::GetShortPathName(lpPath, szShortPath, sizeof(szShortPath)) )
	{
		pPath	= szShortPath;
	}
	else
	{
		pPath	= lpPath;
	}

	hFind	= ::FindFirstFile(pPath, &fData);
	if( INVALID_HANDLE_VALUE == hFind )
	{
		if( bExist )
		{
			*bExist	= false;
		}
		return 0;
	}
	dwSize	= fData.nFileSizeLow;
	::FindClose(hFind);

	/*
		2006.06.15	����/����
		������ �̹� ���� ũ�⸦ �� ���� �� �ֱ� ������ ������ 
		dwSize	= fData.nFileSizeLow;
		�� �߰��ϰ� (�������� ������.) �Ʒ� �κ��� �ּ�ó�� �Ϸô�.
		
	// FILE_READ_ATTRIBUTE �� �ӵ��鿡�� �� ������ ������ ����������, 
	// WIN9X������ �������� �ʴ´�.
	hFile	= ::CreateFile(pPath, GENERIC_READ, //FILE_READ_ATTRIBUTES,
					FILE_SHARE_READ, NULL, OPEN_EXISTING, 
					FILE_ATTRIBUTE_NORMAL|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_READONLY,
					NULL);
	if( INVALID_HANDLE_VALUE == hFile )
	{
		// FindFirstFile�δ� �ִµ�, CreateFile�δ� ����? ��ȣ �̻��� ����̾��.
		//AhnAlert(_T("%s\n%d"), pPath, GetLastError());
		*bExist	= false;
		return 0;
	}
	dwSize	= ::GetFileSize(hFile, NULL);
	::CloseHandle(hFile);
	*/

	if( bExist )
	{
		*bExist	= true;
	}
	return dwSize;
}

DWORD	GetFileSize(IN LPCTSTR lpPath, OUT bool * bExist)
{
	return GetFileSize32(lpPath, bExist);
}

YAGENT_COMMON_END
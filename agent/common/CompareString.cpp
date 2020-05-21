#include "pch.h"

YAGENT_COMMON_BEGIN

/*
	2006.06.13
	������: �̵����� �Լ����� ���̸� ���߿� ����ϴ� ����� �򰥸��� �� �ƴϳ�?
	�����: �׷��� -- (������, ���� �̾��ϴ�..);

	�� �Լ��� �ɸ´� �̸��� �ο��ϰ� ���������� �ɸ´� �̸������� ����� ��������. 

	AhnCompareString ���� ������ AhnIsStartedSameNoCase�� �����ϰ�,
	AhnCompareString���� AhnIsStartedSameNoCase �� ȣ���ϵ��� �ߴ�.

*/

int		IsStartedSameNoCase(IN LPCTSTR lpStr1, IN LPCTSTR lpStr2)
{
	while( *lpStr1 && *lpStr2 )
	{
		if( _totupper(*lpStr1) != _totupper(*lpStr2) )
		{
			return (_totupper(*lpStr1) - _totupper(*lpStr2) );
		}
		
		lpStr1++;
		lpStr2++;
	}
	return 0;	
}
///////////////////////////////////////////////////////////////////////////////
// �� �Լ��� �� ���ڿ��� ª�� �ϳ��� ���ڿ� ���� ���� ������ ���ϴ� ���̴�.
// lstrcmp�ʹ� �ٸ� �Լ��̹Ƿ� ��뿡 �����ϱ� �ٶ�. ��ҹ��� ���е� ����.
// KimPro
// 2011/9/21 CompareString => CompareBeginningString���� �̸� ������.
// CompareString�� WIN32 API�� �����ϰ� �����Ǵ� �Լ����̴�.
///////////////////////////////////////////////////////////////////////////////
int		CompareBeginningString(IN LPCTSTR lpStr1, IN LPCTSTR lpStr2)
{
	// �� �Լ����ٴ� AhnIsStartedSameNoCase ����� �����մϴ�.
	return IsStartedSameNoCase(lpStr1, lpStr2);
}

YAGENT_COMMON_END
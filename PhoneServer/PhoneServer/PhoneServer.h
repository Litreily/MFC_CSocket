
// PhoneServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPhoneServerApp: 
// �йش����ʵ�֣������ PhoneServer.cpp
//

class CPhoneServerApp : public CWinApp
{
public:
	CPhoneServerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPhoneServerApp theApp;
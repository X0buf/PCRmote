
// PCRmote.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPCRmoteApp: 
// �йش����ʵ�֣������ PCRmote.cpp
//

class CPCRmoteApp : public CWinApp
{
public:
	CPCRmoteApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPCRmoteApp theApp;
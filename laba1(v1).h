#define NOMINMAX
// laba1(v1).h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#include <thread>
#include <mutex>
#include <vector>

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// Claba1v1App:
// � ���������� ������� ������ ��. laba1(v1).cpp
//

class Claba1v1App : public CWinApp
{
public:
	Claba1v1App();
	~Claba1v1App();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
private:
	std::thread Display;
};

extern Claba1v1App theApp;
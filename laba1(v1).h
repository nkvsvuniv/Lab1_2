#define NOMINMAX
// laba1(v1).h : главный файл заголовка для приложения PROJECT_NAME
//

#include <thread>
#include <mutex>
#include <vector>

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// Claba1v1App:
// О реализации данного класса см. laba1(v1).cpp
//

class Claba1v1App : public CWinApp
{
public:
	Claba1v1App();
	~Claba1v1App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
private:
	std::thread Display;
};

extern Claba1v1App theApp;
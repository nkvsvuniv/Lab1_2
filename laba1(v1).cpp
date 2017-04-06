
// laba1(v1).cpp : Определяет поведение классов для приложения.
//

#include "stdafx.h"
#include "laba1(v1).h"
#include "laba1(v1)Dlg.h"
#include "DataBase.h"
#include "Draw.h"
#include <fstream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

std::recursive_mutex glock;

// Claba1v1App

BEGIN_MESSAGE_MAP(Claba1v1App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// создание Claba1v1App

Claba1v1App::Claba1v1App()
{
	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
	
}



void animate()
{
	glutPostRedisplay();
}

void resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)width / (float)height, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Set the viewing position and orientation
	gluLookAt(
		0.0, 0.0, 20.0, // eye location
		0.0, 0.0, 0.0, // center location
		0.0, 1.0, 0.0); // up vector

	glTranslatef(0.0, 0.0, -1.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glRotatef(-20, 0.0, 0.0, 1.0);
}

// Единственный объект Claba1v1App

Claba1v1App theApp;

void DisplayMe()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glock.lock();
	DataBase* db = DataBase::getInstance();
	glock.unlock();

	for (auto &el : db->getProperties())
	{
		glock.lock();
		float scale = el.scale;
		unsigned int color = el.color;
		int posX = el.position[0];
		int posY = el.position[1];
		int posZ = el.position[2];
		float angleX = el.angleX;
		float angleY = el.angleY;
		float angleZ = el.angleZ;
		glock.unlock();
		if (el.shape == CUBE)
		{
			drawBox(scale, color, posX, posY, posZ, angleX, angleY, angleZ);
		}
		else
		if (el.shape == PYRAMID)
		{
			drawPyramid(scale, color, posX, posY, posZ, angleX, angleY, angleZ);
		}
		else{
			drawSphere(scale, color, posX, posY, posZ, angleX, angleY, angleZ);
		}
	}
	drawCoordinates();
	glutSwapBuffers();
}

// инициализация Claba1v1App

BOOL Claba1v1App::InitInstance()
{
	CWinApp::InitInstance();


	// Создать диспетчер оболочки, в случае, если диалоговое окно содержит
	// представление дерева оболочки или какие-либо его элементы управления.
	CShellManager *pShellManager = new CShellManager;

	// Активация визуального диспетчера "Классический Windows" для включения элементов управления MFC
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Стандартная инициализация
	// Если эти возможности не используются и необходимо уменьшить размер
	// конечного исполняемого файла, необходимо удалить из следующих
	// конкретных процедур инициализации, которые не требуются
	// Измените раздел реестра, в котором хранятся параметры
	// TODO: следует изменить эту строку на что-нибудь подходящее,
	// например на название организации
	SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));

	DataBase* db;
	try {
		db = DataBase::getInstance();
	}
	catch (std::exception& e)
	{
		std::ofstream fwrite("log.txt");
		fwrite << e.what();
		fwrite.flush();
		fwrite.close();
		return false;
	}

	
	
	

	Claba1v1Dlg dlg;
	

	m_pMainWnd = &dlg;
	
	Display = std::thread([&dlg](){
		int argc = 1;
		char* argv[1];
		argv[0] = "lab1(v1).exe";
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE);
		glutInitWindowSize(300, 300);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("Hello world :D");
		glutIdleFunc(animate);
		glutDisplayFunc(DisplayMe);
		glutReshapeFunc(resize);
		glutSpecialFunc(processSpecialKeys);
		
		init();
		
		glutMainLoop();
	});
	
	
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Введите код для обработки закрытия диалогового окна
		//  с помощью кнопки "ОК"
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Введите код для обработки закрытия диалогового окна
		//  с помощью кнопки "Отмена"
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Предупреждение. Не удалось создать диалоговое окно, поэтому работа приложения неожиданно завершена.\n");
		TRACE(traceAppMsg, 0, "Предупреждение. При использовании элементов управления MFC для диалогового окна невозможно #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	

	// Удалить диспетчер оболочки, созданный выше.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Поскольку диалоговое окно закрыто, возвратите значение FALSE, чтобы можно было выйти из
	//  приложения вместо запуска генератора сообщений приложения.
	//Display.join();
	
	return FALSE;
}


Claba1v1App::~Claba1v1App()
{
	glock.lock();
	DataBase *db = DataBase::getInstance();
	db->Save();
	glock.unlock();
	Display.join();

	//delete destroyer;
}


// laba1(v1)Dlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "laba1(v1).h"
#include "laba1(v1)Dlg.h"
#include "afxdialogex.h"
#include "DataBase.h"
#include <vector>
#include <string>
#include <time.h>

#include <Windows.h>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
extern std::recursive_mutex glock;

// ���������� ���� Claba1v1Dlg



Claba1v1Dlg::Claba1v1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Claba1v1Dlg::IDD, pParent)
	
{
	srand(time(0));
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Claba1v1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_CBString(pDX, IDC_COMBO1, lol);
	DDX_Control(pDX, Combo1, myComboBox1);
	DDX_Control(pDX, SLIDERAX, SliderAX);
	DDX_Control(pDX, SLIDERAY, SliderAY);
	DDX_Control(pDX, SLIDERAZ, SliderAZ);
	DDX_Control(pDX, SLIDERS, SliderS);
	DDX_Control(pDX, Combo2, myComboBox2);
	DDX_Control(pDX, EDIT, edit_name);
	DDX_Control(pDX, EDIT2, editX);
	DDX_Control(pDX, EDIT3, editY);
	DDX_Control(pDX, EDIT4, editZ);
}

BEGIN_MESSAGE_MAP(Claba1v1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Claba1v1Dlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(Combo1, &Claba1v1Dlg::OnCbnSelchangeCombo1)
	ON_WM_INITMENU()
	ON_NOTIFY(NM_CUSTOMDRAW, SLIDERAX, &Claba1v1Dlg::OnNMCustomdrawSliderax)
	ON_NOTIFY(NM_CUSTOMDRAW, SLIDERAY, &Claba1v1Dlg::OnNMCustomdrawSlideray)
	ON_NOTIFY(NM_CUSTOMDRAW, SLIDERAZ, &Claba1v1Dlg::OnNMCustomdrawSlideraz)
	ON_NOTIFY(NM_CUSTOMDRAW, SLIDERS, &Claba1v1Dlg::OnNMCustomdrawSliders)
	ON_BN_CLICKED(IDC_BUTTON1, &Claba1v1Dlg::OnBnClickedButton1)
	ON_EN_CHANGE(EDIT2, &Claba1v1Dlg::OnEnChangeEdit2)
	ON_EN_CHANGE(EDIT3, &Claba1v1Dlg::OnEnChangeEdit3)
	ON_EN_CHANGE(EDIT4, &Claba1v1Dlg::OnEnChangeEdit4)
END_MESSAGE_MAP()


// ����������� ��������� Claba1v1Dlg

BOOL Claba1v1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// ������ ������ ��� ����� ����������� ����.  ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// TODO: �������� �������������� �������������
	
	glock.lock();
	DataBase* db = DataBase::getInstance();
	current = 0;

	
	
	for (auto &el : db->diction)
	{
		myComboBox1.AddString(el.first.c_str());
	}

	myComboBox1.SetCurSel(0);

	myComboBox2.AddString(L"CUBE");
	myComboBox2.AddString(L"PYRAMID");
	myComboBox2.AddString(L"SPHERE");

	myComboBox2.SetCurSel(0);

	SliderAX.SetRangeMin(0, true);
	SliderAX.SetRangeMax(720, true);

	SliderAY.SetRangeMin(0, true);
	SliderAY.SetRangeMax(720, true);

	SliderAZ.SetRangeMin(0, true);
	SliderAZ.SetRangeMax(720, true);

	
	SliderS.SetRangeMin(1, true);
	SliderS.SetRangeMax(5, true);

	std::vector<Property> & curr = db->getProperties();
	if (!curr.empty())
	{
		SliderS.SetPos(curr[current].scale);
		SliderAX.SetPos(curr[current].angleX * 2);
		SliderAY.SetPos(curr[current].angleY * 2);
		SliderAZ.SetPos(curr[current].angleZ * 2);
		editX.SetWindowTextW(std::to_wstring(curr[current].position[0]).c_str());
		editY.SetWindowTextW(std::to_wstring(curr[current].position[1]).c_str());
		editZ.SetWindowTextW(std::to_wstring(curr[current].position[2]).c_str());
	}
	
	glock.unlock();
	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������.  ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void Claba1v1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR Claba1v1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Claba1v1Dlg::OnBnClickedOk()
{
	// TODO: �������� ���� ��� ����������� �����������
	
	
	CDialogEx::OnOK();
}


void Claba1v1Dlg::OnCbnSelchangeCombo1()
{
	// TODO: �������� ���� ��� ����������� �����������
	CString choise;
	myComboBox1.GetLBText(myComboBox1.GetCurSel(), choise);
	std::wstring str(choise.GetString());
	glock.lock();
	DataBase* db = DataBase::getInstance();
	current = db->diction[str];
	std::vector<Property> & curr = db->getProperties();
	if (!curr.empty()){
		SliderS.SetPos(curr[current].scale);
		SliderAX.SetPos(curr[current].angleX * 2);
		SliderAY.SetPos(curr[current].angleY * 2);
		SliderAZ.SetPos(curr[current].angleZ * 2);
		editX.SetWindowTextW(std::to_wstring(curr[current].position[0]).c_str());
		editY.SetWindowTextW(std::to_wstring(curr[current].position[1]).c_str());
		editZ.SetWindowTextW(std::to_wstring(curr[current].position[2]).c_str());
	}
	glock.unlock();
}




void Claba1v1Dlg::OnNMCustomdrawSliderax(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �������� ���� ��� ����������� �����������
	glock.lock();
	DataBase * db = DataBase::getInstance();
	if (!db->getProperties().empty())
		db->getProperties()[current].angleX = SliderAX.GetPos() / 2.0f;
	glock.unlock();
	*pResult = 0;
}


void Claba1v1Dlg::OnNMCustomdrawSlideray(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �������� ���� ��� ����������� �����������
	glock.lock();
	DataBase * db = DataBase::getInstance();
	if (!db->getProperties().empty())
		db->getProperties()[current].angleY = SliderAY.GetPos() / 2.0f;
	glock.unlock();
	*pResult = 0;
}


void Claba1v1Dlg::OnNMCustomdrawSlideraz(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �������� ���� ��� ����������� �����������
	glock.lock();
	DataBase * db = DataBase::getInstance();
	if (!db->getProperties().empty())
		db->getProperties()[current].angleZ = SliderAZ.GetPos() / 2.0f;
	glock.unlock();
	*pResult = 0;
}


void Claba1v1Dlg::OnNMCustomdrawSliders(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	glock.lock();
	DataBase * db = DataBase::getInstance();
	if (!db->getProperties().empty())
		db->getProperties()[current].scale = SliderS.GetPos();
	glock.unlock();
	// TODO: �������� ���� ��� ����������� �����������
	*pResult = 0;
}


void Claba1v1Dlg::OnBnClickedButton1()
{
	// TODO: �������� ���� ��� ����������� �����������
	CString name;
	edit_name.GetWindowText(name);
	std::wstring wstr = name.GetString();
	char buffer[42];
	int ret = wcstombs(buffer, wstr.c_str(), sizeof(buffer));
	if (ret == 42) buffer[41] = '\0';
	Property tmp;
	tmp.name = std::string(buffer);
	tmp.color = RGB(rand() % 200, rand() % 200, rand() % 200);
	tmp.shape = shapes(myComboBox2.GetCurSel());
	tmp.angleX = SliderAX.GetPos() / 2.0f;
	tmp.angleY = SliderAY.GetPos() / 2.0f;
	tmp.angleZ = SliderAZ.GetPos() / 2.0f;
	tmp.scale = SliderS.GetPos();
	tmp.added = true;
	tmp.deleted = false;
	glock.lock();
	DataBase * db = DataBase::getInstance();
	int last = db->getProperties().size();
	db->diction.insert(std::pair<std::wstring, int>(name.GetString(), last));
	db->getProperties().push_back(tmp);
	glock.unlock();

	myComboBox1.AddString(wstr.c_str());

	
}


void Claba1v1Dlg::OnEnChangeEdit2()
{
	// TODO:  ���� ��� ������� ���������� RICHEDIT, �� ������� ���������� �� �����
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  �������� ��� �������� ����������
	CString value;
	editX.GetWindowText(value);
	std::wstring wstr = value.GetString();
	int posX = _wtoi(wstr.c_str());
	glock.lock();
	DataBase* db = DataBase::getInstance();
	db->getProperties()[current].position[0] = posX;
	glock.unlock();
}


void Claba1v1Dlg::OnEnChangeEdit3()
{
	CString value;
	editY.GetWindowText(value);
	std::wstring wstr = value.GetString();
	int posY = _wtoi(wstr.c_str());
	glock.lock();
	DataBase* db = DataBase::getInstance();
	db->getProperties()[current].position[1] = posY;
	glock.unlock();
}


void Claba1v1Dlg::OnEnChangeEdit4()
{
	CString value;
	editZ.GetWindowText(value);
	std::wstring wstr = value.GetString();
	int posZ = _wtoi(wstr.c_str());
	glock.lock();
	DataBase* db = DataBase::getInstance();
	db->getProperties()[current].position[2] = posZ;
	glock.unlock();
}

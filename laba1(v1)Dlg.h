#define NOMINMAX
// laba1(v1)Dlg.h : файл заголовка
//
#include <GL/glut.h>
#include <mutex>

#pragma once


// диалоговое окно Claba1v1Dlg
class Claba1v1Dlg : public CDialogEx
{
// Создание

public:
	Claba1v1Dlg(CWnd* pParent = NULL);	// стандартный конструктор
	CComboBox myComboBox1;
	CComboBox myComboBox2;
	CSliderCtrl SliderAX;
	CSliderCtrl SliderAY;
	CSliderCtrl SliderAZ;
	CSliderCtrl SliderS;
	CEdit edit_name;
	CEdit editX;
	CEdit editY;
	CEdit editZ;
	
private: int current;
// Данные диалогового окна
	enum { IDD = IDD_LABA1V1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCombo1();
//	afx_msg void OnInitMenu(CMenu* pMenu);
//	CString lol;
//	afx_msg void OnNMCustomdrawSliderax(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnTRBNThumbPosChangingSliderax(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderax(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlideray(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlideraz(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliders(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
};
//
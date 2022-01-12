// RotationDialog.cpp: 구현 파일
//

#include "stdafx.h"
#include "OpenCVTest.h"
#include "RotationDialog.h"
#include "afxdialogex.h"
#include"OpenCVTestDlg.h"

// RotationDialog 대화 상자

IMPLEMENT_DYNAMIC(RotationDialog, CDialogEx)

RotationDialog::RotationDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_edit_value(0)
{

}

RotationDialog::~RotationDialog()
{
}

void RotationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_rotate_sldi);
	DDX_Control(pDX, IDC_EDIT1, m_rotateangle);
	DDX_Text(pDX, IDC_EDIT1, m_edit_value);
}


BEGIN_MESSAGE_MAP(RotationDialog, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &RotationDialog::OnEnChangeEdit1)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// RotationDialog 메시지 처리기


BOOL RotationDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	COpenCVTestDlg* pDlg = (COpenCVTestDlg*)AfxGetMainWnd();
	m_rotate_sldi.SetRange(0, 360);
	m_rotate_sldi.SetPos(0);
	m_rotate_sldi.SetLineSize(10);
	m_rotate_sldi.SetPageSize(10);
	pDlg->RotatingAngle = 0;
	int pos = m_rotate_sldi.GetPos();
	CString sPos;
	sPos.Format(_T("%d"), pos);
	m_rotateangle.SetWindowTextW(sPos);
	return TRUE;
}


void RotationDialog::OnEnChangeEdit1()
{
	CString sPos;
	m_rotateangle.GetWindowTextW(sPos);
	int fPos = _ttoi(sPos);
	fPos %= 360;
	m_rotate_sldi.SetPos(fPos);
	COpenCVTestDlg* pDlg = (COpenCVTestDlg*)AfxGetMainWnd();
	pDlg->RotatingAngle = fPos;
	pDlg->DialogRotation();
}


void RotationDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (IDC_SLIDER1 == pScrollBar->GetDlgCtrlID()) {
		int ipos = m_rotate_sldi.GetPos();
		ipos %= 360;
		CString sPos;
		sPos.Format(_T("%d"), ipos);
		m_rotateangle.SetWindowTextW(sPos);
		COpenCVTestDlg* pDlg = (COpenCVTestDlg*)AfxGetMainWnd();
		pDlg->RotatingAngle = ipos;
		pDlg->DialogRotation();
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

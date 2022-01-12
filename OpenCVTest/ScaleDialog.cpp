// ScaleDialog.cpp: 구현 파일
//

#include "stdafx.h"
#include "OpenCVTest.h"
#include "ScaleDialog.h"
#include "afxdialogex.h"
#include"OpenCVTestDlg.h"


// ScaleDialog 대화 상자

IMPLEMENT_DYNAMIC(ScaleDialog, CDialogEx)

ScaleDialog::ScaleDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
}

ScaleDialog::~ScaleDialog()
{
}

void ScaleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER2, m_scale_sld);
	DDX_Control(pDX, IDC_EDIT1, m_scale_edit);
	DDX_Control(pDX, IDC_SLIDER1, m_scalex_sld);
	DDX_Control(pDX, IDC_SLIDER3, m_scaley_sld);
	DDX_Control(pDX, IDC_EDIT2, m_scalex_edit);
	DDX_Control(pDX, IDC_EDIT3, m_scaley_edit);
	DDX_Control(pDX, IDC_EDIT4, m_totalx);
	DDX_Control(pDX, IDC_EDIT5, m_totaly);
}


BEGIN_MESSAGE_MAP(ScaleDialog, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT1, &ScaleDialog::OnEnChangeEdit1)
	ON_WM_CLOSE()
//	ON_WM_NCDESTROY()
ON_EN_CHANGE(IDC_EDIT2, &ScaleDialog::OnEnChangeEdit2)
ON_EN_CHANGE(IDC_EDIT3, &ScaleDialog::OnEnChangeEdit3)
END_MESSAGE_MAP()


// ScaleDialog 메시지 처리기


BOOL ScaleDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	COpenCVTestDlg* pDlg = (COpenCVTestDlg*)AfxGetMainWnd();
	m_scale_sld.SetRange(1, 20);
	m_scale_sld.SetPos(10);
	m_scalex_sld.SetRange(1, 20);
	m_scalex_sld.SetPos(10);
	m_scaley_sld.SetRange(1, 20);
	m_scaley_sld.SetPos(10);
	pDlg->Cur_Scale_total = 1.0;
	pDlg->Cur_scale_x = 1.0;
	pDlg->Cur_scale_y = 1.0;

	m_scale_sld.SetLineSize(1);
	m_scale_sld.SetPageSize(1);
	m_scalex_sld.SetLineSize(1);
	m_scalex_sld.SetPageSize(1);
	m_scaley_sld.SetLineSize(1);
	m_scaley_sld.SetPageSize(1);
	int pos = m_scale_sld.GetPos();
	CString sPos;
	sPos.Format(_T("%.1f"), (double)pos / 10);
	m_scale_edit.SetWindowTextW(sPos);
	pos = m_scalex_sld.GetPos();
	sPos.Format(_T("%.1f"), (double)pos / 10);
	m_scalex_edit.SetWindowTextW(sPos);
	pos = m_scaley_sld.GetPos();
	sPos.Format(_T("%.1f"), (double)pos / 10);
	m_scaley_edit.SetWindowTextW(sPos);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void ScaleDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (IDC_SLIDER2 == pScrollBar->GetDlgCtrlID()) {
		int ipos = m_scale_sld.GetPos();
		CString sPos;
		sPos.Format(_T("%.1f"), (double)ipos / (double)10);
		m_scale_edit.SetWindowTextW(sPos);
		COpenCVTestDlg* pDlg = (COpenCVTestDlg*)AfxGetMainWnd();
		pDlg->Cur_Scale_total = (double)ipos / (double)10;
		pDlg->DialogScaleTotal();
		CalculateX();
		CalculateY();
	}
	if (IDC_SLIDER1 == pScrollBar->GetDlgCtrlID()) {
		int ipos = m_scalex_sld.GetPos();
		CString sPos;
		sPos.Format(_T("%.1f"), (double)ipos / (double)10);
		m_scalex_edit.SetWindowTextW(sPos);
		COpenCVTestDlg* pDlg = (COpenCVTestDlg*)AfxGetMainWnd();
		pDlg->Cur_scale_x = (double)ipos / (double)10;
		pDlg->DialogScaleTotal();
		CalculateX();
		CalculateY();
	}
	if (IDC_SLIDER3 == pScrollBar->GetDlgCtrlID()) {
		int ipos = m_scaley_sld.GetPos();
		CString sPos;
		sPos.Format(_T("%.1f"), (double)ipos / (double)10);
		m_scaley_edit.SetWindowTextW(sPos);
		COpenCVTestDlg* pDlg = (COpenCVTestDlg*)AfxGetMainWnd();
		pDlg->Cur_scale_y = (double)ipos / (double)10;
		pDlg->DialogScaleTotal();
		CalculateX();
		CalculateY();
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void ScaleDialog::OnEnChangeEdit1()
{
	CString sPos;
	m_scale_edit.GetWindowTextW(sPos);
	float fPos = _tstof(sPos);
	m_scale_sld.SetPos(10*fPos);
	COpenCVTestDlg* pDlg = (COpenCVTestDlg*)AfxGetMainWnd();
	pDlg->Cur_Scale_total = fPos;
	pDlg->DialogScaleTotal();
	CalculateX();
	CalculateY();
}


void ScaleDialog::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
	COpenCVTestDlg* pDlg = (COpenCVTestDlg*)AfxGetMainWnd();
	pDlg->m_scale_dlg = nullptr;
	DestroyWindow();
}


//void ScaleDialog::OnNcDestroy()
//{
//	CDialogEx::OnNcDestroy();
//
//	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//}


void ScaleDialog::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	COpenCVTestDlg* pDlg = (COpenCVTestDlg*)AfxGetMainWnd();
	pDlg->m_scale_dlg = nullptr;
	CDialogEx::PostNcDestroy();
}


void ScaleDialog::OnEnChangeEdit2()
{
	CString sPos;
	m_scalex_edit.GetWindowTextW(sPos);
	float fPos = _tstof(sPos);
	m_scalex_sld.SetPos(10 * fPos);
	COpenCVTestDlg* pDlg = (COpenCVTestDlg*)AfxGetMainWnd();
	pDlg->Cur_scale_x = fPos;
	pDlg->DialogScaleTotal();
	CalculateX();
	CalculateY();
}

void ScaleDialog::CalculateX() {
	COpenCVTestDlg* pDlg = (COpenCVTestDlg*)AfxGetMainWnd();
	double fPos = pDlg->Cur_Scale_total * pDlg->Cur_scale_x;
	CString str;
	str.Format(_T("%.2f"), fPos);
	m_totalx.SetWindowTextW(str);
}
void ScaleDialog::CalculateY() {
	COpenCVTestDlg* pDlg = (COpenCVTestDlg*)AfxGetMainWnd();
	double fPos = pDlg->Cur_Scale_total * pDlg->Cur_scale_y;
	CString str;
	str.Format(_T("%.2f"), fPos);
	m_totaly.SetWindowTextW(str);
}
void ScaleDialog::OnEnChangeEdit3()
{
	CString sPos;
	m_scaley_edit.GetWindowTextW(sPos);
	float fPos = _tstof(sPos);
	m_scaley_sld.SetPos(10 * fPos);
	COpenCVTestDlg* pDlg = (COpenCVTestDlg*)AfxGetMainWnd();
	pDlg->Cur_scale_y= fPos;
	pDlg->DialogScaleTotal();
	CalculateX();
	CalculateY();
}

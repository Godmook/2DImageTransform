
// OpenCVTestDlg.cpp : implementation file
//
#include "stdafx.h"
#include "OpenCVTest.h"
#include "OpenCVTestDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// COpenCVTestDlg dialog
COpenCVTestDlg::COpenCVTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OPENCVTEST_DIALOG, pParent)
	, radio_pos(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void COpenCVTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST5, image_listbox);
	DDX_Control(pDX, IDC_COMBO1, Image_combo);
	DDX_Control(pDX, IDC_MFCBUTTON1, m_test1);
	DDX_Control(pDX, IDC_MFCBUTTON2, m_trans);
	DDX_Control(pDX, IDC_MFCBUTTON5, m_save);
	DDX_Control(pDX, IDC_MFCBUTTON3, m_load);
	DDX_Control(pDX, IDC_MFCBUTTON4, m_camera);
	DDX_Control(pDX, IDC_MFCBUTTON6, m_transformimage);
	DDX_Control(pDX, IDC_MFCBUTTON7, m_curimage);
	DDX_Control(pDX, IDC_MFCBUTTON8, m_transexample);
	DDX_Control(pDX, IDC_MFCBUTTON9, m_transformed_image);
	DDX_Control(pDX, IDC_MFCBUTTON10, m_select);
	DDX_Control(pDX, IDC_MFCBUTTON11, m_explain);
	DDX_Control(pDX, IDC_MFCBUTTON12, m_trans_before);
	DDX_Control(pDX, IDC_MFCBUTTON13, m_trans_after);
	DDX_Control(pDX, IDC_MFCBUTTON14, m_title);
	DDX_Radio(pDX, IDC_RADIO1, radio_pos);
	DDX_Control(pDX, IDC_MFCBUTTON15, m_capture);
	DDX_Control(pDX, IDC_MFCBUTTON16, m_transorigin);
	DDX_Control(pDX, IDC_MFCBUTTON17, m_selectorigin);
	DDX_Control(pDX, IDC_COMBO2, m_interpolation);
	DDX_Control(pDX, IDC_MFCBUTTON18, m_beonhwan);
	DDX_Control(pDX, IDC_MFCBUTTON19, m_interpolate);
}
BEGIN_MESSAGE_MAP(COpenCVTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_NCPAINT()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_CBN_SELCHANGE(IDC_COMBO1, &COpenCVTestDlg::OnCbnSelchangeCombo1)
	ON_LBN_SELCHANGE(IDC_LIST5, &COpenCVTestDlg::OnLbnSelchangeList5)
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_MFCBUTTON1, &COpenCVTestDlg::OnBnClickedMfcbutton1)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &COpenCVTestDlg::OnBnClickedMfcbutton2)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_MFCBUTTON5, &COpenCVTestDlg::OnBnClickedMfcbutton5)
	ON_BN_CLICKED(IDC_MFCBUTTON3, &COpenCVTestDlg::OnBnClickedMfcbutton3)
	ON_BN_CLICKED(IDC_MFCBUTTON4, &COpenCVTestDlg::OnBnClickedMfcbutton4)
	ON_BN_CLICKED(IDC_MFCBUTTON10, &COpenCVTestDlg::OnBnClickedMfcbutton10)
	ON_BN_CLICKED(IDC_RADIO3, &COpenCVTestDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO1, &COpenCVTestDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_MFCBUTTON15, &COpenCVTestDlg::OnBnClickedMfcbutton15)
	ON_BN_CLICKED(IDC_MFCBUTTON16, &COpenCVTestDlg::OnBnClickedMfcbutton16)
	ON_BN_CLICKED(IDC_MFCBUTTON17, &COpenCVTestDlg::OnBnClickedMfcbutton17)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()
// COpenCVTestDlg message handlers

Mat COpenCVTestDlg::DoPadding(Mat src) {
	Mat res;
	int x = src.cols;
	int y = src.rows;
	int padding = 0;
	if (src.type() != CV_8UC4)
	{
		padding = 4 - (x % 4);
		if (padding == 4)
			padding = 0;
	}
	if (padding > 0 || src.isContinuous() == false)
	{
		cv::copyMakeBorder(src, res, 0, 0, 0, padding, cv::BORDER_CONSTANT, 0);
	}
	else
	{
		res = src;
	}
	return res;
}
void COpenCVTestDlg::DrawPictrue(int nID, Mat a) {
	BITMAPINFO* m_bit = NULL;
	RECT r;
	GetDlgItem(nID)->GetClientRect(&r);
	float fImageRatio = float(a.cols) / float(a.rows);
	float fRectRatio = float(r.right) / float(r.bottom);
	float fScaleFactor;
	if (fImageRatio < fRectRatio) {
		fScaleFactor = float(r.bottom) / float(a.rows);
		int rightWithRatio = a.cols * fScaleFactor;
		float halfOfDif = ((float)r.right - (float)rightWithRatio) / (float)2;
		r.left = halfOfDif;
		r.right = rightWithRatio;
	}
	else {
		fScaleFactor = float(r.right) / float(a.cols);
		int bottomWithRatio = a.rows * fScaleFactor;
		float halfOfDif = ((float)r.bottom - (float)bottomWithRatio) / (float)2;
		r.top = halfOfDif;
		r.bottom = bottomWithRatio;
	}
	m_bit = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO)];
	m_bit->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_bit->bmiHeader.biPlanes = 1;
	m_bit->bmiHeader.biBitCount = a.channels() * 8;
	m_bit->bmiHeader.biCompression = BI_RGB;
	m_bit->bmiHeader.biSizeImage = 0;
	m_bit->bmiHeader.biXPelsPerMeter = 0;
	m_bit->bmiHeader.biYPelsPerMeter = 0;
	m_bit->bmiHeader.biClrUsed = 0;
	m_bit->bmiHeader.biClrImportant = 0;
	m_bit->bmiHeader.biWidth = a.cols;
	m_bit->bmiHeader.biHeight = -a.rows;
	CClientDC dc(GetDlgItem(nID));
	SetStretchBltMode(dc.GetSafeHdc(), COLORONCOLOR);
	StretchDIBits(dc.GetSafeHdc(), r.left, r.top, r.right, r.bottom, 0, 0, a.cols, a.rows, a.data, m_bit, DIB_RGB_COLORS, SRCCOPY);
	
}
/////////////////////////////////////////////////////////////////////////
/// 다이아로그 초기 설정
/////////////////////////////////////////////////////////////////////////

BOOL COpenCVTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Cur_num = 0;
	CPngImage cButtonImg1;
	CBitmap bit1;
	example_mesh = TRUE;
	/*
	Png resource 넣는 부분 
	CPngImage에 리소스를 넣고 CBitmap으로 붙인다. 
	버튼에 붙인후에 CBitmap과 CPngImage에 DeleteObject를 안하면 문제 발생하므로
	나중에 수정하더라도 DeleteObject를 할 것

	주의 함수로 만들수 없으므로 함수화 X -> CMFCButton은 복사생성자가 허용이 되어 있지 않으므로 CMFCButton에 
	대한 정보를 가지고 올 수 없음.
	*/

	//버튼 붙이기 시작
	cButtonImg1.Load(IDB_PNG4, nullptr);
	bit1.Attach(cButtonImg1.Detach());
	m_test1.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_test1.m_bTransparent = TRUE;    // 투명도 설정
	m_test1.m_bDrawFocus = FALSE;
	m_test1.SetImage(bit1);
	m_test1.SetWindowText(L"");
	m_test1.SetMouseCursorHand();
	bit1.DeleteObject();
	cButtonImg1.DeleteObject();
	//버튼 붙이기 종료

	//이미지 변환 글자 이미지 넣기
	cButtonImg1.Load(IDB_PNG6, nullptr);
	bit1.Attach(cButtonImg1.Detach());
	m_trans.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_trans.m_bTransparent = TRUE;    // 투명도 설정
	m_trans.m_bDrawFocus = FALSE;
	m_trans.SetImage(bit1);
	m_trans.SetWindowText(L"");
	m_trans.SetMouseCursorHand();
	bit1.DeleteObject();
	cButtonImg1.DeleteObject();

	//저장 글자 이미지 넣기
	cButtonImg1.Load(IDB_PNG5, nullptr);
	bit1.Attach(cButtonImg1.Detach());
	m_save.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_save.m_bTransparent = TRUE;    // 투명도 설정
	m_save.m_bDrawFocus = FALSE;
	m_save.SetImage(bit1);
	m_save.SetWindowText(L"");
	m_save.SetMouseCursorHand();
	bit1.DeleteObject();
	cButtonImg1.DeleteObject();

	//이미지 로드라는 글자 이미지 넣기
	cButtonImg1.Load(IDB_PNG3, nullptr);
	bit1.Attach(cButtonImg1.Detach());
	m_load.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_load.m_bTransparent = TRUE;    // 투명도 설정
	m_load.m_bDrawFocus = FALSE;
	m_load.SetImage(bit1);
	m_load.SetWindowText(L"");
	m_load.SetMouseCursorHand();
	bit1.DeleteObject();
	cButtonImg1.DeleteObject();

	//카메라 글자 이미지 넣기
	cButtonImg1.Load(IDB_PNG1, nullptr);
	bit1.Attach(cButtonImg1.Detach());
	m_camera.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_camera.m_bTransparent = TRUE;    // 투명도 설정
	m_camera.m_bDrawFocus = FALSE;
	m_camera.SetImage(bit1);
	m_camera.SetWindowText(L"");
	m_camera.SetMouseCursorHand();
	bit1.DeleteObject();
	cButtonImg1.DeleteObject();

	//변환 이미지라는 글자 이미지 넣기
	cButtonImg1.Load(IDB_PNG7, nullptr);
	bit1.Attach(cButtonImg1.Detach());
	m_transformimage.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_transformimage.m_bTransparent = TRUE;    // 투명도 설정
	m_transformimage.m_bDrawFocus = FALSE;
	m_transformimage.SetImage(bit1);
	m_transformimage.SetWindowText(L"");
	bit1.DeleteObject();
	cButtonImg1.DeleteObject();

	//현재 이미지라는 글자 이미지 넣기
	cButtonImg1.Load(IDB_PNG2, nullptr);
	bit1.Attach(cButtonImg1.Detach());
	m_curimage.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_curimage.m_bTransparent = TRUE;    // 투명도 설정
	m_curimage.m_bDrawFocus = FALSE;
	m_curimage.SetImage(bit1);
	m_curimage.SetWindowText(L"");
	bit1.DeleteObject();
	cButtonImg1.DeleteObject();

	//변환 예시라는 글자 이미지 넣기
	cButtonImg1.Load(IDB_PNG8, nullptr);
	bit1.Attach(cButtonImg1.Detach());
	m_transexample.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_transexample.m_bTransparent = TRUE;    // 투명도 설정
	m_transexample.m_bDrawFocus = FALSE;
	m_transexample.SetImage(bit1);
	m_transexample.SetWindowText(L"");
	bit1.DeleteObject();
	cButtonImg1.DeleteObject();

	//변환된 이미지라는 글자 이미지 넣기
	cButtonImg1.Load(IDB_PNG9, nullptr);
	bit1.Attach(cButtonImg1.Detach());
	m_transformed_image.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_transformed_image.m_bTransparent = TRUE;    // 투명도 설정
	m_transformed_image.m_bDrawFocus = FALSE;
	m_transformed_image.SetImage(bit1);
	m_transformed_image.SetWindowText(L"");
	bit1.DeleteObject();
	cButtonImg1.DeleteObject();

	//이미지 선택이라는 글자 이미지 넣기
	cButtonImg1.Load(IDB_PNG10, nullptr);
	bit1.Attach(cButtonImg1.Detach());
	m_select.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_select.m_bTransparent = TRUE;    // 투명도 설정
	m_select.m_bDrawFocus = FALSE;
	m_select.SetImage(bit1);
	m_select.SetWindowText(L"");
	m_select.SetMouseCursorHand();
	bit1.DeleteObject();
	cButtonImg1.DeleteObject();

	//설명에 대한 정보 적기
	cButtonImg1.Load(IDB_PNG11, nullptr);
	bit1.Attach(cButtonImg1.Detach());
	m_explain.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_explain.m_bTransparent = TRUE;    // 투명도 설정
	m_explain.m_bDrawFocus = FALSE;
	//m_explain.SetImage(bit1);
	m_explain.SetWindowText(L"");
	bit1.DeleteObject();
	cButtonImg1.DeleteObject();

	//변환 전 이라는 글자 이미지 넣기
	cButtonImg1.Load(IDB_PNG12, nullptr);
	bit1.Attach(cButtonImg1.Detach());
	m_trans_before.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_trans_before.m_bTransparent = TRUE;    // 투명도 설정
	m_trans_before.m_bDrawFocus = FALSE;
	m_trans_before.SetImage(bit1);
	m_trans_before.SetWindowText(L"");
	bit1.DeleteObject();
	cButtonImg1.DeleteObject();

	//변환 후 라는 글자 이미지 넣기
	cButtonImg1.Load(IDB_PNG13, nullptr);
	bit1.Attach(cButtonImg1.Detach());
	m_trans_after.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_trans_after.m_bTransparent = TRUE;    // 투명도 설정
	m_trans_after.m_bDrawFocus = FALSE;
	m_trans_after.SetImage(bit1);
	m_trans_after.SetWindowText(L"");
	bit1.DeleteObject();
	cButtonImg1.DeleteObject();

	//Title 바 이미지 넣기
	cButtonImg1.Load(IDB_PNG14, nullptr);
	bit1.Attach(cButtonImg1.Detach());
	m_title.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_title.m_bTransparent = TRUE;    // 투명도 설정
	m_title.m_bDrawFocus = FALSE;
	m_title.SetImage(bit1);
	m_title.SetWindowText(L"");
	bit1.DeleteObject();
	cButtonImg1.DeleteObject();

	//캡처버튼 만들기
	cButtonImg1.Load(IDB_PNG20, nullptr);
	bit1.Attach(cButtonImg1.Detach());
	m_capture.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_capture.m_bTransparent = TRUE;    // 투명도 설정
	m_capture.m_bDrawFocus = FALSE;
	m_capture.SetImage(bit1);
	m_capture.SetWindowText(L"");
	m_capture.SetMouseCursorHand();
	bit1.DeleteObject();
	cButtonImg1.DeleteObject();
	GetDlgItem(IDC_MFCBUTTON15)->ShowWindow(SW_HIDE);

	//원본 이미지 버튼
	cButtonImg1.Load(IDB_PNG4, nullptr);
	bit1.Attach(cButtonImg1.Detach());
	m_transorigin.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_transorigin.m_bTransparent = TRUE;    // 투명도 설정
	m_transorigin.m_bDrawFocus = FALSE;
	m_transorigin.SetImage(bit1);
	m_transorigin.SetWindowText(L"");
	m_transorigin.SetMouseCursorHand();
	bit1.DeleteObject();
	cButtonImg1.DeleteObject();

	//원본 이미지 버튼
	cButtonImg1.Load(IDB_PNG4, nullptr);
	bit1.Attach(cButtonImg1.Detach());
	m_selectorigin.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_selectorigin.m_bTransparent = TRUE;    // 투명도 설정
	m_selectorigin.m_bDrawFocus = FALSE;
	m_selectorigin.SetImage(bit1);
	m_selectorigin.SetWindowText(L"");
	m_selectorigin.SetMouseCursorHand();
	bit1.DeleteObject();
	cButtonImg1.DeleteObject();

	//보간법 버튼
	cButtonImg1.Load(IDB_PNG22, nullptr);
	bit1.Attach(cButtonImg1.Detach());
	m_interpolate.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_interpolate.m_bTransparent = TRUE;    // 투명도 설정
	m_interpolate.m_bDrawFocus = FALSE;
	m_interpolate.SetImage(bit1);
	m_interpolate.SetWindowText(L"");
	bit1.DeleteObject();
	cButtonImg1.DeleteObject();

	//변환 버튼
	cButtonImg1.Load(IDB_PNG23, nullptr);
	bit1.Attach(cButtonImg1.Detach());
	m_beonhwan.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_beonhwan.m_bTransparent = TRUE;    // 투명도 설정
	m_beonhwan.m_bDrawFocus = FALSE;
	m_beonhwan.SetImage(bit1);
	m_beonhwan.SetWindowText(L"");
	bit1.DeleteObject();
	cButtonImg1.DeleteObject();

	//캡처 버튼 처음에 안보이게 하기
	GetDlgItem(IDC_MFCBUTTON19)->ShowWindow(SW_HIDE);


	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	resetImageData();
	Image_combo.AddString(L"     ");
	Make_Transform_combo();
	Image_combo.SetCurSel(0);
	Make_Interpolation_combo();

	///////////////////////////////////////////
	//리소스 Png 파일 Mat로 바꾸는 부분 
	//////////////////////////////
	Mat inputfirst;
	CPngImage before;
	before.Load(IDB_PNG24, nullptr);
	CBitmap bit_before;
	bit_before.Attach(before.Detach());
	BITMAP bmap;
	bit_before.GetBitmap(&bmap);
	int Width = bmap.bmWidth;
	int Height = bmap.bmHeight;
	int nChannels = bmap.bmBitsPixel == 1 ? 1 : bmap.bmBitsPixel / 8;
	int depth = bmap.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
	BYTE* pBuffer = new BYTE[bmap.bmHeight * bmap.bmWidth * nChannels];
	GetBitmapBits((HBITMAP)bit_before.GetSafeHandle(), bmap.bmHeight* bmap.bmWidth* nChannels, pBuffer);
	cv::Mat Channel4Mat(bmap.bmHeight, bmap.bmWidth, CV_MAKETYPE(depth, nChannels));
	memcpy(Channel4Mat.data, pBuffer, bmap.bmHeight* bmap.bmWidth* nChannels);
	cv::Mat Channel3Mat(bmap.bmHeight, bmap.bmWidth* nChannels, CV_8UC3);
	cvtColor(Channel4Mat, Channel3Mat, CV_BGRA2BGR);
	Channel3Mat.copyTo(inputfirst);
	delete[] pBuffer;
	pBuffer = NULL;
	bit_before.DeleteObject();
	before.DeleteObject();
	Channel3Mat.deallocate();

	inputImageData(inputfirst, 1.0, 1.0, L"Original", "Original", Cur_num);
	GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);
	DrawPictrue(IDC_PC_VIEW, Image_processing.at(Cur_num));
	RefreshListBox();
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void COpenCVTestDlg::Make_Interpolation_combo() {
	m_interpolation.AddString(_T("NEAREST"));
	m_interpolation.AddString(_T("LINEAR"));
	m_interpolation.AddString(_T("CUBIC"));
	m_interpolation.AddString(_T("AREA"));
	m_interpolation.AddString(_T("LANCZOS4"));
	m_interpolation.SetCurSel(0);
}
void COpenCVTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
void COpenCVTestDlg::Make_Transform_combo() {
	Image_combo.AddString(_T("Scaling"));
	Image_combo.AddString(_T("Translation"));
	Image_combo.AddString(_T("Rotation"));
	Image_combo.AddString(_T("Affine"));
	Image_combo.AddString(_T("Perspective"));
}
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COpenCVTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COpenCVTestDlg::RefreshListBox() {
	image_listbox.ResetContent();
	vector<CString>::iterator iter;
	for (iter = Image_name.begin(); iter != Image_name.end(); iter++) {
		CString tmp;
		CString num;
		num.Format(_T("%d"), image_listbox.GetCount());
		tmp += num;
		tmp += L". ";
		tmp += *iter;
		image_listbox.AddString(tmp);
	}
	UpdateWindow();
}
void COpenCVTestDlg::OnNcPaint()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnNcPaint()을(를) 호출하지 마십시오.
	//DrawImage();
}

void COpenCVTestDlg::resetImageData() {
	Image_processing.clear();
	scale_x.clear();
	scale_y.clear();
	Image_name.clear();
	Image_translation_name.clear();
	image_source_num.clear();
}
void COpenCVTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	Mat tmp;
	capture->read(tmp);
	GetDlgItem(IDC_RADIO3)->EnableWindow(true);
	mat_temp = DoPadding(tmp);
	DrawPictrue(IDC_PC_VIEW,mat_temp);
	CDialogEx::OnTimer(nIDEvent);
}
void COpenCVTestDlg::TranslationMouseCallBack(int event, int x, int y, int flags, void* param) {
	COpenCVTestDlg* self = static_cast<COpenCVTestDlg*>(param);
	self->doTraslation(event, x, y, flags);
}
void COpenCVTestDlg::AffineMouseCallBack(int event, int x, int y, int flags, void* param) {
	COpenCVTestDlg* self = static_cast<COpenCVTestDlg*>(param);
	self->doAffine(event, x, y, flags);
}
void COpenCVTestDlg::PerspectiveMouseCallBack(int event, int x, int y, int flags, void* param) {
	COpenCVTestDlg* self = static_cast<COpenCVTestDlg*>(param);
	self->doPerspective(event, x, y, flags);
}
void COpenCVTestDlg::doPerspective(int event, int x, int y, int flags) {
	int num = -1;
	if (event == EVENT_LBUTTONDOWN && flags == EVENT_FLAG_LBUTTON) {
		st = Point(x, y);
		Perspective_image_src.copyTo(Perspective_image_tmp);
		line(Perspective_image_tmp, Point(10, 10), Point(Perspective_image_tmp.cols - 10, 10), Scalar(0, 0, 255), 2, 8, 0);
		line(Perspective_image_tmp, Point(Perspective_image_tmp.cols - 10, Perspective_image_tmp.rows - 10), Point(Perspective_image_tmp.cols - 10, 10), Scalar(0, 0, 255), 2, 8, 0);
		line(Perspective_image_tmp, Point(Perspective_image_tmp.cols - 10, Perspective_image_tmp.rows - 10), Point(10, Perspective_image_tmp.rows - 10), Scalar(0, 0, 255), 2, 8, 0);
		line(Perspective_image_tmp, Point(10, 10), Point(10, Perspective_image_tmp.rows - 10), Scalar(0, 0, 255), 2, 8, 0);
		circle(Perspective_image_tmp, Point(10, 10), 10, Scalar(0, 0, 255), -1, 8, 0);
		cv::putText(Perspective_image_tmp, to_string(1), Point(4, 15), 2, 0.7, Scalar::all(255));
		circle(Perspective_image_tmp, Point(Perspective_image_tmp.cols - 10, 10), 10, Scalar(0, 0, 255), -1, 8, 0);
		cv::putText(Perspective_image_tmp, to_string(2), Point(Perspective_image_tmp.cols - 16, 15), 2, 0.7, Scalar::all(255));
		circle(Perspective_image_tmp, Point(Perspective_image_tmp.cols - 10, Perspective_image_tmp.rows - 10), 10, Scalar(0, 0, 255), -1, 8, 0);
		cv::putText(Perspective_image_tmp, to_string(3), Point(Perspective_image_tmp.cols - 16, Perspective_image_tmp.rows - 5), 2, 0.7, Scalar::all(255));
		circle(Perspective_image_tmp, Point(10, Perspective_image_tmp.rows - 10), 10, Scalar(0, 0, 255), -1, 8, 0);
		cv::putText(Perspective_image_tmp, to_string(4), Point(4, Perspective_image_tmp.rows - 5), 2, 0.7, Scalar::all(255));
		if (affine_num < 4) {
			src_pt.push_back(Point(x, y));
			affine_num++;
		}
		if (!src_pt.empty()) {
			for (int i = 0; i < src_pt.size() - 1; i++) {
				line(Perspective_image_tmp, src_pt.at(i), src_pt.at(i + 1), Scalar(255, 0, 0), 2, 8, 0);
			}
			if (affine_num == 4) {
				line(Perspective_image_tmp, src_pt.at(0), src_pt.at(3), Scalar(255, 0, 0), 2, 8, 0);
			}
		}
		if (!src_pt.empty()) {
			for (int i = 0; i < src_pt.size(); i++) {
				circle(Perspective_image_tmp, src_pt.at(i), 10, Scalar(255, 0, 0), -1, 8, 0);
				cv::putText(Perspective_image_tmp, to_string(i + 1), Point(src_pt.at(i).x - 6, src_pt.at(i).y + 5), 2, 0.7, Scalar::all(255));
			}
		}
		imshow("Perspective", Perspective_image_tmp);
		if (affine_num == 4) {
			Mat Perspective_image_result;
			vector<Point2f> per_dst;
			per_dst.push_back(Point(0, 0));
			per_dst.push_back(Point(Perspective_image_src.cols - 1, 0));
			per_dst.push_back(Point(Perspective_image_src.cols - 1, Perspective_image_src.rows - 1));
			per_dst.push_back(Point(0, Perspective_image_src.rows - 1));
			Mat affinematrix = getPerspectiveTransform(src_pt, per_dst);
			warpPerspective(Perspective_image_src, Perspective_image_result, affinematrix, Perspective_image_src.size());
			imshow("Perspective Prediction", Perspective_image_result);
		}
	}
	if (event == EVENT_MOUSEMOVE && flags == EVENT_FLAG_LBUTTON) {
		Perspective_image_src.copyTo(Perspective_image_tmp);
		line(Perspective_image_tmp, Point(10, 10), Point(Perspective_image_tmp.cols - 10, 10), Scalar(0, 0, 255), 2, 8, 0);
		line(Perspective_image_tmp, Point(Perspective_image_tmp.cols - 10, Perspective_image_tmp.rows - 10), Point(Perspective_image_tmp.cols - 10, 10), Scalar(0, 0, 255), 2, 8, 0);
		line(Perspective_image_tmp, Point(Perspective_image_tmp.cols - 10, Perspective_image_tmp.rows - 10), Point(10, Perspective_image_tmp.rows - 10), Scalar(0, 0, 255), 2, 8, 0);
		line(Perspective_image_tmp, Point(10, 10), Point(10, Perspective_image_tmp.rows - 10), Scalar(0, 0, 255), 2, 8, 0);
		circle(Perspective_image_tmp, Point(10, 10), 10, Scalar(0, 0, 255), -1, 8, 0);
		cv::putText(Perspective_image_tmp, to_string(1), Point(4, 15), 2, 0.7, Scalar::all(255));
		circle(Perspective_image_tmp, Point(Perspective_image_tmp.cols - 10, 10), 10, Scalar(0, 0, 255), -1, 8, 0);
		cv::putText(Perspective_image_tmp, to_string(2), Point(Perspective_image_tmp.cols - 16, 15), 2, 0.7, Scalar::all(255));
		circle(Perspective_image_tmp, Point(Perspective_image_tmp.cols - 10, Perspective_image_tmp.rows - 10), 10, Scalar(0, 0, 255), -1, 8, 0);
		cv::putText(Perspective_image_tmp, to_string(3), Point(Perspective_image_tmp.cols - 16, Perspective_image_tmp.rows - 5), 2, 0.7, Scalar::all(255));
		circle(Perspective_image_tmp, Point(10, Perspective_image_tmp.rows - 10), 10, Scalar(0, 0, 255), -1, 8, 0);
		cv::putText(Perspective_image_tmp, to_string(4), Point(4, Perspective_image_tmp.rows - 5), 2, 0.7, Scalar::all(255));
		ed = Point(x, y);
		if (!src_pt.empty()) {
			for (int i = src_pt.size() - 1; i > -1; i--) {
				if (getDist(src_pt.at(i), ed) < 15) {
					num = i;
					break;
				}
			}
		}
		if (!src_pt.empty()) {
			for (int i = 0; i < src_pt.size(); i++) {
				if (i==num) {
					src_pt.at(i).x += ed.x - st.x;
					src_pt.at(i).y += ed.y - st.y;
				}
			}
		}
		if (!src_pt.empty()) {
			for (int i = 0; i < src_pt.size() - 1; i++) {
				line(Perspective_image_tmp, src_pt.at(i), src_pt.at(i + 1), Scalar(255, 0, 0), 2, 8, 0);
			}
			if (affine_num == 4) {
				line(Perspective_image_tmp, src_pt.at(0), src_pt.at(3), Scalar(255, 0, 0), 2, 8, 0);
			}
		}
		if (!src_pt.empty()) {
			for (int i = 0; i < src_pt.size(); i++) {
				if (i == num) {
					circle(Perspective_image_tmp, src_pt.at(i), 15, Scalar(255, 0, 0), -1, 8, 0);
					cv::putText(Perspective_image_tmp, to_string(i + 1), Point(src_pt.at(i).x - 6, src_pt.at(i).y + 5), 2, 0.75, Scalar::all(255));
				}
				else {
					circle(Perspective_image_tmp, src_pt.at(i), 10, Scalar(255, 0, 0), -1, 8, 0);
					cv::putText(Perspective_image_tmp, to_string(i + 1), Point(src_pt.at(i).x - 6, src_pt.at(i).y + 5), 2, 0.7, Scalar::all(255));
				}
			}
		}
		imshow("Perspective", Perspective_image_tmp);
		if (affine_num == 4) {
			Mat Perspective_image_result;
			vector<Point2f> per_dst;
			per_dst.push_back(Point(0, 0));
			per_dst.push_back(Point(Perspective_image_src.cols - 1, 0));
			per_dst.push_back(Point(Perspective_image_src.cols - 1, Perspective_image_src.rows - 1));
			per_dst.push_back(Point(0, Perspective_image_src.rows - 1));
			Mat affinematrix = getPerspectiveTransform(src_pt, per_dst);
			warpPerspective(Perspective_image_src, Perspective_image_result, affinematrix, Perspective_image_src.size());
			imshow("Perspective Prediction", Perspective_image_result);
		}
		st = ed;
	}
	if (event == EVENT_LBUTTONUP) {
		Perspective_image_src.copyTo(Perspective_image_tmp);
		line(Perspective_image_tmp, Point(10, 10), Point(Perspective_image_tmp.cols - 10, 10), Scalar(0, 0, 255), 2, 8, 0);
		line(Perspective_image_tmp, Point(Perspective_image_tmp.cols - 10, Perspective_image_tmp.rows - 10), Point(Perspective_image_tmp.cols - 10, 10), Scalar(0, 0, 255), 2, 8, 0);
		line(Perspective_image_tmp, Point(Perspective_image_tmp.cols - 10, Perspective_image_tmp.rows - 10), Point(10, Perspective_image_tmp.rows - 10), Scalar(0, 0, 255), 2, 8, 0);
		line(Perspective_image_tmp, Point(10, 10), Point(10, Perspective_image_tmp.rows - 10), Scalar(0, 0, 255), 2, 8, 0);
		circle(Perspective_image_tmp, Point(10, 10), 10, Scalar(0, 0, 255), -1, 8, 0);
		cv::putText(Perspective_image_tmp, to_string(1), Point(4, 15), 2, 0.7, Scalar::all(255));
		circle(Perspective_image_tmp, Point(Perspective_image_tmp.cols - 10, 10), 10, Scalar(0, 0, 255), -1, 8, 0);
		cv::putText(Perspective_image_tmp, to_string(2), Point(Perspective_image_tmp.cols - 16, 15), 2, 0.7, Scalar::all(255));
		circle(Perspective_image_tmp, Point(Perspective_image_tmp.cols - 10, Perspective_image_tmp.rows - 10), 10, Scalar(0, 0, 255), -1, 8, 0);
		cv::putText(Perspective_image_tmp, to_string(3), Point(Perspective_image_tmp.cols - 16, Perspective_image_tmp.rows - 5), 2, 0.7, Scalar::all(255));
		circle(Perspective_image_tmp, Point(10, Perspective_image_tmp.rows - 10), 10, Scalar(0, 0, 255), -1, 8, 0);
		cv::putText(Perspective_image_tmp, to_string(4), Point(4, Perspective_image_tmp.rows - 5), 2, 0.7, Scalar::all(255));
		num = -1;
		if (!src_pt.empty()) {
			for (int i = 0; i < src_pt.size() - 1; i++) {
				line(Perspective_image_tmp, src_pt.at(i), src_pt.at(i + 1), Scalar(255, 0, 0), 2, 8, 0);
			}
			if (affine_num == 4) {
				line(Perspective_image_tmp, src_pt.at(0), src_pt.at(3), Scalar(255, 0, 0), 2, 8, 0);
			}
		}
		if (!src_pt.empty()) {
			for (int i = 0; i < src_pt.size(); i++) {
				circle(Perspective_image_tmp, src_pt.at(i), 10, Scalar(255, 0, 0), -1, 8, 0);
				cv::putText(Perspective_image_tmp, to_string(i + 1), Point(src_pt.at(i).x - 6, src_pt.at(i).y +5), 2, 0.7, Scalar::all(255));
			}
		}
		imshow("Perspective", Perspective_image_tmp);
		if (affine_num == 4) {
			Mat Perspective_image_result;
			vector<Point2f> per_dst;
			per_dst.push_back(Point(0, 0));
			per_dst.push_back(Point(Perspective_image_src.cols - 1, 0));
			per_dst.push_back(Point(Perspective_image_src.cols - 1, Perspective_image_src.rows - 1));
			per_dst.push_back(Point(0, Perspective_image_src.rows - 1));
			Mat affinematrix = getPerspectiveTransform(src_pt, per_dst);
			warpPerspective(Perspective_image_src, Perspective_image_result, affinematrix, Perspective_image_src.size());
			imshow("Perspective Prediction", Perspective_image_result);
		}
	}
}
double COpenCVTestDlg::getDist(Point center, Point st) {
	return sqrt((center.x - st.x) * (center.x - st.x) + (center.y - st.y) * (center.y - st.y));
}
void COpenCVTestDlg::DrawDashedLine(cv::Mat& img, cv::Point pt1, cv::Point pt2,
	cv::Scalar color, int thickness, std::string style,
	int gap) {
	float dx = pt1.x - pt2.x;
	float dy = pt1.y - pt2.y;
	float dist = std::hypot(dx, dy);

	std::vector<cv::Point> pts;
	for (int i = 0; i < dist; i += gap) {
		float r = static_cast<float>(i / dist);
		int x = static_cast<int>((pt1.x * (1.0 - r) + pt2.x * r) + .5);
		int y = static_cast<int>((pt1.y * (1.0 - r) + pt2.y * r) + .5);
		pts.emplace_back(x, y);
	}
	int pts_size = pts.size();
	if (style == "dotted") {
		for (int i = 0; i < pts_size; ++i) {
			cv::circle(img, pts[i], thickness, color, -1);
		}
	}
	else {
		cv::Point s = pts[0];
		cv::Point e = pts[0];

		for (int i = 0; i < pts_size; ++i) {
			s = e;
			e = pts[i];
			if (i % 2 == 1) {
				cv::line(img, s, e, color, thickness);
			}
		}
	}
}
void COpenCVTestDlg::doAffine(int event, int x, int y, int flags) {
	int num = -1;
	int flag = 0;
	if (event == EVENT_LBUTTONDOWN && flags == EVENT_FLAG_LBUTTON) {
		st = Point(x, y);
		affine_image_src.copyTo(affine_image_tmp);
		if (affine_num < 3) {
			src_pt.push_back(Point(x, y));
			affine_num++;
		}
		else if (affine_num < 6) {
			dst_pt.push_back(Point(x, y));
			affine_num++;
		}
		vector<Point2f>::iterator iter;
		if (dst_pt.size() == 3) {
			line(affine_image_tmp, dst_pt.at(0), dst_pt.at(1), Scalar(0, 0, 255), 2, 8, 0);
			line(affine_image_tmp, dst_pt.at(0), dst_pt.at(2), Scalar(0, 0, 255), 2, 8, 0);
			line(affine_image_tmp, dst_pt.at(2), dst_pt.at(1), Scalar(0, 0, 255), 2, 8, 0);
		}
		for (int i = 0; i < dst_pt.size(); i++) {
			DrawDashedLine(affine_image_tmp, src_pt.at(i), dst_pt.at(i), Scalar(61, 255, 245), 2, "dotted", 10);
		}
		if (src_pt.size() == 3) {
			line(affine_image_tmp, src_pt.at(0), src_pt.at(1), Scalar(255, 0, 0), 2, 8, 0);
			line(affine_image_tmp, src_pt.at(0), src_pt.at(2), Scalar(255, 0, 0), 2, 8, 0);
			line(affine_image_tmp, src_pt.at(2), src_pt.at(1), Scalar(255, 0, 0), 2, 8, 0);
		}
		if (!src_pt.empty()) {
			for (int i = 0; i < src_pt.size(); i++) {
				circle(affine_image_tmp, src_pt.at(i), 10, Scalar(255, 0, 0), -1, 8, 0);
				cv::putText(affine_image_tmp, to_string(i + 1), Point(src_pt.at(i).x - 6, src_pt.at(i).y + 5), 2, 0.7, Scalar::all(255));
			}
		}
		if (!dst_pt.empty()) {
			for (int i = 0; i < dst_pt.size(); i++) {
				circle(affine_image_tmp, dst_pt.at(i), 10, Scalar(0, 0, 255), -1, 8, 0);
				cv::putText(affine_image_tmp, to_string(i + 1), Point(dst_pt.at(i).x - 6, dst_pt.at(i).y + 5), 2, 0.7, Scalar::all(255));
			}
		}
		imshow("Affine", affine_image_tmp);
		if (affine_num == 6) {
			Mat res;
			Mat affinematrix = getAffineTransform(src_pt, dst_pt);
			warpAffine(affine_image_src, res, affinematrix, affine_image_src.size());
			imshow("Affine Prediction", res);
		}
	}
	if (event == EVENT_MOUSEMOVE && flags == EVENT_FLAG_LBUTTON) {
		affine_image_src.copyTo(affine_image_tmp);
		ed = Point(x, y);
		vector<Point2f>::iterator iter;
		if (!dst_pt.empty()) {
			for (int i = dst_pt.size()-1; i >-1; i--) {
				if (getDist(dst_pt.at(i), ed) < 15) {
					if (!flag) {
						dst_pt.at(i).x += ed.x - st.x;
						dst_pt.at(i).y += ed.y - st.y;
						flag = 1;
						num = i;
					}
					break;
				}
			}
		}
		if (!src_pt.empty()) {
			for (int i = src_pt.size() - 1; i > -1; i--) {
				if (getDist(src_pt.at(i), ed) < 15) {
					if (!flag) {
						src_pt.at(i).x += ed.x - st.x;
						src_pt.at(i).y += ed.y - st.y;
						flag = 1;
						num = i + 3;
					}
					break;
				}
			}
		}
		if (dst_pt.size() == 3) {
			line(affine_image_tmp, dst_pt.at(0), dst_pt.at(1), Scalar(0, 0, 255), 2, 8, 0);
			line(affine_image_tmp, dst_pt.at(0), dst_pt.at(2), Scalar(0, 0, 255), 2, 8, 0);
			line(affine_image_tmp, dst_pt.at(2), dst_pt.at(1), Scalar(0, 0, 255), 2, 8, 0);
		}
		for (int i = 0; i < dst_pt.size(); i++) {
			DrawDashedLine(affine_image_tmp, src_pt.at(i), dst_pt.at(i), Scalar(61, 255, 245), 2, "dotted", 10);
		}
		if (src_pt.size() == 3) {
			line(affine_image_tmp, src_pt.at(0), src_pt.at(1), Scalar(255, 0, 0), 2, 8, 0);
			line(affine_image_tmp, src_pt.at(0), src_pt.at(2), Scalar(255, 0, 0), 2, 8, 0);
			line(affine_image_tmp, src_pt.at(2), src_pt.at(1), Scalar(255, 0, 0), 2, 8, 0);
		}
		if (!src_pt.empty()) {
			for (int i = 0; i < src_pt.size(); i++) {
				if (num == i + 3) {
					circle(affine_image_tmp, src_pt.at(i), 15, Scalar(255, 0, 0), -1, 8, 0);
					cv::putText(affine_image_tmp, to_string(i + 1), Point(src_pt.at(i).x - 6, src_pt.at(i).y + 5), 2, 0.75, Scalar::all(255));
				}
				else {
					circle(affine_image_tmp, src_pt.at(i), 10, Scalar(255, 0, 0), -1, 8, 0);
					cv::putText(affine_image_tmp, to_string(i + 1), Point(src_pt.at(i).x - 6, src_pt.at(i).y + 5), 2, 0.7, Scalar::all(255));
				}
			}
		}
		if (!dst_pt.empty()) {
			for (int i = 0; i < dst_pt.size(); i++) {
				if (num == i) {
					circle(affine_image_tmp, dst_pt.at(i), 15, Scalar(0, 0, 255), -1, 8, 0);
					cv::putText(affine_image_tmp, to_string(i + 1), Point(dst_pt.at(i).x - 6, dst_pt.at(i).y + 5), 2, 0.75, Scalar::all(255));
				}
				else {
					circle(affine_image_tmp, dst_pt.at(i), 10, Scalar(0, 0, 255), -1, 8, 0);
					cv::putText(affine_image_tmp, to_string(i + 1), Point(dst_pt.at(i).x - 6, dst_pt.at(i).y + 5), 2, 0.7, Scalar::all(255));
				}
			}
		}
		imshow("Affine", affine_image_tmp);
		if (affine_num == 6) {
			Mat res;
			Mat affinematrix = getAffineTransform(src_pt, dst_pt);
			warpAffine(affine_image_src, res, affinematrix, affine_image_src.size());
			imshow("Affine Prediction", res);
		}
		st = ed;
	}
	if (event == EVENT_LBUTTONUP) {
		flag = 0;
		num = -1;
		affine_image_src.copyTo(affine_image_tmp);
		vector<Point2f>::iterator iter;
		if (dst_pt.size() == 3) {
			line(affine_image_tmp, dst_pt.at(0), dst_pt.at(1), Scalar(0, 0, 255), 2, 8, 0);
			line(affine_image_tmp, dst_pt.at(0), dst_pt.at(2), Scalar(0, 0, 255), 2, 8, 0);
			line(affine_image_tmp, dst_pt.at(2), dst_pt.at(1), Scalar(0, 0, 255), 2, 8, 0);
		}
		for (int i = 0; i < dst_pt.size(); i++) {
			DrawDashedLine(affine_image_tmp, src_pt.at(i), dst_pt.at(i), Scalar(61, 255, 245), 2, "dotted", 10);
		}
		if (src_pt.size() == 3) {
			line(affine_image_tmp, src_pt.at(0), src_pt.at(1), Scalar(255, 0, 0), 2, 8, 0);
			line(affine_image_tmp, src_pt.at(0), src_pt.at(2), Scalar(255, 0, 0), 2, 8, 0);
			line(affine_image_tmp, src_pt.at(2), src_pt.at(1), Scalar(255, 0, 0), 2, 8, 0);
		}
		if (!src_pt.empty()) {
			for (int i = 0; i < src_pt.size(); i++) {
				circle(affine_image_tmp, src_pt.at(i), 10, Scalar(255, 0, 0), -1, 8, 0);
				cv::putText(affine_image_tmp, to_string(i + 1), Point(src_pt.at(i).x - 6, src_pt.at(i).y + 5), 2, 0.7, Scalar::all(255));
			}
		}
		if (!dst_pt.empty()) {
			for (int i = 0; i < dst_pt.size(); i++) {
				circle(affine_image_tmp, dst_pt.at(i), 10, Scalar(0, 0, 255), -1, 8, 0);
				cv::putText(affine_image_tmp, to_string(i + 1), Point(dst_pt.at(i).x - 6, dst_pt.at(i).y + 5), 2, 0.7, Scalar::all(255));
			}
		}
		imshow("Affine", affine_image_tmp);
		if (affine_num == 6) {
			Mat res;
			Mat affinematrix = getAffineTransform(src_pt, dst_pt);
			warpAffine(affine_image_src, res, affinematrix, affine_image_src.size());
			imshow("Affine Prediction", res);
		}
	}
}
void COpenCVTestDlg::doTraslation(int event, int x, int y, int flags) {
	if (event == EVENT_LBUTTONDOWN && flags == EVENT_FLAG_LBUTTON) {
		st = Point(x, y);
	}
	if (event == EVENT_MOUSEMOVE && flags == EVENT_FLAG_LBUTTON) {
		ed = Point(x, y);
		move_x += ed.x - st.x;
		move_y += ed.y - st.y;
		float warp_values[] = { 1.0,0.0,move_x,0.0,1.0,move_y };
		Mat translation_matrix = Mat(2, 3, CV_32F, warp_values);
		warpAffine(Image_processing.at(Cur_num), img_translated, translation_matrix, Image_processing.at(Cur_num).size());
		imshow("Translation", img_translated);
		st = ed;
	}
}
void COpenCVTestDlg::inputImageData(Mat input, double _x, double _y,CString inputstring,String name,int num) {
	Image_processing.push_back(input);
	Image_name.push_back(inputstring);
	scale_x.push_back(_x);
	scale_y.push_back(_y);
	Image_translation_name.push_back(name);
	image_source_num.push_back(num);
}
void COpenCVTestDlg::deleteImageData(int k) {
	Image_processing.erase(Image_processing.begin()+k);
	Image_name.erase(Image_name.begin() + k);
	scale_x.erase(scale_x.begin() + k);
	scale_y.erase(scale_y.begin() + k);
}
void COpenCVTestDlg::RotationTransform() {
	if (getWindowProperty("Rotation", WND_PROP_VISIBLE) < 1) {
		namedWindow("Rotation", WINDOW_AUTOSIZE);
		m_rotate_dlg = new RotationDialog;
		m_rotate_dlg->Create(IDD_DIALOG2);
		m_rotate_dlg->ShowWindow(SW_SHOW);
	}
	imshow("Rotation", Image_processing.at(Image_processing.size() - 1));
	while (getWindowProperty("Rotation", WND_PROP_VISIBLE) >= 1) {
		if (m_rotate_dlg == nullptr || m_rotate_dlg->IsWindowVisible() == FALSE)
			break;
		if (waitKey(1) != -1) {
			break;
		}
	}
	if (m_rotate_dlg != nullptr && m_rotate_dlg->IsWindowVisible() == TRUE)
		m_rotate_dlg->EndDialog(IDCANCEL);
	Image_processing.at(Image_processing.size() - 1) = img_rotated;
	RefreshListBox();
	destroyAllWindows();
	showTransformImage();
}
void COpenCVTestDlg::AffineTransform() {
	namedWindow("Affine", WINDOW_AUTOSIZE);
	Image_processing.at(Cur_num).copyTo(affine_image_src);
	imshow("Affine", affine_image_src);
	affine_num = 0;
	src_pt.clear();
	dst_pt.clear();
	while (getWindowProperty("Affine", WND_PROP_VISIBLE) >= 1) {
		setMouseCallback("Affine", AffineMouseCallBack, this);
		if (waitKey(1) != -1) {
			break;
		}
		if (affine_num == 6 && getWindowProperty("Affine Prediction", WND_PROP_VISIBLE) < 1)
			break;
	}
	destroyAllWindows();
	if (affine_num != 6) {
		deleteImageData(Image_processing.size() - 1);
		AfxMessageBox(_T("점의 개수가 부족합니다!"));
	}
	else {
		Mat res;
		Mat affinematrix = getAffineTransform(src_pt, dst_pt);
		warpAffine(affine_image_src, res, affinematrix, affine_image_src.size());
		Image_processing.at(Image_processing.size() - 1) = res;
	}
	if (affine_num == 6) {
		showTransformImage();
	}
	RefreshListBox();
}
void COpenCVTestDlg::PerspectiveTransform() {
	namedWindow("Perspective", WINDOW_AUTOSIZE);
	Image_processing.at(Cur_num).copyTo(Perspective_image_src);
	imshow("Perspective", Perspective_image_src);
	affine_num = 0;
	src_pt.clear();
	dst_pt.clear();
	vector<Point2f>per_dst;
	while (getWindowProperty("Perspective", WND_PROP_VISIBLE) >= 1) {
		setMouseCallback("Perspective", PerspectiveMouseCallBack, this);
		if (waitKey(1) != -1) {
			break;
		}
		if (affine_num == 4 && getWindowProperty("Perspective Prediction", WND_PROP_VISIBLE) < 1)
			break;
	}
	destroyAllWindows();
	if (affine_num != 4) {
		deleteImageData(Image_processing.size() - 1);
		AfxMessageBox(_T("점의 개수가 부족합니다!"));
	}
	else {
		Mat res;
		per_dst.push_back(Point(0, 0));
		per_dst.push_back(Point(Perspective_image_src.cols - 1, 0));
		per_dst.push_back(Point(Perspective_image_src.cols - 1, Perspective_image_src.rows - 1));
		per_dst.push_back(Point(0, Perspective_image_src.rows - 1));
		Mat affinematrix = getPerspectiveTransform(src_pt, per_dst);
		warpPerspective(Perspective_image_src, res, affinematrix, Perspective_image_src.size());
		Image_processing.at(Image_processing.size() - 1) = res;
	}
	if (affine_num == 4) {
		showTransformImage();
	}
	RefreshListBox();
}
void COpenCVTestDlg::TranslationTransform() {
	imshow("Translation", Image_processing.at(Cur_num));
	move_x = 0;
	move_y = 0;
	while (getWindowProperty("Translation", WND_PROP_VISIBLE) >= 1) {
		setMouseCallback("Translation", TranslationMouseCallBack, this);
		if (waitKey(1) != -1) {
			break;
		}
	}
	if (move_x != 0 || move_y != 0) {
		Image_processing.at(Image_processing.size() - 1) = img_translated;
	}
	RefreshListBox();
	destroyAllWindows();
	showTransformImage();
}
void COpenCVTestDlg::ScalingTransform() {
	int flag = 0;
	if (getWindowProperty("Scaling", WND_PROP_VISIBLE) < 1) {
		Image_processing.at(Cur_num).copyTo(scaledImage);
		namedWindow("Scaling", WINDOW_AUTOSIZE);
		m_scale_dlg = new ScaleDialog;
		m_scale_dlg->Create(IDD_DIALOG1);
		m_scale_dlg->ShowWindow(SW_SHOW);
	}
	while (getWindowProperty("Scaling", WND_PROP_VISIBLE) >= 1) {
		if (m_scale_dlg == nullptr || m_scale_dlg->IsWindowVisible() == FALSE)
			break;
		if (waitKey(1)!=-1) {
			break;
		}
	}
	if(m_scale_dlg != nullptr && m_scale_dlg->IsWindowVisible()==TRUE)
		m_scale_dlg->EndDialog(IDCANCEL);
	Image_processing.at(Image_processing.size() - 1) = scaledImage;
	scale_x.at(scale_x.size() - 1) *= Cur_Scale_total * Cur_scale_x;
	scale_y.at(scale_y.size() - 1) *= Cur_Scale_total * Cur_scale_y;
	RefreshListBox();
	destroyAllWindows();
	showTransformImage();
}
void COpenCVTestDlg::showTransformImage() {
	GetDlgItem(IDC_PC_VIEW3)->ShowWindow(false);
	GetDlgItem(IDC_PC_VIEW3)->ShowWindow(true);
	Mat TransformTmp = Image_processing.at(Image_processing.size() - 1);
	CString strData;
	int k = scale_x.size() - 1;
	Image_combo.GetLBText(Image_combo.GetCurSel(), strData);
	if (Image_translation_name.at(Image_translation_name.size()-1) == "Scaling") {
		if (scale_x.at(k) / scale_x.at(image_source_num.at(k)) > 1) {
			Rect2i cutting(0, 0, (int)((double)TransformTmp.cols / (scale_x.at(k) / scale_x.at(image_source_num.at(k)))), TransformTmp.rows);
			TransformTmp = TransformTmp(cutting);
		}
		if (scale_y.at(k) / scale_y.at(image_source_num.at(k)) > 1) {
			Rect2i cutting(0, 0, TransformTmp.cols, (int)((double)TransformTmp.rows / (scale_y.at(k) / scale_y.at(image_source_num.at(k)))));
			TransformTmp = TransformTmp(cutting);
		}
		if (scale_x.at(k) / scale_x.at(image_source_num.at(k)) < 1) {
			Mat tmp = Mat::zeros(Size(Image_processing.at(image_source_num.at(k)).cols, Image_processing.at(image_source_num.at(k)).rows), CV_8UC3);
			if (scale_y.at(k) / scale_y.at(image_source_num.at(k)) < 1) {
				for (int x = 0; x < TransformTmp.cols; x++) {
					for (int y = 0; y < TransformTmp.rows; y++) {
						tmp.at<Vec3b>(Point(x, y)) = TransformTmp.at<Vec3b>(Point(x, y));
					}
				}
			}
			else {
				for (int x = 0; x < TransformTmp.cols; x++) {
					for (int y = 0; y < tmp.rows; y++) {
						tmp.at<Vec3b>(Point(x, y)) = TransformTmp.at<Vec3b>(Point(x, y));
					}
				}
			}
			tmp.copyTo(TransformTmp);
		}
		if (scale_y.at(k) / scale_y.at(image_source_num.at(k)) < 1) {
			Mat tmp = Mat::zeros(Size(Image_processing.at(image_source_num.at(k)).cols, Image_processing.at(image_source_num.at(k)).rows), CV_8UC3);
			if (scale_x.at(k) / scale_x.at(image_source_num.at(k)) < 1) {
				for (int x = 0; x < TransformTmp.cols; x++) {
					for (int y = 0; y < TransformTmp.rows; y++) {
						tmp.at<Vec3b>(Point(x, y)) = TransformTmp.at<Vec3b>(Point(x, y));
					}
				}
			}
			else {
				for (int x = 0; x < tmp.cols; x++) {
					for (int y = 0; y < TransformTmp.rows; y++) {
						tmp.at<Vec3b>(Point(x, y)) = TransformTmp.at<Vec3b>(Point(x, y));
					}
				}
			}
			tmp.copyTo(TransformTmp);
		}
	}
	Mat TransformBmp;
	TransformBmp = DoPadding(TransformTmp);
	DrawPictrue(IDC_PC_VIEW3, TransformBmp);
}

void COpenCVTestDlg::ShowExample_Translation1(Mat tmp) {
	int flag = 0;
	CString strData;
		GetDlgItem(IDC_PC_VIEW4)->ShowWindow(false);
		GetDlgItem(IDC_PC_VIEW4)->ShowWindow(true);
		GetDlgItem(IDC_PC_VIEW5)->ShowWindow(false);
		GetDlgItem(IDC_PC_VIEW5)->ShowWindow(true);
		GetDlgItem(IDC_PC_VIEW)->ShowWindow(false);
		GetDlgItem(IDC_PC_VIEW)->ShowWindow(true);
	Image_combo.GetLBText(Image_combo.GetCurSel(), strData);
	Mat mesh_before_bmp;
	Mat mesh_after_bmp;
	Mat mesh_scaling_before;
	Mat mesh_scaling_after;
	//리소스 파일 Mat로 변환하는 부분 시작
	if (example_mesh == TRUE) {
		CPngImage before;
		before.Load(IDB_PNG21, nullptr);
		CBitmap bit_before;
		bit_before.Attach(before.Detach());
		BITMAP bmap;
		bit_before.GetBitmap(&bmap);
		int Width = bmap.bmWidth;
		int Height = bmap.bmHeight;
		int nChannels = bmap.bmBitsPixel == 1 ? 1 : bmap.bmBitsPixel / 8;
		int depth = bmap.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
		BYTE* pBuffer = new BYTE[bmap.bmHeight * bmap.bmWidth * nChannels];
		GetBitmapBits((HBITMAP)bit_before.GetSafeHandle(), bmap.bmHeight * bmap.bmWidth * nChannels, pBuffer);
		cv::Mat Channel4Mat(bmap.bmHeight, bmap.bmWidth, CV_MAKETYPE(depth, nChannels));
		memcpy(Channel4Mat.data, pBuffer, bmap.bmHeight * bmap.bmWidth * nChannels);
		cv::Mat Channel3Mat(bmap.bmHeight, bmap.bmWidth * nChannels, CV_8UC3);
		cvtColor(Channel4Mat, Channel3Mat, CV_BGRA2BGR);
		Channel3Mat.copyTo(mesh_scaling_before);
		Channel3Mat.copyTo(mesh_scaling_after);
		delete[] pBuffer;
		pBuffer = NULL;
		bit_before.DeleteObject();
		before.DeleteObject();
		Channel3Mat.deallocate();
		//끝
	}
	else {
		Image_processing.at(Cur_num).copyTo(mesh_scaling_before);
		Image_processing.at(Cur_num).copyTo(mesh_scaling_after);
	}
	if (strData == L"Scaling") {
		flag = 1;
		Rect2i a(0, 0, mesh_scaling_after.cols / 2, mesh_scaling_after.rows / 2);
		mesh_scaling_after = mesh_scaling_after(a);
		CPngImage cButtonImg1;
		CBitmap bit1;
		cButtonImg1.Load(IDB_PNG11, nullptr);
		bit1.Attach(cButtonImg1.Detach());
		m_explain.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
		m_explain.m_bTransparent = TRUE;    // 투명도 설정
		m_explain.m_bDrawFocus = FALSE;
		m_explain.SetImage(bit1);
		m_explain.SetWindowText(L"");
		bit1.DeleteObject();
		cButtonImg1.DeleteObject();
	}
	if (strData == L"Rotation") {
		flag = 1;
		Mat rotatetmp;
		mesh_scaling_after.copyTo(rotatetmp);
		Point2f point_center(rotatetmp.cols / 2.0, rotatetmp.rows / 2.0);
		Mat rot = cv::getRotationMatrix2D(point_center, 45, 1.0);

		Rect bbox = cv::RotatedRect(point_center, rotatetmp.size(), 45).boundingRect();

		rot.at<double>(0, 2) += bbox.width / 2.0 - point_center.x;
		rot.at<double>(1, 2) += bbox.height / 2.0 - point_center.y;
		mesh_scaling_after = getRotationMatrix2D(point_center, 45, 1.0);

		// warpAffine(m_img_open_ori, m_img_dst, rot, m_img_open_ori.size());
		warpAffine(rotatetmp, mesh_scaling_after, rot, bbox.size());

		CPngImage cButtonImg1;
		CBitmap bit1;
		cButtonImg1.Load(IDB_PNG15, nullptr);
		bit1.Attach(cButtonImg1.Detach());
		m_explain.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
		m_explain.m_bTransparent = TRUE;    // 투명도 설정
		m_explain.m_bDrawFocus = FALSE;
		m_explain.SetImage(bit1);
		m_explain.SetWindowText(L"");
		bit1.DeleteObject();
		cButtonImg1.DeleteObject();
	}
	if (strData == L"Translation") {
		flag = 1;
		float warp_values[] = { 1.0,0.0,mesh_scaling_before.cols / 2,0.0,1.0,mesh_scaling_before.rows / 2 };
		Mat translation_matrix = Mat(2, 3, CV_32F, warp_values);
		warpAffine(mesh_scaling_before, mesh_scaling_after, translation_matrix, mesh_scaling_before.size());
		CPngImage cButtonImg1;
		CBitmap bit1;
		cButtonImg1.Load(IDB_PNG16, nullptr);
		bit1.Attach(cButtonImg1.Detach());
		m_explain.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
		m_explain.m_bTransparent = TRUE;    // 투명도 설정
		m_explain.m_bDrawFocus = FALSE;
		m_explain.SetImage(bit1);
		m_explain.SetWindowText(L"");
		bit1.DeleteObject();
		cButtonImg1.DeleteObject();
	}
	if (strData == L"Affine") {
		flag = 1;
		vector<Point2f>affine_tmp;
		affine_tmp.push_back(Point(mesh_scaling_before.cols / 2, mesh_scaling_before.rows / 3));
		affine_tmp.push_back(Point(2 * mesh_scaling_before.cols / 3, 2 * mesh_scaling_before.rows / 3));
		affine_tmp.push_back(Point(mesh_scaling_before.cols / 3, 2 * mesh_scaling_before.rows / 3));
		vector<Point2f>affine_tmp_bs;
		affine_tmp_bs.push_back(Point(3 * mesh_scaling_before.cols / 5, mesh_scaling_before.rows / 3));
		affine_tmp_bs.push_back(Point(3 * mesh_scaling_before.cols / 4, 3 * mesh_scaling_before.rows / 4));
		affine_tmp_bs.push_back(Point(mesh_scaling_before.cols / 2, mesh_scaling_before.rows / 2));

		Mat affinematrix = getAffineTransform(affine_tmp, affine_tmp_bs);
		warpAffine(mesh_scaling_before, mesh_scaling_after, affinematrix, mesh_scaling_before.size());
		CPngImage cButtonImg1;
		CBitmap bit1;
		cButtonImg1.Load(IDB_PNG18, nullptr);
		bit1.Attach(cButtonImg1.Detach());
		m_explain.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
		m_explain.m_bTransparent = TRUE;    // 투명도 설정
		m_explain.m_bDrawFocus = FALSE;
		m_explain.SetImage(bit1);
		m_explain.SetWindowText(L"");
		bit1.DeleteObject();
		cButtonImg1.DeleteObject();
	}
	if (strData == L"Perspective") {
		flag = 1;
		vector<Point2f>perspective_tmp;
		perspective_tmp.push_back(Point(0, 0));
		perspective_tmp.push_back(Point(mesh_scaling_before.cols - 1, 0));
		perspective_tmp.push_back(Point(mesh_scaling_before.cols - 1, mesh_scaling_before.rows - 1));
		perspective_tmp.push_back(Point(0, mesh_scaling_before.rows - 1));
		circle(mesh_scaling_before, Point(mesh_scaling_before.cols - 1, 0), 25, Scalar(0, 0, 255), -1, 8, 0);
		circle(mesh_scaling_before, Point(0, 0), 25, Scalar(0, 0, 255), -1, 8, 0);
		circle(mesh_scaling_before, Point(mesh_scaling_before.cols - 1, mesh_scaling_before.rows - 1), 25, Scalar(0, 0, 255), -1, 8, 0);
		circle(mesh_scaling_before, Point(0, mesh_scaling_before.rows - 1), 25, Scalar(0, 0, 255), -1, 8, 0);
		vector<Point2f>perspective_tmp_bs;
		perspective_tmp_bs.push_back(Point(mesh_scaling_before.cols / 3, mesh_scaling_before.rows / 3));
		perspective_tmp_bs.push_back(Point(2 * mesh_scaling_before.cols / 3, mesh_scaling_before.rows / 3));
		perspective_tmp_bs.push_back(Point(3 * mesh_scaling_before.cols / 5, 2 * mesh_scaling_before.rows / 3));
		perspective_tmp_bs.push_back(Point(2 * mesh_scaling_before.cols / 5, mesh_scaling_before.rows * 2 / 3));
		circle(mesh_scaling_before, Point(2 * mesh_scaling_before.cols / 3, mesh_scaling_before.rows / 3), 25, Scalar(255, 0, 0), -1, 8, 0);
		circle(mesh_scaling_before, Point(mesh_scaling_before.cols / 3, mesh_scaling_before.rows / 3), 25, Scalar(255, 0, 0), -1, 8, 0);
		circle(mesh_scaling_before, Point(3 * mesh_scaling_before.cols / 5, 2 * mesh_scaling_before.rows / 3), 25, Scalar(255, 0, 0), -1, 8, 0);
		circle(mesh_scaling_before, Point(2 * mesh_scaling_before.cols / 5, mesh_scaling_before.rows * 2 / 3), 25, Scalar(255, 0, 0), -1, 8, 0);
		Mat affinematrix = getPerspectiveTransform(perspective_tmp_bs, perspective_tmp);
		warpPerspective(mesh_scaling_before, mesh_scaling_after, affinematrix, mesh_scaling_before.size());
		CPngImage cButtonImg1;
		CBitmap bit1;
		cButtonImg1.Load(IDB_PNG19, nullptr);
		bit1.Attach(cButtonImg1.Detach());
		m_explain.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
		m_explain.m_bTransparent = TRUE;    // 투명도 설정
		m_explain.m_bDrawFocus = FALSE;
		m_explain.SetImage(bit1);
		m_explain.SetWindowText(L"");
		bit1.DeleteObject();
		cButtonImg1.DeleteObject();
	}
	DoPadding(mesh_scaling_before).copyTo(mesh_before_bmp);
	DoPadding(mesh_scaling_after).copyTo(mesh_after_bmp);
	if (flag) {
		DrawPictrue(IDC_PC_VIEW5, mesh_before_bmp);
		DrawPictrue(IDC_PC_VIEW, tmp);
		DrawPictrue(IDC_PC_VIEW4, mesh_after_bmp);
	}
}

void COpenCVTestDlg::ShowExample_Translation() {
	CString strData;
	GetDlgItem(IDC_PC_VIEW4)->ShowWindow(false);
	GetDlgItem(IDC_PC_VIEW4)->ShowWindow(true);
	GetDlgItem(IDC_PC_VIEW5)->ShowWindow(false);
	GetDlgItem(IDC_PC_VIEW5)->ShowWindow(true);
	Image_combo.GetLBText(Image_combo.GetCurSel(), strData);
	Mat mesh_before_bmp;
	Mat mesh_after_bmp;
	Mat mesh_scaling_before;
	Mat mesh_scaling_after;
	//리소스 파일 Mat로 변환하는 부분 시작
	if (example_mesh==TRUE) {
		CPngImage before;
		before.Load(IDB_PNG21, nullptr);
		CBitmap bit_before;
		bit_before.Attach(before.Detach());
		BITMAP bmap;
		bit_before.GetBitmap(&bmap);
		int Width = bmap.bmWidth;
		int Height = bmap.bmHeight;
		int nChannels = bmap.bmBitsPixel == 1 ? 1 : bmap.bmBitsPixel / 8;
		int depth = bmap.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
		BYTE* pBuffer = new BYTE[bmap.bmHeight * bmap.bmWidth * nChannels];
		GetBitmapBits((HBITMAP)bit_before.GetSafeHandle(), bmap.bmHeight * bmap.bmWidth * nChannels, pBuffer);
		cv::Mat Channel4Mat(bmap.bmHeight, bmap.bmWidth, CV_MAKETYPE(depth, nChannels));
		memcpy(Channel4Mat.data, pBuffer, bmap.bmHeight * bmap.bmWidth * nChannels);
		cv::Mat Channel3Mat(bmap.bmHeight, bmap.bmWidth * nChannels, CV_8UC3);
		cvtColor(Channel4Mat, Channel3Mat, CV_BGRA2BGR);
		Channel3Mat.copyTo(mesh_scaling_before);
		Channel3Mat.copyTo(mesh_scaling_after);
		delete[] pBuffer;
		pBuffer = NULL;
		bit_before.DeleteObject();
		before.DeleteObject();
		Channel3Mat.deallocate();
		//끝
	}
	else {
		Image_processing.at(Cur_num).copyTo(mesh_scaling_before);
		Image_processing.at(Cur_num).copyTo(mesh_scaling_after);
	}
	if (strData == L"Scaling") {
		Rect2i a(0, 0, mesh_scaling_after.cols / 2, mesh_scaling_after.rows / 2);
		mesh_scaling_after = mesh_scaling_after(a);
		CPngImage cButtonImg1;
		CBitmap bit1;
		cButtonImg1.Load(IDB_PNG11, nullptr);
		bit1.Attach(cButtonImg1.Detach());
		m_explain.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
		m_explain.m_bTransparent = TRUE;    // 투명도 설정
		m_explain.m_bDrawFocus = FALSE;
		m_explain.SetImage(bit1);
		m_explain.SetWindowText(L"");
		bit1.DeleteObject();
		cButtonImg1.DeleteObject();
	}
	if (strData == L"Rotation") {
		Mat rotatetmp;
		mesh_scaling_after.copyTo(rotatetmp);
		Point2f point_center(rotatetmp.cols / 2.0, rotatetmp.rows / 2.0);
		Mat rot = cv::getRotationMatrix2D(point_center, 45, 1.0);

		Rect bbox = cv::RotatedRect(point_center, rotatetmp.size(), 45).boundingRect();

		rot.at<double>(0, 2) += bbox.width / 2.0 - point_center.x;
		rot.at<double>(1, 2) += bbox.height / 2.0 - point_center.y;
		mesh_scaling_after = getRotationMatrix2D(point_center, 45, 1.0);

		// warpAffine(m_img_open_ori, m_img_dst, rot, m_img_open_ori.size());
		warpAffine(rotatetmp, mesh_scaling_after, rot, bbox.size());

		CPngImage cButtonImg1;
		CBitmap bit1;
		cButtonImg1.Load(IDB_PNG15, nullptr);
		bit1.Attach(cButtonImg1.Detach());
		m_explain.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
		m_explain.m_bTransparent = TRUE;    // 투명도 설정
		m_explain.m_bDrawFocus = FALSE;
		m_explain.SetImage(bit1);
		m_explain.SetWindowText(L"");
		bit1.DeleteObject();
		cButtonImg1.DeleteObject();
	}
	if (strData == L"Translation") {
		float warp_values[] = { 1.0,0.0,mesh_scaling_before.cols/2,0.0,1.0,mesh_scaling_before.rows/2 };
		Mat translation_matrix = Mat(2, 3, CV_32F, warp_values);
		warpAffine(mesh_scaling_before, mesh_scaling_after, translation_matrix, mesh_scaling_before.size());
		CPngImage cButtonImg1;
		CBitmap bit1;
		cButtonImg1.Load(IDB_PNG16, nullptr);
		bit1.Attach(cButtonImg1.Detach());
		m_explain.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
		m_explain.m_bTransparent = TRUE;    // 투명도 설정
		m_explain.m_bDrawFocus = FALSE;
		m_explain.SetImage(bit1);
		m_explain.SetWindowText(L"");
		bit1.DeleteObject();
		cButtonImg1.DeleteObject();
	}
	if (strData == L"Affine") {
		vector<Point2f>affine_tmp;
		affine_tmp.push_back(Point(mesh_scaling_before.cols / 2, mesh_scaling_before.rows / 3));
		affine_tmp.push_back(Point(2*mesh_scaling_before.cols / 3, 2*mesh_scaling_before.rows / 3));
		affine_tmp.push_back(Point(mesh_scaling_before.cols / 3, 2*mesh_scaling_before.rows / 3));
		vector<Point2f>affine_tmp_bs;
		affine_tmp_bs.push_back(Point(3*mesh_scaling_before.cols / 5, mesh_scaling_before.rows / 3));
		affine_tmp_bs.push_back(Point(3 * mesh_scaling_before.cols / 4, 3 * mesh_scaling_before.rows / 4));
		affine_tmp_bs.push_back(Point(mesh_scaling_before.cols /2, mesh_scaling_before.rows / 2));

		Mat affinematrix = getAffineTransform(affine_tmp, affine_tmp_bs);
		warpAffine(mesh_scaling_before, mesh_scaling_after, affinematrix, mesh_scaling_before.size());
		CPngImage cButtonImg1;
		CBitmap bit1;
		cButtonImg1.Load(IDB_PNG18, nullptr);
		bit1.Attach(cButtonImg1.Detach());
		m_explain.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
		m_explain.m_bTransparent = TRUE;    // 투명도 설정
		m_explain.m_bDrawFocus = FALSE;
		m_explain.SetImage(bit1);
		m_explain.SetWindowText(L"");
		bit1.DeleteObject();
		cButtonImg1.DeleteObject();
	}
	if (strData == L"Perspective") {
		vector<Point2f>perspective_tmp;
		perspective_tmp.push_back(Point(0, 0));
		perspective_tmp.push_back(Point(mesh_scaling_before.cols - 1, 0));
		perspective_tmp.push_back(Point(mesh_scaling_before.cols - 1, mesh_scaling_before.rows - 1));
		perspective_tmp.push_back(Point(0, mesh_scaling_before.rows - 1));
		circle(mesh_scaling_before, Point(mesh_scaling_before.cols - 1, 0), 25, Scalar(0, 0, 255), -1, 8, 0);
		circle(mesh_scaling_before, Point(0, 0), 25, Scalar(0, 0, 255), -1, 8, 0);
		circle(mesh_scaling_before, Point(mesh_scaling_before.cols - 1, mesh_scaling_before.rows - 1), 25, Scalar(0, 0, 255), -1, 8, 0);
		circle(mesh_scaling_before, Point(0, mesh_scaling_before.rows - 1), 25, Scalar(0, 0, 255), -1, 8, 0);
		vector<Point2f>perspective_tmp_bs;
		perspective_tmp_bs.push_back(Point(mesh_scaling_before.cols / 3, mesh_scaling_before.rows / 3));
		perspective_tmp_bs.push_back(Point(2 * mesh_scaling_before.cols / 3, mesh_scaling_before.rows / 3));
		perspective_tmp_bs.push_back(Point(3 * mesh_scaling_before.cols / 5, 2 * mesh_scaling_before.rows / 3));
		perspective_tmp_bs.push_back(Point(2 * mesh_scaling_before.cols / 5, mesh_scaling_before.rows * 2 / 3));
		circle(mesh_scaling_before, Point(2 * mesh_scaling_before.cols / 3, mesh_scaling_before.rows / 3), 25, Scalar(255, 0, 0), -1, 8, 0);
		circle(mesh_scaling_before, Point(mesh_scaling_before.cols / 3, mesh_scaling_before.rows / 3), 25, Scalar(255, 0, 0), -1, 8, 0);
		circle(mesh_scaling_before, Point(3 * mesh_scaling_before.cols / 5, 2 * mesh_scaling_before.rows / 3), 25, Scalar(255, 0, 0), -1, 8, 0);
		circle(mesh_scaling_before, Point(2 * mesh_scaling_before.cols / 5, mesh_scaling_before.rows * 2 / 3), 25, Scalar(255, 0, 0), -1, 8, 0);
		Mat affinematrix = getPerspectiveTransform(perspective_tmp_bs, perspective_tmp);
		warpPerspective(mesh_scaling_before, mesh_scaling_after, affinematrix, mesh_scaling_before.size());
		CPngImage cButtonImg1;
		CBitmap bit1;
		cButtonImg1.Load(IDB_PNG19, nullptr);
		bit1.Attach(cButtonImg1.Detach());
		m_explain.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
		m_explain.m_bTransparent = TRUE;    // 투명도 설정
		m_explain.m_bDrawFocus = FALSE;
		m_explain.SetImage(bit1);
		m_explain.SetWindowText(L"");
		bit1.DeleteObject();
		cButtonImg1.DeleteObject();
	}
	DoPadding(mesh_scaling_before).copyTo(mesh_before_bmp);
	DoPadding(mesh_scaling_after).copyTo(mesh_after_bmp);

	DrawPictrue(IDC_PC_VIEW5, mesh_before_bmp);
	DrawPictrue(IDC_PC_VIEW4, mesh_after_bmp);
}

void COpenCVTestDlg::OnCbnSelchangeCombo1()
{
	UpdateData();
	CString strData;
	Image_combo.GetLBText(Image_combo.GetCurSel(), strData);
	Image_combo.ResetContent();
	Make_Transform_combo();
	Image_combo.SetCurSel(Image_combo.SelectString(-1, strData));
	if (strData == L"Scaling") {
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_MFCBUTTON19)->ShowWindow(SW_SHOW);
	}
	else {
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MFCBUTTON19)->ShowWindow(SW_HIDE);
	}
	ShowExample_Translation();
}

void COpenCVTestDlg::OnLbnSelchangeList5()
{
	GetDlgItem(IDC_PC_DOWNLOAD)->ShowWindow(false);
	GetDlgItem(IDC_PC_DOWNLOAD)->ShowWindow(true);
	Mat show_tmp;
	Mat show_bmp;
	if (!Image_processing.empty()) {
		int k = image_listbox.GetCurSel();
		if (k<0 || k>Image_processing.size())return;
		show_tmp = Image_processing.at(k);
		if (Image_translation_name.at(k) =="Scaling") {
			if (scale_x.at(k)/scale_x.at(image_source_num.at(k)) > 1) {
				Rect2i cutting(0, 0, (int)((double)show_tmp.cols / (scale_x.at(k) / scale_x.at(image_source_num.at(k)))), show_tmp.rows);
				show_tmp = show_tmp(cutting);
			}
			if (scale_y.at(k) / scale_y.at(image_source_num.at(k)) > 1) {
				Rect2i cutting(0, 0, show_tmp.cols, (int)((double)show_tmp.rows / (scale_y.at(k) / scale_y.at(image_source_num.at(k)))));
				show_tmp = show_tmp(cutting);
			}
			if (scale_x.at(k) / scale_x.at(image_source_num.at(k)) < 1) {
				Mat tmp = Mat::zeros(Size(Image_processing.at(image_source_num.at(k)).cols, Image_processing.at(image_source_num.at(k)).rows), CV_8UC3);
				if (scale_y.at(k) / scale_y.at(image_source_num.at(k)) < 1) {
					for (int x = 0; x < show_tmp.cols; x++) {
						for (int y = 0; y < show_tmp.rows; y++) {
							tmp.at<Vec3b>(Point(x, y)) = show_tmp.at<Vec3b>(Point(x, y));
						}
					}
				}
				else {
					for (int x = 0; x < show_tmp.cols; x++) {
						for (int y = 0; y < tmp.rows; y++) {
							tmp.at<Vec3b>(Point(x, y)) = show_tmp.at<Vec3b>(Point(x, y));
						}
					}
				}
				tmp.copyTo(show_tmp);
			}
			if (scale_y.at(k) / scale_y.at(image_source_num.at(k)) < 1) {
				Mat tmp = Mat::zeros(Size(Image_processing.at(image_source_num.at(k)).cols, Image_processing.at(image_source_num.at(k)).rows), CV_8UC3);
				if (scale_x.at(k) / scale_x.at(image_source_num.at(k)) < 1) {
					for (int x = 0; x < show_tmp.cols; x++) {
						for (int y = 0; y < show_tmp.rows; y++) {
							tmp.at<Vec3b>(Point(x, y)) = show_tmp.at<Vec3b>(Point(x, y));
						}
					}
				}
				else {
					for (int x = 0; x < tmp.cols; x++) {
						for (int y = 0; y < show_tmp.rows; y++) {
							tmp.at<Vec3b>(Point(x, y)) = show_tmp.at<Vec3b>(Point(x, y));
						}
					}
				}
				tmp.copyTo(show_tmp);
			}
		}
		show_bmp = DoPadding(show_tmp);
		DrawPictrue(IDC_PC_DOWNLOAD, show_bmp);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void COpenCVTestDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (ClickControl(IDC_PC_VIEW3, point)) {
		if (!Image_processing.empty() &&Image_processing.size()!=1) {
			imshow("Transform Image", Image_processing.at(Image_processing.size() - 1));
			while (getWindowProperty("Transform Image", WND_PROP_VISIBLE) >= 1) {
				imshow("Transform Image", Image_processing.at(Image_processing.size() - 1));
				if (waitKey(1) != -1) {
					destroyWindow("Transform Image");
					break;
				}
			}
		}
	}
	if (ClickControl(IDC_PC_VIEW, point)){
		if (!Image_processing.empty()) {
			imshow("Source Image", Image_processing.at(Cur_num));
			while (getWindowProperty("Source Image", WND_PROP_VISIBLE) >= 1) {
				imshow("Source Image", Image_processing.at(Cur_num));
				if (waitKey(1) != -1) {
					destroyWindow("Source Image");
					break;
				}
			}
		}
	}
	if (ClickControl(IDC_PC_DOWNLOAD, point)) {
		if (image_listbox.GetCurSel() >= 0 && image_listbox.GetCurSel() <= Image_processing.size() - 1) {
			imshow("Selected Image", Image_processing.at(Cur_num));
			while (getWindowProperty("Selected Image", WND_PROP_VISIBLE) >= 1) {
				imshow("Selected Image", Image_processing.at(image_listbox.GetCurSel()));
				if (waitKey(1) != -1) {
					destroyWindow("Selected Image");
					break;
				}
			}
		}
	}
	CDialogEx::OnLButtonDblClk(nFlags, point);
}

bool COpenCVTestDlg::ClickControl(int IDC_TARTGET, CPoint pt)
{
	CRect rcIdcTraget;
	GetDlgItem(IDC_TARTGET)->GetWindowRect(rcIdcTraget);
	ScreenToClient(rcIdcTraget);

	if (rcIdcTraget.left < pt.x && rcIdcTraget.top < pt.y
		&& rcIdcTraget.right > pt.x && rcIdcTraget.bottom > pt.y)
		return true;
	else
		return false;
}


void COpenCVTestDlg::OnBnClickedMfcbutton1()
{
	if (Image_processing.empty()) {
		AfxMessageBox(_T("보여줄 사진이 없습니다!"));
	}
	else {
		imshow("Source Image", Image_processing.at(Cur_num));
		while (getWindowProperty("Source Image", WND_PROP_VISIBLE) >= 1) {
			imshow("Source Image", Image_processing.at(Cur_num));
			if (waitKey(1) != -1) {
				destroyWindow("Source Image");
				break;
			}
		}
	}
}

//다른 변환 작업을 하고 있는지 확인하는 함수이다.
BOOL COpenCVTestDlg::CheckDoingAnotherTranslation() {
	if (getWindowProperty("Scaling", WND_PROP_VISIBLE) >= 1)return TRUE;
	if (getWindowProperty("Translation", WND_PROP_VISIBLE) >= 1)return TRUE;
	if (getWindowProperty("Affine", WND_PROP_VISIBLE) >= 1)return TRUE;
	if (getWindowProperty("Rotation", WND_PROP_VISIBLE) >= 1)return TRUE;
	if (getWindowProperty("Perspective", WND_PROP_VISIBLE) >= 1)return TRUE;
	return FALSE;
}

void COpenCVTestDlg::OnBnClickedMfcbutton2()
{
	if (!Image_processing.empty()) {
		CString input;
		CString num;
		num.Format(_T("%d"), Cur_num);
		input += num;
		CString strData;
		Image_combo.GetLBText(Image_combo.GetCurSel(), strData);
		if (!CheckDoingAnotherTranslation()) {
			if (strData == L"Scaling") {
				input += L" image Scaling (";
				CString strInter;
				m_interpolation.GetLBText(m_interpolation.GetCurSel(), strInter);
				input += strInter;
				input += L")";
				inputImageData(Image_processing.at(Cur_num), scale_x.at(Cur_num), scale_y.at(Cur_num), input, "Scaling",Cur_num);
				ScalingTransform();
			}
			else if (strData == L"Rotation") {
				input += L" image Rotation";
				inputImageData(Image_processing.at(Cur_num), scale_x.at(Cur_num), scale_y.at(Cur_num), input, "Rotation", Cur_num);
				RotationTransform();
			}
			else if (strData == L"Translation") {
				input += L" image Translation";
				inputImageData(Image_processing.at(Cur_num), scale_x.at(Cur_num), scale_y.at(Cur_num), input, "Translation", Cur_num);
				TranslationTransform();
			}
			else if (strData == L"Affine") {
				input += L" image Affine";
				inputImageData(Image_processing.at(Cur_num), scale_x.at(Cur_num), scale_y.at(Cur_num), input, "Affine", Cur_num);
				AffineTransform();
			}
			else if (strData == L"Perspective") {
				input += L" image Perspective";
				inputImageData(Image_processing.at(Cur_num), scale_x.at(Cur_num), scale_y.at(Cur_num), input, "Perspective", Cur_num);
				PerspectiveTransform();
			}
			else {
				AfxMessageBox(_T("변환을 선택하세요!"));
			}
		}
		else {
			AfxMessageBox(_T("진행하고 있던 변환을 마치세요!"));
		}
	}
	else {
		AfxMessageBox(_T("변환할 이미지가 없습니다!"));
	}
}
HBRUSH COpenCVTestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	HBRUSH hk = CreateSolidBrush(RGB(255, 255, 255));
	return hk;
}
/*
이미지 저장을 하는 버튼을 눌렀을 때 액션이 작동하는 부분이다.

*/
void COpenCVTestDlg::OnBnClickedMfcbutton5()
{
	//선택한 이미지가 있다면 저장을 진행할수있도록 한다.

	if (image_listbox.GetCurSel() >= 0 && image_listbox.GetCurSel() <= Image_processing.size() - 1) {
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		CString path;

		CString szFilter = _T("PNG File(*.png)|*.png;|JPG File(*.jpg)|*.jpg;||");

		CFileDialog dlg(FALSE,
			_T(""),
			_T(""),
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			(LPCTSTR)szFilter.GetBuffer(), //(LPCTSTR)(szFilter),
			this
		);

		dlg.m_ofn.lpstrTitle = _T("이미지 저장");
		dlg.m_ofn.lpstrInitialDir = _T("");  //기본 경로 설정

		if (dlg.DoModal() == IDOK)
		{

			CString check = dlg.GetFileExt();
			if (check == "png" || check == "jpg") {
				path = dlg.GetPathName();  
				std::string sPath = std::string(CT2CA(path));
				vector<int> param_jpg, param_png, param_bmp;
				param_jpg.push_back(cv::IMWRITE_JPEG_QUALITY); 
				param_jpg.push_back(50);    
				param_png.push_back(cv::IMWRITE_PNG_COMPRESSION); 
				param_png.push_back(1); 
				if (check == "png") {
					imwrite(sPath, Image_processing.at((image_listbox.GetCurSel())), param_png);
				}
				if (check == "jpg") {
					imwrite(sPath, Image_processing.at((image_listbox.GetCurSel())), param_jpg);
				}
			}
			else AfxMessageBox(_T("확장자를 올바르게 선택하여 주십시오."));
		}
	}
	//저장할 이미지가 없다면 안내 메세지를 띄운다.
	else {
		AfxMessageBox(_T("저장할 이미지가 없습니다. \n"));
	}
}

/*
이미지 불러오기에 버튼을 누르면 작동을 수행하는 함수이다.

*/
void COpenCVTestDlg::OnBnClickedMfcbutton3()
{
	// 만약 변환을 하고 있던 이미지가 있다면, 새로운 이미지를 불러오게 되면 현재까지 했던 변환들은 사라지게 된다.
	if (!Image_processing.empty()) {
		if (IDYES == AfxMessageBox(_T("원본 파일을 다시 로드하게 됩니다. 진행하겠습니까?"), MB_YESNO))
		{
			//혹시 카메라가 켜져있으면 카메라를 강제 종료하게 만들기 위하여 만들었다.
			KillTimer(1000);
			//이미지를 새로 불러오므로, 현재까지 했던 변환들에 대한 이미지 정보를 다 제거한다.
			resetImageData();
			Cur_num = 0;
			GetDlgItem(IDC_PC_VIEW3)->ShowWindow(false);
			GetDlgItem(IDC_PC_VIEW3)->ShowWindow(true);
			GetDlgItem(IDC_PC_DOWNLOAD)->ShowWindow(false);
			GetDlgItem(IDC_PC_DOWNLOAD)->ShowWindow(true);
			GetDlgItem(IDC_PC_VIEW)->ShowWindow(false);
			GetDlgItem(IDC_PC_VIEW)->ShowWindow(true);
			CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, _T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"));
			if (fileDlg.DoModal() == IDOK)
			{
				Mat tmp;
				CString path = fileDlg.GetPathName();
				CT2CA pszString(path);
				std::string strPath(pszString);
				m_matImage = imread(strPath, IMREAD_UNCHANGED);
				tmp = DoPadding(m_matImage);
				DrawPictrue(IDC_PC_VIEW, tmp);
				inputImageData(tmp, 1.0, 1.0, L"Original","Original",Cur_num);
				GetDlgItem(IDC_RADIO3)->EnableWindow(TRUE);
				ShowExample_Translation();
			}
		}
	}
	else {
		KillTimer(1000);
		resetImageData();
		Cur_num = 0;
		GetDlgItem(IDC_PC_VIEW3)->ShowWindow(false);
		GetDlgItem(IDC_PC_VIEW3)->ShowWindow(true);
		GetDlgItem(IDC_PC_DOWNLOAD)->ShowWindow(false);
		GetDlgItem(IDC_PC_DOWNLOAD)->ShowWindow(true);
		GetDlgItem(IDC_PC_VIEW)->ShowWindow(false);
		GetDlgItem(IDC_PC_VIEW)->ShowWindow(true);
		CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, _T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"));
		if (fileDlg.DoModal() == IDOK)
		{
			Mat tmp;
			CString path = fileDlg.GetPathName();
			CT2CA pszString(path);
			std::string strPath(pszString);
			m_matImage = imread(strPath, IMREAD_UNCHANGED);

			tmp = DoPadding(m_matImage);
			DrawPictrue(IDC_PC_VIEW, tmp);
			inputImageData(tmp, 1.0, 1.0, L"Original", "Original", Cur_num);
			GetDlgItem(IDC_RADIO3)->EnableWindow(TRUE);
			ShowExample_Translation();
		}
	}
	//리스트 박스 정보를 갱신한다.
	RefreshListBox();
}


void COpenCVTestDlg::OnBnClickedMfcbutton4()
{
	capture = new VideoCapture(0);
	if (!capture->isOpened())
	{
		MessageBox(_T("웹캠을 열수 없습니다. \n"));
	}
	else if (capture->isOpened()) {
		if (!Image_processing.empty()) {
			if (IDYES == AfxMessageBox(_T("원본 파일을 삭제하고 카메라를 킵니다. 진행하겠습니까?"), MB_YESNO)) {
				Cur_num = 0;
				GetDlgItem(IDC_PC_VIEW3)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_PC_VIEW3)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_PC_DOWNLOAD)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_PC_DOWNLOAD)->ShowWindow(SW_SHOW);
				capture->set(CAP_PROP_FRAME_WIDTH, 1280);
				capture->set(CAP_PROP_FRAME_HEIGHT, 720);
				GetDlgItem(IDC_PC_VIEW)->ShowWindow(false);
				GetDlgItem(IDC_PC_VIEW)->ShowWindow(true);
				resetImageData();
				RefreshListBox();
				GetDlgItem(IDC_MFCBUTTON15)->ShowWindow(SW_SHOW);
				SetTimer(1000, 30, NULL);
			}
		}
		else {
			Cur_num = 0;
			capture->set(CAP_PROP_FRAME_WIDTH, 1280);
			capture->set(CAP_PROP_FRAME_HEIGHT, 720);
			GetDlgItem(IDC_PC_VIEW)->ShowWindow(false);
			GetDlgItem(IDC_PC_VIEW)->ShowWindow(true);
			resetImageData();
			RefreshListBox();
			GetDlgItem(IDC_MFCBUTTON15)->ShowWindow(SW_SHOW);
			SetTimer(1000, 30, NULL);
		}
	}
}



void COpenCVTestDlg::OnBnClickedMfcbutton10()
{
	if (image_listbox.GetCurSel() > -1 && image_listbox.GetCurSel() < Image_processing.size()) {
		Cur_num = image_listbox.GetCurSel();
		Mat tmp = DoPadding(Image_processing.at(Cur_num));
		ShowExample_Translation1(tmp);
	}
	else {
		AfxMessageBox(_T("이미지를 선택해주세요!"));
	}
}

void COpenCVTestDlg::OnBnClickedRadio3()
{
	example_mesh = FALSE;
	ShowExample_Translation();
}

void COpenCVTestDlg::OnBnClickedRadio1()
{
	example_mesh = TRUE;
	ShowExample_Translation();
}


void COpenCVTestDlg::OnBnClickedMfcbutton15()
{
	inputImageData(mat_temp, 1.0, 1.0, L"Original", "Original", Cur_num);
	KillTimer(1000);
	GetDlgItem(IDC_MFCBUTTON15)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PC_VIEW)->ShowWindow(false);
	GetDlgItem(IDC_PC_VIEW)->ShowWindow(true);
	DrawPictrue(IDC_PC_VIEW, DoPadding(mat_temp));
	RefreshListBox();
	ShowExample_Translation();
}


void COpenCVTestDlg::OnBnClickedMfcbutton16()
{
		if (!Image_processing.empty() && Image_processing.size() != 1) {
			imshow("Transform Image", Image_processing.at(Image_processing.size() - 1));
			while (getWindowProperty("Transform Image", WND_PROP_VISIBLE) >= 1) {
				imshow("Transform Image", Image_processing.at(Image_processing.size() - 1));
				if (waitKey(1) != -1) {
					destroyWindow("Transform Image");
					break;
				}
			}
		}
		else {
			AfxMessageBox(_T("변환된 이미지가 없습니다!"));
		}
}


void COpenCVTestDlg::OnBnClickedMfcbutton17()
{
	if (image_listbox.GetCurSel() >= 0 && image_listbox.GetCurSel() <= Image_processing.size() - 1) {
		imshow("Selected Image", Image_processing.at(Cur_num));
		while (getWindowProperty("Selected Image", WND_PROP_VISIBLE) >= 1) {
			imshow("Selected Image", Image_processing.at(image_listbox.GetCurSel()));
			if (waitKey(1) != -1) {
				destroyWindow("Selected Image");
				break;
			}
		}
	}
	else {
		AfxMessageBox(_T("이미지를 선택해주세요!"));
	}
}

void COpenCVTestDlg::DialogScaleTotal() {
	Mat image;
	Image_processing.at(Cur_num).copyTo(image);
	if(Cur_Scale_total*Cur_scale_x>0 && Cur_Scale_total * Cur_scale_y > 0)
	resize(image, scaledImage, Size(), Cur_Scale_total * Cur_scale_x, Cur_Scale_total * Cur_scale_y, m_interpolation.GetCurSel());
	// Display the image
	imshow("Scaling", scaledImage);
}

void COpenCVTestDlg::DialogRotation() {
	Mat image;
	Image_processing.at(Cur_num).copyTo(image);
	Point2f point_center(image.cols / 2.0, image.rows / 2.0);
	Mat rot = cv::getRotationMatrix2D(point_center, RotatingAngle, 1.0);
	Rect bbox = cv::RotatedRect(point_center, image.size(), RotatingAngle).boundingRect();
	rot.at<double>(0, 2) += bbox.width / 2.0 - point_center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - point_center.y;
	img_rotated = getRotationMatrix2D(point_center, RotatingAngle, 1.0);
	warpAffine(image, img_rotated, rot, bbox.size());
	imshow("Rotation", img_rotated);
}

void COpenCVTestDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (start) {
		DrawPictrue(IDC_PC_VIEW, Image_processing.at(Cur_num));
		start = false;
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

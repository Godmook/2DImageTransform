
// OpenCVTestDlg.h : header file
//

#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <vector>
#include <conio.h>
#include<Windows.h>
#include "ScaleDialog.h"
#include "RotationDialog.h"
#pragma comment (lib, "opencv_world453")
using namespace cv;
using namespace std;
// COpenCVTestDlg dialog
class COpenCVTestDlg : public CDialogEx
{
// Construction
public:
	COpenCVTestDlg(CWnd* pParent = NULL);	// standard constructor
	ScaleDialog* m_scale_dlg;	//Scaling하는 모습 보여주는 dialog랑 연결
	RotationDialog* m_rotate_dlg;	//Rotation하는 모습 보여주는 Dialog 랑 연결
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENCVTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public :
	Mat m_matImage; // 이미지 정보를 담고 있는 객체.
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();	//다이오로그 시작 세팅
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNcPaint();
	BOOL start = true;			//프로그램을 시작했는지 확인용
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	VideoCapture* capture;
	Mat mat_temp;
	Mat img_rotated;
	Mat img_translated;
	vector<Mat> Image_processing;	//이미지 원본 저장
	vector<double>scale_x;			//x 확대 비율 저장 -> 이미지 예시를 보여줄 때 계산용
	vector<double>scale_y;			//y 확대 비율 저장 -> 이미지 예시를 보여줄 때 계산용
	vector<CString> Image_name;
	vector<String> Image_translation_name;
	vector<int> image_source_num;	//원본 변환이 어딘지 알려주는 변수
	void RefreshListBox();
	void Make_Transform_combo();
	void ScalingTransform();
	void Make_Interpolation_combo();
	//이동 변환 필요한 것 시작
	static void TranslationMouseCallBack(int event, int x, int y, int flags, void* param);
	void doTraslation(int event, int x, int y, int flags);
	Point st;
	Point ed;
	int move_x;	//Translation 한 x좌표 저장
	int move_y; //Translation 한 y좌표 저장
	void TranslationTransform();
	//이동 변환 필요한 것 끝
	//어핀 변환 필요한 것 시작
	static void AffineMouseCallBack(int event, int x, int y, int flags, void* param);
	void doAffine(int event, int x, int y, int flags);
	double getDist(Point center, Point st);
	vector<Point2f> src_pt;
	vector<Point2f>dst_pt;
	Mat affine_image_src;
	Mat affine_image_tmp;
	int affine_num;
	void AffineTransform();
	//어핀 변환 필요한 것 끝
	//투영 변환 필요한 것 시작
	static void PerspectiveMouseCallBack(int event, int x, int y, int flags, void* param);
	void doPerspective(int event, int x, int y, int flags);
	Mat Perspective_image_src;
	Mat Perspective_image_tmp;
	void PerspectiveTransform();
	//투영 변환 필요한 것 끝
	void ShowExample_Translation();
	void inputImageData(Mat input, double _x, double _y, CString inputstring, String name, int num);
	void resetImageData();
	void showTransformImage();
	void RotationTransform();
	bool ClickControl(int IDC_TARTGET, CPoint pt);
	void deleteImageData(int k);
private:
	CListBox image_listbox;
public:
	Mat scaledImage;
	int Cur_num;
	Mat DoPadding(Mat src);
	void DrawPictrue(int nID, Mat a);
	void ShowExample_Translation1(Mat tmp);
private:
	CComboBox Image_combo;
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnLbnSelchangeList5();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	CMFCButton m_test1;
	afx_msg void OnBnClickedMfcbutton1();
	CMFCButton m_trans;
	afx_msg void OnBnClickedMfcbutton2();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CMFCButton m_save;
	afx_msg void OnBnClickedMfcbutton5();
	CMFCButton m_load;
	afx_msg void OnBnClickedMfcbutton3();
	CMFCButton m_camera;
	afx_msg void OnBnClickedMfcbutton4();
	CMFCButton m_transformimage;
	CMFCButton m_curimage;
	CMFCButton m_transexample;
	CMFCButton m_transformed_image;
	CMFCButton m_select;
	afx_msg void OnBnClickedMfcbutton10();
	CMFCButton m_explain;
	CMFCButton m_trans_before;
	CMFCButton m_trans_after;
	CMFCButton m_title;
	BOOL CheckDoingAnotherTranslation();
	void DrawDashedLine(cv::Mat& img, cv::Point pt1, cv::Point pt2,
		cv::Scalar color, int thickness, std::string style,
		int gap);
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio1();
	int radio_pos;
	BOOL example_mesh;
	CMFCButton m_capture;
	afx_msg void OnBnClickedMfcbutton15();
	CMFCButton m_transorigin;
	CMFCButton m_selectorigin;
	afx_msg void OnBnClickedMfcbutton16();
	afx_msg void OnBnClickedMfcbutton17();
	CComboBox m_interpolation;
	CMFCButton m_beonhwan;
	CMFCButton m_interpolate;
	double Cur_Scale_total;	//현재 확대 비율
	double Cur_scale_x;		//x 확대 비욜
	double Cur_scale_y;		//y 확대 비율

	int RotatingAngle;		//현재 각도
	void DialogScaleTotal();	//확대 계산 후 출력
	void DialogRotation();		//각도 계산 후 출력
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
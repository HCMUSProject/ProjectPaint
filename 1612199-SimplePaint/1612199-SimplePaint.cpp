// 1612199-SimplePaint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1612199-SimplePaint.h"
#include <windowsx.h>
#include <commctrl.h>
#pragma comment(lib, "Comctl32.lib")
#include <commdlg.h>
#include <vector>

#include "CStyle.h"
#include "CPoint.h"
#include "CShape.h"
#include "CLine.h"
#include "CRectangle.h"
#include "CEllipse.h"
#include "CCircle.h"
#include "CSquare.h"
using namespace std;
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnPaint(HWND hwnd);
void OnDestroy(HWND hwnd);
void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY1612199SIMPLEPAINT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1612199SIMPLEPAINT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1612199SIMPLEPAINT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1612199SIMPLEPAINT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLButtonDown);
		HANDLE_MSG(hWnd, WM_LBUTTONUP, OnLButtonUp);
		HANDLE_MSG(hWnd, WM_MOUSEMOVE, OnMouseMove);

		

    //case WM_COMMAND:
    //    {
    //        int wmId = LOWORD(wParam);
    //        // Parse the menu selections:
    //        switch (wmId)
    //        {
    //        case IDM_ABOUT:
    //            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
    //            break;
    //        case IDM_EXIT:
    //            DestroyWindow(hWnd);
    //            break;
    //        default:
    //            return DefWindowProc(hWnd, message, wParam, lParam);
    //        }
    //    }
    //    break;
    //case WM_PAINT:
    //    {
    //        PAINTSTRUCT ps;
    //        HDC hdc = BeginPaint(hWnd, &ps);
    //        // TODO: Add any drawing code that uses hdc here...
    //        EndPaint(hWnd, &ps);
    //    }
    //    break;
    //case WM_DESTROY:
    //    PostQuitMessage(0);
    //    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
// ================ My Global Variable ===================
#define IMAGE_WIDTH     18
#define IMAGE_HEIGHT    18
#define BUTTON_WIDTH    0
#define BUTTON_HEIGHT   0
#define BTN_LINE 0
#define BTN_RECTANGLE 1
#define BTN_SQUARE 2
#define BTN_ELLIPSE 3
#define BTN_CIRCLE 4
#define BTN_DOT 5


CStyle g_StypePen;
vector<CShape*> g_ListShape;
bool isDrawing = false;
CPoint CP_Start, CP_End;
CShape* g_ShapeDrawing = NULL;
bool MouseMove = false;
int nTypeOfShapeNow = BTN_LINE;

// =======

CHOOSECOLOR  cc; // Thông tin màu chọn
COLORREF  acrCustClr[16]; // Mảng custom color
DWORD  rgbCurrent = RGB(255, 0, 0); // Red
HBRUSH  hbrush; // Tạo ra brush từ màu đã chọn

// ==================== My Functions =====================

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) 
{
	// Lấy font hệ thống
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	InitCommonControls();
	TBBUTTON tbButtons[] =
	{
		{ STD_FILENEW,	ID_FILE_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		/*{ STD_FILEOPEN,	ID_FILE_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ STD_FILESAVE,	ID_FILE_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }*/
	};

	HWND hToolBarWnd = CreateToolbarEx(hwnd,
		WS_CHILD | WS_VISIBLE | CCS_ADJUSTABLE | TBSTYLE_TOOLTIPS,
		ID_TOOLBAR, sizeof(tbButtons) / sizeof(TBBUTTON), HINST_COMMCTRL,
		0, tbButtons, sizeof(tbButtons) / sizeof(TBBUTTON),
		BUTTON_WIDTH, BUTTON_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT,
		sizeof(TBBUTTON));
	
	TBBUTTON userButtons[] =
	{
		{ 0, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 },
		{ 0, ID_DRAW_DOT,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ 1, ID_DRAW_ELLIPSE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ 2, ID_DRAW_CIRCLE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ 3, ID_DRAW_RECTANGLE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ 4, ID_DRAW_SQUARE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ 5, ID_DRAW_LINE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }
	};
	TBADDBITMAP	tbBitmap = { hInst, IDB_BITMAP1 };
	// Thêm danh sách ảnh vào toolbar
	int idx = SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM) sizeof(tbBitmap) / sizeof(TBADDBITMAP),
		(LPARAM)(LPTBADDBITMAP)&tbBitmap);
	// Xác định chỉ mục hình ảnh c ủa mỗi button từ ảnh bự liên hoàn nhiều tấm
	userButtons[1].iBitmap += idx;
	userButtons[2].iBitmap += idx;
	userButtons[3].iBitmap += idx;
	userButtons[4].iBitmap += idx;
	userButtons[5].iBitmap += idx;
	userButtons[6].iBitmap += idx;
	// Thêm nút bấm vào toolbar
	SendMessage(hToolBarWnd, TB_ADDBUTTONS, (WPARAM) sizeof(userButtons) / sizeof(TBBUTTON),
		(LPARAM)(LPTBBUTTON)&userButtons);
	
	return true;
}
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case ID_FILE_NEW:
		g_ListShape.clear();
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hwnd);
		break;
		// color
	case ID_CHOOSE_COLOR:
		ZeroMemory(&cc, sizeof(CHOOSECOLOR));
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = hwnd;
		cc.lpCustColors = (LPDWORD)acrCustClr;
		cc.rgbResult = rgbCurrent;
		cc.Flags = CC_FULLOPEN | CC_RGBINIT;
		if (ChooseColor(&cc))
		{
			hbrush = CreateSolidBrush(cc.rgbResult);
			rgbCurrent = cc.rgbResult;
		}
		g_StypePen.SetColor(rgbCurrent);
		break;

		// button
	case ID_DRAW_DOT:
		nTypeOfShapeNow = BTN_DOT;
		break;
	case ID_DRAW_ELLIPSE:
		nTypeOfShapeNow = BTN_ELLIPSE;
		break;
	case ID_DRAW_CIRCLE:
		nTypeOfShapeNow = BTN_CIRCLE;
		break;
	case ID_DRAW_RECTANGLE:
		nTypeOfShapeNow = BTN_RECTANGLE;
		break;
	case ID_DRAW_SQUARE:
		nTypeOfShapeNow = BTN_SQUARE;
		break;
	case ID_DRAW_LINE:
		nTypeOfShapeNow = BTN_LINE;
		break;
	}
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	// TODO: Add any drawing code that uses hdc here...
	
	
	for (int i = 0; i < g_ListShape.size(); i++)
	{
		if (g_ListShape[i] != NULL)
		{
			g_ListShape[i]->Draw(hdc);
		}
	}
	if (isDrawing)
	{
		switch (nTypeOfShapeNow)
		{
		case BTN_LINE:
			g_ShapeDrawing = new CLine(CP_Start, CP_End);
			break;
		case BTN_RECTANGLE:
			g_ShapeDrawing = new CRectangle(CP_Start, CP_End);
			break;
		case BTN_SQUARE:
			g_ShapeDrawing = new CSquare(CP_Start, CP_End);
			break;
		case BTN_ELLIPSE:
			g_ShapeDrawing = new CEllipse(CP_Start, CP_End);
			break;
		case BTN_CIRCLE:
			g_ShapeDrawing = new CCircle(CP_Start, CP_End);
			break;
		case BTN_DOT:

			break;
		}

		g_ShapeDrawing->SetStyle(g_StypePen);
		g_ShapeDrawing->Draw(hdc);
	}

	EndPaint(hwnd, &ps);
}
void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}
void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	isDrawing = true;
	CP_Start.SetX(x);
	CP_Start.SetY(y);
	HDC hdc = GetDC(hwnd);
	MoveToEx(hdc, CP_Start.GetX(), CP_Start.GetY(), NULL);
}
void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
	if (MouseMove == false)
	{
		CP_End.SetX(CP_Start.GetX());
		CP_End.SetY(CP_Start.GetY());
	}
	else
	{
		MouseMove = false;
		g_ListShape.push_back(g_ShapeDrawing->Clone());
	}

	isDrawing = false;
	delete g_ShapeDrawing;
	// Báo hiệu cần xóa đi toàn bộ màn hình & vẽ lại
	InvalidateRect(hwnd, NULL, TRUE);
	
}
void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
	if (isDrawing) {
		MouseMove = true;
		CP_End.SetX(x);
		CP_End.SetY(y);

		// Báo hiệu cần xóa đi toàn bộ màn hình
		// bị lỗi khi mousemove thì màn hình xóa rồi vẽ lại liên tục.
		InvalidateRect(hwnd, NULL, TRUE);
	}
}
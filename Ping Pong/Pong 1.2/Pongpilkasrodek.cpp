// Pong 1.2.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Pong 1.2.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
WCHAR szBallClass[MAX_LOADSTRING];              // the main window class name
WCHAR szPaddleClass[MAX_LOADSTRING];            // the main window class name
HWND  hWnd;
HWND  bAll;
HWND  pAddle;
HRGN ballreg;

// Forward declarations of functions included in this code module:
ATOM                RegisterMainClass(HINSTANCE hInstance);
ATOM                RegisterBallClass(HINSTANCE hInstance);
ATOM                RegisterPaddleClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProcMain(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProcBall(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProcPaddle(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_PONG12, szWindowClass, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_BALL, szBallClass, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_PADDLE, szPaddleClass, MAX_LOADSTRING);
    RegisterMainClass(hInstance);
    RegisterBallClass(hInstance);
    RegisterPaddleClass(hInstance);
    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PONG12));

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
ATOM RegisterMainClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    HBRUSH bg = CreateSolidBrush(RGB(255, 255, 0));
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProcMain;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PONG12));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = bg;
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PONG12);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

ATOM RegisterBallClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex2;
    HBRUSH bg = CreateSolidBrush(RGB(255, 0, 0));
    wcex2.cbSize = sizeof(WNDCLASSEX);

    wcex2.style = CS_HREDRAW | CS_VREDRAW;
    wcex2.lpfnWndProc = WndProcBall;
    wcex2.cbClsExtra = 0;
    wcex2.cbWndExtra = 0;
    wcex2.hInstance = hInstance;
    wcex2.hIcon = 0;
    wcex2.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex2.hbrBackground = bg;
    wcex2.lpszMenuName = MAKEINTRESOURCEW(IDS_BALL);
    wcex2.lpszClassName = szBallClass;
    wcex2.hIconSm = 0;

    return RegisterClassExW(&wcex2);
}

ATOM RegisterPaddleClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex3;
    //HBRUSH bg = CreateSolidBrush(RGB(20, 20, 20));
    wcex3.cbSize = sizeof(WNDCLASSEX);

    wcex3.style = CS_HREDRAW | CS_VREDRAW;
    wcex3.lpfnWndProc = WndProcBall;
    wcex3.cbClsExtra = 0;
    wcex3.cbWndExtra = 0;
    wcex3.hInstance = hInstance;
    wcex3.hIcon = 0;
    wcex3.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex3.hbrBackground = (HBRUSH)(COLOR_WINDOW(-1));
    wcex3.lpszMenuName = MAKEINTRESOURCEW(IDS_PADDLE);
    wcex3.lpszClassName = szPaddleClass;
    wcex3.hIconSm = 0;

    return RegisterClassExW(&wcex2);
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
   int xx = GetSystemMetrics(0);
   int yy = GetSystemMetrics(1);
   int x = 500;
   int y = 300;
   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED|WS_SYSMENU|WS_MINIMIZEBOX, (xx-x)/2, (yy-y)/2, x, y, nullptr, nullptr, hInstance, nullptr);
   if (hWnd==NULL)
   {
      MessageBox(NULL, L"Main Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
      return FALSE;
   }
   SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
   SetLayeredWindowAttributes(hWnd, 0, (255 * 80) / 100, LWA_ALPHA);
   
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
LRESULT CALLBACK WndProcMain(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        RECT dlaball;
        GetClientRect(hWnd, &dlaball);
        int climidx = (dlaball.right - dlaball.left)/2;
        int climidy = (dlaball.bottom - dlaball.top)/2;
        int polpilki = 10;
        int polpaddla = 25;
        bAll = CreateWindowW(szBallClass, L"Ball", WS_CHILD | WS_VISIBLE, climidx-polpilki, climidy-polpilki, 2*polpilki,2*polpilki, hWnd, nullptr, hInst, nullptr);
        if (bAll == NULL)
        {
            MessageBox(NULL, L"Ball Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
            return FALSE;
        }
        SetWindowRgn(bAll, ballreg=CreateEllipticRgn(0, 0, 20, 20), 1);
        
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK WndProcBall(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        MessageBox(NULL, L"Stworzono kulkem", L":DD", MB_ICONEXCLAMATION | MB_OK);
    }
        break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK WndProcPaddle(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        MessageBox(NULL, L"Stworzono padla", L":DD", MB_ICONEXCLAMATION | MB_OK);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
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

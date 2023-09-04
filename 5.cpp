#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// The main window class name.
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Panzerkampfwagen VI");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//User functions

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Win32 Guided Tour"),
            NULL);

        return 1;
    }

    hInst = hInstance;


    HWND hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        300, 300,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Win32 Guided Tour"),
            NULL);

        return 1;
    }


    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
const POINT head[6] = { 6,115,109,84,242,115 };
const POINT window[6] = { 42,111,107,87,175,104 };

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hDC;
    HBRUSH FonOkna;
    HPEN RamkaOkna;
    HBRUSH oldBrush;
    HPEN oldPen;
    HPEN Koleso;
    HBRUSH FonKoleso;
    HPEN Korpus;
    HBRUSH FonKorpusa;
    HPEN Head;
    HBRUSH Window;
    switch (message)
    {
    case WM_PAINT:
        hDC = BeginPaint(hWnd, &ps);
        /*********************************************************************************
                                        G D I
        **********************************************************************************/
        //const POINT head[6] = { 14,115,109,84,244,115 };
        /* рисуем окно для рисунка */
        /* сначала создаем необходимые графические объекты */
        FonOkna = CreateSolidBrush(RGB(255, 255, 255)); /* фон окна */
        RamkaOkna = CreatePen(PS_DASH, 3, RGB(0, 0, 255)); /* рамка */
        /* загружаем созданные объекты в контекст устройства */
        /* при этом запоминаем предыдущие объекты */
        oldBrush = (HBRUSH)SelectObject(hDC, FonOkna);
        oldPen = (HPEN)SelectObject(hDC, RamkaOkna);
        /* рисуем прямоугольник с закругленными краями */
        RoundRect(hDC, 1, 1, 250, 250, 40, 40);

       // Polygon(hDC, head, 5);
        Koleso = CreatePen(PS_SOLID, 3, RGB(8, 0, 8));
        FonKoleso = CreateSolidBrush(RGB(8, 0, 8));
        SelectObject(hDC, Koleso);
        SelectObject(hDC, FonKoleso);
        Ellipse(hDC, 19, 127, 55, 163);
        Ellipse(hDC, 181, 127, 217, 163);
        Korpus = CreatePen(PS_SOLID, 1, RGB(101, 102, 101));
        FonKorpusa = CreateSolidBrush(RGB(101, 102, 101));
        SelectObject(hDC, FonKorpusa);
        SelectObject(hDC, Korpus);
        Rectangle(hDC, 6,116,244,141);
        Head = CreatePen(PS_SOLID, 2, RGB(153, 154, 153));
        SelectObject(hDC, Head);
        Polygon(hDC, head, 3);
        Window = CreateHatchBrush(HS_BDIAGONAL,RGB(70, 30, 40));
        SelectObject(hDC, Window);
        Polygon(hDC, window, 3);
        SetTextColor(hDC, RGB(128, 128, 0));
        SetBkColor(hDC, RGB(200, 200, 255));
        SetTextAlign(hDC, TA_CENTER | TA_TOP);
        TextOut(hDC, 125, 160, L"Дулинец", 7);
        TextOut(hDC, 125, 220, L"Tesla Cybertruck", 16);




        DeleteObject(FonOkna);
        DeleteObject(RamkaOkna);
        DeleteObject(oldBrush);
        DeleteObject(oldPen);
        DeleteObject(Koleso);
        DeleteObject(FonKoleso);
        DeleteObject(Korpus);
        DeleteObject(FonKorpusa);
        DeleteObject(Head);
        DeleteObject(Window);
     
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}

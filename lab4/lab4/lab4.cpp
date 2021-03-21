// lab4.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab4.h"

#define MAX_LOADSTRING 100
DWORD _stdcall Thread1(CONST LPVOID lpParam);
DWORD _stdcall Thread2(CONST LPVOID lpParam);
HWND hWnd;

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HBRUSH brush;

int hight = 800;
int check = 0;
std::string curTimeStr;
char curTimeChar[9];
wchar_t curTime[9];
RECT clientRect; 
int timezone = 0; // часовой пояс

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void current_time();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB4));

    MSG msg;

    // Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB4);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, 400, hight, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
bool bFin = false;
HANDLE thread[2];

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
        PostMessage(hWnd, WM_COMMAND, (WPARAM)WM_USER + 1, 0);
        break;
    case WM_RBUTTONDOWN:
        PostMessage(hWnd, WM_COMMAND, (WPARAM)WM_USER + 2, 0);
        break;
    case WM_CREATE:
    {
        // MultiThread();
        // InvalidateRect(hWnd, NULL, true);
    }
    case WM_COMMAND:
        {
            DWORD dwIDThread1;
            DWORD dwIDThread2;
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case WM_USER + 1:
                bFin = true;
                thread[0] = CreateThread(NULL, 0, Thread1, NULL, 0, &dwIDThread1);
                thread[1] = CreateThread(NULL, 0, Thread2, NULL, 0, &dwIDThread2);
                break;
            case WM_USER + 2:
                bFin = false;
                TerminateThread(thread[0], 0);
                TerminateThread(thread[1], 0);
            break;
            case ID_32771:
                timezone = 0;
                break;
            case ID_32773:
                timezone = 1;
                break;
            case ID_32774:
                timezone = 2;
                break;
            case ID_32775:
                timezone = 3;
                break;
            case ID_32779:
                timezone = -5;
                break;
            case ID_32780:
                timezone = -6;
                break;
            case ID_32781:
                timezone = -7;
                break;
            case ID_32782:
                timezone = -4;
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

            // задний фон светло-голубой
            GetClientRect(hWnd, &clientRect);
            brush = CreateSolidBrush(RGB(241, 248, 255));
            FillRect(hdc, &clientRect, brush);

            // инструкция
            TextOut(hdc, 10, 10, L"Щелчок ПКМ - запустить потоки", 29);
            TextOut(hdc, 10, 40, L"Щелчок ЛКМ - остановить потоки", 29);

            // Вывод темно-зеленого текста
            SetTextColor(hdc, RGB(20, 140, 70));
            TextOut(hdc, 210, hight-100, L"Темно-зеленый текст", 19);

            // Вывод current time
            SetTextColor(hdc, RGB(0, 0, 0));
            TextOut(hdc, 50, 350, curTime, 8);

            
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

// current time
void current_time() {
    SYSTEMTIME sm;
    GetLocalTime(&sm);
    if ((sm.wHour - 3 + timezone) > 24) {
        curTimeStr = std::to_string(sm.wHour + timezone - 27) + ':' + std::to_string(sm.wMinute) + ':' + std::to_string(sm.wSecond);
    }
    else {
        curTimeStr = std::to_string(sm.wHour - 3 + timezone) + ':' + std::to_string(sm.wMinute) + ':' + std::to_string(sm.wSecond);
    }

    for (int i = 0; i < 8; i++)
        curTimeChar[i] = curTimeStr[i];

    size_t convertedChars1 = 0;
    mbstowcs_s(&convertedChars1, curTime, 8, curTimeChar, _TRUNCATE);   
}

// Обработчик сообщений для окна "О программе".
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

DWORD _stdcall Thread1(CONST LPVOID lpParam)
{
    while (bFin) {
        if (hight > 120)
            hight -= 6;
        InvalidateRect(hWnd, NULL, TRUE);
        Sleep(1000);
    }
    ExitThread(0);
}

DWORD _stdcall Thread2(CONST LPVOID lpParam)
{
    while (bFin) {
        current_time();
        InvalidateRect(hWnd, NULL, TRUE);
        Sleep(1000);
    }
    ExitThread(0);
}
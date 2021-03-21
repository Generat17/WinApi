// lab3.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab3.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
int current_question = 0; // Текущий вопрос | использовуется для отрисовки нужного вопроса
int result[5] = { 0, 0, 0, 0, 0 };          // массив в который записываются ответы
int good_result[5] = { 3, 6, 10, 12, 17 };  // массив с правильными ответами
HWND hwndButton_1, hwndButton_2, hwndButton_3, hwndButton_4, hwndButton_5, hwndButton_6, hwndButton_7, hwndButton_8, hwndButton_9, hwndButton_10, hwndButton_11, hwndButton_12, hwndButton_13, hwndButton_14, hwndButton_15, hwndButton_16, hwndButton_17;

// переменные для изменения заднего фона
HBRUSH brush;
RECT clientRect;
int r = 255, g = 255, b = 255;

// Список вопросов-
wchar_t welcome_1[]  = L"Добро пожаловать в вeселую викторину по литературе";                                               // Приветствие
wchar_t welcome_2[]  = L"Нажмите кнопку \"Начать\" когда будете готовы.";                                                   // Приветствие
wchar_t question_1[] = L"Сколько лет пролежал на печи известный богатырь Илья Муромец?";                                    // 1) Ответ: 30 лет и 3 года        - 3_b
wchar_t question_2[] = L"Сказка «Курочка–Ряба» на самом деле имеет автора. Назовите его имя.";                              // 2) Ответ: Владимир Иванович Даль - 6_b
wchar_t question_3[] = L"Он знаком многим. Был и художником, и доктором, и путешественником, и космонавтом. Кто это?";      // 3) Ответ: Незнайка               - 10_b
wchar_t question_4[] = L"В Древней Греции на этих зданиях было написано: «Здесь живут мертвые и говорят живые».";           // 4) Ответ: На библиотеках         - 12_b
wchar_t question_5[] = L"Кому принадлежит выражение: «Краткость – сестра таланта».";                                        // 5) Ответ: А.П.Чехов              - 17_b

/*
wchar_t** answer = new wchar_t* [] {
    L"30 лет и 3 месяца", L"30 лет и 3 года", L"330 лет",
    L"Даль В.И.", L"Пушкин А.С.", L"А.П.Чехов",
    L"Мюнхгаузен", L"Незнайка", L"Гагарин Ю.А.",
    L"На библиотеках", L"На склепах", L"На храмах",
    L"Даль В.И.", L"Пушкин А.С.", L"А.П.Чехов"
};
*/
// Список ответов
wchar_t answer_3[] = L"30 лет и 3 месяца", answer_4[] = L"30 лет и 3 года", answer_5[] = L"330 лет";
wchar_t answer_6[] = L"Даль В.И.", answer_7[] = L"Пушкин А.С.", answer_8[] = L"А.П.Чехов";
wchar_t answer_9[] = L"Мюнхгаузен", answer_10[] = L"Незнайка", answer_11[] = L"Гагарин Ю.А.";
wchar_t answer_12[] = L"На библиотеках", answer_13[] = L"На склепах", answer_14[] = L"На храмах";
wchar_t answer_15[] = L"Даль В.И.", answer_16[] = L"Пушкин А.С.", answer_17[] = L"А.П.Чехов";

void check_answer(HDC hdc, int i, int x, int y) {
    if (result[i] == good_result[i]) {
        //true
        SetTextColor(hdc, RGB(0, 255, 0));
        TextOut(hdc, x, y, L"Правильный ", ARRAYSIZE("Правильный "));
        SetTextColor(hdc, RGB(0, 0, 0));
    }
    else {
        //false
        SetTextColor(hdc, RGB(255, 0, 0));
        TextOut(hdc, x, y, L"Неправильный ", ARRAYSIZE("Неправильный "));
        SetTextColor(hdc, RGB(0, 0, 0));
    }
}

void button_question_1(HWND hWnd) {
    DestroyWindow(hwndButton_1);
    DestroyWindow(hwndButton_2);
    // Вопрос 1 Вариант 1
    hwndButton_3 = CreateWindow(
        L"BUTTON",
        answer_3,
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10,	    // x position 
        100,    // y position 
        150,    // Button width  
        50,     // Button height
        hWnd,
        reinterpret_cast<HMENU>(3),
        nullptr,
        nullptr);
    // Вопрос 1 Вариант 2
    hwndButton_4 = CreateWindow(
        L"BUTTON",
        answer_4,
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        170,	// x position 
        100,    // y position 
        150,    // Button width  
        50,     // Button height
        hWnd,
        reinterpret_cast<HMENU>(4),
        nullptr,
        nullptr);
    // Вопрос 1 Вариант 3
    hwndButton_5 = CreateWindow(
        L"BUTTON",
        answer_5,
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        330,	// x position 
        100,    // y position 
        150,    // Button width  
        50,     // Button height
        hWnd,
        reinterpret_cast<HMENU>(5),
        nullptr,
        nullptr);
}

void button_question_2(HWND hWnd) {
    DestroyWindow(hwndButton_3);
    DestroyWindow(hwndButton_4);
    DestroyWindow(hwndButton_5);
    // Вопрос 2 Вариант 1
    hwndButton_6 = CreateWindow(
        L"BUTTON",
        answer_6,
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10,	    // x position 
        100,    // y position 
        150,    // Button width  
        50,     // Button height
        hWnd,
        reinterpret_cast<HMENU>(6),
        nullptr,
        nullptr);
    // Вопрос 2 Вариант 2
    hwndButton_7 = CreateWindow(
        L"BUTTON",
        answer_7,
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        170,	// x position 
        100,    // y position 
        150,    // Button width  
        50,     // Button height
        hWnd,
        reinterpret_cast<HMENU>(7),
        nullptr,
        nullptr);
    // Вопрос 2 Вариант 3
    hwndButton_8 = CreateWindow(
        L"BUTTON",
        answer_8,
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        330,	// x position 
        100,    // y position 
        150,    // Button width  
        50,     // Button height
        hWnd,
        reinterpret_cast<HMENU>(8),
        nullptr,
        nullptr);
}

void button_question_3(HWND hWnd) {
    DestroyWindow(hwndButton_6);
    DestroyWindow(hwndButton_7);
    DestroyWindow(hwndButton_8);
    // Вопрос 3 Вариант 1
    hwndButton_9 = CreateWindow(
        L"BUTTON",
        answer_9,
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10,	    // x position 
        100,    // y position 
        150,    // Button width  
        50,     // Button height
        hWnd,
        reinterpret_cast<HMENU>(9),
        nullptr,
        nullptr);
    // Вопрос 3 Вариант 2
    hwndButton_10 = CreateWindow(
        L"BUTTON",
        answer_10,
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        170,	// x position 
        100,    // y position 
        150,    // Button width  
        50,     // Button height
        hWnd,
        reinterpret_cast<HMENU>(10),
        nullptr,
        nullptr);
    // Вопрос 3 Вариант 3
    hwndButton_11 = CreateWindow(
        L"BUTTON",
        answer_11,
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        330,	// x position 
        100,    // y position 
        150,    // Button width  
        50,     // Button height
        hWnd,
        reinterpret_cast<HMENU>(11),
        nullptr,
        nullptr);
}

void button_question_4(HWND hWnd) {
    DestroyWindow(hwndButton_9);
    DestroyWindow(hwndButton_10);
    DestroyWindow(hwndButton_11);
    // Вопрос 4 Вариант 1
    hwndButton_12 = CreateWindow(
        L"BUTTON",
        answer_12,
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10,	    // x position 
        100,    // y position 
        150,    // Button width  
        50,     // Button height
        hWnd,
        reinterpret_cast<HMENU>(12),
        nullptr,
        nullptr);
    // Вопрос 4 Вариант 2
    hwndButton_13 = CreateWindow(
        L"BUTTON",
        answer_13,
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        170,	// x position 
        100,    // y position 
        150,    // Button width  
        50,     // Button height
        hWnd,
        reinterpret_cast<HMENU>(13),
        nullptr,
        nullptr);
    // Вопрос 4 Вариант 3
    hwndButton_14 = CreateWindow(
        L"BUTTON",
        answer_14,
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        330,	// x position 
        100,    // y position 
        150,    // Button width  
        50,     // Button height
        hWnd,
        reinterpret_cast<HMENU>(14),
        nullptr,
        nullptr);
}

void button_question_5(HWND hWnd) {
    DestroyWindow(hwndButton_12);
    DestroyWindow(hwndButton_13);
    DestroyWindow(hwndButton_14);
    // Вопрос 5 Вариант 1
    hwndButton_15 = CreateWindow(
        L"BUTTON",
        L"Даль В.И.",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10,	    // x position 
        100,    // y position 
        150,    // Button width  
        50,     // Button height
        hWnd,
        reinterpret_cast<HMENU>(15),
        nullptr,
        nullptr);
    // Вопрос 5 Вариант 2
    hwndButton_16 = CreateWindow(
        L"BUTTON",
        L"Пушкин А.С.",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        170,	// x position 
        100,    // y position 
        150,    // Button width  
        50,     // Button height
        hWnd,
        reinterpret_cast<HMENU>(16),
        nullptr,
        nullptr);
    // Вопрос 5 Вариант 3
    hwndButton_17 = CreateWindow(
        L"BUTTON",
        L"А.П.Чехов",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        330,	// x position 
        100,    // y position 
        150,    // Button width  
        50,     // Button height
        hWnd,
        reinterpret_cast<HMENU>(17),
        nullptr,
        nullptr);
}

void button_question_6(HWND hWnd) {
    DestroyWindow(hwndButton_15);
    DestroyWindow(hwndButton_16);
    DestroyWindow(hwndButton_17);
    // Конец игры. Выход.
    hwndButton_2 = CreateWindow(
        L"BUTTON",
        L"Выйти",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        600,	    // x position 
        280,    // y position 
        150,    // Button width  
        50,     // Button height
        hWnd,
        reinterpret_cast<HMENU>(2),
        nullptr,
        nullptr);
}

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_LAB3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB3);
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
      CW_USEDEFAULT, CW_USEDEFAULT, 
       800, // width
       400, // height
       nullptr, nullptr, hInstance, nullptr);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        
    // Создание кнопки №1 "Начать"
    hwndButton_1 = CreateWindow(
        L"BUTTON",
        L"Начать",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        250,	// x position 
        100,    // y position 
        300,    // Button width  
        50,     // Button height
        hWnd,
        reinterpret_cast<HMENU>(1),
        nullptr,
        nullptr);
    // Создание кнопки №2 "Выйти"
    hwndButton_2 = CreateWindow(
        L"BUTTON",
        L"Выйти",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        250,	// x position 
        200,    // y position 
        300,    // Button width  
        50,     // Button height
        hWnd,
        reinterpret_cast<HMENU>(2),
        nullptr,
        nullptr);
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            // Страница 1
            case 1: {
                current_question = 1;
                button_question_1(hWnd);
                InvalidateRect(hWnd, NULL, true);
            } break;
            case 2: {
                DestroyWindow(hWnd);
            } break;

            // Страница 2
            case 3: {
                current_question = 2;
                button_question_2(hWnd);
                result[0] = 3;
                InvalidateRect(hWnd, NULL, true);
            } break;
            case 4: {
                current_question = 2;
                button_question_2(hWnd);
                result[0] = 4;
                InvalidateRect(hWnd, NULL, true);
            } break;
            case 5: {
                current_question = 2;
                button_question_2(hWnd);
                result[0] = 5;
                InvalidateRect(hWnd, NULL, true);
            } break;

            // Страница 3
            case 6: {
                current_question = 3;
                button_question_3(hWnd);
                result[1] = 6;
                InvalidateRect(hWnd, NULL, true);
            } break;
            case 7: {
                current_question = 3;
                button_question_3(hWnd);
                result[1] = 7;
                InvalidateRect(hWnd, NULL, true);
            } break;
            case 8: {
                current_question = 3;
                button_question_3(hWnd);
                result[1] = 8;
                InvalidateRect(hWnd, NULL, true);
            } break;

            // Страница 4
            case 9: {
                current_question = 4;
                button_question_4(hWnd);
                result[2] = 9;
                InvalidateRect(hWnd, NULL, true);
            } break;
            case 10: {
                current_question = 4;
                button_question_4(hWnd);
                result[2] = 10;
                InvalidateRect(hWnd, NULL, true);
            } break;
            case 11: {
                current_question = 4;
                button_question_4(hWnd);
                result[2] = 11;
                InvalidateRect(hWnd, NULL, true);
            } break;

            // Страница 5
            case 12: {
                current_question = 5;
                button_question_5(hWnd);
                result[3] = 12;
                InvalidateRect(hWnd, NULL, true);
            } break;
            case 13: {
                current_question = 5;
                button_question_5(hWnd);
                result[3] = 13;
                InvalidateRect(hWnd, NULL, true);
            } break;
            case 14: {
                current_question = 5;
                button_question_5(hWnd);
                result[3] = 14;
                InvalidateRect(hWnd, NULL, true);
            } break;

            // Страница 6
            case 15: {
                current_question = 6;
                button_question_6(hWnd);
                result[4] = 15;
                InvalidateRect(hWnd, NULL, true);
            } break;
            case 16: {
                current_question = 6;
                button_question_6(hWnd);
                result[4] = 16;
                InvalidateRect(hWnd, NULL, true);
            } break;
            case 17: {
                current_question = 6;
                button_question_6(hWnd);
                result[4] = 17;
                InvalidateRect(hWnd, NULL, true);
            } break;

            // Страница 7
            case 18: {

            } break;

            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_32776: {
                r = 110; g = 177; b = 244;
                InvalidateRect(hWnd, NULL, true);
            } break;
            case ID_32777: {
                r = 173; g = 244; b = 102;
                InvalidateRect(hWnd, NULL, true);
            } break;
            case ID_32778: {
                r = 252; g = 164; b = 240;
                InvalidateRect(hWnd, NULL, true);
            } break;
            case ID_32779: {
                r = 255; g = 255; b = 255;
                InvalidateRect(hWnd, NULL, true);
            } break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            GetClientRect(hWnd, &clientRect);
            brush = CreateSolidBrush(RGB(r, g, b));
            FillRect(hdc, &clientRect, brush);
            
            switch (current_question){
                case 0: {
                    // Приветствие
                    TextOut(hdc, 200, 10, welcome_1, ARRAYSIZE(welcome_1));
                    TextOut(hdc, 225, 30, welcome_2, ARRAYSIZE(welcome_2));
                }break;

                case 1:{
                    // Вопрос 1
                    TextOut(hdc, 10, 10, L"Вопрос №1", ARRAYSIZE("Вопрос №1"));
                    TextOut(hdc, 10, 30, question_1, ARRAYSIZE(question_1));
                } break;

                case 2: {
                    // Вопрос 2
                    TextOut(hdc, 10, 10, L"Вопрос №2", ARRAYSIZE("Вопрос №2"));
                    TextOut(hdc, 10, 30, question_2, ARRAYSIZE(question_2));
                } break;

                case 3: {
                    // Вопрос 3
                    TextOut(hdc, 10, 10, L"Вопрос №3", ARRAYSIZE("Вопрос №3"));
                    TextOut(hdc, 10, 30, question_3, ARRAYSIZE(question_3));
                } break;

                case 4: {
                    // Вопрос 4
                    TextOut(hdc, 10, 10, L"Вопрос №4", ARRAYSIZE("Вопрос №4"));
                    TextOut(hdc, 10, 30, question_4, ARRAYSIZE(question_4));
                } break;

                case 5: {
                    // Вопрос 5
                    TextOut(hdc, 10, 10, L"Вопрос №5", ARRAYSIZE("Вопрос №5"));
                    TextOut(hdc, 10, 30, question_5, ARRAYSIZE(question_5));
                } break;

                case 6: {
                    // результаты
                    TextOut(hdc, 10, 10, L"Конец. Результаты викторины:", ARRAYSIZE("Конец. Результаты викторины:"));
                    // Вопрос 1
                    TextOut(hdc, 10, 50, question_1, ARRAYSIZE(question_1));
                    TextOut(hdc, 10, 70, L"Правильный ответ: ", ARRAYSIZE("Правильный ответ: "));
                    TextOut(hdc, 150, 70, answer_3, ARRAYSIZE(answer_3));
                    TextOut(hdc, 360, 70, L"Ваш ответ: ", ARRAYSIZE("Ваш ответ: "));
                    check_answer(hdc, 0, 450, 70);

                    // Вопрос 2
                    TextOut(hdc, 10, 100, question_2, ARRAYSIZE(question_2));
                    TextOut(hdc, 10, 120, L"Правильный ответ: ", ARRAYSIZE("Правильный ответ: "));
                    TextOut(hdc, 150, 120, answer_6, ARRAYSIZE(answer_6));
                    TextOut(hdc, 360, 120, L"Ваш ответ: ", ARRAYSIZE("Ваш ответ: "));
                    check_answer(hdc, 1, 450, 120);

                    // Вопрос 3
                    TextOut(hdc, 10, 150, question_3, ARRAYSIZE(question_3));
                    TextOut(hdc, 10, 170, L"Правильный ответ: ", ARRAYSIZE("Правильный ответ: "));
                    TextOut(hdc, 150, 170, answer_10, ARRAYSIZE(answer_10));
                    TextOut(hdc, 360, 170, L"Ваш ответ: ", ARRAYSIZE("Ваш ответ: "));
                    check_answer(hdc, 2, 450, 170);

                    // Вопрос 4
                    TextOut(hdc, 10, 200, question_4, ARRAYSIZE(question_4));
                    TextOut(hdc, 10, 220, L"Правильный ответ: ", ARRAYSIZE("Правильный ответ: "));
                    TextOut(hdc, 150, 220, answer_12, ARRAYSIZE(answer_12));
                    TextOut(hdc, 360, 220, L"Ваш ответ: ", ARRAYSIZE("Ваш ответ: "));
                    check_answer(hdc, 3, 450, 220);

                    // Вопрос 5
                    TextOut(hdc, 10, 250, question_5, ARRAYSIZE(question_5));
                    TextOut(hdc, 10, 270, L"Правильный ответ: ", ARRAYSIZE("Правильный ответ: "));
                    TextOut(hdc, 150, 270, answer_17, ARRAYSIZE(answer_17));
                    TextOut(hdc, 360, 270, L"Ваш ответ: ", ARRAYSIZE("Ваш ответ: "));
                    check_answer(hdc, 4, 450, 270);
                } break;
            }
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

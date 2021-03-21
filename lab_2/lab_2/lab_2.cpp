#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("Окно №1");

int WINAPI _tWinMain(HINSTANCE This,		// Дескриптор текущего приложения 
	HINSTANCE Prev, 						// В современных системах всегда 0 
	LPTSTR cmd, 							// Командная строка 
	int mode) 								// Режим отображения окна
{
	HWND hWnd;								// Дескриптор главного окна программы 
	MSG msg; 								// Структура для хранения сообщения 
	WNDCLASS wc; 							// Класс окна

	// Определение класса окна 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 					// Имя класса окна 
	wc.lpfnWndProc = WndProc; 						// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 	// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 						// Нет меню 
	wc.cbClsExtra = 0; 								// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 								// Нет дополнительных данных окна 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 	// Заполнение окна белым цветом 


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName,	// Имя класса окна 
		_T("Окно №1"), 				// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		635, 						// width 
		320, 						// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 						// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 		// Показать окно

	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 			// Посылает сообщение функции WndProc() 
	}
	return 0;
}

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)			// Обработчик сообщений
	{
	case WM_DESTROY:
		PostQuitMessage(0);		// Завершение программы 
		break; 	

	case WM_CREATE:
	{
		// Создание кнопки №1
		HWND hwndButton_1 = CreateWindow(
			L"BUTTON",  
			L"Найти дескриптор окна №2",      
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  
			10,		// x position 
			10,     // y position 
			600,    // Button width  
			50,     // Button height
			hWnd,     
			reinterpret_cast<HMENU>(1),      
			nullptr,
			nullptr);      

		// Создание кнопки №2
		HWND hwndButton_2 = CreateWindow(
			L"BUTTON",  
			L"Передать свой дескриптор окну №2",     
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
			10,       // x position 
			80,       // y position 
			600,      // Button width 
			50,       // Button height
			hWnd,    
			reinterpret_cast<HMENU>(2),       
			nullptr,
			nullptr);

		// Создание кнопки №3
		HWND hwndButton_3 = CreateWindow(
			L"BUTTON",
			L"Передать WM_USER+2 второму окну для открытия калькулятора",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			10,       // x position 
			150,      // y position 
			600,      // Button width 
			50,       // Button height
			hWnd,
			reinterpret_cast<HMENU>(3),
			nullptr,
			nullptr);

		// Создание кнопки №4
		HWND hwndButton_4 = CreateWindow(
			L"BUTTON",
			L"Передать WM_USER+3 второму окну для закрытия калькулятора",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			10,			// x position 
			220,		// y position 
			600,		// Button width 
			50,			// Button height
			hWnd,
			reinterpret_cast<HMENU>(4),
			nullptr,
			nullptr);
	}
	break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
			// описание того, что произойдет если нажать кнопку №1
			case 1: {
				HWND window_2 = FindWindow(LPCWSTR(L"Окно №2"), NULL);  // Найти дискриптор окна  и записать в переменную window_2
				if (window_2 == NULL) {
					// true
					MessageBox(hWnd, L"404 error", L"INFO", MB_ICONINFORMATION);
				}
				else {
					// false
					MessageBox(hWnd, L"ok", L"ok", MB_ICONINFORMATION);
				}
			} break;

			//описание того, что произойдет если нажать кнопку №2
			case 2: {
				HWND window_1 = FindWindow(LPCWSTR(L"Окно №1"), NULL);\
				HWND window_2 = FindWindow(LPCWSTR(L"Окно №2"), NULL);
				if ((window_1 == NULL)&&(window_2 == NULL)) {
					// true
					MessageBox(hWnd, L"404 error", L"INFO", MB_ICONINFORMATION);
				}
				else {
					// false
					MessageBox(hWnd, L"ok", L"ok", MB_ICONINFORMATION);
					SendMessage(window_2, WM_USER+1, WPARAM(window_1), NULL);
				}
			} break;

			//описание того, что произойдет если нажать кнопку №3
			case 3: {
				HWND window_1 = FindWindow(LPCWSTR(L"Окно №1"), NULL); 
				HWND window_2 = FindWindow(LPCWSTR(L"Окно №2"), NULL);
				if ((window_1 == NULL) && (window_2 == NULL)) {
					// true
					MessageBox(hWnd, L"404 error", L"INFO", MB_ICONINFORMATION);
				}
				else {
					// false
					SendMessage(window_2, WM_USER + 2, NULL, NULL);
				}
			} break;
			
			//описание того, что произойдет если нажать кнопку №4
			case 4: {
				HWND window_1 = FindWindow(LPCWSTR(L"Окно №1"), NULL); 
				HWND window_2 = FindWindow(LPCWSTR(L"Окно №2"), NULL);
				if ((window_1 == NULL) && (window_2 == NULL)) {
					// true
					MessageBox(hWnd, L"404 error", L"INFO", MB_ICONINFORMATION);
				}
				else {
					//false
					SendMessage(window_2, WM_USER + 3, NULL, NULL);
				}
			} break;
		}
	}
	break;

	default: 	// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

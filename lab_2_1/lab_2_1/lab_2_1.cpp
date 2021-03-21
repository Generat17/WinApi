#include <Windows.h>
#include <tchar.h>
#include <ctime>
#include <iostream>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// !!! Attention !!!
// Указать путь к приложению, которое необходимо открывать и закрывать (т.е. калькулятор)
wchar_t path[] = L"C:\\Windows\\System32\\calc1.exe";
// !!! Attention !!!
// !!! Attention !!!


TCHAR WinName[] = _T("Окно №2");

int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 			// Режим отображения окна
{
	HWND hWnd;			// Дескриптор главного окна программы 
	MSG msg; 			// Структура для хранения сообщения 
	WNDCLASS wc; 		// Класс окна
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
		_T("Окно №2"), 				// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		400, 						// width 
		400, 						// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 						// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 				// Показать окно

	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 	// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}
	return 0;
}

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения
PROCESS_INFORMATION pi;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)		 // Обработчик сообщений
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break; 				// Завершение программы 

	// этот блок выполняется если приложение получает сообщение WM_USER+1
	case WM_USER + 1: { 
		MessageBox(hWnd, L"Дескриптор окна №1 - получен", L"INFO", MB_ICONINFORMATION);
	}
	break;

	// этот блок выполняется если приложение получает сообщение WM_USER+2
	case WM_USER + 2: {
		STARTUPINFO cif;
		ZeroMemory(&cif, sizeof(STARTUPINFO));
		CreateProcess(path, NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &cif, &pi);
	}
	break;

	// этот блок выполняется если приложение получает сообщение WM_USER+3
	case WM_USER + 3: {
		TerminateProcess(pi.hProcess, NO_ERROR);
	}
	break;

	// по умолчанию
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Файл определяет точку входа для приложения.
#include "framework.h"
#include "Zaeb.h"
#include "windows.h"
#include "winuser.h"
#include <string>
#include <stdlib.h>
using namespace std;
#include "Source.cpp"
#include "Source1.cpp"
#define MAX_LOADSTRING 100

// Глобальные переменные:
// текущий экземпляр программного приложения
HINSTANCE hInst;
HWND Form1;
ObjectButton* lbl_text_hello = new ObjectButton(600, 10, 150, 100);
ObjectButton* btn_hide = new ObjectButton(150, 50, 50, 150);
ObjectButton* lbl_text_hide_button = new ObjectButton(600, 50, 200, 150);
ObjectButton* btn_change = new ObjectButton(150, 50, 50, 210);
ObjectButton* btn_show_message1 = new ObjectButton(150, 50, 400, 210);
ObjectButton* btn_show_message2 = new ObjectButton(150, 50, 400, 270);
ObjectButton* btn_show_message3 = new ObjectButton(150, 50, 400, 330);
ObjectButton* btn_exit = new ObjectButton(150, 50, 400, 390);

void execute_application_postion_and_size
(HWND Form, int width, int height)
{
	// системная функция ожидания
	// в качестве параметра принимает
	// период ожидания в мс
	Sleep(1000);
	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	int program_width = width;
	int program_height = height;
	int program_left = (screen_width / 2) - (program_width / 2);
	int program_top = (screen_height / 2) - (program_height / 2);
	SetWindowPos
	(
		Form,
		HWND_TOP,
		program_left,
		program_top,
		program_width,
		program_height,
		SWP_ASYNCWINDOWPOS
	);
}


void execute_button()
{
	int r, g, b;
	r = 200;
	g = 200;
	b = 200;
	btn_change->BorderColor = RGB(r, g, b);
	btn_change->TextColor = RGB(r - 30, g - 50, b - 70);
	btn_change->Caption = TEXT("Кнопочка горит");
	MessageBox(NULL,
		TEXT("Сделаем этот мир ярче"),
		TEXT("Кнопочка"), 0);
}
void ExecuteMyButton(ObjectButton* btn, HDC Canvas)
{
	if (btn->help_button_first_draw_status == 0)
	{
		btn->Left = btn->Left - 8;
		btn->Top = btn->Top - 51;
		btn->Create(Form1, Canvas);
		btn->Left = btn->Left + 8;
		btn->Top = btn->Top + 51;
	}
}
void ExitFromProgram()
{
	MessageBox(NULL, TEXT("Будет произведён выход из приложения"),
		TEXT("Выход"), 0);
	PostQuitMessage(1);
}
void MessAnna()
{
	MessageBox(NULL, TEXT("Миронович Анна Олеговна \n Год рождения: 27.08.2007 \n Город рождения: Вильнус \n Супер Сила: делать 10 задач параллельно"),
		TEXT("Информация о студенте"), 0);
}
void MessDaria()
{
	MessageBox(NULL, TEXT("Малышева Дарья Андреевна \n Год рождения: 12.10.2007 \n Город рождения: Златоуст \n Супер Сила: очаровывать всех и вся"),
		TEXT("Информация о студенте"), 0);
}
void MessVictoria()
{
	MessageBox(NULL, TEXT("Герман Виктория Викторовна \n Год рождения: 9.10.2007 \n Город рождения: Краснодар \n Супер Сила: хакнет даже чайник"),
		TEXT("Информация о студенте"), 0);
}


// Текст строки заголовка диалогового окна
WCHAR szTitle[MAX_LOADSTRING];
// имя класса диалогового окна
WCHAR szWindowClass[MAX_LOADSTRING];
// Вспомогательные функции
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE,
		szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_ZAEB,
		szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	// Выполнение инициализации приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return false;
	}
	HACCEL hAccelTable =
		LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ZAEB));
	MSG msg;
	// Цикл основного сообщения
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}
// Функция MyRegisterClass() регистрирует класс окна.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance,
		MAKEINTRESOURCE(IDI_ZAEB));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(16, 30, 161));
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ZAEB);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance,
		MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassExW(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	// Сохранение маркера экземпляра приложения
	// в глобальной переменной
	hInst = hInstance;
	HWND hWnd = CreateWindowW(szWindowClass,
		szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0,
		CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd)
	{
		return false;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return true;
}
LRESULT CALLBACK WndProc(HWND hWnd,
	UINT message, WPARAM wParam, LPARAM lParam)
{
	Form1 = hWnd;
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst,
				MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_CREATE:
	{
		execute_application_postion_and_size(Form1, 900, 450);
		lbl_text_hello->Caption = TEXT("Приветствуем в Тёмном Царстве! \n ГЛАВНОЕ МЕНЮ");
		lbl_text_hello->cfg_enable_border = 0;
		lbl_text_hello->cfg_text_size = 48;
		lbl_text_hello->TextColor = RGB(0, 0, 0);

		btn_hide->Caption = TEXT("҉*\( ‘ ω ’ )/*҉");

		//доделать
		lbl_text_hide_button->Caption =
			TEXT("<- Нажмите Tab для скрытия кнопки и W, чтобы снова ее показать");
		lbl_text_hide_button->cfg_enable_border = 0;
		lbl_text_hide_button->cfg_text_size = 24;
		lbl_text_hide_button->TextColor = RGB(0, 190, 231);

		btn_change->ButtonClick = &execute_button;
		btn_change->Caption = TEXT("Цветастая кнопочка");

		btn_show_message1->ButtonClick = &MessAnna;
		btn_show_message1->Caption = TEXT("Студент 1");
		btn_show_message1->TextColor = RGB(50, 50, 50);
		btn_show_message1->BorderColor = RGB(0, 0, 0);

		btn_show_message2->ButtonClick = &MessDaria;
		btn_show_message2->Caption = TEXT("Студент 2");
		btn_show_message2->TextColor = RGB(50, 50, 50);
		btn_show_message2->BorderColor = RGB(0, 0, 0);

		btn_show_message3->ButtonClick = &MessVictoria;
		btn_show_message3->Caption = TEXT("Студент 3");
		btn_show_message3->TextColor = RGB(50, 50, 50);
		btn_show_message3->BorderColor = RGB(0, 0, 0);

		btn_exit->Caption = TEXT("Выход");
		btn_exit->TextColor = RGB(255, 52, 9);
		btn_exit->BorderColor = RGB(255, 52, 9);
		btn_exit->ButtonClick = &ExitFromProgram;
	}
	break;
	case WM_KEYDOWN:
	{
		if (wParam == VK_TAB)
		{
			btn_hide->ClearButtonDraw(Form1);
		}
		if (0x57 & GetAsyncKeyState(0x51))
		{
			HDC hdc = GetWindowDC(Form1);
			btn_hide->help_button_active_status = 1;
			btn_hide->ActiveButtonAnimate(Form1, hdc);
		}
	}
	break;
	case WM_MOUSEMOVE:
	{
		HDC hdc = GetWindowDC(Form1);
		btn_change->ActiveButtonAnimate(Form1, hdc);
		btn_exit->ActiveButtonAnimate(Form1, hdc);
		btn_show_message1->ActiveButtonAnimate(Form1, hdc);
		btn_show_message2->ActiveButtonAnimate(Form1, hdc);
		btn_show_message3->ActiveButtonAnimate(Form1, hdc);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		btn_change->
			CheckMouseCoordinatesBeforeStartClickFunction(Form1);
		btn_exit->CheckMouseCoordinatesBeforeStartClickFunction(Form1);
		btn_show_message1->
			CheckMouseCoordinatesBeforeStartClickFunction(Form1);
		btn_show_message2->
			CheckMouseCoordinatesBeforeStartClickFunction(Form1);
		btn_show_message3->
			CheckMouseCoordinatesBeforeStartClickFunction(Form1);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		if (lbl_text_hello->help_button_first_draw_status == 0)
		{
			lbl_text_hello->Left = lbl_text_hello->Left - 8;
			lbl_text_hello->Top = lbl_text_hello->Top - 51;
			lbl_text_hello->Create(Form1, hdc);
			lbl_text_hello->Left = lbl_text_hello->Left + 8;
			lbl_text_hello->Top = lbl_text_hello->Top + 51;
		}
		ExecuteMyButton(btn_change, hdc);
		ExecuteMyButton(lbl_text_hello, hdc);
		ExecuteMyButton(lbl_text_hide_button, hdc);
		ExecuteMyButton(btn_exit, hdc);
		ExecuteMyButton(btn_hide, hdc);
		ExecuteMyButton(btn_show_message1, hdc);
		ExecuteMyButton(btn_show_message2, hdc);
		ExecuteMyButton(btn_show_message3, hdc);
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
// Обработчик сообщений для окна «О программе».
INT_PTR CALLBACK About(HWND hDlg, UINT message,
	WPARAM wParam, LPARAM lParam)
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
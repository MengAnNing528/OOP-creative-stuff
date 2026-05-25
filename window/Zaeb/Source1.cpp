// Класс кнопки
#include "framework.h"
#include "windows.h"
#include "winuser.h"
class ObjectButton
{
private:
public:
	int Width = 100;
	int Height = 40;
	int Left = 10;
	int Top = 10;
	COLORREF BorderColor = RGB(0, 0, 0);
	COLORREF TextColor = RGB(0, 0, 0);
	COLORREF BorderActiveColor = RGB(120, 150, 120);
	COLORREF TextActiveColor = RGB(120, 150, 120);
	LPCWSTR Caption = L"Button";
	int cfg_use_animation = 1;
	int cfg_enable_click_on_button = 1;
	int cfg_enable_border = 1;
	LPCSTR cfg_text_style = "Tahoma";
	int cfg_text_size = 18;
	int help_button_active_status = 0;
	int help_left_window_magrin_size = 8;
	int help_top_window_magrin_size = 51;
	int help_button_first_draw_status = 0;
	ObjectButton(int width, int height, int left, int top)
	{
		Width = width;
		Height = height;
		Left = left;
		Top = top;
	}
	void(*ButtonClick)();
	bool CheckMouseCoordinatesBeforeStartClickFunction
	(HWND form_link)
	{
		POINT mouse_coordinates;
		GetCursorPos(&mouse_coordinates);
		RECT program_size_and_position_on_screen;
		GetWindowRect(form_link,
			&program_size_and_position_on_screen);
		bool help_execute_status = false;
		if (mouse_coordinates.x >
			program_size_and_position_on_screen.left + Left &&
			mouse_coordinates.x <
			program_size_and_position_on_screen.left + Left + Width)
		{
			if (mouse_coordinates.y >
				program_size_and_position_on_screen.top + Top &&
				mouse_coordinates.y <
				program_size_and_position_on_screen.top + Top + Height)
			{
				help_execute_status = true;
				if (cfg_enable_click_on_button == 1)
				{
					ButtonClick();
				}
			}
			else
			{
				help_execute_status = false;
			}
		}
		return help_execute_status;
	}
	bool CheckIsMouseOnThisButtonOrNo(HWND form_link,
		int axis_direction)
	{
		POINT mouse_coordinates;
		RECT program_size_and_position_on_screen;
		GetCursorPos(&mouse_coordinates);
		GetWindowRect(form_link,
			&program_size_and_position_on_screen);
		if (axis_direction == 0)
		{
			// проверка координат по оси Х
			if (mouse_coordinates.x >
				program_size_and_position_on_screen.left + Left &&
				mouse_coordinates.x <
				program_size_and_position_on_screen.left + Left + Width)
			{
				// проверка пройдена
				return true;
			}
		}
		else
		{
			if (mouse_coordinates.y >
				program_size_and_position_on_screen.top + Top &&
				mouse_coordinates.y <
				program_size_and_position_on_screen.top + Top + Height)
			{
				// проверка пройдена
				return true;
			}
		}
		return false;
	}
	void DrawButtonText(HDC hdc, LPCWSTR text, COLORREF color)
	{
		HFONT hFont;
		hFont = CreateFontA
		(
			cfg_text_size, // высота текстового символа
			cfg_text_size / 3, // ширина текстового символа
			0, // угол поворота текста
			0, // угол наклона плоскости текста
			// толщина символов (тонкий, средний, толстый, очень толстый)
			FW_NORMAL,
			false, // рисовать курсивом (да или нет)
			false, // подчеркивание текста
			false, // зачеркивание текста
			// указатель степени подгона шрифта под заданные параметры
			OUT_DEFAULT_PRECIS,
			// указатель степени обрезки букв, которые вылезают за
			// пределы своей области
			CLIP_DEFAULT_PRECIS,
			DEFAULT_CHARSET, // указатель кодировки для символов
			// качество отрисовки символов
			// (применение сглаживания, обводки, и т.д.)
			DEFAULT_QUALITY,
			// отступ между символами (передаются сразу два
			// параметра, через условную «запятую», второй
			// параметр указывает может ли расстояние между
			// символами быть постоянным, или любым,
			// в параметре указано любое расстояние)
			DEFAULT_PITCH | FF_DONTCARE,
			cfg_text_style // имя шрифта
		);
		SelectObject(hdc, hFont);
		SIZE help_text_size;
		GetTextExtentPoint32(hdc, text, lstrlen(text), &help_text_size);
		SetTextColor(hdc, color);
		int x = (Width / 2) - (help_text_size.cx / 2);
		int y = (Height / 2) - (help_text_size.cy / 2);
		TextOut(hdc, Left + x, Top + y, text, lstrlen(text));
	}
	void DrawButtonBorder(HDC hdc, COLORREF color)
	{
		if (cfg_enable_border == 0)
		{
			return;
		}
		int a = Left;
		int b = Left + Width;
		while (a <= b)
		{
			SetPixel(hdc, a, Top, color);
			a++;
		}
		a = Top;
		b = Top + Height;
		while (a <= b)
		{
			SetPixel(hdc, Left + Width, a, color);
			a++;
		}
		a = Left;
		b = Left + Width;
		while (a <= b)
		{
			SetPixel(hdc, a, Top + Height, color);
			a++;
		}
		a = Top;
		b = Top + Height;
		while (a <= b)
		{
			SetPixel(hdc, Left, a, color);
			a++;
		}
	}
	void ClearButtonDraw(HWND hwnd)
	{
		RECT help_button_coordinates_and_size;
		help_button_coordinates_and_size.left =
			Left - (help_left_window_magrin_size);
		help_button_coordinates_and_size.top =
			Top - (help_top_window_magrin_size);
		help_button_coordinates_and_size.right =
			(Left + Width) - (help_left_window_magrin_size - 1);
		help_button_coordinates_and_size.bottom =
			(Top + Height) - (help_top_window_magrin_size - 1);
		InvalidateRect(hwnd, &help_button_coordinates_and_size, TRUE);
	}
	void ActiveButtonAnimate(HWND hwnd, HDC hdc)
	{
		if (CheckIsMouseOnThisButtonOrNo(hwnd, 0) == true &&
			CheckIsMouseOnThisButtonOrNo(hwnd, 1) == true)
		{
			if (help_button_active_status < 1)
			{
				DrawButtonBorder(hdc, BorderActiveColor);
				DrawButtonText(hdc, Caption, TextActiveColor);
				help_button_active_status = 1;
			}
		}
		else
		{
			if (help_button_active_status > 0)
			{
				DrawButtonBorder(hdc, BorderColor);
				DrawButtonText(hdc, Caption, TextColor);
				help_button_active_status = 0;
			}
		}
	}
	void Create(HWND hwnd, HDC hdc)
	{
		if (help_button_first_draw_status == 0)
		{
			help_button_first_draw_status = 1;
		}
		else
		{
			return;
		}
		DrawButtonBorder(hdc, BorderColor);
		DrawButtonText(hdc, Caption, TextColor);
	}
	void DrawLine(HDC hdc, COLORREF color,
		int x_from, int y_from, int x_to, int y_to)
	{
		MoveToEx(hdc, x_from, y_from, NULL);
		LineTo(hdc, x_to, y_to);
	}
};
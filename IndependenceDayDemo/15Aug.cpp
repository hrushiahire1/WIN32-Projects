#include <Windows.h>
#include <gdiplus.h>
#include <tchar.h>
#include "window.h"
#define ID_TIMER1 101

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void __DrawLine(HDC, int, RECT);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("15Aug");

	Gdiplus::GdiplusStartupInput gdiplusSI;
	ULONG_PTR gdiplusT;

	//Initialize GDI+
	GdiplusStartup(&gdiplusT, &gdiplusSI, NULL);

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;

	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;

	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	if (RegisterClassEx(&wndclass) == NULL) {
		MessageBox(NULL, TEXT("wndclass was not registered"), TEXT("Error"), MB_OK);
		exit(0);
	}

	hwnd = CreateWindow(
		szAppName,
		TEXT("Happy Independence Day"),
		WS_OVERLAPPEDWINDOW,
		370,
		155,
		900,
		600,
		HWND_DESKTOP,
		NULL,
		hInstance,
		NULL
		);

	if (hwnd == NULL) {
		MessageBox(NULL, TEXT("Window was not created in memory"), TEXT("Error"), MB_OK);
		exit(0);
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Gdiplus::GdiplusShutdown(gdiplusT);
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	HBRUSH hBrush1, hBrush2, hBrush3;
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc, rc1, rc2, rc3;
	static int cgFlag1 = 1, cgFlag2 = 0, cgFlag3 = 129, cgFlag4 = 128, cgFlag5 = 129;
	static int flag = 0;
	static int reverse = 0;
	static int flag_1 = 0;

	switch (iMsg) {
	case WM_CREATE:
		PlaySound(TEXT("15Aug.wav"), NULL, SND_LOOP | SND_ASYNC);
		SetTimer(hwnd, ID_TIMER1, 2000, NULL);
		break;
	case WM_TIMER:
		switch (flag) {
		case 0:
		case 1:
			KillTimer(hwnd, ID_TIMER1);
			if (cgFlag1 < 255)
				cgFlag1++;
			InvalidateRect(hwnd, NULL, TRUE);
			SetTimer(hwnd, ID_TIMER1, 25, NULL);
			if (cgFlag1 == 255) {
				cgFlag1 = 1;
				flag++;
			}
			break;
		case 2:
			KillTimer(hwnd, ID_TIMER1);

			if (reverse == 0) {
				if (cgFlag1 < 255)
					cgFlag1 += 2;
				if (cgFlag2 < 128)
					cgFlag2++;
			}
			else if (reverse == 1) {
				if (cgFlag1 > 128)
					cgFlag1 -= 2;
				if (cgFlag2 > 64)
					cgFlag2--;
			}
			else if (reverse == 2) {
				if (cgFlag5 > 128)
					cgFlag5 = 128;

				if (cgFlag3 < 255)
					cgFlag3 += 2;
				if (cgFlag4 < 128)
					cgFlag4++;

				if (cgFlag5 > 0)
					cgFlag5--;

				if (cgFlag1 > 64)
					cgFlag1 -= 2;
				if (cgFlag2 > 32)
					cgFlag2--;
			}
			else if (reverse == 4) {
				if (cgFlag3 >= 255)
					cgFlag3 = 256;

				if (cgFlag3 > 64)
					cgFlag3 -= 2;
				if (cgFlag4 > 64)
					cgFlag4--;
				if (cgFlag5 < 64 && cgFlag3 > 64)
					cgFlag5++;

				if (cgFlag3 <= 64 && cgFlag4 <= 64 && cgFlag5 <= 64) {
					flag_1 = 0;
					if (cgFlag2 > 0)
						cgFlag2--;
					if (cgFlag1 > 0)
						cgFlag1 -= 2;
				}
			}

			InvalidateRect(hwnd, NULL, TRUE);
			SetTimer(hwnd, ID_TIMER1, 125, NULL);

			if (cgFlag1 == 0 && cgFlag2 == 0 && reverse == 4) {
				KillTimer(hwnd, ID_TIMER1);
				SetTimer(hwnd, ID_TIMER1, 4000, NULL);
				flag = 3;
			}

			if (cgFlag1 == 127 && cgFlag2 == 64 && reverse == 1) {
				KillTimer(hwnd, ID_TIMER1);
				SetTimer(hwnd, ID_TIMER1, 2000, NULL);
				flag_1 = 1;
				reverse = 2;
			}

			if (cgFlag3 == 255 && cgFlag4 == 128) {
				KillTimer(hwnd, ID_TIMER1);
				SetTimer(hwnd, ID_TIMER1, 5000, NULL);
				cgFlag5 = 0;
				cgFlag1 = 64;
				cgFlag2 = 32;
				reverse = 4;
			}

			if (cgFlag1 == 255 && cgFlag2 == 128) {
				KillTimer(hwnd, ID_TIMER1);
				SetTimer(hwnd, ID_TIMER1, 5000, NULL);
				reverse = 1;
			}
			break;
		case 3:
			KillTimer(hwnd, ID_TIMER1);
			if (cgFlag1 < 255)
				cgFlag1++;
			
			cgFlag2++;
			InvalidateRect(hwnd, NULL, TRUE);
			SetTimer(hwnd, ID_TIMER1, 25, NULL);
			
			if (cgFlag2 == 420) {
				KillTimer(hwnd, ID_TIMER1);
				SetTimer(hwnd, ID_TIMER1, 1000, NULL);
				cgFlag1 = 0;
				cgFlag2 =0;
				flag = 4;
			}

			break;
		case 4:
			KillTimer(hwnd, ID_TIMER1);
			if (cgFlag1 < 255)
				cgFlag1++;
			
			cgFlag2++;
			InvalidateRect(hwnd, NULL, TRUE);
			SetTimer(hwnd, ID_TIMER1, 25, NULL);

			if (cgFlag2 == 384) {
				KillTimer(hwnd, ID_TIMER1);
				SetTimer(hwnd, ID_TIMER1, 1000, NULL);
				cgFlag1 = 0;
				cgFlag2 = 0;
				flag = 5;
			}
			break;
		case 5:
			KillTimer(hwnd, ID_TIMER1);
			if (cgFlag1 < 255)
				cgFlag1++;

			cgFlag2++;
			InvalidateRect(hwnd, NULL, TRUE);
			SetTimer(hwnd, ID_TIMER1, 25, NULL);

			if (cgFlag2 == 384) {
				KillTimer(hwnd, ID_TIMER1);
				SetTimer(hwnd, ID_TIMER1, 1000, NULL);
				cgFlag1 = 0;
				cgFlag2 = 0;
				flag = 6;
			}
			break;
		case 6:
			KillTimer(hwnd, ID_TIMER1);
			if (cgFlag1 < 255)
				cgFlag1++;

			cgFlag2++;
			InvalidateRect(hwnd, NULL, TRUE);
			SetTimer(hwnd, ID_TIMER1, 25, NULL);

			if (cgFlag2 == 360) {
				KillTimer(hwnd, ID_TIMER1);
				PlaySound(NULL, 0, 0);
			}
			break;
		default:
			break;
		}
		break;
	case WM_PAINT:
		RECT rect, rect1, rect2;
		HFONT hFont;
		switch (flag) {
		case 0:
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			hFont = CreateFont(54, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, NULL);
			SelectObject(hdc, hFont);
			SetRect(&rect, (0.111111) * (rc.right - rc.left), (0.333333) * (rc.bottom - rc.top), (0.888888) *(rc.right - rc.left), (0.666666) * (rc.bottom - rc.top));
			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(cgFlag1, cgFlag1, cgFlag1));
			DrawText(hdc, TEXT("ASTROMEDICOMP"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DeleteObject(hFont);
			EndPaint(hwnd, &ps);
			break;
		case 1:
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			hFont = CreateFont(48, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, NULL);
			SelectObject(hdc, hFont);
			SetRect(&rect, (0.111111) * (rc.right - rc.left), (0.333333) * (rc.bottom - rc.top), (0.888888) * (rc.right - rc.left), (0.666666) * (rc.bottom - rc.left));
			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(cgFlag1, cgFlag1, cgFlag1));	
			DrawText(hdc, TEXT("WinDev-2021"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DeleteObject(hFont);
			EndPaint(hwnd, &ps);
			break;
		case 2:
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			rc1.left = rc.left;
			rc1.right = rc.right;
			rc1.top = rc.top;
			rc1.bottom = rc.bottom / 3;
			rc2.left = rc.right;
			rc2.right = rc.left;
			rc2.top = rc1.bottom;
			rc2.bottom = rc.bottom - rc1.bottom;
			rc3.left = rc.left;
			rc3.right = rc.right;
			rc3.top = rc2.bottom;
			rc3.bottom = rc.bottom;

			hBrush1 = CreateSolidBrush(RGB(cgFlag1, cgFlag2, 0));
			hBrush2 = CreateSolidBrush(RGB(cgFlag1, cgFlag1, cgFlag1));
			hBrush3 = CreateSolidBrush(RGB(0, cgFlag1, 0));
			SelectObject(hdc, hBrush1);
			FillRect(hdc, &rc1, hBrush1);
			DeleteObject(hBrush1);
			SelectObject(hdc, hBrush2);
			FillRect(hdc, &rc2, hBrush2);
			DeleteObject(hBrush2);
			SelectObject(hdc, hBrush3);
			FillRect(hdc, &rc3, hBrush3);
			DeleteObject(hBrush3);

			hBrush3 = CreateSolidBrush(RGB(0, 0, cgFlag1));
			SelectObject(hdc, hBrush3);
			Ellipse(hdc, (0.416666) * (rc.right - rc.left), (0.37) * (rc.bottom - rc.top), (0.583333) * (rc.right - rc.left), (0.61) * (rc.bottom - rc.top));
			DeleteObject(hBrush3);

			hBrush3 = CreateSolidBrush(RGB(cgFlag1, cgFlag1, cgFlag1));
			SelectObject(hdc, hBrush3);
			Ellipse(hdc, (0.4222) * (rc.right - rc.left), (0.38) * (rc.bottom - rc.top), (0.5777) * (rc.right - rc.left), (0.6) * (rc.bottom - rc.top));
			DeleteObject(hBrush3);

			hBrush3 = CreateSolidBrush(RGB(0, 0, cgFlag1));
			SelectObject(hdc, hBrush3);
			Ellipse(hdc, (0.495) * (rc.right - rc.left), (0.485) * (rc.bottom - rc.top), (0.505) * (rc.right - rc.left), (0.508) * (rc.bottom - rc.top));
			DeleteObject(hBrush3);
			__DrawLine(hdc, cgFlag1, rc);

			if (flag_1 == 1 && cgFlag5  <= 128) {
				hFont = CreateFont((0.066666) * (rc.bottom - rc.top), 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, NULL);
				SelectObject(hdc, hFont);
				SetRect(&rect1, (0.0222222) * (rc.right - rc.left), (0.5) * (rc.bottom - rc.top), (0.277777) * (rc.right - rc.left), (0.583333) * (rc.bottom - rc.top));
				SetBkColor(hdc, RGB(cgFlag1, cgFlag1, cgFlag1));
				SetTextColor(hdc, RGB(cgFlag3, cgFlag4, cgFlag5));
				DrawText(hdc, TEXT("HAPPY"), -1, &rect1, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
				SetRect(&rect2, (0.0222222)* (rc.right - rc.left), (0.583333)* (rc.bottom - rc.top), (0.333333)* (rc.right - rc.left), (0.666666)* (rc.bottom - rc.top));
				SetBkColor(hdc, RGB(cgFlag1, cgFlag1, cgFlag1));
				SetTextColor(hdc, RGB(cgFlag3, cgFlag3, cgFlag3));
				DrawText(hdc, TEXT("INDEPENDENCE"), -1, &rect2, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
				SetRect(&rect, (0.0222222)* (rc.right - rc.left), (0.666666)* (rc.bottom - rc.top), (0.222222)* (rc.right - rc.left), (0.75)* (rc.bottom - rc.top));
				SetBkColor(hdc, RGB(0, cgFlag1, 0));
				SetTextColor(hdc, RGB(0, cgFlag3, 0));
				DrawText(hdc, TEXT("DAY"), -1, &rect, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
			}

			EndPaint(hwnd, &ps);
			break;
		case 3:
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			hFont = CreateFont((0.06) * (rc.bottom - rc.top), (0.015) * (rc.right - rc.left), 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, NULL);
			SelectObject(hdc, hFont);
			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(cgFlag1, cgFlag1, cgFlag1));
			//DrawText(hdc, TEXT("TECHNOLOGIES USED:"), -1, &rect, DT_SINGLELINE | DT_LEFT);
			TextOut(hdc, (0.311111) * (rc.right - rc.left), (0.1) * (rc.bottom - rc.top), TEXT("TECHNOLOGIES USED"), (int)_tcslen(TEXT("TECHNOLOGIES USED")));

			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(cgFlag1, cgFlag1, cgFlag1));
			TextOut(hdc, (0.311111) * (rc.right - rc.left), (0.4) * (rc.bottom - rc.top), TEXT("MUSIC"), (int)_tcslen(TEXT("MUSIC")));
			DeleteObject(hFont);
			
			hFont = CreateFont((0.05) * (rc.bottom - rc.top), (0.012222) * (rc.right - rc.left), 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, NULL);
			SelectObject(hdc, hFont);
			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(cgFlag1, cgFlag1, cgFlag1));
			TextOut(hdc, (0.311111) * (rc.right - rc.left), (0.183333) * (rc.bottom - rc.top), TEXT("* Win32-SDK"), (int)_tcslen(TEXT("* Win32-SDK")));
	
			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(cgFlag1, cgFlag1, cgFlag1));
			TextOut(hdc, (0.311111) * (rc.right - rc.left), (0.233333) * (rc.bottom - rc.top), TEXT("* GDI & GDI+ API'S"), (int)_tcslen(TEXT("* GDI & GDI+ API'S")));

			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(cgFlag1, cgFlag1, cgFlag1));
			TextOut(hdc, (0.311111) * (rc.right - rc.left), (0.483333) * (rc.bottom - rc.top), TEXT("* Maa Tujhe Salaam"), (int)_tcslen(TEXT("* Maa Tujhe Salaam")));

			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(cgFlag1, cgFlag1, cgFlag1));
			TextOut(hdc, (0.311111) * (rc.right - rc.left), (0.533333) * (rc.bottom - rc.top), TEXT("   Singer: A.R. Rahman"), (int)_tcslen(TEXT("   Singer: A.R. Rahman")));
			DeleteObject(hFont);

			EndPaint(hwnd, &ps);
			break;
		case 4:
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			hFont = CreateFont((0.05) * (rc.bottom - rc.top), (0.013) * (rc.right - rc.left), 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, NULL);
			SelectObject(hdc, hFont);
			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(cgFlag1, cgFlag1, cgFlag1));
			TextOut(hdc, (0.4) * (rc.right - rc.left), (0.4) * (rc.bottom - rc.top), TEXT("CREATED BY"), (int)_tcslen("CREATED BY"));
			DeleteObject(hFont);

			hFont = CreateFont((0.06) * (rc.bottom - rc.top), (0.015) * (rc.right - rc.left), 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, NULL);
			SelectObject(hdc, hFont);
			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(cgFlag1, cgFlag1, cgFlag1));
			TextOut(hdc, (0.335555) * (rc.right - rc.left), (0.5) * (rc.bottom - rc.top), TEXT("HRUSHIKESH AHIRE"), (int)_tcslen("HRUSHIKESH AHIRE"));
			DeleteObject(hFont);

			EndPaint(hwnd, &ps);
			break;
		case 5:
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			hFont = CreateFont((0.05) * (rc.bottom - rc.top), (0.013) * (rc.right - rc.left), 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, NULL);
			SelectObject(hdc, hFont);
			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(cgFlag1, cgFlag1, cgFlag1));
			TextOut(hdc, (0.366666) * (rc.right - rc.left), (0.4) * (rc.bottom - rc.top), TEXT("WITH BLESSINGS OF"), (int)_tcslen("WITH BLESSINGS OF"));
			DeleteObject(hFont);

			hFont = CreateFont((0.06) * (rc.bottom - rc.top), (0.015) * (rc.right - rc.left), 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, NULL);
			SelectObject(hdc, hFont);
			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(cgFlag1, cgFlag1, cgFlag1));
			TextOut(hdc, (0.311111) * (rc.right - rc.left), (0.5) * (rc.bottom - rc.top), TEXT("DR. VIJAY GOKHALE SIR"), (int)_tcslen("DR. VIJAY GOKHALE SIR"));
			DeleteObject(hFont);

			EndPaint(hwnd, &ps);
			break;
		case 6:
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			hFont = CreateFont((0.06) * (rc.bottom - rc.top), (0.015) * (rc.right - rc.left), 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, NULL);
			SelectObject(hdc, hFont);
			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(cgFlag1, cgFlag1, cgFlag1));
			TextOut(hdc, (0.4) * (rc.right - rc.left), (0.45) * (rc.bottom - rc.top), TEXT("THANK YOU"), (int)_tcslen("THANK YOU"));
			DeleteObject(hFont);

			EndPaint(hwnd, &ps);
			break;
		default:
			break;
		}
		break;
	case WM_DESTROY:
		PlaySound(NULL, 0, 0);
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void __DrawLine(HDC hdc, int cgFlag1, RECT rc) {

	double h = (0.49777) * (rc.right - rc.left);
	double k = (0.495) * (rc.bottom - rc.top);
	long len = rc.right - rc.left;
	long height = rc.bottom - rc.top;

	double r;
	Gdiplus::Graphics graphics(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, cgFlag1));
	graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, (0.58) * len, (0.495) * height);
		graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.077) * 0.965925), k + ((height * 0.115) * 0.258819));
		graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.074) * 0.866025), k + ((height * 0.1133333) * 0.5));
	graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.071111) * 0.707106), k + ((height * 0.106666) * 0.707106));
		graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.074) * 0.5), k + ((height * 0.113333) * 0.866025));
		graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.074) * 0.258819), k + ((height * 0.113333) * 0.965925));
	graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.071111) * 0), k + ((height * 0.106666) * 1));
		graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.074) * -0.258819), k + ((height * 0.113333) * 0.965925));
		graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.074) * -0.5), k + ((height * 0.113333) * 0.866025));
	graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.071111) * -0.707106), k + ((height * 0.106666) * 0.707106));
		graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.074) * -0.866025), k + ((height * 0.113333) * 0.5));
		graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.074) * -0.965925), k + ((height * 0.113333) * 0.258819));
	graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.075) * -1), k + ((height * 0.116666) * 0));
		graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.075) * -0.965925), k + ((height * 0.116666) * -0.258819));
		graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.075) * -0.866025), k + ((height * 0.116666) * -0.5));
	graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.075) * -0.707106), k + ((height * 0.116666) * -0.707106));
		graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.075) * -0.5), k + ((height * 0.116666) * -0.866025));
		graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.075) * -0.258819), k + ((height * 0.116666) * -0.965925));
	graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.075) * 0), k + ((height * 0.116666) * -1));
		graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.075) * 0.258819), k + (height * 0.116666) * -0.965925);
		graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.075) * 0.5), k + ((height * 0.116666) * -0.866025));
	graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.076) * 0.707106), k + ((height * 0.12) * -0.707106));
		graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.078) * 0.866025), k + ((height * 0.12) * -0.5));
		graphics.DrawLine(&pen, (Gdiplus::REAL)h, (Gdiplus::REAL)k, h + ((len * 0.078) * 0.965925), k + ((height * 0.12) * -0.258819));
}

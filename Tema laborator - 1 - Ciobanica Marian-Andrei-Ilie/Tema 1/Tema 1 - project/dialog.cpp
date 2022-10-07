#undef UNICODE
#include <windows.h>
#include "resource.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL dlgActive = FALSE;
INT randomNumber; // definim variabila pentru numarul random pe care-l vom genera
BOOL selectSucces; // definim variabila de tip BOOL pentru a afla daca am selectat vreun numar
INT selectedNumber; // definim variabila numarului selectat
INT factorial; // definim variabila factorial pentru a-l calcula
HWND hwndMain;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static char szAppName[] = "Dialog";
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);
	hwnd = CreateWindow(szAppName,
		"Factorialul unui numar generat",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOACTIVATE);
	ShowWindow(hwnd, SW_HIDE);
	UpdateWindow(hwnd);
	hwndMain = hwnd;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hInstance;
	switch (iMsg)
	{
	case WM_CREATE:
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		if (!dlgActive) {
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG),
				hwnd, DlgProc);
			PostMessage(hwnd, WM_CLOSE, 0, 0);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	char text[100];
	switch (iMsg) {
	case WM_INITDIALOG:
		return TRUE;
	case WM_CLOSE:
		dlgActive = FALSE;
		EndDialog(hDlg, 0);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_RANDOM:
			randomNumber = rand() % 16; // se va genera un nou numar din intervalul [0, 15]
			SetDlgItemInt(hDlg, IDC_EDIT_NR, randomNumber, true); // setam numarul generat in campul IDC_EDIT_NR
			break;
		case ID_CALC:
			selectedNumber = GetDlgItemInt(hDlg, IDC_EDIT_NR, &selectSucces, false); // selectam numarul(care este de tip INT din campul IDC_EDIT_NR, ne vom folosi de o variabila de verificare selectSucces sa vedem daca s-a selectat ceva din campul respectiv si nu este gol)
			if (selectSucces) { // daca s-a selectat(selectSuccess == true) si selectedNumber nu este NULL
				if (selectedNumber == 0) factorial = 1; // daca numarul selectat este 0, atunci factorial este 1
				else {
					factorial = 1;
					for (int i = 1; i <= selectedNumber; ++i) {
						factorial *= i;
					}
				}
				SetDlgItemInt(hDlg, IDC_EDIT_REZ, factorial, true); // trimitem rezultatul factorialului calculat anterior
			}
			else {
				MessageBox(hDlg, "Nu ati generat niciun numar!", "Eroare", MB_OK | MB_ICONSTOP); // eroare in caz in care nu s-a generat niciun numar
			}
			break;
		case ID_CANCEL:
			dlgActive = FALSE;
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}
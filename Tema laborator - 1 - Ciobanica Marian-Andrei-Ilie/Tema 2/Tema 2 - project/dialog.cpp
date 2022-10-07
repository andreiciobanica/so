#undef UNICODE
#include <windows.h>
#include <stdio.h> // adaugarea librariei pentru functia de string, adica sprintf_s
#include "resource.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL dlgActive = FALSE;
INT nr1;
INT nr2;
BOOL selectSuccesNr1;
BOOL selectSuccesNr2;
INT selectedNr1;
INT selectedNr2;
FLOAT result;
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
		"Operatii simple cu numere generate",
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
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG), hwnd, DlgProc);
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
		case ID_NR1:
			nr1 = rand() % 100; // se va genera un nou numar din intervalul [0, 100)
			SetDlgItemInt(hDlg, IDC_EDIT_NR1, nr1, true); // setam numarul generat in campul IDC_EDIT_NR1
			return TRUE;
		case ID_NR2:
			nr2 = rand() % 100; // se va genera un nou numar din intervalul [0, 100)
			SetDlgItemInt(hDlg, IDC_EDIT_NR2, nr2, true); // setam numarul generat in campul IDC_EDIT_NR2
			return TRUE;
		case ID_ADUNARE:
			selectedNr1 = GetDlgItemInt(hDlg, IDC_EDIT_NR1, &selectSuccesNr1, false); // selectam numarul din campul IDC_EDIT_NR1
			selectedNr2 = GetDlgItemInt(hDlg, IDC_EDIT_NR2, &selectSuccesNr2, false); // selectam numarul din campul IDC_EDIT_NR2
			if (!selectSuccesNr1 && !selectSuccesNr2) { // daca niciunul dintre cele 2 numere nu sunt generate
				MessageBox(hDlg, "Nu ati generat niciun numar!", "Eroare", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
			if (!selectSuccesNr1) { // daca primul numar nu este generat
				MessageBox(hDlg, "Nu ati generat primul numar!", "Eroare", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
			if (!selectSuccesNr2) { // daca al 2-lea numar nu este generat
				MessageBox(hDlg, "Nu ati generat al 2-lea numar!", "Eroare", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
			// Mai sus avem cazurile de exceptie, am abordat metoda "Early return" cu toate cazurile in care primim eroare
			result = (float)selectedNr1 + (float)selectedNr2;
			sprintf_s(text, "%d + %d = %d", selectedNr1, selectedNr2, (int)result);
			MessageBox(hDlg, text, "Adunare", MB_OK); // Afisam rezultatul
			return TRUE;
		case ID_SCADERE:
			selectedNr1 = GetDlgItemInt(hDlg, IDC_EDIT_NR1, &selectSuccesNr1, false);
			selectedNr2 = GetDlgItemInt(hDlg, IDC_EDIT_NR2, &selectSuccesNr2, false);
			if (!selectSuccesNr1 && !selectSuccesNr2) {
				MessageBox(hDlg, "Nu ati generat niciun numar!", "Eroare", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
			if (!selectSuccesNr1) {
				MessageBox(hDlg, "Nu ati generat primul numar!", "Eroare", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
			if (!selectSuccesNr2) {
				MessageBox(hDlg, "Nu ati generat al 2-lea numar!", "Eroare", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
			result = selectedNr1 - selectedNr2;
			sprintf_s(text, "%d - %d = %d", selectedNr1, selectedNr2, (int)result);
			MessageBox(hDlg, text, "Scadere", MB_OK);
			return TRUE;
		case ID_INMULTIRE:
			selectedNr1 = GetDlgItemInt(hDlg, IDC_EDIT_NR1, &selectSuccesNr1, false);
			selectedNr2 = GetDlgItemInt(hDlg, IDC_EDIT_NR2, &selectSuccesNr2, false);
			if (!selectSuccesNr1 && !selectSuccesNr2) {
				MessageBox(hDlg, "Nu ati generat niciun numar!", "Eroare", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
			if (!selectSuccesNr1) {
				MessageBox(hDlg, "Nu ati generat primul numar!", "Eroare", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
			if (!selectSuccesNr2) {
				MessageBox(hDlg, "Nu ati generat al 2-lea numar!", "Eroare", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
			result = (float)selectedNr1 * (float)selectedNr2;
			sprintf_s(text, "%d * %d = %d", selectedNr1, selectedNr2, (int)result);
			MessageBox(hDlg, text, "Inmultire", MB_OK);
			return TRUE;
		case ID_IMPARTIRE:
			selectedNr1 = GetDlgItemInt(hDlg, IDC_EDIT_NR1, &selectSuccesNr1, false);
			selectedNr2 = GetDlgItemInt(hDlg, IDC_EDIT_NR2, &selectSuccesNr2, false);
			if (!selectSuccesNr1 && !selectSuccesNr2) {
				MessageBox(hDlg, "Nu ati generat niciun numar!", "Eroare", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
			if (!selectSuccesNr1) {
				MessageBox(hDlg, "Nu ati generat primul numar!", "Eroare", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
			if (!selectSuccesNr2) {
				MessageBox(hDlg, "Nu ati generat al 2-lea numar!", "Eroare", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
			if (selectedNr2 == 0) { // la impartire mai avem inca un caz, acela in care impartitorul este 0, nu se poate efectua impartirea deoarece este nedefinita(nu poti sa imparti la 0)
				MessageBox(hDlg, "Impartirea la 0 nu este posibila!", "Eroare", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
			result = (float)selectedNr1 / (float)selectedNr2;
			sprintf_s(text, "%d / %d = %f", selectedNr1, selectedNr2, result);
			MessageBox(hDlg, text, "Impartire", MB_OK);
			return TRUE;
		case ID_CANCEL:
			dlgActive = FALSE;
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}
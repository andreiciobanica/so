#undef UNICODE
#include <windows.h>
#include <stdio.h> // adaugarea librariei pentru functia de string, adica sprintf_s
#include <random> // pentru generare de numere
#include <ctime> // pentru generare de numere
#include "resource.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL dlgActive = FALSE;
BOOL isSelectedRadioButton = FALSE; // daca s-a selectat vreun radioButton
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
		"Convertor valutar",
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
	char eur_cursText[11], usd_cursText[11], s[11], str1[11], str2[11], str3[11]; // bufferele pentru fiecare curs, cat si pentru fiecare rezultat
	float eur_curs, usd_curs, low, high, ron, eur, usd;
	switch (iMsg) {
	case WM_INITDIALOG:
		SetDlgItemText(hDlg, IDC_SUMA, "0"); // initializam campul sumei cu 0
		SetDlgItemText(hDlg, IDC_FINAL_RON, "0"); // initializam campul ron(final) cu 0
		SetDlgItemText(hDlg, IDC_FINAL_EUR, "0"); // initializam campul eur(final) cu 0
		SetDlgItemText(hDlg, IDC_FINAL_USD, "0"); // initializam campul usd(final) cu 0

		low = 3;
		high = 5.50;
		// intervalul de randomizare
		srand(time(NULL)); // o randomizare mai corecta, imprumutata din documentatie (cpp docs)
		eur_curs = low + static_cast<float>(rand()) * static_cast<float>(high - low) / RAND_MAX; // generam primul curs euro-ron
		usd_curs = low + static_cast<float>(rand()) * static_cast<float>(high - low) / RAND_MAX; // generam primul curs usd-ron
		while (eur_curs < usd_curs) { // daca euro < usd atunci se randomizeaza iar
			eur_curs = low + static_cast<float>(rand()) * static_cast<float>(high - low) / RAND_MAX; // se regenereaza alt curs euro-ron
			usd_curs = low + static_cast<float>(rand()) * static_cast<float>(high - low) / RAND_MAX; // se regenereaza alt curs usd-ron
		}
		sprintf_s(eur_cursText, "%.2f", eur_curs); // buffer
		SetDlgItemText(hDlg, IDC_CURS_EUR, eur_cursText); // afisam cursul euro-ron
		sprintf_s(usd_cursText, "%.2f", usd_curs); // buffer
		SetDlgItemText(hDlg, IDC_CURS_USD, usd_cursText); // afisam cursul usd-ron
		return TRUE;
	case WM_CLOSE:
		dlgActive = FALSE;
		EndDialog(hDlg, 0);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_CURS:
			low = 3;
			high = 5.50;
			// intervalul de randomizare
			srand(time(NULL)); // o randomizare mai corecta, imprumutata din documentatie (cpp docs)
			eur_curs = low + static_cast<float>(rand()) * static_cast<float>(high - low) / RAND_MAX; // generam primul curs euro-ron
			usd_curs = low + static_cast<float>(rand()) * static_cast<float>(high - low) / RAND_MAX; // generam primul curs usd-ron
			while (eur_curs < usd_curs) { // daca euro < usd atunci se randomizeaza iar
				eur_curs = low + static_cast<float>(rand()) * static_cast<float>(high - low) / RAND_MAX; // se regenereaza alt curs euro-ron
				usd_curs = low + static_cast<float>(rand()) * static_cast<float>(high - low) / RAND_MAX; // se regenereaza alt curs usd-ron
			}
			sprintf_s(eur_cursText, "%.2f", eur_curs); // buffer
			SetDlgItemText(hDlg, IDC_CURS_EUR, eur_cursText); // afisam cursul euro-ron
			sprintf_s(usd_cursText, "%.2f", usd_curs); // buffer
			SetDlgItemText(hDlg, IDC_CURS_USD, usd_cursText); // afisam cursul usd-ron
			return TRUE;
		case ID_CONVERT:
			if ((!GetDlgItemText(hDlg, IDC_CURS_EUR, eur_cursText, 11))) { // daca este vreo valoare in campul cursului euro-ron(se stie ca GetDlgItemText returneaza o valoare TRUE daca nu este gol si 0 daca este gol)
				MessageBox(hDlg, "Nu ati generat un curs valutar!", "Eroare", MB_OK | MB_ICONSTOP);
				return FALSE;
			}

			int selectedRadioButton; // ce denomiare s-a selectat(RON/EUR/USD)
			selectedRadioButton = -1; // initializam cu -1

			if (IsDlgButtonChecked(hDlg, IDC_SELECT_RON)) {
				isSelectedRadioButton = TRUE;
				selectedRadioButton = 1; // s-a selectat RON
			}
			if (IsDlgButtonChecked(hDlg, IDC_SELECT_EUR)) {
				isSelectedRadioButton = TRUE;
				selectedRadioButton = 2; // s-a selectat EUR
			}
			if (IsDlgButtonChecked(hDlg, IDC_SELECT_USD)) {
				isSelectedRadioButton = TRUE;
				selectedRadioButton = 3; // s-a selectat USD
			}

			if (!isSelectedRadioButton) { // daca nu s-a selectat niciuna, atunci dam eroare
				MessageBox(hDlg, "Nu ati selectat denumirea monedei 'suma'!", "Eroare", MB_OK | MB_ICONSTOP);
				return FALSE;
			}

			if (!GetDlgItemText(hDlg, IDC_SUMA, s, 11)) {  // daca nu este nicio suma pusa
				MessageBox(hDlg, "Nu ati introdus suma!", "Eroare", MB_OK | MB_ICONSTOP);
				return FALSE;
			}

			float suma;
			suma = atof(s); // convertim din string in float/double
			GetDlgItemText(hDlg, IDC_CURS_EUR, eur_cursText, 11); // luam cursul euro-ron
			GetDlgItemText(hDlg, IDC_CURS_USD, usd_cursText, 11); // luam cursul usd-ron
			eur_curs = atof(eur_cursText); // convertim din string in float/double
			usd_curs = atof(usd_cursText); // convertim din string in float/double

			if (selectedRadioButton == 1) { // RON selectat
				ron = suma;
				eur = suma / eur_curs;
				usd = suma / usd_curs;
			}
			else if (selectedRadioButton == 2) { // EUR selectat
				ron = suma * eur_curs;
				eur = suma;
				usd = suma * (eur_curs / usd_curs);
			}
			else if (selectedRadioButton == 3) { // USD selectat
				ron = suma * usd_curs;
				eur = suma * (usd_curs / eur_curs);
				usd = suma;
			}
			sprintf_s(str1, "%.2f", ron); // buffer
			sprintf_s(str2, "%.2f", eur); // buffer
			sprintf_s(str3, "%.2f", usd); // buffer
			SetDlgItemText(hDlg, IDC_FINAL_RON, str1); // afisam RON final
			SetDlgItemText(hDlg, IDC_FINAL_EUR, str2); // afisam EUR final
			SetDlgItemText(hDlg, IDC_FINAL_USD, str3); // afisam USD final
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
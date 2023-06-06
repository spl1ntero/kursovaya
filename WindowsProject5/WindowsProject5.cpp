#include <Windows.h>
#include <string>

// Global variables
HWND g_hWindow, g_hGenderLabel, g_hAgeLabel, g_hHemoglobinLabel;
HWND g_hGenderCombo, g_hAgeEdit, g_hHemoglobinEdit, g_hResultLabel;

// Constants
const char g_szClassName[] = "HemoglobinCheckerWindowClass";
const int g_nWidth = 400;
const int g_nHeight = 200;
const int g_nMargin = 10;

// Function prototypes
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void CreateControls(HWND hWnd);
int GetGenderSelection(HWND hWnd);
int GetAge(HWND hWnd);
float GetHemoglobinLevel(HWND hWnd);
std::string GetResult(float fHemoglobinLevel, int nGender, int nAge);

// Entry point of the application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register the window class
    WNDCLASSEX wc = { };
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = g_szClassName;
    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window registration failed.", "Error", MB_ICONERROR | MB_OK);
        return 0;
    }

    // Create the window
    g_hWindow = CreateWindowEx(0, g_szClassName, "Hemoglobin Checker", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, g_nWidth, g_nHeight, NULL, NULL, hInstance, NULL);
    if (g_hWindow == NULL) {
        MessageBox(NULL, "Window creation failed.", "Error", MB_ICONERROR | MB_OK);
        return 0;
    }

    // Show the window
    ShowWindow(g_hWindow, nCmdShow);
    UpdateWindow(g_hWindow);

    // Message loop
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// Window procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateControls(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            int nGender = GetGenderSelection(hWnd);
            int nAge = GetAge(hWnd);
            float fHemoglobinLevel = GetHemoglobinLevel(hWnd);
            std::string sResult = GetResult(fHemoglobinLevel, nGender, nAge);
            SetWindowText(g_hResultLabel, sResult.c_str());
        }
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return 0;
}

// Create the child controls of the window
void CreateControls(HWND hWnd) {
    // Gender label
    g_hGenderLabel = CreateWindowEx(0, "STATIC", "Gender:", WS_CHILD | WS_VISIBLE, g_nMargin, g_nMargin, 50, 20, hWnd, NULL, NULL, NULL);

    // Gender combo box
    g_hGenderCombo = CreateWindowEx(0, "COMBOBOX", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, g_nMargin + 60, g_nMargin, 100, 200, hWnd, NULL, NULL, NULL);
    SendMessage(g_hGenderCombo, CB_ADDSTRING, 0, (LPARAM)"Male");
    SendMessage(g_hGenderCombo, CB_ADDSTRING, 0, (LPARAM)"Female");
    SendMessage(g_hGenderCombo, CB_SETCURSEL, 0, 0);

    // Age label
    g_hAgeLabel = CreateWindowEx(0, "STATIC", "Age:", WS_CHILD | WS_VISIBLE, g_nMargin, g_nMargin * 3,  50, 20, hWnd, NULL, NULL, NULL);

    // Age edit box
    g_hAgeEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | ES_NUMBER, g_nMargin + 60, g_nMargin * 3, 80, 20, hWnd, NULL, NULL, NULL);

    // Hemoglobin level label
    g_hHemoglobinLabel = CreateWindowEx(0, "STATIC", "Hemoglobin Level (g/dL):", WS_CHILD | WS_VISIBLE, g_nMargin, g_nMargin * 5, 150, 20, hWnd, NULL, NULL, NULL);

    // Hemoglobin level edit box
    g_hHemoglobinEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | ES_NUMBER | ES_AUTOHSCROLL, g_nMargin + 160, g_nMargin * 5, 80, 20, hWnd, NULL, NULL, NULL);

    // Result label
    g_hResultLabel = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "", WS_CHILD | WS_VISIBLE, g_nMargin, g_nMargin * 7, g_nWidth - g_nMargin * 2, 20, hWnd, NULL, NULL, NULL);

    // OK button
    CreateWindowEx(0, "BUTTON", "OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, g_nWidth - 50 - g_nMargin, g_nHeight - 50 - g_nMargin, 50, 30, hWnd, (HMENU)IDOK, NULL, NULL);
}

// Get the gender selection from the combo box
int GetGenderSelection(HWND hWnd) {
    return SendMessage(g_hGenderCombo, CB_GETCURSEL, 0, 0);
}

// Get the age from the edit box
int GetAge(HWND hWnd) {
    char szAge[10];
    GetWindowText(g_hAgeEdit, szAge, sizeof(szAge));
    return atoi(szAge);
}

// Get the hemoglobin level from the edit box
float GetHemoglobinLevel(HWND hWnd) {
    char szLevel[10];
    GetWindowText(g_hHemoglobinEdit, szLevel, sizeof(szLevel));
    return atof(szLevel);
}

// Get the result based on the gender, age, and hemoglobin level
std::string GetResult(float fHemoglobinLevel, int nGender, int nAge) {
    if (nGender == 0) {  // Male
        if (nAge < 15) {
            if (fHemoglobinLevel < 115) {
                return "Hemoglobin level is low.";
            }
            else if (fHemoglobinLevel > 155) {
                return "Hemoglobin level is high.";
            }
        }
        else {
            if (fHemoglobinLevel < 135) {
                return "Hemoglobin level is low.";
            }
            else if (fHemoglobinLevel > 175) {
                return "Hemoglobin level is high.";
            }
        }
    }
    else {  // Female
        if (nAge < 15) {
            if (fHemoglobinLevel < 115) {
                return "Hemoglobin level is low.";
            }
            else if (fHemoglobinLevel > 155) {
                return "Hemoglobin level is high.";
            }
        }
        else {
            if (fHemoglobinLevel < 120) {
                return "Hemoglobin level is low.";
            }
            else if (fHemoglobinLevel > 155) {
                return "Hemoglobin level is high.";
            }
        }
    }
    return "Hemoglobin level is normal.";
}

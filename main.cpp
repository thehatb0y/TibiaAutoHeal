#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;


void manaHeal(HANDLE hProc, HWND hWnd);
void lifeHeal(HANDLE hProc, HWND hWnd);
bool initializeClient();

HWND hWnd = FindWindow(0, "Tibia - PlayerName");
HANDLE hProc;
DWORD pId;

struct AddressConfig{
    LPVOID manaAdd = (LPVOID)0x099B0E70; /* Mana Memory Address*/
    LPVOID lifeAdd = (LPVOID)0x099B0990; /* Life Memory Address*/
}AddressConfig;

struct CharConfig{
    string Charname;

    int MaxLife = 4730;
    int MaxMana = 1550;

    int MinLife = MaxLife * 0.9;
    int MaxLifeA = MaxLife / 2;

    bool Heal1 = true;
    bool Heal2 = false;
    bool Heal3 = false;

    bool isActive = true;
    int lastSpell = 0;
}CharConfig;

main (){
    initializeClient();
    while(CharConfig.isActive){
        lifeHeal(hProc, hWnd);
        manaHeal(hProc, hWnd);
    }

    return 0;
}

bool initializeClient(){
        if (hWnd == 0)
        {
            cout << "Window not found" << endl;
            return 0;
        }else{
            GetWindowThreadProcessId(hWnd, &pId);
            hProc = OpenProcess(PROCESS_VM_READ, FALSE, pId);

            if (!hProc)
            {
                cout << "Process not found" << endl;
                return false;
            } else {
                return true;
            }
            CloseHandle(hProc);
        }
}

void manaHeal(HANDLE hProc, HWND hWnd){
                    int newValue= 500;
                    int oldvalue= 0;

                    ReadProcessMemory(hProc, AddressConfig.manaAdd, &newValue, sizeof(newValue), NULL);
                    if(newValue < (CharConfig.MaxMana * 0.90) && newValue != oldvalue){
                        SendMessage(hWnd, WM_KEYDOWN, 0x39, 9);
                    }
                    oldvalue = newValue;
}

void lifeHeal(HANDLE hProc, HWND hWnd){
                    int newValue= 500;
                    int oldvalue= 0;

                    ReadProcessMemory(hProc, AddressConfig.lifeAdd, &newValue, sizeof(newValue), NULL);
                    if(newValue < (CharConfig.MaxLife * 0.3) && newValue != oldvalue){
                        SendMessage(hWnd, WM_KEYDOWN, VK_F2, 1);
                        SendMessage(hWnd, WM_KEYDOWN, 0x30, 0);
                        Sleep(1000);
                    }else if (newValue < (CharConfig.MaxLife * 0.6) && newValue != oldvalue){
                        SendMessage(hWnd, WM_KEYDOWN, 0x30, 0);
                        SendMessage(hWnd, WM_KEYDOWN, VK_F1, 11);
                        Sleep(1000);
                    }else if (newValue < (CharConfig.MaxLife * 0.95) && newValue != oldvalue){
                        SendMessage(hWnd, WM_KEYDOWN, VK_F1, 11);
                        Sleep(1000);
                    }
                    oldvalue = newValue;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    WNDCLASSEX wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hInstance = hInstance;
    wc.lpszClassName = "WindowClass";
    wc.lpfnWndProc = WindowProcedure;
    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.cbSize = sizeof(WNDCLASSEX);
    RegisterClassEx(&wc);
    HWND hWnd = CreateWindowEx(0, "WindowClass", "Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return main();
}

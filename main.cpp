#include <windows.h>
#pragma comment (lib,"user32.lib")

int main(){
    MessageBoxW(NULL, L"Hello, World!", L"Message", MB_ICONEXCLAMATION | MB_OK);
    return 0;
}
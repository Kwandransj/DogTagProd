#include <iostream>
#include <windows.h>
#include <tchar.h>
using namespace std;

int main() {
    ShellExecute(NULL, _T("open"), _T("C:\\Users\\expressed\\Desktop\\Pdf-To-Column\\drag\\Drag and Drop\\Debug\\Drag and Drop.exe"), NULL, NULL, SW_SHOWDEFAULT);
    cout << "done\n";
    return 0;
}

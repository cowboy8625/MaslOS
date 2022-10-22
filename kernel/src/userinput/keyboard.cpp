#include "keyboard.h"

#include <stdint.h>
#include "kbScancodeTranslation.h"
#include "../Rendering/BasicRenderer.h"
#include "../cmdParsing/cmdParser.h"
#include "../Rendering/Cols.h"
#include "../OSDATA/userdata.h"
#include "../OSDATA/osdata.h"
#include "../tasks/enterHandler/taskEnterHandler.h"
#include "../WindowStuff/SubInstances/connect4Instance/connect4Instance.h"


bool lshift = false;
bool rshift = false;
bool allowArrows = false;


void ClearInput(TerminalInstance* instance)
{
    AddToStack();
    for (int i = 0; i < 256; i++)
    {
        instance->lastTerminalInput[i] = instance->terminalInput[i];
        instance->terminalInput[i] = 0;
    }
    instance->userlen = 0;
    RemoveFromStack();
}


void HandleEnter()
{
    Panic("Old Function used!");
    // AddToStack();
    // if (activeWindow->instance->instanceType == InstanceType::Terminal)
    // {
    //     TerminalInstance* instance = (TerminalInstance*)activeWindow->instance;
    //     if (instance->userlen > 0)
    //     {
    //         if (instance->userlen > 255)
    //             instance->userlen = 255;
                
    //         instance->terminalInput[instance->userlen] = 0;
    //         ParseCommand(instance->terminalInput, instance->lastTerminalInput, &instance->currentUser, activeWindow);
    //         //GlobalRenderer->Print("> ");
    //         //GlobalRenderer->Println(userData);
    //     }
    //     if (activeWindow != NULL)
    //     {
    //         if (activeWindow->allowKeyboardDrawing)
    //         {
    //             activeWindow->renderer->Println();
    //             PrintUser(activeWindow, instance->currentUser);
    //             ClearInput(instance);
    //         }
    //     }
    // }
    // RemoveFromStack();
}

void InitKeyboard()
{

}

// void KeyboardPrintStart(Window* window)
// {
//     AddToStack();
//     if (window == NULL)
//     {
//         RemoveFromStack();
//         return;
//     }

//     if (!window->allowKeyboardDrawing)
//     {
//         RemoveFromStack();
//         return;
//     }

//     if (window->instance->instanceType == InstanceType::Terminal)
//     {
//         window->renderer->CursorPosition.y += 16;
//         TerminalInstance* instance = (TerminalInstance*)window->instance;
//         PrintUser(window, instance->currentUser);
//     }
//     RemoveFromStack();
// }

// void PrintUser(Window* window, OSUser* user)
// {
//     AddToStack();
//     if (window == NULL)
//     {
//         RemoveFromStack();
//         return;
//     }
//     if (user== NULL)
//     {
//         RemoveFromStack();
//         return;
//     }

//     window->renderer->Print(user->userName, user->colData.userColor);
//     window->renderer->Print("> ");
//     RemoveFromStack();
// }

int scrollSpeed = 8;

void HandleKeyboard(uint8_t scancode)
{
    AddToStack();
    if (scancode == ARR_LEFT)
    {  
        if (lshift)
        {
            if (activeWindow != NULL)
                if (activeWindow->instance != NULL)
                    if (activeWindow->instance->instanceType == InstanceType::Terminal)
                        if (((TerminalInstance*)activeWindow->instance)->newTermInstance != NULL)
                            ((NewTerminalInstance*)((TerminalInstance*)activeWindow->instance)->newTermInstance)->scrollX -= scrollSpeed;
        }
        else
        {
            int64_t count = Taskbar::taskWindowList->getCount();
            int64_t index = Taskbar::taskWindowList->getIndexOf(activeWindow);
            index = (index + count - 1) % count;
            activeWindow = Taskbar::taskWindowList->elementAt(index);
            activeWindow->moveToFront = true;
        }
    }
    else if (scancode == ARR_RIGHT)
    {
        if (lshift)
        {
            if (activeWindow != NULL)
                if (activeWindow->instance != NULL)
                    if (activeWindow->instance->instanceType == InstanceType::Terminal)
                        if (((TerminalInstance*)activeWindow->instance)->newTermInstance != NULL)
                            ((NewTerminalInstance*)((TerminalInstance*)activeWindow->instance)->newTermInstance)->scrollX += scrollSpeed;
        }
        else
        {
            int64_t count = Taskbar::taskWindowList->getCount();
            int64_t index = Taskbar::taskWindowList->getIndexOf(activeWindow);
            index = (index + count + 1) % count;
            activeWindow = Taskbar::taskWindowList->elementAt(index);
            activeWindow->moveToFront = true;
        }
    }
    else if (scancode == ARR_UP)
    {  
        if (lshift)
        {
            if (activeWindow != NULL)
                if (activeWindow->instance != NULL)
                    if (activeWindow->instance->instanceType == InstanceType::Terminal)
                        if (((TerminalInstance*)activeWindow->instance)->newTermInstance != NULL)
                            ((NewTerminalInstance*)((TerminalInstance*)activeWindow->instance)->newTermInstance)->scrollY -= 2*scrollSpeed;
        }
        else
        {
            
        }
    }
    else if (scancode == ARR_DOWN)
    {
        if (lshift)
        {
            if (activeWindow != NULL)
                if (activeWindow->instance != NULL)
                    if (activeWindow->instance->instanceType == InstanceType::Terminal)
                        if (((TerminalInstance*)activeWindow->instance)->newTermInstance != NULL)
                            ((NewTerminalInstance*)((TerminalInstance*)activeWindow->instance)->newTermInstance)->scrollY += 2*scrollSpeed;
        }
        else
        {
            Window* oldActive = activeWindow;
            Window* mainWindow = (Window*)malloc(sizeof(Window), "Main Window");
            TerminalInstance* terminal = (TerminalInstance*)malloc(sizeof(TerminalInstance), "Terminal Instance");
            *terminal = TerminalInstance(&guestUser, mainWindow);
            *(mainWindow) = Window((DefaultInstance*)terminal, Size(600, 500), Position(10, 40), "Terminal Window", true, true, true);
            osData.windows.add(mainWindow);
            ((TerminalInstance*)mainWindow->instance)->Cls();
            //KeyboardPrintStart(mainWindow);
            ((TerminalInstance*)mainWindow->instance)->KeyboardPrintStart();

            activeWindow = mainWindow;          
            mainWindow->moveToFront = true;
            osData.mainTerminalWindow = mainWindow;

            if (oldActive != NULL)
            {
                osData.windowPointerThing->UpdateWindowBorder(oldActive);
            }

            RemoveFromStack();
            return;
        }
    }


    if (activeWindow == NULL)
    {
        RemoveFromStack();
        return;
    }


    if (scancode == LeftShift)
        lshift = true; 
    else if (scancode == LeftShift + 0x80)
        lshift = false;
    else if (scancode == RightShift)
        rshift = true; 
    else if (scancode == RightShift + 0x80)
        rshift = false;
    else if (scancode == Enter)
    {
        if (activeWindow->instance->instanceType == InstanceType::Terminal)
        {
            TerminalInstance* instance = (TerminalInstance*)activeWindow->instance;
            if (!instance->GetBusy())
            {
                if (activeWindow->allowKeyboardDrawing)
                    ((NewTerminalInstance*)instance->newTermInstance)->Println();
                instance->tasks.add(NewEnterTask(instance));
            }
        }
        else if (activeWindow->instance->instanceType == InstanceType::Connect4)
        {
            Connect4Instance* instance = (Connect4Instance*)activeWindow->instance;
            if (instance->currentMode == Connect4Instance::CurrentMode::PLAYER_1_ENTER || instance->currentMode == Connect4Instance::CurrentMode::PLAYER_2_ENTER
                || instance->currentMode == Connect4Instance::CurrentMode::END || instance->currentMode == Connect4Instance::CurrentMode::START)
            {
                instance->HandleInput();
            }
        }
    }
    else if (scancode == Backspace)
    {
        if (activeWindow->instance->instanceType == InstanceType::Terminal)
        {
            TerminalInstance* instance = (TerminalInstance*)activeWindow->instance;
            if (instance->userlen > 0 && !instance->GetBusy())
            {
                instance->userlen--;
                instance->terminalInput[instance->userlen] = 0;
                if (activeWindow->allowKeyboardDrawing)
                    activeWindow->renderer->CursorPosition.x -= 8; 
                if (activeWindow->allowKeyboardDrawing)
                    ((NewTerminalInstance*)instance->newTermInstance)->DeleteLastCharInLine();//activeWindow->renderer->delChar(activeWindow->renderer->CursorPosition.x, activeWindow->renderer->CursorPosition.y);
            }
        }
        else if (activeWindow->instance->instanceType == InstanceType::Connect4)
        {
            Connect4Instance* instance = (Connect4Instance*)activeWindow->instance;
            if (instance->inputLen > 0 &&  (instance->currentMode == Connect4Instance::CurrentMode::PLAYER_1_ENTER || instance->currentMode == Connect4Instance::CurrentMode::PLAYER_2_ENTER))
            {
                instance->inputLen--;
                instance->userInput[instance->inputLen] = 0;
                activeWindow->renderer->CursorPosition.x -= 8; 
                activeWindow->renderer->delChar(activeWindow->renderer->CursorPosition.x, activeWindow->renderer->CursorPosition.y, instance->bgCol);
            }
        }
    } 
    else if (scancode == ARR_UP)
    {
        if (allowArrows && activeWindow->allowKeyboardDrawing)
        {
            if (activeWindow->renderer->CursorPosition.y >= 16)
                activeWindow->renderer->CursorPosition.y -= 16;
        }
    }
    else if (scancode == ARR_DOWN) 
    {
        if (allowArrows && activeWindow->allowKeyboardDrawing)
        {
            activeWindow->renderer->CursorPosition.y += 16;
        }
    }
    else if (scancode == ARR_LEFT)
    {  
        if (allowArrows && activeWindow->allowKeyboardDrawing)
        {
            if (activeWindow->renderer->CursorPosition.x >= 8)
                activeWindow->renderer->CursorPosition.x -= 8; 
            else if (activeWindow->renderer->CursorPosition.y >= 16)
            {
                activeWindow->renderer->CursorPosition.y -= 16;
                activeWindow->renderer->CursorPosition.x = GlobalRenderer->framebuffer->Width - 8;
            }
        }
    }
    else if (scancode == ARR_RIGHT)
    {
        if (allowArrows && activeWindow->allowKeyboardDrawing)
        {
            activeWindow->renderer->CursorPosition.x += 8; 
        }
    }
    else
    {
        char ascii = QWERTYKeyboard::Translate(scancode, lshift || rshift);

        if (ascii != 0)
        {
            if (activeWindow->instance->instanceType == InstanceType::Terminal)
            {
                TerminalInstance* instance = (TerminalInstance*)activeWindow->instance;

                if ((activeWindow->allowKeyboardDrawing && !instance->GetBusy()))
                {
                    if (instance->mode == commandMode::none)
                        ((NewTerminalInstance*)instance->newTermInstance)->Print(ascii);
                    else if (instance->mode == commandMode::enterText)
                        ((NewTerminalInstance*)instance->newTermInstance)->Print(ascii);
                    else if (instance->mode == commandMode::enterPassword)
                        ((NewTerminalInstance*)instance->newTermInstance)->Print("*");
                }

                if ((instance->userlen < 255 && !instance->GetBusy()) || instance->takeInput)
                {
                    instance->terminalInput[instance->userlen] = ascii;
                    instance->userlen++;
                }
            }
            else if (activeWindow->instance->instanceType == InstanceType::Connect4)
            {
                Connect4Instance* instance = (Connect4Instance*)activeWindow->instance;

                if (instance->currentMode != Connect4Instance::CurrentMode::NONE && instance->currentMode != Connect4Instance::CurrentMode::WAIT)
                {
                    if (instance->currentMode == Connect4Instance::CurrentMode::PLAYER_1_ENTER || 
                        instance->currentMode == Connect4Instance::CurrentMode::PLAYER_2_ENTER)
                        if (instance->inputLen < 4)
                            activeWindow->renderer->Print(ascii);

                    if (instance->inputLen < 4)
                    {
                        instance->userInput[instance->inputLen] = ascii;
                        instance->inputLen++;
                    }   
                }
            }
        }
    }

    RemoveFromStack();
} 



/*
    else if (scancode == Backspace)
    {
        if (GlobalRenderer->CursorPosition.x >= 8)
            GlobalRenderer->CursorPosition.x -= 8; 
        else if (GlobalRenderer->CursorPosition.y >= 16)
        {
            GlobalRenderer->CursorPosition.y -= 16;
            GlobalRenderer->CursorPosition.x = GlobalRenderer->framebuffer->Width - 8;
        }
        GlobalRenderer->delChar(GlobalRenderer->CursorPosition.x, GlobalRenderer->CursorPosition.y);
        if (userLen > 0)
        {
            userLen--;
            userData[userLen] = 0;
        }
    } 
*/
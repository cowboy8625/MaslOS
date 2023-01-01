#pragma once
#include "../task.h"
#include "../../WindowStuff/Window/window.h"
#include <stdint.h>

class TaskTaskManager : public Task
{
    private:    
        Window* window;
        int callsPerFrame = 50;
        int callCount = 0;
        int totalCount = 0;
        const char* oldTitle;

    public:
        bool exit = false;
        TaskTaskManager(Window* window);
        void Do();
        void Free();

};

TaskTaskManager* NewTaskManagerTask(Window* window);
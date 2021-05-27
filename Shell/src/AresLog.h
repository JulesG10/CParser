#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>

namespace AresConsole
{
    enum LogTypes {
        L_INFO,
        L_ERROR,
        L_FAIL,
        L_WARM,
        L_SUCCESS,
        L_NONE,
    };

    class AresLog
    {
    public:
        AresLog();
        void print(const char*, LogTypes type = LogTypes::L_INFO,char end = '\n');
        void color(int);
        ~AresLog();
    private:
        HANDLE console;
    };

}

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>

namespace AresConsole
{
    enum ColorTypes {
        Black,
        Blue,
        Green,
        Aqua,
        Red,
        Purple,
        Yellow,
        LightGray,
        Gray,
        LightBlue,
        LightGreen,
        LightAqua,
        LightRed,
        LightPurple,
        LightYellow,
        White,
    };

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
        void color(ColorTypes, ColorTypes);
        ~AresLog();
    private:
        HANDLE console;
    };

}

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include "src/core/Ares.h"
using namespace AresConsole;

int main(int argc,char** argv)
{
	Ares* ares = new Ares(argv);
	ares->start();
	delete ares;
	return 0;
}
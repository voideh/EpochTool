#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <iostream>
#include <string>

void error(std::string msg, std::string caption = "Error")
{
	std::cout << caption << " : " << msg << std::endl;
	MessageBox(NULL, (LPCWSTR)msg.c_str(), (LPCWSTR)caption.c_str(), MB_ICONERROR);
}


void info(std::string msg, std::string caption = "Info")
{
	std::cout << caption << ": " << msg << std::endl;
	MessageBox(NULL, (LPCWSTR)msg.c_str(), (LPCWSTR)caption.c_str(), MB_ICONINFORMATION);
}
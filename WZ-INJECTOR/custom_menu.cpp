#include"custom_menu.h"
#include "injector.h"
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <shellapi.h>
#include "skStr.h"
#include "xhackorx.hpp"

bool g_once = true;
bool do_once = true;
const char* testing[] = { "Your Tool Name" };
RECT desktop;
bool center_once = true;
float width;
float height;
ImVec2 vec_login, vec_register;
static int testint = 0;





void Ricocheat::Begin()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}


void Ricocheat::Menu(bool* close)
{
	ImGui::Begin(XorStr("Fiz injector").c_str(), close, window_flags);
	{
		ImGui::SetWindowSize({ 400,300 });
		if (b_get_message)
			Tab = Menu_Tab::global_message;

		if (Tab == Menu_Tab::Loading)
		{
			timer_start = true;
			LoadingScreen();
			if (timer_start == false)
			{
				if (!loggedin && !free_version)
				{
					version_check = false;
					Tab = Menu_Tab::check_version; // first start of the programm this will be called
				}

				else if (free_version)
				{
					free_version = false;
					Tab = Menu_Tab::free_page;
				}

				else if (loggedin)
				{
					loggedin = false;
					Tab = Menu_Tab::main_page;
				}
			}
		}

		if (Tab == Menu_Tab::check_version)
		{
			if (!check_version())
			{
				ImGui::PushFont(big_font);
				ColoredText(g_versions_check.c_str(), true, Color::Red);
				ImGui::PopFont();
			}
			else
			{
				Tab = Menu_Tab::Login;
			}
		}

		if (Tab == Menu_Tab::free_page)
		{
			ImGui::SameLine(160);
			const char* testing[] = { XorStr("Vanguard(Beta ) ").c_str() };
			static int testint = 0;
			ImGui::SetCursorPos({ 80.f,130.f });
			ImGui::Combo("##freecombo", &testint, "Vanguard\0", 1);
			ImGui::SetCursorPos({ 160.f,190.f });
			if (ImGui::Button(XorStr("Inject").c_str(), ImVec2(80, 50)))
			{

				if (testint == 0)
				{
					/*spoofstart();*/
					int whatdll = 0;

					std::vector<uint8_t>rawdata;

					switch (whatdll)
					{
					case 0:  rawdata = KeyAuthApp.download(Vanguard); break;
					default:

						Sleep(3000);
						exit(0);
						break;
					}
					if (rawdata.empty())
					{
						log = "Failed to download";
						Tab = Menu_Tab::failure;
						return;
					}

					if (!b_get_message)
					{
						DWORD TaskPid = process_ID(L"winver.exe");
						HANDLE hproc = OpenProcess(PROCESS_ALL_ACCESS, 0, TaskPid);



						if (TaskPid)
						{
							ImGui::SetCursorPos({ 30,30 });
							if (!ManualMapDll(hproc, (BYTE*)&rawdata[0], rawdata.size(), true, true, true, true, DLL_PROCESS_ATTACH, 0))
							{


								log = XorStr("Failed to Inject");
								Tab = Menu_Tab::failure;
							}
							else
							{
								log = XorStr("Successfully injected!");
								Tab = Menu_Tab::Success;
							}
						}
					}


				}

			}
		}

		if (Tab == Menu_Tab::main_page)
		{
				ImGui::Spacing;
				ImGui::Spacing;
				ImGui::SetCursorPos({ 75.f,100.f });
				ImGui::Combo("##test", &testint, testing, IM_ARRAYSIZE(testing));

				ImGui::SetCursorPos({ 170, 200 });
				if (ImGui::Button(XorStr("Inject").c_str(), ImVec2(70, 25)))
				{

					if (testint == 0)
					{
						/*spoofstart();*/
						int whatdll = 0;

						std::vector<uint8_t>rawdata;
						switch (whatdll)
						{
						case 0:  rawdata = KeyAuthApp.download(LoaderDll); break;
						default:

							Sleep(3000);
							exit(0);
							break;
						}


						ShowWindow(GetConsoleWindow(), SW_HIDE);
						DWORD TaskPid = process_ID(L"winver.exe");
						ShowWindow(GetConsoleWindow(), SW_HIDE);
						HANDLE hproc = OpenProcess(PROCESS_ALL_ACCESS, 0, TaskPid);


						if (TaskPid)
						{
							if (!ManualMapDll(hproc, (BYTE*)&rawdata[0], rawdata.size(), true, true, true, true, DLL_PROCESS_ATTACH, 0))
							{

								log = XorStr("Failed to Inject");
								Tab = Menu_Tab::failure;
							}
							else
							{
								log = XorStr("Successfully injected!");
								Tab = Menu_Tab::Success;
							
						}

					}

					if (testint == 1)
					{
						/*spoofstart();*/
						int whatdll = 0;

						std::vector<uint8_t>rawdata;
						switch (whatdll)
						{
						case 0:  rawdata = KeyAuthApp.download(Vanguard); break;
						default:

							Sleep(3000);
							exit(0);
							break;
						}


						DWORD TaskPid = process_ID(L"winver.exe");
						HANDLE hproc = OpenProcess(PROCESS_ALL_ACCESS, 0, TaskPid);



						if (TaskPid)
						{



							ImGui::SetCursorPos({ 30,30 });
							if (!ManualMapDll(hproc, (BYTE*)&rawdata[0], rawdata.size(), true, true, true, true, DLL_PROCESS_ATTACH, 0))
							{

								log = XorStr("Failed to Inject");
								Tab = Menu_Tab::failure;
							}
							else
							{
								log = XorStr("Successfully injected!");
								Tab = Menu_Tab::Success;
								ImGui::SetCursorPos({ 30,30 });
							}
						}

					}


				}


			}
		}

		if (Tab == Menu_Tab::Upgrade)
		{
			ImGui::SetCursorPosY({ ImGui::GetCursorPosY() + 40 });
			ImGui::Text("Username:");

			ImGui::SameLine(80.5);
			ImGui::InputText("##Usernameupgrade", up_Username, IM_ARRAYSIZE(up_Username));

			ImGui::Text("New License:");
			ImGui::SameLine(80.5);
			ImGui::InputText("##Licenseupgrade", up_Licence, IM_ARRAYSIZE(up_Licence), ImGuiInputTextFlags_::ImGuiInputTextFlags_Password);
		}

		if (Tab == Menu_Tab::Register)
		{


			ImGui::SetCursorPosY({ ImGui::GetCursorPosY() + 40 });
			ImGui::Text("Username:");

			ImGui::SameLine(80.5);
			ImGui::InputText("##Usernamereg", reg_Username, IM_ARRAYSIZE(reg_Username));

			ImGui::Text("Password:");
			ImGui::SameLine(80.5);
			ImGui::InputText("##Passwordreg", reg_Password, IM_ARRAYSIZE(reg_Password), ImGuiInputTextFlags_::ImGuiInputTextFlags_Password);

			ImGui::Text(XorStr("License:").c_str());
			ImGui::SameLine(80.5);
			ImGui::InputText(XorStr("##key").c_str(), reg_Licence, IM_ARRAYSIZE(reg_Licence));
			ImGui::SetCursorPos({ 100, ImGui::GetCursorPosY() + 20 });



			if (ImGui::Button(XorStr("Register").c_str(), { 80,35 }))
			{
				int pw_lenght = std::string(reg_Password).length();
				int user_lenght = std::string(reg_Username).length();
				if (std::string(reg_Username).empty())
				{
					str_warn = ("No Username!");
					ImGui::OpenPopup("warn");
				}
				else if (user_lenght <= 4)
				{
					str_warn = ("Username must be greater than 4 Characters!");
					ImGui::OpenPopup("warn");
				}
				else if (std::string(reg_Password).empty())
				{
					str_warn = ("No Password!");
					ImGui::OpenPopup("warn");
				}
				else if (pw_lenght <= 4)
				{
					str_warn = ("Password must be greater than 4 Characters!");
					ImGui::OpenPopup("warn");
				}

				else if (std::string(reg_Licence).empty())
				{
					str_warn = ("No License!");
					ImGui::OpenPopup("warn");
				}
				else
				{
					KeyAuthApp.regstr(reg_Username, reg_Password, reg_Licence);
					if (!b_get_message)
					{
						memset(&reg_Username[0], 0, sizeof(reg_Username));
						memset(&reg_Password[0], 0, sizeof(reg_Password));
						memset(&reg_Licence[0], 0, sizeof(reg_Licence));
						log = XorStr("Successfully registered!");
						is_registered = true;
						Tab = Menu_Tab::Success;

					}
				}




			}
			ImGui::SameLine();
			ImGui::SetCursorPosX(210);
			vec_login = ImGui::GetCursorPos();
			if (ImGui::Button("Back##log1", { 30,30 }))
			{

				Tab = Menu_Tab::Login;
			}

			ImGui::SetCursorPos({ 5.f, 270.f });
			ImGui::Text(version.c_str());
			/*	ImGui::SetCursorPos({ 267.f, 270.f });
				ImGui::Text(XorStr("RICOCHEAT SERVICE").c_str());*/

		}

		if (Tab == Menu_Tab::Login)
		{
			ImGui::SetCursorPos({ 75.f,100.f });
			ImGui::InputTextWithHint(("##KeyInput"), ("Key Here"), Licence, 30);
			ImGui::SetCursorPosX(162);
			/*	if (ImGui::Button("Free Tool##log2", { 80,35 }))
				{
					KeyAuthApp.Free_license(XorStr("FREE-0C8HSNK5MRYX9D"));
					if (!b_get_message)
					{

						free_version = true;
						timer_start = true;
						Tab = Menu_Tab::Loading;
					}
					else
					{
						Tab = Menu_Tab::global_message;
					}
				}*/


			ImGui::SetCursorPos({ 170, 200 });
			if (ImGui::Button("Login##log2", { 70,25 }))
			{
				KeyAuthApp.license(Licence);
				if (!b_get_message)
				{
					timer_start = true;
					loggedin = true;
					Tab = Menu_Tab::main_page;
				}
				else
				{
					KeyAuthApp.log(Licence);
					Tab = Menu_Tab::global_message;


				}


			}

			/*ImGui::SameLine(ImGui::GetCursorPosX() + 203);

			if (ImGui::Button("Register##log1", { 80,35 }))
			{
				Tab = Menu_Tab::Register;
			}*/





			ImGui::SetCursorPos({ 5.f, 270.f });
			ImGui::Text(version.c_str());
			//ImGui::SetCursorPos({ 267.f, 270.f });
			//ImGui::Text(XorStr("RICOCHEAT SERVICE").c_str());

		}

		if (Tab == Menu_Tab::failure)
		{
			ColoredText(log.c_str(), true);
			ImGui::SetCursorPos({ 170, 200 });
			if (ImGui::Button("Exit Application", { 60,30 }))
			{
				TerminateProcess(GetCurrentProcess(), 0);
			}
		}

		if (Tab == Menu_Tab::Success)
		{

			if (!is_registered)
			{
				ColoredText(log.c_str(), true, Color::Green);
				ImGui::SetCursorPos({ 170, 200 });
				if (ImGui::Button("Exit Application", { 60,30 }))
				{
					TerminateProcess(GetCurrentProcess(), 0);
				}
			}
			else
			{
				ColoredText(log.c_str(), true, Color::Green);
				ImGui::SetCursorPos({ 95, 80 });
				if (ImGui::Button("Ok", { 60,30 }))
				{
					Tab = Menu_Tab::Login;
				}
			}




		}

		if (Tab == Menu_Tab::global_message)
		{
			ColoredText(message_response.c_str(), true, Color::Red);
			ImGui::SetCursorPos({ 160, 200 });
			if (ImGui::Button("Exit Application", { 100,30 }))
			{
				TerminateProcess(GetCurrentProcess(), 0);
			}
		}

		PopupWarning(str_warn.c_str());
	}
}

void Ricocheat::End()
{
	ImGui::End();
	ImGui::EndFrame();
}

void Ricocheat::Render(bool* close)
{
	if (do_once)
	{

		KeyAuthApp.init();
		do_once = false;
	}

	Begin();
	Menu(close);
	End();
}

void Ricocheat::LoadingScreen() //global loading screen.
{
	if (timer_start)
	{
		if (g_once)
		{
			timer.start();
			g_once = false;
		}
		ImGui::SetCursorPos({ 170.f,150.f });
		ImGui::Text("Loading...");
		if (timer.elapsedSeconds() > 3.4)
		{
			timer.stop();
			timer_start = false;
			g_once = true;

		}

	}

}

void Ricocheat::PopupWarning(const char* text)
{
	if (ImGui::BeginPopup(XorStr("warn").c_str(), ImGuiWindowFlags_::ImGuiWindowFlags_None))
	{
		ColoredText(text, false);
		ImGui::EndPopup();
	}
}

void Ricocheat::ColoredText(const char* Label, bool center, ImVec4 color)
{
	if (center)
	{
		auto windowWidth = ImGui::GetWindowSize().x;
		auto textWidth = ImGui::CalcTextSize(Label).x;
		ImGui::SetCursorPos({ (windowWidth - textWidth) * 0.5f, 130 });
		ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Text, color);
		ImGui::Text(Label);
		ImGui::PopStyleColor();
	}
	else
	{
		ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Text, color);
		ImGui::Text(Label);
		ImGui::PopStyleColor();

	}

}

bool Ricocheat::check_version()
{
	std::string version = get_version();

	if (strcmp(version.c_str(), "1903") == 0 || strcmp(version.c_str(), "1909") == 0 || strcmp(version.c_str(), "2004") == 0 || strcmp(version.c_str(), "20H2") == 0 || strcmp(version.c_str(), "21H2") == 0 || strcmp(version.c_str(), "21H1") == 0)
		return true;
	else
		g_versions_check = version + " is not supported.Please\n update or downgrade to \n1909, 2004 ,20H2 ,21H1 or 21H2!";
	return false;
}

void Ricocheat::Userinfo()
{
	time_t currenttime;
	struct tm* tminfo;
	time(&currenttime);
	tminfo = localtime(&currenttime);

	std::time_t x = std::mktime(tminfo);
	std::time_t y = std::mktime(&KeyAuthApp.user_data.expiry);
	int difference{};
	if (x != (std::time_t)(-1) && y != (std::time_t)(-1))
	{
		difference = std::difftime(y, x) / (60 * 60 * 24);

		if (difference > 1000)
		{
			ImGui::Text("Lifetime");
		}
		else
		{
			ImGui::Text("%d day(s) left", difference);
		}

	}

}

DWORD Ricocheat::process_ID(const wchar_t* process)
{
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, procId);

	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry)) {
			do {
				if (wcscmp(process, procEntry.szExeFile) == 0) {
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
	return procId;
}

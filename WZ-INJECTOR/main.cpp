
#include <iostream>
#include"custom_menu.h"
#include"injector.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <windows.h>
#include <thread>
#include <random>
#include <D3dx9tex.h>
#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")

#pragma comment(lib, "D3dx9")

IDirect3DTexture9* masterlogo;

#include "others/ImGui/imgui.h"
#include "others/ImGui/imgui_impl_dx9.h"
#include "others/ImGui/imgui_impl_win32.h"

#include"anti_debug.hpp"
#include "others/ImGui/imgui_internal.h"





void ImguiMessage(const char* text,bool injection );



void getLastErrorFromInject();
bool loader_active = true;

static int width = 350;
static int height = 200;

char PassWord[20] = "";
char Licence[50] = "";
char UserName[20] = "";
char RgPassWord[20] = "";
char RgUserName[20] = "";

HWND main_hwnd = nullptr;

LPDIRECT3DDEVICE9        g_pd3dDevice;
D3DPRESENT_PARAMETERS    g_d3dpp;
LPDIRECT3D9              g_pD3D;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

bool CreateDeviceD3D(HWND hWnd)
{
	if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return false;

	// Create the D3DDevice
	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
	//g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
	if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
		return false;
	return true;
}

void CleanupDeviceD3D()
{
	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
	if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
	if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);
	ImGui_ImplDX9_CreateDeviceObjects();
}

bool LoginCheck = false;

void GameIsRunning()
{

	while (true)
	{
		HWND hclass = FindWindowA("IW8", 0);
		if (hclass)
		{
			auto process = GetCurrentProcess();
			TerminateProcess(process, 0);
		}

		Sleep(1000);
	}

}

std::string random_string(const int len) {
	const std::string alpha_numeric("abcdefghijklmnopqrstuvwxyz1234567890");

	std::default_random_engine generator{ std::random_device{}() };
	const std::uniform_int_distribution< std::string::size_type > distribution{ 0, alpha_numeric.size() - 1 };

	std::string str(len, 0);
	for (auto& it : str) {
		it = alpha_numeric[distribution(generator)];
	}

	return str;
}

std::wstring getproc = L"winver.exe";
DWORD getProcID(std::wstring procName) {
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, procId);
	ShowWindow(GetConsoleWindow(), SW_HIDE);

    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry)) {
            do {
                if (wcscmp(procName.c_str(), procEntry.szExeFile) == 0) {
					ShowWindow(GetConsoleWindow(), SW_HIDE);
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;
}
BOOL TerminateProcessEx(DWORD dwProcessId, UINT uExitCode)
{
	DWORD dwDesiredAccess = PROCESS_TERMINATE;
	BOOL  bInheritHandle = FALSE;
	HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
	if (hProcess == NULL)
		return FALSE;

	BOOL result = TerminateProcess(hProcess, uExitCode);

	CloseHandle(hProcess);

	return result;
}
void createTask()
{
	
	DWORD taskPid = getProcID(L"winver.exe");
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	TerminateProcessEx(taskPid, 0);
	ShellExecuteA(0, 0, "winver.exe", 0, 0, false);
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	


}

POINT mouse;

namespace menu_tab
{
	 int Tab = 2;
}
void Message(std::string text)
{
	MessageBoxA(0, text.c_str(), "Error", MB_OK);
}

std::string path()
{
	char shitter[_MAX_PATH]; // defining the path
	GetModuleFileNameA(NULL, shitter, _MAX_PATH); // getting the path
	return std::string(shitter); //returning the path
}

int APIENTRY WindownsMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Ricocheat ricocheat;
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL,L"Loader", NULL };
	RegisterClassEx(&wc);
	main_hwnd = CreateWindow(wc.lpszClassName, L"Loader", WS_POPUP, 0, 0, 5, 5, NULL, NULL, wc.hInstance, NULL);

	
	if (!CreateDeviceD3D(main_hwnd)) {
		CleanupDeviceD3D();
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 1;
	}
	ShowWindow(main_hwnd, SW_HIDE);
	UpdateWindow(main_hwnd);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.IniSavingRate = 1.f;



	ImGuiStyle& style = ImGui::GetStyle();
	const float bor_size = style.WindowBorderSize;
	style.WindowBorderSize = 0.0f;

	ImFont* main_font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 16.0f);
	ricocheat.big_font =  io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 24.0f);

	
	

	

	style.WindowBorderSize = bor_size;
	style.WindowPadding = ImVec2(8, 8);
	style.WindowRounding = 10.0f;
	style.ChildRounding = 0.f;
	style.FramePadding = ImVec2(5, 5);
	style.FrameRounding = 6.0f;
	style.PopupRounding = 3.f;
	style.ItemSpacing = ImVec2(8, 8);
	style.ItemInnerSpacing = ImVec2(8, 6);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 6.0f;
	style.WindowTitleAlign = { 0.5f,0.5f };
	

	style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImColor(0, 0, 0, 0.62);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImColor(0.80f, 0.80f, 0.83f, 1.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImColor(41, 47, 54, 100);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(41, 47, 54, 100);
	style.Colors[ImGuiCol_TitleBgActive] = ImColor(41, 47, 54, 100);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImColor(41, 47, 54, 100);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);

	style.Colors[ImGuiCol_Tab] = ImVec4(0.10f, 0.10f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_TabActive] = style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);


	ImGui_ImplWin32_Init(main_hwnd);
	ImGui_ImplDX9_Init(g_pd3dDevice);

	DWORD window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
	RECT screen_rect;
	GetWindowRect(GetDesktopWindow(), &screen_rect);
	auto x = float(screen_rect.right - width) / 2.f;
	auto y = float(screen_rect.bottom - height) / 2.f;

	static int Tabs = 2;
	bool islogged_in = false;
	bool go_to_free = false;
	bool InfWindow = false;
	const DWORD nTickTime = 64;//64 ms
	bool bUpdateTick = false;
	

	std::string name = random_string(10) + ".exe";
	std::rename(path().c_str(), name.c_str()); //renaming the file

	///*is_already_running();*/
	//auto link = XorStr("https://cdn.discordapp.com/attachments/866616028628385802/958163936828596294/ricocheat_header.png");
	//auto path = XorStr("C:\\ricocheat\\image\\ricocheat_header.png");

	//if(!PathFileExistsA(path.c_str()))
	//URLDownloadToFileA(0, link.c_str(), path.c_str(), 0, 0);


	createTask();
	
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	static float progress = 1;

	while (msg.message != WM_QUIT && !quit)
	{
		
	
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		
		
		ricocheat.Render(&loader_active); //render menu and stuff
		

	

		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		if (g_pd3dDevice->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			g_pd3dDevice->EndScene();
		}
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
		HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
		if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
			ResetDevice();
		}
		if (!loader_active) {
			msg.message = WM_QUIT;
		}
	}

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	CleanupDeviceD3D();
//	DestroyWindow(main_hwnd);
	UnregisterClass(wc.lpszClassName, wc.hInstance);
//	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;
	switch (msg)
	{
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			g_d3dpp.BackBufferWidth = LOWORD(lParam);
			g_d3dpp.BackBufferHeight = HIWORD(lParam);
			ResetDevice();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//using check = security::internal::debug_results;
//utils u;
//
//void DebugCheck()
//{
//	while (true)
//	{
//		/*if (security::internal::memory::check_window_name() != check::none) {
//			exit(0);
//		}*/
//		if (security::check_security() != check::none )
//		{
//			
//			KeyAuthApp.ban();
//			HANDLE currproc = GetCurrentProcess();
//			TerminateProcess(currproc,0);
//		}
//		Sleep(500);
//	}
//}

void create_directory()
{
	
		//CreateDirectoryA("C:\\ricocheat", 0);
		//CreateDirectoryA("C:\\ricocheat\\music", 0);
		//CreateDirectoryA("C:\\ricocheat\\image", 0);
		//CreateDirectoryA("C:\\ricocheat\\modern warfare", 0);
		//CreateDirectoryA("C:\\ricocheat\\modern warfare\\config", 0);
		//CreateDirectoryA("C:\\ricocheat\\vanguard", 0);
		//CreateDirectoryA("C:\\ricocheat\\vanguard\\config", 0);
	
		
}

void getLastErrorFromInject()
{

	/*if (!PathFileExistsA("C:\\ricocheat"))
		CreateDirectoryA("C:\\ricocheat", 0);

	std::ifstream in("C:\\ricocheat\\error.txt", std::ios::app);
	std::string buff;
	std::vector<std::string>errors;
	std::vector<std::string>save_errors;
	std::string input;
	LPSTR buffer = (LPSTR)"error.txt";
	bool is_valid = false;

	if (!PathFileExistsA("C:\\ricocheat\\error.txt"))return;
	
		is_valid = true;
		
		while (in >> input)
		{
			errors.push_back(input);

		}
		if (errors.empty())
		{
			in.close();
			std::remove("C:\\ricocheat\\error.txt");
			return;
		}
		
		for (std::string errorh : errors)
		{
			save_errors.push_back(errorh);
		}

	for (size_t i = 0; i < save_errors.size(); i++)
	{
	
		buff += save_errors.at(i)+ "\n";
	}
	if (is_valid)
	{
		in.close();
		std::remove("C:\\ricocheat\\error.txt");
		MessageBoxA(0, buff.c_str(), "test", MB_OK | MB_SYSTEMMODAL);
	}
	in.close();*/
}




int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR lpCmdLine,int nCmdShow)
{
	/*std::thread anti(DebugCheck); anti.detach();*/
	/*std::thread run(GameIsRunning); run.detach();*/
	
	create_directory();
	//std::thread version(check_version); version.detach();


	WindownsMain(0, 0, 0, 0);

//	MessageBox(NULL, TEXT("Login successful! %d"), TEXT("Login"), MB_OK);

	//KeyAuthApp.init();
	//system(XorStr("cls").c_str());
	//
	//std::cout << XorStr("\n\n [1] Login\n [2] Register\n [3] Upgrade\n [4] License key only\n\n Choose option: ");

	//int option;
	//std::string username;
	//std::string password;
	//std::string key;

	//std::cin >> option;
	//switch (option)
	//{
	//	case 1:
	//		std::cout << XorStr("\n\n Enter username: ");
	//		std::cin >> username;
	//		std::cout << XorStr("\n Enter password: ");
	//		std::cin >> password;
	//		KeyAuthApp.login(username, password);
	//		break;
	//	case 2:
	//		std::cout << XorStr("\n\n Enter username: ");
	//		std::cin >> username;
	//		std::cout << XorStr("\n Enter password: ");
	//		std::cin >> password;
	//		std::cout << XorStr("\n Enter license: ");
	//		std::cin >> key;
	//		KeyAuthApp.regstr(username,password,key);
	//		break;
	//	case 3:
	//		std::cout << XorStr("\n\n Enter username: ");
	//		std::cin >> username;
	//		std::cout << XorStr("\n Enter license: ");
	//		std::cin >> key;
	//		KeyAuthApp.upgrade(username, key);
	//		break;
	//	case 4:
	//		std::cout << XorStr("\n Enter license: ");
	//		std::cin >> key;
	//		KeyAuthApp.license(key);
	//		break;
	//	default:
	//		std::cout << XorStr("\n\n Status: Failure: Invalid Selection");
	//		Sleep(3000);
	//		exit(0);
	//}
	
	/*
	// download file
    std::vector<std::uint8_t> bytes = KeyAuthApp.download("123456");
    std::ofstream file("file.exe", std::ios_base::out | std::ios_base::binary);
    file.write((char*)bytes.data(), bytes.size());
    file.close();
	*/
	
	// KeyAuthApp.log("user logged in"); // send event to logs. if you set discord webhook in app settings, it will send there too
	// KeyAuthApp.webhook("HDb5HiwOSM", "&type=black&ip=1.1.1.1&hwid=abc"); // webhook request to securely send GET request to API, here's what it looks like on dashboard https://i.imgur.com/jW74Hwe.png
	// KeyAuthApp.ban(); // ban the current user, must be logged in

	//#pragma region
	//time_t rawtime = mktime(&KeyAuthApp.user_data.expiry);
	//struct tm* timeinfo;
	//timeinfo = localtime(&rawtime);
	//printf(XorStr("\n Your Subscription Expires At: %s").c_str(), asctime(timeinfo));
	//
	//time_t currtime;
	//struct tm* tminfo;
	//time(&currtime);
	//tminfo = localtime(&currtime);

	//std::time_t x = std::mktime(tminfo);
	//std::time_t y = std::mktime(&KeyAuthApp.user_data.expiry);
	//if (x != (std::time_t)(-1) && y != (std::time_t)(-1))
	//{
	//	double difference = std::difftime(y, x) / (60 * 60 * 24);
	//	std::cout << "\n " << difference << " day(s) left" << std::endl;
	//}
	//#pragma endregion Display Expiration Date and Days Left Until Expiry
	//
	//Sleep(-1); // this is to keep your application open for test purposes. it pauses your application forever, remove this when you want.
}


static void ImguiMessage(const char* text,bool injection_info)
{
	if (!injection_info)
	{
		auto windowWidth = ImGui::GetWindowSize().x;
		auto textWidth = ImGui::CalcTextSize(text).x;
		ImGui::SetCursorPos({ (windowWidth - textWidth) * 0.5f, 130 });
		ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Text, { 255,0,0,255 });
		ImGui::Text(text);
		ImGui::PopStyleColor();
	}
	else
	{
		auto windowWidth = ImGui::GetWindowSize().x;
		auto textWidth = ImGui::CalcTextSize(text).x;
		ImGui::SetCursorPos({ (windowWidth - textWidth) * 0.5f, 130 });
		ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Text, { 255,255,255,255 });
		ImGui::Text(text);
		ImGui::PopStyleColor();
	}

}

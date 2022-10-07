#pragma once


#include "others/ImGui/imgui_impl_dx9.h"
#include "others/ImGui/imgui_impl_win32.h"
#include "others/ImGui/imgui.h"
#include "others/ImGui/imgui_internal.h"
#include"timer.h"
#include "api/KeyAuth.hpp"

extern bool b_get_message;
inline DWORD window_flags =  ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize ;
inline bool quit = false;


using namespace KeyAuth;

inline std::string LoaderDll = XorStr("662035"); // enter keyauth file id here
inline std::string Spoof = XorStr("534037");
inline std::string MW_UAV = XorStr("061904");
inline std::string Vanguard = XorStr("638338");

inline std::string name = XorStr("devwareontop"); //enter your keyauth info here
inline std::string ownerid = XorStr("fYikH6hZ1M"); //enter your keyauth info here
inline std::string secret = XorStr("ca3e43219423a83fd001a0ede19d70eea9424982f50c8eff29b864d6be644c8a"); //enter your keyauth info here
inline std::string version = XorStr("1.0"); //enter your keyauth info here

inline api KeyAuthApp(name, ownerid, secret, version);




inline std::string get_version() {
	DWORD dwType = REG_SZ;
	HKEY hKey = 0;
	char value[1024];
	DWORD value_length = 1024;
	LSTATUS status2{};
	const char* subkey = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
	RegOpenKeyA(HKEY_LOCAL_MACHINE, subkey, &hKey);
	const auto status = RegQueryValueExA(hKey, "DisplayVersion", NULL, &dwType, (LPBYTE)&value, &value_length);

	if (status != 0 || std::string(value).empty())
		status2 = RegQueryValueExA(hKey, "ReleaseId", NULL, &dwType, (LPBYTE)&value, &value_length);

	RegCloseKey(hKey);
	return std::string(value);
}

inline double PI_I = 3.14159265358979323846;
static void  LoadingIndicatorCircle(const char* label, const float indicator_radius,
	const ImVec4& main_color, const ImVec4& backdrop_color,
	const int circle_count, const float speed) {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems) {
		return;
	}

	ImGuiContext& g = *GImGui;
	const ImGuiID id = window->GetID(label);

	const ImVec2 pos = window->DC.CursorPos;
	const float circle_radius = indicator_radius / 10.0f;
	const ImRect bb(pos, ImVec2(pos.x + indicator_radius * 2.0f,
		pos.y + indicator_radius * 2.0f));
	ImGui::ItemSize(bb, 8);
	if (!ImGui::ItemAdd(bb, id)) {
		return;
	}
	const float t = g.Time;
	const auto degree_offset = 2.0f * PI_I / circle_count;
	for (int i = 0; i < circle_count; ++i) {
		const auto x = indicator_radius * std::sin(degree_offset * i);
		const auto y = indicator_radius * std::cos(degree_offset * i);
		const auto growth = max(0.0f, std::sin(t * speed - i * degree_offset));
		ImVec4 color;
		color.x = main_color.x * growth + backdrop_color.x * (1.0f - growth);
		color.y = main_color.y * growth + backdrop_color.y * (1.0f - growth);
		color.z = main_color.z * growth + backdrop_color.z * (1.0f - growth);
		color.w = 1.0f;
		window->DrawList->AddCircleFilled(ImVec2(pos.x + indicator_radius + x,
			pos.y + indicator_radius - y),
			circle_radius + growth * circle_radius,
			ImGui::GetColorU32(color));
	}
}



namespace Color
{
	inline ImVec4 Red = { 255,0,0,255 };
	inline ImVec4 Green = { 0,255,0,255 };
	inline ImVec4 Blue = { 0,0,255,255 };
}


enum Menu_Tab
{
	failure = -1,
	Success,
	global_message,
	Register,
	Login,
	Upgrade,
	check_version,
	main_page,
	free_page,
	Loading

	


};



class Ricocheat
{
	std::string log = "null";
	std::string g_versions_check = "null";
	std::string str_warn = "null";
	char Licence[50] = "";
	char Username[50] = "";
	char Password[50] = "";

	char reg_Licence[50] = "";
	char reg_Username[14] = "";
	char reg_Password[50] = "";

	char up_Licence[50] = "";
	char up_Username[50] = "";

	int Tab = Menu_Tab::Loading;
	bool is_registered = false;
	bool version_check = false;
	bool b_injection = false;
	bool timer_start = false;
	bool loggedin = false;
	bool free_version = false;
	Timer timer = {};
	
	
public:
	bool quit = false;
	ImFont* big_font = nullptr;
public:
	//rendering

	void Begin();
	void Menu(bool* close);
	void End();
	void Render(bool* close);
	void LoadingScreen();
	void PopupWarning(const char* text);
	void ColoredText(const char* Label, bool center = true, ImVec4 color = Color::Red);
	bool check_version();


private:
	//internal
	
	void Userinfo();
	DWORD process_ID(const wchar_t* process);
	
};

#include "Log.h"
		const std::string kLogName("SdlGame.log");
namespace LogInfo {
  Log::Log() {
	}
	Log::~Log() {

	}

	void Log::WriteLog(const char* str) {
		std::string module_path = GetPathModule();
		std::string log_name_path = module_path + ("\\") + kLogName;
		short length = log_name_path.length();
		char* log_np = new char [length];
		strcpy(log_np, log_name_path.c_str());

		std::ofstream log_file;
		log_file.open(log_np, std::ios::out|std::ios::app);
		if (log_file.fail())
		{
			return;
		}

		char* time = GetTime();
		char* date = GetDate();
		log_file << date
						 << "  "
						 << time
						 << "  "
						 << str 
						 << std::endl;

		log_file.close();
	}

	char* Log::GetTime() {
		std::wstringstream wss;
		SYSTEMTIME sys_time;
		::GetLocalTime(&sys_time);
		wss << std::setfill(L'0');
		wss << sys_time.wHour << ":" << std::setw(2);
		wss << sys_time.wMinute << ":" << std::setw(2);
		wss << sys_time.wSecond;

		std::wstring wstr = wss.str();
		char* str_time = new char[wstr.length()];
		for (int i = 0; i <wstr.length(); ++i) {
			str_time[i] = (char)wstr[i];
		}
		str_time[wstr.length()] = '\0';
		return str_time;
	}

	char* Log::GetDate() {
		std::wstringstream wss;
		SYSTEMTIME sys_time;
		::GetLocalTime(&sys_time);
		wss << std::setfill(L'0');
		wss << sys_time.wYear << L"-" << std::setw(2)
			  << sys_time.wMonth << L"-" << std::setw(2)
		    << sys_time.wDay;

		std::wstring wstr = wss.str();
		char* str_date = new char[wstr.length()];
		for (int i = 0; i <wstr.length(); ++i) {
			str_date[i] = (char)wstr[i];
		}
		str_date[wstr.length()] = '\0';
		return str_date;
	}

	std::string WcharToString(wchar_t* wchar_str) {
		std::string str("");
		int index = 0;
		while (wchar_str[index] != 0) {
			str += (char)wchar_str[index];
			++ index;
		}
		return str;
	}

	std::string GetPathModule() {
		wchar_t* md_path = new wchar_t[MAX_PATH];
		::GetModuleFileNameW(NULL, (LPWSTR)md_path, MAX_PATH);

		std::string module_path = WcharToString(md_path);

		int index = module_path.find_last_of("\\");
		module_path.erase(module_path.begin() + index, module_path.end());
		return module_path;
	}
}


#ifndef LOG_H_
#define LOG_H_
#include <string>
#include <fstream>
#include <Windows.h>
#include <sstream>
#include <cstdarg>
#include <cwchar>
#include <iomanip>

namespace LogInfo {
	class Log {
	public:
		Log();
		~Log();
		void WriteLog (const char* wstr);
		char* GetTime();
		char* GetDate();
	private:
	};

  static std::string WcharToString(wchar_t* wchar_str); 
	static std::string GetPathModule();
}



#endif // LOG_H_

#ifndef TBASIC_H_
#define TBASIC_H_
#include <string>
#include <vector>
#include <fstream>

struct ColorMap
{
    int r_;
    int g_;
    int b_;
};

class TBasic
{
public:

    TBasic();
    ~TBasic();

public:
    static TBasic* GetInstance();

    wchar_t* StringToWchar(std::string str);
    //char* CStringToChar(const CString& str);

    //std::vector<std::string> GetItemFolder(std::string path);
    std::vector<std::string> SplitBySpace(std::string str);

    std::string WcharToString(wchar_t* wchar_str);
    std::wstring WcharToWstring(wchar_t* ws_str);
    std::string GetPathAppdata();
    std::string MakeImagePath();
    //std::string GetModulePathExe();

    bool CheckFileExisting(const char* chFile);
    //bool FolderExists(const CString& strFolderName);

private:
    static TBasic* instance_;
};

#endif 


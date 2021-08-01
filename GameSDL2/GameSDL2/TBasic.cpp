
#include "TBasic.h"

TBasic* TBasic::instance_ = NULL;

TBasic::TBasic()
{

}


TBasic::~TBasic()
{

}

TBasic* TBasic::GetInstance()
{
    if (instance_ == NULL)
    {
        instance_ = new TBasic();
    }
    return instance_;
}

wchar_t* TBasic::StringToWchar(std::string str)
{
    int idx = 0;
    int count = str.size();
    wchar_t *ws_str = new wchar_t[count + 1];
    while (idx < str.size())
    {
        ws_str[idx] = (wchar_t)str[idx];
        idx++;
    }
    ws_str[idx] = 0;
    return ws_str;
}

//char* TBasic::CStringToChar(const CString& str)
//{
//    int length = str.GetLength();
//    char* chString = new char[length + 1];
//    for (int i = 0; i < length; i++)
//    {
//        chString[i] = (char)(LPCTSTR)str.GetAt(i);
//    }
//    chString[length] = '\0';
//    return chString;
//}

//std::vector<std::string> TBasic::GetItemFolder(std::string path)
//{
//    WIN32_FIND_DATA find_data;
//    std::vector<std::string> file_list;
//
//    wchar_t* file_path = StringToWchar(path);
//
//    HANDLE hFind = FindFirstFile(file_path, &find_data);
//
//    file_list.push_back(WcharToString(find_data.cFileName));
//    while (FindNextFile(hFind, &find_data)) 
//    {
//        std::string str = WcharToString(find_data.cFileName);
//        file_list.push_back(str);
//    }
//    return file_list;
//}

std::vector<std::string> TBasic::SplitBySpace(std::string str)
{
    std::vector<std::string> list;
    std::string word = "";
    for (auto x : str)
    {
        if (x == ' ')
        {
            list.push_back(word);
            word = "";
        }
        else
        {
            word = word + x;
        }
    }

    return list;
}

std::string TBasic::WcharToString(wchar_t* wchar_str)
{
    std::string str("");
    int idx = 0;
    while (wchar_str[idx] != 0) 
    {
        str += (char)wchar_str[idx];
        ++idx;
    }
    return str;
}

std::wstring TBasic::WcharToWstring(wchar_t* ws_str)
{
    std::wstring wstring_str = (std::wstring)(ws_str);
    return wstring_str;
}


std::string TBasic::GetPathAppdata()
{
    char* Path;
    size_t length;
    _dupenv_s(&Path, &length, "appdata");
    std::string pathStr(Path);

    int idx = pathStr.find("Roaming");
    pathStr = pathStr.substr(0, idx);
    return pathStr;
}

std::string TBasic::MakeImagePath()
{
    std::string exePath;// = GetModulePathExe();
    exePath = exePath + "\\Images\\map1\\";
    return exePath;
}

//std::string TBasic::GetModulePathExe()
//{
//    std::string exePath;
//    TCHAR chPath[MAX_PATH];
//    HMODULE hModule = GetModuleHandle(NULL);
//    if (hModule != NULL)
//    {
//        GetModuleFileName(hModule, chPath, (sizeof(chPath)));
//
//        std::wstring sTemp(&chPath[0]); //convert to wstring
//        exePath = std::string(sTemp.begin(), sTemp.end());
//
//        exePath = exePath.substr(0, exePath.find_last_of("\\/"));
//    }
//
//    return exePath;
//}

bool TBasic::CheckFileExisting(const char* chFile)
{
    bool is_exist = true;
    std::fstream data_file;
    data_file.open(chFile, std::ios::in);
    bool ret = data_file.fail();
    if (ret == true)
    {
        is_exist = false;
    }
    data_file.close();

    return is_exist;
}

//bool TBasic::FolderExists(const CString& strFolderName)
//{
//    return GetFileAttributes(strFolderName) != INVALID_FILE_ATTRIBUTES;
//}
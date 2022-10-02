#ifndef GENERIC_H_INCLUDED
#define GENERIC_H_INCLUDED
#ifdef USE_UNICODE

///std::wstring
#define GString std::wstring
///Build String
#define Str(X) L##X
///std::wcout
#define sout std::wcout
#define gifstream std::wifstream
#define gofstream std::wofstream
#define gchar wchar_t
#else

///std::string
#define GString std::string
///Build String
#define Str(X) X
///std::cout
#define sout std::cout
#define gifstream std::ifstream
#define gofstream std::ofstream
#define gchar char
#endif // USE_UNICODE
#endif // GENERIC_H_INCLUDED

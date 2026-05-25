#include "stddef.h"
#include <string>
#include <Windows.h>
#include <Strsafe.h>
using namespace std;
class MyVariableUniversalType
{
private:
	bool BooleanType;
	int IntegerType;
	string TextType;
protected:
	LPWSTR TransformStringToWideString(string agrument1)
	{
		LPWSTR tmp_return = new WCHAR[agrument1.length()];
		MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS,
			agrument1.c_str(), agrument1.size(),
			tmp_return, agrument1.length());
		tmp_return[agrument1.length()] = 0;
		return tmp_return;
	}
public:
	LPWSTR TransformStringToWideString2(string agrument1)
	{
		LPWSTR tmp_return = new WCHAR[agrument1.length()];
		MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS,
			agrument1.c_str(), agrument1.size(),
			tmp_return, agrument1.length());
		tmp_return[agrument1.length()] = 0;
		return tmp_return;
	}

	LPCWSTR LPCWSTRTextType = L"";
	MyVariableUniversalType()
	{
		BooleanType = false;
		IntegerType = -1;
		TextType = "";
	}

	int BooleanTypeToInteger(bool argument1)
	{
		if (argument1 = true)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	bool IntegerTypeToBoolean(int argument1)
	{
		if (argument1 > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	string BooleanTypeToString(bool argument1)
	{
		if (argument1 = true)
		{
			return "true";
		}
		else
		{
			return "false";
		}
	}
	bool StringTypeToBoolean(string argument1)
	{
		bool tmp_return = "false";
		string true_variants[]
		{ "true", "True", "TRUE", "truE", "TRue" };
		// ??????????-??????? ??? ?????
		int a = 0;
		// ?????????? ? ????? ??????????? ???????
		int b = true_variants->size();
		// ???????? ? ????? ??????? ?? ???????? ??????? true_variants
		// ?? ????????????
		while (a < b)
		{
			if (argument1 == true_variants[a])
			{
				tmp_return = true;
				a = b + 1;
			}
			a = a + 1;
		}
		return tmp_return;
	}
	LPCWSTR GetVariableValue(string call_back_type)
	{
		if (call_back_type == "Boolean")
		{
			LPCWSTRTextType = TransformStringToWideString(BooleanTypeToString(BooleanType));
			return TransformStringToWideString(BooleanTypeToString(BooleanType));
		}
		if (call_back_type == "String")
		{
			LPCWSTRTextType =
				TransformStringToWideString(TextType);
			return TransformStringToWideString(
				TextType);
		}
		LPCWSTRTextType = L"";
		return L"";
	}
};
class MyChildrenUniversalType : private MyVariableUniversalType
{
public:
	void MyVariableUniversalType()
	{
	}
	LPCWSTR AnyTo(string Any_std_string)
	{
		return (LPCWSTR)TransformStringToWideString(Any_std_string);
	}
	LPCWSTR AnyTo(LPCSTR Any_LPCSTR)
	{
		return (LPCWSTR)Any_LPCSTR;
	}
	LPCWSTR AnyTo(char* Any_CHAR)
	{
		return (LPCWSTR)Any_CHAR;
	}
};
/// ***************************************************************************
/// Copyright (c) 2009, Industrial Logic, Inc., All Rights Reserved.
///
/// This code is the exclusive property of Industrial Logic, Inc. It may ONLY be
/// used by students during Industrial Logic's workshops or by individuals
/// who are being coached by Industrial Logic on a project.
///
/// This code may NOT be copied or used for any other purpose without the prior
/// written consent of Industrial Logic, Inc.
/// ****************************************************************************

#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

#include <string>
#include <cstring>

namespace IL
{

inline bool stringEndsWith(const std::string& stringToSearch, const std::string& searchData)
{
	return stringToSearch.rfind(searchData) == stringToSearch.length() - searchData.length();
}

inline bool stringBeginsWith(const std::string& stringToSearch, const std::string& searchData)
{
	return stringToSearch.find(searchData) == 0;
}

inline bool stringContains(const std::string& stringToSearch, const std::string& searchData)
{
	return stringToSearch.find(searchData) != std::string::npos;
}

inline std::string stringUpperCase(const std::string& inString)
{
	std::string result;
	for (std::string::size_type i = 0; i < inString.length(); i++)
		if (inString[i] >= 'a' && inString[i] <= 'z')
			result += inString[i] + 'A' - 'a';
		else
			result += inString[i];
	return result;
}

inline bool stringEndsWithCaseInsensitive(const std::string& stringToSearch, const std::string& searchData)
{
	return stringUpperCase(stringToSearch).rfind(stringUpperCase(searchData)) != std::string::npos;
}

inline std::string numToString(int i)
{
	char buffer[88];
	sprintf(buffer, "%d", i);
	return std::string(buffer);
}

inline bool argvContains(int argc, char * argv[], const std::string& searchString)
{
	for (int i = 0; i < argc; i++ )
		if (std::string(argv[i]) == searchString)
			return true;
	return false;
}

inline std::string trimSpaces(const std::string str)
{
	std::string result = str;

	size_t firstNonSpace = result.find_first_not_of(" \t");
	if (firstNonSpace != std::string::npos)
		result.erase(0, firstNonSpace);

	size_t lastNonSpace = result.find_last_not_of(" \t");
	if (lastNonSpace != std::string::npos)
		result.erase(lastNonSpace + 1);
	else
		result.clear();

	return result;
}

inline std::string removeStringPrefix(const std::string& prefix, const std::string& operand)
{
	if (prefix.length() == 0 || operand.length() == 0)
		return operand;

	size_t pos = operand.find(prefix);
	if (pos != 0)
		return operand;

	std::string result = operand;
	result.erase(0, prefix.length());
	return result;
}

inline std::string removeStringSuffix(const std::string& suffix, const std::string& operand)
{
	if (suffix.length() == 0 || operand.length() == 0)
		return operand;

	size_t pos = operand.rfind(suffix);
	if (pos != operand.length() - suffix.length())
		return operand;

	std::string result = operand;
	result.erase(pos);
	return result;
}

} // namespace IL

#endif

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

#ifndef IL_TEST_INFO_WRITER_H_
#define IL_TEST_INFO_WRITER_H_

#include <iostream>
#include <vector>
#include <string>

namespace IL
{

struct ILTestInfo
{
	std::string testName;
	std::string suiteName;
};

typedef std::vector<ILTestInfo> TestList;
typedef TestList::iterator ILTestIterator;
typedef TestList::const_iterator ILTestIteratorConst;

class TestInfoWriter
{
private:
	std::ostream& output_;
	long timestamp_;

public:
	TestInfoWriter(std::ostream& output, long timestamp);

	~TestInfoWriter();

	void startXmlLine();

	void writeNumTests(int count);

	void writeNumFailures(int count);

	void writeList(const std::string& name, const TestList& testList);

	void writeTimeStamp();

	void closeXmlLine();
};

} // namespace IL

#endif

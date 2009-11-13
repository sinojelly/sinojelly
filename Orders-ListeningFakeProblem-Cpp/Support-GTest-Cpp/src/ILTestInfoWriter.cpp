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

#include "ILTestInfoWriter.h"
#include <ctime>

#define CRLF "\x0d\x0a";

namespace IL
{

TestInfoWriter::TestInfoWriter(std::ostream& output, long timestamp)
	: output_(output), timestamp_(timestamp)
{
	startXmlLine();
}

TestInfoWriter::~TestInfoWriter()
{
	closeXmlLine();
}

void TestInfoWriter::startXmlLine()
{
	output_ << "<test ";
}

void TestInfoWriter::writeNumTests(int count)
{
	output_ << "count='" << count << "' ";
}

void TestInfoWriter::writeNumFailures(int count)
{
	output_ << "failures='" << count << "' ";
}

void TestInfoWriter::writeList(const std::string& name, const TestList& testList)
{
	output_ << name << "='";
	ILTestIteratorConst it = testList.begin();
	while (it != testList.end())
	{
		output_ << it->testName << "(" << it->suiteName << ")";
		it++;
		if (it != testList.end())
		{
			output_ << ", ";
		}
	}
	output_ << "' ";
}

void TestInfoWriter::writeTimeStamp()
{
	output_ << "stamp='" << timestamp_ << "000'";
}

void TestInfoWriter::closeXmlLine()
{
	output_ << "/>" << CRLF;
}

} // namespace IL

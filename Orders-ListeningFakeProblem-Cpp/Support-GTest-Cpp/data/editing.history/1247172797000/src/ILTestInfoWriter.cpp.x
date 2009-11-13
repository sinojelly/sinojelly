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

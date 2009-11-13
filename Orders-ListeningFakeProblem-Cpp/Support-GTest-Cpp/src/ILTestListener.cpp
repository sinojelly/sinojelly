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

#include "ILTestListener.h"

namespace IL
{

TestEventListener::TestEventListener(std::ostream* output, long timestamp)
	: output_(output), timestamp_(timestamp)
{
}

TestEventListener::~TestEventListener()
{
	delete output_;
}

void TestEventListener::OnUnitTestStart(const testing::UnitTest* unitTest)
{
	// called once at very start.
	// unitTest is not null.
	// valid value = const char* dir = unitTest->original_working_dir();
	// which on windows was: " c:\ganymede\workspace\Support-GTest-Cpp\build"
	// NULL	const testing::TestCase* tc = unitTest->current_test_case();
}

// Called after the unit test ends.
void TestEventListener::OnUnitTestEnd(const testing::UnitTest* unitTest)
{
	// called once at very end.
	// unitTest is not null.
	// valid value = const char* dir = unitTest->original_working_dir();
	// NULL const testing::TestCase* tc = unitTest->current_test_case();

	TestInfoWriter writer(*output_, timestamp_);
	writer.writeNumTests(failedTests_.size() + passedTests_.size());
	writer.writeList("failed", failedTests_);
	writer.writeNumFailures(failedTests_.size());
	writer.writeList("passed", passedTests_);
	writer.writeTimeStamp();
}

void TestEventListener::OnTestCaseStart(const testing::TestCase* testCase)
{
	// called once per test suite before those tests start.
}

void TestEventListener::OnTestCaseEnd(const testing::TestCase* testCase)
{
	// called once per test suite after tests end.
}

void TestEventListener::OnGlobalSetUpStart(const testing::UnitTest* unitTest)
{
	// Called before the global set-up starts, after OnUnitTestStart
}

void TestEventListener::OnGlobalSetUpEnd(const testing::UnitTest* unitTest)
{
	// Called after the global set-up ends, after OnUnitTestStart/OnGlobalSetUpStart
}

void TestEventListener::OnGlobalTearDownStart(const testing::UnitTest* unitTest)
{
	// called after last OnTestCaseEnd
	// Called before the global tear-down starts.
}

void TestEventListener::OnGlobalTearDownEnd(const testing::UnitTest* unitTest)
{
	// Called after last OnTestCaseEnd/OnGlobalTearDownStart
	// Called after the global tear-down ends.
}

void TestEventListener::OnTestStart(const testing::TestInfo* testInfo)
{
	// Called before the test starts, but after printing RUN and testname
	++numTests_;
}

void TestEventListener::OnTestEnd(const testing::TestInfo* testInfo)
{
	// Called after the test ends, after printing OK or FAILED
	if (testInfo->result()->Failed())
	{
		ILTestInfo info;
		info.testName = testInfo->name();
		info.suiteName = testInfo->test_case_name();
		failedTests_.push_back(info);
	}
	else
	{
		ILTestInfo info;
		info.testName = testInfo->name();
		info.suiteName = testInfo->test_case_name();
		passedTests_.push_back(info);
	}
}

// Called after an assertion.
void TestEventListener::OnNewTestPartResult(const testing::TestPartResult* result)
{
	// result is not null
}

} // namespace IL

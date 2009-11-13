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

#ifndef IL_TEST_LISTENER_H_
#define IL_TEST_LISTENER_H_

#include "ILTestInfoWriter.h"

#include <gtest/gtest.h>
#include <gtest/internal/gtest-unit-test-listener.h>
#include <gtest/gtest-spi.h>

#define GTEST_IMPLEMENTATION
#include <gtest-internal-inl.h>
#undef GTEST_IMPLEMENTATION

#include <iostream>
#include <vector>
#include <string>

namespace IL
{

class TestEventListener  : public testing::UnitTestEventListenerInterface
{
private:
	std::ostream* output_;
	int numTests_;
	long timestamp_;

	TestList failedTests_;
	TestList passedTests_;

public:
	TestEventListener(std::ostream* output, long timestamp);

	virtual ~TestEventListener();

	virtual void OnUnitTestStart(const testing::UnitTest* unitTest);

	// Called after the unit test ends.
	virtual void OnUnitTestEnd(const testing::UnitTest* unitTest);

	virtual void OnTestCaseStart(const testing::TestCase* testCase);

	virtual void OnTestCaseEnd(const testing::TestCase* testCase);

	virtual void OnGlobalSetUpStart(const testing::UnitTest* unitTest);

	virtual void OnGlobalSetUpEnd(const testing::UnitTest* unitTest);

	virtual void OnGlobalTearDownStart(const testing::UnitTest* unitTest);

	virtual void OnGlobalTearDownEnd(const testing::UnitTest* unitTest);

	virtual void OnTestStart(const testing::TestInfo* testInfo);

	virtual void OnTestEnd(const testing::TestInfo* testInfo);

	// Called after an assertion.
	virtual void OnNewTestPartResult(const testing::TestPartResult* result);
};

} // end namespace IL

#endif

#ifndef GTESTUNITTESTLISTENER_H_
#define GTESTUNITTESTLISTENER_H_

namespace testing {

class UnitTest;
class TestCase;
class TestPartResult;

// The interface for printing the result of a UnitTest
class UnitTestEventListenerInterface {
 public:
  // The d'tor is pure virtual as this is an abstract class.
  virtual ~UnitTestEventListenerInterface() = 0;

  // Called before the unit test starts.
  virtual void OnUnitTestStart(const UnitTest*) {}

  // Called after the unit test ends.
  virtual void OnUnitTestEnd(const UnitTest*) {}

  // Called before the test case starts.
  virtual void OnTestCaseStart(const TestCase*) {}

  // Called after the test case ends.
  virtual void OnTestCaseEnd(const TestCase*) {}

  // Called before the global set-up starts.
  virtual void OnGlobalSetUpStart(const UnitTest*) {}

  // Called after the global set-up ends.
  virtual void OnGlobalSetUpEnd(const UnitTest*) {}

  // Called before the global tear-down starts.
  virtual void OnGlobalTearDownStart(const UnitTest*) {}

  // Called after the global tear-down ends.
  virtual void OnGlobalTearDownEnd(const UnitTest*) {}

  // Called before the test starts.
  virtual void OnTestStart(const TestInfo*) {}

  // Called after the test ends.
  virtual void OnTestEnd(const TestInfo*) {}

  // Called after an assertion.
  virtual void OnNewTestPartResult(const TestPartResult*) {}
};

}  // namespace testing

#endif /* GTESTUNITTESTLISTENER_H_ */

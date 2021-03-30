#include "VM.h"
//#include "VM.cpp"
using namespace std;

void test(string filename) {
  VM* vm = new VM();
  try {
    vm->run(filename);
  }
  catch (exception& e) {
    cout << e.what();
  }
  delete vm;
}

struct testcase {
  string test;
  string expected;
  testcase() {
    test = "";
    expected = "";
  }

  testcase(string test, string expected) {
    this->test = test;
    this->expected = expected;
  }

  testcase& operator=(const testcase & other) {
    this->test = other.test;
    this->expected = other.expected;
    return *this;
  }
};

void testSuite() {
  testcase testArray[100];

  /// <summary>
  /// You only need to add your testcases and your expected outputs here.
  /// testNum is number of testcase.
  /// 
  /// The testcase is at format: testcase(string yourProgram, string yourExpectedOutput)
  /// 
  /// After running the testcases, the console will display the numbers of testcases
  /// whose results yielded by your VM are different from the expected.
  /// </summary>
  int testNum = 0;

  // Examples
  // 1
  testArray[testNum++] = testcase(
    "Move R1, 1A\n"
    "Output R1\n"
    "Halt",
    "1A"
  );
  
  // 2
  testArray[testNum++] = testcase(
    "Move R15, 1142\n"
    "Output R15\n"
    "Halt",
    "14125"
  );


  /// <summary>
  /// This is use to handle testsuite
  /// You do not need to modify it
  /// </summary>
  ofstream iFile;
  cout << "The testcases which get wrong is at number:" << endl;

  for (int i = 1; i <= testNum; i++) {
    string solName = "solution/sol.txt";
    solName.insert(12, to_string(i));
    string testName = "testcase/prog.txt";
    testName.insert(13, to_string(i));
    streambuf* stream_buffer_cout = cout.rdbuf();

    // Write testcase to file
    iFile.open(testName);
    iFile << testArray[i - 1].test;
    iFile.close();

    // Run testcase and parse solution to file
    iFile.open(solName);
    auto coutbuf = cout.rdbuf(iFile.rdbuf());
    test(testName);
    iFile.close();

    // Check for correctness
    cout.rdbuf(stream_buffer_cout);
    string result = "";
    ifstream oFile;
    oFile.open(solName);
    getline(oFile, result);
    oFile.close();

    if (result != testArray[i - 1].expected) {
      cout << i << endl;
    }
  }
}

int main()
{
  testSuite();
  return 0;
}
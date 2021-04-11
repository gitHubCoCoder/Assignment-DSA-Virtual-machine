#include "VM.h"
#include "windows.h"
#define _CRTDBG_MAP_ALLOC //to get more details
#include <stdlib.h>  
#include <crtdbg.h>   //for malloc and free
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

   /*MOVE
   Test simple
   1
   Move address to R*/
  testArray[testNum++] = testcase(
    "Move R1, 1A\n"
    "Output R1\n"
    "Halt",
    "1A"
  );
  
  // 2
  // Move int to R
  testArray[testNum++] = testcase(
    "Move R15, 0\n"
    "Output R15\n"
    "Halt",
    "0"
  );

  // 3
  // Move float to R
  testArray[testNum++] = testcase(
    "Move R15, 0.100\n"
    "Output R15\n"
    "Halt",
    "0.1"
  );

  // 4
  // Move bool to R
  testArray[testNum++] = testcase(
    "Move R9, true\n"
    "Output R9\n"
    "Halt",
    "true"
  );

  // Test loading error
  // 5
  testArray[testNum++] = testcase(
    "Move R9, 0120\n"
    "Output R9\n"
    "Halt",
    "Invalid operand at address: 0A"
  );

  // 6
  testArray[testNum++] = testcase(
    "Move R16, 120\n"
    "Output R16\n"
    "Halt",
    "Invalid operand at address: 0A"
  );

  // 7
  testArray[testNum++] = testcase(
    "Move R1, 0\n"
    "Output R1 \n"
    "Halt",
    "Invalid instruction at address: 1A"
  );

  // 8
  testArray[testNum++] = testcase(
    "Move R1, 0\n"
    "Output R1\n"
    "Hello",
    "Invalid instruction at address: 2A"
  );

  // 9
  testArray[testNum++] = testcase(
    "Move  R1, 0\n"
    "Output R1\n"
    "Halt",
    "Invalid instruction at address: 0A"
  );

  // 10
  testArray[testNum++] = testcase(
    "Move R 1, 0\n"
    "Output R1\n"
    "Halt",
    "Invalid instruction at address: 0A"
  );

  // 11
  testArray[testNum++] = testcase(
    "Move R1, 0\n"
    "Output R1\n"
    "Halt\n"
    "Hi",
    "Invalid instruction at address: 3A"
  );

  // 12
  testArray[testNum++] = testcase(
    "Move R1, 0\n"
    "Output R1\n"
    "Jump 1A\n"
    "Halt\n"
    "Hi",
    "Invalid instruction at address: 4A"
  );

  // Test complex
  // 13
  testArray[testNum++] = testcase(
    "Move R13, 12\n"
    "Div R13, 20\n"
    "CmpEQ R13, 0.0\n"
    "Output R13\n"
    "Halt",
    "true"
  );

  // 14
  testArray[testNum++] = testcase(
    "Move R13, 5\n"
    "Move R13, 5.005\n"
    "Move R1, 5.0009\n"
    "Add R1, R13\n"
    "Output R1\n"
    "Halt",
    "10.0059"
  );

  // LOAD AND STORE
  // Test simple
  // 15
  testArray[testNum++] = testcase(
    "Move R1, 1000A\n"
    "Store R1, 120.0500\n"
    "Load R2, R1\n"
    "CmpEQ R2, 120.05000\n"
    "Output R2\n"
    "Output R1\n"
    "Halt",
    "true1000A"
  );

  // 16
  testArray[testNum++] = testcase(
    "Move R1, 1000A\n"
    "Store R1, 120.05\n"
    "Load R2, R1\n"
    "CmpNE R2, 120.0500\n"
    "Output R2\n"
    "Output R1\n"
    "Halt",
    "false1000A"
  );

  // 17
  testArray[testNum++] = testcase(
    "Move R1, 1000A\n"
    "Store R1, 120.05\n"
    "Load R2, R1\n"
    "Store R1, R2\n"
    "Load R2, R1\n"
    "CmpEQ R2, 120.0500\n"
    "Output R2\n"
    "Output R1\n"
    "Halt",
    "true1000A"
  );

  // Test runtime error
  // 18
  testArray[testNum++] = testcase(
    "Move R1, 1000\n"
    "Store R1, 120.05\n"
    "Load R2, R1\n"
    "Store R1, R2\n"
    "Load R2, R1\n"
    "CmpEQ R2, 120.0500\n"
    "Output R2\n"
    "Output R1\n"
    "Halt",
    "Type mismatch at address: 1A"
  );

  // 19
  testArray[testNum++] = testcase(
    "Move R1, 1000A\n"
    "Store R1, 120.05\n"
    "Load R2, 1000A\n"
    "Move R1, 500\n"
    "Store R1, R2\n"
    "Output R2\n"
    "Output R1\n"
    "Halt",
    "Type mismatch at address: 4A"
  );

  // 20
  testArray[testNum++] = testcase(
    "Move R1, 1000A\n"
    "Store R1, false\n"
    "Load R2, 1000A\n"
    "CmpNE R2, true\n"
    "Output R2\n"
    "Halt",
    "true"
  );

  // JUMP and JUMPIF
  // 21
  testArray[testNum++] = testcase(
    "Move R1, 1000A\n"
    "Jump 5A\n"
    "Load R2, 1000A\n"
    "CmpNE R2, true\n"
    "Output R2\n"
    "Halt",
    ""
  );

  // Test runtime error
  // 22
  testArray[testNum++] = testcase(
    "Move R1, 1000A\n"
    "Jump 10A\n"
    "Load R2, 1000A\n"
    "CmpNE R2, true\n"
    "Output R2\n"
    "Halt",
    "Invalid destination at address: 1A"
  );

  // 23
  testArray[testNum++] = testcase(
    "Move R1, 1000A\n"
    "Jump 2A\n"
    "Store R1, 0.0000\n"
    "Load R2, R1\n"
    "CmpEQ R2, 0\n"
    "Output R2\n"
    "Jump 11A\n"
    "Halt",
    "trueInvalid destination at address: 6A"
  );

  // 24
  testArray[testNum++] = testcase(
    "Move R2, 22.0009\n"
    "Output R2\n"
    "Halt",
    "22.0009"
  );

  // 25
  testArray[testNum++] = testcase(
    "Move R1, 1A\n"
    "Store R1, 1\n"
    "Input R2\n"
    "Move R1, 2A\n"
    "Store R1, R2\n"
    "Load R1, 1A\n"
    "Mul R1, 2\n"
    "Move R2, 1A\n"
    "Store R2, R1\n"
    "Load R2, 2A\n"
    "Minus R2, 1\n"
    "Move R1, 2A\n"
    "Store R1, R2\n"
    "CmpNE R2, 0\n"
    "JumpIf R2, 5A\n"
    "Load R1, 1A\n"
    "Output R1\n"
    "Halt",
    "1024"
  );

  // 26
  testArray[testNum++] = testcase(
    "Move R1, 1A\n"
    "Call R1\n"
    "Halt",
    "Stack full at address: 1A"
  );

  // 27
  testArray[testNum++] = testcase(
    "Move R3, 200\n"
    "Move R4, 1050\n"
    "Move R1, 6A\n"
    "Call R1\n"
    "Output R3\n"
    "Halt\n"
    "Add R3, R4\n"
    "Return",
    "1250"
  );

  // 28
  testArray[testNum++] = testcase(
    "Jump 3A\n"
    "Add R3, R4\n"
    "Return\n"
    "Move R3, 200\n"
    "Move R4, 1050\n"
    "Move R1, 1A\n"
    "Call R1\n"
    "Output R3\n"
    "Halt",
    "1250"
  );

  // 29
  testArray[testNum++] = testcase(
    "Call 2A\n"
    "Halt\n"
    "Move R2, 0A\n"
    "Store R2, 9\n"
    "Load R1, R2\n"
    "CmpEQ R1, 0\n"
    "JumpIf R1, 6A\n"
    "Load R1, R2\n"
    "Output R1\n"
    "Minus R1, 1\n"
    "Store R2, R1\n"
    "Add R1, 10\n"
    "Mul R1, 2\n"
    "Div R2, 5\n"
    "Output R2\n"
    "Minus R2, R1\n"
    "Output R1\n"
    "CmpGT R2, R1\n"
    "JumpIf R2, 3A\n"
    "Jump 5A\n"
    "Return",
    "9Type mismatch at address: 13A"
  );

  // 30
  testArray[testNum++] = testcase(
    "Move R3, false\n"
    "Not R3\n"
    "Move R5, 10A\n"
    "Store R5, R3\n"
    "Move R3, 2.56\n"
    "Call 7A\n"
    "Mul R3, 5\n"
    "Move R2, 7\n"
    "Minus R2, 1\n"
    "CmpLT R2, R3\n"
    "JumpIf R2, 13A\n"
    "Move R3, 3.5\n"
    "Return\n"
    "Load R2, R5\n"
    "Not R2\n"
    "JumpIf R2, 20A\n"
    "Output R2\n"
    "Output R3\n"
    "Move R3, true\n"
    "Jump 1A\n"
    "Output R2\n"
    "Output R3\n"
    "Halt",
    "false17.5true17.5"
  );

  // 31
  testArray[testNum++] = testcase(
    "Call 2A\n"
    "Call 5A\n"
    "Move R1, 0\n"
    "Output R1\n"
    "Return\n"
    "Halt",
    "0"
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
  //_CrtMemState sOld;
  //_CrtMemState sNew;
  //_CrtMemState sDiff;
  //_CrtMemCheckpoint(&sOld); //take a snapchot
  testSuite();
  //_CrtMemCheckpoint(&sNew); //take a snapchot 
  //if (_CrtMemDifference(&sDiff, &sOld, &sNew)) // if there is a difference
  //{
  //  OutputDebugString(L"-----------_CrtMemDumpStatistics ---------");
  //  _CrtMemDumpStatistics(&sDiff);
  //  OutputDebugString(L"-----------_CrtMemDumpAllObjectsSince ---------");
  //  _CrtMemDumpAllObjectsSince(&sOld);
  //  OutputDebugString(L"-----------_CrtDumpMemoryLeaks ---------");
  //  _CrtDumpMemoryLeaks();
  //}
  return 0;
}
#ifndef VM_H
#define VM_H

#include "main.h"

const double EPSILON = 1.0e-11;
class VM;
bool cmpEQFloat(const double&, const double&);
bool cmpNEFloat(const double&, const double&);
bool cmpLTFloat(const double&, const double&);
bool cmpGTFloat(const double&, const double&);
bool cmpLEFloat(const double&, const double&);
bool cmpGEFloat(const double&, const double&);

// Literal for data
class Literal {
public:
	virtual ~Literal() = default;
	virtual char getLitTyp() const;
	virtual int getAdd() const;
	virtual int getInt() const;
	virtual double getFloat() const;
	virtual bool getBool() const;
	virtual void setAdd(int);
	virtual void setInt(int);
	virtual void setFloat(double);
	virtual void setBool(bool);
};


// Address literal
class AddLit : public Literal {
	int value;
public:
	AddLit();
	AddLit(int value);
	char getLitTyp() const;
	int getAdd() const;
	void setAdd(int);
};


// Integer literal
class IntLit : public Literal {
	int value;
public:
	IntLit(int value);
	char getLitTyp() const;
	int getInt() const;
	void setInt(int);
};


// Float literal
class FloatLit : public Literal {
	double value;
public:
	FloatLit(double value);
	char getLitTyp() const;
	double getFloat() const;
	void setFloat(double);
};


// Boolean literal
class BoolLit : public Literal {
	bool value;
public:
	BoolLit(bool value);
	char getLitTyp() const;
	bool getBool() const;
	void setBool(bool);
};


// Instruction stored in Memory Bank
class BankedInstruction {
	string instruction;
	char inTyp;
public:
	string getInstruction() const;
	char getInTyp() const;
	void loadInstruction(string, char);
};


// Memory bank for code
class MemoryBank {
	BankedInstruction* inSlots;
	int size;
	const int MAX_SIZE = 65536;

public:
	MemoryBank();
	~MemoryBank();
	int getSize() const;
	void storeInstruction(string, char);
	BankedInstruction at(int) const;
};

// Static memory for data
class StaticMemory {
	string* dataSlots;
	const int MAX_SIZE = 65536;
public:
	StaticMemory();
	~StaticMemory();
	string loadAt(Literal*);
	void storeAt(Literal*, string);
};


// Stack for addresses
class AddressStack {
	AddLit* retAddresses;
	int top;
	const int MAX_SIZE = 1000;

public:
	// Methods
	// Constructors
	AddressStack();
	~AddressStack();
	bool push(AddLit);
	AddLit pop();
	AddLit topValue() const;
};


// Executable instruction
class ExeInstruction {
public:
	ExeInstruction();
	virtual ~ExeInstruction() = default;
	virtual char getInTyp() const;
	virtual string getCode() const;
	virtual int getDest() const;
	virtual string getSrc() const;
};


// Executable binary instruction
class ExeBinInstruction :public ExeInstruction {
	string code;
	int dest;
	string src;
public:
	ExeBinInstruction(string, int, string);
	char getInTyp() const;
	string getCode() const;
	int getDest() const;
	string getSrc() const;
};


// Executable dest instruction
class ExeDestInstruction :public ExeInstruction {
	string code;
	int dest;
public:
	ExeDestInstruction(string, int);
	char getInTyp() const;
	string getCode() const;
	int getDest() const;
};


// Executable src instruction
class ExeSrcInstruction :public ExeInstruction {
	string code;
	string src;
public:
	ExeSrcInstruction(string, string);
	char getInTyp() const;
	string getCode() const;
	string getSrc() const;
};


// Executable mon instruction
class ExeMonInstruction :public ExeInstruction {
	string code;
public:
	ExeMonInstruction(string);
	char getInTyp() const;
	string getCode() const;
};


// Action node for function
struct BinActionNode {
	string code;
	void (*exeFuncPtr)(VM*, int, string);
};


struct DestActionNode {
	string code;
	void (*exeFuncPtr)(VM*, int);
};


struct SrcActionNode {
	string code;
	void (*exeFuncPtr)(VM*, string);
};


struct MonActionNode {
	string code;
	void (*exeFuncPtr)(VM*);
};


// 23 methods for 23 functions
// Arithmetic
void add(VM*, int, string);
void subtract(VM*, int, string);
void mul(VM*, int, string);
void div(VM*, int, string);

// Comparison
void cmpEQ(VM*, int, string);
void cmpNE(VM*, int, string);
void cmpLT(VM*, int, string);
void cmpLE(VM*, int, string);
void cmpGT(VM*, int, string);
void cmpGE(VM*, int, string);

// Logical
void _not(VM*, int);
void _and(VM*, int, string);
void _or(VM*, int, string);

// Load and store
void move(VM*, int, string);
void load(VM*, int, string);
void store(VM*, int, string);

// Sequence control
void jump(VM*, string);
void jumpIf(VM*, int, string);
void call(VM*, string);
void _return(VM*);
void halt(VM*);

// Input and output
void input(VM*, int);
void output(VM*, string);

// Virtual machine
class VM {
public:
	// List of all language's functions
	BinActionNode BIN_LIST[16] = { {"Add", &add}, {"Minus", &subtract}, {"Mul", &mul},
		{"Div", &div}, {"CmpEQ", &cmpEQ}, {"CmpNE", &cmpNE}, {"CmpLT", &cmpLT}, {"CmpLE", &cmpLE},
		{"CmpGT", &cmpGT}, {"CmpGE", &cmpGE}, {"And", &_and}, {"Or", &_or}, {"Move", &move},
		{"Load", &load}, {"Store", &store}, {"JumpIf", &jumpIf} };

	DestActionNode DEST_LIST[2] = { {"Not", &_not}, {"Input", &input} };
	SrcActionNode SRC_LIST[3] = { {"Jump", &jump}, {"Call", &call}, {"Output", &output} };
	MonActionNode MON_LIST[2] = { {"Return", &_return}, {"Halt", &halt} };

	// Necessary resources
	Literal** R;
	AddLit* IP;
	MemoryBank memoryBank;
	StaticMemory staticMemory;
	AddressStack addressStack;

	// Methods
	VM();
	~VM();
	void run(string filename);
	void perform();
	void execute(ExeInstruction*);
	// Function to check loadtime error
	char checkLoadtime(string) const;
	ExeInstruction* compileInstruction(BankedInstruction) const;
	Literal* decodeSrc(string) const;
	string trimFloatString(string) const;
	string encodeSrc(Literal*) const;
};
#endif
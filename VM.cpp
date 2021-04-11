#include "VM.h"

bool cmpEQFloat(const double& a, const double& b) {
	if (a > b) {
		if (a - b <= EPSILON)
			return true;
	}
	else {
		if (b - a <= EPSILON)
			return true;
	}
	return false;
}

bool cmpNEFloat(const double& a, const double& b) {
	return !cmpEQFloat(a, b);
}

bool cmpLTFloat(const double& a, const double& b) {
	if (b - a > EPSILON) return true;
	return false;
}

bool cmpGTFloat(const double& a, const double& b) {
	if (a - b > EPSILON) return true;
	return false;
}

bool cmpLEFloat(const double& a, const double& b) {
	return !cmpGTFloat(a, b);
}

bool cmpGEFloat(const double& a, const double& b) {
	return !cmpLTFloat(a, b);
}

// *********************************
// **** Literal***********************
// *********************************
char Literal::getLitTyp() const {
	return '0';
}

int Literal::getAdd() const {
	return 0;
}

int Literal::getInt() const {
	return 0;
}

double Literal::getFloat() const {
	return 0.0;
}

bool Literal::getBool() const {
	return false;
}

void Literal::setAdd(int) {}

void Literal::setInt(int) {}

void Literal::setFloat(double) {}

void Literal::setBool(bool) {}


// *********************************
// **** Add Literal*******************
// *********************************
AddLit::AddLit() {
	this->value = 0;
}

AddLit::AddLit(int value) {
	this->value = value;
}

char AddLit::getLitTyp() const {
	return 'a';
}

int AddLit::getAdd() const {
	return this->value;
}

void AddLit::setAdd(int value) {
	this->value = value;
}


// *********************************
// **** Int Literal*******************
// *********************************
IntLit::IntLit(int value) {
	this->value = value;
}

char IntLit::getLitTyp() const {
	return 'i';
}

int IntLit::getInt() const {
	return this->value;
}

void IntLit::setInt(int value) {
	this->value = value;
}


// *********************************
// **** Float Literal*****************
// *********************************
FloatLit::FloatLit(double value) {
	this->value = value;
}

char FloatLit::getLitTyp() const {
	return 'f';
}

double FloatLit::getFloat() const {
	return this->value;
}

void FloatLit::setFloat(double value) {
	this->value = value;
}


// *********************************
// **** Bool Literal******************
// *********************************
BoolLit::BoolLit(bool value) {
	this->value = value;
}

char BoolLit::getLitTyp() const {
	return 'b';
}

bool BoolLit::getBool() const {
	return this->value;
}

void BoolLit::setBool(bool value) {
	this->value = value;
}


// *********************************
// **** Banked Instruction************
// *********************************
string BankedInstruction::getInstruction() const {
	return this->instruction;
}

char BankedInstruction::getInTyp() const {
	return this->inTyp;
}

void BankedInstruction::loadInstruction(string instruction, char inTyp) {
	this->instruction = instruction;
	this->inTyp = inTyp;
}


// *********************************
// **** Memory Bank*******************
// *********************************
MemoryBank::MemoryBank() {
	this->inSlots = new BankedInstruction[MAX_SIZE];
	this->size = 0;
}

MemoryBank::~MemoryBank() {
	delete[]this->inSlots;
}

int MemoryBank::getSize() const {
	return this->size;
}

void MemoryBank::storeInstruction(string instruction, char inTyp) {
	this->inSlots[this->size++].loadInstruction(instruction, inTyp);
}

BankedInstruction MemoryBank::at(int pos) const {
	return this->inSlots[pos];
}


// *********************************
// **** Static Memory*****************
// *********************************
StaticMemory::StaticMemory() {
	this->dataSlots = new string[MAX_SIZE];
}

StaticMemory::~StaticMemory() {
	delete[]this->dataSlots;
}

string StaticMemory::loadAt(Literal* address) {
	return this->dataSlots[address->getAdd()];
}

void StaticMemory::storeAt(Literal* address, string value) {
	this->dataSlots[address->getAdd()] = value;
}


// *********************************
// **** Address Stack*****************
// *********************************
AddressStack::AddressStack() {
	this->retAddresses = new AddLit[MAX_SIZE];
	this->top = 0;
}

AddressStack::~AddressStack() {
	delete[]this->retAddresses;
}

bool AddressStack::push(AddLit address) {
	if (this->top == this->MAX_SIZE) return false;
	this->retAddresses[this->top++] = address;
	return true;
}

AddLit AddressStack::pop() {
	return this->retAddresses[--this->top];
}

AddLit AddressStack::topValue() const {
	return this->retAddresses[this->top - 1];
}

// *********************************
// **** Executable Instruction *******
// *********************************
ExeInstruction::ExeInstruction() {}

char ExeInstruction::getInTyp() const {
	return '0';
}

string ExeInstruction::getCode() const {
	return "0";
}

int ExeInstruction::getDest() const {
	return 0;
}

string ExeInstruction::getSrc() const {
	return "0";
}


// *********************************
// **** Executable Binary Instruction
// *********************************
ExeBinInstruction::ExeBinInstruction(string code, int dest, string src) {
	this->code = code;
	this->dest = dest;
	this->src = src;
}

char ExeBinInstruction::getInTyp() const {
	return 'b';
}

string ExeBinInstruction::getCode() const {
	return this->code;
}

int ExeBinInstruction::getDest() const {
	return this->dest;
}

string ExeBinInstruction::getSrc() const {
	return this->src;
}


// *********************************
// **** Executable Dest Instruction
// *********************************
ExeDestInstruction::ExeDestInstruction(string code, int dest) {
	this->code = code;
	this->dest = dest;
}

char ExeDestInstruction::getInTyp() const {
	return 'd';
}

string ExeDestInstruction::getCode() const {
	return this->code;
}

int ExeDestInstruction::getDest() const {
	return this->dest;
}


// *********************************
// **** Executable Src Instruction
// *********************************
ExeSrcInstruction::ExeSrcInstruction(string code, string src) {
	this->code = code;
	this->src = src;
}

char ExeSrcInstruction::getInTyp() const {
	return 's';
}

string ExeSrcInstruction::getCode() const {
	return this->code;
}

string ExeSrcInstruction::getSrc() const {
	return this->src;
}

// *********************************
// **** Executable Mono Instruction
// *********************************
ExeMonInstruction::ExeMonInstruction(string code) {
	this->code = code;
}

char ExeMonInstruction::getInTyp() const {
	return 'm';
}

string ExeMonInstruction::getCode() const {
	return this->code;
}


// *********************************
// **** 23 functions for the language
// *********************************
// Arithmetic***********************
// Add
void add(VM* vm, int dest, string src) {
	Literal* destCompo = vm->R[dest - 1];
	Literal* srcCompo = vm->decodeSrc(src);
	char destTyp = destCompo->getLitTyp();
	char srcTyp = srcCompo->getLitTyp();
	// Check runtime
	// Check type matching
	if ((destTyp != 'i' && destTyp != 'f')
		|| (srcTyp != 'i' && srcTyp != 'f')) {
		delete srcCompo;
		throw TypeMismatch(vm->IP->getAdd() - 1);
	}
	// Execute instruction
	if (destTyp == 'i') {
		if (srcTyp == 'i')
			destCompo->setInt(destCompo->getInt() + srcCompo->getInt());
		else if (srcTyp == 'f') {
			int destValue = destCompo->getInt();
			delete destCompo;
			vm->R[dest - 1] = new FloatLit(destValue + srcCompo->getFloat());
		}
	}
	else if (destTyp == 'f') {
		if (srcTyp == 'i')
			destCompo->setFloat(destCompo->getFloat() + srcCompo->getInt());
		else if (srcTyp == 'f')
			destCompo->setFloat(destCompo->getFloat() + srcCompo->getFloat());
	}
	delete srcCompo;
}

// Minus
void subtract(VM* vm, int dest, string src) {
	Literal* destCompo = vm->R[dest - 1];
	Literal* srcCompo = vm->decodeSrc(src);
	char destTyp = destCompo->getLitTyp();
	char srcTyp = srcCompo->getLitTyp();
	// Check runtime
	// Check type matching
	if ((destTyp != 'i' && destTyp != 'f')
		|| (srcTyp != 'i' && srcTyp != 'f')) {
		delete srcCompo;
		throw TypeMismatch(vm->IP->getAdd() - 1);
	}
	// Execute instruction
	if (destTyp == 'i') {
		if (srcTyp == 'i')
			destCompo->setInt(destCompo->getInt() - srcCompo->getInt());
		else if (srcTyp == 'f') {
			int destValue = destCompo->getInt();
			delete destCompo;
			vm->R[dest - 1] = new FloatLit(destValue - srcCompo->getFloat());
		}
	}
	else if (destTyp == 'f') {
		if (srcTyp == 'i')
			destCompo->setFloat(destCompo->getFloat() - srcCompo->getInt());
		else if (srcTyp == 'f')
			destCompo->setFloat(destCompo->getFloat() - srcCompo->getFloat());
	}
	delete srcCompo;
}

// Mul
void mul(VM* vm, int dest, string src) {
	Literal* destCompo = vm->R[dest - 1];
	Literal* srcCompo = vm->decodeSrc(src);
	char destTyp = destCompo->getLitTyp();
	char srcTyp = srcCompo->getLitTyp();
	// Check runtime
	// Check type matching
	if ((destTyp != 'i' && destTyp != 'f')
		|| (srcTyp != 'i' && srcTyp != 'f')) {
		delete srcCompo;
		throw TypeMismatch(vm->IP->getAdd() - 1);
	}
	// Execute instruction
	if (destTyp == 'i') {
		if (srcTyp == 'i')
			destCompo->setInt(destCompo->getInt() * srcCompo->getInt());
		else if (srcTyp == 'f') {
			int destValue = destCompo->getInt();
			delete destCompo;
			vm->R[dest - 1] = new FloatLit(destValue * srcCompo->getFloat());
		}
	}
	else if (destTyp == 'f') {
		if (srcTyp == 'i')
			destCompo->setFloat(destCompo->getFloat() * srcCompo->getInt());
		else if (srcTyp == 'f')
			destCompo->setFloat(destCompo->getFloat() * srcCompo->getFloat());
	}
	delete srcCompo;
}

// Div
void div(VM* vm, int dest, string src) {
	Literal* destCompo = vm->R[dest - 1];
	Literal* srcCompo = vm->decodeSrc(src);
	char destTyp = destCompo->getLitTyp();
	char srcTyp = srcCompo->getLitTyp();
	// Check runtime
	// Check type matching
	if ((destTyp != 'i' && destTyp != 'f')
		|| (srcTyp != 'i' && srcTyp != 'f')) {
		delete srcCompo;
		throw TypeMismatch(vm->IP->getAdd() - 1);
	}
	// Check divide by zero
	if ((srcTyp == 'i' && srcCompo->getInt() == 0)
		|| (srcTyp == 'f' && srcCompo->getFloat() == 0.0)) {
		delete srcCompo;
		throw DivideByZero(vm->IP->getAdd() - 1);
	}
	// Execute instruction
	if (destTyp == 'i') {
		if (srcTyp == 'i')
			destCompo->setInt(destCompo->getInt() / srcCompo->getInt());
		else if (srcTyp == 'f') {
			int destValue = destCompo->getInt();
			delete destCompo;
			vm->R[dest - 1] = new FloatLit(destValue / srcCompo->getFloat());
		}
	}
	else if (destTyp == 'f') {
		if (srcTyp == 'i')
			destCompo->setFloat(destCompo->getFloat() / srcCompo->getInt());
		else if (srcTyp == 'f')
			destCompo->setFloat(destCompo->getFloat() / srcCompo->getFloat());
	}
	delete srcCompo;
}

// Comparison***********************
// CmpEQ
void cmpEQ(VM* vm, int dest, string src) {
	Literal* destCompo = vm->R[dest - 1];
	Literal* srcCompo = vm->decodeSrc(src);
	char destTyp = destCompo->getLitTyp();
	char srcTyp = srcCompo->getLitTyp();
	// Check runtime
	// Check type matching
	if (destTyp == 'a' || srcTyp == 'a'
		|| (destTyp == 'b' && srcTyp != 'b') || (srcTyp == 'b' && destTyp != 'b')) {
		delete srcCompo;
		throw TypeMismatch(vm->IP->getAdd() - 1);
	}
	// Execute instruction
	if (destTyp == 'b') {
		destCompo->setBool(destCompo->getBool() == srcCompo->getBool());
	}
	else if (destTyp == 'i') {
		int destValue = destCompo->getInt();
		delete destCompo;
		if (srcTyp == 'f')
			vm->R[dest - 1] = new BoolLit(cmpEQFloat(destValue, srcCompo->getFloat()));
		else vm->R[dest - 1] = new BoolLit(destValue == srcCompo->getInt());
	}
	else {
		double destValue = destCompo->getFloat();
		delete destCompo;
		if (srcTyp == 'f')
			vm->R[dest - 1] = new BoolLit(cmpEQFloat(destValue, srcCompo->getFloat()));
		else vm->R[dest - 1] = new BoolLit(cmpEQFloat(destValue, srcCompo->getInt()));
	}
	delete srcCompo;
}

// CmpNE
void cmpNE(VM* vm, int dest, string src) {
	Literal* destCompo = vm->R[dest - 1];
	Literal* srcCompo = vm->decodeSrc(src);
	char destTyp = destCompo->getLitTyp();
	char srcTyp = srcCompo->getLitTyp();
	// Check runtime
	// Check type matching
	if (destTyp == 'a' || srcTyp == 'a'
		|| (destTyp == 'b' && srcTyp != 'b') || (srcTyp == 'b' && destTyp != 'b')) {
		delete srcCompo;
		throw TypeMismatch(vm->IP->getAdd() - 1);
	}
	// Execute instruction
	if (destTyp == 'b') {
		destCompo->setBool(destCompo->getBool() != srcCompo->getBool());
	}
	else if (destTyp == 'i') {
		int destValue = destCompo->getInt();
		delete destCompo;
		if (srcTyp == 'f')
			vm->R[dest - 1] = new BoolLit(cmpNEFloat(destValue, srcCompo->getFloat()));
		else vm->R[dest - 1] = new BoolLit(destValue != srcCompo->getInt());
	}
	else {
		double destValue = destCompo->getFloat();
		delete destCompo;
		if (srcTyp == 'f')
			vm->R[dest - 1] = new BoolLit(cmpNEFloat(destValue, srcCompo->getFloat()));
		else vm->R[dest - 1] = new BoolLit(cmpNEFloat(destValue, srcCompo->getInt()));
	}
	delete srcCompo;
}

// CmpLT
void cmpLT(VM* vm, int dest, string src) {
	Literal* destCompo = vm->R[dest - 1];
	Literal* srcCompo = vm->decodeSrc(src);
	char destTyp = destCompo->getLitTyp();
	char srcTyp = srcCompo->getLitTyp();
	// Check runtime
	// Check type matching
	if (destTyp == 'a' || srcTyp == 'a'
		|| destTyp == 'b' || srcTyp == 'b') {
		delete srcCompo;
		throw TypeMismatch(vm->IP->getAdd() - 1);
	}
	// Execute instruction
	if (destTyp == 'i') {
		int destValue = destCompo->getInt();
		delete destCompo;
		if (srcTyp == 'f')
			vm->R[dest - 1] = new BoolLit(cmpLTFloat(destValue, srcCompo->getFloat()));
		else vm->R[dest - 1] = new BoolLit(destValue < srcCompo->getInt());
	}
	else {
		double destValue = destCompo->getFloat();
		delete destCompo;
		if (srcTyp == 'f')
			vm->R[dest - 1] = new BoolLit(cmpLTFloat(destValue, srcCompo->getFloat()));
		else vm->R[dest - 1] = new BoolLit(cmpLTFloat(destValue, srcCompo->getInt()));
	}
	delete srcCompo;
}

// CmpLE
void cmpLE(VM* vm, int dest, string src) {
	Literal* destCompo = vm->R[dest - 1];
	Literal* srcCompo = vm->decodeSrc(src);
	char destTyp = destCompo->getLitTyp();
	char srcTyp = srcCompo->getLitTyp();
	// Check runtime
	// Check type matching
	if (destTyp == 'a' || srcTyp == 'a'
		|| destTyp == 'b' || srcTyp == 'b') {
		delete srcCompo;
		throw TypeMismatch(vm->IP->getAdd() - 1);
	}
	// Execute instruction
	if (destTyp == 'i') {
		int destValue = destCompo->getInt();
		delete destCompo;
		if (srcTyp == 'f')
			vm->R[dest - 1] = new BoolLit(cmpLEFloat(destValue, srcCompo->getFloat()));
		else vm->R[dest - 1] = new BoolLit(destValue <= srcCompo->getInt());
	}
	else {
		double destValue = destCompo->getFloat();
		delete destCompo;
		if (srcTyp == 'f')
			vm->R[dest - 1] = new BoolLit(cmpLEFloat(destValue, srcCompo->getFloat()));
		else vm->R[dest - 1] = new BoolLit(cmpLEFloat(destValue, srcCompo->getInt()));
	}
	delete srcCompo;
}

// CmpGT
void cmpGT(VM* vm, int dest, string src) {
	Literal* destCompo = vm->R[dest - 1];
	Literal* srcCompo = vm->decodeSrc(src);
	char destTyp = destCompo->getLitTyp();
	char srcTyp = srcCompo->getLitTyp();
	// Check runtime
	// Check type matching
	if (destTyp == 'a' || srcTyp == 'a'
		|| destTyp == 'b' || srcTyp == 'b') {
		delete srcCompo;
		throw TypeMismatch(vm->IP->getAdd() - 1);
	}
	// Execute instruction
	if (destTyp == 'i') {
		int destValue = destCompo->getInt();
		delete destCompo;
		if (srcTyp == 'f')
			vm->R[dest - 1] = new BoolLit(cmpGTFloat(destValue, srcCompo->getFloat()));
		else vm->R[dest - 1] = new BoolLit(destValue > srcCompo->getInt());
	}
	else {
		double destValue = destCompo->getFloat();
		delete destCompo;
		if (srcTyp == 'f')
			vm->R[dest - 1] = new BoolLit(cmpGTFloat(destValue, srcCompo->getFloat()));
		else vm->R[dest - 1] = new BoolLit(cmpGTFloat(destValue, srcCompo->getInt()));
	}
	delete srcCompo;
}

// CmpGE
void cmpGE(VM* vm, int dest, string src) {
	Literal* destCompo = vm->R[dest - 1];
	Literal* srcCompo = vm->decodeSrc(src);
	char destTyp = destCompo->getLitTyp();
	char srcTyp = srcCompo->getLitTyp();
	// Check runtime
	// Check type matching
	if (destTyp == 'a' || srcTyp == 'a'
		|| destTyp == 'b' || srcTyp == 'b') {
		delete srcCompo;
		throw TypeMismatch(vm->IP->getAdd() - 1);
	}
	// Execute instruction
	if (destTyp == 'i') {
		int destValue = destCompo->getInt();
		delete destCompo;
		if (srcTyp == 'f')
			vm->R[dest - 1] = new BoolLit(cmpGEFloat(destValue, srcCompo->getFloat()));
		else vm->R[dest - 1] = new BoolLit(destValue >= srcCompo->getInt());
	}
	else {
		double destValue = destCompo->getFloat();
		delete destCompo;
		if (srcTyp == 'f')
			vm->R[dest - 1] = new BoolLit(cmpGEFloat(destValue, srcCompo->getFloat()));
		else vm->R[dest - 1] = new BoolLit(cmpGEFloat(destValue, srcCompo->getInt()));
	}
	delete srcCompo;
}

// Logical**************************

// Not
void _not(VM* vm, int dest) {
	// Check runtime
	// Check type matching
	if (vm->R[dest - 1]->getLitTyp() != 'b') throw TypeMismatch(vm->IP->getAdd() - 1);
	vm->R[dest - 1]->setBool(!vm->R[dest - 1]->getBool());
}

// And
void _and(VM* vm, int dest, string src) {
	Literal* destCompo = vm->R[dest - 1];
	Literal* srcCompo = vm->decodeSrc(src);
	char destTyp = destCompo->getLitTyp();
	char srcTyp = srcCompo->getLitTyp();
	// Check runtime
	// Check type matching
	if (destTyp != 'b' || srcTyp != 'b') {
		delete srcCompo;
		throw TypeMismatch(vm->IP->getAdd() - 1);
	}
	destCompo->setBool(destCompo->getBool() && srcCompo->getBool());
	delete srcCompo;
}

// Or
void _or(VM* vm, int dest, string src) {
	Literal* destCompo = vm->R[dest - 1];
	Literal* srcCompo = vm->decodeSrc(src);
	char destTyp = destCompo->getLitTyp();
	char srcTyp = srcCompo->getLitTyp();
	// Check runtime
	// Check type matching
	if (destTyp != 'b' || srcTyp != 'b') {
		delete srcCompo;
		throw TypeMismatch(vm->IP->getAdd() - 1);
	}
	destCompo->setBool(destCompo->getBool() || srcCompo->getBool());
	delete srcCompo;
}

// Load and store*******************
// Move
void move(VM* vm, int dest, string src) {
	Literal* srcCompo = vm->decodeSrc(src);
	// Execute instruction
	delete vm->R[dest - 1];
	vm->R[dest - 1] = srcCompo;
}

// Load
void load(VM* vm, int dest, string src) {
	Literal* srcCompo = vm->decodeSrc(src);
	char srcTyp = srcCompo->getLitTyp();
	// Execute instruction
	if (srcTyp != 'a') {
		delete srcCompo;
		throw TypeMismatch(vm->IP->getAdd() - 1);
	}
	delete vm->R[dest - 1];
	vm->R[dest - 1] = vm->decodeSrc(vm->staticMemory.loadAt(srcCompo));
	delete srcCompo;
}

// Store
void store(VM* vm, int dest, string src) {
	Literal* destCompo = vm->R[dest - 1];
	Literal* srcCompo = vm->decodeSrc(src);
	char destTyp = destCompo->getLitTyp();
	// Execute instruction
	if (destTyp != 'a') {
		delete srcCompo;
		throw TypeMismatch(vm->IP->getAdd() - 1);
	}
	vm->staticMemory.storeAt(destCompo, vm->encodeSrc(srcCompo));
	delete srcCompo;
}

// Sequence control*****************
// Jump
void jump(VM* vm, string src) {
	Literal* srcCompo = vm->decodeSrc(src);
	if (srcCompo->getLitTyp() != 'a') {
		delete srcCompo;
		throw TypeMismatch(vm->IP->getAdd() - 1);
	}
	if (srcCompo->getAdd() >= vm->memoryBank.getSize()) {
		delete srcCompo;
		throw InvalidDestination(vm->IP->getAdd() - 1);
	}
	vm->IP->setAdd(srcCompo->getAdd());
	delete srcCompo;
}

// JumpIf
void jumpIf(VM* vm, int dest, string src) {
	Literal* destCompo = vm->R[dest - 1];
	Literal* srcCompo = vm->decodeSrc(src);
	if (destCompo->getLitTyp() != 'b') {
		delete srcCompo;
		throw TypeMismatch(vm->IP->getAdd() - 1);
	}
	if (destCompo->getBool()) {
		if (srcCompo->getLitTyp() != 'a') {
			delete srcCompo;
			throw TypeMismatch(vm->IP->getAdd() - 1);
		}
		if (srcCompo->getAdd() >= vm->memoryBank.getSize()) {
			delete srcCompo;
			throw InvalidDestination(vm->IP->getAdd() - 1);
		}
		vm->IP->setAdd(srcCompo->getAdd());
	}
	delete srcCompo;
}

// Call
void call(VM* vm, string src) {
	Literal* srcCompo = vm->decodeSrc(src);
	if (srcCompo->getLitTyp() != 'a') {
		delete srcCompo;
		throw TypeMismatch(vm->IP->getAdd() - 1);
	}
	if (srcCompo->getAdd() >= vm->memoryBank.getSize()) {
		delete srcCompo;
		throw InvalidDestination(vm->IP->getAdd() - 1);
	}
	// Put IP address on stack
	if (!vm->addressStack.push(*(vm->IP))) {
		delete srcCompo;
		throw StackFull(vm->IP->getAdd() - 1);
	}
	// IP = src
	vm->IP->setAdd(srcCompo->getAdd());
	delete srcCompo;
}

// Return
void _return(VM* vm) {
	vm->IP->setAdd(vm->addressStack.pop().getAdd());
}

// Halt
void halt(VM* vm) {
	return;
}

// Input and output*****************
void input(VM* vm, int dest) {
	string inputString;
	cin >> inputString;
	regex inputReg("([1-9]\\d*|0)|\\d+\\.\\d+|true|false");
	if (!regex_match(inputString, inputReg)) throw InvalidInput(vm->IP->getAdd() - 1);
	delete vm->R[dest - 1];
	vm->R[dest - 1] = vm->decodeSrc(inputString);
}

void output(VM* vm, string src) {
	Literal* srcCompo = vm->decodeSrc(src);
	cout << vm->encodeSrc(srcCompo);
	delete srcCompo;
}

// *********************************
// **** VM Machine********************
// *********************************
VM::VM() {
	this->IP = new AddLit(0);
	this->R = new Literal * [15];
	for (int i = 0; i < 15; i++) {
		this->R[i] = new Literal();
	}
}

VM::~VM() {
	delete this->IP;
	for (int i = 0; i < 15; i++) {
		delete this->R[i];
	}
	delete[]this->R;
}

void VM::run(string filename)
{
	string instruction = "";
	ifstream myfile(filename);
	// Read all instructions from text file
	while (getline(myfile, instruction)) {
		char inTyp = this->checkLoadtime(instruction);
		this->memoryBank.storeInstruction(instruction, inTyp);
	}
	// CPU runs all instructions
	this->perform();
}

void VM::perform() {
	BankedInstruction bInstruction;
	int insAddress = 0;
	while (this->memoryBank.at(insAddress).getInstruction() != "Halt") {
		// Read instruction at address IP
		// and increase IP by 1
		insAddress = this->IP->getAdd();
		bInstruction = this->memoryBank.at(insAddress);
		this->IP->setAdd(insAddress + 1);
		// Execute the instruction read
		// First extract necessary tokens of the instruction
		ExeInstruction* eInstruction = this->compileInstruction(bInstruction);
		this->execute(eInstruction);
	}
}

void VM::execute(ExeInstruction* eInstruction) {
	if (eInstruction->getInTyp() == 'b') {
		for (BinActionNode x : this->BIN_LIST) {
			if (eInstruction->getCode() == x.code) {
				int dest = eInstruction->getDest();
				string src = eInstruction->getSrc();
				delete eInstruction;
				x.exeFuncPtr(this, dest, src);
				return;
			}
		}
	}
	else if (eInstruction->getInTyp() == 'd') {
		for (DestActionNode x : this->DEST_LIST) {
			if (eInstruction->getCode() == x.code) {
				int dest = eInstruction->getDest();
				delete eInstruction;
				x.exeFuncPtr(this, dest);
				return;
			}
		}
	}
	else if (eInstruction->getInTyp() == 's') {
		for (SrcActionNode x : this->SRC_LIST) {
			if (eInstruction->getCode() == x.code) {
				string src = eInstruction->getSrc();
				delete eInstruction;
				x.exeFuncPtr(this, src);
				return;
			}
		}
	}
	else {
		for (MonActionNode x : this->MON_LIST) {
			if (eInstruction->getCode() == x.code) {
				delete eInstruction;
				x.exeFuncPtr(this);
				return;
			}
		}
	}
}

char VM::checkLoadtime(string instruction) const {
	string code = "";
	int address = this->memoryBank.getSize();
	int size = instruction.size();
	// First we extract the code
	for (int i = 0; instruction[i] != ' ' && i < size; i++) {
		code += instruction[i];
	}
	// Check loadtime
	// Regular expression for tokens
	string destReg = "R(1[0-5]|[1-9])";
	string srcReg = "(R(1[0-5]|[1-9])|([1-9]\\d*|0)A|([1-9]\\d*|0)|\\d+\\.\\d+|true|false)";
	// For a binary instruction
	for (BinActionNode x : this->BIN_LIST) {
		if (code == x.code) {
			regex inReg(code + "\\s[^\\s,]+,\\s[^\\s]+");
			if (!regex_match(instruction, inReg))
				throw InvalidInstruction(address);
			regex operandReg("[a-zA-Z]+\\s" + destReg + ",\\s" + srcReg);
			if (!regex_match(instruction, operandReg))
				throw InvalidOperand(address);
			return 'b';
		}
	}
	// For a unary instruction within dest
	for (DestActionNode x : this->DEST_LIST) {
		if (code == x.code) {
			regex inReg(code + "\\s" + destReg);
			if (!regex_match(instruction, inReg))
				throw InvalidInstruction(address);
			return 'd';
		}
	}
	// For a unary instruction within src
	for (SrcActionNode x : this->SRC_LIST) {
		if (code == x.code) {
			regex inReg(code + "\\s" + srcReg);
			if (!regex_match(instruction, inReg))
				throw InvalidInstruction(address);
			return 's';
		}
	}
	// For a mono instruction
	for (MonActionNode x : this->MON_LIST) {
		if (code == x.code)
			return 'm';
	}
	throw InvalidInstruction(address);
}

ExeInstruction* VM::compileInstruction(BankedInstruction bInstruction) const {
	string code = "";
	int dest = 0;
	string src = "";
	int tokenCount = 0;
	string token = "";
	string instruction = bInstruction.getInstruction();
	char inTyp = bInstruction.getInTyp();
	int size = instruction.size();
	// Depend on each type, parse string different ways
	// If binary
	if (inTyp == 'b') {
		for (int i = 0; i < size; i++) {
			if (instruction[i] == ' ') {
				switch (tokenCount) {
				case 0:
					code = token;
					token = "";
					tokenCount++;
					break;
				case 1:
					token.erase(0, 1);
					token.erase(token.size() - 1, 1);
					dest = stoi(token);
					token = "";
					tokenCount++;
					break;
				}
			}
			else {
				token += instruction[i];

				if (i == size - 1) {
					src = token;
					return new ExeBinInstruction(code, dest, src);
				}
			}
		}
	}
	// If dest unary or src unary
	else if (inTyp == 'd' || inTyp == 's') {
		for (int i = 0; i < size; i++) {
			if (instruction[i] == ' ') {
				code = token;
				token = "";
			}
			else {
				token += instruction[i];
				if (i == size - 1) {
					if (inTyp == 'd') {
						token.erase(0, 1);
						dest = stoi(token);
						return new ExeDestInstruction(code, dest);
					}
					else {
						src = token;
						return new ExeSrcInstruction(code, src);
					}
				}
			}
		}
	}
	// If mono
	else code = instruction;
	return new ExeMonInstruction(code);
}

Literal* VM::decodeSrc(string src) const {
	regex regReg("R(1[0-5]|[1-9])");
	regex addReg("[1-9]\\d*A|0A");
	regex intReg("[1-9]\\d*|0");
	regex floatReg("\\d+\\.\\d+");
	regex boolReg("true|false");
	string token = src;
	if (regex_match(src, regReg)) {
		token.erase(0, 1);
		char srcTyp = this->R[stoi(token) - 1]->getLitTyp();
		switch (srcTyp) {
		case 'a':
			return new AddLit(this->R[stoi(token) - 1]->getAdd());
		case 'i':
			return new IntLit(this->R[stoi(token) - 1]->getInt());
		case 'f':
			return new FloatLit(this->R[stoi(token) - 1]->getFloat());
		default:
			return new BoolLit(this->R[stoi(token) - 1]->getBool());
		}
	}
	else if (regex_match(src, addReg)) {
		token.erase(token.size() - 1, 1);
		return new AddLit(stoi(token));
	}
	else if (regex_match(src, intReg)) {
		return new IntLit(stoi(token));
	}
	else if (regex_match(src, floatReg)) {
		return new FloatLit(stod(token));
	}
	else {
		return token == "true" ? new BoolLit(true) : new BoolLit(false);
	}
}

string VM::trimFloatString(string str) const {
	for (int i = str.length() - 1; str[i] == '0'; i--) {
		str = str.erase(i, 1);
	}
	return str[str.length() - 1] == '.' ? str + '0' : str;
}

string VM::encodeSrc(Literal* src) const {
	char srcTyp = src->getLitTyp();
	switch (srcTyp) {
	case 'a':
		return to_string(src->getAdd()) + 'A';
	case 'i':
		return to_string(src->getInt());
	case 'f':
		return this->trimFloatString(to_string(src->getFloat()));
	default:
		return src->getBool() ? "true" : "false";
	}
}
#ifndef DSA_EXCEPTION_H
#define DSA_EXCEPTION_H
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
class InvalidInstruction : public exception
{
  string mess;

public:
  InvalidInstruction(int address)
  {
    mess = "Invalid instruction at address: " + to_string(address) + "A";
  }
  const char *what() const throw()
  {
    return mess.c_str();
  }
};
class TypeMismatch : public exception
{
  string mess;

public:
  TypeMismatch(int address)
  {
    mess = "Type mismatch at address: " + to_string(address) + "A";
  }
  const char *what() const throw()
  {
    return mess.c_str();
  }
};
class InvalidOperand : public exception
{
  string mess;

public:
  InvalidOperand(int address)
  {
    mess = "Invalid operand at address: " + to_string(address) + "A";
  }
  const char *what() const throw()
  {
    return mess.c_str();
  }
};
class InvalidInput : public exception
{
  string mess;

public:
  InvalidInput(int address)
  {
    mess = "Invalid input at address: " + to_string(address) + "A";
  }
  const char *what() const throw()
  {
    return mess.c_str();
  }
};
class InvalidDestination : public exception
{
  string mess;

public:
  InvalidDestination(int address)
  {
    mess = "Invalid destination at address: " + to_string(address) + "A";
  }
  const char *what() const throw()
  {
    return mess.c_str();
  }
};
class DivideByZero : public exception
{
  string mess;

public:
  DivideByZero(int address)
  {
    mess = "Divide by zero at address: " + to_string(address) + "A";
  }
  const char *what() const throw()
  {
    return mess.c_str();
  }
};
class StackFull : public exception
{
  string mess;

public:
  StackFull(int address)
  {
    mess = "Stack full at address: " + to_string(address) + "A";
  }
  const char *what() const throw()
  {
    return mess.c_str();
  }
};
#endif
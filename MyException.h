/*
 * MyException.h
 *
 *  Created on: Nov 26, 2015
 *      Author: spatel78745
 */

#ifndef MYEXCEPTION_H_
#define MYEXCEPTION_H_

#include <exception>
using namespace std;

class MyException : public std::logic_error
{
public:
    MyException(const char * what_arg) : logic_error(what_arg) {}
};

#endif /* MYEXCEPTION_H_ */

/*
 * Bst_test.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: spatel78745
 */

#include <string>
#include "Bst.h"

using std::string;

void testTree()
{
	Bst<string, int> bst;

	bst.put("H", 1);
	bst.put("C", 2);
	bst.put("S", 3);
	bst.put("A", 4);
	bst.put("E", 5);
	bst.put("R", 6);
	bst.put("X", 7);
	bst.put("Z", 8);
	bst.put("T", 9);

	bst.print();
}


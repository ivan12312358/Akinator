#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

const int SIZE = 128;

struct Node;

class Tree
{
	Node* head_ = nullptr;

	public:
		Tree (const char* filename);
	   ~Tree ();
		void Akinator ();
		void Find	  ();
		void Compare  ();
		void Save     ();
		void Graph	  (char* filename);
		void Search	  (Stack* stk);
		Tree(const Tree& tree) = delete;
		Tree& operator= (Tree& tree);
};

void Menu  (char* filename);
void Split (char** str, char* symbols);
int  Read  (char** symbols, const char* filename);
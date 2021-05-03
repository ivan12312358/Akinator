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
		Tree ();
		Tree (char* filename);
	   ~Tree ();
		void Akinator ();
		void Find	  ();
		void Compare  ();
		void Save     ();
		void Save     (const char* filename);
		void Graph	  (char* filename);
		void Search	  (Stack* stk);
		Tree(const Tree& tree) = delete;
		Tree& operator= (Tree& tree) = delete;
};

void menu();
void split(char** str, char* symbols);
int  read(char** symbols, const char* filename);
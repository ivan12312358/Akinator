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
		int  Search	  (char**& str);
		Tree(const Tree& tree) = delete;
		Tree& operator= (Tree& tree) = delete;
};

void split(char** str, char* symbols);
int  read(char** symbols, char* filename);
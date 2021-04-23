#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#define SIZE 128

struct Tree;
struct Node;
void free_(Node* node_);
void print_(Node* node_);
//void add_node(Tree** tree_);
//void find_(Tree** tree_);
//void find(Tree** tree_, char* str);
void node_delete(Node* node_);
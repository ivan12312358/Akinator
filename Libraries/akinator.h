#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct Tree;
void tree_walk(Tree* tree_, void (*func)(Tree*));
void free_(Tree* tree_);
void print_(Tree* tree_);
void add_node(Tree** tree_);
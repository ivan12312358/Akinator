#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct Tree;
void add_node(char* str, Tree*& tree_);
void tree_walk(Tree* tree_, void (*func)(Tree*));
void free_(Tree* tree_);
void print_(Tree* tree_);

struct Tree{
	char* node_  = nullptr;
	Tree* left_  = nullptr;
	Tree* right_ = nullptr;
};

int main(){

	Tree* tree_ = (Tree*)calloc(1, sizeof(Tree));

	char str[128];

 	add_node(str, tree_);
	
	tree_walk(tree_, print_);

	tree_walk(tree_, free_);

	return 0;
}

void print_(Tree* tree_){
	printf("%s\n", tree_->node_);
}

void free_(Tree* tree_){
	free(tree_->node_);
	free(tree_);
}

void tree_walk(Tree* tree_, void (*func)(Tree*)){
	if(tree_ == nullptr){
		return;
	} else if(tree_->left_ != nullptr){

		tree_walk(tree_->left_, func);
		
		if(tree_->right_ != nullptr){
			tree_walk(tree_->right_, func);
		}
		func(tree_);
	} else if(tree_->right_ != nullptr){

		tree_walk(tree_->right_, func);
		
		if(tree_->left_ != nullptr){
			tree_walk(tree_->left_, func);
		} 
		func(tree_);
	} else {
		func(tree_);
	}
}

void add_node(Tree*& tree_){

	

}

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct Tree{

	int elem_    = 0;
	Tree* left_  = nullptr;
	Tree* right_ = nullptr;

	

} tree;

void add_note(const int& elem, tree*& tree_);
void tree_walk(tree* tree_);

int main(){

	tree* tree_ = nullptr;

	int elem = 0;

	while(true){
		if(scanf("%d", &elem) != EOF){
			add_note(elem, tree_);
		} else {
			break;
		}
	}

	tree_walk(tree_);

	return 0;
}

void add_note(const int& elem, tree*& tree_){
	if(tree_ == nullptr){
		tree_ = (tree*)calloc(1, sizeof(tree));
		tree_->elem_ = elem;
		return;
	} else if(tree_->elem_ < elem){
		add_note(elem, tree_->right_);
	} else if(tree_->elem_ >= elem){
		add_note(elem, tree_->left_);
	}
	return;
}

void tree_walk(tree* tree_){
	if(tree_ == nullptr){
		return;
	} else if(tree_->left_ != nullptr){

		tree_walk(tree_->left_);
		
		if(tree_->right_ != nullptr){
			tree_walk(tree_->right_);
		}

		printf("%d\n", tree_->elem_);
		free(tree_);
	
	} else if(tree_->right_ != nullptr){

		tree_walk(tree_->right_);
		
		if(tree_->left_ != nullptr){
			tree_walk(tree_->left_);
		}

		printf("%d\n", tree_->elem_);
		free(tree_);
	
	} else {

		printf("%d\n", tree_->elem_);
		free(tree_);	
	}
}

void func(tree* tree_){

	assert(tree_);

	char str[128] = {};

	tree* curr_node = tree_;

	while(true){

		if(curr_node != nullptr){
			printf("%s?\n", curr_node->elem_);
			scanf("%s", str);
			if(!strcmp(str, "Yes")){
				curr_node = curr_node->right_;
				for(int i = 0; i < 3; i++){
					str[i] = 0;
				}
			} else if(!strcmp(str, "No")){
				curr_node = curr_node->left_;
				for(int i = 0; i < 2; i++){
					str[i] = 0;
				}
			} else {
				printf("Couldn't understand, please type Yes or No\n");
				scanf("%s", str);
				for(int i = 0; i < 128; i++){
					str[i] = 0;
				}
			}
		} else {
			printf("%s?\n", curr_node->elem_);
			scanf("%s", str);
			if(!strcmp(str, "Yes")){
				printf("Wohooo");
				for(int i = 0; i < 3; i++){
					str[i] = 0;
				}

			} else if(!strcmp(str, "No")){
				printf("Fuck");
				for(int i = 0; i < 3; i++){
					str[i] = 0;
				}
			} else {
				printf("Couldn't understand, please type Yes or No\n");
				scanf("%s", str);
				for(int i = 0; i < 128; i++){
					str[i] = 0;
				}
			}
		}
	} 
}
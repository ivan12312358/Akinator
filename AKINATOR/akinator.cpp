#include "../Libraries/akinator.h"

struct Tree{
	char* node_  = nullptr;
	Tree* left_  = nullptr;
	Tree* right_ = nullptr;
};

int main() {

	Tree* tree_ = nullptr;

 	add_node(&tree_);
	
	tree_walk(tree_, print_);

	tree_walk(tree_, free_);

	return 0;
}

void print_(Tree* tree_) {
	printf("%s\n", tree_->node_);
}

void free_(Tree* tree_) {
	free(tree_->node_);
	free(tree_);
}

void tree_walk(Tree* tree_, void (*func)(Tree*)) {
	if(tree_ == nullptr) {
		return;
	} else if(tree_->left_ != nullptr) {

		tree_walk(tree_->left_, func);
		
		if(tree_->right_ != nullptr) {
			tree_walk(tree_->right_, func);
		}
		func(tree_);
	} else if(tree_->right_ != nullptr) {

		tree_walk(tree_->right_, func);
		
		if(tree_->left_ != nullptr) {
			tree_walk(tree_->left_, func);
		} 
		func(tree_);
	} else {
		func(tree_);
	}
}

void add_node(Tree** tree_) {

	char str[128] = {};

	if(*tree_ == nullptr){
		*tree_ = (Tree*)calloc(1, sizeof(Tree));
		scanf("%s", str);
		(*tree_)->node_ = (char*)calloc(strlen(str), sizeof(char));
		sscanf(str, "%s", (*tree_)->node_);
		printf("%p\n", tree_);
	}

	Tree** cur_tree = tree_;

	while(true) {

		printf ("%s?\n", (*cur_tree)->node_);
		scanf  ("%s", str);
		
		if(!strcmp (str, "No")) {
			
			if((*cur_tree)->left_ == nullptr) {
				
				(*cur_tree)->left_  		= (Tree*) calloc(1, sizeof(Tree));
				(*cur_tree)->left_->node_   = (char*) calloc(strlen((*cur_tree)->node_), sizeof(char));

				printf ("What is your word?\n");
				scanf ("%s", str);

				(*cur_tree)->right_ 		= (Tree*) calloc(1, sizeof(Tree));
				(*cur_tree)->right_->node_  = (char*) calloc(strlen(str), sizeof(char));
				
				sscanf ((*cur_tree)->node_, "%s", (*cur_tree)->left_->node_);
				sscanf (str, "%s", (*cur_tree)->right_->node_);
				
				printf ("How does a {%s} differ from a {%s}?\n", (*cur_tree)->right_->node_, (*cur_tree)->left_->node_);
				scanf  ("%s", str);

				free((*cur_tree)->node_);

				(*cur_tree)->node_ = (char*) calloc(strlen(str), sizeof(char));
				sscanf(str, "%s", (*cur_tree)->node_);

				cur_tree = tree_;

			} else {
				cur_tree = &((*cur_tree)->left_);
			}

		} else if(!strcmp (str, "Yes")) {
			
			if((*cur_tree)->right_ == nullptr){
				printf ("Wohoo!!! We found it\n");
				cur_tree = tree_;
			} else {
				cur_tree = &((*cur_tree)->right_);
			}
		} else if(!strcmp (str, "Quit")) {
			break;
		} else {
			printf ("WRONG COMMAND. Type 'Yes' or 'No'\n");
		}
	}
}

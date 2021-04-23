#include "../Libraries/akinator.h"
#include "../Libraries/stack.h"


int SLSH_CNT = 0;

struct Node
{
	char* data_  = nullptr;
	Node* prev_  = nullptr;
	Node* left_  = nullptr;
	Node* right_ = nullptr;

	public:
		void add_node (char* str);
		void Walk	  (void (*func)(Node*));
		void fprint_  (FILE* f_dump);
		void fprint   ();
		void find	  ();
		void find_	  (char* str, Stack* stk, int* mode);
		void Akinator ();
};

struct Tree
{
	Node* head_ = nullptr;

	public:
	Tree ();
	Tree (char* filename);
   ~Tree ();
};

int main ()
{
	Tree tree;

	tree.head_->Akinator ();

	tree.head_->fprint ();

//	tree.head_->Walk (print_);

	tree.head_->find ();
}

Tree::Tree ()
{
	head_ = (Node*) calloc (1, sizeof (Node));

	printf ("Please, enter first object\n");

	char str[SIZE];
	fgets (str, SIZE, stdin);
	
	head_->data_ = (char*) calloc (strlen (str) + 1, sizeof (char));
	
	sprintf (head_->data_, "%s", str);
	
	head_->data_[strlen (str) - 1] = '\0';
}

Tree::Tree (char* filename)
{

}

Tree::~Tree ()
{
	assert (head_);

	head_->Walk (free_);
	head_ = nullptr;
}

void node_delete (Node* data_)
{
	Node* left  = data_->left_;
    Node* right = data_->right_;

    free (data_->data_);
    data_->data_  = nullptr;
    data_->prev_  = nullptr;
    data_->left_  = nullptr;
    data_->right_ = nullptr;
    free (data_);

    if (left != nullptr)
        node_delete (left);

    if (right != nullptr)
        node_delete (right);

    return;
}

void Node::Akinator () 
{
	char str[128] = {};

	Node* cur_tree = this;

	while(true)
	{
		printf ("%s?\n", cur_tree->data_);
		fgets  (str, SIZE, stdin);

		if (!strcmp (str, "No\n"))
		{
			if(cur_tree->left_ == nullptr)
			{
				cur_tree->add_node (str);		

				cur_tree = this;
			}
			else
				cur_tree = cur_tree->left_;
		} 
		else if(!strcmp (str, "Yes\n"))
		{	
			if(cur_tree->right_ == nullptr)
			{
				printf ("Wohoo!!! We found it\n");
				cur_tree = this;
			} 
			else 
				cur_tree = (cur_tree->right_);
		}
		else if(!strcmp (str, "Quit\n"))
			break;
		else
			printf ("WRONG COMMAND. Type 'Yes' or 'No'\n");
	}
}

void Node::add_node (char* str)
{
	left_ 		  = (Node*) calloc(1, sizeof (Node));
	left_->data_  = (char*) calloc(strlen (data_) + 1, sizeof (char));

	sprintf (left_->data_, "%s", data_);
	free	(data_);

	printf ("What is your word?\n");
	fgets  (str, SIZE, stdin);

	right_ 		  = (Node*) calloc(1, sizeof (Node));
	right_->data_ = (char*) calloc(strlen (str) + 1, sizeof (char));

	sprintf (right_->data_, "%s", str);
	right_->data_[strlen (str) - 1] = '\0';

	printf ("How does a {%s} differ from a {%s}?\n", right_->data_, left_->data_);
	fgets  (str, SIZE, stdin);

	data_ = (char*) calloc(strlen (str) + 1, sizeof (char));
	sprintf (data_, "%s", str);

	data_[strlen (str) - 1] = '\0';
}

void Node::Walk (void (*func) (Node*))
{
	if(left_ != nullptr)
	{
		left_->Walk (func);
		
		if(right_ != nullptr)
			right_->Walk (func);

		func (this);
	}
	else 
		func (this);
}

void print_ (Node* node_)
{
	printf ("%s\n", node_->data_);
}

void free_  (Node* node_)
{
	if(node_->data_ != nullptr)
		free (node_->data_);
	if(node_ != nullptr)
		free (node_);
}

void Node::fprint ()
{	
	FILE* f_dump = fopen ("dump.log", "w");
	assert (f_dump);

	this->fprint_(f_dump);

	fclose (f_dump);	
}

void Node::fprint_ (FILE* f_dump)
{
	assert(f_dump);
	assert(this->data_);

	fprintf(f_dump, "%*s%s\n", SLSH_CNT*4, "", this->data_);

	if(left_ == nullptr && right_ == nullptr)
	{
		fprintf(f_dump, "%*s{\n", SLSH_CNT*4, "");
		fprintf(f_dump, "%*s}\n", SLSH_CNT*4, "");
	}

	if(left_ != nullptr)
	{
		fprintf(f_dump, "%*s{\n", SLSH_CNT*4, "");
		SLSH_CNT++;
		left_->fprint_(f_dump);

		if(right_ != nullptr)
			right_->fprint_(f_dump);

		SLSH_CNT--;
		fprintf(f_dump, "%*s}\n", SLSH_CNT*4, "");
	}
}
 
void Node::find ()
{
	printf("Enter object that you want to find\n");

	char str[SIZE] = {};
	
	fgets(str, SIZE, stdin);
	str[strlen(str) - 1] = '\0';

	Stack stk;

	int mode = 0;

	this->find_ (str, &stk, &mode);

	if(mode == 0)
		printf("There is no \"%s\"\n", str);
	else
	{
		Node* curr = this;

		printf ("{%s}\t", curr->data_);

		for(int start = 0, end = stk.get_size (); start < end; start++)
		{
			if(stk[start] == 1)
				curr = curr->right_;
			else if(stk[start] == -1)
				curr = curr->left_;

			printf ("{%s}\t", curr->data_);
		}

		printf ("\n");
	}
}

void Node::find_ (char* str, Stack* stk, int* mode)
{
	if(!strcmp (str, data_))
		*mode = 1;
	else if(left_ != nullptr && *mode == 0)
	{
		stk->push (-1);
		left_->find_ (str, stk, mode);

		if(right_ != nullptr && *mode == 0)
		{
			stk->push (1);
			right_->find_ (str, stk, mode);
		}

		if(*mode == 0 && stk->get_size () > 0)
			stk->pop ();
	}
	else if(right_ == nullptr && left_ == nullptr && *mode == 0)
		stk->pop ();
}
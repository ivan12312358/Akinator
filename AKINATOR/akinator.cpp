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
		void Akinator ();
		void compare  ();
		void search_  (char* str, Stack* stk, int* mode);
		int  search	  (char**& str);
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

	tree.head_->Walk (print_);

	tree.head_->find ();

	tree.head_->compare ();
}

Tree::Tree ()
{
	head_ = (Node*) calloc (1, sizeof (Node));

	system("echo \"Please, enter first object\" | festival --tts");
	printf ("Please, enter first object:\n");

	char str[SIZE];
	fgets (str, SIZE, stdin);
	
	head_->data_ = (char*) calloc (strlen (str) + 1, sizeof (char));
	
	sprintf (head_->data_, "%s", str);
	
	head_->data_[strlen (str) - 1] = '\0';
}

Tree::Tree (char* filename)
{
/* 	FILE* f_tree = fopen(filename, "r");

	fscanf()
 */
}

Tree::~Tree ()
{
	assert (head_);

	head_->Walk (free_);
	head_ = nullptr;
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
				system("echo \"Wohoo!!! We found it\" | festival --tts");
				printf ("Wohoo!!! We found it!\n");
				cur_tree = this;
			} 
			else 
				cur_tree = (cur_tree->right_);
		}
		else if(!strcmp (str, "Quit\n"))
			break;
		else
		{
			system("echo \"WRONG COMMAND. Type 'Yes' or 'No'\" | festival --tts");			
			printf ("WRONG COMMAND. Type 'Yes' or 'No':\n");
		}
	}
}

void Node::add_node (char* str)
{
	left_ 		  = (Node*) calloc(1, sizeof (Node));
	left_->data_  = (char*) calloc(strlen (data_) + 1, sizeof (char));

	sprintf (left_->data_, "%s", data_);
	free	(data_);

	system ("echo \"What is your word?\" | festival --tts");
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
	system("echo \"Enter object that you want to find\" | festival --tts");	
	printf ("Enter object that you want to find:\n");

	char** path = nullptr;
	int   size = search (path);

	system("echo \"Object's path\" | festival --tts");
	printf ("Object's path:\n");

	for(int i = 0; i < size; i++)
		printf ("{%s}\t", path[i]);

	printf ("\n");

	free (path);
}

void Node::compare ()
{
	system("echo \"Enter objects that you want to compare\" | festival --tts");
	printf ("Enter objects that you want to compare:\n");

	char** obj_1 = nullptr;
	int	  size_1 = search (obj_1);

	char** obj_2 = nullptr;
	int   size_2 = search (obj_2);

	int min = size_2 < size_1? size_2: size_1;
	int max = size_2 > size_1? size_2: size_1;

	char** dif1 = (char**) calloc (min, sizeof(char*));
	char** dif2 = (char**) calloc (min, sizeof(char*));

	int size_d = 0;

	system("echo \"Objects are same in\" | festival --tts");
	printf ("Objects are same in:\n");

	for(int i = 0; i < min; i++)
	{
		if(!strcmp (obj_2[i], obj_1[i]))
			printf ("{%s}\t", obj_1[i]);
		else
		{
			dif1[size_d] = obj_1[i];
			dif2[size_d] = obj_2[i];
			size_d++;
		}
	}

	printf ("\n");

	if(size_d > 0 || min != max)
	{
		system("echo \"Objects are different in\" | festival --tts");
		printf ("Objects are different in:\n");

		for(int i = 0; i < size_d; i++)
			printf ("{%s}\t", dif1[i]);

		if(max == size_1)
			for(int i = min; i < max; i++)
				printf ("{%s}\t", obj_1[i]);

		printf("\n");

		for(int i = 0; i < size_d; i++)
			printf ("{%s}\t", dif2[i]);

		if(max == size_2)
			for(int i = min; i < max; i++)
				printf ("{%s}\t", obj_2[i]);

		printf("\n");
	}

	free (obj_1);
	free (obj_2);
	free (dif1);
	free (dif2);
}

void Node::search_ (char* str, Stack* stk, int* mode)
{
	if(!strcmp (str, data_))
		*mode = 1;
	else if(left_ != nullptr && *mode == 0)
	{
		stk->push (-1);
		left_->search_ (str, stk, mode);

		if(right_ != nullptr && *mode == 0)
		{
			stk->push (1);
			right_->search_ (str, stk, mode);
		}

		if(*mode == 0 && stk->get_size () > 0)
			stk->pop ();
	}
	else if(right_ == nullptr && left_ == nullptr && *mode == 0)
		stk->pop ();
}

int  Node::search (char**& path)
{
	char str[SIZE] = {};
	
	fgets(str, SIZE, stdin);
	str[strlen(str) - 1] = '\0';

	Stack stk;

	int mode = 0;

	this->search_ (str, &stk, &mode);
	
	path = (char**) calloc (stk.get_size() + 1, sizeof(char*));

	if(mode == 0)
	{
		printf("There is no \"%s\"\n", str);
		return 0;
	}
	else
	{
		Node* curr = this;

		path[0] = curr->data_;

		for(int start = 0, end = stk.get_size (); start < end; start++)
		{
			if(stk[start] == 1)
				curr = curr->right_;
			else if(stk[start] == -1)
				curr = curr->left_;

			path[start + 1] = curr->data_;
		}
	}
	return stk.get_size() + 1;
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

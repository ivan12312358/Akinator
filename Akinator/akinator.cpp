#include "../Libraries/stack.h"
#include "../Libraries/node.h"
#include "../Libraries/akinator.h"

//TODO func Save like Print but can change file

int main (int argc, char* argv[])
{
	Tree tree(argv[1]);

//	tree.Akinator ();

	tree.Find ();

	tree.Graph(argv[1]);

//	tree.Compare ();

	return 0;
}

//-------------------------------------------------------------------------------

Tree::Tree ()
{
	head_ = (Node*) calloc (1, sizeof (Node));

	system ("echo \"Please, enter first object\" | festival --tts");
	printf ("Please, enter first object:\n");

	char str[SIZE] = "";
	fgets (str, SIZE, stdin);

	head_->data_ = (char*) calloc (strlen (str) + 1, sizeof (char));

	sprintf (head_->data_, "%s", str);

	head_->data_[strlen (str) - 1] = '\0';
}

//-------------------------------------------------------------------------------

Tree::Tree (char* filename)
{
	char *symbols = nullptr;
	int size = read (&symbols, filename);

	if(size == 0)
	{
		system ("echo \"Empty base!\" | festival --tts");
		printf ("Your base is empty! I will use default base.\n");

		size = read (&symbols, "default.base");
	}

	char* tmp = symbols;

	char** str = (char**) calloc (size, sizeof (char*));
	split (str, symbols);

	head_ = (Node*) calloc (1, sizeof (Node));

	int start = 0;

	head_->walk_ (str, &start);

	free (str);
	free (tmp);
}

//-------------------------------------------------------------------------------

Tree::~Tree ()
{
	Save("base.log");

	assert (head_);

	head_-> free_();
	head_ = nullptr;
}

//-------------------------------------------------------------------------------

void Tree::Akinator () 
{
	char str[128] = {};

	Node* curr = head_;

	while(true)
	{
		printf ("Your object is {%s}? [Y\\N]\n", curr->data_);
		fgets  (str, SIZE, stdin);

		if (!strcmp (str, "N\n"))
		{
			if(curr->left_ == nullptr)
			{
				curr->new_obj_ (str);
				curr = head_;
			}
			else
				curr = curr->left_;
		}
		else if(!strcmp (str, "Y\n"))
		{	
			if(curr->right_ == nullptr)
			{
				system ("echo \"Wohoo!!! We found it\" | festival --tts");
				printf ("Wohoo!!! We found it!\n");
				curr = head_;
			} 
			else 
				curr = curr->right_;
		}
		else if(!strcmp (str, "Quit\n"))
			break;
		else
		{
			system ("echo \"WRONG COMMAND. Type 'Y' or 'N'\" | festival --tts");			
			printf ("WRONG COMMAND. Type 'Y' or 'N':\n");
		}
	}
}

//-------------------------------------------------------------------------------

void Tree::Save ()
{	
	system ("echo \"Where to save your database?\" | festival --tts");
	printf ("Where to save your database?\n");

	char str[SIZE];
	fgets (str, SIZE, stdin);

	FILE*   f_dump = fopen (str, "w");
	assert (f_dump);

	head_->fprint_ (f_dump);

	fclose (f_dump);	
}

//-------------------------------------------------------------------------------

void Tree::Save (const char* filename)
{
	FILE*   f_dump = fopen (filename, "w");
	assert (f_dump);

	head_->fprint_ (f_dump);

	fclose (f_dump);	
}

//-------------------------------------------------------------------------------

void Tree::Find ()
{
	//system ("echo \"Enter object that you want to find\" | festival --tts");	
	//printf ("Enter object that you want to find:\n");

	char** path = nullptr;
	int   size = Search (path);

	if(size < 1)
		return;

	system ("echo \"Object's path\" | festival --tts");
	printf ("Object's path:\n");

	for(int i = 0; i < size; i++)
		printf ("{%s}  ", path[i]);

	printf ("\n");

	free (path);
}

//-------------------------------------------------------------------------------

void Tree::Compare ()
{
	system("echo \"Enter objects that you want to compare\" | festival --tts");
	printf ("Enter objects that you want to compare:\n");

	char** obj_1 = nullptr;
	int	  size_1 = Search (obj_1);

	char** obj_2 = nullptr;
	int   size_2 = Search (obj_2);

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
			printf ("{%s}  ", obj_1[i]);
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
			printf ("{%s}  ", dif1[i]);

		if(max == size_1)
			for(int i = min; i < max; i++)
				printf ("{%s}  ", obj_1[i]);

		printf("\n");

		for(int i = 0; i < size_d; i++)
			printf ("{%s}  ", dif2[i]);

		if(max == size_2)
			for(int i = min; i < max; i++)
				printf ("{%s}  ", obj_2[i]);

		printf("\n");
	}

	free (obj_1);
	free (obj_2);
	free (dif1);
	free (dif2);
}

//-------------------------------------------------------------------------------

int  Tree::Search (char**& path)
{
	char str[SIZE] = {};

	fgets (str, SIZE, stdin);
	str[strlen (str) - 1] = '\0';

	Stack stk;

	int mode = 0;

	head_->search_ (str, &stk, mode);

	stk.dump();

	int size = stk.get_size ();

	path = (char**) calloc (size + 1, sizeof(char*));

	if(mode == 0)
	{
		printf ("There is no \"%s\"\n", str);
		return 0;
	}
	
	Node* curr = head_;

	path[0] = curr->data_;

	for(int start = 0; start < size; start++)
	{
		if(stk[start] == 1)
		{
			curr = curr->right_;
			path[start + 1] = curr->data_;
		}
		else if(stk[start] == -1)
		{
			path[start + 1] = (char*) calloc(SIZE, sizeof(char));
			curr = curr->left_;
			sprintf(path[start + 1], "Not %s", curr->data_);
		}

	}

	return size + 1;
}

//-------------------------------------------------------------------------------

void Tree::Graph (char* filename)
{
	if(head_->data_ == nullptr)
	{
		printf ("Tree is empty\n");
		return;
	}

	FILE*   f_graph = fopen ("graph.dot", "w");
	assert (f_graph);

	fprintf (f_graph, "digraph Tree {\n"
			"\tnode [shape = circle, width = 1]\n"
			"\tedge [color = \"blue\"];\n"
			"\tnodesep = 1.5\n"
			"\tbase [label = \"%s\", fillcolor = yellow, style = \"rounded,filled\","
			"shape = doubleoctagon, fontsize = 15]\n\n"

			"\tsubgraph cluster\n\t{\n"
			"\t\tlabel = \"head\";\n"
			"\t\t%s [fillcolor = royalblue, style = \"rounded,filled\", shape = diamond]\n",
			filename, head_->data_);

	if(head_->right_ && head_->left_)
	{

		head_->g_print_		  (f_graph);
		head_->left_ ->graph_ (f_graph);
		head_->right_->graph_ (f_graph);
	}
	else
		fprintf (f_graph, "\t}\n");

	fprintf (f_graph, "\tlabel = \"This is Akinator base\";\n}\n");

	fclose  (f_graph);

	system ("dot -Tpng graph.dot -o graph.png");
}

//-------------------------------------------------------------------------------

int read (char** symbols, char* filename)
{
	FILE* base = fopen (filename, "r");

	if(base == nullptr)
	{
		printf ("Couldn't find file\n");
		return 0;
	}

	fseek (base, 0, SEEK_END);
	int size = ftell (base);
	rewind (base);

	if(size > 0)
	{
		*symbols = (char*) calloc (size, sizeof (char));
		fread (*symbols, sizeof (char), size, base);
	}

	fclose (base);

	return size;
}

//-------------------------------------------------------------------------------

void split (char** str, char* symbols)
{
	symbols = strtok (symbols, " \n");

	int cnt = 0;

	while(symbols != NULL)
	{
		str[cnt++] = symbols;
		symbols    = strtok (nullptr, " \n");
	}
}

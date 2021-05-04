#include "../Libraries/stack.h"
#include "../Libraries/node.h"
#include "../Libraries/akinator.h"

enum game_modes
{
	Clear = '0',
	Guessing, 
	Definition,
	Compare,
	Graph,
	Save,
	Exit
};


int main (int argc, char* argv[])
{
	Menu(argv[1]);

	return 0;
}
//-------------------------------------------------------------------------------

void Menu(char* filename)
{
	printf ("\t\tHello! I am Akinator!\n");
	system ("echo \"Hello! I am Akinator! Enter base and game mode\" | festival --tts");

	char str[SIZE] = "";

	if(!filename)
	{
		printf ("Enter name of file with base or \"New\" to use empty base and choose game mode\n\n");
		fgets  (str, SIZE, stdin);
		str[strlen(str) - 1] = '\0';
	}
	else
		sprintf(str, "%s", filename);

	Tree tree (str);

	char mode[10];

	while(true)
	{
		printf ("\t\t\tMENU\n"
				"0 - Clear terminal\n"
				"1 - Guessing\n"
				"2 - Definition\n"
				"3 - Compare\n"
				"4 - Graph\n"
				"5 - Make a save\n"
				"6 - Exit\n");

		fgets(mode, 10, stdin);

		switch(mode[0])
		{
			case (Clear):
				system("clear");
				break;
			case(Guessing):
				tree.Akinator ();
				break;
			case(Definition):
				tree.Find ();
				break;
			case(Compare):
				tree.Compare ();
				break;
			case(Graph):
				tree.Graph (str);
				break;
			case(Save):
				tree.Save ();
				break;
			case(Exit):
				return;
				break;
			default:
				scanf("%*s");
				printf("WRONG command. Try again\n");
		}
	}
}

//-------------------------------------------------------------------------------

Tree::Tree (const char* filename)
{
	if(!strcmp(filename, "New"))
	{
		head_ = (Node*) calloc (1, sizeof (Node));

		//system ("echo \"Please, enter first object\" | festival --tts");
		printf ("Please, enter first object:\n");

		char str[SIZE] = "";
		fgets (str, SIZE, stdin);

		head_->data_ = (char*) calloc (strlen (str) + 1, sizeof (char));

		sprintf (head_->data_, "%s", str);

		head_->data_[strlen (str) - 1] = '\0';

		return;
	}

	char *symbols = nullptr;
	int size = Read (&symbols, filename);

	if(size == 0)
	{
		//system ("echo \"Empty base!\" | festival --tts");
		printf ("Your base is empty! I will use default base.\n");

		size = Read (&symbols, "default.base");
	}

	char* tmp = symbols;

	char** str = (char**) calloc (size, sizeof (char*));
	Split (str, symbols);

	head_ = (Node*) calloc (1, sizeof (Node));

	int start = 0;

	head_->walk_ (str, &start);

	free (str);
	free (tmp);
}

//-------------------------------------------------------------------------------

Tree::~Tree ()
{
	printf ("Do you want to save base? Type [Y/N]\n");
	system ("echo \"Do you want to save base?\" | festival --tts ");

	char str[SIZE] = "";
	fgets(str, SIZE, stdin);

	if(!strcmp(str, "Y\n"))
		Save();

	assert (head_);

	head_-> free_();

	printf ("Bye!\n");
	system ("echo \"Bye\" | festival --tts");
}

//-------------------------------------------------------------------------------

void Tree::Akinator () 
{
	char str[SIZE] = "";

	Node* curr = head_;

	system("clear");

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
				//system ("echo \"Wohoo!!! We found it\" | festival --tts");
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
			//system ("echo \"WRONG COMMAND. Type 'Y' or 'N'\" | festival --tts");			
			printf ("WRONG COMMAND. Type 'Y' or 'N':\n");
		}
	}
}

//-------------------------------------------------------------------------------

void Tree::Save ()
{	
	printf("Saving...\n");
	//system ("echo \"Where to save your database?\" | festival --tts");
	printf ("Where to save your database?\n");

	char str[SIZE] = "";;
	fgets (str, SIZE, stdin);

	FILE*   f_dump = fopen (str, "w");
	assert (f_dump);

	head_->fprint_ (f_dump);

	fclose (f_dump);

	printf("Saved in %s", str);
}

//-------------------------------------------------------------------------------

void Tree::Find ()
{
	system("clear");
	//system ("echo \"Enter object that you want to find\" | festival --tts");	
	printf ("Enter object that you want to find:\n");

	Stack stk;

	Search (&stk);

	int size = stk.get_size ();

	Node* curr = head_;

	for(int i = 0; i < size; i++)
	{
		if(stk[i] == -1)
		{
			printf ("Not {%s}\n", curr->data_);
			curr = curr->left_;
		}
		else if(stk[i] == 1)
		{
			printf ("{%s}\n", curr->data_);
			curr = curr->right_;
		}
	}
	printf("{%s}\n", curr->data_);
}

//-------------------------------------------------------------------------------

Node* Node::compare_(Stack& stk, int* diff)
{
	if(stk[*diff] == -1) printf("Not ");
	printf("{%s}  ", data_);

	if(stk[*diff] == -1) return left_;
	else 				 return right_;

}

//-------------------------------------------------------------------------------

void Tree::Compare ()
{

	system("clear");
	//system("echo \"What to compare\" | festival --tts");
	printf ("Enter objects that you want to compare:\n");

	Stack    stk1;
	Search (&stk1);
	int size1 = stk1.get_size ();

	Stack    stk2;
	Search (&stk2);
	int size2 = stk2.get_size ();

	printf ("Objects are same in:\n");

	Node* curr = head_;

	int diff = 0;

	for( ; diff < size1 && diff < size2; diff++)
	{
		if(stk1[diff] == stk2[diff])
			curr = curr->compare_(stk1, &diff);
		else break;
	}

	Node* tmp = curr;

	printf ("\nObjects are different in:\n");

	for(int m = diff; m < size1; m++)
		curr = curr->compare_(stk1, &m);

	printf("\n");

	curr = tmp;

	for(int n = diff; n < size2; n++)
		curr = curr->compare_(stk2, &n);

	printf("\n");
}

//-------------------------------------------------------------------------------

void  Tree::Search (Stack* stk)
{
	char str[SIZE] = "";

	fgets (str, SIZE, stdin);
	str[strlen (str) - 1] = '\0';

	int mode = 0;

	head_->search_ (str, stk, mode);
}

//-------------------------------------------------------------------------------

void Tree::Graph (char* filename)
{
	if(head_->data_ == nullptr)
	{
		printf ("Tree is empty\n");
		return;
	}

	system("clear");
	printf("Making graph...\n");

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

int Read (char** symbols, const char* filename)
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

void Split (char** str, char* symbols)
{
	symbols = strtok (symbols, " \n");

	int cnt = 0;

	while(symbols != NULL)
	{
		str[cnt++] = symbols;
		symbols    = strtok (nullptr, " \n");
	}
}

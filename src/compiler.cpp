#include "../include/ast.hpp"
#include "lexer.flex"
#include "parser.y"

int main(int argc, char *argv[])
{
	std::ofstream output_file(argv[4]);
	yyin=fopen(argv[2], "r");
	Context context;
	const Node *root = parseAST();
	root->translate(context);
	return 0;
}
#include "../include/ast.hpp"

int main(int argc, char *argv[])
{
	std::ofstream output_file(argv[4]);
	yyin = fopen(argv[2], "r");
	Context context;
	const Node *root = parseAST();
	root->translate(context);
	return 0;
}

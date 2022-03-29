#include "../include/ast.hpp"
#include <fstream>

int main(int argc, char *argv[])
{
	std::ofstream output_file(argv[4]);
	yyin=fopen(argv[2], "r");
	Context context;
	std::ifstream src(argv[2]);
	const Node *root = parseAST(src);
	root->translate(context);
	return 0;
}
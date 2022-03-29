#include "ast.hpp"

int main()
{
	// std::ofstream output_file(argv[4]);
	// yyin=fopen(argv[2], "r");
	Context context;
	const std::vector<Expression *> *root = parseAST();
	for (auto it = root->begin(); it != root->end(); it++)
	{
		(*it)->translate(context);
	}
	return 0;
}
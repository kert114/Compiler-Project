#include "../include/ast.hpp"


int main(int argc, char* argv[]){
	std::ofstream outfile(argv[4]);
	yyin = fopen(argv[2], "r");
	Context context;
	const Node* root = parse();
	root->translate(context);
	return 0;
}

#include "../include/ast.hpp"


int main(int argc, char* argv[]){
	yyin = fopen(argv[2], "r");
	std::ofstream output_file(argv[4]);
	Context context;
	const Node* root = parse();
	root->translate(context);
	return 0;
}

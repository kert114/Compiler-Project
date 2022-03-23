#ifndef ast_statements_hpp
#define ast_statements_hpp

#include <string>
#include <iostream>
#include <vector>
#include "ast_expression.hpp"

class compound_statement_declaration
    :public Statement{
        private : 
            std::vector<Statement*>* statements;
            std::vector<Declaration*>* declarations;
        public :
            compound_statement_declaration(std::vector<Statement*>* _statements = NULL, std::vector<Declaration*>* declarations = NULL):
            statements(_statements), declarations(_declarations){}

            virtual void translate(Context& context){
                context.expand_context_scope();
                if (declarations != NULL){
				    for (auto declaration = declarations->begin(); declaration != declarations->end(); declaration++){
					    (*declaration)->translate(context);
				    }
			    }

			    if (statements != NULL)
			    {
			    	for(auto statement = statements->begin(); statement != statements->end(); statement++)
			    	{
			    		(*statement)->translate(context);
			    	}
			    }

			    context.reduce_context_scope();
            }

    };


#endif

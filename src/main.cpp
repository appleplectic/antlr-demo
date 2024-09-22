#include <sstream>
#include "ANTLRDemoLexer.h"
#include "ANTLRDemoParser.h"
#include "ANTLRDemoAST.h"


int main(const int argc, const char** argv) {
    if (argc != 2) {
        std::cerr << "Fatal error: malformed arguments.\nCompilation terminated.\n";
        return 1;
    }

    std::ifstream reader;
    reader.open(argv[1]);

    antlr4::ANTLRInputStream input_stream(reader);
    ANTLRDemoGrammar::ANTLRDemoLexer lexer(&input_stream);
    antlr4::CommonTokenStream tokens(&lexer);
    ANTLRDemoGrammar::ANTLRDemoParser parser(&tokens);

    ANTLRDemoGrammar::ANTLRDemoParser::ProgramContext* tree = parser.program();

    ANTLRDemoAST visitor;
    visitor.visitProgram(tree);

    return 0;
}

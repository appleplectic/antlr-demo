#include "ANTLRDemoAST.h"

double ANTLRDemoAST::castToDouble(const std::any& arg) {
    return std::any_cast<double>(arg);
}

std::any ANTLRDemoAST::visitProgram(ANTLRDemoGrammar::ANTLRDemoParser::ProgramContext *context) {
    for (const auto& line : context->line()) {
        const auto output = castToDouble(visit(line));
        std::cout << output << '\n';
    }

    return defaultResult();
}

std::any ANTLRDemoAST::visitLine(ANTLRDemoGrammar::ANTLRDemoParser::LineContext *context) {
    return visitChildren(context);
}

std::any ANTLRDemoAST::visitMulDiv(ANTLRDemoGrammar::ANTLRDemoParser::MulDivContext *context) {
    if (context->MUL() != nullptr) {
        return castToDouble(visit(context->expr()[0])) * castToDouble(visit(context->expr()[1]));
    }
    return castToDouble(visit(context->expr()[0])) / castToDouble(visit(context->expr()[1]));
}

std::any ANTLRDemoAST::visitAddSub(ANTLRDemoGrammar::ANTLRDemoParser::AddSubContext *context) {
    if (context->ADD() != nullptr) {
        return castToDouble(visit(context->expr()[0])) + castToDouble(visit(context->expr()[1]));
    }
    return castToDouble(visit(context->expr()[0])) - castToDouble(visit(context->expr()[1]));
}

std::any ANTLRDemoAST::visitParen(ANTLRDemoGrammar::ANTLRDemoParser::ParenContext *context) {
    return visitChildren(context);
}


std::any ANTLRDemoAST::visitNumber(ANTLRDemoGrammar::ANTLRDemoParser::NumberContext *context) {
    return stod(context->NUM()->getText());
}

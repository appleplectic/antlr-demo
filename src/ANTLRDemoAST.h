#pragma once
#include "ANTLRDemoParserBaseVisitor.h"

class ANTLRDemoAST final : public ANTLRDemoGrammar::ANTLRDemoParserBaseVisitor {
private:
    static double castToDouble(const std::any& arg);
public:
    std::any visitProgram(ANTLRDemoGrammar::ANTLRDemoParser::ProgramContext *context) override;
    std::any visitLine(ANTLRDemoGrammar::ANTLRDemoParser::LineContext *context) override;
    std::any visitMulDiv(ANTLRDemoGrammar::ANTLRDemoParser::MulDivContext *context) override;
    std::any visitAddSub(ANTLRDemoGrammar::ANTLRDemoParser::AddSubContext *context) override;
    std::any visitParen(ANTLRDemoGrammar::ANTLRDemoParser::ParenContext *context) override;
    std::any visitNumber(ANTLRDemoGrammar::ANTLRDemoParser::NumberContext *context) override;
};

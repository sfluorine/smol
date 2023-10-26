#pragma once

#include "ast.h"
#include "lexer.h"
#include <string>
#include <vector>

class Parser {
public:
    Parser(Lexer lexer);

    std::shared_ptr<Expr> parse_expression();

private:
    bool expect(Token::Type);
    bool eof();
    void consume();
    void match(Token::Type);

private:
    Lexer m_lexer;
    Token m_current_token;

    std::vector<std::string> m_errors;
};

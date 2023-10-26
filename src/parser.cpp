#include "parser.h"

#include <format>

Parser::Parser(Lexer lexer) : m_lexer(std::move(lexer)), m_current_token(lexer.get_token())
{
}

std::shared_ptr<Expr> Parser::parse_expression()
{
    std::format();
}

bool Parser::expect(Token::Type type)
{
    return m_current_token.type == type;
}

bool Parser::eof()
{
    return expect(Token::Type::EndOfFile);
}

void Parser::consume()
{
    if (!eof()) {
        m_current_token = m_lexer.get_token();
    }
}

void Parser::match(Token::Type type)
{
    if (!expect(type)) {
    }
}

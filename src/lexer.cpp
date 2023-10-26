#include <cctype>

#include "lexer.h"

char const* Lexer::current_input_ptr() const
{
    return input().data() + cursor();
}

char Lexer::current() const
{
    return input()[cursor()];
}

bool Lexer::eof() const
{
    return cursor() >= input().length();
}

void Lexer::consume()
{
    if (!eof()) {
        if (current() == '\n') {
            m_line++;
        }

        m_cursor++;
    }
}

Token Lexer::get_token()
{
    skip_ws_and_comments();

    const auto start = current_input_ptr();
    const auto start_line = line();

    if (eof()) {
        return Token(Token::Type::EndOfFile, start_line);
    }

    switch (current()) {
        case '(':
            consume();
            return Token(Token::Type::LParen, "(", start_line);
        case ')':
            consume();
            return Token(Token::Type::RParen, ")", start_line);
        case '=':
            consume();
            return Token(Token::Type::Equal, "=", start_line);
        case ';':
            consume();
            return Token(Token::Type::Semicolon, ";", start_line);
        default:
            break;
    }

    if (std::isalpha(current()) || current() == '_') {
        size_t len = 0;
        do {
            len++;
            consume();
        } while (!eof() && (std::isalnum(current()) || current() == '_'));

        auto span = std::string_view(start, len);

        if (span == "let") {
            return Token(Token::Type::Let, "let", start_line);
        }

        return Token(Token::Type::Identifier, start_line);
    }

    if (std::isdigit(current())) {
        size_t len = 0;
        do {
            len++;
            consume();
        } while (!eof() && std::isdigit(current()));

        auto span = std::string_view(start, len);

        return Token(Token::Type::IntLiteral, span, start_line);
    }

    size_t garbage_len = 0;
    do {
        garbage_len++;
        consume();
    } while (!eof() && !std::isspace(current()));

    auto garbage_span = std::string_view(start, garbage_len);

    return Token(Token::Type::Error, garbage_span, start_line);
}

void Lexer::skip_ws_and_comments()
{
    while (!eof() && (std::isspace(current()) || current() == '#')) {
        while (!eof() && std::isspace(current())) {
            consume();
        }

        if (current() == '#') {
            do {
                consume();
            } while (!eof() && current() != '\n');
        }
    }
}

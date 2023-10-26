#pragma once

#include <string_view>

#include "token.h"

class Lexer {
public:
    Lexer() : m_cursor(0), m_line(1) {}
    Lexer(std::string_view input) : m_input(input), m_cursor(0), m_line(1) {}

    std::string_view const & input() const { return m_input; }

    size_t const& cursor() const { return m_cursor; }

    size_t const& line() const { return m_line; }

    char const* current_input_ptr() const;

    char current() const;

    bool eof() const;

    void consume();

    Token get_token();

private:
    void skip_ws_and_comments();

private:
    std::string_view m_input;
    std::size_t m_cursor;
    std::size_t m_line;
};

#pragma once

#include <string_view>

struct Token {
    enum class Type {
        EndOfFile,
        Error,

        Let,

        IntLiteral,
        Identifier,

        LParen,
        RParen,
        Equal,
        Semicolon,

        Plus,
        Minus,
        Star,
        Slash,
    };

    Token(Type type, std::size_t line) : type(type), repr(""), line(line) {}
    Token(Type type, std::string_view repr, std::size_t line) : type(type), repr(repr), line(line) {}

    Type type;
    std::string_view repr;
    std::size_t line;
};

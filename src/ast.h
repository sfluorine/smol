#pragma once

#include <cstdint>
#include <memory>
#include <string_view>
#include <variant>

class Expr {
public:
    enum class Type {
        Value,
        Binary,
    };

    virtual ~Expr() = 0;

    virtual Type expr_type() const = 0;

protected:
    Expr() {}
};

class ValueExpr : public Expr {
public:
    enum class ValueType {
        Integer,
        Identifier,
    };

    ValueExpr(std::int64_t integer) : m_type(ValueType::Integer), m_value(integer) {}

    ValueExpr(std::string_view identifier) : m_type(ValueType::Identifier), m_value(identifier) {}

    virtual Type expr_type() const override { return Expr::Type::Value; }

private:
    ValueType m_type;
    std::variant<std::int64_t, std::string_view> m_value;
};

class BinaryExpr : public Expr {
public:
    enum class Op {
        Add,
        Sub,
        Mul,
        Div,

        Less,
        Greater,
        Equal,
        NotEqual,
    };

    BinaryExpr(Op op, std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : m_op(op), m_lhs(lhs), m_rhs(rhs) {}

    virtual Type expr_type() const override { return Expr::Type::Binary; }

    Op op() const { return m_op; }

    std::shared_ptr<Expr> lhs() const { return m_lhs; }

    std::shared_ptr<Expr> rhs() const { return m_lhs; }

private:
    Op m_op;
    std::shared_ptr<Expr> m_lhs;
    std::shared_ptr<Expr> m_rhs;
};

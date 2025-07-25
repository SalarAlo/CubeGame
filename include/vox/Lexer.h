#pragma once

#include <functional>
#include <string>
#include <vector>

enum class TokenType {
        Number,

        Plus, Minus, Star, Slash,
        OpenedParen, ClosedParen,

        Less, Greater,
        LessEqual, GreaterEqual,
        EqualEqual,

        If, Do, End, Return,

        Or, And, Not
};

inline const char* tokenTypeToString(const TokenType& type) {
        switch (type) {
        case TokenType::Number: return "Number";
        case TokenType::Plus: return "Plus";
        case TokenType::Minus: return "Minus";
        case TokenType::Star: return "Star";
        case TokenType::Slash: return "Slash";
        case TokenType::OpenedParen: return "OpenedParen";
        case TokenType::ClosedParen: return "ClosedParen";
        case TokenType::Less: return "Less";
        case TokenType::Greater: return "Greater";
        case TokenType::Not: return "Not";
        case TokenType::LessEqual: return "LessEqual";
        case TokenType::GreaterEqual: return "GreaterEqual";
        case TokenType::EqualEqual: return "EqualEqual";
        case TokenType::If: return "If";
        case TokenType::Do: return "Do";
        case TokenType::End: return "End";
        case TokenType::Return: return "Return";
        case TokenType::Or: return "Or";
        case TokenType::And: return "And";
        }
        return "Unknown";
}

struct Token {
        TokenType Type;
        std::string lexeme;
        int line;
};

class Lexer {
public:
        Lexer() = default;
        Lexer(const std::string& sourceCode);
        const std::vector<Token>& StringToTokens();

        inline void SetSourceCode(const std::string& sourceCode) { m_SourceCode = sourceCode; }

private:
        bool IsAtEnd() const;
        void Reset();
        void Scan();
        bool Match(char expected);
        void AddToken(TokenType type);

        bool Peak(char match, int peakAmt = 0);
        bool Peak(std::function<bool(char)>, int peakAmt = 0);
        
        std::string GetLexeme();

private:
        bool m_ErrorOccured {};

        std::vector<Token> m_Tokens {};
        std::string m_SourceCode {};

        unsigned int m_StartIdx {};
        unsigned int m_Idx {};
        unsigned int m_Line { 1 };
};


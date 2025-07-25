#include "vox/Lexer.h"

#include <cctype>
#include <functional>
#include <vector>

Lexer::Lexer(const std::string& sourceCode) : m_SourceCode(sourceCode) {};

void Lexer::Reset() {
        m_Idx = 0;
        m_Tokens = {};
}

const std::vector<Token>& Lexer::StringToTokens() {
        Reset();

        while(!IsAtEnd()) {
                Scan();
        }

        return m_Tokens;
}

void Lexer::Scan() {
        const char current = Advance();

        switch(current) {
        case '(': 
                AddToken(TokenType::OpenedParen);
                break;
        case ')': 
                AddToken(TokenType::ClosedParen);
                break;
        case '+': 
                AddToken(TokenType::Plus);
                break;
        case '-': 
                AddToken(TokenType::Minus);
                break;
        case '*': 
                AddToken(TokenType::Star);
                break;
        case '/': 
                AddToken(TokenType::Slash);
                break;
        case '!':
                AddToken(TokenType::Not);
                break;
        case '<':
                AddToken(Match('=') ? TokenType::LessEqual: TokenType::Less);
                break;
        case '>':
                AddToken(Match('=') ? TokenType::GreaterEqual : TokenType::Greater);
                break;
        case 'o': 
                if(Match('r')) AddToken(TokenType::Or);
                break;
        case 'i': 
                if(Match('f')) AddToken(TokenType::If);
                break;
        case 'd':
                if(Match('o')) AddToken(TokenType::Do);
                break;
        case 'e':
                if(Match('n') && Match('d')) AddToken(TokenType::End);
                break;
        case ' ':
        case '\t':
                break;
        case '\n':
                m_Line++;
                break;
        default:
                
        }
}

bool Lexer::Peak(char match, int peakAmt=1) {
        char peakIdx = m_Idx + (peakAmt-1);
        if(peakIdx >= m_SourceCode.size()) return false;
        return m_SourceCode[peakIdx] == match;
}

bool Lexer::Peak(std::function<bool (char)> match, int peakAmt=1) {
        char peakIdx = m_Idx + (peakAmt-1);
        if(peakIdx >= m_SourceCode.size()) return false;
        return match(m_SourceCode[peakIdx]);
}

char Lexer::Advance() {
        m_StartIdx = m_Idx++;
        return m_SourceCode[m_StartIdx];
}

bool Lexer::Match(char expected) {
        if(IsAtEnd()) return false;
        if(m_SourceCode[m_Idx] != expected) return false;
        
        m_Idx++;
        return true;
}

bool Lexer::IsAtEnd() const {
        return m_Idx >= m_SourceCode.size();
}

std::string Lexer::GetLexeme() {
        return { "" };
}

void Lexer::AddToken(TokenType type) {
        Token token { type, GetLexeme(), m_Line };      
}


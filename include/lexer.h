#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum Token_type { 
    IDENTIFIER,
    NUM_LIT, STR_LIT, TRUE_LIT, FALSE_LIT,
    END_FILE,
    OPERATOR, SEPARATOR, PUNCTUATION,
    
    FOR, RETURN, DEFUN, LOCAL, GLOBAL,
    AS, BEGIN, END,
    COMMENT
};

/* Holds data about each token recovered from the lexer */
class Token {
    Token_type m_type;
    std::string m_raw;
    bool m_keyword;
    int m_index, m_line;

    public:
        Token(Token_type type, std::string raw, bool keyword, int index, int line)
            : m_type(type), m_raw(raw), m_keyword(keyword),
              m_index(index), m_line(line)
            {}

        ~Token() {}
        
        bool isKeyword()     { return this->m_keyword; }

        Token_type type()    { return this->m_type;    }
        std::string raw()    { return this->m_raw;     }
        int line()             { return this->m_line;    }
        int index()            { return this->m_index;   }

        std::string toString();

};

/* Gets the next Token in the program string */
class Lexer {
    std::string m_prog;
    int m_line, m_index;
    char m_currentChar;

    /* Index operations */
    char peek();
    char peekNext();
    void advance();
    
    // Resolves keyword to corresponding Token_type or identifier
    Token_type resolveKeyword(std::string raw);

    /* Get different types of tokens */
    Token makeKeywordOrId();
    Token makePunctuation();
    Token makeSeparator();
    Token makeOperator();
    Token makeNumberLiteral();
    Token makeComment();
    Token makeStringLiteral();

    /* Different character catagorizers */
    bool isWhiteSpace();
    bool isAlpha();
    bool isPunctuation();
    bool isSeparator();
    bool isOperator();
    bool isDigit();

    public:
        Lexer(std::string program) 
            : m_prog(program),
              m_line(1),
              m_index(0) 
        {
            this->m_currentChar = this->m_prog[0];
        }

        Token getNextToken();
        Token peekToken();
        Token peekNextToken();
};
#endif /* LEXER_H */
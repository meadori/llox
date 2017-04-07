#ifndef LLOX_TOKEN_H
#define LLOX_TOKEN_H

namespace llox {

enum TokenType {
  // Single-character tokens.
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,

  // One or two character tokens.
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  // Literals.
  IDENTIFIER,
  STRING,
  NUMBER,

  // Keywords.
  AND,
  CLASS,
  ELSE,
  FALSE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,

  END
};

class Token {
 protected:
  TokenType type;
  std::string lexeme;
  unsigned int line;

 public:
  Token(TokenType type, const std::string &lexeme, unsigned int line)
      : type(type), lexeme(lexeme), line(line) {}

  virtual std::string str() const {
    return std::to_string(type) + " " + lexeme;
  }
};

class StringToken : public Token {
  std::string literal;

 public:
  StringToken(const std::string &lexeme, unsigned int line,
              const std::string &literal)
      : Token(STRING, lexeme, line), literal(literal) {}

  std::string str() const override {
    return std::to_string(type) + " " + lexeme + " " + literal;
  }
};

class NumberToken : public Token {
  double literal;

 public:
  NumberToken(const std::string &lexeme, unsigned int line, double literal)
      : Token(NUMBER, lexeme, line), literal(literal) {}

  std::string str() const override {
    return std::to_string(type) + " " + lexeme + " " + std::to_string(literal);
  }
};

std::ostream &operator<<(std::ostream &out, const Token &token);

}  // namespace llox

#endif

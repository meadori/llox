#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>
#include <vector>

#include "llox/ast-printer.h"
#include "llox/ast.h"
#include "llox/interpreter.h"
#include "llox/parser.h"
#include "llox/scanner.h"
#include "llox/token.h"

static void run(const std::string &source, llox::Interpreter &interpreter) {
  llox::Scanner scanner(source);
  std::unique_ptr<llox::Scanner::TokenList> tokens = scanner.scanTokens();
  llox::Parser parser(std::move(tokens));
  std::unique_ptr<llox::StmtList> statements = parser.parse();

  if (statements) {
    llox::AstPrinter printer;
    std::cout << printer.print(*statements) << "\n";

    interpreter.interpret(*statements);
  }
}

static void runFile(const char *path) {
  llox::Interpreter interpreter;
  std::ifstream t(path);
  std::string str((std::istreambuf_iterator<char>(t)),
                  std::istreambuf_iterator<char>());
  run(str, interpreter);
}

static void runPrompt() {
  llox::Interpreter interpreter;
  for (;;) {
    std::cout << "> ";

    std::string source;
    std::getline(std::cin, source);
    run(source, interpreter);
  }
}

int main(int argc, char **argv) {
  if (argc > 2) {
    std::cerr << "usage: llox [script]" << std::endl;
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    runPrompt();
  }
  return 0;
}

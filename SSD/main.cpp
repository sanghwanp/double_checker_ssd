

#if (MAIN_SELECT == 1)
int main(int argc, char* argv[]) {
  std::string input;

  // 콘솔에서 명령어 입력 받기
  std::getline(std::cin, input);

  std::vector<std::string> tokens = splitCommand(input);

  //    Parser parser;
  //    parser.parse(tokens);

  return 0;
}
#endif
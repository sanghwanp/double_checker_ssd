

#if (MAIN_SELECT == 1)
int main(int argc, char* argv[]) {
  std::string input;

  // �ֿܼ��� ��ɾ� �Է� �ޱ�
  std::getline(std::cin, input);

  std::vector<std::string> tokens = splitCommand(input);

  //    Parser parser;
  //    parser.parse(tokens);

  return 0;
}
#endif
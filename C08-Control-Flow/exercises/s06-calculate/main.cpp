#include <iostream>

int calculate(int a, int b, char op)
{
  switch (op)
  {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    if (b != 0)
      return a / b;
    else
    {
      std::cerr << "Error: Division by zero!" << std::endl;
      return 0;
    }
  case '%':
    return a % b;
  default:
    std::cerr << "Error: Unknown operator!" << std::endl;
    return 0;
  }
}

int main()
{
  int num1;
  int num2;
  std::cout << "Enter two integers: ";
  std::cin >> num1 >> num2;
  
  char operation;
  std::cout << "Enter an operator (+, -, *, /, %): ";
  std::cin >> operation;

  int result = calculate(num1, num2, operation);
  std::cout << "Result: " << result << std::endl;

  return 0;
}
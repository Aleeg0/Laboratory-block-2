#include<iostream>
#include<fstream>
#include<string>

int inputMethod()
{
	 bool isIncorrect = true;
	 std::string str = "\0";
	 // asking what the type user want to use
	 std::cout << "The program works with console input or files.\n";
	 do
	 {
		  std::cout << "To use console enter \'console\'.\n"
				<< "To use a file enter \'file\'.\n"
				<< "Enter what type you want to use: \n";
		  std::cin >> str;
		  if (str == "console")
		  {
				return 1;
		  }
		  else if (str == "file")
		  {
				return 0;
		  }
		  else // wrong input
				std::cerr << "The word " << str << " don't match any of types of inputtin the data.\n";

	 } while (isIncorrect);

}

void consoleInput(double**& matrix, int& n)
{
	 bool isIncorrect = true;
	 // asking for Size of matrix
	 do
	 {
		  std::cout << "Enter the matrix order:\n";
		  std::cin >> n;
		  if (std::cin.get() != '\n')
		  {
				std::cin.clear();
				std::cin.ignore(3424, '\n');
				std::cerr << "Invalid type. Try again.\n";
		  }
		  if (n < 1)
				std::cerr << "Matrix order cannot be less than 1.";
		  else
				isIncorrect = false;
	 } while (isIncorrect);
	 // initialization of matrix
	 initialization(matrix, n);
	 isIncorrect = true;
	 for (int i = 0; i < n; i++)
	 {
		  for (int j = 0; j < n; j++)
		  {
				do
				{
					 std::cout << "Enter a" << i + 1 << j + 1 << ":\n";
					 std::cin >> matrix[i][j];
					 if (std::cin.get() != '\n')
					 {
						  std::cin.clear();
						  std::cin.ignore(3424, '\n');
						  std::cerr << "Invalid type. Try again.\n";
					 }
					 else
						  isIncorrect = false;
				} while (isIncorrect);
		  }
	 }
}

bool isFileExist(std::string nameFile)
{
	 std::ifstream in(nameFile);
	 if (in.is_open())
	 {
		  in.close();
		  return true;
	 }
	 return false;
}

bool isTextFile(std::string nameFile)
{
	 std::string type = nameFile.substr(nameFile.length() - (size_t)5);
	 return (type == ".txt") ? true : false;
}

std::string inputFileName()
{
	 std::string fileName = '\0';
	 bool isIncorrect = true;
	 do
	 {
		  // Inputting name of file or path to the file including file
		  std::cout << "Enter the name of file in this directory or path to this file including name of file:\n";
		  std::cin >> fileName;
		  if (!isFileExist(fileName)) // if file doesn't exist
		  {
				std::cerr << "This file or the path to the file is specified incorrectly or does not exist! Try again.\n";
		  }
		  else if (!isTextFile(fileName)) // if file isn't txt
		  {
				std::cerr << "This file or path to the file isn't .txt! Try again.\n";
		  }
		  else 
				isIncorrect = false; // to exit this loop
	 } while (isIncorrect);
	 return fileName;
}

void fileInput(double**& matrix, int& n)
{
	 std::string fileName = '\0',
					 
	 bool isIncorrect = true;
	 do
	 {
		  fileName = inputFileName();
		  std::ifstream in(fileName);
		  int n = 0;
		  in >> n;
		  if (in.get() != '\n')
		  {
				in.clear();
				in.ignore(4214, '\n');
				std::cerr << "Invalid type. Check data in the file.\n";
		  }
		  if (n < 1)
				std::cerr << "Matrix order cannot be less than 1.";
		  else
				isIncorrect = false;
	 } while (isIncorrect);
	 
	 
}


int main()
{
	 (inputMethod()) ? consoleInput() : fileInput();
}
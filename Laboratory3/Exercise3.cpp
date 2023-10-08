#include<iostream>
#include<fstream>
#include<string>

const int minMatrixOrder = 2;

int inputMethod()
{
	 bool isIncorrect = true;
	 std::string choice = "\0";
	 // asking what the type user want to use
	 std::cout << "The program works with console input or files.\n";
	 do
	 {
		  std::cout << "To use console enter \'console\'.\n"
				<< "To use a file enter \'file\'.\n"
				<< "Enter what type you want to use: \n";
		  std::cin >> choice;
		  if (choice == "console")
		  {
				return true;
		  }
		  else if (choice == "file")
		  {
				isIncorrect = false;
		  }
		  else // wrong input
				std::cerr << "The word " << choice << " don't match any of method to input the data.\n";

	 } while (isIncorrect);
	 return false;
}

void initialization(double**& matrix, int& n)
{
	 matrix = new double* [n];
	 for (int i = 0; i < n; i++)
	 {
		  matrix[i] = new double[n];
	 }
}

void inputSizeOfMatrixFromConsole(int& n)
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
		  else if (n < minMatrixOrder)
				std::cerr << "Matrix order cannot be less than " << minMatrixOrder << ".\n";
		  else
				isIncorrect = false;
	 } while (isIncorrect);
}

void inputElemtensOfMatrixFromConsole(double**& matrix,int& n)
{
	 bool isIncorrect = true;
	 for (int i = 0; i < n; i++)
	 {
		  for (int j = 0; j < n; j++)
		  {
				isIncorrect = true;
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

void consoleInput(double**& matrix, int& n)
{
	 // input size of matrix
	 inputSizeOfMatrixFromConsole(n);
	 // initialization of matrix
	 initialization(matrix, n);
	 // input elements of matrix
	 inputElemtensOfMatrixFromConsole(matrix, n);
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
	 std::string type = nameFile.substr(nameFile.length() - (size_t)(4));
	 return (type == ".txt") ? true : false;
}

bool isAnotherFile()
{
	 bool isIncorrect = true;
	 std::string userAnswer = "\0";
	 std::cout << "Read error was detected in your file.\n"
		  << "This program can't continue to read this file.\n";
	 do
	 {
		  std::cout << "Do you want to change file?(yes/no)\n";
		  std::cin >> userAnswer;
		  if (std::cin.get() != '\n')
		  {
				std::cin.clear();
				std::cin.ignore(4214, '\n');
				std::cerr << "Invalid type. Try again.\n";
		  }
		  if (userAnswer == "yes")
				return true;
		  else if (userAnswer == "no")
				isIncorrect = false;
		  else
				std::cout << "You input incorrect word! Try again.\n";
	 } while (isIncorrect);
	 return false;
}

std::string inputFileName()
{
	 std::string fileName = "\0";
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

bool inputSizeOfMatrixFromFile(std::ifstream& in,int& n)
{
	 in >> n;
	 if (in.fail())
	 {
		  in.clear();
		  in.ignore(12412, in.eof());
		  std::cerr << "Invalid type. Check data in the file.\n";
		  return false;
	 }
	 else if (n < minMatrixOrder)
	 {
		  std::cerr << "Matrix order cannot be less than " << minMatrixOrder << ".\n";
		  return false;
	 }
	 return true;
}

void free(double**& matrix, int& n)
{
	 for (int i = 0; i < n; i++)
	 {
		  delete[] matrix[i];
	 }
	 delete[] matrix;
	 matrix = nullptr;
}

bool inputElemtensOfMatrixFromFile(std::ifstream& in, double**& matrix, int& n)
{
	 initialization(matrix,n);
	 bool isIncorrect = true;
	 for (int i = 0; i < n; i++)
	 {
		  for (int j = 0; j < n; j++)
		  {
				in >> matrix[i][j];
				if(in.fail())
				{
					 in.clear();
					 in.ignore(12412, in.eof());
					 std::cerr << "Invalid type. Check data in the file.\n";
					 return false;
				}
		  }
	 }
	 return true;
}

bool fileInput(double**& matrix, int& n)
{
	 std::string fileName = "\0";
	 std::ifstream in;
	 bool isIncorrect = true;
	 // inputting size of matrix
	 do
	 {
		  fileName = inputFileName();
		  in.open(fileName);
		  if (inputSizeOfMatrixFromFile(in, n) && inputElemtensOfMatrixFromFile(in, matrix, n))
				isIncorrect = false;
		  else if (!isAnotherFile())
		  {
				in.close();
				return false;
		  }
		  in.close();
	 } while (isIncorrect);
	 return true;
}

bool outputMethod()
{
	 bool isIncorrect = true;
	 std::string choice = "\0";
	 // asking what the type user want to use
	 std::cout << "The program is ready to show answer.\n";
	 do
	 {
		  std::cout << "To output in console enter \'console\'.\n"
				<< "To output in a file enter \'file\'.\n"
				<< "Enter what type you want to use: \n";
		  std::cin >> choice;
		  if (choice == "console")
		  {
				return true;
		  }
		  else if (choice == "file")
		  {
				isIncorrect = false;
		  }
		  else // wrong input
				std::cerr << "The word " << choice << " don't match any of method to output the data.\n";

	 } while (isIncorrect);
	 return false;
}

void outputConsole(double& answer)
{
	 std::cout << "The answer is " << answer << ".\n";
}

void outputFile(double& answer)
{
	 std::string fileName = inputFileName();
	 std::ofstream out(fileName);
	 out << "The answer is " << answer << ".\n";
}

double findBestSum(double**& matrix, int& n)
{
	 double bestSum = 0;
	 for (int i = 0; i < n; i++)
	 {
		  for (int j = 0; j < n; j++)
		  {
				if (j + 1 < n && matrix[i][j] + matrix[i][j + 1] > bestSum)
					 bestSum = matrix[i][j] + matrix[i][j + 1];
				if (i + 1 < n && matrix[i][j] + matrix[i + 1][j] > bestSum)
					 bestSum = matrix[i][j] + matrix[i + 1][j];
		  }
	 }
	 return bestSum;
}



int main()
{
	 int n = 0;
	 double answer = 0;
	 double** matrix;
	 if (inputMethod())
	 {
		  consoleInput(matrix, n);
		  answer = findBestSum(matrix, n);
		  (outputMethod()) ? outputConsole(answer) : outputFile(answer);
	 }
	 else if (fileInput(matrix, n))
	 {
		  answer = findBestSum(matrix, n);
		  outputMethod() ? outputConsole(answer) : outputFile(answer);
	 }
	 free(matrix, n);
	 return 0;
}

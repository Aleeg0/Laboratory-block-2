Program Exercise3;

Uses
    System.SysUtils;

Const
    MinMatrixOrder = 2;

Type
    MatrixSize = Array Of Array Of Real;

Procedure InitializationMatrix(Var Matrix: MatrixSize; Const N: Integer);
Var
    I: Integer;
Begin
    SetLength(Matrix, N + 1, N + 1);
End;

Procedure Free(Var Matrix: MatrixSize);
Begin
    Matrix := Nil;
End;

Function InputMethod(): Boolean;
Var
    IsCorrect: Boolean;
    Choice: String;
Begin
    IsCorrect := False;
    Choice := '';
    Writeln('The program works with console input or files.');
    Repeat
        IsCorrect := False;
        Writeln('To use console enter ', #39, 'console', #39, '.', #13#10,
            'To use a file enter ', #39, 'file', #39, '.'#13#10,
            'Enter what type you want to use: ');
        Readln(Choice);
        If Choice = 'console' Then
        Begin
            IsCorrect := True;
            Result := True;
        End
        Else If Choice = 'file' Then
        Begin
            IsCorrect := True;
            Result := False;
        End
        Else
            Writeln('The word ', Choice, ' don', #39,
                't match any of method to input the data.');
    Until IsCorrect;
End;

Procedure InputSizeOfMatrixFromConsole(Var N: Integer);
Var
    IsCorrect: Boolean;
Begin
    // asking for Size of matrix
    Repeat
        IsCorrect := False;
        Try
            Writeln('Enter the matrix order:');
            Readln(N);
            IsCorrect := True;
        Except
            Writeln('Invalid type. Try again.');
        End;
        If (N < MinMatrixOrder) And IsCorrect Then
        Begin
            Writeln('Matrix order cannot be less than ', MinMatrixOrder, '.');
            IsCorrect := False;
        End;
    Until IsCorrect;
    N := N - 1;
End;

Procedure InputElementsOfMatrixFromConsole(Var Matrix: MatrixSize;
    Const N: Integer);
Var
    IsCorrect: Boolean;
    I: Integer;
    J: Integer;
Begin
    IsCorrect := False;
    For I := 0 To N Do
    Begin
        For J := 0 To N Do
        Begin
            IsCorrect := False;
            Repeat

                Try
                    Writeln('Enter a', I + 1, J + 1, ':');
                    Readln(Matrix[I][J]);
                    IsCorrect := True;
                Except
                    Writeln('Invalid type! Try again.');
                End;
            Until IsCorrect;
        End;
    End;
End;

Procedure ConsoleInput(Var Matrix: MatrixSize; Var N: Integer);
Begin
    // input size of matrix
    InputSizeOfMatrixFromConsole(N);
    // initialization of matrix
    InitializationMatrix(Matrix, N);
    // input elements of matrix
    InputElementsOfMatrixFromConsole(Matrix, N);
End;

Function IsFileTxt(Var FileName: String): Boolean;
Var
    FileType: String;
Begin
    FileType := FileName.Substring(FileName.Length - 4);
    If FileType = '.txt' Then
        Result := True
    Else
        Result := False;
End;

Function IsFileReadable(Var InFile: TextFile): Boolean;
Begin
    Try
        Reset(InFile);
        Result := True;
    Except
        Result := False;
    End;
    CloseFile(InFile);
End;

Function IsFileWritable(Var OutFile: TextFile): Boolean;
Begin
    Try
        Rewrite(OutFile);
        Result := True;
    Except
        Result := False;
    End;
    CloseFile(OutFile);
End;

Function InputReadFileName(): String;
Var
    FileName: String;
    IsCorrect: Boolean;
    InFile: TextFile;
Begin
    FileName := '';
    IsCorrect := False;
    Repeat
        IsCorrect := False;
        Assign(InFile, FileName);
        // Inputting name of file or path to the file including file
        Writeln('Enter the name of file in this directory or path to this file including name of file:');
        Readln(FileName);
        If (Not FileExists(FileName)) Then
            Writeln('This file or the path to the file is specified incorrectly or does not exist! Try again.')
        Else If (Not IsFileTxt(FileName)) Then
            Writeln('This file or path to the file isn', #39,
                't .txt! Try again.')
        Else If (Not IsFileReadable(InFile)) Then
            Writeln('The program can', #39, 't read this file!s Try again.')
        Else
            IsCorrect := True;
    Until IsCorrect;
    Result := FileName;
End;

Function InputWriteFileName(): String;
Var
    FileName: String;
    IsCorrect: Boolean;
    OutFile: TextFile;
Begin
    Repeat
        Assign(OutFile, FileName);
        IsCorrect := False;
        // Inputting name of file or path to the file including file
        Writeln('Enter the name of file in this directory or path to this file including name of file:');
        Readln(FileName);
        If (Not FileExists(FileName)) Then
            Writeln('This file or the path to the file is specified incorrectly or does not exist! Try again.')
        Else If (Not IsFileTxt(FileName)) Then
            Writeln('This file or path to the file isn', #39,
                't .txt! Try again.')
        Else If (Not IsFileWritable(OutFile)) Then
            Writeln('The program can', #39,
                't write into this file! Try again.')
        Else
            IsCorrect := True;
    Until IsCorrect;
    Result := FileName;
End;

Function InputSizeOfMatrixFromFile(Var InFile: TextFile;
    Var N: Integer): Boolean;
Var
    IsCorrect: Boolean;
Begin
    IsCorrect := False;
    Try
        Read(InFile, N);
        IsCorrect := True;
    Except
        Writeln('Invalid type. Check data in the file.');
    End;
    If IsCorrect And (N < MinMatrixOrder) Then
        Writeln('Matrix order cannot be less than ', MinMatrixOrder, '.')
    Else If IsCorrect Then
        Result := True
    Else
        Result := False;
End;

Function InputElementsOfMatrixFromFile(Var InFile: TextFile;
    Var Matrix: MatrixSize; Const N: Integer): Boolean;
Var
    IsIncorrect: Boolean;
    I: Integer;
    J: Integer;
Begin
    IsIncorrect := True;
    Result := True;
    InitializationMatrix(Matrix, N);
    For I := 0 To N Do
    Begin
        For J := 0 To N Do
        Begin
            IsInCorrect := True;
            While Result And IsIncorrect Do
            Begin
                Try
                    Read(InFile, Matrix[I][J]);
                    IsIncorrect := False;
                Except
                    Writeln('Invalid type! Try again.');
                    Result := False;
                End;
            End;
        End;
    End;
End;

Function IsAnotherFile(): Boolean;
Var
    IsCorrect: Boolean;
    Choice: String;
Begin
    IsCorrect := False;
    Choice := '';
    Writeln('Read error was detected in your file.', #13#10, 'This program can',
        #39, 't continue to read this file.');
    Repeat
        Writeln('Do you want to change file?(yes/no)');
        Readln(Choice);
        If Choice = 'yes' Then
        Begin
            IsCorrect := True;
            Result := True;
        End
        Else If Choice = 'no' Then
        Begin
            IsCorrect := True;
            Result := False;
        End
        Else
            Writeln('You input incorrect word! Try again.');
    Until IsCorrect;
End;

Function FileInput(Var Matrix: MatrixSize; Var N: Integer): Boolean;
Var
    FileName: String;
    InFile: TextFile;
    IsCorrect: Boolean;
Begin
    FileName := '';
    IsCorrect := False;
    Repeat
        FileName := InputReadFileName();
        AssignFile(InFile, FileName);
        Reset(InFile);
        If InputSizeOfMatrixFromFile(InFile, N) And
            InputElementsOfMatrixFromFile(InFile, Matrix, N) Then
        Begin
            IsCorrect := True;
            Result := True;
        End
        Else If (Not IsAnotherFile()) Then
        Begin
            IsCorrect := True;
            Result := False;
        End
        Else
            CloseFile(InFile);
    Until IsCorrect;
    CloseFile(InFile);
End;

Function FindBestSum(Var Matrix: MatrixSize; Const N: Integer): Real;
Var
    BestSum: Real;
    I: Integer;
    J: Integer;
Begin
    For I := 0 To N Do
    Begin
        For J := 0 To N Do
        Begin
            If (J < N) And ((Matrix[I][J] + Matrix[I][J + 1]) > BestSum) Then
                BestSum := Matrix[I][J] + Matrix[I][J + 1];
            If (I < N) And ((Matrix[I][J] + Matrix[I + 1][J]) > BestSum) Then
                BestSum := Matrix[I][J] + Matrix[I + 1][J];
        End;
    End;
    Result := BestSum;
End;

Function OutputMethod(): Boolean;
Var
    IsCorrect: Boolean;
    Choice: String;
Begin
    IsCorrect := False;
    Choice := '';
    Writeln('The program works with console output or files.');
    Repeat
        IsCorrect := False;
        Writeln('To use console enter ', #39, 'console', #39, '.', #13#10,
            'To use a file enter ', #39, 'file', #39, '.'#13#10,
            'Enter what type you want to use: ');
        Readln(Choice);
        If Choice = 'console' Then
        Begin
            IsCorrect := True;
            Result := True;
        End
        Else If Choice = 'file' Then
        Begin
            IsCorrect := True;
            Result := False;
        End
        Else
            Writeln('The word ', Choice, ' don', #39,
                't match any of method to output the data.');
    Until IsCorrect;
End;

Procedure OutputConsole(Const Answer: Real);
Begin
    Writeln('The answer is ', Answer:6:3, '.');
End;

Procedure OutputFile(Const Answer: Real);
Var
    FileName: String;
    OutFile: TextFile;
Begin
    FileName := InputWriteFileName();
    Assign(OutFile, FileName);
    Rewrite(OutFile);
    Writeln(OutFile, 'The answer is ', Answer:6:3, '.');
    CloseFile(OutFile);
End;

Procedure Main();
Var
    N: Integer;
    Answer: Real;
    Matrix: MatrixSize;
Begin
    N := 0;
    Answer := 0.0;
    If InputMethod() Then
    Begin
        ConsoleInput(Matrix, N);
        Answer := FindBestSum(Matrix, N);
        If OutputMethod() Then
            OutputConsole(Answer)
        Else
            OutputFile(Answer);
    End
    Else If FileInput(Matrix, N) Then
    Begin
        Answer := FindBestSum(Matrix, N);
        If OutputMethod() Then
            OutputConsole(Answer)
        Else
            OutputFile(Answer);
    End;
    Free(Matrix);
End;

Begin
    Main();
    // freeze console
    Writeln('Press enter to exit...');
    Readln;
End.

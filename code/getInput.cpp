#include <bits/stdc++.h>
using namespace std;

#define N 16
#define Q 8

float decode(string a)
{
   int size = a.size();
   int bits_size = N;
   int fraction_size = Q;
   float result = 0;
   char sign_bit = a[0];
   if (size != bits_size)
   {
      cout << "ERROR: Invalid input";
      return (float)0;
   }
   string interger = a.substr(1, bits_size - fraction_size - 1);
   string fraction = a.substr(bits_size - fraction_size);
   for (int i = 0; i < interger.size(); i++)
      if (interger[i] == '1')
         result += pow(2, interger.size() - i - 1);

   for (int i = -1; i >= 0 - fraction.size(); i--)
   {
      if (fraction[-i - 1] == '1')
         result += pow(2, i);
   }
   if (a[0] == '0')
      return result;
   else if (a[0] == '1')
      return result - pow(2, (bits_size - fraction_size - 1));
   else
   {

      cout << "ERROR: Invalid input" << endl;
      return (float)0;
   }
}

string ***getInput(string filePath)
{
   string ***input = new string **[3];
   string **h_matrix = 0;
   string **n_matrix = 0;
   string **y_matrix = 0;
   h_matrix = new string *[4];
   n_matrix = new string *[4];
   y_matrix = new string *[4];

   ifstream file(filePath.c_str());

   for (int i = 0; i < 4; i++)
   {
      h_matrix[i] = new string[4];
      for (int j = 0; j < 4; j++)
      {
         getline(file, h_matrix[i][j]);
         // cout << decode(h_matrix[i][j]) << " ";
      }
      // cout << endl;
   }
   // cout << " y matrix" << endl;
   for (int i = 0; i < 4; i++)
   {
      y_matrix[i] = new string[2];
      for (int j = 0; j < 2; j++)
      {
         getline(file, y_matrix[i][j]);
         // cout << decode(y_matrix[i][j]) << " ";
      }
      // cout << endl;
   }
   // cout << " n matrix" << endl;
   for (int i = 0; i < 4; i++)
   {
      n_matrix[i] = new string[2];
      for (int j = 0; j < 2; j++)
      {
         getline(file, n_matrix[i][j]);
         // cout << decode(n_matrix[i][j]) << " ";
      }
      // cout << endl;
   }
   file.close();
   input[0] = h_matrix;
   input[1] = y_matrix;
   input[2] = n_matrix;
   return input;
}

float **decodeMatrix(string **m, int row)
{
   float **matrix = 0;
   matrix = new float *[4];
   for (int i = 0; i < 4; i++)
   {
      matrix[i] = new float[row];
      for (int j = 0; j < row; j++)
         matrix[i][j] = decode(m[i][j]);
   }
   return matrix;
}

void add(float **a, float **b)
{
   float sum[4][4];
   for (int i = 0; i < 4; i++)
      for (int j = 0; j < 2; j++)
         sum[i][j] = a[i][j] + b[i][j];

   cout << sum[0][0];
}

main()
{
   string ***input = getInput("input.txt");
   float **h_matrix = decodeMatrix(input[0], 4);
   float **y_matrix = decodeMatrix(input[1], 2);
   float **n_matrix = decodeMatrix(input[2], 2);
   add(y_matrix, n_matrix);
   // cout << h_matrix[1][1];
}
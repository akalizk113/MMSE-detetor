#include <bits/stdc++.h>
#define BITS_OF_FRACTION 8
#define BITS_OF_INTEGER 8
using namespace std;

#define N 16
#define Q 8
#define PI 3.141592653589793
string encode(float num)
{
    int h_int = BITS_OF_INTEGER, k_prec = BITS_OF_FRACTION;
    string binary = "";

    // Fetch the integral part of decimal number
    int Integral = num;

    // Fetch the fractional part decimal number
    float fractional = abs(num - Integral);

    // Conversion of integral part to
    // binary equivalent
    if (Integral < 0)
        Integral = Integral + pow(2, h_int - 1);

    while (Integral)
    {
        int rem = Integral % 2;

        // Append 0 in binary
        binary.push_back(rem + '0');

        Integral /= 2;
    }
    int size = binary.size();
    if (binary.size() > h_int - 1)
        return "Can not convert this number to a binary representation";
    else
        for (int i = 0; i < h_int - 1 - size; i++)
            binary.push_back('0');
    if (num < 0)
        binary.push_back('1');
    else
        binary.push_back('0');
    // Reverse string to get original binary
    // equivalent
    reverse(binary.begin(), binary.end());

    // Append point before conversion of
    // fractional part
    // binary.push_back('.');

    // Conversion of fractional part to
    // binary equivalent
    while (k_prec--)
    {
        // Find next bit in fraction
        fractional *= 2;
        int fract_bit = fractional;

        if (fract_bit == 1)
        {
            fractional -= fract_bit;
            binary.push_back(1 + '0');
        }
        else
            binary.push_back(0 + '0');
    }

    return binary;
}
main()
{

    // =============== TEST ==================
    float a = 1;
    float b = -1;
    float ar[8];
    float br[8];
    float cr[8];
    string result = "1111001100000000";
    string a_dec = encode(a);
    string b_dec = encode(b);
    cout << "a = " << a_dec << endl;
    cout << "b = " << b_dec << endl;
    // 1111111100000000 ---- (-1)
    // 1111111000000000 ---- (-2)
    // 1111110100000000 ---- (-3)
    // 1111101100000000 ---- (-5)
    int n = 255;
    string s = "fixedpoint.txt";
    ofstream fixedpoint("input.txt");
    // string s = ("fixedpoint.txt");
    ofstream Decimal("dec.txt");
    int decimalNumber;
    srand((unsigned)time(NULL));
    for (int i = 0; i < 8; i++)
    {

        ar[i] = rand() % (4 - 0 + 1) + 0;
        ar[i] /= 5;
    }
    for (int i = 0; i < 4; i++)
    {
        br[i] = rand() % (4 - 0 + 1) + 0;
        br[i] /= 5;
        cr[i] = rand() % (4 - 0 + 1) + 0;
        cr[i] /= 5;
    }
    for (int i = 0; i < 4; i++)
    {
        cout << br[i] << endl;
        // br[i] /= 7;
        // cr[i] = rand() % (2 - 0 + 1);
        // cr[i] /= 7;
    }
    for (int i = 0; i < 4; i++)
    {
        if ((ar[i] < 1 && ar[i] > 0) || (br[i] < 1 && br[i] > 0) || (cr[i] < 1 && cr[i] > 0))
        {

            br[i] += 1;
            cr[i] += 1;
        }
        if ((ar[i] < 0 && ar[i] > -1) || (br[i] < 0 && br[i] > -1) || (cr[i] < 0 && cr[i] > -1))
        {
            ar[i] -= 1;
            br[i] -= 1;
            cr[i] -= 1;
        }
    }
    float H[4][4];
    float Y[4][4];
    float noise[4][4];
    H[0][0] = H[1][1] = ar[0];
    H[0][1] = -br[0];
    H[1][0] = br[0];
    H[0][2] = H[1][3] = ar[1];
    H[0][3] = -br[1];
    H[1][2] = br[1];
    H[2][0] = H[3][1] = ar[2];
    H[2][1] = -br[2];
    H[3][0] = br[2];
    H[2][2] = H[3][3] = ar[3];
    H[2][3] = -br[3];
    H[3][2] = br[3];
    //--------------------------------//
    Y[0][0] = Y[1][1] = br[0];
    Y[0][1] = -br[1];
    Y[1][0] = br[1];
    Y[2][0] = Y[3][1] = br[2];
    Y[2][1] = -br[3];
    Y[3][0] = br[3];
    //----------------------------//
    noise[0][0] = noise[1][1] = cr[0];
    noise[0][1] = -cr[1];
    noise[1][0] = cr[1];
    noise[0][2] = noise[0][3] = noise[1][2] = noise[1][3] = 0;
    noise[2][0] = noise[3][1] = 0;
    noise[2][1] = 0;
    noise[3][0] = 0;
    noise[2][2] = noise[3][3] = cr[0];
    noise[2][3] = -cr[1];
    noise[3][2] = cr[1];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Decimal << H[i][j] << " ";
            // cout << H[i][j] << endl;
            fixedpoint << encode(H[i][j]) << endl;
        }
        Decimal << endl;
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            Decimal << Y[i][j] << " ";
            fixedpoint << encode(Y[i][j]) << endl;
        }
        Decimal << endl;
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Decimal << noise[i][j] << " ";
            fixedpoint << encode(noise[i][j]) << endl;
        }
        Decimal << endl;
    }
    fixedpoint << encode(noise[3][1]);
    fixedpoint.close();
    Decimal.close();
}

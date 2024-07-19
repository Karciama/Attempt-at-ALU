#include <bitset> //sori, bet neisivaizduoju kaip sukurt dekoderis, kaip suprast ir pritaikyt registrai ir kaip teisingai sukurt sudetis ir daugyba
#include <iostream>
#include <string>
using namespace std;
bitset<8> A;
bitset<8> B;
bool carry = 0;
bool sum = 0;
bool carryin = 0;
bool carryout = 0;
bitset<8> NAND(bitset <8> A, bitset <8> B) { //jei teisingai supratau
    bitset <8> temp;
    for (int i = 0; i < 8; ++i) {
        if (A[i] == 0 && B[i] == 0)
            temp[i] = 1;
        else if (A[i] == 0 && B[i] == 1)
            temp[i] = 1;
        else if (A[i] == 1 && B[i] == 0)
            temp[i] = 1;
        else if (A[i] == 1 && B[i] == 1)
            temp[i] = 0;
    }return temp;
}
bitset<8> NOT(bitset <8> A) {
    bitset <8> temp;
    for (int i = 0; i <8; ++i) {
        temp = NAND(A, A);
    }
    return temp;
}
bitset<8> AND(bitset <8> A, bitset <8> B) {
    bitset <8> temp;
    for (int i = 0; i <8; ++i) {
        temp = NAND(NAND(A, B), NAND(A, B));
    }
    return temp;
}
bitset<8> OR(bitset <8> A, bitset <8> B) {
    bitset <8> temp;
    for (int i = 0; i <8; ++i) {
        temp = NAND(NAND(A, A), NAND(B, B));
    }return temp;
}
bitset<8> NOR(bitset <8> A, bitset <8> B) {
    bitset <8> temp;
    for (int i = 0; i <8; ++i) {
        temp = NAND(NAND(NAND(A, A), NAND(B, B)), NAND(NAND(A, A), NAND(B, B)));
    }return temp;
}
bitset<8> XOR(bitset <8> A, bitset <8> B) {
    bitset <8> temp;
    for (int i = 0; i < 8; ++i) {
        temp = NAND(NAND(A, NAND(A, B)), NAND(B, NAND(A, B)));
    }return temp;
}
bitset<8> lyguB(bitset <8> A, bitset <8> B) {
    bitset<8> temp;
        temp = NOR(XOR(A, B),B);
    return temp;
}
bitset<8> lygu0(bitset <8> A) {
    bitset <8> zero = 0;
    bitset<8> temp;
    temp = NOR(XOR(A, zero), zero);
    return temp;
}
bitset<8> pliusvienas(bitset<8> A) { 
    for (int i = 0; i < 8; ++i) {
        if (!A[i]) {
            A.flip(i);
            break;
        }
        else {
            A.flip(i);
        }
    }
    return A;
}
bitset<8> ikaire(bitset<8> A) {
    bool c = 0;
    bool mest = 0;
    bitset<8> result;

    for (int i = 0; i < 8; ++i) {
        result[i] = XOR(A, mest)[i];
        mest = AND(A, c)[i];
    }

    return result;
}
bitset<8> inversija(bitset <8> A) {
    return pliusvienas(NOT(A));
}
void halfadder(bitset<8> A, bitset<8> B, bool &carry, bool &sum) {
        carry = AND(A, B).any();
        sum = XOR(A, B).any();
}
void fulladder(bitset<8> A, bitset<8> B, bool carryin, bool &carryout, bool &sum) {
    bool carryvienas, carrydu, sum1, sum2;
    halfadder(A, B, carryvienas, sum1);
    halfadder(sum1, carryin, carrydu, sum2);
    carryout = OR(carryvienas, carrydu)[0];
    sum = sum2;
}
void adder(bitset<8> A, bitset<8> B, bool carryin, bool carryout, bitset<8>& rez) {
    bool carry, sum;
    for (int i = 0; i < 8; ++i) {
        fulladder(A, B, carryin, carry, sum);
        carryin = carry;
        rez[i] = sum;
    }
    carryout = carry;
}
int main()
{
    bitset<8> rez;
    cin >> A >> B;
    adder(A, B, carryin, carryout, rez);
    cout << "Inversija: " << inversija(A) << endl << "Sudetis: "<<rez << endl << "Daugyba: labai nera\n" << "Poslinkis i kaire: " << ikaire(A) << endl << "Plius vienas: " << pliusvienas(A) << endl << "Prilyginimas nuliui: " << lygu0(A) << endl << "Prilyginimas B: "<< lyguB(A,B);
}


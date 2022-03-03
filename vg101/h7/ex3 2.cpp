#include "assignment.h"
#include <iostream>
#include <fstream>
using namespace std;

void ex3()
{
    ifstream readFile("matrices.txt");
    char m[10000], m_a[10000], m_b[10000];
    char temp;
    int iline = 0;
    for (int i = 0;; i++)
    {
        m[i] = temp;
        if (temp == '\n')
            iline++;
        temp = readFile.get();
        if (temp == EOF)
            break;
    }
    readFile.close();

    ofstream writeFile("result.txt");
    int isteps = iline / 2;
    int ilength = (isteps * isteps) * 2 - 2;

    for (int i = 0; i <= ilength; i++)
    {
        m_a[i] = m[i];
        m_b[i] = m[ilength + i];
    }

    //sum
    char m_sum[10000];
    for (int i = 0; i <= ilength; i++)
    {
        m_sum[i] = m_a[i] + m_b[i];
        cout <<(int) m_a[i];
    }

    /* //multiply
    char m_multiply[10000];
    for (int i = 0; i <= ilength; i++)
    {
        m_multiply[i]=m_a[i]*m_b[i];
        writeFile<< m_multiply[i];
    } 
    //T
    char m_T[10000];
    for (int i = 0; i <= ilength; i++)
    {
        m_T[i]=m_a[i]+m_b[i];
        writeFile<< m_T[i];
    }*/
    writeFile.close();
}
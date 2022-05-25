#pragma once
#ifndef HUFFMANCODE_H
#define HUFFMANCODE_H
#include <iostream>
#include <fstream>
#include <iomanip> 
#include<cstdlib>
#include <QProgressBar>  


struct myst {
    int key;
    unsigned char value;
    int len;
};
struct myencode {
    unsigned char e;
    char* code;
};
void Heap(int* a, int i, const int n);
void Heapmin(int* a, const int n);
void HuffmanTree(int* a, int n);
class TreeNode {
    friend class Huffmancode;
public:
    TreeNode(int k = 0, unsigned char v = 0, TreeNode* l = 0, TreeNode* r = 0, bool b = 1);
    void getkey();


private:
    int key;
    bool Node;
    unsigned char value;
    TreeNode* leftchild;
    TreeNode* rightchild;
    char encode[100];
};
class Huffmancode {
public:
    Huffmancode(myst* m, int n);
    void Heap(int n);
    void Heapify(int i, int n);
    void Encode();
    void Encode1(myencode*);  //1
    void Encode1(TreeNode*, myencode*); //2
    void TEST();
    void TEST(TreeNode*);
private:
    TreeNode** Tree;
    int num;
    int num2;
    int num3;
    TreeNode* first;

};
bool search(unsigned char c, myst* mm, int s);
void computekv(unsigned char*& h, myst*& m, int& n, int& ss, FILE* f);
void Merge(myencode* t, myencode* dst, int r, int s, int n);
void MergePass(myencode* src, myencode* dst, int n, int s);
void Mergesort(myencode* a, int n);
void Merge(myst* t, myst* dst, int r, int s, int n);
void MergePass(myst* src, myst* dst, int n, int s);
void Mergesort(myst* a, int n);
char* searchencode(myencode* t, int n, unsigned char ele);
void compressfile(int n_file, unsigned char* bincon, myencode* encodetable, int encodenum, FILE* fo,QProgressBar* p,float &cr);
int searchdecode(int num, myencode* table, char* c);
char* transb(unsigned char a, char* c);
void cptwofile(FILE* f1, FILE* f2);
void decodefile(int num_e, int num_d, myencode* table, FILE* fencode, FILE* fdecode,QProgressBar* p);
void encodetable(FILE* ft, myencode* o, int sindex, int num_cont);
void compress(FILE* f, FILE* fo,QProgressBar *p,float &cr);
char* transb2(int n, unsigned char a, char* c);
void decode(FILE* fe, FILE* fd,QProgressBar* p);















#endif // !HUFFMANCODE_H

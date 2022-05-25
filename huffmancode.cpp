// Project6.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#include "huffmancode.h"

using namespace std;    

void Heap(int* a, int i, const int n) {
    int t = a[i];
    int j = i*2;
    while (j <= n) {
        if (a[j] > a[j + 1] && j < n)j++;
        if (a[j] > t) break;
        a[j / 2] = a[j];
        j *= 2;
    }
    a[j / 2] = t;

}
void Heapmin(int* a, const int n) {
    for (int i = n / 2; i >= 1; i--) {

        Heap(a, i, n);
    }
}
void HuffmanTree(int* a, int n) {
    int m1, m2;
    for (int i = n; i >1; i--) {
        Heapmin(a, i);
        cout << a[1]<<"\t";
        m1 = a[1];
        a[1] = a[i];
        Heapmin(a, i - 1);
        m2 = a[1];
        cout << a[1]<<"\n";
        a[1] = m1 + m2;


    }

}


TreeNode::TreeNode(int k, unsigned char v, TreeNode* l, TreeNode* r,bool b)  {
    key = k;
    value = v;
    leftchild = l;
    rightchild = r;
    Node = b;
    strcpy_s(encode, "");
};

void TreeNode::getkey() {
    cout << key << endl;
}


Huffmancode::Huffmancode(myst* m, int n) {
    
    Tree = new TreeNode*[n+1];
    for (int i = 1; i < n+1; i++) {
       
        Tree[i] = new TreeNode(m[i-1].key, m[i-1].value);
        
    }
    first = 0;
    num = n;
    num2 = 0;
    num3 = 0;

}
void Huffmancode::Heapify(int i,int n) {
    TreeNode* temp = Tree[i];
    int j = 2 * i;
    while (j <= n) {
        if (j<n && Tree[j]->key>Tree[j + 1]->key)j++;
        if (Tree[j]->key >= temp->key)break;
        Tree[j / 2] = Tree[j];
        j *= 2;
    }
    Tree[j / 2] = temp;

}
void Huffmancode::Heap(int n) {
    for (int i = n / 2; i >= 1; i--) {
        Heapify(i,n);
    }
   
}
void Huffmancode::Encode() {
    int n = num;
    TreeNode* temp1;
    TreeNode* add;

    unsigned char temp2;
    while (n > 1) {

        Heap(n);
        
       
        temp1 = Tree[1];
        Tree[1] = Tree[n];
        Tree[n] = temp1;
        

        Heap(n - 1);

        
        if (temp1->value < Tree[1]->value) {
            temp2 = temp1->value;
        }
        else {
            temp2 = Tree[1]->value;
        }
        if (temp1->key == Tree[1]->key) {
            if (temp1->value > Tree[1]->value) {
                add= new TreeNode(temp1->key + Tree[1]->key, temp2, Tree[1],temp1, 0);
            }
            else {
                add = new TreeNode(temp1->key + Tree[1]->key, temp2, temp1, Tree[1], 0);
            }
        }
        else {
            add = new TreeNode(temp1->key + Tree[1]->key, temp2, temp1, Tree[1], 0);
        }
        Tree[1] = add;
        
        n -= 1;
        if (n == 1) {
            first = Tree[1];
        }
    }
}
void Huffmancode::TEST() {
    TEST(first);
}
void Huffmancode::TEST(TreeNode* current) {
    
    printf("%d", first->value);
        if (current->leftchild) {
            cout << "left\n";

    }
        
     
}
void Huffmancode::Encode1(myencode*out) {
    Encode1(first,out);
}
void Huffmancode::Encode1(TreeNode* current,myencode* out) {
    
    if (current->leftchild) {
        strcat_s(current->leftchild->encode,current->encode);
        strcat_s(current->leftchild->encode, "0");
        int s1=0;
        int on1 = 0;
        
        
        
        if (current->leftchild->Node) {
            
            while (current->leftchild->encode[s1]) {

               //cout << current->leftchild->encode[s1];
                s1++;
            }
            
            
            char* temp1= new char[s1+1];
            for (int i = 0; i < s1; i++) {
                temp1[i] = current->leftchild->encode[i];
            }
            temp1[s1] = '\0';
            out[num2].code = temp1;
            out[num2].e = current->leftchild->value;
            printf("%2X %s\n", out[num2].e, out[num2].code);
            //printf("  %2X %d %d \n", out[num2].value,out[num2].len,out[num2].key);
            //printf("%2X:", current->leftchild->value); cout<<"\t" << current->leftchild->encode << endl;
            num2++;
        }
        Encode1(current->leftchild,out);
    }
    if (current->rightchild) {
        int s2=0;
        int on2 = 0;
        strcat_s(current->rightchild->encode, current->encode);
        strcat_s(current->rightchild->encode, "1");
        
        if (current->rightchild->Node) {
           
            while (current->rightchild->encode[s2]) {
                //cout << current->rightchild->encode[s2] ;
                s2++;
            }
            char* temp2 = new char[s2 + 1];
            for (int i = 0; i < s2; i++) {
                temp2[i] = current->rightchild->encode[i];
            }
            temp2[s2] = '\0';

           
            out[num2].code = temp2;
            out[num2].e = current->rightchild->value;
            
            printf("%2X %s\n", out[num2].e, out[num2].code);
            //printf("%2X:",current->rightchild->value);cout << "\t" << current->rightchild->encode << endl;
            num2++;
        }
        Encode1(current->rightchild,out);
    }
    else if (current->value) {

    }
    
}


bool search(unsigned char c, myst* mm, int s) {
    for (int i = 0; i < s; i++) {
        if (mm[i].value == c) {
            mm[i].key += 1;
            return true;
        }
    }
    return false;
}


    void computekv(unsigned char *& h,myst*& m,int &n, int& ss, FILE* f) {
        unsigned char ch;
        int size = 100;
        int size1 = 1000;
        while (fread(&ch, sizeof(char), 1, f)) {
            
            if (n < size1) {
                h[n] = ch;
                n++;
            }
            else {
                
                h = (unsigned char*)realloc(h,size1 + 1000);
                size1 += 100;
                h[n] = ch;
                n++;
            }
            
            //printf("%2X \t", ch);
            if (ss < size) {
                
                if (search(ch, m, ss)) {


                }
                else {
                    m[ss].key = 1;

                    m[ss].value = ch;

                    ss++;
                };
            }
            else {
               m=(myst*)realloc(m, sizeof(myst) * (size + 100));

                size += 100;

                if (search(ch, m, ss)) {}
                else {
                    m[ss].key = 1;
                    m[ss].value = ch;
                    ss++;
                };
            };


        }
    }
    void Merge(myencode* t,myencode* dst, int r, int s, int n) {
        
        int left = r;
        int right = r + s;
        
        
        for (int i = r; i < n; i++) {
            if (right < n && t[left].e <= t[right].e && (left < (s+r))) {
                dst[i] = t[left];
                left++;
                

            }
            else if (t[right].e < t[left].e && (right < n) && left <(s+r)) {
                dst[i] = t[right];
                right++;
               
            }
            else if (right >= n) {
                dst[i] = t[left];
                left++;
                
            }
            else {
                dst[i] = t[right];
                right++;
                
            }
        }
       
    }
    void MergePass(myencode* src, myencode* dst, int n, int s) {
        int i = 0;
        
        while (i <= (n - 2 * s + 1)) {

            Merge(src, dst, i, s, i + 2 * s);
            i += 2 * s;
        }
        
        
        if (i < (n - s + 1)) {
            Merge(src, dst, i, s, n + 1);
        }
        else {
            memcpy(dst + i, src + i, sizeof(myencode) * (n - i + 1));
        }

    }
    void Mergesort(myencode* a, int n) {
        myencode* temp = (myencode*)malloc(sizeof(myencode) * (n + 1));
        
        for (int s = 1; s < (n + 1);s*=2) {
            
            MergePass(a, temp, n, s);
            s *= 2;
            MergePass(temp, a, n, s);

        }
        free(temp);

    }
    void Merge(myst* t, myst* dst, int r, int s, int n) {

        int left = r;
        int right = r + s;


        for (int i = r; i < n; i++) {
            if (right < n && t[left].value <= t[right].value && (left < (s + r))) {
                dst[i] = t[left];
                left++;


            }
            else if (t[right].value < t[left].value && (right < n) && left < (s + r)) {
                dst[i] = t[right];
                right++;

            }
            else if (right >= n) {
                dst[i] = t[left];
                left++;

            }
            else {
                dst[i] = t[right];
                right++;

            }
        }

    }
    void MergePass(myst* src, myst* dst, int n, int s) {
        int i = 0;

        while (i <= (n - 2 * s + 1)) {

            Merge(src, dst, i, s, i + 2 * s);
            i += 2 * s;
        }


        if (i < (n - s + 1)) {
            Merge(src, dst, i, s, n + 1);
        }
        else {
            memcpy(dst + i, src + i, sizeof(myst) * (n - i + 1));
        }

    }
    void Mergesort(myst* a, int n) {
        myst* temp = (myst*)malloc(sizeof(myst) * (n + 1));

        for (int s = 1; s < (n + 1); s *= 2) {

            MergePass(a, temp, n, s);
            s *= 2;
            MergePass(temp, a, n, s);

        }
        free(temp);

    }
    char* searchencode(myencode* t, int n,unsigned char ele) {
        int right = n;
        int left = 0;
        unsigned char bench = t[(right+left)/2].e;
        while (bench != ele) {
            
            if (bench > ele) {
                right = (right + left) / 2;

                bench = t[(left + right) / 2].e;
                
            }
            else {
                left = (right + left) / 2;
                bench = t[(left + right) / 2].e;
            }
        }
        return t[(right + left) / 2].code;
    }
    void compressfile(int n_file, unsigned char* bincon, myencode* encodetable, int encodenum,FILE* fo,QProgressBar *p,float &cr) {
        char* code;
        int codelen;
        unsigned char transformbyte;
        unsigned char byte;
        int bit = 0;
        int count = 0;
        char temp[100];

        
        for (int i = 0; i < n_file; i++) {

            if (i % 300 == 0) {
            p->setValue(i);
        }
            byte = bincon[i];
            
            
            code = searchencode(encodetable, encodenum, byte);
          
            codelen = (int)strlen(code) ;
            
            
            memcpy(temp + bit, code, codelen);
            
            
            bit += codelen;
            
            temp[bit] = '\0';
            
            while (bit >= 8) {
                transformbyte = 0;
                for (int j = 0; j < 8; j++) {
                    if (temp[j] == '1') {
                        transformbyte += (int)pow(2, 7 - j);
                    }
                }
                fwrite(&transformbyte, sizeof(unsigned char), 1, fo);
                count++;
                memcpy(temp, temp + 8, bit - 8+1);
                
             
                bit -= 8;
                
                
            }
            
        }
      
        if (bit > 0) {
            transformbyte = 0;
            for (int k = 0; k < bit; k++) {
                if (temp[k] == '1') {
                    transformbyte += (int)pow(2, 7 - k);
                }
            
            }
            fwrite(&transformbyte, sizeof(unsigned char), 1, fo);
            count++;
           

        }
       
        float compres_ratio = (float)count/(float)n_file;
       
        cr = 1 - compres_ratio;
        p->setValue(n_file);
        
        
            
   

    }
    
    int searchdecode(int num, myencode* table, char* c) {
        
        int k,cl;
        k = int(strlen(c));
        for (int i = 0; i < num; i++) {
            cl = (int)strlen(table[i].code);
            
            if ((cl == k)&&strcmp(table[i].code,c)==0) {
                
                return i;

            }
        }
        return -1; 

    }
    char* transb(unsigned char a,char* c) {
        
        for (int i = 7; i >= 0; i--) {
            if (a >= pow(2, i)) {
                c[7 - i] = '1';
                a -= (int)pow(2, i);

            }
            else {
                c[7 - i] = '0';
            }

        
        }
        return c;
    }
    void cptwofile(FILE* f1, FILE* f2) {
        
        unsigned char ch1, ch2;
        while (fread(&ch1, sizeof(char), 1, f1)) {
            fread(&ch2, sizeof(char), 1, f2);
            printf("f1:%2X f2:%2X \n", ch1, ch2);
        }
    }
    
    void decodefile(int num_e, int num_d, myencode* table, FILE* fencode, FILE* fdecode,QProgressBar *p) {
        int i = 0;
        int n1=0;
        int index;
        int count = 0;
        char temp2[200];
        int critnum = 150;
        
        unsigned char ch;
        
        
        p->setRange(0, num_d);
            while (fread( & ch, sizeof(char), 1, fencode)) {
                char* temp1=new char[8];
                //fread(&ch, sizeof(unsigned char), 1, fencode);
               
                
                temp1 = transb(ch,temp1);
                
                 memcpy(temp2 + n1, temp1, 8);
                 delete[]temp1;
                 n1 += 8;
                 temp2[n1] = '\0';                
                 //printf("%s ", temp2);

         
                 if (n1 < critnum) {
                     for (int j = 0; j < n1; j++) {
                         char* temp3 = new char[j + 2];
                         memcpy(temp3, temp2, j + 1);
                         temp3[j + 1] = '\0';

                         index = searchdecode(num_e, table, temp3);
                         delete[] temp3;
                         if (index >= 0) {
                             fwrite(&table[index].e, sizeof(char), 1, fdecode);
                             //  printf("%2X %2X \n", table[index].e);
                             if (i % 100 == 0) {
                                 p->setValue(i);
                             }
                             i++;
                             //printf("%d \n", i);


                             memcpy(temp2, temp2 + j + 1, n1 - (j + 1) + 1);
                             n1 -= (j + 1);
                            
                             break;
                         }
                     }
                 }
                 else {
                     while (n1 > 10) {
                         for (int j = 0; j < n1; j++) {
                             char* temp3 = new char[j + 2];
                             memcpy(temp3, temp2, j + 1);
                             temp3[j + 1] = '\0';

                             index = searchdecode(num_e, table, temp3);
                             delete[] temp3;
                             if (index >= 0) {
                                 fwrite(&table[index].e, sizeof(char), 1, fdecode);
                                 //  printf("%2X %2X \n", table[index].e);
                                 if (i % 100 == 0) {
                                     p->setValue(i);
                                 }
                          
                                 i++;
                                 //printf("%d \n", i);


                                 memcpy(temp2, temp2 + j + 1, n1 - (j + 1) + 1);
                                 n1 -= (j + 1);
                                
                                 break;
                             }
                         }

                     }
                 }
                
            }
            while (n1 > 0 && i < num_d) {
                for (int j = 0; j < n1; j++) {
                    char* temp3 = new char[j + 2];
                    memcpy(temp3, temp2, j + 1);
                    temp3[j + 1] = '\0';
                    index = searchdecode(num_e, table, temp3);
                    delete[] temp3;
                    if (index >= 0) {
                        fwrite(&table[index].e, sizeof(char), 1, fdecode);
                        if (i % 100 == 0) {
                            p->setValue(i);
                        }
                        i++;
                       // printf("%2X %2X \n", table[index].e, cont[i]);

                        memcpy(temp2, temp2 + j + 1, n1 - (j + 1) + 1);
                        n1 -= (j + 1);
                    }
                }

            }
            p->setValue(i++);
            

        
     
    }
    void encodetable(FILE* ft, myencode* o,int sindex,int num_cont) {
        unsigned char ch;
        unsigned char len;
        int code0 =num_cont ;
        fwrite(&code0, sizeof(int), 1, ft);
        unsigned char num_code = sindex;
        printf("%d 4444\n", code0);
        fwrite(&num_code, sizeof(unsigned char), 1, ft);
        for (int i = 0; i < sindex; i++) {
            ch = o[i].e;
            
            len = (int)strlen(o[i].code);
            fwrite(&ch, sizeof(unsigned char), 1, ft);
            fwrite(&len, sizeof(unsigned char), 1, ft);
            cout << o[i].code << endl;
            if (len > 8) {
                unsigned char code1 = 0;
                    unsigned char code2=0;
                for (int j = 0; j < 8; j++) {
                    if (o[i].code[j] == '1') {
                        code1 += (int)pow(2, 7 - j);
                    }
                    
                }
                for (int k = 8; k < len; k++) {
                    if (o[i].code[k] == '1') {
                        code2 += (int)pow(2, len - 1 - k);
                    }
                   
                }
                fwrite(&code1, sizeof(unsigned char), 1, ft);
                fwrite(&code2, sizeof(unsigned char), 1, ft);
                
            }
            else {
                unsigned char code1 = 0;
                for (int j = 0; j < len; j++) {
                    if (o[i].code[j] == '1') {
                        code1 += (int)pow(2, len - 1 - j);
                    }
                }
                printf("%d \n", code1);
                fwrite(&code1, sizeof(unsigned char), 1, ft);
            }
            
        }
     
    }
    void compress(FILE* f,FILE *fo, QProgressBar* p,float &cr) {
        unsigned char* binaryfile = (unsigned char*)malloc(1000);
        int sindex = 0;
        int n_file = 0;
        myst* tt = (myst*)malloc(sizeof(myst) * 100);
        computekv(binaryfile, tt, n_file, sindex, f);
        Mergesort(tt, sindex - 1);
        
        myencode* output = (myencode*)malloc(sizeof(myencode) * sindex);
       
        Huffmancode a = Huffmancode(tt, sindex);
        a.Encode();
        a.Encode1(output);
        p->setRange(0, n_file);
        Mergesort(output, sindex - 1);
        encodetable(fo, output,sindex,n_file);
        compressfile(n_file, binaryfile, output, sindex, fo,p,cr); //binaryfile 原始檔案  output 是轉換表
        
        free(output);

        free(binaryfile);
        
        free(tt);
        fclose(f);
        fclose(fo);
        //fclose(ft);
    }
    char* transb2(int n,unsigned char a, char* c) {

        for (int i = n-1; i >= 0; i--) {
           
            if (a >= pow(2, i)) {
                c[(n-1) - i] = '1';
                a -= (int)pow(2, i);

            }
            else {
                c[(n-1)- i] = '0';
            }


        }
        return c;
    }
    void decode(FILE* fe,FILE* fd,QProgressBar *p) {
        int num_f;
        fread(&num_f, sizeof(int), 1, fe);
        unsigned char ch;
        unsigned char num_code;
        unsigned char code_len;
        unsigned char code1;
        fread(&num_code, sizeof(char), 1, fe);
        
        
        myencode* table = (myencode*)malloc(sizeof(myencode) * num_code);
  
        for (int i = 0; i < num_code; i++) {
            
            fread(&ch, sizeof(char), 1, fe);
            table[i].e = ch;
            
            fread(&code_len, sizeof(char), 1, fe);
            
            fread(&code1, sizeof(char), 1, fe);
           
            if (code_len <= 8) {
                char* c = (char*)malloc(sizeof(char) * (code_len+1));
                transb2(code_len, code1, c);
                c[code_len] = '\0';
                table[i].code = c;
                
            }
            else {
                unsigned char code2;
                fread(&code2, sizeof(char), 1, fe);
                char* c1 = (char*)malloc(sizeof(char) * 8);
                char* c2 = (char*)malloc(sizeof(char) * (code_len - 8 + 1));
                char* cat = (char*)malloc(sizeof(char) * (code_len + 1));
                transb2(8, code1,c1);
                transb2(code_len - 8, code2, c2);
                c2[code_len - 8] = '\0';
                memcpy(cat, c1, 8);
                memcpy(cat + 8, c2, (code_len - 8 + 1));
                table[i].code = cat;
                free(c1);
                free(c2);
                //free(cat);
                

                

            }
            
        }
        decodefile(num_code, num_f,table, fe,fd,p);

        fclose(fe);
        fclose(fd);

    }


// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案

/* Chris Long */
/* Version 0.3 */
/* Elimitates need for pre[], reducing assignments */
/* Version 0.2 */
/* Now uses the array pre[] to retain information previously computed,
   which reduces the number of assignment statements, and also  */
/* Version 0.1 */
/* Now uses the array k[][] to retain information previously computed,
   which reduces the number of binary search probes */

#include <stdio.h>
#include <string.h>

/* Adjust the following to fit your needs.  (word_count) should be the
   number of words in your word list + 1 */

#define word_count (97187)
/* #define word_count (269) */
#define length     (9)

typedef enum       {FALSE,TRUE} boolean;
typedef long       listing_type[word_count][length][2];
typedef char       our_string[length+1];
typedef char       num_string[length];
typedef our_string word_list_type[word_count];
typedef num_string num_list_type[word_count];

/* These are all loop control variables */

long x, y, z, zz;

/* The number of squares found so far */

long total_answers;

/* This LISTING contains information pertaining to which words start
   with which letters */

listing_type listing;

/* This is our LIST of (length)-letter WORDs */

word_list_type word_list;
num_list_type num_list;

long w1,w2,w3,w4,w5,w6,w7,w8,w9;
long b2,b3,b4,b5,b6,b7,b8,b9;
long e2,e3,e4,e5,e6,e7,e8,e9;
long k[9][9];

long m;

FILE *answer_file, *status_file;

long check1[26];
long check2[26][26];
long check3[26][26][26];
long check4[26][26][26][26];

long f_check[word_count][5];

long b_mask[26];

boolean d_error;

void in_list(c_char, first, last, n)

/* Returns TRUE iff the first n+1 letters of C_STRING start a word in
   the word list between words in positions (first) and (last), inclusive.
   This is a simple, but effective, binary search. */

/* N (+1) is the number of letters to check */

char c_char;
int n;
long first, last;

{

/* L ower
   U pper */

   long l, u;
   int p;

   l = first;
   u = last;
   while (l <= u)
   { m = (l + u) >> 1;
     if (c_char > num_list[m][n])
       l = m + 1;
     else if (c_char < num_list[m][n])
       u = m - 1;
     else
       return;
     }
  printf("%s\n","FALSE");
  d_error=TRUE;
  return;
  
}

int main()

{

  total_answers = 0;
  
  for (x = 0; x <= 25; ++x)
    check1[x] = 0;

  for (x = 0; x <= 25; ++x)
  for (y = 0; y <= 25; ++y)
    check2[x][y] = 0;

  for (x = 0; x <= 25; ++x)
  for (y = 0; y <= 25; ++y)
  for (z = 0; z <= 25; ++z)
    check3[x][y][z] = 0;

  for (x = 0; x <= 25; ++x)
  for (y = 0; y <= 25; ++y)
  for (z = 0; z <= 25; ++z)
  for (zz = 0; zz <= 25; ++zz)
    check4[x][y][z][zz] = 0;

  for (x = 1; x <= word_count-1; ++x)
    { scanf("%s",word_list[x]);
/*      printf("%s\n",word_list[x]); */
      for (y = 0; y <= length-1; ++y)
        { num_list[x][y] = word_list[x][y]-'a'; }
      check1[num_list[x][0]]= x;
      check2[num_list[x][0]][num_list[x][1]]= x;
      check3[num_list[x][0]][num_list[x][1]][num_list[x][2]]= x;
      check4[num_list[x][0]][num_list[x][1]][num_list[x][2]][num_list[x][3]]= x;
    }
    
/*  for (x = 1; x <= word_count-1; ++x)
    { printf("%s\n",word_list[x]); } */

  for (y = 1; y <= length-1; ++y)
    { listing[1][y][0] = 1; }

  for (x = 1; x <= word_count-2; ++x)
    { for (y = 0; y <= length-1; ++y)
        { if (word_list[x][y] != word_list[x+1][y])
            { z = y+1;
              break; }
        }

      for (y = 1; y <= z-1; ++y)
        { listing[x+1][y][0] = listing[x][y][0]; }
   
      for (y = z; y <= length-1; ++y)
        { listing[x+1][y][0] = x + 1; }
   
      for (y = z; y <= length-1; ++y)
        { for (zz = listing[x][y][0]; zz <= x; ++zz)
            { listing[zz][y][1] = x; }
        }
    }

  for (y = 1; y <= length-1; ++y)
    { for (z = listing[word_count-1][y][0]; z <= word_count-1; ++z)
        { listing[z][y][1] = word_count-1; }
    }

  b_mask[0]=1;
  for (x = 1; x <= 25; ++x)
    b_mask[x]=b_mask[x-1]<<1;

  for (x = 0; x <= 4; ++x)
  for (y = 1; y < word_count; ++y)
  { f_check[x][y] = 0; }

  for (x = 0; x <= 4; ++x)
  for (y = 1; y < word_count; ++y)
  { if (!listing[y][x+4][0]==y)
    { f_check[y][x] = f_check[listing[y][x+4][0]][x];
      continue; }
    for (z = listing[y][x+4][0]; z <= listing[y][x+4][1]; ++z)
      f_check[y][x] = (f_check[y][x] | b_mask[num_list[y][x+4]]); }

/* Main search routine */

  d_error=FALSE;
    
  answer_file = fopen("output.9", "w");
  status_file = fopen("status.9", "w");

  for (w1=1; w1<=word_count; ++w1)
  {

    if ((w1%25)==1)
    {
      fprintf(status_file,"%s %d\n",word_list[w1],w1);
      printf("%s %d\n",word_list[w1],w1);
      fflush(status_file);
    }

    if (!(check1[num_list[w1][8]]))
      continue;
    if (!(check1[num_list[w1][7]]))
      continue;
    if (!(check1[num_list[w1][6]]))
      continue;
    if (!(check1[num_list[w1][5]]))
      continue;
    if (!(check1[num_list[w1][4]]))
      continue;
    if (!(check1[num_list[w1][3]]))
      continue;
    if (!(check1[num_list[w1][2]]))
      continue;
    if (!(m = check1[num_list[w1][1]]))
      continue;

   b2 = listing[m][1][0];
  e2 = listing[m][1][1];

  for (w2=b2; w2<=e2; ++w2)
  {

    if (!(check2[num_list[w1][8]][num_list[w2][8]]))
      continue;

    if (!(check2[num_list[w1][7]][num_list[w2][7]]))
      continue;

    if (!(check2[num_list[w1][6]][num_list[w2][6]]))
      continue;

    if (!(check2[num_list[w1][5]][num_list[w2][5]]))
      continue;

    if (!(check2[num_list[w1][4]][num_list[w2][4]]))
      continue;

    if (!(check2[num_list[w1][3]][num_list[w2][3]]))
      continue;

    if (!(m = check2[num_list[w1][2]][num_list[w2][2]]))
      continue;

   b3 = listing[m][2][0];
  e3 = listing[m][2][1];

  for (w3=b3; w3<=e3; ++w3)
  {

    if (!(check3[num_list[w1][8]][num_list[w2][8]][num_list[w3][8]]))
      continue;

    if (!(check3[num_list[w1][7]][num_list[w2][7]][num_list[w3][7]]))
      continue;

    if (!(check3[num_list[w1][6]][num_list[w2][6]][num_list[w3][6]]))
      continue;

    if (!(check3[num_list[w1][5]][num_list[w2][5]][num_list[w3][5]]))
      continue;

    if (!(check3[num_list[w1][4]][num_list[w2][4]][num_list[w3][4]]))
      continue;

    if (!(m = check3[num_list[w1][3]][num_list[w2][3]][num_list[w3][3]]))
      continue;

   b4 = listing[m][3][0];
  e4 = listing[m][3][1];

  for (w4=b4; w4<=e4; ++w4)
  {
    if (!(k[4][8] = check4[num_list[w1][8]][num_list[w2][8]][num_list[w3][8]]
	                  [num_list[w4][8]]))
      continue;
    
    if (!(k[4][7] = check4[num_list[w1][7]][num_list[w2][7]][num_list[w3][7]]
	                  [num_list[w4][7]]))
      continue;

    if (!(k[4][6] = check4[num_list[w1][6]][num_list[w2][6]][num_list[w3][6]]
	                  [num_list[w4][6]]))
      continue;

    if (!(k[4][5] = check4[num_list[w1][5]][num_list[w2][5]][num_list[w3][5]]
	                  [num_list[w4][5]]))
      continue;

    if (!(k[4][4] = check4[num_list[w1][4]][num_list[w2][4]][num_list[w3][4]]
	                  [num_list[w4][4]]))
      continue;

    m = k[4][4];
    
    b5 = listing[m][4][0];
   e5 = listing[m][4][1];

  for (w5=b5; w5<=e5; ++w5)
  {

    if (!(f_check[k[4][8]][0] & b_mask[num_list[w5][8]]))
      continue;

    if (!(f_check[k[4][7]][0] & b_mask[num_list[w5][7]]))
      continue;

    if (!(f_check[k[4][6]][0] & b_mask[num_list[w5][6]]))
      continue;

    if (!(f_check[k[4][5]][0] & b_mask[num_list[w5][5]]))
      continue;

    in_list(num_list[w5][8],listing[k[4][8]][4][0],
	          listing[k[4][8]][4][1],4);
    k[5][8]=m;
    
    if (d_error)
    { printf("%d %d %d\n",w5,5,8);
      printf("%s\n",word_list[w5]);
      printf("%o\n",b_mask[num_list[w5][8]]);
      printf("%o\n",f_check[k[4][8]][0]);
      return 0; }
    
    in_list(num_list[w5][7],listing[k[4][7]][4][0],
	          listing[k[4][7]][4][1],4);
    k[5][7]=m;
    
    if (d_error)
    { printf("%d %d\n",5,7);
      return 0; }

    in_list(num_list[w5][6],listing[k[4][6]][4][0],
	          listing[k[4][6]][4][1],4);
    k[5][6]=m;
    
    if (d_error)
    { printf("%d %d\n",5,6);
      return 0; }

    in_list(num_list[w5][5],listing[k[4][5]][4][0],
	          listing[k[4][5]][4][1],4);
    k[5][5]=m;

    if (d_error)
    { printf("%d %d\n",5,5);
      return 0; }

   b6 = listing[m][5][0];
  e6 = listing[m][5][1];

  for (w6=b6; w6<=e6; ++w6)
  {
    if (!(f_check[k[5][8]][0] & b_mask[num_list[w6][8]]))
      continue;

    if (!(f_check[k[5][7]][0] & b_mask[num_list[w6][7]]))
      continue;

    if (!(f_check[k[5][6]][0] & b_mask[num_list[w6][6]]))
      continue;

    in_list(num_list[w6][8],listing[k[5][8]][5][0],
	          listing[k[5][8]][5][1],5);
    k[6][8]=m;
    if (d_error)
    { printf("%d %d\n",6,8);
      return 0; }

    in_list(num_list[w6][7],listing[k[5][7]][5][0],
	          listing[k[5][7]][5][1],5);
    k[6][7]=m;
    if (d_error)
    { printf("%d %d\n",6,7);
      return 0; }

    in_list(num_list[w6][6],listing[k[5][6]][5][0],
	          listing[k[5][6]][5][1],5);
    k[6][6]=m;
    if (d_error)
    { printf("%d %d\n",6,5);
      return 0; }

   b7 = listing[m][6][0];
  e7 = listing[m][6][1];

  for (w7=b7; w7<=e7; ++w7)
  {
    if (!(f_check[k[6][8]][0] & b_mask[num_list[w7][8]]))
      continue;

    if (!(f_check[k[6][7]][0] & b_mask[num_list[w7][7]]))
      continue;

    in_list(num_list[w7][8],listing[k[6][8]][6][0],
	          listing[k[6][8]][6][1],6);
    k[7][8]=m;
    if (d_error)
    { printf("%d %d\n",7,8);
      return 0; }
    in_list(num_list[w7][7],listing[k[6][7]][6][0],
	          listing[k[6][7]][6][1],6);
    k[7][7]=m;    
    if (d_error)
    { printf("%d %d\n",7,7);
      return 0; }

   b8 = listing[m][7][0];
  e8 = listing[m][7][1];

  for (w8=b8; w8<=e8; ++w8)
  {

    if (!(f_check[k[7][8]][0] & b_mask[num_list[w8][8]]))
      continue;

    in_list(num_list[w8][8],listing[k[7][8]][7][0],
	          listing[k[7][8]][7][1],7);
    if (d_error)
    { printf("%d %d\n",8,8);
      return 0; }
   b9 = listing[m][8][0];
  e9 = listing[m][8][1];

  for (w9=b9; w9<=e9; ++w9)
  {

    ++total_answers;
    fprintf(answer_file,"%s\n",word_list[w1]);
    fprintf(answer_file,"%s\n",word_list[w2]);
    fprintf(answer_file,"%s\n",word_list[w3]);
    fprintf(answer_file,"%s\n",word_list[w4]);
    fprintf(answer_file,"%s\n",word_list[w5]);
    fprintf(answer_file,"%s\n",word_list[w6]);
    fprintf(answer_file,"%s\n",word_list[w7]);
    fprintf(answer_file,"%s\n",word_list[w8]);
    fprintf(answer_file,"%s\n\n",word_list[w9]);
    fflush(answer_file);

  }
  }
  }
  }
  }
  }
  }
  }
  }
  
  fprintf(answer_file,"A total of %d 9-squares were found.\n",total_answers);
  fprintf(status_file,"\n%s\n","Finished.");

  fclose(status_file);
  fclose(answer_file);
  
  return 0;
}

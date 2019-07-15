/* Chris Long */
/* Version 0.0 */

#include <stdio.h>
#include <string.h>

/* Adjust the following to fit your needs.  (word_count) should be the
   number of words in your word list + 1 */

#define word_count (36875)
#define length     (9)

typedef enum       {FALSE,TRUE} boolean;
typedef long       listing_type[word_count][length][2];
typedef char       our_string[length+1];
typedef our_string word_list_type[word_count];

our_string try;

/* These are all loop control variables */

long x, y, z, zz;

/* The number of squares found so far */

long total_answers;

/* This LISTING contains information pertaining to which words start
   with which letters */

static listing_type listing;

/* This is our LIST of (length)-letter WORDs */

static word_list_type word_list;

long w1,w2,w3,w4,w5,w6,w7,w8,w9;
long b2,b3,b4,b5,b6,b7,b8,b9;
long e2,e3,e4,e5,e6,e7,e8,e9;

static long m;

boolean failed_check;

FILE *answer_file, *status_file;

static boolean in_list(c_string, n)

/* Returns TRUE iff the first n+1 letters of C_STRING start a word in
   the word list between words in positions (first) and (last), inclusive.
   This is a simple, but effective, binary search. */

/* N (+1) is the number of letters to check */

our_string c_string; 
long n;

{

/* L ower
   U pper
   letter P osition
   current comparison STATUS */

   long l, u, p, status;

   l = (long) 1;
   u = (long) word_count-1;
   while ((l <= u))
     { m = (l + u) / 2;
       status = 0;
       for (p = 0; p <= n; ++p)
         { if (c_string[p] > word_list[m][p])
             { status = 1;
               break; }
           if (c_string[p] < word_list[m][p])
             { status = 2;
               break; }
         }
       if ((status == 1))
         l = m + 1;
       else 
         if ((status == 2))
           u = m - 1;
         else 
           { return(TRUE); }
     }
  return(FALSE);
  
}

int main()

{

  total_answers = 0;

  for (x = 1; x <= word_count-1; ++x)
    { scanf("%s",word_list[x]); }
    
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
    
/* Main search routine */
    
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

    failed_check = FALSE;
    for (x=length-1; x>=1; --x)
    { try[0] = word_list[w1][x];
      if (!(in_list(try, (long) 0)))
      {  failed_check = TRUE;
         break; }
    }

    if (failed_check)
      continue;

   b2 = listing[m][1][0];
  e2 = listing[m][1][1];

  for (w2=b2; w2<=e2; ++w2)
  {

    failed_check = FALSE;
    for (x=length-1; x>=2; --x)
    { try[0] = word_list[w1][x];
      try[1] = word_list[w2][x];
      if (!(in_list(try, (long) 1)))
      {  failed_check = TRUE;
         break; }
    }

    if (failed_check)
      continue;

   b3 = listing[m][2][0];
  e3 = listing[m][2][1];

  for (w3=b3; w3<=e3; ++w3)
  {

    failed_check = FALSE;
    for (x=length-1; x>=3; --x)
    { try[0] = word_list[w1][x];
      try[1] = word_list[w2][x];
      try[2] = word_list[w3][x];
      if (!(in_list(try, (long) 2)))
      {  failed_check = TRUE;
         break; }
    }

    if (failed_check)
      continue;

   b4 = listing[m][3][0];
  e4 = listing[m][3][1];

  for (w4=b4; w4<=e4; ++w4)
  {

    failed_check = FALSE;
    for (x=length-1; x>=4; --x)
    { try[0] = word_list[w1][x];
      try[1] = word_list[w2][x];
      try[2] = word_list[w3][x];
      try[3] = word_list[w4][x];
      if (!(in_list(try, (long) 3)))
      {  failed_check = TRUE;
         break; }
    }

    if (failed_check)
      continue;

    b5 = listing[m][4][0];
   e5 = listing[m][4][1];

  for (w5=b5; w5<=e5; ++w5)
  {

    failed_check = FALSE;
    for (x=length-1; x>=5; --x)
    { try[0] = word_list[w1][x];
      try[1] = word_list[w2][x];
      try[2] = word_list[w3][x];
      try[3] = word_list[w4][x];
      try[4] = word_list[w5][x];
      if (!(in_list(try, (long) 4)))
      {  failed_check = TRUE;
         break; }
    }

    if (failed_check)
      continue;

   b6 = listing[m][5][0];
  e6 = listing[m][5][1];

  for (w6=b6; w6<=e6; ++w6)
  {

    failed_check = FALSE;
    for (x=length-1; x>=6; --x)
    { try[0] = word_list[w1][x];
      try[1] = word_list[w2][x];
      try[2] = word_list[w3][x];
      try[3] = word_list[w4][x];
      try[4] = word_list[w5][x];
      try[5] = word_list[w6][x];
      if (!(in_list(try, (long) 5)))
      {  failed_check = TRUE;
         break; }
    }

    if (failed_check)
      continue;

   b7 = listing[m][6][0];
  e7 = listing[m][6][1];

  for (w7=b7; w7<=e7; ++w7)
  {

    failed_check = FALSE;
    for (x=length-1; x>=7; --x)
    { try[0] = word_list[w1][x];
      try[1] = word_list[w2][x];
      try[2] = word_list[w3][x];
      try[3] = word_list[w4][x];
      try[4] = word_list[w5][x];
      try[5] = word_list[w6][x];
      try[6] = word_list[w7][x];
      if (!(in_list(try, (long) 6)))
      {  failed_check = TRUE;
         break; }
    }

    if (failed_check)
      continue;

   b8 = listing[m][7][0];
  e8 = listing[m][7][1];

  for (w8=b8; w8<=e8; ++w8)
  {

    failed_check = FALSE;
    for (x=length-1; x>=8; --x)
    { try[0] = word_list[w1][x];
      try[1] = word_list[w2][x];
      try[2] = word_list[w3][x];
      try[3] = word_list[w4][x];
      try[4] = word_list[w5][x];
      try[5] = word_list[w6][x];
      try[6] = word_list[w7][x];
      try[7] = word_list[w8][x];
      if (!(in_list(try, (long) 7)))
      {  failed_check = TRUE;
         break; }
    }

    if (failed_check)
      continue;

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

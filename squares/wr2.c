/* Chris Long */

/* Version 1.1 */
/* Now does both strings and rings.  If the 2nd character in the
   first argument is an "r" (e.g. -r), it searches for rings;
   otherwise it looks for strings.  A minor error in the listing
   creation was corrected, and (long)s were added before constant
   parameters.  Ideally, the size of the word list or the length
   of the words should not have to be specified in advance. /*

/* (length)-letter word ring/string program; (word_count) should equal
   the number of (length)-letter words in your word list, plus 1.
   This program is likely to run extremely slowly if (word_count) is
   substantially larger than (15.8)^(length-1) */

#include <stdio.h>
#include <string.h>

/* Adjust the following to fit your needs.  (word_count) is the number
   of words in our word list; (length) is the length of the words in
   our word list; (max_answer) is the space allocated for the word
   rings/strings found */

#define	word_count (7365)
#define	length (4)
#define	max_answer (400)

typedef enum        {FALSE,TRUE} boolean;
typedef enum        {RING,STRING} options;
typedef char        answer_string[max_answer];
typedef char        our_string[length];
typedef long        listing_type[word_count][length][2];
typedef our_string  word_list_type[word_count];
typedef boolean     dup_type[word_count];

/* CURRENT_OPTION stores whether we are looking for rings or strings */

static options current_option;

/* ANSWER_STRING is the current (possibly partial) answer string */

static answer_string answer;

/* position of M atching word in our list
   word P osition
   length of BEST string found so far
   Current TOTAL */

static long m, p, best, ctotal;

/* These are all loop control variables */

long x, y, z, zz;

/* This LISTING contains information pertaining to which words start
   with which letters */

static listing_type listing;

/* This is our LIST of (length)-letter WORDs */

static word_list_type word_list; 

/* This array is used to insure that we aren't trying to DUPlicate a
   word already used */

static dup_type dups; 

static boolean in_list(c_string, first, last, n)

/* Returns TRUE iff the first n+1 letters of C_STRING start a word in
   the word list between words in positions (first) and (last), inclusive.
   This is a simple, but effective, binary search. */

/* FIRST word to check
   LAST word to check
   N (+1) is the number of letters to check */

our_string c_string; 
long first, last, n;

{

/* L ower
   U pper
   letter P osition
   current comparison STATUS */

   long l, u, p, status;

   l = first;
   u = last;
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

static void find_ring(current_string, p, best, ctotal, w1, w2)

/* Exhaustively tries to extend current_string to find all rings */ 

/* CURRENT_STRING is the current word string
   word P osition
   length of BEST string found so far
   Current TOTAL */

answer_string current_string; 
long *p, *best, *ctotal, w1, w2;

{
/* B egining word
   E nding word
   X is a loop control variable
   TRY is a temporary (length)-letter string, used for checking if
   words starting with certain letters exist */

   our_string try; 
   long b, e, x; 

   for (x = 0; x <= length-2; ++x)
     { try[x] = current_string[(*p)+x]; }
     
   if (!(in_list(try, (long) 1, (long) word_count, (long) length-2)))
     { return; }
     
   if (w1==w2)
     { for (x = 0;x<=(*p)+length-2; ++x)
         { printf("%c",current_string[x]); }
         printf("%c%d\n",' ',(*ctotal));
         (*best) = (*ctotal);
	 return;
     }
     
   b = listing[m][length-1][0];
   e = listing[m][length-1][1];
   
   for (x = b; x <= e; ++x)
     { if ((dups[x]) && !(x==w1))
         { continue; }
       dups[x] = TRUE;
       (*p) = (*p)+1;
       (*ctotal) = (*ctotal)+1;
       current_string[(*p)+length-2] = word_list[x][length-1];
       find_ring(current_string,&(*p),&(*best),&(*ctotal),w1,x);
       (*ctotal) = (*ctotal)-1;
       (*p) = (*p)-1;
       dups[x] = FALSE;
     }
}

static void find_string(current_string, p, best, ctotal)

/* Exhaustively tries to extend current_string enough to equal or
   beat (best) letters */ 

/* CURRENT_STRING is the current word string
   word P osition
   length of BEST string found so far
   Current TOTAL */

answer_string current_string; 
long *p, *best, *ctotal;

{

/* B egining word
   E nding word
   X is a loop control variable */

   our_string try; 
   long b, e, x; 

   for (x = 0; x <= length-2; ++x)
     { try[x] = current_string[(*p)+x]; }
     
   if (!(in_list(try, (long) 1, (long) word_count, (long) length-2)))
     {  if ((*ctotal) >= (*best))
          { for (x = 0;x<=(*p)+length-2; ++x)
              { printf("%c",current_string[x]); }
            printf("%c%d\n",' ',(*ctotal));
            (*best) = (*ctotal);
          }
        return;
     }
     
   b = listing[m][length-1][0];
   e = listing[m][length-1][1];
   
   for (x = b; x <= e; ++x)
     { if ((dups[x]))
         { continue; }
       dups[x] = TRUE;
       (*p) = (*p)+1;
       (*ctotal) = (*ctotal)+1;
       current_string[(*p)+length-2] = word_list[x][length-1];
       find_string(current_string,&(*p),&(*best),&(*ctotal));
       (*ctotal) = (*ctotal)-1;
       (*p) = (*p)-1;
       dups[x] = FALSE;
     }
}

int main(argc, argv)

  int argc;
  char *argv[];

{

  current_option = STRING;
  if ((argc>1) && (argv[1][1] == (int)'r'))
      current_option = RING;

  if (current_option == RING)
    printf("%s\n\n", "Looking for rings.");
  else
    printf("%s\n\n", "Looking for strings.");

/* Read in the word list */
	
  for (x = 1; x <= word_count-1; ++x)
    { scanf("%s",word_list[x]);
      dups[x] = FALSE;
    }
    
/* Make the partial word listing.  (listing[x][y][0]) is the position in
   the word list of the first word that starts with the same (y) letters
   as word (x) does; (listing[x][y][1]) is the last such word */
	   
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
  
/* The longest currently known string has length 0 */

  best = 0;
  
/* Try all words as the starting word */

  for (x = 1; x <= word_count-1; ++x)
    { for (y = 0; y <= length-1; ++y)
        { answer[y] = word_list[x][y]; }

      p=1;
      ctotal=length;
      dups[x]=TRUE;
      if (current_option == RING)
        find_ring(answer, &(p), &(best), &(ctotal), x, (long) 0);
      else
	find_string(answer, &(p), &(best), &(ctotal));
      dups[x]=FALSE;
    }

return 0;

}

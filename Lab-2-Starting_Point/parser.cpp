//**************************************************************************
 
//Name: Corbin T Rochelle
//NetID: ctr233
 
//Purpose: This is the body of the parser that takes breaks the input sentences down into their component parts, which are then analyzed to see if they fit the grammar. 

//**************************************************************************

#include <stdio.h>
#include <iostream>
#include "lexer.h"
#include "parser.h"

using namespace std;

extern "C"
{
  extern int   yylex();      // the generated lexical analyzer
  extern char *yytext;       // text of current lexeme
}

int nextToken = 0;

// Production functions
bool firstOf_sentence();

//*****************************************************************************
// Get the next lexeme (word in sentence)
int lex() {
  nextToken = yylex();
  if( nextToken == TOK_EOF ) {
    yytext[0] = 'E'; yytext[1] = 'O'; yytext[2] = 'F'; yytext[3] = 0;   
  }

  printf("Next token: %d, lexeme: |%s|\n", nextToken, yytext);
  return nextToken;
}
//*****************************************************************************
// Report what we found
void output( string what ) {
  cout << "===> Accepted " << what << ": |" << yytext << "| <===" << endl;
}
//*****************************************************************************
// <sentence> -> <noun phrase> <verb phrase> <noun phrase>
void sentence() 
{
  int visit[3] = {0,0,0}; // [noun,adj,verb]
    
  if( firstOf_sentence() == false )
    throw( "<sentence> did not start with an article or possessive." );

  cout << "Enter <sentence>" << endl;

  noun_phrase(visit);
  verb_phrase(visit);
  noun_phrase(visit);

  cout << "Exit <sentence>" << endl;
} 
//*****************************************************************************
// <noun phrase> → <adjective phrase> NOUN
void noun_phrase(int visit[3]) {
    string spaces = spacer(visit[0]++);
    if (nextToken != ARTICLE & nextToken != POSSESSIVE) {
        throw( "<noun phrase> did not start with an article or possessive." );
    }
    cout << spaces << "Enter <noun phrase> " << visit[0] << endl;
    
    adjective_phrase(visit);
    if (nextToken != NOUN) {
        throw( "<noun phrase> did not have a noun." );
    }
    output("NOUN");
    lex();
    
    cout << spaces << "Exit <noun phrase> " << visit[0] << endl;
}
//*****************************************************************************
// <adjective phrase> → ( ARTICLE | POSSESSIVE ) ADJECTIVE
void adjective_phrase(int visit[3]) {
    string spaces = spacer(visit[1]++);
    cout << spaces << "Enter <adjective phrase> " << visit[1] << endl;
    
    if (nextToken == ARTICLE) {
        output("ARTICLE");
        lex();
    }
    else if (nextToken == POSSESSIVE) {
        output("POSSESSIVE");
        lex();
    }
    else throw( "<adjective phrase> did not start with an article or possessive." );
    if (nextToken != ADJECTIVE) {
        throw( "<adjective phrase> did not have an adjective." );
    }
    output("ADJECTIVE");
    lex();
    
    cout << spaces << "Exit <adjective phrase> " << visit[1] << endl;
}
//*****************************************************************************
// <verb phrase> → VERB | ADVERB <verb phrase>
void verb_phrase(int visit[3]) {
    string spaces = spacer(visit[2]++);
    cout << spaces << "Enter <verb phrase> " << visit[2] << endl;
    
    if (nextToken == VERB) {
        output("VERB");
        lex();
    }
    else if (nextToken == ADVERB) {
        output("ADVERB");
        lex();
        verb_phrase(visit);
        visit[2]--;
    }
    else throw( "<verb phrase> did not start with a verb or an adverb." );
    
    spaces = spacer(visit[2]-1);
    cout << spaces << "Exit <verb phrase> " << visit[2] << endl;
}
//*****************************************************************************
bool firstOf_sentence() {
  if (nextToken != ARTICLE & nextToken != POSSESSIVE) return false;
  return true;
}
//*****************************************************************************
std::string spacer(int iter){
    std::string spaces = "";
    for (int i = 0; i<=iter;i++) spaces+= "  ";
    
    return spaces;
}

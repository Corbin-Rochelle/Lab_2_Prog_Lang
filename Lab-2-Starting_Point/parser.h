/*
Name: Corbin T Rochelle
NetID: ctr233
 
Purpose: To define all the structures needed to parse the documents.
*/

extern int nextToken;

// Function forward declarations
int lex();
void sentence();
void noun_phrase(int visit[3]);
void adjective_phrase(int visit[3]);
void verb_phrase(int visit[3]);

std::string spacer(int iter);

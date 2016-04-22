#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define DEFAULT_LEXEME_SIZE 50

typedef enum {
  DIGIT,
  LETTER,
  NUMBER,
  IDENT,
  ADD_OP,
  SUB_OP,
  MUL_OP,
  DIV_OP,
  LEFT_BRACE,
  RIGHT_BRACE,
  LEFT_PAREN,
  RIGHT_PAREN,
  INEQUALITY,
  ASSIGNMENT,
  UNKNOWN
} classes;

classes parse(char);

int main(int argc, char **argv) {

  if (argc < 2) {
    printf("%s: [input]\n", argv[0]);
    return 1;
  }

  char *input = argv[1];
  char *lexemes;
  classes cur_parse;
  classes next_token;
  int i;
  int token_counter;

  lexemes = (char *) malloc(DEFAULT_LEXEME_SIZE);

  for (i = 0, token_counter = 0; input[i] != '\0'; i++){
    if (!isspace(input[i])) {
      cur_parse = parse(input[i]);
      next_token = cur_parse;
      
      while (cur_parse == LETTER || cur_parse == DIGIT) {
	*(lexemes + token_counter++) = input[i++];
	cur_parse = parse(input[i]);
      }
      
      if (next_token == LETTER)
	next_token = IDENT;
      else if (next_token == DIGIT)
	next_token = NUMBER;
      else {
	*(lexemes + token_counter++) = input[i];
      }
      
      *(lexemes + token_counter) = '\0';
      printf("Token: %d\n", next_token);
      printf("Lexeme: %s\n", lexemes);
      token_counter = 0;
    }
  }
 
  free(lexemes);
  
  return 0;
}

classes lookup (char c)
{
  classes token;
  
  switch (c) {
  case '+':
    token = ADD_OP;
    break;
  case '-':
    token = SUB_OP;
    break;
  case '*':
    token = MUL_OP;
    break;
  case '/':
    token = DIV_OP;
    break;
  case '{':
    token = LEFT_BRACE;
    break;
  case '}':
    token = RIGHT_BRACE;
    break;
  case '(':
    token = LEFT_PAREN;
    break;
  case ')':
    token = RIGHT_PAREN;
    break;
  case '>':
    token = INEQUALITY;
    break;
  case '<':
    token = INEQUALITY;
    break;
  case '=':
    token = ASSIGNMENT;
    break;
  default:
    token = UNKNOWN;
    break;
  }

  return token;
}

classes parse(char input)
{
  classes token;

  if (isalpha(input)) {
    token = LETTER;
  }
  else if (isdigit(input)) {
    token = DIGIT;
  }
  else {
    token = lookup(input);
  }

  return token;
}

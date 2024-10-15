#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AMOUNT_OF_TOKENS 3

typedef enum {
  PLUS,     // +
  MINUS,    // -
  PRODUCT,  // *
  DIVISION, // /
} OPERANDS;

typedef enum {
  OPERATOR,
  OPERAND,
} TokenType;

typedef struct {
  char *literal;
  TokenType type;
} Token;

void print_token(Token *t) {
  printf("Token literal: %s\n", t->literal);
  printf("Token type: %s\n", t->type == OPERATOR ? "OPERATOR" : "OPERAND");
}

typedef struct {
  char *buffer;
  size_t buffer_size;
  char current_char;
  int current_position;
} Lexer;

int is_digit(char c) {
  // using ASCII representations
  // to check if c is a digit literal
  return c >= 48 && c <= 57;
}

int is_operator(char c) { return c == '-' || c == '+' || c == '*' || c == '/'; }

int read_char(Lexer *l) {
  if (l->current_position + 1 == l->buffer_size) {
    return EOF;
  }
  l->current_position++;
  l->current_char = l->buffer[l->current_position];
  return l->current_char;
}

void skip_whitespace(Lexer *l) {
  while (l->current_char == ' ' || l->current_char == '\t' ||
         l->current_char == '\n') {
    printf("Skipped whitespace\n");
    read_char(l);
  }
}

Lexer *init_lexer(char *buffer, size_t buffer_size) {
  Lexer *l = malloc(sizeof(Lexer));
  if (l == NULL) {
    perror("Error while allocating memory for lexer:");
    return l;
  }
  l->buffer = buffer;
  l->buffer_size = buffer_size;
  l->current_position = EOF;
  l->current_char = 0;
  return l;
}

void print_lexer_buffer(Lexer *l) {
  for (int i = l->current_position; i < l->buffer_size - 1; i++) {
    printf("%c", l->buffer[i]);
    printf("\n");
  }
}

void print_lexer(Lexer *l) {
  printf("Buffer: %s\n", l->buffer);
  printf("Buffer size: %zu\n", l->buffer_size);
  printf("Current character: %c\n", l->current_char);
  printf("Current position: %d\n", l->current_position);
}

char peek_at_lexer_buffer(Lexer *l, int index) {
  if (l->buffer_size <= index) {
    return EOF;
  }
  return l->buffer[index];
}

char *read_operand(Lexer *l) {
  int operand_len = 0;
  int index = l->current_position;
  char c = l->current_char;
  while (c >= 48 && c <= 57) { // whether c is a numerical character
    c = peek_at_lexer_buffer(l, ++index);
    operand_len++;
  }
  printf("Operand has %d digits\n", operand_len);
  char *operand_literal = malloc(operand_len);
  if (operand_literal == NULL) {
    perror("Error while allocating memory for operand literal:");
    return NULL;
  }
  for (int i = 0; i < operand_len; i++) {
    operand_literal[i] = l->current_char;
    read_char(l);
  }
  operand_literal[operand_len] = '\0';
  return operand_literal;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: evaluator 'expression' \n");
    return 0;
  }
  char *expression = argv[1];
  size_t len = strlen(expression);
  Lexer *l = init_lexer(expression, len);
  if (l == NULL) {
    return 0;
  }
  int num_of_tokens = 0;
  Token tokens[AMOUNT_OF_TOKENS];
  while ((read_char(l) != EOF)) {
    skip_whitespace(l);
    if (is_digit(l->current_char)) {
      // if digit is found read operand and store it as token
      char *operand = read_operand(l);
      if (operand == NULL) {
        break;
      }
      printf("Operand: %s\n", operand);
      Token t = (Token){
          .literal = operand,
          .type = OPERAND,
      };
      if (num_of_tokens < AMOUNT_OF_TOKENS) {
        tokens[num_of_tokens] = t;
        num_of_tokens++;
      }
    }
    if (is_operator(l->current_char)) {
      Token t = (Token){
          .type = OPERATOR,
      };
      switch (l->current_char) {
      case '-':
        t.literal = "-";
        break;
      case '+':
        t.literal = "+";
        break;
      case '*':
        t.literal = "*";
        break;
      case '/':
        t.literal = "/";
        break;
      }
      if (num_of_tokens < AMOUNT_OF_TOKENS) {
        tokens[num_of_tokens] = t;
        num_of_tokens++;
      }
    }
  }
  for (int i = 0; i < num_of_tokens; i++) {
    print_token(&tokens[i]);
  }
  free(l);
  return 0;
}

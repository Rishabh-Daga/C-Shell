#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM ";\n"
#define LSH_RL_BUFSIZE 1024

char *lsh_read_line(void)
{
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    c = getchar();

    // If we hit EOF, replace it with a null character and return.
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      // printf("%ld\n",(buffer) );
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}
// char *lsh_read_line(void)
// {
//   char *line = NULL;
//   ssize_t bufsize = 0; // have getline allocate a buffer for us
//   getline(&line, &bufsize, stdin);
//   return line;
// }
char **lsh_split_line1(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}
char **lsh_split(char *line,char del[])
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, del);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, del);
  }
  tokens[position] = NULL;
  return tokens;
}
// char **lsh_split_line()
// {
// 	char *line = NULL;
// 	ssize_t buffsize = 0; // have getline allocate a buffer for us
// 	getline(&line, &buffsize, stdin);
// 	int bufsize = LSH_TOK_BUFSIZE, position = 0;
// 	char **tokens = malloc(bufsize * sizeof(char*));
// 	char *token;

// 	if (!tokens) {
// 		fprintf(stderr, "lsh: allocation error\n");
// 		exit(EXIT_FAILURE);
// 	}

// 	token = strtok(line, LSH_TOK_DELIM);
// 	while (token != NULL) {
// 		tokens[position] = token;
// 		position++;

// 		if (position >= bufsize) {
// 			bufsize += LSH_TOK_BUFSIZE;
// 			tokens = realloc(tokens, bufsize * sizeof(char*));
// 			if (!tokens) {
// 				fprintf(stderr, "lsh: allocation error\n");
// 				exit(EXIT_FAILURE);
// 			}
// 		}

// 		token = strtok(NULL, LSH_TOK_DELIM);
// 	}
// 	tokens[position] = NULL;
// 	return tokens;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

#define MAX_LINE_LENGTH 1024 /**< Maximum length of a line */
#define MAX_LINES 100        /**< Maximum number of lines */

/**
 * @brief The main function of the program.
 *
 * This function reads lines of text from standard input, stores them in
 * a dynamically allocated array of strings, and allows the user to choose
 * an alignment option for the text. After aligning the text, it prints
 * the aligned lines and frees the allocated memory.
 *
 * @return Exit status of the program. Returns 0 on successful completion.
 */
int main() {
  int i = 0;                                       /**< Index for looping */
  char **par = malloc(MAX_LINES * sizeof(char *)); /**< Array of strings */
  if (par == NULL) {
    perror("Failed to allocate memory for lines");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < MAX_LINES; i++) {
    par[i] = malloc(MAX_LINE_LENGTH *
                    sizeof(char)); /**< Allocate memory for each line */
    if (par[i] == NULL) {
      perror("Failed to allocate memory for a line");
      exit(EXIT_FAILURE);
    }
  }

  int line_count = 0;           /**< Number of lines read */
  char buffer[MAX_LINE_LENGTH]; /**< Buffer for reading input */
  int choice;                   /**< User's alignment choice */

  printf("Enter lines of text. To stop, enter a blank line.\n");

  while (line_count < MAX_LINES) {
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
      perror("fgets failed");
      exit(EXIT_FAILURE);
    }

    buffer[strcspn(buffer, "\n")] = '\0'; /**< Remove newline character */

    if (strlen(buffer) == 0) {
      break; /**< Stop input on blank line */
    }

    strncpy(par[line_count], buffer, MAX_LINE_LENGTH);
    par[line_count][MAX_LINE_LENGTH - 1] = '\0'; /**< Ensure null termination */
    line_count++;
  }

  printf("\nChoose alignment:\n");
  printf("1. Left Align\n");
  printf("2. Right Align\n");
  printf("3. Center Align\n");
  printf("4. Justify\n");
  printf("Enter choice (1-4): ");
  scanf("%d", &choice);
  while (getchar() != '\n'); /**< Clear input buffer */

  /**
   * @brief Align the text based on user choice.
   *
   * Calls the appropriate alignment function based on the user's choice.
   */
  switch (choice) {
    case 1:
      /* Default (left align) - no function call needed */
      break;
    case 2:
      Right(par); /**< Align text to the right */
      break;
    case 3:
      Center(par); /**< Center-align text */
      break;
    case 4:
      Justify(par); /**< Justify text */
      break;
    default:
      printf("Invalid choice.\n");
      break;
  }

  /**
   * @brief Print the aligned text.
   *
   * Iterates through the array of strings and prints each line.
   */
  for (i = 0; i < line_count; i++) {
    printf("%s\n", par[i]);
  }

  /**
   * @brief Free allocated memory.
   *
   * Frees the memory allocated for each line and then for the array of strings.
   */
  for (i = 0; i < MAX_LINES; i++) {
    free(par[i]);
  }
  free(par);

  return 0; /**< Return 0 to indicate successful completion */
}

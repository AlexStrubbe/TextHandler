#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Right-aligns each string in an array of strings.
 *
 * This function adjusts the alignment of each string in the array such that
 * each string is right-aligned to the length of the longest string in the
 * array. The function pads the beginning of each string with spaces as
 * necessary.
 *
 * @param[in,out] str Array of strings to be right-aligned. The function
 * modifies the strings in this array to be right-aligned.
 */
void Right(char **str) {
  int i;
  size_t max_length = strlen(str[0]);

  /* Find the maximum length of the strings */
  for (i = 1; str[i] != NULL; ++i) {
    size_t current_length = strlen(str[i]);
    if (current_length > max_length) {
      max_length = current_length;
    }
  }

  /* Right-align each string */
  for (i = 0; str[i] != NULL; ++i) {
    size_t current_length = strlen(str[i]);
    int space_counter = max_length - current_length;

    /* Allocate memory for the padded string */
    char *padded_str = (char *)malloc(max_length + 1);
    if (padded_str == NULL) {
      perror("Failed to allocate memory");
      exit(EXIT_FAILURE);
    }

    /* Fill the padded string with spaces and copy the original string */
    memset(padded_str, ' ', space_counter);
    strcpy(padded_str + space_counter, str[i]);
    str[i] = padded_str;
  }
}

/**
 * @brief Center-aligns each string in an array of strings.
 *
 * This function adjusts the alignment of each string in the array such that
 * each string is center-aligned to the length of the longest string in the
 * array. The function pads both sides of each string with spaces as necessary.
 *
 * @param[in,out] str Array of strings to be center-aligned. The function
 * modifies the strings in this array to be center-aligned.
 */
void Center(char **str) {
  int i;
  size_t max_length = strlen(str[0]);

  /* Find the maximum length of the strings */
  for (i = 1; str[i] != NULL; ++i) {
    size_t current_length = strlen(str[i]);
    if (current_length > max_length) {
      max_length = current_length;
    }
  }

  /* Center-align each string */
  for (i = 0; str[i] != NULL; ++i) {
    size_t current_length = strlen(str[i]);
    int space_counter = (max_length - current_length) / 2;

    /* Allocate memory for the padded string */
    char *padded_str = (char *)malloc(max_length + 1);
    if (padded_str == NULL) {
      perror("Failed to allocate memory");
      exit(EXIT_FAILURE);
    }

    /* Fill the left side with spaces, copy the original string, and pad the
     * right side */
    memset(padded_str, ' ', space_counter);
    strcpy(padded_str + space_counter, str[i]);
    memset(padded_str + space_counter + current_length, ' ',
           max_length - current_length - space_counter);
    padded_str[max_length] = '\0';
    str[i] = padded_str;
  }
}

/**
 * @brief Justifies each string in an array of strings.
 *
 * This function adjusts the alignment of each string in the array such that
 * each string is justified to the length of the longest string in the array.
 * The function adds spaces between words to ensure that each line reaches
 * the specified maximum width, with extra spaces distributed as evenly as
 * possible.
 *
 * @param[in,out] str Array of strings to be justified. The function modifies
 *                    the strings in this array to be justified.
 */
void Justify(char **str) {
  int i, j, k;
  size_t max_length = strlen(str[0]);

  /* Find the maximum length of the strings */
  for (i = 1; str[i] != NULL; ++i) {
    size_t current_length = strlen(str[i]);
    if (current_length > max_length) {
      max_length = current_length;
    }
  }

  /* Justify each string */
  for (i = 0; str[i] != NULL; ++i) {
    size_t current_length = strlen(str[i]);
    if (current_length >= max_length) {
      continue; /* Skip lines that are already the maximum width or longer */
    }

    /* Allocate memory for the justified string */
    char *padded_str = (char *)malloc(max_length + 1);
    if (padded_str == NULL) {
      perror("Failed to allocate memory");
      exit(EXIT_FAILURE);
    }

    size_t new_space = 0;
    int str_words = 0, space_add = 0, space_rem = 0;

    /* Count number of words */
    for (j = 0; j < current_length; ++j) {
      if (str[i][j] == ' ') {
        ++str_words;
      }
    }
    str_words++; /* Number of words */

    /* Compute spaces needed */
    int space_counter = max_length - current_length;
    if (str_words > 1) {
      space_add = space_counter / (str_words - 1);
      space_rem = space_counter % (str_words - 1);
    } else {
      space_add = space_counter;
      space_rem = 0;
    }

    /* Justify the line */
    for (j = 0; j < current_length; ++j) {
      padded_str[new_space++] = str[i][j];

      if (str[i][j] == ' ') {
        size_t spaces = space_add;
        if (space_rem > 0) {
          spaces++;
          space_rem--;
        }
        for (k = 0; k < spaces; ++k) {
          padded_str[new_space++] = ' ';
        }
      }
    }

    /* If there are any remaining spaces, pad the end of the line */
    while (new_space < max_length) {
      padded_str[new_space++] = ' ';
    }

    padded_str[max_length] = '\0'; /* Null-terminate the string */
    str[i] = padded_str;
  }
}

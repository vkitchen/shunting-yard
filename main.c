#include <stdio.h>
#include <string.h>

/*
 * TODO
 * - Support tokens bunched closer than space seperated
 * - Use more robust methods to detect number
 */

int main(void)
{
	char buf[1024];

	char token[64];
	int advance = 0;

	char operators[64];
	int opIndex = 0;
	while (fgets(buf, sizeof(buf), stdin)) {
		advance = 0;
		while (advance < strlen(buf) && sscanf(&buf[advance], "%s", &token)) {
			advance += strlen(token) + 1;
			/* Assume entirely a number */
			if ('0' <= token[0] && token[0] <= '9') {
				printf(" %s", token);
			} else if (token[0] == '(') {
				operators[opIndex++] = '(';
			} else if (token[0] == ')') {
				while (operators[--opIndex] != '(')
					printf(" %c", operators[opIndex]);
			} else {
				/* Assumed to be an operator */
				while (opIndex > 0 && operators[opIndex-1] != '(')
					printf(" %c", operators[--opIndex]);
				operators[opIndex++] = token[0];
			}
		}
		while (opIndex > 0)
			printf(" %c", operators[--opIndex]);
		printf("\n");
	}
}

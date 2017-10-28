#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <inttypes.h>
#include <stdlib.h>

uint8_t inputValue(const char* str) {
	uint8_t val = 0;

	printf(str);
	scanf("%hhu", &val);

	return val;
}

int8_t** createTable(const int8_t rows, const uint8_t colls) {
	int8_t** table = (int8_t**)calloc(rows, sizeof(int8_t*));
	for (uint8_t i = 0; i < rows; i++) {
		*(table + i) = (int8_t*)calloc(colls, sizeof(int8_t));
	}

	return table;
}

int8_t** initTable(int8_t** table, const uint8_t rows, const uint8_t colls) {
	for (uint8_t i = 0; i < rows; i++) {
		for (uint8_t j = 0; j < colls; j++) {
			if (rand() % 2 == 0) {
				*(*(table + i) + j) = rand() % 10;
			}
			else {
				*(*(table + i) + j) = -rand() % 10;
			}
		}
	}

	return table;
}

int8_t** printTable(int8_t** table, const uint8_t rows, const uint8_t colls) {
	for (uint8_t i = 0; i < rows; i++) {
		for (uint8_t j = 0; j < colls; j++) {
			printf("%4hhi", *(*(table + i) + j));
		}
		putchar('\n');
	}

	return table;
}

int8_t** deleteTable(uint8_t** table, const uint8_t rows, const uint8_t colls) {
	for (uint8_t i = 0; i < rows; i++) {
		free(*(table + i));
	}
	free(table);

	return NULL;
}

bool isMassive(int8_t* mas, uint8_t ln, int8_t val) {
	for (uint8_t i = 0; i < ln; i++) {
		if (val == *(mas + i)) {
			return true;
		}
	}

	return false;
}

bool isTable(int8_t** table, uint8_t r, uint8_t c, int8_t val) {
	for (uint8_t i = 0; i < r; i++) {
		for (uint8_t j = 0; j < c; j++) {
			if (val == *(*(table + i) + j)) {
				return true;
			}
		}
	}

	return false;
}

int8_t* addMassive(int8_t* mas, uint8_t* ln, int8_t val) {
	mas = (int8_t*)realloc(mas, ++*ln * sizeof(int8_t));
	*(mas + *ln - 1) = val;

	return mas;
}

int8_t* printMassive(int8_t* mas, uint8_t ln) {
	printf("Massive: ");
	for (uint8_t i = 0; i < ln; i++) {
		printf("%4hhi", *(mas + i));
	}
	printf("\n");
}

uint8_t menu() {
	uint8_t ch = 0;

	system("cls");

	printf("Menu:\n");
	printf("1 - Create tables.\n");
	printf("2 - Print tables.\n");
	printf("3 - Find common values.\n");
	printf("4 - Find unique values.\n");
	printf("5 - Find common values for A and C.\n");
	printf("6 - Find negative values.\n");
	printf("7 - Delete tables.\n");
	printf("8 - Exit.\n");
	printf("Choice: ");
	scanf("%hhu", &ch);

	return ch;
}

void pass() {
	while (getchar() != '\n');
}


int main(void) {
	uint8_t ch = 0;

	int8_t** A = NULL;
	uint8_t rowA = 0;
	uint8_t collsA = 0;

	int8_t** B = NULL;
	uint8_t rowB = 0;
	uint8_t collsB = 0;

	int8_t** C = NULL;
	uint8_t rowC = 0;
	uint8_t collsC = 0;

	uint8_t ln = 0;
	int8_t* common = NULL;

	while ((ch = menu()) != 8) {
		switch (ch) {
		case 1:
			if (A) {
				A = deleteTable(A, rowA, collsA);
			}
			if (B) {
				B = deleteTable(B, rowB, collsB);
			}
			if (C) {
				C = deleteTable(C, rowC, collsC);
			}

			rowA = inputValue("Input num of a rows for A: ");
			collsA = inputValue("Input num of a colls for A: ");

			rowB = inputValue("\nInput num of a rows for B: ");
			collsB = inputValue("Input num of a colls for B: ");

			rowC = inputValue("\nInput num of a rows for C: ");
			collsC = inputValue("Input num of a colls for C: ");

			A = createTable(rowA, collsA);
			B = createTable(rowB, collsB);
			C = createTable(rowC, collsC);
			initTable(A, rowA, collsA);
			initTable(B, rowB, collsB);
			initTable(C, rowC, collsC);

			break;

		case 2:
			printf("Table A:\n");
			printTable(A, rowA, collsA);

			printf("\nTable B:\n");
			printTable(B, rowB, collsB);

			printf("\nTable C:\n");
			printTable(C, rowC, collsC);
			break;

		case 3:
			for (uint8_t i = 0; i < rowA; i++) {
				for (uint8_t j = 0; j < collsA; j++) {
					if (!isMassive(common, ln, A[i][j]) && isTable(B, rowB, collsB, A[i][j]) && isTable(C, rowC, collsC, A[i][j])) {
						common = addMassive(common, &ln, A[i][j]);
					}
				}
			}

			for (uint8_t i = 0; i < rowB; i++) {
				for (uint8_t j = 0; j < collsB; j++) {
					if (!isMassive(common, ln, B[i][j]) && isTable(A, rowA, collsA, B[i][j]) && isTable(C, rowC, collsC, B[i][j])) {
						common = addMassive(common, &ln, B[i][j]);
					}
				}
			}

			for (uint8_t i = 0; i < rowC; i++) {
				for (uint8_t j = 0; j < collsC; j++) {
					if (!isMassive(common, ln, C[i][j]) && isTable(A, rowA, collsA, C[i][j]) && isTable(B, rowB, collsB, C[i][j])) {
						common = addMassive(common, &ln, C[i][j]);
					}
				}
			}

			printMassive(common, ln);
			free(common);
			common = NULL;
			ln = 0;

			break;

		case 4:
			for (uint8_t i = 0; i < rowA; i++) {
				for (uint8_t j = 0; j < collsA; j++) {
					if (!isMassive(common, ln, A[i][j]) && !isTable(B, rowB, collsB, A[i][j]) && !isTable(C, rowC, collsC, A[i][j])) {
						common = addMassive(common, &ln, A[i][j]);
					}
				}
			}

			for (uint8_t i = 0; i < rowB; i++) {
				for (uint8_t j = 0; j < collsB; j++) {
					if (!isMassive(common, ln, B[i][j]) && !isTable(A, rowA, collsA, B[i][j]) && !isTable(C, rowC, collsC, B[i][j])) {
						common = addMassive(common, &ln, B[i][j]);
					}
				}
			}

			for (uint8_t i = 0; i < rowC; i++) {
				for (uint8_t j = 0; j < collsC; j++) {
					if (!isMassive(common, ln, C[i][j]) && !isTable(A, rowA, collsA, C[i][j]) && !isTable(B, rowB, collsB, C[i][j])) {
						common = addMassive(common, &ln, C[i][j]);
					}
				}
			}

			printMassive(common, ln);
			free(common);
			common = NULL;
			ln = 0;
			break;

		case 5:
			for (uint8_t i = 0; i < rowA; i++) {
				for (uint8_t j = 0; j < collsA; j++) {
					if (!isMassive(common, ln, A[i][j]) && isTable(C, rowC, collsC, A[i][j])) {
						common = addMassive(common, &ln, A[i][j]);
					}
				}
			}

			printMassive(common, ln);
			free(common);
			common = NULL;
			ln = 0;
			break;

		case 6:
			for (uint8_t i = 0; i < rowA; i++) {
				for (uint8_t j = 0; j < collsA; j++) {
					if (A[i][j] < 0 && !isMassive(common, ln, A[i][j])) {
						common = addMassive(common, &ln, A[i][j]);
					}
				}
			}

			for (uint8_t i = 0; i < rowB; i++) {
				for (uint8_t j = 0; j < collsB; j++) {
					if (B[i][j] < 0 && !isMassive(common, ln, B[i][j])) {
						common = addMassive(common, &ln, B[i][j]);
					}
				}
			}

			for (uint8_t i = 0; i < rowC; i++) {
				for (uint8_t j = 0; j < collsC; j++) {
					if (C[i][j] < 0 && !isMassive(common, ln, C[i][j])) {
						common = addMassive(common, &ln, C[i][j]);
					}
				}
			}

			printMassive(common, ln);
			free(common);
			common = NULL;
			ln = 0;
			break;

		case 7:
			A = deleteTable(A, rowA, collsA);
			rowA = 0;
			collsA = 0;

			B = deleteTable(B, rowB, collsB);
			rowB = 0;
			collsB = 0;

			C = deleteTable(C, rowC, collsC);
			rowC = 0;
			collsC = 0;

			break;


		default:
			printf("Wrong input.\n");
			pass();
			break;
		}

		printf("Press any key.\n");
		_getch();
	}

	deleteTable(A, rowA, collsA);
	deleteTable(B, rowB, collsB);
	deleteTable(C, rowC, collsC);

	return 0;
}
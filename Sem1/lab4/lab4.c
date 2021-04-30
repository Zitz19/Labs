#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <time.h>
#include <locale.h>

const wchar_t *MSGS[] = {L"0. Quit\n", L"1. Reading from keyboard\n", L"2. Reading from file\n", L"3. Generation of data\n", 
L"4. Sorting of data\n", L"5. Searching string with 3 russian last letters\n", L"6. Saving current state of data\n",
L"7. Comparison of sort algorythms by time\n"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);



int dialog(const wchar_t *msgs[], int n) {
	wchar_t *error = L"";
	int choice;
	do {
		fputws(error, stdout);
		error = L"You're wrong. Try again!\n";
		for (int i = 0; i < n; ++i) {
			fputws(msgs[i], stdout);
		}
		fputws(L"Make your choice: ", stdout);
		choice = getwchar() - L'0';
		while (getwchar() != L'\n') {}
	} while (choice < 0 || choice >= n);
	return choice;
}

wchar_t *read_wstr_from_stream(FILE *stream) {
	wchar_t buf[1000];
	int wslen = 0;
	wchar_t *wstr = NULL;
	if (fgetws(buf, 1000, stream) != NULL) {
		wslen = wcslen(buf);
		wstr = (wchar_t *) malloc(wslen * sizeof(wchar_t));
		memcpy(wstr, buf, wslen * sizeof(wchar_t));
		wstr[wslen - 1] = L'\0';
	}	
	else {
		fputws(L"-----Changing ended-----\n", stdout);
		return NULL;
	}
	return wstr;
}

char *wchar_to_char(wchar_t *wstring, char *cstring) {
	int len = wcslen(wstring);
	cstring = realloc(cstring, (len + 1) * sizeof(char));
	for (int i = 0; i < len; i++) {
		cstring[i] = (char) wstring[i];
	}
	cstring[len] = '\0';
	return cstring;
}

wchar_t *rand_string() {
	wchar_t *rand_wstr = NULL;
	int str_length;
	int language;
	str_length = rand() % 100 + 1;
	rand_wstr = realloc(rand_wstr, str_length * sizeof(wchar_t));
	for (int i = 0; i < str_length - 1; i++) {
		language = rand() % 2;
		if (language == 0)	{
			rand_wstr[i] = rand() % (L'z' - L'a') + L'a';

		}
		else {
			rand_wstr[i] = rand() % (L'я' - L'а') + L'а';
		}
	}
	rand_wstr[str_length - 1] = L'\0';
	return rand_wstr;
}

void swap(wchar_t **p_array, int wstr1, int wstr2) {
	wchar_t *buf;
	buf = p_array[wstr1];
	p_array[wstr1] = p_array[wstr2];
	p_array[wstr2] = buf;
}

void my_sort(wchar_t **p_array, int array_size) {
	for (int i = 0; i < array_size - 1; i++) {
		int index_min = i;
		for (int j = i + 1; j < array_size; j++) {
			if (wcscmp(p_array[index_min], p_array[j]) > 0) {
				index_min = j;
			}
		}
		swap(p_array, i, index_min);
	}
}

void bubble_sort(wchar_t **p_array, int array_size) {
	for (int i = 0; i < array_size; i++) {
		for (int j = array_size - 1; j > i; j--) {
			if (wcscmp(p_array[j - 1], p_array[j]) > 0) {
				swap(p_array, j - 1, j);
			}
		}
	}
}

wchar_t **test_array(int len) {
	wchar_t **array = (wchar_t **) calloc(len, sizeof(wchar_t *));
	for (int i = 0; i < len; i++) {
		array[i] = (wchar_t *) calloc(101, sizeof(wchar_t));
		for (int j = 0; j < 100; j++) {
			int language = rand() % 2;
			if (language == 0)	{
				array[i][j] = rand() % (0x7e - 0x20) + 0x20;
			}
			else {
				array[i][j] = rand() % (0x44f - 0x410) + 0x410;
			}
		}
		array[i][100] = L'\0';
	}
	return array;
}

int main() {
	setlocale(LC_ALL, "");
	srand(time(NULL));
	int c = 0;
	wchar_t **p_array = NULL;
	wchar_t *wpath = (wchar_t *) calloc(100, sizeof(wchar_t));
	char *path = (char *) calloc(100, sizeof(char));
	FILE *fd;
	int array_size = 0;
	int i = 0;
	int j = 0;
	int str_number;
	int wcstr;
	int flag;
	int num_iter;
	int test_len;
	double time_total;
	int method;
	do {
		c = dialog(MSGS, MSGS_SIZE);
		switch(c) {
		case 0:
			break;
		case 1:
			fputws(L"Please, write a string and press ENTER. Write NULL to end adding strings.\n", stdout);
			i = 0;
			do {
				p_array = realloc(p_array, (i + 1) * sizeof(wchar_t *));
				p_array[i] = read_wstr_from_stream(stdin);
				i++;
			} while (p_array[i - 1] != NULL);
			array_size = i - 1;
			for (int j = 0; j < array_size; j++) {
				wprintf(L"%ls\n", p_array[j]);
			}
			break;
		case 2:
			wprintf(L"Enter file name: ");
			wscanf(L"%ls", wpath);
			while (getwchar() != L'\n') {}
			path = wchar_to_char(wpath, path);
			fd = fopen(path, "a+t");
			i = 0;
			do {
				p_array = realloc(p_array, (i + 1) * sizeof(wchar_t *));
				p_array[i] = read_wstr_from_stream(fd);
				i++;
			} while  (p_array[i - 1] != NULL);
			fclose(fd);
			array_size = i - 1;
			for (int j = 0; j < array_size; j++) {
				wprintf(L"%ls\n", p_array[j]);
			}
			break;
		case 3:
			str_number = rand() % 50 + 1;
			p_array = realloc(p_array, str_number * sizeof(wchar_t *));
			for (int i = 0; i < str_number; i++) {
				p_array[i] = rand_string();
			}
			array_size = str_number;
			for (int k = 0; k < array_size; k++) {
				wprintf(L"%ls\n", p_array[k]);
			}
			break;
		case 4:
			my_sort(p_array, array_size);
			break;
		case 5:
			for (int i = 0; i < array_size; i++) {
				wcstr = wcslen(p_array[i]);
				flag = 1;
				if (wcstr > 3) {
					for (int j = wcstr - 1; j > wcstr - 4; j--) {
						if ((p_array[i][j] >= 0x410) && (p_array[i][j] <= 0x44f)) {}
						else {
							flag = 0;
						}
					}
					if (flag == 1) {
						wprintf(L"%ls\n", p_array[i]);
					}
				}
			}
			break;
		case 6:
			wprintf(L"Enter file name: ");
			wscanf(L"%ls", wpath);
			while (getwchar() != L'\n') {}
			path = wchar_to_char(wpath, path);
			fd = fopen(path, "w+");
			for (int i = 0; i < array_size; i++) {
				fwprintf(fd, L"%ls\n", p_array[i]);
			}
			fclose(fd);
			break;
		case 7:
			wprintf(L"Enter file name: ");
			wscanf(L"%ls", wpath);
			while (getwchar() != L'\n') {}
			path = wchar_to_char(wpath, path);
			fd = fopen(path, "a+");
			fwprintf(stdout, L"Enter array size: ");
			fwscanf(stdin, L"%d", &test_len);
			fwprintf(stdout, L"Enter number of iterations: ");
			fwscanf(stdin, L"%d", &num_iter);
			fwprintf(stdout, L"Enter method (1 - My Sorting, 2 - Bubble Sorting) : ");
			fwscanf(stdin, L"%d", &method);
			time_total = 0;
			for (int i = 0; i < num_iter; ++i) {
				wchar_t **ptr = test_array(test_len);
				clock_t t = clock();
				if (method == 1) {
					my_sort(ptr, test_len);
				}
				else {
					bubble_sort(ptr, test_len);
				}
				t = clock() - t;
				double time = (double) t / CLOCKS_PER_SEC;
				for (int i = 0; i < test_len; i++) {
					free(ptr[i]);
				}
				free(ptr);
				time_total += time;
			}
			if (method == 1) {
				fwprintf(fd, L"%.8lf %d\n", time_total / num_iter, test_len);
			}
			else {
				fwprintf(fd, L"%.8lf %d\n", time_total / num_iter	, test_len);
			}
			fclose(fd);
			while (getwchar() != L'\n') {}
			break;
		}
	} while (c != 0);
	free(wpath);
	free(path);
	for (int i = 0; i < array_size; i++) {
		free(p_array[i]);
	}
	free(p_array);
	return 0;
}

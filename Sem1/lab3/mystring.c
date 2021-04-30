int strlen(char *str0)
{
	int i = 0;
	while (str0[i] != '\0') {
		i++;
	}
	return i;
}

int strcspn(char *str1, char *key) {
	int i = 0;
	while (str1[i] != '\0') {
		int j = 0;
		while (key[j] != '\0')
		{
			if (str1[i] == key[j]) {
				return i;
			}
			j++;
		}
		i++;
	}
	return i;
}

void memcpy(char *dst, char *src, int x) {
	for (int i = 0; i < x; i++) {
		dst[i] = src[i];
	}
}

#include "malloc.h"
#include "util.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// return 1 for all space
int str_all_space(char *str)
{
	while (*str) {
		if (*str != ' ') {
			return 0;
		}
		str ++;
	}

	return 1;
}

// 删除字符串末尾符号，如 \r \n ' ' 
void trim_crlf(char *str)
{
	char *p = &str[strlen(str)-1];
	while (*p == '\r' || *p == '\n' || *p == ' ') {
		*p -- = '\0';
	}
}

// 去除多余的符号，如空格、\r\n等
void str_trim(char *str)
{
	trim_crlf(str);
	char *p = str;
	while (*str != '\0') {
		if (*str != ' ') {
			*p ++ = *str;
		}
		str ++;
	}
	*p = '\0';
}

void str_split(const char *str, char *left, char *right, const char c)
{
	const char *p = strchr(str, c);
	if (p == NULL) {
		strcpy(left, str);
	}else {
		strncpy(left, str, p - str);
		strcpy(right, p + 1);
	}
}

// 除去末尾指定字符
void str_trim_special_ch(char *str, const char c)
{
	char *p = &str[strlen(str)];
	if (*p == c) {
		*p = '\0';
	}
}

// 返回一个字符串中出现特定字符的次数
int ch_apear_times(const char *str, const char c)
{
	const char *p = strchr(str, c);
	int times = 0;
	while (p) {
		++ p; 	// 过滤字符
		++ times;
		p = strchr(p, c);
	}

	return times;
}

char * Strdup(char *str)
{
	int len = strlen(str);
	char *p = (char *)Malloc(len);
	strcpy(p, str);
	p[len] = '\0';
	return p;
	// return p;
}

// 拼接成 长度(4个字节，servant和message的长)+servant(10个字节)+message
void pack(char *dest, int len, SERVANT_TYPE servant, char *message)
{
	// char size[MESSAGE_LEN_SIZE] = {0};
	char sp[SERVANT_SIZE] = {0};
	sprintf(dest, "%04d", len);
	sprintf(sp, "0x%08X", (unsigned int)servant);
	// strcpy(dest, size);
	strcat(dest, sp);
	strcat(dest, message);
}
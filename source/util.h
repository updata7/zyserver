#ifndef UTIL_H
#define UTIL_H

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

#define SERVANT_TYPE long
#define SERVANT_SHIFT 16
#define SERVANT_SIZE 10
#define IO_MAX_MESSAGE_SIZE 4096
#define SERVANT_MASK 0xffff0000
#define MESSAGE_LEN_SIZE 4
	
int str_all_space(char *str);
void str_trim(char *str);
void str_split(const char *str, char *left, char *right, const char c);
char * Strdup(char *str);
void trim_crlf(char *str);
void str_trim_special_ch(char *str, const char c);
int ch_apear_times(const char *str, const char c);
void pack(char *dest, int len, SERVANT_TYPE servant, char *message);

#ifdef __cplusplus
}
#endif 	// __cplusplus

#endif // UTIL_H
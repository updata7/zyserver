#ifndef UTIL_H
#define UTIL_H

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus
	
int str_all_space(char *str);
void str_trim(char *str);
void str_split(const char *str, char *left, char *right, const char c);
char * Strdup(char *str);
void trim_crlf(char *str);
void str_trim_special_ch(char *str, const char c);
int ch_apear_times(const char *str, const char c);

#ifdef __cplusplus
}
#endif 	// __cplusplus

#endif // UTIL_H
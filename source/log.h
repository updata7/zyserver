#ifndef LOG_H
#define LOG_H

#ifdef __cplusplus
extern "C" {
#endif 	// __cplusplus

void log_init(const char *logpath);
void log_error(const char *fmt, ...);
void log_debug(const char *fmt, ...);
void log_info(const char *fmt, ...);
void log_warn(const char *fmt, ...);
void log_release();
#ifdef __cplusplus
}
#endif 	// __cplusplus

#endif //LOG_H
#include "server_env.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ENV_MAX 256
#define CONF_MAX 16
#define STR_MAX 1024
#define MAX_ENDPOINT_COUNT 5

struct server_env {
	char key[128];
	char value[128];
};

static struct server_env E[ENV_MAX];
static int env_index = 0;

char * get_env_value(char *key, char *def_value)
{
	int i;
	for (i = 0; i < env_index; i ++) {
		if (strcmp(key, E[i].key) == 0) {
			return E[i].value;
		}
	}

	return def_value;
}

void env_init(const char *machine_conf, const char *config)
{
	FILE *fp = fopen(machine_conf, "r");
	char line[STR_MAX] = {0};
	char key[STR_MAX] = {0};
	char value[STR_MAX] = {0};
	char left[STR_MAX] = {0}; 
	char right[STR_MAX] = {0};
	char tmp[STR_MAX] = {0};

	while (fgets(line, sizeof(line), fp) != NULL) {
		str_trim(line);
		if (!(strlen(line) == 0
				|| line[0] == '#'
				|| str_all_space(line))) {
			str_split(line, E[env_index].key, E[env_index].value, '=');
			if (strlen(E[env_index].key) == 0 || strlen(E[env_index].value) == 0) {
				fprintf(stderr, "machine_conf error: key (%s) ==== value (%s)\n", E[env_index].key, E[env_index].value);
				exit(1);
			}
			++ env_index;
			assert(env_index < ENV_MAX);
		}

		memset(line, 0, sizeof(line));
	}

	fclose(fp);

	fp = fopen(config, "r");
	while (fgets(line, sizeof(line), fp) != NULL) {
		str_trim(line);
		if (strlen(line) == 0
			|| line[0] == '#'
			|| str_all_space(line))
			continue;

		str_split(line, key, value, '=');
		if (strlen(key) == 0 || strlen(value) == 0) {
			fprintf(stderr, "config error:key (%s) ==== value (%s)\n", key, value);
			exit(1);
		}


		strcpy(E[env_index].key, key);
		if (strcmp(key, "endpointlist") == 0) {
			str_trim_special_ch(value, ';');
			do {
				str_split(value, left, right, ';');
				strcpy(tmp, left);
				strcat(E[env_index].value, get_env_value(left, ""));
				strcat(E[env_index].value, ":");
				strcat(left, "-port");
				strcat(E[env_index].value, get_env_value(left, ""));
				strcat(E[env_index].value, ":");
				strcat(tmp, "-prefix");
				strcat(E[env_index].value, get_env_value(tmp, ""));

				if (strlen(right) > 0) {
					memset(value, 0, sizeof(value));
					strcpy(value, right);
					memset(right, 0, sizeof(right));
					memset(left, 0, sizeof(left));
					strcat(E[env_index].value, ";");
				} else {
					break;
				}
			} while(1);
		} else {
			strcpy(E[env_index].value, get_env_value(value, value));
		}

		++ env_index;

		memset(line, 0, sizeof(line));
		memset(key, 0, sizeof(key));
		memset(value, 0, sizeof(value));
	}

	fclose(fp);
}
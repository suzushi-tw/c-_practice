#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 100010

int Gen(int init, char *str){
    int mul = 37;
    int mod = 1e9 + 7;
    long long ret = init;
    int len = strlen(str);

    for (int i=0; i < len; i++){
        ret = (ret * mul + str[i]) % mod;
    }

    return ret;
}

int main() {
    int T;
    char s[MAX_LEN];
    fgets(s, MAX_LEN, stdin);
    sscanf(s, "%d", &T);

    for (int t = 0; t < T; t++) {
        fgets(s, MAX_LEN, stdin);
        int len = strlen(s);
        if (s[len - 1] == '\n') s[len - 1] = '\0';

        int N = 1, M = 2; 
        int pos = 0;
        char *ptr = s;

        
        if (strncmp(ptr, "for", 3) == 0) {
           
            ptr = strstr(ptr, "int");
            ptr = strstr(ptr, "=");
            ptr++;
            N = atoi(ptr);

            ptr = strstr(ptr, ";");
            ptr++;
            ptr = strstr(ptr, "<");
            ptr++;
            M = atoi(ptr);

            ptr = strstr(ptr, "printf");
        }

        
        ptr = strstr(ptr, "printf");
        ptr = strchr(ptr, '\"');
        ptr++;
        char format_str[MAX_LEN];
        int idx = 0;
        while (*ptr != '\"') {
            format_str[idx++] = *ptr++;
        }
        format_str[idx] = '\0';

       
        ptr++;
        char args_str[MAX_LEN];
        idx = 0;
        if (strchr(ptr, ',')) {
            ptr = strchr(ptr, ',');
            ptr++;
            while (*ptr != ')') {
                if (*ptr != ' ' && *ptr != '\n') {
                    args_str[idx++] = *ptr;
                }
                ptr++;
            }
            args_str[idx] = '\0';
        } else {
            args_str[0] = '\0';
        }

      
        char *args[100];
        int arg_count = 0;
        if (strlen(args_str) > 0) {
            char *token = strtok(args_str, ",");
            while (token != NULL) {
                args[arg_count++] = token;
                token = strtok(NULL, ",");
            }
        }

      
        int ans = 0;
        for (int i = N; i < M; i++) {
            char temp_str[MAX_LEN];
            int temp_idx = 0;
            int arg_idx = 0;
            for (int j = 0; format_str[j] != '\0'; j++) {
                if (format_str[j] == '%' && (format_str[j+1] == 'd' || format_str[j+1] == 'c')) {
                    if (format_str[j+1] == 'd') {
                        char num_str[20];
                        if (strcmp(args[arg_idx], "i") == 0) {
                            sprintf(num_str, "%d", i);
                        } else {
                            sprintf(num_str, "%d", atoi(args[arg_idx]));
                        }
                        strcpy(&temp_str[temp_idx], num_str);
                        temp_idx += strlen(num_str);
                    } else if (format_str[j+1] == 'c') {
                        char ch;
                        if (strcmp(args[arg_idx], "i") == 0) {
                            ch = (char)i;
                        } else if (args[arg_idx][0] == '\'') {
                            ch = args[arg_idx][1];
                        } else {
                            ch = (char)atoi(args[arg_idx]);
                        }
                        temp_str[temp_idx++] = ch;
                    }
                    j++;
                    arg_idx++;
                } else {
                    temp_str[temp_idx++] = format_str[j];
                }
            }
            temp_str[temp_idx] = '\0';
            ans = Gen(ans, temp_str);
        }
        printf("%d\n", ans);
    }
    return 0;
}
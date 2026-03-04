#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 128
#define MAX_KEY_LENGTH 32
#define MAX_VALUE_LENGTH 64
#define MAX_COMMAND_LENGTH 16

typedef struct {
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];
    bool is_set;
} ConfigEntry;

#define MAX_CONFIG_ENTRIES 10
ConfigEntry config_db[MAX_CONFIG_ENTRIES];
int num_config_entries = 0;

void init_config_db() {
    printf("Initializing config database...\n");
    for (int i = 0; i < MAX_CONFIG_ENTRIES; ++i) {
        config_db[i].is_set = false;
    }
    num_config_entries = 0;
}

int set_config_entry(const char* key, const char* value) {
    if (num_config_entries >= MAX_CONFIG_ENTRIES) {
        fprintf(stderr, "Error: Config database is full.\n");
        return -1;
    }

    for (int i = 0; i < num_config_entries; ++i) {
        if (config_db[i].is_set && strcmp(config_db[i].key, key) == 0) {
            strcpy(config_db[i].value, value);
            printf("Updated config: %s = %s\n", key, value);
            return 0;
        }
    }

    strcpy(config_db[num_config_entries].key, key);
    strcpy(config_db[num_config_entries].value, value);
    config_db[num_config_entries].is_set = true;
    num_config_entries++;

    printf("Added config: %s = %s\n", key, value);
    return 0;
}

const char* get_config_entry(const char* key) {
    for (int i = 0; i < num_config_entries; ++i) {
        if (config_db[i].is_set && strcmp(config_db[i].key, key) == 0) {
            return config_db[i].value;
        }
    }
    return NULL;
}

void process_line(char* line) {
    char* token = strtok(line, " \t=\n");

    if (token == NULL) {
        return;
    }

    char command[MAX_COMMAND_LENGTH];
    strcpy(command, token);

    char* value_token = strtok(NULL, "=\n");
    if (value_token != NULL && strchr(line, '=') != NULL) {
         char* key_val_line = strdup(line);
         char* key = strtok(key_val_line, "=");
         char* value = strtok(NULL, "\n");

         if (key && value) {
             set_config_entry(key, value);
         } else {
             fprintf(stderr, "Warning: Invalid key=value format: %s\n", line);
         }

    } else {
        if (strcmp(command, "print") == 0) {
            char* key_to_print = strtok(NULL, " \n");

            if (key_to_print) {
                const char* value = get_config_entry(key_to_print);
                if (value) {
                    printf("Value for %s: %s\n", key_to_print, value);
                } else {
                    printf("Key '%s' not found.\n", key_to_print);
                }
            } else {
                fprintf(stderr, "Error: 'print' command requires a key argument.\n");
            }
        } else {
            fprintf(stderr, "Warning: Unknown command or format: %s\n", command);
        }
    }
}

int main() {
    init_config_db();

    char* input_lines[] = {
        "user=admin",
        "password=secure_password123",
        "server=192.168.1.100",
        "port=8080",
        "print user",
        "print server",
        "print non_existent_key",
        "long_key_name_that_exceeds_max_key_length=some_value",
        "another_key=short_value",
        "user=new_admin_user",
        "command_too_long_for_buffer_abcdefghijklmnopqrstuvwxyz=value",
        "print password",
        "just_a_command_without_equals",
        NULL
    };

    printf("Processing input lines...\n");
    for (int i = 0; input_lines[i] != NULL; ++i) {
        char line_copy[MAX_LINE_LENGTH];
        strcpy(line_copy, input_lines[i]);

        printf("\nProcessing line: \"%s\"\n", input_lines[i]);
        process_line(line_copy);
    }

    printf("\nFinal config database state:\n");
    for (int i = 0; i < MAX_CONFIG_ENTRIES; ++i) {
        if (config_db[i].is_set) {
             printf("Entry %d: Key='%s', Value='%s'\n", i, config_db[i].key, config_db[i].value);
        }
    }

    return 0;
}
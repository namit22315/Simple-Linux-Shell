#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h> // for time tracking

// Structure for history
struct History {
    char commands[20][1200];
    int count;
};

// Structure to store PID, execution time, and duration
struct History2 {
    pid_t pids[20];
    time_t execution_time[20];
    double execution_duration[20];
    int count;
};

void remove_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// Function to execute a single command and record its PID, execution time, and duration
char* execute_command(char *command, struct History *history, struct History2 *history2) {
    char* result = (char*)malloc(1200 + 1);  // +1 for null terminator

    // Check if the command ends with "&"
    int run_in_background = 0;
    int command_length = strlen(command);
    if (command_length > 1 && command[command_length - 1] == '&') {
        run_in_background = 1;
        // Remove the "&" from the command
        command[command_length - 1] = '\0';
    }

    // Add the command to history
    if (history->count < 20) {
        strncpy(history->commands[history->count], command, 1200);
        history->count++;
    } else {
        // If the history is full, remove the oldest command
        for (int i = 0; i < 20 - 1; i++) {
            strncpy(history->commands[i], history->commands[i + 1], 1200);
        }
        strncpy(history->commands[20 - 1], command, 1200);
    }

    // Record the start time
    time_t start_time = time(NULL);

    // Check if the command starts with '#!/bin/bash'
    if (strncmp(command, "#!/bin/bash", 11) == 0) {
        // This is a shebang line, which does not need to be executed directly
        // snprintf(result, 1200, "%s\tShebang line, not executed directly\n", command);
    } else {
        // Fork a child process to execute the command
        pid_t pid = fork();

        if (pid == -1) {
            printf("fork");
        } else if (pid == 0) {
            // Child process
            // Use the system shell to execute the command
            int exec_result = system(command);

            if (exec_result == -1) {
                printf("system failure");
                exit(EXIT_FAILURE);
            } else {
                exit(WEXITSTATUS(exec_result));
            }
        } else {
            // Parent process
            // Record the PID and execution start time
            history2->pids[history2->count] = pid;
            history2->execution_time[history2->count] = start_time;

            if (run_in_background == 0) {
                int status;
                waitpid(pid, &status, 0);

                if (!WIFEXITED(status)) {
                    snprintf(result, 1200, "%s\tCommand did not exit normally\n", command);
                } else {
                    // Record the execution duration
                    time_t end_time = time(NULL);
                    double duration = difftime(end_time, start_time);
                    history2->execution_duration[history2->count] = duration;

                    snprintf(result, 1200, "\n" );
                }
            } else {
                // If the command is running in the background, don't wait for it
                snprintf(result, 1200, "%s\tCommand running in the background with PID: %d\n", command, pid);
            }
        }
    }

    history2->count++;
    return result;
}

void add_to_history(struct History *history, char *command) {
    if (history->count < 20) {
        strncpy(history->commands[history->count], command, 1200);
        history->count++;
    } else {
        // If the history is full, remove the oldest command
        for (int i = 0; i < 20 - 1; i++) {
            strncpy(history->commands[i], history->commands[i + 1], 1200);
        }
        strncpy(history->commands[20 - 1], command, 1200);
    }
}

// Function to execute a shell script
void execute_bash(char *script_name, struct History *history, struct History2 *history2) {
    FILE *script_file = fopen(script_name, "r");
    if (script_file) {
        char script_command[1200];

        while (fgets(script_command, sizeof(script_command), script_file) != NULL) {
            // Remove the trailing newline character
            remove_newline(script_command);

            // Execute the command from the script file
            char *result = execute_command(script_command, history, history2);
            printf("%s", result);
            free(result);
        }

        fclose(script_file);
    } else {
        printf("Error: Unable to open script file '%s'\n", script_name);
    }
}

int main() {
    char command[1200];

    // Initialize the command history
    struct History history;
    history.count = 0;

    // Initialize the History2
    struct History2 history2;
    history2.count = 0;

    do {
        printf("Shell>");
        fgets(command, sizeof(command), stdin);
        remove_newline(command);

        if (strcmp(command, "exit") == 0) {
            // Display the History2 (PID, execution time, duration)
            for (int i = 0; i < history2.count; i++) {
                printf("\nCommand %d:\n", i + 1);
                printf("%s \n",history.commands[i]);
                printf("PID: %d\n", history2.pids[i]);
                printf("Execution Time: %s", asctime(localtime(&history2.execution_time[i])));
                printf("Execution Duration: %.2f seconds\n", history2.execution_duration[i]);
            }
            break; // Exit the shell
        } else if (strstr(command, ".sh") != NULL && strstr(command, "./")) {
            // The command contains ".sh", indicating a script file
            execute_bash(command, &history, &history2);
        } else if (strcmp(command, "history") == 0) {
            // Display the command history
            printf("Command History:\n");
            for (int i = 0; i < history.count; i++) {
                printf("%d: %s\n", i + 1, history.commands[i]);
            }
        } else {
            // Execute the command and get the result
            char *result = execute_command(command, &history, &history2);
            printf("%s", result);
            free(result);
        }
    } while (1);

    return 0;
}

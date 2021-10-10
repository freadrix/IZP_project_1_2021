#include <stdio.h>
#include <stdlib.h>

typedef struct stats{
    int diffrent_symbols;
    int min_lenth;
    double avg_lenth;
} stats;

int lenth_of_str(char* str) {
    // return lenth of str but only if str < 100 symbols
    int i;
    for (i = 0; i < 100; i++) {
        if ((int) str[i] == 0 || (int) str[i] == 3) {
            break;
        }
    }
    return i;
}

int convert_to_num(char* argv) {
    // convert string of numbers to int number
    int lenth = lenth_of_str(argv);
    int number = 0;
    for (int i = 0; i < lenth; i ++) {
        if (argv[0] == '-') {
            i += 1;
            number += -((int) argv[i] - 48);
            continue;
        }
        number *= 10;
        number += (int) argv[i] - 48;
    }
    return number;
}

int check_arguments(int argc, char** argv) {
    // function check if program get all argumets he need
    if (argc < 3) {
        printf("Program require min 2 arg, but got only %d\n", argc - 1);
        return 1;
    }
    int first_arg_num = convert_to_num(argv[1]);
    int second_arg_num = convert_to_num(argv[2]);
    if (first_arg_num > 4 || first_arg_num < 1) {
        printf("first arg must be 1 <= arg <= 4, but it is %d\n", first_arg_num);
        return 1;
    }
    if (second_arg_num < 1) {
        printf("second arg must be positiv num, but is is %d\n", second_arg_num);
        return 1;
    }
    if (first_arg_num == 2 && second_arg_num > 4) {
        printf("if first arg is equal 2 then second arg cant be more then 4 but he is %d\n",  second_arg_num);
        return 1;
    }
    return 0;
}

int count_passwords() {
    // function count passwords
    int count_of_pass = 0;
    char buf[101];
    while (fgets(buf, 101, stdin) != NULL) {
        count_of_pass += 1;
    }
    rewind(stdin);
    return count_of_pass;
}

int count_diff_symbols() {
    // function count diffrent symbols in passwords
    int hash[128] = { 0 };
    int i, c = 0;
    char buf[101];
    int ascii_num;
    while (fgets(buf, 101, stdin) != NULL) {
        char* str = buf;
        int lenth = lenth_of_str(str) - 1;
        for (i = 0; i < lenth; i++) {
            ascii_num = (int) str[i];
            hash[ascii_num] = 1;
        }
    }
    for (i = 0; i < 128; i++) {
        c += hash[i];
    }
    rewind(stdin);
    return c;
}

void get_stats() {
    // function write statistic in console
    stats statistic;
    int sum_of_lenth = 0;
    int count_of_passes = count_passwords();
    char buf[101];
    int pass_lenth;
    int min_pass_lenth = 100;
    statistic.diffrent_symbols = count_diff_symbols();
    while (fgets(buf, 101, stdin) != NULL) {
        char* pass = buf;
        pass_lenth = lenth_of_str(pass) - 1;
        if (pass_lenth < min_pass_lenth) {
            min_pass_lenth = pass_lenth;
        }
        sum_of_lenth += pass_lenth;
    }
    statistic.min_lenth = min_pass_lenth;
    statistic.avg_lenth = (double) sum_of_lenth / count_of_passes;
    printf("Statistika:\nRuznych znaku: %d\nMinimalni delka: %d\nPrumerna delka: %.1f\n",
    statistic.diffrent_symbols, statistic.min_lenth, statistic.avg_lenth);
}

int compare_strings(char* arg, char* string) {
    // function compare lenth of strings and after that compare strings
    // return 1 if something wrong
    // return 0 if everything good
    int bool_cs = 0;
    int lenth_of_arg = lenth_of_str(arg);
    int lenth_of_string = lenth_of_str(string);
    if (lenth_of_arg != lenth_of_string) {
        bool_cs = 1;
        return bool_cs;
    }
    for (int i = 0; i < lenth_of_string; i++) {
        // printf("%c\n", string[i]);
        if (arg[i] == string[i]) {
        } else {
            bool_cs = 1;
            break;
        }
    }
    return bool_cs;
}

void count_diff_group_of_symbols(char* str, int lenth, int diff_symbols[]) {
    // function count diffrent symbols
    // diff_symbols[0] - little_letter
    // diff_symbols[1] - big_letter
    // diff_symbols[2] - numbers
    // diff_symbols[3] - any_others
    for (int i = 0; i < lenth - 1; i++) {
        int ascii_num = (int) str[i];
        if (ascii_num >= 32 && ascii_num <= 126) {
            if (ascii_num >= 97 && ascii_num <= 122) {
                diff_symbols[0] += 1;
            } else if (ascii_num >= 65 && ascii_num <= 90) {
                diff_symbols[1] += 1;
            } else if (ascii_num >= 48 && ascii_num <= 57) {
                diff_symbols[2] += 1;
            } else {
                diff_symbols[3] += 1;
            }
        }
    }
}

int count_max_sequence(char* str, int lenth) {
    // function count max sequence of same symbols
    int sequence = 1;
    char c;
    for (int i = 0; i < lenth - 1; i++) {
        if (str[i] == c) {
            sequence += 1;
        }
        c = str[i];
    }
    return sequence;
}

int contains_substring(char* str, int lenth, int substring_size) {
    // function will return 0 if string doesn't contain a substring
    // of lenth substring_size two or more time
    // and return 1 if does
    char substring[substring_size];
    int matchs = 0;
    for (int i = 0; i < lenth - (substring_size); i++) {
        int tmp_num_for_i = i;
        for (int j = 0; j < substring_size; j++) {
            substring[j] = str[tmp_num_for_i + j];
        }
        for (int k = i + substring_size; k < lenth - (substring_size); k++) {
            int tmp_num_for_k = k;
            for (int l = 0; l < substring_size; l++) {
                if (substring[l] == str[tmp_num_for_k + l]) {
                    matchs += 1;
                }
            }
            if (matchs == substring_size) {
                return 0;
            }
            matchs = 0;
        }
    }
    return 1;
}

void safe_level_1(char* str, int symbols[]) {
    // function check 1 level safety
    if (symbols[0] != 0 && symbols[1] != 0) {
        printf("%s", str);
    }

}

void safe_level_2(char* str, int symbols[], int criterion_number) {
    // function check 2 level safety
    if (criterion_number <= 2) {
        safe_level_1(str, symbols);
    } else if (criterion_number == 3) {
        if (symbols[2] != 0 || symbols[3] != 0) {
            safe_level_1(str, symbols);
        }
    } else {
        if (symbols[2] != 0 && symbols[3] != 0) {
            safe_level_1(str, symbols);
        }
    }
}

void safe_level_3(char* str, int lenth, int symbols[], int criterion_number) {
    // function check 3 level safety
    int max_sequence = count_max_sequence(str, lenth);
    if (max_sequence < criterion_number) {
        safe_level_2(str, symbols, criterion_number);
    }
}

void safe_level_4(char* str, int lenth, int symbols[], int criterion_number) {
    // function check 4 level safety
    if (contains_substring(str, lenth, criterion_number)) {
        safe_level_3(str, lenth, symbols, criterion_number);
    }
}

void check_pass(char** argv) {
    // function check passwords is valid
    int safe_level = convert_to_num(argv[1]);
    int criterion_number = convert_to_num(argv[2]);
    // printf("%d %d \n", safe_level, criterion_number);
    char buf[101];
    while (fgets(buf, 101, stdin) != NULL) {
        char* pass = buf;
        int lenth = lenth_of_str(pass);
        int symbols[4] = {0, 0, 0, 0};
        count_diff_group_of_symbols(pass, lenth, symbols);
        // int max_sequence = count_max_sequence(pass, lenth);
        // int ss = contains_substring(pass, lenth, criterion_number);
        switch (safe_level) {
            case 1:
                safe_level_1(pass, symbols);
                break;
            case 2:
                safe_level_2(pass, symbols, criterion_number);
                break;
            case 3:
                safe_level_3(pass, lenth, symbols, criterion_number);
                break;
            case 4:
                safe_level_4(pass, lenth, symbols, criterion_number);
                break;
        }
    }
    rewind(stdin);
}


int main(int argc, char** argv) {
    // printf("Hellne %s %s %s count of arg is %d\n", argv[1], argv[2], argv[3], argc);
    int cansel = check_arguments(argc, argv);
    if (cansel) {
        return 1;
    }
    check_pass(argv);
    if (argc >= 4) {
        char* string = "--stats";
        if (! compare_strings(argv[3], string)) {
            get_stats();
        }
    }
    return 0;
}

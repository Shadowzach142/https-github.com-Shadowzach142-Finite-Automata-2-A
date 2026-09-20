
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    Q0,
    Q1,
    Q2,
    Q3,
    Q4,
    QTRAP
} State;

State transition(State current, char c) {
    switch (current) {
        case Q0:
            if (c == '/') return Q1;
            return QTRAP;

        case Q1:
            if (c == '*') return Q2;
            return QTRAP;

        case Q2:
            if (c == 'a' || c == '/') return Q2;
            if (c == '*') return Q3;
            return QTRAP;

        case Q3:
            if (c == 'a') return Q2;
            if (c == '*') return Q3;
            if (c == '/') return Q4;
            return QTRAP;

        case Q4:
            return QTRAP; // Extra characters after closing comment go to qtrap

        case QTRAP:
            return QTRAP;
    }
    return QTRAP;
}

bool run_dfa(const char *input) {
    State current = Q0;
    for (int i = 0; input[i] != '\0'; i++) {
        current = transition(current, input[i]);
    }
    return current == Q4;
}

int main() {
    const char *test_cases[] = {
        "/*a*/",       // ACCEPT
        "/**/",        // ACCEPT
        "/***/",       // ACCEPT
        "/*a*a*/",     // ACCEPT
        "/*a/a*/",     // ACCEPT
        "/**",         // REJECT
        "/*/",         // REJECT
        "/**/a",       // REJECT
        "//aaaa"       // REJECT
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        bool result = run_dfa(test_cases[i]);
        printf("Input: %-12s Result: %s\n", test_cases[i], result ? "ACCEPT" : "REJECT");
    }

    return 0;
}


// Sample Output:
// Input: /*a*/        Result: ACCEPT
// Input: /**/         Result: ACCEPT
// Input: /***/        Result: ACCEPT
// Input: /*a*a*/      Result: ACCEPT
// Input: /*a/a*/      Result: ACCEPT
// Input: /**          Result: REJECT
// Input: /*/          Result: REJECT
// Input: /**/a        Result: REJECT
// Input: //aaaa       Result: REJECT

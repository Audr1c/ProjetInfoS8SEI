#!/bin/bash

GREEN="\e[32m"
RED="\e[31m"
RESET="\e[0m"

run_test() {
    i=$1
    shift
    name=$@
    echo "Test n°$i of $name"
    $name > output/o${i}.txt

    if diff output_check/o${i}.txt output/o${i}.txt; then
        echo -e "${GREEN}PASSED${RESET}"
    else
        echo -e "${RED}FAILED${RESET}"
        exit 1
    fi
}

# Exemples d'appels
run_test 1 ./prog/regexp-match.exe a* aaaab
run_test 2 ./prog/regexp-match.exe a*b aaaab
run_test 3 ./prog/regexp-match.exe a*bb aaaab
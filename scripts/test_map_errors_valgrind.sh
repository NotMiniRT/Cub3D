#!/bin/bash

RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
CYAN='\033[1;36m'
NC='\033[0m'

EXECUTABLE_MANDATORY="./cub3D"
EXECUTABLE_BONUS="./cub3D_bonus"
BONUS_MODE=false
MAP_TYPE="mandatory"

for arg in "$@"; do
    case $arg in
        -b|--bonus)
            BONUS_MODE=true
            MAP_TYPE="bonus"
            ;;
    esac
done

if [ $BONUS_MODE = true ]; then
    EXECUTABLE="$EXECUTABLE_BONUS"
else
    EXECUTABLE="$EXECUTABLE_MANDATORY"
fi

ERROR_MAPS_DIR="./assets/${MAP_TYPE}/map_errors"
TOTAL_MAPS=0
PASSED_MAPS=0
VALGRIND_ERRORS=0

mkdir -p scripts/logs
mkdir -p scripts/logs/valgrind/${MAP_TYPE}

echo -e "${CYAN}Cleaning up previous ${MAP_TYPE} Valgrind logs...${NC}"
rm -f scripts/logs/valgrind/${MAP_TYPE}/*

TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
LOG_FILE="scripts/logs/${MAP_TYPE}_map_error_tests_${TIMESTAMP}.log"
VALGRIND_SUMMARY="scripts/logs/valgrind_${MAP_TYPE}_summary_${TIMESTAMP}.log"
VALGRIND_OPTS="--leak-check=full -s --track-fds=yes --trace-children=yes --track-origins=yes --show-mismatched-frees=yes --suppressions=.valgrind_suppress.txt"

if ! command -v valgrind &> /dev/null; then
    echo -e "${YELLOW}Warning: Valgrind is not installed. Skipping memory leak checks.${NC}"
    echo "Warning: Valgrind is not installed. Skipping memory leak checks." >> $LOG_FILE
    RUN_VALGRIND=0
else
    RUN_VALGRIND=1
fi

echo "${MAP_TYPE^} Map Error Tests - $(date)" > $LOG_FILE
echo "Using executable: $EXECUTABLE" >> $LOG_FILE
echo "===============================" >> $LOG_FILE

if [ $RUN_VALGRIND -eq 1 ]; then
    echo "${MAP_TYPE^} Valgrind Summary - $(date)" > $VALGRIND_SUMMARY
    echo "Using executable: $EXECUTABLE" >> $VALGRIND_SUMMARY
    echo "===============================" >> $VALGRIND_SUMMARY
fi

echo -e "${CYAN}Starting ${MAP_TYPE} map error tests...${NC}"
echo -e "${CYAN}Using executable: ${NC}$EXECUTABLE"

if [ ! -f "$EXECUTABLE" ]; then
    echo -e "${RED}Error: Executable $EXECUTABLE not found. Please compile the project first.${NC}"
    if [ $BONUS_MODE = true ]; then
        echo -e "${RED}For bonus mode, run 'make bonus' to create $EXECUTABLE${NC}"
    else
        echo -e "${RED}For mandatory mode, run 'make' to create $EXECUTABLE${NC}"
    fi
    echo "Error: Executable $EXECUTABLE not found. Please compile the project first." >> $LOG_FILE
    exit 1
fi

if [ $BONUS_MODE = true ] && [ ! -f ".bonus" ]; then
    echo -e "${YELLOW}Warning: Testing bonus maps but .bonus file not found.${NC}"
    echo -e "${YELLOW}Consider running 'make bonus' first.${NC}"
    echo "Warning: Testing bonus maps but .bonus file not found." >> $LOG_FILE
fi

if [ ! -d "$ERROR_MAPS_DIR" ]; then
    echo -e "${RED}Error: Directory $ERROR_MAPS_DIR not found.${NC}"
    echo "Error: Directory $ERROR_MAPS_DIR not found." >> $LOG_FILE
    exit 1
fi

declare -a VALGRIND_LOGS=()

shopt -s dotglob
for map_file in "$ERROR_MAPS_DIR"/*; do
    if [[ "$(basename "$map_file")" == "." || "$(basename "$map_file")" == ".." ]]; then
        continue
    fi

    if [ -f "$map_file" ]; then
        MAP_NAME=$(basename "$map_file")
        TOTAL_MAPS=$((TOTAL_MAPS + 1))
        echo -e "${CYAN}Testing map: ${NC}$MAP_NAME"
        echo -e "\n[TEST] Testing map: $MAP_NAME" >> $LOG_FILE

        ERROR_OUTPUT=$("$EXECUTABLE" "$map_file" 2>&1 >/dev/null)
        EXIT_CODE=$?

        echo "Output: $ERROR_OUTPUT" >> $LOG_FILE
        echo "Exit code: $EXIT_CODE" >> $LOG_FILE

        if echo "$ERROR_OUTPUT" | grep -q "Error"; then
            echo -e "${GREEN}✓ Test passed: Error detected correctly${NC}"
            echo "PASS: Error detected correctly" >> $LOG_FILE
            PASSED_MAPS=$((PASSED_MAPS + 1))
        else
            echo -e "${RED}✗ Test failed: No error message detected${NC}"
            echo -e "${RED}Output was: ${NC}$ERROR_OUTPUT"
            echo "FAIL: No error message detected" >> $LOG_FILE
        fi

        if [ $RUN_VALGRIND -eq 1 ]; then
            echo -e "${CYAN}Running Valgrind for: ${NC}$MAP_NAME"
            VALGRIND_LOG="scripts/logs/valgrind/${MAP_TYPE}/valgrind_${MAP_NAME}_${TIMESTAMP}.log"
            VALGRIND_LOGS+=("$VALGRIND_LOG")

            bash -c "valgrind $VALGRIND_OPTS \"$EXECUTABLE\" \"$map_file\"" > "$VALGRIND_LOG" 2>&1
        fi

        echo "----------------------------------------"
        echo "----------------------------------------" >> $LOG_FILE
    fi
done
shopt -u dotglob

if [ $RUN_VALGRIND -eq 1 ]; then
    echo -e "${CYAN}Processing Valgrind logs for ${MAP_TYPE} maps...${NC}"
    DELETED_COUNT=0

    for VALGRIND_LOG in "${VALGRIND_LOGS[@]}"; do
        if [ ! -f "$VALGRIND_LOG" ]; then
            continue
        fi

        MAP_NAME=$(basename "$VALGRIND_LOG" | sed "s/valgrind_\(.*\)_$TIMESTAMP.log/\1/")

        # Using the criteria for deletion:
        # - No errors
        # - All heap blocks freed
        # - No non-zero 'still reachable'
        if grep -q "ERROR SUMMARY: 0 errors" "$VALGRIND_LOG" &&
           grep -q "All heap blocks were freed" "$VALGRIND_LOG" &&
           ! grep -E -q "still reachable:\s*[1-9]" "$VALGRIND_LOG"; then

            echo -e "${GREEN}✓ Valgrind: No memory issues in ${NC}$MAP_NAME"
            echo "Map: $MAP_NAME - Valgrind: No memory issues" >> $VALGRIND_SUMMARY
            rm "$VALGRIND_LOG"
            DELETED_COUNT=$((DELETED_COUNT + 1))
        else
            echo -e "${RED}✗ Valgrind: Memory issues detected in ${NC}$MAP_NAME"
            echo "Map: $MAP_NAME - Valgrind: Memory issues detected - See $VALGRIND_LOG" >> $VALGRIND_SUMMARY
            VALGRIND_ERRORS=$((VALGRIND_ERRORS + 1))

            ERROR_SUMMARY=$(grep "ERROR SUMMARY" "$VALGRIND_LOG" | tail -n 1)
            HEAP_SUMMARY=$(grep -A 4 "HEAP SUMMARY" "$VALGRIND_LOG" | grep "lost")
            FD_SUMMARY=$(grep "FILE DESCRIPTORS" "$VALGRIND_LOG")

            echo "  $ERROR_SUMMARY" >> $VALGRIND_SUMMARY
            [ ! -z "$HEAP_SUMMARY" ] && echo "  $HEAP_SUMMARY" >> $VALGRIND_SUMMARY
            [ ! -z "$FD_SUMMARY" ] && echo "  $FD_SUMMARY" >> $VALGRIND_SUMMARY
            echo "" >> $VALGRIND_SUMMARY
        fi
    done

    echo -e "${CYAN}Log cleanup:${NC} Deleted $DELETED_COUNT clean log(s), kept $VALGRIND_ERRORS log(s) with issues"
fi

echo -e "${CYAN}${MAP_TYPE^} test summary: ${PASSED_MAPS}/${TOTAL_MAPS} tests passed${NC}"
echo -e "\n===============================" >> $LOG_FILE
echo "${MAP_TYPE^} test summary: ${PASSED_MAPS}/${TOTAL_MAPS} tests passed" >> $LOG_FILE

if [ $RUN_VALGRIND -eq 1 ]; then
    echo -e "${CYAN}${MAP_TYPE^} Valgrind summary: ${VALGRIND_ERRORS}/${TOTAL_MAPS} maps had memory issues${NC}"
    echo -e "\n===============================" >> $VALGRIND_SUMMARY
    echo "${MAP_TYPE^} Valgrind summary: ${VALGRIND_ERRORS}/${TOTAL_MAPS} maps had memory issues" >> $VALGRIND_SUMMARY

    if [ $VALGRIND_ERRORS -gt 0 ]; then
        echo -e "${YELLOW}Detailed Valgrind logs can be found in: scripts/logs/valgrind/${MAP_TYPE}/${NC}"
    fi
fi

if [ "$PASSED_MAPS" -ne "$TOTAL_MAPS" ] || [ $VALGRIND_ERRORS -gt 0 ]; then
    if [ "$PASSED_MAPS" -ne "$TOTAL_MAPS" ]; then
        echo -e "${RED}Some ${MAP_TYPE} maps did not trigger the expected error message!${NC}"
        echo "Some ${MAP_TYPE} maps did not trigger the expected error message!" >> $LOG_FILE
    fi
    if [ $VALGRIND_ERRORS -gt 0 ] && [ $RUN_VALGRIND -eq 1 ]; then
        echo -e "${RED}Valgrind detected memory issues with some ${MAP_TYPE} maps!${NC}"
        echo "Valgrind detected memory issues with some ${MAP_TYPE} maps!" >> $VALGRIND_SUMMARY
    fi
    exit 1
else
    echo -e "${GREEN}All ${MAP_TYPE} map error tests passed successfully!${NC}"
    echo "All ${MAP_TYPE} map error tests passed successfully!" >> $LOG_FILE
    if [ $RUN_VALGRIND -eq 1 ]; then
        echo -e "${GREEN}No memory issues detected by Valgrind in ${MAP_TYPE} tests!${NC}"
        echo "No memory issues detected by Valgrind in ${MAP_TYPE} tests!" >> $VALGRIND_SUMMARY
    fi
    exit 0
fi

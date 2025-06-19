#!/bin/bash

RED='\033[1;31m'
GREEN='\033[1;32m'
CYAN='\033[1;36m'
YELLOW='\033[1;33m'
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
    CORRECT_MAPS_DIR="./assets/bonus/maps"
else
    EXECUTABLE="$EXECUTABLE_MANDATORY"
    CORRECT_MAPS_DIR="./assets/mandatory/maps"
fi

TOTAL_MAPS=0
PASSED_MAPS=0

mkdir -p scripts/logs

TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
LOG_FILE="scripts/logs/${MAP_TYPE}_correct_maps_${TIMESTAMP}.log"

echo "${MAP_TYPE^} Correct Maps Tests - $(date)" > $LOG_FILE
echo "Using executable: $EXECUTABLE" >> $LOG_FILE
echo "===============================" >> $LOG_FILE

echo -e "${CYAN}Starting ${MAP_TYPE} correct maps tests...${NC}"
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

if [ ! -d "$CORRECT_MAPS_DIR" ]; then
    echo -e "${RED}Error: Directory $CORRECT_MAPS_DIR not found.${NC}"
    echo "Error: Directory $CORRECT_MAPS_DIR not found." >> $LOG_FILE
    exit 1
fi

shopt -s dotglob
for map_file in "$CORRECT_MAPS_DIR"/*; do
    if [[ "$(basename "$map_file")" == "." || "$(basename "$map_file")" == ".." ]]; then
        continue
    fi

    if [ -f "$map_file" ]; then
        MAP_NAME=$(basename "$map_file")
        TOTAL_MAPS=$((TOTAL_MAPS + 1))
        echo -e "${CYAN}Testing map: ${NC}$MAP_NAME"
        echo -e "\n[TEST] Testing map: $MAP_NAME" >> $LOG_FILE

        OUTPUT=$("$EXECUTABLE" "$map_file" 2>&1 >/dev/null)
        EXIT_CODE=$?

        echo "Output: $OUTPUT" >> $LOG_FILE
        echo "Exit code: $EXIT_CODE" >> $LOG_FILE

        if ! echo "$OUTPUT" | grep -q "Error"; then
            echo -e "${GREEN}✓ Test passed: Map loaded correctly${NC}"
            echo "PASS: Map loaded correctly" >> $LOG_FILE
            PASSED_MAPS=$((PASSED_MAPS + 1))
        else
            echo -e "${RED}✗ Test failed: Map produced an error${NC}"
            echo -e "${RED}Output was: ${NC}$OUTPUT"
            echo "FAIL: Map produced an error" >> $LOG_FILE
        fi
        echo "----------------------------------------"
        echo "----------------------------------------" >> $LOG_FILE
    fi
done
shopt -u dotglob

echo -e "${CYAN}${MAP_TYPE^} test summary: ${PASSED_MAPS}/${TOTAL_MAPS} correct maps passed${NC}"
echo -e "\n===============================" >> $LOG_FILE
echo "${MAP_TYPE^} test summary: ${PASSED_MAPS}/${TOTAL_MAPS} correct maps passed" >> $LOG_FILE

if [ "$PASSED_MAPS" -ne "$TOTAL_MAPS" ]; then
    echo -e "${RED}Some ${MAP_TYPE} maps failed to load correctly!${NC}"
    echo "Some ${MAP_TYPE} maps failed to load correctly!" >> $LOG_FILE
    exit 1
else
    echo -e "${GREEN}All ${MAP_TYPE} maps loaded successfully!${NC}"
    echo "All ${MAP_TYPE} maps loaded successfully!" >> $LOG_FILE
    exit 0
fi

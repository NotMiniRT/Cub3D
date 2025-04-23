#!/bin/bash

# Colors for better output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Path to the executable and error maps
EXECUTABLE="./cub3D"
ERROR_MAPS_DIR="./assets/mandatory/map_errors"
TOTAL_MAPS=0
PASSED_MAPS=0

# Create logs directory if it doesn't exist
mkdir -p scripts/logs

# Timestamp for log file name
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
LOG_FILE="scripts/logs/map_error_tests_${TIMESTAMP}.log"

# Start log file with header
echo "Map Error Tests - $(date)" > $LOG_FILE
echo "===============================" >> $LOG_FILE

echo -e "${YELLOW}Starting map error tests...${NC}"

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo -e "${RED}Error: Executable $EXECUTABLE not found. Please compile the project first.${NC}"
    echo "Error: Executable $EXECUTABLE not found. Please compile the project first." >> $LOG_FILE
    exit 1
fi

# Check if error maps directory exists
if [ ! -d "$ERROR_MAPS_DIR" ]; then
    echo -e "${RED}Error: Directory $ERROR_MAPS_DIR not found.${NC}"
    echo "Error: Directory $ERROR_MAPS_DIR not found." >> $LOG_FILE
    exit 1
fi

# Test all maps in the error directory
for map_file in "$ERROR_MAPS_DIR"/*; do
    if [ -f "$map_file" ]; then
        TOTAL_MAPS=$((TOTAL_MAPS + 1))
        echo -e "${YELLOW}Testing map: ${NC}$(basename "$map_file")"
        echo -e "\n[TEST] Testing map: $(basename "$map_file")" >> $LOG_FILE

        # Run the executable with the map and capture stderr
        ERROR_OUTPUT=$("$EXECUTABLE" "$map_file" 2>&1 >/dev/null)
        EXIT_CODE=$?

        # Log the output and exit code
        echo "Output: $ERROR_OUTPUT" >> $LOG_FILE
        echo "Exit code: $EXIT_CODE" >> $LOG_FILE

        # Check if the output contains "Error" followed by a newline
        if echo "$ERROR_OUTPUT" | grep -q "Error"; then
            echo -e "${GREEN}✓ Test passed: Error detected correctly${NC}"
            echo "PASS: Error detected correctly" >> $LOG_FILE
            PASSED_MAPS=$((PASSED_MAPS + 1))
        else
            echo -e "${RED}✗ Test failed: No error message detected${NC}"
            echo -e "${RED}Output was: ${NC}$ERROR_OUTPUT"
            echo "FAIL: No error message detected" >> $LOG_FILE
        fi
        echo "----------------------------------------"
        echo "----------------------------------------" >> $LOG_FILE
    fi
done

# Print summary
echo -e "${YELLOW}Test summary: ${PASSED_MAPS}/${TOTAL_MAPS} tests passed${NC}"
echo -e "\n===============================" >> $LOG_FILE
echo "Test summary: ${PASSED_MAPS}/${TOTAL_MAPS} tests passed" >> $LOG_FILE

# Exit with error if any test failed
if [ "$PASSED_MAPS" -ne "$TOTAL_MAPS" ]; then
    echo -e "${RED}Some maps did not trigger the expected error message!${NC}"
    echo "Some maps did not trigger the expected error message!" >> $LOG_FILE
    exit 1
else
    echo -e "${GREEN}All map error tests passed successfully!${NC}"
    echo "All map error tests passed successfully!" >> $LOG_FILE
    exit 0
fi

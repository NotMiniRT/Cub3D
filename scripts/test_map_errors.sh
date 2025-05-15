#!/bin/bash

# Colors for better output
RED='\033[1;31m'
GREEN='\033[1;32m'
CYAN='\033[1;36m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Default settings
EXECUTABLE="./cub3D"
BONUS_MODE=false
VERBOSE=false
MAP_TYPE="mandatory"

# Process command line arguments
for arg in "$@"; do
    case $arg in
        -v|--verbose)
            VERBOSE=true
            ;;
        -b|--bonus)
            BONUS_MODE=true
            MAP_TYPE="bonus"
            ;;
    esac
done

# Set maps directory based on mode
ERROR_MAPS_DIR="./assets/${MAP_TYPE}/map_errors"
TOTAL_MAPS=0
PASSED_MAPS=0

# Create logs directory if it doesn't exist
mkdir -p scripts/logs

# Timestamp for log file name
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
LOG_FILE="scripts/logs/${MAP_TYPE}_map_error_tests_${TIMESTAMP}.log"

# Start log file with header
echo "${MAP_TYPE^} Map Error Tests - $(date)" > $LOG_FILE
echo "===============================" >> $LOG_FILE

echo -e "${CYAN}Starting ${MAP_TYPE} map error tests...${NC}"

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo -e "${RED}Error: Executable $EXECUTABLE not found. Please compile the project first.${NC}"
    echo "Error: Executable $EXECUTABLE not found. Please compile the project first." >> $LOG_FILE
    exit 1
fi

# If in bonus mode, check if .bonus exists to confirm bonus compilation
if [ $BONUS_MODE = true ] && [ ! -f ".bonus" ]; then
    echo -e "${YELLOW}Warning: Testing bonus maps but executable may not be compiled with bonus features.${NC}"
    echo -e "${YELLOW}Consider running 'make bonus' first.${NC}"
    echo "Warning: Testing bonus maps but executable may not be compiled with bonus features." >> $LOG_FILE
fi

# Check if error maps directory exists
if [ ! -d "$ERROR_MAPS_DIR" ]; then
    echo -e "${RED}Error: Directory $ERROR_MAPS_DIR not found.${NC}"
    echo "Error: Directory $ERROR_MAPS_DIR not found." >> $LOG_FILE
    exit 1
fi

# Test all maps in the error directory including hidden files
shopt -s dotglob  # Enable dotglob to include hidden files in glob patterns
for map_file in "$ERROR_MAPS_DIR"/*; do
    # Skip directory entries . and ..
    if [[ "$(basename "$map_file")" == "." || "$(basename "$map_file")" == ".." ]]; then
        continue
    fi

    if [ -f "$map_file" ]; then
        TOTAL_MAPS=$((TOTAL_MAPS + 1))
        echo -e "${CYAN}Testing map: ${NC}$(basename "$map_file")"
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
            # Only show error message in verbose mode
            if $VERBOSE; then
                echo -e "${YELLOW}Program output:"
                echo -e "${NC}$ERROR_OUTPUT"
            fi
            echo "PASS: Error detected correctly" >> $LOG_FILE
            PASSED_MAPS=$((PASSED_MAPS + 1))
        else
            echo -e "${RED}✗ Test failed: No error message detected${NC}"
            # Always show output for failed tests
            echo -e "${RED}Output was: ${NC}$ERROR_OUTPUT"
            echo "FAIL: No error message detected" >> $LOG_FILE
        fi
        echo "----------------------------------------"
        echo "----------------------------------------" >> $LOG_FILE
    fi
done
shopt -u dotglob  # Disable dotglob when done

# Print summary
echo -e "${CYAN}${MAP_TYPE^} test summary: ${PASSED_MAPS}/${TOTAL_MAPS} tests passed${NC}"
echo -e "\n===============================" >> $LOG_FILE
echo "${MAP_TYPE^} test summary: ${PASSED_MAPS}/${TOTAL_MAPS} tests passed" >> $LOG_FILE

# Exit with error if any test failed
if [ "$PASSED_MAPS" -ne "$TOTAL_MAPS" ]; then
    echo -e "${RED}Some ${MAP_TYPE} maps did not trigger the expected error message!${NC}"
    echo "Some ${MAP_TYPE} maps did not trigger the expected error message!" >> $LOG_FILE
    exit 1
else
    echo -e "${GREEN}All ${MAP_TYPE} map error tests passed successfully!${NC}"
    echo "All ${MAP_TYPE} map error tests passed successfully!" >> $LOG_FILE
    exit 0
fi

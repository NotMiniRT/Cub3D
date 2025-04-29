#!/bin/bash

# Colors for better output
RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
CYAN='\033[1;36m'
NC='\033[0m' # No Color

# Path to the executable and error maps
EXECUTABLE="./cub3D"
ERROR_MAPS_DIR="./assets/mandatory/map_errors"
TOTAL_MAPS=0
PASSED_MAPS=0
VALGRIND_ERRORS=0

# Create logs directory if it doesn't exist
mkdir -p scripts/logs
mkdir -p scripts/logs/valgrind

# Clean up previous Valgrind logs
echo -e "${CYAN}Cleaning up previous Valgrind logs...${NC}"
rm -f scripts/logs/valgrind/*

# Timestamp for log file name
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
LOG_FILE="scripts/logs/map_error_tests_${TIMESTAMP}.log"
VALGRIND_SUMMARY="scripts/logs/valgrind_summary_${TIMESTAMP}.log"

# Valgrind options
VALGRIND_OPTS="--leak-check=full --show-leak-kinds=all --track-fds=yes --errors-for-leak-kinds=all --show-mismatched-frees=yes"

# Check if valgrind is installed
if ! command -v valgrind &> /dev/null; then
	echo -e "${YELLOW}Warning: Valgrind is not installed. Skipping memory leak checks.${NC}"
	echo "Warning: Valgrind is not installed. Skipping memory leak checks." >> $LOG_FILE
	RUN_VALGRIND=0
else
	RUN_VALGRIND=1
fi

# Start log file with header
echo "Map Error Tests - $(date)" > $LOG_FILE
echo "===============================" >> $LOG_FILE

if [ $RUN_VALGRIND -eq 1 ]; then
	echo "Valgrind Summary - $(date)" > $VALGRIND_SUMMARY
	echo "===============================" >> $VALGRIND_SUMMARY
fi

echo -e "${CYAN}Starting map error tests...${NC}"

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

# Array to track which valgrind logs have errors
declare -a VALGRIND_LOGS=()

# Test all maps in the error directory including hidden files
shopt -s dotglob  # Enable dotglob to include hidden files in glob patterns
for map_file in "$ERROR_MAPS_DIR"/*; do
	# Skip directory entries . and ..
	if [[ "$(basename "$map_file")" == "." || "$(basename "$map_file")" == ".." ]]; then
		continue
	fi

	if [ -f "$map_file" ]; then
		MAP_NAME=$(basename "$map_file")
		TOTAL_MAPS=$((TOTAL_MAPS + 1))
		echo -e "${CYAN}Testing map: ${NC}$MAP_NAME"
		echo -e "\n[TEST] Testing map: $MAP_NAME" >> $LOG_FILE

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

		# Run valgrind if available
		if [ $RUN_VALGRIND -eq 1 ]; then
			echo -e "${CYAN}Running Valgrind for: ${NC}$MAP_NAME"
			VALGRIND_LOG="scripts/logs/valgrind/valgrind_${MAP_NAME}_${TIMESTAMP}.log"
			VALGRIND_LOGS+=("$VALGRIND_LOG")

			# Run Valgrind in a completely new shell process and redirect both stdout and stderr to the log file
			bash -c "valgrind $VALGRIND_OPTS \"$EXECUTABLE\" \"$map_file\"" > "$VALGRIND_LOG" 2>&1
		fi

		echo "----------------------------------------"
		echo "----------------------------------------" >> $LOG_FILE
	fi
done
shopt -u dotglob  # Disable dotglob when done

# Process Valgrind logs
if [ $RUN_VALGRIND -eq 1 ]; then
    echo -e "${CYAN}Processing Valgrind logs...${NC}"
    DELETED_COUNT=0

    for VALGRIND_LOG in "${VALGRIND_LOGS[@]}"; do
        if [ ! -f "$VALGRIND_LOG" ]; then
            continue
        fi

        MAP_NAME=$(basename "$VALGRIND_LOG" | sed "s/valgrind_\(.*\)_$TIMESTAMP.log/\1/")

        # Using the criteria from the second script for deletion:
        # - No errors
        # - All heap blocks freed
        # - No non-zero 'still reachable'
        if grep -q "ERROR SUMMARY: 0 errors" "$VALGRIND_LOG" &&
           grep -q "All heap blocks were freed" "$VALGRIND_LOG" &&
           ! grep -E -q "still reachable:\s*[1-9]" "$VALGRIND_LOG"; then

            echo -e "${GREEN}✓ Valgrind: No memory issues in ${NC}$MAP_NAME"
            echo "Map: $MAP_NAME - Valgrind: No memory issues" >> $VALGRIND_SUMMARY
            # Remove the log file if no issues were found
            rm "$VALGRIND_LOG"
            DELETED_COUNT=$((DELETED_COUNT + 1))
        else
            echo -e "${RED}✗ Valgrind: Memory issues detected in ${NC}$MAP_NAME"
            echo "Map: $MAP_NAME - Valgrind: Memory issues detected - See $VALGRIND_LOG" >> $VALGRIND_SUMMARY
            VALGRIND_ERRORS=$((VALGRIND_ERRORS + 1))

            # Extract key information from valgrind log for the summary
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

# Print summary
echo -e "${CYAN}Test summary: ${PASSED_MAPS}/${TOTAL_MAPS} tests passed${NC}"
echo -e "\n===============================" >> $LOG_FILE
echo "Test summary: ${PASSED_MAPS}/${TOTAL_MAPS} tests passed" >> $LOG_FILE

if [ $RUN_VALGRIND -eq 1 ]; then
	echo -e "${CYAN}Valgrind summary: ${VALGRIND_ERRORS}/${TOTAL_MAPS} maps had memory issues${NC}"
	echo -e "\n===============================" >> $VALGRIND_SUMMARY
	echo "Valgrind summary: ${VALGRIND_ERRORS}/${TOTAL_MAPS} maps had memory issues" >> $VALGRIND_SUMMARY

	if [ $VALGRIND_ERRORS -gt 0 ]; then
		echo -e "${YELLOW}Detailed Valgrind logs can be found in: scripts/logs/valgrind/${NC}"
	fi
fi

# Exit with error if any test failed or valgrind detected issues
if [ "$PASSED_MAPS" -ne "$TOTAL_MAPS" ] || [ $VALGRIND_ERRORS -gt 0 ]; then
	if [ "$PASSED_MAPS" -ne "$TOTAL_MAPS" ]; then
		echo -e "${RED}Some maps did not trigger the expected error message!${NC}"
		echo "Some maps did not trigger the expected error message!" >> $LOG_FILE
	fi
	if [ $VALGRIND_ERRORS -gt 0 ] && [ $RUN_VALGRIND -eq 1 ]; then
		echo -e "${RED}Valgrind detected memory issues with some maps!${NC}"
		echo "Valgrind detected memory issues with some maps!" >> $VALGRIND_SUMMARY
	fi
	exit 1
else
	echo -e "${GREEN}All map error tests passed successfully!${NC}"
	echo "All map error tests passed successfully!" >> $LOG_FILE
	if [ $RUN_VALGRIND -eq 1 ]; then
		echo -e "${GREEN}No memory issues detected by Valgrind!${NC}"
		echo "No memory issues detected by Valgrind!" >> $VALGRIND_SUMMARY
	fi
	exit 0
fi

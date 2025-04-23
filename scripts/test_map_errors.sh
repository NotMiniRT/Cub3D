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

echo -e "${YELLOW}Starting map error tests...${NC}"

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo -e "${RED}Error: Executable $EXECUTABLE not found. Please compile the project first.${NC}"
    exit 1
fi

# Check if error maps directory exists
if [ ! -d "$ERROR_MAPS_DIR" ]; then
    echo -e "${RED}Error: Directory $ERROR_MAPS_DIR not found.${NC}"
    exit 1
fi

# Test all maps in the error directory
for map_file in "$ERROR_MAPS_DIR"/*; do
    if [ -f "$map_file" ]; then
        TOTAL_MAPS=$((TOTAL_MAPS + 1))
        echo -e "${YELLOW}Testing map: ${NC}$(basename "$map_file")"

        # Run the executable with the map and capture stderr
        ERROR_OUTPUT=$("$EXECUTABLE" "$map_file" 2>&1 >/dev/null)

        # Check if the output contains "Error" followed by a newline
        if echo "$ERROR_OUTPUT" | grep -q "Error"; then
            echo -e "${GREEN}✓ Test passed: Error detected correctly${NC}"
            PASSED_MAPS=$((PASSED_MAPS + 1))
        else
            echo -e "${RED}✗ Test failed: No error message detected${NC}"
            echo -e "${RED}Output was: ${NC}$ERROR_OUTPUT"
        fi
        echo "----------------------------------------"
    fi
done

# Print summary
echo -e "${YELLOW}Test summary: ${PASSED_MAPS}/${TOTAL_MAPS} tests passed${NC}"

# Exit with error if any test failed
if [ "$PASSED_MAPS" -ne "$TOTAL_MAPS" ]; then
    echo -e "${RED}Some maps did not trigger the expected error message!${NC}"
    exit 1
else
    echo -e "${GREEN}All map error tests passed successfully!${NC}"
    exit 0
fi

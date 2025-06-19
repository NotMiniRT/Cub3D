#!/bin/bash

RED='\033[1;31m'
GREEN='\033[1;32m'
CYAN='\033[1;36m'
YELLOW='\033[1;33m'
NC='\033[0m'

EXECUTABLE_MANDATORY="./cub3D"
EXECUTABLE_BONUS="./cub3D_bonus"
BONUS_MODE=false
VERBOSE=false
MAP_TYPE="mandatory"

# Check des arguments du script pour les options
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

# Modification de l'executable en fonction de l'activation de l'option ou non
if [ $BONUS_MODE = true ]; then
    EXECUTABLE="$EXECUTABLE_BONUS"
else
    EXECUTABLE="$EXECUTABLE_MANDATORY"
fi

ERROR_MAPS_DIR="./assets/${MAP_TYPE}/map_errors"
TOTAL_MAPS=0
PASSED_MAPS=0

# Dossier de logs/infos pour les logs
mkdir -p scripts/logs
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
LOG_FILE="scripts/logs/${MAP_TYPE}_map_error_tests_${TIMESTAMP}.log"

# Header des fichiers de log
echo "${MAP_TYPE^} Map Error Tests - $(date)" > $LOG_FILE
echo "Using executable: $EXECUTABLE" >> $LOG_FILE
echo "===============================" >> $LOG_FILE

echo -e "${CYAN}Starting ${MAP_TYPE} map error tests...${NC}"
echo -e "${CYAN}Using executable: ${NC}$EXECUTABLE"

# Verif que l'executable existe
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

# Meme chose pour le binaire bonus
if [ $BONUS_MODE = true ] && [ ! -f ".bonus" ]; then
    echo -e "${YELLOW}Warning: Testing bonus maps but .bonus file not found.${NC}"
    echo -e "${YELLOW}Consider running 'make bonus' first.${NC}"
    echo "Warning: Testing bonus maps but .bonus file not found." >> $LOG_FILE
fi

# Check que les maps de test existent
if [ ! -d "$ERROR_MAPS_DIR" ]; then
    echo -e "${RED}Error: Directory $ERROR_MAPS_DIR not found.${NC}"
    echo "Error: Directory $ERROR_MAPS_DIR not found." >> $LOG_FILE
    exit 1
fi

# Test toutes les maps
shopt -s dotglob  # Accepte les fichiers cachés
for map_file in "$ERROR_MAPS_DIR"/*; do
    if [[ "$(basename "$map_file")" == "." || "$(basename "$map_file")" == ".." ]]; then
        continue
    fi

    if [ -f "$map_file" ]; then
        TOTAL_MAPS=$((TOTAL_MAPS + 1))
        echo -e "${CYAN}Testing map: ${NC}$(basename "$map_file")"
        echo -e "\n[TEST] Testing map: $(basename "$map_file")" >> $LOG_FILE

        ERROR_OUTPUT=$("$EXECUTABLE" "$map_file" 2>&1 >/dev/null)
        EXIT_CODE=$?

        echo "Output: $ERROR_OUTPUT" >> $LOG_FILE
        echo "Exit code: $EXIT_CODE" >> $LOG_FILE

        # Check si l'output trouve une erreur
        if echo "$ERROR_OUTPUT" | grep -q "Error"; then
            echo -e "${GREEN}✓ Test passed: Error detected correctly${NC}"
            if $VERBOSE; then
                echo -e "${YELLOW}Program output:"
                echo -e "${NC}$ERROR_OUTPUT"
            fi
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
shopt -u dotglob

# Resumé
echo -e "${CYAN}${MAP_TYPE^} test summary: ${PASSED_MAPS}/${TOTAL_MAPS} tests passed${NC}"
echo -e "\n===============================" >> $LOG_FILE
echo "${MAP_TYPE^} test summary: ${PASSED_MAPS}/${TOTAL_MAPS} tests passed" >> $LOG_FILE

if [ "$PASSED_MAPS" -ne "$TOTAL_MAPS" ]; then
    echo -e "${RED}Some ${MAP_TYPE} maps did not trigger the expected error message!${NC}"
    echo "Some ${MAP_TYPE} maps did not trigger the expected error message!" >> $LOG_FILE
    exit 1
else
    echo -e "${GREEN}All ${MAP_TYPE} map error tests passed successfully!${NC}"
    echo "All ${MAP_TYPE} map error tests passed successfully!" >> $LOG_FILE
    exit 0
fi

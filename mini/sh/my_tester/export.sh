#!/usr/bin/env bash

GREEN='\e[1;32m'
RED='\e[1;31m'
CYAN='\e[1;36m'
RESET='\e[0m'
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
MINISHELL="$SCRIPT_DIR/../minishell"
USE_VALGRIND=1

# Préparation du fichier résumé
timestamp=$(date +"%Y-%m-%d_%H-%M")
RESULT_FILE="$SCRIPT_DIR/results/export_summary_$timestamp.txt"
mkdir -p "$SCRIPT_DIR/results"

echo -e "${CYAN}=== 🚀 Test EXPORT ===${RESET}"

tests=(
  'export'
  'export blabla ; env'
  'export blabla ; export'
  'export bla=la ; export'
  'export bla=st ; export'
  'export just= ; export'
  'export just= ; env'
  'export iiiiiiiiiiiiiiii bloup= ; export'
  'export iiiiiiiiiiiiiiii bloup= ; env'
  'export 23=45'
  'export | grep "HOME"'
  'export ""'
  'export ='
  'export %'
  'export $?'
  'export ?=2'
  'export 42nana= ; export'
  'export nanade42=jolies ; export'
  'export _olalala=bipbip ; export'
  'export dep@rt=newyork'
  'export -vacances=ausoleil'
  'export ala-=plage'
  'export avec.un=mojito '
  'export +estce=unbonus'
  'export moni = lily'
  'export moni =lily'
  'export moni=li ly ; export'
  'export moni= lily ; export'
  'export maison=$HOME'
  'export maison=$HOMEsweethome'
  'export maison=sweet$HOMEhome'
  'export my$USERis=moni'
)

expected_failures=(6 7 8 9 10 12 13 14 15)

expect() { [[ "$output" == *"$1"* ]]; }

total=0
success=0
failed=()

for i in "${!tests[@]}"; do
  ((total++))
  t="${tests[$i]}"
  n=$((i+1))
  echo -e "${CYAN}[Test $n]${RESET} $t"

  if [[ "$t" == \!* ]]; then
    cmd="${t:2}"
    output=$(echo "$cmd; exit" | $MINISHELL 2>&1)
    status=$?
    if [[ $status -ne 0 ]]; then
      echo -e "  ${GREEN}✅ échec attendu${RESET}"
      ((success++))
    else
      echo -e "  ${RED}❌ aurait dû échouer${RESET}"
      failed+=("[Test $n] $t")
    fi
  else
    output=$(echo -e "${t%%||*}\nexit" | $MINISHELL 2>&1)
    if [[ -n "${t##*||}" ]] && ! eval "${t##*||}"; then
      echo -e "  ${RED}❌ ECHEC${RESET}"
      failed+=("[Test $n] $t")
    else
      echo -e "  ${GREEN}✅ OK${RESET}"
      ((success++))
    fi
  fi
done

# Résumé affiché à l'écran
echo -e "\n${CYAN}=== Résumé EXPORT ===${RESET}"
if (( ${#failed[@]} == 0 )); then
  echo -e "${GREEN}🎉 Tous les tests ont réussi !${RESET}"
  echo "🎉 Tous les tests ont réussi !" > "$RESULT_FILE"
else
  for f in "${failed[@]}"; do
    echo -e "${RED}❌ $f${RESET}"
    echo "❌ $f" >> "$RESULT_FILE"
  done
fi

echo -e "\n📊 ${GREEN}$success/$total réussis${RESET}"
echo "📊 $success/$total tests réussis" >> "$RESULT_FILE"

# Code de sortie pour run_all_tests.sh
if (( success < total )); then
  exit 1
else
  exit 0
fi

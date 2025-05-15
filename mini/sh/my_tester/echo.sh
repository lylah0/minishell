#!/usr/bin/env bash

if [[ -t 1 ]]; then
  GREEN='\e[1;32m'
  RED='\e[1;31m'
  CYAN='\e[1;36m'
  RESET='\e[0m'
else
  GREEN=""
  RED=""
  CYAN=""
  RESET=""
fi

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
MINISHELL="$SCRIPT_DIR/../minishell"

printf "\n${CYAN}=== 🚀 Tests ECHO (minishell) ===${RESET}\n\n"

tests=(
  "echo hello        world           !"
  "echo            hello"
  "echo \"              \" pisselit"
  "echo"
  "echo 1"
  "echo 1 3 33"
  "echo \$"
  "echo \$?"
  "echo \$?\$"
  "echo \$7USER"
  "echo \$USER"
  "echo \$USER\$PWD"
  "echo \$U"
  "echo \$U ee"
  "echo   eee"
  "echo -n hello"
  "echo -nnnn hello"
  "echo -nnnnx hello"
  "echo hello -n"
  "echo -n -n"
  "echo -n tulipe -n"
  "echo -nhello"
  "echo ---------n"
  "echo -n -nnn pamplemousse -n"
)

expected_failures=(10 13)

total=0
success=0
failed=()

for i in "${!tests[@]}"; do
  ((total++))
  cmd="${tests[$i]}"
  n=$((i+1))

  printf "${CYAN}[Test %02d]${RESET} %s\n" "$n" "$cmd"
  output=$(echo -e "$cmd\nexit" | $MINISHELL 2>&1)
  status=$?

  is_expected_failure=0
  for x in "${expected_failures[@]}"; do
    if [[ "$n" -eq "$x" ]]; then
      is_expected_failure=1
      break
    fi
  done

  if [[ $status -eq 0 && $is_expected_failure -eq 0 ]]; then
    printf "  ${GREEN}✅ OK${RESET} → $output\n"
    ((success++))
  elif [[ $status -ne 0 && $is_expected_failure -eq 1 ]]; then
    printf "  ${GREEN}✅ Échec attendu${RESET} → status=$status\n"
    ((success++))
  else
    printf "  ${RED}❌ ECHEC${RESET} → status=$status\n"
    failed+=("[Test $n] $cmd")
  fi
done

printf "\n${CYAN}=== Résumé des échecs ===${RESET}\n"
if (( ${#failed[@]} == 0 )); then
  printf "${GREEN}🎉 Tous les tests ont réussi !${RESET}\n"
else
  for f in "${failed[@]}"; do
    printf "${RED}❌ %s${RESET}\n" "$f"
  done
fi

printf "\n📊 %d/%d tests réussis\n" "$success" "$total"
printf "=== ✅ Fin des tests ECHO ===\n\n"

if (( success < total )); then
  exit 1
else
  exit 0
fi

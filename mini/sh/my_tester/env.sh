#!/usr/bin/env bash

MINISHELL="./minishell"
LOGFILE="my_tester/results/env_test_$(date +"%Y-%m-%d_%H-%M").txt"

mkdir -p "$(dirname "$LOGFILE")"

tests=(
  "env"
  "env env"
  "env hola"
)

success=0
total=0

echo "=== TESTS ENV ===" | tee "$LOGFILE"

for i in "${!tests[@]}"; do
  ((total++))
  t="${tests[$i]}"
  echo -e "\n[Test $total] $t" | tee -a "$LOGFILE"
  output=$(echo -e "$t\nexit" | $MINISHELL 2>&1)
  echo "$output" | tee -a "$LOGFILE"

  if [[ "$output" =~ "No such file" ]]; then
    echo "✅ Échec attendu" | tee -a "$LOGFILE"
    ((success++))
  elif [[ "$output" =~ error|command\ not\ found|segfault ]]; then
    echo "❌ ECHEC" | tee -a "$LOGFILE"
  else
    echo "✅ OK" | tee -a "$LOGFILE"
    ((success++))
  fi
done

echo -e "\n=== Résultat : $success/$total tests réussis ===" | tee -a "$LOGFILE"

#!/usr/bin/env bash

MINISHELL="./minishell"
LOGFILE="my_tester/results/unset_test_$(date +"%Y-%m-%d_%H-%M").txt"

mkdir -p "$(dirname "$LOGFILE")"

tests=(
  "export VAR1=42; unset VAR1; echo \$VAR1"
  "export VAR2=bonjour; unset VAR2; env | grep VAR2"
  "unset NOEXIST"
  "export TEST=salut; unset TEST; export | grep TEST"
  "unset PWD; pwd"
  "unset OLDPWD; cd -"
)

success=0
total=0

echo "=== TESTS UNSET ===" | tee "$LOGFILE"

for i in "${!tests[@]}"; do
  ((total++))
  t="${tests[$i]}"
  echo -e "\n[Test $total] $t" | tee -a "$LOGFILE"
  output=$(echo -e "$t\nexit" | $MINISHELL 2>&1)
  echo "$output" | tee -a "$LOGFILE"

  if [[ "$output" =~ error|not\ found|invalid|segfault ]]; then
    echo "❌ ECHEC" | tee -a "$LOGFILE"
  else
    echo "✅ OK" | tee -a "$LOGFILE"
    ((success++))
  fi
done

echo -e "\n=== Résultat : $success/$total tests réussis ===" | tee -a "$LOGFILE"

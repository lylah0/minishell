#!/usr/bin/env bash

MINISHELL="./minishell"
LOGFILE="my_tester/results/exit_test_$(date +"%Y-%m-%d_%H-%M").txt"

mkdir -p "$(dirname "$LOGFILE")"

tests=(
  "exit 0"
  "exit +0"
  "exit -0"
  "exit +-0"
  "exit --1"
  "exit ++42"
  "exit '10'"
  "exit '+10'"
  "exit '++10'"
  "exit -10"
  "exit '-10'"
  "exit 1'2'3"
  "exit \"1'34'6\""
  "exit 42,42"
  "exit -\"17\""
  "exit 99999999999999"
  "exit 99999999999999
  
  "
  "exit 1"
  "exit 1000"
  "exit -00014"
  "exit +200"
  "exit 00042"
  "exit 42 42"
  "exit 42 hello"
  "exit exit"
  "exit hello"
  "exit hello you"
  "exit hello 42"
)

success=0
total=0

echo "=== TESTS EXIT ===" | tee "$LOGFILE"

for i in "${!tests[@]}"; do
  ((total++))
  t="${tests[$i]}"
  echo -e "\n[Test $total] $t" | tee -a "$LOGFILE"
  output=$(echo -e "$t" | $MINISHELL 2>&1)
  echo "$output" | tee -a "$LOGFILE"

  if [[ "$output" =~ "numeric argument required" || "$output" =~ "too many arguments" ]]; then
    echo "✅ Échec attendu" | tee -a "$LOGFILE"
    ((success++))
  elif [[ "$output" =~ error|invalid|segfault ]]; then
    echo "❌ ECHEC" | tee -a "$LOGFILE"
  else
    echo "✅ OK" | tee -a "$LOGFILE"
    ((success++))
  fi
done

echo -e "\n=== Résultat : $success/$total tests réussis ===" | tee -a "$LOGFILE"

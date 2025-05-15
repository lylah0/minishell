#!/usr/bin/env bash

MINISHELL="./minishell"
LOGFILE="my_tester/results/cd_test_$(date +"%Y-%m-%d_%H-%M").txt"

mkdir -p "$(dirname "$LOGFILE")"

tests=(
  "cd ."
  "cd ./"
  "cd ./././."
  "cd ././././"
  "cd .."
  "cd ../"
  "cd ../.."
  "cd ../."
  "cd .././././."
  "cd srcs"
  "cd srcs objs"                  # Erreur attendue : trop d'arguments
  "cd 'srcs'"
  "cd \"srcs\""
  "cd /etc"
  "cd sr"                         # probablement non existant
  "cd Makefile"                   # doit échouer (pas un dossier)
  "cd /"
  "cd '/'"
  "cd ////////"
  "cd _"
  "cd -"                          # dépend de OLDPWD
  "cd \$HOME"
  "cd \$HOME \$HOME"              # erreur attendue
  "cd \$HOME/42_works"
)

success=0
total=0

echo "=== TESTS CD ===" | tee "$LOGFILE"

for i in "${!tests[@]}"; do
  ((total++))
  t="${tests[$i]}"
  echo -e "\n[Test $total] $t" | tee -a "$LOGFILE"
  output=$(echo -e "$t\nexit" | $MINISHELL 2>&1)
  echo "$output" | tee -a "$LOGFILE"

  if [[ "$output" =~ "No such file" || "$output" =~ "not a directory" || "$output" =~ "invalid" ]]; then
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


<h1 align="center">🌿 Minishell 🌿</h1>
<p align="center"><i>Un mini Bash maison avec amour et patience</i></p>

---

## ✨ Aperçu

Minishell est une version allégée du shell Bash, développée dans le cadre du cursus 42.  
Il permet d'exécuter des commandes Unix avec redirections, pipes, variables d’environnement, et builtins.

---

## 🛠️ Compilation

```bash
cd mini/sh ; make
```

🧸 Cela génère un exécutable `./minishell`.

---

## 🚀 Lancement

```bash
./minishell
```

⤷ Vous pouvez alors exécuter des commandes comme :

```bash
ls -l | grep ".c" > fichiers_c.txt
```

---

## 🌟 Fonctionnalités

- 🎯 Commandes simples et multiples
- 🔀 Redirections : `>`, `>>`, `<`, `<<`
- 🔗 Pipes (`|`)
- 🌱 Variables d’environnement (`$HOME`, `$PATH`, etc.)
- 📦 Builtins :
  - `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- 🧠 Gestion des signaux (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- 🧹 Nettoyage mémoire (Valgrind friendly)
	depuis /sh : ``make leaks`` (make ; valgrind... ./minishell)

---

## Arborescence des dossiers et fichiers
```bash
sh
├── Makefile
├── minishell.h
└── src
    ├── exec
    │   ├── builtin
    │   │   ├── b_export
    │   │   │   ├── export.c
    │   │   │   ├── export_T_CMD_ARG.c
    │   │   │   ├── export_T_CMD.c
    │   │   │   └── export_utils.c
    │   │   ├── cd.c
    │   │   ├── echo.c
    │   │   ├── env.c
    │   │   ├── exit.c
    │   │   ├── pwd.c
    │   │   └── unset.c
    │   └── exec
    │       ├── cmd.c
    │       ├── core_exec.c
    │       ├── exec.c
    │       ├── redirections2.c
    │       ├── redirections.c
    │       ├── utils_exec2.c
    │       └── utils_exec.c
    ├── init_structures.c
    ├── main.c
    ├── parsing
    │   ├── expend.c
    │   ├── more.c
    │   ├── parsing2.c
    │   ├── parsing.c
    │   ├── path.c
    │   ├── quote2.c
    │   ├── quote.c
    │   ├── token.c
    │   ├── utils2.c
    │   ├── utils3.c
    │   └── utils.c
    ├── signaux.c
    └── utils
        ├── ft_printf_stderr.c
        ├── linked_list_env
        │   ├── init_env.c
        │   ├── lle_add_back.c
        │   ├── lle_del_one.c
        │   ├── lle_free.c
        │   ├── lle_last.c
        │   ├── lle_new.c
        │   ├── lle_new_empty.c
        │   ├── lle_new_node.c
        │   ├── lle_print.c
        │   ├── lle_search_env.c
        │   ├── lle_size.c
        │   └── lle_to_array.c
        ├── memory_management.c
        ├── utils2.c
        ├── utils3.c
        └── utils.c
```
---

## 📦 Environnement

- ✅ Norminette OK (norme 42)
- 🐧 Linux (Ubuntu 22.04)
- 🧼 Sans variables globales
- 🔒 Comportement POSIX conforme

---

## 👩‍💻 Auteurs
```bash
✿ Monica Nogueira – [monoguei](https://github.com/MoniNog)

✿ Lylah Randrianarijaona – [lylrandr](https://github.com/lylah0)
```
---

## 📄 Licence

Projet à usage pédagogique – École 42  
🔒 Ne pas redistribuer sans autorisation.

---

💗 Merci de votre attention & happy coding !

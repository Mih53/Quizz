# Quizz - Mitologia Brasileira

Descrição:

Projeto final - Laboratório de Algoritmos e Programação

Programa em C que apresenta um quiz interativo sobre figuras da mitologia brasileira: Saci, Caipora, Curupira, Iara, Cuca e Mula sem Cabeça.

Objetivo: 

Testar conhecimentos, ensinar curiosidades e se divertir com perguntas sobre cada personagem.

## Instruções de execução (Windows)

Algumas máquinas/terminais podem exibir acentuação incorreta dependendo da codificação do console.
Para garantir que os acentos apareçam corretamente, siga um destes procedimentos antes de compilar/rodar:

Opção recomendada (UTF-8 - mais portável):

1. Abra o arquivo `quiz.c` no seu editor (ex.: VS Code) e confirme que está salvo em **UTF-8 (sem BOM)**.
2. No PowerShell execute:

```powershell
chcp 65001
gcc -finput-charset=UTF-8 -fexec-charset=UTF-8 quiz.c -o quiz.exe
.\\quiz.exe
```

Opção alternativa (manter ANSI/Windows-1252):

Se o arquivo estiver em codificação ANSI (Windows-1252), use:

```powershell
chcp 1252
gcc quiz.c -o quiz.exe
.\\quiz.exe
```

Observações:
- Eu recomendo a opção UTF-8 por ser mais portável entre sistemas e terminais modernos.
- Caso compartilhe o projeto no GitHub, inclua estas instruções para os avaliadores/usuários.


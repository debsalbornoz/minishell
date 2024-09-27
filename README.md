
## Minishell 

[minishell.webm](https://github.com/user-attachments/assets/1d2f7bdd-3ab1-4b3c-8155-7191f02d140b)


# Sobre

Minishell é um shell simples desenvolvido em C, criado com o objetivo de simular um ambiente de linha de comando básico semelhante ao Bash. Este projeto proporciona uma compreensão prática dos princípios fundamentais que regem o funcionamento de um shell, incluindo a execução de comandos, o gerenciamento de processos, a manipulação de variáveis de ambiente e a interação com o sistema operacional.

O Minishell permite que os usuários executem comandos do sistema, mudem de diretórios, e gerenciem a entrada e saída de dados, oferecendo um ambiente que simula a experiência de um shell real. Durante o desenvolvimento deste projeto, foram exploradas diversas técnicas de programação, incluindo a manipulação de strings, o uso de funções do sistema para gerenciamento de processos e o tratamento de erros, garantindo robustez e confiabilidade.

## Funcionalidades

O Minishell oferece várias funcionalidades que tornam a experiência de uso interativa e prática:

- **Execução de Comandos:** Os usuários podem executar comandos simples e comandos do sistema operacional.
- **Builtins:** Suporte a builtins, como `cd` para mudança de diretório e `exit` para encerrar o shell.
- **Manipulação de Variáveis de Ambiente:** Permite a visualização e definição de variáveis de ambiente, essencial para a configuração do ambiente de execução.
- **Redirecionamento de Entrada e Saída:** Os usuários podem redirecionar a saída de comandos para arquivos e também ler entradas a partir de arquivos.
- **Pipes:** É possível encadear comandos usando pipes, permitindo que a saída de um comando seja utilizada como entrada para outro.
- **Tratamento de Erros:** Implementação de verificação de erros em operações críticas, proporcionando uma experiência mais estável e previsível.

## Instalação

Para instalar o Minishell, você precisará do compilador GCC e do utilitário Make em seu sistema. Abaixo estão os passos para configurar o ambiente:

1. Clone o repositório:

   ```
    git@github.com:debsalbornoz/minishell.git
   ```

2. Navegue até o diretório do projeto:
   ```
   cd minishell
   ```
3. Compile o projeto
   ```
   make
   ```

   Para iniciar o Minishell, execute o seguinte comando no terminal:
      ```
   ./minishell
   ```

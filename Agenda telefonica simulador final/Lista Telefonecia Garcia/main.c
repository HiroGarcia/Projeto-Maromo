#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CONTATOS 100
#define MAX_NOME 50
#define MAX_TELEFONE 15
#define MAX_EMAIL 50

typedef struct
{
  char nome[MAX_NOME];
  char telefone[MAX_TELEFONE];
  char email[MAX_EMAIL];
  int id;
} Contato;

Contato contatos[MAX_CONTATOS];
int totalContatos = 0;
int proximoID = 1;

/**
 * Função: salvarContatos
 * ----------------------
 * Salva todos os contatos no arquivo "agenda.txt".
 * Cada contato é salvo em uma nova linha no formato: id,nome,telefone,email.
 *
 *
 *
 * Passos:
 * 1. Abre o arquivo "agenda.txt" no modo de escrita ("w").
 * 2. Percorre o array de contatos até o total de contatos.
 * 3. Para cada contato, escreve no arquivo os dados formatados como: id,nome,telefone,email.
 * 4. Fecha o arquivo.
 */
void salvarContatos()
{
  FILE *file = fopen("agenda.txt", "w"); // Abre o arquivo "agenda.txt" no modo de escrita
  if (!file)                             // Verifica se o arquivo foi aberto com sucesso
  {
    printf("Erro ao abrir arquivo para escrita");

    return; // Retorna imediatamente se não conseguir abrir o arquivo
  }
  // Percorre o array de contatos e escreve os dados de cada contato no arquivo
  for (int i = 0; i < totalContatos; i++)
  {
    fprintf(file, "%d,%s,%s,%s\n", contatos[i].id, contatos[i].nome, contatos[i].telefone, contatos[i].email);
  }
  fclose(file); // Fecha o arquivo após a escrita
}

/**
 * Função: carregarContatos
 * ------------------------
 * Carrega os contatos do arquivo "agenda.txt" para a memória.
 * Cada linha do arquivo é lida e armazenada no array de contatos.
 *
 *
 *
 * Passos:
 * 1. Abre o arquivo "agenda.txt" no modo de leitura ("r").
 * 2. Se o arquivo for aberto com sucesso, lê cada linha do arquivo.
 * 3. Para cada linha, usa fscanf para ler os dados no formato: id,nome,telefone,email.
 * 4. Armazena os dados lidos no array de contatos e incrementa o contador totalContatos.
 * 5. Fecha o arquivo.
 */
void carregarContatos()
{
  FILE *file = fopen("agenda.txt", "r"); // Abre o arquivo "agenda.txt" no modo de leitura
  if (file != NULL)                      // Verifica se o arquivo foi aberto com sucesso
  {
    // Lê cada linha do arquivo até o final
    while (fscanf(file, "%d,%[^,],%[^,],%s\n", &contatos[totalContatos].id, contatos[totalContatos].nome, contatos[totalContatos].telefone, contatos[totalContatos].email) != EOF)
    {
      // Verifica se o ID do contato é maior ou igual ao próximo ID esperado
      if (contatos[totalContatos].id >= proximoID)
      {
        proximoID = contatos[totalContatos].id + 1; // Atualiza o próximo ID esperado
      }
      totalContatos++; // Incrementa o contador de contatos
    }
    fclose(file); // Fecha o arquivo após a leitura
  }
}

/**
 * Função: ComparaTextoIgnoraCapsLk
 * ------------------------
 * Compara duas strings de forma case-insensitive e verifica se str2 é uma substring de str1.
 *
 * Parâmetros:
 *    str1 - A string principal onde a busca será realizada.
 *    str2 - A string que será buscada dentro de str1.
 *
 * Retorno:
 *    Retorna 1 se str2 é uma substring de str1, 0 caso contrário.
 *
 * Passos:
 * 1. Cria cópias das strings str1 e str2 em minúsculas.
 * 2. Converte todos os caracteres das cópias para minúsculas.
 * 3. Usa a função strstr para verificar se a cópia de str2 está contida na cópia de str1.
 * 4. Libera a memória alocada para as cópias das strings.
 * 5. Retorna 1 se str2 é uma substring de str1, 0 caso contrário.
 */
int ComparaTextoIgnoraCapsLk(const char *str1, const char *str2)
{
  char *lower_str1 = strdup(str1);                     // Cria uma copia da string str1
  char *lower_str2 = strdup(str2);                     // Cria uma cópia da string str2
  for (char *p = lower_str1; *p; ++p)                  // Percorre cada caractere da cópia de str1
    *p = tolower(*p);                                  // Converte o caractere para minúsculo
  for (char *p = lower_str2; *p; ++p)                  // Percorre cada caractere da cópia de str2
    *p = tolower(*p);                                  // Converte o caractere para minúsculo
  int result = strstr(lower_str1, lower_str2) != NULL; // Verifica se a cópia de str2 é uma substring da cópia de str1, ignorando maiúsculas e minúsculas
  free(lower_str1);                                    // Libera a memória alocada para a cópia de str1
  free(lower_str2);                                    // Libera a memória alocada para a cópia de str2
  return result;                                       // Retorna 1 se str2 é uma substring de str1 (ignorando maiúsculas e minúsculas), 0 caso contrário
}

/**
 * Função: isValidNumber
 * ---------------------
 * Verifica se uma string contém apenas dígitos e espaços.
 *
 * Parâmetros:
 *    str - A string a ser verificada.
 *
 * Retorno:
 *    Retorna 1 se a string contém apenas dígitos e espaços, 0 caso contrário.
 *
 * Passos:
 * 1. Percorre cada caractere da string.
 * 2. Verifica se o caractere atual não é um dígito e não é um espaço.
 * 3. Se encontrar um caractere que não seja dígito ou espaço, retorna 0 (falso).
 * 4. Se todos os caracteres forem válidos, retorna 1 (verdadeiro).
 */
int isValidNumber(const char *str)
{
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (!isdigit(str[i]) && !isspace(str[i]))
    {
      return 0; // Retorna falso se qualquer caractere não for um dígito ou espaço
    }
  }
  return 1; // Retorna verdadeiro se todos os caracteres forem dígitos ou espaços
}

/**
 * Função: adicionarContato
 * ------------------------
 * Adiciona um novo contato à agenda.
 * Solicita ao usuário o nome, telefone e email do novo contato.
 * Verifica se o telefone contém apenas dígitos e espaços.
 * Salva o novo contato no array de contatos e atualiza o arquivo "agenda.txt".
 *
 *
 *
 * Passos:
 * 1. Verifica se a agenda está cheia (totalContatos >= MAX_CONTATOS). Se estiver, exibe uma mensagem e retorna.
 * 2. Solicita ao usuário o nome, telefone e email do novo contato.
 * 3. Remove o caractere de nova linha (\n) das entradas do usuário.
 * 4. Verifica se o telefone contém apenas dígitos e espaços usando a função isValidNumber. Se não for válido, exibe uma mensagem de erro e retorna.
 * 5. Verifica se o nome ou telefone estão vazios. Se estiverem, exibe uma mensagem de erro e retorna.
 * 6. Define o ID do novo contato (incremental).
 * 7. Adiciona o novo contato ao array de contatos e incrementa totalContatos.
 * 8. Chama a função salvarContatos para atualizar o arquivo "agenda.txt".
 * 9. Exibe uma mensagem de sucesso.
 */
void adicionarContato()
{
  if (totalContatos >= MAX_CONTATOS) // Verifica se a agenda está cheia
  {
    printf("Agenda cheia.\n");
    return; // Retorna da função, pois não é possível adicionar mais contatos
  }
  Contato novoContato; // Declara uma variável do tipo Contato para armazenar as informações do novo contato
  printf("Informe o nome do contato: ");
  fgets(novoContato.nome, MAX_NOME, stdin);              // Lê o nome fornecido pelo usuário
  novoContato.nome[strcspn(novoContato.nome, "\n")] = 0; // Remove o caractere de nova linha (\n) do nome

  printf("Informe o telefone do contato: ");
  fgets(novoContato.telefone, MAX_TELEFONE, stdin);              // Lê o telefone fornecido pelo usuário
  novoContato.telefone[strcspn(novoContato.telefone, "\n")] = 0; // Remove o caractere de nova linha (\n) do telefone

  if (!isValidNumber(novoContato.telefone)) // Verifica se o telefone contém apenas dígitos e espaços
  {
    printf("Erro: Numero de telefone invalido. Deve conter apenas digitos e espacos.\n");
    return; // Retorna da função, pois o telefone é inválido
  }

  printf("Informe o email do contato (opcional): ");
  fgets(novoContato.email, MAX_EMAIL, stdin);              // Lê o email fornecido pelo usuário
  novoContato.email[strcspn(novoContato.email, "\n")] = 0; // Remove o caractere de nova linha (\n) do email

  if (strlen(novoContato.nome) == 0 || strlen(novoContato.telefone) == 0) // Verifica se o nome ou telefone estão vazios
  {
    printf("Erro: Nome e telefone sao obrigatorios.\n");
    return; // Retorna da função, pois o nome ou telefone está vazio
  }

  novoContato.id = proximoID++;          // Define o ID do novo contato e incrementa o próximo ID
  contatos[totalContatos] = novoContato; // Adiciona o novo contato ao array de contatos
  totalContatos++;                       // Incrementa o número total de contatos

  salvarContatos(); // Salva os contatos atualizados no arquivo
  printf("Contato adicionado com sucesso.\n");
}

/**
 * Função: removerContato
 * ----------------------
 * Remove um contato da agenda com base no ID fornecido pelo usuário.
 * Ajusta os IDs dos contatos restantes após a remoção.
 * Atualiza o arquivo "agenda.txt" com a lista de contatos atualizada.
 *
 *
 *
 * Passos:
 * 1. Solicita ao usuário o ID do contato a ser removido.
 * 2. Procura o contato com o ID fornecido no array de contatos.
 * 3. Se o contato for encontrado, remove-o deslocando os contatos subsequentes para uma posição anterior.
 * 4. Decrementa totalContatos.
 * 5. Ajusta os IDs dos contatos restantes para manter a sequência correta.
 * 6. Chama a função salvarContatos para atualizar o arquivo "agenda.txt".
 * 7. Exibe uma mensagem de sucesso.
 * 8. Se o ID não for encontrado, exibe uma mensagem de erro.
 */
void removerContato()
{
  int id;
  printf("Informe o ID do contato a ser removido: ");
  scanf("%d", &id);
  getchar(); // Limpa o bufer do teclado

  int encontrado = 0;                     // Variável para controlar se o contato foi encontrado
  for (int i = 0; i < totalContatos; i++) // Loop para percorrer todos os contatos no array
  {
    if (contatos[i].id == id) // Verifica se o ID do contato atual corresponde ao ID fornecido pelo usuário
    {
      for (int j = i; j < totalContatos - 1; j++) // Loop para deslocar os contatos subsequentes para uma posição anterior
      {
        contatos[j] = contatos[j + 1]; // Move o contato para uma posição anterior
      }
      totalContatos--;  // Decrementa o número total de contatos
      salvarContatos(); // Salva as alterações no arquivo
      printf("Contato removido com sucesso.\n");
      encontrado = 1; // Define a variável encontrado como verdadeira
      break;
    }
  }
  if (!encontrado)
  {
    printf("Erro: ID nao encontrado.\n");
  }
}

/**
 * Função: buscarContato
 * ---------------------
 * Busca contatos na agenda com base em um critério fornecido pelo usuário.
 * O critério pode ser nome, telefone ou email.
 * Exibe os contatos que correspondem ao critério de busca.
 *
 *
 * Passos:
 * 1. Solicita ao usuário o critério de busca (nome, telefone ou email).
 * 2. Remove o caractere de nova linha (\n) do critério de busca.
 * 3. Percorre o array de contatos.
 * 4. Para cada contato, verifica se o critério de busca é uma substring do nome, telefone ou email (usando ComparaTextoIgnoraCapsLk).
 * 5. Se o critério de busca corresponder, exibe os dados do contato.
 * 6. Se nenhum contato for encontrado, exibe uma mensagem informando que nenhum contato foi encontrado.
 */
void buscarContato()
{
  char criterio[MAX_NOME];                                                             // Define um array para armazenar o critério de busca
  printf("Informe o nome, telefone ou email do contato que busca (apenas 1 opcao): "); // Solicita ao usuário o critério de busca
  fgets(criterio, MAX_NOME, stdin);                                                    // Lê o critério de busca fornecido pelo usuário
  criterio[strcspn(criterio, "\n")] = 0;                                               // Remove o caractere de nova linha do critério

  int encontrado = 0;                     // Variável para controlar se um contato foi encontrado
  for (int i = 0; i < totalContatos; i++) // Loop para percorrer todos os contatos no array
  {
    if (ComparaTextoIgnoraCapsLk(contatos[i].nome, criterio) || // Verifica se o critério de busca corresponde ao nome, telefone ou email do contato atual
        ComparaTextoIgnoraCapsLk(contatos[i].telefone, criterio) ||
        ComparaTextoIgnoraCapsLk(contatos[i].email, criterio))
    {
      printf("ID: %d \nNome: %s \nTelefone: %s \nEmail: %s\n", contatos[i].id, contatos[i].nome, contatos[i].telefone, contatos[i].email);
      printf("\n");
      encontrado = 1; // Define a variável encontrado como verdadeira
    }
  }
  if (!encontrado) // Se nenhum contato foi encontrado exibbe mensagem
  {
    printf("Nenhum contato encontrado com o criterio fornecido.\n");
  }
}

/**
 * Função: listarContatos
 * ----------------------
 * Lista todos os contatos na agenda.
 * Permite ao usuário escolher o critério de ordenação: nome ou id.
 * Exibe os contatos na ordem especificada.
 *
 *
 * Passos:
 * 1. Solicita ao usuário o critério de ordenação (nome ou id).
 * 2. Remove o caractere de nova linha (\n) do critério.
 * 3. Se o critério for "nome", ordena o array de contatos por nome em ordem alfabética.
 * 4. Percorre o array de contatos.
 * 5. Exibe os dados de cada contato, separando-os com uma linha em branco.
 * 6. Se não houver contatos, exibe uma mensagem informando que nenhum contato foi encontrado.
 */
void listarContatos()
{
  char criterio[MAX_NOME]; // Declara um array de caracteres para armazenar o critério de ordenação
  printf("Escolha o criterio de ordenacao (nome ou id): ");
  fgets(criterio, MAX_NOME, stdin); // Armazena no array o criterio

  criterio[strcspn(criterio, "\n")] = 0; // Remove o caractere de nova linha (\n) da entrada do usuário

  if (strcmp(criterio, "nome") == 0) // Verifica se o critério de ordenação escolhido pelo usuário é "nome"
  {
    for (int i = 0; i < totalContatos - 1; i++) // Loop para percorrer todos os contatos no array
    {
      for (int j = i + 1; j < totalContatos; j++) // Loop aninhado para comparar o contato atual com os contatos restantes
      {
        if (strcasecmp(contatos[i].nome, contatos[j].nome) > 0) // Compara os nomes dos contatos, ignorando a diferença entre maiúsculas e minúsculas
        {
          Contato temp = contatos[i]; // Armazena temporariamente o contato atual em temp
          contatos[i] = contatos[j];  // Substitui o contato atual pelo próximo contato na ordem alfabética
          contatos[j] = temp;         // Substitui o próximo contato na ordem alfabética pelo contato armazenado temporariamente em temp
        }
      }
    }
  }

  if (totalContatos == 0)
  {
    printf("Nenhum contato encontrado.\n");
  }
  else
  {
    for (int i = 0; i < totalContatos; i++) // Loop para percorrer todos os contatos no array
    {
      printf("ID: %d \nNome: %s \nTelefone: %s \nEmail: %s\n", contatos[i].id, contatos[i].nome, contatos[i].telefone, contatos[i].email); // Exibe os dados do contato atual
      printf("\n");                                                                                                                        // Adiciona uma linha em branco entre os contatos
    }
  }
}

/**
 * Função: main
 * ------------
 * Função principal do programa. Exibe um menu de opções para o usuário:
 * 1. Adicionar Contato
 * 2. Remover Contato
 * 3. Buscar Contato
 * 4. Listar Contatos
 * 5. Sair
 * Executa a função correspondente à opção escolhida pelo usuário.
 *
 * Passos:
 * 1. Chama a função carregarContatos para carregar os contatos do arquivo para a memória.
 * 2. Exibe um menu de opções em um loop do-while até que o usuário escolha sair (opção 5).
 * 3. Lê a opção escolhida pelo usuário e consome o caractere de nova linha (\n).
 * 4. Executa a função correspondente à opção escolhida:
 *    - adicionarContato: adiciona um novo contato à agenda.
 *    - removerContato: remove um contato da agenda com base no ID.
 *    - buscarContato: busca contatos na agenda com base em um critério fornecido.
 *    - listarContatos: lista todos os contatos na agenda.
 *    - sair: exibe uma mensagem de saída e termina o programa.
 * 5. Exibe uma mensagem de erro para opções inválidas.
 */
int main()
{
  carregarContatos();
  int opcao;
  do
  {
    printf("\n1. Adicionar Contato\n2. Remover Contato\n3. Buscar Contato\n4. Listar Contatos\n5. Sair\nEscolha uma opcao: ");
    scanf("%d", &opcao);
    getchar();
    switch (opcao)
    {
    case 1:
      adicionarContato();
      break;
    case 2:
      removerContato();
      break;
    case 3:
      buscarContato();
      break;
    case 4:
      listarContatos();
      break;
    case 5:
      printf("Saindo...\n");
      break;
    default:
      printf("Opcao invalida.\n");
    }
  } while (opcao != 5);
  return 0;
}
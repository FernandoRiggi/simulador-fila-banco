# Trabalho Prático 04 - Fila do Banco

Este repositório contém um programa em C que simula uma fila de banco com duas filas de clientes (geral e prioridade), atendendo a regras específicas de priorização.

## Integrantes do Grupo:
* Fernando Souza De Riggi
* Filipe Gioanini Braga

## Descrição do Trabalho

O objetivo deste trabalho foi desenvolver um programa que simule a dinâmica de atendimento de um banco, utilizando um Tipo Abstrato de Dados (TAD) de Fila. O banco possui duas filas de clientes: uma para o público geral e outra para clientes com prioridade. Os clientes são atendidos por caixas do banco, seguindo regras específicas de priorização.

### Regras de Atendimento:
* Se a fila de prioridades estiver vazia, o primeiro cliente da fila geral é chamado.
* Se a fila de prioridades não estiver vazia, um cliente dessa fila é chamado, desde que não tenham sido chamados três clientes prioritários de forma seguida.
* Ou seja, se três prioridades forem chamados seguidamente, um cliente da fila geral deve ser chamado.
* Após um cliente geral ser chamado (depois de uma sequência de 3 prioritários), novos clientes prioritários podem ser chamados novamente.

## Requisitos de Implementação

* Todo o código foi implementado em linguagem C.
* Foi utilizado um TAD Fila (`t_queue`), com arquivos `.h` para declarações e `.c` para as implementações.
* A implementação da fila é estática circular.
* O programa principal (`bank_simulator.c`) faz uso das operações do banco utilizando este TAD Fila.
* Um `Makefile` foi incluído para facilitar a compilação do código.

## Entrada e Saída

O programa recebe comandos via entrada padrão:
* `g NOME`: Adiciona um cliente geral com o `NOME` especificado.
* `p NOME`: Adiciona um cliente prioritário com o `NOME` especificado.
* `s`: Simula a liberação de um caixa, chamando o próximo cliente da fila conforme as regras de atendimento.
* `f`: Sinaliza o encerramento do expediente do banco. Todos os clientes restantes nas filas são atendidos (sem as restrições da regra dos 3 prioritários para esvaziamento final), e a ordem em que todos os clientes foram atendidos durante o expediente é impressa.


### Exemplo de Entrada e Saída:


**Entrada:**
```
    g Rodrigo
    g Bia
    p Joel
    s
    g Fatima
    p Frederico
    p Luciana
    s
    s
    p Fabiana
    p Elen
    p Fabio
    g Valter
    s
    s
    s
    s
    s
    s
    s
    f
``` 
**Saída esperada:**
Joel, Frederico, Luciana, Rodrigo, Fabiana, Elen, Fabio, Bia, Fatima, Valter
## Como Compilar e Executar

Para compilar o projeto, navegue até o diretório raiz do projeto no seu terminal e execute:

```bash
make
```
Isso criará um executável chamado bank_simulator.

Para executar o programa, rode:
```bash
./bank_simulator
```
O programa aceitará comandos diretamente pelo terminal. Digite os comandos conforme os exemplos da seção de Entrada e Saída, pressionando Enter após cada um. Quando quiser encerrar o expediente e ver a saída final, digite:
```bash
f
```

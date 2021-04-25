# MC504-projeto2

## Ideia

Temos uma pilha de pedidos compartilhada, essa pilha é alimentada em intervalos de tempo X que adicionam pedidos, uma thread cliente.
Os pedidos são tomados por chefes, thread chef, que avançam o estado do pedido fazendo algumas tarefas como: pegar ingredientes, cortar, cozinhar, entrega o prato.
Vamos começar com uma lista de pedidos fixa e depois criamos a thread que alimenta essa lista.

Estruturas previstas:
- Pedido:
  - Número
  - Receita
- Receita:
  - Lista de ingredientes


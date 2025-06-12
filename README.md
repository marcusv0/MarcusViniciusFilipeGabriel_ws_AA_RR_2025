# **Estudo da Árvore Red-Black: Complexidade, Função de custo e Implementação em C**

Este projeto analisa a **árvore Red-Black**, abordando sua complexidade, função de custo, desempenho prático e implementação em C. O foco está na operação de **inserção**, com experimentações para medir o tempo de execução, a demonstração do comportamento através de gráfico e a apresentação de um algortimo que seja mais eficiente, em termos de complexidade. As execuções das experimentações foram feitas em sistemas Linux (Ubuntu 22.04.5 LTS e Arch Linux com kernel 6.14.6), porém usamos somentes os dados obtidos no Arch Linux para o foco dos estudos.

---

## **Características do Projeto**

✅ **Implementação em C da Árvore Red-Black**

* Código modular com inserção balanceada.
* Uso de rotações e recolorações para manter as propriedades da árvore.

✅ **Análise de Complexidade e Função de Custo**
A inserção em uma Red-Black Tree envolve dois passos: busca pela posição (semelhante a uma BST) e rebalanceamento (rotações + recolorações).

* **Complexidade teórica**:

  * A altura da árvore é **O(log n)**, garantindo que tanto a busca quanto o rebalanceamento tenham esse custo.
  * No pior caso, há no máximo **2 rotações** e **O(log n)** recolorações por inserção.

* **Função de custo da inserção**:
  A função total pode ser modelada como:

  $$
  C(n) = a \cdot \log_2(n) + b
  $$

  onde `a` representa o custo por comparação e ajuste, e `b` é o custo fixo de recolorações e rotações.

* **Tempo médio real medido**:
  A seguir, os tempos de execução obtidos em 13 testes, de 1 até 13 milhões de inserções:

  ```
  Inserção de 1 milhão de elementos:     0.64389 s
  Inserção de 2 milhões de elementos:    1.60182 s
  Inserção de 3 milhões de elementos:    2.70279 s
  Inserção de 4 milhões de elementos:    3.86975 s
  Inserção de 5 milhões de elementos:    5.18800 s
  Inserção de 6 milhões de elementos:    6.47804 s
  Inserção de 7 milhões de elementos:    7.91111 s
  Inserção de 8 milhões de elementos:    9.38703 s
  Inserção de 9 milhões de elementos:    10.69200 s
  Inserção de 10 milhões de elementos:   12.19318 s
  Inserção de 11 milhões de elementos:   13.85909 s
  Inserção de 12 milhões de elementos:   15.50094 s
  Inserção de 13 milhões de elementos:   17.27467 s
  ```

  Os dados mostram uma **tendência de crescimento quase linear**, reflexo da baixa constante associada ao fator logarítmico em grandes `n`, confirmando a complexidade **O(log n)**.
  
✅ **Cálculo da Altura Máxima da Árvore Red-Black**

A altura de uma árvore Red-Black é no máximo 2 ⋅ log₂(n+1). Esse cálculo fundamenta-se nas propriedades estruturais da árvore e demonstra o balanceamento eficiente que garante a complexidade logarítmica.

* Propriedades Fundamentais:

Altura preta: Todos os caminhos de um nó até suas folhas possuem o mesmo número de nós pretos.

Se a altura preta (ℎᵦ) de uma árvore é o número de nós pretos no caminho mais longo da raiz até qualquer folha, então:
h ≤ 2 ⋅ hᵦ
Isso ocorre porque os nós vermelhos não podem ser consecutivos.

Número mínimo de nós em uma Red-Black Tree:
O número mínimo de nós (n) para uma altura ℎᵦ é dado por:
n ≥ 2^hᵦ - 1

* Derivação:

Relacionando ℎᵦ com o número de nós (n):
hᵦ ≤ log₂(n+1)

Substituindo ℎᵦ na equação da altura total ℎ:
h ≤ 2 ⋅ log₂(n+1)

* Conclusão:
A altura máxima ℎ de uma árvore Red-Black com n nós é:
h ≤ 2 ⋅ log₂(n+1)
Essa relação demonstra que a árvore está balanceada, garantindo a eficiência logarítmica nas operações de busca, inserção e remoção.

* Aplicação no Projeto:

A equação fundamentou a modelagem da complexidade da inserção e foi validada por experimentações práticas.

Os tempos medidos confirmaram a proporcionalidade com O(log n).

Os gráficos apresentaram crescimento assintótico logarítmico esperado, confirmando a teoria.

✅ **Experimentação Empírica**

* Testes com diferentes tamanhos de entrada (1 até 13 milhões de elementos).
* Medição do tempo de execução real.

✅ **Gráficos de Desempenho**

* A árvore Red-Black apresenta **crescimento quase linear**, evidenciando o custo logarítmico (baixo fator multiplicativo).
<img src="https://github.com/marcusv0/MarcusViniciusFilipeGabriel_ws_AA_RR_2025/raw/main/Gr%C3%A1ficos/grafico_redblack.png" alt="Gráfico do algoritmo da árvore red-black">

---

## **Apresentação de um algoritmo mais eficiente, em termos de complexidade**

### Tabela hash: inserção com complexidade **O(1)** em média e **O(n)** no pior caso.

✅ **Tempos para a Tabela Hash (13 testes)**:

```
Inserção de 1 milhão de elementos:     0.04244 s
Inserção de 2 milhões de elementos:    0.07570 s
Inserção de 3 milhões de elementos:    0.11153 s
Inserção de 4 milhões de elementos:    0.14611 s
Inserção de 5 milhões de elementos:    0.18118 s
Inserção de 6 milhões de elementos:    0.21820 s
Inserção de 7 milhões de elementos:    0.25720 s
Inserção de 8 milhões de elementos:    0.29483 s
Inserção de 9 milhões de elementos:    0.32612 s
Inserção de 10 milhões de elementos:   0.36554 s
Inserção de 11 milhões de elementos:   0.39911 s
Inserção de 12 milhões de elementos:   0.43212 s
Inserção de 13 milhões de elementos:   0.47136 s
```

A curva é fortemente linear, reforçando o desempenho médio **O(1)** das tabelas hash.

✅ **Gráficos de Desempenho**

* A tabela hash cresce **linearmente com inclinação muito pequena**, típica de inserções O(1).
<img src="https://github.com/marcusv0/MarcusViniciusFilipeGabriel_ws_AA_RR_2025/raw/main/Gr%C3%A1ficos/grafico_hash.png" alt="Gráfico da tabela hash">
Ambos os gráficos demonstram o comportamento assintótico esperado, validando a análise teórica com base nos dados empíricos.
---

## **Como Executar os Testes**

### **Compilação**

```bash
gcc algoritmo.c -o algoritmo
gcc tabela_hash.c -o tabela_hash
```

### **Execução**

```bash
./algoritmo
./tabela_hash
```

* Ambos os programas geram estatísticas de tempo de inserção.
---

## **Principais Conclusões**

* A **árvore Red-Black** é ideal quando a ordenação dos dados e operações como busca mínima/máxima são necessárias.
* O estudo valida a complexidade **O(log n)** teórica da Red-Black Tree com experimentos reais.
* Gráficos confirmam a tendência assintótica esperada: **logarítmica** para a árvore e **linear constante** para a tabela hash.
* * A **tabela hash** se destaca em inserções massivas sem necessidade de ordenação, sendo mais rápida em média.

---

## **Autores**

* Filipe Gabriel Tomaz Brito
* Marcus Vinícius Maia dos Santos

---

import matplotlib.pyplot as plt
import numpy as np

# Dados: (número de elementos, tempo em segundos)
dados_rb = [
    (1_000_000, 0.64389),
    (2_000_000, 1.60182),
    (3_000_000, 2.70279),
    (4_000_000, 3.86975),
    (5_000_000, 5.18800),
    (6_000_000, 6.47804),
    (7_000_000, 7.91111),
    (8_000_000, 9.38703),
    (9_000_000, 10.69200),
    (10_000_000, 12.19318),
    (11_000_000, 13.85909),
    (12_000_000, 15.50094),
    (13_000_000, 17.27467),
]

# Separar os vetores
elementos_rb = np.array([n for n, t in dados_rb])
tempos_rb = np.array([t for n, t in dados_rb])

# Criar o gráfico
plt.figure(figsize=(10, 6))
plt.plot(elementos_rb, tempos_rb, marker='o', linestyle='-', color='blue', label='Árvore Red-Black')

# Ajuste de tendência linear
z_rb = np.polyfit(elementos_rb, tempos_rb, 1)
p_rb = np.poly1d(z_rb)
plt.plot(elementos_rb, p_rb(elementos_rb), "r--", label='Tendência Linear')

# Detalhes
plt.title("Tempo de Inserção - Árvore Red-Black")
plt.xlabel("Número de Elementos Inseridos")
plt.ylabel("Tempo (segundos)")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()

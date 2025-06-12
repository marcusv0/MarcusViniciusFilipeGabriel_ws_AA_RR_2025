import matplotlib.pyplot as plt
import numpy as np

# Dados: (número de elementos, tempo em segundos)
dados_hash = [
    (1_000_000, 0.04244),
    (2_000_000, 0.07570),
    (3_000_000, 0.11153),
    (4_000_000, 0.14611),
    (5_000_000, 0.18118),
    (6_000_000, 0.21820),
    (7_000_000, 0.25720),
    (8_000_000, 0.29483),
    (9_000_000, 0.32612),
    (10_000_000, 0.36554),
    (11_000_000, 0.39911),
    (12_000_000, 0.43212),
    (13_000_000, 0.47136),
]

# Separar os vetores
elementos_hash = np.array([n for n, t in dados_hash])
tempos_hash = np.array([t for n, t in dados_hash])

# Criar o gráfico
plt.figure(figsize=(10, 6))
plt.plot(elementos_hash, tempos_hash, marker='o', linestyle='-', color='green', label='Tabela Hash')

# Ajuste de tendência linear
z_hash = np.polyfit(elementos_hash, tempos_hash, 1)
p_hash = np.poly1d(z_hash)
plt.plot(elementos_hash, p_hash(elementos_hash), "r--", label='Tendência Linear')

# Detalhes
plt.title("Tempo de Inserção - Tabela Hash")
plt.xlabel("Número de Elementos Inseridos")
plt.ylabel("Tempo (segundos)")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()

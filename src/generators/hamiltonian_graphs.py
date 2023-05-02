import numpy as np


def create_hamiltonian_graph(nodes):  
    g=[[0 for i in range(nodes)] for j in range(nodes)]
    for i in range(nodes):
        for j in range(nodes):
            if i != j:
                g[i][j] = 1

    return g

def graph_to_file (m , nodes) :
    with open(f'hamiltonian/graph-{nodes}.txt', 'w') as fp:
        for edges in m:
            linked = [str(i) for i, e in enumerate(edges) if e == 1]
            fp.write(','.join(linked))
            fp.write('\n')

if __name__ == "__main__":
    for x in range(3, 13):
        m = create_hamiltonian_graph(x)
        graph_to_file(m, x)
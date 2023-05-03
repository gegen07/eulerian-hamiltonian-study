import numpy as np

def create_eulerian_graph (n_nodes = 8, max_edges = 50) :

    m = np.zeros((n_nodes,n_nodes))
    
    for i in range( len(m)-2 ) :
        a = min(max_edges, len(m)-i-1)
        n_edges = np.random.randint(1,a//2+1) * 2

        used_edges = int(np.sum(m[i][0:i])) % 2

        n_edges = max(0, n_edges - used_edges)

        edges = np.random.choice(list(range(i+1,len(m))), n_edges, replace=False)
        m[i,edges] = 1
        m[edges,i] = 1

    i = len(m)-2
    if int(np.sum(m[i][0:i])) % 2 != 0 :
        m[i,-1] = 1
        m[-1,i] = 1

    return m

def graph_to_file (m , nodes) :
    with open(f'eulerian/graph-{nodes}.txt', 'w') as fp:
        for edges in m :
            linked = [str(i) for i, e in enumerate(edges) if e == 1]
            fp.write(','.join(linked))
            fp.write('\n')

if __name__ == "__main__":
    for x in range(3, 100):
        m = create_eulerian_graph(x)
        graph_to_file(m, x)
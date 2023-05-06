#!/usr/bin/env python3
import os
import random
from pathlib import Path

import matplotlib.pyplot as plt
import networkx as nx


def random_graph(n: int, k: int) -> nx.Graph:
    """Generate a random graph of n nodes and k types of node/edge labels."""
    G = nx.watts_strogatz_graph(n, 35, 0.4)

    node_attrs = random.choices(range(k), k=n)
    for node, attr in zip(G.nodes, node_attrs):
        G.nodes[node]["node_label"] = attr

    edge_attrs = random.choices(range(k), k=G.number_of_edges())
    for edge, attr in zip(G.edges, edge_attrs):
        G[edge[0]][edge[1]]["edge_label"] = attr

    return G


def plot_graph(G: nx.Graph) -> None:
    """Needs a graphics backend like pyqt5 to actually plot"""
    pos = nx.spring_layout(G)
    node_labels = nx.get_node_attributes(G, "node_label")
    edge_labels = nx.get_edge_attributes(G, "edge_label")

    nx.draw(G, pos)
    nx.draw_networkx_labels(G, pos, labels=node_labels)
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)
    plt.show()


def write_graph(G: nx.Graph, path: Path) -> None:
    """Writes the given attributed graph in G-Finder's format."""
    with open(path, "w") as f:
        f.write(f"t 1 {G.number_of_nodes()}\n")

        for node, attr in nx.get_node_attributes(G, "node_label").items():
            f.write(f"v {node} {attr}\n")

        for edge, attr in nx.get_edge_attributes(G, "edge_label").items():
            a, b = edge
            f.write(f"e {a} {b} {attr},1;{attr},1\n")


def read_graph(path: Path) -> nx.Graph:
    """Read G-Finder's data format into a NetworkX graph."""
    with open(path, "r") as f:
        lines = f.readlines()
    n = int(lines[0].split()[-1])
    vertices = lines[1 : n + 1]
    edges = lines[n + 1 :]

    G = nx.Graph()
    for edge in edges:
        line = edge.split()
        a, b = int(line[1]), int(line[2])
        attr = int(line[3].split(";")[0].split(",")[0])
        G.add_edge(a, b, edge_label=attr)

    for vertex in vertices:
        line = vertex.split()
        a, attr = int(line[1]), int(line[2])
        G.nodes[a]["node_label"] = attr

    return G


def gen_data_graphs() -> None:
    """Write a set of synthetic data graphs."""
    sizes = [1e3]
    """,
        2.5e3,
        5e3,
        7.5e3,
        1e4,
        2.5e4,
        5e4,
        7.5e4,
        1e5,
        2.5e5,
        5e5,
        7.5e5,
        1e6,
    ]"""
    sizes = list(map(int, sizes))
    graphs = [random_graph(n, 10) for n in sizes]
    os.makedirs("data")
    for size, graph in zip(sizes, graphs):
        write_graph(graph, Path("data") / f"data_{int(size)}.format")


def random_walk_subgraph(G: nx.Graph, k: int) -> nx.Graph:
    """
    Pick a random subgraph by starting with the highest degree vertex,
    and then walking the immediate neighbors by a Gaussian distribution.
    """
    node = sorted(G.degree, key=lambda x: x[1])[-1][0]
    walk = set([node])

    last = node
    while len(walk) < k:
        last = random.choice(list(G.adj[last].keys()))
        walk.add(last)

    Q = nx.Graph(G.subgraph(walk))
    Q = nx.relabel_nodes(Q, dict(zip(list(Q.nodes), range(k))))
    return Q


def gen_subgraph_queries(G: nx.Graph):
    """Write query graphs based on the given data graph."""
    Q = random_walk_subgraph(G, 12)

    n = G.number_of_nodes()
    write_graph(Q, Path("data") / f"query_{n}_0.format")

    for i in range(1, 4):
        Q.remove_node(random.choice(list(Q.nodes)))
        k = Q.number_of_nodes()
        Q = nx.relabel_nodes(Q, dict(zip(list(Q.nodes), range(k))))
        write_graph(Q, Path("data") / f"query_{n}_{i}.format")


def main():
    gen_data_graphs()
    for data_graph in Path("data").glob("data_*"):
        G = read_graph(data_graph)
        gen_subgraph_queries(G)


if __name__ == "__main__":
    main()

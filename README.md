# GFinder

This is the implementation of paper "Liu, Lihui, Boxin Du, and Hanghang Tong. "G-Finder: Approximate Attributed Subgraph Matching." 2019 IEEE International Conference on Big Data (Big Data). IEEE, 2019.".

This Project (G-Looker) is implemented on visual studio C++ 2015, windows 10 64 bits.


This is an improvement version of origin gfinder.
In this version, we also support edge similarity, which means two edges can be mapped to each other if their attributes have high similarity.
For example, edge-type-A can mapped to edge-type-B if sim(edge-type-A, edge-type-B) >= t, where t is a threshold setted by users.


For more details please read the docx file in the project.

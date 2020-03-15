此处存放各类C++算法模板

### 图论

- [强连通分量](tested/strongly-connected-components.cpp)
- [虚树](tested/virtual-tree.cpp)（ $O(\log n)$ 的LCA，$O(1)$ 的在路上）
- [支配树](tested/dominator-tree.cpp)
- [最大流](raw/reconstruct/max-flow.cpp)
- [费用流](raw/reconstruct/min-cost-flow.cpp)
- [最小树形图](raw/minimum-arborescence.cpp)
- 边双、圆方树（在路上）
- KM（在路上）

### 字符串

- [后缀数组](raw/reconstruct/suffix-array.cpp)（Manber&Myers的倍增 $O(n\log n)$ ）
- [后缀自动机](raw/suffix_automaton.cpp)（固定字符集大小）
- [基本字串字典](raw/ipm-weak.cpp)（子串周期查询）
- [回文树](raw/palindromic_tree.cpp)
- [后缀树+LCT+线段树](raw/suffix-automaton-lct-sgt.cpp)（奇幻三合一，写的极丑，改动困难）
- 任意字符集后缀自动机（在路上）
- 算法（KMP, Manacher, Duval）（在路上）
- 找Runs（在路上）

### 数据结构

- [splay](raw/splay.cpp)
- [bitset](raw/reconstruct/bitset.cpp)
- [哈希表](raw/reconstruct/hash-table.cpp)
- [ST表](sparse_table.cpp)
- [二维数点](raw/reconstruct/two-dimensional-counting.cpp)（离线）
- [LCT](raw/lct.cpp)（makeroot、翻转子树标记）
- [LCT](raw/lct-subtree_sum.cpp)（上面的+子树和）
- 点分治（在路上）
- 分裂Treap（在路上）
- 模块化线段树（在路上）

### 数列

- [简单多项式](tested/simple-poly.cpp)（任意模数，$O(n^2)$ 乘法、取模、resultant）
- [NTT+多项式](raw/reconstruct/polynomials.cpp)（NTT模数，暂时没有插值和求值）
- [NTT+多项式](raw/polynomial-remake.cpp)（NTT模数，比上一个慢，有插值和求值）
- [FFT](raw/reconstruct/fft-complex.cpp)（啥也没有）
- [二进制变换](raw/reconstruct/binary-transform.cpp)（高维前缀和，and、or、xor、子集卷积）
- [BM](raw/BM.cpp)（ $O(n^2)$ 求解线性递推式）
- [p-recursive](raw/p-recursive-min-25.cpp)（求解p-recursive递推式，by Min25）

### 计算几何

- [整数凸包](raw/convex_hull.cpp)
- [dls的大合集](raw/Geo_std.cpp)（By dls）
- 
### 数论

- [算法](raw/number_theory.cpp)（Miller-Rabin, Pollard-Rho, 扩展欧几里得, Cipolla）
- [Min26筛](raw/min25sieve.cpp)（ $O\left(\frac{n^\frac 34}{\log n}\right)$ 的垃圾筛，能求每个 $\lfloor\frac nd\rfloor$ 的前缀和）

### 线性代数

- [取模矩阵](raw/reconstruct/mod-matrix.cpp)（任意模数，矩阵乘法、行列式、特征多项式）
- 线性基相关（在路上）

### 其他

- [拟阵交](tested/matroid-intersection.cpp)
- [高精度](raw/big-integer-other.cpp)（网上找来的，自己的一堆锅，找时间修）
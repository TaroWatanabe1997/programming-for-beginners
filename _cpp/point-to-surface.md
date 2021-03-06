---
layout: post
title: メッシュ復元アルゴリズムの概要
---

今回は、点群のデータを入力として、表面メッシュを復元する手法について紹介する。この内容は以下の2つの論文を元にした内容となっている。

* Carr et al. 2001, "Reconstruction and Representation of 3D Objects with Radial Basis Functions"
* Morse et al. 2001, "Interpolating Implicit Surfaces From Scattered Surface Data Using Compactly Supported Radial Basis Functions"

これらの論文はいずれも、三次元空間上に定義された陰関数 $f: \mathbb{R}^3 \rightarrow \mathbb{R}$を放射基底関数 (RBF, radial basis function) により補間することで表現する。陰関数が表現できたら、あとはマーチング・キューブ法などを用いて、陰関数のデータを表面メッシュに変換する。

RBFはある空間上の1点からの「距離」だけに依存する関数で、中心点 $\mathbf{c} \in \mathbb{R}^n$と関数の値を評価する点$\mathbf{x} \in \mathbb{R}^n$の間の距離$r = \| \mathbf{x} - \mathbf{c} \|$を用いて定義される。

RBFは距離だけに依存する関数一般を指すので、多様な定義の仕方が可能であり、応用に応じていろいろな定義が用いられる。例えば、

**ガウス関数** \\
$$
\phi(r) = \exp(-\beta r^2)
$$

**薄板スプライン関数 (thin-plate spline)** \\
$$
\phi(r) = r^2 \log(|r|)
$$

などがその代表例として知られる。メッシュ復元のためには、入力の点群それ自体を中心点としてRBF関数を定義し、その重み付き和により陰関数$f$を近似する。すなわち、

$$
f(\mathbf{x}) = \sum_{i=0}^{N-1} w_i \phi_i(\| \mathbf{x}_i - \mathbf{x}\|)
$$

のような形で、陰関数を表現し、$f(\mathbf{x}) = 0$となる等値面を復元される曲面とする。

上記の陰関数の定義にはパラメータとして$w_i$が含まれるので、これを入力点群のデータから求めることが必要となる。各入力頂点には、その点で陰関数が取るべき値がいくつになるのかを表す参照値$d_i$を与えておく。

この時、入力の点群は欲しい表面メッシュ上にあると考えられるので、$f(\mathbf{x}_i)$の値は全て0になるべきで、したがって$d_i = 0$であると考えられる。ところが、このような場合には、全ての$i$について$w_i = 0$となるような単純な解により、必要な条件を満たされてしまう。

そこで、入力の点群と法線の情報を用いて、点を法線方向に沿って正と負の方向にそれぞれ動かしたオフセット点の陰関数の値を$d_i = \{ 1, -1\}$として入力点群に加える。この拡張された点群の情報を用いてRBF関数による近似を行う。

実際に、上記の陰関数$f$がオフセット点を含む入力頂点上で参照値と等しい値を取るとすると、全ての頂点に対する等式をひとまとめにすることで、連立一次方程式を得ることができる。この連立一次方程式を共役勾配法などの線形ソルバーにより解くことで、最適なRBFによる陰関数の表現を見つける。

陰関数が求まれば、あとはマーチング・キューブ法などにより、曲面を三角形メッシュなどとして取り出すことが可能となる。以降では、これらのステップをより詳しく見ていく。

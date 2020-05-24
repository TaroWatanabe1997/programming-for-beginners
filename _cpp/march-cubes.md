---
layout: post
title: "マーチング・キューブ法"
---

[マーチング・キューブ法](https://dl.acm.org/doi/10.1145/37402.37422){: target="_blank" }は1987年にLorensenとClineによって提案されたアルゴリズムで、2020年現在、コンピュータ・グラフィクスのトップ・ジャーナルであるACM Transactions of Graphicsにおいて、最も引用されている論文です。

今日、マーチング・キューブ法とその発展形はCTやMRIなどで得られる三次元ボリュームデータを表面メッシュデータに置き換える方法として広く利用されています。

マーチング・キューブ法のアイディアは単純で、1つのキューブが持つ8つの頂点が表面メッシュの内側にあるのか、外側になるのかのすべてのパターンについて、どのようにメッシュが切られるべきなのかを表す辞書を用意します。

これらのパターンは単純には2の8乗、すなわち256通りのパターンが考えられるが、回転や鏡面対称のものをまとめると、以下の図に示すような15種類のデータとなる。


{% include lightbox.html src="public/images/march_cubes/march_cubes.jpg" %} \\
([『マーチングキューブ法 - Wikipedia』](https://ja.wikipedia.org/wiki/%E3%83%9E%E3%83%BC%E3%83%81%E3%83%B3%E3%82%B0%E3%82%AD%E3%83%A5%E3%83%BC%E3%83%96%E6%B3%95){: target="_blnak" }より引用)

これらの辞書の用意と、回転や考慮したメッシュへの変換は煩雑ではあるが、幸運なことに、ウェブ上に基本的な実装を含むソースコードが多数公開されている。

今回は<http://paulbourke.net/geometry/polygonise/>{: target="_blank" }で公開されているコードを元に、マーチング・キューブ法を実装していく。

## 処理の流れ

上記のウェブページに公開されているコードでは`GRIDCELL`が冒頭の図で言うところのキューブひとつに対応する。この構造体に対して、8つのコーナーの位置と、そのコーナーが持つ*ボリュームの値を`double`で格納する*。

その結果を`Polygonize`関数に閾値 (こちらも`double`型)で渡す。すると、第3引数にある三角形 (`TRIANGLE`型) の配列に対して、三角形とその頂点位置を代入してくれる。何個の三角形を生成したかは`Polygonize` 関数の戻り値に格納される。

あとは`TRIANGLE`型の配列は三角形の個数分処理して、出力の頂点リストと面を構成する頂点番号リスト(テンプレートコードではそれぞれ`vertices`と`indices`)に格納すれば良い。これらの手順を元にテンプレートのプログラムを埋めて、マーチング・キューブのプログラムを完成させよう。

## 補足: マーチング・キューブ法の拡張

マーチング・キューブ法にはいくつかの問題点が知られており、それらを解決する方法も多く提案されている。なお、CTなどのボリューム・データを扱う場合は、そもそも情報が十分に細かく、各ボクセルでマーチング・キューブを実行できるので、以下の議論を利用する場面はそれほど多くはない。

**1つ目の問題**は、特にキューブの取り方がメッシュの細かさに対して荒い場合に起こる問題で、隣あうキューブの間で三角形面が連続せずに穴が空いてしまう。この問題については以下の論文の図3を見てほしい。

Nielsen and Hamann 1991, "The Asymptotic Decider: Resolving the Ambiguity in Marching Cubes" \\
<http://web.cse.ohio-state.edu/~shen.94/788/Site/Reading_files/p83-nielson.pdf>{: target="_blank" }

上記の論文では、このような曖昧さを解決するために、曖昧となりうるパターンには複数の候補を考えておき、適宜隣のキューブが発生させた三角形ときちんと繋がるような三角形を発生させるという方法を取っている。

また、これとは違う考え方で、曖昧さの問題を解決した手法に**Marching Tetrahedra**がある。この方法は、立方体を6つの四面体に分割して、各四面体に対して面貼りのパターンを割り当てるというものである。

Treece et al. 1998, "Regularized marching tetrahedra: improved iso-surface extraction" \\
<http://svr-www.eng.cam.ac.uk/reports/svr-ftp/treece_tr333.pdf>{: target="_blank" }

四面体は頂点がそもそも4つしかないため、対称性などを考慮しなくても、パターンはたったの16種類しかなく、実装の苦労が少ないのがもう一つの特徴である。

**2つ目の問題**は、マーチング・キューブ法で細かなメッシュを再構成しようとしたときには、キューブを細かく切る以外にあまり良い方法がなく、荒いキューブでは鋭いエッジのような特徴を保持できないということである。この問題を解決するために、**Extended Marching Cubes**という方法が以下の論文で提案されている。

Kobbelt et al. 2001, "Feature Sensitive Surface Extraction from Volume Data" \\
<https://www.graphics.rwth-aachen.de/media/papers/feature1.pdf>{: target="_blank" }

この方法ではマーチング・キューブ法同様に、同じサイズのキューブを使う。まずマーチング・キューブ法でメッシュを生成し、各頂点の法線を計算する。もし各キューブ内で発生させた頂点の法線の向きが一定以上開いていたら、feature sampleと呼ばれる余剰の点を発生させて、その点とキューブ内の頂点を結んで錐形状を作る。最後に、feature sampleを含む三角形のエッジを順に見ていき、もしエッジをフリップさせたときにfeature sampleをエッジが結ぶようになるなら、フリップ結果を保存する(論文の図9を参照)。こうすることで、キューブの数を小さく保ちながらも、鋭いエッジの情報を復元することが可能となる。

上記の問題を解決する別の方法に、以下の論文で提案された**Dual Contouring**もある。

Loasso et al. 2002, "Dual Contouring of Hermite Data" \\
<https://www.cse.wustl.edu/~taoju/research/dualContour.pdf>{: target="_blank" }

この方法はExtended Marching Cubesのようにキューブの内部に点を発生させるのだが、通常のマーチング・キューブ法とは異なり、キューブのエッジ上には点を発生させない。その代わりに、両端点の符号が異なるエッジがある場合には、そのエッジを含む4つのキューブに発生させた点を結んだ四角形を生成する。この部分が"dual"という言葉が入っている所以である。

Dual Contouringは通常のマーチング・キューブでキューブの中に埋もれてしまう特徴を、キューブ内に1つずつ発生させる頂点の位置を調整することで保持することを試みる。Dual Contouringにおいては、各キューブのエッジ上のどの位置を面が通るかという情報があり、そのエッジ上の点における法線が求まっていると考える (このようなデータをHermiteデータという)。

キューブの内部で符号が切れ変わっているときに発生させる点の位置は、このエッジ上の頂点位置と法線の情報を使いQEM (quadric error metric)を減少させるように選ばれる。論文中の定義(式(1))から分かる通り、QEMが小さくなれば、各エッジ上の頂点における法線が、復元されるメッシュにおいても保たれるようになる。

Dual ContouringはHermiteデータに対してしか用いることができないが、マーチング・キューブのように三角形が発生するパターンを定義しておく必要がなく、実装の苦労が少なくて済む。

最後に紹介する方法は**Dual Marching Cubes**と呼ばれる方法で、以下の論文で提案されている。

Nielsen et al. 2004, "Dual Marching Cubes: Primal Contouring of Dual Grids" \\
<https://people.eecs.berkeley.edu/~jrs/meshpapers/SchaeferWarren.pdf>{: target="_blank" }

この方法は、これまでの方法のように同じサイズのキューブを使うのではなく、八分木上に定義される"dual grid”上でマーチング・キューブ法を実行する。八分木は上記のdual contouringでも用いられていたQEMが十分に小さくなるまで分割される。各八分木のノード内に発生させられた点をつないでいくと、dual gridが作られるので、各dual gridに対して通常のマーチング・キューブ法で三角形を発生させる。

こうすることで、より細かな特徴を持つ場所に、より細かな三角形が発生するようになり、データ量を大幅に削減することができる。ただし、dual gridを発生させる際に八分木上のノード同士の隣接関係を調べる必要があるため、実装は少し複雑になる。
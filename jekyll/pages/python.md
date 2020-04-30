---
layout: page
title: Pythonプログラミング
permalink: /python/
---

## 環境設定など

* [環境設定]({% link _python/devenv-setup.md %})

## 数独ソルバーを作る

ここでは数独の本を写真で撮影して、それを画像認識することで、自動的に数独を解くソルバーを作ります。

<table class="images">
<tr>
  <td style="text-align: center; width: 50%;">{{ '**入力画像**' | markdownify }}</td>
  <td style="text-align: center; width: 50%;">{{ '**出力画像**' | markdownify }}</td>
</tr>
<tr>
  <td>{% include lightbox.html src="/public/images/sudoku/level_3.jpg" style="width: 100%;" %}</td>
  <td>{% include lightbox.html src="/public/images/sudoku/level_3_ans.jpg" style="width: 100%;" %}</td>
</tr>
</table>

* [バイナリデータの読み込み]({% link _python/read-binary.md %})
* [ロジスティック回帰 -その1-]({% link _python/logistic-regression-01.md %})
* [ロジスティック回帰 -その2-]({% link _python/logistic-regression-02.md %})
* [画像中の図形検出]({% link _python/figure-detection.md %})
* [数独ソルバーを作る]({% link _python/solve-sudoku.md %})

## 深層学習による画像生成の基礎

* [PyTorchによるロジスティック回帰]({% link _python/logistic-regression-pytorch.md %})
* [畳み込みニューラルネット]({% link _python/convolutional-network.md %})
* [変分オートエンコーダ(VAE)]({% link _python/vae.md %})
* [敵対的生成ネットワーク(GAN)]({% link _python/gan.md %})
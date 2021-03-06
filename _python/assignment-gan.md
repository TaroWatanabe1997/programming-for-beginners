---
layout: post
title: GANによる高品質画像生成コンテスト
---

ここまでの内容をベースにより良い画像生成を目指しましょう。

## データ・セット

[Oxford flower dataset](https://www.robots.ox.ac.uk/~vgg/data/flowers/){: target="_blank" }の102カテゴリを使って行います。

## 評価方法

上記のような、10x10の画像タイル1枚を提出してもらいます。名前が分からない状態で、それを参加者に見せて、投票で優勝を決めます。投票後、参加者には各自の実装内容をプレゼンする時間を設けます。

## ルール

* マシンによる有利・不利を避けるため、学習はColabを用いて行うこととします。
  * Colabはリロードなしで90分、一定間隔でリロードしても12時間までしか使えません。
  * 一定間隔でリロードさせるためには、ブラウザ拡張のツールなどを使うと良いでしょう。
* きれいな画像が出るまで乱数をサンプルすることは認めますが、きれいな画像が出るサンプルを100個集めて、それを結果の画像に使うのは禁止とします。
* ウェブ上にあるソースコードはサンプルコードに「組み込む」というところの範囲内で使用を認めます。ただし、公開されているプログラムを、そのまま使って画像を生成することは禁止とします。

## 始め方

* Google Colaboratoryのページを開き、適当なノートを作成する。その後、Google Driveに移動し「Colab Notebooks」というフォルダが作成されていることを確認する。
* 「Colab Notebooks」の中にOxford flower datasetを展開したものを「OxfordFlower」というフォルダ名で配置する
* Colab上で学習を行う[サンプルプログラム (単純なDCGAN)](https://drive.google.com/open?id=1DOfgEWJ7MFdzDhy4K2bVy9v_fIvye40d){: target="_blank" } をダウンロードし、同じく「Colab Notebooks」に配置する。
* Colabで上記のサンプルプログラムを開き、実行してみる。上手く実行できたら、以後、これを改良して、より良い画像が生成されるように改良する。

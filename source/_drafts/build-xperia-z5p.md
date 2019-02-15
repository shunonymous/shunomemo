---
title: Xperia Z5 Premiumを買ったがカスタムROMが寂しかったのでArch Linuxで色々した話
tags: 
- "Android" 
- "Arch Linux"
- "GNU/Linux"
---

### *注意*

* 本記事中にはプロプライエタリ・ソフトウェアをインストールするよう促す内容が含まれます。

* Android端末のroot化、Bootloader Unlockは[文鎮化](https://ja.wikipedia.org/wiki/%E6%96%87%E9%8E%AE_(%E9%9B%BB%E5%AD%90%E6%A9%9F%E5%99%A8))などのリスクを伴う行為です。行う場合は自己責任でお願いします。

### プロローグ

出勤を終えて作業場へ向かうshunonymous。

疲れからか、不幸にもNexus 5が地面に追突してしまう。

後輩をかばいすべての責任を負った三浦に対し、

車の主、暴力団員谷岡に言い渡された示談の条件とは・・・。

### 一般人なのでXperia Z5 Premium\(E6853\)を買った。

というわけで5inch未満のFullHDとか4.5inch未満のHDとかなディスプレイのbootloader unlockableなスマホを探しましたが、見つからなかったので、泣く泣く片手操作を諦め、Xperia Z5 Premiumを購入しました。

勿論Global版です。キャリア端末なんて買うわけないじゃないですかーやだー。

機種の詳細なレビューは他に譲りますが1つだけ。やっぱでかいわこいつ。

なんで最近のスマホってこうも揃いも揃ってでかいんでしょう。

<blockquote class="twitter-tweet" data-lang="ja"><p lang="ja" dir="ltr">すごく…大きいです… <a href="https://t.co/Fz0DGtkkLq">pic.twitter.com/Fz0DGtkkLq</a></p>&mdash; shunonymous (@shunonymous) <a href="https://twitter.com/shunonymous/status/740865099825434624">2016年6月9日</a></blockquote>
<script async src="//platform.twitter.com/widgets.js" charset="utf-8"></script>

ちなみにExpansysで買いました。そして届いたその日のうちにBootloader Unlock。

### Bootloader Unlockしたはいいが…

sudoしないとfastbootできない問題に見舞われつつも\(結局sudoしました\)無事にUnlock成功しました。が。

[\[XDA\]Rom List : Xperia Z5 Premium Android Development](http://forum.xda-developers.com/z5-premium/development#romList)

少ねえ…

TWRPはAndroPlus様謹製のビルドがありますがver2.8.7.0で止まってます。\(執筆時点ではver3.0.2.0が最新\)

しかし、かのマリー=アントワネットはこのような言葉を遺しました。

{% blockquote マリー=アントワネット %}
ROMが無いならビルドすればいいじゃない。
{% endblockquote %}

そうです。何の心配もありません。ソースコードはあるのですから、自由ソフトウェアなのですから\(残念なことに[バイナリブロブ](https://osdn.jp/magazine/08/11/03/0424229)がてんこ盛りではありますが。\)、ビルドしちゃえば用意できます。

というわけでここからが本題です。

今回は私、shunonymousが如何にしてArch Linux上でXperia Z5 Premium向けに諸々のビルドを行ったかという内容となります。\(尚、記事は作業と平行して書いている模様。\)

### 環境

#### ビルド環境

* OS:Arch Linux (x86_64)
  * Arch Linuxはbaseグループとbase-develグループがインストールされており、諸設定が一通り終えてある事が前提です。まだの方は[さぁさぁ](https://wiki.archlinuxjp.org/index.php/%E3%82%A4%E3%83%B3%E3%82%B9%E3%83%88%E3%83%BC%E3%83%AB%E3%82%AC%E3%82%A4%E3%83%89)。
  * わざわざchrootでピカピカの環境を用意したのは内緒。
* CPU:Intel(R) Core(TM) i7-3610QM CPU @ 2.30GHz
* RAM:8GB
* Storage:HDD



#### 端末

* Xperia Z5 Premium Global (E6853)

#### ビルドするもの

* [Resurrection Remix](http://www.resurrectionremix.com/)
* [MultiRom](https://github.com/Tasssadar/multirom/tree/master)一式
	- MultiRom本体
	- TWRP MultiRom
* [AndroPlus Kernel](https://kernel.andro.plus/kitakami_r2.html)

### 準備

Android 6.0系以降をビルドする前提ですがそれ以前の物でも以下の手順で大丈夫だと思います。

まずはmultilibリポジトリを有効にしましょう。

/etc/pacman.conf内のmultilibセクションをコメントアウトし、`sudo pacman -Syu`すればオッケーです。

そして必要なパッケージをインストール。

```bash
$ sudo pacman -S git gnupg flex bison gperf sdl wxgtk squashfs-tools curl ncurses zlib schedtool perl-switch zip unzip libxslt python2-virtualenv bc gcc-multilib lib32-zlib lib32-ncurses lib32-readline rsync repo maven(CM系ROMの場合)
```

また、AURから`libtinfo` `libtinfo-5` `ncurses5-compat-libs` `lib32-ncurses5-compat-libs` をインストールしてください。インストールは[お好みの方法でどうぞ](https://wiki.archlinuxjp.org/index.php/AUR_%E3%83%98%E3%83%AB%E3%83%91%E3%83%BC)。

一部パッケージはビルド前に署名チェックを行います。

PKGBUILD内に実行すべきコマンドがありますので。

gitの設定も済ませておきましょう。

```bash
$ git config --global user.email "you@example.com"
$ git config --global user.name "Your Name"

```

#### OpenJDK

ビルドするAndroidのバージョンによって必要となるJDKのバージョンは異なります。

Android 5.0,6.0系ではJDK7、N PreviewではJDK8が必要です。

執筆時点でResurrectionRemixはAndroid 6.0.1ベースなので`jdk7-openjdk`をインストールします。

N Previewを試したくなった?

心配御無用。Arch Linuxには`archlinux-java`と呼ばれるヘルパースクリプトが用意されています。

```bash
$ sudo archlinux-java set java-8-openjdk
```

#### ビルド環境の設定

Arch wikiから丸パクですが以下を実行してください。

```bash
$ mkdir ~/bin
$ export PATH=~/bin:$PATH
$ curl https://storage.googleapis.com/git-repo-downloads/repo > ~/bin/repo
$ chmod a+x ~/bin/repo
```

pacmanからrepoをインストールする必要は果たして。

次にディレクトリをどこかに作って移動してくださいな。

```bash
$ mkdir ~/path/to/dir/
$ cd ~/path/to/dir/
```

して、Arch Linuxは最先端という点で素晴らしいディストロですが、Androidのビルドにおいてはこれが少々面倒を生みます。

Arch Linuxで単に`python`とした時、それはPython 3の事です。しかし他の多くのディストロでは未だに2.7だったりします。

AndroidのビルドにはPython 2.7が使われますのでArch Linux側に手を入れる必要があります。

```bash
$ virtualenv2 venv
```

アクティベートします。尚、これは現在のターミナルセッションでのみ有効です。

```bash
$ source venv/bin/activate
```

### ソースコードを準備するよ!

Resurrection Remix用のディレクトリ上で以下のコマンドを実行です。

```bash
$ repo init -u https://github.com/ResurrectionRemix/platform_manifest.git -b marshmallow
```

以下デバイスごとに手順が異なりますので[こちら](http://dev.maud.io/entry/2016/03/18/how-to-build-rr#3-1-各種端末向けのソースを取得する)を参考にしましょう。

今回ビルドするXperia Z5 Premiumは残念ながらCyanogenModから公式にサポートされていませんのでmanifestを用意する必要があります。

既に色々と揃っているようなのでそちらを使用します。

```bash
$ git clone https://github.com/Sony-Kitakami/android_.repo_local_manifests .repo/local_manifests
```

`repo sync`でソースコードを引っ張ってきます。

```bash
$ repo sync -jN --force-sync
```

Nには回線速度やマシンのスレッド数などに応じて数字を入れてください。

尚、デフォルトでは4となっています。

ソースコードのダウンロードにはとてもとても長い時間がかかる\(強い回線ならばそうでもないのかもしれませんが\)ので寝る前にでもやりましょう。

### ビルドするよ!

おはようございます。

もし長い間放置してしまった場合、既に何かしら更新があるかもしれませんので`repo sync`し直した方が良いかもしれません。

さて、ビルドを始めます。

```bash
$ . build/envsetup.sh && brunch <device>
```

Xperia Z5 Premiumの場合は`<device>`には`satsuki`と入れます。

ビルドにはとてもとても長い時間が(ry

ここまで正しくやっていて、なおかつ運が悪くなければビルドが通るはずです。

#### MultiRomのビルド


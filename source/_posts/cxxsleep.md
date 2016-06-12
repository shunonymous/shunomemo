---
title: C++でプログラムの動作を一定時間止める
date: 2015-12-20 04:57:01
tags: C++
---


・この記事は初心者 C++er Advent Calendar 2015 - Adventarの20日目の記事です。昨日はろっさむさん([@4_mio_11](https://twitter.com/4_mio_11))で、[C++をのぞく時、C++もまたこちらをのぞいているのだ](http://rossamu.hatenablog.com/entry/2015/12/19/161112)でした。
・勿論C++初心者が何か書いてみる方です。C++力、文章力共にアレなので生暖かい目で見守っていただければ幸いです。
・\(2016/6/12追記\)Markdownが消えたりしたので再現ついでに少々追加しました。

プログラムを書く上で処理をしばらく止めておきたい事があります。n秒にm回処理を行いたいとかそんなのです。組み込み用途\([PWM制御](https://ja.wikipedia.org/wiki/%E3%83%91%E3%83%AB%E3%82%B9%E5%B9%85%E5%A4%89%E8%AA%BF)など\)とかゲームプログラミング(FPS周りとか)とかだと多いと思います。

睡眠は大事なのです。人も、プログラミングも。

## よくある方法

プラットフォーム依存のライブラリに用意された関数を使う事が多いと思います。ググった限りはそんな感じでした。Advent Calendar前に。執筆直前に改めてググってみたら今から書くような事がトップに出てきました。なんてこったい。

[POSIX](https://ja.wikipedia.org/wiki/POSIX) APIにはsleep関数が[用意されています](http://pubs.opengroup.org/onlinepubs/009695399/functions/sleep.html)し、Win32 APIにも似たようなのが[あるっぽい](https://msdn.microsoft.com/ja-jp/library/cc429358.aspx)です。

## こいつらじゃイカンのか?

イカン(個人の感想です)。まずWindows向けに書かれたやつがUNIX(GNU/Linuxとか*BSDとかOS Xとか含む)で使えなくなります。逆もまた然り。#defineとかでごにょごにょやるのも[あまり](http://boost.cppll.jp/HEAD/libs/preprocessor/doc/topics/problems.html)[よろしくない](http://boost.cppll.jp/HEAD/libs/preprocessor/doc/topics/problems.html)方法みたいです。

それに上記の方法はどっちかというとCの方法です。C++の方法があるならそちらの方がよいでしょう。

## それ、標準ライブラリでできるよ!

使うのはchronoライブラリとthreadライブラリです。これらはC++11で入ったライブラリなので-std=c++11とかしてなんとかしてください。

``` bash
$ clang++ -std=c++11 -o sleep sleep.cpp
```

#### chrono

時間ライブラリ。[このあたり](https://cpplover.blogspot.jp/2015/01/c11-chrono.html)が詳しいです。

#### thread

スレッドを扱うライブラリ。マルチスレッドなんかもこれ使えばいけますが、今回は処理を止めるだけに使います。

## 実際にやってみた

{% include_code cxx11sleep.cpp lang:cpp cxx11sleep.cpp %}

こんな感じになります。とりあえずこれで問題は解決です。

## ところでこの関数を見てくれ。こいつをどう思う?

すごく…長いです…

やっぱり3sとか書きたいですね。

ユーザー定義リテラルでなんとかする

ユーザー定義リテラルについては[こちら](http://cpplover.blogspot.jp/2012/02/blog-post_16.html)がわかりやすいかと。

なんと、C++14のchronoライブラリには時間単位のユーザ定義リテラルが定義されています。大人の事情とかでC++14が使えない人は自前実装して圧倒的成長を果たしましょう。できちゃった人は今日から初心者を名乗るのは諦めましょう。

### なんとかしてみたコード

{% include_code cxx14sleep.cpp lang:cpp cxx14sleep.cpp %}

<s>おそらく関数エイリアスなる手法を用いればもうちょっとなんとかなる気はしますが、闇の気配を感じたのでここまでにしておきます。</s>

なんの事はありませんでした。

{% include_code newcxx14sleep.cpp lang:cpp newcxx14sleep.cpp %}

とまぁこんな感じでおしまいです。初めてのAdvent Calendar参戦&残業続きでいろいろグダグダしましたがなんとかなったかなーと思います。

明日はIさん\([@wx257osn2](https://twitter.com/wx257osn2)\)です。初心者向けの記事を期待しましょう。

### 第2版に寄せて

昔に書いた記事を見るのは恥ずかしい。

### 最後に

良い子は早く寝ような。

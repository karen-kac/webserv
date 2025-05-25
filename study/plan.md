# 📚 C++98 Webサーバ開発 学習リソース一覧

## ✅ Day 1–3: C++98基礎復習

### 🔹 メモリ管理（スマートポインタなし）
- [Effective C++（Scott Meyers）](https://www.oreilly.co.jp/books/9784873112498/)
- [C++98 における手動メモリ管理（Qiita）](https://qiita.com/yohhoy/items/7c1f0d2e4b9f29a1d2e3)

### 🔹 STL（vector, map, string）の効率的な使い方
- [cppreference STLコンテナ一覧](https://en.cppreference.com/w/cpp/container)
- [AtCoder の C++ STL 入門記事](https://qiita.com/drken/items/4a7321fa7e6c7f86c3ca)

### 🔹 例外安全なコード設計
- [Exceptional C++（Herb Sutter）](https://www.amazon.co.jp/dp/4894713023)
- [C++例外安全設計まとめ（Qiita）](https://qiita.com/yumetodo/items/cfecef6a84a03bb34615)

### 🔹 コピーコンストラクタ・代入演算子（Rule of Three）
- [Rule of Three - C++の3つの重要な関数](https://cpp-learning.com/ruleofthree/)
- 書籍：『C++プログラミングのしくみ』第9章

---

## 🛠️ Day 4–7: 実装演習

### 🔹 基本クラス設計
- [クラス設計の基本（Qiita）](https://qiita.com/nanbuwks/items/f8e2a6c609cf51b443ed)
- 書籍：『リーダブルコード』

### 🔹 std::string の効率的処理
- [cpprefjp: basic_string](https://cpprefjp.github.io/reference/string/basic_string.html)
- 『Effective STL』項目23（std::stringの効率的な使い方）

### 🔹 ファイルI/O操作（fstream）
- [fstreamの使い方まとめ（Qiita）](https://qiita.com/_EnumHack/items/52c245ed77c2a153d7de)
- 書籍：『C++標準ライブラリ（Josuttis）』

### 🔹 エラーハンドリングパターン
- [C++例外処理の基本（Qiita）](https://qiita.com/yohhoy/items/64516f79d3dba6a252d4)
- [戻り値 vs 例外 処理の使い分け](https://qiita.com/tanakah/items/78eb6623e7ae06324f96)

---

## 🏗 Day 8–14: 設計パターン応用

### 🔹 Singletonパターン（Serverクラス用）
- [Singletonパターン実装方法（Qiita）](https://qiita.com/melpon/items/1a1a8e04a1c0e7dcb886)
- 『GoF デザインパターン』

### 🔹 Factoryパターン（Response生成用）
- 書籍：『Java言語で学ぶデザインパターン入門』
- [Factory パターン解説（Qiita）](https://qiita.com/takuyanin/items/c1b531a5cba7275b185e)

### 🔹 RAIIパターン（リソース管理）
- 『Effective C++』項目13（RAIIの基本）
- [RAII入門（Qiita）](https://qiita.com/yohhoy/items/0b88a5e70984dc8a1d15)

### 🔹 Observerパターン（イベント通知）
- [Observerパターン C++ 実装（Qiita）](https://qiita.com/edo_m18/items/e8662e7cdd47879f8915)
- 『Head First デザインパターン』

---

## 🔧 補助リソース

### 📘 総合書籍
- 『Effective C++ / STL / More Effective C++』
- 『C++標準ライブラリ（Josuttis）』
- 『Modern C++ Design（Alexandrescu）』

### 🔗 公式リファレンス
- [cppreference.com（英語）](https://en.cppreference.com/)
- [cpprefjp（日本語）](https://cpprefjp.github.io/)

### 📺 動画教材
- [ドワンゴC++講座（YouTube）](https://www.youtube.com/playlist?list=PLHX6tGzB4sqXoKXuZqcnCeYslYDK5jDEu)
- [paizaラーニング：C++入門](https://paiza.jp/works/cpp/primer)

---

## 📅 学習の進め方Tips

- モダンC++に頼れないC++98環境では、手動の設計・管理力が問われる。
- 設計意図（「なぜこのクラスがあるのか？」）を意識しながら実装すること。
- `webserv` 本体コードを動かしながら、コードリーディング・模写も並行すると効果大。

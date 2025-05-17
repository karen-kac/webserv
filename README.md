# Webserv

## 概要
Webservは、C++ 98で実装したカスタムHTTPサーバーで、WebサーバーおよびHTTPプロトコルの動作原理を深く理解するために設計されています。このプロジェクトでは、クライアントリクエストの処理、静的コンテンツの提供、CGIスクリプトの実行など、様々な機能を持つサーバーを構築します。

## 機能

### 基本機能
- HTTP/1.1サーバーの完全実装
- ノンブロッキングI/Oを使用した複数の同時接続対応
- GET、POST、DELETEメソッドのサポート
- 標準的なWebブラウザとの互換性
- 静的Webサイトコンテンツの提供
- ファイルアップロード機能
- デフォルトエラーページ
- CGI実行のサポート（PHP、Pythonなど）

### 設定
- カスタム設定ファイル形式（NGINXに類似）
- 異なるホスト:ポートの組み合わせでの複数の仮想サーバー
- ルート固有の設定
- ディレクトリリスティングコントロール
- HTTPリダイレクト
- 複数ポートでのリスニング

## 技術要件

### 依存関係
- C++98対応のC++コンパイラ
- 標準C++ライブラリのみ（外部ライブラリやBoostは使用不可）

### システム対応
- Unixベースのシステム（Linux、macOS）
- macOSのwrite()処理に対する特別な対応

## ビルド方法

```bash
# リポジトリをクローン
git clone <リポジトリURL> webserv
cd webserv

# サーバーをビルド
make

# デフォルト設定で実行
./webserv

# カスタム設定ファイルで実行
./webserv path/to/config
```

## 設定ファイル形式

設定ファイルではサーバーの様々な側面を設定できます。基本的な例を以下に示します：

```
# サーバー設定例
server {
    listen 8080;
    server_name example.com;
    
    error_page 404 /404.html;
    client_max_body_size 10M;
    
    location / {
        root /var/www/html;
        index index.html;
        allowed_methods GET POST;
    }
    
    location /upload {
        root /var/www/uploads;
        allowed_methods POST;
        upload_store /var/www/uploads;
    }
    
    location /cgi-bin {
        root /var/www/cgi-bin;
        cgi_pass .php /usr/bin/php-cgi;
        allowed_methods GET POST;
    }
}

# 複数のサーバーブロックを定義可能
server {
    listen 8081;
    # ... その他の設定
}
```

## 実装詳細

### ノンブロッキングI/O
サーバーはノンブロッキングI/Oとpoll()（または同等機能）を使用して、スレッドや各接続ごとのフォークを使わずに複数のクライアント接続を同時に処理します。

### CGI処理
CGIスクリプトに関して：
- サーバーはファイル拡張子に基づいてリクエストをCGIスクリプトに渡します
- CGI環境変数はHTTP/1.1仕様に従って設定されます
- 標準入力と標準出力は適切に処理されます

### エラー処理
- サーバーは適切なHTTPステータスコードを提供します
- カスタムエラーページを設定できます
- クライアント切断を適切に処理します

## テスト

サーバーは以下を使用してテストできます：
- 標準的なWebブラウザ（Chrome、Firefox、Safariなど）
- コマンドラインツール（curl、wget）
- 生のHTTPリクエスト用Telnet
- カスタムテストスクリプト（Python、Goなどの言語での実装を推奨）

## プロジェクト構造

```
webserv/
├── src/            # ソースコード
├── include/        # ヘッダーファイル
├── config/         # 設定ファイル例
├── www/            # Webコンテンツ例
├── tests/          # テストスクリプト
├── Makefile        # ビルド設定
└── README.md       # このファイル
```

## 標準準拠
- HTTP/1.1 (RFC 2616)
- C++98標準
- NGINX風の設定ファイル形式



# Webserv - HTTPサーバ実装

C++98で実装された堅牢なHTTP/1.1サーバ。ノンブロッキングI/O、CGI対応、仮想ホスト機能などを備えた軽量サーバです。

## 🚀 主な機能

- **HTTP/1.1 対応** - 標準に準拠したプロトコル実装  
- **ノンブロッキングI/O** - `poll()` を用いた効率的な接続処理  
- **HTTPメソッド対応** - GET / POST / DELETE  
- **CGI実行機能** - PHP・PythonなどのCGIスクリプト実行に対応  
- **ファイルアップロード** - `multipart/form-data` のPOSTリクエスト処理  
- **静的ファイル配信** - HTML / CSS / JS / 画像などの提供  
- **ディレクトリリスティング** - 自動的なディレクトリ一覧表示  
- **仮想ホスト対応** - 複数のポートで異なる設定を適用可能  
- **カスタムエラーページ** - 任意のエラーページを設定可能  
- **NGINX風設定ファイル** - 柔軟なサーバ設定が可能  
- **メモリリーク無し** - 安全なメモリ管理を徹底  

## 📁 プロジェクト構成

```
webserv/
├── Makefile                 # ビルド設定
├── README.md               # このファイル
├── default.conf            # デフォルトのサーバ設定
├── inc/                    # ヘッダファイル群
│   ├── webserv.hpp         
│   ├── Server.hpp          
│   ├── Config.hpp          
│   ├── Request.hpp         
│   ├── Response.hpp        
│   ├── Location.hpp        
│   ├── CGI.hpp             
│   └── HttpParser.hpp      
├── src/                    # ソースコード
│   ├── main.cpp            
│   ├── Server.cpp          
│   ├── Config.cpp          
│   ├── Request.cpp         
│   ├── Response.cpp        
│   ├── Location.cpp        
│   ├── CGI.cpp             
│   ├── HttpParser.cpp      
│   └── Utils.cpp           
└── www/                    # デフォルトのWebルート
    ├── index.html          
    ├── test.php            
    ├── test.py             
    └── upload/
        └── index.html      
```

## 🛠️ ビルド方法

### 必須環境

- C++98 対応のC++コンパイラ（g++, clang++など）
- `make` コマンド
- UNIX系OS（Linux, macOS）
- 任意：PHP-CGI、Python3（CGIテスト用）

### コンパイル手順

```bash
# リポジトリをクローン
git clone <repository-url>
cd webserv

# ビルド
make

# 中間ファイル削除
make clean

# 実行ファイルも含めて削除
make fclean

# 再ビルド
make re
```

## 🚀 使用方法

### 基本実行

```bash
# デフォルト設定で起動
./webserv

# 任意の設定ファイルで起動
./webserv path/to/config.conf

# ヘルプ表示
./webserv --help

# バージョン表示
./webserv --version
```

### 初期セットアップ

初回起動時に以下が作成されます：

1. `./www` ディレクトリ（Webファイル置き場）
2. `./uploads` ディレクトリ（アップロード先）
3. `index.html` の初期ページ
4. `http://localhost:8080` で待機

## 🔍 テスト方法

### 基本テスト

```bash
curl http://localhost:8080/
```

### CGIスクリプトの確認

```bash
# PHP
curl http://localhost:8080/test.php

# Python
curl http://localhost:8080/test.py
```

### ファイルアップロード

```bash
curl -X POST -F "file=@example.txt" http://localhost:8080/upload
```

### ブラウザでの確認

`http://localhost:8080` にアクセスしてください。

## ⚙️ 設定ファイル構文（NGINX風）

```nginx
server {
    listen 0.0.0.0:8080;
    server_name localhost;
    root ./www;
    index index.html index.php;
    client_max_body_size 10M;

    error_page 404 /error_pages/404.html;
    error_page 500 502 503 504 /error_pages/50x.html;

    location / {
        root ./www;
        allow_methods GET POST DELETE;
        autoindex on;
    }

    location ~ \.php$ {
        root ./www;
        allow_methods GET POST;
        cgi_extension .php /usr/bin/php-cgi;
    }

    location /upload {
        root ./www;
        allow_methods GET POST;
        upload_path ./uploads/;
        client_max_body_size 50M;
    }
}
```

## 🔧 よくあるトラブルと対処法

### 1. ポートが使用中

```bash
lsof -i :8080
# → 他プロセスが使用中か確認、必要に応じて設定変更
```

### 2. CGIスクリプトが動作しない

- `php-cgi` や `python3` がインストールされているか確認
- `chmod +x` で実行権限を付与
- configの `cgi_extension` を確認

### 3. アップロードできない

- `uploads/` ディレクトリの権限を確認
- `client_max_body_size` の設定を確認
- ディレクトリの存在確認

### 4. パーミッションエラー

```bash
chmod 755 ./www ./uploads
chmod 644 ./www/*
```

## 🔒 セキュリティ考慮事項

- HTTPヘッダーのバリデーション
- パストラバーサル防止
- アップロード制限
- CGIの制限実行
- タイムアウトやボディサイズの制限

## 🧪 HTTP 準拠内容

- HTTP/1.1 準拠
- Keep-Alive対応
- Chunked Transfer Encoding
- Content-Length管理
- ステータスコード・ヘッダー・URI解析対応

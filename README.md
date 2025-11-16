# minitalk
## 課題要件
Name your executable files client and server.
• You must submit a Makefile that compiles your source files. It must not perform
unnecessary relinking.
• You are allowed to use your libft.
• Youhavetohandleerrorsthoroughly. Undernocircumstancesshouldyourprogram
quit unexpectedly (segmentation fault, bus error, double free, and so forth).
• Your program must be free of memory leaks.
• You are allowed to use one global variable per program (one for the client and
one for the server), but its usage must be justified.
• To complete the mandatory part, you are allowed to use the following functions:
◦ write
◦ ft_printf or any equivalent YOU coded
◦ signal
◦ sigemptyset
◦ sigaddset
◦ sigaction
◦ kill
◦ getpid
◦ malloc
◦ free
◦ pause
◦ sleep
◦ usleep
◦ exit
7
Chapter V
Mandatory Part
You must create a communication program in the form of a client and a server.
• The server must be started first. Upon launch, it must print its PID.
• The client takes two parameters:
◦ The server PID.
◦ The string to send.
• The client must send the specified string to the server.
Once received, the server must print it.
• The server must display the string without delay. If it seems slow, it is likely too
slow.
If displaying 100 characters takes 1 second, the program is too slow!
• Your server should be able to receive strings from several clients in a row without
needing to restart.
• Communication between the client and server must exclusively use UNIX signals.
• You can only use these two signals: SIGUSR1 and SIGUSR2.
Linux system does NOT queue signals when you already have pending
signals of this type! Bonus time?

## ファイルの確認
```ls -la```

## サーバーの起動
```./server```

結果例
```
./server
42241
```
ここで出てくる番号がプロセスID（PID）。

## 通信の仕組み
minitalkは**UNIXシグナルのみ**を使用して文字を送信します：
- `SIGUSR1` = ビット`1`
- `SIGUSR2` = ビット`0`

文字の各ビット（8ビット）を順番に送信して1文字を構成します。

例：文字`'A'` (ASCII 65 = `01000001`)
```
ビット0(1) → SIGUSR1送信
ビット1(0) → SIGUSR2送信  
ビット2(0) → SIGUSR2送信
...
ビット7(0) → SIGUSR2送信
```

## クライアントの実行
別のターミナルでクライアントを実行。
```
./client 95922 'Hello, minitalk!'
```
または
```
# エスケープを使用
./client 95922 \"Hello, minitalk!\"
```

## 推奨テストケース

### 1. 基本テスト
```bash
./client [PID] 'Hello'
./client [PID] '42'
./client [PID] 'ABC123'
```

### 2. 特殊文字テスト
```bash
./client [PID] '!@#$%^&*()'
./client [PID] 'Hello, World!'
./client [PID] 'Test with spaces'
```

### 3. 長文テスト
```bash
./client [PID] 'This is a very long message to test the reliability of minitalk.'
```

### 4. 文字コードテスト
```bash
./client [PID] 'abcdefghijklmnopqrstuvwxyz'
./client [PID] 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
./client [PID] '0123456789'
```

### 5. エラーハンドリングテスト
```bash
# 引数不足
./client

# 無効なPID
./client abc 'test'
./client -1 'test'
./client 0 'test'

# 存在しないPID（エラーメッセージが表示される）
./client 99999 'test'
```

**期待される動作：**
- 引数不足 → Usage表示
- 無効なPID → Usage表示  
- 存在しないPID → "Failed to send signal (invalid PID?)" エラー

### 6. 連続送信テスト（重要）
```bash
# サーバーを1回だけ起動
./server

# 別のターミナルで複数のメッセージを連続送信
./client [PID] 'Message1'
./client [PID] 'Message2' 
./client [PID] 'Message3'

# または一度に実行
./client [PID] 'Msg1' && ./client [PID] 'Msg2' && ./client [PID] 'Msg3'
```

**期待される動作：**
- サーバーは再起動せずに全てのメッセージを受信
- 各メッセージが順番に表示される
- サーバープロセスは継続して動作する

**サーバー側の出力例：**
```
12345
Message1
Message2
Message3
```

## トラブルシューティング

### 文字化け・無限ループが発生する場合

**問題が確認されている文字：**
- 大文字: `'Hello'` → `'hello'`は正常
- 数字: `'42tokyo'` → 数字を含む文字列で問題発生

**対処法：**
1. サーバーを`Ctrl+C`で停止
2. `make clean && make`で再ビルド
3. 新しいサーバーを起動
4. 簡単なテスト（`'hello'`など）から開始

**デバッグ用テスト順序：**
```bash
./client [PID] 'a'      # 単一小文字
./client [PID] 'A'      # 単一大文字  
./client [PID] '1'      # 単一数字
./client [PID] 'hello'  # 小文字のみ
./client [PID] 'Hello'  # 大文字混在
./client [PID] '42'     # 数字のみ
```
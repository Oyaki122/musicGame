## 現在の問題

### 判定

- ボタンを押したときに複数判定される可能性がある
- やたら複雑

### 描画

- ミスとかのときに色とかを変更できない
- 色とかホールドとかはまだ

### 送り出し

- 同じタイミングにノーツを配置できない　 ← 　ジョイスティック型だから問題ないかも

### その他

- ボタン操作系統の実装
- 音声同期の実装
- 効果音系統
- タイムキーパーの実装

## 描画について

同じ配列を参照しているのでそのインデックスで判定と描画を結びつけることはできる

1. ノートの流れる速さから描画開始時間を求める
1. ノーツの配列の未処理のものの先頭と描画開始時間を比較して描画開始しないといけないか判断する
1. 描画開始する必要があったら描画リストにノートを入れる
1. 描画リストにあるノーツを描画のたびに調べ、それを元に描画位置を求める
1. 判定がインデックスで描画終了するノーツを指定し、描画側に命令する
1. ホールドはホールド開始からホールド終端まで色を埋めるようにする。
1. ホールド開始は判定で保持中になったら特殊なリストに入れ、判定線からホールド終端まで色を埋めることにする

- ノーマル 普通
- ホールド等開始 ここからホールド終端 or 画面端まで塗る、判定点で bad されなければホールドリストに入れ、判定店から終端まで色を塗る
- ホールド等終端 ここまで塗る、ホールド終端が判定点に来たらホールドリストをリセットする
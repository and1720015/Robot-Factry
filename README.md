# ロボット工場

「あととかたち展」（http://myu-design.jp/atokata）
にて展示したメディアアート「ロボット工場」。

宮城大学のデザイン新棟にて展示が決定したので共有のため作成。<br>
データは学内の最終講評会時点のもの。<br>
「read-me」ファイルに当時の謎のメモ書き記載。

## 現場での操作
実行画面左上のグレースケール映像はKinect視点のもの、輪郭を検出している<br>
Kinect映像上のGUIを操作してKinectの輪郭検知の感度を調整（本番のときは151行目のGUIをコメントアウトして非表示にする）<br>
投影されるロボットの映像の幅に合わせてKinectが拾う幅の数値を書き換える（クリックでxとyの座標がcoutされるのでそちらを参考にする）

現場の状況により微細な調整が必要

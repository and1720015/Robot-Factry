# ロボット工場

「あととかたち展」（http://myu-design.jp/atokata）
にて展示したメディアアート「ロボット工場」。

宮城大学のデザイン新棟にて展示が決定したので共有のため作成。<br>
データは学内の最終講評会時点のもの。<br>
「read-me」ファイルに当時の謎のメモ書き記載。

## 現場での操作
* 実行画面左上のグレースケール映像はKinect視点のもの、輪郭を検出している
* Kinect映像上のGUIを操作してKinectの輪郭検知の感度を調整（本番のときは151行目のGUIをコメントアウトして非表示にする）
* 投影されるロボットの映像の幅に合わせてKinectが拾う幅の数値を書き換える（238行目で調整、クリックでxとyの座標がcoutされるのでそちらを参考にする）
* その入れ子の中はペンキが配置される範囲なのでこちらも現場に合わせて書き換える
* もしペンキがつきすぎて（ボール以外の輪郭にも反応しすぎて）落ちそうになったら、239行目のclick回数を少なくしてペンキの数を制限する
* 使用するPCによりウィンドウサイズが異なるため画像がズレることがあるが、あまりにも酷い場合はその場でイラレ等使い全てリサイズ<br>＊画像データはbin/dataの中<br>＊この時271行目の数値も変えなければループがストップするので注意

現場の状況により微細な調整が必要

## 参考：PCにKinectV2を入れる
https://github.com/umetaman/preparing_kv2_for_of
